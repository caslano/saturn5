// Boost.Geometry

// Copyright (c) 2020, Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_UTIL_TYPE_TRAITS_STD_HPP
#define BOOST_GEOMETRY_UTIL_TYPE_TRAITS_STD_HPP


#include <cstddef>
#include <type_traits>


namespace boost { namespace geometry
{


namespace util
{


// C++17
template <bool B>
using bool_constant = std::integral_constant<bool, B>;

// non-standard
template <int I>
using int_constant = std::integral_constant<int, I>;

// non-standard
template <std::size_t I>
using index_constant = std::integral_constant<std::size_t, I>;

// non-standard
template <std::size_t S>
using size_constant = std::integral_constant<std::size_t, S>;


// C++17
template <typename ...>
struct conjunction
    : std::true_type
{};
template<typename Trait>
struct conjunction<Trait>
    : Trait
{};
template <typename Trait, typename ...Traits>
struct conjunction<Trait, Traits...>
    : std::conditional_t<Trait::value, conjunction<Traits...>, Trait>
{};

// C++17
template <typename ...>
struct disjunction
    : std::false_type
{};
template <typename Trait>
struct disjunction<Trait>
    : Trait
{};
template <typename Trait, typename ...Traits>
struct disjunction<Trait, Traits...>
    : std::conditional_t<Trait::value, Trait, disjunction<Traits...>>
{};

// C++17
template <typename Trait>
struct negation
    : bool_constant<!Trait::value>
{};


// non-standard
/*
template <typename ...Traits>
using and_ = conjunction<Traits...>;

template <typename ...Traits>
using or_ = disjunction<Traits...>;

template <typename Trait>
using not_ = negation<Trait>;
*/


// C++20
template <typename T>
struct remove_cvref
{
    using type = std::remove_cv_t<std::remove_reference_t<T>>;
};

template <typename T>
using remove_cvref_t = typename remove_cvref<T>::type;

// non-standard
template <typename T>
struct remove_cref
{
    using type = std::remove_const_t<std::remove_reference_t<T>>;
};

template <typename T>
using remove_cref_t = typename remove_cref<T>::type;

// non-standard
template <typename T>
struct remove_cptrref
{
    using type = std::remove_const_t
        <
            std::remove_pointer_t<std::remove_reference_t<T>>
        >;
};

template <typename T>
using remove_cptrref_t = typename remove_cptrref<T>::type;


// non-standard
template <typename From, typename To>
struct transcribe_const
{
    using type = std::conditional_t
                    <
                        std::is_const<std::remove_reference_t<From>>::value,
                        std::add_const_t<To>,
                        To
                    >;
};

template <typename From, typename To>
using transcribe_const_t = typename transcribe_const<From, To>::type;


// non-standard
template <typename From, typename To>
struct transcribe_reference
{
    using type = std::remove_reference_t<To>;
};

template <typename From, typename To>
struct transcribe_reference<From &, To>
{
    using type = std::remove_reference_t<To> &;
};

template <typename From, typename To>
struct transcribe_reference<From &&, To>
{
    using type = std::remove_reference_t<To> &&;
};

template <typename From, typename To>
using transcribe_reference_t = typename transcribe_reference<From, To>::type;


// non-standard
template <typename From, typename To>
struct transcribe_cref
{
    using type = transcribe_reference_t<From, transcribe_const_t<From, To>>;
};

template <typename From, typename To>
using transcribe_cref_t = typename transcribe_cref<From, To>::type;


} // namespace util


// Deprecated utilities, defined for backward compatibility but might be
// removed in the future.


/*!
    \brief Meta-function to define a const or non const type
    \ingroup utility
    \details If the boolean template parameter is true, the type parameter
        will be defined as const, otherwise it will be defined as it was.
        This meta-function is used to have one implementation for both
        const and non const references
    \note This traits class is completely independant from Boost.Geometry
        and might be a separate addition to Boost
    \note Used in a.o. for_each, interior_rings, exterior_ring
    \par Example
    \code
        void foo(typename add_const_if_c<IsConst, Point>::type& point)
    \endcode
*/
template <bool IsConst, typename Type>
struct add_const_if_c
{
    typedef std::conditional_t
        <
            IsConst,
            Type const,
            Type
        > type;
};


namespace util
{

template <typename T>
using bare_type = remove_cptrref<T>;

} // namespace util


}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_UTIL_TYPE_TRAITS_STD_HPP

/* type_traits_std.hpp
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
*/