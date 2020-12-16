// Copyright 2004 The Trustees of Indiana University.

// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  Authors: Douglas Gregor
//           Andrew Lumsdaine
#ifndef BOOST_PARALLEL_ALGORITHM_HPP
#define BOOST_PARALLEL_ALGORITHM_HPP

#ifndef BOOST_GRAPH_USE_MPI
#error "Parallel BGL files should not be included unless <boost/graph/use_mpi.hpp> has been included"
#endif

#include <boost/optional.hpp>
#include <boost/config.hpp> // for BOOST_STATIC_CONSTANT
#include <vector>
#include <functional>

namespace boost { namespace parallel {
  template<typename BinaryOp>
  struct is_commutative
  {
    BOOST_STATIC_CONSTANT(bool, value = false);
  };

  template<typename T>
  struct minimum : std::binary_function<T, T, T>
  {
    const T& operator()(const T& x, const T& y) const { return x < y? x : y; }
  };

  template<typename T>
  struct maximum : std::binary_function<T, T, T>
  {
    const T& operator()(const T& x, const T& y) const { return x < y? y : x; }
  };

  template<typename T>
  struct sum : std::binary_function<T, T, T>
  {
    const T operator()(const T& x, const T& y) const { return x + y; }
  };

  template<typename ProcessGroup, typename InputIterator,
           typename OutputIterator, typename BinaryOperation>
  OutputIterator
  reduce(ProcessGroup pg, typename ProcessGroup::process_id_type root,
         InputIterator first, InputIterator last, OutputIterator out,
         BinaryOperation bin_op);

  template<typename ProcessGroup, typename T, typename BinaryOperation>
  inline T
  all_reduce(ProcessGroup pg, const T& value, BinaryOperation bin_op)
  {
    T result;
    all_reduce(pg,
               const_cast<T*>(&value), const_cast<T*>(&value+1),
               &result, bin_op);
    return result;
  }

  template<typename ProcessGroup, typename T, typename BinaryOperation>
  inline T
  scan(ProcessGroup pg, const T& value, BinaryOperation bin_op)
  {
    T result;
    scan(pg,
         const_cast<T*>(&value), const_cast<T*>(&value+1),
         &result, bin_op);
    return result;
  }


  template<typename ProcessGroup, typename InputIterator, typename T>
  void
  all_gather(ProcessGroup pg, InputIterator first, InputIterator last,
             std::vector<T>& out);
} } // end namespace boost::parallel

#include <boost/graph/parallel/detail/inplace_all_to_all.hpp>

#endif // BOOST_PARALLEL_ALGORITHM_HPP

/* algorithm.hpp
/NTRBfb1sUfO87gzHquPZ1vluT4GWjKvmXC3StwfR/TR9NC5xbOK8u15onulPMuF5gzj3y5hnrfDcN+eNCZoq1iZ+9AaKe/RXDEdrPD1lpknfbS1kD5a+lLi2iVxPS1xPZMm1/jI3Lzi4qm6Ly1CR9vU549z0M1OU/Y9/VvJ21OUVS2rE/etMY7ekjf55itxz8nx2nt2m3D7JC1daZcORm1nqA6wkq7TX4ZJW0lKUg0Icch5Kf1cunueJ0W3pXrDg8cvJGyz0s8Vun2tEx2X6cs90pcXqSG6n94j57/Sv4En8FswivEX3JOMTD7FBVwJqgNuAm4prp07SbWJCzBeTFIFjG2zMHDXF3ctrrk3QQ3yVlE/Jrm5Kojb9MPd6HFrsb/6QauhKzOu0LvamuqrpO73PehaSg09EZhPP9KRX6G/pRKmUnKcOoUt0VOqjqONr7DMCpWCTlmtU2tWqMwyIvZmbzMVGalPVU9Y6NJH6H1l5PqtLbJJWtZoplxfEmeBlj0t5eBRWcgKtewRkbVKra5OJDUs87KrtqRTDurr/8NEnzo7YXBCRbWc/f/3JpS3TnkL1aLEHpK2slG6qeXrq+PlakuaI+U5jC9+TjjlfY17e3Jc2bR4NS1toMpPf9xVSdIsuroslwdcWDJs7mhVpnJgGuVMWvXxg5LWg6mrFPdZa4z61PrEOui83DXZsz9upP9BR53UrtIGPkoPtW0V0Xa/OM14NLwW4we5D/WzejHuu1SPQdsMkbn62WWwOtjFkW1NcW7BHssd6qR7pJoY97WaGL9bdfC8p+olNFITE5ooZ1JVVS/pdnUw6bD1ZnI95fdfy9781dXH/vqqOjtXvRKorlwps52L0xs7PipbyekvP1UtKP+2s6BymkrKZi0/rjFOrouIe5RL3VrmLIzshu9NZSR9zLoP3VdCYx3FN0hpAwsi+lOsxctAwx5nnBCdK3P6YBBmAdfZ/czBnoIxl8H0+5s8bsYrPp4lN2ZOyfGoiHUEpgy7y7V6rcV1TE96gTXfcuu90OU7sbTNeVjv3WrZ+8XMkXSWc6zg/lcm6tkwVdUQHcu0keC9O9xGzkxdYdVNr6RGpu9w2WO/UeNCvaXd3+6Xet3u9GBtt42VZY1wDDB9oFf6hc30LE2lnCoE73XST91YRcepy8keTzbRY8IPQ3nnZmnfJ98eIfkv9zT9yGvqocwluly7Sltpne3GsubZjhrWOOdjqqbrffWVu0CNjDuuRsbvVS08H6pqCWepkQmfWL0Tq6oZuNsS66q98HtcZd8G9arvF/Va0tfWy8lNVbz/FnWX/0z2PGipKgTWqWcDZ6qfAvsdc9Mvc8eXn6AuLf+BM7/yCuXK5rko+IyenaTvffp+Sw2mkOd99jVY/mtmaek9AXS+c5lfa69JqjwltHait3W9pffy12Ote9JcaqHretdQb2ryFtf3qQmqbNpVUqYjCOeVMp2VE/FsWTQxb1SuGSvo59tuUlfVrCwsPpcRGTOT5T6dJHEF9xNtJ3F11ONQPV4uml6cO9oer95NXOtF790qkc98U/SYpiwsI2PJs9y38Qz1E0bGc0Qe2dYaxEU+RwXbWSXi9hH3Jon7QJUuyWVVQXKimp/scdweSPMHrwnsuvGXb8Yoz42w01+L9B+Ua+yuHP3+wjxnK92+/ISRNPv1u42IZ/c86YfKOF9V1zBSjtfPSPZ40X5GqppcPaumnPMY4dIkvYURz9NsUafj7cvxjWPlumeElqi6yl4oyE28ezw+tdkjYxTSX1XiGkH567js9y9SnSm6zcdPl7nwrg7MSKx02meSWsn6WUSPH/VYSmKx29y7Y0JjxWqktvT9nbVNpGmgpKk=
*/