//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_REMOVE_HPP
#define BOOST_COMPUTE_ALGORITHM_REMOVE_HPP

#include <boost/static_assert.hpp>

#include <boost/compute/lambda.hpp>
#include <boost/compute/system.hpp>
#include <boost/compute/algorithm/remove_if.hpp>
#include <boost/compute/type_traits/vector_size.hpp>
#include <boost/compute/type_traits/is_device_iterator.hpp>

namespace boost {
namespace compute {

/// Removes each element equal to \p value in the range [\p first,
/// \p last).
///
/// Space complexity: \Omega(3n)
///
/// \see remove_if()
template<class Iterator, class T>
inline Iterator remove(Iterator first,
                       Iterator last,
                       const T &value,
                       command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<Iterator>::value);
    typedef typename std::iterator_traits<Iterator>::value_type value_type;

    using ::boost::compute::_1;
    using ::boost::compute::lambda::all;

    if(vector_size<value_type>::value == 1){
        return ::boost::compute::remove_if(first,
                                           last,
                                           _1 == value,
                                           queue);
    }
    else {
        return ::boost::compute::remove_if(first,
                                           last,
                                           all(_1 == value),
                                           queue);
    }
}

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_REMOVE_HPP

/* remove.hpp
7B2M3soVUrZNVrypY86diK+p47acCBE416uvhLs++jLqZ56vkX1f1IfmvKf3pB4a2acx/JfqeJ6stgNtvZqUvkHTDe2t+k41DK6Hkvup1slGZ9j7Uva2NXlj/0rKGG8fRT3OoW0+tHaWfA4xdX0DT8O9qaXmpq6LaXFHne1jmTNXU1m7FAP7xwVNipo9/EbXNFVYbkLnkvVPvWVN06G2LeuOql3WNy1zWd/0SoT1TW+6rG9aG+qWWeO23uRj1jzJvdlY3PS+Vl1qt4ub3IPilmLcqA8Nl23cpI4cZxWO0PPwJkahM0fZhLDZieY3z/GD5/J7J/3uUgnfMkp//zT+MP09REthS3nOuK+HM+EHUn96ZqDYN/lOtXOs3+wrNFwwnWTtG/yAYVtgp+CSQ19uaR8TeU2dyWeClSZ27k6xf+WL471hb8y9PJty7G7WWruQ36Ce4b9dpN1f6vMciZcetbtvnP4OBdLOMroAD2/ht99jn43WqkQ9W22qhPnV9y4asb63b9e4plzEJRz2dyTuC3Yza4Ydvr6Ps+GknadJWhlRgfxWtxC7Hc2zUN47TDrLSSfJ7kfdBH+39Hp1vR/9MPy3Q655ImGflnAP+s5D69ZtdlXwdyosDfpt+Hlx5jf7TAnXKcrv/6k+t+if5hm1f01doYcr3rwzldWkHbUc91jfXNOXyqWuuHu1jDFir8R+jBWafmZx8GzDfpL+zkbnZ47Yb1N7IM1kib8g8DyR+1F+17Sf3UVv7GIHw5CHlnEe7CxhePaJPdA3z7c74xYez9J418J2Eq6BFVY3em3YxL/K5VrdyzouScuqfa5Y7CnaB3lLFHtzex+0yl1AnTnKHOzjGq6VLWFcynwdHCnX0iAsDfy13jLEf5rlVvZ5cLT470qeUmcaPo97cdc6P8PP/wc8w8PXqK6P8LxeIG7at/TZbNxcwuHm7dt02bf5m+xvbDzz27t+u6nj4kMGn2rbpw1+wdu3WZd9m9k+fc/Xb91Y/jjQos10/TvJig7LR+AUuBBeBB+Fd8DH4UL4DFwMl8Dn4dPwFfgs3AqXwl/U3t7GDntBv31/+Bw8FD4PK+AyeLXaK+GL8Da4HN4JV8Cn4OtwKVwJn4er4Ovqvha+A9fDd2EKZVoDs6Dfng0/gEPhZ7ACrodXq70SfgXvghvhY3AzXAy/hc/B7+Br8Hu4Bm6Fm+BP0Kb//QrbwF9ghtoHqf1wtR8Lf4OToG2TL7TgQrVXQx9cCqPg8zAavgd3hh/CRnADbAg3wcZwC2wCv4FxMCEaO0yBcbCn2g9U+1AYD4+BCfAS2BQuUHsVTIQLYUu4EraC/n5UGXjn0fdG+pG8Q14BLT3z0c/OsLvah8G94fkwA86DXWE13Aeugt3hWtgD/gj3hf60+8J42BumwP4wFQ6Ao+BAeCwcBMfBIfA6eAi8CQ6Fd8BD4b1wBHwAHg4XwpGwGubBZ+BRcA3Mhz/CcfBXeAKMor0LYSw8EabCyTADngR7wSKYC0+Gw+FUOBueBi+DFdqfzoavwHPgaig6P+EF8F14IfwQztR+NgtugZfCJlE84+FecC7sCq+HubASLvL2TQf2Tf+r9ky/spk905u9dTOeeOKJJ5544oknnvyzZQfN/xfkb6f9/+1C9P9t0O/W9rr/X841wH9tEzMXQr7bngsZbGt4UnGf6zD+rvv6c4P+zvF49S8M+ut5XToeWocz1mRs0WX8M8tFn1y2yzhnjmNM07nH4ULZ4zBocdbtg6zMOTOWdckvzX6+8z9zjwPl0DqUthbZCdMnTP9YIkyAybAFbAFbqT0FtoTtIux94LvS7H9otsX7jvPEE0888cQTTzzxxBNP/nuyg74=
*/