// Copyright David Abrahams, Daniel Wallin 2003.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PARAMETER_AUX_PACK_TAG_TEMPLATE_KEYWORD_ARG_HPP
#define BOOST_PARAMETER_AUX_PACK_TAG_TEMPLATE_KEYWORD_ARG_HPP

#include <boost/parameter/template_keyword.hpp>
#include <boost/parameter/config.hpp>

namespace boost { namespace parameter { namespace aux {

    struct tag_template_keyword_arg
    {
        template <typename K, typename T>
        struct apply
        {
            typedef ::boost::parameter::template_keyword<K,T> type;
        };

#if defined(BOOST_PARAMETER_CAN_USE_MP11)
        template <typename K, typename T>
        using fn = ::boost::parameter::template_keyword<K,T>;
#endif
    };
}}} // namespace boost::parameter::aux

#endif  // include guard


/* tag_template_keyword_arg.hpp
yTda+VGXo/yYy1H+kS5H+esF30z9+VNlfSN+lFNP7BjU0yTvtHyD5HHLny55l+VHS95t+TMc/S0/RupP/fkzpf7Ej3X0t2Nez5K80/IOyeOWd0reZXlc8m7Luxz9Le/2eZrbfyPj3P49jHP7b2Kc238z49z+Wxjn9t/KOLf/sxnn9j+OcW7/46X+xE9gnNv/RMa5/U9inNs/wTi3fy/j3P5Jxrn9Uz4vZHCPRNpnKcv6fNab
*/