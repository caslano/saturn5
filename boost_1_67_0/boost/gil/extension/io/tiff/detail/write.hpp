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

    template< typename Views >
    void apply( const any_image_view< Views >& views )
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