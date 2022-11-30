// Copyright (c) 2016-2022 Antony Polukhin
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PFR_DETAIL_FIELDS_COUNT_HPP
#define BOOST_PFR_DETAIL_FIELDS_COUNT_HPP
#pragma once

#include <boost/pfr/detail/config.hpp>
#include <boost/pfr/detail/make_integer_sequence.hpp>
#include <boost/pfr/detail/size_t_.hpp>
#include <boost/pfr/detail/unsafe_declval.hpp>

#include <climits>      // CHAR_BIT
#include <type_traits>
#include <utility>      // metaprogramming stuff

#ifdef __clang__
#   pragma clang diagnostic push
#   pragma clang diagnostic ignored "-Wmissing-braces"
#   pragma clang diagnostic ignored "-Wundefined-inline"
#   pragma clang diagnostic ignored "-Wundefined-internal"
#   pragma clang diagnostic ignored "-Wmissing-field-initializers"
#endif

namespace boost { namespace pfr { namespace detail {

///////////////////// Structure that can be converted to reference to anything
struct ubiq_lref_constructor {
    std::size_t ignore;
    template <class Type> constexpr operator Type&() const && noexcept {  // tweak for template_unconstrained.cpp like cases
        return detail::unsafe_declval<Type&>();
    }

    template <class Type> constexpr operator Type&() const & noexcept {  // tweak for optional_chrono.cpp like cases
        return detail::unsafe_declval<Type&>();
    }
};

///////////////////// Structure that can be converted to rvalue reference to anything
struct ubiq_rref_constructor {
    std::size_t ignore;
    template <class Type> /*constexpr*/ operator Type() const && noexcept {  // Allows initialization of rvalue reference fields and move-only types
        return detail::unsafe_declval<Type>();
    }
};


#ifndef __cpp_lib_is_aggregate
///////////////////// Hand-made is_aggregate_initializable_n<T> trait

// Structure that can be converted to reference to anything except reference to T
template <class T, bool IsCopyConstructible>
struct ubiq_constructor_except {
    std::size_t ignore;
    template <class Type> constexpr operator std::enable_if_t<!std::is_same<T, Type>::value, Type&> () const noexcept; // Undefined
};

template <class T>
struct ubiq_constructor_except<T, false> {
    std::size_t ignore;
    template <class Type> constexpr operator std::enable_if_t<!std::is_same<T, Type>::value, Type&&> () const noexcept; // Undefined
};


// `std::is_constructible<T, ubiq_constructor_except<T>>` consumes a lot of time, so we made a separate lazy trait for it.
template <std::size_t N, class T> struct is_single_field_and_aggregate_initializable: std::false_type {};
template <class T> struct is_single_field_and_aggregate_initializable<1, T>: std::integral_constant<
    bool, !std::is_constructible<T, ubiq_constructor_except<T, std::is_copy_constructible<T>::value>>::value
> {};

// Hand-made is_aggregate<T> trait:
// Before C++20 aggregates could be constructed from `decltype(ubiq_?ref_constructor{I})...` but type traits report that
// there's no constructor from `decltype(ubiq_?ref_constructor{I})...`
// Special case for N == 1: `std::is_constructible<T, ubiq_?ref_constructor>` returns true if N == 1 and T is copy/move constructible.
template <class T, std::size_t N>
struct is_aggregate_initializable_n {
    template <std::size_t ...I>
    static constexpr bool is_not_constructible_n(std::index_sequence<I...>) noexcept {
        return (!std::is_constructible<T, decltype(ubiq_lref_constructor{I})...>::value && !std::is_constructible<T, decltype(ubiq_rref_constructor{I})...>::value)
            || is_single_field_and_aggregate_initializable<N, T>::value
        ;
    }

    static constexpr bool value =
           std::is_empty<T>::value
        || std::is_array<T>::value
        || std::is_fundamental<T>::value
        || is_not_constructible_n(detail::make_index_sequence<N>{})
    ;
};

#endif // #ifndef __cpp_lib_is_aggregate

///////////////////// Detect aggregates with inheritance
template <class Derived, class U>
constexpr bool static_assert_non_inherited() noexcept {
    static_assert(
            !std::is_base_of<U, Derived>::value,
            "====================> Boost.PFR: Boost.PFR: Inherited types are not supported."
    );
    return true;
}

template <class Derived>
struct ubiq_lref_base_asserting {
    template <class Type> constexpr operator Type&() const &&  // tweak for template_unconstrained.cpp like cases
        noexcept(detail::static_assert_non_inherited<Derived, Type>())  // force the computation of assert function
    {
        return detail::unsafe_declval<Type&>();
    }

