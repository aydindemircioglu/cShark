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

    File:        SparseData.cpp

    Maintainer:  aydin demircioglu
    Email:       aydin.demircioglu@ini.rub.de
    Date:        2015 01 20

    Description: Source file for the class cShark::SparseData.

    Credits:

======================================================================================================================*/

// CEDAR INCLUDES
#include "Plugin.h"

// !!!!!!!!!!!!! IMPORT ORDER IS IMPORTANT HERE !!!!
#include <boost/foreach.hpp>
#include <QObject>


#include <cedar/processing/ElementDeclaration.h>


#include "KernelSGD.h"
#include "LIBSVMModelWriter.h"
#include "LinearSVM.h"
#include "SparseData.h"


using namespace cShark;


void pluginDeclaration(cedar::aux::PluginDeclarationListPtr plugin)
{
	cedar::proc::ElementDeclarationPtr SparseDataDeclaration
	(
		new cedar::proc::ElementDeclarationTemplate
		<
		SparseData
		>
		(
			"cShark"
		)
	);
	SparseDataDeclaration->setDescription("Read a Sparse Data File (a.k.a. LIBSVM format).");
	plugin->add(SparseDataDeclaration);
	
	
	cedar::proc::ElementDeclarationPtr KernelSGDDeclaration
	(
		new cedar::proc::ElementDeclarationTemplate
		<
		KernelSGD
		>
		(
			"cShark"
		)
	);
	KernelSGDDeclaration->setDescription("Kernel SGD (bad hack).");
	plugin->add(KernelSGDDeclaration);
	
	
	cedar::proc::ElementDeclarationPtr LinearSVMDeclaration
	(
		new cedar::proc::ElementDeclarationTemplate
		<
		LinearSVM
		>
		(
			"cShark"
		)
	);
	LinearSVMDeclaration->setDescription("Linear SVM (bad hack).");
	plugin->add(LinearSVMDeclaration);
	
	
	
	cedar::proc::ElementDeclarationPtr LIBSVMModelWriterDeclaration
	(
		new cedar::proc::ElementDeclarationTemplate
		<
		LIBSVMModelWriter
		>
		(
			"cShark"
		)
	);
	LIBSVMModelWriterDeclaration->setDescription("LIBSVM Model Writer (bad hack).");
	plugin->add(LIBSVMModelWriterDeclaration);
	
}

