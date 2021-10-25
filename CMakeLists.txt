################################################################################
# CMakeLists.txt
#
# Copyright (C) 2021 Florian Kurpicz <florian@kurpicz.org>
#
# pasta::utils is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# pasta::utils is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with pasta::utils.  If not, see <http://www.gnu.org/licenses/>.
#
################################################################################

cmake_minimum_required(VERSION 3.4.1 FATAL_ERROR)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(pasta_utils)

# pasta::memory_monitor
add_library(pasta_memory_monitor OBJECT
  utils/malloc.cpp)
target_include_directories(pasta_memory_monitor INTERFACE
  ${CMAKE_CURRENT_SOURCE_DIR})

# pasta::utils interface definitions
add_library(pasta_utils INTERFACE)
target_include_directories(pasta_utils INTERFACE
  ${CMAKE_CURRENT_SOURCE_DIR})

################################################################################