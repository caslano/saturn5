//
// Copyright 2012 Kenneth Riddile, Christian Henning
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_EXTENSION_IO_TARGA_DETAIL_READ_HPP
#define BOOST_GIL_EXTENSION_IO_TARGA_DETAIL_READ_HPP

#include <boost/gil/extension/io/targa/tags.hpp>
#include <boost/gil/extension/io/targa/detail/reader_backend.hpp>
#include <boost/gil/extension/io/targa/detail/is_allowed.hpp>

#include <boost/gil/io/base.hpp>
#include <boost/gil/io/bit_operations.hpp>
#include <boost/gil/io/conversion_policies.hpp>
#include <boost/gil/io/device.hpp>
#include <boost/gil/io/dynamic_io_new.hpp>
#include <boost/gil/io/reader_base.hpp>
#include <boost/gil/io/row_buffer_helper.hpp>
#include <boost/gil/io/typedefs.hpp>

#include <type_traits>
#include <vector>

namespace boost { namespace gil {

#if BOOST_WORKAROUND(BOOST_MSVC, >= 1400)
#pragma warning(push)
#pragma warning(disable:4512) //assignment operator could not be generated
#endif

///
/// Targa Reader
///
template< typename Device
        , typename ConversionPolicy
        >
class reader< Device
            , targa_tag
            , ConversionPolicy
            >
    : public reader_base< targa_tag
                        , ConversionPolicy
                        >
    , public reader_backend< Device
                           , targa_tag
                           >
{
private:

    using this_t = reader<Device, targa_tag, ConversionPolicy>;
    using cc_t = typename ConversionPolicy::color_converter_type;

public:

    using backend_t = reader_backend<Device, targa_tag>;

    reader( const Device&                           io_dev
          , const image_read_settings< targa_tag >& settings
          )
    : reader_base< targa_tag
                 , ConversionPolicy
                 >()
    , backend_t( io_dev
               , settings
               )
    {}

    reader( const Device&                         io_dev
          , const cc_t&                           cc
          , const image_read_settings< targa_tag >& settings
          )
    : reader_base< targa_tag
                 , ConversionPolicy
                 >( cc )
    , backend_t( io_dev
               , settings
               )
    {}

    template< typename View >
    void apply( const View& dst_view )
    {
        using is_read_and_convert_t = typename std::is_same
            <
                ConversionPolicy,
                detail::read_and_no_convert
            >::type;

        io_error_if( !detail::is_allowed< View >( this->_info, is_read_and_convert_t() )
                   , "Image types aren't compatible."
                   );

        switch( this->_info._image_type )
        {
            case targa_image_type::_rgb:
            {
                if( this->_info._color_map_type != targa_color_map_type::_rgb )
                {
                    io_error( "Inconsistent color map type and image type in targa file." );
                }

                if( this->_info._color_map_length != 0 )
                {
                    io_error( "Non-indexed targa files containing a palette are not supported." );
                }

                switch( this->_info._bits_per_pixel )
                {
                    case 24:
                    {
                        this->_scanline_length = this->_info._width * ( this->_info._bits_per_pixel / 8 );

                        if( this->_info._screen_origin_bit )
                        {
                            read_data< bgr8_view_t >( flipped_up_down_view( dst_view ) );
                        }
                        else
                        {
                            read_data< bgr8_view_t >( dst_view );
                        }

                        break;
                    }
                    case 32:
                    {
                        this->_scanline_length = this->_info._width * ( this->_info._bits_per_pixel / 8 );

                        if( this->_info._screen_origin_bit )
                        {
                            read_data< bgra8_view_t >( flipped_up_down_view( dst_view ) );
                        }
                        else
                        {
                            read_data< bgra8_view_t >( dst_view );
                        }

                        break;
                    }
                    default:
                    {
                        io_error( "Unsupported bit depth in targa file." );
                        break;
                    }
                }

                break;
            }
            case targa_image_type::_rle_rgb:
            {
                if( this->_info._color_map_type != targa_color_map_type::_rgb )
                {
                    io_error( "Inconsistent color map type and image type in targa file." );
                }

                if( this->_info._color_map_length != 0 )
                {
                    io_error( "Non-indexed targa files containing a palette are not supported." );
                }

                switch( this->_info._bits_per_pixel )
                {
                    case 24:
                    {
                        if( this->_info._screen_origin_bit )
                        {
                            read_rle_data< bgr8_view_t >( flipped_up_down_view( dst_view ) );
                        }
                        else
                        {
                            read_rle_data< bgr8_view_t >( dst_view );
                        }
                        break;
                    }
                    case 32:
                    {
                        if( this->_info._screen_origin_bit )
                        {
                            read_rle_data< bgra8_view_t >( flipped_up_down_view( dst_view ) );
                        }
                        else
                        {
                            read_rle_data< bgra8_view_t >( dst_view );
                        }
                        break;
                    }
                    default:
                    {
                        io_error( "Unsupported bit depth in targa file." );
                        break;
                    }
                }

                break;
            }
            default:
            {
                io_error( "Unsupported image type in targa file." );
                break;
            }
        }
    }

private:

    // 8-8-8 BGR
    // 8-8-8-8 BGRA
    template< typename View_Src, typename View_Dst >
    void read_data( const View_Dst& view )
    {
        byte_vector_t row( this->_info._width * (this->_info._bits_per_pixel / 8) );

        // jump to first scanline
        this->_io_dev.seek( static_cast< long >( this->_info._offset ));

        View_Src v = interleaved_view( this->_info._width,
                                       1,
                                       reinterpret_cast<typename View_Src::value_type*>( &row.front() ),
                                       this->_info._width * num_channels< View_Src >::value
                                     );

        typename View_Src::x_iterator beg = v.row_begin( 0 ) + this->_settings._top_left.x;
        typename View_Src::x_iterator end = beg + this->_settings._dim.x;

        // read bottom up since targa origin is bottom left
        for( std::ptrdiff_t y = this->_settings._dim.y - 1; y > -1; --y )
        {
            // @todo: For now we're reading the whole scanline which is
            // slightly inefficient. Later versions should try to read
            // only the bytes which are necessary.
            this->_io_dev.read( &row.front(), row.size() );
            this->_cc_policy.read( beg, end, view.row_begin(y) );
        }
    }

    // 8-8-8 BGR
    // 8-8-8-8 BGRA
    template< typename View_Src, typename View_Dst >
    void read_rle_data( const View_Dst& view )
    {
        targa_depth::type bytes_per_pixel = this->_info._bits_per_pixel / 8;
        size_t image_size = this->_info._width * this->_info._height * bytes_per_pixel;
        byte_vector_t image_data( image_size );

        this->_io_dev.seek( static_cast< long >( this->_info._offset ));

        for( size_t pixel = 0; pixel < image_size; )
        {
            targa_offset::type current_byte = this->_io_dev.read_uint8();

            if( current_byte & 0x80 ) // run length chunk (high bit = 1)
            {
                uint8_t chunk_length = current_byte - 127;
                uint8_t pixel_data[4];
                for( size_t channel = 0; channel < bytes_per_pixel; ++channel )
                {
                    pixel_data[channel] = this->_io_dev.read_uint8();
                }

                // Repeat the next pixel chunk_length times
                for( uint8_t i = 0; i < chunk_length; ++i, pixel += bytes_per_pixel )
                {
                    memcpy( &image_data[pixel], pixel_data, bytes_per_pixel );
                }
            }
            else // raw chunk
            {
                uint8_t chunk_length = current_byte + 1;

                // Write the next chunk_length pixels directly
                size_t pixels_written = chunk_length * bytes_per_pixel;
                this->_io_dev.read( &image_data[pixel], pixels_written );
                pixel += pixels_written;
            }
        }

        View_Src v = flipped_up_down_view( interleaved_view( this->_info._width,
                                                             this->_info._height,
                                                             reinterpret_cast<typename View_Src::value_type*>( &image_data.front() ),
                                                             this->_info._width * num_channels< View_Src >::value ) );

        for( std::ptrdiff_t y = 0; y != this->_settings._dim.y; ++y )
        {
            typename View_Src::x_iterator beg = v.row_begin( y ) + this->_settings._top_left.x;
            typename View_Src::x_iterator end = beg + this->_settings._dim.x;
            this->_cc_policy.read( beg, end, view.row_begin(y) );
        }
    }
};

namespace detail {

class targa_type_format_checker
{
public:

