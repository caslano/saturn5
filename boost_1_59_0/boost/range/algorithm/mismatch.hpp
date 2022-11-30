//  Copyright Neil Groves 2009. Use, modification and
//  distribution is subject to the Boost Software License, Version
//  1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
//
// For more information, see http://www.boost.org/libs/range/
//
#ifndef BOOST_RANGE_ALGORITHM_MISMATCH_HPP_INCLUDED
#define BOOST_RANGE_ALGORITHM_MISMATCH_HPP_INCLUDED

#include <boost/concept_check.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/concepts.hpp>
#include <boost/range/difference_type.hpp>
#include <algorithm>

namespace boost
{
    namespace range_detail
    {
        template< class SinglePassTraversalReadableIterator1,
                  class SinglePassTraversalReadableIterator2 >
        inline std::pair<SinglePassTraversalReadableIterator1,
                         SinglePassTraversalReadableIterator2>
        mismatch_impl(SinglePassTraversalReadableIterator1 first1,
                      SinglePassTraversalReadableIterator1 last1,
                      SinglePassTraversalReadableIterator2 first2,
                      SinglePassTraversalReadableIterator2 last2)
        {
            while (first1 != last1 && first2 != last2 && *first1 == *first2)
            {
                ++first1;
                ++first2;
            }
            return std::pair<SinglePassTraversalReadableIterator1,
                             SinglePassTraversalReadableIterator2>(first1, first2);
        }

        template< class SinglePassTraversalReadableIterator1,
                  class SinglePassTraversalReadableIterator2,
                  class BinaryPredicate >
        inline std::pair<SinglePassTraversalReadableIterator1,
                         SinglePassTraversalReadableIterator2>
        mismatch_impl(SinglePassTraversalReadableIterator1 first1,
                      SinglePassTraversalReadableIterator1 last1,
                      SinglePassTraversalReadableIterator2 first2,
                      SinglePassTraversalReadableIterator2 last2,
                      BinaryPredicate pred)
        {
            while (first1 != last1 && first2 != last2 && pred(*first1, *first2))
            {
                ++first1;
                ++first2;
            }
            return std::pair<SinglePassTraversalReadableIterator1,
                             SinglePassTraversalReadableIterator2>(first1, first2);
        }
    } // namespace range_detail

