/*
 * Copyright (C) 2019  Rhys Mainwaring
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
*/

#include <cmath>

#include "laser_rahcm_simulation/Physics.hh"
#include "laser_rahcm_simulation/PhysicalConstants.hh"

namespace asv
{
  /////////////////////////////////////////////////
  double Physics::DeepWaterDispersionToOmega(double _wavenumber)
  {
    const double g = std::fabs(PhysicalConstants::Gravity());
    return std::sqrt(g * _wavenumber);
  }

  /////////////////////////////////////////////////
  double Physics::DeepWaterDispersionToWavenumber(double _omega)
  {
    const double g = std::fabs(PhysicalConstants::Gravity());
    return _omega * _omega / g;
  }
}
