//===========================================================================
/*!
 *
 *
 * \brief       Shark SVM definitions
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

#ifndef SHARK_SHARKSVM_H
#define SHARK_SHARKSVM_H

#include <shark/Core/Exception.h>

#include <sstream>


namespace shark {


    ///! error codes.
    ///
    class ErrorCodes {
        public:
            enum _ErrorCodes {
                SUCCESS,
                ERROR_IN_COMMAND_LINE,
                ERROR_UNHANDLED_EXCEPTION,
                ERROR_WRONG_KERNEL_TYPE,
                ERROR_WRONG_SVM_TYPE,
                ERROR_WRONG_SVM_FLAVOR,
                ERROR_INITIALIZATION_FAILED,
                ERROR_DATA,
                ERROR_MODELFILE,
                ERROR_WRONG_BUDGET_STRATEGY,
                ERROR_WRONG_BUDGET_SIZE,
                ERROR_WRONG_MIN_MARGIN,
            };
    };



    ///! usable kernels.
    /// 
    class KernelTypes {
        public:
            enum _KernelTypes {LINEAR = 0, POLYNOMIAL = 1, RBF = 2};
    };


    ///! strategies for budgeted sgd.
    ///
    class BudgetMaintenanceStrategy {
        public:
            enum _BudgetMaintenanceStrategy {
                REMOVE = 0,
                MERGE = 1,
                PROJECT = 2
            };
    };



    /**
     * \brief Top-level exception class of the shark library.
     */
    class SharkSVMException : public shark::Exception {
        public:
            /**
             * \brief Default c'tor.
             * \param [in] what String that describes the exception.
             * \param [in] file Filename the function that has thrown the exception resides in.
             * \param [in] line Line of file that has thrown the exception.
             */
            SharkSVMException (const std::string &what = std::string(), const std::string &file = std::string(), unsigned int line = 0)            {
                m_what = what;
                m_file = file;
                m_line = line;
                std::ostringstream o;
                o << file << ":" << line << ": " << what;
                m_what = o.str();
            }
    };

}

/**
 * \brief Convenience macro that creates an instance of class shark::exception,
 * injecting file and line information automatically.
 */
#define SHARKSVMEXCEPTION(message) shark::SharkSVMException(message, __FILE__, __LINE__)



#endif
