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
4PWARw9hUJpLf9fa0/QLfmBVAEiYZLdLAEikS3elTbcmqpZH07U8mi7dlTY9JTHhQ26doMuY8aR7rQlh8LI4zTJ2Xy4tS3FfsaRTnimoSRiMpV+TlOHNlOFKn5E2NW7qwJrhzZThSp+RJnW4iAIcjSQ8m4ocFNKL39F0Ad8ynloeJfE7Eup2kfI+SErXICjvuZ6PPcP7GGNz6re/x+VFsTyMYpn1Pdq4NafgJmw+tpea7s2QXpw2nSBKbTmRLt2bIb2Y04+bRL6S/X9BIkkjKMaMYsoo5hFkynClz0iTyiPIlOHNlOFKn5EmdfhBijRYLPJ9yFS+WOT7ULp0V9p0a6JqWUvXspYu3ZU2PTWRmHAxrD7i0MiYhUcrxmxSXRLpVJdEunRXunRr4musFB15je3vPGxdY7AFbFlmsEf/P7LSEhiCFRGlmRhzLjJm4Vk6I+u2Mrh06a606dZE1fKoSrQyZWvLadMtiWrXJQFzat5VC8M0os8zEuiDuKdPWdRdnNAh8w4NVPb5NTJu0ZMWoQMOblwIu110l26AIikNgBsAJNI+vqY3NifSBRIJkXsoLcoPqRnKlOHNlFGcNiOWPjVTB7EMHVjpGHWlIZLCGvg9TJZ28b/YOxLwKIvrXkk2yYYssECAIBHCZUDUIHJqQFKpEkki8Sp4oq6r4sFGvMJhSMsatqJCxbNUUdFipS1VtFjRakGLLVLa0pa2aGn7x8WatinGGkzfMe+ff//9NwmKrW1Zv+DuHG/evHnz5r03b2aW5WgdDnOCaXP8aXKck420jRhpGzHSNmI4Jcs7PhUGilIc7xZtXJP1oR0gYA5k7MLSIga2Av+IXXD5iq1n+YPPwN+98NcAf9fAXw38TYa/Evi7/Hx/sAL+xsDfUfCXAX/7z/MHfwZ/L8Lf9iOfI5//4w+9/+jG9x/f/8C8mMlbEbA6Fyv8fEuDzEhJaEbX2qbFLrqG5SKPOUXxsCgc+fHSZNY3abRCJY4Gvaehh3pfAdY7LTpC8dV1dKeV6aMINKxewsF4VoeEb9XqBgpFo9pBXTumbqTZD9F3JeX7vBBiVd6ijyIVMl4lFS0arwFWvD5a2iFee1Lw2u2I1y5HvHbAUuUt3w1BFyXlOzjWQU4nMV6lVnr1t+J1acd4bU/Ba5sjXq864rUFYuhKyrd58VD6liR6Fcg4WujV14rXj+s7xGtzCl6bHPHa6IjXBoxFKd9UUr7RW74hiV69ZRwt9Opjxau0Y7zWp+C1zhGvtY54rYFLpbzl60rL15aUr0miV0jG0UKvXla8Hri9Q7weTMFrtSNeKx3xWgE3FZSUr/aWrywtX5FErx4O87GnFS9vx3gtT8FrmSNeSx3woht8lpeWLyspX+otX2yhF4V0t8JZwRJMk8seujOuVfQG+FVLBC92ZwoShBbdpQPFNBKIWgPeZUN4FGg8EDu6C4bdpQKG8OPLXFYhMC9dhFNKJUtWYXrSjcTdGF0iraCbb0V38+KO0L3aEd1wOnTnpkH3IkL3akIxTEjPJaQxPSmwKsDoeq3UzbOim9churMd0T03Hbqz0qBbSejOJhTPJaRnEdKVdurmCDNYqJtrRfeCRR2hO8MR3enp0J2WBt0yQncGoTidkJ5GSGN60q3VXp4/ST6jbO4CP6T4zEJBVxzjghngK+eW2zRaSxCtcYJWgaBF6MbpyCx73gUM4cunVukUc0kcK3upaGkc02k9kRPfmYyvt6ZZ45tlxbe9rkN8RzriOzwNvsXp8C0ifEcSjsMJ62LCGtNJbrbIVW4Oa3WGVWbNrOtIZq0qBIB2sRUvgEQnydUQggwn4bUqiBkNhYhjA9YupaIlDZjOMlYCEVNlg9c=
*/