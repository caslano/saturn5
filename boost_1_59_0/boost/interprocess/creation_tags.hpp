//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2005-2012. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTERPROCESS_CREATION_TAGS_HPP
#define BOOST_INTERPROCESS_CREATION_TAGS_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/interprocess/detail/config_begin.hpp>
#include <boost/interprocess/detail/workaround.hpp>

namespace boost {
namespace interprocess {

//!Tag to indicate that the resource must
//!be only created
struct create_only_t {};

//!Tag to indicate that the resource must
//!be only opened
struct open_only_t {};

//!Tag to indicate that the resource must
//!be only opened for reading
struct open_read_only_t {};

//!Tag to indicate that the resource must
//!be only opened privately for reading
struct open_read_private_t {};

//!Tag to indicate that the resource must
//!be only opened for reading
struct open_copy_on_write_t {};

//!Tag to indicate that the resource must
//!be created. If already created, it must be opened.
struct open_or_create_t {};

//!Value to indicate that the resource must
//!be only created
static const create_only_t    create_only    = create_only_t();

//!Value to indicate that the resource must
//!be only opened
static const open_only_t      open_only      = open_only_t();

//!Value to indicate that the resource must
//!be only opened for reading
static const open_read_only_t open_read_only = open_read_only_t();

//!Value to indicate that the resource must
//!be created. If already created, it must be opened.
static const open_or_create_t open_or_create = open_or_create_t();

//!Value to indicate that the resource must
//!be only opened for reading
static const open_copy_on_write_t open_copy_on_write = open_copy_on_write_t();

namespace ipcdetail {

enum create_enum_t
{  DoCreate, DoOpen, DoOpenOrCreate   };

}  //namespace ipcdetail {

}  //namespace interprocess {
}  //namespace boost {

#include <boost/interprocess/detail/config_end.hpp>

#endif   //#ifndef BOOST_INTERPROCESS_CREATION_TAGS_HPP


/* creation_tags.hpp
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
*/