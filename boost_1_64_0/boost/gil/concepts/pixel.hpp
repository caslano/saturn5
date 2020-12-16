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
wp0Edj+BfXfrC56hMby1COuJwL7+4bPvMFgN2O0FdtXPH0GZh4GtF9jSZ3w9YbATwDYK7I/f/MizWGatOMWxJMR+cR1NtvDJFvPeuzjE1n3i0z9kWrCBMirCjb/y2b9jmd0t5n2nJcQ+UXjTIPO+NuZ9UaRl/90/8DqDnb5HzHu6wN570R2/x7TAQPNxgV1wyyX3J3bPmPckEd/xJz3vSoMdWxfznt8WYh+7efZbzMMlMe+HQuZfeiZupsxLY95DhMzTidd9ivX+kJj3itUh9pbas37Bei/EvLstDbF3nvv2swG23ytexnaG53rrHtsZsMPA7iMwthdgJ4DdV2BsZ8C8nc3DdQC7n8DYzoDVgPUIjO0M2ElgtxcY2xmwM8DWC4ztDFj7rpjXJbB88QE3G2wW2IdWhti1XZdczrRU0ZZEuH/eJdXN+ID9ORZi93zDm//McONoSy0htmbzM1/BcqnFvO8JmZe84KFPYDofF/NeJGRe8YBr3kSsHvN+LcJ945r9eoyse8XpGOeqlaom3/ijToOdUFhLiJ274si7DHbsihjejQyxyecfeJPB2mdj3pOFzL7tD7kPZQI7FhMyU+97qcFOPzXm/VFg7S/7xy8MtvvpMe81Qmb1nK9lDNbxDIyRAnvSebd7h8FOAqssCrFbe7/xboO1PScG2y0x6FL3vNVgs8+PeW8WMm++83kjLLMXxLz3i3APuWrppNGhT6ASPqfDrYIO/fzE779L7MVoZwI79+m/v4/BzgB7uMBYD8B241JXXGBT295+T+r6wO4nsOr+Gx9EmcBAJPaYH9/jkwZrfyn6n8Au+MgP1zO+lzaXeQTYnQX2zzsmr2X+moeDEb05Fgd2qcAe8oknvcdgh4E9VWBLd/34HIZ7ecz7zaIQu/97/ng51zLXxLx3xkLs8JqtLM/ia2CBXR1if/7qTePMOxrnp0W4N80+52Lm/T0x77IVIfaZc3+5husqOM5bKtK58VN/eaDBTgP7gpB55fJ7H2M9fCLmXSzC7Tr45+sNVgP2eIF9Y8t7P6wx3JHAOC9kdv4k9ieGQwYOiHDJtovux3CfsdN5/dOmTjItwFApYTprv/4AZQKbFdjlf7v2aZR5A/QQgR3fe+RSliewu4p0fjB5lxNsL5+Nef0i3Nt+8cTfMi2fi3m/F9jO9ie0UubnY963BfbV685+xWCzN8a8oojvXcdX9rFNfDHmjYlw3zv1vbDfApsV4V5Z37Ka9X4Su4Ai3Na/tVzHvH855j1GhPtc5tqfs03cFPOuEO3zzW976LeYlq/HvJcKmd/+9aFJ9ltgS4TMLz/lPc/XWKCL/DrmbdZh29R5jCXHoc36u6neLfcO/nXoHsrWf9fFnvhJXfqoyVploj45g3v2wT/r4w8YnqmOjz5g40UbL+rY84D99c6OjRcTO7B18wOCJwYe4G9yGxyY+uO/BHARPBHelqLxY3SwC1u8B+t1uNLonvXojY8K0Ht5V0NzUj9XI//3vO3zjadlbqt8Q7Sdb8y1LdQhb6/q++S5b/VB1PCj9LndNXf6r+QbmxS3Vb4h2sn34Ve20E5wB/XEVd/ZG30QOc0pglrn4L/n3ub5xhbQbZRtI5lrl1e1eAO675+nzlE8+H4Y8wPPTRmsTYwf+fbbPM/YULut+jZEu31795EWruPvqGwDr+iJB+g9vE/q1r57EiPcbZ5vuEW9jbJtJHM8G1nEtZMy1D3/gT+D3hOcaLoG41zwRsN/o1/vG7nN+jVEu/3am1zkDet8K12y5/v3+HOA3t177t10vtf8N9r4VL18G2XbSGb7vmYRdTKlNB769PWf9kFY7k5vCP517B7/jbqu4+jKbZRpJdo=
*/