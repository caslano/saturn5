
// Copyright (C) 2009-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://www.boost.org/libs/functional/overloaded_function

#ifndef BOOST_FUNCTIONAL_OVERLOADED_FUNCTION_CONFIG_HPP_
#define BOOST_FUNCTIONAL_OVERLOADED_FUNCTION_CONFIG_HPP_

/** @file
@brief Change the compile-time configuration of this library.
*/

/**
@brief Specify the maximum number of arguments of the functions being
overloaded.

If this macro is left undefined by the user, it has a default value of 5
(increasing this number might increase compilation time).
When specified by the user, this macro must be a non-negative integer number.

@See @RefSect{getting_started, Getting Started},
@RefClass{boost::overloaded_function}.
*/
#ifndef BOOST_FUNCTIONAL_OVERLOADED_FUNCTION_CONFIG_ARITY_MAX 
#   define BOOST_FUNCTIONAL_OVERLOADED_FUNCTION_CONFIG_ARITY_MAX 5
#endif

/**
@brief Specify the maximum number of functions that can be overloaded.

If this macro is left undefined by the user, it has a default value of 5
(increasing this number might increase compilation time).
When defined by the user, this macro must be an integer number greater or
equal than 2 (because at least two distinct functions need to be specified in
order to define an overload).

@See @RefSect{getting_started, Getting Started},
@RefClass{boost::overloaded_function}.
*/
#ifndef BOOST_FUNCTIONAL_OVERLOADED_FUNCTION_CONFIG_OVERLOAD_MAX
#   define BOOST_FUNCTIONAL_OVERLOADED_FUNCTION_CONFIG_OVERLOAD_MAX 5
#endif
#if BOOST_FUNCTIONAL_OVERLOADED_FUNCTION_CONFIG_OVERLOAD_MAX < 2
#   error "maximum overload macro cannot be less than 2"
#endif

#endif // #include guard


/* config.hpp
PN+EnkDjSrnwHeD5nvYHGv+YC18Oz7e6SzEa+/l453vG812OBe9+ONJJL+QqNyJ/8/HRLnn79Xl8/x5iebn4QTC4/dIQJ31Hl2LS8d2rjmT8devF+wlZvoJy/zlE6i8wUHk5NH8e8xSfrxhCqXyUp+6dd3kxfL4PZfaZgXjxePkIgRHRp/P0+X4gqX9Wb3F7ePr17CHe9dk4xOUPvI/Pn1z5uhVz+ndZuTdl+iBQ2oPeefvfZ0PezV8I9uI5f3nWx1Oub4qLLtU3Kyrv+Uud4l3foBSp/5oh0zdSJm8GgkKkb1wu+qij824/cy76fMDjjwV7b7/pPH11D6m8HdFvsJ9c5O1IkfYHgtR+Ulz+Vla/PnnLu5lSx6v+Kt5/D68DXsdPBZ5erCpPl42fVl7oCvF85IXu42X+UIdK5//sPt7Xa76u+cjgvT4f8vganb3XZ7nBZR/S8W7um3f7HTB476+bBml/zZDPAwb3vCfxtzkuebnYoyo1b38XF5q/9b26u4jvHfxDQ16PIJk831zWV1Nk9eiWKvbnnn4g5g3rM/NYf4/1FbUXF91dvnQ8ZPeTzq+RfDrG5d9zad95qXmPv9Wp3sff6pi87WdHqnd7vcrj79URjy/P8fFANj7Y/nnLe5Cav/lAIdPH1/h21zPy/g7i6Udx/qJ02Xo8kqf37yeVX9elH09v1F46Xqb3977+ULv8gbGORB94gz4qD31k89eAvNs3y4j0/Ky/5P5H1r6T5H7G6N1fPBjgff5q5Vo/GvPX33J9wJT3+FaZ3nA9Ycpl/h/off5v5YpNuehrynv8JZtymf/+lHd/ZeQib55bf+/y1vL0g+V5uqzcrTw9sLTM//wp7/XGAdO7zV83+Xw5TaTjRz0o7/o/k9df1v+sbJ5QvaF/s2XyMqh/FerHmr3LOzDc36s9qVzjlc83w1csD2Fw3vWLNL9bewrrAe/+18yXu3yQ7PpgsPf+9XXJNec9f2d3z9/8Pb3H283f0+XzFepB8by8GQiMeF4y57W+9xz/Svk+FJ9/bi1pf8XFStdvvjQtjP+bubSPKu2fMx7VcXmPxwpp7+Y/1Xw+c49/rP/cEefdf6pd/jOf+k6S79ekufX5h+pr1uStb0ZaLv43LW9/vzzNu79n4/P2BxvTvPuDkzze2N77eD/H04Nae7+eucnTV7fzfj3zmKdv0wh0pYj+iqdn9ZCu56bHS8dLKzpeRP1iebf+/nv3V3PbL2Y994vz5c/+CH+EP8If4T8lBPeMig0xpusMeOtS21lj04jwnfVJOqvNjRb46b1IKSFVk9DRkGSy6G3JqYBBY7clu25EIg3sRjfGXU5HxOCtTH2CRiYEQ4Ip1WzRWa16k9FdrlzvYJ5HnFnbWIvfAWOrPsnIUyhe56WWlN9LLSm/Zy0pXuNNa8S7NPZsL2+3bGn9o6N7h3bqEx0SBVI8tpI+3m7TWWOjsBLe8H11Fn1iJoBYL4MhwtJFb7HaovHn0wQ83lHW6c22ML3VxpfT24mxdrGY3G3qbC2Xplr80CeKigGLJI+QjqZVkpTbW5dmxxaV3+fGqmBst+j6agx2HYBHPgCg994l7eRQxJbZx42z2s3mSHs8TbvyRyVrLDqtkE1vtdpdqluxoTSGcHtqPMVQ/lBK72jURsmIGEzYuZZg/Im6LiZLqgZ1kuNFeke4cPpEag3iLGgPAsFpTxnYtFpsYwEv6b/0pti/bhGYDpCmqQZS+xdKCk426RN0VnF5+jxqSceHPX4Inhfoocv07G5aPjU+ncUbFfuFN5XoTLNOnJb5CY3ZajdovB9bQJvTgnP0CUNcao+Cv7C6rEfKin5FyinoTUVJ+6+3Lt2BdfY=
*/