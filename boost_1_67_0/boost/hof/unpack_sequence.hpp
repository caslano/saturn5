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