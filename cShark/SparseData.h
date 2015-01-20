/*======================================================================================================================

    Copyright 2011, 2012, 2013, 2014, 2015 Institut fuer Neuroinformatik, Ruhr-Universitaet Bochum, Germany
 
    This file is part of cedar.

    cedar is free software: you can redistribute it and/or modify it under
    the terms of the GNU Lesser General Public License as published by the
    Free Software Foundation, either version 3 of the License, or (at your
    option) any later version.

    cedar is distributed in the hope that it will be useful, but WITHOUT ANY
    WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public
    License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with cedar. If not, see <http://www.gnu.org/licenses/>.

========================================================================================================================

    Institute:   Ruhr-Universitaet Bochum
                 Institut fuer Neuroinformatik

    File:        SparseData.h

    Maintainer:  aydin demircioglu
    Email:       aydin.demircioglu@ini.rub.de
    Date:        2015 01 20

    Description: Header file for the class cShark::SparseData.

    Credits:

======================================================================================================================*/

#ifndef C_SHARK_SPARSE_DATA_H
#define C_SHARK_SPARSE_DATA_H

// CEDAR CONFIGURATION
#include "cedar/configuration.h"

// CEDAR INCLUDES
#include <cedar/processing/Step.h>
#include <cedar/processing/InputSlotHelper.h>

#include <cedar/auxiliaries/FileParameter.h>
#include <cedar/auxiliaries/MatData.h>

// SHARK THINGS
#include "SharkSparseData.h"

// FORWARD DECLARATIONS
#include "SparseData.fwd.h"

// SYSTEM INCLUDES


using namespace shark;

/*!@todo describe.
 *
 * @todo describe more.
 */
class cShark::SparseData : public cedar::proc::Step
{
  //--------------------------------------------------------------------------------------------------------------------
  // nested types
  //--------------------------------------------------------------------------------------------------------------------

  //--------------------------------------------------------------------------------------------------------------------
  // constructors and destructor
  //--------------------------------------------------------------------------------------------------------------------
public:
  //!@brief The standard constructor.
  SparseData();

  //--------------------------------------------------------------------------------------------------------------------
  // public methods
  //--------------------------------------------------------------------------------------------------------------------
public:
  // none yet

  //--------------------------------------------------------------------------------------------------------------------
  // protected methods
  //--------------------------------------------------------------------------------------------------------------------
protected:
  // none yet


private:
	
	void updateFilename();
	
	
	void inputConnectionChanged(const std::string& inputName);

	
	void compute(const cedar::proc::Arguments& arguments);

  //--------------------------------------------------------------------------------------------------------------------
  // members
  //--------------------------------------------------------------------------------------------------------------------
protected:
  // none yet
private:
  //!@brief MatrixData representing the input. Storing it like this saves time during computation.
  cedar::aux::ConstMatDataPtr mInput;

  //!@brief The output data.
  cedar::aux::MatDataPtr mOutput;

  //--------------------------------------------------------------------------------------------------------------------
  // parameters
  //--------------------------------------------------------------------------------------------------------------------
protected:
  // none yet

private:
	// data handler
	SparseDataModel<RealVector> sparseDataHandler;

	//!@brief determines the filename from which currently is read
	cedar::aux::FileParameterPtr mFilename;
	
	
}; // class cShark::SparseData

#endif // C_SHARK_SPARSE_DATA_H

