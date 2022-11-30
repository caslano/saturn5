// Boost.uBLAS
//
// Copyright (c) 2018 Fady Essam
// Copyright (c) 2018 Stefan Seefeld
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or
// copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef boost_numeric_ublas_opencl_misc_hpp_
#define boost_numeric_ublas_opencl_misc_hpp_

#include <boost/numeric/ublas/opencl/library.hpp>
#include <boost/numeric/ublas/opencl/vector.hpp>
#include <boost/numeric/ublas/opencl/matrix.hpp>

namespace boost { namespace numeric { namespace ublas { namespace opencl {

template <typename T>
typename std::enable_if<is_numeric<T>::value, T>::type
a_sum(ublas::vector<T, opencl::storage> const &v, compute::command_queue& queue)
{
  compute::vector<T> scratch_buffer(v.size(), queue.get_context());
  compute::vector<T> result_buffer(1, queue.get_context());
  cl_event event;
  if (std::is_same<T, float>::value)
    clblasSasum(v.size(),
		result_buffer.begin().get_buffer().get(), //result buffer
		0, //offset in result buffer
		v.begin().get_buffer().get(), //input buffer
		0, //offset in input buffer
		1, //increment in input buffer
		scratch_buffer.begin().get_buffer().get(),
		1, //number of command queues
		&(queue.get()), //queue
		0, // number of events waiting list
		NULL, //event waiting list
		&event); //event
  else if (std::is_same<T, double>::value)
    clblasDasum(v.size(),
		result_buffer.begin().get_buffer().get(), //result buffer
		0, //offset in result buffer
		v.begin().get_buffer().get(), //input buffer
		0, //offset in input buffer
		1, //increment in input buffer
		scratch_buffer.begin().get_buffer().get(),
		1, //number of command queues
		&(queue.get()), //queue
		0, // number of events waiting list
		NULL, //event waiting list
		&event); //event
  else if (std::is_same<T, std::complex<float>>::value)
    clblasScasum(v.size(),
		 result_buffer.begin().get_buffer().get(), //result buffer
		 0, //offset in result buffer
		 v.begin().get_buffer().get(), //input buffer
		 0, //offset in input buffer
		 1, //increment in input buffer
		 scratch_buffer.begin().get_buffer().get(),
		 1, //number of command queues
		 &(queue.get()), //queue
		 0, // number of events waiting list
		 NULL, //event waiting list
		 &event); //event
  else if (std::is_same<T, std::complex<double>>::value)
    clblasDzasum(v.size(),
		 result_buffer.begin().get_buffer().get(), //result buffer
		 0, //offset in result buffer
		 v.begin().get_buffer().get(), //input buffer
		 0, //offset in input buffer
		 1, //increment in input buffer
		 scratch_buffer.begin().get_buffer().get(),
		 1, //number of command queues
		 &(queue.get()), //queue
		 0, // number of events waiting list
		 NULL, //event waiting list
		 &event); //event
  clWaitForEvents(1, &event);
  return result_buffer[0];
}

template <typename T, typename A>
typename std::enable_if<is_numeric<T>::value, T>::type
a_sum(ublas::vector<T, A> const &v, compute::command_queue& queue)
{
  ublas::vector<T, opencl::storage> vdev(v, queue);
  return a_sum(vdev, queue);
}

template <typename T>
typename std::enable_if<std::is_same<T, float>::value |
			std::is_same<T, double>::value,
			T>::type
norm_1(ublas::vector<T, opencl::storage> const &v, compute::command_queue& queue)
{
  return a_sum(v, queue);
}

template <typename T, typename A>
typename std::enable_if<std::is_same<T, float>::value |
			std::is_same<T, double>::value,
			T>::type
norm_1(ublas::vector<T, A> const &v, compute::command_queue& queue)
{
  ublas::vector<T, opencl::storage> vdev(v, queue);
  return norm_1(vdev, queue);
}

template <typename T>
typename std::enable_if<is_numeric<T>::value, T>::type
norm_2(ublas::vector<T, opencl::storage> const &v, compute::command_queue& queue)
{
  compute::vector<T> scratch_buffer(2*v.size(), queue.get_context());
  compute::vector<T> result_buffer(1, queue.get_context());
  cl_event event;
  if (std::is_same<T, float>::value)
    clblasSnrm2(v.size(),
		result_buffer.begin().get_buffer().get(), //result buffer
		0, //offset in result buffer
		v.begin().get_buffer().get(), //input buffer
		0, //offset in input buffer
		1, //increment in input buffer
		scratch_buffer.begin().get_buffer().get(),
		1, //number of command queues
		&(queue.get()), //queue
		0, // number of events waiting list
		NULL, //event waiting list
		&event); //event
  else if (std::is_same<T, double>::value)
    clblasDnrm2(v.size(),
		result_buffer.begin().get_buffer().get(), //result buffer
		0, //offset in result buffer
		v.begin().get_buffer().get(), //input buffer
		0, //offset in input buffer
		1, //increment in input buffer
		scratch_buffer.begin().get_buffer().get(),
		1, //number of command queues
		&(queue.get()), //queue
		0, // number of events waiting list
		NULL, //event waiting list
		&event); //event
  else if (std::is_same<T, std::complex<float>>::value)
    clblasScnrm2(v.size(),
		 result_buffer.begin().get_buffer().get(), //result buffer
		 0, //offset in result buffer
		 v.begin().get_buffer().get(), //input buffer
		 0, //offset in input buffer
		 1, //increment in input buffer
		 scratch_buffer.begin().get_buffer().get(),
		 1, //number of command queues
		 &(queue.get()), //queue
		 0, // number of events waiting list
		 NULL, //event waiting list
		 &event); //event
  else if (std::is_same<T, std::complex<double>>::value)
    clblasDznrm2(v.size(),
		 result_buffer.begin().get_buffer().get(), //result buffer
		 0, //offset in result buffer
		 v.begin().get_buffer().get(), //input buffer
		 0, //offset in input buffer
		 1, //increment in input buffer
		 scratch_buffer.begin().get_buffer().get(),
		 1, //number of command queues
		 &(queue.get()), //queue
		 0, // number of events waiting list
		 NULL, //event waiting list
		 &event); //event
  clWaitForEvents(1, &event);
  return result_buffer[0];
}

template <typename T, typename A>
typename std::enable_if<is_numeric<T>::value, T>::type
norm_2(ublas::vector<T, A> const &v, compute::command_queue& queue)
{
  ublas::vector<T, opencl::storage> vdev(v, queue);
  return norm_2(vdev, queue);
}

}}}}

#endif 

/* misc.hpp
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
*/