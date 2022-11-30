//
// Copyright 2005-2007 Adobe Systems Incorporated
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_GIL_CHANNEL_ALGORITHM_HPP
#define BOOST_GIL_GIL_CHANNEL_ALGORITHM_HPP

#include <boost/gil/channel.hpp>
#include <boost/gil/promote_integral.hpp>
#include <boost/gil/typedefs.hpp>
#include <boost/gil/detail/is_channel_integral.hpp>
#include <boost/gil/detail/mp11.hpp>

#include <limits>
#include <type_traits>

namespace boost { namespace gil {

namespace detail {

// some forward declarations
template <typename SrcChannelV, typename DstChannelV, bool SrcIsIntegral, bool DstIsIntegral>
struct channel_converter_unsigned_impl;

template <typename SrcChannelV, typename DstChannelV, bool SrcIsGreater>
struct channel_converter_unsigned_integral;

template <typename SrcChannelV, typename DstChannelV, bool SrcLessThanDst, bool SrcDivisible>
struct channel_converter_unsigned_integral_impl;

template <typename SrcChannelV, typename DstChannelV, bool SrcLessThanDst, bool CannotFitInInteger>
struct channel_converter_unsigned_integral_nondivisible;

//////////////////////////////////////
////  unsigned_integral_max_value - given an unsigned integral channel type,
//// returns its maximum value as an integral constant
//////////////////////////////////////

template <typename UnsignedIntegralChannel>
struct unsigned_integral_max_value
    : std::integral_constant
    <
        UnsignedIntegralChannel,
        (std::numeric_limits<UnsignedIntegralChannel>::max)()
    >
{};

template <>
struct unsigned_integral_max_value<uint8_t>
    : std::integral_constant<uint32_t, 0xFF>
{};

template <>
struct unsigned_integral_max_value<uint16_t>
    : std::integral_constant<uint32_t, 0xFFFF>
{};

template <>
struct unsigned_integral_max_value<uint32_t>
    : std::integral_constant<uintmax_t, 0xFFFFFFFF>
{};

template <int K>
struct unsigned_integral_max_value<packed_channel_value<K>>
    : std::integral_constant
    <
        typename packed_channel_value<K>::integer_t,
        (uint64_t(1)<<K)-1
    >
{};

//////////////////////////////////////
//// unsigned_integral_num_bits - given an unsigned integral channel type,
//// returns the minimum number of bits needed to represent it
//////////////////////////////////////

template <typename UnsignedIntegralChannel>
struct unsigned_integral_num_bits
    : std::integral_constant<int, sizeof(UnsignedIntegralChannel) * 8>
{};

template <int K>
struct unsigned_integral_num_bits<packed_channel_value<K>>
    : std::integral_constant<int, K>
{};

} // namespace detail

/// \defgroup ChannelConvertAlgorithm channel_convert
/// \brief Converting from one channel type to another
/// \ingroup ChannelAlgorithm
///
/// Conversion is done as a simple linear mapping of one channel range to the other,
/// such that the minimum/maximum value of the source maps to the minimum/maximum value of the destination.
/// One implication of this is that the value 0 of signed channels may not be preserved!
///
/// When creating new channel models, it is often a good idea to provide specializations for the channel conversion algorithms, for
/// example, for performance optimizations. If the new model is an integral type that can be signed, it is easier to define the conversion
/// only for the unsigned type (\p channel_converter_unsigned) and provide specializations of \p detail::channel_convert_to_unsigned
/// and \p detail::channel_convert_from_unsigned to convert between the signed and unsigned type.
///
/// Example:
/// \code
/// // float32_t is a floating point channel with range [0.0f ... 1.0f]
/// float32_t src_channel = channel_traits<float32_t>::max_value();
/// assert(src_channel == 1);
///
/// // uint8_t is 8-bit unsigned integral channel (aliased from unsigned char)
/// uint8_t dst_channel = channel_convert<uint8_t>(src_channel);
/// assert(dst_channel == 255);     // max value goes to max value
/// \endcode

///
/// \defgroup ChannelConvertUnsignedAlgorithm channel_converter_unsigned
/// \ingroup ChannelConvertAlgorithm
/// \brief Convert one unsigned/floating point channel to another. Converts both the channel type and range
/// @{

//////////////////////////////////////
////  channel_converter_unsigned
//////////////////////////////////////

template <typename SrcChannelV, typename DstChannelV>     // Model ChannelValueConcept
struct channel_converter_unsigned
    : detail::channel_converter_unsigned_impl
    <
        SrcChannelV,
        DstChannelV,
        detail::is_channel_integral<SrcChannelV>::value,
        detail::is_channel_integral<DstChannelV>::value
    >
{};

/// \brief Converting a channel to itself - identity operation
template <typename T> struct channel_converter_unsigned<T,T> : public detail::identity<T> {};

namespace detail {

//////////////////////////////////////
////  channel_converter_unsigned_impl
//////////////////////////////////////

/// \brief This is the default implementation. Performance specializatons are provided
template <typename SrcChannelV, typename DstChannelV, bool SrcIsIntegral, bool DstIsIntegral>
struct channel_converter_unsigned_impl {
    using argument_type = SrcChannelV;
    using result_type = DstChannelV;
    DstChannelV operator()(SrcChannelV src) const {
        return DstChannelV(channel_traits<DstChannelV>::min_value() +
            (src - channel_traits<SrcChannelV>::min_value()) / channel_range<SrcChannelV>() * channel_range<DstChannelV>());
    }
private:
    template <typename C>
    static double channel_range() {
        return double(channel_traits<C>::max_value()) - double(channel_traits<C>::min_value());
    }
};

// When both the source and the destination are integral channels, perform a faster conversion
template <typename SrcChannelV, typename DstChannelV>
struct channel_converter_unsigned_impl<SrcChannelV, DstChannelV, true, true>
    : channel_converter_unsigned_integral
    <
        SrcChannelV,
        DstChannelV,
        mp11::mp_less
        <
            unsigned_integral_max_value<SrcChannelV>,
            unsigned_integral_max_value<DstChannelV>
        >::value
    >
{};

//////////////////////////////////////
////  channel_converter_unsigned_integral
//////////////////////////////////////

template <typename SrcChannelV, typename DstChannelV>
struct channel_converter_unsigned_integral<SrcChannelV,DstChannelV,true>
    : public channel_converter_unsigned_integral_impl<SrcChannelV,DstChannelV,true,
    !(unsigned_integral_max_value<DstChannelV>::value % unsigned_integral_max_value<SrcChannelV>::value) > {};

template <typename SrcChannelV, typename DstChannelV>
struct channel_converter_unsigned_integral<SrcChannelV,DstChannelV,false>
    : public channel_converter_unsigned_integral_impl<SrcChannelV,DstChannelV,false,
    !(unsigned_integral_max_value<SrcChannelV>::value % unsigned_integral_max_value<DstChannelV>::value) > {};


//////////////////////////////////////
////  channel_converter_unsigned_integral_impl
//////////////////////////////////////

// Both source and destination are unsigned integral channels,
// the src max value is less than the dst max value,
// and the dst max value is divisible by the src max value
template <typename SrcChannelV, typename DstChannelV>
struct channel_converter_unsigned_integral_impl<SrcChannelV,DstChannelV,true,true> {
    DstChannelV operator()(SrcChannelV src) const {
        using integer_t = typename unsigned_integral_max_value<DstChannelV>::value_type;
        static const integer_t mul = unsigned_integral_max_value<DstChannelV>::value / unsigned_integral_max_value<SrcChannelV>::value;
        return DstChannelV(src * mul);
    }
};

// Both source and destination are unsigned integral channels,
// the dst max value is less than (or equal to) the src max value,
// and the src max value is divisible by the dst max value
template <typename SrcChannelV, typename DstChannelV>
struct channel_converter_unsigned_integral_impl<SrcChannelV,DstChannelV,false,true> {
    DstChannelV operator()(SrcChannelV src) const {
        using integer_t = typename unsigned_integral_max_value<SrcChannelV>::value_type;
        static const integer_t div = unsigned_integral_max_value<SrcChannelV>::value / unsigned_integral_max_value<DstChannelV>::value;
        static const integer_t div2 = div/2;
        return DstChannelV((src + div2) / div);
    }
};

// Prevent overflow for the largest integral type
template <typename DstChannelV>
struct channel_converter_unsigned_integral_impl<uintmax_t,DstChannelV,false,true> {
    DstChannelV operator()(uintmax_t src) const {
        static const uintmax_t div = unsigned_integral_max_value<uint32_t>::value / unsigned_integral_max_value<DstChannelV>::value;
        static const uintmax_t div2 = div/2;
        if (src > unsigned_integral_max_value<uintmax_t>::value - div2)
            return unsigned_integral_max_value<DstChannelV>::value;
        return DstChannelV((src + div2) / div);
    }
};

// Both source and destination are unsigned integral channels,
// and the dst max value is not divisible by the src max value
// See if you can represent the expression (src * dst_max) / src_max in integral form
template <typename SrcChannelV, typename DstChannelV, bool SrcLessThanDst>
struct channel_converter_unsigned_integral_impl<SrcChannelV, DstChannelV, SrcLessThanDst, false>
    : channel_converter_unsigned_integral_nondivisible
    <
        SrcChannelV,
        DstChannelV,
        SrcLessThanDst,
        mp11::mp_less
        <
            unsigned_integral_num_bits<uintmax_t>,
            mp11::mp_plus
            <
                unsigned_integral_num_bits<SrcChannelV>,
                unsigned_integral_num_bits<DstChannelV>
            >
        >::value
    >
{};

// Both source and destination are unsigned integral channels,
// the src max value is less than the dst max value,
// and the dst max value is not divisible by the src max value
// The expression (src * dst_max) / src_max fits in an integer
template <typename SrcChannelV, typename DstChannelV>
struct channel_converter_unsigned_integral_nondivisible<SrcChannelV, DstChannelV, true, false>
{
    DstChannelV operator()(SrcChannelV src) const
    {
        using dest_t = typename base_channel_type<DstChannelV>::type;
        return DstChannelV(
            static_cast<dest_t>(src * unsigned_integral_max_value<DstChannelV>::value)
            / unsigned_integral_max_value<SrcChannelV>::value);
    }
};

// Both source and destination are unsigned integral channels,
// the src max value is less than the dst max value,
// and the dst max value is not divisible by the src max value
// The expression (src * dst_max) / src_max cannot fit in an integer (overflows). Use a double
template <typename SrcChannelV, typename DstChannelV>
struct channel_converter_unsigned_integral_nondivisible<SrcChannelV, DstChannelV, true, true>
{
    DstChannelV operator()(SrcChannelV src) const
    {
        static const double mul
            = unsigned_integral_max_value<DstChannelV>::value
            / double(unsigned_integral_max_value<SrcChannelV>::value);
        return DstChannelV(src * mul);
    }
};

// Both source and destination are unsigned integral channels,
// the dst max value is less than (or equal to) the src max value,
// and the src max value is not divisible by the dst max value
template <typename SrcChannelV, typename DstChannelV, bool CannotFit>
struct channel_converter_unsigned_integral_nondivisible<SrcChannelV,DstChannelV,false,CannotFit> {
    DstChannelV operator()(SrcChannelV src) const {

        using src_integer_t = typename detail::unsigned_integral_max_value<SrcChannelV>::value_type;
        using dst_integer_t = typename detail::unsigned_integral_max_value<DstChannelV>::value_type;

        static const double div = unsigned_integral_max_value<SrcChannelV>::value
                                / static_cast< double >( unsigned_integral_max_value<DstChannelV>::value );

        static const src_integer_t div2 = static_cast< src_integer_t >( div / 2.0 );

        return DstChannelV( static_cast< dst_integer_t >(( static_cast< double >( src + div2 ) / div )));
    }
};

} // namespace detail

/////////////////////////////////////////////////////
///  float32_t conversion
/////////////////////////////////////////////////////

template <typename DstChannelV> struct channel_converter_unsigned<float32_t,DstChannelV> {
    using argument_type = float32_t;
    using result_type = DstChannelV;
    DstChannelV operator()(float32_t x) const
    {
        using dst_integer_t = typename detail::unsigned_integral_max_value<DstChannelV>::value_type;
        return DstChannelV( static_cast< dst_integer_t >(x*channel_traits<DstChannelV>::max_value()+0.5f ));
    }
};

template <typename SrcChannelV> struct channel_converter_unsigned<SrcChannelV,float32_t> {
    using argument_type = float32_t;
    using result_type = SrcChannelV;
    float32_t operator()(SrcChannelV   x) const { return float32_t(x/float(channel_traits<SrcChannelV>::max_value())); }
};

template <> struct channel_converter_unsigned<float32_t,float32_t> {
    using argument_type = float32_t;
    using result_type = float32_t;
    float32_t operator()(float32_t   x) const { return x; }
};


/// \brief 32 bit <-> float channel conversion
template <> struct channel_converter_unsigned<uint32_t,float32_t> {
    using argument_type = uint32_t;
    using result_type = float32_t;
    float32_t operator()(uint32_t x) const {
        // unfortunately without an explicit check it is possible to get a round-off error. We must ensure that max_value of uint32_t matches max_value of float32_t
        if (x>=channel_traits<uint32_t>::max_value()) return channel_traits<float32_t>::max_value();
        return float(x) / float(channel_traits<uint32_t>::max_value());
    }
};
/// \brief 32 bit <-> float channel conversion
template <> struct channel_converter_unsigned<float32_t,uint32_t> {
    using argument_type = float32_t;
    using result_type = uint32_t;
    uint32_t operator()(float32_t x) const {
        // unfortunately without an explicit check it is possible to get a round-off error. We must ensure that max_value of uint32_t matches max_value of float32_t
        if (x>=channel_traits<float32_t>::max_value())
            return channel_traits<uint32_t>::max_value();

        auto const max_value = channel_traits<uint32_t>::max_value();
        auto const result = x * static_cast<float32_t::base_channel_t>(max_value) + 0.5f;
        return static_cast<uint32_t>(result);
    }
};

/// @}

namespace detail {
// Converting from signed to unsigned integral channel.
// It is both a unary function, and a metafunction (thus requires the 'type' nested alias, which equals result_type)
template <typename ChannelValue>     // Model ChannelValueConcept
struct channel_convert_to_unsigned : public detail::identity<ChannelValue> {
    using type = ChannelValue;
};

template <> struct channel_convert_to_unsigned<int8_t> {
    using argument_type = int8_t;
    using result_type = uint8_t;
    using type = uint8_t;
    type operator()(int8_t val) const {
        return static_cast<uint8_t>(static_cast<uint32_t>(val) + 128u);
    }
};

template <> struct channel_convert_to_unsigned<int16_t> {
    using argument_type = int16_t;
    using result_type = uint16_t;
    using type = uint16_t;
    type operator()(int16_t val) const {
        return static_cast<uint16_t>(static_cast<uint32_t>(val) + 32768u);
    }
};

template <> struct channel_convert_to_unsigned<int32_t> {
    using argument_type = int32_t;
    using result_type = uint32_t;
    using type = uint32_t;
    type operator()(int32_t val) const {
        return static_cast<uint32_t>(val)+(1u<<31);
    }
};


// Converting from unsigned to signed integral channel
// It is both a unary function, and a metafunction (thus requires the 'type' nested alias, which equals result_type)
template <typename ChannelValue>     // Model ChannelValueConcept
struct channel_convert_from_unsigned : public detail::identity<ChannelValue> {
    using type = ChannelValue;
};

template <> struct channel_convert_from_unsigned<int8_t> {
    using argument_type = uint8_t;
    using result_type = int8_t;
    using type = int8_t;
    type  operator()(uint8_t val) const {
        return static_cast<int8_t>(static_cast<int32_t>(val) - 128);
    }
};

template <> struct channel_convert_from_unsigned<int16_t> {
    using argument_type = uint16_t;
    using result_type = int16_t;
    using type = int16_t;
    type operator()(uint16_t val) const {
        return static_cast<int16_t>(static_cast<int32_t>(val) - 32768);
    }
};

template <> struct channel_convert_from_unsigned<int32_t> {
    using argument_type = uint32_t;
    using result_type = int32_t;
    using type = int32_t;
    type operator()(uint32_t val) const {
        return static_cast<int32_t>(val - (1u<<31));
    }
};

}   // namespace detail

/// \ingroup ChannelConvertAlgorithm
/// \brief A unary function object converting between channel types
template <typename SrcChannelV, typename DstChannelV> // Model ChannelValueConcept
struct channel_converter {
    using argument_type = SrcChannelV;
    using result_type = DstChannelV;
    DstChannelV operator()(const SrcChannelV& src) const {
        using to_unsigned = detail::channel_convert_to_unsigned<SrcChannelV>;
        using from_unsigned = detail::channel_convert_from_unsigned<DstChannelV>;
        using converter_unsigned = channel_converter_unsigned<typename to_unsigned::result_type, typename from_unsigned::argument_type>;
        return from_unsigned()(converter_unsigned()(to_unsigned()(src)));
    }
};

/// \ingroup ChannelConvertAlgorithm
/// \brief Converting from one channel type to another.
template <typename DstChannel, typename SrcChannel> // Model ChannelConcept (could be channel references)
inline typename channel_traits<DstChannel>::value_type channel_convert(const SrcChannel& src) {
    return channel_converter<typename channel_traits<SrcChannel>::value_type,
                             typename channel_traits<DstChannel>::value_type>()(src);
}

/// \ingroup ChannelConvertAlgorithm
/// \brief Same as channel_converter, except it takes the destination channel by reference, which allows
///        us to move the templates from the class level to the method level. This is important when invoking it
///        on heterogeneous pixels.
struct default_channel_converter {
    template <typename Ch1, typename Ch2>
    void operator()(const Ch1& src, Ch2& dst) const {
        dst=channel_convert<Ch2>(src);
    }
};

namespace detail {
    // fast integer division by 255
    inline uint32_t div255(uint32_t in) { uint32_t tmp=in+128; return (tmp + (tmp>>8))>>8; }

