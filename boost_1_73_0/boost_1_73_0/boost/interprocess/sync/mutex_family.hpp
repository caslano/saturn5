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
qOofSd9eBi7CZAlsBbaKZCvmvWRlYhUssIM+qkUfqvhakjeOgYRAQiAhzGG47BKrDJlgYRw0tEU0pOBcSP6WMJAZyAxkVj4yyzenCo589aTqdt+5P+2dn/TnJ74e392eRZz+112vE3Ga6mvE2dvz/uxs2KPkfpxF92P9tN+P9dNeP9bPev04y9SPm4Ru+1+hq11PPxp6VH/7/mtnKgjnWnOfd75d6APbcqxHt9EZjxvu9Kd6rblw99SCnGsPxDiqU8ETnyiDVuqB+OZXtt/435z3ntf+P1BLAwQKAAAACAAtZ0pSEjOWz6EBAAAvAwAAPQAJAGN1cmwtbWFzdGVyL3Byb2plY3RzL1dpbmRvd3MvVkMxMS9saWIvbGliY3VybC52Y3hwcm9qLmZpbHRlcnNVVAUAAbZIJGCVktuOmzAQhu/3KRD3DoRzOoQVbEKbu1VP98EM4Ajb1DYpUtV3r2m60kpV21Saf6Sx/hnNJ0/+uPDRuaLSTIq9u934roOCypaJfu/OpiOZ+1g85M9KXpAa56OUo/78Yo9Wux0g9N4djJneeJ6mA/Kz3nBGldSyMxsqudfiFUc5ofK4bmY2tl7g+6FbPDhOfjLI3yo5T2tl65qNBpVzEnScW9y7H+SsKDr2GbV781jXJ8G+
*/