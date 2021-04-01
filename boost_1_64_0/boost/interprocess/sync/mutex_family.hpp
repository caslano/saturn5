//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2005-2012. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTERPROCESS_MUTEX_FAMILY_HPP
#define BOOST_INTERPROCESS_MUTEX_FAMILY_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/interprocess/detail/config_begin.hpp>
#include <boost/interprocess/detail/workaround.hpp>

#include <boost/interprocess/sync/interprocess_mutex.hpp>
#include <boost/interprocess/sync/interprocess_recursive_mutex.hpp>
#include <boost/interprocess/sync/null_mutex.hpp>

//!\file
//!Describes a shared interprocess_mutex family fit algorithm used to allocate objects in shared memory.

namespace boost {

namespace interprocess {

//!Describes interprocess_mutex family to use with Interprocess framework
//!based on boost::interprocess synchronization objects.
struct mutex_family
{
   typedef boost::interprocess::interprocess_mutex                 mutex_type;
   typedef boost::interprocess::interprocess_recursive_mutex       recursive_mutex_type;
};

//!Describes interprocess_mutex family to use with Interprocess frameworks
//!based on null operation synchronization objects.
struct null_mutex_family
{
   typedef boost::interprocess::null_mutex                   mutex_type;
   typedef boost::interprocess::null_mutex                   recursive_mutex_type;
};

}  //namespace interprocess {

}  //namespace boost {

#include <boost/interprocess/detail/config_end.hpp>

#endif   //#ifndef BOOST_INTERPROCESS_MUTEX_FAMILY_HPP



/* mutex_family.hpp
dbkF1IoWpGc/NYRdk5oAKC/LtcdnAdBj8YYxK7Fe3I8jOHZUJEwVjg2ljFldQX6XKFkzSeYjcDI9bUTtydZ3Mg5wbTxu/EIC3l7x3VVpwQ/zuW9WuLMrr4xO/5Zx8QtERfwk0XWtafaPJkneHyD2UW2UxrNPl8KaoxyzeXg3HvKglUvtoReTQldZ2evROjuHMffIrEALgRU0vJvNHK9Gh+JvBiuL8DaExQgLaGxjk0JIrf8ZNht0fbxkL9JjWKzh3dzpRAGTCFW7Ong9lXEVeqg6C/2uWWiVn2y/PaxFSG9e1+BIsPWyUueimd6q9FEZ8jDzvZV2Nf2sNoG14R8wOrIyiJxj8b5y3ue1j0w3DdTDbEgH//Ha3huRQE3vNrbTWwnHoRRj4NNIDxHQYgIPKBd5mVuF68XQvmhyfe7IKeu8+4e3wsszJXrl08LoAWuMGVtg2/uAAf1iiFKpay++/SMmHNxWNRwGhVyvobepdNTVvk4ZMkYnvHgCaNRGsz9izUJLtICB1mRRMXERJODCQL7vczUWLUYDH85zYPxnImcKoB4kLczch8UVQA==
*/