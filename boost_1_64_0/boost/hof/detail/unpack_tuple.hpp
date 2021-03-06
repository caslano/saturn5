/*=============================================================================
    Copyright (c) 2016 Paul Fultz II
    unpack_tuple.hpp
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_HOF_GUARD_UNPACK_TUPLE_HPP
#define BOOST_HOF_GUARD_UNPACK_TUPLE_HPP

#include <boost/hof/unpack_sequence.hpp>
#include <boost/hof/returns.hpp>
#include <boost/hof/detail/forward.hpp>
#include <boost/hof/detail/seq.hpp>
#include <tuple>
#include <array>

namespace boost { namespace hof {

namespace detail {

template<class Sequence>
constexpr typename gens<std::tuple_size<Sequence>::value>::type 
make_tuple_gens(const Sequence&)
{
    return {};
}

#if (defined(__GNUC__) && !defined (__clang__) && __GNUC__ == 4 && __GNUC_MINOR__ < 7)

template<std::size_t I, class Tuple>
struct tuple_element_return
: std::tuple_element<I, Tuple>
{};

template<std::size_t I, class Tuple>
struct tuple_element_return<I, Tuple&>
: std::add_lvalue_reference<typename tuple_element_return<I, Tuple>::type>
{};

template<std::size_t I, class Tuple>
struct tuple_element_return<I, Tuple&&>
: std::add_rvalue_reference<typename tuple_element_return<I, Tuple>::type>
{};

template<std::size_t I, class Tuple>
struct tuple_element_return<I, const Tuple>
: std::add_const<typename tuple_element_return<I, Tuple>::type>
{};

template< std::size_t I, class Tuple, class R = typename tuple_element_return<I, Tuple&&>::type >
R tuple_get( Tuple&& t ) 
{ 
    return (R&&)(std::get<I>(boost::hof::forward<Tuple>(t))); 
}
#define BOOST_HOF_UNPACK_TUPLE_GET boost::hof::detail::tuple_get
#else
#define BOOST_HOF_UNPACK_TUPLE_GET std::get

#endif

template<class F, class T, std::size_t ...N>
constexpr auto unpack_tuple(F&& f, T&& t, seq<N...>) BOOST_HOF_RETURNS
(
    f(
        BOOST_HOF_AUTO_FORWARD(BOOST_HOF_UNPACK_TUPLE_GET<N>(BOOST_HOF_AUTO_FORWARD(t)))...
    )
);

struct unpack_tuple_apply
{
    template<class F, class S>
    constexpr static auto apply(F&& f, S&& t) BOOST_HOF_RETURNS
    (
        boost::hof::detail::unpack_tuple(BOOST_HOF_FORWARD(F)(f), BOOST_HOF_FORWARD(S)(t), boost::hof::detail::make_tuple_gens(t))
    );
};

}

template<class... Ts>
struct unpack_sequence<std::tuple<Ts...>>
: detail::unpack_tuple_apply
{};

template<class T, class U>
struct unpack_sequence<std::pair<T, U>>
: detail::unpack_tuple_apply
{};

template<class T, std::size_t N>
struct unpack_sequence<std::array<T, N>>
: detail::unpack_tuple_apply
{};

}} // namespace boost::hof

#endif

/* unpack_tuple.hpp
Z43g2WHVxtXKDtw/1LsTnWFHqPkPANwb6DkFKycvZo4w9BRPAVyuxMkd7GG41lifUWc9xI79TU+ewrFXLii+W1ntTf6D5aFOSP3Msc58kK9PMyc9ikl7y+N2TMALWtg6KWou6KQ9TJCk054pp0kt29WOafzNWX7+RdIH0CuhRf9wIDGddkqcG45YR7czurdMnt32L2mLybl/a7f9DpSs1qgVA6Zdw5Xa1vnZScs8kiBJSyGZGRQfysikGIqt8eT4/s4ky4pAqQTGMA6gVyI29zNkhy6Uoyc5Ui+jcXBoisFNVv5kni8FGrHL4TTDBNQwNlFLJTI+rlgR25NuQW4DyeshCfHKaKXCKh/uEguIlOg90wyU/hKdj2+tu1yqfgf4fdSK9kU/7ytPPRVcyr+5R9w1dgvgwdvckQC6uCLctr8UsTNLltaTKEKeUEPzwzwqWk1jStOmZEwG/qWXjM58AbA+fXOPA4uvx0tTp+SP5XizSpCOlUF46NREYaoMsqDiTbx8UWZq0+En2B/P3hyNvoYQPpxv9jDfUyo369MD3NHMHzxdlhADEF0JUg==
*/