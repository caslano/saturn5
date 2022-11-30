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
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
*/