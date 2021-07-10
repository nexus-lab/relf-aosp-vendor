PRODUCT_PACKAGES += \
    relf_service \
    ReLF

PRODUCT_COPY_FILES += \
    vendor/relf/permissions/privapp-permissions.xml:system/etc/permissions/org.nexus_lab.relf.mobile.xml \
    vendor/relf/permissions/default-permissions.xml:system/etc/default-permissions/org.nexus_lab.relf.mobile.xml

include vendor/relf/sepolicy/sepolicy.mk
