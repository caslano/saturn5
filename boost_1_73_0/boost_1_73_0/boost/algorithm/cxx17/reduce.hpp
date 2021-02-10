/*
   Copyright (c) Marshall Clow 2017.

   Distributed under the Boost Software License, Version 1.0. (See accompanying
   file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
*/

/// \file  reduce.hpp
/// \brief Combine the elements of a sequence into a single value
/// \author Marshall Clow

#ifndef BOOST_ALGORITHM_REDUCE_HPP
#define BOOST_ALGORITHM_REDUCE_HPP

#include <functional>     // for std::plus
#include <iterator>       // for std::iterator_traits

#include <boost/config.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/value_type.hpp>

namespace boost { namespace algorithm {

template<class InputIterator, class T, class BinaryOperation>
T reduce(InputIterator first, InputIterator last, T init, BinaryOperation bOp)
{
    ;
    for (; first != last; ++first)
        init = bOp(init, *first);
    return init;
}

template<class InputIterator, class T>
T reduce(InputIterator first, InputIterator last, T init)
{
	typedef typename std::iterator_traits<InputIterator>::value_type VT;
    return boost::algorithm::reduce(first, last, init, std::plus<VT>());
}

template<class InputIterator>
typename std::iterator_traits<InputIterator>::value_type
reduce(InputIterator first, InputIterator last)
{
    return boost::algorithm::reduce(first, last,
       typename std::iterator_traits<InputIterator>::value_type());
}

template<class Range>
typename boost::range_value<Range>::type
reduce(const Range &r)
{
    return boost::algorithm::reduce(boost::begin(r), boost::end(r));
}

//	Not sure that this won't be ambiguous (1)
template<class Range, class T>
T reduce(const Range &r, T init)
{
    return boost::algorithm::reduce(boost::begin (r), boost::end (r), init);
}


//	Not sure that this won't be ambiguous (2)
template<class Range, class T, class BinaryOperation>
T reduce(const Range &r, T init, BinaryOperation bOp)
{
    return boost::algorithm::reduce(boost::begin(r), boost::end(r), init, bOp);
}

}} // namespace boost and algorithm

#endif // BOOST_ALGORITHM_REDUCE_HPP

/* reduce.hpp
3OfbmJ0bpC3hKbJR7q6IRuqY6AcXyGqiF5FRemQg0Y8owXIBRSsLOrDijGFt7nQQc9pK8F3qzIhhjyHn0X2YJkzFzKaR9JPaYJXPNZ1jjT9q94CO7ehUkZIsEVcORx6hBGGCUXJOSmx3f9ypJdKjUFmB+uImTqMfbmQx0O2W8ENpJY0J2F37QPY5IE4ooVAQZpElrG8pa9oWiXcEZzxTer3fbfj/P+2YN5bCMi1tXCuxv83FF8pdyAItw4U6rDwhVCd+lV5CimcSFmXFRnlt9+f8xH9IRFXyxG67vrG7LttbS+CVclgSaDhcTwfl2lfwu9TQMZcsSU+b3bHZY7d7BOKu2X9RCwu9R+1bBYrkbdY4nKXsg60VGNxTgpo22Gaxa9qZ9ntgCNEFdK+GRDcABaxuR7M7k/V25pa7IEH8PgdUDHflVWbxaR77XFprV4578DGPLcVzbkpmvIlcWFVJZEhqZdFXUKvzgEyhTA3MQ0Ylt5z4C1ZccptajORMVsliK/lIJThVrZYBL1ax0v9Fq60LgcfpJlfWsE0bJg2i70jNWEdm1D0SHjYRS5oQB4bS3R0CKvNBGf2V17SIStghRwoJd6hhWQ0McAnZQEoyNmB0w6x7TG4ADBbCsp4l1+qgSZ5DJ5/XbN2EUnWx
*/