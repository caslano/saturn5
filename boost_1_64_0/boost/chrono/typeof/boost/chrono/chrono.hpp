//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Vicente J. Botet Escriba 20010.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or
// copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Based on the unique_threader/unique_joiner design from of Kevlin Henney (n1883)
//
// See http://www.boost.org/libs/chrono for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_CHRONO_TYPEOF_CHRONO_HPP
#define BOOST_CHRONO_TYPEOF_CHRONO_HPP

#include <boost/chrono/chrono.hpp>
#include <boost/typeof/typeof.hpp>

#include BOOST_TYPEOF_INCREMENT_REGISTRATION_GROUP()

BOOST_TYPEOF_REGISTER_TEMPLATE(boost::chrono::duration, (typename)(typename))
BOOST_TYPEOF_REGISTER_TEMPLATE(boost::chrono::time_point, (typename)(typename))
#if 0
BOOST_TYPEOF_REGISTER_TYPE(boost::chrono::system_clock)
#ifdef BOOST_CHRONO_HAS_CLOCK_STEADY
BOOST_TYPEOF_REGISTER_TYPE(boost::chrono::steady_clock)
#endif
BOOST_TYPEOF_REGISTER_TYPE(boost::chrono::high_resolution_clock)

#endif
#endif

/* chrono.hpp
OyIFGz8LTz+7qAllGt6plVUNG2BPqyNrY7S8PyMFDgs5mu3Kr9q2kdstBRPQnWiwuHhFIe0vE6D6cp1ohfFrWLVUa09NZFHmY7UamY2eFVGRT+7BkNGxRYFGe+u12bq3ZVTEgG06webz8jF6h8owk+b37DWCzj1K8c2FbfFw58DA30JE2utPaeJuepFP4mP3Tfo+JqfBPojJG1MYG2bgVY6iuaKZT34VzuFgtRFgabX+KTmv151QCblN3OuM+rAvCib1lFhWKi0GcXsP2MparEvyybAeHOsfNQeG3t3ejdhY7YPaUlHB1k4vhJnXDbF28CpSMPXu2qKqAGAFh16zgNIHfNKBvWIj/hf50vCdZRNBUwf70KsFIk7TCxoa2rS9ZkDjCcV00vxwn32DOF9yzF4RecSJ4bTI9GpvGx5M1cVoKVl7YzrQEjZoQ21LKxBI75/I6YTcI7x1AQZ5YAHu2QK7x11eQklRbBESH3Y/3p3Ax3yjMFb6JhdgFJwqldpN/Q6W4ECTuzA0PArVA+4dSx+w5OXsUMLYvSNxtHUZO9qdnvSBqi9gruFEMQ==
*/