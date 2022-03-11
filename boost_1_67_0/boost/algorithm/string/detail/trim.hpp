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
#include <boost/detail/iterator.hpp>

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
                typedef BOOST_STRING_TYPENAME boost::detail::
                    iterator_traits<ForwardIteratorT>::iterator_category category;

                return ::boost::algorithm::detail::trim_end_iter_select( InBegin, InEnd, IsSpace, category() );
            }


        } // namespace detail
    } // namespace algorithm
} // namespace boost


#endif  // BOOST_STRING_TRIM_DETAIL_HPP

/* trim.hpp
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
*/