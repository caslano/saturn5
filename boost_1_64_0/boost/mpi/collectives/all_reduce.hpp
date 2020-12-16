// Copyright (C) 2005-2006 Douglas Gregor <doug.gregor -at- gmail.com>
// Copyright (C) 2004 The Trustees of Indiana University

// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//   Authors: Douglas Gregor
//            Andrew Lumsdaine

// Message Passing Interface 1.1 -- Section 4.9.1. Reduce
#ifndef BOOST_MPI_ALL_REDUCE_HPP
#define BOOST_MPI_ALL_REDUCE_HPP

#include <vector>

#include <boost/mpi/inplace.hpp>

// All-reduce falls back to reduce() + broadcast() in some cases.
#include <boost/mpi/collectives/broadcast.hpp>
#include <boost/mpi/collectives/reduce.hpp>

namespace boost { namespace mpi {
namespace detail {
  /**********************************************************************
   * Simple reduction with MPI_Allreduce                                *
   **********************************************************************/
  // We are reducing for a type that has an associated MPI
  // datatype and operation, so we'll use MPI_Allreduce directly.
  template<typename T, typename Op>
  void
  all_reduce_impl(const communicator& comm, const T* in_values, int n,
                  T* out_values, Op /*op*/, mpl::true_ /*is_mpi_op*/,
                  mpl::true_ /*is_mpi_datatype*/)
  {
    BOOST_MPI_CHECK_RESULT(MPI_Allreduce,
                           (const_cast<T*>(in_values), out_values, n,
                            boost::mpi::get_mpi_datatype<T>(*in_values),
                            (is_mpi_op<Op, T>::op()), comm));
  }

  /**********************************************************************
   * User-defined reduction with MPI_Allreduce                          *
   **********************************************************************/
  // We are reducing at the root for a type that has an associated MPI
  // datatype but with a custom operation. We'll use MPI_Reduce
  // directly, but we'll need to create an MPI_Op manually.
  template<typename T, typename Op>
  void
  all_reduce_impl(const communicator& comm, const T* in_values, int n,
                  T* out_values, Op /* op */, mpl::false_ /*is_mpi_op*/,
                  mpl::true_ /*is_mpi_datatype*/)
  {
    user_op<Op, T> mpi_op;
    BOOST_MPI_CHECK_RESULT(MPI_Allreduce,
                           (const_cast<T*>(in_values), out_values, n,
                            boost::mpi::get_mpi_datatype<T>(*in_values),
                            mpi_op.get_mpi_op(), comm));
  }

  /**********************************************************************
   * User-defined, tree-based reduction for non-MPI data types          *
   **********************************************************************/
  // We are reducing at the root for a type that has no associated MPI
  // datatype and operation, so we'll use a simple tree-based
  // algorithm.
  template<typename T, typename Op>
  void
  all_reduce_impl(const communicator& comm, const T* in_values, int n,
                  T* out_values, Op op, mpl::false_ /*is_mpi_op*/,
                  mpl::false_ /*is_mpi_datatype*/)
  {
    if (in_values == MPI_IN_PLACE) {
      // if in_values matches the in place tag, then the output
      // buffer actually contains the input data.
      // But we can just go back to the out of place 
      // implementation in this case.
      // it's not clear how/if we can avoid the copy.
      std::vector<T> tmp_in( out_values, out_values + n);
      reduce(comm, &(tmp_in[0]), n, out_values, op, 0);
    } else {
      reduce(comm, in_values, n, out_values, op, 0);
    }
    broadcast(comm, out_values, n, 0);
  }
} // end namespace detail

template<typename T, typename Op>
inline void
all_reduce(const communicator& comm, const T* in_values, int n, T* out_values,
           Op op)
{
  detail::all_reduce_impl(comm, in_values, n, out_values, op,
                          is_mpi_op<Op, T>(), is_mpi_datatype<T>());
}

template<typename T, typename Op>
inline void
all_reduce(const communicator& comm, inplace_t<T*> inout_values, int n, Op op)
{
  all_reduce(comm, static_cast<const T*>(MPI_IN_PLACE), n, inout_values.buffer, op);
}

template<typename T, typename Op>
inline void
all_reduce(const communicator& comm, inplace_t<T> inout_values, Op op)
{
  all_reduce(comm, static_cast<const T*>(MPI_IN_PLACE), 1, &(inout_values.buffer), op);
}

template<typename T, typename Op>
inline void
all_reduce(const communicator& comm, const T& in_value, T& out_value, Op op)
{
  detail::all_reduce_impl(comm, &in_value, 1, &out_value, op,
                          is_mpi_op<Op, T>(), is_mpi_datatype<T>());
}

template<typename T, typename Op>
T all_reduce(const communicator& comm, const T& in_value, Op op)
{
  T result;
  ::boost::mpi::all_reduce(comm, in_value, result, op);
  return result;
}

} } // end namespace boost::mpi

