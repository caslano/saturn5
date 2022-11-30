//
// Copyright 2012 Olivier Tournaire, Christian Henning
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_EXTENSION_IO_RAW_DETAIL_READ_HPP
#define BOOST_GIL_EXTENSION_IO_RAW_DETAIL_READ_HPP

#include <boost/gil/extension/io/raw/tags.hpp>
#include <boost/gil/extension/io/raw/detail/device.hpp>
#include <boost/gil/extension/io/raw/detail/is_allowed.hpp>
#include <boost/gil/extension/io/raw/detail/reader_backend.hpp>

#include <boost/gil/io/base.hpp>
#include <boost/gil/io/bit_operations.hpp>
#include <boost/gil/io/conversion_policies.hpp>
#include <boost/gil/io/device.hpp>
#include <boost/gil/io/dynamic_io_new.hpp>
#include <boost/gil/io/reader_base.hpp>
#include <boost/gil/io/row_buffer_helper.hpp>
#include <boost/gil/io/typedefs.hpp>

#include <cstdio>
#include <sstream>
#include <type_traits>
#include <vector>

namespace boost { namespace gil {

#if BOOST_WORKAROUND(BOOST_MSVC, >= 1400)
#pragma warning(push)
#pragma warning(disable:4512) //assignment operator could not be generated
#endif

#define BUILD_INTERLEAVED_VIEW(color_layout, bits_per_pixel) \
{ \
    color_layout##bits_per_pixel##_view_t build = boost::gil::interleaved_view(processed_image->width, \
                                                                             processed_image->height, \
                                                                             (color_layout##bits_per_pixel##_pixel_t*)processed_image->data, \
                                                                             processed_image->colors*processed_image->width*processed_image->bits/8); \
    this->_cc_policy.read( build.begin(), build.end(), dst_view.begin() ); \
} \


template< typename Device
        , typename ConversionPolicy
        >
class reader< Device
            , raw_tag
            , ConversionPolicy
            >
    : public reader_base< raw_tag
                        , ConversionPolicy
                        >
    , public reader_backend< Device
                           , raw_tag
                           >
{
private:

    using this_t = reader<Device, raw_tag, ConversionPolicy>;
    using cc_t = typename ConversionPolicy::color_converter_type;

public:

    using backend_t = reader_backend<Device, raw_tag>;

    //
    // Constructor
    //
    reader( const Device&                         io_dev
          , const image_read_settings< raw_tag >& settings
          )
    : backend_t( io_dev
               , settings
               )
    {}

    //
    // Constructor
    //
    reader( const Device&                         io_dev
          , const cc_t&                           cc
          , const image_read_settings< raw_tag >& settings
          )
    : reader_base< raw_tag
                 , ConversionPolicy
                 >( cc )
    , backend_t( io_dev
               , settings
               )
    {}

    template< typename View >
    void apply( const View& dst_view )
    {
        if( this->_info._valid == false )
        {
            io_error( "Image header was not read." );
        }

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

        // TODO: better error handling based on return code
        int return_code = this->_io_dev.unpack();
        io_error_if( return_code != LIBRAW_SUCCESS, "Unable to unpack image" );
        this->_info._unpack_function_name = this->_io_dev.get_unpack_function_name();

        return_code = this->_io_dev.dcraw_process();
        io_error_if( return_code != LIBRAW_SUCCESS, "Unable to emulate dcraw behavior to process image" );

        libraw_processed_image_t* processed_image = this->_io_dev.dcraw_make_mem_image(&return_code);
        io_error_if( return_code != LIBRAW_SUCCESS, "Unable to dcraw_make_mem_image" );

        if(processed_image->colors!=1 && processed_image->colors!=3)
            io_error( "Image is neither gray nor RGB" );

        if(processed_image->bits!=8 && processed_image->bits!=16)
            io_error( "Image is neither 8bit nor 16bit" );

        // TODO Olivier Tournaire
        // Here, we should use a metafunction to reduce code size and avoid a (compile time) macro
        if(processed_image->bits==8)
        {
            if(processed_image->colors==1){ BUILD_INTERLEAVED_VIEW(gray, 8); }
            else                          { BUILD_INTERLEAVED_VIEW(rgb,  8); }
        }
        else if(processed_image->bits==16)
        {
            if(processed_image->colors==1){ BUILD_INTERLEAVED_VIEW(gray, 16); }
            else                          { BUILD_INTERLEAVED_VIEW(rgb,  16); }
        }
    }
};

namespace detail {

struct raw_read_is_supported
{
    template< typename View >
    struct apply : public is_read_supported< typename get_pixel_type< View >::type
                                           , raw_tag
                                           >
    {};
};

struct raw_type_format_checker
{
    raw_type_format_checker( const image_read_info< raw_tag >& info )
    : _info( info )
    {}

    template< typename Image >
    bool apply()
    {
        using view_t = typename Image::view_t;
        return is_allowed<view_t>(_info, std::true_type{});
    }

private:
    ///todo: do we need this here. Should be part of reader_backend
    const image_read_info< raw_tag >& _info;
};

} // namespace detail

///
/// RAW Dynamic Reader
///
template< typename Device >
class dynamic_image_reader< Device
                          , raw_tag
                          >
    : public reader< Device
                   , raw_tag
                   , detail::read_and_no_convert
                   >
{
    using parent_t = reader<Device, raw_tag, detail::read_and_no_convert>;

public:

    dynamic_image_reader( const Device&                         io_dev
                        , const image_read_settings< raw_tag >& settings
                        )
    : parent_t( io_dev
              , settings
              )
    {}

    template< typename ...Images >
    void apply( any_image< Images... >& images )
    {
        detail::raw_type_format_checker format_checker( this->_info );

        if( !construct_matched( images
                               , format_checker
                               ))
        {
            std::ostringstream error_message;
            error_message << "No matching image type between those of the given any_image and that of the file.\n";
            error_message << "Image type must be {gray||rgb}{8||16} unsigned for RAW image files.";
            io_error( error_message.str().c_str() );
        }
        else
        {
            if( !this->_info._valid )
	      this->read_header();
            this->init_image(images, this->_settings);

            detail::dynamic_io_fnobj< detail::raw_read_is_supported
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