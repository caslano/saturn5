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