#include <org/nexus_lab/relf/service/common.h>
#include <org/nexus_lab/relf/service/parcel/ParcelStructStat.h>

#include <binder/Parcel.h>

using namespace android;
using namespace org::nexus_lab::relf::service::parcel;

status_t ParcelStructStat::readFromParcel(const Parcel *p) {
    READ_PARCEL_INT64_OR_RETURN(st_dev)
    READ_PARCEL_INT64_OR_RETURN(st_ino)
    READ_PARCEL_INT64_OR_RETURN(st_mode)
    READ_PARCEL_INT64_OR_RETURN(st_nlink)
    READ_PARCEL_INT64_OR_RETURN(st_uid)
    READ_PARCEL_INT64_OR_RETURN(st_gid)
    READ_PARCEL_INT64_OR_RETURN(st_rdev)
    READ_PARCEL_INT64_OR_RETURN(st_size)
    READ_PARCEL_INT64_OR_RETURN(st_blksize)
    READ_PARCEL_INT64_OR_RETURN(st_blocks)
    READ_PARCEL_INT64_OR_RETURN(st_atime_)
    READ_PARCEL_INT64_OR_RETURN(st_mtime_)
    READ_PARCEL_INT64_OR_RETURN(st_ctime_)
    return OK;
}

status_t ParcelStructStat::writeToParcel(Parcel *p) const {
    WRITE_PARCEL_INT64_OR_RETURN(st_dev)
    WRITE_PARCEL_INT64_OR_RETURN(st_ino)
    WRITE_PARCEL_INT64_OR_RETURN(st_mode)
    WRITE_PARCEL_INT64_OR_RETURN(st_nlink)
    WRITE_PARCEL_INT64_OR_RETURN(st_uid)
    WRITE_PARCEL_INT64_OR_RETURN(st_gid)
    WRITE_PARCEL_INT64_OR_RETURN(st_rdev)
    WRITE_PARCEL_INT64_OR_RETURN(st_size)
    WRITE_PARCEL_INT64_OR_RETURN(st_blksize)
    WRITE_PARCEL_INT64_OR_RETURN(st_blocks)
    WRITE_PARCEL_INT64_OR_RETURN(st_atime_)
    WRITE_PARCEL_INT64_OR_RETURN(st_mtime_)
    WRITE_PARCEL_INT64_OR_RETURN(st_ctime_)
    return OK;
}
