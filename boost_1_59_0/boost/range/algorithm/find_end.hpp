//  Copyright Neil Groves 2009. Use, modification and
//  distribution is subject to the Boost Software License, Version
//  1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
//
// For more information, see http://www.boost.org/libs/range/
//
#ifndef BOOST_RANGE_ALGORITHM_FIND_END_HPP_INCLUDED
#define BOOST_RANGE_ALGORITHM_FIND_END_HPP_INCLUDED

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

/// \brief template function find_end
///
/// range-based version of the find_end std algorithm
///
/// \pre ForwardRange1 is a model of the ForwardRangeConcept
/// \pre ForwardRange2 is a model of the ForwardRangeConcept
/// \pre BinaryPredicate is a model of the BinaryPredicateConcept
template< class ForwardRange1, class ForwardRange2 >
inline BOOST_DEDUCED_TYPENAME disable_if<
    is_const<ForwardRange1>,
    BOOST_DEDUCED_TYPENAME range_iterator< ForwardRange1 >::type
>::type
find_end(ForwardRange1 & rng1, const ForwardRange2& rng2)
{
    BOOST_RANGE_CONCEPT_ASSERT(( ForwardRangeConcept<ForwardRange1> ));
    BOOST_RANGE_CONCEPT_ASSERT(( ForwardRangeConcept<const ForwardRange2> ));

    return std::find_end(boost::begin(rng1),boost::end(rng1),
                         boost::begin(rng2),boost::end(rng2));
}

/// \overload
template< class ForwardRange1, class ForwardRange2 >
inline BOOST_DEDUCED_TYPENAME range_iterator< const ForwardRange1 >::type
find_end(const ForwardRange1 & rng1, const ForwardRange2& rng2)
{
    BOOST_RANGE_CONCEPT_ASSERT(( ForwardRangeConcept<const ForwardRange1> ));
    BOOST_RANGE_CONCEPT_ASSERT(( ForwardRangeConcept<const ForwardRange2> ));

    return std::find_end(boost::begin(rng1),boost::end(rng1),
                         boost::begin(rng2),boost::end(rng2));
}

/// \overload
template< class ForwardRange1, class ForwardRange2, class BinaryPredicate >
inline BOOST_DEDUCED_TYPENAME disable_if<
    is_const<ForwardRange1>,
    BOOST_DEDUCED_TYPENAME range_iterator<ForwardRange1>::type
>::type
find_end(ForwardRange1 & rng1, const ForwardRange2& rng2, BinaryPredicate pred)
{
    BOOST_RANGE_CONCEPT_ASSERT(( ForwardRangeConcept<ForwardRange1> ));
    BOOST_RANGE_CONCEPT_ASSERT(( ForwardRangeConcept<const ForwardRange2> ));

    return std::find_end(boost::begin(rng1),boost::end(rng1),
                         boost::begin(rng2),boost::end(rng2),pred);
}

/// \overload
template< class ForwardRange1, class ForwardRange2, class BinaryPredicate >
inline BOOST_DEDUCED_TYPENAME range_iterator<const ForwardRange1>::type
find_end(const ForwardRange1& rng1, const ForwardRange2& rng2, BinaryPredicate pred)
{
    BOOST_RANGE_CONCEPT_ASSERT(( ForwardRangeConcept<const ForwardRange1> ));
    BOOST_RANGE_CONCEPT_ASSERT(( ForwardRangeConcept<const ForwardRange2> ));

    return std::find_end(boost::begin(rng1),boost::end(rng1),
                         boost::begin(rng2),boost::end(rng2),pred);
}

/// \overload
template< range_return_value re, class ForwardRange1, class ForwardRange2 >
inline BOOST_DEDUCED_TYPENAME disable_if<
    is_const<ForwardRange1>,
    BOOST_DEDUCED_TYPENAME range_return<ForwardRange1,re>::type
>::type
find_end(ForwardRange1& rng1, const ForwardRange2& rng2)
{
    BOOST_RANGE_CONCEPT_ASSERT(( ForwardRangeConcept<ForwardRange1> ));
    BOOST_RANGE_CONCEPT_ASSERT(( ForwardRangeConcept<const ForwardRange2> ));

    return range_return<ForwardRange1,re>::
        pack(std::find_end(boost::begin(rng1), boost::end(rng1),
                           boost::begin(rng2), boost::end(rng2)),
             rng1);
}

/// \overload
template< range_return_value re, class ForwardRange1, class ForwardRange2 >
inline BOOST_DEDUCED_TYPENAME range_return<const ForwardRange1,re>::type
find_end(const ForwardRange1& rng1, const ForwardRange2& rng2)
{
    BOOST_RANGE_CONCEPT_ASSERT(( ForwardRangeConcept<const ForwardRange1> ));
    BOOST_RANGE_CONCEPT_ASSERT(( ForwardRangeConcept<const ForwardRange2> ));

    return range_return<const ForwardRange1,re>::
        pack(std::find_end(boost::begin(rng1), boost::end(rng1),
                           boost::begin(rng2), boost::end(rng2)),
             rng1);
}

/// \overload
template< range_return_value re, class ForwardRange1, class ForwardRange2,
          class BinaryPredicate >
inline BOOST_DEDUCED_TYPENAME disable_if<
    is_const<ForwardRange1>,
    BOOST_DEDUCED_TYPENAME range_return<ForwardRange1,re>::type
>::type
find_end(ForwardRange1& rng1, const ForwardRange2& rng2, BinaryPredicate pred)
{
    BOOST_RANGE_CONCEPT_ASSERT(( ForwardRangeConcept<ForwardRange1> ));
    BOOST_RANGE_CONCEPT_ASSERT(( ForwardRangeConcept<const ForwardRange2> ));

    return range_return<ForwardRange1,re>::
        pack(std::find_end(boost::begin(rng1), boost::end(rng1),
                           boost::begin(rng2), boost::end(rng2), pred),
             rng1);
}

/// \overload
template< range_return_value re, class ForwardRange1, class ForwardRange2,
          class BinaryPredicate >
inline BOOST_DEDUCED_TYPENAME range_return<const ForwardRange1,re>::type
find_end(const ForwardRange1& rng1, const ForwardRange2& rng2, BinaryPredicate pred)
{
    BOOST_RANGE_CONCEPT_ASSERT(( ForwardRangeConcept<const ForwardRange1> ));
    BOOST_RANGE_CONCEPT_ASSERT(( ForwardRangeConcept<const ForwardRange2> ));

    return range_return<const ForwardRange1,re>::
        pack(std::find_end(boost::begin(rng1), boost::end(rng1),
                           boost::begin(rng2), boost::end(rng2), pred),
             rng1);
}

    } // namespace range
    using range::find_end;
} // namespace boost

#endif // include guard

/* find_end.hpp
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
*/