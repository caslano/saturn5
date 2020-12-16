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
7jd7C/G70i7NttyAta0iB5YRiKIDQRrjyS0ICIvbtDIybvvK8LgnbTDxeL/KrkXt61TFub78ZLxCje9BNsqCYEhxpkzxm4g4G5SV41eeI9nCsGT9MrHylRMobbzlhScdbCauEEGmnysujxZXRI4pd23xK+knN2ehJWCuIynHXvJw/jZbv0xQdUJoTtX+xCFwrgELbIz5ttFBhToyibFNXq9mK94YmUfuMooHDSn6P8NdjqxonAbredbk2P4an1zxiVhvvFj103ZptmaT1STWgRMDM2uuG3sjRHPDY73vugKVeey8KK+3s8gEw++543tnB5IGj0UdFzX5+WEKwp41LQy+sEmPIYTxasaPMX6U8cOMVzBezvgBxgcYL2Vcw3gx4yrGyxjXMV7PuJ7xZsZNjLczbma8m/FexqalhPMYmxlbGFsZ2xknM3YwTmWcwzibcSbjwYwzGKczTmO8lPE9jOcxns+4ivFixjWMj99HuIPxEWCtzsbVgsEe1ASeqvmSpsDmgdiYDOY2Ha3sFtg4cVnAhPsljzYMoevuq01th8LqOjeJlsdHvbFHG462DoO2orqZS6yEmVLxQrhhwoPSxWyqxxYnHvFpWvGj7W2pIRYdISsCFX3Ewn7yMvGK2IkvXrbKORvfUdIYwinFhPsXEh5WQDg/D7j8nhSFf5Im8U//HP6Jz+afgZn8M2QwfpbfGz8NP1C6WTWef82rJuC3tsiyajq9Vx/AwY/G+BWVpHkQY1pJjqsm4a0x3glMJWiMH8+usGwQP019qjBPuLXe1Fg1He+x+nuAa8Y/Jr4T7xtb8G5S35V7MEaIxzd9GRt8VNUWsQ7MLMfE9Zgq6/GaC9RL2cda/t31eBD1+PlqD5n011AFysq5b+MXrxyugzRZB1l9/2N10PKZdeBbYDXN6epbAEsCZt8MK713n5MIlYdif5EVPwWrqI6i6sc347SpDZ5OF7B6xOncIuvsFPxi1zhQZg9Yl/it1Qr8tR2QNTm6/ovX5D8BFwkwu9V76bwiNqrIROPJDwJ7aZjHb0eg4eR00JsCW+k3bmfbaDxPAgUHGsnPztad+3ce3rm32zbv8ZPHAh3wlQwfmJROvhe3s7J7LvzNtVTaaLE/p8u3BsGh33iyjzsIhH5wPLnv5F7fPlPg+cCuwGuUzpRNdtP284e11ABHbfYhe1FJbalrY9XXFnpNWhunuTIDclf9QEzyC/Nx3GChzUeXpB+z3ViP23u9DnhK6WRPV26a03Ud73KQxSW8b7H5LorhaIY1Sx9bbXfb2O22pnLb7A9igHbG+E7FeL5O0XRIT8/PHVxuc79MT7Bc9KvX8tLLA+b08j/YTRO8PddRPsUBNuBGWmRVDfB7An530IlMTqz/asSD34F1HN+sIfbf0u9tHUdtmz6gtHeW2/bvKre17abks0F4q9z28bv43VduO3YAv+/iHbTbPiq37Tpdbit/sdz23W0I9Fq57c2XEPCFctv77fDTCtoO0D4E7QPUUouv03TXJYjkNDzsAaEZKewz4+Hlbps8auWQXBWUDji9QU5HG9ZZiG4JK5PvSBqV2/a0Od33kcVjWXx3EGXxZrw2JA1l8Sens/lgLm4P9AfGrPYuXsFFGa/vJWFXdAObIxs4PsxVbY/XKDtNWkt3oKW/i2c0j21xDwjhIluNGkyoDTbnSlj89vReRymKAoSRJb0aT23J8vlyorJ7Gp7CW3v217TWti3ORDKyhT86o8XSgafWPjL9vUjH25NC75Wh91Uiz5P2wekd5Or4JUC7L6GW6Fav1fdqBJWdcdkZmbLaGTfZ7r6b4n4GtlMCQZu7/qjt8o0bWwcctU0wv7gCfnDubYDNvQ0=
*/