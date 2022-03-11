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