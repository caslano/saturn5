//  Copyright Neil Groves 2009. Use, modification and
//  distribution is subject to the Boost Software License, Version
//  1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
//
// For more information, see http://www.boost.org/libs/range/
//
#ifndef BOOST_RANGE_ALGORITHM_UPPER_BOUND_HPP_INCLUDED
#define BOOST_RANGE_ALGORITHM_UPPER_BOUND_HPP_INCLUDED

#include <boost/concept_check.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/concepts.hpp>
#include <boost/range/detail/range_return.hpp>
#include <algorithm>

namespace boost
{
    namespace range
    {

/// \brief template function upper_bound
///
/// range-based version of the upper_bound std algorithm
///
/// \pre ForwardRange is a model of the ForwardRangeConcept
template< class ForwardRange, class Value >
inline
BOOST_DEDUCED_TYPENAME disable_if<
    is_const<ForwardRange>,
    BOOST_DEDUCED_TYPENAME range_iterator<ForwardRange>::type
>::type
upper_bound( ForwardRange& rng, const Value& val )
{
    BOOST_RANGE_CONCEPT_ASSERT(( ForwardRangeConcept<ForwardRange> ));
    return std::upper_bound(boost::begin(rng), boost::end(rng), val);
}

/// \overload
template< class ForwardRange, class Value >
BOOST_DEDUCED_TYPENAME range_iterator<const ForwardRange>::type
upper_bound( const ForwardRange& rng, const Value& val )
{
    BOOST_RANGE_CONCEPT_ASSERT(( ForwardRangeConcept<const ForwardRange> ));
    return std::upper_bound(boost::begin(rng), boost::end(rng), val);
}

/// \overload
template< class ForwardRange, class Value, class SortPredicate >
inline BOOST_DEDUCED_TYPENAME disable_if<
    is_const<ForwardRange>,
    BOOST_DEDUCED_TYPENAME range_iterator<ForwardRange>::type
>::type
upper_bound( ForwardRange& rng, const Value& val, SortPredicate pred )
{
    BOOST_RANGE_CONCEPT_ASSERT(( ForwardRangeConcept<ForwardRange> ));
    return std::upper_bound(boost::begin(rng), boost::end(rng), val, pred);
}

/// \overload
template< class ForwardRange, class Value, class SortPredicate >
inline BOOST_DEDUCED_TYPENAME range_iterator<const ForwardRange>::type
upper_bound( const ForwardRange& rng, const Value& val, SortPredicate pred )
{
    BOOST_RANGE_CONCEPT_ASSERT(( ForwardRangeConcept<const ForwardRange> ));
    return std::upper_bound(boost::begin(rng), boost::end(rng), val, pred);
}

/// \overload
template< range_return_value re, class ForwardRange, class Value >
inline BOOST_DEDUCED_TYPENAME disable_if<
    is_const<ForwardRange>,
    BOOST_DEDUCED_TYPENAME range_return<ForwardRange,re>::type
>::type
upper_bound( ForwardRange& rng, const Value& val )
{
    BOOST_RANGE_CONCEPT_ASSERT(( ForwardRangeConcept<ForwardRange> ));
    return range_return<ForwardRange,re>::
        pack(std::upper_bound(boost::begin(rng), boost::end(rng), val),
             rng);
}

/// \overload
template< range_return_value re, class ForwardRange, class Value >
inline BOOST_DEDUCED_TYPENAME range_return<const ForwardRange,re>::type
upper_bound( const ForwardRange& rng, const Value& val )
{
    BOOST_RANGE_CONCEPT_ASSERT(( ForwardRangeConcept<const ForwardRange> ));
    return range_return<const ForwardRange,re>::
        pack(std::upper_bound(boost::begin(rng), boost::end(rng), val),
             rng);
}

/// \overload
template< range_return_value re, class ForwardRange, class Value,
          class SortPredicate >
inline BOOST_DEDUCED_TYPENAME disable_if<
    is_const<ForwardRange>,
    BOOST_DEDUCED_TYPENAME range_return<ForwardRange,re>::type
>::type
upper_bound( ForwardRange& rng, const Value& val, SortPredicate pred )
{
    BOOST_RANGE_CONCEPT_ASSERT(( ForwardRangeConcept<ForwardRange> ));
    return range_return<ForwardRange,re>::
        pack(std::upper_bound(boost::begin(rng), boost::end(rng), val, pred),
             rng);
}

/// \overload
template< range_return_value re, class ForwardRange, class Value,
          class SortPredicate >
inline BOOST_DEDUCED_TYPENAME range_return<const ForwardRange,re>::type
upper_bound( const ForwardRange& rng, const Value& val, SortPredicate pred )
{
    BOOST_RANGE_CONCEPT_ASSERT(( ForwardRangeConcept<const ForwardRange> ));
    return range_return<const ForwardRange,re>::
        pack(std::upper_bound(boost::begin(rng), boost::end(rng), val, pred),
             rng);
}

    } // namespace range
    using range::upper_bound;
} // namespace boost

#endif // include guard

/* upper_bound.hpp
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
*/