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
7lCdUtoiuQ5R+1friKQfM/JC34QHNi/hBCbRFNJn0kx+1RCqJPkiH1v65eufuULXIHUSNKmm8y7JD8oQPjVb4I2YhH4sxL7kCnQGB54foT/NJiX1Pb5K6geN2NRbJli7ql30dQRtdWStgDPsx2IZiK/Ty4eyTqZMEG9arBPGIK42heJN4gqmmSl930MGhwjUYrBjI+wdo2BQ2iDbEtePw2hdPzw7nq2mA1r9GVgMp/TsYPwKHPdqcqERCUFTKAl2LeqVPrsgTOj1vbxYelvgHr9zfDeOnjJy8pjOVs4KTtKCp+/QinSNPSyIM0NtBKqGIvDD/wyuAFceI+Nuxp3OadoVGFQX7w08/+XdQAPY3z1axx0TNxtgpnV7vuXkAtZ8YV8h7kvOVKOUz7BisHdZcfQWxEty7TwJW+RnGMuNYWgmT0Jf8hfVC1i0753zXAiyFhD/fvIu8ODrTrI6Bt/SQ+vPbS1fc2SXu6pc1zO+w1/m06cbWsB7R2Iom8tLRL1FA2H32j/GERh5+tYPuxXbQAveqoCA4+LXr9+iLQZptkai8VqMIF8EE1fuPA==
*/