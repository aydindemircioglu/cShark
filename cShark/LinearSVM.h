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

    File:        LinearSVM.h

    Maintainer:  aydin demircioglu
    Email:       aydin.demircioglu@ini.rub.de
    Date:        2015 01 20

    Description: Header file for the class cShark::LinearSVM.

    Credits:

======================================================================================================================*/

#ifndef C_SHARK_LINEAR_SVM_H
#define C_SHARK_LINEAR_SVM_H

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
#include <shark/ObjectiveFunctions/Loss/HingeLoss.h>
#include <shark/Algorithms/Trainers/CSvmTrainer.h> // the C-SVM trainer
#include <shark/Models/Kernels/GaussianRbfKernel.h> //the used kernel for the SVM
#include <shark/ObjectiveFunctions/Loss/ZeroOneLoss.h> //used for evaluation of the classifier
#include <shark/Data/DataDistribution.h> //includes small toy distributions

using namespace shark;
using namespace std;


// FORWARD DECLARATIONS
#include "LinearSVM.fwd.h"

// SYSTEM INCLUDES


using namespace shark;




class LinearSVMThread: public QThread
{
	Q_OBJECT

public:	
	bool start;
	bool finished;
	GaussianRbfKernel<> *kernel;
	KernelClassifier<RealVector> *kc; // (affine) linear function in kernel-induced feature space
	ClassificationDataset *training;
	double gamma;
	double C;
	bool bias;
	
	// eats everything any linear SVM would need
	LinearSVMThread () {
		unsigned int ell = 500;     // number of training data point
		gamma = 0.5;         // kernel bandwidth parameter
		C = 1000.0;          // regularization parameter
		bias = true;           // use bias/offset parameter
		
		// init kernel
		kernel = new GaussianRbfKernel<>(gamma);
		
		Chessboard problem; // artificial benchmark data
		*training = problem.generateDataset(ell);
		
		// threading things
		start = false;
		finished = false;
	}

	~LinearSVMThread() {
		delete kernel;
		delete training;
	}
	
	KernelClassifier<RealVector>* getModel () {
		return (kc);
	}
	
	bool resultReady() {
		return finished;
	}

	void run() {
		CSvmTrainer<RealVector> trainer(kernel, C, bias);
		trainer.train(*kc, *training);
		
		// 		cout << "\n  number of iterations: " << trainer.solutionProperties().iterations;
		// 		cout << "\n  dual value: " << trainer.solutionProperties().value;
		// 		cout << "\n  training time: " << trainer.solutionProperties().seconds << " seconds\ndone." << endl;
		// 		
		// for now just sleep little baby.
		QThread::sleep (10);
		finished = true;
		
		// sleep till death?
	}
	
};



/*!@todo describe.
 *
 * @todo describe more.
 */
class cShark::LinearSVM : public cedar::proc::Step
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
  LinearSVM();

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
	void reinitializeLinearSVM();
	
	

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

	//!@brief thread control
	bool isDeadNow;
	bool isStarted;
	bool isFinished;
	
	//!@brief parameter for using bias term or not
	cedar::aux::BoolParameterPtr mOffset;
	
	//!@brief regularization term
	cedar::aux::DoubleParameterPtr mLambda;

	//!@brief number of epochs
	cedar::aux::IntParameterPtr mEpochs;
	
	//!@brief cache size
	cedar::aux::IntParameterPtr mCacheSize;

	//!@brief we need the trainer in its own thread
	LinearSVMThread *mLinearSVMThread;
	
	//!@brief kernel to use FIXME should be abstract blabla
	GaussianRbfKernel<> mKernel;
	
	//!@brief loss function FIXME should be abstract blabla
	HingeLoss mLoss;
	
}; // class cShark::LinearSVM



#endif // C_SHARK_LINEAR_SVM_H




