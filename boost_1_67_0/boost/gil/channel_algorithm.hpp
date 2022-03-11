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