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