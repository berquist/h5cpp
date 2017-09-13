//
// (c) Copyright 2017 DESY,ESS
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
// Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
// Created on: Aug 24, 2017
//
#pragma once

#include "node.hpp"
#include "link_view.hpp"
#include "node_view.hpp"
#include "dataset.hpp"
#include "../iterator_config.hpp"
#include "../property/link_creation_list.hpp"
#include "../property/group_creation_list.hpp"
#include "../property/group_access_list.hpp"
#include "../property/dataset_creation_list.hpp"
#include "../property/dataset_access_list.hpp"
#include "../dataspace/dataspace.hpp"
#include "../datatype/datatype.hpp"


namespace hdf5 {
namespace node {

class DLL_EXPORT Group : public Node
{
  public:
    LinkView      links;
    NodeView      nodes;

    Group();
    Group(const Group &group);
    Group(const Node &node);

    Group &operator=(const Group &group);

    //!
    //! \brief close the group
    //!
    void close() const;

    //!
    //! \brief flush group
    //!
    void flush() const;

    //!
    //! \brief get reference to the iterator configuration
    //!
    //! Return a non-const reference to the iterator configuration for the group.
    //! \return reference to iterator configuration
    //!
    IteratorConfig &iterator_config() noexcept
    {
      return iter_config_;
    }

    //!
    //! \brief get reference to the interator configuration
    //!
    //! Return a const reference to the iterator configuration of the gruop.
    //! \return reference to iterator configuration
    //!
    const IteratorConfig &iterator_config() const noexcept
    {
      return iter_config_;
    }

    //!
    //! \brief create a new group
    //!
    Group create_group(const std::string &name,
                       const property::LinkCreationList &lcpl = property::LinkCreationList(),
                       const property::GroupCreationList &gcpl = property::GroupCreationList(),
                       const property::GroupAccessList &gapl = property::GroupAccessList());

    //!
    //! \brief create a new dataset
    //!
    //! Like for groups the
    Dataset create_dataset(const std::string &name,
                           const datatype::Datatype &type,
                           const dataspace::Dataspace &space,
                           const property::LinkCreationList &lcpl = property::LinkCreationList(),
                           const property::DatasetCreationList &dcpl = property::DatasetCreationList(),
                           const property::DatasetAccessList &dapl = property::DatasetAccessList()
                           );

  private:
    IteratorConfig iter_config_;

};

} // namespace node
} // namespace hdf5