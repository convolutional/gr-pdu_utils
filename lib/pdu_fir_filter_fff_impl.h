/* -*- c++ -*- */
/*
 * Copyright 2018 National Technology & Engineering Solutions of Sandia, LLC (NTESS). Under the terms of Contract DE-NA0003525 with NTESS, the U.S. Government retains certain rights in this software.
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

#ifndef INCLUDED_PDU_UTILS_PDU_FIR_FILTER_FFF_IMPL_H
#define INCLUDED_PDU_UTILS_PDU_FIR_FILTER_FFF_IMPL_H

#include <pdu_utils/pdu_fir_filter_fff.h>
#include <pdu_utils/constants.h>
#include <gnuradio/filter/fir_filter.h>

namespace gr {
  namespace pdu_utils {

    class pdu_fir_filter_fff_impl : public pdu_fir_filter_fff
    {
     private:
      std::vector<float> d_taps;
      filter::kernel::fir_filter_fff *d_fir;

     public:
      pdu_fir_filter_fff_impl(const std::vector<float> taps);
      ~pdu_fir_filter_fff_impl();

      void handle_pdu(pmt::pmt_t pdu);

      void set_taps(std::vector<float> taps) { d_taps = taps; };
    };

  } // namespace pdu_utils
} // namespace gr

#endif /* INCLUDED_PDU_UTILS_PDU_FIR_FILTER_FFF_IMPL_H */
