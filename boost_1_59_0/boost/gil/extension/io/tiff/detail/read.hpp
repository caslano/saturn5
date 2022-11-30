//
// Copyright 2007-2012 Christian Henning, Lubomir Bourdev
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_EXTENSION_IO_TIFF_DETAIL_READER_HPP
#define BOOST_GIL_EXTENSION_IO_TIFF_DETAIL_READER_HPP

#include <boost/gil/extension/io/tiff/detail/device.hpp>
#include <boost/gil/extension/io/tiff/detail/is_allowed.hpp>
#include <boost/gil/extension/io/tiff/detail/reader_backend.hpp>

#include <boost/gil/io/base.hpp>
#include <boost/gil/io/bit_operations.hpp>
#include <boost/gil/io/conversion_policies.hpp>
#include <boost/gil/io/device.hpp>
#include <boost/gil/io/dynamic_io_new.hpp>
#include <boost/gil/io/reader_base.hpp>
#include <boost/gil/io/row_buffer_helper.hpp>

#include <boost/assert.hpp>

#include <algorithm>
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

#if BOOST_WORKAROUND(BOOST_MSVC, >= 1400)
#pragma warning(push)
#pragma warning(disable:4512) //assignment operator could not be generated
#endif

template < int K >
struct plane_recursion
{
   template< typename View
           , typename Device
           , typename ConversionPolicy
           >
   static
   void read_plane( const View& dst_view
                  , reader< Device
                          , tiff_tag
                          , ConversionPolicy >* p
                  )
   {
        using plane_t = typename kth_channel_view_type<K, View>::type;
        plane_t plane = kth_channel_view<K>( dst_view );

        p->template read_data< detail::row_buffer_helper_view< plane_t > >( plane, K );

        plane_recursion< K - 1 >::read_plane( dst_view, p );
   }
};

template <>
struct plane_recursion< -1 >
{
   template< typename View
           , typename Device
           , typename ConversionPolicy
           >
   static
   void read_plane( const View&               /* dst_view */
                  , reader< Device
                          , tiff_tag
                          , ConversionPolicy
                          >*                  /* p         */
                  )
    {}
};

///
/// Tiff Reader
///
template< typename Device
        , typename ConversionPolicy
        >
