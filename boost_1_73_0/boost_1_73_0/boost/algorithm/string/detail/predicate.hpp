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
DcwfkzBdBMSbhX7qhZQ8zSeTxYWnm7qWykAhFXjCTMlb9gvWlMZw4CznSt9fa8yj6CHwiVuk5WZSvpbcyU2eYxql3iNdu/msMQdemTJjppQVHLk5yFxDo8tqD5k61UY6ZBfBnH7poQJY5NMIByHqrL/Ykql842pqiyfXHy+D0O+rW2REfUnjwfdoyq1tDf4hdyPMlU+jmAbRlvQFXrJGiZQzfUplbZ3RL+DFAWRMCAzCgRkQ3FifsGew5wbKCu08ti5O2E42BvhHqY218aJg89PR1dzgixeHu6soXvtJv6Az9rkTB8ua2edY5LazfX0PW2n4uXxzKO1GeAVM6K9gt3lCwsdpconJN0uNZUqIs447XA7BYOMNardIv/ZrVrgYsizyPyxyTSNj3obBrH0+Z6VPnk5FubNtvfQZCiWP7ZsWNNKpuAk2nYzbJ/je781v2jlu9mnk461Pk3m/xIoblUHNFKbVwYhif0tIaDsapWHkLXDkbJfBqi+CzZQgJMtx3FRFuf9seVm176OaV6gCO5a98ip3rBN7CfEXHu1sPGeYR1sYnhMHIRr0F4Feex2UJFolPiHpxqfDM7RrShy5WC7y9zi8tU0kV06RP8/ubNujgaP2mpNQMijWImOhIuvH5dLOxuHw0YemKM5z
*/