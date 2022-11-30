//  Copyright Neil Groves 2009. Use, modification and
//  distribution is subject to the Boost Software License, Version
//  1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
//
// For more information, see http://www.boost.org/libs/range/
//
#ifndef BOOST_RANGE_ALGORITHM_SEARCH_HPP_INCLUDED
#define BOOST_RANGE_ALGORITHM_SEARCH_HPP_INCLUDED

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

/// \brief template function search
///
/// range-based version of the search std algorithm
///
/// \pre ForwardRange1 is a model of the ForwardRangeConcept
/// \pre ForwardRange2 is a model of the ForwardRangeConcept
/// \pre BinaryPredicate is a model of the BinaryPredicateConcept
template< class ForwardRange1, class ForwardRange2 >
inline BOOST_DEDUCED_TYPENAME range_iterator<ForwardRange1>::type
search(ForwardRange1& rng1, const ForwardRange2& rng2)
{
    BOOST_RANGE_CONCEPT_ASSERT(( ForwardRangeConcept<ForwardRange1> ));
    BOOST_RANGE_CONCEPT_ASSERT(( ForwardRangeConcept<const ForwardRange2> ));
    return std::search(boost::begin(rng1),boost::end(rng1),
                       boost::begin(rng2),boost::end(rng2));
}

/// \overload
template< class ForwardRange1, class ForwardRange2 >
inline BOOST_DEDUCED_TYPENAME range_iterator<const ForwardRange1>::type
search(const ForwardRange1& rng1, const ForwardRange2& rng2)
{
    BOOST_RANGE_CONCEPT_ASSERT(( ForwardRangeConcept<const ForwardRange1> ));
    BOOST_RANGE_CONCEPT_ASSERT(( ForwardRangeConcept<const ForwardRange2> ));
    return std::search(boost::begin(rng1), boost::end(rng1),
                       boost::begin(rng2), boost::end(rng2));
}

/// \overload
template< class ForwardRange1, class ForwardRange2, class BinaryPredicate >
inline BOOST_DEDUCED_TYPENAME range_iterator<ForwardRange1>::type
search(ForwardRange1& rng1, const ForwardRange2& rng2, BinaryPredicate pred)
{
    BOOST_RANGE_CONCEPT_ASSERT(( ForwardRangeConcept<ForwardRange1> ));
    BOOST_RANGE_CONCEPT_ASSERT(( ForwardRangeConcept<const ForwardRange2> ));
    return std::search(boost::begin(rng1),boost::end(rng1),
                       boost::begin(rng2),boost::end(rng2),pred);
}

/// \overload
template< class ForwardRange1, class ForwardRange2, class BinaryPredicate >
inline BOOST_DEDUCED_TYPENAME range_iterator<const ForwardRange1>::type
search(const ForwardRange1& rng1, const ForwardRange2& rng2, BinaryPredicate pred)
{
    BOOST_RANGE_CONCEPT_ASSERT(( ForwardRangeConcept<const ForwardRange1> ));
    BOOST_RANGE_CONCEPT_ASSERT(( ForwardRangeConcept<const ForwardRange2> ));
    return std::search(boost::begin(rng1), boost::end(rng1),
                       boost::begin(rng2), boost::end(rng2), pred);
}

// range_return overloads

/// \overload
template< range_return_value re, class ForwardRange1, class ForwardRange2 >
inline BOOST_DEDUCED_TYPENAME range_return<ForwardRange1,re>::type
search(ForwardRange1& rng1, const ForwardRange2& rng2)
{
    BOOST_RANGE_CONCEPT_ASSERT(( ForwardRangeConcept<ForwardRange1> ));
    BOOST_RANGE_CONCEPT_ASSERT(( ForwardRangeConcept<const ForwardRange2> ));
    return range_return<ForwardRange1,re>::
        pack(std::search(boost::begin(rng1),boost::end(rng1),
                         boost::begin(rng2),boost::end(rng2)),
             rng1);
}

/// \overload
template< range_return_value re, class ForwardRange1, class ForwardRange2 >
inline BOOST_DEDUCED_TYPENAME range_return<const ForwardRange1,re>::type
search(const ForwardRange1& rng1, const ForwardRange2& rng2)
{
    BOOST_RANGE_CONCEPT_ASSERT(( ForwardRangeConcept<const ForwardRange1> ));
    BOOST_RANGE_CONCEPT_ASSERT(( ForwardRangeConcept<const ForwardRange2> ));
    return range_return<const ForwardRange1,re>::
        pack(std::search(boost::begin(rng1),boost::end(rng1),
                         boost::begin(rng2),boost::end(rng2)),
             rng1);
}

/// \overload
template< range_return_value re, class ForwardRange1, class ForwardRange2,
          class BinaryPredicate >
inline BOOST_DEDUCED_TYPENAME range_return<ForwardRange1,re>::type
search(ForwardRange1& rng1, const ForwardRange2& rng2, BinaryPredicate pred)
{
    BOOST_RANGE_CONCEPT_ASSERT(( ForwardRangeConcept<ForwardRange1> ));
    BOOST_RANGE_CONCEPT_ASSERT(( ForwardRangeConcept<const ForwardRange2> ));
    return range_return<ForwardRange1,re>::
        pack(std::search(boost::begin(rng1),boost::end(rng1),
                         boost::begin(rng2),boost::end(rng2),pred),
             rng1);
}

/// \overload
template< range_return_value re, class ForwardRange1, class ForwardRange2,
          class BinaryPredicate >
inline BOOST_DEDUCED_TYPENAME range_return<const ForwardRange1,re>::type
search(const ForwardRange1& rng1, const ForwardRange2& rng2, BinaryPredicate pred)
{
    BOOST_RANGE_CONCEPT_ASSERT(( ForwardRangeConcept<const ForwardRange1> ));
    BOOST_RANGE_CONCEPT_ASSERT(( ForwardRangeConcept<const ForwardRange2> ));
    return range_return<const ForwardRange1,re>::
        pack(std::search(boost::begin(rng1),boost::end(rng1),
                         boost::begin(rng2),boost::end(rng2),pred),
             rng1);
}

    } // namespace range
    using range::search;
} // namespace boost

#endif // include guard

/* search.hpp
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
*/