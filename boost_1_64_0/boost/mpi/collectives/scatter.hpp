// Copyright (C) 2005, 2006 Douglas Gregor.

// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

// Message Passing Interface 1.1 -- Section 4.6. Scatter
#ifndef BOOST_MPI_SCATTER_HPP
#define BOOST_MPI_SCATTER_HPP

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
// We're scattering from the root for a type that has an associated MPI
// datatype, so we'll use MPI_Scatter to do all of the work.
template<typename T>
void
scatter_impl(const communicator& comm, const T* in_values, T* out_values, 
             int n, int root, mpl::true_)
{
  MPI_Datatype type = get_mpi_datatype<T>(*in_values);
  BOOST_MPI_CHECK_RESULT(MPI_Scatter,
                         (const_cast<T*>(in_values), n, type,
                          out_values, n, type, root, comm));
}

// We're scattering from a non-root for a type that has an associated MPI
// datatype, so we'll use MPI_Scatter to do all of the work.
template<typename T>
void
scatter_impl(const communicator& comm, T* out_values, int n, int root, 
             mpl::true_)
{
  MPI_Datatype type = get_mpi_datatype<T>(*out_values);
  BOOST_MPI_CHECK_RESULT(MPI_Scatter,
                         (0, n, type,
                          out_values, n, type,
                          root, comm));
}

// Fill the sendbuf while keeping trac of the slot's footprints
// Used in the first steps of both scatter and scatterv
// Nslots contains the number of slots being sent 
// to each process (identical values for scatter).
// skiped_slots, if present, is deduced from the 
// displacement array authorised be the MPI API, 
// for some yet to be determined reason.
template<typename T>
void
fill_scatter_sendbuf(const communicator& comm, T const* values, 
                     int const* nslots, int const* skipped_slots,
                     packed_oarchive::buffer_type& sendbuf, std::vector<int>& archsizes) {
  int nproc = comm.size();
  archsizes.resize(nproc);
  
  for (int dest = 0; dest < nproc; ++dest) {
    if (skipped_slots) { // wee need to keep this for backward compatibility
      for(int k= 0; k < skipped_slots[dest]; ++k) ++values;
    }
    packed_oarchive procarchive(comm);
    for (int i = 0; i < nslots[dest]; ++i) {
      procarchive << *values++;
    }
    int archsize = procarchive.size();
    sendbuf.resize(sendbuf.size() + archsize);
    archsizes[dest] = archsize;
    char const* aptr = static_cast<char const*>(procarchive.address());
    std::copy(aptr, aptr+archsize, sendbuf.end()-archsize);
  }
}

template<typename T, class A>
T*
non_const_data(std::vector<T,A> const& v) {
  using detail::c_data;
  return const_cast<T*>(c_data(v));
}

// Dispatch the sendbuf among proc.
// Used in the second steps of both scatter and scatterv
// in_value is only provide in the non variadic case.
template<typename T>
void
dispatch_scatter_sendbuf(const communicator& comm, 
                         packed_oarchive::buffer_type const& sendbuf, std::vector<int> const& archsizes,
                         T const* in_values,
                         T* out_values, int n, int root) {
  // Distribute the sizes
  int myarchsize;
  BOOST_MPI_CHECK_RESULT(MPI_Scatter,
                         (non_const_data(archsizes), 1, MPI_INT,
                          &myarchsize, 1, MPI_INT, root, comm));
  std::vector<int> offsets;
  if (root == comm.rank()) {
    sizes2offsets(archsizes, offsets);
  }
  // Get my proc archive
  packed_iarchive::buffer_type recvbuf;
  recvbuf.resize(myarchsize);
  BOOST_MPI_CHECK_RESULT(MPI_Scatterv,
                         (non_const_data(sendbuf), non_const_data(archsizes), c_data(offsets), MPI_BYTE,
                          c_data(recvbuf), recvbuf.size(), MPI_BYTE,
                          root, MPI_Comm(comm)));
  // Unserialize
  if ( in_values != 0 && root == comm.rank()) {
    // Our own local values are already here: just copy them.
    std::copy(in_values + root * n, in_values + (root + 1) * n, out_values);
  } else {
    // Otherwise deserialize:
    packed_iarchive iarchv(comm, recvbuf);
    for (int i = 0; i < n; ++i) {
      iarchv >> out_values[i];
    }
  }
}

// We're scattering from the root for a type that does not have an
// associated MPI datatype, so we'll need to serialize it.
template<typename T>
void
scatter_impl(const communicator& comm, const T* in_values, T* out_values, 
             int n, int root, mpl::false_)
{
  packed_oarchive::buffer_type sendbuf;
  std::vector<int> archsizes;
  
  if (root == comm.rank()) {
    std::vector<int> nslots(comm.size(), n);
    fill_scatter_sendbuf(comm, in_values, c_data(nslots), (int const*)0, sendbuf, archsizes);
  }
  dispatch_scatter_sendbuf(comm, sendbuf, archsizes, in_values, out_values, n, root);
}

template<typename T>
void
scatter_impl(const communicator& comm, T* out_values, int n, int root, 
             mpl::false_ is_mpi_type)
{ 
  scatter_impl(comm, (T const*)0, out_values, n, root, is_mpi_type);
}
} // end namespace detail

template<typename T>
void
scatter(const communicator& comm, const T* in_values, T& out_value, int root)
{
  detail::scatter_impl(comm, in_values, &out_value, 1, root, is_mpi_datatype<T>());
}

