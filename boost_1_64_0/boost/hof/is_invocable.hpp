/*=============================================================================
    Copyright (c) 2014 Paul Fultz II
    is_invocable.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_HOF_GUARD_IS_CALLABLE_H
#define BOOST_HOF_GUARD_IS_CALLABLE_H

/// is_invocable
/// ===========
/// 
/// Description
/// -----------
/// 
/// The `is_invocable` metafunction checks if the function is callable with
/// certain parameters.
/// 
/// Requirements
/// ------------
/// 
/// F must be:
/// 
/// * [Invocable](Invocable)
/// 
/// Synopsis
/// --------
/// 
///     template<class F, class... Ts>
///     struct is_invocable;
/// 
/// Example
/// -------
/// 
///     #include <boost/hof.hpp>
///     using namespace boost::hof;
/// 
///     struct is_invocable_class
///     {
///         void operator()(int) const
///         {
///         }
///     };
///     static_assert(is_invocable<is_invocable_class, int>(), "Not callable");
/// 
///     int main() {}
/// 


#include <boost/hof/detail/can_be_called.hpp>
#include <boost/hof/apply.hpp>

namespace boost { namespace hof {

template<class F, class... Ts>
struct is_invocable 
: detail::can_be_called<detail::apply_f, F, Ts...>
{};

template<class F, class... Ts, class... Us>
struct is_invocable<F(Ts...), Us...>
{
    static_assert(!std::is_same<F, F>::value, 
        "The is_invocable<F(Args...)> form is not supported because it is problematic."
        "Please use is_invocable<F, Args...> instead."
    );
};

}} // namespace boost::hof

#endif

/* is_invocable.hpp
vQFd4KjFuRh2TB4YI89WIHX/zdAeVZ64DOPyN0Vt/rPZqZFWZn+A9H8zQZLDxwRzXcZWN+oi+b0QWCiQEN+bAbkuwzqyoZpi12yayi2fXb7rv+3XtQjIK9F9uDpZXkP8or9xYXEYzroqucX9V6N9xZkmq6GWN7Gx9W6ROUeJeJ4kollssQFDD9iIpSIuzTJH41bWB2CpofOXWtyLylaT/gq4zp2qNlQX0I2OPPHFRcrDewlWiuaFVgukvj1ii+lfUi+unajKngBO0k+cKmik+NYSQ1jDJ8IzVUGZDUuJKvWJ8yoUg3XpcZe/4/667DWJ7WfSV6Hdbsi7SgEIdZad7kfLj3EenIM0inMD2ZY8bm4j7fHjf23Up4s/5dy08VmbKh9u4xHvT0o+3Tb1/4JZ3Wn38C7zIgwBbwTVlpctLllkNPhmtPB5HT7yddBxByury+N2qaFdQAcSf/CK1ogRRgGkKFoMzOdbo+inEz3soPau9UGokjbpsPTSjwQQ6kZIfkc3H/tBXcNIuHfbWPQ4Y/3GmGer1+Vy+b7P+5zLa0w2/9IO/3IGyB+I1vgvkH/XRqdDCem4uBwX7uVdLINc0ZNwRCKDQodyEXC5DFgDTcBr5N+gtkOybe47w7g293F1QoHvOV2ut/D8Ds+P8Dz/d/7i9L1bHB6Zhr7v11g2AmJkdLkbi5q9dD+Wuwo7pJfRgH8BfZ60e0mUl0S7OiqOIvppb4B8iCPdS5/pCVvhkU2OyMzcsDW1E9PvXxW8lnHHltegOA3z1YhMH+5Q4Yn5wz8wKv1+5W5qDuWbeH/7DP1MCiJZgNAMS+BkQz7XD2MwhPh+Mc+8x9YPSxyiBF/n+9VeCp08lhXNiNPmxJUk/z40wxX8NcyV6nMcYTSSKKjCxMH1s1ghUcN06TfKDH3Xp7kTmNQ/57tTK2nKO10wMF390/MXaG/Yx9Zz/HsS2swnMicb68VJ/tFyyFf4N2G8t51ujHdXZpzvXJXtHycjWTstPP2mEKt2QTaRdRUOhEvO07M0JvYiuPgkVmrzsyKFxr9NIeKdmQr334XQSX0U7r8R8FGsIUQGIGR+pqmRZS3kkk+c751Y385yh6GG0t51y6QEdN8jv8ZzTH4R5MI60s+fQjV/yFHc8/wpOIr/s0VSPAwjMVuTwgtFqSWlO08UXkMeRd5hY+X5+iZP6aHASK/47UBThUigP63OEYN43+SBbHiswfmFBK7OsfLLk/ltT84vT0xX+eX1nJ85/iGcyJV/Fvvv9OEFHL58UPpwtDsWbdzcDPQL4y/HLe2jpDnT5ZfPcc5DeT3Vj++cB4fizvkTk7gqkltviKgSzoCO+E8OMtUU+AmhMESdDI+ed+Ymf+XhNpL+372CWSy+SSfKYiFcKXGcPqW0OzDCK4YOiOsKyAZV3pkjW30KGv191eg9/ljceJ/bG8fBLkFXygkH9xj/wB+T4i8+RnyWH6b7N9CdNIzn8vtgb9uD/T+oWm3JM9oy2KstA58e7ycbqvD1p3bxsYvUSq+fQ5Nu1kIcMZbPUEeMxXzU8WYZSWhP7MfllQI5B/zTt2dQOaQpbDlbj8meofgDz+tZ6L5lXmT0wXSV0VRjvfChRW/j7H6XHc9ubEJ2w2JTqsTT01VuP6FDRRtf+jGPFzugvyzAt5DqxK/dshU6qA1mH9UGn+WMoeefup95zplSviePWjLfF5kVC73xSX3oUNb6XpGrY9GCu9+GLdkwWpr0XIReiEVHGwpoZvZmzMxHvn0PRR2RRgeuhQdrpMWWwjOxELhFcUn8xGus1mqGVGhbJel02fgklcFuMv/GtwlPgxgIUX1jYQlxY3bEvjlS/MNtWJyiOZHqQ94=
*/