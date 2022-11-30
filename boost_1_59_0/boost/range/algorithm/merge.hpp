//  Copyright Neil Groves 2009. Use, modification and
//  distribution is subject to the Boost Software License, Version
//  1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
//
// For more information, see http://www.boost.org/libs/range/
//
#ifndef BOOST_RANGE_ALGORITHM_MERGE_HPP_INCLUDED
#define BOOST_RANGE_ALGORITHM_MERGE_HPP_INCLUDED

#include <boost/concept_check.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/concepts.hpp>
#include <algorithm>

namespace boost
{
    namespace range
    {

/// \brief template function merge
///
/// range-based version of the merge std algorithm
///
/// \pre SinglePassRange1 is a model of the SinglePassRangeConcept
/// \pre SinglePassRange2 is a model of the SinglePassRangeConcept
/// \pre BinaryPredicate is a model of the BinaryPredicateConcept
///
template<class SinglePassRange1, class SinglePassRange2,
         class OutputIterator>
inline OutputIterator merge(const SinglePassRange1& rng1,
                            const SinglePassRange2& rng2,
                            OutputIterator          out)
{
    BOOST_RANGE_CONCEPT_ASSERT(( SinglePassRangeConcept<const SinglePassRange1> ));
    BOOST_RANGE_CONCEPT_ASSERT(( SinglePassRangeConcept<const SinglePassRange2> ));
    return std::merge(boost::begin(rng1), boost::end(rng1),
                      boost::begin(rng2), boost::end(rng2), out);
}

/// \overload
template<class SinglePassRange1, class SinglePassRange2,
         class OutputIterator, class BinaryPredicate>
inline OutputIterator merge(const SinglePassRange1& rng1,
                            const SinglePassRange2& rng2,
                            OutputIterator          out,
                            BinaryPredicate         pred)
{
    BOOST_RANGE_CONCEPT_ASSERT(( SinglePassRangeConcept<const SinglePassRange1> ));
    BOOST_RANGE_CONCEPT_ASSERT(( SinglePassRangeConcept<const SinglePassRange2> ));
    return std::merge(boost::begin(rng1), boost::end(rng1),
                      boost::begin(rng2), boost::end(rng2), out, pred);
}

    } // namespace range
    using range::merge;
} // namespace boost

#endif // include guard

/* merge.hpp
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
*/