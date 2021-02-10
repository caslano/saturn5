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
p5vLJhR7m2ZA1FUXL/Spv4Pn9fdpTugksDX7adma50erpnl7n8Hfyza3XOOWtnvn9KCYj0SbEtt7ZWLocDvqeLe9aUG3b/St2Zx+v77m89zVZ/rfy171LrTH8ZwQauWGDgfnDk1DN8n7hTnxDp8/zjVz+b7Gz6bxRD8Z+kR3V+d4e7jR5wZlvZ2utNWMoTkxFlNCJaADZtk6cUK75Prq61+3jxn67a//Okoqgg56Yg1BMy5tMretCXEcy96Mv9P7NDh/9+XDrzf9z5/Gn0fntLaYM4+92RRdRlDH2LV18/7Ssqgi9z3XXlB5wseCM68WJpU9GPLexcJw9esH2xvVKZ1h3fbOCcF1gcwj8p0Y3u7xpqLIr4Lrftdsk35eftdb/u/rbjt00J9CO/Ome0Uca2FPyO5sSpGziIp9KsbCJr2Tx5PXJ7/QJvmfmScUhwlEByRKiGXUQETDBoSuw1NiTrwCfjidm1edljeVfxhTbe7/Tf9NFrbR2p3i29eG2hYqdH1XL9z5YvlO1U1sRWh9CT6cP7rHyyiT4PT9VvuTLU7O1BCwUDf2Cwt1JqKu9V20uB0/OXSZ7tHiHcvwbqL1ofX6uuzUhTZ5oItPz///P35+EyAg+MYfvWCc6HK1v/7z5kKMswWUACVACVAC
*/