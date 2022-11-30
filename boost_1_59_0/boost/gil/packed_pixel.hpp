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
iDPFxvCl+6Vj0nmg82dSYUgpVh4FPrZSzqAURewPU+oqVdXm4Ik1tDjtrqbozfUp+nnwsMf6az2ZkdsoZZQFI1tjbDEOGleMNmYmS7BaomX2vUNvZ05VWWCXHvB6S8lr4smmYl+yXlwKLguXk5O4QK4W146bwK3ktnHpoalL+ZQ0GzBMNdqdrkQbfqU36FP6J80oNIZth8KenwGp5gN2PiFlBf6qKcfJPVHf1dC69EoRpQzweT2lszIQbHsG7Pao8yTVTeWjckh9qspapDYI3v+EfRdKr6C3dZ5T2azvANM5pj/Vq6LftxpHDR/4qFzw+va8MFcbcpPChACFBZMqwDJNYYfTyRKyjewhh4AzH5APxAc9J7DBbBjbmG3NdmH7ou92sadZXy4rVwSINwT4M46bCZa+gdvNHQKWWOWMgCSj6WCR4WCovmIp5x7XRNjVB6kYbKqWnErxQwSupbRSOik/KcOVZUpDNUIdD8+jaLu0q9pbLZNeQBf0HvpUvZnRz3hnJDXzm13M/FYFeJL+1jp7nu1xb+fZlyJkLNkIbvAM8SY7W4ytBdQxkF3NZgcit6PMOG4+p/HV+Xe8TEfQg/QcfUd9oEFthL7gj5sQO9KJueAhaojDxG3iH+J7MbPUVlovXZCeSMXlRnJveZLsrxhKI6UFajtO2a7Eqw+hOam0YG2kdlZ7pwXrg/R1zjNBxYww45NRxmxhbjazwvMpVmOrnTXBYq55O3zGH9Lugzh5i5yA/pcBUugNxP4LkGJqmoGWol3pTHoKeNEe3T7q3IcoAm/fUGwLX79CvCX6AiUskM44LNeSq4LnfpB9FKJEK15qLXjvHvBBKmy9jFEJUhtkDAOHG4c4Nc2YZSwH039ppDYrIsrPBXpx7nM+dfmkNKQMaUTmkyPkCrS5N5uEy8+V5arDIs9wt7hc8LaTgMbzoke70wl0Na0Jn7BbOCUkAWodIi4UT4ippLLSGDDim1IOuQgiT3P5uHxJfil3U8Yqy5U0akN1AGLrSfWl2kWbCbYVpreBZmqoZzOjr7HXyGa2NOcBhWQC7uhtjQKmvO7MK/Nx8HYhMotsImFsZ3YoOxf44SJ7l83IUbDmIdw1oIh3iKOFnFHMBnw7fh5Q5hH+FmyuPJhQaxpD+wOL/Upv0g80s9BKiBdmCccRGVIBMUyCVzsvppc2Qzu90dMSmOoC5Rdlt3JcKaqqaj21N2R6R/XRRC1Aa6fN0/LqDfWh+gJ9p57JCDaGou5HUXvBjDOHAB8+NT+ZrHXP5fEZxtfHGTdJC/taQ86TO6QSu5W1439PePcX3BvOBGvrwF/lGUR8QjU6g66hVwROvCrmAXONgx87Lt2SV6m1EHnPaw9wdaLX1jvot/RHenIgjxXWZed5B9d1ioAtNyL9yWryljRjf4OVNkDsXMFt4j5xc/kaYjfxilhaOo1eeoR+6gdcsEG+Kj+U0yptgYUXwq+k0xQg/QCw8ZG6FyJGNPj4NrMwWHALB2v7OGN0TUk0GUzKs0eAd9+ymbna3Aj4701cK8Tj0/xc+gsicV7gtTZCD2E5MG9lR3s/ilnRIht7TZTXya2VWcoW5YRiqGXVZvDCR7ST8F9J9Wp6P/2SXhL+NwrspZjZ3jxuFoUdrbL2Am/7OHNB66OFZ8hNMgixMh3nj7jRkZ8In9MR3nU3LLyWsE3ILBZEvN8gHgTKZpwnd1o74zW3gI/SyYYcCsteCQu6KSdVsiua8rvaAb27Wzuq2fNvDkK6GQzBqODcKzkJRlgAfRxrbjBfmEmt7FYja4CDh131yUcGkp9JG3YmewY8thgY7Gp+L5/BRnGUozptQi/RW/QBTSaUFCikMlaYK+wVUoiZxAKiDmTSUIoBLn0jVUJcao6+2Atmml7Na8/a1nLpkXo7+PJT+m96GqO4ocNmBhiPjWXmXUTwHBZnRThj6/OtE8CcPs49kSSkNFD4DHYjm5zLxUVz3bjFwE0GX5//id/Fn+IJbQuLuETTAVEPFZbCljOJcUBFNREt30vX5UrKdKWjOkw9rWbUKKLLam2vlhuI772ezlAM+1mhw0Yr843JWb9YzxxM5+O8M6g/4sZN4Jn0iPPr2YNcJn443xqRrjh4ns2A7CcQG4l9pL5qbq2UVkJvAJb13HxlvjU/gnX4WCmsNFZ6KzNQSW3Lfoutfe/Nx40Tg8laorDH2cesN5hDbr4an5bWo23gkQbTndC3JAIRRKDlKcJqtOSy0+dBsOt6iDJDgdU2ASG9UQvqol5Wrwu+3MjoD/y+F31byGxstgOKGWlKVh2rszXFOmJdgA2/sphRPs44HUPSkmKEIxWB3NqCOV8mj0lSYNSO7Ah2PvuerYx43wGIPh1wfGe6jJ6kf9Degr84VpwFzd8svobu15FWSgfQyyPhX44qH5QB6gPV0GKAp3/XusHathq74UluGpvMPeYRYKnr5h3ztZna8rPyWMUsAtZpP0nZCHbY3uoE7RtjzbSWWD/DU+6yTloXrbvWC5fPmeXjzO3wISlJdsKTANS6BrxCBIkDN59KFgB1bkKMP4pW3Cd/AH/az0nkZIsDc75nB/FT+dy0EJXoQliSLNwWgsQYcaW4TjSANw+BWeRC5BkCPHxWTq1kAZZqoLxRc2gltVmw3VB9pr4cntHXyA49rWvFWAcgy/PWfeuJzZaBnXycd2EVI124ddx+7hz3isvOF+PH89v4M/xlvjClsJaa9Ce6me6ihxALL1JPIZWQXigKLlRXCBe6gvvZ8wYWCiNg3XPERajZDfEeOLSP87xjYYlKgYhFlaUIMKLuwPO2vfvI5YDj7bHpB3JKxdfBUzWV7soQZaZSU+2mDlSnwMc/Vw86My2K6DX0TsCDj8wkVlZrCLj+HHDgNdZO67h1xzUmt8Nl9ymgFUMcmf5C9kGeH0kEUG4v4I9N7AV4xsJcR/j5HdxVLimv8e35g/wVsJVstA6Q7BMaKEQIq4UdwnnwlOTAINXEDsAgy8WzYnFpHDx0ZrkS/OQppZRaW+2oTle7a1PA7s9qo8Eq0hum2RAMa6GpQBPsl3w1c+bmlofdnWMfsEW4+twobj045ivuAp+PNodOcmAQ64VcsPTRiHsz4BevivHSQGmqMxPdnqv4XGopD5Ivy02BdE6rJbXhWl2dGpHGImcc0tXmUGjPJzIa/oMR/ODNTCFYqCxUF2KFcWAJa4VL0Jn3Qkoxh1hENIHLLwHb+khZYIuxYFhb0Bct5RHyZuhPemjPAOUusEsJtSKwywh1kXpQfaym1oprZeDz5gKPP9fzGYYx0NhlzEBsTW8Vdp5Ta2gj8ac+zjgiA/za3HmiOB9bn93H8ohGLWCN/biRkP1rLjNfmJ/Br+cv8lloMWDvlEIpIQ68YY2gigFiAyDTbmBUl8T7YlKpgMRKohQshUNzBkoTpIvSU8lX7ir3AhbfJt+Xo8CUFTVcbaFeU4tohlZOq6IdBONLp+fWVX28vkHPahQyTKOG0dpYZmwGcxDM6mYb9FNV4JoO1hnrgeu5Niapg139SSTw4Gx4k4JsODscbPcim5qrB32ZyV8D+6pOB9FRsMRN9B7qXVBoBO1fBezyBDG1ABDrAHEc2Ox+Mb/UQ+oPrDAadZ4mrZIqos7j5KNyRTC12cpbJYUaBm54Wy2uRWtbUdsQfZQ+S78IttPY6ADufsS4bZQz10O+RSzTqgcf0xG+ZTe8ymvLfiFcA4crlCPtwdNXkR3kNsnETgQLaMrN5bZwJ7hH3FuuAG/ytfg4fgq/m38IRl4MaCYctU8vVBEiEV/qiYpWS5uvVdVjgUqLwOMuMhn/pI6PL8deY1+w+TmDb8q3odvpMbQ2E1h8V2GOsFLYJfwmeCFSlhRrQnPtlg6X9sGu7TGOVnI8NJZVTKUX2NFIZRvY0SmlpzpLDdLqal3gXU3dMqoZHYF/NxjVzY7mYvOmOd3aD4b63DWmRZI6Y6I5STvyE7HvSjcFg/jEZoPtrnB7qYp0KT1B79BiYoR0WFr5Pzg4H5+sqjCOv9PVHcJiIx1ZOXqLZf7azrnn3nPOvefcc7eotAlqg5wNh9WiQa+ObCRYkKXkxAEhY7xQi9x0NCOJZrWBYkwpt9iQkCSG76xeA1ZbTGOtzK2+7/sfPHfP83y/3885915524+qQUxnfdAcdKHPDxpjuuDH2VDrfeEBaPIksoqVvruLkjegDVPYmdS7gNuQEXrpNZoHdtpjd4Hwf7U3skpWx05BHfKdx51tYN0TSKsJ5wHow4ybdO/hEn62XFRjJjvFkBgTf4t8cFOP94uX66+Feu1V0+qWrgguBYkgy+QYZSagXR+GfemMYqX3JEpWk+2kgZyE8s+TUtqGdHCd/kNz7CiSfgz5bdCeRSa9YzezDjDJw04J6vgcpHoTpJrrSpBqg5vN9/MO/gkf4hN8gS8VOaJM1IhG0PaG9FnJdrlb7pW18iM5i1yZg450+uf8TeqUuqRG1WV1RU2pGRBeUt1UW3SVPqw7dR9Y9bo2wXNBfdBu+owfFmD+Dqb+y/G8lb4PjJEkKaCF9BXaQLtpaL9s19rHQNfDdga7jxVg7qpZGzuB3H8ZPvIzW2RvYnO+gntkuo+4Je5OTGCVW+M+A5Lq5Wf4FdDoaTEgsuQFSbyr2I+3UOWI/7o6o86reZUBgk5oAuWZDPqQf28hAUdetdIaGydZdAt4uAobkDqpCex89iTbwVaB3j5G6i2DEja66zjhN/gif1QIsVmUi3/FB/JrWYGObVbFqkzVqe/UT2qtfkIn9byOB+NgiG9M5G0rfZZNkN9SRN5NeqG2F+AsSRKlRXQfevYf7bLrmO2UOxX8Pf6UqBXviEH43BKZKVfJKFh62lvqf+kn/R1qt9qvmtSfKgd+1gBH60GydYLpYJ0JTbvpN9fMXeGKsAkpYhxZx0rr+wbQdIJkUkbPgh8K7U/tadYBjh9yv8U0Lrp386exyy08zkd4hrhfFIg58ZgsljWyHro+Ko+jgnNePhQ95sfhWgP+bT9Uu9Rr6oA6AvZLnVMP49nn1L36BR0DyxzRLTquJ/Sszgs2mq2g5wFzx0SOW+l3kQpIMWkFm/4IMn2IrgE/rUFVO+2DqOyinbApK2KtrJ/9wZY4nnPUedFr8Sx/BVz9M3/Mz1ZUFalKVa736Hp9Uv+gG4PzwV+BMC9Bl4+aq2bWrIfHfxFG+q00CxeSStJE3idnySRZSXfRY1DlXNu12zBvM/ZKth4a14ptXWDLnCKn3dmEVDsHv4tBm07zYf47L0FHPFkqD8kpmee1er3ejPebVw0C7vFH/e/9G76llqvDqhdevlUfwvwvA6unvnYfR2+kKTXvmm5z0SyY1eGzYTPyx0g4FkaGrcj/AAAA//80nGXgFLf39Rcp7lrcpWiSmchMJhnci0NxKe78kEJxihd3KO4Ud/dCobi7U7RYkZZSoM/Z5f+8YV+xyeTee87nzMx+J0QiEUH2knukAG1Ox9EkLDt7z+I4aZ08zirnsHPaues8dtK7hd3Abeq2cnu5/d1f3Nvu325uPoY/5wXESHFIvBVxZArZVLaVY+UCuUnelXmUo0qorzzP2+n945Xyv/dH+Wv85/4nP5kep78K3GBj8CkYY66axjZ5+H04OrwRRk4njPTDfkaRY+Qv0pdupCfo3zQPC1gdtpitYDvYXvaGuU5j5zcnp1vNPe4+cRPzBrwLP8pLi0Fik9gnjopPIrHMLUvJ+uqUKupZL5Nf2W/kr/Mf+Hl0Wz1QbwgC08i8NvFsA/uTPWf98H8hFr2dMDIIH4nIW5KMpqGV6U80IZOsK/uT/cOyOcOcyc4C576T1s3qFnSLu+Xctm5vd4H7wS3Ld/E2IrPsKk/JXIqokqqGaqK+U1dVJ2+uV9iv76/yN/jb/Cza1SP1VD3dzDeHzDGTyOa2be3fNm/YORwZRl4mjPTA+hEynxSirehLmpSVYZtYFrcyHy+WyySqrjqvqnoNvXbeOO+m96Xv+NX9bv7P/mG/sC6re+spepVOEzhBraB5MDxYEmw1p8wjXGdSm8EOtjPtYlsu/C4cHs4Mt4a/hO+j1xxJFJmBf0uQ78k28gtJSrPRB/QDdVg/dhtX3cyp5g50x7gPUe0kfDlq3VZ0F9+L2eKFSChLy9qyoRwkp8kt8r501Ug1U+1WV9Q/qp7X2pvsrfSuene9Fv5FP6XOqhfqI/pFkN5IU9W0Nf3MJDPP7DaXzSejbQ07xp62T22psH64OHwdRlIlivVBHXKbZKYj6BS6jOZnTdg6ttt552R2x7pL3FfuJP4zTyXyiUpiiVgjXsiiqgd2sFodUZm8Ul4/7ws/t1/K/8EfrZfpzfqyFkGZoG8wLVgZJDXclLYtbFc7wR6wr232kISVw9nhjvBNGMmZKNIVa18iAa1Eu9MVdBP9jRZny9gFJ51bwJ3jbnNPuAU45Wv5KX6d/8e5CMVMsUvcFuVlDVlNzVIbVF70XX9vudfJn4HKn/O/0k10chOa2bjeZLa4TRsWDcvjWqP1ThSpgo+VZDP5nbSiP9DZNAG7wnLwsqKoqu7N9Of7p3yla+r2OMH0pqH51sw1e81/pqitYzvZa7YIvmlreCJ8GEZKJIq0xXdVJ81JHJzbL/RP+g8twMqxpqwzG8Gm4wQrOo3cdu4LNx3fyG/whKKOaCh6Y2beSoH+yuF19QZ6U72fvYNeFj+13q55UC7Ib7qYBSZiE9gUdql9biPVE0U2YR2fDCI7yXWslRpntYVepylZDlYfK/3CqmA2ivEOfDLfyc/wiqKmGCJeikQyO/pmgBwnZ8tjUImlqNdezGlcr7y3xXvtx9dpdHZtdDldTXfSffQYPU3P1xv1IX1JX9cJglRBtmBQkMwAECzv03Q1Y8wM87NZaw6Y96YYatnLDrOT7Uq72160t+wjGyfMF5YOa4ZNwrHh/vBxGGmWKLIKe05CKpFV5D55CoUpi12vojtphAlWhe1hVzHnU5xNzi7noPPQSeRmcsu6Xdxp7ka3JO/I+/OF/B5OLB9ObIQ4jHrXUh3VaLVCJfZSesW8wd54b4V32UsOvantt/AH+4v8K34SnUkP1y+1j66fYvaYv00+W8HWtf+zfe1o+xtO8x+bJMwWdg+HoAO3hXuiPdE1UWQCPuKRgkSQJjjlCdjzbvRHZpqf9qSj6Vy6Gup4gP4BfeTsG+z9NnvOMjjc+Z8z2lnnXHNeOLnc1u4D6FMm3omP4oEoJb4WrcV34iupZWU5VI6XRFWBUnVRk9QilRg6NdE/5rfXLYP2wfOgFPqsFHY63C6zkUGJIiOxn97kMfmXJKIt6DA6i+5AvR/Q/2hT9jcr5+x0fsdsZnHXuPvdR+5QPpYv4ev5Ef6YVxaNRBvRRYwRAeajuZyHSa2hBnhTvHPec6+g38Uf6o/zd/sJtdUVddygYjAwOB1cDaab9eZ3U8G2suPtJuuEq8PIhESRMdhHKfKJZKcG++hO59D19Ff6BcvFWrBR6O8j7Cajzt/OK/cL3klMxlymka68IJOpNl4vb4h333sKZcjvh1DPVtDPMf5sfykUeo9/0H/rz0enpQmaBWeDR0EF8yt6vqFth/UP2hs2fUjDevCKCeGsaI3mf9aJb8lwaOcjQui3dDF9CreqxUayic5KeOdF
*/