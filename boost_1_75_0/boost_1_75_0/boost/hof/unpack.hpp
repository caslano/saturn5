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
AAGWBxC1MfD5HIh6T/+16HlxMqAyL4aO5j4AQB5nYC0HHJj2AhQgAxtwD40CGqI0gHspelXtyXsASQCiVtWygX50ItYsnwAYo4DAG8BMH4C1AgB/8j3wJ5IAb4BXlBrgTO0Y/BF6dyg+gBjQEwrwKjQES131XMrvw8VmmGmc+DP9E8EEkyRQ0iksCTTB+g+KHcbfHd5/FR7Av4yOoKL1V+y47iW4zLEcF3HOEccVXhC+OuOr8ou69mYthZdIr1OvS4RQxABnE+eomrua9YcL9giSiGrVDgZAkZk/FQkQmpeyp152o/1Jy5tM+DCrhKe358XoRdisgu77JRMQHl22ECe9iaAQbPFLQBDxb+QR8DzMZ94TkBYgSwYgCzRunaS34eD8LGW9oFSep/POacppG6IYMfNcT0Mv8G3TfnVtd/Pq5MX+PCWIiFVyAcXkFgsXXCr+y4ULcZdezznVBYYY+i4E/GCJ/Dr2cwhYaGnmLxfaM7IgjR7AkCUCWfTo0R1OXg+ChxwwHp6QYomJurV7aP5yoUTUbdlTTXeY0QWBJoUABoQYWhcC51wqprhQIEKJLG1QXZASQzNC2GkPQ4mhjSFgrqX6O3pJL3BUF8xE3Wv0Dy0IxNCoEPiDpavrQd0hcJElxr9cOBJDFXtoKC+miaGxIWMxlSfJ14NiQ6rpD5NJsbeJQDo95xQXUCIQuEeE9hB5HRsSwn77sJwU
*/