template<typename T>
void
scatter(const communicator& comm, const std::vector<T>& in_values, T& out_value,
        int root)
{
  using detail::c_data;
  ::boost::mpi::scatter<T>(comm, c_data(in_values), out_value, root);
}

template<typename T>
void scatter(const communicator& comm, T& out_value, int root)
{
  BOOST_ASSERT(comm.rank() != root);
  detail::scatter_impl(comm, &out_value, 1, root, is_mpi_datatype<T>());
}

template<typename T>
void
scatter(const communicator& comm, const T* in_values, T* out_values, int n,
        int root)
{
  detail::scatter_impl(comm, in_values, out_values, n, root, is_mpi_datatype<T>());
}

template<typename T>
void
scatter(const communicator& comm, const std::vector<T>& in_values, 
        T* out_values, int n, int root)
{
  ::boost::mpi::scatter(comm, &in_values[0], out_values, n, root);
}

template<typename T>
void scatter(const communicator& comm, T* out_values, int n, int root)
{
  BOOST_ASSERT(comm.rank() != root);
  detail::scatter_impl(comm, out_values, n, root, is_mpi_datatype<T>());
}

} } // end namespace boost::mpi

#endif // BOOST_MPI_SCATTER_HPP

/* scatter.hpp
kOXjCgJYXFRBcY4qCVBlaDOB+q2AqgxAbI1M60b7OKGRLzG3EtxAUNeLraLH6YPNvl9v6/uV3FTVQdJDyETv1SWrJYbjpo1qJg5BQ30TsmC62CPyvWItdaDxAwC13MYa78mmvV16ioyXPT4cIl16GvG5XmLKacdOcQO8x6gz3sKLYjSwKdlsYJTZwJPJ0gABXQbXF3ni24Hq7kbtRksbOuQCqI8QwlxG9u+Dnme0cHlgnGCLu4cccZMS/JZ31Fvf3tKCvVNKIUssAPgShATkPItCy+Smv8GT+yU21QogQUAfEmsgbqaVPKuwOW0NOn0XjzDGaxzuha9OCNnfGPJzrzPk44lIGswuPsY0xvIn4XWpRf0un4lNOqDzZsISSnYFhiNpJGcUxU8KgTpOX2aiyjobqkxUbT6ByzEC7meMdiOjW/2lOZhatmQeZUY3doeWQU7xIU/h3BgbpcJrrutEc6O857U0IGsZYU7k6SdzyaA5Pwukr3e8xuxLm9AGoCVMOYUmDKQ1Px6njZynL2hN0GFAOXnpAR+pbWWyXCREZXGfVefkphe2R2Sg+/8pXCfkIwhp91JpWL2cPAMgAGTjm3soDV0Ts1nFUh4E+eYlPz19vYqT2v/PJtj/5R/L/zVsW2BFig+9AIwIH7qKzxLuuuxpsnsQM0g6TTXz/vXeE3F4X7S//0F77P844sYa8Crfpl38UxhPV/pno/7PK/G9S5N8SkMmB+Db7B9LaoDFirgs/NLFG6Uk/BnqHuFv4C/9/eRSMw/tH7nVKnLfiZflsvX1UI6EJMbhW5XyUi0BqEUAK3PoPtG2nMljMtrSdKNrxZUk6rkRjj+h3agqoKoB0b0m9GPVicAJpQCSFLSgMdQRw+QpxpJ7qL0cygTZzaSquWQ5oBUfcgV+hGOSkh9alxX/WIs40ZA2v8y7PZmnhOaSpiAn1wviqTL8M9+YVMG7FMqIDlPa/n+GDpPl/xapSpEXZNRGPfw52fjtYcET9LLqw0FnG8l3Y9bNZpYV6gFZw940Co10MOAwjEeR25RvHgSGlpb54d0WI5ueIFYesZiXbW6TJheaNHm3O/rGbrz+nKUy87y8Bxl7d1IqlLBYlQnEwfqI86EOPcSF7NJOHzotbV11JeDDMbK0pj7wQWBHjcE76L5p6m3V4xF7JME6Ym/nI2T6bt4nyJ4Sf5ZbKy94EzmLuZda61LxyhbeCRLGn9G0DP4SoG4FlERDiyCXLgAFfPbSWaOZovcZLNOiEiJO5evKykmECtd+JHJY/Vuz/5dKU7fuoqboOPuz8vmgr8IibmM6NeizbvfYRufNR/P4dBQfK/4LUA66rv+IIy19IihPs3wbv0ShUV8BzI2X9Ou8Obm+wjeVUsCtt3KJ5ukzv3/vb/79OPfdJt7/46if1ET9oXHU/8M7Tb9ff74/Nvy3320ePs9BbPi50r6j//s36L6/oeA4zZHuWOUd3tfZXc9N26DyFGPZBhHx9NAxBS73b7xHLeuV/HU7f43H0AfgE1V1h04ihRK0CA2046u3l8KaN7yF6iUn6wP3ZWo0VV46zHwEOK74Fzx+4ICViRqH0IFgOrlW2GyZk9j0H+r7O1Iv/BmGl9/HIqW7hPtBrwrRCDh/Em51cWyOCnEeOgK7EBSiE6OeITiqE/EcCDHf/4FrVjOoKa/RP0UOPjquNo99vNZQYUljVvTgZ6DEggwoEpzsoa/eROg5fvW2oF9mfwZZ/UmPoz/pDv3xSX98rP4m/dFa1h/WRYLizvgh8c/2sjxM9Lm9LDjEv73BZPE/aIxqbQ+QuYhH4iW77h+xuqowjmebV9vbOMN/qj4L1l38aY97mmW8YyhVjMMHqNQ=
*/