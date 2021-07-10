#include <org/nexus_lab/relf/service/common.h>
#include <org/nexus_lab/relf/service/parcel/ParcelStructPasswd.h>

#include <binder/Parcel.h>

using namespace android;
using namespace org::nexus_lab::relf::service::parcel;

status_t ParcelStructPasswd::readFromParcel(const Parcel *p) {
    READ_PARCEL_STRING_OR_RETURN(pw_name)
    READ_PARCEL_STRING_OR_RETURN(pw_passwd)
    READ_PARCEL_INT32_OR_RETURN(pw_uid)
    READ_PARCEL_INT32_OR_RETURN(pw_gid)
    READ_PARCEL_STRING_OR_RETURN(pw_gecos)
    READ_PARCEL_STRING_OR_RETURN(pw_dir)
    READ_PARCEL_STRING_OR_RETURN(pw_shell)
    return OK;
}

status_t ParcelStructPasswd::writeToParcel(Parcel *p) const {
    WRITE_PARCEL_STRING_OR_RETURN(pw_name)
    WRITE_PARCEL_STRING_OR_RETURN(pw_passwd)
    WRITE_PARCEL_INT32_OR_RETURN(pw_uid)
    WRITE_PARCEL_INT32_OR_RETURN(pw_gid)
    WRITE_PARCEL_STRING_OR_RETURN(pw_gecos)
    WRITE_PARCEL_STRING_OR_RETURN(pw_dir)
    WRITE_PARCEL_STRING_OR_RETURN(pw_shell)
    return OK;
}
