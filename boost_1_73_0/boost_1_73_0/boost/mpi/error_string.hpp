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
Ev4zyuL86ncBpMnAdNmcX//D7nQzMP3HBOutGw0JmMZqi5N99GZBoMdrq9jhU4OP14DUMLGKrbK3u/M7H2i4DpjrTgvWmwxpOzCf2Jzf9bsF0ujTq9jjpwcf71oQ2AfMykkWd6GPXg9cH/uhU190jnPevPRaIG0E5s1zgo93G6T3gLljcnD9cLx/HpjDk4OPF+dXY6dUsa1TXHorKn+X2mszpY/5u09/5e+dB4H7cooT1+Q89E6cStObANzZU4c=
*/