    targa_type_format_checker( const targa_depth::type& bpp )
    : _bpp( bpp )
    {}

    template< typename Image >
    bool apply()
    {
        if( _bpp < 32 )
        {
            return pixels_are_compatible< typename Image::value_type, rgb8_pixel_t >::value
                   ? true
                   : false;
        }
        else
        {
            return pixels_are_compatible< typename Image::value_type, rgba8_pixel_t >::value
                   ? true
                   : false;
        }
    }

private:

    // to avoid C4512
    targa_type_format_checker& operator=( const targa_type_format_checker& ) { return *this; }

private:

    const targa_depth::type _bpp;
};

struct targa_read_is_supported
{
    template< typename View >
    struct apply : public is_read_supported< typename get_pixel_type< View >::type
                                           , targa_tag
                                           >
    {};
};

} // namespace detail

///
/// Targa Dynamic Image Reader
///
template< typename Device >
class dynamic_image_reader< Device
                          , targa_tag
                          >
    : public reader< Device
                   , targa_tag
                   , detail::read_and_no_convert
                   >
{
    using parent_t = reader<Device, targa_tag, detail::read_and_no_convert>;

public:

    dynamic_image_reader( const Device&                           io_dev
                        , const image_read_settings< targa_tag >& settings
                        )
    : parent_t( io_dev
              , settings
              )
    {}

    template< typename ...Images >
    void apply( any_image< Images... >& images )
    {
        detail::targa_type_format_checker format_checker( this->_info._bits_per_pixel );

        if( !construct_matched( images
                              , format_checker
                              ))
        {
            io_error( "No matching image type between those of the given any_image and that of the file" );
        }
        else
        {
            this->init_image( images
                            , this->_settings
                            );

            detail::dynamic_io_fnobj< detail::targa_read_is_supported
                                    , parent_t
                                    > op( this );

            apply_operation( view( images )
                           , op
                           );
        }
    }
};

#if BOOST_WORKAROUND(BOOST_MSVC, >= 1400)
#pragma warning(pop)
#endif

} // namespace gil
} // namespace boost

