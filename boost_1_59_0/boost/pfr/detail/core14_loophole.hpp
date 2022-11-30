// Copyright (c) 2017-2018 Alexandr Poltavsky, Antony Polukhin.
// Copyright (c) 2019-2022 Antony Polukhin.
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)


// The Great Type Loophole (C++14)
// Initial implementation by Alexandr Poltavsky, http://alexpolt.github.io
//
// Description: 
//  The Great Type Loophole is a technique that allows to exchange type information with template
//  instantiations. Basically you can assign and read type information during compile time.
//  Here it is used to detect data members of a data type. I described it for the first time in
//  this blog post http://alexpolt.github.io/type-loophole.html .
//
// This technique exploits the http://www.open-std.org/jtc1/sc22/wg21/docs/cwg_active.html#2118
// CWG 2118. Stateful metaprogramming via friend injection
// Note: CWG agreed that such techniques should be ill-formed, although the mechanism for prohibiting them is as yet undetermined.

#ifndef BOOST_PFR_DETAIL_CORE14_LOOPHOLE_HPP
#define BOOST_PFR_DETAIL_CORE14_LOOPHOLE_HPP

#include <boost/pfr/detail/config.hpp>

#include <type_traits>
#include <utility>

#include <boost/pfr/detail/cast_to_layout_compatible.hpp> // still needed for enums
#include <boost/pfr/detail/offset_based_getter.hpp>
#include <boost/pfr/detail/fields_count.hpp>
#include <boost/pfr/detail/make_flat_tuple_of_references.hpp>
#include <boost/pfr/detail/make_integer_sequence.hpp>
#include <boost/pfr/detail/sequence_tuple.hpp>
#include <boost/pfr/detail/rvalue_t.hpp>
#include <boost/pfr/detail/unsafe_declval.hpp>


#ifdef __clang__
#   pragma clang diagnostic push
#   pragma clang diagnostic ignored "-Wmissing-braces"
#   pragma clang diagnostic ignored "-Wundefined-inline"
#   pragma clang diagnostic ignored "-Wundefined-internal"
#   pragma clang diagnostic ignored "-Wmissing-field-initializers"
#elif defined(__GNUC__)
#   pragma GCC diagnostic push
#   pragma GCC diagnostic ignored "-Wnon-template-friend"
#endif


namespace boost { namespace pfr { namespace detail {

// tag<T,N> generates friend declarations and helps with overload resolution.
// There are two types: one with the auto return type, which is the way we read types later.
// The second one is used in the detection of instantiations without which we'd get multiple
// definitions.

template <class T, std::size_t N>
struct tag {
    friend auto loophole(tag<T,N>);
};

// The definitions of friend functions.
template <class T, class U, std::size_t N, bool B>
struct fn_def_lref {
    friend auto loophole(tag<T,N>) {
        // Standard Library containers do not SFINAE on invalid copy constructor. Because of that std::vector<std::unique_ptr<int>> reports that it is copyable,
        // which leads to an instantiation error at this place.
        //
        // To workaround the issue, we check that the type U is movable, and move it in that case.
        using no_extents_t = std::remove_all_extents_t<U>;
        return static_cast< std::conditional_t<std::is_move_constructible<no_extents_t>::value, no_extents_t&&, no_extents_t&> >(
            boost::pfr::detail::unsafe_declval<no_extents_t&>()
        );
    }
};
template <class T, class U, std::size_t N, bool B>
struct fn_def_rref {
    friend auto loophole(tag<T,N>) { return std::move(boost::pfr::detail::unsafe_declval< std::remove_all_extents_t<U>& >()); }
};


// Those specializations are to avoid multiple definition errors.
template <class T, class U, std::size_t N>
struct fn_def_lref<T, U, N, true> {};

template <class T, class U, std::size_t N>
struct fn_def_rref<T, U, N, true> {};


// This has a templated conversion operator which in turn triggers instantiations.
// Important point, using sizeof seems to be more reliable. Also default template
// arguments are "cached" (I think). To fix that I provide a U template parameter to
// the ins functions which do the detection using constexpr friend functions and SFINAE.
template <class T, std::size_t N>
struct loophole_ubiq_lref {
    template<class U, std::size_t M> static std::size_t ins(...);
    template<class U, std::size_t M, std::size_t = sizeof(loophole(tag<T,M>{})) > static char ins(int);

