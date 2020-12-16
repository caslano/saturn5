// Boost.uBLAS
//
// Copyright (c) 2018 Fady Essam
// Copyright (c) 2018 Stefan Seefeld
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or
// copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef boost_numeric_ublas_opencl_matrix_hpp_
#define boost_numeric_ublas_opencl_matrix_hpp_

#include <boost/numeric/ublas/opencl/library.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/functional.hpp>
#include <boost/compute/core.hpp>
#include <boost/compute/algorithm.hpp>
#include <boost/compute/buffer.hpp>

namespace boost { namespace numeric { namespace ublas { namespace opencl {

class storage;

namespace compute = boost::compute;

} // namespace opencl
	
template<class T, class L>
class matrix<T, L, opencl::storage> : public matrix_container<matrix<T, L, opencl::storage> >
{
  typedef typename boost::compute::buffer_allocator<T>::size_type size_type;
  typedef L layout_type;
  typedef matrix<T, L, opencl::storage> self_type;
public:
  matrix()
    : matrix_container<self_type>(),
      size1_(0), size2_(0), data_() , device_()
  {}

  matrix(size_type size1, size_type size2, compute::context c)
    : matrix_container<self_type>(),
      size1_(size1), size2_(size2), device_(c.get_device())
  {
    compute::buffer_allocator<T> allocator(c);
    data_ = allocator.allocate(layout_type::storage_size(size1, size2)).get_buffer();
  }

  matrix(size_type size1, size_type size2, T const &value, compute::command_queue &q)
    : matrix_container<self_type>(),
      size1_(size1), size2_(size2), device_(q.get_device())
  {
    compute::buffer_allocator<T> allocator(q.get_context());
    data_ = allocator.allocate(layout_type::storage_size(size1, size2)).get_buffer();
    compute::fill(this->begin(), this->end(), value, q);
    q.finish();
  }

  template <typename A>
  matrix(matrix<T, L, A> const &m, compute::command_queue &queue)
    : matrix(m.size1(), m.size2(), queue.get_context())
  {
    this->from_host(m, queue);
  }
  
  size_type size1() const { return size1_;}
  size_type size2() const { return size2_;}

  const compute::buffer_iterator<T> begin() const { return compute::make_buffer_iterator<T>(data_);}
  compute::buffer_iterator<T> begin() { return compute::make_buffer_iterator<T>(data_);}

  compute::buffer_iterator<T> end() { return compute::make_buffer_iterator<T>(data_, layout_type::storage_size(size1_, size2_));}
  const compute::buffer_iterator<T> end() const { return compute::make_buffer_iterator<T>(data_, layout_type::storage_size(size1_, size2_));}

  const compute::device &device() const { return device_;}
  compute::device &device() { return device_;}

  void fill(T value, compute::command_queue &queue)
  {
    assert(device_ == queue.get_device());
    compute::fill(this->begin(), this->end(), value, queue);
    queue.finish();
  }

  /** Copies a matrix to a device
  * \param m is a matrix that is not on the device _device and it is copied to it
  * \param queue is the command queue that will execute the operation
  */
  template<class A>
  void from_host(ublas::matrix<T, L, A> const &m, compute::command_queue &queue)
  {
    assert(device_ == queue.get_device());
    compute::copy(m.data().begin(),
		  m.data().end(),
		  this->begin(),
		  queue);
    queue.finish();
  }

  /** Copies a matrix from a device
  * \param m is a matrix that will be reized to (size1_,size2) and the values of (*this) will be copied in it
  * \param queue is the command queue that will execute the operation
  */
  template<class A>
  void to_host(ublas::matrix<T, L, A> &m, compute::command_queue &queue) const
  {
    assert(device_ == queue.get_device());
    compute::copy(this->begin(),
		  this->end(),
		  m.data().begin(),
		  queue);
    queue.finish();
  }

private:
  size_type size1_;
  size_type size2_;
  compute::buffer data_;
  compute::device device_;
};

}}}

#endif

