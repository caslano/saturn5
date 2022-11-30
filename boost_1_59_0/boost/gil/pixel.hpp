//
// Copyright 2005-2007 Adobe Systems Incorporated
// Copyright 2019 Mateusz Loskot <mateusz at loskot dot net>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_PIXEL_HPP
#define BOOST_GIL_PIXEL_HPP

#include <boost/gil/channel.hpp>
#include <boost/gil/color_base.hpp>
#include <boost/gil/color_base_algorithm.hpp>
#include <boost/gil/concepts.hpp>
#include <boost/gil/metafunctions.hpp>
#include <boost/gil/utilities.hpp>
#include <boost/gil/detail/mp11.hpp>

#include <functional>
#include <type_traits>

namespace boost { namespace gil {

// Forward-declare gray_t
struct gray_color_t;
using gray_t = mp11::mp_list<gray_color_t>;
template <typename PixelBased> struct color_space_type;
template <typename PixelBased> struct channel_mapping_type;
template <typename PixelBased> struct channel_type;
template <typename PixelBased> struct is_planar;

template <typename PixelBased>
struct color_space_type<PixelBased const> : color_space_type<PixelBased> {};

template <typename PixelBased>
struct channel_mapping_type<PixelBased const> : channel_mapping_type<PixelBased> {};

template <typename PixelBased>
struct channel_type<PixelBased const> : channel_type<PixelBased> {};

template <typename PixelBased>
struct is_planar : std::false_type {};

template <typename PixelBased>
struct is_planar<PixelBased const> : is_planar<PixelBased> {};

template <typename T> struct is_pixel : std::false_type {};
template <typename T> struct is_pixel<T const> : is_pixel<T> {};

/// \ingroup PixelBasedAlgorithm
/// \brief Returns the number of channels of a pixel-based GIL construct
template <typename PixelBased>
struct num_channels : mp11::mp_size<typename color_space_type<PixelBased>::type>::type {};

/**
\addtogroup PixelBasedAlgorithm

Example:
\code
static_assert(num_channels<rgb8_view_t>::value == 3, "");
static_assert(num_channels<cmyk16_planar_ptr_t>::value == 4, "");

static_assert(is_planar<rgb16_planar_image_t>::value));
static_assert(std::is_same<color_space_type<rgb8_planar_ref_t>::type, rgb_t>::value, "");
static_assert(std::is_same<channel_mapping_type<cmyk8_pixel_t>::type,
                             channel_mapping_type<rgba8_pixel_t>::type>::value, "");
static_assert(std::is_same<channel_type<bgr8_pixel_t>::type, uint8_t>::value, "");
\endcode
*/

/// \defgroup ColorBaseModelPixel pixel
/// \ingroup ColorBaseModel
/// \brief A homogeneous color base whose element is a channel value. Models HomogeneousColorBaseValueConcept

/// \defgroup PixelModelPixel pixel
/// \ingroup PixelModel
/// \brief A homogeneous pixel value. Models HomogeneousPixelValueConcept

/// \ingroup PixelModelPixel ColorBaseModelPixel PixelBasedModel
/// \brief Represents a pixel value (a container of channels). Models: HomogeneousColorBaseValueConcept, PixelValueConcept, HomogeneousPixelBasedConcept
///
/// A pixel is a set of channels defining the color at a given point in an image. Conceptually, a pixel is little more than a color base whose elements
/// model \p ChannelConcept. The class \p pixel defines a simple, homogeneous pixel value. It is used to store
/// the value of a color. The built-in C++ references to \p pixel, \p pixel& and \p const \p pixel& are used to represent a reference to a pixel
/// inside an interleaved image view (a view in which all channels are together in memory). Similarly, built-in pointer types \p pixel* and \p const \p pixel*
/// are used as the standard iterator over a row of interleaved homogeneous pixels.
///
/// Since \p pixel inherits the properties of color base, assigning, equality comparison and copy-construcion are allowed between compatible pixels.
/// This means that an 8-bit RGB pixel may be assigned to an 8-bit BGR pixel, or to an 8-bit planar reference. The channels are properly paired semantically.
///
/// The single-channel (grayscale) instantiation of the class pixel, (i.e. \p pixel<T,gray_layout_t>) is also convertible to/from a channel value.
/// This allows grayscale pixels to be used in simpler expressions like *gray_pix1 = *gray_pix2  instead of more complicated at_c<0>(gray_pix1) = at_c<0>(gray_pix2)
/// or get_color<gray_color_t>(gray_pix1) = get_color<gray_color_t>(gray_pix2)
///
/// \tparam ChannelValue TODO
/// \tparam Layout mp11::make_integer_sequence<int, ColorSpace::size>
template <typename ChannelValue, typename Layout>
struct pixel :
    detail::homogeneous_color_base
    <
        ChannelValue,
        Layout,
        mp11::mp_size<typename Layout::color_space_t>::value
    >
{
private:
    using channel_t = ChannelValue;
    using parent_t = detail::homogeneous_color_base
        <
            ChannelValue,
            Layout,
            mp11::mp_size<typename Layout::color_space_t>::value
        >;
public:
    using value_type = pixel<ChannelValue, Layout>;
    using reference = value_type&;
    using const_reference = value_type const&;
    static constexpr bool is_mutable = channel_traits<channel_t>::is_mutable;

    pixel() = default;
    explicit pixel(channel_t v) : parent_t(v) {}  // sets all channels to v
    pixel(channel_t v0, channel_t v1) : parent_t(v0, v1) {}
    pixel(channel_t v0, channel_t v1, channel_t v2) : parent_t(v0, v1, v2) {}

    pixel(channel_t v0, channel_t v1, channel_t v2, channel_t v3)
        : parent_t(v0, v1, v2, v3)
    {}

    pixel(channel_t v0, channel_t v1, channel_t v2, channel_t v3, channel_t v4)
        : parent_t(v0, v1, v2, v3, v4)
    {}

    pixel(channel_t v0, channel_t v1, channel_t v2, channel_t v3, channel_t v4, channel_t v5)
        : parent_t(v0, v1, v2, v3, v4, v5)
    {}

    pixel(const pixel& p) : parent_t(p) {}

    pixel& operator=(pixel const& p)
    {
        static_copy(p,*this);
        return *this;
    }

    // Construct from another compatible pixel type
    template <typename Pixel>
    pixel(Pixel const& p,
        typename std::enable_if<is_pixel<Pixel>::value>::type* /*dummy*/ = nullptr)
        : parent_t(p)
    {
        check_compatible<Pixel>();
    }

    template <typename Pixel>
    pixel& operator=(Pixel const& p)
    {
        assign(p, is_pixel<Pixel>());
        return *this;
    }

    template <typename Pixel>
    bool operator==(Pixel const& p) const { return equal(p, is_pixel<Pixel>()); }

    template <typename Pixel>
    bool operator!=(Pixel const& p) const { return !(*this == p); }

    // homogeneous pixels have operator[]
    auto operator[](std::size_t index)
        -> typename channel_traits<channel_t>::reference
    {
        return dynamic_at_c(*this, index);
    }

    auto operator[](std::size_t index) const
        -> typename channel_traits<channel_t>::const_reference
    {
        return dynamic_at_c(*this, index);
    }

private:
    template <typename Pixel>
    void assign(Pixel const& p, std::true_type)
    {
        check_compatible<Pixel>();
        static_copy(p, *this);
    }

    template <typename Pixel>
    bool equal(Pixel const& p, std::true_type) const
    {
        check_compatible<Pixel>();
        return static_equal(*this, p);
    }

    template <typename Pixel>
    void check_compatible() const
    {
        gil_function_requires<PixelsCompatibleConcept<Pixel, pixel>>();
    }

// Support for assignment/equality comparison of a channel with a grayscale pixel

private:
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
    pixel& operator= (channel_t channel)
    {
        check_gray();
        gil::at_c<0>(*this) = channel;
        return *this;
    }

    bool operator==(channel_t channel) const
    {
        check_gray();
        return gil::at_c<0>(*this) == channel;
    }
};

/////////////////////////////
//  ColorBasedConcept
/////////////////////////////

template <typename ChannelValue, typename Layout, int K>
struct kth_element_type<pixel<ChannelValue,Layout>, K>
{
    using type = ChannelValue;
};

template <typename ChannelValue, typename Layout, int K>
struct kth_element_reference_type<pixel<ChannelValue,Layout>, K>
{
    using type = typename channel_traits<ChannelValue>::reference;
};

template <typename ChannelValue, typename Layout, int K>
struct kth_element_reference_type<const pixel<ChannelValue,Layout>, K>
{
    using type = typename channel_traits<ChannelValue>::const_reference;
};

template <typename ChannelValue, typename Layout, int K>
struct kth_element_const_reference_type<pixel<ChannelValue,Layout>, K>
{
    using type = typename channel_traits<ChannelValue>::const_reference;
};

/////////////////////////////
//  PixelConcept
/////////////////////////////

template <typename ChannelValue, typename Layout>
struct is_pixel<pixel<ChannelValue,Layout>> : std::true_type {};

/////////////////////////////
//  HomogeneousPixelBasedConcept
/////////////////////////////

template <typename ChannelValue, typename Layout>
struct color_space_type<pixel<ChannelValue, Layout>>
{
    using type = typename Layout::color_space_t;
};

template <typename ChannelValue, typename Layout>
struct channel_mapping_type<pixel<ChannelValue, Layout>>
{
    using type = typename Layout::channel_mapping_t;
};

template <typename ChannelValue, typename Layout>
struct is_planar<pixel<ChannelValue, Layout>> : std::false_type {};

template <typename ChannelValue, typename Layout>
struct channel_type<pixel<ChannelValue, Layout>>
{
    using type = ChannelValue;
};

}}  // namespace boost::gil

#endif

/* pixel.hpp
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
*/