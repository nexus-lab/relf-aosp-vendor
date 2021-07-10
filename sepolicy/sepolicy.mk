BOARD_SEPOLICY_DIRS += \
    vendor/relf/sepolicy/public \
    vendor/relf/sepolicy/private
BOARD_SEPOLICY_UNION += \
    file_contexts \
    service_contexts \
    service.te \
    relf_service.te
