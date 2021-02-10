//  boost/memory_order.hpp
//
//  Defines enum boost::memory_order per the C++0x working draft
//
//  Copyright (c) 2008, 2009 Peter Dimov
//  Copyright (c) 2018 Andrey Semashev
//
//  Distributed under the Boost Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MEMORY_ORDER_HPP_INCLUDED
#define BOOST_MEMORY_ORDER_HPP_INCLUDED

#include <boost/config.hpp>

#if defined(BOOST_HAS_PRAGMA_ONCE)
# pragma once
#endif

namespace boost
{

//
// Enum values are chosen so that code that needs to insert
// a trailing fence for acquire semantics can use a single
// test such as:
//
// if( mo & memory_order_acquire ) { ...fence... }
//
// For leading fences one can use:
//
// if( mo & memory_order_release ) { ...fence... }
//
// Architectures such as Alpha that need a fence on consume
// can use:
//
// if( mo & ( memory_order_acquire | memory_order_consume ) ) { ...fence... }
//
// The values are also in the order of increasing "strength"
// of the fences so that success/failure orders can be checked
// efficiently in compare_exchange methods.
//

#if !defined(BOOST_NO_CXX11_SCOPED_ENUMS)

enum class memory_order : unsigned int
{
    relaxed = 0,
    consume = 1,
    acquire = 2,
    release = 4,
    acq_rel = 6, // acquire | release
    seq_cst = 14 // acq_rel | 8
};

BOOST_INLINE_VARIABLE BOOST_CONSTEXPR_OR_CONST memory_order memory_order_relaxed = memory_order::relaxed;
BOOST_INLINE_VARIABLE BOOST_CONSTEXPR_OR_CONST memory_order memory_order_consume = memory_order::consume;
BOOST_INLINE_VARIABLE BOOST_CONSTEXPR_OR_CONST memory_order memory_order_acquire = memory_order::acquire;
BOOST_INLINE_VARIABLE BOOST_CONSTEXPR_OR_CONST memory_order memory_order_release = memory_order::release;
BOOST_INLINE_VARIABLE BOOST_CONSTEXPR_OR_CONST memory_order memory_order_acq_rel = memory_order::acq_rel;
BOOST_INLINE_VARIABLE BOOST_CONSTEXPR_OR_CONST memory_order memory_order_seq_cst = memory_order::seq_cst;

#undef BOOST_MEMORY_ORDER_INLINE_VARIABLE

#else // !defined(BOOST_NO_CXX11_SCOPED_ENUMS)

enum memory_order
{
    memory_order_relaxed = 0,
    memory_order_consume = 1,
    memory_order_acquire = 2,
    memory_order_release = 4,
    memory_order_acq_rel = 6, // acquire | release
    memory_order_seq_cst = 14 // acq_rel | 8
};

#endif // !defined(BOOST_NO_CXX11_SCOPED_ENUMS)

} // namespace boost

#endif // #ifndef BOOST_MEMORY_ORDER_HPP_INCLUDED

/* memory_order.hpp
j6d8CeUsX6YxzKJ7DYWe6OS+cbGIigryKVqj7zgpK/S3rJI8O8DQGipdzEt0YYJHaZlDdB8laXSLYaIKZlW1KP/s9SbLIsXMe3E+KXuTl6EfzKr5ahRjzGAePUG+qKDKYVnqLhi9LszzOJmaO1KBwsXyNk3KWfc1FQyUxb28gFKnKbpCs0SXTcoawhUzXaMFC8w2qcytzLPSRHqY5fM1RaQQnUyXRYZhkALUiXMkuAvLLNZFrVsP+iXCis2a2g1T8pprDHmGmcAuC8EJd+E2KpOyC1eOPBcjCVcsCJgnxyAGwLwx+rpwPBvnO8FIBejHRaFLjFxAMl+kiY7rgL/u2kmmHU9IGHnOj/0dAPx55Xhfj8wzIMFV55xdcuU6fduFw7Z0ZPUpcSisCy7fIhhEeZzbBvVC0hclPuPIUyg9NuTwpW1ybQzWpbYrfO615cx1hcXUeSsEC3ymHI9LArPdgeURcpRKF+XvU3I8Kcc+DwkTRxD6wzorCuBDEYwJAPO0+4R7lNdjcAYKKePBRyrUiFa2bcAPhMXDkEjFv7IJ/ZDLf4Y+oR6eITeUgXPmMYpMU0Q1ay0LaSPRNIBFQbmSAa5YaloahDIZh8pnARtSRgYTrrsBCrnLLTI/A9ZL4wOQHrIBJZMbEpXOkG+w
*/