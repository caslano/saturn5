//
// Copyright 2005-2007 Adobe Systems Incorporated
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_CONCEPTS_PIXEL_HPP
#define BOOST_GIL_CONCEPTS_PIXEL_HPP

#include <boost/gil/concepts/basic.hpp>
#include <boost/gil/concepts/channel.hpp>
#include <boost/gil/concepts/color.hpp>
#include <boost/gil/concepts/color_base.hpp>
#include <boost/gil/concepts/concept_check.hpp>
#include <boost/gil/concepts/fwd.hpp>
#include <boost/gil/concepts/pixel_based.hpp>
#include <boost/gil/concepts/detail/type_traits.hpp>
#include <boost/gil/detail/mp11.hpp>

#include <cstddef>
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

/// \brief Pixel concept - A color base whose elements are channels
/// \ingroup PixelConcept
/// \code
/// concept PixelConcept<typename P> : ColorBaseConcept<P>, PixelBasedConcept<P>
/// {
///     where is_pixel<P>::value == true;
///     // where for each K [0..size<P>::value - 1]:
///     //      ChannelConcept<kth_element_type<P, K>>;
///
///     typename P::value_type;
///         where PixelValueConcept<value_type>;
///     typename P::reference;
///         where PixelConcept<reference>;
///     typename P::const_reference;
///         where PixelConcept<const_reference>;
///     static const bool P::is_mutable;
///
///     template <PixelConcept P2> where { PixelConcept<P, P2> }
///         P::P(P2);
///     template <PixelConcept P2> where { PixelConcept<P, P2> }
///         bool operator==(const P&, const P2&);
///     template <PixelConcept P2> where { PixelConcept<P, P2> }
///         bool operator!=(const P&, const P2&);
/// };
/// \endcode
template <typename P>
struct PixelConcept
{
    void constraints()
    {
        gil_function_requires<ColorBaseConcept<P>>();
        gil_function_requires<PixelBasedConcept<P>>();

        static_assert(is_pixel<P>::value, "");
        static const bool is_mutable = P::is_mutable;
        ignore_unused_variable_warning(is_mutable);

        using value_type = typename P::value_type;
        // TODO: Is the cyclic dependency intentional? --mloskot
        // gil_function_requires<PixelValueConcept<value_type>>();

        using reference = typename P::reference;
        gil_function_requires<PixelConcept
            <
                typename detail::remove_const_and_reference<reference>::type
            >>();

        using const_reference = typename P::const_reference;
        gil_function_requires<PixelConcept
            <
                typename detail::remove_const_and_reference<const_reference>::type
            >>();
    }
};

/// \brief Pixel concept that allows for changing its channels
/// \ingroup PixelConcept
/// \code
/// concept MutablePixelConcept<PixelConcept P> : MutableColorBaseConcept<P>
/// {
///     where is_mutable==true;
/// };
/// \endcode
template <typename P>
struct MutablePixelConcept
{
    void constraints()
    {
        gil_function_requires<PixelConcept<P>>();
        static_assert(P::is_mutable, "");
    }
};

/// \brief Homogeneous pixel concept
/// \ingroup PixelConcept
/// \code
/// concept HomogeneousPixelConcept<PixelConcept P>
///     : HomogeneousColorBaseConcept<P>, HomogeneousPixelBasedConcept<P>
/// {
///     P::template element_const_reference_type<P>::type operator[](P p, std::size_t i) const
///     {
///         return dynamic_at_c(p,i);
/// }
/// };
/// \endcode
template <typename P>
struct HomogeneousPixelConcept
{
    void constraints()
    {
        gil_function_requires<PixelConcept<P>>();
        gil_function_requires<HomogeneousColorBaseConcept<P>>();
        gil_function_requires<HomogeneousPixelBasedConcept<P>>();
        p[0];
    }
    P p;
};

/// \brief Homogeneous pixel concept that allows for changing its channels
/// \ingroup PixelConcept
/// \code
/// concept MutableHomogeneousPixelConcept<HomogeneousPixelConcept P>
///     : MutableHomogeneousColorBaseConcept<P>
/// {
///     P::template element_reference_type<P>::type operator[](P p, std::size_t i)
///     {
///         return dynamic_at_c(p, i);
///     }
/// };
/// \endcode
template <typename P>
struct MutableHomogeneousPixelConcept
{
    void constraints()
    {
        gil_function_requires<HomogeneousPixelConcept<P>>();
        gil_function_requires<MutableHomogeneousColorBaseConcept<P>>();
        p[0] = v;
        v = p[0];
    }
    typename P::template element_type<P>::type v;
    P p;
};

