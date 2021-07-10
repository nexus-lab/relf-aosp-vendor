#ifndef RELF_STRUCT_STAT_VFS_PARCEL_H
#define RELF_STRUCT_STAT_VFS_PARCEL_H

#include <binder/Parcelable.h>

using namespace android;

namespace org {
namespace nexus_lab {
namespace relf {
namespace service {
namespace parcel {

class ParcelStructStatvfs : public Parcelable {
public:
    int64_t f_bsize;   /* Filesystem block size */
    int64_t f_frsize;  /* Fragment size */
    int64_t f_blocks;  /* Size of fs in f_frsize units */
    int64_t f_bfree;   /* Number of free blocks */
    int64_t f_bavail;  /* Number of free blocks for unprivileged users */
    int64_t f_files;   /* Number of inodes */
    int64_t f_ffree;   /* Number of free inodes */
    int64_t f_favail;  /* Number of free inodes for unprivileged users */
    int64_t f_fsid;    /* Filesystem ID */
    int64_t f_flag;    /* Mount flags */
    int64_t f_namemax; /* Maximum filename length */

    status_t writeToParcel(Parcel *parcel) const override;
    status_t readFromParcel(const Parcel *parcel) override;

};  // class ParcelStructStat
}  // namespace parcel
}  // namespace service
}  // namespace relf
}  // namespace nexus_lab
}  // namespace org

#endif  // RELF_STRUCT_STAT_VFS_PARCEL_H
