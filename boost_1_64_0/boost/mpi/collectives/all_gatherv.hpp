// Copyright (C) 2005, 2006 Douglas Gregor.

// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

// Message Passing Interface 1.1 -- Section 4.5. Gatherv
#ifndef BOOST_MPI_ALLGATHERV_HPP
#define BOOST_MPI_ALLGATHERV_HPP

#include <cassert>
#include <cstddef>
#include <numeric>
#include <vector>

#include <boost/mpi/exception.hpp>
#include <boost/mpi/datatype.hpp>
#include <boost/mpi/packed_oarchive.hpp>
#include <boost/mpi/packed_iarchive.hpp>
#include <boost/mpi/detail/point_to_point.hpp>
#include <boost/mpi/communicator.hpp>
#include <boost/mpi/environment.hpp>
#include <boost/mpi/detail/offsets.hpp>
#include <boost/mpi/detail/antiques.hpp>
#include <boost/assert.hpp>
#include <boost/scoped_array.hpp>

namespace boost { namespace mpi {

namespace detail {
// We're all-gathering for a type that has an associated MPI
// datatype, so we'll use MPI_Gather to do all of the work.
template<typename T>
void
all_gatherv_impl(const communicator& comm, const T* in_values,
                 T* out_values, int const* sizes, int const* displs, mpl::true_)
{
  // Make displacements if not provided
  scoped_array<int> new_offsets_mem(make_offsets(comm, sizes, displs, -1));
  if (new_offsets_mem) displs = new_offsets_mem.get();
  MPI_Datatype type = get_mpi_datatype<T>(*in_values);
  BOOST_MPI_CHECK_RESULT(MPI_Allgatherv,
                         (const_cast<T*>(in_values), sizes[comm.rank()], type,
                          out_values,
                          const_cast<int*>(sizes),
                          const_cast<int*>(displs),
                          type, 
                          comm));
}

// We're all-gathering for a type that does not have an
// associated MPI datatype, so we'll need to serialize
// it.
template<typename T>
void
all_gatherv_impl(const communicator& comm, const T* in_values,
                 T* out_values, int const* sizes, int const* displs,
                 mpl::false_ isnt_mpi_type)
{ 
  // convert displacement to offsets to skip
  scoped_array<int> skipped(make_skipped_slots(comm, sizes, displs));
  all_gather_impl(comm, in_values, sizes[comm.rank()], out_values, 
                  sizes, skipped.get(), isnt_mpi_type);
}
} // end namespace detail

template<typename T>
void
all_gatherv(const communicator& comm, const T& in_value, T* out_values,
            const std::vector<int>& sizes)
{
  using detail::c_data;
  assert(sizes.size()   == comm.size());
  assert(sizes[comm.rank()] == 1);
  detail::all_gatherv_impl(comm, &in_value, out_values, c_data(sizes), 0, is_mpi_datatype<T>());
}

template<typename T>
void
all_gatherv(const communicator& comm, const T* in_values, T* out_values,
            const std::vector<int>& sizes)
{
  using detail::c_data;
  assert(int(sizes.size()) == comm.size());
  detail::all_gatherv_impl(comm, in_values, out_values, c_data(sizes), 0, is_mpi_datatype<T>());
}

template<typename T>
void
all_gatherv(const communicator& comm, std::vector<T> const& in_values,  std::vector<T>& out_values,
           const std::vector<int>& sizes)
{
  using detail::c_data;
  assert(int(sizes.size()) == comm.size());
  assert(int(in_values.size()) == sizes[comm.rank()]);
  out_values.resize(std::accumulate(sizes.begin(), sizes.end(), 0));
  ::boost::mpi::all_gatherv(comm, c_data(in_values), c_data(out_values), sizes);
}


template<typename T>
void
all_gatherv(const communicator& comm, const T& in_value, T* out_values,
            const std::vector<int>& sizes, const std::vector<int>& displs)
{
  using detail::c_data;
  assert(sizes.size()   == comm.size());
  assert(displs.size() == comm.size());
  detail::all_gatherv_impl(comm, &in_value, 1, out_values,
                           c_data(sizes), c_data(displs), is_mpi_datatype<T>());
}

template<typename T>
void
all_gatherv(const communicator& comm, const T* in_values, T* out_values,
            const std::vector<int>& sizes, const std::vector<int>& displs)
{
  using detail::c_data;
  assert(sizes.size()   == comm.size());
  assert(displs.size() == comm.size());
  detail::all_gatherv_impl(comm, in_values, out_values,
                           c_data(sizes), c_data(displs), is_mpi_datatype<T>());
}

template<typename T>
void
all_gatherv(const communicator& comm, std::vector<T> const& in_values, std::vector<T>& out_values,
            const std::vector<int>& sizes, const std::vector<int>& displs)
{
  using detail::c_data;
  assert(sizes.size()   == comm.size());
  assert(displs.size() == comm.size());
  assert(in_values.size() == sizes[comm.rank()]);
  out_values.resize(std::accumulate(sizes.begin(), sizes.end(), 0));
  ::boost::mpi::all_gatherv(comm, c_data(in_values), c_data(out_values), sizes, displs);
}

} } // end namespace boost::mpi

