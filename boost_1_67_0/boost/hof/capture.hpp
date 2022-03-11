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