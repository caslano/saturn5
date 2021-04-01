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
GHF45truooN9Gu0lELgMxPiGatIPuvssLWxwfnZhLnd0todTqlYv/kw2ZVo7CldyfKi5oMJMn7Fa2f/8N6CY4jnsNhglU6rRZ4ZbOGe7QkyO4yBdEQw3+ZdS3ZfY/O8ziqHHYEuCS7STZltlnUKo2CRXvQtXbCngHiZkO1L1CjhxblMziFiioUSX4bjOXFkNaR90RVFtBG9vQ86kK98kq+gaA5NCjWRjyu1iZB+1vpnMM5NxzGaGSv5tSopu17tFHuh2vgJfKtO4x21M9ediDM3c5Ij7GdAjKM1mO7rsfItRDC2qDYuMHtCnuC3awlySZ7aitCBoMA8EE1/xMQJA+BB4nKCd4GRzYKt80tK40u5OM1B248R5SiIcTQhdNrJTY+ngoeBiGMLAjvmWaIwnQwURAGmrzCphY0HlDTFJG46LqRuFRJiSxVL7WZLCumi/OhY6FPgKkEaGnCOaD0lHx8l57l1RFDLpVfNABY7BdQNS/cjxwqwwls7Y583UdE7ggPuO572iaHe81/1dqbqAEzbcoh6sFBIhD/4WGxDCIhhHqHPwYh6EFT8+2Q==
*/