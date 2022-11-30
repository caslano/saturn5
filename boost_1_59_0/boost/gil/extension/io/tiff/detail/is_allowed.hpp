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
JAzVxbhpJ7bsMf8mJLSHT0l6GuKPVncMrHFgrbeF9TFeJYO79q/8hcdiZ4XEmYXFMfTlE8jPP6CTvAti9L8BV6BkCoqoIhCI3kJK22hQnrUPjtF+0cpePzpzRbvhOMEVZp8pljLvfRGftYXkay+ZFGq1NHWZLlwkly4xIz31fF8b5e0EzAQ/9KVFummRqrj4wJ/Fxy5xAz2jHd3qbRMALiRi9n79PfdjSC9wtujDPcc1EZ+LcP/eNdTTAj1V8XQkfiObqlAvit1IFW6XGPJ0b3//e84qOA3LrRPgk58VQUf+cCe/yPYBHlsxCHzufZtmCfesIb7ofvnCv+DRyYj0tJJMjMVrjqLZm3zH+SvFCXH2jMzRTz2pGz5Sd2m2x/n1YVHnF2UibWETw2OnSSBNnRzV1NrlYiuXds1spUrHfhtLlRZVNplKKpPHDYkHT7HKTonKzOJlmhC/RRHNZRpNFX4qvarpmpoOnR0o8dQBk+d/7fzcE1FeeR75YQsWhGeJJLcUGBtX5Q5hrJ1rWmwyOiWpRCUTPOxXHWNcPpjPSjKlgo+nyiDCg8+lMN06Vz37TQi5EsUTA4AOtdKfuMWgCPmFXerK40V2igmqvCp0dKEjpyB2Oh0Z+SrFo2IHyxK1kUEjZamDM75prTXux/SWjsGttpY2pNFhlVlX1dvMcxAXYlGaQgZ26zIViku30/xNjISgGNfH+KA7DRYT7rWzhcbCCxUHNQQCtt7rEyYHvXrBesJpwkUg7g6O/mgreGNEwr9biOywez1p++3PGB7MHqBMD+zSdsfyv7PzJI3Wmu+KhKZqIBWZXGTuwWcyY28Hh0VmIyGwrirxy6q8UND3eXEQb3s8JtR6lJXfHWgMxGh9kmBVa9kkXLku8dIOhGV4jMNDBUYHetQvK9N5wg79xbn8k56aziJ9JdLRNXdrS/ffxe+uy4O72UworqipHzP4TwSrq3DJEXqKwCQ4VLvklt0+CNhbSq69V9DT7ugGlVSzYz/akT/EZXyhjGRFdmJmkrzytpScJb0apD0Rvk9ULxr1Jk9uw6mCwcSauCzXXIXSB7DH9mpbQToSdJyobvCqUz2/1wUrFSKtt7uL9tGqjj1i54Mm53xVJuBZrFdqjUMqcbDo9wqzDv6e6tFLskJhA4xjpsy2soxt/Ewb+LTQB05C+9nhdRiIbmkiS3SgxuzTWnyFM5BL7cTYiKs+oqZhOhUZ8naJuNPT6Py1soPYPJ8+J5RMEMgHseadBKkptycnB9wX50P+COHTtMi1fJt24SwPNg1vy43sZSsTpwP4uC33bn0q44bVXZp9c9CA7m0oPi9H5nGj1pf7z9+hvJ3/ECs8L+6ok4kqZp1QHZHzJyay5juzWAFaT7xU6aTgrC7iWXf7zcwc38IQPsSDMVe+wA8Pn+K39Sbvk6K3+DUgdH3qonRNmK3LlJmv1La69FaOInrfZjCov5vAhpoq8VmbND+QqtNFvjPsKtWKZRxZzM+7YEpDwXK/YltJSWitxnuSk3Wf8xjxGNK8ta6nYoYt2e40Ouwa0WeXEwGzWYvAzA8GOxJn/XwBW2z4HriTnHlM/cngPWChhkEj67cXwr6rGaUxI+Sw9udfSU/tVeXW/isewwkf517bZ33NQK1xrTPu05ndmfu+JrGjVIMFEywkYPfWckGRHc2HREDMr9tWNX7yzk3O5L5Qdzh8LGU3faLPMNc3/qKsfsE3Ifg5fVxwGAdZdIjIZEVasTb+JYEo2vJVRu7Wadrl+n48QIl7kBXrMmRRyl2t+HzFvOhPq601hKXtat49GPiECPOMauEs6MRuCvGrIIl39r/jL7aWSh99vdUyr4aaUBrAiftRbijUoYOb2zjv6QY9dgpL4qZbl9WrsVHrYoLeRZj2cx/jfpz2YTc0M4J6higIU7jVI7Fl+LgetJi3w5NY5KsEg2HhbpI85ALrnMsbNcsJM6UkEMl3G4Y8xhXSMQNzCJZC5yHY2czld1f08SbmO7mtok/JnoMDhZ+cV6yuuKYtu45ORgHLI5KFqflY91dgbE5hz7gB0jPzbprSjKrqpIB6udbaF0yXn/UzjVcVBXWrMxz12U5v+R6CVSdoriA1XiecFB5NCZAbXtwYeRnloKeTsmvfQ0fpSfmPLkKW7gtswHXGr+YNa47yEircjnvRbijFA9XcEu8KtdCFzPoCTfgWcw5TT8/l5ns9x/9t1JQQXVm/lso4etOTpN5htjCfRFo91RkGvX7dx3Bh8Xsk4fQf7YpMXypai7PQv7fPN2osBmz51DC6LB7l4vCKtlazPOp5q4OvF5rpPfIXYJyJ3AjUsu69B7M6wYLF7u5kSe7Pa+jMHHKO65rdmQ4A1rhpUSiY3fGoH4kvZ3pzD27fcY8V8Qsi8rjkKwVTBC8H2DBCZiESPCfpbV36GfZI4tCbCss7Nebv1h/QSHLPEsbAjYq+C45DWupGBPFT3X0rXWtrjTrSUgAALP/TZUkAvfdDv70hEt/0G7SDFTjjtLEUUK48m/1bEsK0YYL6snjVes+up9aDW9RULZJCcgyyyAUSUbhynPSlhGeljIHX0Xhq1llIvU92tFw3EAO8SqALcnpHzYyX56ccNcjNz8nH645ZI1HjIZQCxbPqKVXapVsq2vc0daHmwtL5WPpRHNmMoZzbeycyPj/weSTo7znpe6VvbNfi+R3KPQmOu6KuNmO5a5hw62D7f5uruQf2/whZsIm9bRZvSN8O38zBnvFhzRS2Rh+GPT0IGDI+qpDsO4LGYHYqsE1AJVfUfX5WfMM8ro5GSQbtrs+VLwrKm9gjiTo2hWjgPy52OOo9dJzgi1cg1C55FfYuCzRo79wWxQqOo5hcTsy7e2I5wcf35lXDgz5ot+WQN2xLf56qDuK4ksEhuFP+7jTEs4m6ge6RpPJd/qGNHcuhJlD0HYFNGsGNl0ifesDCjkuOBLEqwYJoxnKlBbiVfn9330N/hrtSqJiz3RnRzVCOkgfpNSsL0qvm7CUZcwt0vgLOx9g9f3yYggm1xeftAtZMHVgVIUnz9/9Qv9mMNABmGYEAB5hatNdE07kA3/MLjOKb0vygPlr/2ZOh/zfirQUGjLo5vHoIGes9QZhDpsJnpnXKz2j6sHluVp7kLVC05b84BfHCb75BSAu28czAA1iCSBsKdADHYf+Q+bXE5M3RChpuf6OF0ZLDEd0q+BYLg04TtYPPTtq2OpJhv0tVI1sipVNEf+NlenI+uo4yy1ztjTluQO+UmV6bfCqGd0R+ywQYxhT1fA94qLDFMWqKymj1tIhmwWg2sCKTe74wofMhPZQeMZ01VaXIc9pQvD0lMU/S3iKi+U5cvguCUHPsIP0UZJS3e7RAle1ZTWYYdNh82MHHlTfdE4JuIqNTXA8Z+MJJFVj7ic5ZQgLpwh7AgvVvSOeOaQg1yZ5laCUoAZzx26GVyqj7+PyCHNF9CHxxRsPz8SpK9LU2crklY57dbErRcegLj8mz3vAdPzQmXrVEc5Cal9zYC3IP+jYCGAfQJ/V5CHDYJElFr1K3UzIjndC/5GmZASm/KeoDeCE7uu1RAukFq0iXRsgVehYReImp4AJjBEAWuRMXNxKEsRlkM/y4MjE78gJ8KM6XU989lSvZ6jxzx4QsqbJr0kmfOrFaVxD6N9XPfgaaAWYC75pTKiukcPtp1dNKdpyAJDUSMerIiu6uOSOF1zpBCNroy/Iohh/Xq0mEvTzJ0J4oqdp0ogsI2qfYQOMD+a5ABJtZz1PwY5Bmz3SX0f2/4s3Xd0VwodfqB1onSoHuJDF7pudI8DuVYHx6y6yRNpO2+PweafrMh2Wx3+M0Eq2C62+gx8KkL8QNl6QMDRx6zIwA/rVFCDB4NU+M/Hfj+j2Kg6MUGqUaehdMWlYXzBElNTBJCcXpBolUfv3bJOlFs4h0McUqNBnUKIYGjOeogfekYWm34npyDoMSgm+yT875e+hBsaPxu0Ihyxb2jpekedLBqCBZWq18U0nxfLuz4veFw4VZ9oWqU7OrHGN0n3md3Qnpa0oHtUGOHk0c4JZkG7Kt5/QrAIjdp4ZVt2OqBcUlAoIHSOrwQ5lRrYxeKc8jUnZ/p/4aAKDtOqGsPFa58Ezb+k1P3eH7aI/4jujMIWjyKGjfqOkmrRWDJse1fkkBDkmSUrSE+xyiF3ly5Ln2wCshft0uzqJmK3nmKzJ6L0gJi/lUeeprps1ENaqG+bnfpZPmz/w0tukMDWlM2tTp5V7gxFC3axQOSmRnNuT0xYuK1EVOBhNNsjsmuTNDjnzHhN/axY+42sWmH1wdhn7y7ZMaNZgn1/T1zZziICYfKhQmgbNFJsOZEJZBKCWzoNSuGNODCdeMbb9iiWjxxwf/5H1dFr1x8g2+IOOT79PZlqDqQ6UTbuQKej6WJ6r9vLVd05oeCesRBLDOy14It8HG/7pfc+xX9aBHAudmuX8pcLh/Efy8B7jXNFCAJvrMSnhTwjGkRSYEOIAPMsRoIsvF2aPKqxljv0R9NGBbhkJ9iyk1M22UTsRKg3zyI66TqPgVCd0LkKFxaXPFJs9XzWhWrDafWdPAmjJcAXHkLeVeNSEhOp2wHJpyq0x5pz+xDd2lEDPG8XDKH3WPzFuRwFkHND06exed845v8WXHALHIYKfnMmSvJ2X3UmDrMxuTbxXjrntuEgCPOaWPIzUm0Iax4iZjzkuWYsY3AvUTVkxCCnN8wclX0LoWHW5KYutZwc6Tmm/JmshGiwhQeTcakU+vgpTOLh3hscZJUz1tSgtRATufXV+uYQ6gm9wvlQW4oAk2/nOvdcBOBSIKLLsvKSrXgW3D247AoSburVx2jSILf6RkHFibbKOSq8Klr0JrFwnnEwOP/tfc7JDPVZZgsd1mikUfK3Za88vBZxR8E/qcFkHBbsQjFwIXK72bzCVk0dclTb+pM0+vfyP+scb2wChuH/MO1/jl7t/dKxBaJJqm9u9afIyNZXJKtcZK33bG2eAYPu7AOgymLnz5COvihOXbNBjaZwTSx5q9BBcWlBJgfpnTbieratW1juw+bYMlbRJ6Arp0EBb4hyITvtuJqEP/8J32nyvbFs7hNv8Qbr3EHnyvhRy6cojMnkFEPM8YUlMTyVR5CsjY/m3sfag2Acy++V2Bi9qA/ZLrJfgAo0z0Tjx9QRcIyDbpNA9+zzaYzFzm0djixhsSRx2Sz21xMIdh3ea0Zy9CrzxsctjYIQ6jLAmHDqsDGUqY3hs2i/AUkro5EX3qCP1k5QmFyVCi45WDSdrawxjFhviB0fqbGhjuLBqfqGHG+IZGqVilfQ8zOm6WV2DOM9+WXbgnGcOIR0t4I0lpTpoCTZRPTEKZkmfgW8DxzgP3ca+w06s/9NY3I+pjD7crA3GKDzPAf/RUQxqNuOejm6lELWP2Xa1LMHWI7yrFjF1sJNOVeABYeOE3lMYz3zcu/3TVySO4t2bne84d5gcVEV62qc+z+6/WexlpwFnOb8B2aCYexSvMPYHjpm4SuFko8We0J7lUBqPyll+Pz11oDeKEeEyLxTC3GX53BjfwSk3KutR18nOKVdo3JrK7WGb48mlRLnkZR79CZ4xgBdbKvx8BmouSxglmrW5GN5PysO97NDkOJsHFvNHynfg7jhAm/bKwryVpODa8zhWGmI4Vxjf/gTMyJe6Ev505X4mdMFw9A8CwpjX7GOcMyxYRV9vWqIKvFmlu43wQtOTWalUtq0TVDhI1wbF5/rOwz04AV3oWIt4MRz/12MNsMxmNuVpvkX+bE+pRaEdppdIbrRar4fWyHMLlMSlDAxtyQbvXkRgf9lZD7JXM1cEe2Y4qJcQfmezCPx62SJ1IqMWl1ay6RdJgrjIWtxvT/mZyugKxtKOcNDz2AKzngAYffrfP+cTG9ZHl/glXgrpviwPDoZIbPaSUnR4unIjTZh2Io+WmPRgFwD0NXa8Ey81gMTo/dBOC7+AWHn89VgqAOqfQHFXM8djwt8TIPwrrFY2y3UqVlfN5lKdIzfmZkGtDuD0i057rnpYrm5eViyrKSpXplJoEnV3s4E2HpcFPeZSdJ+QGXoR2uEuRk44nxxeE08LyYuNGS8kByEBArME/T6K/1O1bUYz/IVDa0l2aIdsrb6l/ltjVcEVIHc17yeZjMNXFwYB1s8tCsTozWfzXNoVp1DNq+JbC3oIqjEmBisO5ARHxXzo7hrcNjTC955sljexmQ2Xpttw/jptyX/iBTlLE7ktz9hKQArij9aTaKK5OsM62DwLKw390KEt83wB2tNOTbaviMdOuYEM2uRd93hf+vpeK8f3VUfENMgGstSWs9ZtzZHaRa0H1YAawusra/lQwzwn+N/gbG13IKQwU66sOLQesiYaNOgdCCXxRsckWKh42xxygVe/JVo0e1sBMj/uJ8Gh67biX2f5DDFWUqbmL4h8RMzMycWbVOdmdkZBUqkn87C3eNTn4GVhr5DNdodX8YwYRoWDQDZveWrGtPAP7+jzlKQDT5Ob86HUJKaYLAPW+MxwXelolgutw1aOaVpdkj3YMv7LHei16WxqRp1JNIucbhKUtY8XVcPYn2j/Zs71QCnUWJOCY7I9zH1zsCFYENT4bBlDDGbFr68VpOllUE3UijEYxcAJIQKqWG96lrLvN+AklLMcFmkjMR6ggTSUSXymzvR5b+qy/nvY9q+oQ3QHgNi1hK35E68DrWB5U2CsrdCdFLm9zH2bvbjaYFTV5TytwpO7GAm9qtsHViStnR3povw9nmMfiKD/VJ3pVPPHZpp3E1dzVvXUkElQnSnZTJ0TiPXpDJGb80nz/LLTwzQS8Q0z5Z1CAj15zHet8OAz679ZPoR26t//rhtrowGwETMWvdHrvL64+md5Jra4eWYLeGf3I6hDzCo4Cz9og0ub+V8MzMCylo3ovEPftSfrI6ks2E5yJpBhJ+688zzrpLL616TCMeOACNzWRMbR2GfcmOfYwhf6xC7VWQJbUEVbgt9+S6bTrKL+6QxGiw7erX/4GMrQSzzMtfFAOlmStuGLSGWr4FWFa9uxaXDF6n7WeruK+kq/ped06Fct2EH0e9/tu6+KbtXU6dIZng+S6jJaUt6wd40w6Is5lYfA6aop/2jHUWtSpBztMSm/44iLGH2CoTICMgWp6/emeZ15tHieTUVVv+vtB2JpapipvI8gBs0EJuzI03Mxlworxu6wGmJItsvLXH9gnoelL4P6xSmkEiIfAYkbT+WFZ64e1n4iwdBYT4W65G8XapJRBuLAxDQDLTQ0ngiXR7Kv6ntlHb+Ef6yPAjRa3YzDCQWtPZ3CLssYaZiXWdik3LsAGr/IyEk7Kv9VKga25S40TZTd6unFiBbXsJ4NaaYCWOa3+Plx4NJLpsSIySx0H9OPzp7SZuMbsp7OkuJplvHWbYtbYWF6hX0D89ZzyX4A7Kzq5VT+A8J6KrfJf/Fw87Uq5zbK2i8IYB2l6A+YrggGNG24UulhT0+FaBirTDJj8AO/KgC0CmCKxycVG9WaC9qt9n5g8StdCDjQHHNedfsZraCPt3WQjHseCVxbHgvkroDMWSlcPCJGGA0XWSBXtEdaQ8vn/CBnn0e6sG7m7mEzpZIdHz54GoZy4wxuqQwuofdeVe0MIRZ1atZcQjbBq
*/