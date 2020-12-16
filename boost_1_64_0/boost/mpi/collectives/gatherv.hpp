// Copyright (C) 2011 Júlio Hoffimann.

// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

// Message Passing Interface 1.1 -- Section 4.5. Gatherv
#ifndef BOOST_MPI_GATHERV_HPP
#define BOOST_MPI_GATHERV_HPP

#include <vector>

#include <boost/mpi/exception.hpp>
#include <boost/mpi/datatype.hpp>
#include <boost/mpi/packed_oarchive.hpp>
#include <boost/mpi/packed_iarchive.hpp>
#include <boost/mpi/detail/point_to_point.hpp>
#include <boost/mpi/communicator.hpp>
#include <boost/mpi/environment.hpp>
#include <boost/mpi/detail/offsets.hpp>
#include <boost/assert.hpp>
#include <boost/scoped_array.hpp>

namespace boost { namespace mpi {

namespace detail {
  // We're gathering at the root for a type that has an associated MPI
  // datatype, so we'll use MPI_Gatherv to do all of the work.
  template<typename T>
  void
  gatherv_impl(const communicator& comm, const T* in_values, int in_size, 
               T* out_values, const int* sizes, const int* displs, int root, mpl::true_)
  {
    MPI_Datatype type = get_mpi_datatype<T>(*in_values);
    BOOST_MPI_CHECK_RESULT(MPI_Gatherv,
                           (const_cast<T*>(in_values), in_size, type,
                            out_values, const_cast<int*>(sizes), const_cast<int*>(displs),
                            type, root, comm));
  }

  // We're gathering from a non-root for a type that has an associated MPI
  // datatype, so we'll use MPI_Gatherv to do all of the work.
  template<typename T>
  void
  gatherv_impl(const communicator& comm, const T* in_values, int in_size, int root, 
              mpl::true_)
  {
    MPI_Datatype type = get_mpi_datatype<T>(*in_values);
    BOOST_MPI_CHECK_RESULT(MPI_Gatherv,
                           (const_cast<T*>(in_values), in_size, type,
                            0, 0, 0, type, root, comm));
  }

  // We're gathering at the root for a type that does not have an
  // associated MPI datatype, so we'll need to serialize
  // it. Unfortunately, this means that we cannot use MPI_Gatherv, so
  // we'll just have all of the non-root nodes send individual
  // messages to the root.
  template<typename T>
  void
  gatherv_impl(const communicator& comm, const T* in_values, int in_size, 
               T* out_values, const int* sizes, const int* displs, int root, mpl::false_)
  {
    // convert displacement to offsets to skip
    scoped_array<int> skipped(make_skipped_slots(comm, sizes, displs, root));
    gather_impl(comm, in_values, in_size, out_values, sizes, skipped.get(), root, mpl::false_());
  }

  // We're gathering at a non-root for a type that does not have an
  // associated MPI datatype, so we'll need to serialize
  // it.
  template<typename T>
  void
  gatherv_impl(const communicator& comm, const T* in_values, int in_size, int root, 
              mpl::false_)
  {
    gather_impl(comm, in_values, in_size, (T*)0,(int const*)0,(int const*)0, root,
                mpl::false_());
  }
} // end namespace detail

template<typename T>
void
gatherv(const communicator& comm, const T* in_values, int in_size,
        T* out_values, const std::vector<int>& sizes, const std::vector<int>& displs,
        int root)
{
  if (comm.rank() == root)
    detail::gatherv_impl(comm, in_values, in_size,
                         out_values, &sizes[0], &displs[0],
                         root, is_mpi_datatype<T>());
  else
    detail::gatherv_impl(comm, in_values, in_size, root, is_mpi_datatype<T>());
}

template<typename T>
void
gatherv(const communicator& comm, const std::vector<T>& in_values,
        T* out_values, const std::vector<int>& sizes, const std::vector<int>& displs,
        int root)
{
  ::boost::mpi::gatherv(comm, &in_values[0], in_values.size(), out_values, sizes, displs, root);
}

template<typename T>
void gatherv(const communicator& comm, const T* in_values, int in_size, int root)
{
  BOOST_ASSERT(comm.rank() != root);
  detail::gatherv_impl(comm, in_values, in_size, root, is_mpi_datatype<T>());
}

template<typename T>
void gatherv(const communicator& comm, const std::vector<T>& in_values, int root)
{
  BOOST_ASSERT(comm.rank() != root);
  detail::gatherv_impl(comm, &in_values[0], in_values.size(), root, is_mpi_datatype<T>());
}

///////////////////////
// common use versions
///////////////////////
template<typename T>
void
gatherv(const communicator& comm, const T* in_values, int in_size,
        T* out_values, const std::vector<int>& sizes, int root)
{
  int nprocs = comm.size();

  std::vector<int> displs( nprocs );
  for (int rank = 0, aux = 0; rank < nprocs; ++rank) {
    displs[rank] = aux;
    aux += sizes[rank];
  }
  ::boost::mpi::gatherv(comm, in_values, in_size, out_values, sizes, displs, root);
}

template<typename T>
void
gatherv(const communicator& comm, const std::vector<T>& in_values,
        T* out_values, const std::vector<int>& sizes, int root)
{
  ::boost::mpi::gatherv(comm, &in_values[0], in_values.size(), out_values, sizes, root);
}

} } // end namespace boost::mpi

