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