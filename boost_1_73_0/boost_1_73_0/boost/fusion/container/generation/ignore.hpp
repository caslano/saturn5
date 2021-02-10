/*=============================================================================
    Copyright (c) 2001 Doug Gregor
    Copyright (c) 1999-2003 Jaakko Jarvi
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_IGNORE_07192005_0329)
#define FUSION_IGNORE_07192005_0329

#include <boost/fusion/support/config.hpp>

namespace boost { namespace fusion
{
    //  Swallows any assignment (by Doug Gregor)
    namespace detail
    {
        struct swallow_assign
        {
            template<typename T>
            BOOST_FUSION_CONSTEXPR_THIS BOOST_FUSION_GPU_ENABLED
            swallow_assign const&
            operator=(const T&) const
            {
                return *this;
            }
        };
    }

    //  "ignore" allows tuple positions to be ignored when using "tie".
    BOOST_CONSTEXPR_OR_CONST detail::swallow_assign ignore = detail::swallow_assign();
}}

#endif

/* ignore.hpp
XK86u9EA2LfhMx6hq84hTwdVKjQ1ilaZbl4XtJws745maeL4xKPnbtZsv0zGlURuwg9HfXAQKL2NAJ7Z+pa8bSZuuAvBJa5Do00TnF44sgRl+TaH7Xr81FrHW824Bn1gEQDBp13vZbjJhu106nPMiBCwuO3sY0831hfbSjVznQO2s4FtpuJ7hyznK2jEedyLJKA4HQgJD9uBBDZDiT3PJZAU/cXObpXkOv5Itt0Xjn20XpGfY/m//z5+/3OkCtz/Z47O/6b1jPGoPzSg5nYpptbW75BklFrb7/+ahr68NA1OW0D8fDA6b7elFYQB4LBEQ+nV8mId5b24NDk20z3XjUm3Z5h3w/5Hk68lJb//LoOXa4PdXk/DZUjD3ugC95GVQ5XgDQz9vicLU47X6/aHl6Mm8cZd47pBvNHopq81jccybhXMEry/dSdqLJbgDfq6jNXJ4E0GysIW4t3pxuh2ov39TlNhUYh3oV127wZsbbMx6o0GkpBivKFugoPTJpfdnoLUhXiDUa87MPvjs4bx3jSEp2uTe22iq9SxGG90bcLbxuxFu7qQdqIyeJe4aG6iiFaMhz56dDdUwizGG4D9DbtG/14zjZF5B/VThi3Eu9YNpYotw6vQNorxdP1Om/Q0xSoR4t1on8ZdXf9w
*/