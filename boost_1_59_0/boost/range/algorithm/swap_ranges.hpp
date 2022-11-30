//  Copyright Neil Groves 2009. Use, modification and
//  distribution is subject to the Boost Software License, Version
//  1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
//
// For more information, see http://www.boost.org/libs/range/
//
#ifndef BOOST_RANGE_ALGORITHM_SWAP_RANGES_HPP_INCLUDED
#define BOOST_RANGE_ALGORITHM_SWAP_RANGES_HPP_INCLUDED

#include <boost/assert.hpp>
#include <boost/concept_check.hpp>
#include <boost/iterator/iterator_categories.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/concepts.hpp>
#include <boost/range/iterator.hpp>
#include <algorithm>

namespace boost
{
    namespace range_detail
    {
        template<class Iterator1, class Iterator2>
        void swap_ranges_impl(Iterator1 it1, Iterator1 last1,
                              Iterator2 it2, Iterator2 last2,
                              single_pass_traversal_tag,
                              single_pass_traversal_tag)
        {
            ignore_unused_variable_warning(last2);
            for (; it1 != last1; ++it1, ++it2)
            {
                BOOST_ASSERT( it2 != last2 );
                std::iter_swap(it1, it2);
            }
        }

        template<class Iterator1, class Iterator2>
        void swap_ranges_impl(Iterator1 it1, Iterator1 last1,
                              Iterator2 it2, Iterator2 last2,
                              random_access_traversal_tag,
                              random_access_traversal_tag)
        {
            ignore_unused_variable_warning(last2);
            BOOST_ASSERT( last2 - it2 >= last1 - it1 );
            std::swap_ranges(it1, last1, it2);
        }

        template<class Iterator1, class Iterator2>
        void swap_ranges_impl(Iterator1 first1, Iterator1 last1,
                              Iterator2 first2, Iterator2 last2)
        {
            swap_ranges_impl(first1, last1, first2, last2,
                BOOST_DEDUCED_TYPENAME iterator_traversal<Iterator1>::type(),
                BOOST_DEDUCED_TYPENAME iterator_traversal<Iterator2>::type());
        }
    } // namespace range_detail

    namespace range
    {

/// \brief template function swap_ranges
///
/// range-based version of the swap_ranges std algorithm
///
/// \pre SinglePassRange1 is a model of the SinglePassRangeConcept
/// \pre SinglePassRange2 is a model of the SinglePassRangeConcept
template< class SinglePassRange1, class SinglePassRange2 >
inline SinglePassRange2&
swap_ranges(SinglePassRange1& range1, SinglePassRange2& range2)
{
    BOOST_RANGE_CONCEPT_ASSERT((SinglePassRangeConcept<SinglePassRange1>));
    BOOST_RANGE_CONCEPT_ASSERT((SinglePassRangeConcept<SinglePassRange2>));

    boost::range_detail::swap_ranges_impl(
        boost::begin(range1), boost::end(range1),
        boost::begin(range2), boost::end(range2));

    return range2;
}

/// \overload
template< class SinglePassRange1, class SinglePassRange2 >
inline SinglePassRange2&
swap_ranges(const SinglePassRange1& range1, SinglePassRange2& range2)
{
    BOOST_RANGE_CONCEPT_ASSERT((SinglePassRangeConcept<const SinglePassRange1>));
    BOOST_RANGE_CONCEPT_ASSERT((SinglePassRangeConcept<SinglePassRange2>));

    boost::range_detail::swap_ranges_impl(
        boost::begin(range1), boost::end(range1),
        boost::begin(range2), boost::end(range2));

    return range2;
}

/// \overload
template< class SinglePassRange1, class SinglePassRange2 >
inline const SinglePassRange2&
swap_ranges(SinglePassRange1& range1, const SinglePassRange2& range2)
{
    BOOST_RANGE_CONCEPT_ASSERT((SinglePassRangeConcept<SinglePassRange1>));
    BOOST_RANGE_CONCEPT_ASSERT((SinglePassRangeConcept<const SinglePassRange2>));

    boost::range_detail::swap_ranges_impl(
        boost::begin(range1), boost::end(range1),
        boost::begin(range2), boost::end(range2));

    return range2;
}

/// \overload
template< class SinglePassRange1, class SinglePassRange2 >
inline const SinglePassRange2&
swap_ranges(const SinglePassRange1& range1, const SinglePassRange2& range2)
{
    BOOST_RANGE_CONCEPT_ASSERT((SinglePassRangeConcept<const SinglePassRange1>));
    BOOST_RANGE_CONCEPT_ASSERT((SinglePassRangeConcept<const SinglePassRange2>));

    boost::range_detail::swap_ranges_impl(
        boost::begin(range1), boost::end(range1),
        boost::begin(range2), boost::end(range2));

    return range2;
}

    } // namespace range
    using range::swap_ranges;
} // namespace boost

#endif // include guard

/* swap_ranges.hpp
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
*/