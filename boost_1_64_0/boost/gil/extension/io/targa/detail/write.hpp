//
// Copyright 2010-2012 Kenneth Riddile, Christian Henning
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_EXTENSION_IO_TARGA_DETAIL_WRITE_HPP
#define BOOST_GIL_EXTENSION_IO_TARGA_DETAIL_WRITE_HPP

#include <boost/gil/extension/io/targa/tags.hpp>
#include <boost/gil/extension/io/targa/detail/writer_backend.hpp>

#include <boost/gil/io/base.hpp>
#include <boost/gil/io/device.hpp>
#include <boost/gil/io/dynamic_io_new.hpp>

#include <vector>

namespace boost { namespace gil {

#if BOOST_WORKAROUND(BOOST_MSVC, >= 1400)
#pragma warning(push)
#pragma warning(disable:4512) //assignment operator could not be generated
#endif

namespace detail {

template < int N > struct get_targa_view_type {};
template <> struct get_targa_view_type< 3 > { using type = bgr8_view_t; };
template <> struct get_targa_view_type< 4 > { using type = bgra8_view_t; };

struct targa_write_is_supported
{
    template< typename View >
    struct apply
        : public is_write_supported< typename get_pixel_type< View >::type
                                   , targa_tag
                                   >
    {};
};

} // detail

///
/// TARGA Writer
///
template< typename Device >
class writer< Device
            , targa_tag
            >
    : public writer_backend< Device
                           , targa_tag
                           >
{
private:
    using backend_t = writer_backend<Device, targa_tag>;

public:

    writer( const Device&                        io_dev
          , const image_write_info< targa_tag >& info
          )
    : backend_t( io_dev
               , info
               )
    {}

    template<typename View>
    void apply( const View& view )
    {
        write( view );
    }

private:

    template< typename View >
    void write( const View& view )
    {
        uint8_t bit_depth = static_cast<uint8_t>( num_channels<View>::value * 8 );

        // write the TGA header
        this->_io_dev.write_uint8( 0 ); // offset
        this->_io_dev.write_uint8( targa_color_map_type::_rgb );
        this->_io_dev.write_uint8( targa_image_type::_rgb );
        this->_io_dev.write_uint16( 0 ); // color map start
        this->_io_dev.write_uint16( 0 ); // color map length
        this->_io_dev.write_uint8( 0 ); // color map depth
        this->_io_dev.write_uint16( 0 ); // x origin
        this->_io_dev.write_uint16( 0 ); // y origin
        this->_io_dev.write_uint16( static_cast<uint16_t>( view.width() ) ); // width in pixels
        this->_io_dev.write_uint16( static_cast<uint16_t>( view.height() ) ); // height in pixels
        this->_io_dev.write_uint8( bit_depth );

        if( 32 == bit_depth )
        {
            this->_io_dev.write_uint8( 8 ); // 8-bit alpha channel descriptor
        }
        else
        {
            this->_io_dev.write_uint8( 0 );
        }

        write_image< View
                   , typename detail::get_targa_view_type< num_channels< View >::value >::type
                   >( view );
    }


    template< typename View
            , typename TGA_View
            >
    void write_image( const View& view )
    {
        size_t row_size = view.width() * num_channels<View>::value;
        byte_vector_t buffer( row_size );
        std::fill( buffer.begin(), buffer.end(), 0 );


        TGA_View row = interleaved_view( view.width()
                                       , 1
                                       , reinterpret_cast<typename TGA_View::value_type*>( &buffer.front() )
                                       , row_size
                                       );

        for( typename View::y_coord_t y = view.height() - 1; y > -1; --y )
        {
            copy_pixels( subimage_view( view
                                      , 0
                                      , static_cast<int>( y )
                                      , static_cast<int>( view.width() )
                                      , 1
                                      )
                       , row
                       );

            this->_io_dev.write( &buffer.front(), row_size );
        }

    }
};

///
/// TARGA Dynamic Image Writer
///
template< typename Device >
class dynamic_image_writer< Device
                          , targa_tag
                          >
    : public writer< Device
                   , targa_tag
                   >
{
    using parent_t = writer<Device, targa_tag>;

public:

    dynamic_image_writer( const Device&                        io_dev
                        , const image_write_info< targa_tag >& info
                        )
    : parent_t( io_dev
              , info
              )
    {}

    template< typename Views >
    void apply( const any_image_view< Views >& views )
    {
        detail::dynamic_io_fnobj< detail::targa_write_is_supported
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
V9DYsGiHotjg3USE8orZoJYWoMH7qhk3f/t5qcQde1L6NVfHE27LxkNk095dy3PaCS99heCdwzw4Odo4ke2pWz2NozJHK6N1SNpt6ua97LnNrX5NC0YO4VLfPp0ubKvZjV6iGI4Jnb6JloBoiddxPBuQf6hPPCtOyOm27B4C8ZMR6J5WZseGawz//xesmvcB/L8XYrxnMT1lwzxsEKMn87cTk+n+6yEZDySZBcZLexOS2b1X4QVkbRBRkznwhrrpmeiYFs8O/h6yisOb0jxZimlpDb4z5H0IbdD81IWJ+k7c8az0ze7DB8jw/eML+EoYPjGOodzfhNfj8jUWrxHWdZa99Lozdxc6q/t8pcT/W4EzXSyGZUHb3kk8KptKsg8flxHBp56h3K+rdPbQBmM7ULGQhC4/AfpBZyV0KydBCytN4CAj+vC49OHaPcNzx0fHQxWndCa2Cq54hPxEX6/i76PgAySTyIcDeH4YuNeE0GZIH/F3JmpECtSO/w8YBATwlxncO58mpljA04LeuPWZz1/5Rr3gRnaTw1vOZezY8PZ6Pi1Ssebaz6zYrWeIAF55z+81esVgIoJWIrPOddK933NvT+nr99SnpcB/rfs9/iVdDeCHVW8Fimg2B4ZXJYazwCAujJNjvJ7OmKgmBnoTuGhbK4zujUhlLvjCi4qLP+oxzfEMk6qvQ54QT4EoNWsVfMSOEjRrFcBvOS7BD0yQpX5dSUoR7KHmHgc8HWK9dIDpizxO9x/Gye7Vs0OPXdY02auMp7lXr6LW17LWNOpV69+q1Qm11EH9wX8Kit4V4LnV79KZ8m/WrgUuyiqLD29EcfCBkpqgaVpa0mIuiCaTMzoYJPmk8oH5iE1dqZi0UsOAFvwkqXSjXSt6aw+j1EJLxRdgmpCmUppp2+N+TT7KQgx19n/O+b6ZwW2fv/Xn5bvfueeee79zz32de+6ZxZJ9K2U/evdvZP/hrMfD09BMGhieyGbVbzRy2iXnW5TzReR023lR75nt+02jv1zipusimC99JRLvArKtcqzY+q4FkFp7PYDMa1n2rPmDV+HZDxQaGpjCC0yhRiX8VkWHo6Jq+N3cJFH8eXTPislHliG/ujjrN3JFnqUqsiKQLUE6k/beAf3kJzDsozEPK64YzdGwVeQMKjnNkYek1RbCO4pYOce+RqyMY+WIlbKwYF+PeBFDXzbviKIvLNActaQlzeEuhkg2gFmaQ+GRqTn24pGB3NnUb5yIVFEkBZEyiiQiYmG3c7yFwFsid7DiRetVVgde1hT1wHJ78Vh8+POHmXF7t0O3s6hS/TpTtl7aYXXbPbIaabzAe+sY2t2pTrMEuB0Nhx1CbgetRjtc7ID6ssIdQbXVFlVq4yucGqtMwcB4ZlorYRo+lkQb3GLeMYNMlnkc671c+9rLtXLmmo9XpV5eMduKVzDL0BjENWmJ2jTyj/Z/45r62CosO9UMlg0Hy+YcYpY9s41uIBHTds0Qpm0KYJuPPwiLtjT78e3YDAEuvcjAHLbduo65coaqjU+rYo3Rvn/Cpv+GPRUmewDJE4YRe0zWkFgze7CE+79wyN2aOLQgY/FUcOfWg7KmrDK589p0f+403y2ue7yc2YlkMf6N7CBZg7/EgHHv9JZ9US88Dc5N3wwO0ObQpn1Jmo/Hk0EUSwjozEx9y3/OUh8/Sf5StY5fgsn/G2uBxEzJQaQvRbLB7P8Lb5dHiPTlnIf02cCkUweYSV23gr+OSpV6lz93nzW6583n/WTvLqDwahMCKT+RZF3WgP4LNoK7rKrrISiP/wwi+YsqsB0izSuO+NajqBVf8Ol6Ja3/Ubg6NI2HzJmIY04Wa6PWKhskEnZXF6Y=
*/