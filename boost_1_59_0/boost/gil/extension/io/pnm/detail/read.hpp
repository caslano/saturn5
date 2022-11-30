//
// Copyright 2012 Christian Henning
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_EXTENSION_IO_PNM_DETAIL_READ_HPP
#define BOOST_GIL_EXTENSION_IO_PNM_DETAIL_READ_HPP

#include <boost/gil/extension/io/pnm/tags.hpp>
#include <boost/gil/extension/io/pnm/detail/reader_backend.hpp>
#include <boost/gil/extension/io/pnm/detail/is_allowed.hpp>

#include <boost/gil.hpp> // FIXME: Include what you use!
#include <boost/gil/io/base.hpp>
#include <boost/gil/io/bit_operations.hpp>
#include <boost/gil/io/conversion_policies.hpp>
#include <boost/gil/io/device.hpp>
#include <boost/gil/io/dynamic_io_new.hpp>
#include <boost/gil/io/reader_base.hpp>
#include <boost/gil/io/row_buffer_helper.hpp>
#include <boost/gil/io/typedefs.hpp>

#include <type_traits>
#include <vector>

namespace boost { namespace gil {

#if BOOST_WORKAROUND(BOOST_MSVC, >= 1400)
#pragma warning(push)
#pragma warning(disable:4512) //assignment operator could not be generated
#endif

///
/// PNM Reader
///
template< typename Device
        , typename ConversionPolicy
        >
class reader< Device
            , pnm_tag
            , ConversionPolicy
            >
    : public reader_base< pnm_tag
                        , ConversionPolicy
                        >
    , public reader_backend< Device
                           , pnm_tag
                           >
{

private:

    using this_t = reader<Device, pnm_tag, ConversionPolicy>;
    using cc_t = typename ConversionPolicy::color_converter_type;

public:

    using backend_t = reader_backend<Device, pnm_tag>;

    reader( const Device&                         io_dev
          , const image_read_settings< pnm_tag >& settings
          )
    : reader_base< pnm_tag
                 , ConversionPolicy
                 >()
    , backend_t( io_dev
               , settings
               )
    {}

    reader( const Device&                         io_dev
          , const cc_t&                           cc
          , const image_read_settings< pnm_tag >& settings
          )
    : reader_base< pnm_tag
                 , ConversionPolicy
                 >( cc )
    , backend_t( io_dev
               , settings
               )
    {}

    template<typename View>
    void apply( const View& view )
    {
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

        switch( this->_info._type )
        {
            // reading mono text is reading grayscale but with only two values
            case pnm_image_type::mono_asc_t::value:
            case pnm_image_type::gray_asc_t::value:
            {
                this->_scanline_length = this->_info._width;

                read_text_data< gray8_view_t >( view );

                break;
            }

            case pnm_image_type::color_asc_t::value:
            {
                this->_scanline_length = this->_info._width * num_channels< rgb8_view_t >::value;

                read_text_data< rgb8_view_t  >( view );

                break;
            }

            case pnm_image_type::mono_bin_t::value:
            {
                //gray1_image_t
                this->_scanline_length = ( this->_info._width + 7 ) >> 3;

                read_bin_data< gray1_image_t::view_t >( view );

                break;
            }

            case pnm_image_type::gray_bin_t::value:
            {
                // gray8_image_t
                this->_scanline_length = this->_info._width;

                read_bin_data< gray8_view_t >( view );

                break;
            }

            case pnm_image_type::color_bin_t::value:
            {
                // rgb8_image_t
                this->_scanline_length = this->_info._width * num_channels< rgb8_view_t >::value;

                read_bin_data< rgb8_view_t >( view );
                break;
            }
        }
    }

private:

    template< typename View_Src
            , typename View_Dst
            >
    void read_text_data( const View_Dst& dst )
    {
        using y_t = typename View_Dst::y_coord_t;

        byte_vector_t row( this->_scanline_length );

        //Skip scanlines if necessary.
        for( int y = 0; y <  this->_settings._top_left.y; ++y )
        {
            read_text_row< View_Src >( dst, row, y, false );
        }

        for( y_t y = 0; y < dst.height(); ++y )
        {
            read_text_row< View_Src >( dst, row, y, true );
        }
    }

    template< typename View_Src
            , typename View_Dst
            >
    void read_text_row( const View_Dst&              dst
                      , byte_vector_t&               row
                      , typename View_Dst::y_coord_t y
                      , bool                         process
                      )
    {
        View_Src src = interleaved_view( this->_info._width
                                       , 1
                                       , (typename View_Src::value_type*) &row.front()
                                       , this->_scanline_length
                                       );

        for( uint32_t x = 0; x < this->_scanline_length; ++x )
        {
            for( uint32_t k = 0; ; )
            {
                int ch = this->_io_dev.getc_unchecked();

                if( isdigit( ch ))
                {
                    buf[ k++ ] = static_cast< char >( ch );
                }
                else if( k )
                {
                    buf[ k ] = 0;
                    break;
                }
                else if( ch == EOF || !isspace( ch ))
                {
                    return;
                }
            }

            if( process )
            {
                int value = atoi( buf );

                if( this->_info._max_value == 1 )
                {
                    using channel_t = typename channel_type<typename get_pixel_type<View_Dst>::type>::type;

                    // for pnm format 0 is white
                    row[x] = ( value != 0 )
                             ? typename channel_traits< channel_t >::value_type( 0 )
                             : channel_traits< channel_t >::max_value();
                }
                else
                {
                    row[x] = static_cast< byte_t >( value );
                }
            }
        }

        if( process )
        {
            // We are reading a gray1_image like a gray8_image but the two pixel_t
            // aren't compatible. Though, read_and_no_convert::read(...) wont work.
            copy_data< View_Dst
                     , View_Src >( dst
                                 , src
                                 , y
                                 , typename std::is_same< View_Dst
                                                   , gray1_image_t::view_t
                                                   >::type()
                                 );
        }
    }

    template< typename View_Dst
            , typename View_Src
            >
    void copy_data( const View_Dst&              dst
                  , const View_Src&              src
                  , typename View_Dst::y_coord_t y
                  , std::true_type // is gray1_view
                  )
    {
        if(  this->_info._max_value == 1 )
        {
            typename View_Dst::x_iterator it = dst.row_begin( y );

            for( typename View_Dst::x_coord_t x = 0
               ; x < dst.width()
               ; ++x
               )
            {
                it[x] = src[x];
            }
        }
        else
        {
            copy_data(dst, src, y, std::false_type{});
        }
    }

    template< typename View_Dst
            , typename View_Src
            >
    void copy_data( const View_Dst&              view
                  , const View_Src&              src
                  , typename View_Dst::y_coord_t y
                  , std::false_type // is gray1_view
                  )
    {
        typename View_Src::x_iterator beg = src.row_begin( 0 ) + this->_settings._top_left.x;
        typename View_Src::x_iterator end = beg + this->_settings._dim.x;

        this->_cc_policy.read( beg
                             , end
                             , view.row_begin( y )
                             );
    }


    template< typename View_Src
            , typename View_Dst
            >
    void read_bin_data( const View_Dst& view )
    {
        using y_t = typename View_Dst::y_coord_t;
        using is_bit_aligned_t = typename is_bit_aligned<typename View_Src::value_type>::type;

        using rh_t = detail::row_buffer_helper_view<View_Src>;
        rh_t rh( this->_scanline_length, true );

        typename rh_t::iterator_t beg = rh.begin() + this->_settings._top_left.x;
        typename rh_t::iterator_t end = beg + this->_settings._dim.x;

        // For bit_aligned images we need to negate all bytes in the row_buffer
        // to make sure that 0 is black and 255 is white.
        detail::negate_bits
            <
                typename rh_t::buffer_t,
                std::integral_constant<bool, is_bit_aligned_t::value> // TODO: Simplify after MPL removal
            > neg;

        detail::swap_half_bytes
            <
                typename rh_t::buffer_t,
                std::integral_constant<bool, is_bit_aligned_t::value> // TODO: Simplify after MPL removal
            > swhb;

        //Skip scanlines if necessary.
        for( y_t y = 0; y < this->_settings._top_left.y; ++y )
        {
            this->_io_dev.read( reinterpret_cast< byte_t* >( rh.data() )
                        , this->_scanline_length
                        );
        }

        for( y_t y = 0; y < view.height(); ++y )
        {
            this->_io_dev.read( reinterpret_cast< byte_t* >( rh.data() )
                        , this->_scanline_length
                        );

            neg( rh.buffer() );
            swhb( rh.buffer() );

            this->_cc_policy.read( beg
                                 , end
                                 , view.row_begin( y )
                                 );
        }
    }

private:

    char buf[16];

};


namespace detail {

struct pnm_type_format_checker
{
    pnm_type_format_checker( pnm_image_type::type type )
    : _type( type )
    {}

