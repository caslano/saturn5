// Copyright (c) 2017-2018 Chris Beck
// Copyright (c) 2019-2022 Antony Polukhin
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PFR_DETAIL_OFFSET_BASED_GETTER_HPP
#define BOOST_PFR_DETAIL_OFFSET_BASED_GETTER_HPP
#pragma once

#include <boost/pfr/detail/config.hpp>

#include <type_traits>
#include <utility>
#include <memory>  // std::addressof
#include <boost/pfr/detail/sequence_tuple.hpp>
#include <boost/pfr/detail/rvalue_t.hpp>
#include <boost/pfr/detail/size_t_.hpp>


namespace boost { namespace pfr { namespace detail {

// Our own implementation of std::aligned_storage. On godbolt with MSVC, I have compilation errors
// using the standard version, it seems the compiler cannot generate default ctor.

template<std::size_t s, std::size_t a>
struct internal_aligned_storage {
   alignas(a) char storage_[s];
};

// Metafunction that replaces tuple<T1, T2, T3, ...> with
// tuple<std::aligned_storage_t<sizeof(T1), alignof(T1)>, std::aligned_storage<sizeof(T2), alignof(T2)>, ...>
//
// The point is, the new tuple is "layout compatible" in the sense that members have the same offsets,
// but this tuple is constexpr constructible.

template <typename T>
struct tuple_of_aligned_storage;

template <typename... Ts>
struct tuple_of_aligned_storage<sequence_tuple::tuple<Ts...>> {
  using type = sequence_tuple::tuple<internal_aligned_storage<sizeof(Ts),
#if defined(__GNUC__) && __GNUC__ < 8 && !defined(__x86_64__) && !defined(__CYGWIN__)
      // Before GCC-8 the `alignof` was returning the optimal alignment rather than the minimal one.
      // We have to adjust the alignemnt because otherwise we get the wrong offset.
      (alignof(Ts) > 4 ? 4 : alignof(Ts))
#else
      alignof(Ts)
#endif
  >...>;
};

// Note: If pfr has a typelist also, could also have an overload for that here

template <typename T>
using tuple_of_aligned_storage_t = typename tuple_of_aligned_storage<T>::type;

/***
 * Given a structure type and its sequence of members, we want to build a function
 * object "getter" that implements a version of `std::get` using offset arithmetic
 * and reinterpret_cast.
 *
 * typename U should be a user-defined struct
 * typename S should be a sequence_tuple which is layout compatible with U
 */

template <typename U, typename S>
class offset_based_getter {
  using this_t = offset_based_getter<U, S>;

  static_assert(sizeof(U) == sizeof(S), "====================> Boost.PFR: Member sequence does not indicate correct size for struct type! Maybe the user-provided type is not a SimpleAggregate?");
  static_assert(alignof(U) == alignof(S), "====================> Boost.PFR: Member sequence does not indicate correct alignment for struct type!");

  static_assert(!std::is_const<U>::value, "====================> Boost.PFR: const should be stripped from user-defined type when using offset_based_getter or overload resolution will be ambiguous later, this indicates an error within pfr");
  static_assert(!std::is_reference<U>::value, "====================> Boost.PFR: reference should be stripped from user-defined type when using offset_based_getter or overload resolution will be ambiguous later, this indicates an error within pfr");
  static_assert(!std::is_volatile<U>::value, "====================> Boost.PFR: volatile should be stripped from user-defined type when using offset_based_getter or overload resolution will be ambiguous later. this indicates an error within pfr");

  // Get type of idx'th member
  template <std::size_t idx>
  using index_t = typename sequence_tuple::tuple_element<idx, S>::type;

  // Get offset of idx'th member
  // Idea: Layout object has the same offsets as instance of S, so if S and U are layout compatible, then these offset
  // calculations are correct.
  template <std::size_t idx>
  static constexpr std::ptrdiff_t offset() noexcept {
    constexpr tuple_of_aligned_storage_t<S> layout{};
    return &sequence_tuple::get<idx>(layout).storage_[0] - &sequence_tuple::get<0>(layout).storage_[0];
  }

  // Encapsulates offset arithmetic and reinterpret_cast
  template <std::size_t idx>
  static index_t<idx> * get_pointer(U * u) noexcept {
    return reinterpret_cast<index_t<idx> *>(reinterpret_cast<char *>(u) + this_t::offset<idx>());
  }

  template <std::size_t idx>
  static const index_t<idx> * get_pointer(const U * u) noexcept {
    return reinterpret_cast<const index_t<idx> *>(reinterpret_cast<const char *>(u) + this_t::offset<idx>());
  }

  template <std::size_t idx>
  static volatile index_t<idx> * get_pointer(volatile U * u) noexcept {
    return reinterpret_cast<volatile index_t<idx> *>(reinterpret_cast<volatile char *>(u) + this_t::offset<idx>());
  }

  template <std::size_t idx>
  static const volatile index_t<idx> * get_pointer(const volatile U * u) noexcept {
    return reinterpret_cast<const volatile index_t<idx> *>(reinterpret_cast<const volatile char *>(u) + this_t::offset<idx>());
  }

public:
  template <std::size_t idx>
  index_t<idx> & get(U & u, size_t_<idx>) const noexcept {
    return *this_t::get_pointer<idx>(std::addressof(u));
  }

  template <std::size_t idx>
  index_t<idx> const & get(U const & u, size_t_<idx>) const noexcept {
    return *this_t::get_pointer<idx>(std::addressof(u));
  }

  template <std::size_t idx>
  index_t<idx> volatile & get(U volatile & u, size_t_<idx>) const noexcept {
    return *this_t::get_pointer<idx>(std::addressof(u));
  }

  template <std::size_t idx>
  index_t<idx> const volatile & get(U const volatile & u, size_t_<idx>) const noexcept {
    return *this_t::get_pointer<idx>(std::addressof(u));
  }

  // rvalues must not be used here, to avoid template instantiation bloats.
  template <std::size_t idx>
  index_t<idx> && get(rvalue_t<U> u, size_t_<idx>) const = delete;
};


}}} // namespace boost::pfr::detail

#endif // BOOST_PFR_DETAIL_OFFSET_LIST_HPP

/* offset_based_getter.hpp
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
*/