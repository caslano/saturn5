/*=============================================================================
    Copyright (c) 2009-2010 Hartmut Kaiser
    Copyright (c) 2010 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_ADAPTED_DETAIL_STRUCT_PROXY_TYPE_HPP
#define BOOST_FUSION_ADAPTED_DETAIL_STRUCT_PROXY_TYPE_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/adapted/struct/detail/namespace.hpp>

#define BOOST_FUSION_PROXY_PREFIX() obj.

#define BOOST_FUSION_ADAPT_STRUCT_DEFINE_PROXY_TYPE_IMPL(                       \
    WRAPPED_TYPE,NAMESPACE_SEQ,NAME)                                            \
                                                                                \
    BOOST_FUSION_ADAPT_STRUCT_NAMESPACE_DEFINITION_BEGIN(NAMESPACE_SEQ)         \
                                                                                \
    struct NAME                                                                 \
    {                                                                           \
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED                                \
        NAME(WRAPPED_TYPE& in_obj)                                              \
          : obj(in_obj)                                                         \
        {}                                                                      \
                                                                                \
        WRAPPED_TYPE& obj;                                                      \
                                                                                \
    private:                                                                    \
        NAME& operator= (NAME const&);                                          \
    };                                                                          \
                                                                                \
    BOOST_FUSION_ADAPT_STRUCT_NAMESPACE_DEFINITION_END(NAMESPACE_SEQ)

#define BOOST_FUSION_ADAPT_STRUCT_DEFINE_PROXY_TYPE(                            \
    WRAPPED_TYPE, NAMESPACE_SEQ, NAME)                                          \
                                                                                \
    BOOST_FUSION_ADAPT_STRUCT_DEFINE_PROXY_TYPE_IMPL(                           \
        WRAPPED_TYPE, (0)NAMESPACE_SEQ, NAME)

#endif

/* proxy_type.hpp
rXSmNWzvsZn2wJdrXbnO1JvxV18sOSoaJkdryfHhtpF7fN0kn/xeRtoD0P3Z4edm/yH7cO77avGfg433nO2/ZR/OfZ9y4+3P/Vv24T6w9uEWbflO+5k1v0+d/M7Rl8597rJrG74Pp++AZ7969s3Ud7vur+3hxFNfSx9cT3qZiteznni1itd5PfFqPOpb4HLFawFLgvYTd4PtdF71APm2PFDnSttr364DPBmmwUu0v3etyRs+CLvA5+FBsE77fsti3Hd5/SX+76X4z/8l9l02bN8lseey6fZc9qzbtPsuiT2XDd9zyayjDyHMIMwjLCOsq0vsqySu//61qfT/88vLNor+v38NoPZQR7ffqBMPHTak94BBw4ZqEcBaA8gLWgPIcVkDuN+sARSZMZNLQnHq2bdOD6wBBPJcGu08QWGUPOPUta87NPo6QJrLOsADZh2gOErecejb++e4q5VHvtYBjpO+/dpCR98+Ip8Y7NhJr91Vzz7bE6pnn+MJ0rM3avaO7T09E6vphejijmrsrhOfWfzX6cSvauyuE+8r3jQ68f5ntkzrEu8m2eV+Axo9ZN9YRw852jMrUu7RdJF7FoXqIvui6CLXhOkiS29Zz9EqfKVjPy/4ObrrI+f8A3WK/+q1jMSaxX9Dp7h1Fyt+l5FLrs39/eQ+LTp+udPm5/bYgLWMouhrGfsF+6UsjL6WsU8gnr4XsO160sv2qM/Xt2BOmD/w9tJR7QAtW5PwEK0tjNSawnGwa/DaSHFsusC+4vp1gVd61L+p3zPy7WD6QsVLl3w9pEN7CDzYyCCbXr3l/72vbKD1g9dLx3aB/O69Ihtrr8nG2vfSvd2K/A6TTbTDYWs4ULa2joCnwkHwdJgDz4ZHwjlwCFwsHdynpXv7Ahxp8oFHwzeke/t2jGswi19hrvXK37/+kvLq/2sNJqH7umnXYTblGkxC93XjrMMc8CpyEmoIcwhLCKsJLZYl1mL+qmtT7f/nF+eZ6f8Gzf119p/31Zr7DxmcO1KTFc36zVhDcTxZTpy+WUOGeQcMOnSwY0I5RFdgeAe+4Zo3T3VZJ7jJrBPkm/FD9ATj1Rm4KkhnoI/y9kQ5l59SsP6849EdyMyKWDMIlL3EZc3gZuRMrSf/eHQI0pXX240i6/lWY/9eeQU/XFO1saTvr9vLnboN+IrIaRxFHyM/Ij/qJY41mH7h9enkeXvjyPq8zegiuJSRKqy3fMHPKic5UgfjDmOnu8DRwYj2vOKpy7kN0MXwl3+Vi4zzzBpUYaiMqoOYZbqzATId6vgniNAPuYf0RvvXrAo2Tr1dFU1PJKyOvnORZ76xiRGQp2F1dHk9+X8HZyVFX6dwX++IPm93X3eIPl91X3+Jfz3CfX0k/vUI93Wc6OsI7utE0dYXoq9TDLTm/483+nHF9s2v7j0ifW7ymju/nRc0n8935rdTw+a3GcHz9ALN513ipQfiERSvbT3pqR92zbeLE0/9p3u+nYJ1GELzjZ6e4vWsr7yFildPeqMVr3M96c2JFk/pzacvn7KccenyjaO/EDZ3Dp83M2d21VdwnyeHzIs3zpxY8+GQubAzDw6dA2dnBs973fUOFhPC57jh89vwuW34vFa+5MPntcxn65/LBs9jo89hzfw1dO56AKFA89TsvuFz0/jmpNHmo7MI8vUePh8Nn4Nq/hmy/8+cM2y+Gcc8c33zyoGB+eRfO5ecT3Dmju5zRme+aM8V65YTdwVyEXIJNYRZhAcJqwjJr5Hea4l5Y+JKXP+M+f+G6/+buXpOB8YV2stM01z9SI33BxKe5R91Q6xvufFsxwSgc0f/uL0NXN9eamrAl5jjEw94qsPmEu2V/9vKf0/5Oms=
*/