class reader< Device
            , tiff_tag
            , ConversionPolicy
            >
    : public reader_base< tiff_tag
                        , ConversionPolicy >

    , public reader_backend< Device
                           , tiff_tag
                           >
{
private:

    using this_t = reader<Device, tiff_tag, ConversionPolicy>;
    using cc_t = typename ConversionPolicy::color_converter_type;

public:

    using backend_t = reader_backend<Device, tiff_tag>;

    reader( const Device&                          io_dev
          , const image_read_settings< tiff_tag >& settings
          )
    : reader_base< tiff_tag
                 , ConversionPolicy
                 >()
    , backend_t( io_dev
               , settings
               )
    {}

    reader( const Device&                                          io_dev
          , const typename ConversionPolicy::color_converter_type& cc
          , const image_read_settings< tiff_tag >&                 settings
          )
    : reader_base< tiff_tag
                 , ConversionPolicy
                 >( cc )
    , backend_t( io_dev
               , settings
               )
    {}

    // only works for homogeneous image types
    template< typename View >
    void apply( View& dst_view )
    {
        if( this->_info._photometric_interpretation == PHOTOMETRIC_PALETTE )
        {
            this->_scanline_length = this->_info._width
                                   * num_channels< rgb16_view_t >::value
                                   * sizeof( channel_type<rgb16_view_t>::type );

            // Steps:
            // 1. Read indices. It's an array of grayX_pixel_t.
            // 2. Read palette. It's an array of rgb16_pixel_t.
            // 3. ??? Create virtual image or transform the two arrays
            //    into a rgb16_image_t object. The latter might
            //    be a good first solution.

            switch( this->_info._bits_per_sample )
            {
                case 1:  { read_palette_image< gray1_image_t  >( dst_view ); break; }
                case 2:  { read_palette_image< gray2_image_t  >( dst_view ); break; }
                case 4:  { read_palette_image< gray4_image_t  >( dst_view ); break; }
                case 8:  { read_palette_image< gray8_image_t  >( dst_view ); break; }
                case 16: { read_palette_image< gray16_image_t >( dst_view ); break; }

                default: { io_error( "Not supported palette " ); }
            }

            return;

        }
        else
        {
            this->_scanline_length = this->_io_dev.get_scanline_size();

            // In case we only read the image the user's type and
            // the tiff type need to compatible. Which means:
            // color_spaces_are_compatible && channels_are_pairwise_compatible

            using is_read_only = typename std::is_same
                <
                    ConversionPolicy,
                    detail::read_and_no_convert
                >::type;

            io_error_if( !detail::is_allowed< View >( this->_info
                                                    , is_read_only()
                                                    )
                       , "Image types aren't compatible."
                       );

            if( this->_info._planar_configuration == PLANARCONFIG_SEPARATE )
            {
                plane_recursion< num_channels< View >::value - 1 >::read_plane( dst_view
                                                                              , this
                                                                              );
            }
            else if( this->_info._planar_configuration == PLANARCONFIG_CONTIG )
            {
                read( dst_view
                    , typename is_read_only::type()
                    );
            }
            else
            {
                io_error( "Wrong planar configuration setting." );
            }
        }
    }

private:

    template< typename View >
    void read( View v
             , std::true_type // is_read_only
             )
    {
        read_data< detail::row_buffer_helper_view< View > >( v, 0 );
    }

    template< typename View >
    void read( View v
             , std::false_type  // is_read_only
             )
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
                    case  1: { read_data< detail::row_buffer_helper_view< gray1_image_t::view_t > >( v, 0 );  break; }
                    case  2: { read_data< detail::row_buffer_helper_view< gray2_image_t::view_t > >( v, 0 );  break; }
                    case  4: { read_data< detail::row_buffer_helper_view< gray4_image_t::view_t > >( v, 0 );  break; }
                    case  8: { read_data< detail::row_buffer_helper_view< gray8_view_t  > >( v, 0 );  break; }
                    case 16: { read_data< detail::row_buffer_helper_view< gray16_view_t > >( v, 0 );  break; }
                    case 32: { read_data< detail::row_buffer_helper_view< gray32_view_t > >( v, 0 );  break; }
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
                            case  8: { read_data< detail::row_buffer_helper_view< rgb8_view_t  > >( v, 0 );  break; }
                            case 16: { read_data< detail::row_buffer_helper_view< rgb16_view_t > >( v, 0 );  break; }
                            case 32: { read_data< detail::row_buffer_helper_view< rgb32_view_t > >( v, 0 );  break; }
                            default: { io_error( "Image type is not supported." ); }
                        }

                        break;
                    }

                    case 4:
                    {
                        switch( this->_info._bits_per_sample )
                        {
                            case  8: { read_data< detail::row_buffer_helper_view< rgba8_view_t  > >( v, 0 );  break; }
                            case 16: { read_data< detail::row_buffer_helper_view< rgba16_view_t > >( v, 0 );  break; }
                            case 32: { read_data< detail::row_buffer_helper_view< rgba32_view_t > >( v, 0 );  break; }
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
                    case  8: { read_data< detail::row_buffer_helper_view< cmyk8_view_t  > >( v, 0 );  break; }
                    case 16: { read_data< detail::row_buffer_helper_view< cmyk16_view_t > >( v, 0 );  break; }
                    case 32: { read_data< detail::row_buffer_helper_view< cmyk32_view_t > >( v, 0 );  break; }
                    default: { io_error( "Image type is not supported." ); }
                }

                break;
            }

            default: { io_error( "Image type is not supported." ); }
        }
    }

   template< typename PaletteImage
           , typename View
           >
   void read_palette_image( const View& dst_view )
   {
      PaletteImage indices( this->_info._width  - this->_settings._top_left.x
                          , this->_info._height - this->_settings._top_left.y );

      // read the palette first
      read_data< detail::row_buffer_helper_view
          <
            typename PaletteImage::view_t>
        >(view(indices), 0);

      read_palette_image(dst_view, view(indices),
          typename std::is_same<View, rgb16_view_t>::type());
   }

   template< typename View
           , typename Indices_View
           >
   void read_palette_image( const View&         dst_view
                          , const Indices_View& indices_view
                          , std::true_type   // is View rgb16_view_t
                          )
   {
      tiff_color_map::red_t   red   = nullptr;
      tiff_color_map::green_t green = nullptr;
      tiff_color_map::blue_t  blue  = nullptr;

      this->_io_dev.get_field_defaulted( red, green, blue );

      using channel_t = typename channel_traits<typename element_type<typename Indices_View::value_type>::type>::value_type;

      int num_colors = channel_traits< channel_t >::max_value();

      rgb16_planar_view_t palette = planar_rgb_view( num_colors
                                                   , 1
                                                   , red
                                                   , green
                                                   , blue
                                                   , sizeof(uint16_t) * num_colors );

      for( typename rgb16_view_t::y_coord_t y = 0; y < dst_view.height(); ++y )
      {
         typename rgb16_view_t::x_iterator it  = dst_view.row_begin( y );
         typename rgb16_view_t::x_iterator end = dst_view.row_end( y );

         typename Indices_View::x_iterator indices_it = indices_view.row_begin( y );

         for( ; it != end; ++it, ++indices_it )
         {
            uint16_t i = gil::at_c<0>( *indices_it );

            *it = palette[i];
         }
      }
   }

   template< typename View
           , typename Indices_View
           >
   inline
   void read_palette_image( const View&         /* dst_view     */
                          , const Indices_View& /* indices_view */
                          , std::false_type  // is View rgb16_view_t
                          )
   {
      io_error( "User supplied image type must be rgb16_image_t." );
   }

   template< typename Buffer >
   void skip_over_rows( Buffer& buffer
                      , int     plane
                      )
   {
      if( this->_info._compression != COMPRESSION_NONE )
      {
         // Skipping over rows is not possible for compressed images(  no random access ). See man
         // page ( diagnostics section ) for more information.
         for( std::ptrdiff_t row = 0; row < this->_settings._top_left.y; ++row )
         {
            this->_io_dev.read_scanline( buffer
                                 , row
                                 , static_cast< tsample_t >( plane ));
         }
      }
   }

   template< typename Buffer
           , typename View
           >
   void read_data( const View& dst_view
                 , int         /* plane */ )
    {
        if( this->_io_dev.is_tiled() )
        {
            read_tiled_data< Buffer >( dst_view, 0 );
        }
        else
        {
            read_stripped_data< Buffer >( dst_view, 0 );
        }
    }


   template< typename Buffer
           , typename View
           >
   void read_tiled_data( const View& dst_view
                       , int         plane
                       )
   {
      if(  dst_view.width()  != this->_info._width
        || dst_view.height() != this->_info._height
        )
      {
          // read a subimage
          read_tiled_data_subimage< Buffer >( dst_view, plane );
      }
      else
      {
          // read full image
          read_tiled_data_full< Buffer >( dst_view, plane );
      }
   }

   template< typename Buffer
           , typename View
           >
   void read_tiled_data_subimage( const View& dst_view
                                , int         plane
                                )
   {
       ///@todo: why is
       /// using row_buffer_helper_t = Buffer;
       /// not working? I get compiler error with MSVC10.
       /// read_stripped_data IS working.
       using row_buffer_helper_t = detail::row_buffer_helper_view<View>;

       using it_t = typename row_buffer_helper_t::iterator_t;

       tiff_image_width::type  image_width  = this->_info._width;
       tiff_image_height::type image_height = this->_info._height;

       tiff_tile_width::type  tile_width  = this->_info._tile_width;
       tiff_tile_length::type tile_height = this->_info._tile_length;

       std::ptrdiff_t subimage_x = this->_settings._top_left.x;
       std::ptrdiff_t subimage_y = this->_settings._top_left.y;

       std::ptrdiff_t subimage_width  = this->_settings._dim.x;
       std::ptrdiff_t subimage_height = this->_settings._dim.y;

       row_buffer_helper_t row_buffer_helper(this->_io_dev.get_tile_size(), true );

       for( unsigned int y = 0; y < image_height; y += tile_height )
       {
           for( unsigned int x = 0; x < image_width; x += tile_width )
           {
               uint32_t current_tile_width  = ( x + tile_width  <  image_width ) ? tile_width  : image_width  - x;
               uint32_t current_tile_length = ( y + tile_height < image_height ) ? tile_height : image_height - y;

               this->_io_dev.read_tile( row_buffer_helper.buffer()
                                , x
                                , y
                                , 0
                                , static_cast< tsample_t >( plane )
                                );

               // these are all whole image coordinates
               point_t tile_top_left   ( x, y );
               point_t tile_lower_right( x + current_tile_width - 1, y + current_tile_length - 1 );

               point_t view_top_left   ( subimage_x, subimage_y );
               point_t view_lower_right( subimage_x + subimage_width  - 1
                                       , subimage_y + subimage_height - 1 );

               if(  tile_top_left.x    > view_lower_right.x
                 || tile_top_left.y    > view_lower_right.y
                 || tile_lower_right.x < view_top_left.x
                 || tile_lower_right.y < view_top_left.y
                 )
               {
                   // current tile and dst_view do not overlap
                   continue;
               }
               else
               {
                   // dst_view is overlapping the current tile

                   // next is to define the portion in the tile that needs to be copied

                   // get the whole image coordinates
                   std::ptrdiff_t img_x0 = ( tile_top_left.x >= view_top_left.x ) ? tile_top_left.x : view_top_left.x;
                   std::ptrdiff_t img_y0 = ( tile_top_left.y >= view_top_left.y ) ? tile_top_left.y : view_top_left.y;

                   std::ptrdiff_t img_x1 = ( tile_lower_right.x <= view_lower_right.x ) ? tile_lower_right.x : view_lower_right.x;
                   std::ptrdiff_t img_y1 = ( tile_lower_right.y <= view_lower_right.y ) ? tile_lower_right.y : view_lower_right.y;

                   // convert to tile coordinates
                   std::ptrdiff_t tile_x0 = img_x0 - x;
                   std::ptrdiff_t tile_y0 = img_y0 - y;
                   std::ptrdiff_t tile_x1 = img_x1 - x;
                   std::ptrdiff_t tile_y1 = img_y1 - y;

                   BOOST_ASSERT(tile_x0 >= 0 && tile_y0 >= 0 && tile_x1 >= 0 && tile_y1 >= 0);
                   BOOST_ASSERT(tile_x0 <= img_x1 && tile_y0 <= img_y1);
                   BOOST_ASSERT(tile_x0 < tile_width && tile_y0 < tile_height && tile_x1 < tile_width && tile_y1 < tile_height);

                   std::ptrdiff_t tile_subimage_view_width  = tile_x1 - tile_x0 + 1;
                   std::ptrdiff_t tile_subimage_view_height = tile_y1 - tile_y0 + 1;

                   // convert to dst_view coordinates
                   std::ptrdiff_t dst_x0 = img_x0 - subimage_x;
                   std::ptrdiff_t dst_y0 = img_y0 - subimage_y;
                   BOOST_ASSERT(dst_x0 >= 0 && dst_y0 >= 0);

                   View dst_subimage_view = subimage_view( dst_view
                                                         , (int) dst_x0
                                                         , (int) dst_y0
                                                         , (int) tile_subimage_view_width
                                                         , (int) tile_subimage_view_height
                                                         );

                   // the row_buffer is a 1D array which represents a 2D image. We cannot
                   // use interleaved_view here, since row_buffer could be bit_aligned.
                   // Interleaved_view's fourth parameter "rowsize_in_bytes" doesn't work
                   // for bit_aligned pixels.

                   for( std::ptrdiff_t dst_row = 0; dst_row < dst_subimage_view.height(); ++dst_row )
                   {
                       std::ptrdiff_t tile_row = dst_row + tile_y0;

                       // jump to the beginning of the current tile row
                       it_t begin = row_buffer_helper.begin() + tile_row * tile_width;

                       begin    += tile_x0;
                       it_t end  = begin + dst_subimage_view.width();

                       this->_cc_policy.read( begin
                                            , end
                                            , dst_subimage_view.row_begin( dst_row )
                                            );
                    } //for
               }
           } // for
       } // for
   }

   template< typename Buffer
           , typename View
           >
   void read_tiled_data_full( const View& dst_view
                            , int         plane
                            )
   {
       ///@todo: why is
       /// using row_buffer_helper_t = Buffer;
       /// not working? I get compiler error with MSVC10.
       /// read_stripped_data IS working.
       using row_buffer_helper_t = detail::row_buffer_helper_view<View>;

       using it_t = typename row_buffer_helper_t::iterator_t;

       tiff_image_width::type  image_width  = this->_info._width;
       tiff_image_height::type image_height = this->_info._height;

       tiff_tile_width::type  tile_width  = this->_info._tile_width;
       tiff_tile_length::type tile_height = this->_info._tile_length;

       row_buffer_helper_t row_buffer_helper(this->_io_dev.get_tile_size(), true );

       for( unsigned int y = 0; y < image_height; y += tile_height )
       {
           for( unsigned int x = 0; x < image_width; x += tile_width )
           {
               uint32_t current_tile_width  = ( x + tile_width  <  image_width ) ? tile_width  : image_width  - x;
               uint32_t current_tile_length = ( y + tile_height < image_height ) ? tile_height : image_height - y;

               this->_io_dev.read_tile( row_buffer_helper.buffer()
                                , x
                                , y
                                , 0
                                , static_cast< tsample_t >( plane )
                                );

               View dst_subimage_view = subimage_view( dst_view
                                                     , x
                                                     , y
                                                     , current_tile_width
                                                     , current_tile_length
                                                     );

               // the row_buffer is a 1D array which represents a 2D image. We cannot
               // use interleaved_view here, since row_buffer could be bit_aligned.
               // Interleaved_view's fourth parameter "rowsize_in_bytes" doesn't work
               // for bit_aligned pixels.

               for( int row = 0; row < dst_subimage_view.height(); ++row )
               {
                   it_t begin = row_buffer_helper.begin() + row * tile_width;
                   it_t end   = begin + dst_subimage_view.width();

                   this->_cc_policy.read( begin
                                        , end
                                        , dst_subimage_view.row_begin( row )
                                        );
                } //for
           } // for
       } // for
   }

   template< typename Buffer
           , typename View
           >
   void read_stripped_data( const View& dst_view
                          , int         plane     )
   {
      using is_view_bit_aligned_t = typename is_bit_aligned<typename View::value_type>::type;

      //using row_buffer_helper_t =detail::row_buffer_helper_view<View>;
      using row_buffer_helper_t = Buffer;
      using it_t = typename row_buffer_helper_t::iterator_t;

      std::size_t size_to_allocate = buffer_size< typename View::value_type >( dst_view.width()
                                                                             , is_view_bit_aligned_t() );
      row_buffer_helper_t row_buffer_helper( size_to_allocate, true );

      it_t begin = row_buffer_helper.begin();

      it_t first = begin + this->_settings._top_left.x;
      it_t last  = first + this->_settings._dim.x; // one after last element

      // I don't think tiff allows for random access of row, that's why we need
      // to read and discard rows when reading subimages.
      skip_over_rows( row_buffer_helper.buffer()
                    , plane
                    );

      std::ptrdiff_t row     = this->_settings._top_left.y;
      std::ptrdiff_t row_end = row + this->_settings._dim.y;
      std::ptrdiff_t dst_row = 0;

      for(
         ; row < row_end
         ; ++row, ++dst_row
         )
      {
         this->_io_dev.read_scanline( row_buffer_helper.buffer()
                              , row
                              , static_cast< tsample_t >( plane )
                              );

         this->_cc_policy.read( first
                              , last
                              , dst_view.row_begin( dst_row ));
      }
   }

    template< typename Pixel >
    std::size_t buffer_size( std::size_t width
                           , std::false_type // is_bit_aligned
                           )
    {
        std::size_t scanline_size_in_bytes = this->_io_dev.get_scanline_size();

        std::size_t element_size = sizeof( Pixel );

        std::size_t ret = std::max( width
                                  , (( scanline_size_in_bytes + element_size - 1 ) / element_size )
                                  );

        return ret;
    }

    template< typename Pixel >
    std::size_t buffer_size( std::size_t /* width */
                            , std::true_type  // is_bit_aligned
                            )
    {
        return this->_io_dev.get_scanline_size();
    }

