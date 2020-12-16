//
// Copyright 2007-2012 Christian Henning, Lubomir Bourdev
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_EXTENSION_IO_TIFF_DETAIL_SCANLINE_READ_HPP
#define BOOST_GIL_EXTENSION_IO_TIFF_DETAIL_SCANLINE_READ_HPP

#include <boost/gil/extension/io/tiff/detail/device.hpp>
#include <boost/gil/extension/io/tiff/detail/is_allowed.hpp>
#include <boost/gil/extension/io/tiff/detail/reader_backend.hpp>

#include <boost/gil/io/base.hpp>
#include <boost/gil/io/bit_operations.hpp>
#include <boost/gil/io/conversion_policies.hpp>
#include <boost/gil/io/device.hpp>
#include <boost/gil/io/reader_base.hpp>
#include <boost/gil/io/row_buffer_helper.hpp>
#include <boost/gil/io/scanline_read_iterator.hpp>

#include <algorithm>
#include <functional>
#include <string>
#include <type_traits>
#include <vector>

// taken from jpegxx - https://bitbucket.org/edd/jpegxx/src/ea2492a1a4a6/src/ijg_headers.hpp
#ifndef BOOST_GIL_EXTENSION_IO_TIFF_C_LIB_COMPILED_AS_CPLUSPLUS
    extern "C" {
#endif

#include <tiff.h>
#include <tiffio.h>

#ifndef BOOST_GIL_EXTENSION_IO_TIFF_C_LIB_COMPILED_AS_CPLUSPLUS
    }
#endif

