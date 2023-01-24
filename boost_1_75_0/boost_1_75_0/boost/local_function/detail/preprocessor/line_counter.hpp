
// Copyright (C) 2009-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://www.boost.org/libs/local_function

#ifndef BOOST_LOCAL_FUNCTION_DETAIL_PP_LINE_COUNTER_HPP_
#define BOOST_LOCAL_FUNCTION_DETAIL_PP_LINE_COUNTER_HPP_

#include <boost/config.hpp>

// PUBLIC //

// MSVC has problems expanding __LINE__ so use (the non standard) __COUNTER__.
#ifdef BOOST_MSVC
#   define BOOST_LOCAL_FUNCTION_DETAIL_PP_LINE_COUNTER __COUNTER__
#else
#   define BOOST_LOCAL_FUNCTION_DETAIL_PP_LINE_COUNTER __LINE__
#endif

#endif // #include guard


/* line_counter.hpp
eD8/b1GQL6KNanLgN7PZRXNto5YllZjzmCyht89En0+i717BcfEhY5AMQyB9gXytpjKUmEkiYWpLsQQndvKgpXkZcPik0TfnqIY0DM5uNs8cJxhKfhvpcIwMWmMe+JIBbcnqa0oINJcSEaX0GK1x5om38bwKAasKA65p+Q354aB7yd5p6so5gl2YGe3XaT5V2MgdQgzYu39cBbv8m6VE+a7X1vLHUXiuBhW1/uiU3bGcup3sPM2ag705dvf+LCaYVhmevL1qInwaJK17WkETse1MugKMwOD/lqvuGSMy0SB/8+bNNNx/yVVT/OfyyF8Nnf+RoibUtsFVhwCvGJXz7lP21Xuppk+jugLfrkww6x7CtxX1f6Rsbm82NQCYtXKqlfYvYig89xD6Reu30RIrzEr03BdgbTVH+KZb3OeFYrxwXnxSKdtfFWiwJSizpaQkntg5WR1qvRM8T/e6fTrX0Pc9P8lwpA/Krn1jJ88cMqA2GI2J9xc41QPoz4iICAv3LfLnkg22fsJHW5mDIcl72lzN4Jeiez38pvNeGMZjz8AQEiI+730Ku1YOillwmIHKIVCNtPM1cBpkOzrc+ctylIgP+O46TIQQtaxTJ5Yl8AtC3FAYE5ghyeg9TYJVPxLJysSH52ZRG62J9J9AJar5ARcvwL62mWt9k4/uEMd1pOvo8jSf1xoyuX+amHno1YbNg/1b+t25tWy281Fa
*/