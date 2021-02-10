//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2005-2012. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTERPROCESS_DETAIL_WINDOWS_RECURSIVE_MUTEX_HPP
#define BOOST_INTERPROCESS_DETAIL_WINDOWS_RECURSIVE_MUTEX_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/interprocess/detail/config_begin.hpp>
#include <boost/interprocess/detail/workaround.hpp>
#include <boost/interprocess/sync/windows/mutex.hpp>

namespace boost {
namespace interprocess {
namespace ipcdetail {

//Windows mutex is already recursive
class windows_recursive_mutex
   : public windows_mutex
{
   windows_recursive_mutex(const windows_recursive_mutex &);
   windows_recursive_mutex &operator=(const windows_recursive_mutex &);
   public:
   windows_recursive_mutex() : windows_mutex() {}
};

}  //namespace ipcdetail {
}  //namespace interprocess {
}  //namespace boost {


#include <boost/interprocess/detail/config_end.hpp>

#endif   //BOOST_INTERPROCESS_DETAIL_WINDOWS_RECURSIVE_MUTEX_HPP

/* recursive_mutex.hpp
rAarwWqwWilWc9xDTGM1dh0VN5Qj3by1MZXhxYUXF15cxUmbDbQV5CzX/cg8VrEyXmAV9zAP1RQFC8FCsBAsrLDNmZWF2BGNd8rW4/XH8KvCrwq/ahUJV6+fYxQ28dZZIuEYVct2jOLlwdiKwCvwCrwCr7LxWthqBF4VNUcj87tV2CCFdxXeVXhXFYdjrdjIxfRUxjuqzE7hQdp7oBfoBXqBXhWz7JShl3p7e7V5vQJckXBFwhVZRV7V+BcUHLf90mJZsFGouOmId/yB1WA1WA1Wq8lqjnuIaazGrqPihjLeRAgvLry48OKq68Wt7i88uO5H5rGKlfECq7iHeaimKFgIFoKFFWHhmnjY3YzY3cxjdSrDQoV2RKlEU+uH0xiPL4cVtu7gXIVzFc5VdTAXg7Zt+oWcq9UiWMkvpq+PR1Oh3cdt0G0ODQefQD1QD9QD9cRQz/TGwND/BgKBQKm23sE4OwFJQBKQrBQkK8zFWOcmuFgJH2jYNAQkAUlAEpBUEZJ1sSRBzGoQMxxBU5N9Q0TCIBIGkTCqIm47EqZaUCvZPVpdf2Q8ReqyKQekAClAiqpIibKawJdD4MvhOPNAIBAIBFKVQNWFTsmeujq6xg50OwkEAoFAIFUJVBMbqLY48j+tloqr/s0fN/2b
*/