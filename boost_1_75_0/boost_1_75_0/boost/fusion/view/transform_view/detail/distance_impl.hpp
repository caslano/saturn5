/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_DISTANCE_IMPL_13122005_2139)
#define FUSION_DISTANCE_IMPL_13122005_2139

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/distance.hpp>

namespace boost { namespace fusion {
    
    struct transform_view_iterator_tag;
    struct transform_view_iterator2_tag;

    namespace extension
    {
        template<typename Tag>
        struct distance_impl;

        // Unary Version
        template<>
        struct distance_impl<transform_view_iterator_tag>
        {
            template<typename First, typename Last>
            struct apply
                : result_of::distance<typename First::first_type, typename Last::first_type>
            {
                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static 
                typename result_of::distance<typename First::first_type, typename Last::first_type>::type
                call(First const& first, Last const& last)
                {
                    return boost::fusion::distance(first.first, last.first);
                }
            };
        };

        // Binary Version
        template<>
        struct distance_impl<transform_view_iterator2_tag>
        {
            template<typename First, typename Last>
            struct apply
                : result_of::distance<typename First::first1_type, typename Last::first1_type>
            {
                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static 
                typename result_of::distance<typename First::first1_type, typename Last::first1_type>::type
                call(First const& first, Last const& last)
                {
                    return boost::fusion::distance(first.first1, last.first1);
                }
            };
        };
    }
}}

#endif

/* distance_impl.hpp
AbvkuV4rXbnrN+jpNj7WZ5KcDz7hlsXl/Mt6kY+Yog5jsY2iAZllvOOieItucfjuSkWlQ7YeJxzEHnffqLBG1oz1Ju0M0xo63UYqHXW2HmhTWK7RIGbuo0eQ+K2UtgXvMQWVPHzf4rIfMOgSj/H+5jAfrSvLczqdXZgpkx4zetjYy3y9Sd79It104hmWI35jJhjxDIwddFaAEmuy9Qb5hpv0nztnc/9lDgAuLNHTT5qEfQj+AlhqwFPm69HB3Ondr/KJfV54XudomaG0Jr28h3kw8/tLNo0OPPK786G5BkWB+CqL9L2x49x8piPn641Bl2Gv31iViwR/cGJSe50mosBC7wj7eK7HvG5mdHiWn+vxuzxz+Aq8v2Wyk9SY4Zm6X69WxMdEwCWLLyfFb+6Pao/TMEkXswPnesyRW5Tduh2ezk0W0fzopaJt8C1GIJIfqy7y0V9g/hz+ZPsBCpM6pee54hsQYRSyNud6u/xDT1xegh5cznOpW9vGppNIrF8o7kby/LwssShuQavUsoP4u+YTbPW81GtL5atXWf+cX4/J9TDa0B9FvdP+BvVVM1UPym85d8W85OWyHqiyUV5pG55iw/5S7x7lfXG32Vfr75xPv41S5w0clmdFEV/S6+T5OHgj1AY4YVO4WyCXj86URl4Q0/nO/oVF55k/rUE3CSzM5tPfLvKBJBgP+fYjnu60M66g3BTBFnqH1Ki3
*/