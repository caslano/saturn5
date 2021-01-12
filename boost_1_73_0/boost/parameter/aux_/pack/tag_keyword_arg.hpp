// Copyright David Abrahams, Daniel Wallin 2003.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PARAMETER_AUX_PACK_TAG_KEYWORD_ARG_HPP
#define BOOST_PARAMETER_AUX_PACK_TAG_KEYWORD_ARG_HPP

#include <boost/parameter/aux_/tag.hpp>
#include <boost/parameter/config.hpp>

namespace boost { namespace parameter { namespace aux {

    struct tag_keyword_arg
    {
        template <typename K, typename T>
        struct apply
        {
            typedef typename ::boost::parameter::aux::tag<K,T>::type type;
        };

#if defined(BOOST_PARAMETER_CAN_USE_MP11)
        template <typename K, typename T>
        using fn = typename ::boost::parameter::aux::tag<K,T>::type;
#endif
    };
}}} // namespace boost::parameter::aux

#endif  // include guard


/* tag_keyword_arg.hpp
/GtSf+Jfl/oT/4bUn/g3pf7EvyX1J36H1J/4t6X+xO/0+dCOpH8WxF0+T/Ny+angncTvFjxO/GeCdxH/ueDdxH/BOC+XXwreQ/xXjPNy+TXjvFx+I/Un/lupP/HfSf2J3yP1J/57qT/xe6X+xP8g9Sd+HyuXIdzrfL9gnZr9kTP07x4QzMR7kDPcq/uQYCbew5x1mXj7BTPxHuGs28T7k2Am3qOcbTTx/iyYifcYZz0m3l8E
*/