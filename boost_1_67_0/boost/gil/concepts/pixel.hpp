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