//
// Copyright 2007-2012 Christian Henning, Andreas Pokorny, Lubomir Bourdev
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_EXTENSION_IO_PNG_DETAIL_READ_HPP
#define BOOST_GIL_EXTENSION_IO_PNG_DETAIL_READ_HPP

#include <boost/gil/extension/io/png/tags.hpp>
#include <boost/gil/extension/io/png/detail/reader_backend.hpp>
#include <boost/gil/extension/io/png/detail/is_allowed.hpp>

#include <boost/gil.hpp> // FIXME: Include what you use!
#include <boost/gil/io/base.hpp>
#include <boost/gil/io/conversion_policies.hpp>
#include <boost/gil/io/device.hpp>
#include <boost/gil/io/dynamic_io_new.hpp>
#include <boost/gil/io/error.hpp>
#include <boost/gil/io/reader_base.hpp>
#include <boost/gil/io/row_buffer_helper.hpp>
#include <boost/gil/io/typedefs.hpp>

#include <type_traits>

namespace boost { namespace gil {

#if BOOST_WORKAROUND(BOOST_MSVC, >= 1400)
#pragma warning(push)
#pragma warning(disable:4512) //assignment operator could not be generated
#endif

///
/// PNG Reader
///
template< typename Device
        , typename ConversionPolicy
        >
class reader< Device
            , png_tag
            , ConversionPolicy
            >
    : public reader_base< png_tag
                        , ConversionPolicy >
    , public reader_backend< Device
                           , png_tag
                           >
{
private:

    using this_t = reader<Device, png_tag, ConversionPolicy>;
    using cc_t = typename ConversionPolicy::color_converter_type;

public:

    using backend_t = reader_backend<Device, png_tag>;

public:

    reader( const Device&                         io_dev
          , const image_read_settings< png_tag >& settings
          )
    : reader_base< png_tag
                 , ConversionPolicy
                 >()
    , backend_t( io_dev
               , settings
               )
    {}

    reader( const Device&                                          io_dev
          , const typename ConversionPolicy::color_converter_type& cc
          , const image_read_settings< png_tag >&                  settings
          )
    : reader_base< png_tag
                 , ConversionPolicy
                 >( cc )
    , backend_t( io_dev
               , settings
               )
    {}

    template< typename View >
    void apply( const View& view )
    {
        // guard from errors in the following functions
        if (setjmp( png_jmpbuf( this->get_struct() )))
        {
            io_error("png is invalid");
        }

        // The info structures are filled at this point.

        // Now it's time for some transformations.

        if( little_endian() )
        {
            if( this->_info._bit_depth == 16 )
            {
                // Swap bytes of 16 bit files to least significant byte first.
                png_set_swap( this->get_struct() );
            }

            if( this->_info._bit_depth < 8 )
            {
                // swap bits of 1, 2, 4 bit packed pixel formats
                png_set_packswap( this->get_struct() );
            }
        }

        if( this->_info._color_type == PNG_COLOR_TYPE_PALETTE )
        {
            png_set_palette_to_rgb( this->get_struct() );
        }

        if( png_get_valid( this->get_struct(), this->get_info(), PNG_INFO_tRNS ) )
        {
            png_set_tRNS_to_alpha( this->get_struct() );
        }

        // Tell libpng to handle the gamma conversion for you.  The final call
        // is a good guess for PC generated images, but it should be configurable
        // by the user at run time by the user.  It is strongly suggested that
        // your application support gamma correction.
        if( this->_settings._apply_screen_gamma )
        {
            // png_set_gamma will change the image data!

#ifdef BOOST_GIL_IO_PNG_FLOATING_POINT_SUPPORTED
        png_set_gamma( this->get_struct()
                     , this->_settings._screen_gamma
                     , this->_info._file_gamma
                     );
#else
        png_set_gamma( this->get_struct()
                     , this->_settings._screen_gamma
                     , this->_info._file_gamma
                     );
#endif // BOOST_GIL_IO_PNG_FLOATING_POINT_SUPPORTED
        }

        // Turn on interlace handling.  REQUIRED if you are not using
        // png_read_image().  To see how to handle interlacing passes,
        // see the png_read_row() method below:
        this->_number_passes = png_set_interlace_handling( this->get_struct() );


        // The above transformation might have changed the bit_depth and color type.
        png_read_update_info( this->get_struct()
                            , this->get_info()
                            );

        this->_info._bit_depth = png_get_bit_depth( this->get_struct()
                                                  , this->get_info()
                                                  );

        this->_info._num_channels = png_get_channels( this->get_struct()
                                                    , this->get_info()
                                                    );

        this->_info._color_type = png_get_color_type( this->get_struct()
                                                    , this->get_info()
                                                    );

        this->_scanline_length = png_get_rowbytes( this->get_struct()
                                                 , this->get_info()
                                                 );

        switch( this->_info._color_type )
        {
            case PNG_COLOR_TYPE_GRAY:
            {
                switch( this->_info._bit_depth )
                {
                    case  1: read_rows< gray1_image_t::view_t::reference >( view ); break;
                    case  2: read_rows< gray2_image_t::view_t::reference >( view ); break;
                    case  4: read_rows< gray4_image_t::view_t::reference >( view ); break;
                    case  8: read_rows< gray8_pixel_t  >( view ); break;
                    case 16: read_rows< gray16_pixel_t >( view ); break;
                    default: io_error( "png_reader::read_data(): unknown combination of color type and bit depth" );
                }

                break;
            }
            case PNG_COLOR_TYPE_GA:
            {
                #ifdef BOOST_GIL_IO_ENABLE_GRAY_ALPHA
                switch( this->_info._bit_depth )
                {
                    case  8: read_rows< gray_alpha8_pixel_t > ( view ); break;
                    case 16: read_rows< gray_alpha16_pixel_t >( view ); break;
                    default: io_error( "png_reader::read_data(): unknown combination of color type and bit depth" );
                }
                #else
                    io_error( "gray_alpha isn't enabled. Define BOOST_GIL_IO_ENABLE_GRAY_ALPHA when building application." );
                #endif // BOOST_GIL_IO_ENABLE_GRAY_ALPHA


                break;
            }
            case PNG_COLOR_TYPE_RGB:
            {
                switch( this->_info._bit_depth )
                {
                    case 8:  read_rows< rgb8_pixel_t > ( view ); break;
                    case 16: read_rows< rgb16_pixel_t >( view ); break;
                    default: io_error( "png_reader::read_data(): unknown combination of color type and bit depth" );
                }

                break;
            }
            case PNG_COLOR_TYPE_RGBA:
            {
                switch( this->_info._bit_depth )
                {
                    case  8: read_rows< rgba8_pixel_t > ( view ); break;
                    case 16: read_rows< rgba16_pixel_t >( view ); break;
                    default: io_error( "png_reader_color_convert::read_data(): unknown combination of color type and bit depth" );
                }

                break;
            }
            default: io_error( "png_reader_color_convert::read_data(): unknown color type" );
        }

        // read rest of file, and get additional chunks in info_ptr
        png_read_end( this->get_struct()
                    , nullptr
                    );
    }

private:

    template< typename ImagePixel
            , typename View
            >
    void read_rows( const View& view )
    {
        // guard from errors in the following functions
        if (setjmp( png_jmpbuf( this->get_struct() )))
        {
            io_error("png is invalid");
        }

        using row_buffer_helper_t = detail::row_buffer_helper_view<ImagePixel>;

        using it_t = typename row_buffer_helper_t::iterator_t;

        using is_read_and_convert_t = typename std::is_same
            <
                ConversionPolicy,
                detail::read_and_no_convert
            >::type;

        io_error_if( !detail::is_allowed< View >( this->_info
                                                , is_read_and_convert_t()
                                                )
                   , "Image types aren't compatible."
                   );

        std::size_t rowbytes = png_get_rowbytes( this->get_struct()
                                               , this->get_info()
                                               );

        row_buffer_helper_t buffer( rowbytes
                                  , true
                                  );

        png_bytep row_ptr = (png_bytep)( &( buffer.data()[0]));

        for( std::size_t pass = 0; pass < this->_number_passes; pass++ )
        {
            if( pass == this->_number_passes - 1 )
            {
                // skip lines if necessary
                for( std::ptrdiff_t y = 0; y < this->_settings._top_left.y; ++y )
                {
                    // Read the image using the "sparkle" effect.
                    png_read_rows( this->get_struct()
                                 , &row_ptr
                                 , nullptr
                                 , 1
                                 );
                }

                for( std::ptrdiff_t y = 0
                   ; y < this->_settings._dim.y
                   ; ++y
                   )
                {
                    // Read the image using the "sparkle" effect.
                    png_read_rows( this->get_struct()
                                 , &row_ptr
                                 , nullptr
                                 , 1
                                 );

                    it_t first = buffer.begin() + this->_settings._top_left.x;
                    it_t last  = first + this->_settings._dim.x; // one after last element

                    this->_cc_policy.read( first
                                         , last
                                         , view.row_begin( y ));
                }

                // Read the rest of the image. libpng needs that.
                std::ptrdiff_t remaining_rows = static_cast< std::ptrdiff_t >( this->_info._height )
                                              - this->_settings._top_left.y
                                              - this->_settings._dim.y;
                for( std::ptrdiff_t y = 0
                   ; y < remaining_rows
                   ; ++y
                   )
                {
                    // Read the image using the "sparkle" effect.
                    png_read_rows( this->get_struct()
                                 , &row_ptr
                                 , nullptr
                                 , 1
                                 );
                }
            }
            else
            {
                for( int y = 0; y < view.height(); ++y )
                {
                    // Read the image using the "sparkle" effect.
                    png_read_rows( this->get_struct()
                                 , &row_ptr
                                 , nullptr
                                 , 1
                                 );
                }
            }
        }
    }
};

namespace detail {

struct png_type_format_checker
{
    png_type_format_checker( png_bitdepth::type   bit_depth
                           , png_color_type::type color_type
                           )
    : _bit_depth ( bit_depth  )
    , _color_type( color_type )
    {}

