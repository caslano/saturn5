// Boost.Range library
//
//  Copyright Thorsten Ottosen, Neil Groves 2006 - 2008. Use, modification and
//  distribution is subject to the Boost Software License, Version
//  1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see http://www.boost.org/libs/range/
//

#ifndef BOOST_RANGE_ADAPTOR_REVERSED_HPP
#define BOOST_RANGE_ADAPTOR_REVERSED_HPP

#include <boost/range/iterator_range.hpp>
#include <boost/range/concepts.hpp>
#include <boost/iterator/reverse_iterator.hpp>

namespace boost
{
    namespace range_detail
    {
        template< class R >
        struct reversed_range : 
            public boost::iterator_range< 
                      boost::reverse_iterator<
                        BOOST_DEDUCED_TYPENAME range_iterator<R>::type 
                                              >
                                         >
        {
        private:
            typedef boost::iterator_range< 
                      boost::reverse_iterator<
                        BOOST_DEDUCED_TYPENAME range_iterator<R>::type 
                                              >
                                         >
                base;
            
        public:
            typedef boost::reverse_iterator<BOOST_DEDUCED_TYPENAME range_iterator<R>::type> iterator;

            explicit reversed_range( R& r ) 
                : base( iterator(boost::end(r)), iterator(boost::begin(r)) )
            { }
        };

        struct reverse_forwarder {};
        
        template< class BidirectionalRange >
        inline reversed_range<BidirectionalRange> 
        operator|( BidirectionalRange& r, reverse_forwarder )
        {
            BOOST_RANGE_CONCEPT_ASSERT((
                BidirectionalRangeConcept<BidirectionalRange>));

            return reversed_range<BidirectionalRange>( r );
        }

        template< class BidirectionalRange >
        inline reversed_range<const BidirectionalRange> 
        operator|( const BidirectionalRange& r, reverse_forwarder )
        {
            BOOST_RANGE_CONCEPT_ASSERT((
                BidirectionalRangeConcept<const BidirectionalRange>));

            return reversed_range<const BidirectionalRange>( r ); 
        }
        
    } // 'range_detail'
    
    using range_detail::reversed_range;

    namespace adaptors
    { 
        namespace
        {
            const range_detail::reverse_forwarder reversed = 
                                            range_detail::reverse_forwarder();
        }
        
        template<class BidirectionalRange>
        inline reversed_range<BidirectionalRange>
        reverse(BidirectionalRange& rng)
        {
            BOOST_RANGE_CONCEPT_ASSERT((
                BidirectionalRangeConcept<BidirectionalRange>));

            return reversed_range<BidirectionalRange>(rng);
        }
        
        template<class BidirectionalRange>
        inline reversed_range<const BidirectionalRange>
        reverse(const BidirectionalRange& rng)
        {
            BOOST_RANGE_CONCEPT_ASSERT((
                BidirectionalRangeConcept<const BidirectionalRange>));

            return reversed_range<const BidirectionalRange>(rng);
        }
    } // 'adaptors'
    
} // 'boost'

#endif

/* reversed.hpp
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
*/