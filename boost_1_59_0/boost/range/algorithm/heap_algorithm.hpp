//  Copyright Neil Groves 2009. Use, modification and
//  distribution is subject to the Boost Software License, Version
//  1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
//
// For more information, see http://www.boost.org/libs/range/
//
#ifndef BOOST_RANGE_ALGORITHM_HEAP_ALGORITHM_HPP_INCLUDED
#define BOOST_RANGE_ALGORITHM_HEAP_ALGORITHM_HPP_INCLUDED

#include <boost/concept_check.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/concepts.hpp>
#include <algorithm>

namespace boost
{
    namespace range
    {

/// \brief template function push_heap
///
/// range-based version of the push_heap std algorithm
///
/// \pre RandomAccessRange is a model of the RandomAccessRangeConcept
/// \pre Compare is a model of the BinaryPredicateConcept
template<class RandomAccessRange>
inline RandomAccessRange& push_heap(RandomAccessRange& rng)
{
    BOOST_RANGE_CONCEPT_ASSERT(( RandomAccessRangeConcept<RandomAccessRange> ));
    std::push_heap(boost::begin(rng), boost::end(rng));
    return rng;
}

/// \overload
template<class RandomAccessRange>
inline const RandomAccessRange& push_heap(const RandomAccessRange& rng)
{
    BOOST_RANGE_CONCEPT_ASSERT(( RandomAccessRangeConcept<const RandomAccessRange> ));
    std::push_heap(boost::begin(rng), boost::end(rng));
    return rng;
}

/// \overload
template<class RandomAccessRange, class Compare>
inline RandomAccessRange& push_heap(RandomAccessRange& rng, Compare comp_pred)
{
    BOOST_RANGE_CONCEPT_ASSERT(( RandomAccessRangeConcept<RandomAccessRange> ));
    std::push_heap(boost::begin(rng), boost::end(rng), comp_pred);
    return rng;
}

/// \overload
template<class RandomAccessRange, class Compare>
inline const RandomAccessRange& push_heap(const RandomAccessRange& rng, Compare comp_pred)
{
    BOOST_RANGE_CONCEPT_ASSERT(( RandomAccessRangeConcept<const RandomAccessRange> ));
    std::push_heap(boost::begin(rng), boost::end(rng), comp_pred);
    return rng;
}

/// \brief template function pop_heap
///
/// range-based version of the pop_heap std algorithm
///
/// \pre RandomAccessRange is a model of the RandomAccessRangeConcept
/// \pre Compare is a model of the BinaryPredicateConcept
template<class RandomAccessRange>
inline RandomAccessRange& pop_heap(RandomAccessRange& rng)
{
    BOOST_RANGE_CONCEPT_ASSERT(( RandomAccessRangeConcept<RandomAccessRange> ));
    std::pop_heap(boost::begin(rng), boost::end(rng));
    return rng;
}

/// \overload
template<class RandomAccessRange>
inline const RandomAccessRange& pop_heap(const RandomAccessRange& rng)
{
    BOOST_RANGE_CONCEPT_ASSERT(( RandomAccessRangeConcept<const RandomAccessRange> ));
    std::pop_heap(boost::begin(rng), boost::end(rng));
    return rng;
}

/// \overload
template<class RandomAccessRange, class Compare>
inline RandomAccessRange& pop_heap(RandomAccessRange& rng, Compare comp_pred)
{
    BOOST_RANGE_CONCEPT_ASSERT(( RandomAccessRangeConcept<RandomAccessRange> ));
    std::pop_heap(boost::begin(rng), boost::end(rng), comp_pred);
    return rng;
}

/// \overload
template<class RandomAccessRange, class Compare>
inline const RandomAccessRange& pop_heap(const RandomAccessRange& rng, Compare comp_pred)
{
    BOOST_RANGE_CONCEPT_ASSERT(( RandomAccessRangeConcept<const RandomAccessRange> ));
    std::pop_heap(boost::begin(rng), boost::end(rng), comp_pred);
    return rng;
}

/// \brief template function make_heap
///
/// range-based version of the make_heap std algorithm
///
/// \pre RandomAccessRange is a model of the RandomAccessRangeConcept
/// \pre Compare is a model of the BinaryPredicateConcept
template<class RandomAccessRange>
inline RandomAccessRange& make_heap(RandomAccessRange& rng)
{
    BOOST_RANGE_CONCEPT_ASSERT(( RandomAccessRangeConcept<RandomAccessRange> ));
    std::make_heap(boost::begin(rng), boost::end(rng));
    return rng;
}

/// \overload
template<class RandomAccessRange>
inline const RandomAccessRange& make_heap(const RandomAccessRange& rng)
{
    BOOST_RANGE_CONCEPT_ASSERT(( RandomAccessRangeConcept<const RandomAccessRange> ));
    std::make_heap(boost::begin(rng), boost::end(rng));
    return rng;
}

/// \overload
template<class RandomAccessRange, class Compare>
inline RandomAccessRange& make_heap(RandomAccessRange& rng, Compare comp_pred)
{
    BOOST_RANGE_CONCEPT_ASSERT(( RandomAccessRangeConcept<RandomAccessRange> ));
    std::make_heap(boost::begin(rng), boost::end(rng), comp_pred);
    return rng;
}

/// \overload
template<class RandomAccessRange, class Compare>
inline const RandomAccessRange& make_heap(const RandomAccessRange& rng, Compare comp_pred)
{
    BOOST_RANGE_CONCEPT_ASSERT(( RandomAccessRangeConcept<const RandomAccessRange> ));
    std::make_heap(boost::begin(rng), boost::end(rng), comp_pred);
    return rng;
}

/// \brief template function sort_heap
///
/// range-based version of the sort_heap std algorithm
///
/// \pre RandomAccessRange is a model of the RandomAccessRangeConcept
/// \pre Compare is a model of the BinaryPredicateConcept
template<class RandomAccessRange>
inline RandomAccessRange& sort_heap(RandomAccessRange& rng)
{
    BOOST_RANGE_CONCEPT_ASSERT(( RandomAccessRangeConcept<RandomAccessRange> ));
    std::sort_heap(boost::begin(rng), boost::end(rng));
    return rng;
}

/// \overload
template<class RandomAccessRange>
inline const RandomAccessRange& sort_heap(const RandomAccessRange& rng)
{
    BOOST_RANGE_CONCEPT_ASSERT(( RandomAccessRangeConcept<const RandomAccessRange> ));
    std::sort_heap(boost::begin(rng), boost::end(rng));
    return rng;
}

/// \overload
template<class RandomAccessRange, class Compare>
inline RandomAccessRange& sort_heap(RandomAccessRange& rng, Compare comp_pred)
{
    BOOST_RANGE_CONCEPT_ASSERT(( RandomAccessRangeConcept<RandomAccessRange> ));
    std::sort_heap(boost::begin(rng), boost::end(rng), comp_pred);
    return rng;
}

/// \overload
template<class RandomAccessRange, class Compare>
inline const RandomAccessRange& sort_heap(const RandomAccessRange& rng, Compare comp_pred)
{
    BOOST_RANGE_CONCEPT_ASSERT(( RandomAccessRangeConcept<const RandomAccessRange> ));
    std::sort_heap(boost::begin(rng), boost::end(rng), comp_pred);
    return rng;
}

    } // namespace range
    using range::push_heap;
    using range::pop_heap;
    using range::make_heap;
    using range::sort_heap;
} // namespace boost

#endif // include guard

/* heap_algorithm.hpp
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
*/