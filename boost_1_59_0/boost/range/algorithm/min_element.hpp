//  Copyright Neil Groves 2009. Use, modification and
//  distribution is subject to the Boost Software License, Version
//  1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
// Copyright 2019 Glen Joseph Fernandes (glenjofe@gmail.com)
//
// For more information, see http://www.boost.org/libs/range/
//
#ifndef BOOST_RANGE_ALGORITHM_MIN_ELEMENT_HPP_INCLUDED
#define BOOST_RANGE_ALGORITHM_MIN_ELEMENT_HPP_INCLUDED

#include <boost/concept_check.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/concepts.hpp>
#include <boost/range/detail/less.hpp>
#include <boost/range/detail/range_return.hpp>

namespace boost
{
    namespace range
    {

namespace detail
{

template<typename Iterator, class Predicate>
inline Iterator
min_element(Iterator first, Iterator last, Predicate comp)
{
    if (first == last) {
        return last;
    }
    Iterator result = first;
    while (++first != last) {
        if (comp(*first, *result)) {
            result = first;
        }
    }
    return result;
}

} // namespace detail

/// \brief template function min_element
///
/// range-based version of the min_element std algorithm
///
/// \pre ForwardRange is a model of the ForwardRangeConcept
/// \pre BinaryPredicate is a model of the BinaryPredicateConcept
template<class ForwardRange>
inline BOOST_DEDUCED_TYPENAME range_iterator<ForwardRange>::type
min_element(ForwardRange& rng)
{
    BOOST_RANGE_CONCEPT_ASSERT(( ForwardRangeConcept<ForwardRange> ));
    return detail::min_element(boost::begin(rng), boost::end(rng), detail::less());
}

/// \overload
template<class ForwardRange>
inline BOOST_DEDUCED_TYPENAME range_iterator<const ForwardRange>::type
min_element(const ForwardRange& rng)
{
    BOOST_RANGE_CONCEPT_ASSERT(( ForwardRangeConcept<const ForwardRange> ));
    return detail::min_element(boost::begin(rng), boost::end(rng), detail::less());
}

/// \overload
template<class ForwardRange, class BinaryPredicate>
inline BOOST_DEDUCED_TYPENAME range_iterator<ForwardRange>::type
min_element(ForwardRange& rng, BinaryPredicate pred)
{
    BOOST_RANGE_CONCEPT_ASSERT(( ForwardRangeConcept<ForwardRange> ));
    return detail::min_element(boost::begin(rng), boost::end(rng), pred);
}

/// \overload
template<class ForwardRange, class BinaryPredicate>
inline BOOST_DEDUCED_TYPENAME range_iterator<const ForwardRange>::type
min_element(const ForwardRange& rng, BinaryPredicate pred)
{
    BOOST_RANGE_CONCEPT_ASSERT(( ForwardRangeConcept<const ForwardRange> ));
    return detail::min_element(boost::begin(rng), boost::end(rng), pred);
}

// range_return overloads

/// \overload
template<range_return_value re, class ForwardRange>
inline BOOST_DEDUCED_TYPENAME range_return<ForwardRange,re>::type
min_element(ForwardRange& rng)
{
    BOOST_RANGE_CONCEPT_ASSERT(( ForwardRangeConcept<ForwardRange> ));
    return range_return<ForwardRange,re>::pack(
        detail::min_element(boost::begin(rng), boost::end(rng), detail::less()),
        rng);
}

/// \overload
template<range_return_value re, class ForwardRange>
inline BOOST_DEDUCED_TYPENAME range_return<const ForwardRange,re>::type
min_element(const ForwardRange& rng)
{
    BOOST_RANGE_CONCEPT_ASSERT(( ForwardRangeConcept<const ForwardRange> ));
    return range_return<const ForwardRange,re>::pack(
        detail::min_element(boost::begin(rng), boost::end(rng), detail::less()),
        rng);
}

/// \overload
template<range_return_value re, class ForwardRange, class BinaryPredicate>
inline BOOST_DEDUCED_TYPENAME range_return<ForwardRange,re>::type
min_element(ForwardRange& rng, BinaryPredicate pred)
{
    BOOST_RANGE_CONCEPT_ASSERT(( ForwardRangeConcept<ForwardRange> ));
    return range_return<ForwardRange,re>::pack(
        detail::min_element(boost::begin(rng), boost::end(rng), pred),
        rng);
}

/// \overload
template<range_return_value re, class ForwardRange, class BinaryPredicate>
inline BOOST_DEDUCED_TYPENAME range_return<const ForwardRange,re>::type
min_element(const ForwardRange& rng, BinaryPredicate pred)
{
    BOOST_RANGE_CONCEPT_ASSERT(( ForwardRangeConcept<const ForwardRange> ));
    return range_return<const ForwardRange,re>::pack(
        detail::min_element(boost::begin(rng), boost::end(rng), pred),
        rng);
}

    } // namespace range
    using range::min_element;
} // namespace boost

#endif // include guard

/* min_element.hpp
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
*/