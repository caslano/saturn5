//  Copyright Neil Groves 2009. Use, modification and
//  distribution is subject to the Boost Software License, Version
//  1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
//
// For more information, see http://www.boost.org/libs/range/
//
#ifndef BOOST_RANGE_ALGORITHM_ADJACENT_FIND_HPP_INCLUDED
#define BOOST_RANGE_ALGORITHM_ADJACENT_FIND_HPP_INCLUDED

#include <boost/concept_check.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/concepts.hpp>
#include <boost/range/value_type.hpp>
#include <boost/range/detail/range_return.hpp>
#include <algorithm>

namespace boost
{
    namespace range
    {

/// \brief template function adjacent_find
///
/// range-based version of the adjacent_find std algorithm
///
/// \pre ForwardRange is a model of the ForwardRangeConcept
/// \pre BinaryPredicate is a model of the BinaryPredicateConcept
template< typename ForwardRange >
inline typename range_iterator<ForwardRange>::type
adjacent_find(ForwardRange & rng)
{
    BOOST_RANGE_CONCEPT_ASSERT((ForwardRangeConcept<ForwardRange>));
    return std::adjacent_find(boost::begin(rng),boost::end(rng));
}

/// \overload
template< typename ForwardRange >
inline typename range_iterator<const ForwardRange>::type
adjacent_find(const ForwardRange& rng)
{
    BOOST_RANGE_CONCEPT_ASSERT((ForwardRangeConcept<ForwardRange>));
    return std::adjacent_find(boost::begin(rng),boost::end(rng));
}

/// \overload
template< typename ForwardRange, typename BinaryPredicate >
inline typename range_iterator<ForwardRange>::type
adjacent_find(ForwardRange & rng, BinaryPredicate pred)
{
    BOOST_RANGE_CONCEPT_ASSERT((ForwardRangeConcept<ForwardRange>));
    BOOST_RANGE_CONCEPT_ASSERT((BinaryPredicateConcept<BinaryPredicate,
        typename range_value<ForwardRange>::type,
        typename range_value<ForwardRange>::type>));
    return std::adjacent_find(boost::begin(rng),boost::end(rng),pred);
}

/// \overload
template< typename ForwardRange, typename BinaryPredicate >
inline typename range_iterator<const ForwardRange>::type
adjacent_find(const ForwardRange& rng, BinaryPredicate pred)
{
    BOOST_RANGE_CONCEPT_ASSERT((ForwardRangeConcept<ForwardRange>));
    BOOST_RANGE_CONCEPT_ASSERT((BinaryPredicateConcept<BinaryPredicate,
        typename range_value<const ForwardRange>::type,
        typename range_value<const ForwardRange>::type>));
    return std::adjacent_find(boost::begin(rng),boost::end(rng),pred);
}

//  range_return overloads

/// \overload
template< range_return_value re, typename ForwardRange >
inline typename range_return<ForwardRange,re>::type
adjacent_find(ForwardRange & rng)
{
    BOOST_RANGE_CONCEPT_ASSERT((ForwardRangeConcept<ForwardRange>));
    return range_return<ForwardRange,re>::
        pack(std::adjacent_find(boost::begin(rng),boost::end(rng)),
             rng);
}

/// \overload
template< range_return_value re, typename ForwardRange >
inline typename range_return<const ForwardRange,re>::type
adjacent_find(const ForwardRange& rng)
{
    BOOST_RANGE_CONCEPT_ASSERT((ForwardRangeConcept<ForwardRange>));
    return range_return<const ForwardRange,re>::
        pack(std::adjacent_find(boost::begin(rng),boost::end(rng)),
             rng);
}

/// \overload
template< range_return_value re, typename ForwardRange, typename BinaryPredicate >
inline typename range_return<ForwardRange,re>::type
adjacent_find(ForwardRange& rng, BinaryPredicate pred)
{
    BOOST_RANGE_CONCEPT_ASSERT((ForwardRangeConcept<ForwardRange>));
    BOOST_RANGE_CONCEPT_ASSERT((BinaryPredicateConcept<BinaryPredicate,
        typename range_value<ForwardRange>::type,
        typename range_value<ForwardRange>::type>));
    return range_return<ForwardRange,re>::
        pack(std::adjacent_find(boost::begin(rng),boost::end(rng),pred),
             rng);
}

/// \overload
template< range_return_value re, typename ForwardRange, typename BinaryPredicate >
inline typename range_return<const ForwardRange,re>::type
adjacent_find(const ForwardRange& rng, BinaryPredicate pred)
{
    BOOST_RANGE_CONCEPT_ASSERT((ForwardRangeConcept<ForwardRange>));
    return range_return<const ForwardRange,re>::
        pack(std::adjacent_find(boost::begin(rng),boost::end(rng),pred),
             rng);
}

    } // namespace range
    using range::adjacent_find;
} // namespace boost

#endif // include guard

/* adjacent_find.hpp
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
*/