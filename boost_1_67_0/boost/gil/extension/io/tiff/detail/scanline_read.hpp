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
i+ASgFiQ5PfvI2YiywRZmOoExk50XUF3aJqErmad57v3emA4NqJDu+KTfHi1FGDy2v38LclNl8vRlEbEWbD/E3dib1VJ6iml9jHwpJgGTuEonW7UbMmpwZEzutHXMy0PdQ3DcVsMr2rKshWFQSABTvW4wCwgoBRc0Gv34PSyM0eeW2tM670cfGFtEmWy5RSziqKRIvwAlMPJp2ml3DzIoxOwacBpFtnrieYG3rMMHl0HVbdWYx5tFe+RnUfnA4tpMI2rwOQRz+fIrLxc6MknD0NjVD6mBzmZqSMPy2dq3dzwSSKcNCiThxW64ksaL4w+MwIqyl+skAVOEHAcapWD7gCuITdl4U4gbsyi+KSZBh0dDa7GZ/aoE2ypgVluVd6HvyHOVd5hHKxuYkjX67K69seFMyKCy5IVZYVCLC06qCOXp0wyu80bqNmZqepf9F53RwQ45x8wDo5dvw4ZzCby6eei2sxm2gaBeYnGMp8tyO1/QHN5nCON/kyRKUzgi6dXFXlOFzF+FXDcazF+rSDkcUWwIV2wlRe+CpvsfGfd9NLsC90VfgoiMln/534F/1iIHHFt0lwjnIFgcjjDeIWaVLgVrqgYVrJGNSFw9e1gLJlo/U2RczU1cGWSECEJywWa0ThDvuJKuFbcHkKgSEOr0yqNLPRhdivUMDffrAzCgszUeK/vw57iSivWJlckbC11RzBQBLKGIKhObqPfAWoa6Ks/356E9cVOcd2WOHTHJS/B78BhixEjDeKCZuy3QgR2tjGFF1ldVFPkgMMBoirf5QtCzjH4ZiZW44Ifzzbf8zu+Uj/sOODZCWwtOeWJ3VjRqRbEvaT8nSS6UZFhBLrrz2GTrrROavX9uHlq71W4feBZwbpAHZDJ5Mnc8VHJlnSZqrFaQEyvYif8o7tIkRIMENhNnmHYEEJZ55b/SK65CFCFC2gImirTvxrhBblq4cTDae6/JZiaKDtHdnfY0oS3hMKa4sFSw6BxGXs/d5kepFr3jVsfh117rlADBNzUFVnIaM9CvtvRpObsICXRVUEKo6rbvO1YFi+EIvpN2G+g0ZY9qhSmm7NXsfOLkppU5UVJMd8M7Hi5Uq7s8bwRM2DwFBhJgxUnK25+sUF6qav0HFNOqANdRIQpmA49LmDl5cq8/Klhnf5Ivl8GcIcW4Zx8RkTUhFPRfttsf5a6W9gpLu52t0boNMErG5ySsD6DcrCit1Jibca1PqTUhUKyN7AbbDbl+aSSVdm3Jtw8ZEpmbkDik48eWMqvbPtQBEGjnDTy4DQnEDOy2pFk1G3i5w3b1c3r4Hg7u7BbSC64exEL/yCXVtneBwdscFGPsrSqQcqD6IIK3wKAVC5iBjfayZoXwnmrEyeeOxpyAGGuC6RS49WD9HdN6L5uUthZSi+Ix10ro3poiqIYWcZdWwyTrU+R6/MMUcbeFcWTCyY532ptd+saIMvmMhDOngR85R0POi8/c3gr6IloZaiVf6fa0Lh8Dq5dX4Y11L30TqqUCi762KVlGJq7HEAo+3kEdc4ebISCrbinfwELa0vXHm9H8sVpUh+ekOmJ5tV8/UB8bnWBoPe69QUYbGCtQtRytl8jFXeW6uRPRamWffYAYL3QyCGfbZWeicJ9FZXw1pFOqQ92cbm02CSqzJN6TY0cHJp3oTmFw5NtGJFtwZoga2rlV5TnYVxCeBQNyrCid8ljPspXVs8ZjjR6CObLk/5z59TK62HXzOKdtMmXDFMwQot0HtF6YP2C2+fuP3QOZgvAmj/jQDGA8w4KV0u2lAWAma/+VQ7FxKDYZzTlm0c/zTNgj8IdyNEpt0myvgaKAXZ8eRF5ur3CHnG0WPdF3UGIORV2j8Bl81y0+cYqPqXvNk6IdRfCVlQ8EG6MXWEPV5cUNSRhlUWHt3mYDgZcIK1BAl3v8yKFDmd9Nxbs++bCvNbTUm6eyGbcHrf7j1+3Spd9UhvTw2AAzSXMocnozNF9qA2bNCGSvgmHDajl1hFYpIu7HGkZDgnyej/OrCWaMS+96YKaLA+h2Tn0WxsS0cIKaxU1y3yqoLUbkWlSN8vPz7lspgRchkvQacwfzc4IS4uz/pZOzZA9OnJpaKkIJVkAPPowMuprxt/qJfTRL9JQ4/orhTxVLKcPccQRzdiWiMTsW6SA+j917/9vG8uiZtGRLIuyo+wUxtKbDeEHmuhftsJPki3huzErT+FLDQgMwB+AvLsCceGpMXA3o2OwCOCPN08BvkF8Itf1kr+943b77eMErMnY8mi7V27hGeRljzM/7On/kh9Xsr4d6OkSpSqP/3/ApzSbyvZ5qD+tfOkyOWCw2YZRZtAM7JXZCJskZg2O8rBqBBu7Bnt7W6ScVYuX7pG8VHtp5+rJ8zEGDzgyCV9b1Uc+XBrl4wuTKIU8AJsTjWHD6RKovke8aZNj2G6UvGFUf9UfcZdaxVVJJ3Oxp8PDXOEH1sp58Z4k8d3VACfK00eZS7Ftarv8iDfC9JyL9Pw1XgwIuRXQRRTNSatgvQk09ZvVkBWls3Wcy3BRa3MLswzJYyYraCjUnGzClnqSKBYXPAPWgW89zp21+EJlgI0HdGv4KjPk385ymmBUU4lbItrClnCrTUkv+Z9pBb4CLTMIsxMdcSZwR+i/8nYUYjGOEn5Bntq1eFumkvUIBJJjEh7sjwleZ88Kgdza19NqCF0gTH+SuTOckzaMq5Grcwwfc5y4OzWMIwmWnl27RqwED8Mij1BDjzrkudQNhYkZGF+5HX0W88215MnOOt6gE5NDO+tQcOSENY6rKT0PneDbb3w++M5T3PzyH4LyPVRMEhpnxIgdhaM2E/ByVsskz1WARVkeIQBVU+UuEUOb5xMy4LqH9a8mpYxTVgU13n4gDfRgm3IO3WcvktMiau+NsDi/CcRa0fKD9I0ps0DyZOjdogEMbw3Sbt0PrfKsNApXM5h2NqxShHnx/Nk+PzfIyleBCS3fKJiQf+ek7oUI2IoJFdnm9JDLAaH04d+vq7q0Jv8ZUbjXIschgTSzt5HpgnSXQ5PAh2lYkxhXWB9/1H1sQMar0z7ofyqngMG9zK2CHdwMSOLlqRFegRFl5508OXpPGuD1J9lNBisVTQ+2xpqEgQKeyw5j61vYKIU8v9OzentKCusbZvVSVWA2P2icXoCw1Io31r9t+M9tVJBf47uU1mu1qwGiYiJtXfNObCQpFRnS6pamBhRu3BT0+BuY/HYtJc3tyihgc/HpVHJypOukn+X4O/Es+biCNlsDmzbs1+vitmT0uRFrXuRg3o5RG1Dem7pgmAqG3bxfHa7q3Tz4BHd54ygVCpnMinD4Y2kV0dtak8/zW/3OCuAhNz5+HS2BHQNnNeOC6Vka08VwQlSNMO6YV/qiKRgxqZdiSbfUFTTy6MSFSZNWQ5J2tYzIstpQ2wAfnV/LltIEvU5B1wNxtc8AFNvk2Lob+929ViNuIiUwut2ua5cyAO+oYbobmDVYcRRva7bl1t8dK9L8d8HvFe/ceDsqv+XPRlZFVxIO2ZEYUHrUeYMtAwPuYtGo+H6DII/h8ML5yWmWz/15W62LmNoC1kI+rhfYoQzvQNhVr0aghG+ZPsHeC6qi4UH+uUa+Xxi0bSBPXJ9pN3QEApPrMEETwxlm1A/zfQb5yh/ye+0T8+BLRLpQo5kGPDM55BPjyeVnymGxsIsur/6SlqteMIYu3Jx3cQKnRth9tw7fUahrPghQ1kliuj8epysG7Z0CwaJ4vx02Z3LQATzFXntp9vB+wLEBMLd62TlyslkX/uJlJ9rxlgVDztVQv6MiyDFEAdbV1KVIHtYXyOGTzJTp6FuMDTLXe72YJWHtJ6IBHrPjgoFiWYCNnb3jAnFsXZA9DUIwrrOsoCroJzaCJW8tJ87fQMOZ2fAPzZDrH6R6hxL80LgvXwQOPnrbNgJCNB/mhIV2lBJA87tcm4R+5o4TlnxIOkZNP8dMmrYteOlEAObNe1S2VXxekUbHxMw1u1chpd9oiNN4T03h6Be2x6TjWdtJ+2loeIvaoxZkN43/y0b6dFL7cY+JKpCNWyNFWhL3QgB3guXnwUruqZyqVr5GFq3muAz+pWIzvZDFP21LZSi4wWTjR2+PvmYi6BgJLm1xdDsApRTgyVCdBaXyX9nY+nEwFglTwG2zXKlwHliEq/vOqQXcft6FnP8wKuIJ1v4Z77PujCO0W6SVFEMnTyormoUVlcSBE14/L2l5duRLLdqjlRgNSU1HonqvsUsTMiR0XuUfUSYVKs7lExsGLNvOefUsiE72xCtHJ++Y7oex1/r6ske/Pg7N6MHG8x8l7cWJnjLMn7bSBNxw9xnxRSunv7FI0GfD0behAwdoJvZPw5XvvvdO9feKPV+w4nicHnfnZo5WPmHq+vawfA23lNZ8UELXRRMYOSVRNL5nryXZwag1F+L9pHdENVUhqKPlPLG30g2/VujLRPqXMMiHJwr9d5khDALlBFF9CaLeBKL+iqieW4EQTgoorPa3oIPJR7wZhAcKgCDB+AFbEPonwPWviZN9MkMdOABWRrHijePHKKSTWjlhHNVjqQaNLN0RETs6dvyycmE6sXXMQZFt+TLyS7IlIKNEcdHL6FszR8eeNrjZtXEtxorch9mG6lNJJ13GA9WYCTgaviHENQiBK2J8MFMChsd3A6L3ZQin8vLM1ShXiyuPv95BuxQ9JJRLF2qZ6+GZIq6nquKh7maSIqQeze7My92JWORxVVys1BN6tCzCULJDVlpCLJHg/mmRUmWDKBASYmQbx5bqkxz4Qb7Kz8vzStKngSshlIOPGjvxi4XmraJ8foJrKzNHyp0l6Puh4ebw/8Tkc4AyvaFSQ25utxyfKqte9M3042JBoViShRcndBBEBNySqeb90ybpGoXQFLGdgCsz485ONfNYv8oZjCUmH05jFiRnHUGXa4Xdib/akqP/ojiyYj1glWeo6pkX2ZI2CyvMwlwW/tQxmLXNJOcG8w+g3Y4N9G36MqvfS2aZtxsINtfiRmnnhopGN48iijPs+7ayYyYTLzEOlns6DirhZYOicZmOMiTfOymKWRLLQCh9hJscNkY2shwXc+MjXTiiiz3Qx5J1kuUCoiEa15JDKsSTzfUF/uQ3Xlz+si6dFrDuGS+W+IBk9LHDH1v1jpZWJWy98AIu8RdFnFZz+DQjJbf9xRqN38rDxCHLrahhMKqnWZT1tsPvKZDYS6V50sscX1pLSqUsd4J+D7HIAKKBGU2JTDga0E5fBLxETa3JQYm5iVSVrmM76CBnnqonBgUJX5pGFj+dLGW5bgxKWZcPZ3rncZZ+mKqZ4b0BgIdsPNqGGBGBDcN54vwlZcbsYtOn5uY17C78Qv3PzMvuZa0bVsO1RP5Rb55L2hJw5pmMAiAMTwpAuf3zaTCedvPh11uV7eEH7TN5yaXwI63O2eml7nKBUyZWAuiyGcePjnPtkeCcu+z8bsYuT2yEKCcbzYzCjPlY3zr3u4lsZCNvYK6I1jAWgcy5lQ+vJswYD+yiNVpUCPhosPhRZ7sRV6LNsd7TlPCtnqnRgpCQClIZ7RtKQcKjD9v08baMPFKKPpIQoYi8fomwDJMHAZvQcR1sCIBGqEGJbE+wUhTwjDc87dWscsyCsLO2D3ZszLZbUz3WBdkt3aPF8EkHGCqdassHBAICvCQvYx5O9KohZP7KPx6xzDv0e+S/Vtc6l7ZTxqlE5Tlx/1eKQDSv67D0h3RUTUrQF2YgTEpaVSK/BiGIaQXIrHz4/emzR2aQOYS2UaBSa8iccofyDOdcUsMfo5RNQBX60/dy7CcI7ECXB9LEy4C9FzGa88RpRhjVbO6FBYIKgXETCLnHsULUxNqP90RFhvcCzMO32ah0bzEVScO9cHfZOiYAjt3kkgc+Bo3yngXrHvQDoLrH+cxYd5rHBAnFiMzdMUIQkNuUzZGrWXi1uRcTNsLjEcrk13ONxC59/Jfxx2jF6NsG5KAKU7nlCoIun6xd6c/XsJCKMILe0s61++BT/XRGNdJKsKdEvB3kQ5z/SnMax+ge9FEpfzC8k83BGfoNf6BXcTPggfi5tN6RoPGzfbR37XhOv2OGXEBR4Zv0AlZzqKDn6A+y6uAZuKAEWGBig7wpkyI6LBMalAFxSQUwkB2o/vltCD5wtlNh/oQonfWoViFkZRyBnym2MfFxAkuOccjHbQd9/zju+1t/vStNat6v6YOGSJX9AzHvaNvsAzaDwyWj3fjvGnsfCS/4l/q1Jak5KOjQuVEukf9gffMa8kJysyQRtiL4nyjhjif+lnpozc4M1BVsJJwrOXjmO+PZDAtK+6WAEn5Kd/CWUJy5yPaApvR2pB3DC4ARZPFgy9UMgaX6wCWQtd4/Ttr2f0p8jrWFm5Bzidc4+6hJGxsC/S+yMIXomW6FhubDn8Zd+Aqs51u6+wC34q0u3Ba+UAzEPsvZcOKCKhXGSIniK0Bgr7YPW6zrKQo1HiiHCnqvaLb5JA7MuBR2QYje8ktvw+irSFELZVm0lnuGW8r3Bvbh1lsgMU1B8qCYumSYLv2HlwBZWmO47hGZaIfGdC6D0Rz7czVhhLfk+NxUk+zas+UvNa1plc6J1yQddy4i6tzoUV0NVjIsVvYGKwemjX32TglDs5rQ7Uo6tFjqr7hPNSyb54SRxRjMWTUYrUGO/6R+MDYHSmti6CuMCjsjGBlwmohIT/DonJXmJYy1XhCYe6YDXZBFgPpcbHMksW3jifwLgstLQ4iJKmv43CJd1WcyFlxjnrX7dJY6u/ZqLdar5Qp9iMaW6lkFDwufK923D9++8VXqPMVADAC2jOJ+PACYPvUpKQXSs1OS9GMNPekWoaQj1z/TmiMDWwJ19RHdOIZHl/AVfcNPf6l4EbXsVNk4UP19jomOYYWuxozBr0O0dVEBtlLCUdy+v9N06xrCU/JGIx6cKX3n28HR8uChtL1dMXe0GsAg9R7Q6Q8qITDn8Hupc75hspTeHpDG/Pm6I2bGlxiPC6kvZ8WcN2K6HGu4Siwy0lhybXeOu5iUkFxkpKC86r4OrDQ10/816PWVloQc86C6yEDNahgk02S+vEaxasgzT882z856guD8MzruVn7PP9+hcx45f+E4cuVtJRr2mTHNTavwLN4+CTVhn1KqVaBVPuvP97dwaJdLFkc3fzrzrsDsGCZXA5piALE2fSb8L/ktt+qoG7XMzxWqbavAvLE28l5QqB74lvjte4J2t37egPEWMjZwdd/FWjRCQHLWdliofG7QOF0E3xKMKXusH5VJyz2mXW54+w5I8NnUk1nZbmwRBhs8xdEMTCAeEh4ewInBF8bLbN1Lje3JF9qr7Ccf8CzxhGZY96yICYOvVMk46kCUTtULssliPWnxwnva/rmARLFTTN+aa5CVGCjLzg0q0CwaZS3nK/RJf9m+iDZn/4WL321WSohY/N1CIOfJPDM7TxS2u3j5BMFUT59Rp8FARcHxArtwuB8SGd9A3MhenOq0ks0Wn+frETwFURhrPKsb9ucdtczCO4qJBXG6b4b62MRgXF6XU9c8gS3gbAT7HjquPfPgxXF9iotOl4SUSy/1P2Q46sga0Q5GLiXKcWMYtSLB7rpQVktyTPYsKZUIRZXGPmadRsm4y5IxmMVD0d8rDEWVWOWUqV0ZEB9zV8bXGdkjWAvKHVqD5EpoxRTdSkYplUdgD4oviHhEFQtuCbhEUPzyTGiWku5sRn+3gk2E99csg+DqWUfMYnzQQoGNbmb0nOQ0CKIQQEmPpILc5DQruKOZcIF/SWnUxyUAjG8KbaiQQ30a8oA/KIIkb2xYlIN9W/mMX1hAMHdFa0cy9lgCcbQ5V7Oz5sdiTJpTxYsTkPTl72ZOUikNltlFoWly9aoYVH5UpxhHyaGZh7hJfifQruSAK79kWQAV73edhS4FWG0g/Ud8XO/MnbIbgbW0vXI5YnoqjaA95bnS+QnR3chgeqlEaaVmyaWb78S5yY1Qw3bceqmX+3EXKca9vgXZbAOIeihEI1NTpFq4K0Hdnsp6qpz6ZuSV51lH3jysVogwQ8RRvVcihSLmvES4w4Z5xlBR2dHe+bJ26xCZRJKMSE9pPuSf7S3HEe4cdEubihVz5olax1tPjrvGVlIq2MWwgeK6qSY7cHWdR0QsYz0fmUK5Ak7YkljAr8H2UMKhFBMJZecGg0cHT9EHyoDL2FxZLRjIg93GKyuiR55umaqHtPoFc74Ti1r35pcmaqKC4ZHBWpmt5J32SYPKPXD/jcBclQg7X18M+LqH5kLfNUfmRt8pp4Rb8SHE4wP/88/Q77ehc1/w0q3Pe8DYNHF6b0QezxRqUfxXAZB7d5Z6KtpLDbOYRHDN+vm42HDy8qhuzcitIxtzKn/YsRDTZ4/7XNOtocwNCDUz2I+ubpVJZrjxltflruQFTT0O5P4Ln8zDgGyDux1utEcSKfPNbuJ3myfJKVdnzFyFAUpyCMwydDYn1cyF8flqcaAdNzSOO0LtQdcFNdQpcm/Z4h6Z2KA8I/6fa2qZcWplhgW7JRmVS/YB80/Pldu66q5xVyCany5stx5kzgFS9+0IPGoWwh6eOD/3enS9pqTZflcPktzjiHtVnFnzrYN+0JRpxsUdLo0HG4ExhezhM1bX2yDj84+/XQLXnruIcDbRUH6WsfnAoGdO9CUL1mqV3h4+WRUV64q0m7V3Ze060SQtbhMAiDVZc1vUyi+41WrOOvwvtLPDk+NDXDL60Tm/UVZzLth7IwbAfTKCOKT/ZENg8vHGOUaTQQdDtjUpiutB/S6n2KPN8KnPEAVm/qR55RC+qL89s2B6NPbIuvyVPoY/X2DF4TCr8ssoAPp0VMO6ClP2g25FY1KLURmbRVoABiz508zLzhbsQ5lQEGpoEMznmkUjC7+ahoh4adHEDULwUXzWUmqh1aAFbKtcRcPkeW9QzU7swHlrPOEX2AQN9T21uhrDBjGPVWyWKk/sglWJaFKeYL0pFvE3VHI3VhL4E+cTCj3cEzuOrnI3yRYnsDtZXOj3v4eALOumwhfMU9u4RYHnliJ5R6mlSWCqu07ITWsdAYJ3KtUFOlAHysqUGXy0mRWc5FIaQFdFZ7A2M5FLYepn8uuj99312oHMFpjiFtJRkgyiTSQc1XQd2GmbujErjfgLjUFX4kqxqtuER1STo5m0MFPWOEazow7GTN0=
*/