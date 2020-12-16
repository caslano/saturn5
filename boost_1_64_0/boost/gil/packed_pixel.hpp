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
S5jaOVVWwxiq7mG//TW+X3JpL17ocJ5xGGfqmUWBDTzOYFTM+De1R43Reo/+/sjH0/fobJWRtfYJ9F3rIMIcYUy1EaN7cIC+O++T8ftoPhy3xhzEaTf1q2xL4RN9XNJFlOvXNI+sKWHJMKevThyd5ZCJscBq18cEBzaF6hhYl94Rxnx2Cct4m81TFYSx60YF5sw5jlsY21aMbzlocJ9tclbiNN+hZwuZs22MOJ61M63jBYsD7YUOE+OEOetkWv6tAnftFd7HaEgOzU9I0YfoeneIOEuvdbHOJyUfHcPB+cNcbtsOG2xJu0HzlrE+xXV9gsN4x/xFC0d3INe0JwnrtkYky/7JxHW8DblfY7z7/QY7n0IczxrTbp0HmrPMtR+t3/4pDuddv78gcf+aD3PHp4nbfb2H471Fc521Hp5LzBDuW+eR9dbi+cf8I7OG4475iSZjS475N3l5NOZL+/mpxOu2NiTnU3PM9Y7DN1i4fxw+0iKOf82I82Bdm3hmvYj1eLnEaGyVebxlXuL+MfyEh0PjM+uw82nMoTFWjL+McT6YfvnphNH6k0z/+gXC/GtPkEH6MY/sApG+3mcQhsMUk201tOMJpHhOh+9UFoIDsfz9kvmOCtHA73QG5Zn4Ls603ZW+DzxLfZd+dvAlJ+y9MRZ5686N4u/ZsVbTuFphOm64i892uDAlzNG4mPsQ4p55jsNdgK/B03a4dNbxbc8lvnJgdrD28whrNuamJ1G7n2bSvP4IYfHNkXxe5rrnq+/xulJ7gdeNGN/0AgvHXEStyZg4jzJOmAj7V8KcPWoOu/oGwsVa02adLy8E5txXQMs+zNn2Ig+H77+jsvZy+GwF87a9GLxu9yhIeREPVZld0YoZvrpApL1wlHhw+VA6IU7rvqr3Shz6yHzpfYnAIFtiz7YwHKMR2K0So0NVD9HhXqqxweFQvVM9nE0PI43q11wxyLr630r8bvc7NF/WiZMIzqtfeTicFTKvXu7hIUu4LnhwSjpzMq/o5FAWcLu8iTjxqXz25uHikzqNvJK4tns/x3e+A+eksYydr+rkIFks472dOKvCMo51cNCKjIybOnBKtkjL8Kslh9XkenNS4lQZuX94jcBYPVGPJU6lorEtrxUYqaXrxgmNqeav+sf4jl867mbKrPA6L49TIevAyS5cpIjlbX29n4OUddTfM34upUTs+bwBPNeHW94HoHHat8Cx5bl6Y2wsNvWx5oA5w2EhL/NG8D1+1botf82P11ND2STelKincfgvVxV7iG8C3+9fzZzVbwbH72fOnDZxPL7KXOaXmKMyTbUZ0Xe+hTBr/6AeXxEsz8W/lXhRiURzPTpvJ9ZBmHOY50Q4VP4MpIvj2/82cLz3YqjnqxeQnyRL8ZZxfwbf1/B2D7+F6TOdJ+f9rHdYPFx6EhPYdnsn4SIzVJ5K+27dceLEB31lXnCeH2MOQMpNbQM9+13AyO9cpmGRvnvf2Zbr4O8mHip/c2p0jDQETrYO4zyTQa0iXIV/j4NTeG379b4XuOMzr9vz2fcRFp8wopV8nCASNv3U+8FZ0j9frCF6uMwSMvd/ALylzwdw/pw13KY6SAP7Ho3c4CMnCKfJtmK0xb1CEx8ETvcKaVvtYvwNJlHcJelyznyIv0+Pqzolzj3MRWcisXYeBaGCbKnaYDgL4PAZ07g+RbeQz4ozPM+1OFB3YbItzzb+/YLnPuH5mfrszBidEaf7YH9CZ1XjMUmZdvUNhN2qz6oiGdhyHNVhjv1Ef0db6O/fKe9rfbfEdm3vl9gJxsbVSfqDY8D43XoLa4w3diiC0eUU43NjiHBch/uc/F6fwCsISlkT51nGMacZjWROa+wbImw=
*/