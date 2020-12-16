// Copyright (C) 2005, 2006 Douglas Gregor <doug.gregor -at- gmail.com>.

// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

// Message Passing Interface 1.1 -- Section 4.4. Broadcast
#ifndef BOOST_MPI_BROADCAST_HPP
#define BOOST_MPI_BROADCAST_HPP

#include <boost/mpi/collectives_fwd.hpp>
#include <boost/mpi/exception.hpp>
#include <boost/mpi/datatype.hpp>
#include <boost/mpi/communicator.hpp>

namespace boost { namespace mpi {

/************************************************************************
 * Specializations                                                      *
 ************************************************************************/

/**
 * INTERNAL ONLY
 */
template<>
BOOST_MPI_DECL void
broadcast<const packed_oarchive>(const communicator& comm,
                                 const packed_oarchive& oa,
                                 int root);

/**
 * INTERNAL ONLY
 */
template<>
BOOST_MPI_DECL void
broadcast<packed_oarchive>(const communicator& comm, packed_oarchive& oa,
                           int root);

/**
 * INTERNAL ONLY
 */
template<>
BOOST_MPI_DECL void
broadcast<packed_iarchive>(const communicator& comm, packed_iarchive& ia,
                           int root);

/**
 * INTERNAL ONLY
 */
template<>
BOOST_MPI_DECL void
broadcast<const packed_skeleton_oarchive>(const communicator& comm,
                                          const packed_skeleton_oarchive& oa,
                                          int root);

/**
 * INTERNAL ONLY
 */
template<>
void
broadcast<packed_skeleton_oarchive>(const communicator& comm,
                                    packed_skeleton_oarchive& oa, int root);

/**
 * INTERNAL ONLY
 */
template<>
void
broadcast<packed_skeleton_iarchive>(const communicator& comm,
                                    packed_skeleton_iarchive& ia, int root);

/**
 * INTERNAL ONLY
 */
template<>
void broadcast<content>(const communicator& comm, content& c, int root);

/**
 * INTERNAL ONLY
 */
template<>
void broadcast<const content>(const communicator& comm, const content& c,
                              int root);

/************************************************************************
 * broadcast() implementation                                           *
 ************************************************************************/
namespace detail {
  // We're sending a type that has an associated MPI datatype, so
  // we'll use MPI_Bcast to do all of the work.
  template<typename T>
  void 
  broadcast_impl(const communicator& comm, T* values, int n, int root, 
                 mpl::true_)
  {
    BOOST_MPI_CHECK_RESULT(MPI_Bcast,
                           (values, n,
                            boost::mpi::get_mpi_datatype<T>(*values),
                            root, MPI_Comm(comm)));
  }

  // We're sending a type that does not have an associated MPI
  // datatype, so we'll need to serialize it.
  template<typename T>
  void
  broadcast_impl(const communicator& comm, T* values, int n, int root, 
                 mpl::false_ non_mpi_datatype)
  {
    // Implementation proposed by Lorenz Hübschle-Schneider
    if (comm.rank() == root) {
      packed_oarchive oa(comm);
      for (int i = 0; i < n; ++i) {
        oa << values[i];
      }
      std::size_t asize = oa.size();
      broadcast(comm, asize, root);
      void const* aptr = oa.address();
      BOOST_MPI_CHECK_RESULT(MPI_Bcast,
                             (const_cast<void*>(aptr), asize,
                              MPI_BYTE,
                              root, MPI_Comm(comm)));
    } else {
      packed_iarchive ia(comm);
      std::size_t asize;
      broadcast(comm, asize, root);
      ia.resize(asize);
      void* aptr = ia.address();
      BOOST_MPI_CHECK_RESULT(MPI_Bcast,
                             (aptr, asize,
                              MPI_BYTE,
                              root, MPI_Comm(comm)));
      for (int i = 0; i < n; ++i)
        ia >> values[i];
    }
  }
} // end namespace detail

template<typename T>
void broadcast(const communicator& comm, T& value, int root)
{
  detail::broadcast_impl(comm, &value, 1, root, is_mpi_datatype<T>());
}

template<typename T>
void broadcast(const communicator& comm, T* values, int n, int root)
{
  detail::broadcast_impl(comm, values, n, root, is_mpi_datatype<T>());
}

} } // end namespace boost::mpi

// If the user has already included skeleton_and_content.hpp, include
// the code to broadcast skeletons and content.
#ifdef BOOST_MPI_SKELETON_AND_CONTENT_HPP
#  include <boost/mpi/detail/broadcast_sc.hpp>
#endif

