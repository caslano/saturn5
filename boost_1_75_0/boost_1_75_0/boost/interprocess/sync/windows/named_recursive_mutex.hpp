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
PQuvldS90RMlt+hbMTy9P+D9ge4WqXpLeP/Fc85Fseo1EjVyP9i46jUGQ3JLTphtsWe4RnLk8j6ZpQp2vVKAO3vLxDp1sXcifm6x2cJHOiZBaa2o/ogd0ODCT66Sg6viTCPwIckXYdmGjneUukqWwk+k531oOab65LlXslTgs6DTKGtyAjBOMy7pSvgh+vVCV5g36/rJ/MFGcUS/s+C+5cBqOC7XFfhAMn81+I4hYNFd+cGqzSVradBMGyNaj3X2r2etzV9X3OcabF7mW8Je9+6umXLe8qOmAvj2AXhoU+7CD47CAoJpTPSsyQL8xFE0BRb4bbe7lxyW53h6RNoVqfoObJCRg/m15c77z91r2EfXxVffCVOQinec2sJOPEp1P5NKpeomkzTD9zqZFrAXTNO3gtsbCYrmOxUvs0CvsOI9F0P7uMyEkgPKlqJjV/sPuACDACps798VyrmCnsf+Qq5rSbyv9fzpzYs9HoLd7iasuVGDsdm/l3+DZiNybXUKFg/lWSsPuDW6JjqzbawrzGOtnIT8ZyC0buWJDTJ8LYHHg85+OB2CQfXmAit4stUEbju1oznG8fcA7DN/igcvURWe/eFWImctL9HMAzp/ViNZ5kbJ+sFsO6wiisrNiqlZa7ITGYhqMiiraGZR3jHn8vN6Uuoq9vXvbEFbhouSLf42R5aCmeXdaTCCtMt2Zd9KMU9hIPaCI6gAKRnI
*/