//
// Copyright 2012 Christian Henning, Andreas Pokorny, Lubomir Bourdev
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_EXTENSION_TOOLBOX_METAFUNCTIONS_GET_PIXEL_TYPE_HPP
#define BOOST_GIL_EXTENSION_TOOLBOX_METAFUNCTIONS_GET_PIXEL_TYPE_HPP

#include <boost/gil/extension/toolbox/dynamic_images.hpp>
#include <boost/gil/extension/toolbox/metafunctions/is_bit_aligned.hpp>

#include <boost/gil/detail/mp11.hpp>

namespace boost{ namespace gil {

/// get_pixel_type metafunction
/// \brief Depending on Image this function generates either
///        the pixel type or the reference type in case
///        the image is bit_aligned.
template<typename View>
struct get_pixel_type
{
    using type = mp11::mp_if
        <
            is_bit_aligned<typename View::value_type>,
            typename View::reference,
            typename View::value_type
        >;
};

template<typename Views>
struct get_pixel_type<any_image_view<Views>>
{
    using type = any_image_pixel_t;
};

}} // namespace boost::gil

#endif

/* get_pixel_type.hpp
FYkoNY04szh8vk1dGM9LgthSxprw/noej+ZoGVYbpWcMXqr5p0v+qBO7RSscru6qf2VfpWCzNfPO0MRKfs0+khbapR7J/Xn0QxTOTirOvge57WBLLj1zPsS9XxW1dMzwu2a9HgV+MbeX1P0lgagb8ZDonBzrXnBzKGen+0ZRWgWhlpylEd6coDP7V1kg0v1LClF03TLWPqT2vzpKf6UjF8sSesoSp60sqxeenv+F/KbDLn8jVIF7fq38Hs6wgKRux2rEJ/tK+ME4QWK0OeOmelZv3nX5NzmrymGiA6hCIfn8AfZxu2pBVXLTM4ba4Z/116VsAmfqR9XLuFO2lgsbwhPsd5IxloQd47v8veKD1fx1md6MqCcp2nuTCn1pgEiMJt78XomiijJs8c/cI4RIUvnv9bJSE1GpIFX1LOkgzdSR+V9awAlRblCnqljov5RH16lYuElaLhcUPFcdw6omuw1P4QGvG+ZXc5I/RNfytPgOfn3urlkxvmHenIJ4bw4kpo7gMLlXTAb5qMG4/lvNcMp6zkGpB1r83QJr3SPrTTwbKsONoqaqU3Xn/i4UK1MPJr7V5/Q9Kf+bpOacxoVpFaDAdRB4AwUyhBOC7wKwCgDo9clmflS4+SHCUL7ef9XyZeLX19i9INNh6Wvp6o3x1S0vKpJ2Q9LgcFjwDw4GPq/iSye+nLKI7LuYlve2Wri3Zccj6BbGj4ang8RJrm41RQSboi6iOy/Io2kzpqmZgTIjYf2SfciDp0j0VlvmR9vflLi1tU6Q12Ytp3gGxYvNHXjW5RbMqZaw36J/AtZpK6FdTi5zZ9fjnONO8uc+DW+GcNoi5mPNYQsWC5hqpXmK28Lyxgo+9r39OoYvaqmoogSCC8UDgWwk5nptrQ0f/mrNLdcz06McerJuj44fgi+vkleOcPCnYWyxou2aoODU1/JsDJqujtQizn2t2vTfL3eD1TyUPoLCwMh9vDf/3niu12vlxED7/9eofUBeXVMrlHgNSjzA9FrMZMxWTxlx3yD6p6AcwW4hbi010D+FSMnzNX/cN5bIEhOYAUwALgBQAftg677S/tRH15JvNlj1DZgai5W9Z6QzzNOTJRNb9fYILw0KNcz8QFvDMA0Ner8P28MqlaXouFu2h04kkexBbkjFg4IXSbHFDDOTkYr6v9qxvjo+Bhw2hxGz00nRKfsPlEe4SNjmKku+2gyXVKUcEDQcPl9Tn7wZmcxHUg6PRlzcqOaD9v8YjhPmDIQFRQGslzwLG/WFM2+Xyr8iEjn4aGOMzT6EkXvg6+/8uv87HYEhX3tb3tEuGM/QSkRrBxQchpEm/1tr8O14aqtGijzljSwS9t30pJPu5zqJRlSpUdzJtirrnsAdGgkpWYa1mYsnfLKQ4SBRdb+KX2+fFE26VvMLxdOQjUj7f0DFRrgSxxX+fv934cQwt8lv3ASN7bRib10s0McBlZ5dbx44oenmavwshNgvJS/o0WgbW8bDbMhj9p1Eu0qilaRSHoCYbHhtze76hkhS+9vwQEhEDhgIQ8x45EILjmIzK+NHSbOtjaR5cZ8WMVGKWL8IUJbrARRCmIDGsRjfM5DzG7ip/w2RWImzcUrB82gl/ApGRvVTq9hEC4RqVPpMwcZYkb4wnI3+1jr70sJ2371ArhdtmMHf4Ce/4h6MBH1cz+MgJdMUpOV4LkVIsDba/9ci+9C5TSObBxbpOWuQPtg/JGjdk6kgj600NXzI7mtbMVOaen5vEjbhQyp9CSMVVomZly+wZPz8h5VilHO25siaOH8cx3V9cU1WpowsybStyLnk411wIMtYL/ckFpAn4eU7PH+gK4Xx+tcEPA8AjHGR3OfMnt1Qvkk=
*/