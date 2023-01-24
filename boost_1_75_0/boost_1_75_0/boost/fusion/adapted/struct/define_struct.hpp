/*=============================================================================
    Copyright (c) 2010-2011 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_ADAPTED_STRUCT_DEFINE_STRUCT_HPP
#define BOOST_FUSION_ADAPTED_STRUCT_DEFINE_STRUCT_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/adapted/struct/adapt_struct.hpp>
#include <boost/fusion/adapted/struct/detail/define_struct.hpp>
#include <boost/preprocessor/cat.hpp>

#define BOOST_FUSION_DEFINE_TPL_STRUCT(                                         \
    TEMPLATE_PARAMS_SEQ, NAMESPACE_SEQ, NAME, ATTRIBUTES)                       \
                                                                                \
    BOOST_FUSION_DEFINE_TPL_STRUCT_IMPL(                                        \
        TEMPLATE_PARAMS_SEQ,                                                    \
        (0)NAMESPACE_SEQ,                                                       \
        NAME,                                                                   \
        BOOST_PP_CAT(BOOST_FUSION_DEFINE_STRUCT_FILLER_0(0,0)ATTRIBUTES,_END),  \
        2)                                                                      \
                                                                                \
    BOOST_FUSION_ADAPT_TPL_STRUCT(                                              \
        TEMPLATE_PARAMS_SEQ,                                                    \
        (BOOST_FUSION_ADAPT_STRUCT_NAMESPACE_DECLARATION((0)NAMESPACE_SEQ) NAME)\
            TEMPLATE_PARAMS_SEQ,                                                \
        ATTRIBUTES)

#define BOOST_FUSION_DEFINE_STRUCT(NAMESPACE_SEQ, NAME, ATTRIBUTES)             \
    BOOST_FUSION_DEFINE_STRUCT_IMPL(                                            \
        (0)NAMESPACE_SEQ,                                                       \
        NAME,                                                                   \
        BOOST_PP_CAT(BOOST_FUSION_DEFINE_STRUCT_FILLER_0(0,0)ATTRIBUTES,_END),  \
        2)                                                                      \
                                                                                \
    BOOST_FUSION_ADAPT_STRUCT(                                                  \
        BOOST_FUSION_ADAPT_STRUCT_NAMESPACE_DECLARATION((0)NAMESPACE_SEQ) NAME, \
        ATTRIBUTES)

#endif

/* define_struct.hpp
ArSIBUWt4Pm7l9bj90WZAMNPP2XqBzCS6T2CeL40Bf3+jC5U46BQjUGi6H5IFc+9BLWdIu3InYbasXUmakefMXFmPxuZp+2a9KTwO54R1MxmMu48YEdnTb344VCOpXsklPYiZNgbjm3rFp/yk6j8F4LRQbNRLTDlShJulfkdE/w6DgQp4Dy9NJIej4G9LdFIuX6d3HZoQxn2WGJBjYQ0ZKE0pKI05Jh+HUosqg9R+LaQEFBdLaEu0f+1yE0KcaMX/xxCvAd4iCh+WuXgTS6hM+SGCwZXk5woXi7vz6A4a3Q5g1fe4Fd4nHtthkRRdHRGl7Od9OtYZzvt1stAygxy5UHyvvBcJGvt5JdXMfm+jPvhwsaV+01zsc8uPkste2kIR2ZR/Ml60Q5ndcv6lFQWNIcoyJJwpEVBY7DVCcVlS5Pkc2P77Jrgx+/49owud8bysIN+wvUmY9vAonMztR0sf0W1T4nysN252hYkA0+eIU6/sMnex+nXg2fU3n/b1oTe516PDVF6/fwz1Ov5NrV1wlGivRJ/0e/Y95+uwfmDS3Xk0s2+qxtMoFuiYD4rVZ+VBj4rV58pwBomVgaZmEo2Mf+tQBOzpV4T06WdnLhd2I7GUt/s436nLz0ErGcSZu+EYznjcXFbmJFZnWTS6iNtqfyUTvxeR7qWdMQh+iZRvqIF23RoKSJF+z9GonhaTqlBOwLhzUY/ek23Xguo
*/