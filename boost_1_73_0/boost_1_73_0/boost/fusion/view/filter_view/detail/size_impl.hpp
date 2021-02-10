/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_SIZE_IMPL_09232005_1058)
#define FUSION_SIZE_IMPL_09232005_1058

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/distance.hpp>
#include <boost/fusion/sequence/intrinsic/begin.hpp>
#include <boost/fusion/sequence/intrinsic/end.hpp>

namespace boost { namespace fusion
{
    struct filter_view_tag;

    namespace extension
    {
        template <typename Tag>
        struct size_impl;

        template <>
        struct size_impl<filter_view_tag>
        {
            template <typename Sequence>
            struct apply
                : result_of::distance<
                    typename result_of::begin<Sequence>::type
                  , typename result_of::end<Sequence>::type>
            {};
        };
    }
}}

#endif



/* size_impl.hpp
1/rUxpHEv/NXrF11MTJCxPfhPuA4LgJ2QsXGLmNf7lkqgQToDFqdVorMXfK/3/RzumdnV4sfyVFJCNLO7Ly6p5+/ho62SeI9G1WMpYdJjQQ0REPE0wl+FETyQ8M9xsdRkR9JaH9YPHt9+ufewKpGadgyrU5T5DJs8kMZ+fw3zt0yccK+urlVPPgbjpBMVHoEj1rOZSQAwDibLgn5z+fWcJT8xgDqLdFbzCFxJ4PqbFNmBjDsKTmeBTBAKqZz7sHyfM6ta75yo77htvBzw6AIgnsSPRu+evhBxQEdYXZv352cPEMocERU4du1XGMqAdZO4USeD4yyCycRyMgoQeF6eLCk6E7ywp9dj2bv2bgoaniVqcIoxB865wEwYSdz7GPMDdUX1i6avC6+82k11OPQ5rhP6tvLdfgGTfVUOQYI4KkJI4vP6+LmAGiOXu2+fPXmmTmVlPxEaqzBoMlUa4zuh1gZV8r0BBXZKSSR/Aot/8O8AiZw9AoyZsIDo8rFau09VMTREbIBBcoB7hAOEFUEI0YyC7q2Dw0xQs1kHm6f8bQCPt5WiyG7dbh92Uvv9ZtXf/lrXQyCQ5Pk+dRjMbrVzOOzN0za05sh92i719LaUukKEM9pbLBj5qur5XIun9M6tBBr7mUuTMpmI8cI
*/