//
// (c) Copyright 2018 DESY,ESS
//
// This file is part of h5cpp.
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
// Author: Jan Kotanski <jan,kotanski@desy.de>
// Created on: Jul 2, 2018
//
#include <catch2/catch.hpp>
#include <h5cpp/datatype/ebool.hpp>
#include <h5cpp/datatype/enum.hpp>
#include <h5cpp/hdf5.hpp>

using namespace hdf5;

#ifndef _MSC_VER

SCENARIO("given an HDF5 file") {
  auto h5file =
      file::open("../pniio_test_boolattr.h5", file::AccessFlags::READONLY);
  auto root = h5file.root();

  GIVEN("a scalar bool attribute with value true") {
    auto attr = root.attributes["bool_true"];
    THEN("the datatype will be integer") {
      REQUIRE(attr.datatype().get_class() == datatype::Class::INTEGER);
      AND_THEN("of size 1") { REQUIRE(attr.datatype().size() == 1ul); }
    }

    THEN("we can read its value as native C++ bool value") {
      bool buffer;
      REQUIRE_NOTHROW(attr.read(buffer));
      REQUIRE(buffer);
    }

    THEN("we can read its value as EBool value") {
      datatype::EBool buffer;
      attr.read(buffer, attr.datatype());
      REQUIRE(buffer == true);
      REQUIRE(buffer == 1);
      REQUIRE(buffer == datatype::EBool::TRUE);
    }

    GIVEN("a scalar bool attribute of value false") {
      auto attr = root.attributes["bool_false"];
      THEN("we can read its value as native C++ bool") {
        bool buffer;
        REQUIRE_NOTHROW(attr.read(buffer));
        REQUIRE_FALSE(buffer);
      }

      THEN("we can read its value as EBOOL value") {
        datatype::EBool buffer;
        REQUIRE_NOTHROW(attr.read(buffer, attr.datatype()));
        REQUIRE(buffer == false);
        REQUIRE(buffer == 0);
        REQUIRE(buffer == datatype::EBool::FALSE);
      }
    }
  }

  GIVEN("an array attribute of bool values") {
    auto attr = root.attributes["bool_array"];
    // we cannot read to std::vector<bool> as this is not an addressable type
    THEN("we can read the values to a vector of unsigned char") {
      using bools = std::vector<unsigned char>;
      bools buffer(4);
      REQUIRE_NOTHROW(attr.read(buffer));
      bools expected = {0, 1, 1, 0};
      REQUIRE_THAT(expected, Catch::Matchers::Equals(buffer));
    }

    THEN("we can read the values to a vector of ebool") {
      using EBool = datatype::EBool;
      using bools = std::vector<EBool>;
      bools buffer(4);
      REQUIRE_NOTHROW(attr.read(buffer, attr.datatype()));
      bools expected = {EBool::FALSE, EBool::TRUE, EBool::TRUE, EBool::FALSE};
      REQUIRE_THAT(expected, Catch::Matchers::Equals(buffer));
    }
  }
}

#endif
