/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_EQUAL_TO_IMPL_05052005_1215)
#define FUSION_EQUAL_TO_IMPL_05052005_1215

#include <boost/fusion/support/config.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/mpl/equal_to.hpp>
#include <boost/mpl/and.hpp>

namespace boost { namespace fusion
{
    struct vector_iterator_tag;

    namespace extension
    {
        template <typename Tag>
        struct equal_to_impl;

        template <>
        struct equal_to_impl<vector_iterator_tag>
        {
            template <typename I1, typename I2>
            struct apply
                : is_same<
                    typename I1::identity
                  , typename I2::identity
                >
            {
            };
        };
    }
}}

#endif


/* equal_to_impl.hpp
HrLe0R3BPfppTeJz63opK1h/UZqO8YqoQAs2BpWS16Hl9GJ+AQblMdZmDnOHxfvMh+/52vfnGeS+fKSPdrkpU7uiWxsHyvw5Wg8/s2woVIe3jWV2GG9s57XzzZ+5QO0GsJZejAJBegJoq8TZb6DbWUOFDu19tzD8PbLMqzvqk4F49UMTxM8il59AaQZtoQ68zpDXrw5bAI7qwmypsQCnw3N/q9IskUWoua/9Ge7KjQ66FFDzMsvAy0Zoer1bqXaLreCEzVgkyefC2g+HHOOah+5kWKmitmtcQopMNDfJ39IN/yzyvaCBMMBkXcq0+C9mLWXDiQQMGsM58XpRzr4uANR/3zJEGlJjjdGjlN+LCgrYxxeHT3APGN2VcpMjtWn80JDyklYoz70j64fljxAm0a6sjsvQY04wW+6Aw28vwD/FxkJwbwO9PupsCf3xJncpWtSaJssA0h2KJWLSi2ifwVSwWa3k8KAwOjvTzcxkNlykG4UztF/tCEphSNOlJEVhaGSNPBpH1qG540+Z2IT8JFmrFf5DjqEtMNK/NTYglcQFjLAle+arrmGaSQ==
*/