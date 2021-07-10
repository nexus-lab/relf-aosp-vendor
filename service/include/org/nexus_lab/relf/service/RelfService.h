#include <org/nexus_lab/relf/service/BnRelfService.h>

using namespace std;
using namespace android;
using namespace android::os;
using namespace android::binder;
using namespace org::nexus_lab::relf::service;
using namespace org::nexus_lab::relf::service::parcel;

namespace org {
namespace nexus_lab {
namespace relf {
namespace service {

class RelfService : public BnRelfService {
public:
    Status stat(const String16 &path, ParcelStructStat *retval) override;
    Status lstat(const String16 &path, ParcelStructStat *retval) override;
    Status statvfs(const String16 &path, ParcelStructStatvfs *retval) override;
    Status readlink(const String16 &path, String16 *retval) override;
    Status realpath(const String16 &path, String16 *retval) override;
    Status listdir(const String16 &path, vector<String16> *retval) override;
    Status pipe(const ParcelFileDescriptor &pipe, const String16 &path, int64_t offset, int64_t length) override;
    Status getpwuid(int32_t uid, ParcelStructPasswd *retval) override;
    Status getpwent(vector<ParcelStructPasswd> *retval) override;
};

}  // namespace service
}  // namespace relf
}  // namespace nexus_lab
}  // namespace org
