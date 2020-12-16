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
0fHqzWVQXtKbW0W5pSd3hDIfzUW+RuvrzZmUSTRXRrmyF1dPeQnq303je3Em5breXDFjtINxH66Fcn0fjn+djlsfroByYx+umnJLH64JTF8vit5D0/XmkvbQdL25BXtout7cdiZHPW9QOfrzBpX34vLeoPl7c7WMe3FNlElvbsBeOg/Q65T5vtwKyrF9ue2UU/BK0j7af6xfyvVdOJOy75ONDVD2IP5+UwjhloDvQ3gPeDX4BDgXPGB5eNR8xMeBpyGcAp5O84GngheDi8CrwDzSbQSL4F3gJPAhcD7iW8CXINzxIdyDIRwNLgPz4FvBaeDbwHngm5CugqYLQfngDHA1OBO8HTwH6ZrAlQifAt+BcPgKhGm54Dtpu8F3gRPAd9N2g+9B+gLwveBK8K8gXwaeD64Fz4J8P/jXCB8B/4agfPBCWu7D4VGfgFXwYloe+EakLwbfQ8cB7KHtfBjlE/QbvISOI/gp2s+VCCM+AyzR8QYfgHwLuJbWA36GtvsR+js70oE3gheAt9B04JdoOnA9WIL930PQH/Ab4DrwXhoP3kfrg92/HzwZvBS8AvwAbRe4D+qPXI1+gRPAyyCfB34QfBicDDkHuy+DU8B2COLBM8EN4PvAMbD/WeAk8HJaPvghOm7g/QTlw+7vBMeBV9DywQ+D68EP0nkD3x+CdsLur4S8GPwIuAq8irYTPAfxBPa+nKYDp4WgP+A8Wh84ms4XeBz4LPgWOi6w+4fouIDvpPMBXhqCfoHn0XbD/ufQcsAJIagPHA8+Cn6M5n8S44FwGbgK4Rpwd4SbwL9FuCPs/hPgWPDtdB2Ba2i/wE+Dm8FrwTGw+1MRPwG8jrYX7KX7AVxH1xPs/nqCePDzdB2CN9F5Br9A0B/wVroeYP9H0XLALxLUBx4ZgvrA2xEetA7rmK4r8Mt0vYBfoe0Bj6XjDI4LQb9g/3dAXgGuoPsUnEvjwYdpPc9gfdBxAb9K5wG8i2B8wa/R+YT9n0DbAd5NkB/8Kd3X4K4hyA+7/zpdt+Bf03EHLwA3gpfTfQ87/yZdl+CP6LoEN9J9A/6Ylgd+m64/sIr04bD7v0fYBA9EuAI8hpYLTqHlgm8AXwq7/y7SJYHH03kDT6TjDG6APAb2vwfCeeCe4DrwQ3S9gPOoXoP9P0LXHzgf4VrwtBD0Czw9BPXD/hfQeQY7VP+AY2l+8CAaD/vfPRzx4LNhiAf3RLgZzIEHwf73As8Btw9HP8FRNB7cGxwD+98NPAF8HPlXgHsg3AguJ+jfVqwz2j9wE91H4D9SPQ3+DExg98toP8BzES4DL6D6DDyYrmvwEDo/L6Ieuk7AK+g4gq+j4wg+SMcJdr8P6s0G9w1HPPj7MMwH+GcIR8Pu9wfHgW3an5eQH7wLrIIjYfeTwGngIeB54HPIvx8cjXBH2P1hYB48CVwAngiuA99I4+uxvug4gMeDl4BnUH0DLqT6CPa/CJwNfpSuT/DDdF+Cddo/2P+v6DyCjxO0C/wNOAp2/wS1L+BvCcoFc7Rc8Em6n2H3v6P7GXyK7i/wX2h+8F10f4AXEZQP+19Mxw98mtYPPkMwvuCzNH43+kv3M/gHuq7BqSEoBxxC1z/svkH1JTgUvAAcBt4DTqTrCXwL1XOw/0/SeQQvRrgGfAftJ7gdXe+w+7PpPgR3pHYE3ImWAy6heh12P4KuB3DnEMwTOJKue3AXqgf3Xny7+OLn//NzRT8SdSH8jbT/8F7Bng8j/+pn/L+Rt207zp091dJYX/lDSFiHS/o5d1DZ+j6vxCV/Fvui/3ew8hVIh0/rb2MXP3/rM3tTO7IQWAlsAHYCHwKngejNeF8QiAUmAcXAfKAK2A4cBD4=
*/