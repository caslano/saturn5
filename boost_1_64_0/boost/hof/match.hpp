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
EE6nKmtF7Fk1/odGDmUHazGRE6tUPGvc9JLPGjdQh0ZHm/eK/ssy4qaF63X/T6IjQeH/v7qbZP7G6g018yJP8kilYJF8SPOWarKT/IVZ8be8Ub7l9r8lvqX0+ePyYd4haGKzexYweJrdMz3i4G7Opx1S6HsR8hd1CTIWOtl/1uHIv2tCDqZGDhXmo+hTRKxYLMuXtDmv34xnyC/c/QM+YZoPli202FFVnrFyQIkIZKcmrEQXIH+VOONTdS/jqXrVDLEvQ3Loxa2h541QJZkSazDfP8WgeqKi+hfvMtX1emMcLMthKuQWOIORxet/9Rh0v9/Eh+SXHBYTa0kXY2wccnGE1DAA24aSS3NDfQK22FV5PvGElE3Jt+ts+nNy8baxmEy4pujBhnfC7zskFJYXBB2j9EdnYOIQV2Vet/agmauiHQfH23HuMYs4KfjvPTCDYe2rNA3YaAv1lM1KE26jPcjGoecfknyiOtbOIz70WvGuGjgGxZU7ckFb68Px5xrSodECX7wXJ0dgtmwszu5NW8Dj0+lwnatiyEbr6+H628JE/W2OB3+KsIe1OVl/m5+svy34pvS3hSb9bYH46Sukdd3wSpL+tkDpqbuuvy0QcxmTD3/j+ltUk0+Gt2VR/IGiMdd5/ZYvWftu9IOugP8vs0B5H2/BPzBefLxO3v4kiSIcnQkNYqeXgUMbKZWQPNJclVFfd4GSRyCO0FIQIMcUDpg5ffyoUsacgtfnW3keUfQUrXu7WozjfY84ATYovF62/A2BlEtKWY6pd961rcuOD/WPlDJoPEs7HRH8WBc1qPmpK6HxLcCxbGbwOMh8g0talw/AcPvrB7wBkPYAi75FeX3aIQAnM8P8K0w8SWWwJ2DBxK8RT8c69Ag9ziZyyEzB0q6ibWZOwws6S7PYMVI2AhZ3QxT6KA4LiuIYo14L1OwC9EPss7Wd6P4oWhvK5Ta5UOTNEF6ujT0zo6JQmfjp+zxTE498KoDmsCOfPB6ZhsdNEAFj0NmtcuFq/oiG6RxGBa3gFLTLSGytyW5JGY/QufXy7rRFjlbmgbdV5tY776Q4RM22Shq2X4szfbVPje67qla07ZPmDMROoLbQFs8Ra/7JMp8djrysbtZlFH0IeSk0BQ0s8rYprdVgvhJt3ZgfdEV2wiujBgx4k2ju7FaUcYtyoJGesyetYyzvHtAbl/RbNeLhl/Xdd0OG4SMbldSIx55SQ/r7jOjQh2qnsFWr4p4HNw4ul3F89n6o2vlyDuKzMrmSyaqSgaZKZhqVnMyBfG6OV8KjjLzZUE/bHSTB0kvxdadcSo/Ybd+0QyzTR7/uN3OjK0i3YlpZHwAluCvYY6Mt2Gc20mjByeQf5MlZq5pV60XE5s7Yr+j+qHj6gGqW6bwf05O/8wELvgWaQNcvtuqHJsFcbboHc2V87ExynT3dqfS5p8libhE6oFrnUa3KQ1eOImMQLroTTZIfcqEtdDryERB+uBXPPJ6/euwN3l/lsNoGm1GEmvmE2Q9Y4N4lp9YgYSXLXhySWlccQC+9cDNxxKWvMUg7hGDyMZJDaoGiRkwnFAIAeHk/vhYJ4w0UoVIoFou5cKkszHHoYyGyzsyfi7MN2prhrSmm+TVP88BhfTCrzFnnfYyDocYnHUrT3quBzYDBcqbbcZTdm5hmi8isxw4dsSLJj9yhDtWXY9X+jof6rf9gSiJjbCEXhw8rjqkxPYDH9FNckA2n6+qJxrr6LvIZuX79AoIxxWh36E55SQYrJRlsmN/WUxdIpdewyyCQHsdNl0Puecn8l3fg5z+oT78ekOLaexvp1j/plC7J1nIKVr0c7EkuCcBDtuNCb4+ehojOiJ/ZqyPu+iI=
*/