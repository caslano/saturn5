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
/3fcWy3R/2pUgAZdDJdawCuZ03Hq5KPgX8etMnrUhlmsNEToS5IizU2ZuL/sGWyX0Emw39qi+K4GSGNOYaFqwHKGLFgB9zG2wxzjXTXbnapRANBjKu+l8GINl9N5G2hiiKBnS7j84v/hl1fyJoHnvYJirg8ID5Bzhu6MQUVMcgIUCbS94vFeRe3uVSkxPelbcQpWlINSezHuk68sRuloWEnBqWZ1RoM3kQofg/b+hsPisaBEw6K/Ybk1Ft6PE71xDcynRAI0tTZY8Sdcv5W8xb6xhToZvAtP5qXA3qHXaOfimswT5WiHRKQGH5yYwaB5Zd0IymhUUtCfqOg8+YLUy0uvFsvhDVf2Qym8DbxgddmDwv8YJI9yXpFicw8dZbXCRl4pQL0A8KKwURefUURYvBbAdAvDifGT/JxfDoldTm+X/iTrCYX3vaGEK/+fi0rHANivHV/kjx9Y9WZ24FOI0qh04SSz6BkjBeXKFq0M/wdBz0A2s9HioEI7MBq8NOX8iHo8ewF/J8JhWSoRPiv0RFh1XPxMbf21PtUvi2hJYv14S5aRy9TUsEbdjg==
*/