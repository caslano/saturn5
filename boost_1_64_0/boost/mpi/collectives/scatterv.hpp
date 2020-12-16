// Copyright (C) 2011 Júlio Hoffimann.

// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

// Message Passing Interface 1.1 -- Section 4.6. Scatterv
#ifndef BOOST_MPI_SCATTERV_HPP
#define BOOST_MPI_SCATTERV_HPP

#include <boost/scoped_array.hpp>
#include <boost/mpi/collectives/scatter.hpp>
#include <boost/mpi/detail/offsets.hpp>
#include <boost/mpi/detail/antiques.hpp>

namespace boost { namespace mpi {

namespace detail {

//////////////////////////////////////////////
/// Implementation for MPI primitive types ///
//////////////////////////////////////////////

// We're scattering from the root for a type that has an associated MPI
// datatype, so we'll use MPI_Scatterv to do all of the work.
template<typename T>
void
scatterv_impl(const communicator& comm, const T* in_values, T* out_values, int out_size,
              const int* sizes, const int* displs, int root, mpl::true_)
{
  assert(!sizes || out_size == sizes[comm.rank()]);
  assert(bool(sizes) == bool(in_values));
  
  scoped_array<int> new_offsets_mem(make_offsets(comm, sizes, displs, root));
  if (new_offsets_mem) displs = new_offsets_mem.get();
  MPI_Datatype type = get_mpi_datatype<T>(*in_values);
  BOOST_MPI_CHECK_RESULT(MPI_Scatterv,
                         (const_cast<T*>(in_values), const_cast<int*>(sizes),
                          const_cast<int*>(displs), type,
                          out_values, out_size, type, root, comm));
}

// We're scattering from a non-root for a type that has an associated MPI
// datatype, so we'll use MPI_Scatterv to do all of the work.
template<typename T>
void
scatterv_impl(const communicator& comm, T* out_values, int out_size, int root, 
              mpl::true_ is_mpi_type)
{
  scatterv_impl(comm, (T const*)0, out_values, out_size, 
                (const int*)0, (const int*)0, root, is_mpi_type);
}

//////////////////////////////////////////////////
/// Implementation for non MPI primitive types ///
//////////////////////////////////////////////////

// We're scattering from the root for a type that does not have an
// associated MPI datatype, so we'll need to serialize it.
template<typename T>
void
scatterv_impl(const communicator& comm, const T* in_values, T* out_values, int out_size,
              int const* sizes, int const* displs, int root, mpl::false_)
{
  packed_oarchive::buffer_type sendbuf;
  bool is_root = comm.rank() == root;
  int nproc = comm.size();
  std::vector<int> archsizes;
  if (is_root) {
    assert(out_size == sizes[comm.rank()]);
    archsizes.resize(nproc);
    std::vector<int> skipped;
    if (displs) {
      skipped.resize(nproc);
      offsets2skipped(sizes, displs, c_data(skipped), nproc);
      displs = c_data(skipped);
    }
    fill_scatter_sendbuf(comm, in_values, sizes, (int const*)0, sendbuf, archsizes);
  }
  dispatch_scatter_sendbuf(comm, sendbuf, archsizes, (T const*)0, out_values, out_size, root);
}

// We're scattering to a non-root for a type that does not have an
// associated MPI datatype. input data not needed.
// it.
template<typename T>
void
scatterv_impl(const communicator& comm, T* out_values, int n, int root, 
              mpl::false_ isnt_mpi_type)
{
  assert(root != comm.rank());
  scatterv_impl(comm, (T const*)0, out_values, n, (int const*)0, (int const*)0, root, isnt_mpi_type);
}

} // end namespace detail

template<typename T>
void
scatterv(const communicator& comm, const T* in_values,
         const std::vector<int>& sizes, const std::vector<int>& displs,
         T* out_values, int out_size, int root)
{
  using detail::c_data;
  detail::scatterv_impl(comm, in_values, out_values, out_size, c_data(sizes), c_data(displs), 
                root, is_mpi_datatype<T>());
}

template<typename T>
void
scatterv(const communicator& comm, const std::vector<T>& in_values, 
         const std::vector<int>& sizes, const std::vector<int>& displs,
         T* out_values, int out_size, int root)
{
  using detail::c_data;
  ::boost::mpi::scatterv(comm, c_data(in_values), sizes, displs,
                         out_values, out_size, root);
}

template<typename T>
void scatterv(const communicator& comm, T* out_values, int out_size, int root)
{
  BOOST_ASSERT(comm.rank() != root);
  detail::scatterv_impl(comm, out_values, out_size, root, is_mpi_datatype<T>());
}

///////////////////////
// common use versions
///////////////////////
template<typename T>
void
scatterv(const communicator& comm, const T* in_values,
         const std::vector<int>& sizes, T* out_values, int root)
{
  using detail::c_data;
  detail::scatterv_impl(comm, in_values, out_values, sizes[comm.rank()], 
                        c_data(sizes), (int const*)0,
                        root, is_mpi_datatype<T>());
}

template<typename T>
void
scatterv(const communicator& comm, const std::vector<T>& in_values,
         const std::vector<int>& sizes, T* out_values, int root)
{
  ::boost::mpi::scatterv(comm, &in_values[0], sizes, out_values, root);
}

template<typename T>
void
scatterv(const communicator& comm, const T* in_values,
         T* out_values, int n, int root)
{
  detail::scatterv_impl(comm, in_values, out_values, n, (int const*)0, (int const*)0,
                root, is_mpi_datatype<T>());
}

template<typename T>
void
scatterv(const communicator& comm, const std::vector<T>& in_values,
         T* out_values, int out_size, int root)
{
  ::boost::mpi::scatterv(comm, &in_values[0], out_values, out_size, root);
}

} } // end namespace boost::mpi

