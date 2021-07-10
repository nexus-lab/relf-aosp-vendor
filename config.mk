PRODUCT_PACKAGES += \
    relf_service \
    ReLF

PRODUCT_COPY_FILES += \
    vendor/relf/service/etc/relf_service.rc:root/init.relf_service.rc

include vendor/relf/sepolicy/sepolicy.mk
