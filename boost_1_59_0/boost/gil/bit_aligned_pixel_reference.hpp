//
// Copyright 2005-2007 Adobe Systems Incorporated
// Copyright 2019 Mateusz Loskot <mateusz at loskot dot net>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_BIT_ALIGNED_PIXEL_REFERENCE_HPP
#define BOOST_GIL_BIT_ALIGNED_PIXEL_REFERENCE_HPP

#include <boost/gil/pixel.hpp>
#include <boost/gil/channel.hpp>
#include <boost/gil/detail/mp11.hpp>

#include <boost/assert.hpp>
#include <boost/config.hpp>

#include <functional>
#include <type_traits>

namespace boost { namespace gil {

/// A model of a heterogeneous pixel that is not byte aligned.
/// Examples are bitmap (1-bit pixels) or 6-bit RGB (222).

/////////////////////////////
//  bit_range
//
//  Represents a range of bits that can span multiple consecutive bytes. The range has a size fixed at compile time, but the offset is specified at run time.
/////////////////////////////

template <int RangeSize, bool IsMutable>
class bit_range {
public:
    using byte_t = mp11::mp_if_c<IsMutable, unsigned char, unsigned char const>;
    using difference_type = std::ptrdiff_t;
    template <int RS, bool M> friend class bit_range;
private:
    byte_t* _current_byte;   // the starting byte of the bit range
    int     _bit_offset;     // offset from the beginning of the current byte. 0<=_bit_offset<=7

public:
    bit_range() : _current_byte(nullptr), _bit_offset(0) {}
    bit_range(byte_t* current_byte, int bit_offset)
        : _current_byte(current_byte)
        , _bit_offset(bit_offset)
    {
        BOOST_ASSERT(bit_offset >= 0 && bit_offset < 8);
    }

    bit_range(const bit_range& br) : _current_byte(br._current_byte), _bit_offset(br._bit_offset) {}
    template <bool M> bit_range(const bit_range<RangeSize,M>& br) : _current_byte(br._current_byte), _bit_offset(br._bit_offset) {}

    bit_range& operator=(const bit_range& br) { _current_byte = br._current_byte; _bit_offset=br._bit_offset; return *this; }
    bool operator==(const bit_range& br) const { return  _current_byte==br._current_byte && _bit_offset==br._bit_offset; }

    bit_range& operator++() {
        _current_byte += (_bit_offset+RangeSize) / 8;
        _bit_offset    = (_bit_offset+RangeSize) % 8;
        return *this;
    }
    bit_range& operator--() { bit_advance(-RangeSize); return *this; }

    void bit_advance(difference_type num_bits) {
        int new_offset = int(_bit_offset+num_bits);
        _current_byte += new_offset / 8;
        _bit_offset    = new_offset % 8;
        if (_bit_offset<0) {
            _bit_offset+=8;
            --_current_byte;
        }
    }
    difference_type bit_distance_to(const bit_range& b) const {
        return (b.current_byte() - current_byte())*8 + b.bit_offset()-bit_offset();
    }
    byte_t* current_byte() const { return _current_byte; }
    int     bit_offset()   const { return _bit_offset; }
};

/// \defgroup ColorBaseModelNonAlignedPixel bit_aligned_pixel_reference
/// \ingroup ColorBaseModel
/// \brief A heterogeneous color base representing pixel that may not be byte aligned, i.e. it may correspond to a bit range that does not start/end at a byte boundary. Models ColorBaseConcept.
///
/// \defgroup PixelModelNonAlignedPixel bit_aligned_pixel_reference
/// \ingroup PixelModel
/// \brief A heterogeneous pixel reference used to represent non-byte-aligned pixels. Models PixelConcept
///
/// Example:
/// \code
/// unsigned char data=0;
///
/// // A mutable reference to a 6-bit BGR pixel in "123" format (1 bit for red, 2 bits for green, 3 bits for blue)
/// using rgb123_ref_t = bit_aligned_pixel_reference<unsigned char, mp11::mp_list_c<int,1,2,3>, rgb_layout_t, true> const;
///
/// // create the pixel reference at bit offset 2
/// // (i.e. red = [2], green = [3,4], blue = [5,6,7] bits)
/// rgb123_ref_t ref(&data, 2);
/// get_color(ref, red_t()) = 1;
/// assert(data == 0x04);
/// get_color(ref, green_t()) = 3;
/// assert(data == 0x1C);
/// get_color(ref, blue_t()) = 7;
/// assert(data == 0xFC);
/// \endcode
///
/// \ingroup ColorBaseModelNonAlignedPixel PixelModelNonAlignedPixel PixelBasedModel
/// \brief Heterogeneous pixel reference corresponding to non-byte-aligned bit range. Models ColorBaseConcept, PixelConcept, PixelBasedConcept
///
/// \tparam BitField
/// \tparam ChannelBitSizes Boost.MP11-compatible list of integral types defining the number of bits for each channel. For example, for 565RGB, mp_list_c<int,5,6,5>
/// \tparam Layout
/// \tparam IsMutable
template <typename BitField, typename ChannelBitSizes, typename Layout, bool IsMutable>
struct bit_aligned_pixel_reference
{
    static constexpr int bit_size =
            mp11::mp_fold
            <
                ChannelBitSizes,
                std::integral_constant<int, 0>,
                mp11::mp_plus
            >::value;

