/*******************************************************************************
 * utils/timer.hpp
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

#pragma once

#include <chrono>

namespace pasta {

  //! \addtogroup pasta_util
  //! \{

  /*!
   * \brief Utility wrapper for chrono timer.
   *
   * This small timer utility can be used to measure running times. It provided
   * more functionality than simply computing two \c time_points.
   */
  class Timer {

    //! Time when the timer was created or reset.
    std::chrono::system_clock::time_point begin_;

  public:
    //! Constructor. Creates and starts a timer.
    Timer();

    //! Resets the timer, i.e., sets \c begin_ to the current time.
    void reset();

    /*!
     * \brief Computes duration of timer up to this point.
     * \return The duration the timer has been running in milliseconds.
     */
    [[nodiscard]]
    size_t get() const;

    /*!
     * \brief Computes duration of timer up to this point and calls \c reset.
     * \return The duration the timer has been running in milliseconds.
     */
    [[nodiscard]]
    size_t get_and_reset();
  }; // class Timer

  //! \)

} // namespace pasta
  
/******************************************************************************/
