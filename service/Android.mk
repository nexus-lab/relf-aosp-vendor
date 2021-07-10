LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE := relf_service
LOCAL_MODULE_TAGS := optional
LOCAL_SRC_FILES := \
	$(call all-cpp-files-under, src) \
	$(call all-Iaidl-files-under, aidl)
LOCAL_AIDL_INCLUDES := \
	$(LOCAL_PATH)/aidl
LOCAL_SHARED_LIBRARIES := \
	libutils \
	libcutils \
	libbinder \
	liblog
LOCAL_C_INCLUDES += \
	frameworks/native/include \
	system/core/include \
	$(LOCAL_PATH)/include
LOCAL_INIT_RC := etc/relf_service.rc
include $(BUILD_EXECUTABLE)
