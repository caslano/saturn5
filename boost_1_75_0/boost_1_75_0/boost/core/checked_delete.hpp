#ifndef BOOST_CORE_CHECKED_DELETE_HPP
#define BOOST_CORE_CHECKED_DELETE_HPP

// MS compatible compilers support #pragma once

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

#include <boost/config.hpp>

//
//  boost/checked_delete.hpp
//
//  Copyright (c) 2002, 2003 Peter Dimov
//  Copyright (c) 2003 Daniel Frey
//  Copyright (c) 2003 Howard Hinnant
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
//  See http://www.boost.org/libs/core/doc/html/core/checked_delete.html for documentation.
//

namespace boost
{

// verify that types are complete for increased safety

template<class T> inline void checked_delete(T * x) BOOST_NOEXCEPT
{
    // intentionally complex - simplification causes regressions
    typedef char type_must_be_complete[ sizeof(T)? 1: -1 ];
    (void) sizeof(type_must_be_complete);
    delete x;
}

template<class T> inline void checked_array_delete(T * x) BOOST_NOEXCEPT
{
    typedef char type_must_be_complete[ sizeof(T)? 1: -1 ];
    (void) sizeof(type_must_be_complete);
    delete [] x;
}

template<class T> struct checked_deleter
{
    typedef void result_type;
    typedef T * argument_type;

    void operator()(T * x) const BOOST_NOEXCEPT
    {
        // boost:: disables ADL
        boost::checked_delete(x);
    }
};

template<class T> struct checked_array_deleter
{
    typedef void result_type;
    typedef T * argument_type;

    void operator()(T * x) const BOOST_NOEXCEPT
    {
        boost::checked_array_delete(x);
    }
};

} // namespace boost

#endif  // #ifndef BOOST_CORE_CHECKED_DELETE_HPP

/* checked_delete.hpp
r4fnR73Sfk3wlNinUw/y8CXRU0asWXwv+fXeEb8aXwtT4N413OPQwf3HbX+M/DVyu2q/ZFObb3/E/Wy4jiFNWuWxISgk6fmLd6d1XnHSHfe4YT6fTXn/wMKJuxI2uhnKqjf7LcZ9bziu/eC6fsvTxz9KWdo23q5xUAjFvXAYP+Tyzrltn3KMXRC84NZP3d1/xv1xCG83o9q0zD05+RXVjmPSnhWluGcO58ED7yV6KseHjz98arPD7cIBfc7z8XMjw0vL79jHbtU+l9upasqvuLcO57Tt7p8rvvXPrZGv+w2Y1/G78j243w7j//PeT2fJdxNT9hz4dODgpU9/gHPmuHaSqli8Zom+c8p+u6xJPQxTXsM9eWnIf1jkh+ePvxa70PPb3+231L6D+/RwjrZuqU/7I9KhsS9t759399jVaNy3h+uHN1163lBPvDfu2TNqea+Iwxtx/x72yTMf7Z+0b8rG1NUuPnc6zO1wDuefcB3i2DNflO8f+OOETV+9fCEyvTwQ9/nh2tor2yZ8PLTi9cjtw2TDds32H437/nC+/8PcLY7lxz+NXTvjdCSdH1KCewFx3rntN8+P2T3ENO7F5Xs6Jh5fOQL3B+Jc2Mayn5/+bcjACTsu7O+6b2vNXlzbxDUWxZ03+j4XE5Kwptf7Yz73fzkbfQ1c59028LeDw9LeS3hhxNYXXps+ZBHOA+C0yu9H61wPzV81bvGi
*/