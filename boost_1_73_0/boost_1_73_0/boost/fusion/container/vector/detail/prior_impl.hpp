/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_PRIOR_IMPL_05042005_1145)
#define FUSION_PRIOR_IMPL_05042005_1145

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
        struct prior_impl;

        template <>
        struct prior_impl<vector_iterator_tag>
        {
            template <typename Iterator>
            struct apply
            {
                typedef typename Iterator::vector vector;
                typedef typename Iterator::index index;
                typedef vector_iterator<vector, index::value-1> type;

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

/* prior_impl.hpp
vdjMnhVdu1+3qKxmCzmKJhFHeZjvGrQjKNs60IUzWuCuxiEweAw6WGgarZiBM86cYlyGAFrx8fKsIeT1kbhJJ3vD2VKq8BMlSYG4rDZsKG1PQIk3kuQ8hHcMjN7wBtzxW/LhTcJoxiyLPbeijzER93hi2Z44oASHAXQPaVrhbXhvp6/F70d5Rlx8rhbOiAZrvjBTdxim+FkcFumRiIJwBv6f3y8iwAZYxxbwRmD4hw1mkkeiZ6RghBeHswCMtgRZ2MyS75OlVn7SZUzyK54OCXxGHhszsWXLKKdgnUUa3UQzeS3HbicAtLTpPuhMCIjoT5Jj2jfeQEQwIANAENSNbgllbsJZNHbQAfbM7Qpn5m1qU1zyURXNUXYPczm7dwe3hrjSkcaPvzmHPP4o3dsiRw2FYpKDGyT8gpyBH4JozGxzpQDFp5k5KPljve5uHunVnbPnII10e4PgrHfVPT1yOgTMcrm6+6ra+9OEYDKBbRfDEKRakruAO+HeoUKp6VAQIRYMk0gHxl57gqQR7+SGAdhd2HmW7WzRcg2frwBqpztoX561TtAK3Tlvn7pNvzl/GwW1BITWGcGhf3WBwljbgwUstg8iL/AyssDBgjGoiqVMjZlGCgjnEZABmn9MZJm3dG/eV10zYEA28ZPe
*/