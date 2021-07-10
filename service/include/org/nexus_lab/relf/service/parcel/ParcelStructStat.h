#ifndef RELF_STRUCT_STAT_PARCEL_H
#define RELF_STRUCT_STAT_PARCEL_H

#include <binder/Parcelable.h>

using namespace android;

namespace org {
namespace nexus_lab {
namespace relf {
namespace service {
namespace parcel {

class ParcelStructStat : public Parcelable {
public:
    int64_t st_dev;     /* ID of device containing file */
    int64_t st_ino;     /* inode number */
    int64_t st_mode;    /* protection */
    int64_t st_nlink;   /* number of hard links */
    int64_t st_uid;     /* user ID of owner */
    int64_t st_gid;     /* group ID of owner */
    int64_t st_rdev;    /* device ID (if special file) */
    int64_t st_size;    /* total size, in bytes */
    int64_t st_blksize; /* blocksize for file system I/O */
    int64_t st_blocks;  /* number of 512B blocks allocated */
    int64_t st_atime_;  /* time of last access */
    int64_t st_mtime_;  /* time of last modification */
    int64_t st_ctime_;  /* time of last status change */

    status_t writeToParcel(Parcel *parcel) const override;
    status_t readFromParcel(const Parcel *parcel) override;

};  // class ParcelStructStat
}  // namespace parcel
}  // namespace service
}  // namespace relf
}  // namespace nexus_lab
}  // namespace org

#endif  // RELF_STRUCT_STAT_PARCEL_H
