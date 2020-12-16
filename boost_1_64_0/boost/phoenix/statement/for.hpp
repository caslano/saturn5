/*==============================================================================
    Copyright (c) 2001-2010 Joel de Guzman
    Copyright (c) 2010 Thomas Heller

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef BOOST_PHOENIX_STATEMENT_FOR_HPP
#define BOOST_PHOENIX_STATEMENT_FOR_HPP

#include <boost/phoenix/core/limits.hpp>
#include <boost/phoenix/core/call.hpp>
#include <boost/phoenix/core/expression.hpp>
#include <boost/phoenix/core/meta_grammar.hpp>
    
BOOST_PHOENIX_DEFINE_EXPRESSION(
    (boost)(phoenix)(for_)
  , (meta_grammar) // Cond
    (meta_grammar) // Init
    (meta_grammar) // Step
    (meta_grammar) // Do
)

namespace boost { namespace phoenix
{
    struct for_eval
    {
        typedef void result_type;

        template <
            typename Init
          , typename Cond
          , typename Step
          , typename Do
          , typename Context
        >
        result_type
        operator()(
            Init const& init
          , Cond const& cond
          , Step const& step
          , Do const& do_it
          , Context const & ctx
        ) const
        {
            for(boost::phoenix::eval(init, ctx); boost::phoenix::eval(cond, ctx); boost::phoenix::eval(step, ctx))
                boost::phoenix::eval(do_it, ctx);
        }
    };
    
    template <typename Dummy>
    struct default_actions::when<rule::for_, Dummy>
        : call<for_eval, Dummy>
    {};
    
    template <typename Init, typename Cond, typename Step>
    struct for_gen
    {
        for_gen(Init const& init_, Cond const& cond_, Step const& step_)
            : init(init_), cond(cond_), step(step_) {}

        template <typename Do>
        typename expression::for_<Init, Cond, Step, Do>::type const
        operator[](Do const& do_it) const
        {
            return
                expression::
                    for_<Init, Cond, Step, Do>::
                        make(init, cond, step, do_it);
        }

        Init init;
        Cond cond;
        Step step;
    };

    template <typename Init, typename Cond, typename Step>
    inline
    for_gen<Init, Cond, Step> const
    for_(Init const& init, Cond const& cond, Step const& step)
    {
        return for_gen<Init, Cond, Step>(init, cond, step);
    }

}}

#endif

/* for.hpp
pBgrmswQq4zRacmHoWYZ3UnhwzCZbxwL5WWHS7ycexCyP8LCt96jHKHLWJ6BiO+BkPlpfF0CjZNig07P58Ld+J+XKcnhderr+VKdbvcsRfgzUpexf44ySuLrMza/e2fzKFsMCT2jJTm6r6KxJvwfY+aLyZL7OdaWp505F+XHSTLm89tHyTzx7Sk588B4K1/7iW+u+2iJb/7ukQkSTyukja+JOo+epwQE/RgzvUv4eayZ3puhu1PBL7PyRSSIf1wu32gCWi9NIr7pTCv36XiDp/1KNo/9ZINuPeZHdqfoMqZnJ8Q/gfiW86vEP9HK548x47ROn2riU9tyv6fJvPUYD0SfnkPv1O+BTiI6u29jK5cIhl6XzZpvhiyHL9+JQkyzWa7x8LCiQ+3E0UhBrzDodEsi6DN1eibEfnZcq3elQWfyxnxI5aoMPnV70SaziC7O8BoXPtbU2hprNsmw+0+NNodobF5bSzbmEk2royY7j+h8LqGYzDdo+upIi2u1DS8U7uhIq33sT33OWWAjp9smOwt1GdYRtXsTEbOTc3mWe59FxKe5SFrRCd2nEF9rcvjRm6E13mKDl63kk6vw+VSdbrtW42WXyDK8Iwq6W6KLe09Br8mhG+tJj0G3rMe8Ek/c39JQJb7P4JvPB4vvVJD58FCLd51Bt5wHrjd4Oeszje83+LZrsKUSn+67yGn6HgWDn+/dGfe9QZbjX30l2qbRoOddNwUMmf7WTVy2yZDN+75Li1uzJKv1Bm38LJd5nVFe1xai5Xv3pOltleR4l+G3gPRdCQbP9rsUVhDf+j5KPDNbSfxDeV/EfFllyMtrLl6fNuLle0+kya0muX7eEXFba0gu9/2QqNdpOs+yLuJl23W+df1zus7LXf98TqfnX/+EdBnL+ofbPSOHn7vuDxMvz/slLtNhI8PspFU+CrlMxEZGe84JPTzG0X5luC7ur2rIGREkfztzeOkUtZOYnagtu/qTCaX0Z53dulzOWoPbiREvzzsfLnMmyeR538PbdS3JGO96BD2u0/X1hPjuA51uv05J6HzTOoT0JnW+tqYQ9BTRjXiKeWcd0a1xWh/LduurNx6vtCYrX9bIr4zGs1zyxFyTJb78/LSXaKZ3STy2fcTL8z6Ky6w3ZKzvosivDSRjfXckdGw08U2muMxZJhmTKW7nbEnG7jnDOXn43Ar128+TTD/vnLiuc/PIcQmyd54hY33XRH1lE8mY34mer9HXh2NZ1oxYPopnIqItLzD4UCVoFxJNfEeeGF8XMZrlKw+F/MXEk7+z8BJGs3zdofDpUsYTXyFo+lJCUZfLJL78PTibJbqd3i8Y/Fl2ei+X+LLeLRLdTu8VOt+sVejdqvNzvwvxSp1u1ipiehXjR2fFEGv9nYTGu5rxYrOiuTzjty7W8N+6+GvRvZPOnbxubvjMiQ8+OvfySsVJTnKSk5zkJCc5yUlOctL/YCpE7hDf//+f+9r+dvDa8QCEPSCoSHaw739ciN8SYF80OEgZSb8hMNL2twSaUniZGzsLd5BlHrxxxs1pGt9F2FCi4gvh5ynF3E+8X+DpW8hjkbcj7wF/0ylFeD3ssnyj+jFKaXG1ffUvLMV/Q5WFJR/jew/HKAPwCwfD+HfrD4O+DJB93gleEp/TiSgkBioLyY/t5MdVwALgVuBMfHn8GYuFH638KXfOTi/uS56muAC+6PaHwwK+0TrHXvEAIfgn+l7GNxWyt8Rkz9g99pnsLSZ728jeUcwexboK9ja5DXvW3ePKYdtkn4czG+iM0MB9WEo+TGaGyTb7czTybPiwXfPhEHaof1Z/ngMTzxdzYnJPgTUmc+HP45o/9jvgD9uHMeRDCjExttE=
*/