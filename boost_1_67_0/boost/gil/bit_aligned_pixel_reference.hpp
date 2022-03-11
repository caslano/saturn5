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
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
*/