// Copyright (C) 2005-2006 Alain Miniussi <alain.miniussi -at- oca.eu>.

// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

// Message Passing Interface 1.1 -- Section 4. MPI Collectives

/** @file inplace.hpp
 *
 *  This header provides helpers to indicate to MPI collective operation
 *  that a buffer can be use both as an input and output.
 */
#ifndef BOOST_MPI_INPLACE_HPP
#define BOOST_MPI_INPLACE_HPP

#include <boost/mpi/communicator.hpp>
#include <vector>

namespace boost { namespace mpi {

/**
 *  @brief Wrapper type to explicitly indicate that a input data 
 * can be overriden with an output value.
 */
template <typename T>
struct inplace_t {
  inplace_t(T& inout) : buffer(inout) {}
  T& buffer;
};

template <typename T>
struct inplace_t<T*> {
  inplace_t(T* inout) : buffer(inout) {}
  T* buffer;
};


/**
 *  @brief Wrapp a input data to indicate that it can be overriden 
 *  with an ouput value.
 *  @param inout the contributing input value, it will be overriden 
 *  with the output value where one is expected. If it is a pointer, 
 *  the number of elements will be provided separatly.
 *  @returns The wrapped value or pointer.
 */
template<typename T>
inplace_t<T>
inplace(T& inout) { 
  return inplace_t<T>(inout);
}
/**
 * \overload
 */
template<typename T>
inplace_t<T*>
inplace(T* inout) { 
  return inplace_t<T*>(inout);
}
} }  // end namespace boost::mpi

#endif // BOOST_MPI_INPLACE_HPP


/* inplace.hpp
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
*/