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