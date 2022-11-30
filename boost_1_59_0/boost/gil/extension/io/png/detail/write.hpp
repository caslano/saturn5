//
// Copyright 2007-2012 Christian Henning, Andreas Pokorny, Lubomir Bourdev
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_EXTENSION_IO_PNG_DETAIL_WRITE_HPP
#define BOOST_GIL_EXTENSION_IO_PNG_DETAIL_WRITE_HPP

#include <boost/gil/extension/io/png/detail/writer_backend.hpp>

#include <boost/gil/io/device.hpp>
#include <boost/gil/io/dynamic_io_new.hpp>
#include <boost/gil/io/row_buffer_helper.hpp>
#include <boost/gil/detail/mp11.hpp>

#include <type_traits>

namespace boost { namespace gil {

#if BOOST_WORKAROUND(BOOST_MSVC, >= 1400)
#pragma warning(push)
#pragma warning(disable:4512) //assignment operator could not be generated
#endif

namespace detail {

struct png_write_is_supported
{
    template< typename View >
    struct apply
        : public is_write_supported< typename get_pixel_type< View >::type
                                   , png_tag
                                   >
    {};
};

} // namespace detail

///
/// PNG Writer
///
template< typename Device >
class writer< Device
            , png_tag
            >
    : public writer_backend< Device
                           , png_tag
                           >
{

public:

    using backend_t = writer_backend<Device, png_tag>;

    writer( const Device&                      io_dev
          , const image_write_info< png_tag >& info
          )
    : backend_t( io_dev
               , info
               )
    {}


    template< typename View >
    void apply( const View& view )
    {
        io_error_if( view.width() == 0 && view.height() == 0
                   , "png format cannot handle empty views."
                   );

        this->write_header( view );

        write_view( view
                  , typename is_bit_aligned< typename View::value_type >::type()
                  );
    }

private:

    template<typename View>
    void write_view( const View& view
                   ,  std::false_type       // is bit aligned
                   )
    {
        using pixel_t = typename get_pixel_type<View>::type;

        using png_rw_info = detail::png_write_support
            <
                typename channel_type<pixel_t>::type,
                typename color_space_type<pixel_t>::type
            >;

        if( little_endian() )
        {
            set_swap< png_rw_info >();
        }

        std::vector< pixel< typename channel_type< View >::type
                          , layout<typename color_space_type< View >::type >
                          >
                   > row_buffer( view.width() );

        for( int y = 0; y != view.height(); ++ y)
        {
            std::copy( view.row_begin( y )
                     , view.row_end  ( y )
                     , row_buffer.begin()
                     );

            png_write_row( this->get_struct()
                         , reinterpret_cast< png_bytep >( row_buffer.data() )
                         );
        }

        png_write_end( this->get_struct()
                     , this->get_info()
                     );
    }

    template<typename View>
    void write_view( const View& view
                   , std::true_type         // is bit aligned
                   )
    {
        using png_rw_info = detail::png_write_support
            <
                typename kth_semantic_element_type<typename View::value_type, 0>::type,
                typename color_space_type<View>::type
            >;

        if (little_endian() )
        {
            set_swap< png_rw_info >();
        }

        detail::row_buffer_helper_view< View > row_buffer( view.width()
                                                         , false
                                                         );

        for( int y = 0; y != view.height(); ++y )
        {
            std::copy( view.row_begin( y )
                     , view.row_end  ( y )
                     , row_buffer.begin()
                     );

            png_write_row( this->get_struct()
                         , reinterpret_cast< png_bytep >( row_buffer.data() )
                         );
        }

        png_free_data( this->get_struct()
                     , this->get_info()
                     , PNG_FREE_UNKN
                     , -1
                     );

        png_write_end( this->get_struct()
                     , this->get_info()
                     );
    }

    template<typename Info>
    struct is_less_than_eight : mp11::mp_less
        <
            std::integral_constant<int, Info::_bit_depth>,
            std::integral_constant<int, 8>
        >
    {};

    template<typename Info>
    struct is_equal_to_sixteen : mp11::mp_less
        <
            std::integral_constant<int, Info::_bit_depth>,
            std::integral_constant<int, 16>
        >
    {};

    template <typename Info>
    void set_swap(typename std::enable_if<is_less_than_eight<Info>::value>::type* /*ptr*/ = 0)
    {
        png_set_packswap(this->get_struct());
    }

    template <typename Info>
    void set_swap(typename std::enable_if<is_equal_to_sixteen<Info>::value>::type* /*ptr*/ = 0)
    {
        png_set_swap(this->get_struct());
    }

    template <typename Info>
    void set_swap(
        typename std::enable_if
        <
            mp11::mp_and
            <
                mp11::mp_not<is_less_than_eight<Info>>,
                mp11::mp_not<is_equal_to_sixteen<Info>>
            >::value
        >::type* /*ptr*/ = nullptr)
    {
    }
};

///
/// PNG Dynamic Image Writer
///
template< typename Device >
class dynamic_image_writer< Device
                          , png_tag
                          >
    : public writer< Device
                   , png_tag
                   >
{
    using parent_t = writer<Device, png_tag>;

public:

    dynamic_image_writer( const Device&                      io_dev
                        , const image_write_info< png_tag >& info
)
    : parent_t( io_dev
              , info
              )
    {}

    template< typename ...Views >
    void apply( const any_image_view< Views... >& views )
    {
        detail::dynamic_io_fnobj< detail::png_write_is_supported
                                , parent_t
                                > op( this );

        apply_operation( views, op );
    }
};

#if BOOST_WORKAROUND(BOOST_MSVC, >= 1400)
#pragma warning(pop)
#endif

} // namespace gil
} // namespace boost

#endif

/* write.hpp
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
*/