// Copyright (c) 2016-2022 Antony Polukhin
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PFR_DETAIL_MAKE_FLAT_TUPLE_OF_REFERENCES_HPP
#define BOOST_PFR_DETAIL_MAKE_FLAT_TUPLE_OF_REFERENCES_HPP
#pragma once

#include <boost/pfr/detail/config.hpp>

#include <utility>      // metaprogramming stuff
#include <boost/pfr/detail/sequence_tuple.hpp>
#include <boost/pfr/detail/rvalue_t.hpp>
#include <boost/pfr/detail/make_integer_sequence.hpp>


namespace boost { namespace pfr { namespace detail {

template <std::size_t Index>
using size_t_ = std::integral_constant<std::size_t, Index >;

// Helper: Make a "getter" object corresponding to built-in tuple::get
// For user-defined structures, the getter should be "offset_based_getter"
struct sequence_tuple_getter {
  template <std::size_t idx, typename TupleOfReferences>
  decltype(auto) get(TupleOfReferences&& t, size_t_<idx>) const noexcept {
    return sequence_tuple::get<idx>(std::forward<TupleOfReferences>(t));
  }
};


template <class TupleOrUserType, class Getter, std::size_t Begin, std::size_t Size>
constexpr auto make_flat_tuple_of_references(TupleOrUserType&, const Getter&, size_t_<Begin>, size_t_<Size>) noexcept;

template <class TupleOrUserType, class Getter, std::size_t Begin>
constexpr sequence_tuple::tuple<> make_flat_tuple_of_references(TupleOrUserType&, const Getter&, size_t_<Begin>, size_t_<0>) noexcept;

template <class TupleOrUserType, class Getter, std::size_t Begin>
constexpr auto make_flat_tuple_of_references(TupleOrUserType&, const Getter&, size_t_<Begin>, size_t_<1>) noexcept;

template <class... T>
constexpr auto tie_as_tuple_with_references(T&... args) noexcept {
    return sequence_tuple::tuple<T&...>{ args... };
}

template <class... T>
constexpr decltype(auto) tie_as_tuple_with_references(detail::sequence_tuple::tuple<T...>& t) noexcept {
    return detail::make_flat_tuple_of_references(t, sequence_tuple_getter{}, size_t_<0>{}, size_t_<sequence_tuple::tuple<T...>::size_v>{});
}

template <class... T>
constexpr decltype(auto) tie_as_tuple_with_references(const detail::sequence_tuple::tuple<T...>& t) noexcept {
    return detail::make_flat_tuple_of_references(t, sequence_tuple_getter{}, size_t_<0>{}, size_t_<sequence_tuple::tuple<T...>::size_v>{});
}

template <class Tuple1, std::size_t... I1, class Tuple2, std::size_t... I2>
constexpr auto my_tuple_cat_impl(const Tuple1& t1, std::index_sequence<I1...>, const Tuple2& t2, std::index_sequence<I2...>) noexcept {
    return detail::tie_as_tuple_with_references(
        sequence_tuple::get<I1>(t1)...,
        sequence_tuple::get<I2>(t2)...
    );
}

template <class Tuple1, class Tuple2>
constexpr auto my_tuple_cat(const Tuple1& t1, const Tuple2& t2) noexcept {
    return detail::my_tuple_cat_impl(
        t1, detail::make_index_sequence< Tuple1::size_v >{},
        t2, detail::make_index_sequence< Tuple2::size_v >{}
    );
}

template <class TupleOrUserType, class Getter, std::size_t Begin, std::size_t Size>
constexpr auto make_flat_tuple_of_references(TupleOrUserType& t, const Getter& g, size_t_<Begin>, size_t_<Size>) noexcept {
    constexpr std::size_t next_size = Size / 2;
    return detail::my_tuple_cat(
        detail::make_flat_tuple_of_references(t, g, size_t_<Begin>{}, size_t_<next_size>{}),
        detail::make_flat_tuple_of_references(t, g, size_t_<Begin + Size / 2>{}, size_t_<Size - next_size>{})
    );
}

template <class TupleOrUserType, class Getter, std::size_t Begin>
constexpr sequence_tuple::tuple<> make_flat_tuple_of_references(TupleOrUserType&, const Getter&, size_t_<Begin>, size_t_<0>) noexcept {
    return {};
}

template <class TupleOrUserType, class Getter, std::size_t Begin>
constexpr auto make_flat_tuple_of_references(TupleOrUserType& t, const Getter& g, size_t_<Begin>, size_t_<1>) noexcept {
    return detail::tie_as_tuple_with_references(
        g.get(t, size_t_<Begin>{})
    );
}

}}} // namespace boost::pfr::detail

#endif // BOOST_PFR_DETAIL_MAKE_FLAT_TUPLE_OF_REFERENCES_HPP

/* make_flat_tuple_of_references.hpp
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
*/