//
// Copyright 2005-2007 Adobe Systems Incorporated
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_CONCEPTS_COLOR_BASE_HPP
#define BOOST_GIL_CONCEPTS_COLOR_BASE_HPP

#include <boost/gil/concepts/basic.hpp>
#include <boost/gil/concepts/color.hpp>
#include <boost/gil/concepts/concept_check.hpp>
#include <boost/gil/concepts/fwd.hpp>

#include <boost/core/ignore_unused.hpp>
#include <type_traits>

#if defined(BOOST_CLANG)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunknown-pragmas"
#pragma clang diagnostic ignored "-Wunused-local-typedefs"
#endif

#if defined(BOOST_GCC) && (BOOST_GCC >= 40900)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#endif

namespace boost { namespace gil {

// Forward declarations of at_c
namespace detail {

template <typename Element, typename Layout, int K>
struct homogeneous_color_base;

} // namespace detail

template <int K, typename E, typename L, int N>
auto at_c(detail::homogeneous_color_base<E, L, N>& p)
    -> typename std::add_lvalue_reference<E>::type;

template <int K, typename E, typename L, int N>
auto at_c(detail::homogeneous_color_base<E, L, N> const& p)
    -> typename std::add_lvalue_reference<typename std::add_const<E>::type>::type;

template <typename P, typename C, typename L>
struct packed_pixel;

template <int K, typename P, typename C, typename L>
auto at_c(packed_pixel<P, C, L>& p)
    -> typename kth_element_reference_type<packed_pixel<P, C, L>, K>::type;

template <int K, typename P, typename C, typename L>
auto at_c(packed_pixel<P, C, L> const& p)
    -> typename kth_element_const_reference_type<packed_pixel<P, C, L>, K>::type;

template <typename B, typename C, typename L, bool M>
struct bit_aligned_pixel_reference;

template <int K, typename B, typename C, typename L, bool M>
inline auto at_c(bit_aligned_pixel_reference<B, C, L, M> const& p)
    -> typename kth_element_reference_type
        <
            bit_aligned_pixel_reference<B, C, L, M>,
            K
        >::type;

// Forward declarations of semantic_at_c
template <int K, typename ColorBase>
auto semantic_at_c(ColorBase& p)
    -> typename std::enable_if
        <
            !std::is_const<ColorBase>::value,
            typename kth_semantic_element_reference_type<ColorBase, K>::type
        >::type;

template <int K, typename ColorBase>
auto semantic_at_c(ColorBase const& p)
    -> typename kth_semantic_element_const_reference_type<ColorBase, K>::type;

/// \ingroup ColorBaseConcept
/// \brief A color base is a container of color elements (such as channels, channel references or channel pointers).
///
/// The most common use of color base is in the implementation of a pixel,
/// in which case the color elements are channel values. The color base concept,
/// however, can be used in other scenarios. For example, a planar pixel has
/// channels that are not contiguous in memory. Its reference is a proxy class
/// that uses a color base whose elements are channel references. Its iterator
/// uses a color base whose elements are channel iterators.
///
/// A color base must have an associated layout (which consists of a color space,
/// as well as an ordering of the channels).
/// There are two ways to index the elements of a color base: A physical index
/// corresponds to the way they are ordered in memory, and a semantic index
/// corresponds to the way the elements are ordered in their color space.
/// For example, in the RGB color space the elements are ordered as
/// {red_t, green_t, blue_t}. For a color base with a BGR layout, the first element
/// in physical ordering is the blue element, whereas the first semantic element
/// is the red one.
/// Models of \p ColorBaseConcept are required to provide the \p at_c<K>(ColorBase)
/// function, which allows for accessing the elements based on their physical order.
/// GIL provides a \p semantic_at_c<K>(ColorBase) function (described later)
/// which can operate on any model of ColorBaseConcept and returns the corresponding
/// semantic element.
///
/// \code
/// concept ColorBaseConcept<typename T> : CopyConstructible<T>, EqualityComparable<T>
/// {
///     // a GIL layout (the color space and element permutation)
///     typename layout_t;
///
///     // The type of K-th element
///     template <int K>
///     struct kth_element_type;
///         where Metafunction<kth_element_type>;
///
///     // The result of at_c
///     template <int K>
///     struct kth_element_const_reference_type;
///         where Metafunction<kth_element_const_reference_type>;
///
///     template <int K>
///     kth_element_const_reference_type<T,K>::type at_c(T);
///
///     // Copy-constructible and equality comparable with other compatible color bases
///     template <ColorBaseConcept T2> where { ColorBasesCompatibleConcept<T,T2> }
///         T::T(T2);
///     template <ColorBaseConcept T2> where { ColorBasesCompatibleConcept<T,T2> }
///         bool operator==(const T&, const T2&);
///     template <ColorBaseConcept T2> where { ColorBasesCompatibleConcept<T,T2> }
///         bool operator!=(const T&, const T2&);
/// };
/// \endcode
template <typename ColorBase>
struct ColorBaseConcept
{
    void constraints()
    {
        gil_function_requires<CopyConstructible<ColorBase>>();
        gil_function_requires<EqualityComparable<ColorBase>>();

        using color_space_t = typename ColorBase::layout_t::color_space_t;
        gil_function_requires<ColorSpaceConcept<color_space_t>>();

        using channel_mapping_t = typename ColorBase::layout_t::channel_mapping_t;
        // TODO: channel_mapping_t must be an Boost.MP11-compatible random access sequence

        static const int num_elements = size<ColorBase>::value;

        using TN = typename kth_element_type<ColorBase, num_elements - 1>::type;
        using RN = typename kth_element_const_reference_type<ColorBase, num_elements - 1>::type;

        RN r = gil::at_c<num_elements - 1>(cb);
        boost::ignore_unused(r);

        // functions that work for every pixel (no need to require them)
        semantic_at_c<0>(cb);
        semantic_at_c<num_elements-1>(cb);
        // also static_max(cb), static_min(cb), static_fill(cb,value),
        // and all variations of static_for_each(), static_generate(), static_transform()
    }
    ColorBase cb;
};

/// \ingroup ColorBaseConcept
/// \brief Color base which allows for modifying its elements
/// \code
/// concept MutableColorBaseConcept<ColorBaseConcept T> : Assignable<T>, Swappable<T>
/// {
///     template <int K>
///     struct kth_element_reference_type; where Metafunction<kth_element_reference_type>;
///
///     template <int K>
///     kth_element_reference_type<kth_element_type<T,K>::type>::type at_c(T);
///
///     template <ColorBaseConcept T2> where { ColorBasesCompatibleConcept<T,T2> }
///         T& operator=(T&, const T2&);
/// };
/// \endcode
template <typename ColorBase>
struct MutableColorBaseConcept
{
    void constraints()
    {
        gil_function_requires<ColorBaseConcept<ColorBase>>();
        gil_function_requires<Assignable<ColorBase>>();
        gil_function_requires<Swappable<ColorBase>>();

        using R0 = typename kth_element_reference_type<ColorBase, 0>::type;

        R0 r = gil::at_c<0>(cb);
        gil::at_c<0>(cb) = r;
    }
    ColorBase cb;
};

/// \ingroup ColorBaseConcept
/// \brief Color base that also has a default-constructor. Refines Regular
/// \code
/// concept ColorBaseValueConcept<typename T> : MutableColorBaseConcept<T>, Regular<T>
/// {
/// };
/// \endcode
template <typename ColorBase>
struct ColorBaseValueConcept
{
    void constraints()
    {
        gil_function_requires<MutableColorBaseConcept<ColorBase>>();
        gil_function_requires<Regular<ColorBase>>();
    }
};

/// \ingroup ColorBaseConcept
/// \brief Color base whose elements all have the same type
/// \code
/// concept HomogeneousColorBaseConcept<ColorBaseConcept CB>
/// {
///     // For all K in [0 ... size<C1>::value-1):
///     //     where SameType<kth_element_type<CB,K>::type, kth_element_type<CB,K+1>::type>;
///     kth_element_const_reference_type<CB,0>::type dynamic_at_c(CB const&, std::size_t n) const;
/// };
/// \endcode
template <typename ColorBase>
struct HomogeneousColorBaseConcept
{
    void constraints()
    {
        gil_function_requires<ColorBaseConcept<ColorBase>>();

        static const int num_elements = size<ColorBase>::value;

        using T0 = typename kth_element_type<ColorBase, 0>::type;
        using TN = typename kth_element_type<ColorBase, num_elements - 1>::type;

        static_assert(std::is_same<T0, TN>::value, "");   // better than nothing

        using R0 = typename kth_element_const_reference_type<ColorBase, 0>::type;
        R0 r = dynamic_at_c(cb, 0);
        boost::ignore_unused(r);
    }
    ColorBase cb;
};

/// \ingroup ColorBaseConcept
/// \brief Homogeneous color base that allows for modifying its elements
/// \code
/// concept MutableHomogeneousColorBaseConcept<ColorBaseConcept CB>
///     : HomogeneousColorBaseConcept<CB>
/// {
///     kth_element_reference_type<CB, 0>::type dynamic_at_c(CB&, std::size_t n);
/// };
/// \endcode
template <typename ColorBase>
struct MutableHomogeneousColorBaseConcept
{
    void constraints()
    {
        gil_function_requires<ColorBaseConcept<ColorBase>>();
        gil_function_requires<HomogeneousColorBaseConcept<ColorBase>>();
        using R0 = typename kth_element_reference_type<ColorBase, 0>::type;
        R0 r = dynamic_at_c(cb, 0);
        boost::ignore_unused(r);
        dynamic_at_c(cb, 0) = dynamic_at_c(cb, 0);
    }
    ColorBase cb;
};

/// \ingroup ColorBaseConcept
/// \brief Homogeneous color base that also has a default constructor.
/// Refines Regular.
///
/// \code
/// concept HomogeneousColorBaseValueConcept<typename T>
///     : MutableHomogeneousColorBaseConcept<T>, Regular<T>
/// {
/// };
/// \endcode
template <typename ColorBase>
struct HomogeneousColorBaseValueConcept
{
    void constraints()
    {
        gil_function_requires<MutableHomogeneousColorBaseConcept<ColorBase>>();
        gil_function_requires<Regular<ColorBase>>();
    }
};

/// \ingroup ColorBaseConcept
/// \brief Two color bases are compatible if they have the same color space and their elements are compatible, semantic-pairwise.
/// \code
/// concept ColorBasesCompatibleConcept<ColorBaseConcept C1, ColorBaseConcept C2>
/// {
///     where SameType<C1::layout_t::color_space_t, C2::layout_t::color_space_t>;
///     // also, for all K in [0 ... size<C1>::value):
///     //     where Convertible<kth_semantic_element_type<C1,K>::type, kth_semantic_element_type<C2,K>::type>;
///     //     where Convertible<kth_semantic_element_type<C2,K>::type, kth_semantic_element_type<C1,K>::type>;
/// };
/// \endcode
template <typename ColorBase1, typename ColorBase2>
struct ColorBasesCompatibleConcept
{
    void constraints()
    {
        static_assert(std::is_same
            <
                typename ColorBase1::layout_t::color_space_t,
                typename ColorBase2::layout_t::color_space_t
            >::value, "");

//        using e1 = typename kth_semantic_element_type<ColorBase1,0>::type;
//        using e2 = typename kth_semantic_element_type<ColorBase2,0>::type;
//        "e1 is convertible to e2"
    }
};

}} // namespace boost::gil

#if defined(BOOST_CLANG)
#pragma clang diagnostic pop
#endif

#if defined(BOOST_GCC) && (BOOST_GCC >= 40900)
#pragma GCC diagnostic pop
#endif

#endif

/* color_base.hpp
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
*/