    using bit_range_t = boost::gil::bit_range<bit_size,IsMutable>;
    using bitfield_t = BitField;
    using data_ptr_t = mp11::mp_if_c<IsMutable, unsigned char*, const unsigned char*>;

    using layout_t = Layout;

    using value_type = typename packed_pixel_type<bitfield_t,ChannelBitSizes,Layout>::type;
    using reference = const bit_aligned_pixel_reference<BitField, ChannelBitSizes, Layout, IsMutable>;
    using const_reference = bit_aligned_pixel_reference<BitField,ChannelBitSizes,Layout,false> const;

    static constexpr bool is_mutable = IsMutable;

    bit_aligned_pixel_reference(){}
    bit_aligned_pixel_reference(data_ptr_t data_ptr, int bit_offset)   : _bit_range(data_ptr, bit_offset) {}
    explicit bit_aligned_pixel_reference(const bit_range_t& bit_range) : _bit_range(bit_range) {}
    template <bool IsMutable2> bit_aligned_pixel_reference(const bit_aligned_pixel_reference<BitField,ChannelBitSizes,Layout,IsMutable2>& p) : _bit_range(p._bit_range) {}

    // Grayscale references can be constructed from the channel reference
    explicit bit_aligned_pixel_reference(typename kth_element_type<bit_aligned_pixel_reference,0>::type const channel0)
        : _bit_range(static_cast<data_ptr_t>(&channel0), channel0.first_bit())
    {
        static_assert(num_channels<bit_aligned_pixel_reference>::value == 1, "");
    }

    // Construct from another compatible pixel type
    bit_aligned_pixel_reference(bit_aligned_pixel_reference const& p)
        : _bit_range(p._bit_range) {}

    // TODO: Why p by non-const reference?
    template <typename BF, typename CR>
    bit_aligned_pixel_reference(packed_pixel<BF, CR, Layout>& p)
        : _bit_range(static_cast<data_ptr_t>(&gil::at_c<0>(p)), gil::at_c<0>(p).first_bit())
    {
        check_compatible<packed_pixel<BF, CR, Layout>>();
    }

    auto operator=(bit_aligned_pixel_reference const& p) const
        -> bit_aligned_pixel_reference const&
    {
        static_copy(p, *this);
        return *this;
    }

    template <typename P>
    auto operator=(P const& p) const -> bit_aligned_pixel_reference const&
    {
        assign(p, is_pixel<P>());
        return *this;
    }

    template <typename P>
    bool operator==(P const& p) const
    {
        return equal(p, is_pixel<P>());
    }

    template <typename P>
    bool operator!=(P const& p) const { return !(*this==p); }

    auto operator->() const -> bit_aligned_pixel_reference const* { return this; }

    bit_range_t const& bit_range() const { return _bit_range; }

private:
    mutable bit_range_t _bit_range;
    template <typename B, typename C, typename L, bool M> friend struct bit_aligned_pixel_reference;

