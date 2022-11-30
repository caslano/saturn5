//  Boost string_algo library iter_find.hpp header file  ---------------------------//

//  Copyright Pavol Droba 2002-2003.
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org/ for updates, documentation, and revision history.

#ifndef BOOST_STRING_ITER_FIND_HPP
#define BOOST_STRING_ITER_FIND_HPP

#include <boost/algorithm/string/config.hpp>
#include <algorithm>
#include <iterator>
#include <boost/iterator/transform_iterator.hpp>

#include <boost/range/iterator_range_core.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/iterator.hpp>
#include <boost/range/value_type.hpp>
#include <boost/range/as_literal.hpp>

#include <boost/algorithm/string/concept.hpp>
#include <boost/algorithm/string/find_iterator.hpp>
#include <boost/algorithm/string/detail/util.hpp>

/*! \file
    Defines generic split algorithms. Split algorithms can be 
    used to divide a sequence into several part according 
    to a given criteria. Result is given as a 'container 
    of containers' where elements are copies or references 
    to extracted parts.

    There are two algorithms provided. One iterates over matching
    substrings, the other one over the gaps between these matches.
*/

namespace boost {
    namespace algorithm {

//  iterate find ---------------------------------------------------//

        //! Iter find algorithm
        /*!
            This algorithm executes a given finder in iteration on the input,
            until the end of input is reached, or no match is found.
            Iteration is done using built-in find_iterator, so the real 
            searching is performed only when needed.
            In each iteration new match is found and added to the result.

            \param Result A 'container container' to contain the result of search.
                Both outer and inner container must have constructor taking a pair
                of iterators as an argument.
                Typical type of the result is 
                    \c std::vector<boost::iterator_range<iterator>>
                (each element of such a vector will container a range delimiting 
                a match).
            \param Input A container which will be searched.
            \param Finder A Finder object used for searching
            \return A reference to the result

            \note Prior content of the result will be overwritten.
        */
        template< 
            typename SequenceSequenceT,
            typename RangeT,
            typename FinderT >
        inline SequenceSequenceT&
        iter_find(
            SequenceSequenceT& Result,
#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
            RangeT&& Input,
#else
            RangeT& Input,
#endif
            FinderT Finder )
        {
            BOOST_CONCEPT_ASSERT((
                FinderConcept<
                    FinderT,
                    BOOST_STRING_TYPENAME range_iterator<RangeT>::type>
                ));

            iterator_range<BOOST_STRING_TYPENAME range_iterator<RangeT>::type> lit_input(::boost::as_literal(Input));

            typedef BOOST_STRING_TYPENAME 
                range_iterator<RangeT>::type input_iterator_type;
            typedef find_iterator<input_iterator_type> find_iterator_type;
            typedef detail::copy_iterator_rangeF<
                BOOST_STRING_TYPENAME 
                    range_value<SequenceSequenceT>::type,
                input_iterator_type> copy_range_type;
            
            input_iterator_type InputEnd=::boost::end(lit_input);

            typedef transform_iterator<copy_range_type, find_iterator_type>
                transform_iter_type;
    
            transform_iter_type itBegin=
                ::boost::make_transform_iterator( 
                    find_iterator_type( ::boost::begin(lit_input), InputEnd, Finder ),
                    copy_range_type());
            
            transform_iter_type itEnd=
                ::boost::make_transform_iterator( 
                    find_iterator_type(),
                    copy_range_type());

            SequenceSequenceT Tmp(itBegin, itEnd);
                        
            Result.swap(Tmp);
            return Result;
        }

//  iterate split ---------------------------------------------------//

        //! Split find algorithm
        /*!
            This algorithm executes a given finder in iteration on the input,
            until the end of input is reached, or no match is found.
            Iteration is done using built-in find_iterator, so the real 
            searching is performed only when needed.
            Each match is used as a separator of segments. These segments are then
            returned in the result.

            \param Result A 'container container' to contain the result of search.
                Both outer and inner container must have constructor taking a pair
                of iterators as an argument.
                Typical type of the result is 
                    \c std::vector<boost::iterator_range<iterator>>
                (each element of such a vector will container a range delimiting 
                a match).
            \param Input A container which will be searched.
            \param Finder A finder object used for searching
            \return A reference to the result

            \note Prior content of the result will be overwritten.
        */
        template< 
            typename SequenceSequenceT,
            typename RangeT,
            typename FinderT >
        inline SequenceSequenceT&
        iter_split(
            SequenceSequenceT& Result,
#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
            RangeT&& Input,
#else
            RangeT& Input,
#endif
            FinderT Finder )
        {
            BOOST_CONCEPT_ASSERT((
                FinderConcept<FinderT,
                BOOST_STRING_TYPENAME range_iterator<RangeT>::type>
                ));

            iterator_range<BOOST_STRING_TYPENAME range_iterator<RangeT>::type> lit_input(::boost::as_literal(Input));

            typedef BOOST_STRING_TYPENAME 
                range_iterator<RangeT>::type input_iterator_type;
            typedef split_iterator<input_iterator_type> find_iterator_type;
            typedef detail::copy_iterator_rangeF<
                BOOST_STRING_TYPENAME 
                    range_value<SequenceSequenceT>::type,
                input_iterator_type> copy_range_type;
            
            input_iterator_type InputEnd=::boost::end(lit_input);

            typedef transform_iterator<copy_range_type, find_iterator_type>
                transform_iter_type;
    
            transform_iter_type itBegin=
                ::boost::make_transform_iterator( 
                    find_iterator_type( ::boost::begin(lit_input), InputEnd, Finder ),
                    copy_range_type() );

            transform_iter_type itEnd=
                ::boost::make_transform_iterator( 
                    find_iterator_type(),
                    copy_range_type() );
            
            SequenceSequenceT Tmp(itBegin, itEnd);

            Result.swap(Tmp);
            return Result;
        }

    } // namespace algorithm

    // pull names to the boost namespace
    using algorithm::iter_find;
    using algorithm::iter_split;

} // namespace boost


#endif  // BOOST_STRING_ITER_FIND_HPP

/* iter_find.hpp
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
*/