/// \brief Pixel concept that is a Regular type
/// \ingroup PixelConcept
/// \code
/// concept PixelValueConcept<PixelConcept P> : Regular<P>
/// {
///     where SameType<value_type,P>;
/// };
/// \endcode
template <typename P>
struct PixelValueConcept
{
    void constraints()
    {
        gil_function_requires<PixelConcept<P>>();
        gil_function_requires<Regular<P>>();
    }
};

/// \brief Homogeneous pixel concept that is a Regular type
/// \ingroup PixelConcept
/// \code
/// concept HomogeneousPixelValueConcept<HomogeneousPixelConcept P> : Regular<P>
/// {
///     where SameType<value_type,P>;
/// };
/// \endcode
template <typename P>
struct HomogeneousPixelValueConcept
{
    void constraints()
    {
        gil_function_requires<HomogeneousPixelConcept<P>>();
        gil_function_requires<Regular<P>>();
        static_assert(std::is_same<P, typename P::value_type>::value, "");
    }
};

namespace detail {

template <typename P1, typename P2, int K>
struct channels_are_pairwise_compatible
    : mp11::mp_and
    <
        channels_are_pairwise_compatible<P1, P2, K - 1>,
        channels_are_compatible
        <
            typename kth_semantic_element_reference_type<P1, K>::type,
            typename kth_semantic_element_reference_type<P2, K>::type
        >
    >
{
};

template <typename P1, typename P2>
struct channels_are_pairwise_compatible<P1, P2, -1> : std::true_type {};

} // namespace detail

/// \ingroup PixelAlgorithm
/// \brief Returns whether two pixels are compatible
/// Pixels are compatible if their channels and color space types are compatible.
/// Compatible pixels can be assigned and copy constructed from one another.
/// \tparam P1 Models PixelConcept
/// \tparam P2 Models PixelConcept
template <typename P1, typename P2>
struct pixels_are_compatible
    : mp11::mp_and
        <
            typename color_spaces_are_compatible
            <
                typename color_space_type<P1>::type,
                typename color_space_type<P2>::type
            >::type,
            detail::channels_are_pairwise_compatible
            <
                P1, P2, num_channels<P1>::value - 1
            >
        >
{
};

/// \ingroup PixelConcept
/// \brief  Concept for pixel compatibility
/// Pixels are compatible if their channels and color space types are compatible.
/// Compatible pixels can be assigned and copy constructed from one another.
/// \tparam P1 Models PixelConcept
/// \tparam P2 Models PixelConcept
/// \code
/// concept PixelsCompatibleConcept<PixelConcept P1, PixelConcept P2>
///     : ColorBasesCompatibleConcept<P1,P2> {
///     // where for each K [0..size<P1>::value):
///     //    ChannelsCompatibleConcept<kth_semantic_element_type<P1,K>::type, kth_semantic_element_type<P2,K>::type>;
/// };
/// \endcode
template <typename P1, typename P2>
struct PixelsCompatibleConcept
{
    void constraints()
    {
        static_assert(pixels_are_compatible<P1, P2>::value, "");
    }
};

/// \ingroup PixelConcept
/// \brief Pixel convertible concept
/// Convertibility is non-symmetric and implies that one pixel
/// can be converted to another, approximating the color.
/// Conversion is explicit and sometimes lossy.
/// \code
/// template <PixelConcept SrcPixel, MutablePixelConcept DstPixel>
/// concept PixelConvertibleConcept
/// {
///     void color_convert(const SrcPixel&, DstPixel&);
/// };
/// \endcode
template <typename SrcP, typename DstP>
struct PixelConvertibleConcept
{
    void constraints()
    {
        gil_function_requires<PixelConcept<SrcP>>();
        gil_function_requires<MutablePixelConcept<DstP>>();
        color_convert(src, dst);
    }
    SrcP src;
    DstP dst;
};

}} // namespace boost::gil

#if defined(BOOST_CLANG)
#pragma clang diagnostic pop
#endif

#if defined(BOOST_GCC) && (BOOST_GCC >= 40900)
#pragma GCC diagnostic pop
#endif

#endif

/* pixel.hpp
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
*/