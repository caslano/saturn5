/*=============================================================================
    Copyright (c) 2014 Paul Fultz II
    remove_rvalue_reference.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_HOF_GUARD_FUNCTION_REMOVE_RVALUE_REFERENCE_H
#define BOOST_HOF_GUARD_FUNCTION_REMOVE_RVALUE_REFERENCE_H

namespace boost { namespace hof { namespace detail {

template<class T>
struct remove_rvalue_reference
{
    typedef T type;
};

template<class T>
struct remove_rvalue_reference<T&&>
: remove_rvalue_reference<T>
{};

}}} // namespace boost::hof

#endif

/* remove_rvalue_reference.hpp
9QBCFKbqZOH07WUGNvhbsUrNJIe/R9tWt133M+drVWm70Ssig7WGkZaY75mRwcnnm3qdQVJBPusMmAoCbPIbItmtvURa23GusGuky/7/Tmntcb711/ZG77ZzALrnuJySxTyL4B2u/wJChONejLgrhmY/CNzXFgxWfh5oO3DrrIwOLHZe38vrwHf+Wgfcx2DKyLSJxWXs37BR6MA8nceNgoZlRnPGkJ/lp875AS0qdQU7/jIt
*/