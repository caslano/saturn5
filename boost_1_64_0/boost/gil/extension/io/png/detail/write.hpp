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
PFlH8eTxMXKoN9U7Nn8etpnFq5dHg0tyWlSwKJjU3C4zC3jEpaSlJnonpKVkj0tUMsf1To1L3ctatTwfndRanTdrs9SorVT+SE9krfFp41SqZKvWm8yUUyar9bnq+seOTM7KSByfTYIBJUPrHPy+NyV5ZEZcRriP+u76TGaSOjo1blxiZvLoVLoJ01eMu11qHBqELDLMfHJ6GqkB1HgL5OA5Z2UgdhMSR2aPtvIYi2pXw/zRSKMSM1iAs8YM7wTSJ5N6EDoeYz2Rl6aGOpX3p1p5cqoqr2+XJySmJFqJgqwlelMSU0fDEazRqZ+QZRHQ6Lh0vYXSe2rRWZPTE22eih8Z4b8/rHcB7rjErKS0BDtXojcTdRjmPWvZmclTEiP2QHjRvMHskrzhdzImxEV0p6s+Mamqrr6rbiT9xo8k5dFY1be2hjA8Faz08kEDnPI6evmojLRxpFkaF5fKEAkKZjXWk1IyKy6ZfD7p6Qlp4/grAosY/Z14GwZpmVkAPgPgKbrsqK0jMS5rjDcrKTt1rNcGklUvdWz4psRlZtp4UH2r8nToibfDNbsz4MPWig+7wIcZvkBRDnlR4kuDSflWFidyjeaRE4aEpKEwDx6qheK/qPo/FCqKCG3+1PV/tyr9GdNRsydOUOXW3z1curM7z+VWLswY5k1BWV1HPzt5IXsqXdhL1+nau/TpvONROv0k9U4ffTzXO10k+nh91bv91LuXV8tNQrpSr6N/7b7q2GUFTs6S3rZOzsnP91blejzZ1ssFpNGxCrUcc7SzEyepstgYlWsvZDd02vVQZVbLYSo/fn9Np6Kvy0Nl3IPJVJQitVF0UCnYip7nM78wglb7L9oVaDaHutmtBFtby0Vn3U9Wvay+XUbyG6e5k2MdWAatSok8HyNBq5UMUXdLDorR89CVFYW8NM8pmhGKTEwvUnQXPW+bb07Am+cPcNslVsjcyOsHlaq8bYMVngfV2FdxvrsfVeL0MUT1ERu1jzxy8uk9OM/O+0PV+0Nq5jlfyEpkFOlCK9J5cFhM9ZyIp9ow5eYWr20SWoPa8D/NptFwmY0ERaenW3Rqz7cqZ+Rw235kMFee947iC5TmFcoYhb8RGv7IOwq2+nE/CPmrS0LkkWKW2I/23KNX1YzPP0HbFgxGRvwXBYN4e15Wk5CT76l++NmbZ6dCwo9SuYYTdBo8eNxQ9IFD9tx/8Ti+Y4plRHhHJo5Ky0hUelOVpY1VOj1BFcRnkE2YhH2Wsk4eNdlr2S6JmVn0p/w/p1lmxgTVVuktrS4+MSMroh+OcpVbdl5WdqY9bl2tbmziZCtTclLkvXrUXdOnn9FpaC92xIkvN/RvXzTmw6Qn/v5k5wdmbvi1M2UnWzck2KkhT7acjpCcHArmnVxoZ8/PtbKJMWNkKD9WD20UJBvz01D91FVlR6nf74/vbxzx/4/4/0f8/yP+/xH//4j/f8T/P+L/H/H/j/j/R/z/I/7/Ef//iP9/xP//b/r/llbB+Cyw75KAr9uI0cK+pYnvkVQdfoK3n/VOB1WXXr0ut1LdWdFT1WdUry/ylcwoK/QG7JzhZI3v9yfaxmrjuudUwk+1+qyD6/tb9Z1V/YTq9aHyXG8Ax8UHPTjrnlTVJuDzzWKyVf1PqV6nFl7V/1RXfV5poFI1cvpw928vQhtjWpT6/toY01312iKcPnKcNvBccY6/hLsbdTj8FCOKW/OspOTeMjtnPAAj4NJCtSlp6rSxk9J3iF7unV3uK7fW1z16PRPI8/nngMnc8gKulJbONbSzjoeoNs4c5jttbNfSmf+VTnl+OOl9ZAUOnPT+80vLyY7uNAEOB6/R0tNV8CtopsohE1ffLvgVovg=
*/