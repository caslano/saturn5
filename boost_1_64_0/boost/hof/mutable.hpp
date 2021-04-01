/*=============================================================================
    Copyright (c) 2014 Paul Fultz II
    mutable.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_HOF_GUARD_FUNCTION_MUTABLE_H
#define BOOST_HOF_GUARD_FUNCTION_MUTABLE_H

/// mutable
/// =======
/// 
/// Description
/// -----------
/// 
/// The `mutable` function adaptor allows using a non-const function object
/// inside of a const-function object. In Fit, all the function adaptors use
/// `const` call overloads, so if there is a function that has a non-const
/// call operator, it couldn't be used directly. So, `mutable_` allows the
/// function to be used inside of the call operator.
/// 
/// NOTE: This function should be used with caution since many functions are
/// copied, so relying on some internal shared state can be error-prone.
/// 
/// Synopsis
/// --------
/// 
///     template<class F>
///     mutable_adaptor<F> mutable_(F f)
/// 
/// Requirements
/// ------------
/// 
/// F must be:
/// 
/// * [MutableFunctionObject](MutableFunctionObject)
/// * MoveConstructible
/// 

#include <boost/hof/detail/result_of.hpp>
#include <boost/hof/detail/delegate.hpp>
#include <boost/hof/detail/move.hpp>
#include <boost/hof/detail/make.hpp>
#include <boost/hof/detail/static_const_var.hpp>

namespace boost { namespace hof {

template<class F>
struct mutable_adaptor
{
    mutable F f;

    BOOST_HOF_DELEGATE_CONSTRUCTOR(mutable_adaptor, F, f);

    BOOST_HOF_RETURNS_CLASS(mutable_adaptor);

    template<class... Ts>
    BOOST_HOF_SFINAE_RESULT(F, id_<Ts>...) 
    operator()(Ts&&... xs) const BOOST_HOF_SFINAE_RETURNS(BOOST_HOF_CONST_THIS->f(BOOST_HOF_FORWARD(Ts)(xs)...));
};

BOOST_HOF_DECLARE_STATIC_VAR(mutable_, detail::make<mutable_adaptor>);

}} // namespace boost::hof


#endif

/* mutable.hpp
P4UJgVsf6gi4Vz4y4PhPzmML94t44vCFzPvlrqM34aZZRXCqYizvfWcgaRA11OGb2jeQIx2sZO9mSWUKEh2F5XuSjf+XZ8ZSP8JxCOx397x7tYu97Qf54MD8FxeuQ/73+YbVG74cC/OwqVIVH2G7/Pa10jucrBOpXRlVMyrsOvMqeKZhtw1FOCizmSw+h0nrbWWUTP4wYG4rBI3CSCMMv/IkyL6MJewCX91cjCYPKOu8+lXNJVuPkLzowjGu2W/VBcsNznEArGKN3ygYl2Nl6H4SrpqaRr3YRQL5ZQax0NAT2OCWe0VEHz1AZV0sWyzAdApbCYyZ7aYzFBXxKBxKr0b7sbxjobwV95S6xSpm/h1sU93fqrfnDLXh6ZlACAPqAhVd+67+9saLkbQzps/e2yMhdnJi4DTHbOTqtRkm3W7VVdbQ2Ecx1wOazIOjBrJPj4LJIImS0MCdb70E1jcKxF2PAINGFV7rZW731blAzwsc5GIfTRsF+HwQsLhW48Zh/8nFnUHUUVr0oY3Be2kkzpZS/OsYw7FmTlp5zWZkD18jemswAWSisVLF+A==
*/