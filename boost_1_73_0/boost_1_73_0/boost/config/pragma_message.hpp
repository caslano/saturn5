#ifndef BOOST_CONFIG_PRAGMA_MESSAGE_HPP_INCLUDED
#define BOOST_CONFIG_PRAGMA_MESSAGE_HPP_INCLUDED

//  Copyright 2017 Peter Dimov.
//
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt
//
//  BOOST_PRAGMA_MESSAGE("message")
//
//  Expands to the equivalent of #pragma message("message")
//
//  Note that this header is C compatible.

#include <boost/config/helper_macros.hpp>

#if defined(BOOST_DISABLE_PRAGMA_MESSAGE)
# define BOOST_PRAGMA_MESSAGE(x)
#elif defined(__INTEL_COMPILER)
# define BOOST_PRAGMA_MESSAGE(x) __pragma(message(__FILE__ "(" BOOST_STRINGIZE(__LINE__) "): note: " x))
#elif defined(__GNUC__)
# define BOOST_PRAGMA_MESSAGE(x) _Pragma(BOOST_STRINGIZE(message(x)))
#elif defined(_MSC_VER)
# define BOOST_PRAGMA_MESSAGE(x) __pragma(message(__FILE__ "(" BOOST_STRINGIZE(__LINE__) "): note: " x))
#else
# define BOOST_PRAGMA_MESSAGE(x)
#endif

#endif // BOOST_CONFIG_PRAGMA_MESSAGE_HPP_INCLUDED

/* pragma_message.hpp
6E4m6B8tlVj3Ee7pwzzM33SOXXITjUy+Q6+OiQHLSpp9gX8Ob3AedTSr3hvTU/Ctku7pv6Ag+DHTLDTWExoAjUA1FAN70rfUkDmCH2wDnJ6E83MvSc17eHKCE2KvVrWNd+kW8aulP18tt2CmO95nz595H/2ZnywtL8+7fx3dnBqH+TRZzAP47M0WU2tOFV6I0iSbpuEZEjQl6YZXK0u2TcMFXmzdZds5LoKzAM+XhkbZOqjmqtOMHU+n4M3iEAf/4/x52cAevBlio5/JYbthwv6rqouovyi2zn8DUEsDBAoAAAAIAC1nSlKHbQFrEQQAAAcJAAA+AAkAY3VybC1tYXN0ZXIvZG9jcy9saWJjdXJsL29wdHMvQ1VSTElORk9fQ09OVEVOVF9MRU5HVEhfVVBMT0FELjNVVAUAAbZIJGCtVWtzm0YU/c6vuKXTVvZgZDVuXSdupkQmMWMFGIHiakYzzAoWsw1imd3Fj8b577nLI4rt1vaHoJGA3XvPuY9zV/bKhN3vdhm2hoMnr6T9JnjhfXAKBf+Hpuq/HZLkFroPOq7w/gyqMWy9bpMdeJbXLYxar6TnOtbPSfIMupUOUv+MtfMq0Y+40nn2/lNe3wh2USgYTXdgcnT0B+zBr/uTQwtOSMVoCZGi1ZqK
*/