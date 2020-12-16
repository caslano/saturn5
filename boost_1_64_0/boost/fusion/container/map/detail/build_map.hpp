/*=============================================================================
    Copyright (c) 2005-2013 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_BUILD_MAP_02042013_1448)
#define BOOST_FUSION_BUILD_MAP_02042013_1448

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/equal_to.hpp>
#include <boost/fusion/iterator/next.hpp>
#include <boost/fusion/iterator/value_of.hpp>
#include <boost/fusion/iterator/deref.hpp>
#include <boost/fusion/sequence/intrinsic/begin.hpp>
#include <boost/fusion/sequence/intrinsic/end.hpp>
#include <boost/fusion/container/map/map.hpp>
#include <boost/fusion/algorithm/transformation/push_front.hpp>

namespace boost { namespace fusion { namespace detail
{
    template <typename First, typename Last, bool is_assoc
      , bool is_empty = result_of::equal_to<First, Last>::value
    >
    struct build_map;

    template <typename First, typename Last, bool is_assoc>
    struct build_map<First, Last, is_assoc, true>
    {
        typedef map<> type;
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static type
        call(First const&, Last const&)
        {
            return type();
        }
    };

    template <typename T, typename Rest>
    struct push_front_map;

    template <typename T, typename ...Rest>
    struct push_front_map<T, map<Rest...>>
    {
        typedef map<T, Rest...> type;

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static type
        call(T const& first, map<Rest...> const& rest)
        {
            return type(push_front(rest, first));
        }
    };

    template <typename First, typename Last, bool is_assoc>
    struct build_map<First, Last, is_assoc, false>
    {
        typedef
            build_map<typename result_of::next<First>::type, Last, is_assoc>
        next_build_map;

        typedef push_front_map<
            typename pair_from<First, is_assoc>::type
          , typename next_build_map::type>
        push_front;

        typedef typename push_front::type type;

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static type
        call(First const& f, Last const& l)
        {
            return push_front::call(
                pair_from<First, is_assoc>::call(f)
              , next_build_map::call(fusion::next(f), l));
        }
    };
}}}

#endif

/* build_map.hpp
W2g+SC3JzEeiYmrmoyTTfGb4SL1JZWaJZXZ/s/vfZQZ2ZVHs3u7d+XwOX3Z25pwzZ2Znd845cwbTcT1m4gZcjR/hR7gRT2G25GuT3GOwGevgFmyNH2Nf3IZD8FOMw134Au7GtbgX1+NnuB33YS4ewEN4EI/jYbyIR9CTbT+GjfA4NsYT2AlPYi88hYPxND6CZ3A0/gvH4Xc4BS/gDMzHl/AnfAMv4Xy8jBn4K67CK7gBC3ATXpVy4HMl10KUreyflvxvkP1zTfbPH+iDLhzXLdEVO6Ab9sbyOAQr4Eh0x2SshE/jHTgXq+BbeBe+hx74CVbDPKyOrKOrgR5YE+thLWyFtbEL1sH7sC6OwHoYi/UxHhviE9gIX0RvfAMb41L0wQ/xbszG5ngFW2B9pQxQj34YgK3wIWyDUajHCdgWU7EdTsOO+DJ2xjfRHzOxC67ErnJe4Bwr12Z8xqTcvc3lY5pOs5wPnkM/zMce+D0G4Q/4MP6IsXgRk/ESvo4/Ywb+gmvxV9yIV/A0FuAveBWVNH/HdngNO+MfOBCv4xD8E+egzpXtQBdch664DcvhV+iGyvFdEbuhOwZiJXwAK+MwrIKjsCqOx7twAnrI9/15glyP8d1pLp968mwwZdpAfqpjDjbGrdgGP5Zy2oZBuF3K6RNMxJ34JO7C13C3HJf7cDnm4ir8Ar/E/bK/vsSKyudajsOvsA0ewofwMA7HIxiHRzEZj+E0PI4z8QTOw29wAebhGratj6+7w/0VtP0UbPRNKKFfQodWjvdFkHGNpN9B8T4HaZhJkD4GdvsXaPsWlPxcHS+9/X4Ei/U37juQQ1D1F9D0FYignIv0F5C+Auo+AtoxlZII2j4BJfcHkL4A0g+gaNt/6dv9bbXzpxOS2J4bjdGUxvvaNv3C9vxkacdPJyxguWzCAUI+we0enlND6E4IIcQRphEWENYQ9t7jbO93Ts7pf2X6S9r/x936/f+W9v8sT1X7PxFb2v/Pc/HUWtr/vey0/3tXLmz/Z1WH2v2lDZPvedttmBmVTHGOM/wXt2Faxqj3Qm9xB3HmukneS9mGGVpR24bpX7GwDXNnheLtlbMqFG+bDCqc19Eyr0GF4u2VP5a3zmtraa/80DrP3/R6mPV1hzJvr/TVPGfafvn7F22f1LQbGfgU2G+z1Gv3nbWdL5PEiY+E5Xnj1rwYmKfdx97Sh2CI5G2gtDHqLceng88Jr6rJT6QmjcOSRgzBixBF2EIaAdbjiHG9E0vdjsnuspaNtCcqz4Iv+tx1pVHkxvtkomqfqPMdIv0PgqVsBkjZ5LhLvsug/VWVH03aXtJ/4KCUWa6Umb6cpP0XtL9qnz1v4/npDpxDzsh25Mt2nCPQnspCsh1/QXvqrWzHZealuf7927T+2+7bsj2u+N+/raumQZm/6tNdC2NHjhmqfzXiQo9N5Qxl17ZqHV+7cmGbmW+RNjOiTFXUY0Vsi+a2CvndgWNkPXVbxacsVx93YVPci+3wc+yK+7AHfoH98EschV9hJB6y1hHKbwT5zeCrriOUOmNvnIm++DJ2xnSJ91WcjrNxNs7BVfgPXIdzcTO+gXk4D7/FBfgz/hOVxN9ED3wLq2MG1sOF2AjfRj9cjF1wCQbiUhyImfgwvoPjcQVOxpWYgu/hTFyF72IWrsP3MRvX4C78EL/BtXgW1+EvuB6v4EfoRhltxBqYjc1wE7bAzdgFt2A33IqjcDtG4g7r+OnyvS3f575FnpF9n9Tl98Z62AcbYl/UYz/sjv0xEO/HgfiANX75zsYYG/EflbrfE9gS8yS+kxiApzEUz2A4nsUoPGeNX75bMdhG/B0k/50lHX/0wS7oi93kOOoux1E=
*/