    template <typename Pixel> static void check_compatible() { gil_function_requires<PixelsCompatibleConcept<Pixel,bit_aligned_pixel_reference> >(); }

    template <typename Pixel>
    void assign(Pixel const& p, std::true_type) const
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

private:
    static void check_gray()
    {
        static_assert(std::is_same<typename Layout::color_space_t, gray_t>::value, "");
    }

    template <typename Channel>
    void assign(Channel const& channel, std::false_type) const
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
};

/////////////////////////////
//  ColorBasedConcept
/////////////////////////////

template <typename BitField, typename ChannelBitSizes, typename L, bool IsMutable, int K>
struct kth_element_type
<
    bit_aligned_pixel_reference<BitField, ChannelBitSizes, L, IsMutable>,
    K
>
{
    using type = packed_dynamic_channel_reference
        <
            BitField,
            mp11::mp_at_c<ChannelBitSizes, K>::value,
            IsMutable
        > const;
};

template <typename B, typename C, typename L, bool M, int K>
struct kth_element_reference_type<bit_aligned_pixel_reference<B,C,L,M>, K>
    : public kth_element_type<bit_aligned_pixel_reference<B,C,L,M>, K> {};

template <typename B, typename C, typename L, bool M, int K>
struct kth_element_const_reference_type<bit_aligned_pixel_reference<B,C,L,M>, K>
    : public kth_element_type<bit_aligned_pixel_reference<B,C,L,M>, K> {};

namespace detail {

// returns sum of IntegralVector[0] ... IntegralVector[K-1]
template <typename IntegralVector, int K>
struct sum_k
    : mp11::mp_plus
        <
            sum_k<IntegralVector, K - 1>,
            typename mp11::mp_at_c<IntegralVector, K - 1>::type
        >
{};

template <typename IntegralVector>
struct sum_k<IntegralVector, 0> : std::integral_constant<int, 0> {};

} // namespace detail

// at_c required by MutableColorBaseConcept
template <int K, typename BitField, typename ChannelBitSizes, typename L, bool IsMutable>
inline
auto at_c(const bit_aligned_pixel_reference<BitField, ChannelBitSizes, L, IsMutable>& p)
    -> typename kth_element_reference_type<bit_aligned_pixel_reference<BitField, ChannelBitSizes, L, IsMutable>, K>::type
{
    using pixel_t = bit_aligned_pixel_reference<BitField, ChannelBitSizes, L, IsMutable>;
    using channel_t = typename kth_element_reference_type<pixel_t, K>::type;
    using bit_range_t = typename pixel_t::bit_range_t;

    bit_range_t bit_range(p.bit_range());
    bit_range.bit_advance(detail::sum_k<ChannelBitSizes, K>::value);

    return channel_t(bit_range.current_byte(), bit_range.bit_offset());
}

/////////////////////////////
//  PixelConcept
/////////////////////////////

/// Metafunction predicate that flags bit_aligned_pixel_reference as a model of PixelConcept. Required by PixelConcept
template <typename B, typename C, typename L, bool M>
struct is_pixel<bit_aligned_pixel_reference<B, C, L, M> > : std::true_type {};

/////////////////////////////
//  PixelBasedConcept
/////////////////////////////

template <typename B, typename C, typename L, bool M>
struct color_space_type<bit_aligned_pixel_reference<B, C, L, M>>
{
    using type = typename L::color_space_t;
};

template <typename B, typename C, typename L, bool M>
struct channel_mapping_type<bit_aligned_pixel_reference<B, C, L, M>>
{
    using type = typename L::channel_mapping_t;
};

template <typename B, typename C, typename L, bool M>
struct is_planar<bit_aligned_pixel_reference<B, C, L, M>> : std::false_type {};

/////////////////////////////
//  pixel_reference_type
/////////////////////////////

// Constructs a homogeneous bit_aligned_pixel_reference given a channel reference
template <typename BitField, int NumBits, typename Layout>
struct pixel_reference_type
    <
        packed_dynamic_channel_reference<BitField, NumBits, false> const,
        Layout, false, false
    >
{
private:
    using channel_bit_sizes_t = mp11::mp_repeat
        <
            mp11::mp_list<std::integral_constant<unsigned, NumBits>>,
            mp11::mp_size<typename Layout::color_space_t>
        >;

public:
    using type =
        bit_aligned_pixel_reference<BitField, channel_bit_sizes_t, Layout, false>;
};

// Same but for the mutable case. We cannot combine the mutable
// and read-only cases because this triggers ambiguity
template <typename BitField, int NumBits, typename Layout>
struct pixel_reference_type
    <
        packed_dynamic_channel_reference<BitField, NumBits, true> const,
        Layout, false, true
    >
{
private:
    using channel_bit_sizes_t = mp11::mp_repeat
        <
            mp11::mp_list<std::integral_constant<unsigned, NumBits>>,
            mp11::mp_size<typename Layout::color_space_t>
        >;

public:
    using type = bit_aligned_pixel_reference<BitField, channel_bit_sizes_t, Layout, true>;
};

} }  // namespace boost::gil

