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
CRxHwAmo7qTC5wALJFZbC4MM1XHJ+Hp1qj9TW83UsFWH1t9RTzPyAr095RokuY5bC7v75aqUXMc51+feXI4F+hfNyBTA3+lI0evo7ex2JpFpLQwGCTlDCerHBDL5TGMNYX28nRctDzwt+7Md4qPhk9705IEH0G3L8XGY5HDqDmzjZhwWyBB2kn8i89h2s4hlq/hUI0sfRfA/SgYaYfUkAkwWgKKcfQmQJoAzBOhMgGQBNBEglADXCqCKAL/8CsAV202W5Kjr9ljkCD0QqYeRits7paQGmuDELW98J5ruut781XgD4lyausXfXh/AgVWBBR2W+W5BtghyBSOnANnYfv3ai/TdJ9WqbczkUv0eFIacuZONEnHJE9i+Ut/v5VfquQBvqe/0klLZpowxS3r5FflxgLfIPwGu+m9jLy5683l8eew27jPh7OJUv/FX6uyedq6xOJ2tJdcx0comtGrNk7LFNHyqKmYY3evaZvh0Uz/P8V10SOhkMQ0nOiC/vpzKWlfFH5qhL8Fbfh2XRDot0KY8vwYwTbXzqiBLyQKPOw68cIVC4EpzA0n5yJ+TG0EoLwAlqAmXxop2USao34KTbsodRnZFqM5GGqaV606uTnGieuQq+oLh4dI12P3u9CjQdbpCcTzkhDVU8RQosc+q9qggnatS/5uETHpDE6r9JgSVfct+RG8vm28f0tsq820tva0w38rZNmMlzcWobddPeG/j9MBx6mNIGXqGptbChynL6XpT8hLVS1sZL06fRimFeJMfDl+3lZeDvVaEYv3fU36xuTmN/rv1Ax25t4UjDZjTtkpvmw4sX28buwxr0C1qIAiS/uMpRn3cQE1sgdqXUJ8C1vuC5TSw2rfACgQW/4YHEB8XxNEGot7DH/EzDYg2QZwpiFOAqGbyV2jNdvzHR7SVjxguGAsJ44UWdJ4gOuflZwJOvhICLdQOC50VJRwRCuAHlHDZltwwzA57R/PRei3yJaMR1bIeXleT/eh9Ib/z9X5l6ctp5WqaIFWoTImsBnb+NlqZD6eReZZAjwM6l6F2gmb0oKgDUcDHA07yniyomWoKDwa8MFXb+zBQqfNxHDmjznDE5SThvZYP848xZDHVsxWXcWuw6Ct1TjhH3fEQaQqOcAl71GRw0fSueRvH05uUUyJFytVbnK3ZpGicdEgkS81eSgwyPCUxbayt1UapWaWqiBNl9V4BZJMurorqM5m+eRKgfLi/qleG7CCjLttBqiMfAe/qj+mQdCefFuN7XSGkkRmAXqxMr7LjnhC7GVLEjYvzb+4Xi9HcEZizCd2W/12KayZlGgwSrhvRcStcrYxRMTcDhFoLoZ1EqHULQrcToW0XWP6+KWWsPxLWN7H+WAmE9VdgEVEHXUWFaooap5RG435oIfYZ9LIQeJY0ci+3IPBTEanLQIAacyxVtaOKiCUR9w7Xoy54lUmBsTJcC95X3RnPHKx7Ag+lAg8TyCkM2+oAEPDN5ewVM07qEEAfsbi7fx3+SHU41EzWZjSLbuFVQy4prU/SvKDTZCdJ+c09XemgmGEtfA1AUj4UPmcx1xQrJJYizh5R5FvLucj3PiTutiiy+U8ocjqKzG9u53KmJfVxJRIN1+8ov6s//tZypWcLhZeJwu4r/SlsJAo9QMFbXXdXnHN08GE8TRieX/FZSHSSZRXPV6SLx9Kg3QSvr9RQKWTiU2T/cmWL4eVtK5vfJuHqQLloFKHVXLkdQ0W7UdJm3ambBd/CcrL5cSZ09YfiLiTmSpL3xo10moz1s+ztICQ2q6OxcUeUK1Jz5KU0VudZHdtwUcGuncUqO46gZV5oGfhjLVxrWAW5WqlxPCE5mFu5Q2hV5hqEIg8=
*/