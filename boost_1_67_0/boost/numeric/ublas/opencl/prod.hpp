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
+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
*/