    template <class Type> constexpr operator Type&() const &  // tweak for optional_chrono.cpp like cases
        noexcept(detail::static_assert_non_inherited<Derived, Type>())  // force the computation of assert function
    {
        return detail::unsafe_declval<Type&>();
    }
};

template <class Derived>
struct ubiq_rref_base_asserting {
    template <class Type> /*constexpr*/ operator Type() const &&  // Allows initialization of rvalue reference fields and move-only types
        noexcept(detail::static_assert_non_inherited<Derived, Type>())  // force the computation of assert function
    {
        return detail::unsafe_declval<Type>();
    }
};

template <class T, std::size_t I0, std::size_t... I, class /*Enable*/ = typename std::enable_if<std::is_copy_constructible<T>::value>::type>
constexpr auto assert_first_not_base(std::index_sequence<I0, I...>) noexcept
    -> typename std::add_pointer<decltype(T{ ubiq_lref_base_asserting<T>{}, ubiq_lref_constructor{I}... })>::type
{
    return nullptr;
}

template <class T, std::size_t I0, std::size_t... I, class /*Enable*/ = typename std::enable_if<!std::is_copy_constructible<T>::value>::type>
constexpr auto assert_first_not_base(std::index_sequence<I0, I...>) noexcept
    -> typename std::add_pointer<decltype(T{ ubiq_rref_base_asserting<T>{}, ubiq_rref_constructor{I}... })>::type
{
    return nullptr;
}

template <class T>
constexpr void* assert_first_not_base(std::index_sequence<>) noexcept
{
    return nullptr;
}

///////////////////// Helper for SFINAE on fields count
template <class T, std::size_t... I, class /*Enable*/ = typename std::enable_if<std::is_copy_constructible<T>::value>::type>
constexpr auto enable_if_constructible_helper(std::index_sequence<I...>) noexcept
    -> typename std::add_pointer<decltype(T{ ubiq_lref_constructor{I}... })>::type;

template <class T, std::size_t... I, class /*Enable*/ = typename std::enable_if<!std::is_copy_constructible<T>::value>::type>
constexpr auto enable_if_constructible_helper(std::index_sequence<I...>) noexcept
    -> typename std::add_pointer<decltype(T{ ubiq_rref_constructor{I}... })>::type;

template <class T, std::size_t N, class /*Enable*/ = decltype( enable_if_constructible_helper<T>(detail::make_index_sequence<N>()) ) >
using enable_if_constructible_helper_t = std::size_t;

///////////////////// Helpers for range size detection
template <std::size_t Begin, std::size_t Last>
using is_one_element_range = std::integral_constant<bool, Begin == Last>;

using multi_element_range = std::false_type;
using one_element_range = std::true_type;

///////////////////// Non greedy fields count search. Templates instantiation depth is log(sizeof(T)), templates instantiation count is log(sizeof(T)).
template <class T, std::size_t Begin, std::size_t Middle>
constexpr std::size_t detect_fields_count(detail::one_element_range, long) noexcept {
    static_assert(
        Begin == Middle,
        "====================> Boost.PFR: Internal logic error."
    );
    return Begin;
}

template <class T, std::size_t Begin, std::size_t Middle>
constexpr std::size_t detect_fields_count(detail::multi_element_range, int) noexcept;

template <class T, std::size_t Begin, std::size_t Middle>
constexpr auto detect_fields_count(detail::multi_element_range, long) noexcept
    -> detail::enable_if_constructible_helper_t<T, Middle>
{
    constexpr std::size_t next_v = Middle + (Middle - Begin + 1) / 2;
    return detail::detect_fields_count<T, Middle, next_v>(detail::is_one_element_range<Middle, next_v>{}, 1L);
}

template <class T, std::size_t Begin, std::size_t Middle>
constexpr std::size_t detect_fields_count(detail::multi_element_range, int) noexcept {
    constexpr std::size_t next_v = Begin + (Middle - Begin) / 2;
    return detail::detect_fields_count<T, Begin, next_v>(detail::is_one_element_range<Begin, next_v>{}, 1L);
}

///////////////////// Greedy search. Templates instantiation depth is log(sizeof(T)), templates instantiation count is log(sizeof(T))*T in worst case.
template <class T, std::size_t N>
constexpr auto detect_fields_count_greedy_remember(long) noexcept
    -> detail::enable_if_constructible_helper_t<T, N>
{
    return N;
}

template <class T, std::size_t N>
constexpr std::size_t detect_fields_count_greedy_remember(int) noexcept {
    return 0;
}

template <class T, std::size_t Begin, std::size_t Last>
constexpr std::size_t detect_fields_count_greedy(detail::one_element_range) noexcept {
    static_assert(
        Begin == Last,
        "====================> Boost.PFR: Internal logic error."
    );
    return detail::detect_fields_count_greedy_remember<T, Begin>(1L);
}

template <class T, std::size_t Begin, std::size_t Last>
constexpr std::size_t detect_fields_count_greedy(detail::multi_element_range) noexcept {
    constexpr std::size_t middle = Begin + (Last - Begin) / 2;
    constexpr std::size_t fields_count_big_range = detail::detect_fields_count_greedy<T, middle + 1, Last>(
        detail::is_one_element_range<middle + 1, Last>{}
    );

    constexpr std::size_t small_range_begin = (fields_count_big_range ? 0 : Begin);
    constexpr std::size_t small_range_last = (fields_count_big_range ? 0 : middle);
    constexpr std::size_t fields_count_small_range = detail::detect_fields_count_greedy<T, small_range_begin, small_range_last>(
        detail::is_one_element_range<small_range_begin, small_range_last>{}
    );
    return fields_count_big_range ? fields_count_big_range : fields_count_small_range;
}

///////////////////// Choosing between array size, greedy and non greedy search.
template <class T, std::size_t N>
constexpr auto detect_fields_count_dispatch(size_t_<N>, long, long) noexcept
    -> typename std::enable_if<std::is_array<T>::value, std::size_t>::type
{
    return sizeof(T) / sizeof(typename std::remove_all_extents<T>::type);
}

template <class T, std::size_t N>
constexpr auto detect_fields_count_dispatch(size_t_<N>, long, int) noexcept
    -> decltype(sizeof(T{}))
{
    constexpr std::size_t middle = N / 2 + 1;
    return detail::detect_fields_count<T, 0, middle>(detail::multi_element_range{}, 1L);
}

template <class T, std::size_t N>
constexpr std::size_t detect_fields_count_dispatch(size_t_<N>, int, int) noexcept {
    // T is not default aggregate initialzable. It means that at least one of the members is not default constructible,
    // so we have to check all the aggregate initializations for T up to N parameters and return the bigest succeeded
    // (we can not use binary search for detecting fields count).
    return detail::detect_fields_count_greedy<T, 0, N>(detail::multi_element_range{});
}

///////////////////// Returns fields count
template <class T>
constexpr std::size_t fields_count() noexcept {
    using type = std::remove_cv_t<T>;

    static_assert(
        !std::is_reference<type>::value,
        "====================> Boost.PFR: Attempt to get fields count on a reference. This is not allowed because that could hide an issue and different library users expect different behavior in that case."
    );

#if !BOOST_PFR_HAS_GUARANTEED_COPY_ELISION
    static_assert(
        std::is_copy_constructible<std::remove_all_extents_t<type>>::value || (
            std::is_move_constructible<std::remove_all_extents_t<type>>::value
            && std::is_move_assignable<std::remove_all_extents_t<type>>::value
        ),
        "====================> Boost.PFR: Type and each field in the type must be copy constructible (or move constructible and move assignable)."
    );
#endif  // #if !BOOST_PFR_HAS_GUARANTEED_COPY_ELISION

    static_assert(
        !std::is_polymorphic<type>::value,
        "====================> Boost.PFR: Type must have no virtual function, because otherwise it is not aggregate initializable."
    );

#ifdef __cpp_lib_is_aggregate
    static_assert(
        std::is_aggregate<type>::value             // Does not return `true` for built-in types.
        || std::is_scalar<type>::value,
        "====================> Boost.PFR: Type must be aggregate initializable."
    );
#endif

// Can't use the following. See the non_std_layout.cpp test.
//#if !BOOST_PFR_USE_CPP17
//    static_assert(
//        std::is_standard_layout<type>::value,   // Does not return `true` for structs that have non standard layout members.
//        "Type must be aggregate initializable."
//    );
//#endif

#if defined(_MSC_VER) && (_MSC_VER <= 1920)
    // Workaround for msvc compilers. Versions <= 1920 have a limit of max 1024 elements in template parameter pack
    constexpr std::size_t max_fields_count = (sizeof(type) * CHAR_BIT >= 1024 ? 1024 : sizeof(type) * CHAR_BIT);
#else
    constexpr std::size_t max_fields_count = (sizeof(type) * CHAR_BIT); // We multiply by CHAR_BIT because the type may have bitfields in T
#endif

    constexpr std::size_t result = detail::detect_fields_count_dispatch<type>(size_t_<max_fields_count>{}, 1L, 1L);

    detail::assert_first_not_base<type>(detail::make_index_sequence<result>{});

#ifndef __cpp_lib_is_aggregate
    static_assert(
        is_aggregate_initializable_n<type, result>::value,
        "====================> Boost.PFR: Types with user specified constructors (non-aggregate initializable types) are not supported."
    );
#endif

    static_assert(
        result != 0 || std::is_empty<type>::value || std::is_fundamental<type>::value || std::is_reference<type>::value,
        "====================> Boost.PFR: If there's no other failed static asserts then something went wrong. Please report this issue to the github along with the structure you're reflecting."
    );

    return result;
}

}}} // namespace boost::pfr::detail

#ifdef __clang__
#   pragma clang diagnostic pop
#endif

#endif // BOOST_PFR_DETAIL_FIELDS_COUNT_HPP

/* fields_count.hpp
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
*/