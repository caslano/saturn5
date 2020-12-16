// Boost.Bimap
//
// Copyright (c) 2006-2007 Matias Capeletto
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

/// \file relation/pair_layout.hpp
/// \brief Tags for pair layouts

#ifndef BOOST_BIMAP_RELATION_PAIR_LAYOUT_HPP
#define BOOST_BIMAP_RELATION_PAIR_LAYOUT_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp>

namespace boost {
namespace bimaps {
namespace relation {

//@{

/// \brief Tag for normal layout. ( A,B -> A,B )

struct normal_layout {};

/// \brief Tag for mirror layout. ( A,B -> B,A )

struct mirror_layout {};

//@}

/** \struct boost::bimaps::relation::inverse_layout
\brief Metafunction to obtain the inverse of a layout.

\code
template< class Layout >
struct inverse_layout
{
    typedef {InverseLayout} type;
};
\endcode

See also normal_layout, mirror_layout.
                                                                    **/

#ifndef BOOST_BIMAP_DOXYGEN_WILL_NOT_PROCESS_THE_FOLLOWING_LINES

template< class Layout >
struct inverse_layout
{
    typedef normal_layout type;
};

template<>
struct inverse_layout< normal_layout >
{
    typedef mirror_layout type;
};

#endif // BOOST_BIMAP_DOXYGEN_WILL_NOT_PROCESS_THE_FOLLOWING_LINES

} // namespace relation
} // namespace bimaps
} // namespace boost

#endif // BOOST_BIMAP_RELATION_DETAIL_PAIR_LAYOUT_HPP


/* pair_layout.hpp
aKhijI45EPeXot+f61mY3x/7bSgieM73IHL/rDyLPd7c876/TyE/XmXA+yRyHAnqvRgbp3KpEKbYpp/BSHHKMPUojv5wDyC3pu5XFArTwvmcWAdjPNNgEMmHD3fPS9gA1qO0LsPtHsd3nf8YxdcPUtwPKgPgZ5rioH5vnEuHQfnJQ/qNKY5ydsv8G/rIRSKK+8j7KL4lShbKaA7Hx/veyf0Bh5CfS0opUnTJFM7HzYoFJ1foeSigNBX89RClWUvGcZj8D1JwHdYVx9ckCzGkebeIYn3PHrq2VEnAToP3I18R0o/81ie/0eAu8vuokqo0EfPgV1/jwPoynpMRQ3lKlvs4WmAHkyxWzjeokA4elb4X42OUzk5lohIjtikWeb7mRaT1HewXVV3vyzEKbz53oEzOHbCGD6Jv/jCsV8/Ido/pn/XxPl3yfJ9k/wn1kc/p1N/FFnr/Sc5PGEQy1DVdxvMBqH5VmBOAcjP0pRyKWZ/m+vtYc8n/xNoN4jZXX7rxh7u3zjsw/1xv9ANIfuvWNT0++fmPnc889+hjgesSn0Jb53DKU1JW9T3xzo/RvY/eU6P38hoYuP8j9b0+Wf+Z/eu0h62BA09lZE07vM68j1WX5FsXTXw4ecG2UX+r/tPzF+rXybj+Ph/6auiTcFvJ7fFirkvJsDDUNwkB24BVwYFgNLvPgcLdZnA7t5jj+ZbDD4G/OuAosAV4BzgRHMd9ukngCrAEXAOWghvAyeBr4D3gQXAa+Dk4E/wBvA8MRqJzwKHg/WAxOB/8DfgbcCG4AFwM/hZ8CFwIPgI+AC4Dl4CbwKXg++Aj4HlwCihwP3eD1cFSsAY4FowDC8EEvj4L+dmA/tY+2IxkVfbR8vD3PthO6KcdhP0W1tJEFX1hL8E6+25HYd1nwc5CH+4ZWHdfLidNFXlpIPp0z8OWwUZnwD/sUdiTsMeQ5iV/X89v/MZv/MZv/Oa/0vwK/f+RBTdw/78zMfr+fwdVQeYtnq86F7ZfXXwLNpb9XU6bOr0879zr/D/2X1uYnvcn/cTLefObyL3ae34A70n/Cl0fSu6eMnxDrz30ecyHr0/zucd9H1xfR9eHGfplY8eKCvvphzWhfrdH36wlySLleoAzFM8Y41ivHIf6nq5Vkevot5K7LWbz15X7xK0mWTvIwljHcW37oxvPoDPu353lfb4d+c0F5RgWyzr52I87Rfa3qDw89CFD+HzIAbChsL1gT4WhrJvo+0Ogmk0YXyLkvTwWdi33EhzeFQV08iXWw7CsFByRARmeXVGp3veLU66/T/VLzxP/mPp+7/6hVZW/dchauavmnYcvP2L7zLyPeiTAKd8dHLk9PyPjjdbWRtkTa3WINetbXn8f9RzknQS/B/xOL4a1weZw4aM6zIoEG4CxYCOwCdgYnAY2BeeC6SCNBwp+1uAAjs8O2979vsBfKFgVjAZjweZgLbA9WBvswu5e7Ea/77r7Whuu0t9KSLu2Ptcl2CmPBYjHHvP3u/zGb/zGb/zGb/zGb/zmnzO/Tv8//Yad/3fa0P+fwv27L2GjYVfA9kEnYWiy7N9x2pQbs/4/+08w7/9LP/Xk3gAPkPtVj/5/qmHvtEfp+ovk7inDN/Pwn2bQFyyi65PJ3Uv6b+rhP10Y9/RnP7xuHX0d8/P5DH55PbuXniGC9QyzyN9dolioleoafkz21jUkUd8tSuoaysnPDLilrsFjbfwRuh4p54wvIHcXo39nNFL3MI2u3yNKkTc6n43Xmn/xC+sfUlnWySBLY1lPgyydZXnXqKf4d68VD5sJq/ywaW1c44DsDT+1aFb27NoHhlS+Vrynuy7xezelQp86lPvS1cA4MApsBsaADxk=
*/