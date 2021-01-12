/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_CATEGORY_OF_IMPL_04202013_0940)
#define BOOST_FUSION_CATEGORY_OF_IMPL_04202013_0940

namespace boost { namespace fusion
{
    struct std_tuple_tag;
    struct random_access_traversal_tag;

    namespace extension
    {
        template<typename T>
        struct category_of_impl;

        template<>
        struct category_of_impl<std_tuple_tag>
        {
            template<typename T>
            struct apply
            {
                typedef random_access_traversal_tag type;
            };
        };
    }
}}

#endif

/* category_of_impl.hpp
PHpWhp7ZsQH2RWiD5e+WWNpFeCtsAFfBbvBO2BfeBZ+Ea+A2eB98Bd4PP4EPwM9gyzjyC9yI2meTz2AN+BisA5+CjeHT8GK4BXaAz8Au8FnYEz4Hh8Bt8Ar4PJyh9vPgDrgFv++Eb8CXoO1lXO30t+GrqJvC12EXuAb2UrXfx3ebsAb8ALaAe2FP+BHsDffDdPgJzIUHYBE8BG+Aznv+CL9C/RD8Gm6DR+BueBTuVfOfwGPw
*/