/*=============================================================================
    Copyright (c) 2012-2014 Kohei Takahashi

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_BUILD_CONS_10172012_0130)
#define BOOST_FUSION_BUILD_CONS_10172012_0130

#include <boost/tuple/tuple.hpp>
#include <boost/fusion/iterator/equal_to.hpp>
#include <boost/fusion/iterator/next.hpp>
#include <boost/fusion/iterator/value_of.hpp>
#include <boost/fusion/iterator/deref.hpp>

namespace boost { namespace fusion { namespace detail
{
    template <
        typename First
      , typename Last
      , bool is_empty = result_of::equal_to<First, Last>::value>
    struct build_tuple_cons;

    template <typename First, typename Last>
    struct build_tuple_cons<First, Last, true>
    {
        typedef boost::tuples::null_type type;

        BOOST_FUSION_GPU_ENABLED
        static type
        call(First const&, Last const&)
        {
            return type();
        }
    };

    template <typename First, typename Last>
    struct build_tuple_cons<First, Last, false>
    {
        typedef
            build_tuple_cons<typename result_of::next<First>::type, Last>
        next_build_tuple_cons;

        typedef boost::tuples::cons<
            typename result_of::value_of<First>::type
          , typename next_build_tuple_cons::type>
        type;

        BOOST_FUSION_GPU_ENABLED
        static type
        call(First const& f, Last const& l)
        {
            typename result_of::value_of<First>::type v = *f;
            return type(v, next_build_tuple_cons::call(fusion::next(f), l));
        }
    };
}}}

#endif

/* build_cons.hpp
wGYiX/IsDJ9hSCYehR8TA0/C3p0M6YJH4PTOhvhwI9OQK6yGTNX14Q92QyJ42GFIrmFIudYDf3IbEtVxjyHzSRUeg5+SmD4Lj5NluJiG3EniOh8u8BqyHk/B8FmGJPRZ+BNp1PlnG3IeSep7QU9XQ3bjUeg4h72oMwjfIkNwfzdDXiF+PA592YYE8QD8jIzE0/Bod0NCOt7DkPGkLx6FX5IwnoLdexoyTteEk8hwPAI3kal4Ep7how+4Aa8lEa0HPk8CuibcQqI6H8Z6EV0f+nvTE50PK8+lJ1ob/L4/PcFjA6h3mCFN+uw1hpjXcu5aDzyYz7njoesMmUn6fsVdgjtvoE48NNyQxTdyvnj6JkN63szd0GdhiAQYj8LlRPA4/P0W7oaO34oTP27cxhmRkbo+XBikn7omvGgEPcfD8C9ygvV9txuygfgYlzsMeZV00Wfh9EJ6qw6NO+mt7nsX/b+bmvAkLBpJb3XNe7hL/6Gf+i730htSrnPggQc4dx1/0JDZJKbrwLnj6bPWP8GQARPprc6BR0kc9xUbMoas1/VhYBL3DY/A3Ee4bzoOsydz33QveOgx7hvun2Lwr6Ppv9YPix+n/3gMep7g3XUOTJLM7fqvlw15lKS1Hnj+VPrMeBDOJgYeg4dIF53/lCH5xIeHYJz0xZNw7dO8F56GN5TSH30W1k2jb7g8a8hmElN/zpBBJKh7wQ7TuQ94GCbIODwF75pBf/AIjJbRW9w305BfSAT3v2DIjSSg68CDs6hJvdyQ70gVLi8a0mk2Z6rj0P0S90QdTiZDdH24kPi1ZnjnHHqCJ+GBl+mb7vWKIWVR+pOkNtjrVXqIR+Dh+fQKTyzgfKroFR5aZMhq0qjrwG6vcaa6DlxBcpKMw6MkqXUuZk3SpnPgaJLCw3AR2Y3HYWY1PcJ9cOkSQ/JYx3iL/r3D/dB9lxmyleRrnXDACkMK8CgctJKe72AO3ESG4yloqaW3SdaE95IoHoZfkCo8DWev4jcaj8MfSETHYe27PKvrwGvq6DPjsQ/o/3reV+dv0O+Pc9Tadhpy3R7WZ37iW34b9/K7ofvCvW2cHR5sN+Ssvw1pwZOnDen/L3dGx+GCTi6Zivs7u6TE4pJc1jGsLtlETmk9sMnmkgwdt7vkI4dL7Lg/yyWzSKvWBjs5XeJj3AdnkGM6Dg+RdlwMl/zoZg/mxD0uudB0SUhrgEfIOK3Z65KbyUjtJ3yxC3PUu7pkPqnVZ+Fj3V1ShYd7uGQuacBj0NaHenT8PJcsJvU6H/a40CV1uFzkkgMXu6RZ18xxyYl+vJt6f5ecO9AlLeq5LtkxhHfH00NdMn4Y74InAy55Jp930fWvc0nm9fTka/oAJxM7HoV33uASUx3OuNEl2bjcRK9udkkfPA1fLXBJDp6Ah0mujqvf4pI8XfNWlzSSfB2HA25zSQEehK+TQjwOrw66ZAwehqtIka4JPxnhkmLcuN0l599Bz3UOvGKUS0r12XtccpKU6ZzRLllEKvRZ+BOpxGWMS4be65JqPAnvGOuSGh2/n30e4Cx0PhxWRG/xEIyTep0Pz3qQc9F3gdNIEx6Dpx+itzr/Ye7dOPq2k3XgpPH0DY/BtRPoGy4TXfJnMX3DI5Nc8jbJxePwO5KHp+GUR+iVPgu/JwU6Dmc9Sq90PrwoTK/wIHycFOmaUCbTH9wHbyOleAjWkDKtDWY8Rn90DhxLKvVZKFPoj47D20iNPgtzn6A/WgO84EnuG+8bgPWkBU/Btqc5I63tGZdsKeXe6llMc8nCGdwxXMpccuVMnmFOFA6aRZ/xGOw9m97iSWhWcD/1fOGPc6hVx1/mPr/C+s2sD51R3hf3wxgpwxM=
*/