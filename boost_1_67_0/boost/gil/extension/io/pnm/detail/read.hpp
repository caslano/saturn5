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

    template< typename Images >
    void apply( any_image< Images >& images )
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