typedef     signed char         int8_t;
typedef     signed short        int16_t;
typedef     signed int          int32_t;
typedef     signed long long    int64_t;
typedef     unsigned char       uint8_t;
typedef     unsigned short      uint16_t;
typedef     unsigned int        uint32_t;
typedef     unsigned long long  uint64_t;

/**
 * 接口通用回调的定义
 *
 * @param code 值为 0 表示成功，其他值表示失败
 * @param desc 错误描述字符串
 * @param json_params Json 字符串，不同的接口，Json 字符串不一样
 *
 * @note
 * 所有回调均需判断 code 是否等于 0，若不等于说明接口调用失败了
 */
typedef void (*NeoCommonCallback)(int32_t code, const char* desc, const char* json_params);