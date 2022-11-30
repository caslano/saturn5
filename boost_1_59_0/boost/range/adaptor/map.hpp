// Boost.Range library
//
//  Copyright Thorsten Ottosen, Neil Groves 2006 - 2008. Use, modification and
//  distribution is subject to the Boost Software License, Version
//  1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see http://www.boost.org/libs/range/
//

#ifndef BOOST_RANGE_ADAPTOR_MAP_HPP
#define BOOST_RANGE_ADAPTOR_MAP_HPP

#include <boost/range/adaptor/transformed.hpp>
#include <boost/range/iterator_range.hpp>
#include <boost/range/value_type.hpp>
#include <boost/range/reference.hpp>
#include <boost/range/concepts.hpp>

namespace boost
{
    namespace range_detail
    {
        struct map_keys_forwarder {};
        struct map_values_forwarder {};

        template< class Map >
        struct select_first
        {
            typedef BOOST_DEDUCED_TYPENAME range_reference<const Map>::type argument_type;
            typedef const BOOST_DEDUCED_TYPENAME range_value<const Map>::type::first_type& result_type;

            result_type operator()( argument_type r ) const
            {
                return r.first;
            }
        };

        template< class Map >
        struct select_second_mutable
        {
            typedef BOOST_DEDUCED_TYPENAME range_reference<Map>::type argument_type;
            typedef BOOST_DEDUCED_TYPENAME range_value<Map>::type::second_type& result_type;

            result_type operator()( argument_type r ) const
            {
                return r.second;
            }
        };

        template< class Map >
        struct select_second_const
        {
            typedef BOOST_DEDUCED_TYPENAME range_reference<const Map>::type argument_type;
            typedef const BOOST_DEDUCED_TYPENAME range_value<const Map>::type::second_type& result_type;

            result_type operator()( argument_type r ) const
            {
                return r.second;
            }
        };

        template<class StdPairRng>
        class select_first_range
            : public transformed_range<
                        select_first<StdPairRng>,
                        const StdPairRng>
        {
            typedef transformed_range<select_first<StdPairRng>, const StdPairRng> base;
        public:
            typedef select_first<StdPairRng> transform_fn_type;
            typedef const StdPairRng source_range_type;

            select_first_range(transform_fn_type fn, source_range_type& rng)
                : base(fn, rng)
            {
            }

            select_first_range(const base& other) : base(other) {}
        };

        template<class StdPairRng>
        class select_second_mutable_range
            : public transformed_range<
                        select_second_mutable<StdPairRng>,
                        StdPairRng>
        {
            typedef transformed_range<select_second_mutable<StdPairRng>, StdPairRng> base;
        public:
            typedef select_second_mutable<StdPairRng> transform_fn_type;
            typedef StdPairRng source_range_type;

            select_second_mutable_range(transform_fn_type fn, source_range_type& rng)
                : base(fn, rng)
            {
            }

            select_second_mutable_range(const base& other) : base(other) {}
        };

        template<class StdPairRng>
        class select_second_const_range
            : public transformed_range<
                        select_second_const<StdPairRng>,
                        const StdPairRng>
        {
            typedef transformed_range<select_second_const<StdPairRng>, const StdPairRng> base;
        public:
            typedef select_second_const<StdPairRng> transform_fn_type;
            typedef const StdPairRng source_range_type;

            select_second_const_range(transform_fn_type fn, source_range_type& rng)
                : base(fn, rng)
            {
            }

            select_second_const_range(const base& other) : base(other) {}
        };

        template< class StdPairRng >
        inline select_first_range<StdPairRng>
        operator|( const StdPairRng& r, map_keys_forwarder )
        {
            BOOST_RANGE_CONCEPT_ASSERT((
                SinglePassRangeConcept<const StdPairRng>));

            return operator|( r,
                boost::adaptors::transformed( select_first<StdPairRng>() ) );
        }

        template< class StdPairRng >
        inline select_second_mutable_range<StdPairRng>
        operator|( StdPairRng& r, map_values_forwarder )
        {
            BOOST_RANGE_CONCEPT_ASSERT((SinglePassRangeConcept<StdPairRng>));

            return operator|( r,
                boost::adaptors::transformed( select_second_mutable<StdPairRng>() ) );
        }

        template< class StdPairRng >
        inline select_second_const_range<StdPairRng>
        operator|( const StdPairRng& r, map_values_forwarder )
        {
            BOOST_RANGE_CONCEPT_ASSERT((
                SinglePassRangeConcept<const StdPairRng>));

            return operator|( r,
                boost::adaptors::transformed( select_second_const<StdPairRng>() ) );
        }

    } // 'range_detail'

    using range_detail::select_first_range;
    using range_detail::select_second_mutable_range;
    using range_detail::select_second_const_range;

    namespace adaptors
    {
        namespace
        {
            const range_detail::map_keys_forwarder map_keys =
                                            range_detail::map_keys_forwarder();

            const range_detail::map_values_forwarder map_values =
                                           range_detail::map_values_forwarder();
        }

        template<class StdPairRange>
        inline select_first_range<StdPairRange>
        keys(const StdPairRange& rng)
        {
            BOOST_RANGE_CONCEPT_ASSERT((
                SinglePassRangeConcept<const StdPairRange>));

            return select_first_range<StdPairRange>(
                range_detail::select_first<StdPairRange>(), rng );
        }

        template<class StdPairRange>
        inline select_second_const_range<StdPairRange>
        values(const StdPairRange& rng)
        {
            BOOST_RANGE_CONCEPT_ASSERT((
                SinglePassRangeConcept<const StdPairRange>));

            return select_second_const_range<StdPairRange>(
                range_detail::select_second_const<StdPairRange>(), rng );
        }

        template<class StdPairRange>
        inline select_second_mutable_range<StdPairRange>
        values(StdPairRange& rng)
        {
            BOOST_RANGE_CONCEPT_ASSERT((SinglePassRangeConcept<StdPairRange>));

            return select_second_mutable_range<StdPairRange>(
                range_detail::select_second_mutable<StdPairRange>(), rng );
        }
    } // 'adaptors'

}

#endif

/* map.hpp
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
*/