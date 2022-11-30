//  Copyright Neil Groves 2009. Use, modification and
//  distribution is subject to the Boost Software License, Version
//  1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
//
// For more information, see http://www.boost.org/libs/range/
//
#ifndef BOOST_RANGE_ALGORITHM_FIND_FIRST_OF_HPP_INCLUDED
#define BOOST_RANGE_ALGORITHM_FIND_FIRST_OF_HPP_INCLUDED

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

/// \brief template function find_first_of
///
/// range-based version of the find_first_of std algorithm
///
/// \pre SinglePassRange1 is a model of the SinglePassRangeConcept
/// \pre ForwardRange2 is a model of the ForwardRangeConcept
/// \pre BinaryPredicate is a model of the BinaryPredicateConcept
template< class SinglePassRange1, class ForwardRange2 >
inline BOOST_DEDUCED_TYPENAME disable_if<
    is_const<SinglePassRange1>,
    BOOST_DEDUCED_TYPENAME range_iterator<SinglePassRange1>::type
>::type
find_first_of(SinglePassRange1 & rng1, ForwardRange2 const & rng2)
{
    BOOST_RANGE_CONCEPT_ASSERT(( SinglePassRangeConcept<SinglePassRange1> ));
    BOOST_RANGE_CONCEPT_ASSERT(( ForwardRangeConcept<const ForwardRange2> ));

    return std::find_first_of(boost::begin(rng1),boost::end(rng1),
                              boost::begin(rng2),boost::end(rng2));
}

/// \overload
template< class SinglePassRange1, class ForwardRange2 >
inline BOOST_DEDUCED_TYPENAME range_iterator<const SinglePassRange1>::type
find_first_of(const SinglePassRange1& rng1, const ForwardRange2& rng2)
{
    BOOST_RANGE_CONCEPT_ASSERT(( SinglePassRangeConcept<const SinglePassRange1> ));
    BOOST_RANGE_CONCEPT_ASSERT(( ForwardRangeConcept<const ForwardRange2> ));

    return std::find_first_of(boost::begin(rng1),boost::end(rng1),
                              boost::begin(rng2),boost::end(rng2));
}

/// \overload
template< class SinglePassRange1, class ForwardRange2, class BinaryPredicate >
inline BOOST_DEDUCED_TYPENAME disable_if<
    is_const<SinglePassRange1>,
    BOOST_DEDUCED_TYPENAME range_iterator<SinglePassRange1>::type
>::type
find_first_of(SinglePassRange1 & rng1, ForwardRange2 const & rng2, BinaryPredicate pred)
{
    BOOST_RANGE_CONCEPT_ASSERT(( SinglePassRangeConcept<SinglePassRange1> ));
    BOOST_RANGE_CONCEPT_ASSERT(( ForwardRangeConcept<const ForwardRange2> ));

    return std::find_first_of(boost::begin(rng1),boost::end(rng1),
                              boost::begin(rng2),boost::end(rng2),pred);
}

/// \overload
template< class SinglePassRange1, class ForwardRange2, class BinaryPredicate >
inline BOOST_DEDUCED_TYPENAME range_iterator<const SinglePassRange1>::type
find_first_of(const SinglePassRange1& rng1, const ForwardRange2& rng2, BinaryPredicate pred)
{
    BOOST_RANGE_CONCEPT_ASSERT(( SinglePassRangeConcept<const SinglePassRange1> ));
    BOOST_RANGE_CONCEPT_ASSERT(( ForwardRangeConcept<const ForwardRange2> ));

    return std::find_first_of(boost::begin(rng1),boost::end(rng1),
                              boost::begin(rng2),boost::end(rng2),pred);
}

// range return overloads
/// \overload
template< range_return_value re, class SinglePassRange1, class ForwardRange2 >
inline BOOST_DEDUCED_TYPENAME disable_if<
    is_const<SinglePassRange1>,
    BOOST_DEDUCED_TYPENAME range_return<SinglePassRange1,re>::type
>::type
find_first_of(SinglePassRange1& rng1, const ForwardRange2& rng2)
{
    BOOST_RANGE_CONCEPT_ASSERT(( SinglePassRangeConcept<SinglePassRange1> ));
    BOOST_RANGE_CONCEPT_ASSERT(( ForwardRangeConcept<const ForwardRange2> ));

    return range_return<SinglePassRange1,re>::
        pack(std::find_first_of(boost::begin(rng1), boost::end(rng1),
                                boost::begin(rng2), boost::end(rng2)),
             rng1);
}

/// \overload
template< range_return_value re, class SinglePassRange1, class ForwardRange2 >
inline BOOST_DEDUCED_TYPENAME range_return<const SinglePassRange1,re>::type
find_first_of(const SinglePassRange1& rng1, const ForwardRange2& rng2)
{
    BOOST_RANGE_CONCEPT_ASSERT(( SinglePassRangeConcept<const SinglePassRange1> ));
    BOOST_RANGE_CONCEPT_ASSERT(( ForwardRangeConcept<const ForwardRange2> ));

    return range_return<const SinglePassRange1,re>::
        pack(std::find_first_of(boost::begin(rng1), boost::end(rng1),
                                boost::begin(rng2), boost::end(rng2)),
             rng1);
}

/// \overload
template< range_return_value re, class SinglePassRange1, class ForwardRange2,
          class BinaryPredicate >
inline BOOST_DEDUCED_TYPENAME disable_if<
    is_const<SinglePassRange1>,
    BOOST_DEDUCED_TYPENAME range_return<SinglePassRange1,re>::type
>::type
find_first_of(SinglePassRange1 & rng1, const ForwardRange2& rng2,
              BinaryPredicate pred)
{
    BOOST_RANGE_CONCEPT_ASSERT(( SinglePassRangeConcept<SinglePassRange1> ));
    BOOST_RANGE_CONCEPT_ASSERT(( ForwardRangeConcept<const ForwardRange2> ));

    return range_return<SinglePassRange1,re>::
        pack(std::find_first_of(boost::begin(rng1), boost::end(rng1),
                                boost::begin(rng2), boost::end(rng2), pred),
             rng1);
}

/// \overload
template< range_return_value re, class SinglePassRange1, class ForwardRange2,
          class BinaryPredicate >
inline BOOST_DEDUCED_TYPENAME range_return<const SinglePassRange1,re>::type
find_first_of(const SinglePassRange1 & rng1, const ForwardRange2& rng2,
              BinaryPredicate pred)
{
    BOOST_RANGE_CONCEPT_ASSERT(( SinglePassRangeConcept<const SinglePassRange1> ));
    BOOST_RANGE_CONCEPT_ASSERT(( ForwardRangeConcept<const ForwardRange2> ));

    return range_return<const SinglePassRange1,re>::
        pack(std::find_first_of(boost::begin(rng1), boost::end(rng1),
                                boost::begin(rng2), boost::end(rng2), pred),
             rng1);
}

    } // namespace range
    using range::find_first_of;
} // namespace boost

#endif // include guard

/* find_first_of.hpp
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
*/