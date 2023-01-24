/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2007 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_COUNT_IF_09162005_0137)
#define BOOST_FUSION_COUNT_IF_09162005_0137

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/algorithm/query/detail/count_if.hpp>
#include <boost/fusion/support/category_of.hpp>
#include <boost/fusion/support/is_sequence.hpp>
#include <boost/utility/enable_if.hpp>

namespace boost { namespace fusion
{
    namespace result_of
    {
        template <typename Sequence, typename F>
        struct count_if
        {
            typedef int type;
        };
    }

    template <typename Sequence, typename F>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename
        enable_if<
            traits::is_sequence<Sequence>
          , int
        >::type
    count_if(Sequence const& seq, F f)
    {
        return detail::count_if(
            seq, f, typename traits::category_of<Sequence>::type());
    }
}}

#endif


/* count_if.hpp
9p7SNMjw3slQZiS9EwAbLOTTXSMoGbfiQ0KapMsvfSdmveKFMtoZikfPUSjHwzkles4UyinhnCKZI9KKzJo4V+QUGHIKQnLchhy3MWczklJNT3qDwcjxB9ZfbzRKimQxc+Bba7hZUtBW+W9TaJzN0BB2ZI80Rb1vHtojleT5Xyb15tbskZ41tS9+3dwEtkeyqg+9hLY29wSiyiYrD4JvvECUss7liwsJodnzW2s74i0++wJJgMpJAhQevG7z8USQ6a0XD/V+C8r3Voj3NmJT3l2oT6vSMjTlgm/oQAkJTal8AIPIHnIUA1PCBavvY0iJHJcytkVcyukUl7J/tu8D8seth6UMKRwpLOWRfe2ZpmnPSw2oFmEprz2JU5R/MrGlnou0f7uuzdiiM/a1IOHFkTTRrSyQcK+FTH0QU3xxgWi3z6bR9gP3tYe2f/c5GkORG23kDfFGfzwaoe8GOuGJscZY4pr9nmb3vHKvUVq7maW1H0Nf83hRTSxxdYRcwsTXQCz1BGlwEG8YcqxU1vugwAgJmTokZK5KNi4u+0Vcxfsp03t9i2DjYXW7fdhFHVzCahTgcl+o5T0Bz2Bt4lfsiXCtZMmOJHXlsDLIaJxdqx/7GeGXSTEnEJ7+/qt1eEoY0yY8nbOnNXhyt4AndyR4+v7r9sDThKWtwdPiI23DU+61bcPTHV9HhCf3/wJP7hbw5G4Vnjr8Q3hyt4An
*/