/* 
 * File:   wbt_bmtp2.h
 * Author: fcten
 *
 * Created on 2017年6月19日, 下午9:31
 */

#ifndef WBT_BMTP2_H
#define WBT_BMTP2_H

#ifdef __cplusplus
extern "C" {
#endif

#include "../common/wbt_list.h"
#include "../common/wbt_rbtree.h"
#include "../common/wbt_string.h"
#include "../event/wbt_event.h"

enum {
    TYPE_BOOL = 0,
    TYPE_VARINT,
    TYPE_64BIT,
    TYPE_STRING
};

enum {
    OP_RSV = 0,
    OP_CONN,
    OP_CONNACK,
    OP_PUB,
    OP_PUBACK,
    OP_SUB,
    OP_SUBACK,
    OP_PING,
    OP_PINGACK,
    OP_DISCONN,
    OP_WINDOW,
    OP_MAX
};

enum {
    HEAD_END = 0,
    HEAD_PAYLOAD,
    HEAD_STREAM_ID,
    HEAD_STATUS_CODE,
    HEAD_EXT = 16
};

typedef struct {
    unsigned int opcode;
    wbt_str_t name;
    wbt_status (*on_proc)( wbt_event_t *ev );
} wbt_bmtp2_cmd_t;

typedef struct wbt_bmtp2_msg_list_s {
    wbt_list_t head;

    unsigned int   buff_len;
    unsigned int   buff_offset;
    unsigned char *buff;
    
    /* 为了避免拷贝消息产生性能损耗，这里使用指针来直接读取消息内容。
     * 由此产生的问题是，消息可能会在发送的过程中过期。
     * 
     * TODO 通过引用计数来避免消息过期
     */
    wbt_msg_t     *msg;
    unsigned int   msg_offset;
} wbt_bmtp2_msg_list_t;

typedef struct wbt_bmtp2_param_list_s {
    wbt_list_t head;
    
    unsigned int key;
    unsigned int key_type:3;
    struct {
        unsigned char *s;
        unsigned long long int l;
    } value;
} wbt_bmtp2_param_list_t;

typedef struct {
    // 接收报文状态
    unsigned int state;
    // 当前处理进度
    unsigned int recv_offset;
    // 当前数据包起始偏移
    unsigned int msg_offset;

    // 指令
    unsigned int op_code;
    unsigned int op_type:3;
    struct {
        unsigned char *s;
        unsigned long long int l;
    } op_value;
    wbt_bmtp2_param_list_t param;
    
    // 发送报文队列
    wbt_bmtp2_msg_list_t send_list;
    // 等待确认报文队列
    wbt_rb_t ack_queue;
    
    // 连接状态
    unsigned int is_conn:1;
    // 发送窗口，用于流量控制
    unsigned int window;
    // 最后一次分配的流标识符
    wbt_mq_id stream_id;
} wbt_bmtp2_t;

wbt_status wbt_bmtp2_init();
wbt_status wbt_bmtp2_exit();

wbt_status wbt_bmtp2_on_conn(wbt_event_t *ev);
wbt_status wbt_bmtp2_on_recv(wbt_event_t *ev);
wbt_status wbt_bmtp2_on_send(wbt_event_t *ev);
wbt_status wbt_bmtp2_on_close(wbt_event_t *ev);

wbt_status wbt_bmtp2_on_handler(wbt_event_t *ev);

wbt_status wbt_bmtp2_on_connect(wbt_event_t *ev);
wbt_status wbt_bmtp2_on_connack(wbt_event_t *ev);
wbt_status wbt_bmtp2_on_pub(wbt_event_t *ev);
wbt_status wbt_bmtp2_on_puback(wbt_event_t *ev);
wbt_status wbt_bmtp2_on_sub(wbt_event_t *ev);
wbt_status wbt_bmtp2_on_suback(wbt_event_t *ev);
wbt_status wbt_bmtp2_on_ping(wbt_event_t *ev);
wbt_status wbt_bmtp2_on_pingack(wbt_event_t *ev);
wbt_status wbt_bmtp2_on_disconn(wbt_event_t *ev);
wbt_status wbt_bmtp2_on_window(wbt_event_t *ev);

wbt_status wbt_bmtp2_notify(wbt_event_t *ev);

wbt_status wbt_bmtp2_send_conn(wbt_event_t *ev);
wbt_status wbt_bmtp2_send_connack(wbt_event_t *ev, unsigned char status);
wbt_status wbt_bmtp2_send_pub(wbt_event_t *ev, wbt_msg_t *msg);
wbt_status wbt_bmtp2_send_puback(wbt_event_t *ev, unsigned char status);
wbt_status wbt_bmtp2_send_sub(wbt_event_t *ev, unsigned long long int channel_id);
wbt_status wbt_bmtp2_send_suback(wbt_event_t *ev, unsigned char status);
wbt_status wbt_bmtp2_send_ping(wbt_event_t *ev);
wbt_status wbt_bmtp2_send_pingack(wbt_event_t *ev);
wbt_status wbt_bmtp2_send_disconn(wbt_event_t *ev);
wbt_status wbt_bmtp2_send_window(wbt_event_t *ev);
wbt_status wbt_bmtp2_send(wbt_event_t *ev, char *buf, int len);

#ifdef __cplusplus
}
#endif

#endif /* WBT_BMTP2_H */
