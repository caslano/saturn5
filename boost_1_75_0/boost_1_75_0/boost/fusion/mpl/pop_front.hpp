/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_POP_FRONT_10022005_1800)
#define FUSION_POP_FRONT_10022005_1800

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/pop_front.hpp>
#include <boost/fusion/support/tag_of.hpp>
#include <boost/fusion/algorithm/transformation/pop_front.hpp>
#include <boost/fusion/sequence/convert.hpp>

namespace boost { namespace mpl
{
    template <typename Tag>
    struct pop_front_impl;

    template <>
    struct pop_front_impl<fusion::fusion_sequence_tag>
    {
        template <typename Sequence>
        struct apply
        {
            typedef typename
                fusion::result_of::pop_front<Sequence>::type
            result;

            typedef typename
                fusion::result_of::convert<
                    typename fusion::detail::tag_of<Sequence>::type, result>::type
            type;
        };
    };
}}

#endif


/* pop_front.hpp
maP0tdHupxg9kh+CxeTFlG8Wmduvo4VkIXRWR50UGYjqutxGaF8rSAXqqr+RkiLZ9g8ij7qFcXH9rZptYA2fNTALGWxoY+XcY7i1Ha+4nvIyzGkm9jj4JargAP3o8wz3pFmN/BJ74m+N/h/a3gQ+iip5HJ/JZMiQg47KYBCQYAJEghoZ0MSApmEGemBGohCJBxoXyeKNMMOhhGsIMDxaUUFd14MVD1wv3F0loC4ZIiThSsCVY9nVICo9jq4BkSQg9K+qXnfP5ODY/f7/fD5M+nj9XtWrevXq1atXZWG3N28chlYje+3Hepgy32SqNbtF2q2Wq7MmOOVRZidzN3PAeMWH11JddKcoG57Xa3ZAzeTuoZX749sxADxjFEtGAAjJOmXO83St4AbbVLi2fEV1hlfywo3K13AljzBHLGivZt5mHFpfzNIdEXQl38i/Z6M4stq6B0+30PEc6MU6TAhP0WvT+XaE/T03cocbuGNMBXkuwRejUnUfie3KY8jGcsq0y9AdTHkfHTKsky+jTOzwdtyLuAgclSZC6fI9cymVx03E+KNsFE8J5taU6+jbd/m3VxrfXqqVi7ZlfdFICqOfJNbGS+zZQeIvXL8cG2gkznNhShjy7pZvAWD+DZ1WH5yoOIMP/wj/8W8D/P9WWf80Ub0eeF3xyK4foQN8LSBQnj8QUfEbZcaziO5taXQTjJb+FkoDOe0jsfT9emkJ
*/