//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_EXPERIMENTAL_SORT_BY_TRANSFORM_HPP
#define BOOST_COMPUTE_EXPERIMENTAL_SORT_BY_TRANSFORM_HPP

#include <iterator>

#include <boost/compute/algorithm/sort_by_key.hpp>
#include <boost/compute/algorithm/transform.hpp>
#include <boost/compute/container/vector.hpp>
#include <boost/compute/detail/iterator_range_size.hpp>
#include <boost/compute/type_traits/result_of.hpp>

namespace boost {
namespace compute {
namespace experimental {

template<class Iterator, class Transform, class Compare>
inline void sort_by_transform(Iterator first,
                              Iterator last,
                              Transform transform,
                              Compare compare,
                              command_queue &queue = system::default_queue())
{
    typedef typename std::iterator_traits<Iterator>::value_type value_type;
    typedef typename boost::compute::result_of<Transform(value_type)>::type key_type;

    size_t n = detail::iterator_range_size(first, last);
    if(n < 2){
        return;
    }

    const context &context = queue.get_context();

    ::boost::compute::vector<key_type> keys(n, context);

    ::boost::compute::transform(
        first,
        last,
        keys.begin(),
        transform,
        queue
    );

    ::boost::compute::sort_by_key(
        keys.begin(),
        keys.end(),
        first,
        compare,
        queue
    );
}

} // end experimental namespace
} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_EXPERIMENTAL_SORT_BY_TRANSFORM_HPP

/* sort_by_transform.hpp
9RvbV6ruw5UBQnD2zHr7l9P6RCahsRvvt+bgVF99de2FwuGViQnWKS1p9Wm8/aO82Xa8zs5TfF69LW/tOp831463Zn2Q33w73trO4PnHvOsDDWETsT0PS2Pkis5x5kSGGMTuoc5Tiqc5CRRpmuMVPtmWd+q69Vrfroi3Zm3nOpff2jXrhJe053UWT1mvcm/PW1M8tVPl1J5HTbVc86m2vHWrT9H2Ftvz1qMaurfvHJWttaN1YhefsxjOC3uVe7rcPfhonEmwR72mGCPOnoEq44bxfMCsh0/ixsWO/OsTOo/r/eJiuU71g/XN5N1yj1oGZYkNxvcy/cVf4TrNeukf8sjnkJm/Tqj1s2Ly1m+2KHZpeWrSx2YeabG9UzSLUZxYQ+To7msNAkiY+2Ts+LbDKiOju6sqj+8G11f7ZXVsS7H0tRt6pqJY4UKHERYxTvrvOCURRgA3ysxI9wHftlhxfKe/b7D4lxDrbPlJ7aOOr4U4KbDGBgvfycF1YNE9Bj/J49ETrOdJ/PDLiMOYkXgxz8xvQ5zdiLxs6M17DlE5pFNgtmf5OuDJyfWLlH1RjNE3fCS+LWVxK+eqzD+zHEvRNctGv8chdDf+HsPxEPOHLCnjmxEHGY2y+4bJofriAY9DCG28PdRzPwuxqof1DvrY9KABE/lEmG3YpOT7B8Vb3erHDS4eIhjy44aZxF1HDnwkrz/q9TiveWcjhMNBPP1Cd50hqlUJvKToDp+XxjgDp4fXXpnBGTAVX3htjDNQenj/m2KcAdLDe6+N8d3TE0P63KA45PAJQJVrV6+9ztJ/6hLMtNQ5xprC8u6t32Bx3X+m5X0hxdKle43Lal/0rjOS+/ZXv8lhlfL08GQzfg1ipoUcnP/Yzmqkzzu+knLszbpHz7/Of9yka4Hfspjqusae33NY5GcbwfUgVmk8LsX89Rjpp+0exgrigVToE2JbileBgj1W9R0OczGQ+tk5D9OBVfNtCK4xkvRJn2LWHnS98wcWw5b9mHhul/WV2Kq/vyW5Y4lcj/Mq7HQYswEvju44/ZD0Om9ktXZmd7MxsXv7hr7uzbp/IOawi7P7zO7tQOpjyd9yfNe2XWz7Altn1h+oV1X8B/el15nI+Ncf7/g0Rn0s6/GWv29gbLpMOMKaq+iFwy4ZrY5EzyBqDmsGAQwwgU/6VwvbeUZpS/eWaO957799bM/UJJ5JbMIsjbB0q3SQ9yKfgzZ6frfjLhFGvfx3K2oOxzjsgLdfxstTwMymDTv6/J2zuhdvvujwaOes8dr2SMdxu2e1bjNrHBbsntX9mRscLtgBmRudKdhku7LnexzH7ZLVsarBHlkw3SSLzCQm7F1lwLq39/Wc0bMJNe3ddk7Ppp5uu0NZ5wrteOQXzIHa8ugPfw950qrvlg2b5C0CtsSbbpHHxSHO7Fpj8ikfi/ayhhiRftE+mWvtklc/GfKonLfGUhHsjNEJHKj3fHe2KlgPz590jXmfXN+ZLqRrfoX9grHncJpIT+OYwudTbEdpE1bOmn8PT7zSJg2J7l2Wx6Fwo5yu3HxoltfXSR7HDl4IR+fFR9/V8rpTRSsPb+ZZmlNq5R2Ty3PqqXs4n740l4eirrb7uYddnh3PFy5B6dhkknLdxpYDLs/krY63vTxUHk2q29MtnJZY9POcvzafa1W8eJKLe96Wz0u1CAfJFz/ObVyWz/ffyZxplyddAzzQ6XzH9cpDX0fpHRHW2eUDpSGeUdm1qbu4+s4e/J602qPDapvPz/CbGpDp194rc3nSr678hXxeWm5Cx6YmJ/yZj+Tz9w5MjUolPH7towfhU0iRLY17PH7hY/+Fb+vjZF78r/zJqdE9SNCTefLx/3I=
*/