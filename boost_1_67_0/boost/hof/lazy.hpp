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