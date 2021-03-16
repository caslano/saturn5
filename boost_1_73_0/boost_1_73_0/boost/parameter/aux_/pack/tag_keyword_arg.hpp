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
oNXHoLw+0FGKQdExRAfdBtsC7QcrYCf7GlT5MtHi03W64hiD3hijmedxfZlPVH8+Uf6RWEcUgd8eGi07jqjLLMTIqTodd4xGWc8SrXwUkXCTTgsP0Skfun/kNqIFhcC9CX2lYUwPapQGe7kYsrzxPcgNtj76YaI7X9ZpYK1OGXM1+vN5jU54B+tV+NG73xJ9BPu7Dzb129c63XcsfAJ9tXsaY52l0b3Q86N3Q/+bNPoQNvU7ePl9X+gtQHTE4UQ=
*/