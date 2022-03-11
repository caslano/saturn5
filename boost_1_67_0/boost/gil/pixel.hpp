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