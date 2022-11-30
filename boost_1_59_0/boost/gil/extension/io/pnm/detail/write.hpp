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

    template< typename ...Views >
    void apply( const any_image_view< Views... >& views )
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
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
*/