#endif // BOOST_MPI_SCATTERV_HPP

/* scatterv.hpp
sZRKR0UGJx2dkpjaX4E2pCVGG+1sv/KmAqF1+brKCoP5+qxgG01Gcxxl+fQbIU2Kf+axFzeyqIin2XjF/P79KvNPLENkdQrTNSdyE2VwyZfGj5drdLM8koX/wBqblHAjkghrKZJ5dtmnVfP+2NNJ/xXgocyTxVMJ4tDsXpFSzyJlwRrgH0AwgGbpMit+niTr/sBtL9VvgQUlhsmY1U7hUDfEn4aO5R8ep1mySZQLhkMTQXJW83A3DTAPzMfQvZGsQpvIBpJhitDrf0fSQ04LpVow4zhf98aHP7ReQwWH+uobft5G0xdd10YDXWzqDWkaeknT0JvQAjtPy//VHvP9RMLybgDQluOK15FN2gm/aGf4fUaHvXYajPY64vt94UXkDZstAfXdUofESAfZEoR433p0belW8t4rMVti/ME6vjMTgfjIlYVHqHNemP11mqs9illpESW1UYLOUA/9DWlWvw1+GV35tgT5imkL9SHicCcz6Po+KU78XJ/HqfTQY2Oem3z/3E30mSKi57QL9CZCJ4bbE2Hs0UEOLiF3Sp6EQD+yiYI/stiPrmmUppm1sPyQ0GD2gwbh1XPGewpbAU70CGUyFJqpcAN8TD726HhXGM80pYk6Q/HANTs+dkuXJnDa0F0zL3ypWf94c+5umr969TXnfLtqUttnFHMSxd/VP9c8fzfjjqbb7/VG0/ld/tp0/tkPNZ1/y87Y/On822Prew6paKzvmfha8+Md82TT/Sl8VfKd9J0DGhbiSJPfNUjB2PavMDipmVT1kpiOejnSOoQgBlxEmmGgGj7foqvgFk0bYPmFuOWpGNrfsXqI/oRFV8JEmBduYc9yT1pbOUxH/TSV8ZRk0M4fy6mhWwjwzTQGj/6MBZVU+LuquuWSTtPr4dSj2DAx5V/wRu6foW/6E9HWZ3bZaWtgkGmD4G14S9jY87Ewk6vCzUfLxtrPl94UZD192nE49t3jPNtpplDfHKGq46TZ+qOs+u/EVZ8mdFiC+L/s6l9OAyMUvOs3Fu+FzEOT7bcjSMZ6wnxpLhb9TX3R5Df1A39SnMHA7REKAz8x6m+ra+jbALbXo0n83ZUsCXiRFvuX+dsaC7ay+CxDv83McVPOOZyDfBZzqfUq4meC6J0Qd/nptmOSHOB4ZpH+w44I+aY8CVbwP49FPBDu5H/2Ka00YrY3GH2CKNypwJczUBl50hxOa//VMJw1T7P05ZZWkP6MZOrIIhmXM7ZypAas/KxZeRxV/omqPB0qswbp3eoOC4VfiCrcVRXuj4Vz9zEtev1BtTI7i4t2YhM7zVpzqFblU1yrNsn2ILqd/VQdWP0iejGC+a8Av2plBIma3hs1yHsVkEeTkDxV0JXsAMdO2AUlG9gfAxM93zYLNefuoawCY5cnOQEKA72epgKC7IfIG8G8TRSsI6W4aDsySn2SzM5h+opBUDOxYH/aC+MbisOpgQ7QRmIefM1vKP46OeAJpaJu334ijftDrxUXbYIrOoDNyduEx/h22hztGcYuN7T/GHFej8FLSSI2fkAtPDikdy1fUFpQAUcz5JVN9TbA2CxvwEbaC57kvg2mVX/aM57xxYeyAiOx4oo+yj8zUHEoCD5/328QW2so6ZsEz5+FGsx18WF4aDygugUDRnJ/NRBXtSiwBuRSfmNpwUbeEA/LG9JGPsIflpfIvaW5e9Ne8DZuyAsgjweQpQWQ7y4On59Wws91e0nyig+NDHqmgCpHz3h58Ai8mTMK29gcS3CzQ6SsQQP0Fn91YWA4TYobqBKQo834QOWFlGDB5tDTejuX4M6lhDuzn2DcWUJG8IcAX6BN8B24b4py/Pp+ivVOe1YiZu/jlpf+JgK3O5g=
*/