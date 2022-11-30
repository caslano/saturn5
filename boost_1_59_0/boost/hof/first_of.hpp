/*=============================================================================
    Copyright (c) 2012 Paul Fultz II
    first_of.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_HOF_GUARD_FUNCTION_CONDITIONAL_H
#define BOOST_HOF_GUARD_FUNCTION_CONDITIONAL_H

/// first_of
/// ========
/// 
/// Description
/// -----------
/// 
/// The `first_of` function adaptor combines several functions together. If
/// the first function can not be called, then it will try to call the next
/// function. This can be very useful when overloading functions using
/// template constraints(such as with `enable_if`).
/// 
/// Note: This is different than the [`match`](match.md) function adaptor, which
/// can lead to ambiguities. Instead, `first_of` will call the first function
/// that is callable, regardless if there is another function that could be
/// called as well.
/// 
/// Synopsis
/// --------
/// 
///     template<class... Fs>
///     constexpr first_of_adaptor<Fs...> first_of(Fs... fs);
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
///     #include <iostream>
///     using namespace boost::hof;
/// 
///     struct for_ints
///     {
///         void operator()(int) const
///         {
///             printf("Int\n");
///         }
///     };
/// 
///     struct for_floats
///     {
///         void operator()(float) const
///         {
///             printf("Float\n");
///         }
///     };
/// 
///     int main() {
///         first_of(for_ints(), for_floats())(3.0);
///     }
/// 
/// This will print `Int` because the `for_floats` function object won't ever be
/// called. Due to the conversion rules in C++, the `for_ints` function can be
/// called on floats, so it is chosen by `first_of` first, even though
/// `for_floats` is a better match.
/// 
/// So, the order of the functions in the `first_of_adaptor` are very important
/// to how the function is chosen.
/// 
/// References
/// ----------
/// 
/// * [POO51](http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2016/p0051r2.pdf) - Proposal for C++
///   Proposal for C++ generic overload function
/// * [Conditional overloading](<Conditional overloading>)
/// 

#include <boost/hof/reveal.hpp>
#include <boost/hof/detail/compressed_pair.hpp>
#include <boost/hof/detail/callable_base.hpp>
#include <boost/hof/detail/delegate.hpp>
#include <boost/hof/detail/join.hpp>
#include <boost/hof/detail/seq.hpp>
#include <boost/hof/detail/make.hpp>
#include <boost/hof/detail/static_const_var.hpp>

namespace boost { namespace hof {

namespace detail {

template<class F1, class F2>
struct basic_first_of_adaptor : F1, F2
{
    BOOST_HOF_INHERIT_DEFAULT(basic_first_of_adaptor, F1, F2)

    template<class A, class B,
        BOOST_HOF_ENABLE_IF_CONVERTIBLE(A, F1),
        BOOST_HOF_ENABLE_IF_CONVERTIBLE(B, F2)>
    constexpr basic_first_of_adaptor(A&& f1, B&& f2)
    noexcept(BOOST_HOF_IS_NOTHROW_CONSTRUCTIBLE(F1, A&&) && BOOST_HOF_IS_NOTHROW_CONSTRUCTIBLE(F2, B&&))
    : F1(BOOST_HOF_FORWARD(A)(f1)), F2(BOOST_HOF_FORWARD(B)(f2))
    {}

    template<class X,
        class=typename std::enable_if<
        BOOST_HOF_IS_CONVERTIBLE(X, F1) && 
        BOOST_HOF_IS_DEFAULT_CONSTRUCTIBLE(F2)
    >::type>
    constexpr basic_first_of_adaptor(X&& x) 
    BOOST_HOF_NOEXCEPT_CONSTRUCTIBLE(F1, X&&)
    : F1(BOOST_HOF_FORWARD(X)(x))
    {} 

    template<class... Ts>
    struct select
    : std::conditional
    <
        is_invocable<F1, Ts...>::value, 
        F1,
        F2
    >
    {};

    BOOST_HOF_RETURNS_CLASS(basic_first_of_adaptor);

    template<class... Ts, class F=typename select<Ts...>::type>
    constexpr BOOST_HOF_SFINAE_RESULT(typename select<Ts...>::type, id_<Ts>...) 
    operator()(Ts && ... xs) const
    BOOST_HOF_SFINAE_RETURNS
    (
        BOOST_HOF_RETURNS_STATIC_CAST(const F&)(*BOOST_HOF_CONST_THIS)(BOOST_HOF_FORWARD(Ts)(xs)...)
    );
};

template <class F1, class F2>
constexpr const F1& which(std::true_type, const F1& f1, const F2&) noexcept
{ 
    return f1; 
}

template <class F1, class F2>
constexpr const F2& which(std::false_type, const F1&, const F2& f2) noexcept
{ 
    return f2; 
}

template<class F1, class F2>
struct conditional_kernel : compressed_pair<F1, F2>
{
    typedef compressed_pair<F1, F2> base;
    BOOST_HOF_INHERIT_CONSTRUCTOR(conditional_kernel, base)

    template<class... Ts>
    struct select
    : std::conditional
    <
        is_invocable<F1, Ts...>::value, 
        F1,
        F2
    >
    {};

    BOOST_HOF_RETURNS_CLASS(conditional_kernel);

    template<class... Ts, class PickFirst=is_invocable<F1, Ts...>>
    constexpr BOOST_HOF_SFINAE_RESULT(typename select<Ts...>::type, id_<Ts>...) 
    operator()(Ts && ... xs) const
    BOOST_HOF_SFINAE_RETURNS
    (
        boost::hof::detail::which(
            BOOST_HOF_RETURNS_CONSTRUCT(PickFirst)(),
            BOOST_HOF_MANGLE_CAST(const F1&)(BOOST_HOF_CONST_THIS->first(xs...)),
            BOOST_HOF_MANGLE_CAST(const F2&)(BOOST_HOF_CONST_THIS->second(xs...))
        )
        (BOOST_HOF_FORWARD(Ts)(xs)...)
    );
};
}

template<class F, class... Fs>
struct first_of_adaptor 
: detail::conditional_kernel<F, BOOST_HOF_JOIN(first_of_adaptor, Fs...) >
{
    typedef first_of_adaptor fit_rewritable_tag;
    typedef BOOST_HOF_JOIN(first_of_adaptor, Fs...) kernel_base;
    typedef detail::conditional_kernel<F, kernel_base > base;

    BOOST_HOF_INHERIT_DEFAULT(first_of_adaptor, base)

    template<class X, class... Xs, 
        BOOST_HOF_ENABLE_IF_CONSTRUCTIBLE(base, X, kernel_base), 
        BOOST_HOF_ENABLE_IF_CONSTRUCTIBLE(kernel_base, Xs...)>
    constexpr first_of_adaptor(X&& f1, Xs&& ... fs) 
    noexcept(BOOST_HOF_IS_NOTHROW_CONSTRUCTIBLE(base, X&&, kernel_base) && BOOST_HOF_IS_NOTHROW_CONSTRUCTIBLE(kernel_base, Xs&&...))
    : base(BOOST_HOF_FORWARD(X)(f1), kernel_base(BOOST_HOF_FORWARD(Xs)(fs)...))
    {}

    template<class X, class... Xs, 
        BOOST_HOF_ENABLE_IF_CONSTRUCTIBLE(base, X)>
    constexpr first_of_adaptor(X&& f1) 
    BOOST_HOF_NOEXCEPT_CONSTRUCTIBLE(base, X&&)
    : base(BOOST_HOF_FORWARD(X)(f1))
    {}

    struct failure
    : failure_for<F, Fs...>
    {};
};

template<class F>
struct first_of_adaptor<F> : F
{
    typedef first_of_adaptor fit_rewritable_tag;
    BOOST_HOF_INHERIT_CONSTRUCTOR(first_of_adaptor, F);

    struct failure
    : failure_for<F>
    {};
};

template<class F1, class F2>
struct first_of_adaptor<F1, F2> 
: detail::conditional_kernel<F1, F2>
{
    typedef detail::conditional_kernel<F1, F2> base;
    typedef first_of_adaptor fit_rewritable_tag;
    BOOST_HOF_INHERIT_CONSTRUCTOR(first_of_adaptor, base);

    struct failure
    : failure_for<F1, F2>
    {};
};

BOOST_HOF_DECLARE_STATIC_VAR(first_of, detail::make<first_of_adaptor>);

}} // namespace boost::hof

#endif

/* first_of.hpp
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
*/