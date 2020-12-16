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
dZhHWI+EhGh4pb3431zOUIdehd6Vn5Owf7xHu7cxG+/+cekzs68+ZKgm/S6QNZbSqIOmaIna2Pa0eGmN3AsduOxwcYF5unoceVivrv3SEO6sZ70WWcsG5Lz3L/rynJnPXs+rceyfp4v93ALZ58e86C9rLrLmIUdRz2rdVqbIH7O9XeVxVjwRCaXpc/++ZNe49PGL55vkVR8HfZ5HcDFGZI1jJO7EvbgHd2MMflq3B/z8EB7bv25Z39nyWi9rnIs6mH+yO4289nlCLGuu2rG52+RpK/SJhA4dwq/WYKWfk4tkzsGaUtnWg21cMVl+cELCAc/2x8804nefJdszZOurkVzAwj3s957MvjZ5L3t/i72+UeqP+12aNZ9rss3peqzFR9gcu18qHUYKaqMVGqATxiL7mB9MNVbExjzJ6yO4D+Px0zN433P4OTXzWZ5LTggrjpBzlWfMZY88cO7eTP3j54iNfZnr3sGB8zgmJsf+fuA83oGVWWNYy86V5qv0E6fXvIqPIaf8gfeyjUWdPPuA7LK60e+L/8T4lrvGGI3vd9fZWH4pt6v9vgoZOJgMT2VzE9vxQYbaA97hnzSTx6/EN+rKlj7ru1UDnXGlmld5xPl97eV8jiE5yHxuZytnOntIp/tscc7DjeNxefNZnmsC2VLvWnQbn4VNOpgdqmKviH037twt4YC1+2fn6Ji0/TbnZ/22HllzlWWDsta33gFzVcbn8iFmm45IyxxzviTrfbKaevMymN9Q4JaE0KIk/6GI+nO2MqMRPywt/GU9zmabso3/t3U48COHtpcHZGcmyF9mn199Zre1P3/mjAf5xePtLdsjf2tsv6EjvznGWS+a44bOd9LCnxrfhkV8Hfvfs/J5ddIOPqbPxRVzXTOYr5KzBDmU4xs58uCy1vdEPukq/myG/PCGyEHv/2538+rcqLAzmVM/COHaauzLe/zqaSH07vTrvbWhsdRH9v7GO3N4anrk51zfd15z+MyuI2O5OjYyv7loo68Crh9CFwt6lbuP/R/g78v1tU6KfTckxFu8/etbUxyDgSgf+06O7zzW2J35XreyfGwXfDYzhNOSoyFkpqpD3ZPsJXQmPcHvh7In9OHkuc6xC/udDl01MoQ9zhJnVgyhw7Ag/su6Lg+fI5mtv9D9TtMfvbmltPglr/cOoT/+1r0JX+SCEIokeS/Ra21jKCHedd8WVe3FdLF/JfbqWNcdbvx0cl6qzx4Vwo7c9pzKIYwrRXWXeD/oO4dXNIroDxUjrs+hP685jKeDn7l/IdHrbH9r6udBnqs3OueU7wie09jCkZmf2+H9qnLyBf3txtj4cntub8/w93uDv+WK/e7amva2KsbsWsfTgekJHXEeaqIWzkdt1MEFqIsLcRHqIR310QAN0QiNcTGaoCmaoTkuQQu0RCu0Rhu0RTsURSEkoTCKoCCSUQwpKI4SKIlSSEUajkJplEFZHI1jcCzK4TiUx/GogBNQESfiJFTCyTgFlXEqTkMVnI4zUBVn4iycjXNQDYPQGV3QFd3QHT3QE72y1qoP+qIf+mMABuJcVEcNLA/2NbyFt/EO3sUGvIf3sQofYDXWYC3WISNkytOHWImP8DE+wUZswmZ8ii3YGuhN1vcfPscX+BJfYTu+xg7sxDfYhd34Ft/he+zBD9iLfQgJ/iGCKHLgEOTEoTgMuZAbhyMReXAE8iIfjkR+FMCy4HPB9cH1wfXB9cH1wfXBfUHdiL7PBJ9BQRRCEgqjCIoiGcWQguIogZIohVSk4SiURhmUxdEh0/Yci3KBHKE8jkcFnICK4af/b40c4WScgso4FaehCk4P5AhVcSbOwtk4B9VwLqqjBs5DTdTC+ag=
*/