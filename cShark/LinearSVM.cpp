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

    File:        LinearSVM.cpp

    Maintainer:  aydin demircioglu
    Email:       aydin.demircioglu@ini.rub.de
    Date:        2015 01 20

    Description: Source file for the class cShark::LinearSVM.

    Credits:

======================================================================================================================*/

// CEDAR CONFIGURATION
#include "cedar/configuration.h"

// CLASS HEADER
#include "LinearSVM.h"

// CEDAR INCLUDES
#include "cedar/processing/typecheck/IsMatrix.h"

// SYSTEM INCLUDES

using namespace shark;


//----------------------------------------------------------------------------------------------------------------------
// constructors and destructor
//----------------------------------------------------------------------------------------------------------------------



cShark::LinearSVM::LinearSVM():
	//TODO:mKernelType(new cedar::aux::X),
	//TODO:mLossType(new cedar::aux::X )
	mOutput(new CedarRealVector()),
	mOffset(new cedar::aux::BoolParameter(this, "Use Offset", false)),
	mLambda(new cedar::aux::DoubleParameter(this, "Lambda", 1.0, cedar::aux::DoubleParameter::LimitType::positive())),
	mEpochs(new cedar::aux::IntParameter(this, "Epochs", 1, cedar::aux::IntParameter::LimitType::fromLower(1)))
	//	mCacheSize(new cedar::aux::IntParameter(this, "Cache Size in MB", 1, cedar::aux::IntParameter::LimitType::fromLower(1)))
//mOutput(new cedar::aux::MatData(cv::Mat())),
{
	cedar::aux::LogSingleton::getInstance()->message("Constructing Linear SVM..", "LinearSVM");

	// declare all data
	cedar::proc::DataSlotPtr input = this->declareInput("input");
	this->declareOutput("output", mOutput);
	
	// do all connections
	QObject::connect(mOffset.get(), SIGNAL(valueChanged()), this, SLOT(reinitializeLinearSVM()));
	QObject::connect(mLambda.get(), SIGNAL(valueChanged()), this, SLOT(reinitializeLinearSVM()));
	QObject::connect(mEpochs.get(), SIGNAL(valueChanged()), this, SLOT(reinitializeLinearSVM()));
	
	// TODO: parameter of source changes
	
	// make sure that we initialize a kernel SGD
	
//	input->setCheck(cedar::proc::typecheck::IsMatrix());
}



void cShark::LinearSVM::reinitializeLinearSVM() 
{
	cedar::aux::LogSingleton::getInstance()->message("Reinitializing Kernel SGD..", "SharkLinearSVMOnlineTrainer");
	
	// TODO: recreate kernel, loss etc

	// check if there is no thread running etc
	
	// remove old trainer
	if (mLinearSVMThread != NULL) {
		// TODO: kill that thing!
		delete mLinearSVMThread;
		mLinearSVMThread = NULL;
	}
	
	// reset model with our parameters
	double lambda = mLambda->getValue();
	bool offset = mOffset->getValue();
	size_t cacheSize = mCacheSize->getValue();
	size_t epochs = mEpochs->getValue();
	mLinearSVMThread = new LinearSVMThread();
	
	// reset flags
	isDeadNow = false;
	isStarted = false;
	isFinished = false;
}



void cShark::LinearSVM::inputConnectionChanged(const std::string& inputName)
{
	// TODO: you may want to replace this code by using a cedar::proc::InputSlotHelper

	// Again, let's first make sure that this is really the input in case anyone ever changes our interface.
	cedar::aux::LogSingleton::getInstance()->message("Input Connection Changed..", "SharkLinearSVMOnlineTrainer");
	CEDAR_DEBUG_ASSERT(inputName == "input");

	// Assign the input to the member. This saves us from casting in every computation step.
	//	this->mInput = boost::dynamic_pointer_cast<ConstCedarRealVectorPtr>(this->getInput(inputName));
	//	this->mInput = boost::dynamic_pointer_cast<ConstCedarRealVectorPtr>(this->getInput(inputName));
	
	
	bool output_changed = false;
	if (!this->mInput)
	{
		// no input -> no output
		//    this->mOutput->setData(cv::Mat());
		output_changed = true;
	}
	else
	{
		// Let's get a reference to the input matrix.
		const CedarRealVector& input = this->mInput->getData();

		// check if the input is different from the output
		//    if (input.type() != this->mOutput->getData().type() || input.size != this->mOutput->getData().size)
		{
			output_changed = true;
		}

		// Make a copy to create a matrix of the same type, dimensions, ...
		//this->mOutput->setData(input.clone());

		//this->mOutput->copyAnnotationsFrom(this->mInput);
	}

	if (output_changed)
	{
		this->emitOutputPropertiesChangedSignal("output");
	}
}



void cShark::LinearSVM::compute(const cedar::proc::Arguments& arguments)
{
	// overwrite output already 
	RealVector notFinishedVec (1, -1);
	CedarRealVector deadPixel (notFinishedVec );
	this->mOutput = CedarRealVectorPtr (&deadPixel );

	// check, if we already finished all our steps
	if (isDeadNow == true) {
		// oh yes, so we do not do anything anymore until
		// we get a new input connection or some parameter changed etc
		return;
	}
		
	// check first, if our trainer thread is started or not
	if (isStarted == true) {
		// check if we are finished
		
		if (isFinished == true) {
			// get data
			KernelClassifier<RealVector> *linearSVMModel = mLinearSVMThread -> getModel ();
			
			// kill the thread now
//			mLinearSVMThread -> m_abort = true;
			if (!mLinearSVMThread -> wait(100)) {
				// why that thread!...
				// LOG ERROR
				mLinearSVMThread -> quit();
				mLinearSVMThread -> terminate();
				return;
			}
			
			// post the data to the next worker
//			this -> mOutput (Model);

			// signal that our processing stopped, and we need to be restarted again
			isDeadNow = true;
		}
		else {
			// we have to wait, so we return nothing
			return;
		}
	}
	else {
		// well, we should start now.
		mLinearSVMThread = new LinearSVMThread();
		mLinearSVMThread->run();
		isStarted = true;
	}
}



