#include <org/nexus_lab/relf/service/common.h>
#include <org/nexus_lab/relf/service/RelfService.h>

#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <limits.h>
#include <private/android_filesystem_config.h>
#include <pthread.h>
#include <pwd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/statvfs.h>
#include <sys/types.h>
#include <utils/String8.h>

using namespace std;
using namespace android;
using namespace android::binder;
using namespace org::nexus_lab::relf::service;
using namespace org::nexus_lab::relf::service::parcel;

namespace org {
namespace nexus_lab {
namespace relf {
namespace service {

struct _pipe_args {
    int ffd;
    int pfd;
    long skip;
    long len;
};
typedef struct _pipe_args pipe_args;

const char *string16_to_char(const String16 &str) {
    return String8(str).string();
}

int is_fd_valid(int fd) {
    return errno != EBADF || fcntl(fd, F_GETFD) != -1;
}

void fill_stat_parcel(const struct stat st, ParcelStructStat *p) {
    p->st_dev = st.st_dev;
    p->st_ino = st.st_ino;
    p->st_mode = st.st_mode;
    p->st_nlink = st.st_nlink;
    p->st_uid = st.st_uid;
    p->st_gid = st.st_gid;
    p->st_rdev = st.st_rdev;
    p->st_size = st.st_size;
    p->st_blksize = st.st_blksize;
    p->st_blocks = st.st_blocks;
    p->st_atime_ = st.st_atime;
    p->st_mtime_ = st.st_mtime;
    p->st_ctime_ = st.st_ctime;
}

Status RelfService::stat(const String16 &path, ParcelStructStat *retval) {
    struct stat st;
    if (::stat(string16_to_char(path), &st) != 0) {
        return ERRNO_EXCEPTION();
    }
    fill_stat_parcel(st, retval);
    return Status::ok();
}

Status RelfService::lstat(const String16 &path, ParcelStructStat *retval) {
    struct stat st;
    if (::lstat(string16_to_char(path), &st) != 0) {
        return ERRNO_EXCEPTION();
    }
    fill_stat_parcel(st, retval);
    return Status::ok();
}

Status RelfService::statvfs(const String16 &path, ParcelStructStatvfs *retval) {
    struct statvfs st;
    if (::statvfs(string16_to_char(path), &st) != 0) {
        return ERRNO_EXCEPTION();
    }
    retval->f_bsize = st.f_bsize;
    retval->f_frsize = st.f_frsize;
    retval->f_blocks = st.f_blocks;
    retval->f_bfree = st.f_bfree;
    retval->f_bavail = st.f_bavail;
    retval->f_files = st.f_files;
    retval->f_ffree = st.f_ffree;
    retval->f_favail = st.f_favail;
    retval->f_fsid = st.f_fsid;
    retval->f_flag = st.f_flag;
    retval->f_namemax = st.f_namemax;
    return Status::ok();
}

Status RelfService::readlink(const String16 &path, String16 *retval) {
    char buf[PATH_MAX + 1];
    ssize_t len = ::readlink(string16_to_char(path), buf, sizeof(buf) - 1);
    if (len == -1) {
        return ERRNO_EXCEPTION();
    }
    buf[len] = '\0';
    *retval = String16(buf);
    return Status::ok();
}

Status RelfService::realpath(const String16 &path, String16 *retval) {
    char buf[PATH_MAX + 1];
    char *res = ::realpath(string16_to_char(path), buf);
    if (!res) {
        return ERRNO_EXCEPTION();
    }
    *retval = String16(buf);
    return Status::ok();
}

Status RelfService::listdir(const String16 &path, vector<String16> *retval) {
    struct dirent *dir;
    DIR *d = opendir(string16_to_char(path));
    if (d) {
        while ((dir = readdir(d)) != NULL) {
            if (strcmp(".", dir->d_name) == 0 || strcmp("..", dir->d_name) == 0) {
                continue;
            }
            retval->push_back(String16(dir->d_name));
        }
        closedir(d);
    } else {
        return ERRNO_EXCEPTION();
    }
    return Status::ok();
}

void *write_file_to_pipe(void *_args) {
    long oread, lread;
    char buf[10 * 1024];
    pipe_args *args = (pipe_args *)_args;
    if (lseek(args->ffd, args->skip, SEEK_SET) == -1) {
        return NULL;
    }
    lread = args->len;
    while ((args->len == -1 || lread > 0) && is_fd_valid(args->pfd) &&
           (oread = read(args->ffd, buf, sizeof(buf))) > 0) {
        write(args->pfd, buf, (lread > oread || args->len == -1) ? oread : lread);
        lread -= oread;
    }
    close(args->ffd);
    close(args->pfd);
    free(_args);
    return NULL;
}

Status RelfService::pipe(const ParcelFileDescriptor &pipe, const String16 &path, int64_t offset, int64_t length) {
    const char *cpath = string16_to_char(path);
    int ffd = open(cpath, O_RDONLY);
    if (ffd == -1) {
        return ERRNO_EXCEPTION();
    }
    int pfd_old = pipe.fd();
    int pfd = dup(pfd_old);
    close(pfd_old);
    if (pfd == -1) {
        return ERRNO_EXCEPTION();
    }
    pthread_t tid;
    pipe_args *args = (pipe_args *)malloc(sizeof(pipe_args));
    args->ffd = ffd;
    args->pfd = pfd;
    args->skip = offset;
    args->len = length;
    if (pthread_create(&tid, NULL, write_file_to_pipe, (void *)args) != 0) {
        return ERRNO_EXCEPTION();
    }
    return Status::ok();
}

void fill_passwd(const passwd *pwd, ParcelStructPasswd *retval) {
    if (pwd->pw_name != NULL) {
        retval->pw_name = String16(pwd->pw_name);
    }
    if (pwd->pw_passwd != NULL) {
        retval->pw_passwd = String16(pwd->pw_passwd);
    }
    retval->pw_uid = pwd->pw_uid;
    retval->pw_gid = pwd->pw_gid;
    if (pwd->pw_gecos != NULL) {
        retval->pw_gecos = String16(pwd->pw_gecos);
    }
    if (pwd->pw_dir != NULL) {
        retval->pw_dir = String16(pwd->pw_dir);
    }
    if (pwd->pw_shell != NULL) {
        retval->pw_shell = String16(pwd->pw_shell);
    }
}

Status RelfService::getpwuid(int32_t uid, ParcelStructPasswd *retval) {
    struct passwd *pwd;
    if ((pwd = ::getpwuid(uid)) == NULL) {
        return ERRNO_EXCEPTION();
    }
    fill_passwd(pwd, retval);
    return Status::ok();
}

Status RelfService::getpwent(vector<ParcelStructPasswd> *retval) {
    int i;
    struct passwd *pwd;
    for (i = 0; i < AID_APP; i++) {
#ifdef AID_OEM_RESERVED_START
#ifdef AID_OEM_RESERVED_2_START
        if ((i >= AID_OEM_RESERVED_START && i <= AID_OEM_RESERVED_END) ||
            (i >= AID_OEM_RESERVED_2_START && i <= AID_OEM_RESERVED_2_END)) {
            continue;
        }
#else
        if (i >= AID_OEM_RESERVED_START && i <= AID_OEM_RESERVED_END) {
            continue;
        }
#endif
#endif
        if ((pwd = ::getpwuid(i)) != NULL) {
            ParcelStructPasswd p = ParcelStructPasswd();
            fill_passwd(pwd, &p);
            retval->push_back(p);
        }
    }
    return Status::ok();
}

}  // namespace service
}  // namespace relf
}  // namespace nexus_lab
}  // namespace org
