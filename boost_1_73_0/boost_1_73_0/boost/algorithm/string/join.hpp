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
UFRCijRWvMjxhX3vBvpp+rgKzRXFt0Eo78r6qSn1BgWbSDZEEF2/dTtCaXz+/svbt8pJjs40mqtUBwFkFt/3F5eeWuu9K+1HyIh/nJKzfYz3NnTmRyJjcyAAM2JGki424TsaBKp8b3EhQYXyyFlDKhwZ94WFWUmhC5UW716/efnlb9efP7/5dPv02Z1pAElRy57fOJQJe0DpesxU65foHVJ1LoP7r5DrQMADzqwkPIAeNBRUDnEMhKKtIiIIhieKlnPo25LTdx643bEMYiMwhy+4rWjkj1ncf4joX+0LMirVIJgptnNzOMQ0owjWeEhmz+QjI91EavApoPGsHr6SQOChkB+a0jKwSUBoRFslcUkMkFTmHB+PzMv7moFGn1JMok66MI1kGd9rnJrkMuahF+Ln7Rqk1z7PrvMTMPuVhCquSCWBn6bQ2AeXAgk+E6JqH26hxR9f1sYBjgUKTAVcKXZFV/J4lFwFyWfFQufdJNMFfL57ErrWd3cIqTG/1QcUXAU6YUv2h9IMoTFDrE6vWw0szhegSaQ5npkT6WDhVnGJCO6u0CoHfzDkMA9WVmUYM1CJNhzHX2PXmaBYEMjAna+o6oOCfXWQkKYJ9yOr8GJw3/3Fj2z9GpRJCpMq28QkzbS0ghel/6QZsbw4
*/