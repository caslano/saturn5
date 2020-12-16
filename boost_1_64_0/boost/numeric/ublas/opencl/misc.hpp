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
DnPpzVnZEyZHh6gtnjznZ7JTuVgcqUcs9wXPgTvXM0Er16wQSM4UoHCbdksFXfXt1rFoHt1uRTdV06kvy0EcULB42WSykINKVcigG+Tk7ae2g+WNeetvKJPeTGwyr7g2LTG8AriqkEOn02P0Qqy6dRVFUAfdZlI1UEzKJX29ZhhXfMyKLi0zXUW1c7tS4iuevl9OXK3tvjebXHT+pMU3HgMuXd4aWPO80KlvV2mu6QPdEGtntnYQUM2zPq1lss18tC/gVhy4d+faKeo61HYeUKE33su1HfId6bYYUjRrOVA7YrFEslGqmXz1vgXyhD6iZLqSz7Z+3XzkTF5QKKj17e1EyvCvucBJ3g8X49c7r0706xrjp/vtUIaGnG4PVsXIdLFLCfFwhyv+q77MdNLpYymzXTuSuIHJdKKqqdswzVYfIDN54t4Ihw/SLYG7f9rDHOhbSIqPt0/c9ZA6OgWjq0J1OgSNFJnRr9GH76xqSXbyG0R5ZfOhI5Qv9NlO+BeqCv9CVeGfSxXFRDMcdYMc3AWeGmWqOa5b6nvz6QZ+KwJU0sN5FByb7c5/++JOzXfXt5yjvrmvwjedxd3uwXePCG076+A2F3NLvilCeULhpZsFAjdd14uTsVsLuBbXWhhi5ieH6HhhiIyufKlsX84inG53ft96QdkJK3o60c1RtnZ3tWjkgpcVwh2CizWCguoQyKEfXsX7Gdyyb0vhbUnxoWnqwSh4jhy2Glfi0TUUotyFYshdDA8c7t1Z3DBkpLC7wc45G2xydTbYjutbC52zGSQMH0/ZbBW7DEqd9tSWoVKJ1yxtB/3ZlF4O6k02p4PTM1XwqDHTUs5vSJh8u3siHl0VrS/MLnTrxLcX28P9wF1XVsskwhWwXP0bfRGs1fFxhr6+/9DX9xzc3zno58sJ/XwgwfHtCyff0um6eMWJJ8d+Pi7h+ARDX19ZMKakNAY1GTRUlF1Rb3477n6igmq7mFXJdqObP3tz6fVKWzqY5UGj5aYbU5sfJireBqKpg+0k377VtcIWULcxqxdHKZ1DhOxksOqU4mOkFhZXGoTZ15yHXnwewkS00HeGXnFu81w5Y3dOmm/HjZiOuBm1155Y9p5U0rWWZOQzwYm8MJHNmmkW8X24Yj77pmSCTz4Qi24KpMUWuQgUzsWo2XSiOTQ5ubga0HtGSyHMicmm8fUwqv7c7pjtGvL2nFelllmAgymwWtEjs72aRzx7eqyDGjottqfEYfPewg9I259JUd9DUb/mWNaaLjsuyyUn9cJ/TF8CQHxd4qhZCQbrcNdsCmChjZbR0nyEYPF5NDTLHFkFF8eRszX/1k0dfUXcZAWdu3siTi48Q+kDXbpwEH+iykDNCFLAnKFTE4RfXu20HaVRXrremgik7M6LeHTZSqK3tD0zsVcGXKsCmu2Uxqd78ZlazUWyZANpm20u3vVyo7dElYt7waGYxYZARDd6mk93Uyibyj/bHluGa9xiTUsWN9aJFjDRo0SQrNKoX6UihmMlw1rFIDsVseDmb4tv5at2sD2zV4mIFQwuNNMx4nAspdAKAFa9tYWmXvF2/A9YIgncSy6u5RawdcWm4an6al3gSgMdu1QF3wcJYVEbHvCt0kVvDeg6ZrH1DdfEDkkKW4AG7IsKbG2mjYohLwQW0wq8GXXSbS9CaVZeFgPX0lPospO95GTzUANRM0yumWT0NafAIvKaxkDqy/lWb0Ru8oZqsmNMLK55UzYaQJA5Rzc3SHPhd5QVU+Ss6wNR+oNO+uM+ZAh8pwIrDbq5t+zoOZqb8foiN/aSLVRGOUAjBItjjRmoWJuTdOLKhIL6bszVJSs/gWqYsDl7E3JZbcgFwy2y6X4=
*/