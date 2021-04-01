// Copyright (C) 2006 Douglas Gregor <doug.gregor -at- gmail.com>

// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  Authors: Douglas Gregor
#ifndef BOOST_MPI_PYTHON_HPP
#define BOOST_MPI_PYTHON_HPP

#include <boost/python/object.hpp>

/** @file python.hpp
 *
 *  This header interacts with the Python bindings for Boost.MPI. The
 *  routines in this header can be used to register user-defined and
 *  library-defined data types with Boost.MPI for efficient
 *  (de-)serialization and separate transmission of skeletons and
 *  content.
 *
 */

namespace boost { namespace mpi { namespace python {

/**
 * @brief Register the type T for direct serialization within Boost.MPI
 *
 * The @c register_serialized function registers a C++ type for direct
 * serialization within Boost.MPI. Direct serialization elides the use
 * of the Python @c pickle package when serializing Python objects
 * that represent C++ values. Direct serialization can be beneficial
 * both to improve serialization performance (Python pickling can be
 * very inefficient) and to permit serialization for Python-wrapped
 * C++ objects that do not support pickling.
 *
 *  @param value A sample value of the type @c T. This may be used
 *  to compute the Python type associated with the C++ type @c T.
 *
 *  @param type The Python type associated with the C++ type @c
 *  T. If not provided, it will be computed from the same value @p
 *  value.
 */
template<typename T>
void
register_serialized(const T& value = T(), PyTypeObject* type = 0);

/**
 * @brief Registers a type for use with the skeleton/content mechanism
 * in Python.
 *
 * The skeleton/content mechanism can only be used from Python with
 * C++ types that have previously been registered via a call to this
 * function. Both the sender and the transmitter must register the
 * type. It is permitted to call this function multiple times for the
 * same type @c T, but only one call per process per type is
 * required. The type @c T must be Serializable.
 *
 *  @param value A sample object of type T that will be used to
 *  determine the Python type associated with T, if @p type is not
 *  specified.
 *
 *  @param type The Python type associated with the C++ type @c
 *  T. If not provided, it will be computed from the same value @p
 *  value.
 */
template<typename T>
void 
register_skeleton_and_content(const T& value = T(), PyTypeObject* type = 0);

} } } // end namespace boost::mpi::python

#ifndef BOOST_MPI_PYTHON_FORWARD_ONLY
#  include <boost/mpi/python/serialize.hpp>
#  include <boost/mpi/python/skeleton_and_content.hpp>
#else
#  undef BOOST_MPI_PYTHON_FORWARD_ONLY
#endif

#endif // BOOST_MPI_PYTHON_HPP

/* python.hpp
NTId3zaAXw/muuI9eTo8xzl3z8zURut8AQ3YboBg2t47fG+npErX7O258AV03MLn7Ah72tUSmNArVF4RMkhudPYdiThta98HwkM5lY1YOyxsJmaeS061dpb13taLPx7w95o1mzhEYABY/5JZ54wDy3Npe8IHjqwUAfDnDmPjGyrYERkqqSUVzPwlyLnHo+q2JFZWLX0Z2uaAI/jk/gPEjpXHHpTZuoSXOI+rRAxD8z/4F+ZQpmU43ixUfKePtKkwxYELuyvVMylC5Ca1Brm8xpHDZuH9uYiXtyd0FI46Vh65bXpx8A7wNeKxqvDHhUvBY0pgl07WZECzeHbk7Dtckcl9FazwDoBvKQMiGp4xnjSrJV0MspMQeWmf+op3I/8rul/x9qKyvDV93Y997uN783iMhP7wI/z2K+E2tm3HuS2xPqNVuBBkQSZ9J2qurjLm7veMdfENQEeZ/RseIgOAyZ2H0t2fk4S5SzqrHQ3So6P1JSUAe3Q55w21O3brjhr0jhIzu7F5SNWvzpjNW+YZ7iky3zVViD4fO0J6dhSaoRfvADg3eXuZhVvplw==
*/