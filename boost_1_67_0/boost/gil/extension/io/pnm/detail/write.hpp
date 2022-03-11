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
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
*/