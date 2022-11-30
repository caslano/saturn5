// Boost.Range library
//
//  Copyright Neil Groves 2009. Use, modification and
//  distribution is subject to the Boost Software License, Version
//  1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see http://www.boost.org/libs/range/
//
#ifndef BOOST_RANGE_ALGORITHM_EXT_FOR_EACH_HPP_INCLUDED
#define BOOST_RANGE_ALGORITHM_EXT_FOR_EACH_HPP_INCLUDED

#include <boost/range/config.hpp>
#include <boost/range/concepts.hpp>
#include <boost/range/difference_type.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/assert.hpp>

namespace boost
{
    namespace range_detail
    {
        template<class InputIterator1, class InputIterator2, class Fn2>
        inline Fn2 for_each_impl(InputIterator1 first1, InputIterator1 last1,
                                 InputIterator2 first2, InputIterator2 last2,
                                 Fn2 fn)
        {
            for (; first1 != last1 && first2 != last2; ++first1, ++first2)
            {
                fn(*first1, *first2);
            }
            return fn;
        }
    }

    namespace range
    {
        template<class SinglePassRange1, class SinglePassRange2, class Fn2>
        inline Fn2 for_each(const SinglePassRange1& rng1, const SinglePassRange2& rng2, Fn2 fn)
        {
            BOOST_RANGE_CONCEPT_ASSERT(( SinglePassRangeConcept<const SinglePassRange1> ));
            BOOST_RANGE_CONCEPT_ASSERT(( SinglePassRangeConcept<const SinglePassRange2> ));

            return ::boost::range_detail::for_each_impl(
                ::boost::begin(rng1), ::boost::end(rng1),
                ::boost::begin(rng2), ::boost::end(rng2), fn);
        }

        template<class SinglePassRange1, class SinglePassRange2, class Fn2>
        inline Fn2 for_each(const SinglePassRange1& rng1, SinglePassRange2& rng2, Fn2 fn)
        {
            BOOST_RANGE_CONCEPT_ASSERT(( SinglePassRangeConcept<const SinglePassRange1> ));
            BOOST_RANGE_CONCEPT_ASSERT(( SinglePassRangeConcept<SinglePassRange2> ));

            return ::boost::range_detail::for_each_impl(
                ::boost::begin(rng1), ::boost::end(rng1),
                ::boost::begin(rng2), ::boost::end(rng2), fn);
        }

        template<class SinglePassRange1, class SinglePassRange2, class Fn2>
        inline Fn2 for_each(SinglePassRange1& rng1, const SinglePassRange2& rng2, Fn2 fn)
        {
            BOOST_RANGE_CONCEPT_ASSERT(( SinglePassRangeConcept<SinglePassRange1> ));
            BOOST_RANGE_CONCEPT_ASSERT(( SinglePassRangeConcept<const SinglePassRange2> ));

            return ::boost::range_detail::for_each_impl(
                ::boost::begin(rng1), ::boost::end(rng1),
                ::boost::begin(rng2), ::boost::end(rng2), fn);
        }

        template<class SinglePassRange1, class SinglePassRange2, class Fn2>
        inline Fn2 for_each(SinglePassRange1& rng1, SinglePassRange2& rng2, Fn2 fn)
        {
            BOOST_RANGE_CONCEPT_ASSERT(( SinglePassRangeConcept<SinglePassRange1> ));
            BOOST_RANGE_CONCEPT_ASSERT(( SinglePassRangeConcept<SinglePassRange2> ));

            return ::boost::range_detail::for_each_impl(
                ::boost::begin(rng1), ::boost::end(rng1),
                ::boost::begin(rng2), ::boost::end(rng2), fn);
        }
    } // namespace range
    using range::for_each;
} // namespace boost

#endif // include guard

/* for_each.hpp
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
*/