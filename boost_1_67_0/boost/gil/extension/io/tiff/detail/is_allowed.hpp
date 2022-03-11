//
// Copyright 2008 Christian Henning, Lubomir Bourdev
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_EXTENSION_IO_TIFF_DETAIL_IS_ALLOWED_HPP
#define BOOST_GIL_EXTENSION_IO_TIFF_DETAIL_IS_ALLOWED_HPP

#include <boost/gil/extension/io/tiff/tags.hpp>
#include <boost/gil/extension/toolbox/metafunctions/is_bit_aligned.hpp>
#include <boost/gil/detail/mp11.hpp>
#include <boost/gil/io/base.hpp>

#include <type_traits>

namespace boost { namespace gil { namespace detail {

using channel_sizes_t = std::vector<tiff_bits_per_sample::type>;

template <typename View, typename Channel, typename Enable = void>
struct Format_Type {};

// is_bit_aligned< View >
template <typename View, typename Channel>
struct Format_Type
<
    View,
    Channel,
    typename std::enable_if
    <
        is_bit_aligned
        <
            typename get_pixel_type<View>::type
        >::value
    >::type
>
{
    static const int value = SAMPLEFORMAT_UINT;
};

// is_not_bit_aligned< View > && is_unsigned< Channel >
template <typename View, typename Channel>
struct Format_Type
<
    View,
    Channel,
    typename std::enable_if
    <
        mp11::mp_and
        <
            mp11::mp_not
            <
                typename is_bit_aligned<typename get_pixel_type<View>::type>::type
            >,
            std::is_unsigned<Channel>
        >::value
    >::type
>
{
    static const int value = SAMPLEFORMAT_UINT;
};

// is_not_bit_aligned< View > && is_signed< Channel >
template <typename View, typename Channel>
struct Format_Type
<
    View,
    Channel,
    typename std::enable_if
    <
        mp11::mp_and
        <
            mp11::mp_not
            <
                typename is_bit_aligned<typename get_pixel_type<View>::type>::type
            >,
            std::is_signed<Channel>
        >::value
    >::type
>
{
    static const int value = SAMPLEFORMAT_INT;
};

// is_not_bit_aligned< View > && is_floating_point< Channel >
template <typename View, typename Channel>
struct Format_Type
<
    View,
    Channel,
    typename std::enable_if
    <
        mp11::mp_and
        <
            mp11::mp_not
            <
                typename is_bit_aligned<typename get_pixel_type<View>::type>::type
            >,
            is_floating_point<Channel>
        >::value
    >::type
>
{
    static const int value = SAMPLEFORMAT_IEEEFP;
};

//template< typename Channel >
//int format_value( std::true_type ) // is_bit_aligned
//{
//    return SAMPLEFORMAT_UINT;
//}
//
//template< typename Channel >
//int format_value( std::false_type ) // is_bit_aligned
//{
//    if( is_unsigned< Channel >::value )
//    {
//        return SAMPLEFORMAT_UINT;
//    }
//
//    if( is_signed< Channel >::value )
//    {
//        return SAMPLEFORMAT_INT;
//    }
//
//    else if( is_floating_point< Channel >::value )
//    {
//        return SAMPLEFORMAT_IEEEFP;
//    }
//
//    io_error( "Unkown channel format." );
//}

// The following two functions look the same but are different since one is using
// a pixel_t as template parameter whereas the other is using reference_t.
template< typename View >
bool compare_channel_sizes( const channel_sizes_t& channel_sizes // in bits
                          , std::false_type                      // is_bit_aligned
                          , std::true_type                       // is_homogeneous
                          )
{
    using pixel_t = typename View::value_type;
    using channel_t = typename channel_traits<typename element_type<pixel_t>::type>::value_type;

    unsigned int s = detail::unsigned_integral_num_bits< channel_t >::value;

    return ( s == channel_sizes[0] );
}


template< typename View >
bool compare_channel_sizes( const channel_sizes_t& channel_sizes // in bits
                          , std::true_type                       // is_bit_aligned
                          , std::true_type                       // is_homogeneous
                          )
{
    using ref_t = typename View::reference;
    using channel_t = typename channel_traits<typename element_type<ref_t>::type>::value_type;

    unsigned int s = detail::unsigned_integral_num_bits< channel_t >::value;
    return ( s == channel_sizes[0] );
}

struct compare_channel_sizes_fn
{
    compare_channel_sizes_fn( uint16_t* a )
    : _a( a )
    , _b( true )
    {}

    template< typename ChannelSize >
    void operator()( ChannelSize x)
    {
        if( x != *_a++ )
        {
            _b = false;
        }
    }

    uint16_t* _a;
    bool _b;
};

template< typename T >
struct channel_sizes_type {};

template< typename B, typename C, typename L, bool M >
struct channel_sizes_type< bit_aligned_pixel_reference< B, C, L, M > > { using type = C; };

template< typename B, typename C, typename L, bool M >
struct channel_sizes_type< const bit_aligned_pixel_reference< B, C, L, M > > { using type = C; };

template< typename View >
bool compare_channel_sizes( channel_sizes_t& channel_sizes // in bits
                          , std::true_type                 // is_bit_aligned
                          , std::false_type                // is_homogeneous
                          )
{
    // loop through all channels and compare

    using ref_t = typename View::reference;
    using cs_t = typename channel_sizes_type<ref_t>::type;

    compare_channel_sizes_fn fn( &channel_sizes.front() );
    mp11::mp_for_each<cs_t>(fn);

    return fn._b;
}

template< typename View >
bool is_allowed( const image_read_info< tiff_tag >& info
               , std::true_type // is read_and_no_convert
               )
{
    channel_sizes_t channel_sizes( info._samples_per_pixel
                                 , info._bits_per_sample
                                 );

    using pixel_t = typename get_pixel_type<View>::type;
    using channel_t = typename channel_traits<typename element_type<pixel_t>::type>::value_type;

    using num_channel_t = typename num_channels<pixel_t>::value_type;

    const num_channel_t dst_samples_per_pixel = num_channels< pixel_t >::value;

    //const num_channel_t dst_sample_format     = format_value< channel_t >( typename is_bit_aligned< pixel_t >::type() );
    const num_channel_t dst_sample_format     = Format_Type<View, channel_t>::value;


    return (  dst_samples_per_pixel == info._samples_per_pixel
           && compare_channel_sizes< View >( channel_sizes
                                           , typename is_bit_aligned< pixel_t >::type()
                                           , typename is_homogeneous< pixel_t >::type()
                                           )
           && dst_sample_format == info._sample_format
           );
}

template< typename View >
bool is_allowed( const image_read_info< tiff_tag >& /* info */
               , std::false_type // is read_and_no_convert
               )
{
    return true;
}

} // namespace detail
} // namespace gil
} // namespace boost

#endif

/* is_allowed.hpp
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
*/