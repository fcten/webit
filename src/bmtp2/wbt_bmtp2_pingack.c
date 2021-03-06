#include "wbt_bmtp2.h"

wbt_status wbt_bmtp2_on_pingack(wbt_event_t *ev) {
    wbt_bmtp2_t *bmtp = ev->data;
    
    if( bmtp->role != BMTP_CLIENT ) {
        return WBT_ERROR;
    }

    return WBT_OK;
}

wbt_status wbt_bmtp2_send_pingack(wbt_event_t *ev) {
    wbt_bmtp2_msg_list_t *node = wbt_calloc(sizeof(wbt_bmtp2_msg_list_t));
    if( node == NULL ) {
        return WBT_ERROR;
    }

    wbt_bmtp2_append_opcode(node, OP_PINGACK, TYPE_BOOL, 0);
    
    return wbt_bmtp2_send(ev, node);
}