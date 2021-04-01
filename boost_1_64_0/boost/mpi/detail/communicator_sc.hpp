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
D3BZycAO39WNlYpUKa5SyrwSaARgYUA6CaGaT2GOh/+81wrdQOqQRPXNZgDeZHEfc6IYQ0d1dvNLUoffzyLc1CnKzWfQx7IYJPq7PxHGKidj0prv3k21GCysDTWnD9T8C4jJG3FQheLhJk3GVA0ie2hrEQjJTx7DziZjq/LXrSEhIuHZkh5PiUynTYp4EqKyWhdmOEa/vUxWC04+Eof1aB+P3WxyNa3+QnFplGVaLqy9xY9MeFOLpXJi9bhfXdgPXGeEG00hY9wwZ2PeD2gI/dafrEhzC0TlPDSDiJph3WFimdq2XwH/LZReD2rjakJhhZ7ch5jeMa54CiFrM9jk09Qwso40vmsESpqVVYPohZ6hTcAL7Z1OOIeqeH7wgTs0irns0VY+YK4rYKpFbpXKZRbT3BmcF+cr/pT+a59mN/MyMvtFXZkCwvWYl1wVE6PBTRndXaJI9uOZxdCKHSz0VibgFJ4+3BZK8Kc1qlVapGvZi7mvUsxSoHf8DrqBjuAcP3WChspdKnhwpwH5KbchPFzHym/tCic8Osy5hQAyCZgPwyGIMOTtpdELkA==
*/