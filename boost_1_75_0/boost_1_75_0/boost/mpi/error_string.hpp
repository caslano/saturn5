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
6LY0JWktJZ65PV7WO+03Hh3w5/xJCdHtw2Q9JMmPoKrGU2hH7qKw4yU8KSCkb7ZSi51s9YrQR0HRaA97WGc0L6ukNYNdrC0rS+9M6alVX2etuJBmW4Ibqry2ZCvlbd/OXHHSwynAeFYJkyAIE7NAFcRM4J9gH/FynPn6Q5lxnUYr3IWdf0ShkeRt1svOaE+t9fpIE7uyydnEH/4b1tuBFPqmYc8iQvotdKG/fiE9a/QNplhnjGOQxjxKyJdjK/N+JtuEmeRUjvhAWxRXcqZ1rx3xU2iLaXDZJsOW7opJK+SJ8xed5f/dk1D22YDHrIcI8x+3a+3Koz79+dgci2CfsE7qfJ8PbLCrx80zXWVuejnu7T8xBGy1IHiJf999WYrrw2AaPxDYZqVePC9zBWb7Zf0bFkMudkmUUhycOJ6oLX+C+bxOVWwH6cprFXn9YIYeXP5bdoYeAKoY27miTSQ4O6S0ec8E/OKJ0VLqTJfRCBrVI/Yv6fGotGHomzvrNG1ejSPK1w4nhjOLAn8QW3Xm996VRE8j9+KWGSrUE9T3r3e5XraI9Q7G55WEQKdpRdVYL2PyAadh9Psg3/tWpwyLUYBz2p4zMdzCQPKJ9EwznxtdTuACS4Jt2+9oF3utUKd3qbSSf6rXX1EkOFiGCRyWKIr77veyINwVx0BXWTCelUdKKYpRRgcml2si2KSAH5b5r7i6kOjuF4wp8fBe
*/