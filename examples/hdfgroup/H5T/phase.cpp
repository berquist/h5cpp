//
// (c) Copyright 2019 DESY,ESS, Eugen Wintersberger <eugen.wintersberger@gmail.com>
//
// This file is part of h5pp.
//
// This library is free software; you can redistribute it and/or modify it
// under the terms of the GNU Lesser General Public License as published
// by the Free Software Foundation; either version 2.1 of the License, or
// (at your option) any later version.
//
// This library is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty ofMERCHANTABILITY
// or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public
// License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this library; if not, write to the
// Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor
// Boston, MA  02110-1301 USA
// ===========================================================================
//
// Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
// Created on: Jan 13, 2019
//

#include "phase.hpp"

std::ostream &operator<<(std::ostream &stream,const Phase &phase)
{
  switch(phase)
  {
    case Phase::SOLID: return stream<<"SOLID";
    case Phase::LIQUID: return stream<<"LIQUID";
    case Phase::GAS: return stream<<"GAS";
    case Phase::PLASMA: return stream<<"PLASMA";
    default:
      return stream;
  }
}



