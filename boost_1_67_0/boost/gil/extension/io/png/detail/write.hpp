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

    template< typename Views >
    void apply( const any_image_view< Views >& views )
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