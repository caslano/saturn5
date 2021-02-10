//
// Copyright 2009 Christian Henning
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_EXTENSION_IO_PNM_DETAIL_IS_ALLOWED_HPP
#define BOOST_GIL_EXTENSION_IO_PNM_DETAIL_IS_ALLOWED_HPP

#include <boost/gil/extension/io/pnm/tags.hpp>

#include <type_traits>

namespace boost { namespace gil { namespace detail {

template< typename View >
bool is_allowed( const image_read_info< pnm_tag >& info
               , std::true_type   // is read_and_no_convert
               )
{
    pnm_image_type::type asc_type = is_read_supported< typename get_pixel_type< View >::type
                                                     , pnm_tag
                                                     >::_asc_type;

    pnm_image_type::type bin_type = is_read_supported< typename get_pixel_type< View >::type
                                                     , pnm_tag
                                                     >::_bin_type;
    if( info._type == pnm_image_type::mono_asc_t::value )
    {
        // ascii mono images are read gray8_image_t
        return (  asc_type == pnm_image_type::gray_asc_t::value );
    }


    return (  asc_type == info._type
           || bin_type == info._type
           );
}

template< typename View >
bool is_allowed( const image_read_info< pnm_tag >& /* info */
               , std::false_type  // is read_and_convert
               )
{
    return true;
}

} // namespace detail
} // namespace gil
} // namespace boost

#endif

/* is_allowed.hpp
mJub8rNKd2mn/W00gPItFsk+evPX4Efl7AWh2WO3Hgy3rMCwJZiq0kSlIhMi2SXKbJ7bpCoOglcVSgB9MQSJBvFG8sUQuGhdbIrWxRZUMyCOUJAioswYeoA03M94YT8G6YEhETdOMienPjz0FtZ2pvdRBrWAJJAxOXQrlTKTB3OYZqISSjWprL+tcKK/nH7S1NLm68zmuYGD+VQxqsbNuvhD9vh8YgCiNwSEO3C2EMkyKMlM8P19P9NHpalEeof8opdqMBghZ5Cgi+Ula7khFjvIimjmbL7ppURoAodQzS8E9yhZselYqh8kBiEOwmXFH+cJ8bKNDrrKZKqfMEp7WEMs1/0LudAGACzQPgrF1JpYC40zvHPKA/PbYdQADZVfIRxVmbQZnQAUE4/4F9v7rHvW2bft66XGzCR+W+Vl6gqUshwa1obwysWuXwr6rkKyUDgdb+CN3LiGqevn1Y4wHVsGmMb6NwKRRICxmQpBermccIX1+4gfPtbTjULvvetvZzCDjm/XOnA++SdYBjbDc9bCWpKLpmEFq/rgsHiV/g+PqkynxIHEfincyhmVFmvzRdVc4/XUme6wUEnB+wlKLnBtRtzjp83ruDdsSqoVBAdItqkyD4IDMOnvWbKeEVlk6wON4WENY8Ny2vLn
*/