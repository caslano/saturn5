/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005 Eric Niebler

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_VALUE_OF_IMPL_07172005_0838)
#define FUSION_VALUE_OF_IMPL_07172005_0838

namespace boost { namespace fusion
{
    struct cons_iterator_tag;

    namespace extension
    {
        template <typename Tag>
        struct value_of_impl;

        template <>
        struct value_of_impl<cons_iterator_tag>
        {
            template <typename Iterator>
            struct apply
            {
                typedef typename Iterator::cons_type cons_type;
                typedef typename cons_type::car_type type;
            };
        };
    }

}}

#endif



/* value_of_impl.hpp
WuUniz6/48m8tq+TU31u4ourMc2H+xjzDoCfwAT4KUyCn8FxcDN0w8/h9zAWaRB9EaKvC4wUfVVB7JcLz4B94JlQiZeChPh8PRKvGxwi8cLknKQD4eGwDxwPD4ITYLjuvKUq0XOL6NGftzRPzm2rhIfB+TAGngSHwlPhRHgaPBGerjv3qRKeBc+BC+G18By4Ei72po/t4nOCZZJ+MBwt6RdL+iWSfqmk75F058ACWAaLYbnorUXEb4Q/yat3X/HXKeEo0TsB9oXpUk4TYTKcBI+GSFU5zIDz4RR4NsyCt8Kp8E6YDR+Cx8KX4XFwE5wOt8EZUDHGCQ+COXAonAmHwTytPsSHBJ+2qI9F0h4Ww97wXHgQPB+mwqXwKHgBTIcXwtNgNVwML4KXwmXwNngxfAwuh1If+JEC18dlkv4VcDC8Eo6BV8FMeA3MgdfCYngdlHYuPiL6hOZ2Luf9dYNfwz3hN9D3fUuReE6L79uxYs9xsD+cDifCGXAyPAEeB53Qp69O9GVa6Osr+g6GYTACpsBIOBoeKvoP0/SJnwZOtdCXLPqGSz2NkHpKgePgKJgBU3X6atYEtm9n0Rcs9nUX+3YR+3YT+3YXfTkO8a+I36XGdE7dd/I9+B6Gwx/gQPgjnAx/glPhL9AFt8IK+Cs8Ff4GtXKVdJIt7J4pdufBvtAl9eWG8TAfJsJZUFuPvDawvijRN0D0RYu+gaIvRvQN0unLaULfWNE3TvSlib7xou8o0TdBp6+2CX17ib4Q0be36NtH9O0r+nr49Yk/ARss9L3HfT1hA4yDH8Ak+CFMhh/BUfBj3fctR/TFW3zfXhR9L8EYWK+LVyPx9rCIdzL3dYOnwN3hqbrfo1qJN8ni9yhffo9mwcGwAI6DhfK7dKK0o8sdMkYOvxE9IXAJ4pDzK7GLz97yvED0XSjttBrOgMvgLHgxLIfL4enwEng+vBReAS+DN8LL4TPwCtgAr4QfwxXwc3g1lHzKuDrPYot81kl9Pyrfy8egGz4Oq+ATWnnJuDY43ULPfaJnndTv/dAJH4QnwfU6PTVN6LlD9NwpempFzxrRc7fowTYZ16VuRc8e8i4gPqWqUJgAw+HhcABMhHEwCQ6HQ2EqHA4z4Aipj5EwD46CpTAVzoVjpZ8wTtcfaBA7pln8/kRIO4qEveEhsA88VPojh8GRsB/MhP2h1m+TMdfxFt+vyfJ9yISD4BR4OMySepwKR8Nj9N//JvTtL/p6i74DRF+Y6DtQ9PXRP+8eDKwvQfQdLvqOEH2Joi9J9A3V6fM0oe9Pee7/BQdBh6oPiL6dRF8XXb+gXvQdY1Evr8rv0WvwMPg6HAA3wTT4JkyHb8HJ8G3teSPjeDDO4nnzlrS7t+FA+A70xauSeEdYxHtf1qU0OOR56f/+Mh4WuN8cLe1roPQHY+T5NEj6zbGiJ9sh41owS/R0h+miZzb52xuWwkjogdFwjjy3y+FIOBdOgJXwaDhf375E/zKL+qsRO2+Qdr9Svn83Qw9cBZfCW7R8y/gSLLbI99OkGw43wBHwGTgWPgsL4HNi1yaHjPOAo6Rf3Yt/Py967pLnw93yfF4rz+d7pF99rzz3H4S5cD2cDR+BC2Cd9K8fhxfAJ+At8Cm4Hm6AT8Bn4IvwOfg6fB7+Bl+Af8KX4M7YVw97wJfhwfAVOAS+ClPg63AMfEPKCdtl3Ie+hfSfgpAekr9puvJskPtcFuV5ozx3b4IJ8Gbph94CnfBWGN21deuDVrZgjVD0+9t3ndCQNuw5mv1+x6wbWvh+o7VDnbbvaI9RxnVEte//O/YfbXi/c/cgdTS0bn3RjrgP6Yobgx3rkXeQrUiPm4IdwxAXUoXUIOs=
*/