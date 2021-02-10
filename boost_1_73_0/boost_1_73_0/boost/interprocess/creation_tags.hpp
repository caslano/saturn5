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
yM7gK/7BeVieD4+BaZ5stdu38O36+jf4BX++XU/gD7PXsJT1YaPsbjBdKXuonKuMhtZA59QECvSewMGU1RZ/pS6vjIWycq2tNl2roN1XDpzZtkdpFWxxU+onwmo62xin4Fi1e8Bl+jVdC1ulAF32yqrNE+ys1K0qJ9BY81iVqkRA2eI/BXJjHhUhFacEtGmrQhGLPm7zzHfcaholLVQaZF2TZ6Xc5ZBdtuAgkll2x1IOoYBVmtyGUz6FT0zg+ydg8dQbsXW2SFKYhiKIWLgUwKII0CtlcRZyQVh3YbaAlM9Zii4JeiHeM3YcROtpGM+9Y7hcRSFGeQaAZEYYS54GC1xhN2EUZvc+/CzMYi7EJWJAnAC/5XEGYkE4L5jdcIhCdhNxmCUpQbH4HsSKByGLJsg75UE2QYjxCV1QJ4L/tUY4tIEpW7I5EUm96/DqE1uwTCQYN8X0xDrKKI1ZmiwhSgQxh7XgGINljLzxDJGymKAfR4Ip8WaxpxRkYRKTA4bOUkY8Yj6PwjmPA06+iXfIkhQN12JwmABLQ0FBkzWJmQASD4swMe9B/enTeSAXz4KneBBL5oFnr6sxVP/q7OwKJUCqwT+tFGmN5BoYva12HYq3Va51JPyd6hVYGGtV0YL6UbXgWtl2joAeTVVC
*/