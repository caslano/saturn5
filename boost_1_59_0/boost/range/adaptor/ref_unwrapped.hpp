// Boost.Range library
//
//  Copyright Robin Eckert 2015.
//  Copyright Thorsten Ottosen, Neil Groves 2006 - 2008. Use, modification and
//  distribution is subject to the Boost Software License, Version
//  1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see http://www.boost.org/libs/range/
//

#ifndef BOOST_RANGE_ADAPTOR_REF_UNWRAPPED_HPP
#define BOOST_RANGE_ADAPTOR_REF_UNWRAPPED_HPP

#include <boost/range/adaptor/transformed.hpp>
#include <boost/range/reference.hpp>
#include <boost/range/concepts.hpp>
#include <boost/type_traits/declval.hpp>
#include <utility>

#if !defined(BOOST_NO_CXX11_DECLTYPE)

namespace boost
{
    namespace range_detail
    {
        struct ref_unwrapped_forwarder {};

        template<class SinglePassRange>
        struct unwrap_ref
        {
            typedef BOOST_DEDUCED_TYPENAME
                          range_reference<SinglePassRange>::type argument_type;

            typedef decltype( boost::declval<argument_type>().get() ) result_type;

            result_type operator()( argument_type &&r ) const
            {
                return r.get();
            }
        };


        template<class SinglePassRange>
        class unwrap_ref_range
            : public transformed_range<unwrap_ref<SinglePassRange>,
                                       SinglePassRange>
        {
            typedef transformed_range<unwrap_ref<SinglePassRange>,
                                           SinglePassRange> base;
        public:
            typedef unwrap_ref<SinglePassRange> transform_fn_type;
            typedef SinglePassRange source_range_type;

            unwrap_ref_range(transform_fn_type fn, source_range_type &rng)
                : base(fn, rng)
            {
            }

            unwrap_ref_range(const base &other) : base(other) {}
        };

        template<class SinglePassRange>
        inline unwrap_ref_range<SinglePassRange>
        operator|(SinglePassRange& r, ref_unwrapped_forwarder)
        {
            BOOST_RANGE_CONCEPT_ASSERT((
                SinglePassRangeConcept<SinglePassRange>));

            return operator|( r,
                boost::adaptors::transformed(unwrap_ref<SinglePassRange>()));
        }

    }

    using range_detail::unwrap_ref_range;

    namespace adaptors
    {
        namespace
        {
            const range_detail::ref_unwrapped_forwarder ref_unwrapped =
                                       range_detail::ref_unwrapped_forwarder();
        }

        template<class SinglePassRange>
        inline unwrap_ref_range<SinglePassRange>
        ref_unwrap(SinglePassRange& rng)
        {
            BOOST_RANGE_CONCEPT_ASSERT((
                SinglePassRangeConcept<SinglePassRange>));

            return unwrap_ref_range<SinglePassRange>(
                range_detail::unwrap_ref<SinglePassRange>(), rng );
        }
    } // 'adaptors'

}

#endif

#endif

/* ref_unwrapped.hpp
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
*/