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
Tn697USpc5uG3VCcHcYC1AdfQ87Eqz+tNkeHas/XL0S+vXK/Lt/0uEId5A/6w+VRSMnDrJWo/WTNeSAdhN4fCF/oTzHwzVlzIfCdmdLeK6CN/fHdzFQe0L+Rx4mO9NIN3Q1mLTXMHlourcIBI1Z0JkaQkbAu0Kd7fkhmxYdvtfBtXk/wjfmaSE5X1HUYqBHt8+lSoE71GrHVgM6UN67ncP8JJ6vU6nOzPcoLH2KUNV8ingYqfhV0DpBOJ+CrU5HOklpdmtdzLkZjq6b6KZ8wlffXeygnJquT2KrVJs1HfR11LRUlGJTD63ClQG1pcCr16zRzd4PmTrL992RixN6ItdrGxrlf8ONqbq7d1NOQe+iDholBUPxy2xQQWu8tiq7sQZeRsBL5gEIUQp/l3cK3dHKwX6wiq4500R0IXXlD9Z4hH+49yvx1PPiyvwd572F0ebbVQ3vhaDcd9pKOag5VqTR/oO+Nr9AQO1ZKiK2OsZ3i+c6iWIc34AblNHFDGvkxW//dQ+cGE7HHZ0v5QRKJfYQ+XZSys0HjkHLVn4KqpE0eNSF8U5zOLE46rCGvQis2Xg8GCiCJlEPvI+v0GlSIrFO01BN8ebU+mStb8B2mosUv9A7aEttBAw3WWa2xzsQPtPjU5c9zBy//QISpP3oU4YFOLeHKqkpSD+uIRfr+EfstXEr0pDc4Aww2Nsly9e+odNOLfKwK5UPMtDuW
*/