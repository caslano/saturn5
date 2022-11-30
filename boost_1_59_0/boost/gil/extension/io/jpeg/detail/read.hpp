//
// Copyright 2007-2012 Christian Henning, Andreas Pokorny, Lubomir Bourdev
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_EXTENSION_IO_JPEG_DETAIL_READ_HPP
#define BOOST_GIL_EXTENSION_IO_JPEG_DETAIL_READ_HPP

#include <boost/gil/extension/io/jpeg/tags.hpp>
#include <boost/gil/extension/io/jpeg/detail/base.hpp>
#include <boost/gil/extension/io/jpeg/detail/is_allowed.hpp>

#include <boost/gil/io/base.hpp>
#include <boost/gil/io/conversion_policies.hpp>
#include <boost/gil/io/device.hpp>
#include <boost/gil/io/dynamic_io_new.hpp>
#include <boost/gil/io/reader_base.hpp>
#include <boost/gil/io/typedefs.hpp>

#include <csetjmp>
#include <type_traits>
#include <vector>

namespace boost { namespace gil {

#if BOOST_WORKAROUND(BOOST_MSVC, >= 1400)
#pragma warning(push)
#pragma warning(disable:4512) //assignment operator could not be generated
#pragma warning(disable:4611) //interaction between '_setjmp' and C++ object destruction is non-portable
#endif

///
/// JPEG Reader
///
template< typename Device
        , typename ConversionPolicy
        >
class reader< Device
            , jpeg_tag
            , ConversionPolicy
            >
    : public reader_base< jpeg_tag
                        , ConversionPolicy
                        >
    , public reader_backend< Device
                           , jpeg_tag
                           >
{
private:

    using this_t = reader<Device, jpeg_tag, ConversionPolicy>;
    using cc_t = typename ConversionPolicy::color_converter_type;

public:

    using backend_t = reader_backend<Device, jpeg_tag>;

public:

    //
    // Constructor
    //
    reader( const Device&                          io_dev
          , const image_read_settings< jpeg_tag >& settings
          )
    : reader_base< jpeg_tag
                 , ConversionPolicy
                 >()

    , backend_t( io_dev
               , settings
               )
    {}

    //
    // Constructor
    //
    reader( const Device&                                          io_dev
          , const typename ConversionPolicy::color_converter_type& cc
          , const image_read_settings< jpeg_tag >&                 settings
          )
    : reader_base< jpeg_tag
                 , ConversionPolicy
                 >( cc )
    , backend_t( io_dev
               , settings
               )
    {}

    template<typename View>
    void apply( const View& view )
    {
        // Fire exception in case of error.
        if( setjmp( this->_mark ))
        {
            this->raise_error();
        }

        this->get()->dct_method = this->_settings._dct_method;

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

        if( jpeg_start_decompress( this->get() ) == false )
        {
            io_error( "Cannot start decompression." );
        }

        switch( this->_info._color_space )
        {
            case JCS_GRAYSCALE:
            {
                this->_scanline_length = this->_info._width;
                read_rows< gray8_pixel_t >( view );

                break;
            }

            case JCS_RGB:
            //!\todo add Y'CbCr? We loose image quality when reading JCS_YCbCr as JCS_RGB
            case JCS_YCbCr:
            {
                this->_scanline_length = this->_info._width * num_channels< rgb8_view_t >::value;

                read_rows< rgb8_pixel_t  >( view );
                break;
            }

            case JCS_CMYK:
            //!\todo add Y'CbCrK? We loose image quality when reading JCS_YCCK as JCS_CMYK
            case JCS_YCCK:
            {
                this->get()->out_color_space = JCS_CMYK;
                this->_scanline_length = this->_info._width * num_channels< cmyk8_view_t >::value;

                read_rows< cmyk8_pixel_t >( view );

                break;
            }
            default: { io_error( "Unsupported jpeg color space." ); }
        }

        jpeg_finish_decompress ( this->get() );
    }

private:

    template< typename ImagePixel
            , typename View
            >
    void read_rows( const View& view )
    {
        using buffer_t = std::vector<ImagePixel>;
        buffer_t buffer( this->_info._width );

        // In case of an error we'll jump back to here and fire an exception.
        // @todo Is the buffer above cleaned up when the exception is thrown?
        //       The strategy right now is to allocate necessary memory before
        //       the setjmp.
        if( setjmp( this->_mark ))
        {
            this->raise_error();
        }


        JSAMPLE *row_adr = reinterpret_cast< JSAMPLE* >( &buffer[0] );

        //Skip scanlines if necessary.
        for( int y = 0; y <  this->_settings._top_left.y; ++y )
        {
            io_error_if( jpeg_read_scanlines( this->get()
                                            , &row_adr
                                            , 1
                                            ) !=1
                       , "jpeg_read_scanlines: fail to read JPEG file"
                       );
        }

        // Read data.
        for( int y = 0; y < view.height(); ++y )
        {
            io_error_if( jpeg_read_scanlines( this->get()
                                            , &row_adr
                                            , 1
                                            ) != 1
                       , "jpeg_read_scanlines: fail to read JPEG file"
                       );

            typename buffer_t::iterator beg = buffer.begin() + this->_settings._top_left.x;
            typename buffer_t::iterator end = beg + this->_settings._dim.x;

            this->_cc_policy.read( beg
                                 , end
                                 , view.row_begin( y )
                                 );
        }

        //@todo: There might be a better way to do that.
        while( this->get()->output_scanline < this->get()->image_height )
        {
            io_error_if( jpeg_read_scanlines( this->get()
                                            , &row_adr
                                            , 1
                                            ) !=1
                       , "jpeg_read_scanlines: fail to read JPEG file"
                       );
        }

    }
};

namespace detail {

struct jpeg_type_format_checker
{
    jpeg_type_format_checker( jpeg_color_space::type color_space )
    : _color_space( color_space )
    {}

