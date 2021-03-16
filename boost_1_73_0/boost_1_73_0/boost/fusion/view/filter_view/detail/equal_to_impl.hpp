/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_EQUAL_TO_IMPL_02012005_2133)
#define BOOST_FUSION_EQUAL_TO_IMPL_02012005_2133

namespace boost { namespace fusion 
{
    struct filter_view_iterator_tag;

    namespace extension
    {
        template<typename I1, typename I2>
        struct equal_to;

        template<typename Tag>
        struct equal_to_impl;

        template<>
        struct equal_to_impl<filter_view_iterator_tag>
        {
            template<typename I1, typename I2>
            struct apply
                : result_of::equal_to<typename I1::first_type, typename I2::first_type>
            {};
        };
    }
}}

#endif

/* equal_to_impl.hpp
nMX2s+Ak8YXjJHHccZL40pnwjNemjo7XRgVmbq5wZcJVCHe3cPcK96hwm4TD8mVuqDZc/s5BOpSJqh8tnL9yemd4sKo6kbGjsZtMTx5RuPA20lP+XR3EsXO6XAljwGBpSVl+f9V0jS9ayF2bWePDPCxizo0zY8kZFfVU4g4Uc3f1l0FXYnzHRuVVhA8qnrbAlC+Mj4MJLynGhwBR6Yc+LIzf9IHiMsE+i8sEj9qq64SbLNwy4aqE2ybcX4WL3VY=
*/