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
OcDewkgZgpBfJh5vKRy0Iej9eEIf7URz+mXjI7M61mUZdpPe9r5wJlvWe4FbqykMdzJHbfob2EjLpItgzU04bIuaKIWUDue5h6/q3p9c03GXGnx9H+bGw9lJFoMG4aKAAPxUVmirrxS/1rrJjvB2p3W2zHbd6MuLQZRPdxrp8IaLBOJo/D8HEFNMJyWxZnbBKiFUwnDBo0J+IgWcz3Ft7xL7Xa61sksQa3wI9ldtJqhYBzO3PGotXKOHX8HmWrKZzDlQEaaiRcDqiGwxpKnb72E0xRR92RmIEcbOaJSgUxxcHVi2ycAhn6hAd3vvuSS+vQQ04MPIUTzp3ZXJ7sDqFlGvqZaat2KGkLGLdR0r7B1/PlFvkqo1dDJtKMB2eU2KDyDySv5xrAtigYqiaALsqmStsNZX/J0s5WGlcJ5ES+kw6M9yS3jIuBLrPjG3c+RAuyfYmX9RL3SePe7MFPSi5s3yK7vJmisGgy2oD7hNiaKO3EbDK8H62QA3zEPIYti5UKWFx0YtatsCTfQUFATzouQy1wjn1SJFn3BAwRwYagZaraXigyjD6QGatQ==
*/