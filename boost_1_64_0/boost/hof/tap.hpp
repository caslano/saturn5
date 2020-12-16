/*=============================================================================
    Copyright (c) 2014 Paul Fultz II
    tap.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_HOF_GUARD_FUNCTION_TAP_H
#define BOOST_HOF_GUARD_FUNCTION_TAP_H

/// tap
/// ===
/// 
/// Description
/// -----------
/// 
/// The `tap` function invokes a function on the first argument passed in and
/// then returns the first argument. This is useful in a chain of pipable
/// function to perform operations on intermediate results. As a result, this
/// function is [`pipable`](/include/boost/hof/pipable).
/// 
/// Synopsis
/// --------
/// 
///     template<class T, class F>
///     pipable constexpr T tap(T&& x, const F& f);
/// 
/// Requirements
/// ------------
/// 
/// F must be:
/// 
/// * [UnaryInvocable](UnaryInvocable)
/// 
/// Example
/// -------
/// 
///     #include <boost/hof.hpp>
///     #include <cassert>
///     #include <iostream>
///     using namespace boost::hof;
/// 
///     struct sum_f
///     {
///         template<class T, class U>
///         T operator()(T x, U y) const
///         {
///             return x+y;
///         }
///     };
/// 
///     const pipable_adaptor<sum_f> sum = {};
///     int main() {
///         // Prints 3
///         int r = 1 | sum(2) | tap([](int i) { std::cout << i; }) | sum(2);
///         assert(r == 5);
///     }
/// 

#include <boost/hof/pipable.hpp>
#include <boost/hof/apply.hpp>
#include <boost/hof/detail/static_const_var.hpp>

namespace boost { namespace hof { namespace detail {

struct tap_f
{
    template<class T, class F>
    constexpr T operator()(T&& x, const F& f) const
    BOOST_HOF_RETURNS_DEDUCE_NOEXCEPT((boost::hof::apply(f, x), BOOST_HOF_FORWARD(T)(x)))
    {
        return boost::hof::apply(f, x), BOOST_HOF_FORWARD(T)(x);
    }
};

}

BOOST_HOF_DECLARE_STATIC_VAR(tap, pipable_adaptor<detail::tap_f>);


}} // namespace boost::hof

#endif

/* tap.hpp
9c8uhokCqhXPkm22sgp9m7GsXfpr+mRJP9aRjwqxNd9IwktPXJ3uJslr5N+A/Cx4jfzP2FBEw4aY/JSXRHjRhsetYS4sMJwb0L76kX/5NmXzAvlpDvELJPmkLBNJ3ioJinnUwWcIa5nFviMfwOPCeRjuwLXwE3ixTzyPgZRo1SjIKkyShxkadIFHzNlGL3aaiZa8uqk8/fBndi0Iz9c5yc6VXft8STd3nU0M5ytBlkSLcZWCFAxVAq4N2TSqC8is1zcPR+1EXcUE2UG9T14Iy2BzfOLxNDJR8/oAQt5ImTNbrML13SNefpeKdbO3TeRAWaPq5suyruNm7Ooktb0gZDQSG5U1wCbioUY8/jbIBCT5Kt51A5kU3XpwypgWbhOnniTP98DTKL1e7MYiM3xblotbtiM/WBv6VmoP4s+HmnnXZHU7OJNNmJWxE7V1SXZar/PttbDlBFXPAUYNlJ1nJkMj75yy3cO43SWy3c2S9E0eJQ/PTjIGTqO1zfXdsQE1WcRcLqKtY7RD//t2Mdr7aS7okwD/e8e/lzUnwP+sBPuBSXHv2s1+Jf/d9Yj+ISi+KSG9uOTMo8lHIj6B3rj8JEVvVPFRetrbZybS0/xiZl/DRVZfLYOQsp0TmOHzS8nwsXVQs96kDCrApHnfTBM8uuQOU/gi6T/3olWuvTo+gy3UveRSwnhDdfZiULgye2KGm9O3X383ydMy1izyOpfSjZ4qi/Sv7M9Flra7vNPqrADqUzsaV7zgIO2SfhaIEV6YqXwlTiEHi5DHIq4NTrC732g17BO8BvGruVZOZthvdfc2SXcHAQWRVV/XLmt6//qnRjyCBarDUQ7m7xVLdP7ulPM3PJXnj64F0j+Pn4TPanvFkWJAh0jqSatAw5HChjQzuqhJmyJPat8KTBqdV2nFbmN8q63FHhrfNXTeJI7v6dJv+5UdlaXxQh7gGiF6xRI0DCtDxhgXva7GeDMYVt0tnNJbIR7raVpeqQYA+z5t5K+gNS8WpEXpoQ3Z6QgCn/qJ7P54yN/m15/iJ7J4k0Gnn8jqaQ7fAJyKXkDqph7cWFagcIT2OVw3fYMskezGWUPT3Gy4UrsLq1f7I37EX9v4tkPH8haqYk/zJvzFpFqBn5atMQHPUsA63IMbQWisBhrGe0H88qvWSMtfY4PfpuAQBf86Nng7BV9BwTdpdGlERA6bq37zG9WUhiCGlqtkcX/tI2RppuFGObrm0GGi0x4c6lo+IsmDHxv9WOnHIqmaJLvFRXtEyYdUZmZMWZYJKCsZZYXa3JAJkmhMNsZ2mWv5RRYUInlrhAFWaztRcV2yR+z+oDUCUl9/rMPGK236V1L/wTa8YXVwXyNEI3NfH4v1WGmtRECb/vyaZtuu3+nPh95P2nV/6EBqIIPSjEV84wIrUuyZ8Rui6M4Ip5aFDjjm3UQIDLWQqF2xrazFBpYDvxvtkGGjEIbBolRGF88Glk+tpZwFHs2NVOK9Peg2js7TCBEKkEEi9nu96yQTOLwKbt0U8gQo9mEFQTJBv5kXG2i/JTgNbnyWFmMTArOs7B6ZBdhOMWPofnnaBWnuK/FtwHcUvn/BdzK+v8L3Q3ybh6S5X/wf/rBElJ4aasMOIgsmPtzR7cOhMZuFIebz7dEuURcF8FSkDVYRP0+IGK8iboiPYGaOQ6uX0eliKkc7E6IbVPTQI0bfrKKzEqJxzGq3IdInUhCj9U36MZw5AKRCIao7U/1jCtJnGduqP1FGPEQvoR/aVike7V6ugtxUdI7LiD0UZBFruTprxN0c7yCyHPZSF5Qgt1O19hTH38DxzsY5NqImvUMMK4T228SYN4z1TqLRWq1Ga6wsLa5Db3OHBiE=
*/