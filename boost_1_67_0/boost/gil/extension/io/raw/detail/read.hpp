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

    template< typename Images >
    void apply( any_image< Images >& images )
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