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
kqR31ZL1H0CQGxP4qQxTEOw4FbiCK7yrVEdjVUYg0j7wkKHVBZTO1b7gFKLQckeL89TxQ7kSrdJFRUGmCuWwIVsbbQlT4xlRsKECRWp2O6mzgZMzNnlYbZPHNZ90ZOvVJmHRbBp5sTPQb49+eqev1Ki8xa4JlLmjBl1J/c1gKS2+EWkc29K4MYhDj/UUdWOcSU21gM5uL4GnZzCCB2Mdx/+cjOCv7zi4Lby4n/e+qdjkdbnZPq5eRscb43jNrkcw8iYvEoKdddnl5f4DUEsDBAoAAAAIAC1nSlK3R8ef4AEAAD8DAAAfAAkAY3VybC1tYXN0ZXIvdGVzdHMvZGF0YS90ZXN0MTQzMlVUBQABtkgkYLVTTW+jMBC9j5T/MKLKpVrWQGjaWGykqtttuts2UcL27pohoBAbYSdd/v0a8nXY80oIPOOZ957nmcSSsVIYmkJSqly7z4baT91kZgqzNF30L3x6TCFhl52EHYohaaiuWpfIhBWotCxIbr55LRnv0M/CryEGYTSKb8a3d5P/t8L5L/guLHFMd/QFgwm+6T1GQRhgGPN4woMAn15TWFGzp4Zjd3Df9AHLxYbgRbjEq87KvKTsiBKO8OdOORTXHEY8DE4oj6lYc/SiMIhu/Eze+qNJPI7iyZ0H91JS
*/