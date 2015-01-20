//===========================================================================
/*!
 *
 *
 * \brief       Shark SVM config
 *
 *
 *
 * \author      Aydin Demircioglu
 * \date        2014
 *
 *
 * \par Copyright 1995-2014 Shark Development Team
 *
 * <BR><HR>
 * This file is part of Shark.
 * <http://image.diku.dk/shark/>
 *
 * Shark is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published
 * by the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Shark is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with Shark.  If not, see <http://www.gnu.org/licenses/>.
 *
 */
//===========================================================================

#ifndef SHARK_SHARKSVMCONFIG_H
#define SHARK_SHARKSVMCONFIG_H

#define SHARKSVM_VERSION_PATCH 0
#define SHARKSVM_VERSION_MINOR 2
#define SHARKSVM_VERSION_MAJOR 0
#define SHARKSVM_BUILD_TYPE "Release"

// need to fake boost log as it is not available on LIDO for now
#undef REPLACE_BOOST_LOG
#ifdef REPLACE_BOOST_LOG
#define localstr(s) #s
#define BOOST_LOG_TRIVIAL_FULL(x)    std::cout << std::endl << "(" << localstr(x) << "): "
#define BOOST_LOG_TRIVIAL(x)    std::cout << std::endl << ": "
#endif

// if we need not replace boost, we can include it
#ifndef REPLACE_BOOST_LOG
#include <boost/log/core.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/utility/setup/console.hpp>
#endif


// WTF??
#define BOOST_SPIRIT_USE_PHOENIX_V3

namespace shark {
}


#endif
