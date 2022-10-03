/*******************************************************************************
 * This file is part of pasta::utils.
 *
 * Copyright (C) 2022 Florian Kurpicz <florian@kurpicz.org>
 *
 * pasta::bit_vector is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * pasta::bit_vector is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with pasta::bit_vector.  If not, see <http://www.gnu.org/licenses/>.
 *
 ******************************************************************************/

#pragma once

#include "pasta/utils/debug_asserts.hpp"

#include <cstddef>
#include <cstdlib>

namespace pasta {

/*!
 * \brief Simple vector where the memory alignment can be specified at compile
 * time.
 *
 * \tparam alignment Alignment of the data in memory. Has to be a power of two.
 * \tparam DataType Type of the data that is stored in the vector.
 */
template <size_t alignment, typename DataType>
class AlignedVector {
private:
  //! Number of elements that can be stored in the vector.
  size_t size_;
  //! Pointer to the first element of the vector.
  DataType* data_;

public:
  /*!
   * \brief Empty constructor, creating a vector of size 0.
   */
  AlignedVector() : size_(0), data_(nullptr) {}

  /*!
   * \brief Constructor. Creates a vector of the given size.
   * \param size Number of elements the vector can hold.
   */
  AlignedVector(size_t const size)
      : size_(size),
        data_(static_cast<DataType*>(
            std::aligned_alloc(alignment, sizeof(DataType) * size))) {
    PASTA_ASSERT((sizeof(DataType) * size) % alignment == 0,
                 "Allocted memory has to be a multiple of template parameter "
                 "alignment.");
  }

  /*!
   * \brief Constructor. Coreates a vector of the give containing a default
   * value. \param size Number of elements the vector can hold. \param
   * default_value Value the vector is initially filled with.
   */
  AlignedVector(size_t const size, DataType default_value)
      : AlignedVector(size) {
    std::fill_n(data_, size_, default_value);
  }

  /*!
   * \brief Destructor.
   */
  ~AlignedVector() {
    if (data_) {
      std::free(data_);
    }
  }

  /*!
   * \brief Size of the vector.
   * \return Size of the vector.
   */
  size_t size() const {
    return size_;
  }

  /*!
   * \brief Pointer to the first element of the vector.
   * \return Pointer to the first element of the vector.
   */
  DataType* data() {
    return data_;
  }

  /*!
   * \brief Pointer to the first element of the vector. Elements are immutable.
   * \return Pointer to the first element of the vector. Elements are immutable.
   */
  DataType* data() const {
    return data_;
  }

  /*!
   * \brief Subscript operator access to the vector.
   * \param index Index of the requested element.
   * \return Requested element.
   */
  DataType& operator[](size_t const index) {
    return data_[index];
  }

  /*!
   * \brief Subscript operator access to the vector.
   * \param index Index of the requested element.
   * \return Requested immutable element.
   */
  DataType& operator[](size_t const index) const {
    return data_[index];
  }

  /*!
   * \brief Resize the vector.
   *
   * Data remains in the vector. If the new size is smaller than the current
   * size, only a prefix of the data remains.
   *
   * \param size New size of the vector.
   */
  void resize(size_t const size) {
    if (data_) {
      DataType* tmp = static_cast<DataType*>(
          std::aligned_alloc(alignment, sizeof(DataType) * size));
      std::move(data_, data_ + std::min(size, size_), tmp);
      std::swap(tmp, data_);
      size_ = size;
      std::free(tmp);
    } else {
      data_ = static_cast<DataType*>(
          std::aligned_alloc(alignment, sizeof(DataType) * size));
      size_ = size;
    }
  }
};
} // namespace pasta
