// Boost.Range library
//
//  Copyright Thorsten Ottosen, Neil Groves 2006. Use, modification and
//  distribution is subject to the Boost Software License, Version
//  1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see http://www.boost.org/libs/range/
//

#ifndef BOOST_RANGE_ADAPTOR_COPIED_HPP
#define BOOST_RANGE_ADAPTOR_COPIED_HPP

#include <boost/range/adaptor/argument_fwd.hpp>
#include <boost/range/adaptor/sliced.hpp>
#include <boost/range/size_type.hpp>
#include <boost/range/iterator_range.hpp>
#include <boost/range/concepts.hpp>

namespace boost
{
    namespace adaptors
    {
        struct copied
        {
            copied(std::size_t t_, std::size_t u_)
                : t(t_), u(u_) {}

            std::size_t t;
            std::size_t u;
        };

        template<class CopyableRandomAccessRange>
        inline CopyableRandomAccessRange
        operator|(const CopyableRandomAccessRange& r, const copied& f)
        {
            BOOST_RANGE_CONCEPT_ASSERT((
                RandomAccessRangeConcept<const CopyableRandomAccessRange>));

            iterator_range<
                BOOST_DEDUCED_TYPENAME range_iterator<
                    const CopyableRandomAccessRange
                >::type
            > temp(adaptors::slice(r, f.t, f.u));

            return CopyableRandomAccessRange(temp.begin(), temp.end());
        }

        template<class CopyableRandomAccessRange>
        inline CopyableRandomAccessRange
        copy(const CopyableRandomAccessRange& rng, std::size_t t, std::size_t u)
        {
            BOOST_RANGE_CONCEPT_ASSERT((
                RandomAccessRangeConcept<const CopyableRandomAccessRange>));

            iterator_range<
                BOOST_DEDUCED_TYPENAME range_iterator<
                    const CopyableRandomAccessRange
                >::type
            > temp(adaptors::slice(rng, t, u));

            return CopyableRandomAccessRange( temp.begin(), temp.end() );
        }
    } // 'adaptors'

}

#endif // include guard

/* copied.hpp
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
*/