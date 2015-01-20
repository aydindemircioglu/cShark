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

    File:        KernelSGD.cpp

    Maintainer:  aydin demircioglu
    Email:       aydin.demircioglu@ini.rub.de
    Date:        2015 01 20

    Description: Source file for the class cShark::KernelSGD.

    Credits:

======================================================================================================================*/

// CEDAR CONFIGURATION
#include "cedar/configuration.h"

// CLASS HEADER
#include "KernelSGD.h"

// CEDAR INCLUDES
#include "cedar/processing/typecheck/IsMatrix.h"

// SYSTEM INCLUDES

using namespace shark;


//----------------------------------------------------------------------------------------------------------------------
// constructors and destructor
//----------------------------------------------------------------------------------------------------------------------


cedar::aux::BoolParameter mOffset;
cedar::aux::DoubleParameter mLambda;
cedar::aux::IntParameter mEpochs;
cedar::aux::IntParameter mCacheSize;
shark::KernelSGDOnlineTrainer<RealVector> *mKernelSGDTrainer;
GaussianRbfKernel<> kernel;
HingeLoss loss;



cShark::KernelSGD::KernelSGD():
	//TODO:mKernelType(new cedar::aux::X),
	//TODO:mLossType(new cedar::aux::X )
	mOffset(new cedar::aux::BoolParameter(this, "Use Offset", false)),
	mLambda(new cedar::aux::DoubleParameter(this, "Lambda", 1.0, cedar::aux::DoubleParameter::LimitType::positive())),
	mEpochs(new cedar::aux::IntParameter(this, "Epochs", 1, cedar::aux::IntParameter::LimitType::fromLower(1)))
//	mCacheSize(new cedar::aux::IntParameter(this, "Cache Size in MB", 1, cedar::aux::IntParameter::LimitType::fromLower(1)))
//mOutput(new cedar::aux::MatData(cv::Mat())),
{
	// declare all data
	cedar::proc::DataSlotPtr input = this->declareInput("input");
	this->declareOutput("output", mOutput);

	// do all connections
	QObject::connect(mCacheSize.get(), SIGNAL(valueChanged()), this, SLOT(reinitializeKernelSGD()));

	// TODO: parameter of source changes
	
	// make sure that we initialize a kernel SGD
	
	input->setCheck(cedar::proc::typecheck::IsMatrix());
}



void cShark::KernelSGD::reinitializeKernelSGD() 
{
	cedar::aux::LogSingleton::getInstance()->debugMessage ("Reinitializing Kernel SGD..");

	// TODO: recreate kernel, loss etc
		
	// remove old trainer
	if (mKernelSGDTrainer != NULL) {
		delete mKernelSGDTrainer;
		mKernelSGDTrainer = NULL;
	}
	
	// reset model with our parameters
	double lambda = mLambda->getValue();
	bool offset = mOffset->getValue();
	size_t cacheSize = mCacheSize->getValue();
	size_t epochs = mEpochs->getValue();
	mKernelSGDTrainer = new KernelSGDOnlineTrainer<RealVector> (&mKernel, &mLoss, lambda, offset, false, cacheSize);
	mKernelSGDTrainer	-> setEpochs (epochs);
}



void cShark::KernelSGD::inputConnectionChanged(const std::string& inputName)
{
  // TODO: you may want to replace this code by using a cedar::proc::InputSlotHelper

  // Again, let's first make sure that this is really the input in case anyone ever changes our interface.
  CEDAR_DEBUG_ASSERT(inputName == "input");

  // Assign the input to the member. This saves us from casting in every computation step.
  this->mInput = boost::dynamic_pointer_cast<const cedar::aux::MatData>(this->getInput(inputName));

  bool output_changed = false;
  if (!this->mInput)
  {
    // no input -> no output
    this->mOutput->setData(cv::Mat());
    output_changed = true;
  }
  else
  {
    // Let's get a reference to the input matrix.
    const cv::Mat& input = this->mInput->getData();

    // check if the input is different from the output
    if (input.type() != this->mOutput->getData().type() || input.size != this->mOutput->getData().size)
    {
      output_changed = true;
    }

    // Make a copy to create a matrix of the same type, dimensions, ...
    this->mOutput->setData(input.clone());

    this->mOutput->copyAnnotationsFrom(this->mInput);
  }

  if (output_changed)
  {
    this->emitOutputPropertiesChangedSignal("output");
  }
}



void cShark::KernelSGD::compute(const cedar::proc::Arguments& arguments)
{
	// go one step in the initialized kernelsgd object
	mKernelSGDTrainer	-> oneStep ();
}
