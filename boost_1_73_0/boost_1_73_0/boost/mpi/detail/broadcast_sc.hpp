// Copyright (C) 2005, 2006 Douglas Gregor <doug.gregor -at- gmail.com>.

// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

// Allows broadcast of skeletons via proxy.

// This header may only be included after both the broadcast.hpp and
// and skeleton_and_content.hpp headers have been included.
#ifndef BOOST_MPI_BROADCAST_SC_HPP
#define BOOST_MPI_BROADCAST_SC_HPP

namespace boost { namespace mpi {

template<typename T>
void
broadcast(const communicator& comm, const skeleton_proxy<T>& proxy, int root)
{
  if (comm.rank() == root) {
    packed_skeleton_oarchive oa(comm);
    oa << proxy.object;
    broadcast(comm, oa, root);
  } else {
    packed_skeleton_iarchive ia(comm);
    broadcast(comm, ia, root);
    ia >> proxy.object;
  }
}

template<typename T>
inline void
broadcast(const communicator& comm, skeleton_proxy<T>& proxy, int root)
{
  const skeleton_proxy<T>& const_proxy(proxy);
  broadcast(comm, const_proxy, root);
}


} } // end namespace boost::mpi

#endif // BOOST_MPI_BROADCAST_SC_HPP

/* broadcast_sc.hpp
SJUN5iLTZmN5ecautW7d5KJ2lqyylYjj1mnC2O5JZPIkyGS48wFW6A7o4kavUWQO66rj7LqkEoxVW1TPX886bM5yMS+KpUwuE7gaj2HxXXwrCVMo9vgRxlO4twdOJGNIJulkmrLk9mchZtYQGop/oHmibQpTf2JQkbYmBVXZBgdN0dVcj/CFZF2V2gjhHXoSpvVLLnjzRsjgs0r7awFc9QGTN72dXGyJapYfQ5GZcsejmnlHoDcw+sO10blXKM06RDyjV2haTWoLv5FaRAPhuNcE/SUXDaUyZXc7ToReqZSj+WJV3C3TkZ/UcvFQyGTy+QvEjFgxHPzzFnBeaYPJAOGjqwHCR5/OudHQgbdvBtn4Izq96SBM5tAH3nggNdZg6wv8B8/We+zN+Jfo+QIoW34P2s8gCDnPwuNHnIvbmwLCMI9uIjG3DaXwbuaR+MVvHl8/MRuj7l0lR483D6u7xX0krpXCmo8v5EUkIu51apHJYZLy9Gf9BVBLAwQKAAAACAAtZ0pS/OMc9NABAAD4AgAAHwAJAGN1cmwtbWFzdGVyL3Rlc3RzL2RhdGEvdGVzdDE0NThVVAUAAbZIJGBtUsFO4zAQvVvqP4yKuFRrnJTCUiuKhNgusAu0arPcTTJpIhI7it1C/n4nSdtw
*/