//  Boost string_algo library join.hpp header file  ---------------------------//

//  Copyright Pavol Droba 2002-2006.
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org/ for updates, documentation, and revision history.

#ifndef BOOST_STRING_JOIN_HPP
#define BOOST_STRING_JOIN_HPP

#include <boost/algorithm/string/config.hpp>
#include <boost/algorithm/string/detail/sequence.hpp>
#include <boost/range/value_type.hpp>
#include <boost/range/as_literal.hpp>

/*! \file
    Defines join algorithm. 

    Join algorithm is a counterpart to split algorithms.
    It joins strings from a 'list' by adding user defined separator.
    Additionally there is a version that allows simple filtering
    by providing a predicate.
*/

namespace boost {
    namespace algorithm {

//  join --------------------------------------------------------------//

        //! Join algorithm
        /*!
            This algorithm joins all strings in a 'list' into one long string.
            Segments are concatenated by given separator.

            \param Input A container that holds the input strings. It must be a container-of-containers.
            \param Separator A string that will separate the joined segments.
            \return Concatenated string.

            \note This function provides the strong exception-safety guarantee
        */
        template< typename SequenceSequenceT, typename Range1T>
        inline typename range_value<SequenceSequenceT>::type 
        join(
            const SequenceSequenceT& Input,
            const Range1T& Separator)
        {
            // Define working types
            typedef typename range_value<SequenceSequenceT>::type ResultT;
            typedef typename range_const_iterator<SequenceSequenceT>::type InputIteratorT;

            // Parse input
            InputIteratorT itBegin=::boost::begin(Input);
            InputIteratorT itEnd=::boost::end(Input);

            // Construct container to hold the result
            ResultT Result;
            
            // Append first element
            if(itBegin!=itEnd)
            {
                detail::insert(Result, ::boost::end(Result), *itBegin);
                ++itBegin;
            }

            for(;itBegin!=itEnd; ++itBegin)
            {
                // Add separator
                detail::insert(Result, ::boost::end(Result), ::boost::as_literal(Separator));
                // Add element
                detail::insert(Result, ::boost::end(Result), *itBegin);
            }

            return Result;
        }

// join_if ----------------------------------------------------------//

        //! Conditional join algorithm
        /*!
            This algorithm joins all strings in a 'list' into one long string.
            Segments are concatenated by given separator. Only segments that
            satisfy the predicate will be added to the result.

            \param Input A container that holds the input strings. It must be a container-of-containers.
            \param Separator A string that will separate the joined segments.
            \param Pred A segment selection predicate
            \return Concatenated string.

            \note This function provides the strong exception-safety guarantee
        */
        template< typename SequenceSequenceT, typename Range1T, typename PredicateT>
        inline typename range_value<SequenceSequenceT>::type 
        join_if(
            const SequenceSequenceT& Input,
            const Range1T& Separator,
            PredicateT Pred)
        {
            // Define working types
            typedef typename range_value<SequenceSequenceT>::type ResultT;
            typedef typename range_const_iterator<SequenceSequenceT>::type InputIteratorT;

            // Parse input
            InputIteratorT itBegin=::boost::begin(Input);
            InputIteratorT itEnd=::boost::end(Input);

            // Construct container to hold the result
            ResultT Result;

            // Roll to the first element that will be added
            while(itBegin!=itEnd && !Pred(*itBegin)) ++itBegin;
            // Add this element
            if(itBegin!=itEnd)
            {
                detail::insert(Result, ::boost::end(Result), *itBegin);
                ++itBegin;
            }

            for(;itBegin!=itEnd; ++itBegin)
            {
                if(Pred(*itBegin))
                {
                    // Add separator
                    detail::insert(Result, ::boost::end(Result), ::boost::as_literal(Separator));
                    // Add element
                    detail::insert(Result, ::boost::end(Result), *itBegin);
                }
            }

            return Result;
        }

    } // namespace algorithm

    // pull names to the boost namespace
    using algorithm::join;
    using algorithm::join_if;

} // namespace boost


#endif  // BOOST_STRING_JOIN_HPP


/* join.hpp
yuJq+vXiBdv3NKHyzElYbM5EC85suXjPfNXP6dnYoZ0DgvRsgBB2kQf5MopcwDf07yyLR+B7ZpHNXpDWN9UvxajdhAUpCIjWWuID+tmwZGqQVKTuZbkzGilbFUVJdssT5/du/GsJmWn0VaKIXREma9sV84PgjsiOf2nkEU7y7yNNtp/4700aNO0SrJwwvkYBGLFKflWEE1yZPH4Rt2ArfRfrJ3+f8PdYRuKYHUrGw82MpXGmIXa2EEygXiuh0lJF/sa/ge19aIVPtd8Pv5ql4S/KLWFHUYoSs32jZ4yKPYilBdYGOEWGgTlPhFazCJn/XmdUxPWPa81rF+ZfhmLRbXtUCaoWAmVsFuGkmWRm3SSYlYw9Qd5kKwWanI+ZsgcDDV8YamQPcCqd94s+vM2VTlT1ZJzeS9Dlm08s+2LItFMoL2FZ4tZFd86Aek3KZqqr3DRygB/8FypzQFf/KJ2s5QqrUlcV/fpZlyXhOml2AKJgUvAp1GLkyclwPRRj/9rl/Y6STddXkYOFxCe8fh/YCJba0mdfz2+1n1ctXgFlt1Ml3ZRbNTDrzz9OqSqgP/EvZL2foU0g2UHIFxcVDFhzakVaqIwslqTdMxRfhhG/epjOfFJksnQlsz3dd3FGZifjwZ2e8TxALXAFvxnsF7WdTLNnQdRvKXhPvz5C5IbTmpK/3y2bfZMWJkouV7jBoyLjSwSUDaoE5hZaqErD
*/