/////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga  2014-2015
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/intrusive for documentation.
//
/////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_INTRUSIVE_DETAIL_MINIMAL_LESS_EQUAL_HEADER_HPP
#define BOOST_INTRUSIVE_DETAIL_MINIMAL_LESS_EQUAL_HEADER_HPP
#
#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif
#
#//Try to avoid including <functional>, as it's quite big in C++11
#if defined(BOOST_GNU_STDLIB)
#  include <bits/stl_function.h>
#else
#  include <functional>    //Fallback
#endif
#
#endif //BOOST_INTRUSIVE_DETAIL_MINIMAL_LESS_EQUAL_HEADER_HPP

/* minimal_less_equal_header.hpp
wuuqEzzzCWLhJgVm7sp6b87i+nrid5biFemKGSgShgSTyQc5HQIl7YW6hfDfZPiiBB779yW0wd87BpW4w4alBUU80ci+mLCAf+Irwy08SsvazF3PjPZX4JLHmbnmbIh67CR5n1qbeMsK38kzBndBkXJNFkfr5IIXITDAqfCzKw+6cZGdvCNpyNv828wyKCmj7opNxwg0byGbd+bcF0dy7iOtv39P0WXjRu9WJYJqlqL76C65a6RX2P0kp4U8akexX+CblhLQi0FqFvCo6pkk5OHHTSXajCl291AAD29LzLr5bzzO90XgP/6n637mr8/nCE+1LkxXnB1yDlV/JGo/xUvGxoLBkuY/poD5VXM9RkWcoBrCzgXTvmbyORMbBGo/sQIFPdo2jSCcNa61GN0PfXPAr43l3j9lqnG38wtwrHviJL/usOw/+LuLVsQeVD9UBeV0/HFCLIdeSvK6YWu72nsd0813AjiqO1Jy5CwCc8qrfK3azq/0jCwqT5JopFY31mqIZPkNDR0c/WP92r4HppZrEJoqsITJGH2uSKkgO2tQrUkGa6rSrPmEhQ==
*/