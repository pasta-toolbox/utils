/*******************************************************************************
 * utils/timer.cpp
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

#include "util/timer.hpp"

namespace pasta {

  Timer::Timer() : begin_(std::chrono::system_clock::now()) { }

  void Timer::reset() {
    begin_ = std::chrono::system_clock::now();
  }

  [[nodiscard]]
  size_t Timer::get() const {
    auto const end = std::chrono::system_clock::now();
    return std::chrono::duration_cast<
      std::chrono::milliseconds>(end - begin_).count();
  }

  [[nodiscard]]
  size_t Timer::get_and_reset() {
    auto const time = get();
    reset();
    return time;
  }

} // namespace pasta
  
/******************************************************************************/
