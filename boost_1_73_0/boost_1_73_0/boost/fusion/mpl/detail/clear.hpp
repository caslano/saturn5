/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_CLEAR_10022005_1442)
#define FUSION_CLEAR_10022005_1442

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/vector/vector_fwd.hpp>
#include <boost/fusion/container/list/list_fwd.hpp>
#include <boost/fusion/container/map/map_fwd.hpp>
#include <boost/fusion/container/set/set_fwd.hpp>
#include <boost/fusion/container/deque/deque_fwd.hpp>

namespace boost { namespace fusion
{
    struct cons_tag;
    struct map_tag;
    struct set_tag;
    struct vector_tag;
    struct deque_tag;

    namespace detail
    {
        template <typename Tag>
        struct clear;

        template <>
        struct clear<cons_tag> : mpl::identity<list<> > {};

        template <>
        struct clear<map_tag> : mpl::identity<map<> > {};

        template <>
        struct clear<set_tag> : mpl::identity<set<> > {};

        template <>
        struct clear<vector_tag> : mpl::identity<vector<> > {};

        template <>
        struct clear<deque_tag> : mpl::identity<deque<> > {};
    }
}}

#endif

/* clear.hpp
HawPsZRrNOlFErpcNJWQje8JWYzXuXqflxDFAMCy0S8MWN4gELiOIlUWhpYmGiaFYGjDyA1wkZnOHdDLI6m1wCnZtWBaD2Hn75UGZAQ56DaHHGTcrmcYxFcnsCoEhdC6kzZc6URnQeKI/mkpNPIzJUgNp1d/iDYUHMEKtD3tJFgPk/Tu0Y6kdI/QEl831ZzAf3cAevWgAIZx2ENR5pG8AwanAc6MtiKwFZNbqMT5uTh+ZTw8jbYMjK07TZdCuO1ROwmBhwHVkV5WBgIiVYFvTev7tYO+YjbOosUCVhXm4Zr2CCa6O35LLWzzM/OYDN9z4o0zK19eak+PGP31lA8tFTFN0wQMCuDDLF3RexCZ4NdxPCBioxIIWp26v8hJOgWdUfey2xkHRyIFL8iNYCL5uNM09INVmN8qCwnNaPyokQd40y3EobgeXF72+ow5bvbruT9rr1/fa3AzfqwbvK7v1x0OH+sHrx1sUhuDUeb56eQ1DlmHUo04HhJnA6TVIJhR/8LDJTBrVvhT1KCTWz2CUDtzBa2M68e6VHGqMF2LEiuwGOrdJBaqmWzFKSIgDTZ6zehYRHcY3UfH7UhL1ZMyvXlTNqrWFP5uGbHv2n2PSB3lKNOYQSGUvGK4HuuGAKG+bHkKawcx58q5lu5Z
*/