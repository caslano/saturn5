// (C) Copyright 2006 Douglas Gregor <doug.gregor -at gmail.com>

// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  Authors: Douglas Gregor

/** @file skeleton_and_content_fwd.hpp
 *
 *  This header contains all of the forward declarations required to
 *  use transmit skeletons of data structures and the content of data
 *  structures separately. To actually transmit skeletons or content,
 *  include the header @c boost/mpi/skeleton_and_content.hpp.
 */

#ifndef BOOST_MPI_SKELETON_AND_CONTENT_FWD_HPP
#define BOOST_MPI_SKELETON_AND_CONTENT_FWD_HPP

namespace boost { namespace mpi {

template <class T> struct skeleton_proxy;
template <class T> const skeleton_proxy<T> skeleton(T& x);
class content;
template <class T> const content get_content(const T& x);
class packed_skeleton_iarchive;
class packed_skeleton_oarchive;

} } // end namespace boost::mpi

#endif // BOOST_MPI_SKELETON_AND_CONTENT_FWD_HPP

/* skeleton_and_content_fwd.hpp
NcHGWIO7Vhv8BOnHSCIYE3bOklW2LcX1VQUxgXe6REytpxw+BJWIX/wp0ssn7sWtN66Vg8erh8XN7D4Rl0phx9fn8jwRCfc6tijkIRl5/NlfAVBLAwQKAAAACAAtZ0pSMx5/fKwBAADYAgAAHgAJAGN1cmwtbWFzdGVyL3Rlc3RzL2RhdGEvdGVzdDE0NFVUBQABtkgkYI1SbUvdMBT+Huh/ODj81hp7VQYSymS7Y4Jod1s3hIsQm3QNpklJ0qtl7r8vSbt792UwCs1p+ryc83CI49Y11PICEaFa7Y9nPr1ow2yBPtclKu82Nbq9qWqUZYw6mj0JRc2ECD7gCJ6p76DiZsdNZgXjiBg+yMn/DbQAWk4bMU3PCrRZlzcPENTh/OIUbjW0QnILrR4V84y/oAQvct7loxRcucWliR973QK1bthTCwRE0Z7HWWYjJgxIYR28CNfp0UGjlfMKNoXRCvUD4sRA8MwD0ui+p4pF4UuMj7/cVfV1eXnsFQMUQ1ZCBpn0pnuoL5e2fLvfuBHtBGF8oK3jBlzHIQQPHbXwxLmCI9tpd4TILmJjlM6IAaiUsKNSMHgWilnQbewPvAusS1+4jvoRRiOhoQosD7nZQC3QY0Ru2c88PfuV/ueJHqPs9i3fvi1X25N/FzPm
*/