namespace boost { namespace gil {

///
/// TIFF scanline reader
///
template< typename Device >
class scanline_reader< Device
                     , tiff_tag
                     >
    : public reader_backend< Device
                           , tiff_tag
                           >
{
public:

    using tag_t = tiff_tag;
    using backend_t = reader_backend<Device, tag_t>;
    using this_t = scanline_reader<Device, tag_t>;
    using iterator_t = scanline_read_iterator<this_t>;

    scanline_reader( Device&                                device
                   , const image_read_settings< tiff_tag >& settings
                   )
    : backend_t( device
               , settings
               )
    {
        initialize();
    }

    /// Read part of image defined by View and return the data.
    void read( byte_t* dst, int pos )
    {
        _read_function( this, dst, pos );
    }

    /// Skip over a scanline.
    void skip( byte_t* dst, int pos )
    {
        this->_read_function( this, dst, pos );
    }

    iterator_t begin() { return iterator_t( *this ); }
    iterator_t end()   { return iterator_t( *this, this->_info._height ); }

private:

    void initialize()
    {
        io_error_if( this->_info._is_tiled
                   , "scanline_reader doesn't support tiled tiff images."
                   );

        if( this->_info._photometric_interpretation == PHOTOMETRIC_PALETTE )
        {

            this->_scanline_length = this->_info._width
                                   * num_channels< rgb16_view_t >::value
                                   * sizeof( channel_type<rgb16_view_t>::type );

            this->_io_dev.get_field_defaulted( this->_red
                                        , this->_green
                                        , this->_blue
                                        );

            _buffer = std::vector< byte_t >( this->_io_dev.get_scanline_size() );

            switch( this->_info._bits_per_sample )
            {
                case 1:
                {
                    using channel_t = channel_type<get_pixel_type<gray1_image_t::view_t>::type>::type;

                    int num_colors = channel_traits< channel_t >::max_value() + 1;

                    this->_palette = planar_rgb_view( num_colors
                                              , 1
                                              , this->_red
                                              , this->_green
                                              , this->_blue
                                              , sizeof(uint16_t) * num_colors
                                              );

                    _read_function = std::mem_fn(&this_t::read_1_bit_index_image);

                    break;
                }

                case 2:
                {
                    using channel_t = channel_type<get_pixel_type<gray2_image_t::view_t>::type>::type;

                    int num_colors = channel_traits< channel_t >::max_value() + 1;

                    this->_palette = planar_rgb_view( num_colors
                                              , 1
                                              , this->_red
                                              , this->_green
                                              , this->_blue
                                              , sizeof(uint16_t) * num_colors
                                              );

                    _read_function = std::mem_fn(&this_t::read_2_bits_index_image);

                    break;
                }
                case 4:
                {
                    using channel_t = channel_type<get_pixel_type<gray4_image_t::view_t>::type>::type;

                    int num_colors = channel_traits< channel_t >::max_value() + 1;

                    this->_palette = planar_rgb_view( num_colors
                                              , 1
                                              , this->_red
                                              , this->_green
                                              , this->_blue
                                              , sizeof(uint16_t) * num_colors
                                              );

                    _read_function = std::mem_fn(&this_t::read_4_bits_index_image);

                    break;
                }

                case 8:
                {
                    using channel_t = channel_type<get_pixel_type<gray8_image_t::view_t>::type>::type;

                    int num_colors = channel_traits< channel_t >::max_value() + 1;

                    this->_palette = planar_rgb_view( num_colors
                                              , 1
                                              , this->_red
                                              , this->_green
                                              , this->_blue
                                              , sizeof(uint16_t) * num_colors
                                              );

                    _read_function = std::mem_fn(&this_t::read_8_bits_index_image);

                    break;
                }

                case 16:
                {
                    using channel_t = channel_type<get_pixel_type<gray16_image_t::view_t>::type>::type;

                    int num_colors = channel_traits< channel_t >::max_value() + 1;

                    this->_palette = planar_rgb_view( num_colors
                                              , 1
                                              , this->_red
                                              , this->_green
                                              , this->_blue
                                              , sizeof(uint16_t) * num_colors
                                              );

                    _read_function = std::mem_fn(&this_t::read_16_bits_index_image);

                    break;
                }

                case 24:
                {
                    using channel_t = channel_type<get_pixel_type<gray24_image_t::view_t>::type>::type;

                    int num_colors = channel_traits< channel_t >::max_value() + 1;

                    this->_palette = planar_rgb_view( num_colors
                                              , 1
                                              , this->_red
                                              , this->_green
                                              , this->_blue
                                              , sizeof(uint16_t) * num_colors
                                              );

                    _read_function = std::mem_fn(&this_t::read_24_bits_index_image);

                    break;
                }

                case 32:
                {
                    using channel_t = channel_type<get_pixel_type<gray32_image_t::view_t>::type>::type;

                    int num_colors = channel_traits< channel_t >::max_value() + 1;

                    this->_palette = planar_rgb_view( num_colors
                                              , 1
                                              , this->_red
                                              , this->_green
                                              , this->_blue
                                              , sizeof(uint16_t) * num_colors
                                              );

                    _read_function = std::mem_fn(&this_t::read_32_bits_index_image);

                    break;
                }
                default: { io_error( "Not supported palette " ); }
            }
        }
        else
        {
            this->_scanline_length = this->_io_dev.get_scanline_size();

            if( this->_info._planar_configuration == PLANARCONFIG_SEPARATE )
            {
                io_error( "scanline_reader doesn't support planar tiff images." );
            }
            else if( this->_info._planar_configuration == PLANARCONFIG_CONTIG )
            {

                // the read_data function needs to know what gil type the source image is
                // to have the default color converter function correctly

                switch( this->_info._photometric_interpretation )
                {
                    case PHOTOMETRIC_MINISWHITE:
                    case PHOTOMETRIC_MINISBLACK:
                    {
                        switch( this->_info._bits_per_sample )
                        {
                            case  1:
                            case  2:
                            case  4:
                            case  6:
                            case  8:
                            case 10:
                            case 12:
                            case 14:
                            case 16:
                            case 24:
                            case 32: { _read_function = std::mem_fn(&this_t::read_row); break; }
                            default: { io_error( "Image type is not supported." ); }
                        }

                        break;
                    }

                    case PHOTOMETRIC_RGB:
                    {
                        switch( this->_info._samples_per_pixel )
                        {
                            case 3:
                            {
                                switch( this->_info._bits_per_sample )
                                {
                                    case  2:
                                    case  4:
                                    case  8:
                                    case 10:
                                    case 12:
                                    case 14:
                                    case 16:
                                    case 24:
                                    case 32: { _read_function = std::mem_fn(&this_t::read_row);  break; }
                                    default: { io_error( "Image type is not supported." ); }
                                }

                                break;
                            }

                            case 4:
                            {
                                switch( this->_info._bits_per_sample )
                                {
                                    case  2:
                                    case  4:
                                    case  8:
                                    case 10:
                                    case 12:
                                    case 14:
                                    case 16:
                                    case 24:
                                    case 32: { _read_function = std::mem_fn(&this_t::read_row);  break; }
                                    default: { io_error( "Image type is not supported." ); }
                                }

                                break;
                            }

                            default: { io_error( "Image type is not supported." ); }
                        }

                        break;
                    }
                    case PHOTOMETRIC_SEPARATED: // CYMK
                    {
                        switch( this->_info._bits_per_sample )
                        {
                            case  2:
                            case  4:
                            case  8:
                            case 10:
                            case 12:
                            case 14:
                            case 16:
                            case 24:
                            case 32: { _read_function = std::mem_fn(&this_t::read_row);  break; }
                            default: { io_error( "Image type is not supported." ); }
                        }

                        break;
                    }

                    default: { io_error( "Image type is not supported." ); }
                }
            }
            else
            {
                io_error( "Wrong planar configuration setting." );
            }
        }
    }

    template< typename Src_View >
    void read_n_bits_row( byte_t* dst, int pos )
    {
        using dst_view_t = rgb16_view_t;

        this->_io_dev.read_scanline( _buffer
                                   , pos
                                   , 0
                                   );

        Src_View src_view = interleaved_view( this->_info._width
                                            , 1
                                            , (typename Src_View::x_iterator) &_buffer.front()
                                            , this->_scanline_length
                                            );

        dst_view_t dst_view = interleaved_view( this->_info._width
                                              , 1
                                              , (typename dst_view_t::value_type*) dst
                                              , num_channels< dst_view_t >::value * 2 * this->_info._width
                                              );


        typename Src_View::x_iterator   src_it = src_view.row_begin( 0 );
        typename dst_view_t::x_iterator dst_it = dst_view.row_begin( 0 );

        for( dst_view_t::x_coord_t i = 0
           ; i < this->_info._width
           ; ++i, src_it++, dst_it++
           )
        {
            auto const c = static_cast<std::uint16_t>(get_color(*src_it, gray_color_t()));
            *dst_it = this->_palette[c];
        }
    }

    void read_1_bit_index_image( byte_t* dst, int pos )
    {
        read_n_bits_row< gray1_image_t::view_t >( dst, pos );
    }

    void read_2_bits_index_image( byte_t* dst, int pos )
    {
        read_n_bits_row< gray2_image_t::view_t >( dst, pos );
    }

    void read_4_bits_index_image( byte_t* dst, int pos )
    {
        read_n_bits_row< gray4_image_t::view_t >( dst, pos );
    }

    void read_8_bits_index_image( byte_t* dst, int pos )
    {
        read_n_bits_row< gray8_image_t::view_t >( dst, pos );
    }

    void read_16_bits_index_image( byte_t* dst, int pos )
    {
        read_n_bits_row< gray16_image_t::view_t >( dst, pos );
    }

    void read_24_bits_index_image( byte_t* dst, int pos )
    {
        read_n_bits_row< gray24_image_t::view_t >( dst, pos );
    }

    void read_32_bits_index_image( byte_t* dst, int pos )
    {
        read_n_bits_row< gray32_image_t::view_t >( dst, pos );
    }

    void read_row(byte_t* dst, int pos )
    {
         this->_io_dev.read_scanline( dst
                                    , pos
                                    , 0
                                    );
    }

private:

    std::vector< byte_t> _buffer;
    detail::mirror_bits<std::vector<byte_t>, std::true_type> _mirror_bites;
    std::function<void(this_t*, byte_t*, int)> _read_function;
};

} // namespace gil
} // namespace boost

