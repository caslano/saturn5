//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_SWAP_RANGES_HPP
#define BOOST_COMPUTE_ALGORITHM_SWAP_RANGES_HPP

#include <boost/static_assert.hpp>

#include <boost/compute/system.hpp>
#include <boost/compute/command_queue.hpp>
#include <boost/compute/algorithm/copy.hpp>
#include <boost/compute/container/vector.hpp>
#include <boost/compute/type_traits/is_device_iterator.hpp>

namespace boost {
namespace compute {

/// Swaps the elements in the range [\p first1, \p last1) with the
/// elements in the range beginning at \p first2.
///
/// Space complexity: \Omega(distance(\p first1, \p last1))
template<class Iterator1, class Iterator2>
inline Iterator2 swap_ranges(Iterator1 first1,
                             Iterator1 last1,
                             Iterator2 first2,
                             command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<Iterator1>::value);
    BOOST_STATIC_ASSERT(is_device_iterator<Iterator2>::value);

    typedef typename std::iterator_traits<Iterator1>::value_type value_type;

    Iterator2 last2 = first2 + std::distance(first1, last1);

    ::boost::compute::vector<value_type> tmp(first1, last1, queue);
    ::boost::compute::copy(first2, last2, first1, queue);
    ::boost::compute::copy(tmp.begin(), tmp.end(), first2, queue);

    return last2;
}

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_SWAP_RANGES_HPP

/* swap_ranges.hpp
o5ynMMZ59dLp9730W8k6fpFWJ1hHpnK+jf24Kg3GkF3X/ghT+5uqox5nKHtZszvI+ctjLF6O1+zbjQXdefYdxjJrMEZx+bozlNLGEmUYo7ziunmpZCzjRff7H1pvGXWpZSxtLfOrbyw1zlyaKGf37JhiLDSV692vXMq78z/VVpV9e8RYyhqyx5XfeebSRXV0ZW09jMWc9r1VRzn2bYBy9n//K/0a8lo8VHazqdUo5XyQ2j+vnM+wtomK25n9mGos/W/6zpJWk7lnEsYime78z1h4N9kS9aMd2XL5nmCMN1TbcdbxtvRzz3UfqI5x1GCNfC9Sqw2yy0JNtyiX3sxlm/rh/iZp561euvO/W7lQq0OKO5vXq2PSdBx1Pq0eVXLnf8aSY2n3nXx70O5nsZ2s4zfVcZBa/aH83LX9mlgzsv+0nvu8lS1k/ZhLllssB69r+Y3Ft3B2C8nOndEWM5b6LPW701igLPUrJzabce82ll7Dnf8pxkT2PGwsNId7q56xzKeYX2PlUoH3shbGUqZzXlop7mTGeEi+OZhfe8Vdx5l8TOuNYi6djUWrUoPuilGOPX/KWNBdX/or7t1kz2i9xuz5EMXtS01HGkt+T/3GSr/XWEdcdWRhvS8ol7GMO1NxN5DNkc4TyOYrlzzUebH6u4nz95pq68EerVQufbKDvWUsNoG1vW8sbRDtPjYWdn87st5Yhttvm1VbR/Z8q9aby37sUM5v8HqwV3ZOg3TV4c4Oj0r7g2SnZHecc3BO/bjKflyQ73Syn1THRbJf1Q/33Pm7sYSb+79V71TWdkMx3O+vZi1nufxCu1zGku59cj5jKe9T54LGMk9zhopqvUPMuZSx8CVqHzIW2E5N7zIW+50xqhhLdTNZU8zNeF3FcJ9JGsluEn2bK24NspbG0gqRPah63dl/O603gVp1MJYxndp3Mha8xnq7KcZCrtfLWCLMfvQzFmrtzv8UYzl1jqlHh9z53631eI0Yox4V4HV8guwmML8pqvcI+zbDWHQta5stuzu43svq+e3M+RXpfIMztEy5nGDfVqjeatT+TfXyd/f//xlL/4r5fSQNupKtU4ytXO9T1buDcdPEdtLuS9U2gXXsUR0NyA4ql7vIjmh257nf/9B6h5nf11qvCuN+q9kIcTZ+vLUvud4l5XyOc3BF9bpzrr+ki3tG/1d2rRgjS3mbZ/fZOaexxHhqf5uxdPfd5KCxqPuMWES+3TiTJY1lzqdvWWORCtSlorHYy5yXe4wFv6DONRR3C3Wpo7hPMG5DxXXf62tmLNmWutxnLK0l98wDitE3CNbWWMD5PipdfiHrqPW2sb9PKj/3bjGqet33I/oqv6rs79OK8RnreNZYxhzaDVfO55nzc9LvBmOMF2vGOZisXH5jftNldxfreMlYPDd7Ps9Yiv///4yFy7LnS6WLP/9TjPuZy2pp9Q/rfVf1dmKMVPnGc4B9olxCzHmT9HuPM/S51ivgzv+UXwdqsFu+V935n9gjXO8rzcYXjHtCMdwcnFXOaxj3G7H/GPcH6exyuai9+g51uawZX8kYf8rO7bd/lPMD1DlQQd8T5NznMJbRk9f7vMZi7lpSwFjqYM5fYWNpFd35n7G4+123MsaCTqsKxgILmHNlY5n72fPqxkJv0be24nZgbQ1UhzujbaoYq9zvf8h3JH1by25pFrA2yjk75yAiDRrS7gmt14l2XY2lV+f9sqfy+5az28fYiem0Gyj92lOXwepbMV4nhxkLOzZa+Z2kBuOMRVZQv0nSdDF9pylGqvv9X9mNp+9c1eviLlQMx141Ft3EXJKqzT13rhJ7hDHeUYy11PlDred+P2qt4ro6NspuNdf7TL0=
*/