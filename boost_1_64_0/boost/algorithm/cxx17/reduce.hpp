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
nCzbvKu6Cb74M4L+tGRfPEALvySRPIB63051KWLx+hxlK42YTb3bA+U1ir/TqFP8WoNG8XSFxc9dfghiJdLPj8BJqMacgyHmoKsiCjuP1qF7ZIdiqonZMPER4f8mHWQVqf7YDVUEffYp4oYH0vcT2SiQr9LdMmkJUXanpLu/ge7qxMqJTHcFszW6u6pCo7skXI7UdHqb9fIco2UCD2MpfgMmw8oHLEAStwKKlOzeRpdYeS+NgXJ/fjr8YPY8v5qj20P8AYr5leH5rKHdkIXvifky6Czbc3jf/u+r2pXcQTPwdzakGX+z15rnHO1h71NRP3GOVxSvFko/dYfovHqG2sBROcVXcAPvoIFwcXoCv68kZxKsgpAtN20HP8mKyeeLU7EKegnVAC7VAaM4/GWcXtzRZ7/4NUpAtHEiH5J1Bfg1aQ88FRmfLvzEUdJTVwCN5RXkG1Rvk0ozur5YNEVa3hZ+Flbz4eZL/vN9ZdQyW12D2Yl8/N1IW32mgR/e6ssofd3q29W5WSvn5rsZNDdv8+R/Op7nxucFT9IasKbrvrMeVjyv5sdPaNLsbPC3VPfia9iX9wTLQ0xeNH6+u+ICAILXKWnnWBNmoJfhZ+NYSiRzMyPKVfzQqZURJV43eLV7+xGAMv1meFGmE3rN5YE33hp6owDtCGOIl/9t0hD4tSp0u2b6WCZCSYpda70VSLsYmSR7ReO0Lt0oUzKPrwtzXcmHNvcYsxjvW4IZSZQa1yit7HJ4SGaqguQHd2q6prVrvbqmwhswc3XUneFmEYfjq64bumOhDPx8s4xxT7d2hf2a5tOzc/P54gbzgNA2NBN2cTRDXr5a2oJ+CJ9GsqGSEMvvqKfEAhPOpCQL6+34/Kjq7aKUgay3I5uoLZDMnspgyexVjufOIoE8S2dqXYTBkN5FZV3N3s2X5Q/2XGN4wxTP3aHN2PJyfcZmsR34Po4Ns8Oy7AgjczS9JVXK5wJcr4EMmtwjTak35GhXhC4r0HraNKk2iDeS2uAOqTa4Wwy8UaVLCYTFJIwPJzm26aLOTIRBF83riRtVZ5N5W3otiHPN6LUg2TWVZrUr5gITzG5tquPxiDtZ0F0BjxPcXkuvFDFzUyQZAXbzLYvq/cFcUS5VLzcQ5dL2k0a0AhZXt3j4+bGbZIgiiNhne/GCp05dLqWDyYtYggQoug4sVblJNz2k0ZZevJg75Fm/5U+u5Tmf/9MMXtbjeJcwzKHUSec1EnMGJULXQxKQiJwqlVYJGk0GGu3uZs+nKT7lwoKUuwTDfvX8O8Pn/Jse5Pzrky8WBDn/Tvfmb+8R5Pzrk1/ZL8j51ye/cZD2i3zyn5sU5Pzrkz99UGB+tk9+Mvp/nvVqqRYFq7LScu0Bk80fBmpKnUV3N5Vk3wO64uvZbHl9utGg3yDPBLdhDazvdWvBXDOX33ujeufNsssS3AwMANw9MzW4K1W4WfJAeZddGWOm36Mm8++pOsAuKsBiaYSSA2BxhvyxAKbowGaowI7buEwnAIuj3wPHM5m20IF9PkcCy7jxXM53P/kl1Dn07w9PU88i5XIZML6X78T4WCqueEl2u5mNu11fFb+b8saN093qQ/Wq99P/B7aforefpbb/WNa52/9hlm/7z4TSvhr/4zYvvl7jOJc/7EyU0qUA0iW2c+ZBYzbMTGYlX6yDzXieyW6MVEw+PVOMPj9CkTdSmf5lS448IUM6kLYSrbTggISi2K5fD7WDNGpT1tHgp+cyosXZjdeRVYzJXtKWbgKupx8R9l5t8xm3R8zFeWiqKo5tkUJk2RQSx8ohju0Xvxl+ed+DV/WfU3341Zxzza9lauD6366v/wp1/a1B1l8zWGEsePI=
*/