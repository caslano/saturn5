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
Dxi+lnqDnvwP5e2yB+kbvrrYGgGHgHYhfQlAHMAwOIQBPfkf6uINeuU/1JTLnlT/8FXu9ggwHLQr1Z+AxgcMA8MZ0Cv/oXLfovf+QzG77uUODF+p7oxIRYF2cwcSgK8Aw1JRDP91H5iBUrUPCHeau/q7hA/hJPCu5/3EFmerKZdxAbX+cDtsoDkyRfSpY4FE3W+8HEd0wo+7ibUDdRHE43BvDGNHwbuGFaT+2jawUIWicNDoc8sClwLptBHWArYH2ZAZ6fbu0YjnSAsMEjqFBI1RC3kS/+gP6bssibkPL0jf7NKdglT+fAAlWSQHBVaPhipLReESTul/MWCfUJcNvAk12yHKAUv0JTxNMQsvKGNVXsiWn4BFjsb2xPM/K2fkSSk2wdVml3YYueiUYXkz0sWU95eADU1Yu4faxUmRYiaJMRPxQpEAi3ZMSx4bejsXfYrkdjSabIVc5gJ4lQ/BAenmbiVI533xY2e3+HNahcmFbPSvxlO7+De/snzRhpNSaByRTiAid+/vYIa8yCTZNzfCiyKjy0dVkbSWb7yTb1kM4t9pz1N8WxzNBo49oo02wdAwyMNHIJg7ggfNiuZpxwGijcc2rhDAsY0qfw5OKI5KwZoI1EIGi8vtFXmibr3HCJb+raaAm/xz9ydtdhUm6xCGJg3LrOP0iQxcXbPL4NAq0Rf5HqQQUKzy1wRauFwu7ctSNIOZLGva0huR
*/