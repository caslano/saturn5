/*=============================================================================
    Copyright (c) 2015 Paul Fultz II
    apply_eval.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_HOF_GUARD_APPLY_EVAL_H
#define BOOST_HOF_GUARD_APPLY_EVAL_H

/// apply_eval
/// ==========
/// 
/// Description
/// -----------
/// 
/// The `apply_eval` function work like [`apply`](/include/boost/hof/apply), except it calls
/// [`eval`](/include/boost/hof/eval) on each of its arguments. Each [`eval`](/include/boost/hof/eval) call is
/// always ordered from left-to-right.
/// 
/// Synopsis
/// --------
/// 
///     template<class F, class... Ts>
///     constexpr auto apply_eval(F&& f, Ts&&... xs);
/// 
/// Semantics
/// ---------
/// 
///     assert(apply_eval(f)(xs...) == f(eval(xs)...));
/// 
/// Requirements
/// ------------
/// 
/// F must be:
/// 
/// * [ConstInvocable](ConstInvocable)
/// 
/// Ts must be:
/// 
/// * [EvaluatableFunctionObject](EvaluatableFunctionObject)
/// 
/// Example
/// -------
/// 
///     #include <boost/hof.hpp>
///     #include <cassert>
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
///     int main() {
///         assert(boost::hof::apply_eval(sum_f(), []{ return 1; }, []{ return 2; }) == 3);
///     }
/// 

#include <boost/hof/config.hpp>
#include <boost/hof/returns.hpp>
#include <boost/hof/detail/forward.hpp>
#include <boost/hof/detail/static_const_var.hpp>
#include <boost/hof/apply.hpp>
#include <boost/hof/eval.hpp>

#if BOOST_HOF_NO_ORDERED_BRACE_INIT
#include <boost/hof/pack.hpp>
#include <boost/hof/capture.hpp>
#endif

namespace boost { namespace hof {

namespace detail {

#if BOOST_HOF_NO_ORDERED_BRACE_INIT
template<class R, class F, class Pack>
constexpr R eval_ordered(const F& f, Pack&& p)
{
    return p(f);
}

template<class R, class F, class Pack, class T, class... Ts>
constexpr R eval_ordered(const F& f, Pack&& p, T&& x, Ts&&... xs)
{
    return boost::hof::detail::eval_ordered<R>(f, boost::hof::pack_join(BOOST_HOF_FORWARD(Pack)(p), boost::hof::pack_forward(boost::hof::eval(x))), BOOST_HOF_FORWARD(Ts)(xs)...);
}
#else
template<class R>
struct eval_helper
{
    R result;

    template<class F, class... Ts>
    constexpr eval_helper(const F& f, Ts&&... xs) : result(boost::hof::apply(f, BOOST_HOF_FORWARD(Ts)(xs)...))
    {}
};

template<>
struct eval_helper<void>
{
    int x;
    template<class F, class... Ts>
    constexpr eval_helper(const F& f, Ts&&... xs) : x((boost::hof::apply(f, BOOST_HOF_FORWARD(Ts)(xs)...), 0))
    {}
};
#endif

struct apply_eval_f
{
    template<class F, class... Ts, class R=decltype(
        boost::hof::apply(std::declval<const F&>(), boost::hof::eval(std::declval<Ts>())...)
    ),
    class=typename std::enable_if<(!std::is_void<R>::value)>::type 
    >
    constexpr R operator()(const F& f, Ts&&... xs) const BOOST_HOF_RETURNS_DEDUCE_NOEXCEPT(boost::hof::apply(f, boost::hof::eval(BOOST_HOF_FORWARD(Ts)(xs))...))
    {
        return
#if BOOST_HOF_NO_ORDERED_BRACE_INIT
        boost::hof::detail::eval_ordered<R>
            (f, boost::hof::pack(), BOOST_HOF_FORWARD(Ts)(xs)...);
#else
        boost::hof::detail::eval_helper<R>
            {f, boost::hof::eval(BOOST_HOF_FORWARD(Ts)(xs))...}.result;
#endif
    }

    template<class F, class... Ts, class R=decltype(
        boost::hof::apply(std::declval<const F&>(), boost::hof::eval(std::declval<Ts>())...)
    ),
    class=typename std::enable_if<(std::is_void<R>::value)>::type 
    >
    constexpr typename detail::holder<Ts...>::type 
    operator()(const F& f, Ts&&... xs) const BOOST_HOF_RETURNS_DEDUCE_NOEXCEPT(boost::hof::apply(f, boost::hof::eval(BOOST_HOF_FORWARD(Ts)(xs))...))
    {
        return (typename detail::holder<Ts...>::type)
#if BOOST_HOF_NO_ORDERED_BRACE_INIT
        boost::hof::detail::eval_ordered<R>
            (f, boost::hof::pack(), BOOST_HOF_FORWARD(Ts)(xs)...);
#else
        boost::hof::detail::eval_helper<R>
            {f, boost::hof::eval(BOOST_HOF_FORWARD(Ts)(xs))...};
#endif
    }
};

}

BOOST_HOF_DECLARE_STATIC_VAR(apply_eval, detail::apply_eval_f);

}} // namespace boost::hof

#endif

/* apply_eval.hpp
lPc8hGg/xRX5tGJ8NVTQMDk1wQiaqCffypXUSckrE5IPRXJAocRiPy2VyHhjqL1zNMafuHfE9mYc0mMFrJhLFhJuvWEkE1cBoer0SJ0nCUaFmqgXJ8cbU+pQVCKwc7QPCcxIoCMxxRrH+Z9sxCjeMpCi7qmMd4+oGeR+F3DEPzwV4TdR+zPkIRZz5Se0fipb8ny0pf+4kTroHTN7fjAFymGilNVSqcIgV5t7i2wS0BwEb/Brq3plkDwp02Yya+21S5KSqrMCM5INVc/QPntLd+fwE5UOnTp8bV0kpRGuTuKj6jCFwPNIkDh9w2stlWwQMrVn8RCoNCAiKL9MGzRFtxbR+UTGU/gP1XolTTpeAYTeL/zNzTTQuyrtozfQu2r3AJr/vDGxPr2IIIEJSdzAJgseNTyW0TOYh8lIvJXrMe/gmZTaKSTD/eJpDiNNpM07ePeJJz/XRR81GqoMRmH+gCA8YeyFfKOpdXucQ2hc5jtJRsW6Wz6ly7EYdByXihTotZv6aKTUKZN0pV76lQqjL/bKDaypMWo09sshrJ8s4SCxRTOjK8H7eNPn0thyRKeXkeB9WvQSY0jGTn39WJb2AnfqzJ0DiQQTGYZL8VU6KPfS4IAK7UkZWaY9hody7ZrLSCmYKdT5QAZdKR68iZRi94D/qFIY3w+ZgYvijfPntIGTpVXeD4YEMrs/Gd7w8XkrJzG8q9YOoP7fDYn6QBaiggT7dzwEhsR7VBbtL5XxSlc9FAew3M1pQfv3Kol2gtVQ5qdOvW5mXk/hfg4ybF84KzC8u/vQUsVy4qbpKu6J2+FAkHY9h8pWavj02aIxoYyc7jIC6QnED/JxpsCF3XQfnUQyYsVGDPe6AeDQjQzgrAoIA2eQB3qHGI1pKOPRR200mSYoNRvtpRPRrV5D9lIjdWkW5Ukrho8bhm/87fjGv9I0roC+8euT8Zlft7rnN36uv1hrv9mAhT7aYnxsTaDO2X68QgkmViYB+JErmH4UZRfFZuji7AZxlbz3UJJ/XiOVpPkrPZWk5RpWEmQADWfKGfY/4U0vKvww7bPpCJwhoEHywncvvvZX3SS75WBbcCwq+tViqGhZkTzOBJ6sPhVPXGXFWhTclPx4vFz7fg6/8DiMaMKtryMxPetTMXHm8euIQxat4Wbuv3az7tefT+y/ojOuPUghDyb0fz7P/ddTdnEC349315zaTTfokqs2NcAzSfoNWeXNLG8WviXJF0fSKT2HYPFoOtgaLrBTJy9c0Gt8hwIlzasTP819Wv6N8QpZbeZunJxFGh54sjvRUD1RsQMx29gtR1J8CvtyxZd72xdRx9aFumkbBshmZAvu1O5buS9q9FSaipkT2k8VvcOycH4lJ7PD/n+xu3canOGnvDKTVh1PrcZTrzRSm0mP5F4mCeZl61fi1oF04GdfYr3ScUGy5ynZajYkv/3KWTMkurywPAkymwx5EXIDl78Q7M/4Yf6w4aT2JnYpKtjvWSxsbBCg+QPc8qWzxTkNe/Ox2KXF2nUMi42NbhFmiTUzp/fVMHR4kD/xfd0NPd/VS3q+5+X1fI/d1PP974Ge71/rBe8f2T3fO8f1fP9dL3h1veBd1Avet3rBe7gXvNm94GX3gpfRm/7rE957ya+ihzWY+eWEj7dl3Z9m8Q81c8KHWlN/+cImgTaMKrGXhTHsdo0VX9exSyu0tHdixkQEfZKvBxn4REe/6Fk80QjGLIusCQNhpvtPR0sLfPSPECA3Ha+z3kd7AL2z0JdTAbS3Bg4Ssdttd11i0nc9WqHAwDvy04OW/AFBc/7AasuKQlMh1PBf5aIzUm6CP9GKq5KuQsDhMXtsoUMgLa/DFtmHO6YR/Pg=
*/