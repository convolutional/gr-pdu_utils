/* -*- c++ -*- */
/*
 * Copyright 2019 gr-pdu_utils author.
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

#ifndef INCLUDED_PDU_UTILS_PDU_FINE_TIME_MEASURE_IMPL_H
#define INCLUDED_PDU_UTILS_PDU_FINE_TIME_MEASURE_IMPL_H

#include <pdu_utils/pdu_fine_time_measure.h>

namespace gr {
  namespace pdu_utils {

    class pdu_fine_time_measure_impl : public pdu_fine_time_measure
    {
     private:
      std::vector<float> d_magnitude_squared_f;
      float d_pre_burst_time;
      float d_post_burst_time;
      size_t d_average_size;
      float d_buffer_percent;

      void pdu_handler(pmt::pmt_t pdu);

      // PMT declarations
      const pmt::pmt_t PMT_START_TIME = pmt::mp("start_time");
      const pmt::pmt_t PMT_SAMPLE_RATE = pmt::mp("sample_rate");
      const pmt::pmt_t PMT_DURATION = pmt::mp("duration");
      const pmt::pmt_t PMT_PDU_IN = pmt::mp("pdu_in");
      const pmt::pmt_t PMT_PDU_OUT = pmt::mp("pdu_out");

     public:
      pdu_fine_time_measure_impl(float pre_burst_time, float post_burst_time, size_t average_width, float buffer_percent);
      ~pdu_fine_time_measure_impl();

    };

  } // namespace pdu_utils
} // namespace gr

#endif /* INCLUDED_PDU_UTILS_PDU_FINE_TIME_MEASURE_IMPL_H */
