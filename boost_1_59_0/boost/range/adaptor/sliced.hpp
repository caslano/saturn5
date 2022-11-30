// Boost.Range library
//
//  Copyright Thorsten Ottosen, Neil Groves 2006 - 2008. Use, modification and
//  distribution is subject to the Boost Software License, Version
//  1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see http://www.boost.org/libs/range/
//

#ifndef BOOST_RANGE_ADAPTOR_SLICED_HPP
#define BOOST_RANGE_ADAPTOR_SLICED_HPP

#include <boost/range/adaptor/argument_fwd.hpp>
#include <boost/range/size_type.hpp>
#include <boost/range/iterator_range.hpp>
#include <boost/range/concepts.hpp>
#include <boost/next_prior.hpp>

namespace boost
{
    namespace adaptors
    {
        struct sliced
        {
            sliced(std::size_t t_, std::size_t u_)
                : t(t_), u(u_) {}
            std::size_t t;
            std::size_t u;
        };

        template< class RandomAccessRange >
        class sliced_range : public boost::iterator_range< BOOST_DEDUCED_TYPENAME range_iterator<RandomAccessRange>::type >
        {
            typedef boost::iterator_range< BOOST_DEDUCED_TYPENAME range_iterator<RandomAccessRange>::type > base_t;
        public:
            template<typename Rng, typename T, typename U>
            sliced_range(Rng& rng, T t, U u)
                : base_t(boost::next(boost::begin(rng), t),
                         boost::next(boost::begin(rng), u))
            {
            }
        };

        template< class RandomAccessRange >
        inline sliced_range<RandomAccessRange>
        slice( RandomAccessRange& rng, std::size_t t, std::size_t u )
        {
            BOOST_RANGE_CONCEPT_ASSERT((
                RandomAccessRangeConcept<RandomAccessRange>));

            BOOST_ASSERT( t <= u && "error in slice indices" );
            BOOST_ASSERT( static_cast<std::size_t>(boost::size(rng)) >= u &&
                          "second slice index out of bounds" );

            return sliced_range<RandomAccessRange>(rng, t, u);
        }

        template< class RandomAccessRange >
        inline iterator_range< BOOST_DEDUCED_TYPENAME range_iterator<const RandomAccessRange>::type >
        slice( const RandomAccessRange& rng, std::size_t t, std::size_t u )
        {
            BOOST_RANGE_CONCEPT_ASSERT((
                RandomAccessRangeConcept<const RandomAccessRange>));

            BOOST_ASSERT( t <= u && "error in slice indices" );
            BOOST_ASSERT( static_cast<std::size_t>(boost::size(rng)) >= u &&
                          "second slice index out of bounds" );

            return sliced_range<const RandomAccessRange>(rng, t, u);
        }

        template< class RandomAccessRange >
        inline sliced_range<RandomAccessRange>
        operator|( RandomAccessRange& r, const sliced& f )
        {
            BOOST_RANGE_CONCEPT_ASSERT((
                RandomAccessRangeConcept<RandomAccessRange>));

            return sliced_range<RandomAccessRange>( r, f.t, f.u );
        }

        template< class RandomAccessRange >
        inline sliced_range<const RandomAccessRange>
        operator|( const RandomAccessRange& r, const sliced& f )
        {
            BOOST_RANGE_CONCEPT_ASSERT((
                RandomAccessRangeConcept<const RandomAccessRange>));

            return sliced_range<const RandomAccessRange>( r, f.t, f.u );
        }

    } // namespace adaptors
    using adaptors::sliced_range;
} // namespace boost

#endif

/* sliced.hpp
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
*/