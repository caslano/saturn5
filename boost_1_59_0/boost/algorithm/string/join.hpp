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
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
*/