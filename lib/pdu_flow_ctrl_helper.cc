/* -*- c++ -*- */
/* 
 * Copyright 2018 gr-pdu_utils author.
 * 
 * This is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 * 
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this software; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <gnuradio/io_signature.h>
#include <pdu_utils/pdu_flow_ctrl_helper.h>

namespace gr {
  namespace pdu_utils {

    pdu_flow_ctrl_helper::pdu_flow_ctrl_helper(std::vector<gr::basic_block_sptr> blocks)
    {
      for(const gr::basic_block_sptr &block : blocks) {
        block_port bp;
        bp.block = basic_block_wptr(block);
        pmt::pmt_t ports = block->message_ports_in();
        int len = pmt::length(ports);
        for (int i=0; i<len; i++) {
          pmt::pmt_t port = pmt::vector_ref(ports, i);
          if (!pmt::eq(port, SYSTEM_PORT)) {
            bp.ports.push_back(port);
          }
        }
        if (bp.ports.empty()) {
          printf("WARNING: pdu_flow_ctrl: no input ports found on block '%s', ignoring", block->name().c_str());
        } else {
          d_blocks.push_back(bp);
        }
      }
    }

    pdu_flow_ctrl_helper::~pdu_flow_ctrl_helper()
    {
    }

    int pdu_flow_ctrl_helper::max_nmsgs() {
      int max_nmsgs = 0;
      for (const block_port &bp : d_blocks) {
        basic_block_sptr block = bp.block.lock();
        if (block) {
          for (const pmt::pmt_t &port : bp.ports) {
            max_nmsgs = std::max(max_nmsgs, (int)block->nmsgs(port));
          }
        }
      }
      return max_nmsgs;
    }

    void pdu_flow_ctrl_helper::print_nmsgs() {
      printf("\n====================== PDU Flow Controller ========================\n");
      for (const block_port &bp : d_blocks) {
        basic_block_sptr block = bp.block.lock();
        if (block) {
          for (const pmt::pmt_t &port : bp.ports) {
            int nmsgs = block->nmsgs(port);
            printf("'%s' has %d messages waiting at '%s'\n", block->name().c_str(), nmsgs, pmt::symbol_to_string(port).c_str());
          }
        }
      }
      printf("\n");
    }

  } /* namespace pdu_utils */
} /* namespace gr */

