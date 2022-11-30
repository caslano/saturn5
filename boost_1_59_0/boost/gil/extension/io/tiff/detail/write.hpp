//
// Copyright 2007-2012 Christian Henning, Lubomir Bourdev
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_EXTENSION_IO_TIFF_DETAIL_WRITE_HPP
#define BOOST_GIL_EXTENSION_IO_TIFF_DETAIL_WRITE_HPP

#include <boost/gil/extension/io/tiff/tags.hpp>
#include <boost/gil/extension/io/tiff/detail/writer_backend.hpp>
#include <boost/gil/extension/io/tiff/detail/device.hpp>

#include <boost/gil/premultiply.hpp>
#include <boost/gil/io/base.hpp>
#include <boost/gil/io/device.hpp>
#include <boost/gil/io/dynamic_io_new.hpp>

#include <algorithm>
#include <string>
#include <type_traits>
#include <vector>

extern "C" {
#include "tiff.h"
#include "tiffio.h"
}

namespace boost { namespace gil {

#if BOOST_WORKAROUND(BOOST_MSVC, >= 1400)
#pragma warning(push)
#pragma warning(disable:4512) //assignment operator could not be generated
#endif

namespace detail {

template <typename PixelReference>
struct my_interleaved_pixel_iterator_type_from_pixel_reference
{
private:
    using pixel_t = typename std::remove_reference<PixelReference>::type::value_type;

public:
    using type = typename iterator_type_from_pixel
        <
            pixel_t,
            false,
            false,
            true
        >::type;
};


template< typename Channel
        , typename Layout
        , bool Mutable
        >
struct my_interleaved_pixel_iterator_type_from_pixel_reference< const bit_aligned_pixel_reference< byte_t
                                                                                                 , Channel
                                                                                                 , Layout
                                                                                                 , Mutable
                                                                                                 >
                                                              >
    : public iterator_type_from_pixel< const bit_aligned_pixel_reference< uint8_t
                                                                        , Channel
                                                                        , Layout
                                                                        , Mutable
                                                                        >
                                     ,false
                                     ,false
                                     ,true
                                     > {};

struct tiff_write_is_supported
{
    template< typename View >
    struct apply
        : public is_write_supported< typename get_pixel_type< View >::type
                                   , tiff_tag
                                   >
    {};
};

} // namespace detail

///
/// TIFF Writer
///
template < typename Device, typename Log >
class writer< Device
            , tiff_tag
            , Log
            >
    : public writer_backend< Device
                           , tiff_tag
                           >
{
private:
    using backend_t = writer_backend<Device, tiff_tag>;

public:

    writer( const Device&                       io_dev
          , const image_write_info< tiff_tag >& info
          )
    : backend_t( io_dev
               , info
               )
    {}

    template<typename View>
    void apply( const View& view )
    {
        write_view( view );
    }

private:

    template< typename View >
    void write_view( const View& view )
    {
        using pixel_t = typename View::value_type;
        // get the type of the first channel (heterogeneous pixels might be broken for now!)
        using channel_t = typename channel_traits<typename element_type<pixel_t>::type>::value_type;
        tiff_bits_per_sample::type bits_per_sample = detail::unsigned_integral_num_bits< channel_t >::value;

        tiff_samples_per_pixel::type samples_per_pixel = num_channels< pixel_t >::value;

        this->write_header( view );

        if( this->_info._is_tiled == false )
        {
            write_data( view
                      , (view.width() * samples_per_pixel * bits_per_sample + 7) / 8
                      , typename is_bit_aligned< pixel_t >::type()
                      );
        }
        else
        {
            tiff_tile_width::type  tw = this->_info._tile_width;
            tiff_tile_length::type th = this->_info._tile_length;

            if(!this->_io_dev.check_tile_size( tw, th ))
            {
                io_error( "Tile sizes need to be multiples of 16." );
            }

            // tile related tags
            this->_io_dev.template set_property<tiff_tile_width> ( tw );
            this->_io_dev.template set_property<tiff_tile_length>( th );

            write_tiled_data( view
                            , tw
                            , th
                            , typename is_bit_aligned< pixel_t >::type()
                            );
        }
    }

	//////////////////////////////

	template<typename View>
	void write_bit_aligned_view_to_dev( const View&       view
                                      , const std::size_t row_size_in_bytes
                                      , const std::true_type&    // has_alpha
                                      )
    {
        byte_vector_t row( row_size_in_bytes );

        using x_it_t = typename View::x_iterator;
        x_it_t row_it = x_it_t( &(*row.begin()));

		auto pm_view = premultiply_view <typename View:: value_type> (view);

        for( typename View::y_coord_t y = 0; y < pm_view.height(); ++y )
        {
					std::copy( pm_view.row_begin( y )
										 , pm_view.row_end( y )
										 , row_it
						);


            this->_io_dev.write_scaline( row
                                       , (uint32) y
                                       , 0
                                       );

            // @todo: do optional bit swapping here if you need to...
        }
    }

	template<typename View>
	void write_bit_aligned_view_to_dev( const View&       view
                                      , const std::size_t row_size_in_bytes
                                      , const std::false_type&    // has_alpha
                                      )
    {
        byte_vector_t row( row_size_in_bytes );

        using x_it_t = typename View::x_iterator;
        x_it_t row_it = x_it_t( &(*row.begin()));

        for( typename View::y_coord_t y = 0; y < view.height(); ++y )
        {
			std::copy( view.row_begin( y )
                     , view.row_end( y )
                     , row_it
				     );


            this->_io_dev.write_scaline( row
                                       , (uint32) y
                                       , 0
                                       );

            // @todo: do optional bit swapping here if you need to...
        }
    }

    /////////////////////////////

    template< typename View >
    void write_data( const View&   view
                   , std::size_t   row_size_in_bytes
                   , const std::true_type&    // bit_aligned
                   )
    {
        using colour_space_t = typename color_space_type<typename View::value_type>::type;
        using has_alpha_t = mp11::mp_contains<colour_space_t, alpha_t>;

        write_bit_aligned_view_to_dev(view, row_size_in_bytes, has_alpha_t());
    }

    template< typename View>
    void write_tiled_data( const View&            view
                         , tiff_tile_width::type  tw
                         , tiff_tile_length::type th
                         , const std::true_type&    // bit_aligned
                         )
    {
        byte_vector_t row( this->_io_dev.get_tile_size() );

        using x_it_t = typename View::x_iterator;
        x_it_t row_it = x_it_t( &(*row.begin()));

        internal_write_tiled_data(view, tw, th, row, row_it);
    }

    template< typename View >
    void write_data( const View&   view
                   , std::size_t
                   , const std::false_type&    // bit_aligned
                   )
    {
        std::vector< pixel< typename channel_type< View >::type
                          , layout<typename color_space_type< View >::type >
                          >
                   > row( view.size() );

        byte_t* row_addr = reinterpret_cast< byte_t* >( &row.front() );

				// @todo: is there an overhead to doing this when there's no
				// alpha to premultiply by? I'd hope it's optimised out.
				auto pm_view = premultiply_view <typename View:: value_type> (view);

        for( typename View::y_coord_t y = 0; y < pm_view.height(); ++y )
        {
					std::copy( pm_view.row_begin( y )
										 , pm_view.row_end( y )
										 , row.begin()
						);

            this->_io_dev.write_scaline( row_addr
                                       , (uint32) y
                                       , 0
                                       );

            // @todo: do optional bit swapping here if you need to...
        }
    }

    template< typename View >
    void write_tiled_data( const View&            view
                         , tiff_tile_width::type  tw
                         , tiff_tile_length::type th
                         , const std::false_type&    // bit_aligned
                         )
    {
        byte_vector_t row( this->_io_dev.get_tile_size() );

        using x_iterator = typename detail::my_interleaved_pixel_iterator_type_from_pixel_reference<typename View::reference>::type;
        x_iterator row_it = x_iterator( &(*row.begin()));

        internal_write_tiled_data(view, tw, th, row, row_it);
    }


	//////////////////////////////

	template< typename View
            , typename IteratorType
            >
	void write_tiled_view_to_dev( const View&  view
                                , IteratorType it
                                , const std::true_type& // has_alpha
                                )
    {
        auto pm_view = premultiply_view <typename View:: value_type>( view );

        std::copy( pm_view.begin()
                 , pm_view.end()
                 , it
                 );
    }


	template< typename View
            , typename IteratorType
            >
	void write_tiled_view_to_dev( const View&  view
                                , IteratorType it
                                , const std::false_type& // has_alpha
                                )
    {
        std::copy( view.begin()
                 , view.end()
                 , it
                 );
    }

    /////////////////////////////



    template< typename View,
              typename IteratorType
            >
    void internal_write_tiled_data( const View&            view
                                  , tiff_tile_width::type  tw
                                  , tiff_tile_length::type th
                                  , byte_vector_t&         row
                                  , IteratorType           it
                                  )
    {
        std::ptrdiff_t i = 0, j = 0;
        View tile_subimage_view;
        while( i < view.height() )
        {
            while( j < view.width() )
            {
                if( j + tw < view.width() && i + th < view.height() )
                {
                    // a tile is fully included in the image: just copy values
                    tile_subimage_view = subimage_view( view
                                                      , static_cast< int >( j  )
                                                      , static_cast< int >( i  )
                                                      , static_cast< int >( tw )
                                                      , static_cast< int >( th )
                                                      );

                    using colour_space_t = typename color_space_type<typename View::value_type>::type;
                    using has_alpha_t = mp11::mp_contains<colour_space_t, alpha_t>;

                    write_tiled_view_to_dev(tile_subimage_view, it, has_alpha_t());
                }
                else
                {
                    std::ptrdiff_t width  = view.width();
                    std::ptrdiff_t height = view.height();

                    std::ptrdiff_t current_tile_width  = ( j + tw < width ) ? tw : width  - j;
                    std::ptrdiff_t current_tile_length = ( i + th < height) ? th : height - i;

                    tile_subimage_view = subimage_view( view
                                                      , static_cast< int >( j )
                                                      , static_cast< int >( i )
                                                      , static_cast< int >( current_tile_width )
                                                      , static_cast< int >( current_tile_length )
                                                      );

                    for( typename View::y_coord_t y = 0; y < tile_subimage_view.height(); ++y )
                    {
                        std::copy( tile_subimage_view.row_begin( y )
                                 , tile_subimage_view.row_end( y )
                                 , it
                                 );
                        std::advance(it, tw);
                    }

                    it = IteratorType( &(*row.begin()));
                }

                this->_io_dev.write_tile( row
                                        , static_cast< uint32 >( j )
                                        , static_cast< uint32 >( i )
                                        , 0
                                        , 0
                                        );
                j += tw;
            }
            j = 0;
            i += th;
        }
        // @todo: do optional bit swapping here if you need to...
    }
};

///
/// TIFF Dynamic Image Writer
///
template< typename Device >
class dynamic_image_writer< Device
                          , tiff_tag
                          >
    : public writer< Device
                   , tiff_tag
                   >
{
    using parent_t = writer<Device, tiff_tag>;

public:

    dynamic_image_writer( const Device&                       io_dev
                        , const image_write_info< tiff_tag >& info
                        )
    : parent_t( io_dev
              , info
              )
    {}

    template< typename ...Views >
    void apply( const any_image_view< Views... >& views )
    {
        detail::dynamic_io_fnobj< detail::tiff_write_is_supported
                                , parent_t
                                > op( this );

        apply_operation( views, op );
    }
};

#if BOOST_WORKAROUND(BOOST_MSVC, >= 1400)
#pragma warning(pop)
#endif

} // namespace gil
} // namespace boost

#endif

/* write.hpp
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
*/