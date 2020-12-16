//          Copyright Alain Miniussi 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

// Authors: Alain Miniussi

#ifndef BOOST_MPI_OFFSETS_HPP
#define BOOST_MPI_OFFSETS_HPP

#include <vector>
#include <boost/mpi/config.hpp>
#include <boost/mpi/communicator.hpp>

namespace boost { namespace mpi {
namespace detail {

// Convert a sequence of sizes [S0..Sn] to a sequence displacement 
// [O0..On] where O[0] = 0 and O[k+1] = O[k]+S[k].
void BOOST_MPI_DECL sizes2offsets(int const* sizes, int* offsets, int n);

// Same as size2offset(sizes.data(), offsets.data(), sizes.size())
void BOOST_MPI_DECL sizes2offsets(std::vector<int> const& sizes, std::vector<int>& offsets);

// Given a sequence of sizes (typically the number of records dispatched
// to each process in a scater) and a sequence of displacements (typically the
// slot index at with those record starts), convert the later to a number 
// of skipped slots.
void offsets2skipped(int const* sizes, int const* offsets, int* skipped, int n);

// Reconstruct offsets from sizes assuming no padding.
// Only takes place if on the root process and if 
// displs are not already provided.
// If memory was allocated, returns a pointer to it
// otherwise null.
int* make_offsets(communicator const& comm, int const* sizes, int const* displs, int root = -1);

// Reconstruct skip slots from sizes and offsets.
// Only takes place if on the root process and if 
// displs are provided.
// If memory was allocated, returns a pointer to it
// otherwise null.
int* make_skipped_slots(communicator const& comm, int const* sizes, int const* displs, int root = -1);

}
}}// end namespace boost::mpi

#endif // BOOST_MPI_OFFSETS_HPP

/* offsets.hpp
j5z93G2P/Ub4iVmFzi0KO/cA/k7yCYkP746FP/LL4T2x8J/00PCJx2+Nn8fPZLduIS/99YYGhovpTIe7ymCDiMp3M5rk8InhTEp1VR3AdjGKdimpWeJi2JsOjmxwcSdIN6dw8t5veFrtOZbao9wRLbqFgI4KdvIHYUo7safLdNE0MBl1HmvKqzB7dHGFCfs/mGyN8Xaf7hor38EpFCrZ4NHm2X0X+MMX7qmlFKU947Uv+0r8PT7o/6QbYzBeOgLt1J/FisbvTfJXh3+qp+kJ1Er610gTAWlt0tZ1MEb5TXqcBkfqVJ5O8H4JTxoNBAtMw1PN3iHB+aJHC87LaBJPUdPSteA8iSUtJP8YL8N7Af+qBX854M+04FO6LE/j9cdI+P8eZM/XWm1ukv82yX9r+T902V0D0GUyeUqXFRCRYJo6qZ+Zt0r3WBv12HbpsbmtusdSWnbwiTPS5BgIxtyzd3CmQcO4vRPdPrhkdUbtXebMvYq4h2WR+vAVcLic+WflbD4hkkl622g1iNQh5CpeJaljM0xNWrmuTWkJ4jyqMifqNppK3gINQUP31exsY8WuXL8+65VX6Q7+mM7AwiSeGqV59EnbaZZBcwzK/SKQatBAuagnAAel4Q/I9svRAW4Dn09rLGkm5TXgdYJL7137it1Bq3HotNVdNZDOIXikG+jqw5haoIuU6mJUQS2BhtOpoIc04qnA0eyqKlAjya9HDv9UUN3ddm9qkgNJESM5CE6Nn/eSLmwvIny53PqyzVDBQQofvIkeRIPTKRPDfHEzOoi35jlyzks+0YDUg2EznQ2w5eqjz/HKXdFj964IvWw3549E5kB12ycmhpXq5ZcsWUR1zyUIIF0iSKEgquPpk3i5NiyZVcmpyQz5M4KE0p5MX7CVvOpbQE+o50w7TzW/rHn/EJZfpckV6nL5EMK4YVgyaILqXFke6L576x/ZZrf+QxwG2ewKFTXwNfD3dJrfsClQkqQ1v5JNRE4U7+3CPLOv1mPtbsiVWNzu+5n7aGHDoIH03Wsc7qhxlrCvg5kbTd1ULfVqBtHySvFalBzIWrk/eXuX34fZfLKRRhnasuYE2gquCBqBj1hsnNAhY8icrI75B3iBRIWbdcML9dexFFSHfQYckIZJr8oglexfZfZ/8MdaPy8mbdu6Xm27Y5llC3F7Ub0Vl6Y2skRskTGiKCkVasjbGIahTEPE3IPdEDidIZYeKVXE7ZQA3X8ciDHZZrcDwG4dswaZRb+QGRNa4tvvm/Qdgd/gnzrMVwWnxJlHmah4p1LojxGukUBIo0U0Km8SJnI5T8XLxHEkW7Rp60qaA0uSZYlXq00sFaoXCMxLHGOeXRqWSazDa7sJVuHJKOyVwuGzVB+awm2DTKFpTWkY5mvwyqLvyAw0xOrNdpnIjicMEBozulHvuyVWF9m/vPYCvMOPZ0apPswx07d/0/Ru2z/pGLEWETHL9Gb+jw0sPKvCDzT9NVvK/5ilPI0t9UJHs9APS4JQv0Cj1c1TgiHq5qUedDNNGpg9PTEzFyjrphdsqeUiOHU3LX/LYycoUTsucsBuhaSOkKSuOZVNP0+CICMkpikJVtZtkt1Ast8rB2CZAZi4Dhbisqn5BiAjC9/vduCDhOw4ZzI4oAPr+GaRdKrsNfOh5BAhZcztWN+0kuD/F3LJtTHDNdTjcjN3HOlGB8gELprHmUCSiR71WrOO5G372J6RWk3bglrUpufUIKZCnnRiO6h4i91BD1FBNGiobvf1H8efbmUgUqyynvA1zJShoWxTVO3tZr3NgYf1+LIOwcyqHhpgzlaZsJYYNiudwjzAcDxVxdZ1+/N2XQdYZNfEbIQ5qnkr6gys0xU=
*/