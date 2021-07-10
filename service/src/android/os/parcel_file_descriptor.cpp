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
    return parcel->writeParcelFileDescriptor(fd_, commChannel_);
}

status_t ParcelFileDescriptor::readFromParcel(const Parcel* parcel) {
    fd_ = parcel->readParcelFileDescriptor(commChannel_);
    if (fd_ == -1) {
        return BAD_VALUE;
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
