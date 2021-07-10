#ifndef I_RELF_SERVICE_H
#define I_RELF_SERVICE_H

#include <android/os/parcel_file_descriptor.h>
#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <org/nexus_lab/relf/service/parcel/ParcelStructPasswd.h>
#include <org/nexus_lab/relf/service/parcel/ParcelStructStat.h>
#include <org/nexus_lab/relf/service/parcel/ParcelStructStatvfs.h>
#include <utils/String16.h>
#include <utils/StrongPointer.h>
#include <cstdint>
#include <vector>

using namespace android;
using namespace std;
using namespace android::binder;
using namespace android::os;
using namespace org::nexus_lab::relf::service::parcel;

namespace org {
namespace nexus_lab {
namespace relf {
namespace service {

class IRelfService : public IInterface {
public:
    DECLARE_META_INTERFACE(RelfService)

    virtual Status stat(const String16& path, ParcelStructStat* retval) = 0;
    virtual Status lstat(const String16& path, ParcelStructStat* retval) = 0;
    virtual Status statvfs(const String16& path, ParcelStructStatvfs* retval) = 0;
    virtual Status readlink(const String16& path, String16* retval) = 0;
    virtual Status realpath(const String16& path, String16* retval) = 0;
    virtual Status listdir(const String16& path, vector<String16>* retval) = 0;
    virtual Status pipe(const ParcelFileDescriptor& pipe, const String16& path, int64_t offset, int64_t length) = 0;
    virtual Status getpwuid(int32_t uid, ParcelStructPasswd* retval) = 0;
    virtual Status getpwent(vector<ParcelStructPasswd>* retval) = 0;

    enum Call {
        STAT = IBinder::FIRST_CALL_TRANSACTION + 0,
        LSTAT = IBinder::FIRST_CALL_TRANSACTION + 1,
        STATVFS = IBinder::FIRST_CALL_TRANSACTION + 2,
        READLINK = IBinder::FIRST_CALL_TRANSACTION + 3,
        REALPATH = IBinder::FIRST_CALL_TRANSACTION + 4,
        LISTDIR = IBinder::FIRST_CALL_TRANSACTION + 5,
        PIPE = IBinder::FIRST_CALL_TRANSACTION + 6,
        GETPWUID = IBinder::FIRST_CALL_TRANSACTION + 7,
        GETPWENT = IBinder::FIRST_CALL_TRANSACTION + 8,
    };
};  // class IRelfService

}  // namespace service
}  // namespace relf
}  // namespace nexus_lab
}  // namespace org

#endif  // I_RELF_SERVICE_H
