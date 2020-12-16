// Boost.uBLAS
//
// Copyright (c) 2018 Fady Essam
// Copyright (c) 2018 Stefan Seefeld
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or
// copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef boost_numeric_ublas_opencl_vector_hpp_
#define boost_numeric_ublas_opencl_vector_hpp_

#include <boost/numeric/ublas/opencl/library.hpp>
#include <boost/numeric/ublas/functional.hpp>
#include <boost/compute/core.hpp>
#include <boost/compute/algorithm.hpp>
#include <boost/compute/buffer.hpp>
#include <boost/compute/container/vector.hpp>

namespace boost { namespace numeric { namespace ublas { namespace opencl {

class storage;

namespace compute = boost::compute;

} // namespace opencl

template <class T>
class vector<T, opencl::storage> : public boost::compute::vector<T>
{
  typedef std::size_t size_type;
public:
  vector() : compute::vector<T>() {}
  vector(size_type size, compute::context context)
    : compute::vector<T>(size, context)
  { device_ = context.get_device();}
  vector(size_type size, T value, compute::command_queue queue)
    : compute::vector<T>(size, value, queue.get_context())
  {
    queue.finish();
    device_ = queue.get_device();
  }

  template <typename A>
  vector(vector<T, A> const &v, compute::command_queue &queue)
    : vector(v.size(), queue.get_context())
  {
    this->from_host(v, queue);
  }
  

  const compute::device device() const { return device_;}
  compute::device device() { return device_;}

  template<class A>
  void from_host(ublas::vector<T, A> const &v, compute::command_queue & queue)
  {
    assert(this->device() == queue.get_device());
    compute::copy(v.begin(),
		  v.end(),
		  this->begin(),
		  queue);
    queue.finish();
  }

  template<class A>
  void to_host(ublas::vector<T, A>& v, compute::command_queue& queue) const
  {
    assert(this->device() == queue.get_device());
    compute::copy(this->begin(),
		  this->end(),
		  v.begin(),
		  queue);
    queue.finish();
  }

  void fill(T value, compute::command_queue & queue)
  {
    assert(this->device() == queue.get_device());
    compute::fill(this->begin(), this->end(), value, queue);
    queue.finish();
  }

private:
  compute::device device_;
};

}}}

#endif

/* vector.hpp
A04B/+qn7wvtSH9gCFAAJAHDAPWFf77M/lvakV3ANmAj8leDlwPv4PuHwDHgFBAB2QggC5i75Z+vh35eRjlrgL3/ZDtX/JPpa//J9FsewjuRQCPQArRfgfdOAREYCUwFyoD5wEqgFtgJvAM0A+cA7mG8XQmowAhgElAIVAKLgdVALbANOAAcAY4B54CIlagPGALEAilABlAAzAOWA88CO4HDQAtwGmj/CN4+BQYBI4BJwDRgDrAYqAI2A3uBD4GTQPdVWDuACSQDecAc4F5gJVAN1AHbgT3AIeAT4DQQ+SjeNQWGADaQCmQDFcBCoBp4GTgMNAPtV7cjMcAQIBZIBaYCc4ClQDWwGdgLNAIngcjH0B9gGJABzAFWABuBBqAZiKjCW7RALJANzAeeBDYDO4H3gaPAWaDjb7EngYGADaQChcA8YDlQA2wD9gPvA8eA00D7NXgrFBgCjAAygNnAQmAZsAbYDBwEGoGzAPc42gXYQCowDagElgJrgA1APXAAOAIcA04BkdWoCxgI6EACMAkoAOYCS4A1wEZgN3AYOAFEPYH2AUlANjAHWAZUA5uBPcD7wJdAxyexHh7CvINTgTxgLrAMWAtsA/YDnwDHgbNA5FNYX4AEjADGAwXAPGAVUAfsApqAs0CvGuwZIBUoBu4FaoG9QDPQ9WnMLaADKcBkoBhYCKwGNgJ7gaNAxFrUDUhAMpAHLADWAu8AJ4DwdagTEIERwHggD5gDLAM2AnuBD4HTQGQt1i9gA2nANGAusBSoBl4G9gKHgSbgFND+GawfYBAQB4wHSoB5wDKgFtgJHASOAR2fxbu0gAIkA9OA+UAtsA04ADQBJ4D2z2E/Av0BEbCBJGASkAeUAZXAQmAZUANsA/YA7wBNwHEgvA5rD7gKUICRwC+BOcBqoB44DDQD7ddD1wADgWFABjANmAMsAFYDtcBO4B3gGBC6AeMMXAUowAhgPJANlAALgCpgLbAFOAS0AOcA7nmsUSAOmAAUABXAUmAtsB04ADQBpwFuI8YaGAFMAKYBs4F5wL1ADbALeB9oAc4B3CaMOcADNpAGLH4IfQIKgQlAAqADA4FooD1wYjnWBrAX2AI8CSwH5gMVwFRgPDAC0IEBQDQQChx/EHsF2AtsANYAy4H5wGxgKjAJSAZigUFANNAROLUMaxw4DOwHdgJ1wGrgXqAS6I/9V7zsn7NjFz//2c+Exa3jPw1rquFOrPWFrbJI6mdUYk4XtcrmQ1YJ2akgWcMWzCXy1gfJWiBTIRsQVEf3rdhHkKUFpZMg21/Z7qIfetEPveiHXvRDL/qhF/3Qi37oRT/0oh/6f/QpDxueOjElbUz67MwCvKdMYv1h9vbYqpBhiWPSWx9EG8jCwa+o3cIk7j+Q7744VEIl7CmaRHzzFURWBkpiz42QZBbODYQfDcSzR3HIDW58IFwViA88AEHG+9IEy2qZzPeaA6ljIfddgiHsO3sPjlxDv7d5z24hkxXjPXNCEtyW5xf6+nSHr08VaMlqf0t84XH+VqDKspJZ+H9maRFa8pgvXVv5fa488Jad49ble5yFkMEszF63QwW+3KSqXXxqKlrnf6hrHUtVllPqnxqymEnYKz/k5+z70Li4VDYR5GeBsDsdfQJhdzIJmR46bNyI9NHxo1mGPH/IN3v5gXBuSRHKK0RrfFl97antOCYlPpm9rzE9vbB8BiGbgiXsvX5C1gXLUBFSFhSQp4KlrMIngiRsGshzwRI2STf4V+oMd+U+GEiRnZ9D1rijXMhelcRKKGAtzszOdtvrW3VG+/jxKemj49JL82fnkF6+EHvabEY2aWhHw8MTUxLiU/2j/HywDOn8L7ptbyvPn5k=
*/