// Boost.uBLAS
//
// Copyright (c) 2018 Fady Essam
// Copyright (c) 2018 Stefan Seefeld
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or
// copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef boost_numeric_ublas_opencl_vector_hpp_
#define boost_numeric_ublas_opencl_vector_hpp_

#include <boost/numeric/ublas/opencl/library.hpp>
#include <boost/numeric/ublas/functional.hpp>
#include <boost/compute/core.hpp>
#include <boost/compute/algorithm.hpp>
#include <boost/compute/buffer.hpp>
#include <boost/compute/container/vector.hpp>

namespace boost { namespace numeric { namespace ublas { namespace opencl {

class storage;

namespace compute = boost::compute;

} // namespace opencl

template <class T>
class vector<T, opencl::storage> : public boost::compute::vector<T>
{
  typedef std::size_t size_type;
public:
  vector() : compute::vector<T>() {}
  vector(size_type size, compute::context context)
    : compute::vector<T>(size, context)
  { device_ = context.get_device();}
  vector(size_type size, T value, compute::command_queue queue)
    : compute::vector<T>(size, value, queue.get_context())
  {
    queue.finish();
    device_ = queue.get_device();
  }

  template <typename A>
  vector(vector<T, A> const &v, compute::command_queue &queue)
    : vector(v.size(), queue.get_context())
  {
    this->from_host(v, queue);
  }
  

  const compute::device device() const { return device_;}
  compute::device device() { return device_;}

  template<class A>
  void from_host(ublas::vector<T, A> const &v, compute::command_queue & queue)
  {
    assert(this->device() == queue.get_device());
    compute::copy(v.begin(),
		  v.end(),
		  this->begin(),
		  queue);
    queue.finish();
  }

  template<class A>
  void to_host(ublas::vector<T, A>& v, compute::command_queue& queue) const
  {
    assert(this->device() == queue.get_device());
    compute::copy(this->begin(),
		  this->end(),
		  v.begin(),
		  queue);
    queue.finish();
  }

  void fill(T value, compute::command_queue & queue)
  {
    assert(this->device() == queue.get_device());
    compute::fill(this->begin(), this->end(), value, queue);
    queue.finish();
  }

private:
  compute::device device_;
};

}}}

#endif

/* vector.hpp
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
*/