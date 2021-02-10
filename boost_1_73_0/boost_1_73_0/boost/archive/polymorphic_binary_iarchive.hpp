#ifndef BOOST_ARCHIVE_POLYMORPHIC_BINARY_IARCHIVE_HPP
#define BOOST_ARCHIVE_POLYMORPHIC_BINARY_IARCHIVE_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// polymorphic_binary_iarchive.hpp

// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com .
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

#include <boost/config.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/detail/polymorphic_iarchive_route.hpp>

#ifdef BOOST_MSVC
#  pragma warning(push)
#  pragma warning(disable : 4511 4512)
#endif

namespace boost {
namespace archive {

class BOOST_SYMBOL_VISIBLE polymorphic_binary_iarchive :
    public detail::polymorphic_iarchive_route<binary_iarchive>
{
public:
    polymorphic_binary_iarchive(std::istream & is, unsigned int flags = 0) :
        detail::polymorphic_iarchive_route<binary_iarchive>(is, flags)
    {}
    ~polymorphic_binary_iarchive(){}
};

} // namespace archive
} // namespace boost

#ifdef BOOST_MSVC
#pragma warning(pop)
#endif

// required by export
BOOST_SERIALIZATION_REGISTER_ARCHIVE(
    boost::archive::polymorphic_binary_iarchive
)

#endif // BOOST_ARCHIVE_POLYMORPHIC_BINARY_IARCHIVE_HPP


/* polymorphic_binary_iarchive.hpp
kHDZzUAREzKA3qFNmn7oVkKU6Bl1qrighXKlAkNh7Iy6GvgcOixVMzCXl61H23lz7DM6ZXPWgI4gakOEVEo53jMEdWS5UUS4CP2XbQ0nqZJjL5TCKb8tTF9RDtywDwmXxKOHpIcKRTSfhwXIaEfCZ0Mu0YIc92FDhQtFI/2dMny3qwOlsVBLD4Zai0Eu6DmJln3UPAeH4nFy/yD2KSwPuPH1qEA6mqDuPuxWtsGF8Xnbg7E4fisi/3XCn1a5/ifyCdvAFDby6TXcQXyGGUi960RLZgSPXNuqalCcVVnWmwG51EUkl5PcoiYbzlFfzjn6eNvR4djUUW2nVkml0Ix0QdOicwQVZgy7M+5uHuuhSFs/OjXrnoD8kFc5fFupF2Y4ahItRQq0P5VPM9cUDnyNcLNq/wAGyDlXNUn1epsa+cCDKBL4GdEbQ+IuEo7iyOtSbP2cD3mGLzUpc1R5raJK13DbNLXSJW5+wTOu6heRdgvb9yJsZ5+L0+0ZdD+q036DusUM3LAzbzDs84zHmnBX7kbBDpaSor+5m3Lk91jS+VszQpLxDmrONRhubfGcg4e3S5z2RYanjLATjzBux1+KL3k1uR+zNKY+i7sHy10o5YoojsDKlZZKqC+UyQ2pLn6S8jmNWIXw55e8qit4
*/