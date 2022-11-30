//  Copyright Neil Groves 2009. Use, modification and
//  distribution is subject to the Boost Software License, Version
//  1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
// Copyright 2019 Glen Joseph Fernandes (glenjofe@gmail.com)
//
// For more information, see http://www.boost.org/libs/range/
//
#ifndef BOOST_RANGE_ALGORITHM_MAX_ELEMENT_HPP_INCLUDED
#define BOOST_RANGE_ALGORITHM_MAX_ELEMENT_HPP_INCLUDED

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
max_element(Iterator first, Iterator last, Predicate comp)
{
    if (first == last) {
        return last;
    }
    Iterator result = first;
    while (++first != last) {
        if (comp(*result, *first)) {
            result = first;
        }
    }
    return result;
}

} // namespace detail

/// \brief template function max_element
///
/// range-based version of the max_element std algorithm
///
/// \pre ForwardRange is a model of the ForwardRangeConcept
/// \pre BinaryPredicate is a model of the BinaryPredicateConcept
template<class ForwardRange>
inline BOOST_DEDUCED_TYPENAME range_iterator<ForwardRange>::type
max_element(ForwardRange& rng)
{
    BOOST_RANGE_CONCEPT_ASSERT(( ForwardRangeConcept<ForwardRange> ));
    return detail::max_element(boost::begin(rng), boost::end(rng), detail::less());
}

/// \overload
template<class ForwardRange>
inline BOOST_DEDUCED_TYPENAME range_iterator<const ForwardRange>::type
max_element(const ForwardRange& rng)
{
    BOOST_RANGE_CONCEPT_ASSERT(( ForwardRangeConcept<const ForwardRange> ));
    return detail::max_element(boost::begin(rng), boost::end(rng), detail::less());
}

/// \overload
template<class ForwardRange, class BinaryPredicate>
inline BOOST_DEDUCED_TYPENAME range_iterator<ForwardRange>::type
max_element(ForwardRange& rng, BinaryPredicate pred)
{
    BOOST_RANGE_CONCEPT_ASSERT(( ForwardRangeConcept<ForwardRange> ));
    return detail::max_element(boost::begin(rng), boost::end(rng), pred);
}

/// \overload
template<class ForwardRange, class BinaryPredicate>
inline BOOST_DEDUCED_TYPENAME range_iterator<const ForwardRange>::type
max_element(const ForwardRange& rng, BinaryPredicate pred)
{
    BOOST_RANGE_CONCEPT_ASSERT(( ForwardRangeConcept<const ForwardRange> ));
    return detail::max_element(boost::begin(rng), boost::end(rng), pred);
}

// range_return overloads

/// \overload
template<range_return_value re, class ForwardRange>
inline BOOST_DEDUCED_TYPENAME range_return<ForwardRange,re>::type
max_element(ForwardRange& rng)
{
    BOOST_RANGE_CONCEPT_ASSERT(( ForwardRangeConcept<ForwardRange> ));
    return range_return<ForwardRange,re>::pack(
        detail::max_element(boost::begin(rng), boost::end(rng), detail::less()),
        rng);
}

/// \overload
template<range_return_value re, class ForwardRange>
inline BOOST_DEDUCED_TYPENAME range_return<const ForwardRange,re>::type
max_element(const ForwardRange& rng)
{
    BOOST_RANGE_CONCEPT_ASSERT(( ForwardRangeConcept<const ForwardRange> ));
    return range_return<const ForwardRange,re>::pack(
        detail::max_element(boost::begin(rng), boost::end(rng), detail::less()),
        rng);
}

/// \overload
template<range_return_value re, class ForwardRange, class BinaryPredicate>
inline BOOST_DEDUCED_TYPENAME range_return<ForwardRange,re>::type
max_element(ForwardRange& rng, BinaryPredicate pred)
{
    BOOST_RANGE_CONCEPT_ASSERT(( ForwardRangeConcept<ForwardRange> ));
    return range_return<ForwardRange,re>::pack(
        detail::max_element(boost::begin(rng), boost::end(rng), pred),
        rng);
}

/// \overload
template<range_return_value re, class ForwardRange, class BinaryPredicate>
inline BOOST_DEDUCED_TYPENAME range_return<const ForwardRange,re>::type
max_element(const ForwardRange& rng, BinaryPredicate pred)
{
    BOOST_RANGE_CONCEPT_ASSERT(( ForwardRangeConcept<const ForwardRange> ));
    return range_return<const ForwardRange,re>::pack(
        detail::max_element(boost::begin(rng), boost::end(rng), pred),
        rng);
}

    } // namespace range
    using range::max_element;
} // namespace boost

#endif // include guard

/* max_element.hpp
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
*/