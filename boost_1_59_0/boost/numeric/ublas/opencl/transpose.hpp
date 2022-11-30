// Boost.uBLAS
//
// Copyright (c) 2018 Fady Essam
// Copyright (c) 2018 Stefan Seefeld
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or
// copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef boost_numeric_ublas_opencl_transpose_hpp_
#define boost_numeric_ublas_opencl_transpose_hpp_

#include <boost/numeric/ublas/opencl/library.hpp>
#include <boost/numeric/ublas/opencl/vector.hpp>
#include <boost/numeric/ublas/opencl/matrix.hpp>

// Kernel for transposition of various data types
#define OPENCL_TRANSPOSITION_KERNEL(DATA_TYPE)	\
"__kernel void transpose(__global "  #DATA_TYPE "* in, __global " #DATA_TYPE "* result, unsigned int width, unsigned int height) \n"                       \
"{ \n"								        \
"  unsigned int column_index = get_global_id(0); \n"			\
"  unsigned int row_index = get_global_id(1); \n"			\
"  if (column_index < width && row_index < height) \n"			\
"  { \n"							      	\
"    unsigned int index_in = column_index + width * row_index; \n"	\
"    unsigned int index_result = row_index + height * column_index; \n"	\
"    result[index_result] = in[index_in]; \n"				\
"  } \n"								\
"} \n"


namespace boost { namespace numeric { namespace ublas { namespace opencl {

template<class T, class L1, class L2>
typename std::enable_if<is_numeric<T>::value>::type
change_layout(ublas::matrix<T, L1, opencl::storage> const &m,
	      ublas::matrix<T, L2, opencl::storage> &result,
	      compute::command_queue& queue)
{
  assert(m.size1() == result.size1() && m.size2() == result.size2());
  assert(m.device() == result.device() && m.device() == queue.get_device());
  assert(!(std::is_same<L1, L2>::value));
  char const *kernel;
  if (std::is_same<T, float>::value)
    kernel = OPENCL_TRANSPOSITION_KERNEL(float);
  else if (std::is_same<T, double>::value)
    kernel = OPENCL_TRANSPOSITION_KERNEL(double);
  else if (std::is_same<T, std::complex<float>>::value)
    kernel = OPENCL_TRANSPOSITION_KERNEL(float2);
  else if (std::is_same<T, std::complex<double>>::value)
    kernel = OPENCL_TRANSPOSITION_KERNEL(double2);
  size_t len = strlen(kernel);
  cl_int err;
  cl_context c_context = queue.get_context().get();
  cl_program program = clCreateProgramWithSource(c_context, 1, &kernel, &len, &err);
  clBuildProgram(program, 1, &queue.get_device().get(), NULL, NULL, NULL);
  cl_kernel c_kernel = clCreateKernel(program, "transpose", &err);
  size_t width = std::is_same < L1, ublas::basic_row_major<>>::value ? m.size2() : m.size1();
  size_t height = std::is_same < L1, ublas::basic_row_major<>>::value ? m.size1() : m.size2();
  size_t global_size[2] = { width , height };
  clSetKernelArg(c_kernel, 0, sizeof(T*), &m.begin().get_buffer().get());
  clSetKernelArg(c_kernel, 1, sizeof(T*), &result.begin().get_buffer().get());
  clSetKernelArg(c_kernel, 2, sizeof(unsigned int), &width);
  clSetKernelArg(c_kernel, 3, sizeof(unsigned int), &height);
  cl_command_queue c_queue = queue.get();
  cl_event event = NULL;
  clEnqueueNDRangeKernel(c_queue, c_kernel, 2, NULL, global_size, NULL, 0, NULL, &event);
  clWaitForEvents(1, &event);
}

template<class T, class L1, class L2, class A>
typename std::enable_if<is_numeric<T>::value>::type
change_layout(ublas::matrix<T, L1, A> const &m,
	      ublas::matrix<T, L2, A> &result,
	      compute::command_queue& queue)
{
  ublas::matrix<T, L1, opencl::storage> mdev(m, queue);
  ublas::matrix<T, L2, opencl::storage> rdev(result.size1(), result.size2(), queue.get_context());
  change_layout(mdev, rdev, queue);
  rdev.to_host(result, queue);
}

template<class T, class L>
typename std::enable_if<is_numeric<T>::value>::type
trans(ublas::matrix<T, L, opencl::storage> const &m,
      ublas::matrix<T, L, opencl::storage> &result,
      compute::command_queue& queue)
{
  assert(m.size1() == result.size2() && m.size2() == result.size1());
  assert(m.device() == result.device() && m.device() == queue.get_device());
  char const *kernel;
  if (std::is_same<T, float>::value)
    kernel = OPENCL_TRANSPOSITION_KERNEL(float);
  else if (std::is_same<T, double>::value)
    kernel = OPENCL_TRANSPOSITION_KERNEL(double);
  else if (std::is_same<T, std::complex<float>>::value)
    kernel = OPENCL_TRANSPOSITION_KERNEL(float2);
  else if (std::is_same<T, std::complex<double>>::value)
    kernel = OPENCL_TRANSPOSITION_KERNEL(double2);
  size_t len = strlen(kernel);
  cl_int err;
  cl_context c_context = queue.get_context().get();
  cl_program program = clCreateProgramWithSource(c_context, 1, &kernel, &len, &err);
  clBuildProgram(program, 1, &queue.get_device().get(), NULL, NULL, NULL);
  cl_kernel c_kernel = clCreateKernel(program, "transpose", &err);
  size_t width = std::is_same <L, ublas::basic_row_major<>>::value ? m.size2() : m.size1();
  size_t height = std::is_same <L, ublas::basic_row_major<>>::value ? m.size1() : m.size2();
  size_t global_size[2] = { width , height };
  clSetKernelArg(c_kernel, 0, sizeof(T*), &m.begin().get_buffer().get());
  clSetKernelArg(c_kernel, 1, sizeof(T*), &result.begin().get_buffer().get());
  clSetKernelArg(c_kernel, 2, sizeof(unsigned int), &width);
  clSetKernelArg(c_kernel, 3, sizeof(unsigned int), &height);
  cl_command_queue c_queue = queue.get();
  cl_event event = NULL;
  clEnqueueNDRangeKernel(c_queue, c_kernel, 2, NULL, global_size, NULL, 0, NULL, &event);
  clWaitForEvents(1, &event);
}

template<class T, class L, class A>
typename std::enable_if<is_numeric<T>::value>::type
trans(ublas::matrix<T, L, A> const &m,
      ublas::matrix<T, L, A> &result,
      compute::command_queue& queue)
{
  ublas::matrix<T, L, opencl::storage> mdev(m, queue);
  ublas::matrix<T, L, opencl::storage> rdev(result.size1(), result.size2(), queue.get_context());
  trans(mdev, rdev, queue);
  rdev.to_host(result, queue);
}

template<class T, class L, class A>
typename std::enable_if<is_numeric<T>::value, ublas::matrix<T, L, A>>::type
trans(ublas::matrix<T, L, A>& m, compute::command_queue& queue)
{
  ublas::matrix<T, L, A> result(m.size2(), m.size1());
  trans(m, result, queue);
  return result;
}

}}}}

#endif

/* transpose.hpp
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
*/