namespace std {

// We are forced to define swap inside std namespace because on some platforms (Visual Studio 8) STL calls swap qualified.
// swap with 'left bias':
// - swap between proxy and anything
// - swap between value type and proxy
// - swap between proxy and proxy
// Having three overloads allows us to swap between different (but compatible) models of PixelConcept

template <typename B, typename C, typename L, typename R> inline
void swap(const boost::gil::bit_aligned_pixel_reference<B,C,L,true> x, R& y) {
    boost::gil::swap_proxy<typename boost::gil::bit_aligned_pixel_reference<B,C,L,true>::value_type>(x,y);
}


template <typename B, typename C, typename L> inline
void swap(typename boost::gil::bit_aligned_pixel_reference<B,C,L,true>::value_type& x, const boost::gil::bit_aligned_pixel_reference<B,C,L,true> y) {
    boost::gil::swap_proxy<typename boost::gil::bit_aligned_pixel_reference<B,C,L,true>::value_type>(x,y);
}


template <typename B, typename C, typename L> inline
void swap(const boost::gil::bit_aligned_pixel_reference<B,C,L,true> x, const boost::gil::bit_aligned_pixel_reference<B,C,L,true> y) {
    boost::gil::swap_proxy<typename boost::gil::bit_aligned_pixel_reference<B,C,L,true>::value_type>(x,y);
}

} // namespace std

#endif

