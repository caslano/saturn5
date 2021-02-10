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
93HWbjld92dV7C7RVMTNnDRGvtYDX3hra5wZ3bm6rY+oRaZT+oFZ27cBW04ixxGdYef6z8gGnXRwcLd80HITC+Ly1soNl7eQG32E9JD9/jtzE7CPO+tZC2X1pOi6JSl6TAzTp14sbpw6slIiBd8ObdmQKTgERid0jYNPOcQsM1Al5E2zrus/POsafFpp1/WD0q7rPyftGnxyIn1w3oVAAugIPFpDfIBUKfOanF9Q1gUANwmSKqYhHqIBd8t5POZLiJlYcATfJ/B1A0ikPrsNT6CPWyXFX02VcqMqnaorUr2QB58h/4oV2P/lXKxi3JlIxzflel+UyOVStfOv1RxKTaoscFNFkDJsibNGWTaYkjUDs4xE0DmhJIPeyXR2iFaC1adHn9YkE7EoZavI7xYJqm+NSGSPjhUPZJrQri1KBmRFOQFBVu8vi3Mo/LQESYKRgrRYd7nTjHWL+CaPimp/0CxjqrlWyCRUXdUV8/dQWkD+8UlJWspHitqWQIVHiz0pbzvftARf5DzPU0yXUSpYJNHKLsg5OlHf4nr8wqM0BtPIIbPh9WqQ+pVNWy5XMHqF0LZuBntd5EMWpmeHKR4yxV0eL9O8WNfmO5F6ZxC0Y9z2Ek7P8JBDkC6XqyQKfAQicJz9adlIKU1pJzWZ
*/