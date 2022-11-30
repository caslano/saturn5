// Boost.uBLAS
//
// Copyright (c) 2018 Fady Essam
// Copyright (c) 2018 Stefan Seefeld
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or
// copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef boost_numeric_ublas_opencl_prod_hpp_
#define boost_numeric_ublas_opencl_prod_hpp_

#include <boost/numeric/ublas/opencl/library.hpp>
#include <boost/numeric/ublas/opencl/vector.hpp>
#include <boost/numeric/ublas/opencl/matrix.hpp>
#include <boost/numeric/ublas/opencl/transpose.hpp>
#include <boost/compute/buffer.hpp>

namespace boost { namespace numeric { namespace ublas { namespace opencl {

#define ONE_DOUBLE_COMPLEX  {{1.0, 00.0}}
#define ONE_FLOAT_COMPLEX  {{1.0f, 00.0f}}

template <typename T, typename L1, typename L2>
typename std::enable_if<is_numeric<T>::value>::type
prod(ublas::matrix<T, L1, opencl::storage> const &a,
     ublas::matrix<T, L2, opencl::storage> const &b,
     ublas::matrix<T, L1, opencl::storage> &result,
     compute::command_queue &queue)
{
  assert(a.device() == b.device() &&
	 a.device() == result.device() &&
	 a.device() == queue.get_device());
  assert(a.size2() == b.size1());

  result.fill(0, queue);

  //to hold matrix b with layout 1 if the b has different layout
  std::unique_ptr<ublas::matrix<T, L1, opencl::storage>> bl1;

  cl_event event = NULL;

  cl_mem buffer_a = a.begin().get_buffer().get();
  cl_mem buffer_b = b.begin().get_buffer().get();
  cl_mem buffer_result = result.begin().get_buffer().get();

  if (!(std::is_same<L1, L2>::value))
  {
    bl1.reset(new ublas::matrix<T, L1, opencl::storage>(b.size1(), b.size2(), queue.get_context()));
    change_layout(b, *bl1, queue);
    buffer_b = bl1->begin().get_buffer().get();
  }

  clblasOrder Order = std::is_same<L1, ublas::basic_row_major<> >::value ? clblasRowMajor : clblasColumnMajor;
  size_t lda = Order == clblasRowMajor ? a.size2() : a.size1();
  size_t ldb = Order == clblasRowMajor ? b.size2() : a.size2();
  size_t ldc = Order == clblasRowMajor ? b.size2() : a.size1();

  if (std::is_same<T, float>::value)
    clblasSgemm(Order, clblasNoTrans, clblasNoTrans,
		a.size1(), b.size2(), a.size2(),
		1, buffer_a, 0, lda,
		buffer_b, 0, ldb, 1,
		buffer_result, 0, ldc,
		1, &(queue.get()), 0, NULL, &event);
  else if (std::is_same<T, double>::value)
    clblasDgemm(Order, clblasNoTrans, clblasNoTrans,
		a.size1(), b.size2(), a.size2(),
		1, buffer_a, 0, lda,
		buffer_b, 0, ldb, 1,
		buffer_result, 0, ldc,
		1, &(queue.get()), 0, NULL, &event);
  else if (std::is_same<T, std::complex<float>>::value)
    clblasCgemm(Order, clblasNoTrans, clblasNoTrans,
		a.size1(), b.size2(), a.size2(),
		ONE_FLOAT_COMPLEX, buffer_a, 0, lda,
		buffer_b, 0, ldb, ONE_FLOAT_COMPLEX,
		buffer_result, 0, ldc,
		1, &(queue.get()), 0, NULL, &event);
  else if (std::is_same<T, std::complex<double>>::value)
    clblasZgemm(Order, clblasNoTrans, clblasNoTrans,
		a.size1(), b.size2(), a.size2(),
		ONE_DOUBLE_COMPLEX, buffer_a, 0, lda,
		buffer_b, 0, ldb, ONE_DOUBLE_COMPLEX,
		buffer_result, 0, ldc,
		1, &(queue.get()), 0, NULL, &event);
  clWaitForEvents(1, &event);
}

template <typename T, typename L1, typename L2, typename A>
typename std::enable_if<is_numeric<T>::value>::type
prod(ublas::matrix<T, L1, A> const &a,
     ublas::matrix<T, L2, A> const &b,
     ublas::matrix<T, L1, A> &result,
     compute::command_queue &queue)
{
  ublas::matrix<T, L1, opencl::storage> adev(a, queue);
  ublas::matrix<T, L2, opencl::storage> bdev(b, queue);
  ublas::matrix<T, L1, opencl::storage> rdev(a.size1(), b.size2(), queue.get_context());
  prod(adev, bdev, rdev, queue);
  rdev.to_host(result,queue);
}

template <typename T, typename L1, typename L2, typename A>
typename std::enable_if<is_numeric<T>::value, ublas::matrix<T, L1, A>>::type
prod(ublas::matrix<T, L1, A> const &a,
     ublas::matrix<T, L2, A> const &b,
     compute::command_queue &queue)
{
  ublas::matrix<T, L1, A> result(a.size1(), b.size2());
  prod(a, b, result, queue);
  return result;
}

template <typename T, typename L>
typename std::enable_if<is_numeric<T>::value>::type
prod(ublas::matrix<T, L, opencl::storage> const &a,
     ublas::vector<T, opencl::storage> const &b,
     ublas::vector<T, opencl::storage> &result,
     compute::command_queue &queue)
{
  assert(a.device() == b.device() &&
	 a.device() == result.device() &&
	 a.device() == queue.get_device());
  assert(a.size2() == b.size());
  result.fill(0, queue);

  cl_event event = NULL;
  clblasOrder Order = std::is_same<L, ublas::basic_row_major<> >::value ? clblasRowMajor : clblasColumnMajor;
  int lda = Order == clblasRowMajor ? a.size2() : a.size1();
  int ldb = Order == clblasRowMajor ? 1 : a.size2();
  int ldc = Order == clblasRowMajor ? 1 : a.size1();

  if (std::is_same<T, float>::value)
    clblasSgemm(Order, clblasNoTrans, clblasNoTrans,
		a.size1(), 1, a.size2(),
		1, a.begin().get_buffer().get(), 0, lda,
		b.begin().get_buffer().get(), 0, ldb, 1,
		result.begin().get_buffer().get(), 0, ldc,
		1, &(queue.get()), 0, NULL, &event);
  else if (std::is_same<T, double>::value)
    clblasDgemm(Order, clblasNoTrans, clblasNoTrans,
		a.size1(), 1, a.size2(),
		1, a.begin().get_buffer().get(), 0, lda,
		b.begin().get_buffer().get(), 0, ldb, 1,
		result.begin().get_buffer().get(), 0, ldc,
		1, &(queue.get()), 0, NULL, &event);
  else if (std::is_same<T, std::complex<float>>::value)
    clblasCgemm(Order, clblasNoTrans, clblasNoTrans,
		a.size1(), 1, a.size2(),
		ONE_FLOAT_COMPLEX, a.begin().get_buffer().get(), 0, lda,
		b.begin().get_buffer().get(), 0, ldb, ONE_FLOAT_COMPLEX,
		result.begin().get_buffer().get(), 0, ldc,
		1, &(queue.get()), 0, NULL, &event);
  else if (std::is_same<T, std::complex<double>>::value)
    clblasZgemm(Order, clblasNoTrans, clblasNoTrans,
		a.size1(), 1, a.size2(),
		ONE_DOUBLE_COMPLEX, a.begin().get_buffer().get(), 0, lda,
		b.begin().get_buffer().get(), 0, ldb, ONE_DOUBLE_COMPLEX,
		result.begin().get_buffer().get(), 0, ldc,
		1, &(queue.get()), 0, NULL, &event);
  clWaitForEvents(1, &event);
}

template <typename T, typename L, typename A>
typename std::enable_if<is_numeric<T>::value>::type
prod(ublas::matrix<T, L, A> const &a,
     ublas::vector<T, A> const &b,
     ublas::vector<T, A> &result,
     compute::command_queue &queue)
{
  ublas::matrix<T, L, opencl::storage> adev(a, queue);
  ublas::vector<T, opencl::storage> bdev(b, queue);
  ublas::vector<T, opencl::storage> rdev(a.size1(), queue.get_context());
  prod(adev, bdev, rdev, queue);
  rdev.to_host(result, queue);
}

template <typename T, typename L, typename A>
typename std::enable_if<is_numeric<T>::value, ublas::vector<T, A>>::type
prod(ublas::matrix<T, L, A> const &a,
     ublas::vector<T, A> const &b,
     compute::command_queue &queue)
{
  ublas::vector<T, A> result(a.size1());
  prod(a, b, result, queue);
  return result;
}

template <typename T, typename L>
typename std::enable_if<is_numeric<T>::value>::type
prod(ublas::vector<T, opencl::storage> const &a,
     ublas::matrix<T, L, opencl::storage> const &b,
     ublas::vector<T, opencl::storage> &result,
     compute::command_queue &queue)
{
  assert(a.device() == b.device() &&
	 a.device() == result.device() &&
	 a.device() == queue.get_device());
  assert(a.size() == b.size1());
  result.fill(0, queue);
  cl_event event = NULL;
  clblasOrder Order = std::is_same<L, ublas::basic_row_major<> >::value ? clblasRowMajor : clblasColumnMajor;
  size_t lda = Order == clblasRowMajor ? a.size() : 1;
  size_t ldb = Order == clblasRowMajor ? b.size2() : a.size();
  size_t ldc = Order == clblasRowMajor ? b.size2() : 1;

  if (std::is_same<T, float>::value)
    clblasSgemm(Order, clblasNoTrans, clblasNoTrans,
		1, b.size2(), a.size(),
		1, a.begin().get_buffer().get(), 0, lda,
		b.begin().get_buffer().get(), 0, ldb, 1,
		result.begin().get_buffer().get(), 0, ldc,
		1, &(queue.get()), 0, NULL, &event);
  else if (std::is_same<T, double>::value)
    clblasDgemm(Order, clblasNoTrans, clblasNoTrans,
		1, b.size2(), a.size(),
		1, a.begin().get_buffer().get(), 0, lda,
		b.begin().get_buffer().get(), 0, ldb, 1,
		result.begin().get_buffer().get(), 0, ldc,
		1, &(queue.get()), 0, NULL, &event);
  else if (std::is_same<T, std::complex<float>>::value)
    clblasCgemm(Order, clblasNoTrans, clblasNoTrans,
		1, b.size2(), a.size(),
		ONE_FLOAT_COMPLEX, a.begin().get_buffer().get(), 0, lda,
		b.begin().get_buffer().get(), 0, ldb, ONE_FLOAT_COMPLEX,
		result.begin().get_buffer().get(), 0, ldc,
		1, &(queue.get()), 0, NULL, &event);
  else if (std::is_same<T, std::complex<double>>::value)
    clblasZgemm(Order, clblasNoTrans, clblasNoTrans,
		1, b.size2(), a.size(),
		ONE_DOUBLE_COMPLEX, a.begin().get_buffer().get(), 0, lda,
		b.begin().get_buffer().get(), 0, ldb, ONE_DOUBLE_COMPLEX,
		result.begin().get_buffer().get(), 0, ldc,
		1, &(queue.get()), 0, NULL, &event);
  clWaitForEvents(1, &event);
}

template <class T, class L, class A>
typename std::enable_if<is_numeric<T>::value>::type
prod(ublas::vector<T, A> const &a,
     ublas::matrix<T, L, A> const &b,
     ublas::vector<T, A> &result,
     compute::command_queue &queue)
{
  ublas::vector<T, opencl::storage> adev(a, queue);
  ublas::matrix<T, L, opencl::storage> bdev(b, queue);
  ublas::vector<T, opencl::storage> rdev(b.size2(), queue.get_context());
  prod(adev, bdev, rdev, queue);
  rdev.to_host(result, queue);
}

template <class T, class L, class A>
typename std::enable_if<is_numeric<T>::value, ublas::vector<T, A>>::type
prod(ublas::vector<T, A> const &a,
     ublas::matrix<T, L, A> const &b,
     compute::command_queue &queue)
{
  ublas::vector<T, A> result(b.size2());
  prod(a, b, result, queue);
  return result;
}

template<class T>
typename std::enable_if<std::is_fundamental<T>::value, T>::type
inner_prod(ublas::vector<T, opencl::storage> const &a,
	   ublas::vector<T, opencl::storage> const &b,
	   compute::command_queue &queue)
{
  assert(a.device() == b.device() && a.device() == queue.get_device());
  assert(a.size() == b.size());
  return compute::inner_product(a.begin(), a.end(), b.begin(), T(0), queue);
}

template<class T, class A>
typename std::enable_if<std::is_fundamental<T>::value, T>::type
inner_prod(ublas::vector<T, A> const &a,
	   ublas::vector<T, A> const &b,
	   compute::command_queue& queue)
{
  ublas::vector<T, opencl::storage> adev(a, queue);
  ublas::vector<T, opencl::storage> bdev(b, queue);
  return inner_prod(adev, bdev, queue);
}

template <class T, class L>
typename std::enable_if<is_numeric<T>::value>::type
outer_prod(ublas::vector<T, opencl::storage> const &a,
	   ublas::vector<T, opencl::storage> const &b,
	   ublas::matrix<T, L, opencl::storage> &result,
	   compute::command_queue & queue)
{
  assert(a.device() == b.device() &&
	 a.device() == result.device() &&
	 a.device() == queue.get_device());
  result.fill(0, queue);
  cl_event event = NULL;
  clblasOrder Order = std::is_same<L, ublas::basic_row_major<> >::value ? clblasRowMajor : clblasColumnMajor;
  size_t lda = Order == clblasRowMajor ? 1 : a.size();
  size_t ldb = Order == clblasRowMajor ? b.size() : 1;
  size_t ldc = Order == clblasRowMajor ? b.size() : a.size();

  if (std::is_same<T, float>::value)
    clblasSgemm(Order, clblasNoTrans, clblasNoTrans,
		a.size(), b.size(), 1,
		1, a.begin().get_buffer().get(), 0, lda,
		b.begin().get_buffer().get(), 0, ldb, 1,
		result.begin().get_buffer().get(), 0, ldc,
		1, &(queue.get()), 0, NULL, &event);
  else if (std::is_same<T, double>::value)
    clblasDgemm(Order, clblasNoTrans, clblasNoTrans,
		a.size(), b.size(), 1,
		1, a.begin().get_buffer().get(), 0, lda,
		b.begin().get_buffer().get(), 0, ldb, 1,
		result.begin().get_buffer().get(), 0, ldc,
		1, &(queue.get()), 0, NULL, &event);
  else if (std::is_same<T, std::complex<float>>::value)
    clblasCgemm(Order, clblasNoTrans, clblasNoTrans,
		a.size(), b.size(), 1,
		ONE_FLOAT_COMPLEX, a.begin().get_buffer().get(), 0, lda,
		b.begin().get_buffer().get(), 0, ldb, ONE_FLOAT_COMPLEX,
		result.begin().get_buffer().get(), 0, ldc,
		1, &(queue.get()), 0, NULL, &event);
  else if (std::is_same<T, std::complex<double>>::value)
    clblasZgemm(Order, clblasNoTrans, clblasNoTrans,
		a.size(), b.size(), 1,
		ONE_DOUBLE_COMPLEX, a.begin().get_buffer().get(), 0, lda,
		b.begin().get_buffer().get(), 0, ldb, ONE_DOUBLE_COMPLEX,
		result.begin().get_buffer().get(), 0, ldc,
		1, &(queue.get()), 0, NULL, &event);
  clWaitForEvents(1, &event);
}

template <class T, class L, class A>
typename std::enable_if<is_numeric<T>::value>::type
outer_prod(ublas::vector<T, A> const &a,
	   ublas::vector<T, A> const &b,
	   ublas::matrix<T, L, A> &result,
	   compute::command_queue &queue)
{
  ublas::vector<T, opencl::storage> adev(a, queue);
  ublas::vector<T, opencl::storage> bdev(b, queue);
  ublas::matrix<T, L, opencl::storage> rdev(a.size(), b.size(), queue.get_context());
  outer_prod(adev, bdev, rdev, queue);
  rdev.to_host(result, queue);
}

template <class T,class L = ublas::basic_row_major<>, class A>
typename std::enable_if<is_numeric<T>::value, ublas::matrix<T, L, A>>::type
outer_prod(ublas::vector<T, A> const &a,
	   ublas::vector<T, A> const &b,
	   compute::command_queue &queue)
{
  ublas::matrix<T, L, A> result(a.size(), b.size());
  outer_prod(a, b, result, queue);
  return result;
}

#undef ONE_DOUBLE_COMPLEX
#undef ONE_FLOAT_COMPLEX

}}}}

#endif 

/* prod.hpp
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
*/