/*******************************************************************************
 * utils/memory_monitor.cpp
 *
 * Copyright (C) 2021 Florian Kurpicz <florian@kurpicz.org>
 *
 * pasta::utils is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * pasta::utils is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with pasta::utils.  If not, see <http://www.gnu.org/licenses/>.
 *
 ******************************************************************************/

#include <cstddef>
#include <ostream>
#include <iostream>

#include "util/malloc.hpp"
#include "util/memory_monitor.hpp"

namespace pasta {

  MemoryMonitorStats::MemoryMonitorStats(size_t const _cur_peak,
					 size_t const _total_size_malloc,
					 size_t const _total_size_free,
					 size_t const _number_malloc,
					 size_t const _number_free,
					 size_t const _uncounted)
    : cur_peak(_cur_peak), total_size_malloc(_total_size_malloc),
      total_size_free(_total_size_free), number_malloc(_number_malloc),
      number_free(_number_free), uncounted(_uncounted) { }

  std::ostream& operator << (std::ostream& os, MemoryMonitorStats const& mms) {
    os << "cur_peak=" << mms.cur_peak << " "
       << "total_size_malloc=" << mms.total_size_malloc << " "
       << "total_size_free=" << mms.total_size_free  << " "
       << "number_malloc=" << mms.number_malloc << " "
       << "number_free=" << mms.number_free << " "
       << "uncounted=" << mms.uncounted;
    return os;
  }

  MemoryMonitor& MemoryMonitor::instance() {
    static MemoryMonitor instance;
    return instance;
  }

  void MemoryMonitor::reset() {
    instance().memory_stats_ = { 0, 0, 0, 0, 0, 0 };
  }

  MemoryMonitorStats MemoryMonitor::get() {
    return memory_stats_;
  }
  MemoryMonitorStats MemoryMonitor::get_and_reset() {
    auto tmp = memory_stats_;
    reset();
    return tmp;
  }

  MemoryMonitor::MemoryMonitor() : memory_stats_(0, 0, 0, 0, 0, 0) {
    MemoryMonitorCallbacks::malloc_callback = MemoryMonitor::malloc_callback;
    MemoryMonitorCallbacks::free_callback = MemoryMonitor::free_callback;
    MemoryMonitorCallbacks::uncounted_callback =
      MemoryMonitor::uncounted_callback;
  }

  void MemoryMonitor::malloc_callback(size_t const size) {
    instance().memory_stats_.cur_peak += size;
    instance().memory_stats_.total_size_malloc += size;
    ++instance().memory_stats_.number_malloc;
  }

  void MemoryMonitor::free_callback(size_t const size) {
    MemoryMonitorStats& cur_stats = instance().memory_stats_;
    cur_stats.cur_peak -= size;
    cur_stats.total_size_free += size;
    ++cur_stats.number_free;
  }

  void MemoryMonitor::uncounted_callback() {
    ++instance().memory_stats_.uncounted;
  }
} // namespace pasta

/******************************************************************************/
