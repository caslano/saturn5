//  Copyright Neil Groves 2009. Use, modification and
//  distribution is subject to the Boost Software License, Version
//  1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
//
// For more information, see http://www.boost.org/libs/range/
//
#ifndef BOOST_RANGE_ALGORITHM_TRANSFORM_HPP_INCLUDED
#define BOOST_RANGE_ALGORITHM_TRANSFORM_HPP_INCLUDED

#include <boost/assert.hpp>
#include <boost/concept_check.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/concepts.hpp>
#include <algorithm>

namespace boost
{
    namespace range
    {

        /// \brief template function transform
        ///
        /// range-based version of the transform std algorithm
        ///
        /// \pre SinglePassRange1 is a model of the SinglePassRangeConcept
        /// \pre SinglePassRange2 is a model of the SinglePassRangeConcept
        /// \pre OutputIterator is a model of the OutputIteratorConcept
        /// \pre UnaryOperation is a model of the UnaryFunctionConcept
        /// \pre BinaryOperation is a model of the BinaryFunctionConcept
        template< class SinglePassRange1,
                  class OutputIterator,
                  class UnaryOperation >
        inline OutputIterator
        transform(const SinglePassRange1& rng,
                  OutputIterator          out,
                  UnaryOperation          fun)
        {
            BOOST_RANGE_CONCEPT_ASSERT(( SinglePassRangeConcept<const SinglePassRange1> ));
            return std::transform(boost::begin(rng),boost::end(rng),out,fun);
        }

    } // namespace range

    namespace range_detail
    {
        template< class SinglePassTraversalReadableIterator1,
                  class SinglePassTraversalReadableIterator2,
                  class OutputIterator,
                  class BinaryFunction >
        inline OutputIterator
        transform_impl(SinglePassTraversalReadableIterator1 first1,
                       SinglePassTraversalReadableIterator1 last1,
                       SinglePassTraversalReadableIterator2 first2,
                       SinglePassTraversalReadableIterator2 last2,
                       OutputIterator                       out,
                       BinaryFunction                       fn)
        {
            for (; first1 != last1 && first2 != last2; ++first1, ++first2)
            {
                *out = fn(*first1, *first2);
                ++out;
            }
            return out;
        }
    }

    namespace range
    {

        /// \overload
        template< class SinglePassRange1,
                  class SinglePassRange2,
                  class OutputIterator,
                  class BinaryOperation >
        inline OutputIterator
        transform(const SinglePassRange1& rng1,
                  const SinglePassRange2& rng2,
                  OutputIterator          out,
                  BinaryOperation         fun)
        {
            BOOST_RANGE_CONCEPT_ASSERT(( SinglePassRangeConcept<const SinglePassRange1> ));
            BOOST_RANGE_CONCEPT_ASSERT(( SinglePassRangeConcept<const SinglePassRange2> ));
            return boost::range_detail::transform_impl(
                        boost::begin(rng1), boost::end(rng1),
                        boost::begin(rng2), boost::end(rng2),
                        out, fun);
        }

    } // namespace range
    using range::transform;
} // namespace boost

#endif // include guard

/* transform.hpp
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
*/