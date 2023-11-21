#include "base.h"

enum NeoConversationEvent {
    // 会话新增,例如收到一条新消息,产生一个新的会话是事件触发
    kNeoConversatonEvent_Add,
    // 会话删除,例如自己删除某会话时会触发
    kNeoConversatonEvent_Del,
    // 会话更新,会话内消息的未读计数变化和收到新消息时触发
    kNeoConversatonEvent_Update,
};

/**
 * 会话事件回调
 *
 * @param conv_event 会话事件类型
 * @param json_conv_array 会话信息列表
 */ 
typedef void (*NeoConversationEventCallback)(enum NeoConversationEvent conv_event, const char* json_conv_array);

/**
 * 获取会话列表
 *
 * @param cb 获取会话列表的回调
 * @return int 返回 0 表示接口调用成功（接口只有返回 0，回调cb才会被调用），其他值表示接口调用失败
 */
int get_conversations(NeoCommonCallback cb);

/**
 * 设置会话事件回调
 * 
 * @param cb 会话事件回调，请参考[TIMConvEventCallback]()
 * @param user_data 用户自定义数据，ImSDK只负责传回给回调函数cb，不做任何处理
 *
 * @note
 * 会话事件包括：
 *  - 会话新增
 *  - 会话删除
 *  - 会话更新
 */
void set_conversation_event_callback(NeoConversationEventCallback cb);