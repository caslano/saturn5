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
1aL4j34b3/Nmux7l4qbxX84avzLp9Pi7l5ljHQkM+D5F4f/jIpPYPDG+0oMGvWGEVksgmRnvWQ7ZbzwIvprvsgtuW8Kr5gfdcD+1k1actuCy+SJCdbm0oAgBoc9fFHnaOf2sI8/f9tVWfKnef1HcE1WswR3Zttys7fsPGevdeaQrlPgc6sdFhHl42SeFLPb4WsneGVq/HPIkbxAbJ/3E3+Ekx+WZivNRvN46YM69s1qN40g3zDW90hyfEQ8vJ/SWeX0PLbaWJ6eNWlKIOYVlQXS2Xh/eL3u7VmhZnj5QDfogDx2LD9X36Z5c/x+wn/hydbSUkEU5kyeN0KWYFoat29iwJ3XRmGl+mrboP+U31KecmK4UUblDUu9VbU9/L8xzLDDARgS0FCfiYut3/XfCnG/UbW8SfVZSKrsK9IpLHhmU3yaeIEhLEXxLI1th2nPJJwM+Y2X07BVohrc10DuqlwO8D5Y3Gq/SMfUn25TuqlDlxB1rhVapLRuFHK4bQb5K7+UJ/v4D8wbtufGSa5Rs3RFzW9bsEg7gEeQDSfOxwUqoP6wLOcFBnjUbr19iBlCXkpcqr3X404kjU0J1ruLOfemxrgOcvk5gbeAq7LZ031D5h0bheNjOl7Xjq7W5/77B5rgdE2dzt5M9T/EankXb+6PJifbd/2P5v/zwf7Ce9qtK1kfWZQFmsA7bk9r1YFepsk0rAc+qLX/icD9o
*/