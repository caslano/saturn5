//
// Copyright 2005-2007 Adobe Systems Incorporated
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_PACKED_PIXEL_HPP
#define BOOST_GIL_PACKED_PIXEL_HPP

#include <boost/gil/pixel.hpp>
#include <boost/gil/detail/mp11.hpp>

#include <functional>
#include <type_traits>

namespace boost { namespace gil {

/// A model of a heterogeneous pixel whose channels are bit ranges.
/// For example 16-bit RGB in '565' format.

/// \defgroup ColorBaseModelPackedPixel packed_pixel
/// \ingroup ColorBaseModel
/// \brief A heterogeneous color base whose elements are reference proxies to channels in a pixel. Models ColorBaseValueConcept. This class is used to model packed pixels, such as 16-bit packed RGB.

/// \defgroup PixelModelPackedPixel packed_pixel
/// \ingroup PixelModel
/// \brief A heterogeneous pixel used to represent packed pixels with non-byte-aligned channels. Models PixelValueConcept
///
/// Example:
/// \code
/// using rgb565_pixel_t = packed_pixel_type<uint16_t, mp11::mp_list-c<unsigned,5,6,5>, rgb_layout_t>::type;
/// static_assert(sizeof(rgb565_pixel_t) == 2, "");
///
/// rgb565_pixel_t r565;
/// get_color(r565,red_t())   = 31;
/// get_color(r565,green_t()) = 63;
/// get_color(r565,blue_t())  = 31;
/// assert(r565 == rgb565_pixel_t((uint16_t)0xFFFF));
/// \endcode

/// \ingroup ColorBaseModelPackedPixel PixelModelPackedPixel PixelBasedModel
/// \brief Heterogeneous pixel value whose channel references can be constructed from the pixel bitfield and their index. Models ColorBaseValueConcept, PixelValueConcept, PixelBasedConcept
/// Typical use for this is a model of a packed pixel (like 565 RGB)
/// \tparam BitField Type that holds the bits of the pixel. Typically an integral type, like std::uint16_t.
/// \tparam ChannelRefs MP11 list whose elements are packed channels. They must be constructible from BitField. GIL uses packed_channel_reference
/// \tparam Layout defining the color space and ordering of the channels. Example value: rgb_layout_t
template <typename BitField, typename ChannelRefs, typename Layout>
struct packed_pixel
{
    BitField _bitfield{0}; // TODO: Make private

    using layout_t = Layout;
    using value_type = packed_pixel<BitField, ChannelRefs, Layout>;
    using reference = value_type&;
    using const_reference = value_type const&;

    static constexpr bool is_mutable =
        channel_traits<mp11::mp_front<ChannelRefs>>::is_mutable;

    packed_pixel() = default;
    explicit packed_pixel(const BitField& bitfield) : _bitfield(bitfield) {}

    // Construct from another compatible pixel type
    packed_pixel(const packed_pixel& p) : _bitfield(p._bitfield) {}

    template <typename Pixel>
    packed_pixel(Pixel const& p,
        typename std::enable_if<is_pixel<Pixel>::value>::type* /*dummy*/ = nullptr)
    {
        check_compatible<Pixel>();
        static_copy(p, *this);
    }

    packed_pixel(int chan0, int chan1)
        : _bitfield(0)
    {
        static_assert(num_channels<packed_pixel>::value == 2, "");
        gil::at_c<0>(*this) = chan0;
        gil::at_c<1>(*this) = chan1;
    }

    packed_pixel(int chan0, int chan1, int chan2)
        : _bitfield(0)
    {
        static_assert(num_channels<packed_pixel>::value == 3, "");
        gil::at_c<0>(*this) = chan0;
        gil::at_c<1>(*this) = chan1;
        gil::at_c<2>(*this) = chan2;
    }

    packed_pixel(int chan0, int chan1, int chan2, int chan3)
        : _bitfield(0)
    {
        static_assert(num_channels<packed_pixel>::value == 4, "");
        gil::at_c<0>(*this) = chan0;
        gil::at_c<1>(*this) = chan1;
        gil::at_c<2>(*this) = chan2;
        gil::at_c<3>(*this) = chan3;
    }

    packed_pixel(int chan0, int chan1, int chan2, int chan3, int chan4)
        : _bitfield(0)
    {
        static_assert(num_channels<packed_pixel>::value == 5, "");
        gil::at_c<0>(*this) = chan0;
        gil::at_c<1>(*this) = chan1;
        gil::at_c<2>(*this) = chan2;
        gil::at_c<3>(*this) = chan3;
        gil::at_c<4>(*this) = chan4;
    }

    auto operator=(packed_pixel const& p) -> packed_pixel&
    {
        _bitfield = p._bitfield;
        return *this;
    }

    template <typename Pixel>
    auto operator=(Pixel const& p) -> packed_pixel&
    {
        assign(p, is_pixel<Pixel>());
        return *this;
    }

