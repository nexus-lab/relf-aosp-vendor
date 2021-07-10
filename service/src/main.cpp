#define LOG_TAG "relf_service"

#define SERVICE_NAME "relf_service"

#include <org/nexus_lab/relf/service/RelfService.h>
#include <org/nexus_lab/relf/service/IRelfService.h>

#include <binder/IPCThreadState.h>
#include <binder/IServiceManager.h>
#include <binder/ProcessState.h>
#include <private/android_filesystem_config.h>
#include <sys/capability.h>
#include <sys/prctl.h>
#include <utils/Log.h>

using namespace std;
using namespace android;
using namespace android::binder;
using namespace org::nexus_lab::relf::service;


static void drop_privileges() {
    if (prctl(PR_SET_KEEPCAPS, 1) < 0) {
        ALOGE("prctl(PR_SET_KEEPCAPS) failed: %s\n", strerror(errno));
        exit(1);
    }

    if (setgid(AID_SYSTEM) < 0) {
        ALOGE("setgid() can't drop privileges; exiting.\n");
        exit(1);
    }

    if (setuid(AID_SYSTEM) < 0) {
        ALOGE("setuid() can't drop privileges; exiting.\n");
        exit(1);
    }

    struct __user_cap_header_struct capheader;
    struct __user_cap_data_struct capdata[2];
    memset(&capheader, 0, sizeof(capheader));
    memset(&capdata, 0, sizeof(capdata));
    capheader.version = _LINUX_CAPABILITY_VERSION_3;
    capheader.pid = 0;

    capdata[CAP_TO_INDEX(CAP_DAC_READ_SEARCH)].permitted |= CAP_TO_MASK(CAP_DAC_READ_SEARCH);
    capdata[CAP_TO_INDEX(CAP_SYS_PTRACE)].permitted |= CAP_TO_MASK(CAP_SYS_PTRACE);

    capdata[0].effective = capdata[0].permitted;
    capdata[1].effective = capdata[1].permitted;
    capdata[0].inheritable = 0;
    capdata[1].inheritable = 0;

    if (capset(&capheader, &capdata[0]) < 0) {
        ALOGE("capset failed: %s\n", strerror(errno));
        exit(1);
    }
}

int main(int argc, char **argv) {
    drop_privileges();
    defaultServiceManager()->addService(String16(SERVICE_NAME), new RelfService());
    ALOGD("service registered");
    ProcessState::self()->startThreadPool();
    IPCThreadState::self()->joinThreadPool();
    return 0;
}
