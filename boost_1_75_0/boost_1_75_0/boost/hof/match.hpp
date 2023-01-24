/*=============================================================================
    Copyright (c) 2012 Paul Fultz II
    match.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_HOF_GUARD_FUNCTION_OVERLOAD_H
#define BOOST_HOF_GUARD_FUNCTION_OVERLOAD_H

/// match
/// =====
/// 
/// Description
/// -----------
/// 
/// The `match` function adaptor combines several functions together and
/// resolves which one should be called by using C++ overload resolution. This
/// is different than the [`first_of`](/include/boost/hof/conditional) adaptor which resolves
/// them based on order.
/// 
/// Synopsis
/// --------
/// 
///     template<class... Fs>
///     constexpr match_adaptor<Fs...> match(Fs...fs);
/// 
/// Requirements
/// ------------
/// 
/// Fs must be:
/// 
/// * [ConstInvocable](ConstInvocable)
/// * MoveConstructible
/// 
/// Example
/// -------
/// 
///     #include <boost/hof.hpp>
///     using namespace boost::hof;
/// 
///     struct int_class
///     {
///         int operator()(int) const
///         {
///             return 1;
///         }
///     };
/// 
///     struct foo
///     {};
/// 
///     struct foo_class
///     {
///         foo operator()(foo) const
///         {
///             return foo();
///         }
///     };
/// 
///     typedef match_adaptor<int_class, foo_class> fun;
/// 
///     static_assert(std::is_same<int, decltype(fun()(1))>::value, "Failed match");
///     static_assert(std::is_same<foo, decltype(fun()(foo()))>::value, "Failed match");
/// 
///     int main() {}
/// 
/// References
/// ----------
/// 
/// * [POO51](http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2016/p0051r2.pdf) - Proposal for C++
///   Proposal for C++ generic overload function
/// 

#include <boost/hof/reveal.hpp>
#include <boost/hof/detail/callable_base.hpp>
#include <boost/hof/detail/delegate.hpp>
#include <boost/hof/detail/move.hpp>
#include <boost/hof/detail/make.hpp>
#include <boost/hof/detail/static_const_var.hpp>

namespace boost { namespace hof {

template<class...Fs> struct match_adaptor;
 
template<class F, class...Fs>
struct match_adaptor<F, Fs...> : detail::callable_base<F>, match_adaptor<Fs...>
{
    typedef match_adaptor<Fs...> base;
    typedef match_adaptor fit_rewritable_tag;

    struct failure
    : failure_for<detail::callable_base<F>, Fs...>
    {};

    BOOST_HOF_INHERIT_DEFAULT(match_adaptor, detail::callable_base<F>, base);

    template<class X, class... Xs, BOOST_HOF_ENABLE_IF_CONVERTIBLE(X, detail::callable_base<F>), BOOST_HOF_ENABLE_IF_CONSTRUCTIBLE(base, Xs...)>
    constexpr match_adaptor(X&& f1, Xs&& ... fs) 
    : detail::callable_base<F>(BOOST_HOF_FORWARD(X)(f1)), base(BOOST_HOF_FORWARD(Xs)(fs)...)
    {}

    using F::operator();
    using base::operator();
};

template<class F>
struct match_adaptor<F> : detail::callable_base<F>
{
    typedef detail::callable_base<F> base;
    typedef match_adaptor fit_rewritable_tag;
    using F::operator();

    BOOST_HOF_INHERIT_CONSTRUCTOR(match_adaptor, detail::callable_base<F>);
};

BOOST_HOF_DECLARE_STATIC_VAR(match, detail::make<match_adaptor>);

}} // namespace boost::hof

#endif

/* match.hpp
9chnwhoBkMBlz9cLy7Durkldf+FA4ueXPvsvuMArEYyHsxWBPdxHZ8hja631a/6yCHinTUovgO48yZIUMakEhxINgqyehWLTVp4g0JXVla2g7oDphT3jheeJPDY6hfq3T37xO/oSpvCTz2Eef/ZAzfveEDqEHcBuNYqUKB9RQwMPDL7S2mjIibASf5QAe+Vdub62ZUpIv3RnwpzG0LDp5vOtfVODWvPaRMl+shapBs35lfA3sm+x3Srd0K8vfvmv2VEL/NM6axD+zhak7G8iX9k+EU9hX9tmVW46T51Q3zqxl95tdaAdIF1y76hAv1DhDgQ/HIrP4mTS6oD8uB3JY1CTzceIufumC+AX6pUMpKpxnwN1AjmJSFVCCxNPJYNvP9P24NngDBX+1GHlgpcIvCDn9OFIOra2gtO58v1SDMnoLOsuuarXBl9o3jegOkehVOsxcu9gy4wv3qvz5Hw+o/05HUmogOU5FJ5EOyxfKHUBN6OGYg5U9Xzm5Rc/R3V4qsskCf9LlB5v1WfyKVOkiG5OszC5Gx9J1Q4T0PM/3O1IYn93txO5Pxd8Xvy1chNucRH6vNmgmjniutkwFINlYF79RXLjXp2FCG0f6YsVox2OPprURaiAv8F73x+KQWd3h3d//UjKQhHVNfXXz7cvz3758Ld+YDxYTCfBNfy9lz+AElTQ4ZdfyKV/hL30W6pbs6DAatwK8wCexLAd
*/