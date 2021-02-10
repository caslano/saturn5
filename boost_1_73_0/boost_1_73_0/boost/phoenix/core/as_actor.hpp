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
dXJsLW1hc3Rlci90ZXN0cy9zZXJ2ZXIvTWFrZWZpbGUuYW1VVAUAAbZIJGDFVW1v4kYQ/lz/ihGJ1HAlkDtVp7v0UsUBXw6FAMLm0qiprLU94L0su9bumgQpP76zBiehuZR+OKlGYDOeeWbmmZfde/PjLm8Pdl5x9Y3porszGGv1DVP7feU4foD1h4xu6L7DRQeeLB7iJuy0eICDyiLe+PjknuN4h5sbF5j76TjDm9g9ksTbI7uuKlaaz3MLB90mvP348QMcwrujd0ct6DHJUUBoUSao5y34lFWS05zd37cN/t4CtMBEuwKKcm7AqJm9YxqBngVPURrMgBnI0KSaJ/SHS7A5wowLhO5ofN0fnrfgLudpThgrVYLJVSkyyNkSQWOKfLmGKJi2oGZkTdgZN5bwSsuVbJNrBIt6YQjCOWfCKGBLxgVLyA2zkFtbmONOJy21oMg7mUpNJ61Tb+d2scnimiJYsBWowoJVUBpsgdNrwUJlfObuRAUJizIR3OStp1DIkcw6SoNBIQiKzDiadcgI4YaZltOCgqLl1t2MksZ5usvVYkuRKCSQWakluSEKSCdTRHALSpmhrnSrpGsPGzYral8pyVOsGShJkUDDD6EfNiBhhpsWXPWjL6NpBFf+ZOIPo2sYfQZ/eE1Y
*/