/*=============================================================================
    Copyright (c) 2016 Paul Fultz II
    unpack_sequence.hpp
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_HOF_GUARD_UNPACK_SEQUENCE_HPP
#define BOOST_HOF_GUARD_UNPACK_SEQUENCE_HPP

/// unpack_sequence
/// ===============
/// 
/// How to unpack a sequence can be defined by specializing `unpack_sequence`.
/// By default, `std::tuple` is already specialized. To implement this, one
/// needs to provide a static `apply` function which will unpack the sequence
/// to the parameters of the function.
/// 
/// Synopsis
/// --------
/// 
///     template<class Sequence, class=void>
///     struct unpack_sequence;
/// 
/// Example
/// -------
/// 
///     #include <boost/hof.hpp>
///     #include <cassert>
/// 
///     struct my_sequence
///     {
///         int x;
///         int y;
///     };
///     
///     namespace boost { namespace hof {
///         template<>
///         struct unpack_sequence<my_sequence>
///         {
///             template<class F, class Sequence>
///             constexpr static auto apply(F&& f, Sequence&& s) BOOST_HOF_RETURNS
///             (
///                 f(s.x, s.y)
///             );
///         };
///     }} // namespace boost::hof
/// 
///     int main() {
///     }
/// 
/// See Also
/// --------
/// 
/// * [unpack](unpack)
/// * [is_unpackable](is_unpackable)
/// 

#include <boost/hof/config.hpp>

namespace boost { namespace hof {

template<class Sequence, class=void>
struct unpack_sequence
{
    typedef void not_unpackable;
};

}} // namespace boost::hof

#endif

/* unpack_sequence.hpp
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
*/