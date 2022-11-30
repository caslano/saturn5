// Boost.Range library
//
//  Copyright Thorsten Ottosen, Neil Groves 2006 - 2008. Use, modification and
//  distribution is subject to the Boost Software License, Version
//  1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see http://www.boost.org/libs/range/
//

#ifndef BOOST_RANGE_ADAPTOR_UNIQUED_IMPL_HPP
#define BOOST_RANGE_ADAPTOR_UNIQUED_IMPL_HPP

#include <boost/range/adaptor/adjacent_filtered.hpp>
#include <boost/range/concepts.hpp>

namespace boost
{

    namespace range_detail
    {
        struct unique_forwarder { };

        struct unique_not_equal_to
        {
            typedef bool result_type;

            template< class T >
            bool operator()( const T& l, const T& r ) const
            {
                return !(l == r);
            }
        };

        template<class ForwardRng>
        class uniqued_range : public adjacent_filtered_range<unique_not_equal_to, ForwardRng, true>
        {
            typedef adjacent_filtered_range<unique_not_equal_to, ForwardRng, true> base;
        public:
            explicit uniqued_range(ForwardRng& rng)
                : base(unique_not_equal_to(), rng)
            {
            }
        };

        template< class ForwardRng >
        inline uniqued_range<ForwardRng>
        operator|( ForwardRng& r,
                   unique_forwarder )
        {
            BOOST_RANGE_CONCEPT_ASSERT((ForwardRangeConcept<ForwardRng>));
            return uniqued_range<ForwardRng>(r);
        }

        template< class ForwardRng >
        inline uniqued_range<const ForwardRng>
        operator|( const ForwardRng& r,
                   unique_forwarder )
        {
            BOOST_RANGE_CONCEPT_ASSERT((ForwardRangeConcept<const ForwardRng>));
            return uniqued_range<const ForwardRng>(r);
        }

    } // 'range_detail'

    using range_detail::uniqued_range;

    namespace adaptors
    {
        namespace
        {
            const range_detail::unique_forwarder uniqued =
                       range_detail::unique_forwarder();
        }

        template<class ForwardRange>
        inline uniqued_range<ForwardRange>
        unique(ForwardRange& rng)
        {
            BOOST_RANGE_CONCEPT_ASSERT((ForwardRangeConcept<ForwardRange>));
            return uniqued_range<ForwardRange>(rng);
        }

        template<class ForwardRange>
        inline uniqued_range<const ForwardRange>
        unique(const ForwardRange& rng)
        {
            BOOST_RANGE_CONCEPT_ASSERT((
                ForwardRangeConcept<const ForwardRange>));

            return uniqued_range<const ForwardRange>(rng);
        }
    } // 'adaptors'

}

#endif

/* uniqued.hpp
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
*/