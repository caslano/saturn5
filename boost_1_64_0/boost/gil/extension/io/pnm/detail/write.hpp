//
// Copyright 2012 Christian Henning
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_EXTENSION_IO_PNM_DETAIL_WRITE_HPP
#define BOOST_GIL_EXTENSION_IO_PNM_DETAIL_WRITE_HPP

#include <boost/gil/extension/io/pnm/tags.hpp>
#include <boost/gil/extension/io/pnm/detail/writer_backend.hpp>

#include <boost/gil/io/base.hpp>
#include <boost/gil/io/bit_operations.hpp>
#include <boost/gil/io/device.hpp>
#include <boost/gil/io/dynamic_io_new.hpp>
#include <boost/gil/detail/mp11.hpp>

#include <cstdlib>
#include <string>
#include <type_traits>

namespace boost { namespace gil {

#if BOOST_WORKAROUND(BOOST_MSVC, >= 1400)
#pragma warning(push)
#pragma warning(disable:4512) //assignment operator could not be generated
#endif

namespace detail {

struct pnm_write_is_supported
{
    template< typename View >
    struct apply
        : public is_write_supported< typename get_pixel_type< View >::type
                                   , pnm_tag
                                   >
    {};
};

} // namespace detail

///
/// PNM Writer
///
template< typename Device >
class writer< Device
            , pnm_tag
            >
    : public writer_backend< Device
                           , pnm_tag
                           >
{
private:
    using backend_t = writer_backend<Device, pnm_tag>;

public:

    writer( const Device&                      io_dev
          , const image_write_info< pnm_tag >& info
          )
    : backend_t( io_dev
                , info
                )
    {}

    template< typename View >
    void apply( const View& view )
    {
        using pixel_t = typename get_pixel_type<View>::type;

        std::size_t width  = view.width();
        std::size_t height = view.height();

        std::size_t chn    = num_channels< View >::value;
        std::size_t pitch  = chn * width;

        unsigned int type = get_type< num_channels< View >::value >( is_bit_aligned< pixel_t >() );

        // write header

        // Add a white space at each string so read_int() can decide when a numbers ends.

        std::string str( "P" );
        str += std::to_string( type ) + std::string( " " );
        this->_io_dev.print_line( str );

        str.clear();
        str += std::to_string( width ) + std::string( " " );
        this->_io_dev.print_line( str );

        str.clear();
        str += std::to_string( height ) + std::string( " " );
        this->_io_dev.print_line( str );

        if( type != pnm_image_type::mono_bin_t::value )
        {
            this->_io_dev.print_line( "255 ");
        }

        // write data
        write_data( view
                  , pitch
                  , typename is_bit_aligned< pixel_t >::type()
                  );
    }

private:

    template< int Channels >
    unsigned int get_type( std::true_type  /* is_bit_aligned */ )
    {
        return mp11::mp_if_c
            <
                Channels == 1,
                pnm_image_type::mono_bin_t,
                pnm_image_type::color_bin_t
            >::value;
    }

    template< int Channels >
    unsigned int get_type( std::false_type /* is_bit_aligned */ )
    {
        return mp11::mp_if_c
            <
                Channels == 1,
                pnm_image_type::gray_bin_t,
                pnm_image_type::color_bin_t
            >::value;
    }

    template< typename View >
    void write_data( const View&   src
                   , std::size_t   pitch
                   , const std::true_type&    // bit_aligned
                   )
    {
        static_assert(std::is_same<View, typename gray1_image_t::view_t>::value, "");

        byte_vector_t row( pitch / 8 );

        using x_it_t = typename View::x_iterator;
        x_it_t row_it = x_it_t( &( *row.begin() ));

        detail::negate_bits<byte_vector_t, std::true_type> negate;
        detail::mirror_bits<byte_vector_t, std::true_type> mirror;
        for (typename View::y_coord_t y = 0; y < src.height(); ++y)
        {
            std::copy(src.row_begin(y), src.row_end(y), row_it);

            mirror(row);
            negate(row);

            this->_io_dev.write(&row.front(), pitch / 8);
        }
    }

    template< typename View >
    void write_data( const View&   src
                   , std::size_t   pitch
                   , const std::false_type&    // bit_aligned
                   )
    {
        std::vector< pixel< typename channel_type< View >::type
                          , layout<typename color_space_type< View >::type >
                          >
                   > buf( src.width() );

        // using pixel_t = typename View::value_type;
        // using view_t = typename view_type_from_pixel< pixel_t >::type;

        //view_t row = interleaved_view( src.width()
        //                             , 1
        //                             , reinterpret_cast< pixel_t* >( &buf.front() )
        //                             , pitch
        //                             );

        byte_t* row_addr = reinterpret_cast< byte_t* >( &buf.front() );

        for( typename View::y_coord_t y = 0
           ; y < src.height()
           ; ++y
           )
        {
            //copy_pixels( subimage_view( src
            //                          , 0
            //                          , (int) y
            //                          , (int) src.width()
            //                          , 1
            //                          )
            //           , row
            //           );

            std::copy( src.row_begin( y )
                     , src.row_end  ( y )
                     , buf.begin()
                     );

            this->_io_dev.write( row_addr, pitch );
        }
    }
};

///
/// PNM Writer
///
template< typename Device >
class dynamic_image_writer< Device
                          , pnm_tag
                          >
    : public writer< Device
                   , pnm_tag
                   >
{
    using parent_t = writer<Device, pnm_tag>;

public:

    dynamic_image_writer( const Device&                      io_dev
                        , const image_write_info< pnm_tag >& info
                        )
    : parent_t( io_dev
              , info
              )
    {}

    template< typename Views >
    void apply( const any_image_view< Views >& views )
    {
        detail::dynamic_io_fnobj< detail::pnm_write_is_supported
                                , parent_t
                                > op( this );

        apply_operation( views, op );
    }
};

#if BOOST_WORKAROUND(BOOST_MSVC, >= 1400)
#pragma warning(pop)
#endif

} // gil
} // boost