    namespace range
    {
/// \brief template function mismatch
///
/// range-based version of the mismatch std algorithm
///
/// \pre SinglePassRange1 is a model of the SinglePassRangeConcept
/// \pre SinglePassRange2 is a model of the SinglePassRangeConcept
/// \pre BinaryPredicate is a model of the BinaryPredicateConcept
template< class SinglePassRange1, class SinglePassRange2 >
inline std::pair<
    BOOST_DEDUCED_TYPENAME range_iterator<SinglePassRange1>::type,
    BOOST_DEDUCED_TYPENAME range_iterator<const SinglePassRange2>::type >
mismatch(SinglePassRange1& rng1, const SinglePassRange2 & rng2)
{
    BOOST_RANGE_CONCEPT_ASSERT(( SinglePassRangeConcept<SinglePassRange1> ));
    BOOST_RANGE_CONCEPT_ASSERT(( SinglePassRangeConcept<const SinglePassRange2> ));

    return ::boost::range_detail::mismatch_impl(
        ::boost::begin(rng1), ::boost::end(rng1),
        ::boost::begin(rng2), ::boost::end(rng2));
}

/// \overload
template< class SinglePassRange1, class SinglePassRange2 >
inline std::pair<
    BOOST_DEDUCED_TYPENAME range_iterator<const SinglePassRange1>::type,
    BOOST_DEDUCED_TYPENAME range_iterator<const SinglePassRange2>::type >
mismatch(const SinglePassRange1& rng1, const SinglePassRange2& rng2)
{
    BOOST_RANGE_CONCEPT_ASSERT(( SinglePassRangeConcept<const SinglePassRange1> ));
    BOOST_RANGE_CONCEPT_ASSERT(( SinglePassRangeConcept<const SinglePassRange2> ));

    return ::boost::range_detail::mismatch_impl(
        ::boost::begin(rng1), ::boost::end(rng1),
        ::boost::begin(rng2), ::boost::end(rng2));
}

/// \overload
template< class SinglePassRange1, class SinglePassRange2 >
inline std::pair<
    BOOST_DEDUCED_TYPENAME range_iterator<SinglePassRange1>::type,
    BOOST_DEDUCED_TYPENAME range_iterator<SinglePassRange2>::type >
mismatch(SinglePassRange1& rng1, SinglePassRange2 & rng2)
{
    BOOST_RANGE_CONCEPT_ASSERT(( SinglePassRangeConcept<SinglePassRange1> ));
    BOOST_RANGE_CONCEPT_ASSERT(( SinglePassRangeConcept<SinglePassRange2> ));

    return ::boost::range_detail::mismatch_impl(
        ::boost::begin(rng1), ::boost::end(rng1),
        ::boost::begin(rng2), ::boost::end(rng2));
}

/// \overload
template< class SinglePassRange1, class SinglePassRange2 >
inline std::pair<
    BOOST_DEDUCED_TYPENAME range_iterator<const SinglePassRange1>::type,
    BOOST_DEDUCED_TYPENAME range_iterator<SinglePassRange2>::type >
mismatch(const SinglePassRange1& rng1, SinglePassRange2& rng2)
{
    BOOST_RANGE_CONCEPT_ASSERT(( SinglePassRangeConcept<const SinglePassRange1> ));
    BOOST_RANGE_CONCEPT_ASSERT(( SinglePassRangeConcept<SinglePassRange2> ));

    return ::boost::range_detail::mismatch_impl(
        ::boost::begin(rng1), ::boost::end(rng1),
        ::boost::begin(rng2), ::boost::end(rng2));
}


/// \overload
template< class SinglePassRange1, class SinglePassRange2, class BinaryPredicate >
inline std::pair<
    BOOST_DEDUCED_TYPENAME range_iterator<SinglePassRange1>::type,
    BOOST_DEDUCED_TYPENAME range_iterator<const SinglePassRange2>::type >
mismatch(SinglePassRange1& rng1, const SinglePassRange2& rng2, BinaryPredicate pred)
{
    BOOST_RANGE_CONCEPT_ASSERT(( SinglePassRangeConcept<SinglePassRange1> ));
    BOOST_RANGE_CONCEPT_ASSERT(( SinglePassRangeConcept<const SinglePassRange2> ));

    return ::boost::range_detail::mismatch_impl(
        ::boost::begin(rng1), ::boost::end(rng1),
        ::boost::begin(rng2), ::boost::end(rng2), pred);
}

/// \overload
template< class SinglePassRange1, class SinglePassRange2, class BinaryPredicate >
inline std::pair<
    BOOST_DEDUCED_TYPENAME range_iterator<const SinglePassRange1>::type,
    BOOST_DEDUCED_TYPENAME range_iterator<const SinglePassRange2>::type >
mismatch(const SinglePassRange1& rng1, const SinglePassRange2& rng2, BinaryPredicate pred)
{
    BOOST_RANGE_CONCEPT_ASSERT(( SinglePassRangeConcept<const SinglePassRange1> ));
    BOOST_RANGE_CONCEPT_ASSERT(( SinglePassRangeConcept<const SinglePassRange2> ));

    return ::boost::range_detail::mismatch_impl(
        ::boost::begin(rng1), ::boost::end(rng1),
        ::boost::begin(rng2), ::boost::end(rng2), pred);
}

/// \overload
template< class SinglePassRange1, class SinglePassRange2, class BinaryPredicate >
inline std::pair<
    BOOST_DEDUCED_TYPENAME range_iterator<SinglePassRange1>::type,
    BOOST_DEDUCED_TYPENAME range_iterator<SinglePassRange2>::type >
mismatch(SinglePassRange1& rng1, SinglePassRange2& rng2, BinaryPredicate pred)
{
    BOOST_RANGE_CONCEPT_ASSERT(( SinglePassRangeConcept<SinglePassRange1> ));
    BOOST_RANGE_CONCEPT_ASSERT(( SinglePassRangeConcept<SinglePassRange2> ));

    return ::boost::range_detail::mismatch_impl(
        ::boost::begin(rng1), ::boost::end(rng1),
        ::boost::begin(rng2), ::boost::end(rng2), pred);
}

/// \overload
template< class SinglePassRange1, class SinglePassRange2, class BinaryPredicate >
inline std::pair<
    BOOST_DEDUCED_TYPENAME range_iterator<const SinglePassRange1>::type,
    BOOST_DEDUCED_TYPENAME range_iterator<SinglePassRange2>::type >
mismatch(const SinglePassRange1& rng1, SinglePassRange2& rng2, BinaryPredicate pred)
{
    BOOST_RANGE_CONCEPT_ASSERT(( SinglePassRangeConcept<const SinglePassRange1> ));
    BOOST_RANGE_CONCEPT_ASSERT(( SinglePassRangeConcept<SinglePassRange2> ));

    return ::boost::range_detail::mismatch_impl(
        ::boost::begin(rng1), ::boost::end(rng1),
        ::boost::begin(rng2), ::boost::end(rng2), pred);
}

    } // namespace range
    using range::mismatch;
} // namespace boost

#endif // include guard

/* mismatch.hpp
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
*/