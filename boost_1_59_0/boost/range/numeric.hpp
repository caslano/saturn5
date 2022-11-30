// Copyright 2009-2014 Neil Groves.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// Copyright 2006 Thorsten Ottosen.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// Copyright 2004 Eric Niebler.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
//   Contains range-based versions of the numeric std algorithms
//
#if defined(_MSC_VER)
    #pragma once
#endif

#ifndef BOOST_RANGE_NUMERIC_HPP
#define BOOST_RANGE_NUMERIC_HPP

#include <boost/config.hpp>
#include <boost/assert.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/category.hpp>
#include <boost/range/concepts.hpp>
#include <boost/range/distance.hpp>
#include <boost/range/size.hpp>
#include <numeric>


namespace boost
{
    template<class SinglePassRange, class Value>
    inline Value accumulate(const SinglePassRange& rng, Value init)
    {
        BOOST_RANGE_CONCEPT_ASSERT((
            SinglePassRangeConcept<const SinglePassRange>));

        return std::accumulate(boost::begin(rng), boost::end(rng), init);
    }

    template<class SinglePassRange, class Value, class BinaryOperation>
    inline Value accumulate(const SinglePassRange& rng, Value init,
                            BinaryOperation op)
    {
        BOOST_RANGE_CONCEPT_ASSERT((
                SinglePassRangeConcept<const SinglePassRange> ));

        return std::accumulate(boost::begin(rng), boost::end(rng), init, op);
    }

    namespace range_detail
    {
        template<class SinglePassRange1, class SinglePassRange2>
        inline bool inner_product_precondition(
            const SinglePassRange1&,
            const SinglePassRange2&,
            std::input_iterator_tag,
            std::input_iterator_tag)
        {
            return true;
        }

        template<class SinglePassRange1, class SinglePassRange2>
        inline bool inner_product_precondition(
            const SinglePassRange1& rng1,
            const SinglePassRange2& rng2,
            std::forward_iterator_tag,
            std::forward_iterator_tag)
        {
            return boost::size(rng2) >= boost::size(rng1);
        }

    } // namespace range_detail

    template<
        class SinglePassRange1,
        class SinglePassRange2,
        class Value
    >
    inline Value inner_product(
        const SinglePassRange1& rng1,
        const SinglePassRange2& rng2,
        Value                   init)
    {
        BOOST_RANGE_CONCEPT_ASSERT((
            SinglePassRangeConcept<const SinglePassRange1>));

        BOOST_RANGE_CONCEPT_ASSERT((
            SinglePassRangeConcept<const SinglePassRange2>));

        BOOST_ASSERT(
            range_detail::inner_product_precondition(
                    rng1, rng2,
                    typename range_category<const SinglePassRange1>::type(),
                    typename range_category<const SinglePassRange2>::type()));

        return std::inner_product(
            boost::begin(rng1), boost::end(rng1),
            boost::begin(rng2), init);
    }

    template<
        class SinglePassRange1,
        class SinglePassRange2,
        class Value,
        class BinaryOperation1,
        class BinaryOperation2
    >
    inline Value inner_product(
        const SinglePassRange1& rng1,
        const SinglePassRange2& rng2,
        Value                   init,
        BinaryOperation1        op1,
        BinaryOperation2        op2)
    {
        BOOST_RANGE_CONCEPT_ASSERT((
                SinglePassRangeConcept<const SinglePassRange1>));

        BOOST_RANGE_CONCEPT_ASSERT((
                SinglePassRangeConcept<const SinglePassRange2>));

        BOOST_ASSERT(
            range_detail::inner_product_precondition(
                rng1, rng2,
                typename range_category<const SinglePassRange1>::type(),
                typename range_category<const SinglePassRange2>::type()));

        return std::inner_product(
            boost::begin(rng1), boost::end(rng1),
            boost::begin(rng2), init, op1, op2);
    }

    template<class SinglePassRange, class OutputIterator>
    inline OutputIterator partial_sum(const SinglePassRange& rng,
                                      OutputIterator result)
    {
        BOOST_RANGE_CONCEPT_ASSERT((
                SinglePassRangeConcept<const SinglePassRange>));

        return std::partial_sum(boost::begin(rng), boost::end(rng), result);
    }

    template<class SinglePassRange, class OutputIterator, class BinaryOperation>
    inline OutputIterator partial_sum(
        const SinglePassRange&  rng,
        OutputIterator          result,
        BinaryOperation         op)
    {
        BOOST_RANGE_CONCEPT_ASSERT((
                SinglePassRangeConcept<const SinglePassRange>));

        return std::partial_sum(boost::begin(rng), boost::end(rng), result, op);
    }

    template<class SinglePassRange, class OutputIterator>
    inline OutputIterator adjacent_difference(
        const SinglePassRange&  rng,
        OutputIterator          result)
    {
        BOOST_RANGE_CONCEPT_ASSERT((
                SinglePassRangeConcept<const SinglePassRange>));

        return std::adjacent_difference(boost::begin(rng), boost::end(rng),
                                        result);
    }

    template<class SinglePassRange, class OutputIterator, class BinaryOperation>
    inline OutputIterator adjacent_difference(
        const SinglePassRange&  rng,
        OutputIterator          result,
        BinaryOperation         op)
    {
        BOOST_RANGE_CONCEPT_ASSERT((
                SinglePassRangeConcept<const SinglePassRange>));

        return std::adjacent_difference(boost::begin(rng), boost::end(rng),
                                        result, op);
    }

} // namespace boost

#endif

/* numeric.hpp
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
*/