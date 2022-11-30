/*
 [auto_generated]
 boost/numeric/odeint/util/split_adaptor.hpp

 [begin_description]
 A range adaptor which returns even-sized slices.
 [end_description]

 Copyright 2013 Karsten Ahnert
 Copyright 2013 Mario Mulansky
 Copyright 2013 Pascal Germroth

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */


#ifndef BOOST_NUMERIC_ODEINT_UTIL_SPLIT_ADAPTOR_INCLUDED
#define BOOST_NUMERIC_ODEINT_UTIL_SPLIT_ADAPTOR_INCLUDED

#include <boost/range/adaptor/argument_fwd.hpp>
#include <boost/range/size_type.hpp>
#include <boost/range/iterator_range.hpp>
#include <algorithm>

namespace boost {
namespace numeric {
namespace odeint {
namespace detail {

/** \brief Returns the begin and end offset for a sub-range */
inline std::pair<std::size_t, std::size_t>
split_offsets( std::size_t total_length, std::size_t index, std::size_t parts )
{
    BOOST_ASSERT( parts > 0 );
    BOOST_ASSERT( index < parts );
    const std::size_t
        slice = total_length / parts,
        partial = total_length % parts,
        lo = (std::min)(index, partial),
        hi = (std::max<std::ptrdiff_t>)(0, index - partial),
        begin_offset = lo * (slice + 1) + hi * slice,
        length = slice + (index < partial ? 1 : 0),
        end_offset = begin_offset + length;
    return std::make_pair( begin_offset, end_offset );
}

/** \brief Return the sub-range `index` from a range which is split into `parts`.
 *
 * For example, splitting a range into three about equal-sized sub-ranges:
 * \code
 * sub0 = make_split_range(rng, 0, 3);
 * sub1 = rng | split(1, 3);
 * sub2 = rng | split(2, 3);
 * \endcode
 */
template< class RandomAccessRange >
inline iterator_range< typename range_iterator<RandomAccessRange>::type >
make_split_range( RandomAccessRange& rng, std::size_t index, std::size_t parts )
{
    const std::pair<std::size_t, std::size_t> off = split_offsets(boost::size(rng), index, parts);
    return make_iterator_range( boost::begin(rng) + off.first, boost::begin(rng) + off.second );
}

template< class RandomAccessRange >
inline iterator_range< typename range_iterator<const RandomAccessRange>::type >
make_split_range( const RandomAccessRange& rng, std::size_t index, std::size_t parts )
{
    const std::pair<std::size_t, std::size_t> off = split_offsets(boost::size(rng), index, parts);
    return make_iterator_range( boost::begin(rng) + off.first, boost::begin(rng) + off.second );
}


struct split
{
    split(std::size_t index, std::size_t parts)
        : index(index), parts(parts) {}
    std::size_t index, parts;
};

template< class RandomAccessRange >
inline iterator_range< typename range_iterator<RandomAccessRange>::type >
operator|( RandomAccessRange& rng, const split& f )
{
    return make_split_range( rng, f.index, f.parts );
}

template< class RandomAccessRange >
inline iterator_range< typename range_iterator<const RandomAccessRange>::type >
operator|( const RandomAccessRange& rng, const split& f )
{
    return make_split_range( rng, f.index, f.parts );
}


}
}
}
}

#endif

/* split_adaptor.hpp
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
*/