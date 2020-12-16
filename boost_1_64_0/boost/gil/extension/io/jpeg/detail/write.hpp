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
+Hq17mu2OpKK7zKerYYSmcToEBK7cq6BLm0UulT7X5TzMTxODaVS3MckdibYH5HZ2U4O8jzKKYxit2EwOZwUfVJkU4TxYaC5savNhIfN3gzp6qYgXd1mZ1zj6yjhjKebx5anm0xJyGpi6qSLx5Auen4kjm7y2/bnHaOb/FvD8TGMdc/QfLvVvf2ddyj9Bf0AvArnWMJTcYH6+07S2xj934z/Wypc/T1a6W8cYRaG0FvgSb0F//RuuwiHpJ8XgoWdQiE55OLYPSgnNYgw6/5BzqC7Ly3SLHTMzMp9qJb2dV35Cfgg2eV5aZaLOGgww1dbOL1zTnQ6Lcyj8Azz0u2MJIfQ/JAnw9Y72YShOogrD4Azj/AvXMCe9DYJ2wRcevnVCsbo4wy04S2iDW9+BfWRfBrYvWln7Fki78XXqr34NWR/NyT4CsmzQOMWg82tA+ClziomScO0p+Em/x2trU1+n4gjCBu8JOGtK5HvRhyi2JPaWHukvy3a1YeTe8o6KIr3X44nuqO+sxKYf8j7Ea6tJoen8TmjI/wbmKVxMbyvOsPU9ybW0XnsNlkHL7Mcp/vuxXT57oZUqvM99zyxbSQ+OppIASZsNTBepISdBl0TMbT4/sgAbmJIe4wjErt2uLq2ks7s0gHlKVEUWYpg2+ZJpLf3AlmX4N9J2DnnAJf3cHAHl8MrKsm3heXbbmWiB2nz9Q05G0d2dRSuNeFFHEZZya6OwmETXsxhyJTs6ii80CG7Ogo3m/CyYni5Q3Z1FF5twsuL4U6H7Ooo3OeQXR2FN9nwIg5vtuEWDo/Y8GIOZ2x4CYd3OkW7ukKTkRVt+5Jo2P6mBnHSfrPG2msOyjDsNYdkGPaaW2T4amm/ifB1iJfhmxCfFOFbQU+G75T2mwjfJ+03a1x7zWaB/7C036xx7TVbRPgJab9Z49prLhHh58l+8xjo7Hzo/Hah805F7Ige+BPq7cbTyN0R7yRRdYfjokCbQTuwPbwytK0/xmK/a9tNBcF3izY0rNZcJzX573OejLAXdxzF4b+NO5X67T1N4o4qnY9qf1enE+4Zaiw40PHn9y7Ee741Ksmu4ewmYe/IuPBzLXy1zKdv1mz/mex5gv9vqbuqFxBPFxJPRIv9Xz9E+Dgzt7QuJvy9TX7f2/MNPn3ANfnwe3G7SGY4F7e96SVE41KiYcp34Qw3rUN912UcLuUHqbOrB65Le3A0GrMKIcLUT16mynR5k8un9s97BfHzftKDlbwvURg1L0AkzT0IPm9kCPpP72xIYKG+eoRPrQ/YdUBuMJuPuQeruDqM/bFCxvzP09R/HAQz37+Z+WmNwojCWOnxOXYFYOZE3wJ5fQJY/4Y+6QOsysCikfW9A5F+QM09VDo7AHz9hm5YagDkpg8ZWE9vf6Snn/3QznNhA5Zub3TAey9/tc2/t+0IymePCXe3YrTqc4wv3H1IDldBDjBvQ6T1N+uWWwBMOddIuxZ7n7I4p6iy4RYO19jwYseza6q14SXOArJZudo/Pq/d0EU2X+ZXCRtHrqkduNZrngbaDs9aqeTgLpuyRBxoYW1idekjnKdYm6BM02Gd8dEm9wWX5NZC1k3v3ompAK8fE+kqXiYPrL+gMGztps6pHNduc8UKNjs0q503FsgWUQFXl0hu9zIr/j/vMJn14MchK11WygtxL+9+06txS+A6ry7/g/tNl1jdPKc8+9ux9aghObJgVcDVk6hqc5+c65rt5owcrx8jxxzLEXH4yxl9RChc80mEq8ovx6T1EXKze4WL6zyZTSq//4rcGqRPOYwnhZy7vm6htn+j3EOdYEzrGa/PGo3jDvuOwB5Dx+p+66Zx+q3PBPRbPcT7Z2W/9R8=
*/