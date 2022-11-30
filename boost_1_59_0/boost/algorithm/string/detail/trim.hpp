//  Boost string_algo library trim.hpp header file  ---------------------------//

//  Copyright Pavol Droba 2002-2003.
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org/ for updates, documentation, and revision history.

#ifndef BOOST_STRING_TRIM_DETAIL_HPP
#define BOOST_STRING_TRIM_DETAIL_HPP

#include <boost/algorithm/string/config.hpp>
#include <iterator>

namespace boost {
    namespace algorithm {
        namespace detail {

//  trim iterator helper -----------------------------------------------//

            template< typename ForwardIteratorT, typename PredicateT >
            inline ForwardIteratorT trim_end_iter_select( 
                ForwardIteratorT InBegin, 
                ForwardIteratorT InEnd, 
                PredicateT IsSpace,
                std::forward_iterator_tag )
            {
                ForwardIteratorT TrimIt=InBegin;

                for( ForwardIteratorT It=InBegin; It!=InEnd; ++It )
                {
                    if ( !IsSpace(*It) ) 
                    {
                        TrimIt=It;
                        ++TrimIt;
                    }
                }

                return TrimIt;
            }

            template< typename ForwardIteratorT, typename PredicateT >
            inline ForwardIteratorT trim_end_iter_select( 
                ForwardIteratorT InBegin, 
                ForwardIteratorT InEnd, 
                PredicateT IsSpace,
                std::bidirectional_iterator_tag )
            {
                for( ForwardIteratorT It=InEnd; It!=InBegin;  )
                {
                    if ( !IsSpace(*(--It)) )
                        return ++It;
                }

                return InBegin;
            }
   // Search for first non matching character from the beginning of the sequence
            template< typename ForwardIteratorT, typename PredicateT >
            inline ForwardIteratorT trim_begin( 
                ForwardIteratorT InBegin, 
                ForwardIteratorT InEnd, 
                PredicateT IsSpace )
            {
                ForwardIteratorT It=InBegin;
                for(; It!=InEnd; ++It )
                {
                    if (!IsSpace(*It))
                        return It;
                }

                return It;
            }

            // Search for first non matching character from the end of the sequence
            template< typename ForwardIteratorT, typename PredicateT >
            inline ForwardIteratorT trim_end( 
                ForwardIteratorT InBegin, 
                ForwardIteratorT InEnd, 
                PredicateT IsSpace )
            {
                typedef BOOST_STRING_TYPENAME
                    std::iterator_traits<ForwardIteratorT>::iterator_category category;

                return ::boost::algorithm::detail::trim_end_iter_select( InBegin, InEnd, IsSpace, category() );
            }


        } // namespace detail
    } // namespace algorithm
} // namespace boost


#endif  // BOOST_STRING_TRIM_DETAIL_HPP

/* trim.hpp
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
*/