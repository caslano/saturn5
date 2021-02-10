/*=============================================================================
    Copyright (c) 2009 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_CONTAINER_MAP_DETAIL_VALUE_OF_IMPL_HPP
#define BOOST_FUSION_CONTAINER_MAP_DETAIL_VALUE_OF_IMPL_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/sequence/intrinsic/value_at.hpp>
#include <boost/type_traits/is_const.hpp>

namespace boost { namespace fusion { namespace extension
{
    template <typename>
    struct value_of_impl;

    template <>
    struct value_of_impl<map_iterator_tag>
    {
        template <typename It>
        struct apply
        {
            typedef typename
                result_of::value_at<
                    typename mpl::if_<
                        is_const<typename It::seq_type>
                      , typename It::seq_type::storage_type const
                      , typename It::seq_type::storage_type
                    >::type
                  , typename It::index
                >::type
            type;
        };
    };
}}}

#endif

/* value_of_impl.hpp
c4elShbao6GWR+eOZTTnkGkbe2mSP1tSpEQv3XtZ696KXqPaFek2c+Sw9Krp81i1ze/E1eTMtfTJFOflRYvYmEmpyoCac4Cnt7Z/ruV57T9QSwMECgAAAAgALWdKUhchOTE6DwAA2T4AAB4ACQBjdXJsLW1hc3Rlci9saWIvY29uZmlnLW9zNDAwLmhVVAUAAbZIJGCtW21z2zYS/p5fgUk/xMnYVuIkbtrJdY6WKJsTiVRJyqlvOkNDJGTxQpEsANrRTX/87YKkTEoyQbdV4jcReHaxb9gFVj/EyzRiS3JlGiPTDYZzdxIMHXtsXQaO9+Ht2+DqxQ/wPE5Z15DBm3/u9YK8IdpXoL4CeMFPNWPGs/+yUB4eHQR/kvIfzPodfuqIDMjjlD+D10Q/5U9ypKYEFZXP+HsQ6Aj9jrzhtwHO/D3AX+EdmIYzh1m+4fHdSpKj4Wvy7qefPpETcvb27O0xGdE0ZgnxJEsXjN8dk8+ReuffK/r9+6lgvxwTJglNTisofxULIrKlfKCcEfg9iUOWChYRKkjERMjjBfwRp0SuGFnGCSNDZ3Zj2ZfH5GEVhysE2WQFEausSCKyoveMcBay+L7EyCmXJFvCdACPYiEBsJBxlp4CbUYk42uBGEieJiIj9J7GCV0AISrJ
*/