#endif // BOOST_MPI_GATHERV_HPP

/* gatherv.hpp
8drQqcNdco1lMTosPnKZ05mQ/W47jXjTa17kLXgFm05ADYaqfCMhX1VYl42HA91efVFrIij352JJtygGlktJtwFHyKy9Qm1H1J4TB8csdeB43pclxp7uJVdapbHuN2oxmcqSEl7nhmooMnq4hc6Lhc6tHzPqOQicSxWYpZZIqZ2q1D4PH56RR0z6/5zah1VRIstaKLKsRa6d9PdToWUtdTNQ6ZL0SkyX2DI6qxNHD/Zp1N0g+Ybv38sD1YwNGjdkc9xMM92idK/AWddX4NeeYbyyHSWwvC5SJLiiWnPDLkIUDFZcvkjff7qvzOnumGxEdlJ7TYbbHEQfHC1VsUfP9NRr5u/IHVEwxAX/z29A415eoehr3AtQ6eH/AN96iph8zYQIKNWeoW74pr2XusKk5yx68unwNvBBthPCkBGe08fFNwr/poBwUEtymWABYxkdZ+6qf6G7RvREKVIGPelFcJ/9I/WSsnuTbC6of8dT29e0rE4zFEvRHgYVwBN9PrCAUXRKv6OX0j1+JHj9R+uLboeTH3o4IvicXMc3vMqY9gstgb/O5wSrLRJYit36phbCtyaGsm9WuVfqXx7OfFdcaZyYIH6kcmfBgNL16LlGvz4IuRXu3sYZdxNYZn2w03JEt6RPytMs17iTZ3LTRwTYOOkoOd/4E5861fE58nT8d35M/8xvMyz36wVdC0cYD8DMlTAUGLsgk74PpOojwLhsGr//F3tHAhhVdcxuNrAkG/KBAAECBAQNl1KgggTkkFC0RgkSwAtRVD4LCMIG0RIOQypriNUq9VZUrGih3hgtWlAKqKhRqdIKLWrUHzZoWmNcNZrO8eb/v5u/yQa092pC9h3zrnnz5s2bY48l3Of7xMQGdYcILafqbYAYuRXTUIssmPgP4cflz5g2EvN51Sv4Ba/yrA3504500gTdKuxXJ5YcEqu+sqPgDrvPHvU61m1eibQFH0v/3yPzYzlO/PZvNBdq7CTPGS4uwv3s3o22by0db+lINy5ItN+77iZZmK8FxpzQH3+D/huX4k/zoG8AAKWqLkiDrHcSVaPXWlkfJ1DWu4nq0J5jZb3KWf0SFcAzrazHOGuQAHw/xcxaz1kPuRTAXZIVWAHJD0jvHjWT58CxP5Cg3GmmncMHXl+CsMZMHuUfC2lYfZGZlg3Ve1L1C8y0dH+2qjuJ08TZVTxuU4/6Y+k/uZW+4p9hxhzjNYkxo7N8foE7Uj+83wERtDiqhE8xPmhnKoRfCDuFX1pSJUASOgAovgZcWIxR+uBvQ469TwNJxzuTDT0+bi8bh3Vkf07fafZCwWO6xJn8ZZmL/bPI+J5kfXYSuRjqEn0OncEGPZpWwgksbqerye10NWXB44OhqZFXp5WhvTGex5Lna2d3Pb0sEyXtLzT2xE10pkJmsL5oAg6bFcPb2fx98/13xPtC4rqJjyNjLbA6zKtQ32qA37mfzrhMGAscicUfaIGkqnFA2pzcZ1eC1mma2fh0XAPiCu9JU42D1PlQ8SnY+ZdBa4D8aNSabW86ZPVHrvph1g+BVScfmNifX1S9CM44vj9XMnF9TPp4N5B8WuhZfxL5fuNloOF0sWbiR6b97wSZiVoWo7Kw2xjktm/tzqGnzUhiu8d5jyawqSk/OgLcs33/dWjTyD7jPruBEGqQBHy06bzJVNQpkFktSX8famtu1TwcsqR/1lYNsppYx6zPI+RKEEmC7bFgCZUbhx1sj9UKlhl9cP2KFK9px5bv/H6kdFZ83M5WdNTJxpEKbrlPqLcKN9DZLt6+ak+d5dsKdNfigd+PxPSp4nBIQ6c7Tr6QQz2VQ6EOLOiHbnGBoCvUPH3H9d1M75/f1tnkQUZbwMo=
*/