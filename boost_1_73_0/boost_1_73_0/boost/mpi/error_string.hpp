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
cZ2YVuY7rLNFA20bQC2Io1OKtvGQKgPfETX0TVoSZ1hbLIewUceiO73wii7wNHY8gKUh/zVMT3zmAr3Jktn4EK/qXA7uTm9uL8NZT8xtwVM39FmpfbhCrLxJnq2xJ34XwB2SjlhLkMq4zMeCrxr4U5P+ieOE76Oyzh6VY9FdUvdnFBajt+EPevx2vy3+WsokjrFi84E8eMHc9XdHvaMcyJ3Q8vk+/QlQSwMECgAAAAgALWdKUh6IuP0FAgAAKwQAAB8ACQBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3QxNDI5VVQFAAG2SCRg7VRdb5swFH23lP9wRRVVquYaCO2GxSJVXdd0a5soYX2dXLgEFGJH2EmGpv332ZCPh/2FSQh8zb3n3nOO5cSgNpnQOCZJJQtlPyts96rJ9ZhM0nTWveDxIe0WzL+OScLOKQnrq0jS4KZu7UYujACpshKz1WevRe31QCy4DiAcRTcw/U6+CIMc0i1+AD+GV7WD0A98CCIexdz34fElJQtsdthwcBNS3QWsECskz8JuvKi8KirMDyjBCL5tpUWxxUHIA/+I8pCKJQcvDPzwhubZRzqKo9swij955C7LcGPoXMglag7vre1E7pU0KA19Rrk0JYdbtyMxM5WSHLJaaTzl
*/