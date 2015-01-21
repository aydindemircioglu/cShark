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

    File:        KernelSGD.h

    Maintainer:  aydin demircioglu
    Email:       aydin.demircioglu@ini.rub.de
    Date:        2015 01 20

    Description: Header file for the class cShark::KernelSGD.

    Credits:

======================================================================================================================*/

#ifndef C_SHARK_KERNEL_SGD_H
#define C_SHARK_KERNEL_SGD_H

// CEDAR CONFIGURATION
#include "cedar/configuration.h"

// CEDAR INCLUDES
#include <cedar/processing/Step.h>
#include <cedar/processing/InputSlotHelper.h>

#include <cedar/auxiliaries/FileParameter.h>
#include <cedar/auxiliaries/DoubleParameter.h>
#include <cedar/auxiliaries/IntParameter.h>
#include <cedar/auxiliaries/MatData.h>

// SHARK THINGS
#include "SharkSVM/SharkKernelSGDOnlineTrainer.h"
#include <shark/ObjectiveFunctions/Loss/HingeLoss.h>
#include <shark/Models/Kernels/GaussianRbfKernel.h> //the used kernel for the SVM

// FORWARD DECLARATIONS
#include "KernelSGD.fwd.h"

// SYSTEM INCLUDES


using namespace shark;

/*!@todo describe.
 *
 * @todo describe more.
 */
class cShark::KernelSGD : public cedar::proc::Step
{
	Q_OBJECT
	typedef cedar::aux::DataTemplate<RealVector> CedarRealVector;
	CEDAR_GENERATE_POINTER_TYPES(CedarRealVector);
	
  //--------------------------------------------------------------------------------------------------------------------
  // nested types
  //--------------------------------------------------------------------------------------------------------------------

  //--------------------------------------------------------------------------------------------------------------------
  // constructors and destructor
  //--------------------------------------------------------------------------------------------------------------------
public:
  //!@brief The standard constructor.
  KernelSGD();

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
		
	void inputConnectionChanged(const std::string& inputName);
	
	void compute(const cedar::proc::Arguments& arguments);

public slots: 
	void reinitializeKernelSGD();
	
	

protected:
  // none yet
private:
	//!@brief MatrixData representing the input. Storing it like this saves time during computation.
	CedarRealVectorPtr mInput;

	//!@brief The output data.
	CedarRealVectorPtr mOutput;

  //--------------------------------------------------------------------------------------------------------------------
  // parameters
  //--------------------------------------------------------------------------------------------------------------------
protected:
  // none yet

private:

	//!@brief parameter for using bias term or not
	cedar::aux::BoolParameterPtr mOffset;
	
	//!@brief regularization term
	cedar::aux::DoubleParameterPtr mLambda;

	//!@brief number of epochs
	cedar::aux::IntParameterPtr mEpochs;
	
	//!@brief cache size
	cedar::aux::IntParameterPtr mCacheSize;

	//!@brief current trainer we work on
	shark::KernelSGDOnlineTrainer<RealVector> *mKernelSGDTrainer;

	//!@brief kernel to use FIXME should be abstract blabla
	GaussianRbfKernel<> mKernel;
	
	//!@brief loss function FIXME should be abstract blabla
	HingeLoss mLoss;
	
}; // class cShark::KernelSGD

#endif // C_SHARK_KERNEL_SGD_H

