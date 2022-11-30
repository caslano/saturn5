/*=============================================================================
    Copyright (c) 2015 Paul Fultz II
    capture.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_HOF_GUARD_CAPTURE_H
#define BOOST_HOF_GUARD_CAPTURE_H

#include <boost/hof/detail/callable_base.hpp>
#include <boost/hof/detail/compressed_pair.hpp>
#include <boost/hof/reveal.hpp>
#include <boost/hof/pack.hpp>
#include <boost/hof/always.hpp>
#include <boost/hof/detail/move.hpp>
#include <boost/hof/detail/result_type.hpp>

/// capture
/// =======
/// 
/// Description
/// -----------
/// 
/// The `capture` function decorator is used to capture values in a function.
/// It provides more flexibility in capturing than the lambda capture list in
/// C++. It provides a way to do move and perfect capturing. The values
/// captured are prepended to the argument list of the function that will be
/// called.
/// 
/// Synopsis
/// --------
/// 
///     // Capture by decaying each value
///     template<class... Ts>
///     constexpr auto capture(Ts&&... xs);
/// 
///     // Capture lvalues by reference and rvalue reference by reference
///     template<class... Ts>
///     constexpr auto capture_forward(Ts&&... xs);
/// 
///     // Capture lvalues by reference and rvalues by value.
///     template<class... Ts>
///     constexpr auto capture_basic(Ts&&... xs);
/// 
/// Semantics
/// ---------
/// 
///     assert(capture(xs...)(f)(ys...) == f(xs..., ys...));
/// 
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
///         auto add_one = boost::hof::capture(1)(sum_f());
///         assert(add_one(2) == 3);
///     }
/// 

namespace boost { namespace hof {

namespace detail {

template<class F, class Pack>
struct capture_invoke : detail::compressed_pair<detail::callable_base<F>, Pack>, detail::function_result_type<F>
{
    typedef capture_invoke fit_rewritable1_tag;
    typedef detail::compressed_pair<detail::callable_base<F>, Pack> base;
    BOOST_HOF_INHERIT_CONSTRUCTOR(capture_invoke, base)
    template<class... Ts>
    constexpr const detail::callable_base<F>& base_function(Ts&&... xs) const noexcept
    {
        return this->first(xs...);
    }

    template<class... Ts>
    constexpr const Pack& get_pack(Ts&&...xs) const noexcept
    {
        return this->second(xs...);
    }

    template<class Failure, class... Ts>
    struct unpack_capture_failure
    {
        template<class... Us>
        struct apply
        {
            typedef typename Failure::template of<Us..., Ts...> type;
        };
    };

    struct capture_failure
    {
        template<class Failure>
        struct apply
        {
            template<class... Ts>
            struct of
            : Pack::template apply<unpack_capture_failure<Failure, Ts...>>::type
            {};
        };
    };

    struct failure
    : failure_map<capture_failure, detail::callable_base<F>>
    {};

    BOOST_HOF_RETURNS_CLASS(capture_invoke);

    template<class... Ts>
    constexpr BOOST_HOF_SFINAE_RESULT
    (
        typename result_of<decltype(boost::hof::pack_join), 
            id_<const Pack&>, 
            result_of<decltype(boost::hof::pack_forward), id_<Ts>...> 
        >::type,
        id_<detail::callable_base<F>&&>
    ) 
    operator()(Ts&&... xs) const BOOST_HOF_SFINAE_RETURNS
    (
        boost::hof::pack_join
        (
            BOOST_HOF_MANGLE_CAST(const Pack&)(BOOST_HOF_CONST_THIS->get_pack(xs...)), 
            boost::hof::pack_forward(BOOST_HOF_FORWARD(Ts)(xs)...)
        )
        (BOOST_HOF_RETURNS_C_CAST(detail::callable_base<F>&&)(BOOST_HOF_CONST_THIS->base_function(xs...)))
    );
};

template<class Pack>
struct capture_pack : Pack
{
    BOOST_HOF_INHERIT_CONSTRUCTOR(capture_pack, Pack);

    BOOST_HOF_RETURNS_CLASS(capture_pack);

    // TODO: Should use rvalue ref qualifier
    template<class F>
    constexpr auto operator()(F f) const BOOST_HOF_SFINAE_RETURNS
    (
        capture_invoke<F, Pack>(BOOST_HOF_RETURNS_STATIC_CAST(F&&)(f), 
            BOOST_HOF_RETURNS_C_CAST(Pack&&)(
                BOOST_HOF_RETURNS_STATIC_CAST(const Pack&)(*boost::hof::always(BOOST_HOF_CONST_THIS)(f))
            )
        )
    );
};

struct make_capture_pack_f
{
    template<class Pack>
    constexpr capture_pack<Pack> operator()(Pack p) const
    BOOST_HOF_NOEXCEPT_CONSTRUCTIBLE(capture_pack<Pack>, Pack&&)
    {
        return capture_pack<Pack>(static_cast<Pack&&>(p));
    }
};

template<class F>
struct capture_f
{
    template<class... Ts>
    constexpr auto operator()(Ts&&... xs) const BOOST_HOF_RETURNS
    (
        BOOST_HOF_RETURNS_CONSTRUCT(make_capture_pack_f)()(BOOST_HOF_RETURNS_CONSTRUCT(F)()(BOOST_HOF_FORWARD(Ts)(xs)...))
    );
};
}

BOOST_HOF_DECLARE_STATIC_VAR(capture_basic, detail::capture_f<detail::pack_basic_f>);
BOOST_HOF_DECLARE_STATIC_VAR(capture_forward, detail::capture_f<detail::pack_forward_f>);
BOOST_HOF_DECLARE_STATIC_VAR(capture, detail::capture_f<detail::pack_f>);

}} // namespace boost::hof

#endif

/* capture.hpp
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
*/