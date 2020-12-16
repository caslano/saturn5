//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2017-2017. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/container for documentation.
//
//////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_CONTAINER_DETAIL_IS_CONTAINER_HPP
#define BOOST_CONTAINER_DETAIL_IS_CONTAINER_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif

#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

//empty
#define BOOST_INTRUSIVE_HAS_MEMBER_FUNCTION_CALLABLE_WITH_FUNCNAME empty
#define BOOST_INTRUSIVE_HAS_MEMBER_FUNCTION_CALLABLE_WITH_NS_BEG namespace boost { namespace container { namespace is_container_detail {
#define BOOST_INTRUSIVE_HAS_MEMBER_FUNCTION_CALLABLE_WITH_NS_END   }}}
#define BOOST_INTRUSIVE_HAS_MEMBER_FUNCTION_CALLABLE_WITH_MIN 0
#define BOOST_INTRUSIVE_HAS_MEMBER_FUNCTION_CALLABLE_WITH_MAX 0
#include <boost/intrusive/detail/has_member_function_callable_with.hpp>

//size
#define BOOST_INTRUSIVE_HAS_MEMBER_FUNCTION_CALLABLE_WITH_FUNCNAME size
#define BOOST_INTRUSIVE_HAS_MEMBER_FUNCTION_CALLABLE_WITH_NS_BEG namespace boost { namespace container { namespace is_container_detail {
#define BOOST_INTRUSIVE_HAS_MEMBER_FUNCTION_CALLABLE_WITH_NS_END   }}}
#define BOOST_INTRUSIVE_HAS_MEMBER_FUNCTION_CALLABLE_WITH_MIN 0
#define BOOST_INTRUSIVE_HAS_MEMBER_FUNCTION_CALLABLE_WITH_MAX 0
#include <boost/intrusive/detail/has_member_function_callable_with.hpp>

namespace boost {
namespace container {
namespace dtl {

template <class Container>
struct is_container
{
   static const bool value =
      boost::container::is_container_detail::
         has_member_function_callable_with_size <const Container>::value &&
      boost::container::is_container_detail::
         has_member_function_callable_with_empty<const Container>::value;
};

template <>
struct is_container<void>
{
   static const bool value = false;
};


}  //namespace dtl {
}  //namespace container {
}  //namespace boost {

#endif   //#ifndef BOOST_CONTAINER_DETAIL_IS_CONTAINER_HPP

/* is_container.hpp
/v291E269z4+oOzmIvup6Hj5bn6Pg3+ASQbSPRizQXavbTC5YMdXh1yFRZHJmemWXF8Nq0WGv0f/ZpWaT/kEUwt2f81cBayBYOt3pklhGjJXZhlpHWJhWsFmfTLWgekE07xOU8LiyfxYDdKuj1bC9GSezGLlQcNhBjJvZheCMrvAjGS+zOacOXQJZibDd0S3qLKsZttG4bPDTobPnNs029nNm3eAKZL+uy7dpTWVHUu4wFRkXsyan/YLg2nIQpmdrZlyEZYorBlTvu8HWApZELMOO2YdhJkES/uyLQ2WSRbGrNn/NPGwHDJfZs+25/eDOcgimO3UvjgPUwyiawEzq+/pOJiajK85sefuczAdGV+zVd8tebAUsmBmx880D4CZhP3uPJROgmWSKZh1OzWyyHIEW7au2xBYPlkIM4/hjXrDFIPpnohZp8YDq8JUZOWYXXMzJsESyXgN/fJKDYAZyHhfbpf58R3MRObDbLrXtnswMxnPM3O492lYNpmcWe6gBnqYnYzX/tebWnNhkiHOcQf6lZoFU5AFMTtatV5JmJqM5zJcmjYcFk/Ge7a91pXXML1gs193SIelCrn82ULqgKULcT3WbLsIyyTjvf652NN+sByyAGbrJ5fygTkES4h68TNMNtTZzHHdj8GiyMKYTc39uQtMQ8Z79qbsgQuwRDJeQ4HtzlFYihDXwlyiJswkxC14P7oYzELmxSwooNQamJWsJLOqb6dWgOWRhTKrnrF0HEw2zPncVLf1WQ9TkfFex1z8/BCmIwth1ibOzQbTk/EayleOWw5LJeO1j6/QqwnMjFwQl//7JZiNLNTpWvchD+YgC2cW9nz1S5h8uLN5DozuBVMJplqYrILpyHh9P/fZkgbTk/kxGzTnkRcslcyb2eSEk9EwE5kvs1VfV66AWch4z7otfLYRlj1cuE702vsOlkPmzyx6xfLrMIcQ1/2HzxEwyQjn82/WpqRcmIKM125v0n8ITC3EzV9ypxVMRxbALKJWNwcsiYznMuJLlZawFDLezysfvu6DGYX91rcotQBmFqyYsXpDmJWMz8GrVbvTMJtgd1f/+glmF2pIbdj7KSyfjM/v4rzZj2FyvbP1cNk2CaYkc2dWrdbbTTA1WSizawm5CbB4wX6TtVwMSyFTMMuqMPxvmEmwTcnHK8IyhTUHdrzdA5YjmEsJ/a+wfGHNUws3HoEpRjrbuhuyUTA1WRCzmlO3zofFk4Uz6/PZwweWQhbFbEXbU69h6WRhzApm98qAWckimV2/Xu8aLI+sJLOfv1Z9BZMnO9vh7S7XYWqyEGa757z8Aosn4/XlHCj1DpYixO2xr50LMwn7tZvUZwLMSlaG2f+WuPwFyyPj9S2svqQfTD7K2dr0PaSFqcn4bD/aZllg8WQ8z945QQ5YCpkHs6sxRikslcyb2dI9e3fDTGRyZk13jbkEs5D5Mitfs89JWLZg2xadT4HZyQKYvQ3e1gCWT+bOLMoecA0mG+18nGX8Js2GKck8mY3aWnwpTE3GZ5SypmQGLJEsjNnhcS1GF1oViYEMzxZ2abKka43RFQttlCST2T1pkqSK8desQhsucZDhueO+tIqkVOOHrwstQaIc8589IAuvtv1QodWQJJKh9lzpcEl786pHMP2/cTAv/0qlCm2sxMzsoVQv6XcFv8OtKrGT4d3oI2kNycCmK87A5GMpjtm7j/vnF9oYiZYM9T2WVpXcW/shCDUYyGySwufiPKphSPxr3yIbV/RO57sFqm+cg2WS+THL1WysCjtPhvcF3yx8Rrk02FUyV2at4ywjYbcEOy25+QGWK1gvzcsNMAeZnOVy06GuD5OlONuudkfHwqLI/Jnde7E=
*/