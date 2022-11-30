//
// Copyright 2007-2012 Christian Henning, Andreas Pokorny, Lubomir Bourdev
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_EXTENSION_IO_PNG_DETAIL_SCANLINE_READ_HPP
#define BOOST_GIL_EXTENSION_IO_PNG_DETAIL_SCANLINE_READ_HPP

#include <boost/gil/extension/io/png/detail/is_allowed.hpp>
#include <boost/gil/extension/io/png/detail/reader_backend.hpp>

#include <boost/gil.hpp> // FIXME: Include what you use!
#include <boost/gil/io/base.hpp>
#include <boost/gil/io/conversion_policies.hpp>
#include <boost/gil/io/device.hpp>
#include <boost/gil/io/reader_base.hpp>
#include <boost/gil/io/row_buffer_helper.hpp>
#include <boost/gil/io/scanline_read_iterator.hpp>
#include <boost/gil/io/typedefs.hpp>

namespace boost { namespace gil {

///
/// PNG Reader
///
template< typename Device >
class scanline_reader< Device
                     , png_tag
                     >
    : public reader_backend< Device
                           , png_tag
                           >
{
public:

    using tag_t = png_tag;
    using backend_t = reader_backend<Device, tag_t>;
    using this_t = scanline_reader<Device, tag_t>;
    using iterator_t = scanline_read_iterator<this_t>;

    //
    // Constructor
    //
    scanline_reader( const Device&                         io_dev
                   , const image_read_settings< png_tag >& settings
                   )
    : reader_backend< Device
                    , png_tag
                    >( io_dev
                     , settings
                     )
    {
        initialize();
    }

    void read( byte_t* dst
             , int
             )
    {
        read_scanline( dst );
    }

    /// Skip over a scanline.
    void skip( byte_t* dst, int )
    {
        read_scanline( dst );
    }

    iterator_t begin() { return iterator_t( *this ); }
    iterator_t end()   { return iterator_t( *this, this->_info._height ); }

private:

    void initialize()
    {
        // Now it's time for some transformations.

        if( little_endian() )
        {
            if( this->_info._bit_depth == 16 )
            {
                // Swap bytes of 16 bit files to least significant byte first.
                png_set_swap( this->get()->_struct );
            }

            if( this->_info._bit_depth < 8 )
            {
                // swap bits of 1, 2, 4 bit packed pixel formats
                png_set_packswap( this->get()->_struct );
            }
        }

        if( this->_info._color_type == PNG_COLOR_TYPE_PALETTE )
        {
            png_set_palette_to_rgb( this->get()->_struct );
        }

        if( this->_info._num_trans > 0 )
        {
            png_set_tRNS_to_alpha( this->get()->_struct );
        }

        // Tell libpng to handle the gamma conversion for you.  The final call
        // is a good guess for PC generated images, but it should be configurable
        // by the user at run time by the user.  It is strongly suggested that
        // your application support gamma correction.
        if( this->_settings._apply_screen_gamma )
        {
            // png_set_gamma will change the image data!

#ifdef BOOST_GIL_IO_PNG_FLOATING_POINT_SUPPORTED
        png_set_gamma( this->get()->_struct
                     , this->_settings._screen_gamma
                     , this->_info._file_gamma
                     );
#else
        png_set_gamma( this->get()->_struct
                     , this->_settings._screen_gamma
                     , this->_info._file_gamma
                     );
#endif // BOOST_GIL_IO_PNG_FLOATING_POINT_SUPPORTED
        }

        // Interlaced images are not supported.
        this->_number_passes = png_set_interlace_handling( this->get()->_struct );
        io_error_if( this->_number_passes != 1
                   , "scanline_read_iterator cannot read interlaced png images."
                   );


        // The above transformation might have changed the bit_depth and color type.
        png_read_update_info( this->get()->_struct
                            , this->get()->_info
                            );

        this->_info._bit_depth = png_get_bit_depth( this->get()->_struct
                                                  , this->get()->_info
                                                  );

        this->_info._num_channels = png_get_channels( this->get()->_struct
                                                    , this->get()->_info
                                                    );

        this->_info._color_type = png_get_color_type( this->get()->_struct
                                                    , this->get()->_info
                                                    );

        this->_scanline_length = png_get_rowbytes( this->get()->_struct
                                                 , this->get()->_info
                                                 );
    }

    void read_scanline( byte_t* dst )
    {
        png_read_row( this->get()->_struct
                    , dst
                    , NULL
                    );
    }
};

} // namespace gil
} // namespace boost

#endif

/* scanline_read.hpp
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
*/