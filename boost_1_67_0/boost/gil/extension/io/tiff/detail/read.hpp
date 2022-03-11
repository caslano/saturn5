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

    template< typename Images >
    void apply( any_image< Images >& images )
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
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
*/