#endif // BOOST_MPI_ALL_GATHERV_HPP

/* all_gatherv.hpp
mncNZUT6GHGzCGeW+RIBGo0fTaaMQ+mZPv/afpyKBeoDMQP9GdmrwvU88x4/U/DNJLEhbaTnlzfPI34hGTEGsGMZAZ7eeHkrrtx+xJhggc48u/0tFA0saxZmoP/U0zW3iJy/L71Yup6aL7uGr10o+zWp9f9+Uef1R58m9Z3zL+sA/j1dgD9E6qfQk0/93BWsHgwL1uoRcn7vqDCmRFzG+xy2G75pJv3cyz+7Etuk/X/nmv5d48bZehs8g5YEPJMbLRBM+ViE8c3hvAt7fKSItCf09dQerwP35keKUPbzHN85Wfxu4JcNL7/IpTYbQeXi7WladwvA5097Wv14C2Crx21u6FMUly9RgL9kwvA6Tws3ruCJoZHKsGsnaWNfZ87dfwZxLqlPL5x12B1uQD/j+TEw7WmUb5wlI2jJ54MpQDsKuosFecLXjwfbj/bzwBno5040Vvpi3an7eAGuitUbTIWyIXurux0+mK/rhFSdAtoGLGCJGgt2uXuI/4elKLYejQiHOuoTB2vs/v84SXA08Muo18p9W+dJDJeTe5FgGN+UtsyekIR0kgJH62xB5EoZs4eV/+N0Khq5itJp6L57stJsWw9t7Ex5NFnjDwNCFA4whSPByEFC0xhzCpGAZ+MqsjiC1vDhKcZPTgBSkX704+OSjJWM+m3tiaMtQ90W8ycChPq0qkM6EZKKf5TiP2Yl32+7gkfiQf7fJv7fBmW3QdTKsUp9W0+dyZWfa+vr1lOM01qc2ld5cQqthWmb5XKR8HdHB4dxdSfKh9fitzU8KI9OZ/PpJKhDzN5nFFPLeO0Y+jIZgxyh+qtm9ccs1eeq6q0exQ8DximU1tXXrXPBkl+zrn4CegF+LPUji6TyMFX5+1DZ+AlPt3W4aJWPVqNA1/jWDg7vNBt/0tL4n0/j+rd6kEobRaHbSArdRggmBi9TptJNNtYd31ixEWTcerhvABIJ/AaOgobUDWQG7BopyrwHNK3vNVasrzKONyEAHr838XjcgseFCo+/o9HKlO8vTSyP+IAPd+NYr2cPDnRyOdzL8iXFh2vq69ZgF98zQT9hAe1ToFej97FiNURBbK7GsGzj1zBeJJGh6t/MqustVV//AledQ6b8msaa1RO7wzh+YBZ+1FL4QVX4OHIhra6ECuz42Vxp1BjduSmofdCs/Yil9gWqNiISyYwcjJxgvDRRJt2GKqPofNXZlfV1K7GzWW4B87QFTB8FBu0CM8R9JRy+oqnmJ79qN7MmlpKavy1n4zwar3mQ6TOeQ/fJa9DLrLPOUudJVaeMotP9UO1B5L0dx+jG+psVn7JUvI4rorhbQbMf2jRO5AhbIwtFCbAVxNyeqQ4PrGDv5s/P+rx4N//zH5R/hST/ZlrWnxZZf0iSLPiiHsHxySP4DTX/T+WBuFnx3BnjmefIMF9/DvGcdkOeqnnOAuNRBePEreX7aDDxBLxBak+sZr9cRdQM6teo42Bk4zX7qo1vT1Xuohby+kw4Q7kaWg7b8Or93zPZfuUttxOGKNl83UD1JWdQyrbwsbaTVeQAM05GZeD5QursoTsrEJ/ppP9XWNerePkmOhZCPkC8dY8l0iBc8a0S6RGm9UlTxdw4tVHVjPhINtKI7TtZsBvIsonVB6n94RSbm4Bm1aLKTzKrUD/6FUz0yqRbhlrPlONRTuWfpPKi1Xe7RI4zdWS/zJ/VuX2QcVbH9kdpjWO+8eVTrPgsOL1jfOT8K3jASZOoPS6FceYBRVF/zTF+PZSP1HuAv9FZPIHmA+7Qbgvy1JhKITZk/r3ze/oaqwqQAQHbWPoIRqJfZGB4DA/jAzyMJ5R9ghDU1PNsleEwstcbp7uCxp8ryUM854c=
*/