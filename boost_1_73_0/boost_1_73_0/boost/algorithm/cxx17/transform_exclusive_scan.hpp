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
WfYyn26Xll7qUy3docx30okpeU+ot72oVpdtXTXUhLHg5aW3KoEoqYIKu6U7v5fFHoJ0ctVDbpAeD2oAcvcez19bPrSlkxBf6eqY6TKkJEOVKZHVu/PSL1C+TUqJrLtRpesqMUnkfXDVCdsbcy4mnV+g07bmR2gMqxWZdljh6jzPJnU2JJeWDnqpazd0yrdfdWCbUMeHPIR0itKu/h+lkRKz6JY95jj7BoCmuu/deLzgnzAfT5KfUFJpHOXNQe730ugL4gu4m2tkGSfpBNg6kTB5MMKkViQRGWtt/xRwSTlT9lAIt+x3X1KCF6zRaLmDUjqIN2zVy8kKHuvlYEO7KSKJOaREjCUbrft4uahbJflFaqsvU1GWsqhPqS2lyA8/vf/07oeq9Ado2evWVFbXX3ejzq/MLSWp9Ai3qkhXLa00HgL8HLVuSxplVWUR7ffhcN9gpzLlplq3/4TtU9OG4hu5cUzd9TwLXehKyztbgshhvIoexwIecN9Pkh2y1X2/sjZt+xdKMF/Odggw33Wu8dKOAZMhhhv3VUXxoPWp2HxORTodx9y2WuimkFG36LsCDL5ppSu1FLSoI9XS7LkSuLNvm1V9scmKRqQyCOfgx07ril4o27ydBNMxyy3fR79GYd5m3pocN71iZMnF
*/