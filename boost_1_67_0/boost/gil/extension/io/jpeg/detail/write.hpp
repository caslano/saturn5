//
// Copyright 2007-2008 Christian Henning, Andreas Pokorny, Lubomir Bourdev
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_EXTENSION_IO_JPEG_DETAIL_WRITE_HPP
#define BOOST_GIL_EXTENSION_IO_JPEG_DETAIL_WRITE_HPP

#include <boost/gil/extension/io/jpeg/tags.hpp>
#include <boost/gil/extension/io/jpeg/detail/supported_types.hpp>
#include <boost/gil/extension/io/jpeg/detail/writer_backend.hpp>

#include <boost/gil/io/base.hpp>
#include <boost/gil/io/device.hpp>
#include <boost/gil/io/dynamic_io_new.hpp>

#include <vector>

namespace boost { namespace gil {

#if BOOST_WORKAROUND(BOOST_MSVC, >= 1400)
#pragma warning(push)
#pragma warning(disable:4512) //assignment operator could not be generated
#pragma warning(disable:4611) //interaction between '_setjmp' and C++ object destruction is non-portable
#endif

namespace detail {

struct jpeg_write_is_supported
{
    template< typename View >
    struct apply
        : public is_write_supported< typename get_pixel_type< View >::type
                                   , jpeg_tag
                                   >
    {};
};

} // detail

///
/// JPEG Writer
///
template< typename Device >
class writer< Device
            , jpeg_tag
            >
    : public writer_backend< Device
                           , jpeg_tag
                           >
{
public:

    using backend_t = writer_backend<Device, jpeg_tag>;

public:

    writer( const Device&                       io_dev
          , const image_write_info< jpeg_tag >& info
          )
    : backend_t( io_dev
               , info
               )
    {}

    template<typename View>
    void apply( const View& view )
    {
        write_rows( view );
    }

private:

    template<typename View>
    void write_rows( const View& view )
    {
        std::vector< pixel< typename channel_type< View >::type
                          , layout<typename color_space_type< View >::type >
                          >
                   > row_buffer( view.width() );

        // In case of an error we'll jump back to here and fire an exception.
        // @todo Is the buffer above cleaned up when the exception is thrown?
        //       The strategy right now is to allocate necessary memory before
        //       the setjmp.
        if( setjmp( this->_mark )) { this->raise_error(); }

        using channel_t = typename channel_type<typename View::value_type>::type;

        this->get()->image_width      = JDIMENSION( view.width()  );
        this->get()->image_height     = JDIMENSION( view.height() );
        this->get()->input_components = num_channels<View>::value;
        this->get()->in_color_space   = detail::jpeg_write_support< channel_t
                                                                  , typename color_space_type< View >::type
                                                                  >::_color_space;

        jpeg_set_defaults( this->get() );

        jpeg_set_quality( this->get()
                        , this->_info._quality
                        , TRUE
                        );

        // Needs to be done after jpeg_set_defaults() since it's overridding this value back to slow.
        this->get()->dct_method = this->_info._dct_method;


        // set the pixel dimensions
        this->get()->density_unit = this->_info._density_unit;
        this->get()->X_density    = this->_info._x_density;
        this->get()->Y_density    = this->_info._y_density;

        // done reading header information

        jpeg_start_compress( this->get()
                           , TRUE
                           );

        JSAMPLE* row_addr = reinterpret_cast< JSAMPLE* >( &row_buffer[0] );

        for( int y =0; y != view.height(); ++ y )
        {
            std::copy( view.row_begin( y )
                     , view.row_end  ( y )
                     , row_buffer.begin()
                     );

            jpeg_write_scanlines( this->get()
                                , &row_addr
                                , 1
                                );
        }

        jpeg_finish_compress ( this->get() );
    }
};

///
/// JPEG Dyamic Image Writer
///
template< typename Device >
class dynamic_image_writer< Device
                          , jpeg_tag
                          >
    : public writer< Device
                   , jpeg_tag
                   >
{
    using parent_t = writer<Device, jpeg_tag>;

public:

    dynamic_image_writer( const Device&                       io_dev
                        , const image_write_info< jpeg_tag >& info
                        )
    : parent_t( io_dev
              , info
              )
    {}

    template< typename Views >
    void apply( const any_image_view< Views >& views )
    {
        detail::dynamic_io_fnobj< detail::jpeg_write_is_supported
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