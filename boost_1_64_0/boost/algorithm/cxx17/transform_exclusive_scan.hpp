/*
   Copyright (c) Marshall Clow 2017.

   Distributed under the Boost Software License, Version 1.0. (See accompanying
   file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
*/

/// \file  transform_exclusive_scan.hpp
/// \brief ????
/// \author Marshall Clow

#ifndef BOOST_ALGORITHM_TRANSFORM_EXCLUSIVE_SCAN_HPP
#define BOOST_ALGORITHM_TRANSFORM_EXCLUSIVE_SCAN_HPP

#include <functional>     // for std::plus
#include <iterator>       // for std::iterator_traits

#include <boost/config.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/value_type.hpp>

namespace boost { namespace algorithm {

template<class InputIterator, class OutputIterator, class T,
         class BinaryOperation, class UnaryOperation>
OutputIterator transform_exclusive_scan(InputIterator first, InputIterator last,
                                        OutputIterator result, T init,
                                        BinaryOperation bOp, UnaryOperation uOp)
{
    if (first != last)
    {
        T saved = init;
        do
        {
            init = bOp(init, uOp(*first));
            *result = saved;
            saved = init;
            ++result;
        } while (++first != last);
    }
    return result;
}

}} // namespace boost and algorithm

#endif // BOOST_ALGORITHM_TRANSFORM_EXCLUSIVE_SCAN_HPP

/* transform_exclusive_scan.hpp
tovGAu+f1PnW779rio++ESwntHgQ/WQtydZgE4XxjJuh8YvCyZJfVGZKJvV7Vic187MD6j9E5j0gbdbMUPhN7sbsJd/duQfOMzIZZ+0KF993/zCdwK8D+OsleHIzmpzJVexAFQK6+w7+2QuFmqt9aLmQk8gyiZGkbCr/bkbAYaJS2xW7+4mFv9YM1OoLrhxO4nIGkQiMf5vno69Fb+rn7/TJL4UCLfD+8m95mq0yrjN+j4ML6z3WS4v/MbBAPG88Lpes7SyBJOtUNjrlsyrxM/PIIrccVmw7cHQTszqd/20cL7z2weEN1OFt7Q94iSHD23lrUHgWHd5jNwDetuQLw9Pmq/BWn/m6a4L/fFU1vcB8ZQfvT79btf60RldEZgj9kfC+uyUovFdv0eDFdwC82o6hwlsRHN4IHd5taYD3bMjwRgWHN1SHN47wIzcEeNr8m27xmf/j4/znH84n55//dZOC9uelSVp/FtL4yjpcuD8q/geHN1OHl5FE+B8yvPbB4VVN1ODlWgn/Q4a3c2JwfNPhvZxJ+N/+wvB0/J/oM/8f3OI//x2vuBD+X6g/z4MJi6GuC/dHxf+bg8JrrsN7pi/gefJDhbciOLxPb9bgTe0BeK+GAE+brxE3+8zXC5P85+vxuAvMV3zw/lj0/hy+Gv1pG0J/VPyfEBTekgkavINXAd7WuaHCcwWHd7UOr2cXwFsSMrz2weG11eGlEH50CQGeNv8fjPeZ/6sn+s//m5YLzP+j44P25+7xWn+cNL5n5ly4Pyr+B4fXT4cXk0j4HzK878YFhff4OA1eYh/C/9mhwlsRHJ5Fh7egN+F/KPDGMv+X8NLKAIw9Mim+C4CxEg4Q5UNusb/AtPBb5vItvVVy/xt7Yfjf3RQIf3og/NtT/OCPDhn+oxI+OSktx29ugn4Uqz/SVe8laqf+pN1zkzZpS4F24kDH8zYq22sfZDztbgoYzzM9/MZzX8dQx7PuxkD4h24MgH/tGD/4HUKGPyUI/OcD4f8wyA9+ZYdQ4UfceOnrcc2N2nqQZkcM6xDCejw6NnA8vxwbMJ5jo/3Gc7x9qOPpHgT+sTGB6z3BD/5jIcPfOSYQ/n2B8K+5ww9+j5Dhu4LAnxMIf2RLP/i7kkKFHz/m0td79WhtvZ+AKk3ckhTCeq8YHTieB0YHjCfrJr/xNAh5PNlB4PcPhH9qoB/8318dKvyDo4L0f1QA/Mf96W9AyPCLgsA/NjIAfrQ//K/ahQq/fRD4fwyE/0eHP/8LGf66kYHwrwmcn72j/ODvmRIq/ClB4O8L7P9HSX7w54UMP2LkpdPDoREaPdSB68A5KwR6eHREEP43ImA8llS/8aycHOp4ugeBf1Mg/N/m+sG3hwx/5/BA+I0D4d9u84Mv8kKF7xp+6evxm+HaetwLzY2YmxfCekQEGU/Y8IDx3Oo/Xwkhj2fFsED4tw4LXG9/+aD01lDhZweBfzw3AP5vpvrBHxsy/IO5gfA/D4T/XhM/+CduCRV+Ue6lr/c1udp6m4G/ovCWENY7Psh4Tg0NGM/fRviNJznk8bwxNBD+XwPhT7f6wV8/KVT4o4LAPzUkAH6kP/1NCxn+d0OC4Gsg/Huy/OCbQ4b/aBD4LQPht/SHv3LiheGzv7CqD+8yxBsvoo5s2KQSX3/6hQxcxe8mq8+unBBHOuNrkUe++Y4837KIwRFDLhP2jtSlDM6SkY0v7t0Y3/49nBNC/yI76f0bEkL/fpl7+fp31BlC/+7O0/v355QL9+83t/y4/qnx72XPlNg7xuE9jLg+3vcwxo/jFzAmQ5LBrzUT+NdoR8jvYZzjfiWV458MVqO07OVALYec5G/YRZpm/DJTN1Ruh4s=
*/