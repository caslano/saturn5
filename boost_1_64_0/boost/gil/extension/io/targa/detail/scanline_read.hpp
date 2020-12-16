//
// Copyright 2012 Kenneth Riddile, Christian Henning
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_EXTENSION_IO_TARGA_DETAIL_SCANLINE_READ_HPP
#define BOOST_GIL_EXTENSION_IO_TARGA_DETAIL_SCANLINE_READ_HPP

#include <boost/gil/extension/io/targa/detail/is_allowed.hpp>
#include <boost/gil/extension/io/targa/detail/reader_backend.hpp>

#include <boost/gil/io/base.hpp>
#include <boost/gil/io/bit_operations.hpp>
#include <boost/gil/io/conversion_policies.hpp>
#include <boost/gil/io/device.hpp>
#include <boost/gil/io/reader_base.hpp>
#include <boost/gil/io/row_buffer_helper.hpp>
#include <boost/gil/io/scanline_read_iterator.hpp>
#include <boost/gil/io/typedefs.hpp>

#include <vector>

namespace boost { namespace gil {

///
/// Targa Scanline Reader
///
template< typename Device >
class scanline_reader< Device
                     , targa_tag
                     >
    : public reader_backend< Device
                           , targa_tag
                           >
{
public:

    using tag_t = targa_tag;
    using backend_t = reader_backend<Device, tag_t>;
    using this_t = scanline_reader<Device, tag_t>;
    using iterator_t = scanline_read_iterator<this_t>;

    //
    // Constructor
    //
    scanline_reader( Device&                                 device
                   , const image_read_settings< targa_tag >& settings
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
        // jump to scanline
        long offset = this->_info._offset
                    + ( this->_info._height - 1 - pos ) * static_cast< long >( this->_scanline_length );

        this->_io_dev.seek( offset );


        read_row( dst );
    }

    /// Skip over a scanline.
    void skip( byte_t*, int )
    {
        this->_io_dev.seek( static_cast<long>( this->_scanline_length )
                          , SEEK_CUR
                          );
    }

    iterator_t begin() { return iterator_t( *this ); }
    iterator_t end()   { return iterator_t( *this, this->_info._height ); }

private:

    void initialize()
    {
        if( this->_info._color_map_type != targa_color_map_type::_rgb )
        {
            io_error( "scanline reader cannot read indexed targa files." );
        }

        if( this->_info._image_type != targa_image_type::_rgb )
        {
            io_error( "scanline reader cannot read this targa image type." );
        }

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

                if( this->_info._screen_origin_bit )
                {
                    io_error( "scanline reader cannot read targa files which have screen origin bit set." );
                }

                switch( this->_info._bits_per_pixel )
                {
                    case 24:
                    case 32:
                    {
                        this->_scanline_length = this->_info._width * ( this->_info._bits_per_pixel / 8 );

                        // jump to first scanline
                        this->_io_dev.seek( static_cast< long >( this->_info._offset ));

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

    void read_row( byte_t* dst )
    {
        this->_io_dev.read( dst, this->_scanline_length );
    }
};

} // namespace gil
} // namespace boost

#endif

/* scanline_read.hpp
iruQW/lwp5rM/Mg4B91VcyZCiom0qj4sEn1yoY8b5HFIZmHKznmbG98urMjId2lXi66BT158zzDC+1Cm6oxxq5Nj1HQ0qBWL87OxDKuyLngMIO487768WXNcY5zbepRYF8xTWDmckpquoEa8M7sOC+hLAuDUF/OY6HYS7KqQRD83m3NjkCv+MKdOrXKJ9fx5Bl8DcJElYQ8hS7SoC7uceDbiSKdqUIWNo8geR2ZHqEeoiAbWHzLzW0ZRwJ+8bOpGwNOBzj9LzKsJ86VZjHkeYf5Sp70yi+Xk3OabdVzx4u5o1mlGEjuQKo7ZqWLLyvwdny/aM5dn46+pGmwqKVmllV7IYkVlqr/gvB+NNqKg+Wy539eYn1nnhQkJdcRu0N2U4r8/gYSus+WaYOhchqH9ohsEbSrZyHd7cxbn3oBcE+e2otwc5NJoboWifSg6dZqKEqjoaRSRnG1z5bb4vXinnixNPqpwzG65Uu94amDsotfwvV76efHLH60oH+FXgN8m/Lbhtwe/H/Crwc8KmNb4dcbvAfwG4vc4fr/an0oYPMT4mNW4xfrhsbSD/DWrM3J955lEc/Jf/6lp+jnBbuTQDcN09Qd5rZTON5DXtHx26OspFM0sO8eyvB1FfP9xpgytjJst3cg2GJH6fn2G8X2HJIqd0CYQCSMRAPpmXpfZvIULcWyX5zUr59Doq4J1+BCmh6xpyRxpx5Zmqn+MoVi5iy8HEPDGObLF9/FUiyvzjf4n1JvfP0xeS/tEy2kiHfmqEUA7VBml7xPR6WE+DtJ2/9ko6f248/L3y4Pmh2sseMtahB9u4F1AwRKFHIMaZCxxUkaWYue3eKcaRDFJF2/p+K3Bq5DYquRjkSx04TcZr36ZWyofa+XjqHxky0eBrDEDv3H4peCXiuydChnerP74Dcfvc/wK8FsLMxST59yP5FH8BH6j8Rua5yzFYwN+y/G7jF8yfmfxq8JvD3478avGbxV+h/A7gYYy8EsocQ60ZNPsW26KBwPfxsxMHxl5LclE35hEFhnWeWbdL/npb+SXpFpfoMAv+yY5L+q+SYlzg4nXv614bp8cjKWpazu/5VI3gz9HUDvLTZSuotXVWhTSIerj9PKOrLcmuJfeXpNv44IlPAU5y4MbuXZ/rv0ppwWnVxP4WAmeElxCb0PlW2rwRXp7sJXupRx7j7yUVUEP5XaRhAlCMYYybpEZVZTxCGU053pVQSe9WFoZjtfAwtpoZHiQQRNuR5SS/TvDY+YKQiI40C6qZtDYeXJJpnooS72cpf4cNJN6fmNjnyx4kQzJpzam0hU8QW+ruKg6uM9EXavirm2jApXBcrMpo5A8B98sWJI4sR5NoDqPncXiSYJSs/hQ4icz5Lm0v5Kj9gLjG834/srptZyeRGnLTcEohV9Hc1GpQumBnL7M+S4Guyp0sG5EUU1LnaHLVxND9wRvodzjRu6LnLszGEu5241cD+dWB6+SjqxvyX2i5nS1CR6h/GUy318nv4TyX2gpdarEmSzlT5lTwpkRlPk2ZY6QGNZSxgLKcMsMGnWVs0XvltLx9ciP2FROEHfI8kX0NlK0kzhnlDjPcrlbNA3nRFBOd3GtRSjHTDkpQoRzIimnlfgOOTI4eegcOYu5+/n8UVt2X++TAyv4/s/s6Q77FzxdZ4LJUJgSZwyJQdebbWjVGFqL2sMdzl1Dyb23mHj+F6x270kvGO1UM2emSbuZ/QE7qvPZbVvVlg4btN1zOorGnCeev0f+kaZR2XqF9WqN4s2k84bAJu/T/BUpMU8q2hqaHm5Hm+8DAw7yD0AZgIfiQXEQ2uy45qWKDOl5CmUZKJNmv/cM6fVFi5WgrfIeuiuxW7o=
*/