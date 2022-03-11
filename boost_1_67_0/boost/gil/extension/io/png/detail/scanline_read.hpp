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