#endif

/* write.hpp
9vRani2z5oKOxk6sPvMnrfDOWanWwK6HbznB5s6Iym4V23z74TdjMA3e9YzLRCFe77HTYI4tA/PYMjDXloG59gjMY4/AXHsE5tojMI89AnPtEZhrj8A89gjMjTGCufYIzBNPBHNtD5hre8A8tgfM1XcwV4/BPDoL5uonmKtPYBvhh/f0cpQKIQ38Vv+6/SmlR9C0bHIkJ1lpJVxyaPWtPVyiiwshOTIzwyMzYI4MgnlkEMwdOzB3nMA8fgaY24dgbh+CbcSeVEdbqrkhPAbQvHxFzp7Uq1n+RdY5g/AIirn6oC3wKiSn/TM97Qdz+xPM7U8wjw6CuToI5uogmEcHwVwdBHN1EMyjg2CuDoK54wjm0UEwd2zBXJ8AzKOXYK5egrl6CeaZ18FcXQVzdRXMo6tgrpyBuXIG9jfMfZlJpSdPrG3T4e7ZpdnY+tGDaKsQg/fID5grP2CuPoJ55BHMHUcwd8zAPPoI5vYTmNtPYBvh9wf6aF7dbe7uC7ff0Uq3jwYP9+0V7xPOn20pPjK1mrnfrM7a7PmZOdAXDeJpeD/l0a9PefQLzNUvMFe/wDz6BebqF5irX2Ab0T82hhuEMULXJZQip39GD/edpSij/YH3Y1ehNg/ZaDnui9yw3ihkwhDlyPGOWWM0wY6R9p2iXMKrsYP7ETzyOdsj72CuvIO58g7mkVkwV2bBXJkF24gxCWU2mg/M4QZff+zhyGx/cwkBBsZ0ovZJQx5DDTlTBMYI9jRH92y5slzmkeUyjyyXeWS5zCPLZR5ZLvPIctlG9JuWpXDDPuWT5ZIsWZ7o+ODmyfDGwcZsr10m98/rRr7eHCg/Yp/FX+Hjd6M5gU+yMfyZqBbPKTlwnkOJuD7M+GpoYvjZBr5b6tOlco8ulXt0CczVJYtVjo2wc/fNYAsM9hmDuTpX7tG5co/OlW+s3xZ89DR021yZqcjSNfn/f///7////f+////3///+/99/1H/b4KtsRdqVtDVpS9J2pB1JY0kLSTWkKlI9qZa0jHQo6RBSC2kFqZW0hPRN0pmkC0knm78fJz1K+g3pRdJjQWwhyJf4fxOplbQ/qYV0HOmsMfCQniM9TXppTLSXOIo0krQLaTxpZ1INqYq0hNRsfg8htZBOJH2PdCHpG6SzSN8hnU26iHQf6SXSvaQJO9IXpC1Jg0nDSTuSxpF2IVWTmkhVpAtI3yR9g3QG6T7SY6S7SA+QHjb/foL0LGn0CJF35uG7Xx2TH7fEZJtD8BfXJ+SuM+Py1IiYVL8g8uU/xuWuZQn55kdx2XafhPzp1YQ8yUGYP50lUvpYTH5wfkzueU7kgG6RK8oSspzFwCGPJqTuNpHiw+m/N2Nyw5q4jBgRlVdA2oX0mwvictu+cVkwLCGP9cXkwJ3jck8qLj3nxeSzvxF54ysx+c5RCZk3OiEH48lte3FMloyPyaEXxeTnE2Py8IVxufrhuLz6ckKeOTYh27GAGfGlhFSWxeSam2KybDhl/yQmj52SkE+ticn8D5Cbl+Ly7vKYPPMx7UzG5eTSmDx1GtG+vyTkozsSMvRd2rhAZPGYuDy+Z1x+tDQhv/opckV929n3WbUZ65+TWLdTxhevSsgdj8Tk5fdj8t6mIpt9Gp+3JyaDexgTyv/L52Jy5uYiPRcn5NDjEvLdJ2PS8WeRo1hAPXldXGq+wPgcFZOzH43LAdvxXG1MnjwnJrG5CXl7eVzG/pH8To9L35kJOW+IyJW7iXzyAsb29YQseC0h3V1xGbQ6Jpe8Tz3fRKbB//jlmPSBL7kDeT4aediCuMeTcbn+dpEv0aZWxi91WkJuPFHkZ7Uit0+kP+nT6+iDX7ydkMsaEvKZo+Ny0Yw=
*/