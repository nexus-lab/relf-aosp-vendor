#pragma once

#include <binder/IInterface.h>
#include <org/nexus_lab/relf/service/IRelfService.h>

using namespace android;

namespace org {
namespace nexus_lab {
namespace relf {
namespace service {

class BnRelfService : public BnInterface<IRelfService> {
public:
    status_t onTransact(uint32_t code, const Parcel& data, Parcel* reply, uint32_t flags = 0) override;
};  // class BnRelfService

}  // namespace service
}  // namespace relf
}  // namespace nexus_lab
}  // namespace org
