#=======================================================================================================================
#
#   Copyright 2011, 2012, 2013, 2014, 2015 Institut fuer Neuroinformatik, Ruhr-Universitaet Bochum, Germany
# 
#   This file is part of cedar.
#
#   cedar is free software: you can redistribute it and/or modify it under
#   the terms of the GNU Lesser General Public License as published by the
#   Free Software Foundation, either version 3 of the License, or (at your
#   option) any later version.
#
#   cedar is distributed in the hope that it will be useful, but WITHOUT ANY
#   WARRANTY; without even the implied warranty of MERCHANTABILITY or
#   FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public
#   License for more details.
#
#   You should have received a copy of the GNU Lesser General Public License
#   along with cedar. If not, see <http://www.gnu.org/licenses/>.
#
#=======================================================================================================================
#
#   Institute:   Ruhr-Universitaet Bochum
#                Institut fuer Neuroinformatik
#
#   File:        CMakeLists.txt
#
#   Maintainer:  Oliver Lomp
#   Email:       oliver.lomp@ini.ruhr-uni-bochum.de
#   Date:        2012 06 27
#
#   Description:
#
#   Credits:
#
#=======================================================================================================================

cmake_minimum_required(VERSION 2.8)

# Include cedar's project script
include("cedarProject.cmake")

# this is needed to tame boost qi spirits. *ommmmm*. actually there are no spirits.
# and no spoon. sorry, folks, nothing to see here, move along.
add_definitions( -DBOOST_SPIRIT_USE_PHOENIX_V3)

cedar_project_add_target(
                         LIBRARY cShark # use this if you want to compile a library
                         #EXECUTABLE folder # use this if you want to compile an executable
                         TARGET_NAME cShark # if you leave this out, it will be the same as the folder
                         MOC_HEADERS # specify this and a list of moc headers below if you have any
                         KernelSGD.h SparseData.h LIBSVMModelWriter.h
                         #DEPENDS_ON OtherTargetNames # specify if this target depends on others 
                         )

set (CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmakeModules)
add_definitions("-DBOOST_LOG_DYN_LINK")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -fno-strict-aliasing")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wl -subsystem,console,debug")

find_package (Shark REQUIRED)
find_package (Boost COMPONENTS filesystem log program_options regex serialization system thread unit_test_framework REQUIRED)

target_link_libraries (cShark ${Boost_LIBRARIES}  ${SHARK_LIBRARIES})