    template<class U, std::size_t = sizeof(fn_def_lref<T, U, N, sizeof(ins<U, N>(0)) == sizeof(char)>)>
    constexpr operator U&() const&& noexcept; // `const&&` here helps to avoid ambiguity in loophole instantiations. optional_like test validate that behavior.
};

template <class T, std::size_t N>
struct loophole_ubiq_rref {
    template<class U, std::size_t M> static std::size_t ins(...);
    template<class U, std::size_t M, std::size_t = sizeof(loophole(tag<T,M>{})) > static char ins(int);

    template<class U, std::size_t = sizeof(fn_def_rref<T, U, N, sizeof(ins<U, N>(0)) == sizeof(char)>)>
    constexpr operator U&&() const&& noexcept; // `const&&` here helps to avoid ambiguity in loophole instantiations. optional_like test validate that behavior.
};


// This is a helper to turn a data structure into a tuple.
template <class T, class U>
struct loophole_type_list_lref;

template <typename T, std::size_t... I>
struct loophole_type_list_lref< T, std::index_sequence<I...> >
     // Instantiating loopholes:
    : sequence_tuple::tuple< decltype(T{ loophole_ubiq_lref<T, I>{}... }, 0) >
{
    using type = sequence_tuple::tuple< decltype(loophole(tag<T, I>{}))... >;
};


template <class T, class U>
struct loophole_type_list_rref;

template <typename T, std::size_t... I>
struct loophole_type_list_rref< T, std::index_sequence<I...> >
     // Instantiating loopholes:
    : sequence_tuple::tuple< decltype(T{ loophole_ubiq_rref<T, I>{}... }, 0) >
{
    using type = sequence_tuple::tuple< decltype(loophole(tag<T, I>{}))... >;
};


// Lazily returns loophole_type_list_{lr}ref.
template <bool IsCopyConstructible /*= true*/, class T, class U>
struct loophole_type_list_selector {
    using type = loophole_type_list_lref<T, U>;
};

template <class T, class U>
struct loophole_type_list_selector<false /*IsCopyConstructible*/, T, U> {
    using type = loophole_type_list_rref<T, U>;
};

template <class T>
auto tie_as_tuple_loophole_impl(T& lvalue) noexcept {
    using type = std::remove_cv_t<std::remove_reference_t<T>>;
    using indexes = detail::make_index_sequence<fields_count<type>()>;
    using loophole_type_list = typename detail::loophole_type_list_selector<
        std::is_copy_constructible<std::remove_all_extents_t<type>>::value, type, indexes
    >::type;
    using tuple_type = typename loophole_type_list::type;

    return boost::pfr::detail::make_flat_tuple_of_references(
        lvalue,
        offset_based_getter<type, tuple_type>{},
        size_t_<0>{},
        size_t_<tuple_type::size_v>{}
    );
}

template <class T>
auto tie_as_tuple(T& val) noexcept {
    static_assert(
        !std::is_union<T>::value,
        "====================> Boost.PFR: For safety reasons it is forbidden to reflect unions. See `Reflection of unions` section in the docs for more info."
    );
    return boost::pfr::detail::tie_as_tuple_loophole_impl(
        val
    );
}

template <class T, class F, std::size_t... I>
void for_each_field_dispatcher(T& t, F&& f, std::index_sequence<I...>) {
    static_assert(
        !std::is_union<T>::value,
        "====================> Boost.PFR: For safety reasons it is forbidden to reflect unions. See `Reflection of unions` section in the docs for more info."
    );
    std::forward<F>(f)(
        boost::pfr::detail::tie_as_tuple_loophole_impl(t)
    );
}

}}} // namespace boost::pfr::detail


#ifdef __clang__
#   pragma clang diagnostic pop
#elif defined(__GNUC__)
#   pragma GCC diagnostic pop
#endif


#endif // BOOST_PFR_DETAIL_CORE14_LOOPHOLE_HPP


/* core14_loophole.hpp
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
*/