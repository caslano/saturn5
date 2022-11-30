/*=============================================================================
    Copyright (c) 2014 Paul Fultz II
    lazy.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_HOF_GUARD_FUNCTION_LAZY_H
#define BOOST_HOF_GUARD_FUNCTION_LAZY_H

/// lazy
/// ====
/// 
/// Description
/// -----------
/// 
/// The `lazy` function adaptor returns a function object call wrapper for a
/// function. Calling this wrapper is equivalent to invoking the function. It
/// is a simple form of lambda expressions, but is constexpr friendly. By
/// default, `lazy` captures all of its variables by value, just like `bind`.
/// `std::ref` can be used to capture references instead.
/// 
/// Ultimately, calling `lazy(f)(x)` is the equivalent to calling
/// `std::bind(f, x)` except the lazy version can be called in a constexpr
/// context, as well. The `lazy` adaptor is compatible with `std::bind`, so
/// most of the time `lazy` and `std::bind` can be used interchangeably.
/// 
/// Synopsis
/// --------
/// 
///     template<class F>
///     constexpr lazy_adaptor<F> lazy(F f);
/// 
/// Semantics
/// ---------
/// 
///     assert(lazy(f)(xs...) == std::bind(f, xs...))
///     assert(lazy(f)(xs...)() == f(xs...))
///     assert(lazy(f)(_1)(x) == f(x))
///     assert(lazy(f)(lazy(g)(_1))(x) == f(g(x)))
/// 
/// Requirements
/// ------------
/// 
/// F must be:
/// 
/// * [ConstInvocable](ConstInvocable)
/// * MoveConstructible
/// 
/// Example
/// -------
/// 
///     #include <boost/hof.hpp>
///     #include <cassert>
///     using namespace boost::hof;
/// 
///     int main() {
///         auto add = [](auto x, auto y) { return x+y; };
///         auto increment = lazy(add)(_1, 1);
///         assert(increment(5) == 6);
///     }
/// 
/// References
/// ----------
/// 
/// * [std::bind](http://en.cppreference.com/w/cpp/utility/functional/bind)
/// 

#include <boost/hof/arg.hpp>
#include <boost/hof/first_of.hpp>
#include <boost/hof/always.hpp>
#include <boost/hof/static.hpp>
#include <boost/hof/detail/delegate.hpp>
#include <boost/hof/detail/compressed_pair.hpp>
#include <boost/hof/pack.hpp>
#include <boost/hof/detail/make.hpp>
#include <boost/hof/detail/static_const_var.hpp>
#include <functional>
#include <type_traits>

namespace boost { namespace hof {

namespace detail {

struct placeholder_transformer
{
    template<class T, typename std::enable_if<(std::is_placeholder<T>::value > 0), int>::type = 0>
    constexpr detail::make_args_f<std::size_t, std::is_placeholder<T>::value> operator()(const T&) const noexcept
    {
        return {};
    }
};

struct bind_transformer
{
    template<class T, typename std::enable_if<std::is_bind_expression<T>::value, int>::type = 0>
    constexpr const T& operator()(const T& x) const noexcept
    {
        return x;
    }
};

struct ref_transformer
{
    template<class T>
    constexpr auto operator()(std::reference_wrapper<T> x) const 
    BOOST_HOF_SFINAE_RETURNS(boost::hof::always_ref(x.get()));
};

struct id_transformer
{
    template<class T>
    constexpr auto operator()(T&& x) const 
    BOOST_HOF_SFINAE_RETURNS(always_detail::always_base<T>(BOOST_HOF_FORWARD(T)(x)));
};

BOOST_HOF_DECLARE_STATIC_VAR(pick_transformer, first_of_adaptor<placeholder_transformer, bind_transformer, ref_transformer, id_transformer>);

template<class T, class Pack>
constexpr auto lazy_transform(T&& x, const Pack& p) BOOST_HOF_RETURNS
(
    p(boost::hof::detail::pick_transformer(BOOST_HOF_FORWARD(T)(x)))
);

template<class F, class Pack>
struct lazy_unpack
{
    const F& f;
    const Pack& p;

    constexpr lazy_unpack(const F& fp, const Pack& pp) noexcept
    : f(fp), p(pp)
    {}

    template<class... Ts>
    constexpr auto operator()(Ts&&... xs) const BOOST_HOF_RETURNS
    (
        f(lazy_transform(BOOST_HOF_FORWARD(Ts)(xs), p)...)
    );
};

template<class F, class Pack>
constexpr lazy_unpack<F, Pack> make_lazy_unpack(const F& f, const Pack& p) noexcept
{
    return lazy_unpack<F, Pack>(f, p);
}

template<class F, class Pack>
struct lazy_invoker 
: detail::compressed_pair<F, Pack>
{
    typedef detail::compressed_pair<F, Pack> base_type;
    typedef lazy_invoker fit_rewritable1_tag;

#ifdef _MSC_VER
    BOOST_HOF_INHERIT_CONSTRUCTOR(lazy_invoker, base_type)
#else
    BOOST_HOF_INHERIT_DEFAULT_EMPTY(lazy_invoker, base_type)

    template<class X, class Y, 
        BOOST_HOF_ENABLE_IF_CONSTRUCTIBLE(base_type, X&&, Y&&)
    >
    constexpr lazy_invoker(X&& x, Y&& y) 
    BOOST_HOF_NOEXCEPT_CONSTRUCTIBLE(base_type, X&&, Y&&)
    : base_type(BOOST_HOF_FORWARD(X)(x), BOOST_HOF_FORWARD(Y)(y))
    {}
#endif

    template<class... Ts>
    constexpr const F& base_function(Ts&&... xs) const noexcept
    {
        return this->first(xs...);
    }

    template<class... Ts>
    constexpr const Pack& get_pack(Ts&&... xs) const noexcept
    {
        return this->second(xs...);
    }

    BOOST_HOF_RETURNS_CLASS(lazy_invoker);

    template<class... Ts>
    constexpr auto operator()(Ts&&... xs) const BOOST_HOF_RETURNS
    (
        BOOST_HOF_MANGLE_CAST(const Pack&)(BOOST_HOF_CONST_THIS->get_pack(xs...))(
            boost::hof::detail::make_lazy_unpack(
                BOOST_HOF_MANGLE_CAST(const F&)(BOOST_HOF_CONST_THIS->base_function(xs...)), 
                boost::hof::pack_forward(BOOST_HOF_FORWARD(Ts)(xs)...)
            )
        )
    );
};

template<class F, class Pack>
constexpr lazy_invoker<F, Pack> make_lazy_invoker(F f, Pack pack)
BOOST_HOF_NOEXCEPT_CONSTRUCTIBLE(lazy_invoker<F, Pack>, F&&, Pack&&)
{
    return lazy_invoker<F, Pack>(static_cast<F&&>(f), static_cast<Pack&&>(pack));
}

template<class F>
struct lazy_nullary_invoker : F
{
    BOOST_HOF_INHERIT_CONSTRUCTOR(lazy_nullary_invoker, F);

    template<class... Ts>
    constexpr const F& base_function(Ts&&... xs) const noexcept
    {
        return boost::hof::always_ref(*this)(xs...);
    }

    BOOST_HOF_RETURNS_CLASS(lazy_nullary_invoker);

    template<class... Ts>
    constexpr auto operator()(Ts&&... xs) const BOOST_HOF_RETURNS
    (
        BOOST_HOF_MANGLE_CAST(const F&)(BOOST_HOF_CONST_THIS->base_function(xs...))()
    );
};

template<class F>
constexpr lazy_nullary_invoker<F> make_lazy_nullary_invoker(F f)
BOOST_HOF_NOEXCEPT_CONSTRUCTIBLE(lazy_nullary_invoker<F>, F&&)
{
    return lazy_nullary_invoker<F>(static_cast<F&&>(f));
}
}


template<class F>
struct lazy_adaptor : detail::callable_base<F>
{
    BOOST_HOF_INHERIT_CONSTRUCTOR(lazy_adaptor, detail::callable_base<F>);

    template<class... Ts>
    constexpr const detail::callable_base<F>& base_function(Ts&&... xs) const noexcept
    {
        return boost::hof::always_ref(*this)(xs...);
    }

    BOOST_HOF_RETURNS_CLASS(lazy_adaptor);

    template<class T, class... Ts>
    constexpr auto operator()(T x, Ts... xs) const BOOST_HOF_RETURNS
    (
        boost::hof::detail::make_lazy_invoker(BOOST_HOF_RETURNS_C_CAST(detail::callable_base<F>&&)(BOOST_HOF_CONST_THIS->base_function(x, xs...)), 
            boost::hof::pack_basic(BOOST_HOF_RETURNS_STATIC_CAST(T&&)(x), BOOST_HOF_RETURNS_STATIC_CAST(Ts&&)(xs)...))
    );

    // Workaround for gcc 4.7
    template<class Unused=int>
    constexpr detail::lazy_nullary_invoker<F> operator()() const
    BOOST_HOF_RETURNS_DEDUCE_NOEXCEPT(
        boost::hof::detail::make_lazy_nullary_invoker(BOOST_HOF_RETURNS_C_CAST(detail::callable_base<F>&&)(
            BOOST_HOF_CONST_THIS->base_function(BOOST_HOF_RETURNS_CONSTRUCT(Unused)())
        ))
    )
    {
        return boost::hof::detail::make_lazy_nullary_invoker((detail::callable_base<F>&&)(
            this->base_function(Unused())
        ));
    }

    // TODO: Overloads to use with ref qualifiers

    // template<class... Ts>
    // constexpr auto operator()(Ts... xs) const& BOOST_HOF_RETURNS
    // (
    //     boost::hof::detail::make_lazy_invoker(this->base_function(xs...), 
    //         pack(boost::hof::move(xs)...))
    // );

    // template<class... Ts>
    // constexpr auto operator()(Ts... xs) && BOOST_HOF_RETURNS
    // (
    //     boost::hof::detail::make_lazy_invoker((F&&)this->base_function(xs...), 
    //         pack(boost::hof::move(xs)...))
    // );
    
};

BOOST_HOF_DECLARE_STATIC_VAR(lazy, detail::make<lazy_adaptor>);

}} // namespace boost::hof

namespace std {
    template<class F, class Pack>
    struct is_bind_expression<boost::hof::detail::lazy_invoker<F, Pack>>
    : std::true_type
    {};

    template<class F>
    struct is_bind_expression<boost::hof::detail::lazy_nullary_invoker<F>>
    : std::true_type
    {};
}

#endif

/* lazy.hpp
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
*/