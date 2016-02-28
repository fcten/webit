/* 
 * File:   wbt_bmtp.h
 * Author: fcten
 *
 * Created on 2016年2月26日, 下午4:42
 */

#ifndef WBT_BMTP_H
#define	WBT_BMTP_H

#ifdef	__cplusplus
extern "C" {
#endif

/* 
 * +---------+-----------------------------------------------+
 * +   Bit   |  7  |  6  |  5  |  4  |  3  |  2  |  1  |  0  |
 * +---------+-----------------------------------------------+
 * +  Byte1  |      Message Type     |     Protocol Type     |
 * +---------+-----------------------------------------------+
 * +         |  0  |  0  |  0  |  0  |  0  |  0  |  0  |  1  |
 * +---------+-----------------------------------------------+
 * +  Byte2  |                     Flags                     |
 * +---------+-----------------------------------------------+
 * +         |  X  |  X  |  X  |  X  |  X  |  X  |  X  |  X  |
 * +---------+-----------------------------------------------+
 * +  Byte3+ |                    Payload                    |
 * 
 * Flags:
 *     7: 身份认证
 *   6-0: 保留
 */

#define BMTP_CONN 0x10

/* 
 * +---------+-----------------------------------------------+
 * +   Bit   |  7  |  6  |  5  |  4  |  3  |  2  |  1  |  0  |
 * +---------+-----------------------------------------------+
 * +  Byte1  |      Message Type     |      Status Code      |
 * +---------+-----------------------------------------------+
 * +         |  0  |  0  |  1  |  0  |  X  |  X  |  X  |  X  |
 * +---------+-----------------------------------------------+
 *
 * Status Code:
 *      0: 接受
 *      1: 拒绝，不支持的协议版本
 *      2: 拒绝，服务不可用
 *      3: 拒绝，身份认证失败
 *   4-15: 保留
 */

#define BMTP_CONNACK 0x20

/* 
 * +---------+-----------------------------------------------+
 * +   Bit   |  7  |  6  |  5  |  4  |  3  |  2  |  1  |  0  |
 * +---------+-----------------------------------------------+
 * +  Byte1  |      Message Type     | DUP |  R  |    QoS    |
 * +---------+-----------------------------------------------+
 * +         |  0  |  0  |  1  |  1  |  X  |  0  |  X  |  X  |
 * +---------+-----------------------------------------------+
 * +  Byte2  |                   Stream ID                   |
 * +---------+-----------------------------------------------+
 * +         |  X  |  X  |  X  |  X  |  X  |  X  |  X  |  X  |
 * +---------+-----------------------------------------------+
 * +  Byte3  |                     Flags                     |
 * +---------+-----------------------------------------------+
 * +         |  X  |  X  |  X  |  X  |  X  |  X  |  X  |  X  |
 * +---------+-----------------------------------------------+
 * +  Byte4+ |                    Payload                    |
 *
 * DUP: 重发标志
 * QoS: 服务质量等级 0-至多一次 1-至少一次 2-恰好一次
 * 
 * Flags:
 *     7: 延迟时间，毫秒，4 字节
 *     6: 过期时间，毫秒，4 字节
 *     5: 0-单点消息 1-广播消息
 *   4-0: 保留位
 *
 * Payload: 总是在最后包含 Channel ID（8字节）+消息体（长度+正文）
 */

#define BMTP_PUB 0x30

/* 
 * +---------+-----------------------------------------------+
 * +   Bit   |  7  |  6  |  5  |  4  |  3  |  2  |  1  |  0  |
 * +---------+-----------------------------------------------+
 * +  Byte1  |      Message Type     | Reserved  |    QoS    |
 * +---------+-----------------------------------------------+
 * +         |  0  |  1  |  0  |  0  |  0  |  0  |  X  |  X  |
 * +---------+-----------------------------------------------+
 * +  Byte2  |                   Stream ID                   |
 * +---------+-----------------------------------------------+
 * +         |  X  |  X  |  X  |  X  |  X  |  X  |  X  |  X  |
 * +---------+-----------------------------------------------+
 *
 */

#define BMTP_PUBACK 0x40

/* 
 * +---------+-----------------------------------------------+
 * +   Bit   |  7  |  6  |  5  |  4  |  3  |  2  |  1  |  0  |
 * +---------+-----------------------------------------------+
 * +  Byte1  |      Message Type     | DUP |  R  |    QoS    |
 * +---------+-----------------------------------------------+
 * +         |  0  |  1  |  0  |  1  |  X  |  0  |  X  |  X  |
 * +---------+-----------------------------------------------+
 * +  Byte2  |                   Stream ID                   |
 * +---------+-----------------------------------------------+
 * +         |  X  |  X  |  X  |  X  |  X  |  X  |  X  |  X  |
 * +---------+-----------------------------------------------+
 *
 */

#define BMTP_PUBREL 0x50

/* 
 * +---------+-----------------------------------------------+
 * +   Bit   |  7  |  6  |  5  |  4  |  3  |  2  |  1  |  0  |
 * +---------+-----------------------------------------------+
 * +  Byte1  |      Message Type     | Reserved  |    QoS    |
 * +---------+-----------------------------------------------+
 * +         |  0  |  1  |  1  |  0  |  0  |  0  |  X  |  X  |
 * +---------+-----------------------------------------------+
 * +  Byte2  |                   Stream ID                   |
 * +---------+-----------------------------------------------+
 * +         |  X  |  X  |  X  |  X  |  X  |  X  |  X  |  X  |
 * +---------+-----------------------------------------------+
 *
 */

#define BMTP_PUBEND 0x60

/* 
 * +---------+-----------------------------------------------+
 * +   Bit   |  7  |  6  |  5  |  4  |  3  |  2  |  1  |  0  |
 * +---------+-----------------------------------------------+
 * +  Byte1  |      Message Type     | DUP |     Reserved    |
 * +---------+-----------------------------------------------+
 * +         |  0  |  1  |  1  |  1  |  X  |  0  |  0  |  0  |
 * +---------+-----------------------------------------------+
 * + Byte2-9 |                  Channel ID                   |
 * +---------+-----------------------------------------------+
 * +         |  X  |  X  |  X  |  X  |  X  |  X  |  X  |  X  |
 * +---------+-----------------------------------------------+
 *
 */

#define BMTP_SUB 0x70

/* 
 * +---------+-----------------------------------------------+
 * +   Bit   |  7  |  6  |  5  |  4  |  3  |  2  |  1  |  0  |
 * +---------+-----------------------------------------------+
 * +  Byte1  |      Message Type     |       Reserved        |
 * +---------+-----------------------------------------------+
 * +         |  1  |  0  |  0  |  0  |  X  |  X  |  X  |  X  |
 * +---------+-----------------------------------------------+
 * + Byte2-9 |                  Channel ID                   |
 * +---------+-----------------------------------------------+
 * +         |  X  |  X  |  X  |  X  |  X  |  X  |  X  |  X  |
 * +---------+-----------------------------------------------+
 *
 */

#define BMTP_SUBACK 0x80

/* 
 * +---------+-----------------------------------------------+
 * +   Bit   |  7  |  6  |  5  |  4  |  3  |  2  |  1  |  0  |
 * +---------+-----------------------------------------------+
 * +  Byte1  |      Message Type     |       Channels        |
 * +---------+-----------------------------------------------+
 * +         |  1  |  0  |  0  |  1  |  X  |  X  |  X  |  X  |
 * +---------+-----------------------------------------------+
 * + Byte2-9 |                  Channel ID                   |
 * +---------+-----------------------------------------------+
 * +         |  X  |  X  |  X  |  X  |  X  |  X  |  X  |  X  |
 * +---------+-----------------------------------------------+
 *
 */

#define BMTP_UNSUB 0x90

/* 
 * +---------+-----------------------------------------------+
 * +   Bit   |  7  |  6  |  5  |  4  |  3  |  2  |  1  |  0  |
 * +---------+-----------------------------------------------+
 * +  Byte1  |      Message Type     |       Channels        |
 * +---------+-----------------------------------------------+
 * +         |  1  |  0  |  1  |  0  |  X  |  X  |  X  |  X  |
 * +---------+-----------------------------------------------+
 * + Byte2-9 |                  Channel ID                   |
 * +---------+-----------------------------------------------+
 * +         |  X  |  X  |  X  |  X  |  X  |  X  |  X  |  X  |
 * +---------+-----------------------------------------------+
 *
 */

#define BMTP_UNSUBACK 0xA0

/* 
 * +---------+-----------------------------------------------+
 * +   Bit   |  7  |  6  |  5  |  4  |  3  |  2  |  1  |  0  |
 * +---------+-----------------------------------------------+
 * +  Byte1  |      Message Type     |       Reserved        |
 * +---------+-----------------------------------------------+
 * +         |  1  |  0  |  1  |  1  |  X  |  X  |  X  |  X  |
 * +---------+-----------------------------------------------+
 *
 */

#define BMTP_PING 0xB0

/* 
 * +---------+-----------------------------------------------+
 * +   Bit   |  7  |  6  |  5  |  4  |  3  |  2  |  1  |  0  |
 * +---------+-----------------------------------------------+
 * +  Byte1  |      Message Type     |       Reserved        |
 * +---------+-----------------------------------------------+
 * +         |  1  |  1  |  0  |  0  |  X  |  X  |  X  |  X  |
 * +---------+-----------------------------------------------+
 *
 */

#define BMTP_PINGACK 0xC0

/* 
 * +---------+-----------------------------------------------+
 * +   Bit   |  7  |  6  |  5  |  4  |  3  |  2  |  1  |  0  |
 * +---------+-----------------------------------------------+
 * +  Byte1  |      Message Type     |       Reserved        |
 * +---------+-----------------------------------------------+
 * +         |  1  |  1  |  0  |  1  |  X  |  X  |  X  |  X  |
 * +---------+-----------------------------------------------+
 *
 */

#define BMTP_DISCONN 0xD0

#ifdef	__cplusplus
}
#endif

#endif	/* WBT_BMTP_H */

