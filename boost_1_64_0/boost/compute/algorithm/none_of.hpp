//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_NONE_OF_HPP
#define BOOST_COMPUTE_ALGORITHM_NONE_OF_HPP

#include <boost/static_assert.hpp>

#include <boost/compute/system.hpp>
#include <boost/compute/algorithm/find_if.hpp>
#include <boost/compute/type_traits/is_device_iterator.hpp>

namespace boost {
namespace compute {

/// Returns \c true if \p predicate returns \c true for none of the elements in
/// the range [\p first, \p last).
///
/// Space complexity: \Omega(1)
///
/// \see all_of(), any_of()
template<class InputIterator, class UnaryPredicate>
inline bool none_of(InputIterator first,
                    InputIterator last,
                    UnaryPredicate predicate,
                    command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<InputIterator>::value);
    return ::boost::compute::find_if(first, last, predicate, queue) == last;
}

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_NONE_OF_HPP

/* none_of.hpp
/U3jpRu95OgcdOzvWB9Wnm0NOEMyyTGG5HpGvoFr4MY1wvRSltA/pXwqkzVazyXdFlKu8VNm5B+fP12OJA09x1PnJA07jO/I/hD/VVoW4x9RPnG/+MeYOeegsZs9CuVBuaIU+Jz490LWymOfc9oA2a7ws0Od43GVo14+jXE/59Q/tH69cMSp2/mmhD0655sG89RNBSs3aH4u03tItkuemPTc7h8adh7t3ML1frFV/DOMbs9rxd67nr7gFsYvhW9r0TKnfEmd7Yvlu25gTslpnZg2pE6v60bc9mIC86avNVsgOvpjYhLTeqi+UOTr698rcg9TR3l2P1e7+7j9Ms79XnHAtc50Aop8nyBexPsEfsfuPhEsz674+uXpQHn8w9zLs1wKVFeerPrlIV7E8uDnLM+DDei/wfJkRS6Po09vaOJ+38t2KQ83CLf7AmEj3/PwM/e83dTdDK730DG45wXbpyTB/Z5X4loe09/cykWciPc7/I7t/e6AyubPwWToN/XOBFzjXg7tZ67l0DiF4pflLIf6ZaudsxsCdpUFLKMuN5OPRwLzRkbCQGYOX2xCLPD77bOVdW9Jnd56dqkYndKSxv6Eun0GjxIuMSYj0dc0YT4JxDMduebnYbl+k/D8YJew/JbMmxeyZ2ur+HdqyNxl9gh10z1COm852qMAe5ZpD3t9uLOp+/rDGl6vPXTxEXntQZzIaw/xP7Zrj2Af29isfpn6EDazrkyjpwRKEraysrRcvTTfjjV8SLnyHOXWdXxYuXYcQbl6mTLY5cqzy+poq+rm7uXKc5bLbrFDlCnvMGXKO8ZlCsq475Z/keXQMr2JSSZ+SV2ZAs/ODbp/1oVPFvsJ2GvE/ozaWSWOkD2PRkbenG1v4vrFPh17tdh3q93ENWOVuHq+CXt+TPznrC2qA7/QGUfl5WWtKf6VJs7v1G6H78jcUks7F1Ivjwfmp2S2d/ZOyEdSOT6ef1IS7fklzlpm1l+bJb2rkLtqKvtKk7Rhrgy4EyNd3Dy42GETSYHwdnq6Bpto0jvXmqXpJWt6G8Q9jvRwc6R3Lq6JgfAyZ9X1m4ad7SZn0LusVQqM7PscCVNo5jCtf8fZC9RvWN/arpleqn1rESYHtzUjTN9q0FqG8NK3krR/XCb22eygaGX6yC/ErZVb/9L4fok/Dft6sZeyssjSPQ8mfoQ+pmlQkv6yhsbNjuPoD0Z/v/h1cPSFp8Ut3ko1fcEOR18I7Qead+Pv6APPaF9NFTdHOtIHGtj2E0LbPusI217b2bEnIVMTbo/pQWb9I+12rl7uWEvoGXtztL6CYTNd793qF/Fe3VL82xx231igXHFmj+wcsfvD7ssjtExb9QyCC7TvrsEEGiDPLpPu+zn0e6hUKZ/GI7XetM8cx/N0qZ7jZdK2utDXpzj0fFQGNldIuAoTbrnVgyf7eaSnZ7CY/c+3H0G7u4x5s55PcuxtkTw46uhAal2C92kdbcVkJePuXkfa/BHHucbzM7fJOKWgAfvPKGEm9dHSOhMTUm8SbmIwHlfvTr1Npd7Oql93ErYiGJY0e1N380n5Soye2enYQ/74EcybWd+iDhfp5t/Nuh7/CSaNOtybF16Hh3+PJnHMnMa9a5To7DBzXJ7Y+7g9d2jcHLUHwyaE16P4V5jwM9UeDN8y0ppd3hd8Sn8pS9M1e2xWTIyvrSzZ3cZ8T0mPvq35yRT7GHLUI+I80ETC9CYO9pDy8pZb7onBPLyveSADJYd6Zpgo8ZtoHjQ90b7RJGIexkiYpIh5CH2+ORrPFPqM59bPzNk1tAdu0h6OvpfRpv6zYFfCbhvl2veWH+KZljgRnwXxcz4L7j1039LwXQ7Zl6oZNxs=
*/