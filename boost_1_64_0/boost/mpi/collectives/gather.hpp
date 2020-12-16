// Copyright (C) 2005, 2006 Douglas Gregor.

// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

// Message Passing Interface 1.1 -- Section 4.5. Gather
#ifndef BOOST_MPI_GATHER_HPP
#define BOOST_MPI_GATHER_HPP

#include <cassert>
#include <cstddef>
#include <numeric>
#include <boost/mpi/exception.hpp>
#include <boost/mpi/datatype.hpp>
#include <vector>
#include <boost/mpi/packed_oarchive.hpp>
#include <boost/mpi/packed_iarchive.hpp>
#include <boost/mpi/detail/point_to_point.hpp>
#include <boost/mpi/communicator.hpp>
#include <boost/mpi/environment.hpp>
#include <boost/mpi/detail/offsets.hpp>
#include <boost/mpi/detail/antiques.hpp>
#include <boost/assert.hpp>

namespace boost { namespace mpi {

namespace detail {
// We're gathering at the root for a type that has an associated MPI
// datatype, so we'll use MPI_Gather to do all of the work.
template<typename T>
void
gather_impl(const communicator& comm, const T* in_values, int n, 
            T* out_values, int root, mpl::true_)
{
  MPI_Datatype type = get_mpi_datatype<T>(*in_values);
  BOOST_MPI_CHECK_RESULT(MPI_Gather,
                         (const_cast<T*>(in_values), n, type,
                          out_values, n, type, root, comm));
}

// We're gathering from a non-root for a type that has an associated MPI
// datatype, so we'll use MPI_Gather to do all of the work.
template<typename T>
void
gather_impl(const communicator& comm, const T* in_values, int n, int root, 
            mpl::true_ is_mpi_type)
{
  assert(comm.rank() != root);
  gather_impl(comm, in_values, n, (T*)0, root, is_mpi_type);
}

// We're gathering at the root for a type that does not have an
// associated MPI datatype, so we'll need to serialize
// it.
template<typename T>
void
gather_impl(const communicator& comm, const T* in_values, int n, T* out_values, 
            int const* nslot, int const* nskip, int root, mpl::false_)
{
  int nproc = comm.size();
  // first, gather all size, these size can be different for
  // each process
  packed_oarchive oa(comm);
  for (int i = 0; i < n; ++i) {
    oa << in_values[i];
  }
  bool is_root = comm.rank() == root;
  std::vector<int> oasizes(is_root ? nproc : 0);
  int oasize = oa.size();
  BOOST_MPI_CHECK_RESULT(MPI_Gather,
                         (&oasize, 1, MPI_INT,
                          c_data(oasizes), 1, MPI_INT, 
                          root, MPI_Comm(comm)));
  // Gather the archives, which can be of different sizes, so
  // we need to use gatherv.
  // Everything is contiguous (in the transmitted archive), so 
  // the offsets can be deduced from the collected sizes.
  std::vector<int> offsets;
  if (is_root) sizes2offsets(oasizes, offsets);
  packed_iarchive::buffer_type recv_buffer(is_root ? std::accumulate(oasizes.begin(), oasizes.end(), 0) : 0);
  BOOST_MPI_CHECK_RESULT(MPI_Gatherv,
                         (const_cast<void*>(oa.address()), int(oa.size()), MPI_BYTE,
                          c_data(recv_buffer), c_data(oasizes), c_data(offsets), MPI_BYTE, 
                          root, MPI_Comm(comm)));
  if (is_root) {
    for (int src = 0; src < nproc; ++src) {
      // handle variadic case
      int nb = nslot ? nslot[src] : n;
      int skip = nskip ? nskip[src] : 0;
      std::advance(out_values, skip);
      if (src == root) {
        BOOST_ASSERT(nb == n);
        for (int i = 0; i < nb; ++i) {
          *out_values++ = *in_values++;
        }
      } else {
        packed_iarchive ia(comm,  recv_buffer, boost::archive::no_header, offsets[src]);
        for (int i = 0; i < nb; ++i) {
          ia >> *out_values++;
        }
      }
    }
  }
}

// We're gathering at a non-root for a type that does not have an
// associated MPI datatype, so we'll need to serialize
// it.
template<typename T>
void
gather_impl(const communicator& comm, const T* in_values, int n, T* out_values,int root, 
            mpl::false_ is_mpi_type)
{
  gather_impl(comm, in_values, n, out_values, (int const*)0, (int const*)0, root, is_mpi_type);
}
} // end namespace detail

template<typename T>
void
gather(const communicator& comm, const T& in_value, T* out_values, int root)
{
  BOOST_ASSERT(out_values || (comm.rank() != root));
  detail::gather_impl(comm, &in_value, 1, out_values, root, is_mpi_datatype<T>());
}

template<typename T>
void gather(const communicator& comm, const T& in_value, int root)
{
  BOOST_ASSERT(comm.rank() != root);
  detail::gather_impl(comm, &in_value, 1, (T*)0, root, is_mpi_datatype<T>());
}

template<typename T>
void
gather(const communicator& comm, const T& in_value, std::vector<T>& out_values,
       int root)
{
  using detail::c_data;
  if (comm.rank() == root) {
    out_values.resize(comm.size());
  }
  ::boost::mpi::gather(comm, in_value, c_data(out_values), root);
}

template<typename T>
void
gather(const communicator& comm, const T* in_values, int n, T* out_values, 
       int root)
{
  detail::gather_impl(comm, in_values, n, out_values, root, 
                      is_mpi_datatype<T>());
}

template<typename T>
void
gather(const communicator& comm, const T* in_values, int n, 
       std::vector<T>& out_values, int root)
{
  if (comm.rank() == root) {
    out_values.resize(comm.size() * n);
  }
  ::boost::mpi::gather(comm, in_values, n, out_values.data(), root);
}

template<typename T>
void gather(const communicator& comm, const T* in_values, int n, int root)
{
  BOOST_ASSERT(comm.rank() != root);
  detail::gather_impl(comm, in_values, n, root, is_mpi_datatype<T>());
}


} } // end namespace boost::mpi

