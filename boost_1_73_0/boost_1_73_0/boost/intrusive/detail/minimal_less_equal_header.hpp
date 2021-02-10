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
EG13Yr/aDpmdK0HcbFCtLTIjhiPr5wY9RPVThga9BX6iN7vn3bNfvkDDdJ1zxitp0SvVlfphrk6c1znxOqNu0yZzGjAZ5dDWj9oLUalOgdFvx97au05P6jDSI5IjFUQSqlVECwSuREVuU2ZHkC6MQgluwPeAIJQglCBUyoi9cV0hxe80AaIkiMvHYcm+SI2/yF38UaAw2FrphA7GaAdlxGSCi/L2jkCoQKhAKAoRNq6y3PlQHlYe2jP85Iw8li4WmVFV8EgZllsqQMY6JCdfCBwKHAocZgv6kYsLN9ZH3x6WCoUFeCUbBsPvTo+HiOtdvl754DHSSWlZGe+qQ3hJUFRQVFAUjxfRKy0/eEQjRnn5Wri/WMm7LBhLy9dmar6ues5G0EAMZvVLMw0DN83BsQSBY4uIPzgtNNpHInx/GfvX0T0BV8egez+eVNu6c1Kpn5JK/eOg0t4gSwMdDUQGSRVXl9eC39MicDLHylUNbCp6lMouziiPUqGSOeLj1qjECj3kHVMWWqDVqez3QkVIwhyNy6y7IAl6xI0pnUgZf1Feh1XG5gwEQikSQaYRbpkIQxflJBVaqQivhwTFyqO7oFjOET2mqOGNMe0QHkhDOJRiDiy0YZZzJEsuGciQSjoY/SGwVR7dBbbyCtpb
*/