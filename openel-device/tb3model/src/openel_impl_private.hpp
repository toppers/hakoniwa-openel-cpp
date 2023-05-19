#ifndef _OPENEL_IMPL_PRIVATE_HPP_
#define _OPENEL_IMPL_PRIVATE_HPP_

#include <hako.hpp>

#define HAKO_PDU_CHANNEL_CMDVEL    0
#define HAKO_PDU_CHANNEL_SCAN      8

extern bool hako_pdu_write_init(HakoPduChannelIdType pdu_channel, int buflen);
extern bool hako_pdu_write_data(HakoPduChannelIdType pdu_channel, char* pdu_msg, int buflen);
extern bool hako_pdu_read_data(HakoPduChannelIdType pdu_channel, char* pdu_msg, int buflen);

#endif /* _OPENEL_IMPL_PRIVATE_HPP_ */