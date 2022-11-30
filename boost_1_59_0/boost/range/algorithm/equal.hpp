// Boost.Range library
//
//  Copyright Neil Groves 2009.
//  Use, modification and distribution is subject to the Boost Software
//  License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see http://www.boost.org/libs/range/
//
#ifndef BOOST_RANGE_ALGORITHM_EQUAL_HPP_INCLUDED
#define BOOST_RANGE_ALGORITHM_EQUAL_HPP_INCLUDED

#include <boost/config.hpp>
#include <boost/range/concepts.hpp>
#include <iterator>

namespace boost
{
    namespace range_detail
    {
        // An implementation of equality comparison that is optimized for iterator
        // traversal categories less than RandomAccessTraversal.
        template< class SinglePassTraversalReadableIterator1,
                  class SinglePassTraversalReadableIterator2,
                  class IteratorCategoryTag1,
                  class IteratorCategoryTag2 >
        inline bool equal_impl( SinglePassTraversalReadableIterator1 first1,
                                SinglePassTraversalReadableIterator1 last1,
                                SinglePassTraversalReadableIterator2 first2,
                                SinglePassTraversalReadableIterator2 last2,
                                IteratorCategoryTag1,
                                IteratorCategoryTag2 )
        {
            for (;;)
            {
                // If we have reached the end of the left range then this is
                // the end of the loop. They are equal if and only if we have
                // simultaneously reached the end of the right range.
                if (first1 == last1)
                    return first2 == last2;

                // If we have reached the end of the right range at this line
                // it indicates that the right range is shorter than the left
                // and hence the result is false.
                if (first2 == last2)
                    return false;

                // continue looping if and only if the values are equal
                if (*first1 != *first2)
                    break;

                ++first1;
                ++first2;
            }

            // Reaching this line in the algorithm indicates that a value
            // inequality has been detected.
            return false;
        }

        template< class SinglePassTraversalReadableIterator1,
                  class SinglePassTraversalReadableIterator2,
                  class IteratorCategoryTag1,
                  class IteratorCategoryTag2,
                  class BinaryPredicate >
        inline bool equal_impl( SinglePassTraversalReadableIterator1 first1,
                                SinglePassTraversalReadableIterator1 last1,
                                SinglePassTraversalReadableIterator2 first2,
                                SinglePassTraversalReadableIterator2 last2,
                                BinaryPredicate                      pred,
                                IteratorCategoryTag1,
                                IteratorCategoryTag2 )
        {
            for (;;)
            {
                // If we have reached the end of the left range then this is
                // the end of the loop. They are equal if and only if we have
                // simultaneously reached the end of the right range.
                if (first1 == last1)
                    return first2 == last2;

                // If we have reached the end of the right range at this line
                // it indicates that the right range is shorter than the left
                // and hence the result is false.
                if (first2 == last2)
                    return false;

                // continue looping if and only if the values are equal
                if (!pred(*first1, *first2))
                    break;

                ++first1;
                ++first2;
            }

            // Reaching this line in the algorithm indicates that a value
            // inequality has been detected.
            return false;
        }

        // An implementation of equality comparison that is optimized for
        // random access iterators.
        template< class RandomAccessTraversalReadableIterator1,
                  class RandomAccessTraversalReadableIterator2 >
        inline bool equal_impl( RandomAccessTraversalReadableIterator1 first1,
                                RandomAccessTraversalReadableIterator1 last1,
                                RandomAccessTraversalReadableIterator2 first2,
                                RandomAccessTraversalReadableIterator2 last2,
                                std::random_access_iterator_tag,
                                std::random_access_iterator_tag )
        {
            return ((last1 - first1) == (last2 - first2))
                && std::equal(first1, last1, first2);
        }

        template< class RandomAccessTraversalReadableIterator1,
                  class RandomAccessTraversalReadableIterator2,
                  class BinaryPredicate >
        inline bool equal_impl( RandomAccessTraversalReadableIterator1 first1,
                                RandomAccessTraversalReadableIterator1 last1,
                                RandomAccessTraversalReadableIterator2 first2,
                                RandomAccessTraversalReadableIterator2 last2,
                                BinaryPredicate                        pred,
                                std::random_access_iterator_tag,
                                std::random_access_iterator_tag )
        {
            return ((last1 - first1) == (last2 - first2))
                && std::equal(first1, last1, first2, pred);
        }

        template< class SinglePassTraversalReadableIterator1,
                  class SinglePassTraversalReadableIterator2 >
        inline bool equal( SinglePassTraversalReadableIterator1 first1,
                           SinglePassTraversalReadableIterator1 last1,
                           SinglePassTraversalReadableIterator2 first2,
                           SinglePassTraversalReadableIterator2 last2 )
        {
            BOOST_DEDUCED_TYPENAME std::iterator_traits< SinglePassTraversalReadableIterator1 >::iterator_category tag1;
            BOOST_DEDUCED_TYPENAME std::iterator_traits< SinglePassTraversalReadableIterator2 >::iterator_category tag2;

            return equal_impl(first1, last1, first2, last2, tag1, tag2);
        }

        template< class SinglePassTraversalReadableIterator1,
                  class SinglePassTraversalReadableIterator2,
                  class BinaryPredicate >
        inline bool equal( SinglePassTraversalReadableIterator1 first1,
                           SinglePassTraversalReadableIterator1 last1,
                           SinglePassTraversalReadableIterator2 first2,
                           SinglePassTraversalReadableIterator2 last2,
                           BinaryPredicate                      pred )
        {
            BOOST_DEDUCED_TYPENAME std::iterator_traits< SinglePassTraversalReadableIterator1 >::iterator_category tag1;
            BOOST_DEDUCED_TYPENAME std::iterator_traits< SinglePassTraversalReadableIterator2 >::iterator_category tag2;

            return equal_impl(first1, last1, first2, last2, pred, tag1, tag2);
        }

    } // namespace range_detail

    namespace range
    {

        /// \brief template function equal
        ///
        /// range-based version of the equal std algorithm
        ///
        /// \pre SinglePassRange1 is a model of the SinglePassRangeConcept
        /// \pre SinglePassRange2 is a model of the SinglePassRangeConcept
        /// \pre BinaryPredicate is a model of the BinaryPredicateConcept
        template< class SinglePassRange1, class SinglePassRange2 >
        inline bool equal( const SinglePassRange1& rng1, const SinglePassRange2& rng2 )
        {
            BOOST_RANGE_CONCEPT_ASSERT(( SinglePassRangeConcept<const SinglePassRange1> ));
            BOOST_RANGE_CONCEPT_ASSERT(( SinglePassRangeConcept<const SinglePassRange2> ));

            return ::boost::range_detail::equal(
                ::boost::begin(rng1), ::boost::end(rng1),
                ::boost::begin(rng2), ::boost::end(rng2) );
        }

        /// \overload
        template< class SinglePassRange1, class SinglePassRange2, class BinaryPredicate >
        inline bool equal( const SinglePassRange1& rng1, const SinglePassRange2& rng2,
                           BinaryPredicate pred )
        {
            BOOST_RANGE_CONCEPT_ASSERT(( SinglePassRangeConcept<const SinglePassRange1> ));
            BOOST_RANGE_CONCEPT_ASSERT(( SinglePassRangeConcept<const SinglePassRange2> ));

            return ::boost::range_detail::equal(
                ::boost::begin(rng1), ::boost::end(rng1),
                ::boost::begin(rng2), ::boost::end(rng2),
                pred);
        }

    } // namespace range
    using ::boost::range::equal;
} // namespace boost

#endif // include guard

/* equal.hpp
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
*/