#endif

/* read.hpp
sRlanyCu8HuAhWx/aEWlrqgPtXcsOcHgtC7niXBjXNkl9ZMW1I1djmv1B+z24JzZ3Rk5DOLYdjQs9PjKVyhWVk1FpBSHDo08ygVuO7xrCFu1FJOSMledwRAxDFbqGCwjEVdc1Tq45ztxZQiwTn1AhJHfCnmDk9wVownomgtntdlZBwoFKdzw5MapIWIB7iFe6t/pT99EV0hRKuuCE0mp1kKJ/Mfu6rGJJCjf6nhcdiDgQjdsmfz7M7ShbhI3naWemH1QbBMDeNAJUwPu4yHJGhuxFJjrwVO7t0GXbJpSWIzlrEJUQjOM5eZ5hkLFSMVYCZ2uCw0Q46njBw//PI41B/mw4FVWXSTRxJ1/x5gfq6i0zTNlxXZQZTXLwCsktKLwHCjN0dM5RgL8RUejp/JagN0TztWuHTUba3uMtizWhjcxzWHNnKNcYJmhyxx1CZaY/dEXMFPFcUEymtaxKSc61mkyvZQe1QfOEYYV71cp5c8EDV5NsAsxOtZvwkBFbSQbJM7cXaE/xapXX1rmiarS4DCYkrRmAtEMjxqHuHxoYxBQrkCm7XRrCo6w2IeI8gbL1rHYGq7cKz19UJrJFX4D7SwUmY9mYe2VGonAZDQedEwI7hvwbTWhL8CZNffKo/V2aVoUgsu7ZwETKBgRzWJJmTY8JrDaT7caBbUHSaqKWMXuNTvtw2n7Yz/J+3gANGxbOFxGbZuALhZWPgX7fINbGXyD2/1bymvvC00A1fOHYZ2pu13PSXOX7MbETpXLlvY0YcNXpmVvw4NADOqd/ZOLcf1erwJLoyihTbt5BE1w+S6gyJpSx1qoUgOV7Fu2SLIaBLYajeHtmwmFTcT3VaOoBQyvIpEML5VmV6tNCd7p+vd30c0B+HZ2bfIM7p37YZo35TygmE5PxGzEDkMOt/vJuefINKOZtDCvk7V/jZm4nj174MQU66abhjSllRof/fwbgH7ubMa9oFr9apTNcHmbOzttb/fbLXGH27Np8LBXAtpjsHge7mpY8ufxSZro6OZBoAnxjAloW2wvCPEM9byqrE+ind6kvVNDz15Nr1XRFyO8shQwd9ouNwDknqyg+UDp+g7qOkbe4lrosA2klnsJvM/JwnMH28qBZerNsYffRdIjkuTemPCo2JB7d9dH0sPniyCkoDNxvGLEdbyKcEEnmKHCE5h0eN2+7oA5Q5Xz5WRo7Eo+ctovBstEH+bY9ZhY1oK1iU74kq0JOmyFmic3oXOaGG+GpYlN2Jq9CQ64TzYPDve4V2uOHuqZDhwbwlJXABSn010ZggtjYSOAzkNz0k6RgRdqzB5fWIAmygMhzBkdjlZ/boFcSt1eFphtTLtFB4ksYwEfQwHKNyF+ut/nABi+F86psC1/55x36U59qD356/yvjGxYZOOPOVVoms3zwW1Cdad0OJG6OKM6A4Os/fMX3V4aLsLpuohX26t3HRaQWn8Xpr2rKvUS/fiKLMINLegyb1+DKIJmEMB+LqKLVEcwXEaM4JwlOlmq7V8mm1Tux6EoP4WFoOF+6aWD/JG2yB/HuYt5OwZDCbZU09DBYYAY+caBtVNMV1yyRdFliCLSSIl6MtcFUnydp1mOFkTBssjUGiBe++tHq46uEEZE/LW6SKEhyedlgfMCBSYCgXe6M0S1ckbSNDSrIyP1z2ovEqX8tFXzyc+zA19AdfCO9N8wKBDw4nBOlQm/yfARV2FnKbobMcpoBTiBMkc8GxwFsb1KVlssH0gp0N4GT7QUL/VbU9RO/ROoWqU2cGTXZol82GKxQ4S2PLURb9WFblwLeu5kdw33SbJOsGsFer3olMBzKVg+hpChA43V/wGA0Kzs9gkqstgTwlBlCZY/9oT7g4AeC1nu73rGqL2yjAVITieA9Gn8owcaM83g4YEdtEKaHHdxtRbOSlZU63fVnop4TmURBcGNzCAUOM6I8EZVSCxzGTRF8Krzh7mPO9ZsKFTQJJNmRDIpTU2BnM95xSQIawqy8ZHLokE2nxzCk7BhNjJingjvTApwIPlXGsGDpE1MIR+1oRRJvk74GgCu4FaCIAQPQ3Ehi+DZTRFd29IoXihrU0wmocRhRtfhgyF4wxFkUq5+kKdJz3pMW7whf/8zqdDN1tdRAvJf4OMSFk/rPhqmGODAMhbGqfreLTHH1PkrsVD8fV8Uqny2WCAimon9eANEerjckGHst0DuoJ9Be829fZyh/bH3EIypIBiCKrUrsDVQAJkA+WpuaA+OyM2g/z/9/5Qo49LMDm/P9KM8CrDRtrDHOAO9ttDEfXasCsd70Mg665/W7ePd3sB5vsyJw4EGXUrXWlnr9VZ0kJLtnmvvHak9PbEU5LH3BPugkhNOx+wYHrhijreWreu8ENPNqrovML9sG9R5A3vLrlXj++khGDElN2zKuJWdMW/oBrdt2+j7IrJgSAdEAoJdGo/RY5aqF/t2YgzBhp7NWP/x2JH0SdBWt4FES8ZxSFKy4qQPPsAdRbupLYb6mGNUAY7LjxeyGFNUtQsQSjWGwScxIOqexxHUPsmsL0fbZaGayoDTyVXxxwIM9oeDQFdqqd14QCB4xICfolQYihyQyEQJS/9dow5kdXqQLG4UI0RBIer3zX1m2O8e3byEXSD30A3R/PwEAUHK1otkiyq740o+EbaIMpewUbCHBww17Aw4TgYOwkR0SVdhSRRC3pZuXnwiFiOQ37dpFKLPE1gkftZ2FLP22I6SCoNI7Hq2IEbIADBWqoJ7TVQBQn0JNQmQiNpTYwE/EeEOKgTepx5IWi8Ilh2A8/VYu4nFXAqqVpQo8jzQe656ERceiQ0N6s35NLE5/g34XLvS1GIDDtbGLu09qDEJ0M+jAKO0bMmUlq0ZRtwKEN3sBQdeIajPruDSAyfxn4FCKy0CVuYRBFFDwBpmQToX9GMFFDgpwktmB/kzoabjIwMb6PJzODHTfCdTwES2uyv/xW9zgz5c0WUvw+D/ohAMOgZjKSlEIja/Gid+e0tGqobvn/VboMfIq0gpwEdUK+IjeNzWSx/AXqnWa36TVfUTwuAphzugDwkvyVCkO8Jp8OwBMBgDeTeAeEsQ7irGa5GRJrpJcSQC26YPFZEZDg2DYkIGIJctQX4Aq2F4V4X/UqGOrNriCkFF+7kIEyJ0kBPS8QSqirtSwNODPsvM7IJZYFQYEg4NzUMUF9CwRmkOrhVR9BIl+QefNUsKwz9BUk7FCG3FLSgqYB1GwzCvqqMvTCUZM64Ak5xW0/274t8O5Ry+vhw9G6iIWxpGWlajFBNy854jSIUhY045HaMvxnwWpEb6FeRwCFkFJmoGQB0W0U/pwrIDXyqqMZGutvf5KUEg3FVY1a5cdpWadO0uiV2gXqHYsGkZAmN2HiQjn+IslmFd/8cmSFZcvZwTxSbWcqGPJJdqsz1q71srT7V80kQ860eiPJ/kKQYQBjI2UdVLkJkN8yHvATozMA1AyD3c8W59qzjh0h2HgsAKPbYXU044QAb+paY1cElyjQEH8Rj7KpNxNxtS8dWx+wSpsk9Tbhj6S0sarW1lWCB40qXZHRQ/KmARGeoPLExsMjZx25dAJMzGByj8uyVFCC4/qhAOU3KvAgHIPpZjcSTH6FSG1b4osDqeY3c0cxD6/R2ESxuWIRJiLr3wFZdUrfyVjNkdROvYt8np1di/yf1kFtpq5tXYt4l/byuyUpF0MMO/Rw2EX8kZtCE6kehDgNwZwNqYPJzDzwHbLRfQDF4UhBaSTaZG2TCxkbKNoEgDuP8sI6pvrOggdFFKJ+3M8k7rupoNDNl++1pvNCMdqy0cq+38KHJhqMee56Jel8DSiR1+PQc+l9mpnaILcP8YGkmyQ/rICmGoF5YIkC1jf3UCFTLYqiYjCJVM1J4WkkN6hk0HALcXstbmnPYXvQPpf4JVAXU5gBaBHRkqQBaBfgaxkEtHzeGCLB9UDbkYfRlkLksPVQBVksEEXYmgUq0O6XdN0yB/MQmOXHvJ/7MAgETJlqQN7hunmNbMPUE491asLyGSi5InxRYQ8c3jKa9hVo/pQ/BDZ7EoJiKmxtpCYDjaN/lqU1Rz4VfNVfN6u5m/jxUK7zHVwjVTFnTFMO3CrerF1af+4YUIWWy4abkPZja9VHQeUg+YM3Etqu/ghsRrNA4Gb2BVu8x7dzcTM3+mQt0RE4DFS0/TuEf0Mar2GCqUsnC0p84fTtol1AqYmSgbPJhBc6INccv3nHDA5G/A4G/A4m+QNGEGAhbjtTx+Lk911kgIAFwf7RL7RouqKTnF87opIZ/4FhsGKyrcKt8Vu61UjEfrP7EqFoFMqYizIWJ01S/WFpxlvGBXtELliT+RkzEQfw/bFWURLuaRQ/Cg66iBtLIizGuvh/8r90Zkftrbry2Cu35fVE818BLo+c3/OWKgyMH/upkXAlXyL9pE3H6YFsACDqxYAq4sTUdj1oBT102BLfGxw4up2dBhAZCVlQDy3tBtA2Fc7BedDlpxHkCUDf6n/MQVhfdf+LylQPdc18JxaOab4qsAkbtPZkRSPuWTtwPrNuQ/iqWYo1xSj9DRJF84FzwdVeObvvVCUDYY/aw2uG2BzDwkrQ7CXhfQptBmGmHLlmIdtQUSakj8KJfv/V2/5ktrz+LL9dOYwkCJXX7pwp7d1//WX/dy5mDPOAJyHUxn6zLcl3PJJ3KxRXFSHOvYF25j5MGeN8F0TKtTeBQAAH5wzmX6acREkQRI5U0hf0DOojlxKhYLBxkduBeycH7m7I89pnRXh06EVk/tAIBiJYyMwDLnZ7mB1WybGo2avdiroWb/VsAK47n6rhmhxLQBxXwYK2GItwRgwXW6vQoSlnolRDxJVxoXaj3LedXARoQnUandnG+JaSSjUwt7XCkhC7hXIXkoU6nhxE8ju9SRW/B2Yo69VhBRDRdJa0ebgKdq0PgptgoVxk3YQZSDtSkbfY8GaL3hH04046pRjEmsYjddJ6AWi9MqRntVTvtis0zTZOH8RiMYwX+U4E9+lrthOvuR/4V0Yxq9kPFMTAE7VpjpGyWhlf/wLb6ZbHZ7s2th1HSGluGclZLA29wMkH0TQPFASQAx4CsX4M0xOQcACwltLCNrHItIBLCTM8pM71eLXFf4/NeIFFsFWMyXcO7gUhsQyRR+zyG2h6FycBAfx757AMxqdI2yN6sMBSgfhzYKdSx/b5YHDLpXQXZYZvIP+xwVFE3p7pILoMJI5GDYPZ+rdXlMN+Jkw8rkYpqy0dSXYv2Clkgu/eTlnMCEwE573q2eiNFvCWo9hpXg6P3LPfL1m1lw0wP/ZGbNghIwjaKVJP/UuSzgATuRTdHTzLc/+mU6FcIkkdij9qD3a+C5vtlHY8ypO7zua90UccYYXpuyCUIoAg6aRvN0/TMWn/TfI+iIk/hhWWRBkyVo/UlSXDhNFq+PChpS2MiLCLyJLFeU2Ta2H1DOXPVH4v0VBUl9CVrLllmx5jPYJNF1FyXbA73fFrmcyNUB4je3SSfgk5D63VZYp0bt8vLDGMtqxUNF7eGx8j8swV7+aSdaACnBsRbOXgKTisc7cntSKgfphtSLZqovcw1754E3VIbq3SYAQanp084bwKitpWwGVj4nalEx8c//IhQdnnMxQOPN3ox1wG7zYU6CtgKywgu2YFBUyBLzjQRF+ocjLNaiLSxc1WoDLOsSzsinWddv0UzYPTSEAnXyTKtDve1u0UdrZV7Jh5i25DAD9rut50rT7jkYa6UO3ONvSatzrS3lxkCuvM6HLmCQoRH9QthWF7KRZAfgvl1uUHlXOheMxJAAdm2fC0mPabRZSuo98WrECErrz8za4yp3DR5LTXqh25qvZYtsgE0MIXuAnM3fCigLnjELBFZvtkvGEXau1eeEBk5KrslUTekdVpHS2AVaok0rWWj0YYESGJGMCMZazIU3G/Nti6p12KAq7xp/e2P93ub8rVLQYLmhpcSZZimBOV12UAhgQxl6VZElGNt5FypH73+Xj7gaJRN88D5hNI7+6WulKqmwvt/b7/E0YXhuj3WC69BaVY4O/mKHYOd+UCNxyJhkwU3TJ7mgjuvBETsFTSTpI16ip8UJdbP5AE/mIJmzb7W3yg8llVRCQH5suEq5mCfx3vQjgjAdG4wwbX1pWyRmldGXKQFjfoTJiOKGggUs3KdJsArEyOxZ4VQU38qHcFbh54EEoU5lhvPvphXPjSVsm3ZzkgzPg5avaic5hMYsAbfEWlQ1xC6kFVp0rOVJrNPOgQxziXaEdzze3H6AGASE5sBsPnGWAaYaBgLOH/gC+x5U2Yb6ywtV0VaygGKzxbiqzoA5ALuZTQXpm1WYeLIZF9BaWQhEooluuqAYWHWEFTBQW6FWlPxELJuMzWzIPr7Tzkmz9AIcuq8YT6PKEVhE6z7h/SefVm5lNa4GnrNloVwoys8vLlqnS8Cczq4crZxsRJuG8PT1jA9Tmu2XwPgPNLM51w8ngi3wiKsE7t6opgiAADlpHGAcCTlpiwIlpQp6I67Je4W7vAoa2UGZFi8lFCSquKVVxHC+s3T4Nl4D1p3agZPeTujEZEDI6W1Ogg1uYua9SxWCtt1uYHfvm/ndD7nHffxV8g0v7bZ1oJMfsH0Cnj5YaguLx7zuA8ByNlv3kRnng8SHigZSwlgP3Na7GdB3CRg3ik0F3mFYLzQNVaVXnOOR60o7b0ShlpZ69cDF+VPtiXbcyVmjmX/W6zFnJ1cN3nrKyf0qbM4O5uZlD2uHdkE7IDc5cIZ50iEvzb7RsuoZRpujASmgiWKkEJbGnCiCKVkhneFk361zS/hyoPv5sFOU9lrmJGck2/N6pNApbdUMZpQupAbMlcJu1Gw//sDN5qH7iktnoK/fMYuSgWDn8e71JZ9wWO8ZWaeOM+NNC6wutE0w+eeKRIdwt7yHpNh+xmkqxbpfZrcwVLEDjNaQ6BvGrpYnOxL1B4WqeFknejunEUvpS7L+oFFq3opsRXsI/KdYSXzrs+msUynTE0+kW/uMHKlkiJT7YKdo+D9vAOyQFuV82z1rTN475lOGpl+ouMI0Q7Uvf0rPA3aVhzr0z7mUzPK9FmVLMxL86kHOyx5YmZsWjUjz+iEvaOw4SJtieASafmFtZDTGGgWUtYHWARaHZ4qEdDNnYWJyZKk3hvT4f++0oUS+2Er1SA9Bd7OV3njNuIegKkaarBQcUZO2zerbsWKuhiAdOc/h+81GlFX24aFNSz2eIBvdlAbwpAdPKoNaqgLVhhJm4Xt23HbN2l8D4FocJPffhBogN3YnN26qxqbHn3pxtcXgAQABwtKAAAG//vlmlWguMH2u1cVjJ7TDvuZ6D8RbmE6sVS9m7uwP1ubb0BIGyQBoeR4Q9WNogskxldILWNzKPDaI57gLV27Q3kMHRTpmIlgJ/4X/yg7alICu1FigfQP2zXtm/NiheJMhR6rBuLd2Q4E+sidUzFeXc/L9vNMY2OXHFXZgi8Q3hzNpQsui2ncH+Kl90Zfkv7HvwVWLL2D/tPpSRuXPvLR1IpIudfr6tGoqMp9ZQjGWJJrpBlD5TIKeL6DpTzPPW/l8dTYsIKjt9IUK6BlqhMafCjqeCWB4rdQY4P5YVnURvhqSCD1OVpe3Co0dqscUDvIFYl3xFJULFuMTZsjL
*/