    template< typename Image >
    bool apply()
    {
        using is_supported_t = is_read_supported
            <
                typename get_pixel_type<typename Image::view_t>::type,
                pnm_tag
            >;

        return is_supported_t::_asc_type == _type
            || is_supported_t::_bin_type == _type;
    }

private:

    pnm_image_type::type _type;
};

struct pnm_read_is_supported
{
    template< typename View >
    struct apply : public is_read_supported< typename get_pixel_type< View >::type
                                           , pnm_tag
                                           >
    {};
};

} // namespace detail

///
/// PNM Dynamic Image Reader
///
template< typename Device
        >
class dynamic_image_reader< Device
                          , pnm_tag
                          >
    : public reader< Device
                   , pnm_tag
                   , detail::read_and_no_convert
                   >
{
    using parent_t = reader
        <
            Device,
            pnm_tag,
            detail::read_and_no_convert
        >;

public:

    dynamic_image_reader( const Device&                         io_dev
                        , const image_read_settings< pnm_tag >& settings
                        )
    : parent_t( io_dev
              , settings
              )
    {}

    template< typename ...Images >
    void apply( any_image< Images... >& images )
    {
        detail::pnm_type_format_checker format_checker( this->_info._type );

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

            detail::dynamic_io_fnobj< detail::pnm_read_is_supported
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
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
*/