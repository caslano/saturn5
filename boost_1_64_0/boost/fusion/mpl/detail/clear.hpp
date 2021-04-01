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
RBECFubG3H+eMwdkUpR0bRiBkTOmhabEV0c+wcanbjJuV9ZtGCWxNgqcrgmRJawdwNBb4oHWiA2He7AecsVAMg7Jv1WJhQe6biUMQb/WAJ0echfluToG5s6Eou8wjYzsQupWfs1OEr2CqV8KYQEMxisw7QYJK4E9GDhfxJJtjT9xnVUXKFarFHpoilEfnqxf9DLo5Q0VhZl7/DnAOCTgJqthL9xb+NVctC1rpb+YcY74X9BGNPLi5cSGkIrkcxCU/kMc4axrZ26feHJWDFNeMW/czkEJ9Ki0yJeqEjtcOgym+4NgqJCTZEriDYhdzJNwtDRyg4Q4Pka+6kKokK4bmNsbYZPoHhR/5VVtOnEDPEp2DEp5U3CMWGcSKypuNwqMp1Pkro5bcWd4WX/HQCh2IS/pSr+jVFjkaG7Quy4RCPhW2n2sY0ykMOpA1cPIAshbCbtczfRuz1BDjlUZylieQBBCZO1jOAvDeTIn371I+Zfh3rreVMUihi2N6rFeC7fQT2JE/Jw+Ctd68cT12hXEUge7sbGWnxEKCfEkyFZ14iJW6YLgiuEfFQMxxw==
*/