// Copyright (C) 2006 Douglas Gregor <doug.gregor -at- gmail.com>.

// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

// Skeleton and content support for communicators

// This header should be included only after both communicator.hpp and
// skeleton_and_content.hpp have been included.
#ifndef BOOST_MPI_COMMUNICATOR_SC_HPP
#define BOOST_MPI_COMMUNICATOR_SC_HPP

namespace boost { namespace mpi {

template<typename T>
void
communicator::send(int dest, int tag, const skeleton_proxy<T>& proxy) const
{
  packed_skeleton_oarchive ar(*this);
  ar << proxy.object;
  send(dest, tag, ar);
}

template<typename T>
status
communicator::recv(int source, int tag, const skeleton_proxy<T>& proxy) const
{
  packed_skeleton_iarchive ar(*this);
  status result = recv(source, tag, ar);
  ar >> proxy.object;
  return result;
}

template<typename T>
status communicator::recv(int source, int tag, skeleton_proxy<T>& proxy) const
{
  packed_skeleton_iarchive ar(*this);
  status result = recv(source, tag, ar);
  ar >> proxy.object;
  return result;
}

template<typename T>
request
communicator::isend(int dest, int tag, const skeleton_proxy<T>& proxy) const
{
  shared_ptr<packed_skeleton_oarchive> 
    archive(new packed_skeleton_oarchive(*this));

  *archive << proxy.object;
  request result = isend(dest, tag, *archive);
  result.preserve(archive);
  return result;
}

} } // end namespace boost::mpi

#endif // BOOST_MPI_COMMUNICATOR_SC_HPP


/* communicator_sc.hpp
f4pyei8XWGSLjvHnao5wrnF1icpg+O8Irkt/8NCHgTPQYm7a1n+FGc/gjju9aofMhUFaIZJwYc4M22ybGcid9pEX7Ny2Pc7YKQsxN72jz13pdjfbeE8OXrT0ue67TdQQyJ85cFaC1/z2GEo3REoyrZN1i5CNP8LgNsFN3YUX/myjyf2Slc5yw8lTTj8nKkNDW+ZfqI3TnI/HiOB2oV/pNhpwgAgq+F7WSxGL5hORRbnvMOWM/LzTHiAwQqtzoOmywz7qAmgqDxt+iBmE6yDFB4gqksIy4I5RpnlxlBl7nCsGuo08AMcK1kz2L+2iIuuCK5DDwiTnZXBavqGFuOzmywM4yrfvVIwkYBi8OuZ2A6T40I9uPP3b6MO4V9+3oX/oG6o3JCC31jSGew7nvm9YTW8NN5AZrOu2PRTy3U7RI5XJdzEuN0AqxrXqHmHmTa9cVnwBjp4oA3+Y7Guqfcecf3gnBqEkkGssGCFZP+xb0ebrzzuq31lvldNAIJaYQtKCsFwmBiwnq/hIc+SNScMn8pU0MQ7cNfVuQ5GVHiAn7njQ1jE7ArFpz4vYkIzbNPyYCe/P0Bbyib4o7EG2/Z6e4tpFPE3oggxJnLw+wbac1idovnd4gRNGQ2jOdWjmSKuNwquHMPvPabdieH3Cv+r2NM+bh786Lc+fba5VhJfjt3kUfaMGIM9L57KyIQ2qcGD7W7F5auT50WJAscee
*/