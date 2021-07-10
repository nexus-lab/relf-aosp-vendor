#include <org/nexus_lab/relf/service/common.h>
#include <org/nexus_lab/relf/service/parcel/ParcelStructStatvfs.h>

#include <binder/Parcel.h>

using namespace android;
using namespace org::nexus_lab::relf::service::parcel;

status_t ParcelStructStatvfs::readFromParcel(const Parcel *p) {
    READ_PARCEL_INT64_OR_RETURN(f_bsize)
    READ_PARCEL_INT64_OR_RETURN(f_frsize)
    READ_PARCEL_INT64_OR_RETURN(f_blocks)
    READ_PARCEL_INT64_OR_RETURN(f_bfree)
    READ_PARCEL_INT64_OR_RETURN(f_bavail)
    READ_PARCEL_INT64_OR_RETURN(f_files)
    READ_PARCEL_INT64_OR_RETURN(f_ffree)
    READ_PARCEL_INT64_OR_RETURN(f_favail)
    READ_PARCEL_INT64_OR_RETURN(f_fsid)
    READ_PARCEL_INT64_OR_RETURN(f_flag)
    READ_PARCEL_INT64_OR_RETURN(f_namemax)
    return OK;
}

status_t ParcelStructStatvfs::writeToParcel(Parcel *p) const {
    WRITE_PARCEL_INT64_OR_RETURN(f_bsize)
    WRITE_PARCEL_INT64_OR_RETURN(f_frsize)
    WRITE_PARCEL_INT64_OR_RETURN(f_blocks)
    WRITE_PARCEL_INT64_OR_RETURN(f_bfree)
    WRITE_PARCEL_INT64_OR_RETURN(f_bavail)
    WRITE_PARCEL_INT64_OR_RETURN(f_files)
    WRITE_PARCEL_INT64_OR_RETURN(f_ffree)
    WRITE_PARCEL_INT64_OR_RETURN(f_favail)
    WRITE_PARCEL_INT64_OR_RETURN(f_fsid)
    WRITE_PARCEL_INT64_OR_RETURN(f_flag)
    WRITE_PARCEL_INT64_OR_RETURN(f_namemax)
    return OK;
}
