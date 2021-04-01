//  Boost string_algo library predicate.hpp header file  ---------------------------//

//  Copyright Pavol Droba 2002-2003.
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org/ for updates, documentation, and revision history.

#ifndef BOOST_STRING_PREDICATE_DETAIL_HPP
#define BOOST_STRING_PREDICATE_DETAIL_HPP

#include <iterator>
#include <boost/algorithm/string/find.hpp>

namespace boost {
    namespace algorithm {
        namespace detail {

//  ends_with predicate implementation ----------------------------------//

            template< 
                typename ForwardIterator1T, 
                typename ForwardIterator2T,
                typename PredicateT>
            inline bool ends_with_iter_select( 
                ForwardIterator1T Begin, 
                ForwardIterator1T End, 
                ForwardIterator2T SubBegin,
                ForwardIterator2T SubEnd,
                PredicateT Comp,
                std::bidirectional_iterator_tag)
            {
                ForwardIterator1T it=End;
                ForwardIterator2T pit=SubEnd;
                for(;it!=Begin && pit!=SubBegin;)
                {
                    if( !(Comp(*(--it),*(--pit))) )
                        return false;
                }

                return pit==SubBegin;
            }

            template< 
                typename ForwardIterator1T, 
                typename ForwardIterator2T,
                typename PredicateT>
            inline bool ends_with_iter_select( 
                ForwardIterator1T Begin, 
                ForwardIterator1T End, 
                ForwardIterator2T SubBegin,
                ForwardIterator2T SubEnd,
                PredicateT Comp,
                std::forward_iterator_tag)
            {
                if ( SubBegin==SubEnd )
                {
                    // empty subsequence check
                    return true;
                }

                iterator_range<ForwardIterator1T> Result
                    =last_finder( 
                        ::boost::make_iterator_range(SubBegin, SubEnd),
                        Comp)(Begin, End);

                return !Result.empty() && Result.end()==End;
            }

        } // namespace detail
    } // namespace algorithm
} // namespace boost


#endif  // BOOST_STRING_PREDICATE_DETAIL_HPP

/* predicate.hpp
IMyg6AAHu3cY9odEXwDJGrH99AklsBpNSG4gBcp7G6YPeNU7YWhfsPGIpTvlN0iYaG20xQRwGOuH8Btk74TTIHaQDlFrO1XTZCAeCn2wRn/qYsxv4NKzptx5DOYG6kaczptCR6voQabo2Y3I2eW4X9vmlj8sFptALhffe3Zoqx4jNYRsqhgatmKsAXqLIQNYggII7lV8GNCvb9E9Hxb36MxEEya/COqzP+Ia7dLDkLH6AE/zhBbxq0x3AaEAReGjsBtCvNiq3fHY/qn2qY+s8UFx0JDvFLHB8QOO0Myk1i5bLpjWdLHqa5twCb14P7qY/DMsziXLfnd9is/7H8q5iAX9pjf6dA/p0Y4EYM2IOBPRMeBzPosXUMKSwYOdjzVS360NQDegCkkdHAXQhV04FfmH181Hn/8bIzNNEMYBYWqnEsiwpQIHDkT8yrq0TylIlNNbJ0PmuKm8EAGCDPbNujRh9koM2Q8QG0bVZqBk9PYpxSKgBZrnKetUf2q90uWHqaLpi2XkHSW+mCQdMQOXb+kaCuTrsM69FlpJf48HpiV+XNxYz97SWe+nWg==
*/