    // fast integer divison by 32768
    inline uint32_t div32768(uint32_t in) { return (in+16384)>>15; }
}

/// \defgroup ChannelMultiplyAlgorithm channel_multiply
/// \ingroup ChannelAlgorithm
/// \brief Multiplying unsigned channel values of the same type. Performs scaled multiplication result = a * b / max_value
///
/// Example:
/// \code
/// uint8_t x=128;
/// uint8_t y=128;
/// uint8_t mul = channel_multiply(x,y);
/// assert(mul == 64);    // 64 = 128 * 128 / 255
/// \endcode
/// @{

/// \brief This is the default implementation. Performance specializatons are provided
template <typename ChannelValue>
struct channel_multiplier_unsigned {
    using first_argument_type = ChannelValue;
    using second_argument_type = ChannelValue;
    using result_type = ChannelValue;
    ChannelValue operator()(ChannelValue a, ChannelValue b) const {
        return ChannelValue(static_cast<typename base_channel_type<ChannelValue>::type>(a / double(channel_traits<ChannelValue>::max_value()) * b));
    }
};

/// \brief Specialization of channel_multiply for 8-bit unsigned channels
template<> struct channel_multiplier_unsigned<uint8_t> {
    using first_argument_type = uint8_t;
    using second_argument_type = uint8_t;
    using result_type = uint8_t;
    uint8_t operator()(uint8_t a, uint8_t b) const { return uint8_t(detail::div255(uint32_t(a) * uint32_t(b))); }
};

/// \brief Specialization of channel_multiply for 16-bit unsigned channels
template<> struct channel_multiplier_unsigned<uint16_t> {
    using first_argument_type = uint16_t;
    using second_argument_type = uint16_t;
    using result_type = uint16_t;
    uint16_t operator()(uint16_t a, uint16_t b) const { return uint16_t((uint32_t(a) * uint32_t(b))/65535); }
};

/// \brief Specialization of channel_multiply for float 0..1 channels
template<> struct channel_multiplier_unsigned<float32_t> {
    using first_argument_type = float32_t;
    using second_argument_type = float32_t;
    using result_type = float32_t;
    float32_t operator()(float32_t a, float32_t b) const { return a*b; }
};

/// \brief A function object to multiply two channels. result = a * b / max_value
template <typename ChannelValue>
struct channel_multiplier {
    using first_argument_type = ChannelValue;
    using second_argument_type = ChannelValue;
    using result_type = ChannelValue;
    ChannelValue operator()(ChannelValue a, ChannelValue b) const {
        using to_unsigned = detail::channel_convert_to_unsigned<ChannelValue>;
        using from_unsigned = detail::channel_convert_from_unsigned<ChannelValue>;
        using multiplier_unsigned = channel_multiplier_unsigned<typename to_unsigned::result_type>;
        return from_unsigned()(multiplier_unsigned()(to_unsigned()(a), to_unsigned()(b)));
    }
};

/// \brief A function multiplying two channels. result = a * b / max_value
template <typename Channel> // Models ChannelConcept (could be a channel reference)
inline typename channel_traits<Channel>::value_type channel_multiply(Channel a, Channel b) {
    return channel_multiplier<typename channel_traits<Channel>::value_type>()(a,b);
}
/// @}

/// \defgroup ChannelInvertAlgorithm channel_invert
/// \ingroup ChannelAlgorithm
/// \brief Returns the inverse of a channel. result = max_value - x + min_value
///
/// Example:
/// \code
/// // uint8_t == uint8_t == unsigned char
/// uint8_t x=255;
/// uint8_t inv = channel_invert(x);
/// assert(inv == 0);
/// \endcode

/// \brief Default implementation. Provide overloads for performance
/// \ingroup ChannelInvertAlgorithm channel_invert
template <typename Channel> // Models ChannelConcept (could be a channel reference)
inline typename channel_traits<Channel>::value_type channel_invert(Channel x) {

    using base_t = typename base_channel_type<Channel>::type;
    using promoted_t = typename promote_integral<base_t>::type;
    promoted_t const promoted_x = x;
    promoted_t const promoted_max = channel_traits<Channel>::max_value();
    promoted_t const promoted_min = channel_traits<Channel>::min_value();
    promoted_t const promoted_inverted_x = promoted_max - promoted_x + promoted_min;
    auto const inverted_x = static_cast<base_t>(promoted_inverted_x);
    return inverted_x;
}

} }  // namespace boost::gil

#endif

/* channel_algorithm.hpp
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
*/