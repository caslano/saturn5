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
qECaJjdFRSFA85qg4BWRgJTMccwpx8rKMTMzj2MdU4/Txcys1MzKyjlZOWVl1pSVY2WlVmY5mc76Lut733d/KnbO/nlZPvv5P8/6vnXZa2+WEA3e8ihG+w0Tb5YSDS1c/cwZ6+w9T6geoTo94HTQfL72aslv8kV26+Dz52+y8sXDnadz5at5Etl7m8nfovOB5XIPbgmVKzKXhZw/d4dcovvQZQiIH5aqib6GeM0iriJEjiFyDLFbEWKvq4qAmNI=
*/