#endif

/* scanline_read.hpp
ny9YDGuTLaGG0UUYIBpKxAtb6Z/rJFb6WQFiYxHQ0sai55cWC4UghElfWCwLEB5FeA5hDcIuhDHHLJaZCAuOAY7wDsJOhANIO4HwM0IY3jsifI/47/AchhCLoCF8gqAQ/t390KPR5h0U7MpwO4RsZO7kzoXLIfkfe2y45jEK3BBNMS+Fb58n90K58Xeo9RcDLe77zFO4VDpVIgb58K8R/PYGfgHh30xDURlivItBfH+IcRc8ipzWRBKfn0aypzqt+Crq6YPBfMKbwXlce7VTVNL2iwLNwpNXltquf34z8zft2eXS46GOcumxqkbcT9L6CQs1T0mIDMJ2TQ507FoTMMoMDDtMvrUmu3ZGU1oDhtioFwzPkSr0JVlR6RZjRTXzClpRhRsrqkzdXFFNfoYKkkIhmLIOqn1Gcq8nAV6nkgycMnr9XF37DKEq919UHGJcLffjWCi6i2kSilS3Xgg071z0VReRyZh4nYCTbl+f4uE1Qk98nFr0LCu6Kb0b0qmv91VzECPtYRE9kTIuWEaeCubyKr6iZQOncdOxhelQ+au8wujCdzLJ381M7lHXzEUverwZrV4GY5yFdk0+lw7cP1Y/3OjxMIt5AsxF1Yx7djgrd7WRo6ILqIc7xjhWj/E/Vj+GGsmqxNWLxklxxV05BwVeiQIRf5Pif0NcjwFtlR/ku5wcRoA5QT4fyY1YPPGNS7Uf0rYxmiZIeMNILZ4fp6pY/m7ta8PRe7ENYt1W9Q4yBklkUw2/Ip3e2FiheEQMXStuawxOHyMRSkq1Dk/zglqx4EWRHjiB+L8UiRg++8iO5VFGrScWJV0g9cyCkbJrmY4EjJOf2TWRCBoa06CBfWmgx2Oexl53idlYZrARMwWvpR6i2TKW/My8iBnyAJAMnkYaCPcCQWug28PqouhpgciW8aUF31ksFPogrP3WYtmPcALBjXAO4QLC5f3L3C8dr4yjRf297QwFSSMuiVC52o9pxS6sGiOwY0KsyqF96yhZHIDo6jS2ftJOIV6LUE7vCxCpQLAgNCE0ICiEcFrk5tiLXasQFtQ4sj34h2gRQg7S6/EsU2df5gVBx1dgYmqJk42P9QZWnJPVt9oRwKdre5eGGE5RD0Pib3pWEAc9j25SMiKQmHshgAjd+FS0B4PjJe7ddS/TiXNn6582II16+GMVZ6mH7/OcsPPa/9kAWorbEXuKOHH3St6vhOuF9Ha7vDXo8+ntlpVi4HsPvdwkScbmKV6S7MWL8LU4wB1JwK4+oD6IABGSR+l96e3CCmOX5chjK2E1G8l06BMhboGX/YEH55PTZHD+7lwg9Lqn9PaBQK1aYVpxV/+RJ97V+qcQKRRVpu/hiCtb3y6QbH2jRFbpcrcGSwr9VcTUQ6AipuxPW6h8fnVU6MXGj41Gq1UoFCAxJEbrkRyr4cAzzrQeRzolpSPJPV4Mm7M5j7EKH+jhJbGySh726WfkuYLy9FCOV0xL3SjVCo1KSZdYHeGIouZW4xiY21M8j+i9ZR+1pSgE7VOGxtcuEVua6Qs2YpjXmmB3rzwv8bfEkM3RVVixLO5O/r+ymaMHXhSOrmxkjooJ36Ic9PYeaUkuxQY7VkGtB6qaa+ChMDy/tcOrXJrVMXO1OsVrkVpVDwSMVGxiolp5BPgBgLQZ5hU9rtHJGPRnROxJrlW53UF9Peffp/7Cz+i/3h3Kr0/wazrZ4zWJPd4SXMMxjwPpnttsHkxnA1/V/0Lj7Cngn0EfyXuJtJVFdKWZepJqg0qQaetAPIHShMyTCaVyKVub/8LQKpWEZLlP//SvDKpVqyWtXD0vkXpaV3DW5ZT1LYGWqs8lslrNnerxmCsr8Ywcd9niSpucTdc=
*/