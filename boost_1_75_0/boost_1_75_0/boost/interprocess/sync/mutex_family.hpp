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
WN2ynl27aSVwydMonRQvI6CS4n0stxKmoIiy/6JBD1d/vVDEPsDTAxXjeCa0iCf9JmMR72nGccdHWyqOKqxE8JLjnCBMgy0qEpWdhnnO/H014g8w++dCOdfwNA7EKOQaGetUWgY3Paee1a1dCLdzY3Ifn4EGP9yRNQmZBahAOS9DzkjxGa+6Bv04K3pf+djoaQsKvYfXtBn2Ws933yfREYJdnaS3PwLEwvKv5I8o5onhGH7nP7a8Ip+CybSZNbRUPj7/E7h1pdmr/GsIQTRoeQfTA38rENjPtk2/ApGPxkFJAW+vm/FhMxnRvqFthUJDKfQC3LeXHXG3QkA9Dq5Hb2Eel5o7o6JEw1NhmjvAWbAokn8w1RMhdTgcMyDMYceT00sxdpRDYqV2uJaeKP5xLJ7GQrqSrnxHdlLnWqiEpbHaP2UgATenqLMxJucMp/gmUBugKjlJiJq2yvBERybLYUNFy0EsuH1shVpEzzDfQkmgmBSsfT4jDPEIGaRq/0EoKmH68TyGxn3vLq0HS7BvtFSBfzM7mmoQXpajhj/LzKaq9yGvkYpn1uwvz6FSqbVBagrS1vWZk/C/vmp5K0Sh2LsLUum62bQncl9+2UrYYTFmmTjgoZDVc/gZ4KC6i8F5Gx9tjOEK0xqe/5N9eZuU9inpcWkmPv77wuCvahH1Aldh8rgxhjhZAe+06oYk1eIKSyYzHj36ErLFbnlk
*/