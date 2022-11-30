// Boost.uBLAS
//
// Copyright (c) 2018 Fady Essam
// Copyright (c) 2018 Stefan Seefeld
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or
// copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef boost_numeric_ublas_opencl_elementwise_hpp_
#define boost_numeric_ublas_opencl_elementwise_hpp_

#include <boost/numeric/ublas/opencl/library.hpp>
#include <boost/numeric/ublas/opencl/vector.hpp>
#include <boost/numeric/ublas/opencl/matrix.hpp>

namespace boost { namespace numeric { namespace ublas { namespace opencl {

namespace compute = boost::compute;
namespace lambda = boost::compute::lambda;

template <typename T, typename L1, typename L2, typename L3, class O>
void element_wise(ublas::matrix<T, L1, opencl::storage> const &a,
		  ublas::matrix<T, L2, opencl::storage> const &b,
		  ublas::matrix<T, L3, opencl::storage> &result,
		  O op, compute::command_queue& queue)
{
  assert(a.device() == b.device() &&
	 a.device() == result.device() &&
	 a.device() == queue.get_device());
  assert(a.size1() == b.size1() && a.size2() == b.size2());

  compute::transform(a.begin(),
		     a.end(),
		     b.begin(),
		     result.begin(),
		     op,
		     queue);
  queue.finish();
}

template <typename T, typename L1, typename L2, typename L3, typename A, class O>
void element_wise(ublas::matrix<T, L1, A> const &a,
		  ublas::matrix<T, L2, A> const &b,
		  ublas::matrix<T, L3, A> &result,
		  O op,
		  compute::command_queue &queue)
{
  ublas::matrix<T, L1, opencl::storage> adev(a, queue);
  ublas::matrix<T, L2, opencl::storage> bdev(b, queue);
  ublas::matrix<T, L3, opencl::storage> rdev(a.size1(), b.size2(), queue.get_context());
  element_wise(adev, bdev, rdev, op, queue);
  rdev.to_host(result, queue);
}

template <typename T, typename L1, typename L2, typename A, typename O>
ublas::matrix<T, L1, A> element_wise(ublas::matrix<T, L1, A> const &a,
				     ublas::matrix<T, L2, A> const &b,
				     O op,
				     compute::command_queue &queue)
{
  ublas::matrix<T, L1, A> result(a.size1(), b.size2());
  element_wise(a, b, result, op, queue);
  return result;
}

template <typename T, typename O>
void element_wise(ublas::vector<T, opencl::storage> const &a,
		  ublas::vector<T, opencl::storage> const &b,
		  ublas::vector<T, opencl::storage> &result,
		  O op,
		  compute::command_queue& queue)
{
  assert(a.device() == b.device() &&
	 a.device() == result.device() &&
	 a.device() == queue.get_device());
  assert(a.size() == b.size());
  compute::transform(a.begin(),
		     a.end(),
		     b.begin(),
		     result.begin(),
		     op,
		     queue);
  queue.finish();
}

template <typename T, typename A, typename O>
void element_wise(ublas::vector<T, A> const &a,
		  ublas::vector<T, A> const &b,
		  ublas::vector<T, A>& result,
		  O op,
		  compute::command_queue &queue)
{
  ublas::vector<T, opencl::storage> adev(a, queue);
  ublas::vector<T, opencl::storage> bdev(b, queue);
  ublas::vector<T, opencl::storage> rdev(a.size(), queue.get_context());
  element_wise(adev, bdev, rdev, op, queue);
  rdev.to_host(result, queue);
}

template <typename T, typename A, typename O>
ublas::vector<T, A> element_wise(ublas::vector<T, A> const &a,
				 ublas::vector<T, A> const &b,
				 O op,
				 compute::command_queue &queue)
{
  ublas::vector<T, A> result(a.size());
  element_wise(a, b, result, op, queue);
  return result;
}

template <typename T, typename L1, typename L2, typename L3>
void element_add(ublas::matrix<T, L1, opencl::storage> const &a,
		 ublas::matrix<T, L2, opencl::storage> const &b,
		 ublas::matrix<T, L3, opencl::storage> &result,
		 compute::command_queue &queue)
{
  element_wise(a, b, result, compute::plus<T>(), queue);
}

template <typename T, typename L1, typename L2, typename L3, typename A>
void element_add(ublas::matrix<T, L1, A> const &a,
		 ublas::matrix<T, L2, A> const &b,
		 ublas::matrix<T, L3, A> &result,
		 compute::command_queue &queue)
{
  element_wise(a, b, result, compute::plus<T>(), queue);
}

template <typename T, typename L1, typename L2, typename A>
ublas::matrix<T, L1, A> element_add(ublas::matrix<T, L1, A> const &a,
				    ublas::matrix<T, L2, A> const &b,
				    compute::command_queue &queue)
{
  return element_wise(a, b, compute::plus<T>(), queue);
}

template <typename T>
void element_add(ublas::vector<T, opencl::storage> const &a,
		 ublas::vector<T, opencl::storage> const &b,
		 ublas::vector<T, opencl::storage> &result,
		 compute::command_queue& queue)
{
  element_wise(a, b, result, compute::plus<T>(), queue);
}

template <typename T, typename A>
void element_add(ublas::vector<T, A> const &a,
		 ublas::vector<T, A> const &b,
		 ublas::vector<T, A> &result,
		 compute::command_queue &queue)
{
  element_wise(a, b, result, compute::plus<T>(), queue);
}

template <typename T, typename A>
ublas::vector<T, A> element_add(ublas::vector<T, A> const &a,
				ublas::vector<T, A> const &b,
				compute::command_queue &queue)
{
  return element_wise(a, b, compute::plus<T>(), queue);
}

template<typename T, typename L>
void element_add(ublas::matrix<T, L, opencl::storage> const &m, T value,
		 ublas::matrix<T, L, opencl::storage> &result,
		 compute::command_queue& queue)
{
  assert(m.device() == result.device() && m.device() == queue.get_device());
  assert(m.size1() == result.size1() && m.size2() == result.size2());
  compute::transform(m.begin(), m.end(), result.begin(), lambda::_1 + value, queue);
  queue.finish();
}

template<typename T, typename L, typename A>
void element_add(ublas::matrix<T, L, A> const &m, T value,
		 ublas::matrix<T, L, A> &result,
		 compute::command_queue& queue)
{
  ublas::matrix<T, L, opencl::storage> mdev(m, queue);
  ublas::matrix<T, L, opencl::storage> rdev(result.size1(), result.size2(), queue.get_context());
  element_add(mdev, value, rdev, queue);
  rdev.to_host(result, queue);
}

template<typename T, typename L, typename A>
ublas::matrix<T, L, A> element_add(ublas::matrix<T, L, A> const &m, T value,
				   compute::command_queue& queue)
{
  ublas::matrix<T, L, A> result(m.size1(), m.size2());
  element_add(m, value, result, queue);
  return result;
}

template<typename T>
void element_add(ublas::vector<T, opencl::storage> const &v, T value,
		 ublas::vector<T, opencl::storage> &result,
		 compute::command_queue& queue)
{
  assert(v.device() == result.device() && v.device() == queue.get_device());
  assert(v.size() == result.size());
  compute::transform(v.begin(), v.end(), result.begin(), lambda::_1 + value, queue);
  queue.finish();
}

template<typename T, typename A>
void element_add(ublas::vector<T, A> const &v, T value,
		 ublas::vector<T, A> &result,
		 compute::command_queue& queue)
{
  ublas::vector<T, opencl::storage> vdev(v, queue);
  ublas::vector<T, opencl::storage> rdev(v.size(), queue.get_context());
  element_add(vdev, value, rdev, queue);
  rdev.to_host(result, queue);
}

template <typename T, typename A>
ublas::vector<T, A> element_add(ublas::vector<T, A> const &v, T value,
				compute::command_queue& queue)
{
  ublas::vector<T, A> result(v.size());
  element_add(v, value, result, queue);
  return result;
}

template <typename T, typename L1, typename L2, typename L3>
void element_sub(ublas::matrix<T, L1, opencl::storage> const &a,
		 ublas::matrix<T, L2, opencl::storage> const &b,
		 ublas::matrix<T, L3, opencl::storage> &result,
		 compute::command_queue& queue)
{
  element_wise(a, b, compute::minus<T>(), result, queue);
}

template <typename T, typename L1, typename L2, typename L3, typename A>
void element_sub(ublas::matrix<T, L1, A> const &a,
		 ublas::matrix<T, L2, A> const &b,
		 ublas::matrix<T, L3, A> &result,
		 compute::command_queue &queue)
{
  element_wise(a, b, result, compute::minus<T>(), queue);
}

template <typename T, typename L1, typename L2, typename A>
ublas::matrix<T, L1, A> element_sub(ublas::matrix<T, L1, A> const &a,
				    ublas::matrix<T, L2, A> const &b,
				    compute::command_queue &queue)
{
  return element_wise(a, b, compute::minus<T>(), queue);
}

template <typename T>
void element_sub(ublas::vector<T, opencl::storage> const &a,
		 ublas::vector<T, opencl::storage> const &b,
		 ublas::vector<T, opencl::storage> &result,
		 compute::command_queue& queue)
{
  element_wise(a, b, result, compute::minus<T>(), queue);
}

template <typename T, typename A>
void element_sub(ublas::vector<T, A> const &a,
		 ublas::vector<T, A> const &b,
		 ublas::vector<T, A> &result,
		 compute::command_queue &queue)
{
  element_wise(a, b, result, compute::minus<T>(), queue);
}

template <typename T, typename A>
ublas::vector<T, A> element_sub(ublas::vector<T, A> const &a,
				ublas::vector<T, A> const &b,
				compute::command_queue &queue)
{
  return element_wise(a, b, compute::minus<T>(), queue);
}

template <typename T, typename L>
void element_sub(ublas::matrix<T, L, opencl::storage> const &m, T value,
		 ublas::matrix<T, L, opencl::storage> &result,
		 compute::command_queue& queue)
{
  assert(m.device() == result.device() && m.device() == queue.get_device());
  assert(m.size1() == result.size1() && m.size2() == result.size2());
  compute::transform(m.begin(), m.end(), result.begin(), lambda::_1 - value, queue);
  queue.finish();
}

template <typename T, typename L, typename A>
void element_sub(ublas::matrix<T, L, A> const &m, T value,
		 ublas::matrix<T, L, A> &result,
		 compute::command_queue& queue)
{
  ublas::matrix<T, L, opencl::storage> mdev(m, queue);
  ublas::matrix<T, L, opencl::storage> rdev(result.size1(), result.size2(), queue.get_context());
  element_sub(mdev, value, rdev, queue);
  rdev.to_host(result, queue);
}

template <typename T, typename L, typename A>
ublas::matrix<T, L, A> element_sub(ublas::matrix<T, L, A> const &m, T value,
				   compute::command_queue& queue)
{
  ublas::matrix<T, L, A> result(m.size1(), m.size2());
  element_sub(m, value, result, queue);
  return result;
}

template <typename T>
void element_sub(ublas::vector<T, opencl::storage> const &v, T value,
		 ublas::vector<T, opencl::storage> &result,
		 compute::command_queue& queue)
{
  assert(v.device() == result.device() && v.device() == queue.get_device());
  assert(v.size() == result.size());
  compute::transform(v.begin(), v.end(), result.begin(), lambda::_1 - value, queue);
  queue.finish();
}

template <typename T, typename A>
void element_sub(ublas::vector<T, A> const &v, T value,
		 ublas::vector<T, A> &result,
		 compute::command_queue& queue)
{
  ublas::vector<T, opencl::storage> vdev(v, queue);
  ublas::vector<T, opencl::storage> rdev(v.size(), queue.get_context());
  element_sub(vdev, value, rdev, queue);
  rdev.to_host(result, queue);
}

template <typename T, typename A>
ublas::vector<T, A> element_sub(ublas::vector<T, A> const &v, T value,
				compute::command_queue& queue)
{
  ublas::vector<T, A> result(v.size());
  element_sub(v, value, result, queue);
  return result;
}

template <typename T, typename L1, typename L2, typename L3>
void element_prod(ublas::matrix<T, L1, opencl::storage> const &a,
		  ublas::matrix<T, L2, opencl::storage> const &b,
		  ublas::matrix<T, L3, opencl::storage> &result,
		  compute::command_queue& queue)
{
  element_wise(a, b, result, compute::multiplies<T>(), queue);
}

template <typename T, typename L1, typename L2, typename L3, typename A>
void element_prod(ublas::matrix<T, L1, A> const &a,
		  ublas::matrix<T, L2, A> const &b,
		  ublas::matrix<T, L3, A> &result,
		  compute::command_queue &queue)
{
  element_wise(a, b, result, compute::multiplies<T>(), queue);
}

template <typename T, typename L1, typename L2, typename A>
ublas::matrix<T, L1, A> element_prod(ublas::matrix<T, L1, A> const &a,
				     ublas::matrix<T, L2, A> const &b,
				     compute::command_queue &queue)
{
  return element_wise(a, b, compute::multiplies<T>(), queue);
}

template <typename T>
void element_prod(ublas::vector<T, opencl::storage> const &a,
		  ublas::vector<T, opencl::storage> const &b,
		  ublas::vector<T, opencl::storage> &result,
		  compute::command_queue& queue)
{
  element_wise(a, b, result, compute::multiplies<T>(), queue);
}

template <typename T, typename A>
void element_prod(ublas::vector<T, A> const &a,
		  ublas::vector<T, A> const &b,
		  ublas::vector<T, A> &result,
		  compute::command_queue &queue)
{
  element_wise(a, b, result, compute::multiplies<T>(), queue);
}

template <typename T, typename A>
ublas::vector<T, A> element_prod(ublas::vector<T, A> const &a,
				 ublas::vector<T, A> const &b,
				 compute::command_queue &queue)
{
  return element_wise(a, b, compute::multiplies<T>(), queue);
}

template <typename T, typename L>
void element_scale(ublas::matrix<T, L, opencl::storage> const &m, T value,
		   ublas::matrix<T, L, opencl::storage> &result,
		   compute::command_queue& queue)
{
  assert(m.device() == result.device() && m.device() == queue.get_device());
  assert(m.size1() == result.size1() && m.size2() == result.size2());
  compute::transform(m.begin(), m.end(), result.begin(), lambda::_1 * value, queue);
  queue.finish();
}

template <typename T, typename L, typename A>
void element_scale(ublas::matrix<T, L, A> const &m, T value,
		   ublas::matrix<T, L, A> &result,
		   compute::command_queue& queue)
{
  ublas::matrix<T, L, opencl::storage> mdev(m, queue);
  ublas::matrix<T, L, opencl::storage> rdev(result.size1(), result.size2(), queue.get_context());
  element_scale(mdev, value, rdev, queue);
  rdev.to_host(result, queue);
}

template <typename T, typename L, typename A>
ublas::matrix<T, L, A>  element_scale(ublas::matrix<T, L, A> const &m, T value,
				      compute::command_queue& queue)
{
  ublas::matrix<T, L, A> result(m.size1(), m.size2());
  element_scale(m, value, result, queue);
  return result;
}

template <typename T>
void element_scale(ublas::vector<T, opencl::storage> const &v, T value,
		   ublas::vector<T, opencl::storage> &result,
		   compute::command_queue& queue)
{
  assert(v.device() == result.device() && v.device() == queue.get_device());
  assert(v.size() == result.size());
  compute::transform(v.begin(), v.end(), result.begin(), lambda::_1 * value, queue);
  queue.finish();
}

template <typename T, typename A>
void element_scale(ublas::vector<T, A> const &v, T value,
		   ublas::vector<T, A> & result,
		   compute::command_queue& queue)
{
  ublas::vector<T, opencl::storage> vdev(v, queue);
  ublas::vector<T, opencl::storage> rdev(v.size(), queue.get_context());
  element_scale(vdev, value, rdev, queue);
  rdev.to_host(result, queue);
}

template <typename T, typename A>
ublas::vector<T,A> element_scale(ublas::vector<T, A> const &v, T value,
				 compute::command_queue& queue)
{
  ublas::vector<T, A> result(v.size());
  element_scale(v, value, result, queue);
  return result;
}

template <typename T, typename L1, typename L2, typename L3>
void element_div(ublas::matrix<T, L1, opencl::storage> const &a,
		 ublas::matrix<T, L2, opencl::storage> const &b,
		 ublas::matrix<T, L3, opencl::storage> &result,
		 compute::command_queue& queue)
{
  element_wise(a, b, result, compute::divides<T>(), queue);
}

template <typename T, typename L1, typename L2, typename L3, typename A>
void element_div(ublas::matrix<T, L1, A> const &a,
		 ublas::matrix<T, L2, A> const &b,
		 ublas::matrix<T, L3, A> &result,
		 compute::command_queue &queue)
{
  element_wise(a, b, result, compute::divides<T>(), queue);
}

template <typename T, typename L1, typename L2, typename A>
ublas::matrix<T, L1, A> element_div(ublas::matrix<T, L1, A> const &a,
				    ublas::matrix<T, L2, A> const &b,
				    compute::command_queue &queue)
{
  return element_wise(a, b, compute::divides<T>(), queue);
}

template <typename T>
void element_div(ublas::vector<T, opencl::storage> const &a,
		 ublas::vector<T, opencl::storage> const &b,
		 ublas::vector<T, opencl::storage> &result,
		 compute::command_queue& queue)
{
  element_wise(a, b, result, compute::divides<T>(), queue);
}

template <typename T, typename A>
void element_div(ublas::vector<T, A> const &a,
		 ublas::vector<T, A> const &b,
		 ublas::vector<T, A> &result,
		 compute::command_queue &queue)
{
  element_wise(a, b, result, compute::divides<T>(), queue);
}

template <typename T, typename A>
ublas::vector<T, A> element_div(ublas::vector<T, A> const &a,
				ublas::vector<T, A> const &b,
				compute::command_queue &queue)
{
  return element_wise(a, b, compute::divides<T>(), queue);
}

}}}}

#endif 

/* elementwise.hpp
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
*/