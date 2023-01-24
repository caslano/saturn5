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
r31ngdoRwnKaQCjmkNtWDZPmavlY8KkFTx06JKPRc+5mUMv4LTwn+S02ZXP/vZ1Bfsv8tFkU8guvFnsNmWOI6PmsR6zPecflVhqL5UYfw633OMTWkcPj0/bzfy3g7WSe/W36CZr9fugnWUG8x4uKrK0iWh91aSbURruUW6mNPrSol5Bn7dgt1yO+JOLiNk73PszaA9Jcz3tQzdT8H/+wlNQZ5qH5I04hD8pVWZzrT6oxR6N6rmQ53aVGsn1mBtY0Idjvxlxl9FcdTJ3E1e582SCVO9+yW9Srj2cMU8+f89b067Mu+6eKNs+6nIa3uI33YEEYTa/DaRH2eGgWTCE/bLMkPfMVr7lYj72Wc2qOno3TLTBlCTvmIcozZwTF5rKldOIiEyJ8pkuoV8r5TcRxhWsx9a+hHL6pVM6wFqemnqTfVBoT6dJjvlHN8YGI7x7x/ciLYNwvrxn+G2V3vvhzTVpTSZdINo1ykmjRFet4jfWtWRbDf/54m4zsOkpBbfqLT1qw27aJTVHPxrBFMrb3Y6fDA0O+kKb9cu8CU10+Vt+qE6v5/OdWxjtd9xWwHscx4HOMMm/n98zzde+yW6g9dO51f44FN8+T2+fn9cwXdi16fspbabHfC1ubta+nb0MIz4U9ObXqWNW05ojf9elNeRgrfi2zsLVKpPfhtGR1tWXfWNpcZkHV6miMK5MyaGdU1mjz6LdVuHuDOqO2
*/