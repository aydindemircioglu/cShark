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

    File:        LIBSVMModelWriter.cpp

    Maintainer:  aydin demircioglu
    Email:       aydin.demircioglu@ini.rub.de
    Date:        2015 01 20

    Description: Source file for the class cShark::LIBSVMModelWriter.

    Credits:

======================================================================================================================*/

// CEDAR CONFIGURATION
#include "cedar/configuration.h"

// CLASS HEADER
#include "LIBSVMModelWriter.h"

// CEDAR INCLUDES
#include "cedar/processing/typecheck/IsMatrix.h"

// SYSTEM INCLUDES

using namespace shark;


cShark::LIBSVMModelWriter::LIBSVMModelWriter():
	mInput(new CedarRealVector()),
	mFilename(new cedar::aux::FileParameter(this, "Filename", cedar::aux::FileParameter::READ, "none"))
{
	// declare all data
	cedar::proc::DataSlotPtr input = this->declareInput("input");

	// do all connections
	QObject::connect(mFilename.get(), SIGNAL(valueChanged()), this, SLOT(updateFilename()));
  
//	input->setCheck(cedar::proc::typecheck::IsMatrix());
}



void cShark::LIBSVMModelWriter::updateFilename() 
{
	cedar::aux::LogSingleton::getInstance()->debugMessage ("Changing file name of data..");

	// change filename
	std::string trainingDataPath = mFilename->getPath();

	// what else?
}



void cShark::LIBSVMModelWriter::inputConnectionChanged(const std::string& inputName)
{
	// TODO: you may want to replace this code by using a cedar::proc::InputSlotHelper

	// Again, let's first make sure that this is really the input in case anyone ever changes our interface.
	CEDAR_DEBUG_ASSERT(inputName == "input");


	bool output_changed = false;

	if (output_changed) {
		this->emitOutputPropertiesChangedSignal("output");
	}
}



void cShark::LIBSVMModelWriter::compute(const cedar::proc::Arguments& arguments)
{
	// TODO: write model
}
