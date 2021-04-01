/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_BEGIN_IMPL_09272006_0719)
#define BOOST_FUSION_BEGIN_IMPL_09272006_0719

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/adapted/boost_tuple/boost_tuple_iterator.hpp>

namespace boost { namespace fusion 
{
    struct boost_tuple_tag;

    namespace extension
    {
        template<typename T>
        struct begin_impl;

        template <>
        struct begin_impl<boost_tuple_tag>
        {
            template <typename Sequence>
            struct apply 
            {
                typedef boost_tuple_iterator<Sequence> type;
    
                BOOST_FUSION_GPU_ENABLED
                static type
                call(Sequence& v)
                {
                    return type(v);
                }
            };
        };
    }
}}

#endif

/* begin_impl.hpp
AeYGGmYAv8YX4KsneGqOhJqXVxSmwgsq6A2kbsekfzym43yqhCM0AWfBIqz5sSH4ee2FjniRtJOwjV8pxz59uakA9WZQIZouVJWc4N7dYQdBvir/2Jhw7XVwsTGiHo/ZwVBNLLkC9F7ocQDqshA3J/e60YEgNg7UX840plYOVZAarA6i6uBAX1TGUWvP8z96P22eiv95KHz8smibpmlE3rRKIs0SbIT1vaUsw5SbeE235MWBOZ1suATfxhXxNf+GLSi/M5XhMNcUYYEL1OWgdl0paRz+s7ZZGlcASDcw/Uji1+/Q2VETjuy1LaAsAhEpOBVi+CS1c41XKxLsTPKKUSbWXW1PfxATlljCH7bZzZLZgxd9tfpbW0/4xhXMsSzIQtQj2dOER4wMcV/tT5uYpvtdBetzuYhJl7JAh+EVvrqwE0WJB2VzvQ5ZVhjt5bun0Ezeu62h4SGxxQN1pZIcWoyx8liN4ebVI9tVJDPtgAdfBsRz51mCKGoQvnKaRYi3f5NSLvXrW2vxc4J4FyENjNq0MC8pn9QP+Xd6tRWIXW+jpu5MTd7T1/ll+A==
*/