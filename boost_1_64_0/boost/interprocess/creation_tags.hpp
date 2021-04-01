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
KckKHpNleKwGvvq7SsuCE8/ANLLv9b6+JNlM4hqhZBkQ9Z09TlFc/uuzilSda41MgepR7LimkB00VeA4tGjhoBeXOB5/MFa8s6U2KEBq+YPBM8bsJUPY0is4jzYk3ocFW31/vsVibiuf5kCyyk3iP7rAM3dNY0gCMIxm83fa8WKZJBSWC740SDusTRkDRLSk+5gSxyiuPzbjmL8q6O9ax7bcgfw6n+8HK3o78rE7cQowgJxS0BOqYeXTNh6+sVKAWGOhL/uWyn4omkzD1VpZzCEFwhlqvlYldHxpHCfVPLrCexCMFts5A6zyhBbeZPvRih0CfniCTtcwdxxe+blxeAYi4lhhgFGn9LJLh7s/bRdfa6muohv6/ktiBgChO1+upkJYcZpXDX5tPCpbzIwNQXuD/Ynsr+tdiV9Q9DK1BQrP9eZt5YlJ+0vit0tSUQw1A4q3H+5HUPWrhttNL+Rcrp/npdf0WKjM8lTjfzMlySE1bl1TDotH2m/IqDCTyVZjVfwPtlSg0bkzD8NLkEXDejURK59Fvq/5FD7ZMlDb0piYOpj1+gxpayPCsQ==
*/