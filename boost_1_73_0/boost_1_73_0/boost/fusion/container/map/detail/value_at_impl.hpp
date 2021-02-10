/*=============================================================================
    Copyright (c) 2001-2013 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_MAP_DETAIL_VALUE_AT_IMPL_02042013_0821)
#define BOOST_FUSION_MAP_DETAIL_VALUE_AT_IMPL_02042013_0821

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/at.hpp>
#include <boost/utility/declval.hpp>

namespace boost { namespace fusion
{
    struct map_tag;

    namespace extension
    {
        template <typename Tag>
        struct value_at_impl;

        template <>
        struct value_at_impl<map_tag>
        {
            template <typename Sequence, typename N>
            struct apply
            {
                typedef mpl::int_<N::value> index;
                typedef
                    decltype(boost::declval<Sequence>().get_val(index()))
                type;
            };
        };
    }
}}

#endif


/* value_at_impl.hpp
r3SRpioXQXTExJYs1sJonYowMOa1FPsu/ryEpvMwywVONdUnfi2IlxbZmbPZrhhyedk0vmAKjQPP4yPQDsVjhQUGhR+I0/ZI3efgkbqr4Xd5ZmO06n2j3R6JFzIhAt+nVl9ifM+z9ZKnRFmmiWV85tajFKO0jfiVjjBO6UyK/IAa5hBRYHdouZ5IKKMzLvFaGQRTd0hVJds9Hlilp/YdUzJGN4LhKaglVLlEyLWVmWdCdxXcAnKA8I08NDnVj0teeP5FlOMmNtCfBfTQQ+RuOBe+7MynZD4MwRNDEWsKtsHkoGqCqdVgpLGMLe0AhxhAnUsOpTQ7waNNvZ8266+z0o2dBkNTSAsIqcyeZ08polqKYWnahThxw0RL5AqmbZWiXWebWedWnfUd8V/bzeMvvUFP2jB95/Lxh+dae1R6SELxrxRwo6QJE6lknbfAjrIVLFbDW8mNkgYY1IT3GP26B7QwzlYrb+dIQIWXz/M1osJokfNF+WqElcbHxHYHq/etGhxb4HYlOXFGI+8AeLVV1NpheeKczNuJirpNI0PPoCsRiSuU3n5ckF+FAszNW6ahE5q2NZqYsZcYVhoiwIvtxXjHxQy+echfsH58udn/fSEJaprg19JSklWoc18ho/kHPgqY7nVAS9qNKBWC
*/