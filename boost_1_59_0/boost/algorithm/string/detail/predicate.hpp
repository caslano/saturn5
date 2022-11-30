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
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
*/