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