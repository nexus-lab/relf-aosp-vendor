#include <binder/Parcel.h>
#include <binder/Parcelable.h>
#include <org/nexus_lab/relf/service/BnRelfService.h>
#include <limits>

using namespace std;
using namespace android;
using namespace android::binder;
using namespace org::nexus_lab::relf::service::parcel;

namespace org {
namespace nexus_lab {
namespace relf {
namespace service {

status_t _writeParcelable(Parcel& parcel, const Parcelable& parcelable) {
    status_t status = parcel.writeInt32(1);  // parcelable is not null.
    if (status != OK) {
        return status;
    }
    return parcelable.writeToParcel(&parcel);
}

status_t _writeString16Vector(Parcel& parcel, const vector<String16>& val) {
    if (val.size() > std::numeric_limits<int32_t>::max()) {
        return BAD_VALUE;
    }
    status_t status = parcel.writeInt32(static_cast<int32_t>(val.size()));
    if (status != OK) {
        return status;
    }
    for (const auto& item : val) {
        status = parcel.writeString16(item);
        if (status != OK) {
            return status;
        }
    }
    return OK;
}

template <typename T>
status_t _writeParcelableVector(Parcel& parcel, const vector<T>& val) {
    if (val.size() > std::numeric_limits<int32_t>::max()) {
        return BAD_VALUE;
    }
    status_t status = parcel.writeInt32(static_cast<int32_t>(val.size()));
    if (status != OK) {
        return status;
    }
    for (const auto& item : val) {
        status = _writeParcelable(parcel, item);
        if (status != OK) {
            return status;
        }
    }
    return OK;
}

IRelfService::IRelfService() {}
IRelfService::~IRelfService() {}

const android::String16 IRelfService::descriptor("org.nexus_lab.relf.service.IRelfService");

const android::String16& IRelfService::getInterfaceDescriptor() const { return IRelfService::descriptor; }

status_t BnRelfService::onTransact(uint32_t code, const Parcel& data, Parcel* reply, uint32_t flags) {
    status_t status = OK;
    switch (code) {
        case Call::STAT: {
            String16 in_path;
            ParcelStructStat retval;
            if (!(data.checkInterface(this))) {
                status = BAD_TYPE;
                break;
            }
            in_path = data.readString16();
            if (in_path.size() <= 0) {
                status = BAD_VALUE;  // UNEXPECTED_NULL
                break;
            }
            Status ret_status(stat(in_path, &retval));
            status = ret_status.writeToParcel(reply);
            if (status != OK) {
                break;
            }
            if (!ret_status.isOk()) {
                break;
            }
            status = _writeParcelable(*reply, retval);
            if (status != OK) {
                break;
            }
        } break;
        case Call::LSTAT: {
            String16 in_path;
            ParcelStructStat retval;
            if (!(data.checkInterface(this))) {
                status = BAD_TYPE;
                break;
            }
            in_path = data.readString16();
            if (in_path.size() <= 0) {
                status = BAD_VALUE;
                break;
            }
            Status ret_status(lstat(in_path, &retval));
            status = ret_status.writeToParcel(reply);
            if (status != OK) {
                break;
            }
            if (!ret_status.isOk()) {
                break;
            }
            status = _writeParcelable(*reply, retval);
            if (status != OK) {
                break;
            }
        } break;
        case Call::STATVFS: {
            String16 in_path;
            ParcelStructStatvfs retval;
            if (!(data.checkInterface(this))) {
                status = BAD_TYPE;
                break;
            }
            in_path = data.readString16();
            if (in_path.size() <= 0) {
                status = BAD_VALUE;
                break;
            }
            Status ret_status(statvfs(in_path, &retval));
            status = ret_status.writeToParcel(reply);
            if (status != OK) {
                break;
            }
            if (!ret_status.isOk()) {
                break;
            }
            status = _writeParcelable(*reply, retval);
            if (status != OK) {
                break;
            }
        } break;
        case Call::READLINK: {
            String16 in_path;
            String16 retval;
            if (!(data.checkInterface(this))) {
                status = BAD_TYPE;
                break;
            }
            in_path = data.readString16();
            if (in_path.size() <= 0) {
                status = BAD_VALUE;
                break;
            }
            Status ret_status(readlink(in_path, &retval));
            status = ret_status.writeToParcel(reply);
            if (status != OK) {
                break;
            }
            if (!ret_status.isOk()) {
                break;
            }
            status = reply->writeString16(retval);
            if (status != OK) {
                break;
            }
        } break;
        case Call::REALPATH: {
            String16 in_path;
            String16 retval;
            if (!(data.checkInterface(this))) {
                status = BAD_TYPE;
                break;
            }
            in_path = data.readString16();
            if (in_path.size() <= 0) {
                status = BAD_VALUE;
                break;
            }
            Status ret_status(realpath(in_path, &retval));
            status = ret_status.writeToParcel(reply);
            if (status != OK) {
                break;
            }
            if (!ret_status.isOk()) {
                break;
            }
            status = reply->writeString16(retval);
            if (status != OK) {
                break;
            }
        } break;
        case Call::LISTDIR: {
            String16 in_path;
            vector<String16> retval;
            if (!(data.checkInterface(this))) {
                status = BAD_TYPE;
                break;
            }
            in_path = data.readString16();
            if (in_path.size() <= 0) {
                status = BAD_VALUE;
                break;
            }
            Status ret_status(listdir(in_path, &retval));
            status = ret_status.writeToParcel(reply);
            if (status != OK) {
                break;
            }
            if (!ret_status.isOk()) {
                break;
            }
            status = _writeString16Vector(*reply, retval);
            if (status != OK) {
                break;
            }
        } break;
        case Call::PIPE: {
            ParcelFileDescriptor in_pipe;
            String16 in_path;
            int32_t has_fd;
            int64_t in_offset;
            int64_t in_length;
            if (!(data.checkInterface(this))) {
                status = BAD_TYPE;
                break;
            }
            status = data.readInt32(&has_fd);
            if (status != OK) {
                break;
            }
            if (has_fd != 1) {
                status = BAD_VALUE;
                break;
            }
            status = in_pipe.readFromParcel(&data);
            if (status != OK) {
                break;
            }
            in_path = data.readString16();
            if (in_path.size() <= 0) {
                status = BAD_VALUE;
                break;
            }
            status = data.readInt64(&in_offset);
            if (status != OK) {
                break;
            }
            status = data.readInt64(&in_length);
            if (status != OK) {
                break;
            }
            Status ret_status(pipe(in_pipe, in_path, in_offset, in_length));
        } break;
        case Call::GETPWUID: {
            int32_t in_uid;
            ParcelStructPasswd retval;
            if (!(data.checkInterface(this))) {
                status = BAD_TYPE;
                break;
            }
            status = data.readInt32(&in_uid);
            if (status != OK) {
                break;
            }
            Status ret_status(getpwuid(in_uid, &retval));
            status = ret_status.writeToParcel(reply);
            if (status != OK) {
                break;
            }
            if (!ret_status.isOk()) {
                break;
            }
            status = _writeParcelable(*reply, retval);
            if (status != OK) {
                break;
            }
        } break;
        case Call::GETPWENT: {
            vector<ParcelStructPasswd> retval;
            if (!(data.checkInterface(this))) {
                status = BAD_TYPE;
                break;
            }
            Status ret_status(getpwent(&retval));
            status = ret_status.writeToParcel(reply);
            if (status != OK) {
                break;
            }
            if (!ret_status.isOk()) {
                break;
            }
            status = _writeParcelableVector(*reply, retval);
            if (status != OK) {
                break;
            }
        } break;
        default: { status = BBinder::onTransact(code, data, reply, flags); } break;
    }
    if (status == BAD_VALUE) {  // UNEXPECTED_NULL
        status = Status::fromExceptionCode(Status::EX_NULL_POINTER).writeToParcel(reply);
    }
    return status;
}

}  // namespace service
}  // namespace relf
}  // namespace nexus_lab
}  // namespace org
