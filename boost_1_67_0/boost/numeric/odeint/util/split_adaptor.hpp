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