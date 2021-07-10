#ifndef RELF_STRUCT_PASSWD_PARCEL_H
#define RELF_STRUCT_PASSWD_PARCEL_H

#include <binder/Parcelable.h>

using namespace android;

namespace org {
namespace nexus_lab {
namespace relf {
namespace service {
namespace parcel {

class ParcelStructPasswd : public Parcelable {
public:
    String16 pw_name;   /* Username. */
    String16 pw_passwd; /* Password. */
    int32_t pw_uid;     /* User ID. */
    int32_t pw_gid;     /* Group ID. */
    String16 pw_gecos;  /* Real name. */
    String16 pw_dir;    /* Home directory. */
    String16 pw_shell;  /* Shell program. */

    status_t writeToParcel(Parcel *parcel) const override;
    status_t readFromParcel(const Parcel *parcel) override;

};  // class ParcelStructPasswd
}  // namespace parcel
}  // namespace service
}  // namespace relf
}  // namespace nexus_lab
}  // namespace org

#endif  // RELF_STRUCT_PASSWD_PARCEL_H
