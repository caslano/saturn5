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
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
*/