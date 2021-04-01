/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_CONVERT_09232005_1340)
#define FUSION_CONVERT_09232005_1340

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/map/detail/cpp03/as_map.hpp>
#include <boost/fusion/container/map/detail/cpp03/convert_impl.hpp>
#include <boost/fusion/container/map/detail/cpp03/map.hpp>
#include <boost/fusion/sequence/intrinsic/begin.hpp>
#include <boost/fusion/sequence/intrinsic/size.hpp>

namespace boost { namespace fusion
{
    namespace result_of
    {
        template <typename Sequence>
        struct as_map
        {
            typedef typename
                detail::as_map<
                    result_of::size<Sequence>::value
                  , is_base_of<
                        associative_tag
                      , typename traits::category_of<Sequence>::type>::value
                >
            gen;
            typedef typename gen::
                template apply<typename result_of::begin<Sequence>::type>::type
            type;
        };
    }

    template <typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::as_map<Sequence>::type
    as_map(Sequence& seq)
    {
        typedef typename result_of::as_map<Sequence>::gen gen;
        return gen::call(fusion::begin(seq));
    }

    template <typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::as_map<Sequence const>::type
    as_map(Sequence const& seq)
    {
        typedef typename result_of::as_map<Sequence const>::gen gen;
        return gen::call(fusion::begin(seq));
    }
}}

#endif

/* convert.hpp
0xtANqyhF6pQRYPkP8+wg/Uay8L+3yZou2/xFmQmc4cXdRaNGiJs0PibZlf3vBGtoDR5SBppUXYsVgnWOgZcFVa05hAvapKz880yFEm50IoVzBXGs+sWvWUE761ad6bBFZ1SIPOzsU2+z5wXdI6xcNM+LNQ4FKwvsmaHc3d1gTQBx95eH2GkgmUTmOEqljynGIbQMovjMLufWQFLdpFbp8AKIYqJ7sutxDWqC5GKNRXu81QfxT6nb1Vz0nluC7iXj4fU32IEblYrogLM+W4z8IkniEgWIbu+nlhTGazJQxnSvigvYDJ5yhbCz/bs/eNI7yCAVXDsTjDkxIdD8u6LFd7evH9ymPpt5nMP+bBfIU8tqSzi1I3kJLLAqxgydK2n7Z1CkNuK+xzqMxM2/5HiRh4RRRj4nnsHvVjBQIOcZLl5fULJ7Gb/uvMeEZbnMkiRwPpbi/BA0MJrmBf6mT9cVV+U3F8LuOV9NWwY/bnKltcFtyi9CTUgVe7lKSysFm1C2zEpywkXH2jQBBiYeCJiXMG0QeGHpyUxHaWRcNnVPFWtgYDYAqn79w17cA==
*/