private:

   template < int K > friend struct plane_recursion;
};

namespace detail {

struct tiff_type_format_checker
{
    tiff_type_format_checker( const image_read_info< tiff_tag >& info )
    : _info( info )
    {}

    template< typename Image >
    bool apply()
    {
        using view_t = typename Image::view_t;

        return is_allowed< view_t >( _info
                                   , std::true_type()
                                   );
    }

private:
    tiff_type_format_checker& operator=( const tiff_type_format_checker& ) { return *this; }

private:

    const image_read_info< tiff_tag > _info;
};

struct tiff_read_is_supported
{
    template< typename View >
    struct apply : public is_read_supported< typename get_pixel_type< View >::type
                                           , tiff_tag
                                           >
    {};
};

} // namespace detail


///
/// Tiff Dynamic Image Reader
///
template< typename Device >
class dynamic_image_reader< Device
                          , tiff_tag
                          >
    : public reader< Device
                   , tiff_tag
                   , detail::read_and_no_convert
                   >
{
    using parent_t = reader<Device, tiff_tag, detail::read_and_no_convert>;

public:

    dynamic_image_reader( const Device&                          io_dev
                        , const image_read_settings< tiff_tag >& settings
                        )
    : parent_t( io_dev
              , settings
              )
    {}

    template< typename ...Images >
    void apply( any_image< Images... >& images )
    {
        detail::tiff_type_format_checker format_checker( this->_info );

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

            detail::dynamic_io_fnobj< detail::tiff_read_is_supported
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
+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
*/