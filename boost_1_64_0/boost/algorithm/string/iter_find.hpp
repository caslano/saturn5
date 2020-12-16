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
GJ5InjAO4UsyffmM6nwuAaNaPGef+GGpj4HnIjTlp6N2YNl/XWm2hVvytdt0uokdL0uIqcF7lL6hJPdo7G0JnEWnVG5qFQCi4tN/LrfqH2XWPyzBHN99qeb4XnlF2PhuqxdpfEOuGl1X2lQX0C1yevwTZKaqSZpQjX/Qdsm/IplWYE27N0Zxzguprko/h3mBruZ6F/+8T10tS/t1vvL3xYMHjJ5Vt4aintGc3cCq6ucwS/BOWScxXMUZO3SM0N+mmeH9TUB/Y6m/F18u/f25Afc3IUJ/BzWsqL+vDJP+bu/C/U2Q/nrjw/rbqOG/ob/sv5IvMyx5ausxLzONHwoTgYlRnPiuxOvAka7hh9PLfOz0dgfYRwN6pI73kFOvGf/6mn8liETpNevcCKxivq0vyzq2AgZVYENOD9FDJm60Zve2tsjlMH3JTsUQMpn0XaUd6nH4mGYoobZcIyPc6lImllM4W63RqdFdOPUaQtzkWotq3kut2xRjUc3JQjWdtxLVXKOapIjT9/6JaGix/aq9fhAzb89o5o1dWrJ0hsBb12fmE6f1dQns/yOonYalNhCJBDkhYTkGuwJjsQWVS0ngcn6mTmi4FeVL0TP9sGCQXQd2drryfmXDso1cknlY59NVOSbIl8ig15uB0u11rfhahOEj/C+1luovAibl7aN1iXRsvmFDmFlI4jGgSo8Ks3DiFh4LMAsPqTqXYFJ3BQOKX+m44DsU36T7+YJ4N9JNT9N/Qzl3QTCGpgZiVoxFEjHm3aRfOdelGzH8njbQyaEELuXas63aa1bh2udYtR9VSzpI7TejFgvuG2nlEAvuRzVWw/UEHIfICaTiGwEX80ynU1Ldk/8j0nyt/5Bu2svC/w3xqdvkkHGtkPiiSUWV1Ley2cfWTQ+96X+H/ZoBp1SHSHDRQK1vbHqU97kheniB3f+oYXWZ9LUHAwPitnGQ9thUqg5qJYr9tAs3k4d9F8hd67pM7vaA03Qb+7EIhjWzdvxqgNAL1yPNmdPtw8HVW/G9K51kZhPx3SrXjMuJCPNWvpW7hL5+7ZJNVIuKdGtl07X6o6xnKxxfyxXtEvZ/3FMPK+xswh2XWkc3PzowR9hJxXUwD/G8HiaXWr2m9OsS/KRgXs14kJhFH0dPBouEjLnH0aZYhU2xTg28mHs/Xot2d/K+VxvrS0kANwAwIZjECKw3h6qqkZTsEHIGTHXWaR5ya5tD0vS7+MYxjJaeDmtrd666mHQp/A8x/cwEO5ZpTAU5+OIPGG+THxrotvh9Yva3tTeHsUf3MF7ozerMC1VKnzSYZvJ4zCK8rapl2+zpq6se/NpLHu6Hs4Jm31ahp/EGKFsZQ6NTx6ucL7VTOHjo2OzNNLZlGirl59ztQTXz0pCTqr4OuRzMaCfSnPPxm/Alpfv7VnEXkGiaVqPwJcuuYrrbkv1DsG8JWTpVb8LS6UuvW/VVAjigwH5KN7ISeP3wsssc5aAwsuI359NOUhlJM8zwGJtupBPgaWp6zVjeoaYji2eQww887JnC9r71lza4ak606oEkpWxF07iiuS0kAuWL0tqhwCd4+gBPr6pqDOG5MHNUQzwwd0UmlDvc69YC4HX2PVWA4aJGZuZf5s6vgyrk9Dvoi7cCYcWiFFGNGoN1tMr/imCV4fbQoVBEN/bQCzOQNaqUjAFTfiY1huOicMpnvoMUDTlwAC2OzI6hBVPdIWKDNzrKHH4YpReMe10Mi3OjHLJkoElIcCMG6zWzQK+ZW2UW9o4mcvMw1kwD9eVFWDNLmY2UQPUcRkrI1a88hXNuM5UjHxhN68THl6joMIcn85DDml7shse2TvKAvqRTGG4d9PQxQd4o3dBpWEs=
*/