#endif // BOOST_MPI_GATHER_HPP

/* gather.hpp
BT7y+9Y7JW9Uxfk5PksKYXH+YBWCk790ibAyvvgZKgFmUnXoilfjOCkZ/RIgVkITCKeNPCYKgUh5ZpFxchaDqn6/t6QXQVUEmVzv52Bryyx5wfL4WSO+bRwIqp8e+hkKlr5BOu5bextr4LfPw0+o7cxorMXs3qWvDN62iZJ2eFUN/rklk0r4Mkt3DH5jyYft6HjxJCqep8y3pLH6Jh+OgScxRp5mA3QBiBv3F4HF1dwClYO1/ce/RYczJY78bev4kBX8gFs5PZsv+PzMAu3/BfWXGOFH7wk7UlhtCF6g9hL38aPD+c+U0zfm0Tbi0RFu1NdDSEgKOutLItYPItYD3zT5/HfUhJaF3PqZ1SCMQs6J5nt2L78Naf5lvpxN9Gsv6oJI8SV/wyIy2BV+gPEC/XgHrGQcqyV/tTyh50UYAY8+UEIvHBuZT9P4QHL9Frwi5cYhMJ4wyCUUkxYC/SA+Iwh+jljbAUuwa5X4m8HZS7Y40ejFEpOPxTPDU8TPU+QhySdvVZ46sP7ZRk5u7/Q8zk+96e/P2DiYdmmgR9nsv/HxKYH08EiD+XJe6vtk+lZ1LFRkuVWdEgott6rLdQrJ9ysE09+vIPubZXKCS34Pt/2GOK2076/BIO9yp3GoCP6jyAKIfkxzgTtSbZx3FC13lFUxXEcLF5E7srDSCPWSRArmKex8pM3zMgd7qnjAYthjTD6IS9DJU/r9d5WW9+E+9eUeMIxs25b73GTHjCHPkec3ZJ6AUtQn4uL9uH76Vu9VUJTu9RkO5KdmhsPOZeIE0ug2vEOgKbmIH6QHad1MephhgMIo97jNZCi4vZMb8Ufa6WrgP+4+YF4Wdy/60Pw/o8vi7lXvX2SxNtYTrcmRIHIq8bixPGs4YbhazgxczkS7IvWljZXI44p1DOtPzdgbwjsEtrdkkU7zqDRPWyKvf0TZ4bVmKlQ1fkQjF9A+0jq+T66Nu7vlbwLTk7iU+uq29PXDX0pfB4TXp/b19Uy5whNBnfc2k1XA8+s3xg+I2mrjsDj8XBLOvRhnqt/37QOfbkvnM/2Y8VejQN1OtsCAqdvhI0oO3l0EfqCh4dekq/Q2Sni18n9lENHA+930RbcKBCFf63PM8XBA8G315U6eDHJHuh/r9BLOLoYLrYwN+9F94I9NLTanmIWtm3mNGM5D/cafNWdvQVzcJDz/YJk2T2IHB7rpFHqL+WZnwxDFQvtpKorLYT+9W0yceevRwmThX0unaePwxA9pfJH1FmUrOiW+wKwBagZ/gf4zhvcVCRiqcFT4HZOCD1soWO0jClLL+353oPPYuc/ig/wwm/a/8pP8i3yVCm0jwB0q5gUrG/kGnvV4TUDQS70iC+d+7tIiL0sNr0d5I6v6qwj926bh9R6RUmNHK/WUV7zj+5CY54B4hNnPhHmDwCxRMJ9xi6RFvzvfT/KDHtqBdKcbpcw6PCzPmV8ZICJocLhY4NIuv4De4WHQs6AqIhC9qRFuOqlYN9EPV1qMMlG5ScqvUeWLCZV11Vh6up+uGjHOWyt3fwwLl3r1eOvWLuHacv9KFnyhJ7p/wYHusGR9pObJ2ohLlrQlQ60XvEA30f1Mt2b8+WdUmuYBdApqrEUJ7w7jnEbBtwkcGFSmgC+domfWNsWmD4+4aen5dh/t/appFMohhUONfvkC3SNIE2ilDcETnPj25qIh4dMc+7jQbfZR8Bz8FuFJV8R8OaAW6I3sG0vk/7f5xszzZ+/lgn2o9ADZCzLiA3XY8Z9cQiC6KfpyfP/NJU6apT51lcOevi5X0jMiZ0OOER+EjqfuRbb3Iwb52ANKCs495FEKULtXg49L7vNs6p90n2eRhBAXGqeD5KSLO4s=
*/