    template <typename Pixel>
    bool operator==(Pixel const& p) const
    {
        return equal(p, is_pixel<Pixel>());
    }

    template <typename Pixel>
    bool operator!=(Pixel const& p) const { return !(*this==p); }

private:
    template <typename Pixel>
    static void check_compatible()
    {
        gil_function_requires<PixelsCompatibleConcept<Pixel, packed_pixel>>();
    }

    template <typename Pixel>
    void assign(Pixel const& p, std::true_type)
    {
        check_compatible<Pixel>();
        static_copy(p, *this);
    }

    template <typename Pixel>
    bool  equal(Pixel const& p, std::true_type) const
    {
        check_compatible<Pixel>();
        return static_equal(*this, p);
    }

    // Support for assignment/equality comparison of a channel with a grayscale pixel
    static void check_gray()
    {
        static_assert(std::is_same<typename Layout::color_space_t, gray_t>::value, "");
    }

    template <typename Channel>
    void assign(Channel const& channel, std::false_type)
    {
        check_gray();
        gil::at_c<0>(*this) = channel;
    }

    template <typename Channel>
    bool equal (Channel const& channel, std::false_type) const
    {
        check_gray();
        return gil::at_c<0>(*this) == channel;
    }

public:
    auto operator=(int channel) -> packed_pixel&
    {
        check_gray();
        gil::at_c<0>(*this) = channel;
        return *this;
    }

    bool operator==(int channel) const
    {
        check_gray();
        return gil::at_c<0>(*this) == channel;
    }
};

/////////////////////////////
//  ColorBasedConcept
/////////////////////////////

template <typename BitField, typename ChannelRefs, typename Layout, int K>
struct kth_element_type<packed_pixel<BitField, ChannelRefs, Layout>, K>
{
    using type = typename channel_traits<mp11::mp_at_c<ChannelRefs, K>>::value_type;
};

template <typename BitField, typename ChannelRefs, typename Layout, int K>
struct kth_element_reference_type<packed_pixel<BitField, ChannelRefs, Layout>, K>
{
    using type = typename channel_traits<mp11::mp_at_c<ChannelRefs, K>>::reference;
};

template <typename BitField, typename ChannelRefs, typename Layout, int K>
struct kth_element_const_reference_type<packed_pixel<BitField, ChannelRefs, Layout>, K>
{
    using type = typename channel_traits<mp11::mp_at_c<ChannelRefs, K>>::const_reference;
};

template <int K, typename P, typename C, typename L>
inline
auto at_c(packed_pixel<P, C, L>& p)
    -> typename kth_element_reference_type<packed_pixel<P, C, L>, K>::type
{
    return typename kth_element_reference_type
        <
            packed_pixel<P, C, L>,
            K
        >::type{&p._bitfield};
}

template <int K, typename P, typename C, typename L>
inline
auto at_c(const packed_pixel<P, C, L>& p)
    -> typename kth_element_const_reference_type<packed_pixel<P, C, L>, K>::type
{
    return typename kth_element_const_reference_type
        <
            packed_pixel<P, C, L>,
        K>::type{&p._bitfield};
}

/////////////////////////////
//  PixelConcept
/////////////////////////////

// Metafunction predicate that flags packed_pixel as a model of PixelConcept.
// Required by PixelConcept
template <typename BitField, typename ChannelRefs, typename Layout>
struct is_pixel<packed_pixel<BitField, ChannelRefs, Layout>> : std::true_type {};

/////////////////////////////
//  PixelBasedConcept
/////////////////////////////

template <typename P, typename C, typename Layout>
struct color_space_type<packed_pixel<P, C, Layout>>
{
    using type = typename Layout::color_space_t;
};

template <typename P, typename C, typename Layout>
struct channel_mapping_type<packed_pixel<P, C, Layout>>
{
    using type = typename Layout::channel_mapping_t;
};

template <typename P, typename C, typename Layout>
struct is_planar<packed_pixel<P, C, Layout>> : std::false_type {};

////////////////////////////////////////////////////////////////////////////////
/// Support for interleaved iterators over packed pixel
////////////////////////////////////////////////////////////////////////////////

/// \defgroup PixelIteratorModelPackedInterleavedPtr Pointer to packed_pixel<P,CR,Layout>
/// \ingroup PixelIteratorModel
/// \brief Iterators over interleaved pixels.
/// The pointer packed_pixel<P,CR,Layout>* is used as an iterator over interleaved
/// pixels of packed format.
/// Models PixelIteratorConcept, HasDynamicXStepTypeConcept, MemoryBasedIteratorConcept

template <typename P, typename C, typename L>
struct iterator_is_mutable<packed_pixel<P, C, L>*>
    : std::integral_constant<bool, packed_pixel<P, C, L>::is_mutable>
{};

template <typename P, typename C, typename L>
struct iterator_is_mutable<const packed_pixel<P, C, L>*> : std::false_type {};

}}  // namespace boost::gil

#endif

/* packed_pixel.hpp
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
*/