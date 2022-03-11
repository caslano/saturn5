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
MmrPijHeIruGSXVmulDnMGs33vLlbWpP5LUw0uTB8pGlHE9qEty648zZvva7+MgTkwrTswKZ+rq0Na0pWmAv6v7OaynBUDQm2qFxzCI/nnmKnC5OO+XiFfLo83ZV3zJm8u0S6Z0ROVvVow4bxwbGnwuRHfJArysxAY+HaDZRvM4W09EDmoLoB87iNzk5S1s/el0kG5cEFO3hZ8XY3AzPsiEkvnoJF7jLR2rLeA2dpUIshRIvV28L43S/lZ6hoqYbKNmJkd4iwQzP8vjXwhLNZzRlljHvB0EQawm5Jn9GTYEwmBjcNMd0kM0wtQCsln8hEhAx3ueNy1XJtcQZ+00hy3Rxh3Y9QbI2nZ+dF7tLs1oZIFw7kQcVmAZFdUxvrbL8dDPeTbdIMcyfolcJJQPwVkgf3h6B7aQVtvLQDRZJMvfMXks8U4gL1nySX2V/pizoYXs3mvYoKYDfzQdWMO4qY5WQp4f2NDNZO/Fkyuwa9x6QAL6bWbnngszUawB74O6YclYq8ff88JYK13iDdipgX4g/jxVk6u3P/NycguwJkbzZTi5ZTHbJbNjjd2/W7Yn6gH4z/QjWTHF6TWxZktMyWHIk7ewq2JE/mvYFxemESMwmrBbN8HsdTXvCATNNe2Vbt96uSpGmXyA/4k5KC6u4Nv056caA3LueTQg7X21E7DfvBfWpaDobRHJ5Gf+WKmj4SKipL4DR2MZDzan/LTHe9NLKYHkh0fmRjRdtmpT4PVRmr8xqjaGWv/cZNy0xEWps0UjVM+50UGrQ/nyQVixVUGpo0NYeZqeoodoi+S28gIV8Xcd76S5NThNFtQ9/Zc8Hl2C6dBshnmGJUqpNUwzPr5cvCJ72PmWSHI2eIkvA1nez+pVmig0/jnWVCFkEPECbPACBeuyOU5lcS39MSnqcB4InfSr7Cgq/1aiVzQi5qY0nLJWrzTc2+vkmrQ931/NrcPmaqsgXy7hMeySNHV5XFxu1qcf49iQUXPcQVqBkDHRJdrHSmyUJgu8Bs1grxghOQBryKsoaqZV9HBbjBKODVSvWkLqpzQtn6BJlLxYn152zZn3yrx2z5/cKawn1Rb/efMMnUuoeeT+pjry/jT9HcuTLILdTQkcZdZSVOLC5KMltvLsoqfYO23BUpEefdrCUsu62r7AF/97heap46u5+1pER7kNIXjEMfU5GKs7QR2bDW27S+V7nuFee2+AOhadlB25EtcByLVw76oieNt74XD24LU/nHOHP8v4IPKTRV8AWAIAYVis17AQPhjVZZHnCvkn9rqMcecRxP98YXPN9kGMcvM4yj666qykJjNNB1z8i4txlnzQ/1m2d1T5vFWxfom8W31qH90VFV+M/+YnwGnoz0eGbh7mUUi976csDYEF8D7dHP6DLno+q3GT/v36YyOOhrbz00hqYrlhdxEfqR0FhmS6lbvraFJyTnqd6DfXH4k9rUUASdHAuJKBta2Fqsamp+h/xolag4wCoiADId5GTPgCmA/oomulYr237Ga5YN7Gv2xntaZ+XLa/rLjO+E4f2J1m/pkjYEPELqkNbeuEVCZPm8887u4xjJ9v9rqq/qydVWubsK1H0npNG6EodSW5Kyi7trEfPcqcbzYJEV8NLV2EsHNL74U5HVDCDisIG2O9mbH0wwMWk005Ns68jjuFxf4FlSudvDiLK1TrRU44JMximI9Px8ztLH3v6K8L0duhQekqumezv6bcrxONNDyhhSW38ynryu+5Rcrsb1KZs7tWCFlrD9vTPktoh9vRdzh56CQLAGV5ndBITh5TWpde/58//SEoCK+luFo0a0G+UGLJLt9VgwCnBjSGff9ObSJ0Qhfapsg3a+4HxdYmx+9IE/lCElDC4h2Fcj8vesTBs5vRpsaoGMcFFu+/164Ft8LuSZyERijLkR/xpwX4Gidayb3bEUqCkq0Kcah67oyHi1NuIERFuVK+L4LQaxqebP4T0be/VqU88VTOWr1g5UE7AmA9L18XCoSNCt03gshO6VfMw989FGDzA91egn2ehf8uYU3FPvnBa0tJnXlzMu6J6LCloRdIR6Yj9HjW/ife4hU2/crj1YaLwTH0awu6Wjta9Pseey2+qYl08WmfNSBOoDiKrg9/i2sjHQILO9NJpEHkbQD9pQMuiLK3Z6IkUQRcTrg+s2dgsG03ulGRowQZLzXgpDC/ffEt/8FpvVOWNL1G5SStekuaoWj+36BIqVuliU0KCNa7xXTMhADeXz/dnCnLJKqU1jYDeOon/kwgJ4yhQs/tlwO2KcegLHznooUKt9ogU9ESZm82544vc2cZ0eSIczFQJ7hSiI8Fvpi4QMK9ihj9U4omixzuOckTBa524FKHgWx+7zxReSOKHnp4fRS9bJ4bRgMO6pW5m61x8d2aXgzZYUoJRdDLuA3GulzFU0pN6UYibgycPTzRXo7pFvvV6tHR39vxzbfjj49dGxft1VHgy7fNakaWAkMPbDliii8hUMatSoXYueSNJXlJYfCHno/ZUklSi00Se7S23ynvP42DkpeiI8nI4ZDQ4ZcGnB21UWmMnCTN60ZsqNiTP1w/OoAzevnGBuMLSqXzQGJ73voTvqMcxzIPVkIw/1mPwGTrHvPNkynwOd3Tf2TtyfpcXfxpRVQtrXZ+bEZ+K3NCOiZq5oqaJp5O72xknkKZDt2OQ+jZU84AbEo7f+ucwKhuBa13FPP7O7LamGt2Bqd4KRmbq6SN9XFNCgRmAgLf8b8VHByLYoWkXTCAthBoPepBN3IKp8Bzt5GdEe7BSt6DiIl9Eeey7hqfgcr3Z2ZtXgT3OborsK80ub/MJse9hutgCcco3T9ZDh16Z9Erl8UBv+cbKxfrdLWBlyJQeY6SJrpbqmkB8ilWVkE2LwM7C0/QrXqzJOw1xdI7K09VPF2NDn9p5uflG7OI5Z789Kbtinx7Unn3hsDaqJZV94bsz4rrGnrhLt+YgT8i8MPEelZ7Y/NFk+KAWfpXg2624J44crcjFfA1TtHEHp+g89ibQsM/eoAo6+dmrOM/cIF9amEA8lxs2ZOWOcIFM0mitNZsrHdd96kcceGkx2ysLs+NijUyTnhStJ9Dy4p7mLNRzTJELTSbGFtw0OVguNuIi/6MpiOhuMmhq42ePQdM97jGZtzwBcyBZk/FzHrBgPuJGxFteQPDBjdGtqqE7UGAKGOQeJ1gPZYgW5mcqxvVa+tqqL4OD1k5KMFK8nRmHgtcJu3Ugt5b2hGDzubTfY9tafmkvD1V69mqHwiej5EuRYhJmbwvHw84y4vD7lNEt8Fm/er87WE+rsLuHEoZ3lQxS3wKGdzNG9tiukA3FetsekjeKVCtpzEwIqfiKh2kFyntyMDw6zQ+Y9BGq+KaEV8XfDITcrHJLfLUmP9Umtor1iqO6PR5kZ2/I7wjSxkX1gB5DyKzqCxH71eAX9JPI3VropxxxQWSAQL5SlH4D9Gm1fqTdbvLjgxiaaFaL4DI7w60rGAe70nClsYTAiLCOvRaB07zx88pmBoFU9YAWel0qHGvp+8nd88F9hO0IQjQLmL0qDMHyOGYqrbxNn+tS/utnLwIePd9v57gONjOIw2sXR7DTVKrW6x7oiiPbD7+uVT86OuWxLS54Pjfd00OKBP7racoU9gcpMS506y0NTLB6ZUEWaZuOpqZUJwAoy7dx0Kb+5THG0d0nsuB0+I0v0Bh4wb8LXsyVN0ZBE09CdbBRnzTrWL3dF8iimG/rlGSMvp2x2Y0H3vSWYztCTIG7sq/Ef9pdYEpU3zopPbMvd/MDdJ74Y2cOPBkbTJUmYQs0B6YplZW5Uf4qtS+oXdWA+vvypw1KaBjqNanhtjdSDly0SXihXBhJOJfo7xW4peOEuJqWpLFDc+rjSyFu700NcHVquIfW/OksjxV1BxdHR19iLRhBOvbjE2VkbCJleXj0pUFUGcHd4Df3UntSmxwLnRkTg7ti1CJt9B3zIMlzxuZ6vcAFCY1e/rJd0kZVr2XTPLNWVWkSSSIh5s0s+ZA2olnvae7yM1H5IdDRO7rc6249wD5yl6VmxD3hDqfHJVNPlyK9Xp4f69lDsP1IjkAQyuDZJ7cd5kE+AQqVIhUcdzPCLpx7KhKn0/QT2rKb3snNVkUE6jGQFoJY8vg8OSbmgVI443NiIOMTAH1INLB3aAmW3xE8aFNOcXIbkeKlC5Js5vBfJEFFBXMCLTreQijXw4ObPLm4Ve5iYkU4WWAPogLTAzUMSeoRIaLnixycgrohko75EUtAP9W5RkPR19wpAQprKLfpIqd0ZvUba9OIFzQLPErsJFls2203+V1w/+7IE3EsrnXHeAl7A+TRLd0C0riP1cHrD0rF+ADQJYnD0SKacOHdAbSCtz0+P17pTBdFQLclIpOmn23Zqi+pSQy3EOA8Nn3qHmUSaG0yc0zVtUgFIV1uqNxKRA8acMJsX1bTR4mM7OLRRQzIg9FrVb6+YcJ8z6IGtnm2WRxLp32kQDxBsAbbwA716cJcv9TQY0Al0y+puO/qQ1rsnxhAXu+fJGB4n6Mh1zjFe6gpohElKF5Lpv4YCWpi2uWXa+M07/GqMefvhX07UdRc4JPfx8JoEUPLHiebirFUeLQacnn9NMzM8uVvu16qdCVyE+tIhsS3cxS4yddMVERTcMFl0d63ezdoZmvaX5hpjHNviXv9/HiFfCM+fbe4RBd1Gha+NOXFb18xBg5eEWlFmTt0mOV2uE3xk+4urIKhfMbY5F4ST3pO38V08/OYVMCgZEWqGPmZ9io15QIeQwRF0TtxJq4281dUZ474+rvef1SdLMh+N0A3Jtyj/O7GVIZ+pvVf/ixUNCF/+Gk4oOjEnlFdFU53nyzLnsew/pb9oBToay23CU5MHzKAFfTbqbqUmSbDRlC+S0XalxoRkkV1YQa6puMSktE6k18i53rJHz/kfcxJ8L+sGwO26yUhcjGnrTmWqBRsfO+4XvaUFJfNdvnOOBV4bQEhttegS27KxWuLx17UCQ7qFYCa/nFfPc5IChB1IfG1Ll/XskE/97sI3otUusX9+xMf/IjFtjX+3k3/3RmZ0GgMYC6Z6+OxdTyItW6jfCXaQvpHf+2xlJennTS+N+ajpZR/YzcujS+lMiUs3m/+BgA4Z+JLTdLiet11fTvIZva9v1nolTQMzOtOQ77S1KbkymEV7BPOYGb9bvvyy3AJNcwEMc/mSVzi+1zCqDHz0XuM/w4mrTErIfz++J0AC+zlDun8hJ0LdKH0yzZ1sViE9eMUiJt0yzZ3HEOb365gbkBw9fCTiMkCm0k6Ux+80+S4PNABMuxglpw5rBzgxidKwSsrKxIiz3ctLWTvETuPPN7+a1jFfqlsiKSpazqBdIx5zRxlbSJTfdN5bUMVcXMpaW1xyL6FNWo5co+HUyBahlrsKiDcsoJC2mEZLG8SQgmn6A4KfwhlB2HAIKJq0D7V0MKPcLOEvGBG5fZc50k9CmrvnwjGx1s8CXbhqsV6U+vfRYAMRkG5xCIHqTJA81FFrJZ3tGYBQ8zDEnK3qilFkUkLNyyY1MqC+TkG68ACxxo4Oc+aPjRfBm4wrVZimzhDnYxz1Dt99hqRRSrl2rjsQ4fvcpyU2EdtDB8ZMZGM5wgPaxe1Dd9dF5sLwjEW7kIk6WkhktiDraVlUvdP2S0i3cyeZbFGgNHpUGWf6GFWfXfSZgGBjJ84KG3AVbCX09vQxUL627zBujXD+ubOswqrZu1kfL8LQw8wj4bQ62/Gtp97s/Obgo+B7R/iSz0Z4gO8XhAD7BXXWWQiJhZ+FHyuNd7dO9sZ1r2Vqy81NyVZAPrtb0AVmQzeXIzGozknrUyxaPOq5F3Mrmyxssc07vCdOSOPRx6vBxJFKWdkCy8pg/sGx69a7vETsyOFbc4/sfd7hB7uxTe2KifEnox1N9Y3jNMPiu2nY012le6dV+netOgD5IiioUlr72F7lJdPDytQew40GHZzLzEJMUyDMx8MkjptlYKlWQ0kmbD7Jz7qSDETfsEhCHpgKdfQewIAbkia8P8wPk8+TllLE/kYAUr2V269UW9AnPleZUe5ALdOhuz53WwYcGZ1+BQhwJ39yHzxZnHfXIIh4E6vSX7zrqPs2RSwU12qEOD2lPWgbn7+l4yXW2E77Tyy+wJMqJtqVs7KJzdFGDdTik3CECGEpyebfmTMGXn2roRmYIH1ekkf4D6Ul2GgqHZ1RrGhn2H575eZS6B+leLKena4oLZOjeKUlWX1RX/66OPZzfv9OeZn53lrKqHEEE3LYh7KHZa172pWBTQRXWSar28cmITW6wLXjP6xlZoGCDpL6OODcQE/cVkxqu/WE/kLYSfrQJF82xjhgNoMNUPQqlssi+06a85hqEtGmY6JowjBUBEG+HEhAEahP/uXGZ+REscvWGU2+bu71K1G9ubduIYM7JXrplKo68x9Yj6mtv4D7/od3EExZtSBfgd7rdnHW4SlFWtYln/m3iilMhX23cNtcuoHM/lHpKTPD93DHbJw6OoMa+mtycP6qqqLtINdn2hJ94MS7CjRWQJ4+7AG2uElJQ49TVU28NquycSqvS6Km/0CWNy9lL0aOTcFzpqOgks8SH2ci62D4WFlTy/hJTkeNLW0bRdGTU6ZepQxwvp2fx6qJEpXGRK92XVeuSOrk8mMI9OAA1c41dQHEoH6W7xYI9R9qWlZj9BjPg9vrGOm1Py+SqF63mnKsHqmGX0DnV02KBmB/9Jnz+RDzc7RUAFcj+WD5UdrLAZ0U4FGSzRpabUSYKaKdGki18EWIcuskQaVw47mKwCLaWmE8W/8icSKTjdWgD0Zs5GQj+pV+SMKAMrowmZXsVnX6Gfj9TNe/h1Fd/pc/qGGTmKxNt4v95wRfFQ+k9Eb3o6v/iD8SiW7yEctQ8SeWXpf1n+yJ8zSThu+a5/vy6WTEDSAp8c184KwXqJytaNyha9yhaHCJbyka59NBZRgN8fEuo+mwo+3+afsz/nXrZyXwo3fTyP6U0iCy7NruEyBY+MELQkMV11kTv5EoHReBxJIOThp8NJTV9GgU2kzo4f96hWS43GzsaJsJ1lCeZsUU9mewzFH+3Vd2qMszLAr1kQa/OKd/AIFGbxu99AO/NKbrD727Tp9ApW/CdvddXsDV+DBUAOWyMStBzAXgf9qyHnA7/lx8/uRKX+G52ffvGOBCAX26SB9SWkPoK0q92OxadWnIHlp+oCwqWoLrb7Q7sDqblDOA51g8GWHELeZt78S6HSBBz4SWP9Wf5du/2Hw8uPxoJzcVGF5oAuJNO3u5R191mEx/ZZjyHqz6k9za4BXbPxYM9XlELv2M3SLTvEt97TIzzktgnwWALvxaE4J2fjoCfhCDVpMYTLeIZ/lIRBiygUje9MFC6l4nMgFb3cCWw++BpklyMb/LAv66Q99iyF9bYXwmGYIlVpKgpQtUgpwocBFrZu9HsJQW9exSYs1Sn5Ls03yTmf4VhdoOKJuJHpadU5M0IPM8x0EPBs90pMr+Y9Er4CK8vnelxapj4QgqVLSIJ0roCCttLSEgHT3LiElJd0sSkl3x4J0Lt2wdMPSy7Ls7t/v73/OO8/MO/e998zcee6cO+edgWx0xvCT+OiC5+wyr4qAUkXyaccSNySg8tNBDO/OjEPrp2SXD9EqlNgoRTa542LfJt/MRCK309zv/lAWhJC4Q+GtA8Vowt+jytqvlvTT/VmSL10wzVI5z5nNGyr2KjaX2i4rvtxkglK5ZwbLwKclF7wfz1OSZ98VwaKcB3ICjhQ8NwXqs6bYiwILgFkfoBsw5owfl73GDQ931ehrE/y1h65lxKPbuKdJgmtieT0unk9R5IY1933xB9IHqC5/qg2afqlfWzjVhovvHVG21a99mr+Bc6PNfDVe0ToYbSeFMRlv3xJKNw2EE1j59wnk6SuQLfNy3Afd8ACqhNgie3kCYjbPR/Z6Dmp91i32Qn7J/h174GWYzx4me3hFFj1PihRfnc2/aLCemxTpuJCzn10FA2kkhbL3PztWW1xJBTZ+JwJr5r5dIz1DH/Q4MLxFBx0anHdyGbwuUgHNqbLVM8fxraYmN02od71vuP3xLsfhGK/ix1sBlyEKaLNURV/nMk4OMRvDfGb4rRYhyK/sHOlHmjf13pHMCnf9qZBMPLGFj+VYzjLN7ZRHqvj9m10dHgG1H7pBLvZy9qgPPRj990dy+RzalOs2bzXy8SSMl6fp6if1hze0OEjARLNs3s+WpXBEjftc344f2gkDnq8MfpzvgIx9b7DYt8oeENeSa/uehMpXo7yA2TD1GpIlvFPXsvOI/jEDH9J5NDXr/XTJLJu+Gj872qFhadPW8Jr2uxjN+XuJGDDC6vx53hCu1bZIyX9Pd32fgAE2T359ii/5uf9SBvqRemwX9+tvs/vIvE0I9tevQgjHBzYqFJGetMIcxmguLzlYmvHnW5qCzbLbbnyRV6SDv7EvqLx1u+9jKQ1uYi28HvFLkDbdbvfMA1M/5gqmIqr1TRNMf86CXZaDetzU0UsyL5+GSrGuM4QLIfQJExKoncsYVhqmEod8uuJEqKLlAsKir7J+yV6svI7Q/dY4rJJ6R/tpRkfIsfjVX3VfbYWyd0nUiMSmcmq15coi12nv5FDtUj5/wqaiix8woDL7LvpnYLxloCpcl3uqrWQ6bFmGBlnuwT33p5Jr1r9Ix7CkTucPwaHlEyUSjqKPgf0l+YVdxhiy9FeVfe9Ettgcez8Tq8rbfPV+wm7gQPs8ukZC94yBc+FeaVnIJTTL+y3/zFHj10gY92Hr/BjZ5UDv9VzrcNKbINU2/4wmLSYlXUaV4t9DWsPUogxJh97fOXRYe35bMx5fWUslCA23WFupEkPX1pBCceePD0JSNa6UfsMufpa8ZxeXFpZW/ET0sjq0+tWqtIBIJ8ecziKkwf3gaOnUvCOtvGRZgEgnY67n4DybOXmCJPqx+iaTEGPxJEaG+e+CkgUlYlzrE9Hot+p5TXSGd9ZtWQaX4O7rh/zJGSsn6N2yvOczAnuI5YSO2dSFxcsEx0xAR3CkNr7PwpWDfkbopR7UQ5dvlCk+kMdKQh/kIansN7GtmMH9yfex+OmVPfuqoGmS8RB0fts5I/1GhXNcKmvfg4T4vUzZN/hLJxZ7K/5lKltmBe463uafH4vfBmoaOXLv6Vo5epCGMXA=
*/