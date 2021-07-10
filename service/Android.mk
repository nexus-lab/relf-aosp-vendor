LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE := relf_service
LOCAL_MODULE_TAGS := optional
LOCAL_SRC_FILES := \
	$(call all-cpp-files-under, src)
LOCAL_SHARED_LIBRARIES := \
	libutils \
	libcutils \
	libbinder \
	liblog \
	libstlport
LOCAL_C_INCLUDES += \
    bionic \
    bionic/libstdc++/include \
    external/stlport/stlport \
	frameworks/native/include \
	system/core/include \
	$(LOCAL_PATH)/include
LOCAL_CPPFLAGS += -std=c++11
include $(BUILD_EXECUTABLE)
