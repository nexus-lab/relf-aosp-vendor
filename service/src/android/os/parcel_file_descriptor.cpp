//
//  Copyright 2017, The Android Open Source Project
//
//  Licensed under the Apache License, Version 2.0 (the "License");
//  you may not use this file except in compliance with the License.
//  You may obtain a copy of the License at:
//
//  http://www.apache.org/licenses/LICENSE-2.0
//
//  Unless required by applicable law or agreed to in writing, software
//  distributed under the License is distributed on an "AS IS" BASIS,
//  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//  See the License for the specific language governing permissions and
//  limitations under the License.
//

#include "android/os/parcel_file_descriptor.h"

using android::OK;
using android::Parcel;
using android::status_t;

namespace android {
namespace os {

status_t ParcelFileDescriptor::writeToParcel(Parcel* parcel) const {
    status_t status;
    status = parcel->writeInt32(commChannel_ > -1 ? 1 : 0);
    if (status != OK) {
        return status;
    }
    status = parcel->writeDupFileDescriptor(fd_);
    if (status != OK) {
        return status;
    }
    if (commChannel_ > -1) {
        status = parcel->writeDupFileDescriptor(commChannel_);
        if (status != OK) {
            return status;
        }
    }
    return status;
}

status_t ParcelFileDescriptor::readFromParcel(const Parcel* parcel) {
    int hasCommChannel;
    status_t status;
    hasCommChannel = parcel->readInt32();
    if (status != OK) {
        return status;
    }
    fd_ = parcel->readFileDescriptor();
    if (fd_ < 0) {
        return BAD_VALUE;
    }
    if (hasCommChannel != 0) {
        commChannel_ = parcel->readFileDescriptor();
        if (commChannel_ < 0) {
            return BAD_VALUE;
        }
    }
    return OK;
}

void ParcelFileDescriptor::setFileDescriptor(int fd, int commChannel) {
    fd_ = fd;
    commChannel_ = commChannel;
}

int ParcelFileDescriptor::fd() const {
    return fd_;
}

}  // namespace os
}  // namespace android
