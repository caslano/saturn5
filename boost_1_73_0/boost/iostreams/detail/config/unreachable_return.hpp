// (C) Copyright 2010 Daniel James
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

#ifndef BOOST_IOSTREAMS_DETAIL_UNREACHABLE_RETURN_HPP_INCLUDED
#define BOOST_IOSTREAMS_DETAIL_UNREACHABLE_RETURN_HPP_INCLUDED

#if defined(_MSC_VER)
# pragma once
#endif              

#include <boost/config.hpp>

#if defined(_MSC_VER) || defined(__GNUC__)
#define BOOST_IOSTREAMS_UNREACHABLE_RETURN(x) \
    BOOST_UNREACHABLE_RETURN(x)
#else
#define BOOST_IOSTREAMS_UNREACHABLE_RETURN(x) \
    return x;
#endif

#endif

/* unreachable_return.hpp
zlsUmDt/QV1iRuL6T86eTwrz8Pew/dPCDPrb6n4N083FwUG0Gs4B6y/wqFaN49BKxRebeuo9ynu+B9Va8ERc/eXT7zNW6xfvEsOcq8OpbpjKor/tfY1uWw7Qfwli7G+wSrGo6oBJcii1xOq+fURcA9jFnzWbLyda+yR+neBX27lO/BA+FTb5cCZ+3TIYE0jVd/Uyndiec1Ex+kmxEZxBOz9P3NRQjmGps/V9BjVrfYZZex/H
*/