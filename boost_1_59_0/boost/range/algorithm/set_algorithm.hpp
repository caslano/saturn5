//  Copyright Neil Groves 2009. Use, modification and
//  distribution is subject to the Boost Software License, Version
//  1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
//
// For more information, see http://www.boost.org/libs/range/
//
#ifndef BOOST_RANGE_ALGORITHM_SET_ALGORITHM_HPP_INCLUDED
#define BOOST_RANGE_ALGORITHM_SET_ALGORITHM_HPP_INCLUDED

#include <boost/concept_check.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/concepts.hpp>
#include <algorithm>

namespace boost
{
    namespace range
    {

/// \brief template function includes
///
/// range-based version of the includes std algorithm
///
/// \pre SinglePassRange1 is a model of the SinglePassRangeConcept
/// \pre SinglePassRange2 is a model of the SinglePassRangeConcept
/// \pre BinaryPredicate is a model of the BinaryPredicateConcept
template<class SinglePassRange1, class SinglePassRange2>
inline bool includes(const SinglePassRange1& rng1,
                     const SinglePassRange2& rng2)
{
    BOOST_RANGE_CONCEPT_ASSERT(( SinglePassRangeConcept<const SinglePassRange1> ));
    BOOST_RANGE_CONCEPT_ASSERT(( SinglePassRangeConcept<const SinglePassRange2> ));
    return std::includes(boost::begin(rng1),boost::end(rng1),
                         boost::begin(rng2),boost::end(rng2));
}

/// \overload
template<class SinglePassRange1, class SinglePassRange2,
         class BinaryPredicate>
inline bool includes(const SinglePassRange1& rng1,
                     const SinglePassRange2& rng2,
                     BinaryPredicate         pred)
{
    BOOST_RANGE_CONCEPT_ASSERT(( SinglePassRangeConcept<const SinglePassRange1> ));
    BOOST_RANGE_CONCEPT_ASSERT(( SinglePassRangeConcept<const SinglePassRange2> ));
    return std::includes(boost::begin(rng1), boost::end(rng1),
                         boost::begin(rng2), boost::end(rng2), pred);
}

/// \brief template function set_union
///
/// range-based version of the set_union std algorithm
///
/// \pre SinglePassRange1 is a model of the SinglePassRangeConcept
/// \pre SinglePassRange2 is a model of the SinglePassRangeConcept
/// \pre BinaryPredicate is a model of the BinaryPredicateConcept
template<class SinglePassRange1, class SinglePassRange2,
         class OutputIterator>
inline OutputIterator set_union(const SinglePassRange1& rng1,
                                const SinglePassRange2& rng2,
                                OutputIterator          out)
{
    BOOST_RANGE_CONCEPT_ASSERT(( SinglePassRangeConcept<const SinglePassRange1> ));
    BOOST_RANGE_CONCEPT_ASSERT(( SinglePassRangeConcept<const SinglePassRange2> ));
    return std::set_union(boost::begin(rng1), boost::end(rng1),
                          boost::begin(rng2), boost::end(rng2), out);
}

/// \overload
template<class SinglePassRange1, class SinglePassRange2,
         class OutputIterator, class BinaryPredicate>
inline OutputIterator set_union(const SinglePassRange1& rng1,
                                const SinglePassRange2& rng2,
                                OutputIterator          out,
                                BinaryPredicate         pred)
{
    BOOST_RANGE_CONCEPT_ASSERT(( SinglePassRangeConcept<const SinglePassRange1> ));
    BOOST_RANGE_CONCEPT_ASSERT(( SinglePassRangeConcept<const SinglePassRange2> ));
    return std::set_union(boost::begin(rng1), boost::end(rng1),
                          boost::begin(rng2), boost::end(rng2), out, pred);
}

/// \brief template function set_intersection
///
/// range-based version of the set_intersection std algorithm
///
/// \pre SinglePassRange1 is a model of the SinglePassRangeConcept
/// \pre SinglePassRange2 is a model of the SinglePassRangeConcept
/// \pre BinaryPredicate is a model of the BinaryPredicateConcept
template<class SinglePassRange1, class SinglePassRange2,
         class OutputIterator>
inline OutputIterator set_intersection(const SinglePassRange1& rng1,
                                       const SinglePassRange2& rng2,
                                       OutputIterator          out)
{
    BOOST_RANGE_CONCEPT_ASSERT(( SinglePassRangeConcept<const SinglePassRange1> ));
    BOOST_RANGE_CONCEPT_ASSERT(( SinglePassRangeConcept<const SinglePassRange2> ));
    return std::set_intersection(boost::begin(rng1), boost::end(rng1),
                                 boost::begin(rng2), boost::end(rng2), out);
}

/// \overload
template<class SinglePassRange1, class SinglePassRange2,
         class OutputIterator, class BinaryPredicate>
inline OutputIterator set_intersection(const SinglePassRange1& rng1,
                                       const SinglePassRange2& rng2,
                                       OutputIterator          out,
                                       BinaryPredicate         pred)
{
    BOOST_RANGE_CONCEPT_ASSERT(( SinglePassRangeConcept<const SinglePassRange1> ));
    BOOST_RANGE_CONCEPT_ASSERT(( SinglePassRangeConcept<const SinglePassRange2> ));
    return std::set_intersection(boost::begin(rng1), boost::end(rng1),
                                 boost::begin(rng2), boost::end(rng2),
                                 out, pred);
}

/// \brief template function set_difference
///
/// range-based version of the set_difference std algorithm
///
/// \pre SinglePassRange1 is a model of the SinglePassRangeConcept
/// \pre SinglePassRange2 is a model of the SinglePassRangeConcept
/// \pre BinaryPredicate is a model of the BinaryPredicateConcept
template<class SinglePassRange1, class SinglePassRange2,
         class OutputIterator>
inline OutputIterator set_difference(const SinglePassRange1& rng1,
                                     const SinglePassRange2& rng2,
                                     OutputIterator out)
{
    BOOST_RANGE_CONCEPT_ASSERT(( SinglePassRangeConcept<const SinglePassRange1> ));
    BOOST_RANGE_CONCEPT_ASSERT(( SinglePassRangeConcept<const SinglePassRange2> ));
    return std::set_difference(boost::begin(rng1), boost::end(rng1),
                               boost::begin(rng2), boost::end(rng2), out);
}

/// \overload
template<class SinglePassRange1, class SinglePassRange2,
         class OutputIterator, class BinaryPredicate>
inline OutputIterator set_difference(const SinglePassRange1& rng1,
                                     const SinglePassRange2& rng2,
                                     OutputIterator          out,
                                     BinaryPredicate         pred)
{
    BOOST_RANGE_CONCEPT_ASSERT(( SinglePassRangeConcept<const SinglePassRange1> ));
    BOOST_RANGE_CONCEPT_ASSERT(( SinglePassRangeConcept<const SinglePassRange2> ));
    return std::set_difference(
        boost::begin(rng1), boost::end(rng1),
        boost::begin(rng2), boost::end(rng2), out, pred);
}

/// \brief template function set_symmetric_difference
///
/// range-based version of the set_symmetric_difference std algorithm
///
/// \pre SinglePassRange1 is a model of the SinglePassRangeConcept
/// \pre SinglePassRange2 is a model of the SinglePassRangeConcept
/// \pre BinaryPredicate is a model of the BinaryPredicateConcept
template<class SinglePassRange1, class SinglePassRange2,
         class OutputIterator>
inline OutputIterator
set_symmetric_difference(const SinglePassRange1& rng1,
                         const SinglePassRange2& rng2,
                         OutputIterator          out)
{
    BOOST_RANGE_CONCEPT_ASSERT(( SinglePassRangeConcept<const SinglePassRange1> ));
    BOOST_RANGE_CONCEPT_ASSERT(( SinglePassRangeConcept<const SinglePassRange2> ));
    return std::set_symmetric_difference(boost::begin(rng1), boost::end(rng1),
                                         boost::begin(rng2), boost::end(rng2), out);
}

/// \overload
template<class SinglePassRange1, class SinglePassRange2,
         class OutputIterator, class BinaryPredicate>
inline OutputIterator
set_symmetric_difference(const SinglePassRange1& rng1,
                         const SinglePassRange2& rng2,
                         OutputIterator          out,
                         BinaryPredicate         pred)
{
    BOOST_RANGE_CONCEPT_ASSERT(( SinglePassRangeConcept<const SinglePassRange1> ));
    BOOST_RANGE_CONCEPT_ASSERT(( SinglePassRangeConcept<const SinglePassRange2> ));
    return std::set_symmetric_difference(
        boost::begin(rng1), boost::end(rng1),
        boost::begin(rng2), boost::end(rng2), out, pred);
}

    } // namespace range
    using range::includes;
    using range::set_union;
    using range::set_intersection;
    using range::set_difference;
    using range::set_symmetric_difference;
} // namespace boost

#endif // include guard

/* set_algorithm.hpp
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
*/