    template< typename Image >
    bool apply()
    {
        using is_supported_t = is_read_supported
            <
                typename get_pixel_type<typename Image::view_t>::type,
                png_tag
            >;

        return is_supported_t::_bit_depth  == _bit_depth
            && is_supported_t::_color_type == _color_type;
    }

private:

    png_bitdepth::type   _bit_depth;
    png_color_type::type _color_type;
};

struct png_read_is_supported
{
    template< typename View >
    struct apply : public is_read_supported< typename get_pixel_type< View >::type
                                           , png_tag
                                           >
    {};
};

} // namespace detail


///
/// PNG Dynamic Image Reader
///
template< typename Device
        >
class dynamic_image_reader< Device
                          , png_tag
                          >
    : public reader< Device
                   , png_tag
                   , detail::read_and_no_convert
                   >
{
    using parent_t = reader
        <
            Device,
            png_tag,
            detail::read_and_no_convert
        >;

public:

    dynamic_image_reader( const Device&                         io_dev
                        , const image_read_settings< png_tag >& settings
                        )
    : parent_t( io_dev
              , settings
              )
    {}

    template< typename ...Images >
    void apply( any_image< Images... >& images )
    {
        detail::png_type_format_checker format_checker( this->_info._bit_depth
                                                      , this->_info._color_type
                                                      );

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

            detail::dynamic_io_fnobj< detail::png_read_is_supported
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
A1sI1W4bpPBN2sqk1whzqL9/lVdigHoXddRh+iGdDz3BwcbNSutA5wvjvyw978RV0iLPOUgpm2GPKWXPvTmmlH1KZaVs5ayBStnHVChlM+ynuS8s+IupFeauXrkzQStslpg+oMQ9ryaUsEBhQlKiYpfL/fkPiYpdWVBPkcmD5LjOf3aA6CCm+n3kGVhk7bMPVP32PHi66teECLc4/OBZVb877DHV771aoup37Mn+f6H6TdTmDv28/6za3JykBG1u+9/6Y9rc8UkJ2twJpr3j7yODtLkT2MDw9mr7wAe/HPzg/BcHWzxO+NcWjxMGmJNtfDJBaTswgqAMgHhYHOGExgLk20ugYnQIV2nzpkU25DgGCFh1S8CqWwJW3RSwlrHnLAIplOqqsALgvH60f0AExefkvSsoIygOQRosm83J0qJpiKYlA/ClWQH49poxA2U0xA8exK5gae08MeoztxUvVw45QRVt6r4tEI3rvjFzARdOLHghGzVYxgH2F+KdRGtOtezftOYskoBuAl5aaPHdtgHxBwks5xsvs1j9dFX59NnqdVJV/sff0+lztakqX0M3FTuxAAO142uOnEU7nmi6YA09wXQBGM0yXUhQlU9g8+SNMVX5IB27VZGpYz+jQrzy14MtGgeCYH7jQIU4Hxbda+MK8dvHDVSIXz/OVIijpN4rjv/2LApxrmn0705TiK99MqYQ5yLz1ptaa/P+xJuJWuwi8T7Rr6Fy1xC9Sx0mPaZ/mm3IEPmuGIX4/EiiELNBqaStO51CHNlLNNvtoxIpxMUJievc6wbZYcbiH890FhORcWIGK6zhydzgeXwRqxEfj+msC6TOehx01otZZ73oaqmvHib11b49D+cMUlXzQFvelNq+IrtEOx0rY6aPpvK6Riqv1b/oTzBcD1Bc/12NK66bvlVx/cDy/1fFtVzDlyT7iOAE0ScJQz/P0DEm4u8Lxkt1rZajAY7LbWWVdZH3pW67qbJmsn7zdVBZt5+usi7aEVdZh8bGVNYXtkuVteK21NUlHLSizxPegxiT9R3NYByeMBFPbGqu+omcGn17x+/PosHuHqTBHvJAgga7u9TSYEOuxxrs3oEa7OZSqcEGWjxNg91tabB74xrsP4yBBhvFT9Ng+8Aevf/jfqPj6kQNNmKmxDXYj32bBrvu1GAN9rpTgzXY/+eUqcFmgnSRSzQRqdixJEGx3CUVy93CPuasGuyu0zTYkr6FdTn0Xs71Egp+nKDBzoEGu+hMDT33HUuD3ZWowe62au0SVxDsdRzqM/6FWvnO6///1Mp80GbUJKiVWdP4eJb0e0fCRttfbbbSdLsZIYm15r/Ba2jNoZI08QtU49nLnTZzV+h/JIj/YMH8jnVPD9JEM+2nDBVvf2Npokd87yxFno4VWXTLmZTV45/9d5TV3J+dL1nKarvk1Ggj27cXUad/vLJfItdJLK9EyEAZEi7HWGTG9X26zaSlUvW0Iiuub0JAf6aGlzhMzTLmNI7wYprl+hjqEgd+/a2aZUuX+t7xRKvl8h9+q9WyFKQ/P5oGk4Bb58dVU4Mkx8UsOYbE/DTJMR7KdT2D5BgvxbF7BkmO77BDciyjn/9BSo49unTe6PNumAuBa5Z3w8vMJbAg2ELhk6MPx0XFI1oTRMWxEhbB9y9FxTf/iEXFkyAqTpetsYz42Gky4gNrLBlxfWwaBsqIMaCzyYgvuQcyYgarZ18fJCOu/6ElI5auV7ACB/nAudi9iPhRCh5c3Phx/+nxyJmRjtlEMKj89LeJNhFXrh5oE8Hk0wCbCGCE/4VNxIAg9nEludSna1VYUC/zFVCVM+GzRzzw9P9GVT4oSr2shVXlsTj1B59i9UfxK1Jjnp1A48U05nio+liJPcXLEgn1CovJb6yChNJuk3zNz7C2KbHp0erwMjoNhUtcnAWqQNxKZUInkxS371Oow7PsZ1CHn5Ta8Cx7Qszr3I8Gag9ZOd1tN5XTjOpf/a5UTjN43PgCK+McoxI5TEKfqXyIZ8LKvUEZoefl5OcHy1LkEW0mIhtgymhaMnKdrz3Jdf5pZGKdMWuOH7wWt+a4INGCgxUGY/7kMGUr4sjawRYc7BFyglN3WbKb3Rul4YA6i8i0vhIz4I3i1R/PkQZR2TE7DwZlfhxiyLOpo8T7Tw6MDqtCHduTHo9oOlBlyv2a9EpMZdqcfhbdKhf8xQuxgq8MLmhpRKUsYSNP2NL0s6hNZVoGWejOby10zx+50OR4IZy5f5wE5aWUQr16VuVlV8q/UF5envS/VF5eY2ksD/352zSWq14brLEck25qLOukovLSf1NRmWuYGk7PykWwpBTD/sAbt/z1fmOQ3jL3vCSb+HMKIgK6ajs+x/iTIfOTB5Q+HRDDYZUuBAAdonUcyt48dJEuy3if4/PLwYozntxjT8gQMxGbjIR0yEqYQ9P5qfqo+P1nLHTtFHt/2cexwPW9NGXivolW5KVZb/UbIvyZKZp9/ZemaFaGG7qei3Xh+y81GXWpuHhw1CUWui5b0WeFfFHo0mLvOjZR7Z8ly9guve9b3jJ0vFecSPuLzfYQ/T2P/i66ruIEsuXhvusY/b2M7g2brfwCKveZWY7+Lhq5hoWDxET6ZufA/6NkO86GWLUIpElI5eK9xHoHnVp6qN41IAp+gA6EOti1+D5QsrRqXLFMo+OpZBtHO2qnC4v5PlKBhMCHxccdCFB382OIV4qcZfLEgjkfnYbeG/MUt3ZjHieTg3Y/8aDSKlYOelKU26NN0hY6/9tYBqMStzLUq6YpTn03cvtoLuuJaj2Z7YxvvdBmrKyNh6kMIRYmOD7qKj04g9BYcEKC3yB1rcI5HJotb4WL/kYq1g0H5o5UvDAckebl09rstnPS1ORaN/1B5EYnSCwktrdro42au6QEbZwYF8F5BS87nFlQuuouKmwfYaeiO+fHsHqs0SxZveKqaNiI5sZUNLya0Ozm8dzs5gw0mw4jjFucGgLR8gCGJrh5ynle00xE+fS/g1oaR1gi4FJHU1OpQSALtzf1DvrreaY+VJ80eALssg+d4NmGEjFHyJxGMaBJ7nwD5h2BcGfTr1ubTS8ytNlZ2uzs7bU11MntzVxrqx/RwI4k29DvgLugbRdSdx9JXnzzKET0zmjbdnj3K5hLLTUNv1MwQG16Fv2+ks2Pc/jxeH48ga+7ZmXRdTd+p+Tcguvx+J2Sdyuub6Zfcf8/3bZWf4be0rKrZZuYS3eh6c2g4rVxdwey0l65l360cQtvp0vldlwu/z5dVtKPckOr38VfXYA6knOsnvCzEfTs41R04xXu1zj065MG0XPMbXsFj6POIy1HWvTUtpksjF9obYbD9Ue++LT9yGHaEI/eGZr+Kqf2onl5gS6iSYfrrc0yyZhyEPKZij5kdh9cTOTny6qPZI8XbXQaRz3afwbX4Im2+I5o0pGWRIm87s/SCzNM+b4eSNOq3hkujaOqAVraqtfxW72Rr2vxu/oF/gXca1Uvo3CLtno9l+qG5/iqXhy5/LVufj1tKJ7nDR38HIplbZXTOfi5OxnP05IHP589DM9vo9/WKjyXIFPctkvCCuBE1HTR7FdzeVqjBrGc7hGAtTorBR3Oxm/1+CG4noDf6kkuXE922azlV+5vrcLo2lJRO1UxnaporeIhDnwxnl/w3PDr2Ivh/IKni1/LFwQD//zKTY/wIrYQGRZpnKPvjwTaxU7OPO5GakikjHCxlVqW5hdsq9ar+7OpFHL1JOXru42aybR9Y7noY5VUDKwk54yV5BMm4YpQz1SuJzuu79EdzJvvMThCubiy6RQSPdz3vsm+fimzLQUzQCdJlXIeu+6EjUeGmrRt0Inzfl6iAHFuPy3HCeIL3z6IkywA5ml22ULR8KwlToTic68yRKxBCJAuRFEkXN84ky3KBzQUIgSa2FLUQYyR+IAaiOmMqhdTI0aoeon8s5z/1KFlm3JlQXGkumk4PG5uNdO5pbGKIzhXH0KV0oXTLKt+tGBe6LWX3XEtkq41DwfZHh2n76ctfIE+x0UH7AHlOz6/e4lLn5PjK3QprrzwLvVT6hQmQPxj5ymjeeDHmfzxGOvj9NhHf+ePnDZRG//ITsxKISKP0qG87fgnY3tCnyeVGcM/mgOOq6ZWmr3FMRqVzoRMQnF5n2TkcZ33yan4m6YXunLrfU9iTgjJRi8FW1CxhPGKrwITpnp0DX9DJwwFHENiwmJTPoSoDbmt+jHvgqDysHdBnvoQUGd6ZNYdQY6TqPxQSiEQPOYiG7HG4Nxzdx1vudG7+jY0NdRbkkWYeD9h4gPSUkZJ845rgr+3y7uaO0w4Wj9vjvHW7OGs7kG2xzRuAFnUjIKsBbn18/PmJeh9CCXxej512A5SXaK9PBddfiN+9p41kQVF+huY/+Lc1uhl+k4C5e/qi4kgpfW/FLT3rDugCzcyb5aB6lNCy/JsSsYMokgP0KqY4CzOo/p6Zo23q1F9e/QLhrbNL89CbsBdybbN+2bT1QN0Fal+FWz1fL5cDzOvArxvJ1wkbsGV7Ta6uoFfd9IRJCbzJdsCXMqXvXRqinNRNI3wkcjAVQ6hIzEMV5MIGwkbF2yi41J804TLg3TIiS/4sp3OuPkdn9B13Jmacb3nmYZ8uXFuzyCISxaBHacMyCv/1G9xUfW2gQ4IEwosHY9DRrL1VCKtDPzD5/2GTofqg4w6XFqgl8jcRn/L4v3EXKiddAQJuPrwufFDfSaSR8yLrLClGUbFia8IQhYF2JLo5zM5kybR/TW32c20iY8pKG9o/rYFyliLQk0lBsO3cPxDyb6FExYlm2qoYAE60vvaqUSBSGjzzbzZAcIXEBCFtJWAJoKk0EUraLnMBBjYQQcdCXowkCFiwyzqc4nLjIV5VzHxEfQJwcn3ivRG+vN9HaHUaUwziWYXC5wsTbpUfwvQRQcDQOtygj8CrXplpHduDp1WAXdQfHSIwLNH/TRsqLXzEeE7z71AAtXubRaQhjonF1iO7zUsEnBZ26g1UrWYTqLg8VYxppatJXMNLMU2nI/Vc90Qy9ztRkj4u+h3YsPzE7ft70X+VFfk5qnEi/i7gyL1TeiaE8vee6ayYtY65CBBPfTI0RjUq/ANXYDfEY1vDH6LuiY2BoWHv7tXvpnYODvxw6NBUf2G9Vq+k591NGAE8rFVq+wQ33GPjLdQD8K2ilvilZy9NGoWFb8/6ygOBoX9jQF9jb8Vt5z23d1ml5EFSjStj48i/o7j/3roy1khgzjXH8KATe2jp+LBt2J6J1P1jyxmOhZTbCVuLhJ6Gusq7stJAZu7zJ1i847rxok4JHQR/tr0KQyAPcq0YsKSDGDnWWfXaKhLWu0Mg05EAiYQ+zg6UiyqhxlD3+bLcThN9htWLj0Tut5inFhzG1SsEj/qKQtYU5sDsszS6koRNs50ZYjp1gP96MEkYMTSNipa2wNTm896gN6Nt1GTuO9/5J73VEJNB+XN/S5baKnTpoWzEC56plsLZ9NF40w3y7SS9ZlTYbo/OVz/SImJ6l0I3FBmKzamgICNRHKofJHInJjCEYXlvVhwkykR4NtQr135js5NaDNdOjehzXSLX12YYouOFSvpjzRlYINdiep5JOI31HtzaqoYRe/KPUDTuaCYqAOk97D5VmFgikf/vusmQisiOkOMfvcUAkQf77lxvF0ZE3okSJSFzjOpp9zCbgSY2+gY61kk346Q2avkvCNywgJTNc7dqcAZallfuwuKgGQ1tdtEkZkSNXJ6eQjMCrP7jehiOkMgj2v4Kk0r6eV0UOplLEYbhqWDQXz0sVxjFpxxbpF6MpkzappW3ptryPPK97VyBQPUJH0ukX76NUT4BadCOuPz9yk5BEGEEmdfzDk/RhJofQhh3jwo3UVGHRvK6FBOuQBTaq++t8CoaZF87kc4nz8sU2ovvpcApKHbzfGdy936MSQVeEcr3+hdjUGrI4JiVRfI1nc6YApUFAk8Jzy0xziytZoa8T8HX+gAFYmmljqJ2UGBczbgCGwmtrSkmZhVGnqyCG0lZMTkxx0w0fXvkDdz+aZG8+/T/Ts0/0GEeU5MWSBTlxNpdJLIIn1vUPPXooj49JtkuMbQ0wZ++Uy9FiBCtYVwkgQTWO8iVj3Brr9eb8LtYphQPOLSqUF8Utlu45D4Y7yrQUUqI2WP5K7yhHF0e1dnMXUW8S/HMFd+ZcBhCFXu0AM1hCq0wLpIYF0+DZr+X6H51+tD8kGkZrPQwPw8Ra9ShiMXwUZ1tl4IdXVhi5LsXZCmDAO1QnhwV269I9DiC+xb6tAC+/TCNsc2n/8g3fgP0phQ8krd38SC9B2Rm5OSo9kJxR3+Nquwbs2Bt4RG4OD4/c1YkTDOU5pj9R1sSS1Fp5kOPKfNdIpVSGOyU9z4tTsWRUpmOsxYwtmFdQKiNHb6WLt2LccubVprzJnNJBdBDdOodDQQKbo9KFw9hmHuE01S+Zqk8jXeWSaRRwA9tZjh+hrroLzCJPKPzwAILPfTGm8jBlQdpQ+RBNHTDfmcXAWmVj3qbimoEtdsIZwMqcertHC09tvXuIiVg8w7eU07ceEJJogP4tDbOtzJhmLytiOSGksudTl9Z9RCdqEk1+JGdx0WtHSSc2cR0Qg9Few8TRYdKc7D9cTONxzeZvH918cf4urIx1HnkcOHd308otjkfxsO7xI1fyHWc6ZT7/1kN/Gbv6A77XqqbwHKHmlJtL7QUyejE34X0fk0+aksYXHpLGOJunA1FU9M8RGvFsHT87xXQRDNsgjp2NlxHXLLXFPaBSefD96NWY4NlzO+kI6OcaCjP9RZ3e0IuQw+RXie924+ZcjnSVoWMXN/jwv6INuKk6GbpzJLls6vMoaz1o6PclmEM585ucgNRfrbTIuN4t5N1Ge7dLt+jUzXQf3okGgAuxDB1pj7WyDPYXEDdWeBqW7NF7297MUGVPYr2IWVdv6DhthZZ+lpiaizSihqkQxEvtd6S0A9X28qMf4LWokiqY9747SXbfyS7YqfPu0ljELLbKUIUikWnfaWnaLqWSNRCzRvWRHhUJZqmllXOG0h4zJlWMi4SkkOGReoGdLEZ1mKYcQ9kaWmzlIinmC+v3uEyfDPMcfVs9Vsf4TMgFQstisOW3SKObJD1mtXZAV49uinVse3JrxBnKroe1j97RLlJYTkMelxuM2Yhrym7JHj551IhgqSKFaYz7PslDrvTGLFpC0h6M0wycOst3Mgn+FSYZfg6GmGcBr3VbK0OBlNJJrMinT8nbgpF/EVGn8d1/cQ3DVWsA0glCSDpNANodouZjhGMT+cfJRugqUriA8y5ow3o32VHCA8GPyHG2mlhhHPktsqhu6xS9nz+SV9kcKWOfKLYF4YaZxTqAyP8nJQZC1E003zmQ5JaUS8NBlznKHyo2DD1L9xbL+/wrF9u3jvH+5YFobN64gjLel48/KUQSLl87wV2E/qSG8yhF80bYEM741OvWHZBURWRMed/jpNvibE5IqzSzRutzth3DZQsqWvnj7uuZ007sM8bjFqtzlqDDnX4OJwAuBxJ3vLjy67ygwTJtJ2ywiExzp5TBEdDYjJ1xlQbcXnwbsFvVDbEZLsuLLN3PbmwZ9dmk27Vv9AjN7CC+wuNqvx72aGbH/0
*/