/* bit_aligned_pixel_reference.hpp
3l9X4Fcs1CDwDTBRr10uwSy0HSg2yJI/JH0eHPCbAHwseCFIxE+LYyNCwALx+Cf7gWxeBPkAcYDiQtT7y/b+2oUxoEOECwIe8NcTMM1lnQWyA7FxFeEGgQdd6/UgxAoDLQY1Aub//06W6deR3ZrtbySAHgtRCYbsr/nzGNizkKewLODnQC9chDMCrM+hHDbgycB3vZ4CHAwgmEBuoNZA6gLAMgKano8zvX8MIGvxJUCOQRb8EA04duEagdNBnvzGe6tcRpljYawgl0En/Gb8fi7L8OsWnAtUFhjcbdefC+TeH68XmxApFS4IaOCnG8PNorrhlsJu2kTUg5j6DfSqGfyOBRsEretlMaD5X33AWMBRd9VwEtE4YC9B5v139MVy4A6BN/xVCIFT4URACoD4d016Qe3Ay4Fb5uToQagRxYkZcMIgAoD0c3Fm8c3gDwNbYDQQaCCOQcgVXxbsnPy3oFu/iPdBp4FC/Xl/ohCEBuwY5L/2ZujFMUNoBaYTcN5lG4ZgtoMYPVrdo6zhP9LUIT/HXMZ/gFMXUDzBO8mbAf//PgwPC7m5uwJ9CwwBLCiAykAAdRbKBNrSOzFwhx0L8gW/i7u7CmaNYwbdCfsKrCjAE/vrECTFH1KA99F5yn/aD2XfHfsWLBk40C/Sh6nmwbNg2m+u13CXtRfnFkjHP72X95HzLyEBB1ChIDvOlyEHA+4puBPIJhDGLvDliX/m9lPVA0cOnHOioIBz7mkHl9RbNNf47o09WGbDBQWtX1+vhAFybHN3dDxkaq8tbCME109EGfm7+s34N/Xa7NLYQVNAJjZySZHswhkA16Kv/sIFl/ITZyeWy4X5Gc8gi0Ea/MAFsO0QW6E4rMoLWMC4gAL9BAhxX6E0gK2An4FLgJhvcRSsHfGOJHN/z4JjAkWCFQMRgE74y+xC3cLcQipwd0XPw56CPEKEAAH3ohpA1GKuAuEC+QDLaMdC3BLPorihpEJ5gdEANwNB+gvtItuhUEBiW1UVtILS/8R9Xq8bIboEEBvQhn+XAL4C1CY4lXVFAQ+cE9inH3Svzi4OIQ4HzCaEhWnupgCkASEDLibkJEQyyIUfXq/5LpMdjt2oCB4onp+gABQDigRQ988o9eEPskum4OiJdwSdC337EyZgQHG9MoTArxCrULiQ08BFAk22c8tArrnUP90cdBIMHdTS779bg2wC4zacU7D6lfhjANHvqhqg3tIhwnj9DG1M/1XNDtwN7KqTbRbWDLQT9hE4BOhbgOWWsxZ/FOzeH3mXTgFtRZx3FzwXgQHsFnIbuBuIDaStl3KX7BazuuBdgDoXgwE5FcILahBUH5TaP+onDkEzIWyA11nfB81Ey9IrKLafLKhf0hfVuFxKq2CvdDcsCJzqm/cXR8gsfWHCLWGPkRwJlFkQe0bXUPln1qIdh8cUcRuWrncrBfn+xMLA1scI6pnHZqFzU5s4y44jKrea4zL0sYADOtIDZONe2YHtWNtIXGf2AAwLDHuLG4fWv1hlWURTQWQUiwWUw/wBNKuCu1lMhUVJkglfvTECuQSd4iRk308CWv6xAzJVsrp/ogQoULGLUX/5cHDIgSTd1tS/zwSpPAEg/M7CO2VA+HF99ooZY90zw9xA7Iyxqw2ihgHNLLqK70B2Onk5hJ2BMlEi3ZcHBOGdcEJUXf7ZxXKzj0G+qI3+xDkJRHAsUUxRQ3HY7AsPxPyHMv2MuHmEZh5EyfjFfcVEpaD8o7p+JyLar/qFGAH1YF/qZ89AtoiG+KTzj4JeeaW/scQTSw8EkLhn4C+YgQywlb8VrSPSr/7siF0u3NhE6XKHAkiDKRJ5Vu30QPHXk7UifNFmbOU1Cr4VYatnZRE5/yGvCBT8sncWx0NAX4lUm0EBFGcDVqzLDN8uFzwPCJKYEbn0cFBEU9XFUyXYdaoqFPOnrVemMmK11pJ2xB8RD2S79znETlPvfZWIq0izbm07zQu1TJsdRrsH4CIZ5gLIKmglsu3VC83eU+7AtGfuBgzfG1xwIql/lkroBwpz0tHC3rK9Pfbt8/KozthFyXwqix6umUXfZN6A9bH1kMez59mnHn9f9yUZxsKdUTp87+nA7+EG52AHV9Hu4bzBBIUU0Dl0iPxrDdthJvlPemlrafViVimGNMOhRK60xjuDgPSM8N9lqweAjtcjt5KZlLiRisg33wVjHKNG6hGOZRUr+Xq9KPvzh+UpFjQHoMNdQLlNE6p3pXu5hvZ7PVgYctCvvwzrrS5J2BcHNRNED7QTBtQLgHxchBnPWV8v/EY+TT2i4fjPG6ldi9eX2jrXyNMKjml5xZlFsyZIt1fWb/kZcXrWbsDRGyasnN/pw1MXtbCiIc8urB2xR6JZITqEj+kCjIRRfhhtv4XvmsqAiuyguOeQnhr1mAgjqMGVGb7q3t3MK9M1vkVZ4O4QkmK0TJ+Lu0Gm79DC/RrBwSriooAf5oTmSTcxBlFI63c4+cH7A/aZlYdoFbf6Hh50Bm5bRyp2hp7IVPsBhThj9Lbg+arABWkhI7ZRU4lBp2GUckc4wfLNszAu8LKGlakToWEEIuP6tAU5Xg7rkP1BTibMd9co5X7Oct0Z/fnln6uvnWMPzP0b03r9rUg1T25rqyhUddlF4RVoAFvXHELbuHVB8lXlhE7syik/D/n6pKtIsAc2oRQKlVJtDvA3ubpPQ+hkQ3s/OxRvn9scCVhGK/xnxdtczszeIawjxaNiiKpZwa+T/uVwq5/8Nx1yQ4rw2POAExbN8qDnvmy15rsD+fvlIJNvqyf9aa2azvsacJNNsLHplO9M+t6TkF3Hd9gp36HWv+QeUrHasWsh1eyguYEC7hpeCxnOWsRGn1r6TEcfpqrYyvXwpZ840FpsgGV1MoRwQP8whs4hFZmHMsgHfUJrReug4413K8z1pdoGqTWJ+Bjeleetu+SMtvydfyXVo0ccTdjR6qHtOOBDoWDmvdi+cG+I7M2ubo+Urx772w6Nl9l7JEwppLyrQbLlnbnMkhLrGd0ZmcbrdYSZFWrvjkNOzZmPmO54YPsee34fNy8jbIR0fDiq0dZS9U7bt6BmpfPjRpfi3zVzaWVltBJIqr9hLuIqaCHwmAAIIkwkkAcwvh+1AkIp/CZtMH0swiUwBHgMFiYS7ja7W7m+scDroF9v6W5uXr6OoKEYpr9DC2tT3xqM0He/CNbuAi8TByHV6i54l6udxq3+uacIAqv7NuJHJOM2B9fuaQTJTVJ0bx1ytCDHvZ4FWHSnOhfeCBXHcLlPWbl+9rmr+pOyjVTPNHvRTm3GfE1KGf30GmFT1COatSTMi/IG5oDwYkENByjTZRWM6wg/7SbolV2hGbSufTZEBOuXRB2AAfFqPJtZ5FLmUcDzNpBHpBZyzf69r4Lb8DzUzhe3Y2DYuw4/5JFlpw+iq2b2PWwL4R1BAJY390VsFWHWsesO4Mdfh/Uw7uMBtH9lfQ6dfWNoerQhMATvjjDHqqOkiHGPiBf3jdhFuaZ55z1S+AqK5PdhlbDPvVQ4SDipqaO60GHI9lLNVbIwTVnkasD6TDl/gvekgaZjvSKuN1c39uw+6klgPkzo7feU2bSoiXV9lpvobaEUb5qKWrPEmmQqzkGRQsBBSclbTuGdU051q5UcGN+5WVi4jwlWSSrGRWFkn9n6qNi3dEuzj4NylssC1tltr5BvykFha8xFkdBbE9E6seOikLwncR0bBT8OnHtBCvmbalKwjGlL0B34lXFQsA1yEd5ZIR3E2x/qJzXBe4Uu5VkWdMd3Q0uFnQSN9+/qNek1wZ2H3AbaVq2DXe3qE6SUEfJBFwz1qt00F2C7Bb//DqkJVHosDqw3KwrcB+aeOOgaE+REOcqNDOreuyyXmiwdSTzgV8eACoh2SJqGz69Gz8fV9lPFw02kIUS4ez4PfwfRA2LrmvRKTywATkokC/tAk08T22OfDr+gycQgBJHYNlRyyFVGpEv/5xJgpIXdj0X2G++d6dQw9wHkk90PQRff6Tt2y79elexom8n0N1w7FGG2vYC62M5MHmg8cJUsBXSs7cQHKTzZB7/sdDIkQYnqtBTb6zfMbovA8dOyVCF4FsZhPZi2XkTuS/A0GoVUrPtU8DRePfSodKz7FaQuT3/3IeloZzqyCTdcm9GE+iPeHEa4HU3/0pIdcb+cBQf4nyOio9PXI/iZYsvmJ8nzj6dz2aIIvg7mWqtdFG71F9nKYx2WB68FmyNflp7EtzMMXYxHy44q+QWEeu9ywOP6VYn402TlTWO5nd1NrItPkg08R/zx11V0iJxzu2emeZjH6AeICV8AV+8c3psJwQLK16+RN8Hz1G39yj2yf4yJ3uZA1QYFetFfCNquCKgVwG1kZrTXu5GQK5HPx87qy9LWTbmfkub5JP16BzLhxT2qkgHvLFndDibQ5xHJaVSbD/Pf3zZWdLdw7v0T3Hkfyb+l87eOc7L4qK8K6Hk+Wp0/rLaS+6rpk/VP7wcYewTbxN/JeO8sE1wheTD12G1FRkwmyJ0m3J4iEm0YabVXx8fTNG3tMcKo04AYQzMgIr5oxDbUbVX/oLEdEVXAsNex+ei11NzvFJZcCds/E1AY/vHl1socWt7PhG/uoEenUru9l+cHHH43bc7doVCu1SQ3peGeZK1/RSnYfwM8nvF/H+shIaSJblz/xTzZ8jnHw5xSny61dq+bGsOKdwXXqbJmVZnaELnApugtvLKOUnfFtXZ8kDRUk8xotsEObiuv0I1qC38jm6nQ0TdvsG7r/3vZvT+dzpNTtfRUAysOVQ0bE1wYPHLKoZifyMQzjp3M/E3onHLRw6nv633j7zs1xP/BrZbn0pGh82FxBK9kuu3f7u1T1XyE18TQ9MUeoDZMC3hfa0JTF+5YeaF+f9a9+zWvFgCg614+b/qrw/qVlWJd9LFyNtbB7wH4zr8mz/sCC/OYGxnp6rorz+J2ihKFg/jHy/qMoATfeN3/hHwmolFjsK6v8PKMf1yxJkNMS1uk8FTugMbcoEgsd8Z6Z+tosJMQ2bidc/a3q8BoMo1WdxqIZJCGUUCHPc6Fc7Hk8nvWyf1F5JrSfjDe0wdtwfEL8ndTTUwKQDHj1dW0ed/Zoke8bGmlp6fn9eTus+EjQosncOmpwQUcoXljDuozpYMMkPEK6ASrJ4ACYZ59rJT0jTmtqRH3psN3ufaooB10SwJ4e77KG353cMIseI88Er8/wpMh4Hrb+XT8837CtxgFBayXtdsYNAmP4n1G77qwNgVvQtRzW2Vr1P1jNCZYhsU7p7RPxegOr715cdA9eqNdptBE0Fd397btqQ4f9XhtlxpjorTn1LA85KaQluOisH7hotiD6hDKaR4RxPLtF3yDddhXrMz6hZs4uwA/Pi8EeYQe7WOKl/jK7JDV56ZP6aDAxxvThDULk9oxIWgec3AZAT/enIOX2AFlK6Bl4jeCAC81bQN5tE4UFCe3DT954M/UG9RJ7UdtwEW6F33L9IrLH9yEt18VwWEBgus6MDiN+VLnGcHIIpPJWvUb4utsehGqruSx+dSEGBBftjMQ33HkHH6Zo4mFzEfhJnM6WLor0VOG1PclJP4mE4bLxMgRP+x/e+XvyA1m1LmJcx9SnGP3yUwPQDX9fUw4Dk8hMOdaioCPkJpYnVr2Wu5pxneeqT0hXgBsqdMp53TeYDw25Ggtv4356Xr1tGxRGQM/1hTCf4FlB45KCIep2HYtvGIjn5H5sWnlmPfh2qHMX65+rlFmDLesF2r/feq5ypftY1mnxm2oPWN8MLp2Z+z8F5f0+G/99pfTR4Jvykv+syNIuxOf0kfgeTEr2UzNjk+F+vOEfCvrTRLTk8UntfpmQZTzn02cxesOXvJrTf5Q7KsgwEcEABImKnPgbEU+UzhaKAKL5HgSZVDGjuv7LuahwA+9ylf33KHxeZiqODWuix9vZctWCGim5iYoTBJJeGBoqlFT9ZwKqVThKqpJp6V9mVWJ6ZyqCurJmI0yS9l6j0OX45c1k8Jm6DHgT37ownFyaZP6otGK0Ktb1ghnG/FHxF0M9/cZX+RKFMCL4LjqPNqQ4K8mrXiRHvMI4OSDoeuCY/1qgGdjU/HsFdNJFY/6ckCGc+8x5vmPBkJQM0LB0o72FW7SPFv0+DU5XlJnM7xUBAZeUgBZ9HhncfR4XHq0lNHi2EPvioAkSeHNeSkq70kpSyXkBnW0FPK5DdD9ErJOzHp0vg90Zm91zT9mHNJrYbBRpPaKq19eYxOkLT1LPXJ696urFUT7rJxLqhZY1WvtkXmDhYusOpNPpT3GSjqwXnzB6bBdgQVd3XgKTnjeC8KP5rsrzIMDh63s5u8JPT0d0wXLnNRjZjk4plTjtEEPiNmYaFjYfMOsFv1gK7XQexqhwfLwUDBwDqpPSChkIWLBclDsznox3SfFMhkHrjSHokjR4RUJVjjaGZwUE0Q3g3G8Ap6R050Sa+xmX8ISEgYqxhoX0P5zmJDvcNdXvPtZ1dtbPLxbHc22R1dnBwvnQxgdH43nq83CoWrX17od7R0tV8t5FxH03dz5rm4ih0G9fX1xCYEkG82Mb67ulyXyn9kqx5DcaVqNHO9Bdfg67Ntmr9Xbems+kWUOF4xFnraas9VxRh4ikBDiYUL7NR9+0IqB5KIiMmGRv+DnNdtfEPD5iRzKeV3tTl/Dag08s+QsNKuqVx/m30vIspu/x8DZMHR3jjSn/lZY1b6dWf1WBWwmAzCaC+GmpbjZIetmKrNqRnJcEU8qwJpTDD6qUozAM9TTG+af5K2ga58+UbRf/J/RDu40dOswXmvv05Fm/I/NxGmtrcvsYbBiTsRMi/jfAzkMGO1wDQCzW9wshFb9mMog+7KzQxnqE+i2w2JtvnydBQM71zmOPT8Zfw7A9nkmpfNQ4Q+gM7Q1hU58JSVuuxbbueojE56qdeYMobrYVUXQG+qxL+my5iG9l3105TT01DOghkNlsebiMLc1g+rcVBhQ68MHZVJpPcsP3hnI9tQqOPPtISweyn+V4ziHj9eJl+iTkZnUzUG2f7o4Ikg5bO+JcGjZwAMRztspwEjCvg0aVXegwF8MQi5/NHqC0k81uJ9Ot5DURvXR3cGVs6/P+d1uqIsdpUqZM+muWJnXyjzq2bDoisGNpGh4QwkLSu7K+EgTtULg2Lm9z2nSNvLGED3FhZi3Msj1Z1x4Hpfir+kzJT9Nt/8+p0Wa45uxE+FwHhsFPwA5u7Ii1XJZNdyPIuGSGeLAY9J9ftkULGwtt8YDkl6nUaPsInodFu3OVT3H2it1Cj30mbSYbIL7KmGRs23RPcJZMVeDSDTVytbE7Fkwv7CZAyJiK4mig6Mxi6GAZgdq7zsgagOjucwwR5CvjgHzLbmjy99wqPrOS2RKVmnFSmu9WbWbMeeZu1+XYHzuw7Ldhxjv64Oiuf2AbxjT0rypvg7hDqUJ3STlO6hnDBRAPHutPCevD7H5iZfIQIjzitQKqQLfm4mRivAJ1hrzMzMAfSMA/ff/hJe60F6ooss3Z2eZhHy4xKWlccJz4LCuIrGkCUEiyMjxdqUCqcbpxsZMKGQo8JxgIre9aGi3IGCioibBT8ImaGiiujycIsDg4EfKg6CKnYI9vqpPxh5crND1u9fva29dTisV
*/