#endif // BOOST_MPI_ALL_REDUCE_HPP

/* all_reduce.hpp
XSx/xxSH8hGX/Cc05RrHHA81biYpUWxHuMv1p/fvtL7xLJhSjKUddeOt0YJwB/VvnGzlh1mTO+YH0f+/SPyAC9/PiyR6h6Zz/mAlYl6U9BYQpL1ru2FxOTWUyBLjsnUStk6yu4Xd3vZOvHA0winq0rBb+f9hhGysnNjpfFPl51H5xsGdlDe+gOVSsPzHKXJlh3P883SSx9ZbG/pgy2zXgv3QnwOdhyaKae64a/tqxzVS+ayeXCAj4a3f1mXJpe+/SG3/bDIT88SaplhgCgDuxkg1lheCzynmZ/sIOsquMrY/Qf6xuaTs04oQW+CJKwi6u/ZLWE1DDzD0oAV6kKCL/dom9quf7FdqooCbIKR08HHiENcg+HS+3zXqNNQnmrU+obcQgtABWtT5KxrUNS0cfW7MmKQV//kRtfOFEYnEznHYpEX/lvFHPyrdBVRshmXbty18ANerq3Hu8p0iRK8gmEMkZjlisRV3H3DYDAzXkG2gZtqxbDPrYzsPjlZmcfOnpkxyfKw7OjBSSO2Ev4ctPsMy+eEJsrSOSglLD8T8Nn8Gja14odK2Zw+lL+BQevv5B9ClFWaDIpMtmD2t7B/BrOm3tvh5Zi5ryDtxdyFzt83dwrwPwyqFg1Q4yIV5lasdwRNJ+LqgMQe7Xmhh60JyyyQq1dTuSa3gC0VcIOZOnEhrqAdg0bThdGSnYKw7k1FmUpCC8Q/nJEgz3qMsVF2v4t/HyXhnC0mDXYt3f/NUy3hdYoH8LYY8a5wlsv4M63gp5aKPNar8od4sDAclBihx08sqTId1o+xDkpT28z+Mb/KtOldkSSCzGcIXMLe5TlNb2r/7ksUTxIcoYBXi+AASALg3C1jDXOaK3ahEbtYncUbK/bfGNVNpPUb6DgnXAlwLib/DJP7rWJkSJ1k26duIpnhiQjYAA2C24B0+YgK0Zrhc+g64j0w3a/249tqxTHLa32/h3RWjpAeuo5eerWjVQtseLeau7guIDXulup1kvV3uG1roInu10qZXK+2z12aa0Zw3054uHvNcI64SAyQjRn/ItUzXj7XeuVMRcbN60czytRnlK5pjcTiyaJzhFcmMZY+G04Gw5u6FYgYx2i+7k0BtugbY8rBPti58TH6Ml2l//F9OQgJ7atJsmwfdatvcbUo+vsWNdxaN58ik++Gs5DtCW+k040hzrPsad0I55oBvsbMeYKOvjC5woR34maTAb3VjQ8bSfgj2agaLHJIDeLFmL3cj3SwqjYeIWzjFugU+OzGcsljwmiXpBsBZWdaSJ0gUt1EHJXV6PzTKjFYOeKYFMxir8n+mw2bqw++dbPeHsxohrL6NA130acJribKFHMFB2yBz4hIOcrBMb46cRuXe8/BuH2/G32oHNoiqjR6sgeGBVBYygAf71ltctQEqt4aBUYjIidMPqw/CvK/it5OT/dPrLY5pWCI5OutoxYIb6us2lN2IvDsA3ZXm5Q8FNJ1fOlbfQ/E4VS+EHUNyApDXtICuCXmdvD4FFEm0GEvxFSkAaSOUBlgUpxUbpncd5oR3mMoTFDJuIKoHxHnsSUyywgBnX5W0daoFSh8i9KZYd3Lzb4z55XoK7gVMtCANFjjaMSBsjzSJ8Iz9Q6hJgXvdVCKIdLzVpcamQN0/Z15z8copn8R58Qk+Jn/nTaL1kEK42M4r6CfmHameO8bQT1n2RhJ3fZ8TK41FPNRDslz5rskelB04YS/iBfA8ghftqTacR4Ij4eZxtOWYGI7HoBblGAtO5t8FeCAKfp+ifvuNu9sP4DexoNv4KM3rARqhT00j8cf8YWrn/piBIzr2x9RMccw3DoyS/cIvjNMldP4vMN/oOVMwcPBvGN+BMsk=
*/