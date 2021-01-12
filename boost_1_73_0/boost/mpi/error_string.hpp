// Copyright (C) 2018 Alain Miniussi <alain.miniussi -at- oca.eu>.

// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

/** @file error_string.hpp
 *
 *  Error code to string convertion.
 */
#ifndef BOOST_MPI_ERROR_STRING_HPP
#define BOOST_MPI_ERROR_STRING_HPP

#include <boost/mpi/config.hpp>
#include <string>

namespace boost { namespace mpi {

/**
 * @brief Convert a MPI error code to an error string.
 */
std::string error_string(int err_code);

} } // end namespace boost::mpi

#endif // BOOST_MPI_ERROR_STRING_HPP

/* error_string.hpp
YBO09c9RKvlo7qQf2+GSjxHYEGPQ2m+r3NsLZif9tv4o9e8y1sCf0At/wSZ4RbaLX7E7/ob90Y3pD4NKOBYrYzq64yT0QGv5ETL/l53128p4jXETNsfN2Bq3Snltw964HQfgmzgUd+BEfAtTcSeasAgfxLfxGdyL0k+J3I9LW+6kP9zuUg4h2Ah7YHMMxfYYhr0xHG39ExXK9Iqd9E/0ivQrvAHr4kZsjq9iIL6GobgJ43Ez
*/