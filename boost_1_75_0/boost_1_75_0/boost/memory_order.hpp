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
8FBCqsPQjuikzt7hfaBZUWKaWYRXxzlNEG5tq9YlPcQ5nehvV234geWtMJJedvzRf1EPeAu8+4G98LUWvsHivdUHXtVEce9PVzNRfPGwaqKIlja8L5t74WVYZXh5Gie83wrcLsy7EJiaZLd4U2UUDL0n6bE2M8L0vge5KVep5ZxfnAZuDOzcBFPOm9ODJ5jel8HJlSZFhw+CiVVA9ESaEk3teYAln5X2o9k+uG1SXecsiG+U6tE1NMdA/A2PRps7D3bu5w8SaYf0tXQAkwtrLYQeteVJ9z8O0yqugx53fgXzcH++cIhzioKRsVJ2EtXe+j1O27gORlR6zrV/IHJLk9RcLOkoC3TbfynGE16vPmEHcMN4nb0dfjhhKK4T6sGXlB6eLRWYgUIsea4lCvfPLsNFrG3mB0a6lo39FrqsIgLGZxT4YAlZcR24Un2zLFrNtt/yx3V2XRr3T4+hDiQb4JYWJScC1zPbRCh50Sg8VLKbDQdat+Gp3JF9sP4BGMAgL8vvbMq/tY4e+sDaH9MldACs/f9ktL4Oq13rCcQuJxxalItrQfZfdBShaX/BlQnXW2c6RkHS1L/QYcQaVgzGGx7Qoz5YBe33xRzhakKLRWOcayG7NzDVflpQiqbbr4NkTrABNJQVt6c0s1h8NKlnWiGScmtXzFlYX0YWiwbXdJotdCreOGgF7lyLnNfQ+ingtgnP0fhT4SANmmzT
*/