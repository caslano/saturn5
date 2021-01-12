/*=============================================================================
    Copyright (c) 2001-2007 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef BOOST_PHOENIX_CORE_AS_ACTOR_HPP
#define BOOST_PHOENIX_CORE_AS_ACTOR_HPP

#include <boost/phoenix/core/actor.hpp>
#include <boost/fusion/support/void.hpp>

namespace boost { namespace phoenix
{
    template <typename T, typename U = typename is_actor<T>::type >
    struct as_actor
    {
        typedef T type;

        static type const &
        convert(T const & t)
        {
            return t;
        }
    };
}}

#endif

/* as_actor.hpp
4YPD3kUW+NNakWDZavxlLHXANULBvGkXFfE+PwfVgIdUZZ4C1Pde8YPwwEW34ZrY4Dji/bfgZPMex2aJoxegY0XJxKRH4G/4/ZSGzD9+7uNVYDxYPQAcHZiCHVK3L3pdrgJyBHPP0q8Vkeo6KJxkPzHfq9jySfr+qCxmNEP28MP6C+H96Nvs94irfpVErcXsFx4Hbg5GL/D/dub3/XnI+GNkPwbeVwmug0wvJZHb+Yb+ngF7
*/