// Boost.Range library
//
//  Copyright Thorsten Ottosen, Neil Groves 2006 - 2008. Use, modification and
//  distribution is subject to the Boost Software License, Version
//  1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see http://www.boost.org/libs/range/
//

#ifndef BOOST_RANGE_ADAPTOR_INDIRECTED_HPP
#define BOOST_RANGE_ADAPTOR_INDIRECTED_HPP

#include <boost/range/iterator_range.hpp>
#include <boost/range/concepts.hpp>
#include <boost/iterator/indirect_iterator.hpp>

namespace boost
{
    namespace range_detail
    {
        template< class R >
        struct indirected_range :
            public boost::iterator_range<
                        boost::indirect_iterator<
                            BOOST_DEDUCED_TYPENAME range_iterator<R>::type
                        >
                    >
        {
        private:
            typedef boost::iterator_range<
                        boost::indirect_iterator<
                            BOOST_DEDUCED_TYPENAME range_iterator<R>::type
                        >
                    >
                base;

        public:
            explicit indirected_range( R& r )
                : base( r )
            { }
        };

        struct indirect_forwarder {};

        template< class SinglePassRange >
        inline indirected_range<SinglePassRange>
        operator|( SinglePassRange& r, indirect_forwarder )
        {
            BOOST_RANGE_CONCEPT_ASSERT((
                SinglePassRangeConcept<SinglePassRange>));

            return indirected_range<SinglePassRange>( r );
        }

        template< class SinglePassRange >
        inline indirected_range<const SinglePassRange>
        operator|( const SinglePassRange& r, indirect_forwarder )
        {
            BOOST_RANGE_CONCEPT_ASSERT((
                SinglePassRangeConcept<const SinglePassRange>));

            return indirected_range<const SinglePassRange>( r );
        }

    } // 'range_detail'

    using range_detail::indirected_range;

    namespace adaptors
    {
        namespace
        {
            const range_detail::indirect_forwarder indirected =
                                            range_detail::indirect_forwarder();
        }

        template<class SinglePassRange>
        inline indirected_range<SinglePassRange>
        indirect(SinglePassRange& rng)
        {
            BOOST_RANGE_CONCEPT_ASSERT((
                SinglePassRangeConcept<SinglePassRange>));
            return indirected_range<SinglePassRange>(rng);
        }

        template<class SinglePassRange>
        inline indirected_range<const SinglePassRange>
        indirect(const SinglePassRange& rng)
        {
            BOOST_RANGE_CONCEPT_ASSERT((
                SinglePassRangeConcept<const SinglePassRange>));

            return indirected_range<const SinglePassRange>(rng);
        }
    } // 'adaptors'

}

#endif

/* indirected.hpp
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
*/