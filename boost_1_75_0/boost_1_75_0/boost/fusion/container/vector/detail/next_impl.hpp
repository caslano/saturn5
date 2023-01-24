/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_NEXT_IMPL_05042005_1058)
#define FUSION_NEXT_IMPL_05042005_1058

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/vector/vector_iterator.hpp>

namespace boost { namespace fusion
{
    struct vector_iterator_tag;
    template <typename Vector, int N>
    struct vector_iterator;

    namespace extension
    {
        template <typename Tag>
        struct next_impl;

        template <>
        struct next_impl<vector_iterator_tag>
        {
            template <typename Iterator>
            struct apply
            {
                typedef typename Iterator::vector vector;
                typedef typename Iterator::index index;
                typedef vector_iterator<vector, index::value+1> type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Iterator const& i)
                {
                    return type(i.vec);
                }
            };
        };
    }
}}

#endif

/* next_impl.hpp
tLXO/5tU2uCLctfHpLTBD6607fWDctNAStshIZMrj88k/SYSlbZqXWkjsaJW+c8Uo9KGMF3nkdLWeYZQ2vB1t/lUVVWErs5rGQYBnZSIQtLYkPWDxpaJGptIdn7DAR9pbHkwrUxjUzWNDc/l8pRHd5NilQcaG5vp0w8ITfQq1EThHsNHxdSNjAihhrpAesQs6LVKxymosd0TorHlKf1FxZrGRhacC9fYUFl7P5Uk3D2chOcp1TO5ooZTtHFmiKIWsYJvIJH5ndHrY8utBszWsBc+HVxu3BpCUZvPFTWRElPoyDjjb9wepqiJSKeBIlTSUtAT41t9+y1ZzpkAgv88hatohrT168LT1tcZv9UZvxGhg02QuJyPVNEZRdRywSiqwnhTiKpl4qpW+c2kaiWcS9UibvHaa5z+8+eT/NnvXXpey59XwlN543rQt17Gf1ddj0zBwflKPLGZaP5zJK/nRv48+s75ecUJm8YrbBqvIDZRRGyiiLMJ2zJiE6tC2MQqwSaGRxO5q9e5QL1gEyj2p0Wfk49wf0J7RcdoIyvhS0Fsok5nE6pFZxMNGpuoG30ONtFgZBNrOJuo5Ci4BlEq08/Xvk5nE/s4m1gTxiZWRpHsuZazhwLlsu9VYg9U2a8PGLcHZRMV1J/zhqwQdqgXQV6oaRNXWGgWasK4QzGItIcFd0Cl61nOWRyzHtA5we/cujfB8O57zbqXxN4G
*/