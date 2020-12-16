//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_EQUAL_HPP
#define BOOST_COMPUTE_ALGORITHM_EQUAL_HPP

#include <boost/static_assert.hpp>

#include <boost/compute/system.hpp>
#include <boost/compute/command_queue.hpp>
#include <boost/compute/algorithm/mismatch.hpp>
#include <boost/compute/type_traits/is_device_iterator.hpp>

namespace boost {
namespace compute {

/// Returns \c true if the range [\p first1, \p last1) and the range
/// beginning at \p first2 are equal.
///
/// Space complexity: \Omega(1)
template<class InputIterator1, class InputIterator2>
inline bool equal(InputIterator1 first1,
                  InputIterator1 last1,
                  InputIterator2 first2,
                  command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<InputIterator1>::value);
    BOOST_STATIC_ASSERT(is_device_iterator<InputIterator2>::value);
    return ::boost::compute::mismatch(first1,
                                      last1,
                                      first2,
                                      queue).first == last1;
}

/// \overload
template<class InputIterator1, class InputIterator2>
inline bool equal(InputIterator1 first1,
                  InputIterator1 last1,
                  InputIterator2 first2,
                  InputIterator2 last2,
                  command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<InputIterator1>::value);
    BOOST_STATIC_ASSERT(is_device_iterator<InputIterator2>::value);
    if(std::distance(first1, last1) != std::distance(first2, last2)){
        return false;
    }

    return ::boost::compute::equal(first1, last1, first2, queue);
}

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_EQUAL_HPP

/* equal.hpp
DWA/2BDOhI3gebAxvA+2gE/AlvAgbAU/h63hV7AtrEvY7WAebA/PgblwHuwIF8AmcBNsCr8Pm8EfwU5av3eZPTPoZ7V+97XkfsvnLe0n3oXD4XuwHB6Gl8G/wq3wKLwXfgSfh5/Cw/Bz2CjYTmEh/BiWw0/gKhiUu0SvXw2/hHfAr+DD8O/wGWhRvn+wAXwP+qCP+pMAs2Ey7A5T4FRYBy6B9eBFsD68CqbDW2EGvA9mwqdgA623DeFXMAv6/ZQXrA+ba71sAVvAlrAzbAV7wxw4EbaDM2B7OAfmwiLYSetpZ7gJdoE3wK7wLtgNVsHuWk97wFdgHjwCe8H63J8+sDXsC3NhP613Yy3dgwE2t0LP7CQ4CCO6Sj2T6g/QB1+FdeEfYTZ8DTaDr2v/X2X2EyAurccN+L5dwxsUjB8Ogd1hvvb/o+EUOAEWwQJYAmfCy+FseCM8D94LF8AnYBF8Bi6Er8Bi+BYsge/AiTCRNEyCqXAMzIZjYRP4DS2HAvMOO21f092B7yO1Pt9A/oL2m2BnuBV2gz+CPdR9OLwZjoTb4DnwFjgX/hgWqb0c3go3wO3wSng7vAnugLfAO+DP4J3wSXgXfBbeA1+CVbAa/gJ+Bn8JP4f3Qcum/4U++CBMhQ/BNPgrmAkfgw1hFWwHn4Gd4LOwG3weDoIvwGHwCVgAb4IL4H64GL4K18Mn4ZXqfhV8ClKuJEbffYZv6LiiLqzQ+rAJkZZwM+wNL4Nnwe/CGfAaWAy3aLldATfB72k/ciW8A1bCX8Kr4K/h1Vpe12g6rjfv4ZJXTUe6hKvv8OkZdWP0vo6DZ8DxOt6aAAvhRL2Pk+FyOAVeDKfBy+FZ8Fo4Hd4AZ+h9nQm3wTmwCp4HH4BzNX3zzPun9J2avlQJJ/Sp8tN+4b0wF94HR8P74QS4E54PH4Qr4C/gNvhL+Bh8HOrZe/reH3mWeu48e28Eci3gSNgZjobd4BjYC46F4+E4eBacAIvhRFgCJ8EKOBmug1Pgt1WuEp4FfwCnw3vgDHgfPAc+B2fD38E58CU4F74Cz4N/VPshOA/+FS6A9OVWEWwCF8LusBjmwUUwVL76DhosdCnfbyAX5PkwCy6FvWEZ7AeXwf7qPkztw/X6XLUfhZSBvhtG2Wk8deS+hz7rkKsP18NsuAk2V/f2au8ML4Hd4aUwD27WdHwH5os9kq9yjW+5S76u13zdABuoPQveCLvArZqfH+l9vQnOhDdrfdqm8aSbd5MoI603rSx5jsonW+tnY62fTTT85pr+FnAybAXnwRxYBFvDZbANvAC2hWtVbgPsAC+FHeGtsDOsgl3g/bCr1u9u8CnYHT6tcr+DveBh2BtWw/7wM9gXfgH7wa/UPUBeBsIMOAjmwsHwTDgEFsChcBrMh6bdpnjXq5Va/hVQxvtar1bp/bwA9lf3YWofrtfnql3rlb6nQltyqVeXI5cJr9R6dRXMgZWwk9q7w6u1HX8f9oE/gGfAa+AosUfGBVUa39kSn3NccKvGtx12gD+Bg+FtcBK8HU5T+1Hxr+9c6Dsb2JmTlPGyfMp9oXpfAbvBNbAPXA37q30oXAsL4LfgxfBC+H34bbgVroc/hhfDffBy+DG8An4Jvwd9NuUC0+FVsCH8PmwCr4Ut4Q2wP/whzIdb4VlwG5wBf6zj5lvgXHgrLILb4SL4E3g+vB0ugXfCFfAuuAreAy+AVXAdvBdugA/CS+HP4eXwEXgHfBTeCx+DD8LH4aPwabgHboKvwN/BA3AfbOVjnS1sB1+G/eHbcAt8B94ID0LyIPL3wz/Ah+Gr8Bj8I/T5Q+XdAr4J8+G7kD5Y5CrErvXGrOUlLu0nckPjPvn0RK4H7KM=
*/