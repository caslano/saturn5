//  Copyright Neil Groves 2009. Use, modification and
//  distribution is subject to the Boost Software License, Version
//  1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
//
// For more information, see http://www.boost.org/libs/range/
//
#ifndef BOOST_RANGE_ALGORITHM_PERMUTATION_HPP_INCLUDED
#define BOOST_RANGE_ALGORITHM_PERMUTATION_HPP_INCLUDED

#include <boost/concept_check.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/concepts.hpp>
#include <algorithm>

namespace boost
{
    namespace range
    {

/// \brief template function next_permutation
///
/// range-based version of the next_permutation std algorithm
///
/// \pre BidirectionalRange is a model of the BidirectionalRangeConcept
/// \pre Compare is a model of the BinaryPredicateConcept
template<class BidirectionalRange>
inline bool next_permutation(BidirectionalRange& rng)
{
    BOOST_RANGE_CONCEPT_ASSERT(( BidirectionalRangeConcept<BidirectionalRange> ));
    return std::next_permutation(boost::begin(rng), boost::end(rng));
}

/// \overload
template<class BidirectionalRange>
inline bool next_permutation(const BidirectionalRange& rng)
{
    BOOST_RANGE_CONCEPT_ASSERT(( BidirectionalRangeConcept<const BidirectionalRange> ));
    return std::next_permutation(boost::begin(rng), boost::end(rng));
}

/// \overload
template<class BidirectionalRange, class Compare>
inline bool next_permutation(BidirectionalRange& rng, Compare comp_pred)
{
    BOOST_RANGE_CONCEPT_ASSERT(( BidirectionalRangeConcept<BidirectionalRange> ));
    return std::next_permutation(boost::begin(rng), boost::end(rng),
                                 comp_pred);
}

/// \overload
template<class BidirectionalRange, class Compare>
inline bool next_permutation(const BidirectionalRange& rng,
                             Compare                   comp_pred)
{
    BOOST_RANGE_CONCEPT_ASSERT(( BidirectionalRangeConcept<const BidirectionalRange> ));
    return std::next_permutation(boost::begin(rng), boost::end(rng),
                                 comp_pred);
}

/// \brief template function prev_permutation
///
/// range-based version of the prev_permutation std algorithm
///
/// \pre BidirectionalRange is a model of the BidirectionalRangeConcept
/// \pre Compare is a model of the BinaryPredicateConcept
template<class BidirectionalRange>
inline bool prev_permutation(BidirectionalRange& rng)
{
    BOOST_RANGE_CONCEPT_ASSERT(( BidirectionalRangeConcept<BidirectionalRange> ));
    return std::prev_permutation(boost::begin(rng), boost::end(rng));
}

/// \overload
template<class BidirectionalRange>
inline bool prev_permutation(const BidirectionalRange& rng)
{
    BOOST_RANGE_CONCEPT_ASSERT(( BidirectionalRangeConcept<const BidirectionalRange> ));
    return std::prev_permutation(boost::begin(rng), boost::end(rng));
}

/// \overload
template<class BidirectionalRange, class Compare>
inline bool prev_permutation(BidirectionalRange& rng, Compare comp_pred)
{
    BOOST_RANGE_CONCEPT_ASSERT(( BidirectionalRangeConcept<BidirectionalRange> ));
    return std::prev_permutation(boost::begin(rng), boost::end(rng),
                                 comp_pred);
}

/// \overload
template<class BidirectionalRange, class Compare>
inline bool prev_permutation(const BidirectionalRange& rng,
                             Compare                   comp_pred)
{
    BOOST_RANGE_CONCEPT_ASSERT(( BidirectionalRangeConcept<const BidirectionalRange> ));
    return std::prev_permutation(boost::begin(rng), boost::end(rng),
                                 comp_pred);
}

    } // namespace range
    using range::next_permutation;
    using range::prev_permutation;
} // namespace boost

#endif // include guard

/* permutation.hpp
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
*/