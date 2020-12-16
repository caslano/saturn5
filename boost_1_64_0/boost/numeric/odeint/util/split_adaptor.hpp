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
DBmWqyPD2xBeHVExrgL1iyuvkpMcfblbRGp3FgCogv8qWzYNCinrJLawjF8d1UvzCGnOl+Z8ac6x0cyvXjw3XDJXLw6ESwLRtaS3KKKdXxSiQtj13yq0MfU/TEG5cTcnI/KrgyxDM7+K1OqNLJM/SBW0Xci+MBhtXKBf5uDRs0iJAx6VzjJx/2jzprPT1EmLvLzLHIEzIiVOI8BiFYCYsl9c4TdJ9axrXro/Bd56iYP0rxIM7MxwSSb7ZeAroUWZFn8gXRwqx/nKVLEKP3aT4iHhkiF68cJwyUK9bnAv5hlf5H+INPOLYkYXVImtyLUuyf0KqznRK9ahUzOlZXRlPVdymEtGgApwlxmATgxwkQww2CoDfAcnOwtih0FBxeay+Bw9feYhddGH5ZkoCXp5zbeY+mXKfOLQKB7vKRd/zkcDUKzSJ26SkxNV72VGx7PXvjIqIXLVC9P1JlZTuYjkMSC64Km+TvW3NgfFlbLgkVuHcAKylok3ZFi3vv04Ua7/6CeJ//1gZ/739wz+d25X/O/hsuM46TbCdDvJcPt8fN1aIPlYvQrklGbHVNiIPXOYXtQSPSK690j+9kkYhGyW2H3EbBayuMeOTmRx/w2uHI0nozsZfBCx+6uxoefDoFuWL0sjudanklR8f77kUYNMLD4ZaRxVkn2OnmHp6RA18j9VBL9GPJ3dXNwKo3nHMYyAaeJs4J3dg5owtoyr5Nh0+MSksy0mjl/iBYe7JSVGheciLKaNJMANNN5TAf/34/6r6TgK/toHcceH6DiYjss/I298Oe2X5cJ+TgftS2kfIxuvMLp2Lm0/y4fvJ3EQATr+4QI4Hog7rqTjTjq2p3TmEzxHR8WYHyxjfq3TpY3iFdj1YihlyKXCGG6DOu0Pf+uNMefXTaHx79xdCWCUxRXeK8kCgd3AAgEDRg0YOSQY1IQFDYchWtTFkF2Us5bavym1GHchWAgJm4PNTxCrrdTSere0tRYFQlTEYCABRcQ7CioqtkPjgRcEEbbfe/P//26WRILac2Emc1//m5k3b957k9GNdCO4UYjdZtRUT/FXoiaMFTkHo4fy04urqXNJelKvOBepoLHxX4MLfBc/wu0Ip5BajIHo05qkluZhXENmuJ2E+y8HiiVpc/YG+tNEaTvmxwuK0pj75ZpNBOkgNE0hhooDo3Q65PjgUymM3WUHSxJN/uHaOSSOdPmb4XHBk0wTIdADIsOz6TFTMxAHYspiBy4SSIKi4+GNrf8mqn+uUf/1ev3XSonkyVoDbNWm5Xr9dkRV55jZn2z4LexP0fwgCIXMxMeNMuwksn25PWTvVPvaxe/otY1qgrKQHW5S+WjFyDtqq7dx2En055zFRpB2NFvMvRoJLG2wJu1SjHPa84N0D85p48/VPT2bKim9mbEBmoUditTL+oiSV53V/v2EPCTv+Hr+jFKaiw2GPx8CibTl3km5Vj8g2fV7q6tpHpKK76UUPp2kY4sLfB7RaxqY+zPD4rcX6Le8V/jyxS/hU4ViRjdYUaK4kBFBFylkqziMG+VbKMEheoSnwCuW6nkhTD9J5MNHO2/r4trZM7F/4jVuMUWGzZ7J8l+zMr+h/Lvsr4v6G+WnZSUiMnwLFqWY8WuPf6bD/Dkx+TnGq66jkUTXk9R1VD+rmFtgw580r/j+yAi+sbWk1xTg9gjRRMcAzR1BgP5e3BlqGZWOmnrJIzzyJUiyqIXaG5u+r1p2SPape3BRiglpSzdoRJCTxovpVXWpOnnGu4Wc7kb1csWRe6hsK50TNTL1C1fFkKk7Gn+t7q5qKeXWG9lxeroLM17t6o01HMmj4zdHx38x6qR4Qkyjv3d6W38O/s8J74+SRyo=
*/