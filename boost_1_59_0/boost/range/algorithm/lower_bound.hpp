//  Copyright Neil Groves 2009. Use, modification and
//  distribution is subject to the Boost Software License, Version
//  1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
//
// For more information, see http://www.boost.org/libs/range/
//
#ifndef BOOST_RANGE_ALGORITHM_LOWER_BOUND_HPP_INCLUDED
#define BOOST_RANGE_ALGORITHM_LOWER_BOUND_HPP_INCLUDED

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

/// \brief template function lower_bound
///
/// range-based version of the lower_bound std algorithm
///
/// \pre ForwardRange is a model of the ForwardRangeConcept
template< class ForwardRange, class Value >
inline BOOST_DEDUCED_TYPENAME disable_if<
    is_const<ForwardRange>,
    BOOST_DEDUCED_TYPENAME range_iterator<ForwardRange>::type
>::type
lower_bound( ForwardRange& rng, const Value& val )
{
    BOOST_RANGE_CONCEPT_ASSERT(( ForwardRangeConcept<ForwardRange> ));
    return std::lower_bound(boost::begin(rng), boost::end(rng), val);
}

/// \overload
template< class ForwardRange, class Value >
inline BOOST_DEDUCED_TYPENAME range_iterator<const ForwardRange>::type
lower_bound( const ForwardRange& rng, const Value& val )
{
    BOOST_RANGE_CONCEPT_ASSERT(( ForwardRangeConcept<const ForwardRange> ));
    return std::lower_bound(boost::begin(rng), boost::end(rng), val);
}

/// \overload
template< class ForwardRange, class Value, class SortPredicate >
inline BOOST_DEDUCED_TYPENAME disable_if<
    is_const<ForwardRange>,
    BOOST_DEDUCED_TYPENAME range_iterator<ForwardRange>::type
>::type
lower_bound( ForwardRange& rng, const Value& val, SortPredicate pred )
{
    BOOST_RANGE_CONCEPT_ASSERT(( ForwardRangeConcept<ForwardRange> ));
    return std::lower_bound(boost::begin(rng), boost::end(rng), val, pred);
}

/// \overload
template< class ForwardRange, class Value, class SortPredicate >
inline BOOST_DEDUCED_TYPENAME range_iterator<const ForwardRange>::type
lower_bound( const ForwardRange& rng, const Value& val, SortPredicate pred )
{
    BOOST_RANGE_CONCEPT_ASSERT(( ForwardRangeConcept<const ForwardRange> ));
    return std::lower_bound(boost::begin(rng), boost::end(rng), val, pred);
}

/// \overload
template< range_return_value re, class ForwardRange, class Value >
inline BOOST_DEDUCED_TYPENAME disable_if<
    is_const<ForwardRange>,
    BOOST_DEDUCED_TYPENAME range_return<ForwardRange,re>::type
>::type
lower_bound( ForwardRange& rng, const Value& val )
{
    BOOST_RANGE_CONCEPT_ASSERT(( ForwardRangeConcept<ForwardRange> ));
    return range_return<ForwardRange,re>::
        pack(std::lower_bound(boost::begin(rng), boost::end(rng), val),
             rng);
}

/// \overload
template< range_return_value re, class ForwardRange, class Value >
inline BOOST_DEDUCED_TYPENAME range_return<const ForwardRange,re>::type
lower_bound( const ForwardRange& rng, const Value& val )
{
    BOOST_RANGE_CONCEPT_ASSERT(( ForwardRangeConcept<const ForwardRange> ));
    return range_return<const ForwardRange,re>::
        pack(std::lower_bound(boost::begin(rng), boost::end(rng), val),
             rng);
}

/// \overload
template< range_return_value re, class ForwardRange, class Value, class SortPredicate >
inline BOOST_DEDUCED_TYPENAME disable_if<
    is_const<ForwardRange>,
    BOOST_DEDUCED_TYPENAME range_return<ForwardRange,re>::type
>::type
lower_bound( ForwardRange& rng, const Value& val, SortPredicate pred )
{
    BOOST_RANGE_CONCEPT_ASSERT(( ForwardRangeConcept<ForwardRange> ));
    return range_return<ForwardRange,re>::
        pack(std::lower_bound(boost::begin(rng), boost::end(rng), val, pred),
             rng);
}

/// \overload
template< range_return_value re, class ForwardRange, class Value, class SortPredicate >
inline BOOST_DEDUCED_TYPENAME range_return<const ForwardRange,re>::type
lower_bound( const ForwardRange& rng, const Value& val, SortPredicate pred )
{
    BOOST_RANGE_CONCEPT_ASSERT(( ForwardRangeConcept<const ForwardRange> ));
    return range_return<const ForwardRange,re>::
        pack(std::lower_bound(boost::begin(rng), boost::end(rng), val, pred),
             rng);
}

    } // namespace range
    using range::lower_bound;
} // namespace boost

#endif // include guard

/* lower_bound.hpp
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
*/