/* matrix.hpp
gR4E/RT0HGjQcJRD0JmgxaAE6HLQ+0FbQPeBvgb6Hmgf6A3Qm0YgbUH1IxCGEUg/0M2gu0BfGQFZ0JOgP4BeAx12BNIbdBJoBqgetBR0Kegy0A2gW0H3graDdoEeA70IGjwScQGdAjoTtBjUDLoStBF0B+gLoB+Cfgd6BTT8SIQRNB20ENQGeifoetDtoC8fCXnQb0EVo6rYGNAZoOWgd4CuGIX4gz4H+jroB6D9oJdBQ0dXsbGgs0CLQC2gd4E2gW4D3Q/aAfoZ6EXQYUdBHjQN1AC6BLQa9D7QraB7QF8HPQx6EvRn0MFHoy0BjQPVgpaDOkFXgT4I2gLaBtoF2gv6Legl0D9Aw8dUoX9C3EGzQeeBLgDFQGnQ9aA7xiDNQLtBT42Bn6DKY6rYMaBTQdNB80HLQJ2gK0E3gD4Gug+0C/RL0Ougg49F/EDzQe2gHtBVoFtB94EeBO0DVR6HsIFOB50PugiUBV0NuhF0N+gB0KOgZ0GDfJR10CzQW0GXgq4B3eJDL+gh0OM+4g76O+jw4xF+0JtBC0FvB+VBV4A+ALoL9ABoL+hPoENPgH7QWaC3gXKgG0C3gO4BbQc9ANoDegL0ImjQm6rYSNA40BzQW0FtoHeC1oM2g7aB+AZJBavEPl4V9ioHYX9yMBuCXc2h2FY/lB2GTb3DsZ8+nI3AgYqRYtsdw6mj2RhsAB/LjsN3749nJ7A3sRPZWHYSOxnflDuFvZmdysax8ew0djqbwCaySWwym8KmsjPYmWwam85msLPY2Vj5O4e9Bfuws9kcNpfVsjqcZT2XzWcL2HnsfFbPFrJFbDH2aN/KGlkTW4JTrhfgxOsytpy9jV3EVrCL2dtZjF3C4qyZtbAES7JW1oZ9pBS7lK1kHayTdbE0y2AHKsty2CfuZqvYatbD1rDL2DvZ5exd7N3sCuzRXsnew65i69jV7Bp2LVvPrmPvZdezDewG9j72fraR3cg+wD7INrGb2IfYh9nN7Bb2EfZRtpl9jH2c3cq2sNvY7ewOtpV9gn2SfYrdyT7N7mJ3s23sM+yz7B52L7uPfY59nt3PvsC+yL7EtrMvs6+wr7Kvsa+zb7BvYk/5W+wB9m22k32HfZc9yHaxh9j32MNsN/s++wH7IXuE/Yg9yn7M9rCfsMfY42wv+yn7Gfs528d+wX7JnmBPsl+xp9iv2X72G/Zb9jv2NPs9+wP7I3sGu9DPYaf5BfYie4n9ib3M/sz+wv7KXmF/Y6+yv7PX2OvsH+wN/nIQzk1U4vRElXeQN8ir9gZ7Q7yDvaHeId6h3mFe1DvcG+YN90Z4R3gjvSO9Ud5o7yjvaG+Md4x3rHec53vHeyd4b/JO9MZ6J3knezXeKd6bvVO9cd547zTvdG+CN9Gb5E32pnhTvTO8M71p3nRvhneWd7Y30zvHe4s3y5vtzfHmerVenTfPO9eb7y3wzvPO9+q9hd4ib7HX4L3Va/SavCXeUu8C70Jvmbfce5t3kbfCu9h7uxfzLvHiXrPX4iW8pNfqtXntXsq71FvpdXidXpeX9jLeO7ysl/PyXre3ylvt9XhrvMu8d3qXe+/y3u1d4a31rvTe413lrfOu9q7xrvXWe9d57/Wu9zZ4N3jv897vbfT0ynUCt/DNWbA41hqDnUx4UU9ep8dZ6nNw2skUs92FPbPGuOBI8fWdQXRoXm0Hizs7iWWa1a6uZtFnNyZJlM227eFoG2t+yUPYCt0sLTi/L64MpPuP6Mtzud7ftWioW0gXt5lf7gmY/KJC24FeHnBwbXm6Qine0RKbHaOT2eIuzAUN83HaLJHMtWRTdN+Lyeb3DRh2etM73o2rl7tSNh/e5XM2T7zfEiYt3u0=
*/