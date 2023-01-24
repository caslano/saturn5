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
Zhwld2VkAKviMjNugTO6b2f6krFwDdIgWPRC+bKrKgtoqc9bo07MOEElIy//RnoOJJmrZHQnFTT06OmqK5BAF66rrT0G6H0bE88vVlxDfXxt9/z+Wh5dTG7dex6cRCCvcTApOLHbybPHg8/YM4RjPuqinAmQs3PmX+caGYq5eEV/RTs6Zw3tz9OyZvHv7UYm73AVPPbzsjDgz2XunxTHwQzXlOQzw3FDZJoFKUKS9lkvjOQG+xROFhnAjzyvemh7NshIuMZJ4WtkXGlP0EfV7nT0AD7S2GFSuAWyQPmlToDDzVeU1Ay9XdhW6+b6G+XqKLbRjZGHD18qiXIqBsg4moMWMMbe6hjL0Y1n5yRQDetocumAo9OIK6p8ZXUPSKDdmX7BMPnQLTC0G9Rm/XjBmjuDRyewNNGIEiJIYltFBY5mhtxLVohpaG3jYueS7i6/7ysnkxk+3WI92VyRYqBXj6yXO2zujr+NQjZM+5ob1QKcS1b+cQQMk9gmdDevicbGmgf11PuFmVwvEOUcIwDWpuPU3+fK+prz5EmX6U3tOj4Nl2oSl2QRuqLfZcnwftW4kgzBOFlmcvgX33L6Vff4MsCDkpN4R8DYNfq14Hj6Bx/U55IDHEQGjtYx9HLp2S3e5vvvLqjUDPOZzKjosJ2t5p9CA5kNWn4Su4RK/UiwvUuAyxgNG1SRe+kmulDD7KQ+LGju9xYmalzFAFh3
*/