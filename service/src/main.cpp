#define LOG_TAG "relf_service"

#define SERVICE_NAME "relf_service"

#include <org/nexus_lab/relf/service/RelfService.h>
#include <org/nexus_lab/relf/service/IRelfService.h>

#include <binder/IPCThreadState.h>
#include <binder/IServiceManager.h>
#include <binder/ProcessState.h>
#include <utils/Log.h>

using namespace std;
using namespace android;
using namespace android::binder;
using namespace org::nexus_lab::relf::service;


int main(int argc, char **argv) {
    defaultServiceManager()->addService(String16(SERVICE_NAME), new RelfService());
    ALOGD("service registered");
    ProcessState::self()->startThreadPool();
    IPCThreadState::self()->joinThreadPool();
    return 0;
}
