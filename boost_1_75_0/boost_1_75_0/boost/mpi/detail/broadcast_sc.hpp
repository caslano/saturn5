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
Z6sNHt5oxhyzNxyliZdJ1q1ntkImcsDUgV00CC9mRnpbRoplZ9DFJWrO5Aj0BgA3KKnHVTfxAOOMjrprJsitFv3YTcezBNCrnnduUKef0jU9n3JAZocN5jsOipOVRZbgQy6Plq3LA90ccCzw91zQ0xu/0MeecphcG/JYGI/7XPzzeZRglNi0Glppo6/M5mDnEuBHiDo6ZkaV9he6RbdW8Inf1k/t6B4hM/ofbDEOmUJim6WzaTlyR5XmNdpSFQ2j7uSE4kS25E+lPlzxTu7FxEcEZ9I4mQNo3SJfGzUOtL6cXyfWg3OPs+/ADbYdwiPuVLtW4lrWQI3U3Lu9FJreSlLXLvMubGj6Q9LT/Y1VzE0mLcaWm4rmvp+4p4yYLhK1WjVpp+R2JsfigKIz5eguZpKdpM/CfRoq7cMucrhef50hsNY0On3IvKGBQ0jQsfF4752NSsQ0mWazheSq44bgIDuOW7CK+502lOjaI276nCuTfuGJlAxO0Rr/w0v45yj1dv8h7+NlprH1Xvhtf5MCt4rW3iVDpe7OTju/kf/kb2ejT2RhhaXHslN4aT3CzyzsI3nVIqlXzbzWYwSl1IJPADsSvRZyYFt2v/SD0mn1AQfUBJPUXJJnh19sOEiNaD18PMdxCD3BHmME1jiUBlp1faP2vsA8zdwYI2wtzJsheLTEflomNEf6bQ/XVvTXbSlDNW7misbzK2bclFmM
*/