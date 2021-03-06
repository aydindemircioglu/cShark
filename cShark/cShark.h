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

    File:        cShark.h

    Maintainer:  aydin demircioglu
    Email:       aydin.demircioglu@ini.rub.de
    Date:        2015 01 20

    Description: Header file for the class cShark::SparseData.

    Credits:

======================================================================================================================*/

#ifndef C_SHARK_H
#define C_SHARK_H

#include "SharkSVM/LabelOrder.h"

using namespace shark;

typedef cedar::aux::DataTemplate<shark::RealVector> CedarRealVector;
CEDAR_GENERATE_POINTER_TYPES(CedarRealVector);

typedef shark::LabeledData<shark::RealVector, unsigned int> SharkSVMData;
typedef cedar::aux::DataTemplate<SharkSVMData> CedarSVMData;
CEDAR_GENERATE_POINTER_TYPES(CedarSVMData);

typedef cedar::aux::DataTemplate<shark::Data<shark::RealVector> > CedarDataRealVector;
CEDAR_GENERATE_POINTER_TYPES(CedarDataRealVector);

typedef cedar::aux::DataTemplate<shark::RealMatrix> CedarRealMatrix;
CEDAR_GENERATE_POINTER_TYPES(CedarRealMatrix);

typedef cedar::aux::DataTemplate<LabelOrder> CedarLabelOrder;
CEDAR_GENERATE_POINTER_TYPES(CedarLabelOrder);



#endif // C_SHARK_H