#endif // BOOST_MPI_BROADCAST_HPP

/* broadcast.hpp
osQ5pkaUmGGqQ4kpUgCVHVGEdB/xWq9fJys7t6vzP0cl6fZzodlr4e9x+LsF/hqKP72eo+NfRpj0+CNPEvt4jZDxCiZOto3XsZxl6m7PJA/ZUu5O1YBDHzITv2uGq/icuwfxpFZ211eZO2V20lwrpIKNHx2QgrRptub9A53zsbZ/h6n2zgylrr+4W8222ZtePTk6tv8BnnF9AufaiEm225jnUkPPs33OGsi6k/W+eznJ6M3/5O6Iy+PMDw+YJQYbfRCyMpj28krADnK1QCdGGy3vQhES8S9xgfBYj14NN/AYPd3/0MfI+fzjUC2fsXdZPa0KBbhpyqRxih4Nf1udf5b20XZrhTvHXBZa4apWrnGWOh/2kzr9FQUGDaVaTIFDVVHs/THG9rXHwxnDOoqHy6Ty4jv5eEJn8Ta3g+or2eKPPWtU5/7YO3t27I99rcQx3+jh0N4fRnbe3sBO2qtJ094jo7k9e/n5ozqG90wPZ3jVaeAN7gTehQLPUf4Vq/17L0QG9AvvAg4j/gqvYyZbWSBMNjH1PjbSV3vRk5v5NFnrXujOSnZQztl2flWbic9I0v8GJ+8v7Uu6ZnmvaSe9kqlv793NdlLUy4EciyAGLVhHP0L0I1RO+2RF6Kuo2E1XCoBrpohSBkamUacjC8OPcY8f6SPOmMEAY0kdgYLghi8ycb4LpaToAilKxx2Mj/+IWxZ76WLejKbVmHTFR5i0Ry5NLoJ5tKfa8LYckOsLIjXcfKbAHMwwm6JQnS6Z/bjIekN0/le/R/6IXXz/4aV+fdnwVA/7/qSxPVXG/X/XDV1oa+iF3txQrgfFlnEAjIm9dDfvXtrXHRCZyxWmSIWYqvBrclvuxcWFEPwNu4OokSu5zuVSp0bVeRzqEEZLRJmeA3Kc739mPxe27iF4i9lNJbcQDzkOdbn9Jyoq7Kuv24fkxQhw41naQtlxotwgTTvT+9Q9dH1ov3wf745DJjEv3hBF6t1J71L7xhf3Yc8NuoQOXtH1Q00KLaInU3MEN4OeAjC+9mcoTD+gJY5OQGLJpXUVRmMV6wo+MEzG0ebCXrhoOaRv40cVhyryadAg/dwLvrkmQkexeKQd/pMt5j8QfUMAnRul7nkSZ+N+KT0LiCHovf9xQF0JwNYiBzzspuvqFuUkXWu2L1FBwe624X2KsAzRKB3MoH4jqaM9jEePhZ5QK3UDeInFCIsDwDKWW46zBv+bti4/lx/zfZ0XQXdVgyjCywwbsF2Ktt96j4y6dKjYrcaFgnvCT/DQ5PcUOTPNS9FpdEUaXsUH4hccOLj2DyMG8E0maTUkXGIC+q4F0I96CKCP6HxWM2mIrrE4izI5FoNnGOIyxgSxwQKi3gSxyUPzC1Xnp1rUZDb+or7sZVuZL05HaBNNaCst0E40oUVQDI07gOJSVKUpbpNJpXyGWR7v1sU9fNkg3sMbefeP0OECe6G+iqx4u4g6JzfFY9IIiT2BK8ZON1u6XFp6oDtLrgcgS55Ra8YG0Q5WlKP0EAfzBjGR3nA9ljAguDUm3EyBe6qCe6p6zzF/KdKDge7nSKb9HMlkQN+MP5DbKkT9CSK0iwQkXY3+NTIHA8pdCGXwAiL2A+7nm0/2880nBj9vttIC7mWJ+ApAVmy6X74bMX8TndeISFOcgwM9NLm9AeFrUsfo4iDb/3ORzKmXB2lkFrgFmaLwfJM9NlrYo7cC1Re7U95C8bL7JV4Wh5df7D6TLW1aeHuH6wUUNXKxjzAm8XXqPuROXOL+fyWVzf+cB+sxrCQF4O9pFh8RxkszG7319viK0HxUrnbwvbGlOz+obW3YGcWkF5HOL8lCQq92ZA0gYls3Oe+liq1v4TMCQW8=
*/