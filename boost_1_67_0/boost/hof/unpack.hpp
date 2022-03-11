/*=============================================================================
    Copyright (c) 2015 Paul Fultz II
    unpack.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_HOF_GUARD_UNPACK_H
#define BOOST_HOF_GUARD_UNPACK_H

/// unpack
/// ======
/// 
/// Description
/// -----------
/// 
/// The `unpack` function adaptor takes a sequence and uses the elements of
/// the sequence for the arguments to the function. Multiple sequences can be
/// passed to the function. All elements from each sequence will be passed
/// into the function. 
/// 
/// 
/// Synopsis
/// --------
/// 
///     template<class F>
///     unpack_adaptor<F> unpack(F f);
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
///     struct sum
///     {
///         template<class T, class U>
///         T operator()(T x, U y) const
///         {
///             return x+y;
///         }
///     };
/// 
///     int main() {
///         int r = unpack(sum())(std::make_tuple(3,2));
///         assert(r == 5);
///     }
/// 
/// References
/// ----------
/// 
/// * [std::apply](http://en.cppreference.com/w/cpp/utility/apply) - C++17 function to unpack a tuple
/// * [`unpack_sequence`](unpack_sequence)
/// 

#include <boost/hof/unpack_sequence.hpp>
#include <boost/hof/is_unpackable.hpp>
#include <boost/hof/detail/seq.hpp>
#include <boost/hof/capture.hpp>
#include <boost/hof/always.hpp>
#include <boost/hof/reveal.hpp>
#include <boost/hof/detail/and.hpp>
#include <boost/hof/detail/delegate.hpp>
#include <boost/hof/detail/holder.hpp>
#include <boost/hof/detail/move.hpp>
#include <boost/hof/detail/make.hpp>
#include <boost/hof/detail/static_const_var.hpp>

namespace boost { namespace hof {

namespace detail {

template<class F, class Sequence>
constexpr auto unpack_simple(F&& f, Sequence&& s) BOOST_HOF_RETURNS
(
    detail::unpack_impl(BOOST_HOF_FORWARD(F)(f), BOOST_HOF_FORWARD(Sequence)(s))
)

template<class F, class... Sequences>
constexpr auto unpack_join(F&& f, Sequences&&... s) BOOST_HOF_RETURNS
(
    boost::hof::pack_join(unpack_simple(boost::hof::pack_forward, BOOST_HOF_FORWARD(Sequences)(s))...)(BOOST_HOF_FORWARD(F)(f))
);

}

template<class F>
struct unpack_adaptor : detail::callable_base<F>
{
    typedef unpack_adaptor fit_rewritable1_tag;
    BOOST_HOF_INHERIT_CONSTRUCTOR(unpack_adaptor, detail::callable_base<F>);

    template<class... Ts>
    constexpr const detail::callable_base<F>& base_function(Ts&&... xs) const noexcept
    {
        return boost::hof::always_ref(*this)(xs...);
    }

    struct unpack_failure
    {
        template<class Failure>
        struct apply
        {
            struct deducer
            {
                template<class... Ts>
                typename Failure::template of<Ts...> operator()(Ts&&...) const;
            };

            template<class T, class=typename std::enable_if<(
                is_unpackable<T>::value
            )>::type>
            static auto deduce(T&& x)
            BOOST_HOF_RETURNS
            (
                boost::hof::detail::unpack_simple(deducer(), BOOST_HOF_FORWARD(T)(x))
            );

            template<class T, class... Ts, class=typename std::enable_if<(
                is_unpackable<T>::value && BOOST_HOF_AND_UNPACK(is_unpackable<Ts>::value)
            )>::type>
            static auto deduce(T&& x, Ts&&... xs) BOOST_HOF_RETURNS
            (
                boost::hof::detail::unpack_join(deducer(), BOOST_HOF_FORWARD(T)(x), BOOST_HOF_FORWARD(Ts)(xs)...)
            );
#ifdef _MSC_VER
            template<class... Ts>
            struct nop_failure;
            template<class... Ts, class=typename std::enable_if<(
                !BOOST_HOF_AND_UNPACK(is_unpackable<Ts>::value)
            )>::type>
            static as_failure<nop_failure> deduce(Ts&&... xs);
#endif
            template<class... Ts>
            struct of
#if (defined(__GNUC__) && !defined (__clang__) && __GNUC__ == 4 && __GNUC_MINOR__ < 7) || defined (_MSC_VER)
            : std::enable_if<true, decltype(apply::deduce(std::declval<Ts>()...))>::type
#else
            : decltype(apply::deduce(std::declval<Ts>()...))
#endif
            {};
        };
    };

    struct failure
    : failure_map<unpack_failure, detail::callable_base<F>>
    {};

    BOOST_HOF_RETURNS_CLASS(unpack_adaptor);
    template<class T, class=typename std::enable_if<(
        is_unpackable<T>::value
    )>::type>
    constexpr auto operator()(T&& x) const
    BOOST_HOF_RETURNS
    (
        boost::hof::detail::unpack_simple(BOOST_HOF_MANGLE_CAST(const detail::callable_base<F>&)(BOOST_HOF_CONST_THIS->base_function(x)), BOOST_HOF_FORWARD(T)(x))
    );

    template<class T, class... Ts, class=typename std::enable_if<(
        is_unpackable<T>::value && BOOST_HOF_AND_UNPACK(is_unpackable<Ts>::value)
    )>::type>
    constexpr auto operator()(T&& x, Ts&&... xs) const BOOST_HOF_RETURNS
    (
        boost::hof::detail::unpack_join(BOOST_HOF_MANGLE_CAST(const detail::callable_base<F>&)(BOOST_HOF_CONST_THIS->base_function(x)), BOOST_HOF_FORWARD(T)(x), BOOST_HOF_FORWARD(Ts)(xs)...)
    );
};

BOOST_HOF_DECLARE_STATIC_VAR(unpack, detail::make<unpack_adaptor>);

}} // namespace boost::hof

#endif

/* unpack.hpp
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
*/