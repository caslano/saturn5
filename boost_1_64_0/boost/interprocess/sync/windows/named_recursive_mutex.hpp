 //////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2011-2012. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_INTERPROCESS_WINDOWS_RECURSIVE_NAMED_MUTEX_HPP
#define BOOST_INTERPROCESS_WINDOWS_RECURSIVE_NAMED_MUTEX_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/interprocess/detail/config_begin.hpp>
#include <boost/interprocess/detail/workaround.hpp>
#include <boost/interprocess/sync/windows/named_mutex.hpp>

namespace boost {
namespace interprocess {
namespace ipcdetail {


class windows_named_recursive_mutex
   //Windows mutexes based on CreateMutex are already recursive...
   : public windows_named_mutex
{
   #if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)

   //Non-copyable
   windows_named_recursive_mutex();
   windows_named_recursive_mutex(const windows_named_mutex &);
   windows_named_recursive_mutex &operator=(const windows_named_mutex &);
   #endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED

   public:
   windows_named_recursive_mutex(create_only_t, const char *name, const permissions &perm = permissions())
      : windows_named_mutex(create_only_t(), name, perm)
   {}

   windows_named_recursive_mutex(open_or_create_t, const char *name, const permissions &perm = permissions())
      : windows_named_mutex(open_or_create_t(), name, perm)
   {}

   windows_named_recursive_mutex(open_only_t, const char *name)
      : windows_named_mutex(open_only_t(), name)
   {}
};

}  //namespace ipcdetail {
}  //namespace interprocess {
}  //namespace boost {

#include <boost/interprocess/detail/config_end.hpp>

#endif   //BOOST_INTERPROCESS_WINDOWS_RECURSIVE_NAMED_MUTEX_HPP

/* named_recursive_mutex.hpp
9G/VF658DEcY2UjXaCnRd8k1sJcGsKdZ65aza8n/TV8MGSuNE/EgZoZVeb9VUZLlPKbz6so/mWAbYqdFuEei+9YPdP9Tv9TX26Ky6rkJqYxckWUMaW//3Ms10hIul8lkEEYIY8XgLvXLCEgGkDUUnl+CEjE0MGGMHeu6St4jDXehljLK+8G0+mWsdT7j+vclsjpNn+F/DNnizFHfkDeyFvVXagb5+7Go/P465sZKi+HccOnYjGj/LBny60ubuN9J4JbL5V8Sc0l+QiLZC9SrjYnERD05YG/rwRLvhv+5YZjZ2pEeFhsoN8YVeI/sYq2X621HlX3w8g+GWbqoSOIPqTypCpBDJl9pu6FJsxXuVkDC4v0r5dXaM2YLzl5jqlgFRl5Odp1gN2oBrmXnBperlXwZAJ5qznMjGGl0oGmaa64H3v+LfBCAcg1nXt/H5cYsbyPl8kygG3peNUeCRfsN/sfGvKTiYn3njwjItD1vnrewTU5h9i5U7p7AjoOlszyiKsar4+HQ11xbrf+mhP1fX715KaltSqoF3Sq4kfu7dOj5Q+ERHh/SCMxcEQ==
*/