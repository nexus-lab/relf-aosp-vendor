# In order to allow relf domain to grant itself as DAC_READ_SEARCH capability,
# the relf domain exception has to be added to the `system/sepolicy/public/domain.te`
# file. We disable policy split in Android P so that our relf domain in `domain.te` 
# can be recognized in the built public policy. This can also be resolved by putting 
# all relf sepolicy files under AOSP sepolicy folders.
PRODUCT_SEPOLICY_SPLIT_OVERRIDE := false
# Also, the `sepolicy_freeze_test` should be disabled.
BOARD_PLAT_PUBLIC_SEPOLICY_DIR += vendor/relf/sepolicy/public
BOARD_PLAT_PRIVATE_SEPOLICY_DIR += vendor/relf/sepolicy/private