    template< typename Image >
    bool apply()
    {
        return is_read_supported< typename get_pixel_type< typename Image::view_t >::type
                                , jpeg_tag
                                >::_color_space == _color_space;
    }

private:

    jpeg_color_space::type _color_space;
};

struct jpeg_read_is_supported
{
    template< typename View >
    struct apply : public is_read_supported< typename get_pixel_type< View >::type
                                           , jpeg_tag
                                           >
    {};
};

} // namespace detail

///
/// JPEG Dynamic Reader
///
template< typename Device >
class dynamic_image_reader< Device
                          , jpeg_tag
                          >
    : public reader< Device
                   , jpeg_tag
                   , detail::read_and_no_convert
                   >
{
    using parent_t = reader<Device, jpeg_tag, detail::read_and_no_convert>;

public:

    dynamic_image_reader( const Device&                          io_dev
                        , const image_read_settings< jpeg_tag >& settings
                        )
    : parent_t( io_dev
              , settings
              )
    {}

    template< typename ...Images >
    void apply( any_image< Images... >& images )
    {
        detail::jpeg_type_format_checker format_checker( this->_info._color_space != JCS_YCbCr
                                                       ? this->_info._color_space
                                                       : JCS_RGB
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

            detail::dynamic_io_fnobj< detail::jpeg_read_is_supported
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

} // gil
} // boost

#endif

/* read.hpp
pkSEOsw2lQgCKSlkD9v9IDIPsBq7QErHPRmWf9RaDw1dxW9uCPXmN8DvXAJaHQveCxbxv4LcxRGxYEIYw67Or8sXYAj/N7yP3aBmkORC9q5xq9YOKuhPLOqO2H5u2prwojuhelGbmwWcVhtxWlQdD5CisR2qbBg6ATaLZ2MkMGHtC/wR71LWfzksL9gM9LXJSyca7QGXsjJ8vYOdRylwH+SN7+l4AqGORqlW3b8WJe5YT5TAOLB+yIS46fQ3zFX5H1Dn9zpp+icLHEFmQPXC7P8eZwzTMawSlvm5Tr3MvF0ovGyhxgKIilA8TxXZTGDmi0ZK16Btc0niaf1JIjMYBlbsOqA1qPFuQXC5rbKD5SUSbQIBYR2+AP4kUZYF7SjpG7SSLLYpDvvNFv4N5gS54gry/UEHgfSgDxjycrPfzebhVfGBr4l+MIWWs5QLn+vD76H3WMbsvmzJJl6GUpH9BUqqPI0+vk0EsElaN2+3So8o/ufbSeYsI6Azd13aHQbOLnyjMBUP0n7VmYyLEZ6H+vsG0WSaH+vPYd249Qie4NAxPrcGSRqCf6scTmMOeE7nRXqm68O1eYlMOUmbgqRBQb7RfuI75C/4N/MP/TfzD/s38w//N/OP/Dfzj7pi/iHGTh+ADnzSV3gEGLcM0Y3lEoYwed+9IGNTC/Kthl7pvzxYJ/xbg9V3xcbKuVSzTLooS+EWf8C1Pp6pqMhrjX/zliKvXeos8jqk44gO9kWC3oUGjwmLnfzLlWUQOVvqdHMv02VTUrvM2IADw7WORP7eFGZPRHsfbEhu6WO/3Kd7X9Rs01NNeiA9wRaeuUvT0jFLSgN5rRgQ0YsYNHiCYb1k8a7T5AIqUT6W6EJbCChgrrFtjDlzsV8xZy7mTGZwXG7wGUeP9XLj7eIWshO0v5V9tpcUwJlNArrHJCx8wu2O5IZy2o0gW4RCK8+BHe7HRZyp8MmPwO7WXqjR0elFh08oL4sub7t8l1pscbk75NtDFtoAFtF5tP0YgWZnqc1s6Z3cCYYL+qX8eFQMwKce/Qfsu3pY6f9Yyf00QmMb7kTB8Z1Ps/GExyiRt7KTH2HIVfQ1dn1ke6FRqdrj2gDbYO0KAn0NZd4XmVMZqV351TLE7PNaVblVGTNNdecq91QqT0xRxkxXJneHtTTZXuQPQtmQs5io+aYVfqBMPqhMblMmH1UmM2Vy6wINQVnkbDz9Q9bRzw6hDxF0Wwa29Y4AF/sV93Y95Uidx/SzlxA24yYVmOvGSuA8W9jsXyLf2oKJJRhgLazpj5rWcOg4HkhV7VHd20OZkScq74vIUGw2EGodH6wLaq3TEPacjoJvx/7xs8/aiY/oVzTLKfdOumv4GILj4bl4/An3C6MT1YZT+K14EKQNR7Lj4EdoRkLWsxgnZtCC80tcuXbp2gXnEfpZyllwfhH+9lpwXgCBTkpnMxF0oyxoiHymembimWrRrAIMJFYgcJyk5FsfhRxj2k9BuNaDjB35BcLvfRLn1XgEx7Ig6nh2GnIOVeqCMHxEVQwEcOirngL4M4ODahXVjZR6BHAAjTusae8+CcWrwGMbMtdBhmzd/A/62VGj2DrOjIOtL94PG2NGRsZQwApu0INgpl9wBjAZ2s6LYQ5BngEW8NbOVBbw2S+MLCC604fvMgXUM/IEA79f2qrz+0deh1YrlVz3OuWe2qx57OlNwI5mqpnqTs2HrfexViP6mPgxfeMmFYqNsN8gBtdY8EhvrpMpJ+hdrxBG7nrlK5193skyqdC4KFCdKAYVBjVA3pfCO8auMgJS4/mGU/vQx+QvdP7xCGrBNsfOEC8H0msGxXO3oJ4SHQ71bBhL4CVNh7i+Cph7i9oBBVnEhdWvkrZDhDdCsjAItVNxO5MG+FnhF1T6/KSdzyynj/XtvnC4ctObXEHK4zJ0zkUuSb+iA3ijOPkS395CUsMPccn4/ONsASSM66I6eHZjrBYBJGbl4VDpM4QQRh4M6LEv4ZFAj6QP1eIg/LQEIqX5rP1mEw/4tx5kyPnswb+TVTUXduYrcjtznkRL75eFwi31jbYX1tOwPoFJX6LYYbGeuFw3szPQaezWw9kJqxQ8M0fUUSkT79LkbIrQw4q1hDh0B6NxZZBBfDDktFkW9QTrr6WOwax42iAeKTcsxuqzQ/rMjnib2VvPIJgEas9Z435SkBJkB5fqo7i++xU99uNREv63R+oxtV9xH2RPMVq8+0ITNJcHNe2q9zDcHHY5FPWHqrcDNoZmH5q+bWcf8KflapXVdVi6KxDggT112gk/UOl6vTT2QpDfEInbLME/GVLPcFemlB7u6iGnFR6oICDqZnbtMyld7Tptq/dqukMakVHeQ/rsRtQ4Nh9KtrIOsoLG/NBct3ArBl9SCx3EtTDUTWcPuqxylyCnKRkclyZ+rEBkYKjWONX9XMmDJ6cYXAQHYez7KKIGpJGwcOnB6CaR6H2jNjcf0szGqs/N5wOtyOPEaJCIpbG3kEcOS0uYXxn8RwNrcR3zq2eSy1jgHVzHWB9YuCgqES5Wpw9f03gDBYVKLKB4dPA3nKCtsIgelmqKnrDIua7TNAEwFCAWe8dQkwDPpfvg3gf3FQFtxPOw3PN4rLQwqNuAGWDNMCdGW4UXF8HUg9pvY0/cAqlhrI6wwm5ACcO13QKazdFuzyNuxuu0ZSNqo05gSFyPqHissMfMRRtFyyr6sS/Fo7yfauTbimYb5AwoCuGfWPV4LCXAVIDwCiv+xiYT5S3heUsob1MJbruNDC3iois1IcEOacXAATmSx89eURvv8KuPO+Ss5II/K9UPHFeVYPE8NAcT2aRJ57Uqo5torZY8rbtLSp7WhWfmW+xRHAZ4Z4m+od/Zo7MSdy8l3j6WuJuIPVQyCRdUUsXxALzRo0Zcqsqu5De3zrkIqPtEuG6mIN9G7T4UbTdKTRxryfq2RlyalhMkpZYY0tju6vMaz4zHHtVV2ssUYeGCLauvVuNgmWuJJeupbz7WWA52roO9djax17z0aXyvuWBxwtn25NnUxemxT40LGVqlAb1ZVkg58WxitRufksgPzOqGD2B+uo7BDtoMM4H12p44ZPvt7xEAHRjekcEl0F9s0zzS1lv0VX5k8OfzyHiFnw6j9botgXmIMF6xj4D83g/iobh05a1fTBqchduHwiiCuWRb3bUe1qgDMIgpULT8Pdc5+kgIw8hP3IDnVRVwWx7S8FyxtlXzWYuqujmT5kEP8eEGLuD7LRQ4NJ0deAUyzkf1ugvWg90Yb4y5uRZ4s+uc9DsgWkFmZQGgZ1RFUdxVtEMcEKjAtYEv1t2qJ4UztrLWnTq/8XjyS+OcvFjfw2AFbF8Xfe6Y6oa5i0dZttVe64ItglAmlGtyt+LuRKZEkbviJUgyOMB4zvyE+tgO+8Dt39DtjWqxM3b9xYEpuKlUj5BFX75pEF7AoagdfliaOnzsN3z76/Szw0dgPOhrGhnUbiFkSXHBkQ6c5x3q+luKO2AfqUMw45/gP1m34N5nq8cT/gVnpuHLDELQ/xFs3/9ZoU518qDXuI6NnsnbjfifI7SnY6jp3iaD1Y06YiakrtD2ofa/AmHru7V9D8Af1+JdzjQ8ROwNm7dVJgw3PIEI3WpY0Xmf4Twe/1cdnk6yIaPe852OsTAYnkKI0h3MNjSutO2tR1gUQjkYYvHtU5BrR3X0tjZDTNPzK1NJUaB51iFhUrZpSJzU1exdYIUprvMsnJUYSRlIPnxK05JqZfbGPRTlSy/PCF6epwxEai5FZACViy05jMpnUQg5GhqQ3VixNxvdz/B8IC6ql4Vylbua3O2IbIbAjx8+hvPUfRQBtYCf6IlcxAEY9bH+FPLV28be/S3IQtFuwjsEUmoTJDOjsJmhutvZsb1JuwHyVRNhKdp5c7y891fAn7/HE+fW+gPSPX6OrZdLHTpTP+aBgs/Hk+JW6WZ1nFNxd+GCcp3cHcuAnTFuywv7wGNoojRHHwnGQADQ3+f98iMLau0mjHXbG24y8aYH3CCwhfwDhMDL43PiLjo4sdLSnn1Y55lv0nKepyfdwOS7OqT+UKZFQ2jJzaaySgWJPZSrwyc07MYWfntPNiKgqVWOtbmz+9j9AaW2WanapOVU0mBuQTD6LWGWoXhbFW93k3sP6mptC99EDTm7mkfvC7OHpAdu+QVNlNWE0OE9qHjbFO9RxctYCH0COyLuPbqUe3qnpsE6ZA+iUAv8fAtHEtFkbgyASd49jrJ2K5OhcIhkIreEugOclUKgkCn4q+V0X0/+PLAmj0SE7+IA09D0ftv6qL3ctm5buY/9DgRW4qGfX69498RyK9ghSBFQO9jeQxhfSoYGM1PwhT2C9IsKvmwniwTlicq4QribFfdyaAnFvQJWNsW9UnVvUtyrIu7lPmRPO8NIYjtI360ofW9n42FzbnjhPIy4YCki/ZvvgZbuuxvHsh14WMOqyuO6PLUV1dsUxVK3yrItpZAQZqmPv4Ls+At42NzoKhNh9c118DA07Pt/Rhj5YvgTkd1h4D2lUgSA0yVOHL+2+gBJWLb6e+F3RtGITbDtyaNDw6r9vkj9CgLC//Or2QK/V96iJ2tXwlYH+ylbvg3NuHNnvIq5ZuDJ9M+AaKgNhFofd6aa4UrHd7b6F+FFNIZceU2eDqZ/YgX3V62AsfjmQd0Iw8gor0VG2R/qruB14R3s2gxtyIMYmMI/dPBzGE6w9VXgyHDAGUMFoEkon4f9CRb8GH/u97Epx7M5emIg1K3buvIPYZBgPtor+DiHJi/k+Pr4ZNLg5BsXZZBzMLwpDLJg5zfI2lfwonKg/oqQOdE94fewF2AnkXrRMzLQ+WEBgpj+Zle2kDQkN+zfP2tO8CD9YauCyVhU55CGhOsKBPn6ZFzfBzT4cno8rm8BjZK/vgitVOcwWDOF24fhyaKdoqBdhaiXlQN11Ms1L+JIFnlEJTJGcSjuDlRcudGhBg2i3bBaHVXd+Yq7TXUXgJSmuoeiPg6m4kd/xD0Ccu9R3cMieA7cQvbTFE5dzk4a2MCqW+ZnOWR81QKTWpNb8ShUbkPEFbQKbydDgE6KjtLNdm3BITZM7WLffETbdE8jKZoQuOsNpfNIdb9qDiSCX/XkMUdX4IwYQceLWiAQGogr7D7cYPQ/2IbjFPbx0GlcxF2Hsd2WaJdO+mvEPcmZgB3fJGXiU5+2Dw/tCU+2oQzn8Wc7YB6fQSPSDtiG0BSChzBZcA7POqHLYI5n4t6/uJMOK20LS9LQtrwDV85oC4ZjO1cm36x67UUm28JBiPGWGZncMZFOOXdqi7t4rvo/QMpoBkHA2cPnMmS7nw3cjzw4LFHMCztc+JxTdqibgZX02dZt9gXYSs7sPa+OQ12DNzxPEurGLThHHpvignPosllzDfxt4n9jkO2arEj4KYRj7LLPzVPvDaomLAq6aFVoi5/XS5JHZU6HMXnOJvUNn3PI02BTfI2rjCaH5wHz2wMetPAHY6MYYgz+Dp/Qd83/CD9hEaShelFXb/ZhCNY/A2eAUuOPB5gEQvFHJoVOileSxwvqrgpA3KwSQ5kRb7viti/4FBH0WTqMmEcPoEnVgo2LcQ2tYi6zfCu0p7rRVSrK+WqlBTNU2Vk2QvMesC1E+IoFtaIAv7Pd0bsJSpGpVSjFKKJSKdKioifAYswZRQBVFnbX22jDgIvLg+gSUIKEWUMzTiS7WgniIMhHWvhMhe2/unBvz4883CPNju+KLUEk5otdo47BzxSJtoXvmDl1ehPeCLvR4bd4C8kfQWG0PmorFDrsgl10Fu06DFFj8Yue5gRQDruzGR0f2B3v09YIHb/+mN22bke5L0rsBfD8T0JtfNB8u6PT+JPYSfprIlpMsAP7YAxF8xHhMdEfmGvjPsIlhXQ3k2UFPFoJj2L/64/9LeI9yNIXYBg/SyQS1HjwUFgk2JYmWtZrRAQPTVPci9jyfTQGB/Ix2FuTF6HG6yxHTTbD8hGpRwJ+Ygbwc+FH2oTwI4sEThgmFSGjvhnVoLYHCbK+BOoTXYLRvKAYdfOpGFoNTLk2TgNxSzkdtJzfAqsb1svPTuyFGtlWu63RfGpOK68u/N0Ce76fTXsD24kexz7kk293FENN0M2NhB2ZyOOLdpr0JluC0y12LKX5KEuniXfAvL0Ul+5x/ClsLJrrtD3f6IsdxFdt9TgoXsDbI38RhNhXSYrUC9vx4W68K4TcsT3+2KnUbsrDx28muz0Wpa5Kh8cUkjhR+6/26LWPLVS9Vtu6XcAW2dZtUSaLitca7rpZ7u1nO/fw9QRGe/ROyFw+MZqNBnhRDIzmj1er5ByR9WM7/Tn55agFMWqT48/YWJgPOiM6/NwVk0Q3CLy1KQiXbSGicUb74DbMNv4ZbifRbQPc+qIRQR+Vr+ObH0EBbat3lFPjqM0LjgggmpUP0mwEsWVlX++Oj+bwWWSQoPjRovOXK0xsz8XPcd6sjbdBLA9mIy4qlRb2DtoxPOCIv6I91EGqCW+HIsan6S834TQtjlZ0w0AeL2xLT7MfMlyn4eqTkWYfANd1cC2Hawdcn2Xwd/h8BKwlX8Pv1fBryeS/IBck7vvD781w3a5fMQP9T9J5mgnw/IdwzYbrSbj+G66X4PofuN6Ea20mT7sdftv0yy7yvH1FXoZ3DfTw3Q1wDRX5exdc1XAV9/jXrjqR08U2eA7ufyvyOr+uf3s1/B7Rvx+DX7NeHnyHF0YYZVkdCSOVw2hjr4tAZ3aRLppirNMDtgvFAFcXiAFTq9X13K4knnrbLtq1+qrFTrXM6VovDSoHiaKUc4UoRi07zvHd2RP4jVm6LJWEzQu3W/8Pd36/a8PcmdL3w11DbD9DbiHcdVvN4+GuImlmuKtMrlVhr4aNwSeiR5a7u/CUH8VC2+oNvQShbA1M2C8fhymskBuAFd7CGERP46veg1cfPE5l/JHqdcCYcu2QHlFMsQdHo55ydv7oHNzHM0fbUVDsq8mOdGFNPJKjj40Brid2e2TxDhRzzmbMvUmdbEU8iXR8ECDhtPP/AQAA//+svX9AlFXWOP7MMMAIIzMqKCoW/koSKls0pZHCdJB+QAOjDGagtcVOs7Zr9jxKJSgNYz49jrmt/dqs7Hf7ru1amzlmKYivYLpK5RYFW+xm26WhbdxYxESe7znnPs8woO37vp/v8gfzPPfHuefee+6559x7znmc2T2lnrHvCoK8uJeNPK2qObOXScbs+orDB2yCb+rGyak2oVQ55avxCOJwpcijGDzXnlNV1en0Cl5BOcaMYVWtOGAWvKageONIGzvw30kClK+29O2PzRPWW/1PCoKgxKlbtuJvr1+1btyAT/lZ/nrJG3CEnSwBQGBO1UrfnRZBcYQVs+/OPiGw2FLi8aweZXOqI/z1VZcqDkugdGZJoHRGiZyfpZidarFFXZ2lSmZPAZRiX02wCUqhTTZAQV9hn5qt+uvFCVTOHEpxRsq9p5fLVpUm9g3ge8AieGwmQQj+BnvwHKRg++xvzwFeBSa2Z5Wqsq8gtZEZXoCuBwLsLKRMvKFfVXadhEclLlt1ewSjIAQCXfBerBw75Ogzqk4LYJAV8GOa07MVWvDUV42yeep/PsoW8CMQz0vw6GQbbulXfQdTQ5MvXGgTFbqNCiW7
*/