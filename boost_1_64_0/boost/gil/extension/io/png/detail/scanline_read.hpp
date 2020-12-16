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
6iw0kUHE0LGhx8BvjaHH6wvwYc/BZ+S8TCE+SPGFhpxVnxgicsji5Xo3oANy8G/xcR/Fz3sImyD+J+I+i6BN6DCUic8HjTctxqdLYU4bsOfqE6fKQC6ebJ1VYu/qK2gH/TgxE59iNL5rK9o3IF6J7ktFbz38PL4xawhhB3/L/tUwdNvF0PIO/MmTHiTWbu1NQKtdzkNuF7BW9t6/i8XG6km8eQn6AXhvPxP4PYZOwbdOugk4ML8hAfb8kIMJjHMVPsRw4jqnIHMHZ7NHWcQ5ktamTEhg32Av885HzkGPF1kxiHPgPda/Ctk7y4uu2w1st+IfoC+zsTmy2nAuoz72jYGueJx3x2GDEx8t+BQYQQNrkE+Lr0D34zck4ktnx8KrwOwAa7sH+hiL7Nl8B3SIbs/9mb9HEb9lfyK4E92LLTzM2sM81vqwhqxRbdivBn+f4/+Y3eFl4NAWGBx1KzYiezr7ofUV0EUJ/lB79hrPRs9MH0z5rfADdtYxyCtBNlk5udewt/TCGnjnNewK+C94I3o9Azr5gthIDvBPIw7zBL4SMYGGrdijRKaczdhbKjjnw7zjh8LfXfBXoPmH8PeaXuuRucQT2uygT9qPycbX/hJcAds46G4HOP0thhjBqyKCP3ReG3ySj5EhMdiu4MOH3H5+NvO3fG10+7ms+Sn28QoHEWcDZ2fiVy7fiC+whb4uRieeBO+x5zj6UvC4DXsJP/+ufeyhQcPZFwO3O7E/dmK3LALWwPAXYgcG+iD9DGCN35ZAfRNky3Wb4FNsyR7g6WH0xBfw5vltsbPwxfJehJ6Qk8ey1zphOHy3jLh5OXuezal/B/pKR74hY/dAtyGTfttRBqwXortavm3izyMPl8Cnz2ODo1fassfaEzoqZi6dnsG3Zc5Ho5+m3wI/GNhH+MYj4An/WM6rEWeJwQbKQJbOBEa/A/NRO8DrLPYlgM9a9MypbaH9H4lhLWVfaB+xFsa8F39p+kT0OTosCN3Hgaf5rLM7f1+BzduNPYNvmPPwLJP9OPz7E4gnjOUc1EvhuME7Jdgl/L2CmF/JfmjpGnjtInyz6dgexGzyiXVM3QVfPsrZmuPYP1qLzTFbOBcI3UDHiUvRaU8he6G1bY2R4Q+Gba078VHOxv4agJ1U1pTvWkLQ+CfI0uvQLzH4TtD3G4vw2bDzyjKRP8X4AY2J6VQim4DhbHTUjExotj777p3RnWPRUfDqt8Ds4+uA41fsk2LjX4CdkAacY9E1He9kHciwc+dSN449fexGLz7ph9cQJ50KH0PPFcdjw00ARt9gm5fDA/D31kb4nWeih5HxW9gff6AePkI+Ni4w3NuStuwP9UJO94KfO+OzjiJuWXYZdBcPj1D//TR4czl25HrkO3Z0NnZ2fdbQewwyAl3yt+Ho3S/QAcQ56+/DNmMON7A/lvsNtLcUPfAh8t2DX78NPDXjXBF2Tusn+IFnSqH3e8Hn8JbESKHPIvTaXGz6VOipfHh4v2rVWmTgzZypwA/6C/5rD4TTje+hO85CR/AT+y1xL/yqir9DC9gHKSfgF//OugZho7JPfBQ6Khs5PpS1dC3Bz+mBXT4IW3ErunES/l4bbKXTGY+xPkpDbn2FnmgIDS8jdnEqe5j8bgyPlbPvHMhknBjkA7LtxPPQRcioAPHgZx9jjQbxXuztW7YAt6a0n4vvUAcd04Q9GGKUF/+ObkYe/cEewgJob1936HCt2HuUn84BzunQ7wOsnb2FxF+BF7yytCX9EK+KwZfIr8QPQK6ZA4kJ8NyUdos4X7D4BmQ+/tGcVdA6MF99ABmBTTYFvsyAZq9EVj5Tn7hxf+LVbVhvP3yF17EvpnD+AbwfYJ8=
*/