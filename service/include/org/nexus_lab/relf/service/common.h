#ifndef READ_PARCEL_INT32_OR_RETURN
#define READ_PARCEL_INT32_OR_RETURN(var)           \
    {                                              \
        status_t status;                           \
        if ((status = p->readInt32(&var)) != OK) { \
            return status;                         \
        }                                          \
    };
#endif

#ifndef WRITE_PARCEL_INT32_OR_RETURN
#define WRITE_PARCEL_INT32_OR_RETURN(var)          \
    {                                              \
        status_t status;                           \
        if ((status = p->writeInt32(var)) != OK) { \
            return status;                         \
        }                                          \
    }
#endif

#ifndef READ_PARCEL_INT64_OR_RETURN
#define READ_PARCEL_INT64_OR_RETURN(var)           \
    {                                              \
        status_t status;                           \
        if ((status = p->readInt64(&var)) != OK) { \
            return status;                         \
        }                                          \
    };
#endif

#ifndef WRITE_PARCEL_INT64_OR_RETURN
#define WRITE_PARCEL_INT64_OR_RETURN(var)          \
    {                                              \
        status_t status;                           \
        if ((status = p->writeInt64(var)) != OK) { \
            return status;                         \
        }                                          \
    }
#endif

#ifndef READ_PARCEL_STRING_OR_RETURN
#define READ_PARCEL_STRING_OR_RETURN(var)             \
    {                                                 \
        var = p->readString16();                      \
        if (var.size() <= 0) {                        \
            return BAD_VALUE;                         \
        }                                             \
    }
#endif

#ifndef WRITE_PARCEL_STRING_OR_RETURN
#define WRITE_PARCEL_STRING_OR_RETURN(var)            \
    {                                                 \
        status_t status;                              \
        if ((status = p->writeString16(var)) != OK) { \
            return status;                            \
        }                                             \
    }
#endif

#ifndef ERRNO_EXCEPTION
#define ERRNO_EXCEPTION() android::binder::Status::fromServiceSpecificError(errno, android::String8(::strerror(errno)))
#endif
