//  (C) Copyright Nick Thompson 2019.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_INTERPOLATORS_DETAIL_CARDINAL_TRIGONOMETRIC_HPP
#define BOOST_MATH_INTERPOLATORS_DETAIL_CARDINAL_TRIGONOMETRIC_HPP
#include <cstddef>
#include <cmath>
#include <stdexcept>
#include <boost/math/constants/constants.hpp>

#ifdef BOOST_HAS_FLOAT128
#include <quadmath.h>
#endif

#ifdef __has_include
#  if __has_include(<fftw3.h>)
#    include <fftw3.h>
#  else
#    error "This feature is unavailable without fftw3 installed"
#endif
#endif

namespace boost { namespace math { namespace interpolators { namespace detail {

template<typename Real>
class cardinal_trigonometric_detail {
public:
  cardinal_trigonometric_detail(const Real* data, size_t length, Real t0, Real h)
  {
    m_data = data;
    m_length = length;
    m_t0 = t0;
    m_h = h;
    throw std::domain_error("Not implemented.");
  }
private:
  size_t m_length;
  Real m_t0;
  Real m_h;
  Real* m_data;
};

template<>
class cardinal_trigonometric_detail<float> {
public:
  cardinal_trigonometric_detail(const float* data, size_t length, float t0, float h) : m_t0{t0}, m_h{h}
  {
    if (length == 0)
    {
      throw std::logic_error("At least one sample is required.");
    }
    if (h <= 0)
    {
      throw std::logic_error("The step size must be > 0");
    }
    // The period sadly must be stored, since the complex vector has length that cannot be used to recover the period:
    m_T = m_h*length;
    m_complex_vector_size = length/2 + 1;
    m_gamma = fftwf_alloc_complex(m_complex_vector_size);
    // The const_cast is legitimate: FFTW does not change the data as long as FFTW_ESTIMATE is provided.
    fftwf_plan plan = fftwf_plan_dft_r2c_1d(length, const_cast<float*>(data), m_gamma, FFTW_ESTIMATE);
    // FFTW says a null plan is impossible with the basic interface we are using, and I have no reason to doubt them.
    // But it just feels weird not to check this:
    if (!plan)
    {
      throw std::logic_error("A null fftw plan was created.");
    }

    fftwf_execute(plan);
    fftwf_destroy_plan(plan);

    float denom = length;
    for (size_t k = 0; k < m_complex_vector_size; ++k)
    {
      m_gamma[k][0] /= denom;
      m_gamma[k][1] /= denom;
    }

    if (length % 2 == 0)
    {
      m_gamma[m_complex_vector_size -1][0] /= 2;
      // numerically, m_gamma[m_complex_vector_size -1][1] should be zero . . .
      // I believe, but need to check, that FFTW guarantees that it is identically zero.
    }
  }

  cardinal_trigonometric_detail(const cardinal_trigonometric_detail& old)  = delete;

  cardinal_trigonometric_detail& operator=(const cardinal_trigonometric_detail&) = delete;

  cardinal_trigonometric_detail(cardinal_trigonometric_detail &&) = delete;

  float operator()(float t) const
  {
    using std::sin;
    using std::cos;
    using boost::math::constants::two_pi;
    using std::exp;
    float s = m_gamma[0][0];
    float x = two_pi<float>()*(t - m_t0)/m_T;
    fftwf_complex z;
    // boost::math::cos_pi with a redefinition of x? Not now . . .
    z[0] = cos(x);
    z[1] = sin(x);
    fftwf_complex b{0, 0};
    // u = b*z
    fftwf_complex u;
    for (size_t k = m_complex_vector_size - 1; k >= 1; --k) {
      u[0] = b[0]*z[0] - b[1]*z[1];
      u[1] = b[0]*z[1] + b[1]*z[0];
      b[0] = m_gamma[k][0] + u[0];
      b[1] = m_gamma[k][1] + u[1];
    }

    s += 2*(b[0]*z[0] - b[1]*z[1]);
    return s;
  }

  float prime(float t) const
  {
      using std::sin;
      using std::cos;
      using boost::math::constants::two_pi;
      using std::exp;
      float x = two_pi<float>()*(t - m_t0)/m_T;
      fftwf_complex z;
      z[0] = cos(x);
      z[1] = sin(x);
      fftwf_complex b{0, 0};
      // u = b*z
      fftwf_complex u;
      for (size_t k = m_complex_vector_size - 1; k >= 1; --k)
      {
        u[0] = b[0]*z[0] - b[1]*z[1];
        u[1] = b[0]*z[1] + b[1]*z[0];
        b[0] = k*m_gamma[k][0] + u[0];
        b[1] = k*m_gamma[k][1] + u[1];
      }
      // b*z = (b[0]*z[0] - b[1]*z[1]) + i(b[1]*z[0] + b[0]*z[1])
      return -2*two_pi<float>()*(b[1]*z[0] + b[0]*z[1])/m_T;
  }

  float double_prime(float t) const
  {
      using std::sin;
      using std::cos;
      using boost::math::constants::two_pi;
      using std::exp;
      float x = two_pi<float>()*(t - m_t0)/m_T;
      fftwf_complex z;
      z[0] = cos(x);
      z[1] = sin(x);
      fftwf_complex b{0, 0};
      // u = b*z
      fftwf_complex u;
      for (size_t k = m_complex_vector_size - 1; k >= 1; --k)
      {
        u[0] = b[0]*z[0] - b[1]*z[1];
        u[1] = b[0]*z[1] + b[1]*z[0];
        b[0] = k*k*m_gamma[k][0] + u[0];
        b[1] = k*k*m_gamma[k][1] + u[1];
      }
      // b*z = (b[0]*z[0] - b[1]*z[1]) + i(b[1]*z[0] + b[0]*z[1])
      return -2*two_pi<float>()*two_pi<float>()*(b[0]*z[0] - b[1]*z[1])/(m_T*m_T);
  }

  float period() const
  {
    return m_T;
  }

  float integrate() const
  {
    return m_T*m_gamma[0][0];
  }

  float squared_l2() const
  {
    float s = 0;
    // Always add smallest to largest for accuracy.
    for (size_t i = m_complex_vector_size - 1; i >= 1; --i)
    {
        s += (m_gamma[i][0]*m_gamma[i][0] + m_gamma[i][1]*m_gamma[i][1]);
    }
    s *= 2;
    s += m_gamma[0][0]*m_gamma[0][0];
    return s*m_T;
  }


  ~cardinal_trigonometric_detail()
  {
    if (m_gamma)
    {
      fftwf_free(m_gamma);
      m_gamma = nullptr;
    }
  }


private:
  float m_t0;
  float m_h;
  float m_T;
  fftwf_complex* m_gamma;
  size_t m_complex_vector_size;
};


template<>
class cardinal_trigonometric_detail<double> {
public:
  cardinal_trigonometric_detail(const double* data, size_t length, double t0, double h) : m_t0{t0}, m_h{h}
  {
    if (length == 0)
    {
      throw std::logic_error("At least one sample is required.");
    }
    if (h <= 0)
    {
      throw std::logic_error("The step size must be > 0");
    }
    m_T = m_h*length;
    m_complex_vector_size = length/2 + 1;
    m_gamma = fftw_alloc_complex(m_complex_vector_size);
    fftw_plan plan = fftw_plan_dft_r2c_1d(length, const_cast<double*>(data), m_gamma, FFTW_ESTIMATE);
    if (!plan)
    {
      throw std::logic_error("A null fftw plan was created.");
    }

    fftw_execute(plan);
    fftw_destroy_plan(plan);

    double denom = length;
    for (size_t k = 0; k < m_complex_vector_size; ++k)
    {
      m_gamma[k][0] /= denom;
      m_gamma[k][1] /= denom;
    }

    if (length % 2 == 0)
    {
      m_gamma[m_complex_vector_size -1][0] /= 2;
    }
  }

  cardinal_trigonometric_detail(const cardinal_trigonometric_detail& old)  = delete;

  cardinal_trigonometric_detail& operator=(const cardinal_trigonometric_detail&) = delete;

  cardinal_trigonometric_detail(cardinal_trigonometric_detail &&) = delete;

  double operator()(double t) const
  {
    using std::sin;
    using std::cos;
    using boost::math::constants::two_pi;
    using std::exp;
    double s = m_gamma[0][0];
    double x = two_pi<double>()*(t - m_t0)/m_T;
    fftw_complex z;
    z[0] = cos(x);
    z[1] = sin(x);
    fftw_complex b{0, 0};
    // u = b*z
    fftw_complex u;
    for (size_t k = m_complex_vector_size - 1; k >= 1; --k)
    {
      u[0] = b[0]*z[0] - b[1]*z[1];
      u[1] = b[0]*z[1] + b[1]*z[0];
      b[0] = m_gamma[k][0] + u[0];
      b[1] = m_gamma[k][1] + u[1];
    }

    s += 2*(b[0]*z[0] - b[1]*z[1]);
    return s;
  }

  double prime(double t) const
  {
      using std::sin;
      using std::cos;
      using boost::math::constants::two_pi;
      using std::exp;
      double x = two_pi<double>()*(t - m_t0)/m_T;
      fftw_complex z;
      z[0] = cos(x);
      z[1] = sin(x);
      fftw_complex b{0, 0};
      // u = b*z
      fftw_complex u;
      for (size_t k = m_complex_vector_size - 1; k >= 1; --k)
      {
        u[0] = b[0]*z[0] - b[1]*z[1];
        u[1] = b[0]*z[1] + b[1]*z[0];
        b[0] = k*m_gamma[k][0] + u[0];
        b[1] = k*m_gamma[k][1] + u[1];
      }
      // b*z = (b[0]*z[0] - b[1]*z[1]) + i(b[1]*z[0] + b[0]*z[1])
      return -2*two_pi<double>()*(b[1]*z[0] + b[0]*z[1])/m_T;
  }

  double double_prime(double t) const
  {
      using std::sin;
      using std::cos;
      using boost::math::constants::two_pi;
      using std::exp;
      double x = two_pi<double>()*(t - m_t0)/m_T;
      fftw_complex z;
      z[0] = cos(x);
      z[1] = sin(x);
      fftw_complex b{0, 0};
      // u = b*z
      fftw_complex u;
      for (size_t k = m_complex_vector_size - 1; k >= 1; --k)
      {
        u[0] = b[0]*z[0] - b[1]*z[1];
        u[1] = b[0]*z[1] + b[1]*z[0];
        b[0] = k*k*m_gamma[k][0] + u[0];
        b[1] = k*k*m_gamma[k][1] + u[1];
      }
      // b*z = (b[0]*z[0] - b[1]*z[1]) + i(b[1]*z[0] + b[0]*z[1])
      return -2*two_pi<double>()*two_pi<double>()*(b[0]*z[0] - b[1]*z[1])/(m_T*m_T);
  }

  double period() const
  {
    return m_T;
  }

  double integrate() const
  {
    return m_T*m_gamma[0][0];
  }

  double squared_l2() const
  {
    double s = 0;
    for (size_t i = m_complex_vector_size - 1; i >= 1; --i)
    {
        s += (m_gamma[i][0]*m_gamma[i][0] + m_gamma[i][1]*m_gamma[i][1]);
    }
    s *= 2;
    s += m_gamma[0][0]*m_gamma[0][0];
    return s*m_T;
  }

  ~cardinal_trigonometric_detail()
  {
    if (m_gamma)
    {
      fftw_free(m_gamma);
      m_gamma = nullptr;
    }
  }

private:
  double m_t0;
  double m_h;
  double m_T;
  fftw_complex* m_gamma;
  size_t m_complex_vector_size;
};


template<>
class cardinal_trigonometric_detail<long double> {
public:
  cardinal_trigonometric_detail(const long double* data, size_t length, long double t0, long double h) : m_t0{t0}, m_h{h}
  {
    if (length == 0)
    {
      throw std::logic_error("At least one sample is required.");
    }
    if (h <= 0)
    {
      throw std::logic_error("The step size must be > 0");
    }
    m_T = m_h*length;
    m_complex_vector_size = length/2 + 1;
    m_gamma = fftwl_alloc_complex(m_complex_vector_size);
    fftwl_plan plan = fftwl_plan_dft_r2c_1d(length, const_cast<long double*>(data), m_gamma, FFTW_ESTIMATE);
    if (!plan)
    {
      throw std::logic_error("A null fftw plan was created.");
    }

    fftwl_execute(plan);
    fftwl_destroy_plan(plan);

    long double denom = length;
    for (size_t k = 0; k < m_complex_vector_size; ++k)
    {
      m_gamma[k][0] /= denom;
      m_gamma[k][1] /= denom;
    }

    if (length % 2 == 0) {
      m_gamma[m_complex_vector_size -1][0] /= 2;
    }
  }

  cardinal_trigonometric_detail(const cardinal_trigonometric_detail& old)  = delete;

  cardinal_trigonometric_detail& operator=(const cardinal_trigonometric_detail&) = delete;

  cardinal_trigonometric_detail(cardinal_trigonometric_detail &&) = delete;

  long double operator()(long double t) const
  {
    using std::sin;
    using std::cos;
    using boost::math::constants::two_pi;
    using std::exp;
    long double s = m_gamma[0][0];
    long double x = two_pi<long double>()*(t - m_t0)/m_T;
    fftwl_complex z;
    z[0] = cos(x);
    z[1] = sin(x);
    fftwl_complex b{0, 0};
    fftwl_complex u;
    for (size_t k = m_complex_vector_size - 1; k >= 1; --k)
    {
      u[0] = b[0]*z[0] - b[1]*z[1];
      u[1] = b[0]*z[1] + b[1]*z[0];
      b[0] = m_gamma[k][0] + u[0];
      b[1] = m_gamma[k][1] + u[1];
    }

    s += 2*(b[0]*z[0] - b[1]*z[1]);
    return s;
  }

  long double prime(long double t) const
  {
      using std::sin;
      using std::cos;
      using boost::math::constants::two_pi;
      using std::exp;
      long double x = two_pi<long double>()*(t - m_t0)/m_T;
      fftwl_complex z;
      z[0] = cos(x);
      z[1] = sin(x);
      fftwl_complex b{0, 0};
      // u = b*z
      fftwl_complex u;
      for (size_t k = m_complex_vector_size - 1; k >= 1; --k)
      {
        u[0] = b[0]*z[0] - b[1]*z[1];
        u[1] = b[0]*z[1] + b[1]*z[0];
        b[0] = k*m_gamma[k][0] + u[0];
        b[1] = k*m_gamma[k][1] + u[1];
      }
      // b*z = (b[0]*z[0] - b[1]*z[1]) + i(b[1]*z[0] + b[0]*z[1])
      return -2*two_pi<long double>()*(b[1]*z[0] + b[0]*z[1])/m_T;
  }

  long double double_prime(long double t) const
  {
      using std::sin;
      using std::cos;
      using boost::math::constants::two_pi;
      using std::exp;
      long double x = two_pi<long double>()*(t - m_t0)/m_T;
      fftwl_complex z;
      z[0] = cos(x);
      z[1] = sin(x);
      fftwl_complex b{0, 0};
      // u = b*z
      fftwl_complex u;
      for (size_t k = m_complex_vector_size - 1; k >= 1; --k)
      {
        u[0] = b[0]*z[0] - b[1]*z[1];
        u[1] = b[0]*z[1] + b[1]*z[0];
        b[0] = k*k*m_gamma[k][0] + u[0];
        b[1] = k*k*m_gamma[k][1] + u[1];
      }
      // b*z = (b[0]*z[0] - b[1]*z[1]) + i(b[1]*z[0] + b[0]*z[1])
      return -2*two_pi<long double>()*two_pi<long double>()*(b[0]*z[0] - b[1]*z[1])/(m_T*m_T);
  }

  long double period() const
  {
    return m_T;
  }

  long double integrate() const
  {
    return m_T*m_gamma[0][0];
  }

  long double squared_l2() const
  {
    long double s = 0;
    for (size_t i = m_complex_vector_size - 1; i >= 1; --i)
    {
        s += (m_gamma[i][0]*m_gamma[i][0] + m_gamma[i][1]*m_gamma[i][1]);
    }
    s *= 2;
    s += m_gamma[0][0]*m_gamma[0][0];
    return s*m_T;
  }

  ~cardinal_trigonometric_detail()
  {
    if (m_gamma)
    {
      fftwl_free(m_gamma);
      m_gamma = nullptr;
    }
  }

private:
  long double m_t0;
  long double m_h;
  long double m_T;
  fftwl_complex* m_gamma;
  size_t m_complex_vector_size;
};

#ifdef BOOST_HAS_FLOAT128
template<>
class cardinal_trigonometric_detail<__float128> {
public:
  cardinal_trigonometric_detail(const __float128* data, size_t length, __float128 t0, __float128 h) : m_t0{t0}, m_h{h}
  {
    if (length == 0)
    {
      throw std::logic_error("At least one sample is required.");
    }
    if (h <= 0)
    {
      throw std::logic_error("The step size must be > 0");
    }
    m_T = m_h*length;
    m_complex_vector_size = length/2 + 1;
    m_gamma = fftwq_alloc_complex(m_complex_vector_size);
    fftwq_plan plan = fftwq_plan_dft_r2c_1d(length, reinterpret_cast<__float128*>(const_cast<__float128*>(data)), m_gamma, FFTW_ESTIMATE);
    if (!plan)
    {
      throw std::logic_error("A null fftw plan was created.");
    }

    fftwq_execute(plan);
    fftwq_destroy_plan(plan);

    __float128 denom = length;
    for (size_t k = 0; k < m_complex_vector_size; ++k)
    {
      m_gamma[k][0] /= denom;
      m_gamma[k][1] /= denom;
    }
    if (length % 2 == 0)
    {
      m_gamma[m_complex_vector_size -1][0] /= 2;
    }
  }

  cardinal_trigonometric_detail(const cardinal_trigonometric_detail& old)  = delete;

  cardinal_trigonometric_detail& operator=(const cardinal_trigonometric_detail&) = delete;

  cardinal_trigonometric_detail(cardinal_trigonometric_detail &&) = delete;

  __float128 operator()(__float128 t) const
  {
    using std::sin;
    using std::cos;
    using boost::math::constants::two_pi;
    using std::exp;
    __float128 s = m_gamma[0][0];
    __float128 x = two_pi<__float128>()*(t - m_t0)/m_T;
    fftwq_complex z;
    z[0] = cosq(x);
    z[1] = sinq(x);
    fftwq_complex b{0, 0};
    fftwq_complex u;
    for (size_t k = m_complex_vector_size - 1; k >= 1; --k)
    {
      u[0] = b[0]*z[0] - b[1]*z[1];
      u[1] = b[0]*z[1] + b[1]*z[0];
      b[0] = m_gamma[k][0] + u[0];
      b[1] = m_gamma[k][1] + u[1];
    }

    s += 2*(b[0]*z[0] - b[1]*z[1]);
    return s;
  }

  __float128 prime(__float128 t) const
  {
      using std::sin;
      using std::cos;
      using boost::math::constants::two_pi;
      using std::exp;
      __float128 x = two_pi<__float128>()*(t - m_t0)/m_T;
      fftwq_complex z;
      z[0] = cosq(x);
      z[1] = sinq(x);
      fftwq_complex b{0, 0};
      // u = b*z
      fftwq_complex u;
      for (size_t k = m_complex_vector_size - 1; k >= 1; --k)
      {
        u[0] = b[0]*z[0] - b[1]*z[1];
        u[1] = b[0]*z[1] + b[1]*z[0];
        b[0] = k*m_gamma[k][0] + u[0];
        b[1] = k*m_gamma[k][1] + u[1];
      }
      // b*z = (b[0]*z[0] - b[1]*z[1]) + i(b[1]*z[0] + b[0]*z[1])
      return -2*two_pi<__float128>()*(b[1]*z[0] + b[0]*z[1])/m_T;
  }

  __float128 double_prime(__float128 t) const
  {
      using std::sin;
      using std::cos;
      using boost::math::constants::two_pi;
      using std::exp;
      __float128 x = two_pi<__float128>()*(t - m_t0)/m_T;
      fftwq_complex z;
      z[0] = cosq(x);
      z[1] = sinq(x);
      fftwq_complex b{0, 0};
      // u = b*z
      fftwq_complex u;
      for (size_t k = m_complex_vector_size - 1; k >= 1; --k)
      {
        u[0] = b[0]*z[0] - b[1]*z[1];
        u[1] = b[0]*z[1] + b[1]*z[0];
        b[0] = k*k*m_gamma[k][0] + u[0];
        b[1] = k*k*m_gamma[k][1] + u[1];
      }
      // b*z = (b[0]*z[0] - b[1]*z[1]) + i(b[1]*z[0] + b[0]*z[1])
      return -2*two_pi<__float128>()*two_pi<__float128>()*(b[0]*z[0] - b[1]*z[1])/(m_T*m_T);
  }

  __float128 period() const
  {
    return m_T;
  }

  __float128 integrate() const
  {
    return m_T*m_gamma[0][0];
  }

  __float128 squared_l2() const
  {
    __float128 s = 0;
    for (size_t i = m_complex_vector_size - 1; i >= 1; --i)
    {
      s += (m_gamma[i][0]*m_gamma[i][0] + m_gamma[i][1]*m_gamma[i][1]);
    }
    s *= 2;
    s += m_gamma[0][0]*m_gamma[0][0];
    return s*m_T;
  }

  ~cardinal_trigonometric_detail()
  {
    if (m_gamma)
    {
      fftwq_free(m_gamma);
      m_gamma = nullptr;
    }
  }


private:
  __float128 m_t0;
  __float128 m_h;
  __float128 m_T;
  fftwq_complex* m_gamma;
  size_t m_complex_vector_size;
};
#endif

}}}}
#endif

/* cardinal_trigonometric_detail.hpp
BaHdaQz67m8lI06LXXpB/X3zMXRNw9B1ApiQmrfp4rUiSV8y3OFyc0DFrI6rXC26U366Z4NJM2s7iptPOeASNuwXi9y0Gp0rX6+aIAEisZSCmMEpX/MYwZ8lZlfwSZfBrR19J2aZR8UUVdwb7foq+1/tkoYx5ODw+V5OZIFyVrGGrVmLE+qP8doSVZRDBm4LuRpcDn90xQOw3AZ0iGswrbGHSGnfXNfL5jLZ2AxqQxvgoyfqOAvvtl98gUHVFEV3aIXcwVqWKVZJoaCmUog58od2FHq8CCVPSQY7SDYTbsdVqi/dqV1IhopUU7ltbDdLAvw9CdV31iBjJRVambIYKqcSIG2ncPTybPgwb+4LjziZZqbdJE+OPH5bwxGvrI3fuYRjg/bTB5FNO+nVsFEdova89aXSrD11KwM5u5MI0O0y6voqi0o3zm8CTUb6RjoQpvvw8vdmcDCwlMt3lsdXwHByW53nBBWJ0p66457Rx46Gfsxw1W8MbvWjp/C2LhdxdNSSiudSE603sud0s3qBPWqRlICSqll6+y5chvlN2fF+SKN5WcKZ1nqpBP6k2FU1ZZQTLM4xixuW2jpd3lIveEoZ4BrI0WhEzgG9ppmmGlRyLrEQnfF8+c+e9N5xIS/ZEx1v03m12nPyttoX5CEiXUWszvCZS1FqdEquMOIcfQMGxD9Ew4TycvFtNCCvKBnq8axQjKtEXG0/F2lfRmKCc1vY+UN429mjllN032O1szeBRX8LtWO3z0Yu7sg6QZ/vpzz4GD65U2l0JRUkfdvg6S/Aoi8huYugp4pPysHRd5ZeXLYKlJS4RK9yDuaU8cYzqk0k5EX2UYw1covWpajq9aOxiqvoT8mrBYXL0C6lmH4dKoYaxXxqqLYxUu0qjj13WJfE5iRutpxadkBcW/eC1oWDowk01KFNdCn+msj7YVgn5GotyrugXYET7dnl8MUGC68tldHtUKjH3aW2LCNjV8Qw8ODRMZ6rJsBZ4Y7qzIz6+vpM3jE/cyM+Rytw8osBpHQotarVVlv2C0pI61qdiGg7W2LzGpbS2An0HiUHlCVcWAlGF/oUaHcTmt2zRiL6BVXHXk1Pjw208hQb0Y/shXJ4NiiM03hF/fQpRp98OvNDEheyyEk6I3NRzwKxS5TWjNvwti1EUzTL7+JU64Gnv8VgPaLVpVdUkwq5KggCn+N4M1uV/MYWeNhHdVdxchKq+bl9OarnVj4EhNlaKwsIq+E898Tq7tQn38/CpGHZvedN1xkdsQsWnV5DnE3dOwNkG3GWdG8Yn+c56oPLufqihpWjezSt6vqO4oCYM9fqJkuqZlWN6E3I2Qs8y46gNZ3QB6F+vqxHD1+cw+UOmaz3oVkpHfpfxhSJjmWOPfCK8aDZwB0jWecc0uK5/mU3iaeoErAoRXQZpKi0DwZXcJH8YpFxT6ScH7I4oIUgx6lcwelLvrkHau7wDpJ+/ZgRPh1WA/ASY5I9UiQ2pRBntOdh7eHiCuz82El80jgYwjdGuMSR+M7qsfZuo5q47ugYWjNrF0oo7Xx2gcPpn0MFL2p+dEYbiAvzFxidHlLnE19jfUp/mev5NgRJoKXzT+Lx55ZaRKapMRjzwCXH9rXAPvEYJ7p9T9IBVG7q8uEy2UGAnXFxvVSI4HzsJUsKNC8jVl3hATFbdNkIUgWnK8v8BiSN3Y4DsfudQ9WvF2Hfhc02UjuZ+luIZk3Lk7P1Q+TOHBs3o3s9cY3ipJfEaMqCugTgHvCYyUi7IBIOAAtKEprYl9k2cpbqW/LYKyURnIyA2+C5b7rVo3OTKPV9pgkDifABNRmTXbJZq80FLrvL5D956ghOAJMI89lMKwqc2+Ffo8qV7XKy4uHcqQkB3XY3mqDd7LudiEINkalNkeNOsJKR5QNDaysmjy8F/kBpEAuLuCeCG4Z+ebJgt7WIWCslvmNS6NHrPy4Bye90oqJbPU21UFYp3IfskJ8mWxjcKaya3YvGD+6FzpKztavXU7kxURehBQdlhW30xEb0h2PnXTjjwA2Ly2V0sKgk1SVnKeaOJS71GiXi3ZOt2a1hgl18+XYKXkbvcjeYNVu8SU6J+Jo8PaQ4Eae3t2DS55cQImxAK18lmgIfh9GTd7ZmvLP8+a6/bLS/PQuFdbKmmTi9HuzOH0YHHk49Ls9b6OSgcSFsSbU6Uy3aRRsHqNIQd9JmYzZ5TkBnFtyORkHPSr5oYLvTxuoE06N4Xc6X62U0vNpXCxjg7I9w7ycbPDyp3YTc5xysUyWAgWlRWG8iODKmrhdbmZoUpsx4NXSlrGuF7QL2R4DsAtSiT66JTs+FRDfwR6aF5QM9WXGHUWqbRGcxaxF1ewGTFEuWugLkV7oj8J/ZzUtJLsGV+MEp84I4oh7We6eR8ORcGYldubBIDTYKYdOp4zrd1iTxsLcXGLuNamABu4ns1z+X0TCBVLRAiOJloQQTtILU+sjUzyaVECNjoKEndtwJEM3JjFSigaVzRtXBnoizUEkamxl1s2ugKUHIVcigZg411yItsGtF5f4ecuwtiOscTMyOBnaVi3obfnA+wxrtCYlZIlr780wXobDdxqQ/tSPs32CCX2CHdI7CjUZmpcB2iBpriD27iBkroSPznhgy2iiHuFFragHeq0vxibYbneajyr/75IVrUvu7kdWFT7I9B4ANQYwt//Ew5+vtsE452Y9rDQiF4vK+wTUqT8P1D2Tp25Sr6UazgetmCYop+JfK01t4o9IbQ5MNOaNKo4kWEWmd3F6z0KYSbTHeeFxXOPErvjY/r7fk4453OS12N32t14M2lmledab0JRUsBQRHFpCVhlaDTvLASPbBnCJBLRhx3tZunSYBkCrRiOTRz2uNpXgOVovjLR+KL3pk++ylUQNEtiNe0XRlw2Dxr0+crGxEbMKhnENy5RhPd+rZV+BaUjnAnZmMeUEqCMLp8/kFbuNNNYhsy1a6+YTL21PGzgE/VGFa566cMVdnm6rqROAuOi+6QDiDcPCrUv1N6MxHbFcYwhLJ+zk5GLtUwnSgKg3lvafrVOFX5lmOh/gvC1o1tDrrAKurJPd0mdprtbC61fdr8pgXbv1rCvFYCsapJ2IPuWjdfvyvz5IH6MAXbnEut+dVcNTwToCT8P6zpaGty/K1xppmy9RBCbNePY+ST9VEXyNAhsnxoawoKnV2f+F2nVzLhn1nNVSPlNlBuwg8QCfAA1EvYOHPVlBfzPMwk/tYXQNlNjqi58IGg5qAuCd4jFy3jnQkb6RSgxdqZV+pq7B9Ap2G5TuvHHwZs90JGhYV7DmfMsM23+vtf1lACHV314rXiQiOzWAs6tVkB45UCd/04xcv+O1uKQjOID3ybPz/EwTk1AwaeQHGScCAiFZ48XbNyUutSKb2+ef2AfALqu9VDR5G+WxGbfTrskaWJ7UfAodkP5yrF12CbZ/hv+ffPdIR25sekaGEVUnryqXWefviLUiIshD4GHV3sv/xBimJ44o7vFaUZJCcXD2nyIYCNjBs46XFiuor9P5Fy+pM/d3lalAmZx8DT8i7J+UmckFjjuXGPzJG2b5ZW2PzQGL2VBzKCVtt5jxLWMy06cWpDonbcVdOt0HUDu3vS3xMkDcA2U6ZTlxq9BN/zDHMhznCibg/UCee6qnOQ2RBRv9XlKLnRH/XgYX+Jnjd05Qe/1OQIKYeL3Py/LwSpi5Xg+ZxP0YN94ssnj3XCq7tBCo2ZzRVhaN1ioJJ1PLQTY7FELwB/uQHzvITgCtcZXva9TQDlALCHBntKkEwSo5al7Ju52E0jJDHU1P0n8+6ljAWBreV8/HK51hc79VnRVNVG/Laz5YTCmJPvsbfohpSvvY1U83Wq8n1Zzm1EXtcsMOFXJaS+iHd++j2t2pACnOi+IbEjQ6UaOV66AuSEl9ED1TTW+VjYkI7w7iiYDNykLZ+SjWgTKryWudXKK+pZNGnAE9gB8UdgDAIgWmqKvfmSTb6VcNBGDu5BUpKZ2dzwWB0a8SdNzY46Mlzlxr8mLwflBN9VBIqf8koTm/K54nurcPz72Uq20zh4V3jwFfJhFhZ+VHzT720l2SB7tk+QOn8MoLySNsj89AqS4qhu2eb3ImGuHrZz8ac1fWbKfkeyJH6tGo8xqWMDhRp+8+iU8ll6pMHu6AXfzFgrm+dn9CXa925vZD/rq98GQ53OVZBk8ObvkuyEs76Y9Kkwpp7gLBig60sldyIzzfWCVa80KlOwjnrswFulIhqgAXZvwc0r+sy1qYB8wtRtnLG/1u4yFxv2EvrMxzqkvkiLIBb55L9R+C3i7ANvhm+Wtn+0kAO2GfAKzUSfTwyQR7MfoYSmsKW7a4DXZPSKWHqQs6ugGPkPF7zVKclcSrRdQwke6KXvoE2lTxNTupSjkwbF4oMo2xPh+XGxtbZ8OTuD9Tvmwi4CCV+o0pQkxXidxdZiWzUKqMlcVEowKPgtEP1oSxYUPEfjHkxokVMcOIbGAoOjdLqqfn6IHiUhL3WI1iaUfjoewNuviY8eJVL80ppd1RVcuCYmUGXi6U107ZdqyM4SkB85lkkv5nQOaoxGfoReOw1vj8QKDpii82LP2mmF/4AAJ+BZ7992DnKIE01wNg0G6zU2ADOCW5L6P2HETxxD9Jgf2qe336CtpYDyUExLCeyUygaHXQXBsy23LuE7Iz/YkpJDmNLmo52ICo6KEWr4Wm3smCTSnGsXbCvewk3OhztYK72k8XZrkyJamlE1j5qQx/oKISL6FT9hrAEaNSa8teU/iSHpcs7OG11Lfnctu29B+HzKdY+2rLJ4wVGvMT0iMbbliV3f6t+JVLVf2lA3z+1mL32zU0IoBWOa8/8s5NG9VWL4+yq5/ES44RBlbi+0Fm/tIlR7zHeTutBZJti1UKtGIv0MGawfFgQqshz65puVxlBauOZxQNvKA9TyVG4L+t+AohlU+xI4btGMza67nll92HImz7xR7aXj4kdhZ4X6fpZn61cadSBHO6yPgV5qKbbytFToTC3JuLTeYZogOuEKJ2AjGsdyK9K4ZG9ClpssadPGEuU2QbBwwZEAbX7PgbML7DzoeNmRkFvQat8fu6mJVhMkp6p1Zwfs4meQxZu5xpH5sldYcWr4YFd55L+NEfp9GVB9aGz082q8xmW89fIOv2QAkgEIqkiNC820OiY08XYGYQ7eMmbYiyrB8faDwVwKcCVhveslJOhDotd9FCNciwfsS3EKdGjf92KK3eosor0qNKTey6DCofCDIcB2ZJHFfxRfUfIdOvXz7K2m8FqYGGJD56uvmgmbA6tNmDIsbk8McIGwrmEzuO8kcJ72+WHc5EcZC3ePna+IqijXbIq1CO1ACovEyERZIM6uafLa05Rr35H1Q0ty39mTunEQy/oJbEa+Xa5MzZO3SjvrYeSgmdzdIbyiLexfEjboHWllGkZXHeCtTvBga4ZytgDeduU5U6GfVPrmTrmMmD9aZycDAf42pus69vBDXjIpqup1tcP4X0ZnCyCZebStyDBybawDULdcRVfO226i76LZm6HY3ASmaBAT3srvIcD6w1FJFPSoe5eEXH3ei+Wj808Vo78b0HHF0zPkZj9aPyP1jfSWdd6mDn69Q7066uS7uKZavW0oulUqi/eKTXBo7WwDGwT786aEFYnW0SPpPsZuHpbs7OqiMaWckfFFhyWpv4+pObJRYzzikB1Cv8CJcmoLjeAdtAvOQxx0bLBs/csv41eSwdfC5PDJOkc5AoA1WndYTv3glKSW7qCkPHAbdPEYRRde5WNnpA9bQv4gi9QdbCiN5JS6K+5so42Sw18CzhV1lNfRAwvVrUln6G0tTfWE4J7V0oBEOyqkgvSnZCDvQwO1+aQhLf4JvSkcYTbiCm9ltnccUrmthq2r6Unw52vuVaHqdj/y9nw5sIrPvSr2mS8EZROxpaxhuBIB29jIlz3N7Be7Xcld+oNCmDZ+ZtZAJfjXvuWxgVQnBUqSLZOZLn21T76o8j52wWvHQggGjlUpfu6Sml4QC8pmWEciSwFLqz2cfW8Se3dWeFIt5Vc+XWxftPhRBY6imzASrlNlx0HAu2mOKJAlwKG5lZ4klne8jBd6uyN0xSn5WqIba2CMja44WUZcaNfjCpJJ5ZIRZ793TGpRsVvmipopowPyMs6bKWzR3QsuL+WSta7Pwn7jxEGDURrNRvIVcYeBEx+Nhk3uUsYooUJMuSmhJKELlQDJ7KLm9uF3FKvSWxsny/KSqb9sBjZpOOUsN7V6JMkvj3KRsrDQ8PsNK4nYd/EKDkgJygqyy3RVq5kt8xEDaPffBnmOrueMgtHU1cK8IXsyyC5eCA0crJItNf2fALgePTO6kmF3nc2gmRxfLB639u+rowCjnti9XaD6nYkmJQOEAcKEwuNkCBvydoE7Ez7RFD7Ajw+LRZrO05sW1UDY1UuyScDDL978stzJtP5TZp+hIxF3R4nQu/BAaM6NeKq/rT5Nh0N3ZR1E0MBI0i+8QsdGZREvG0U6gUl4Njz8MfgSYrsllwyVSJUo8Rzk69vdLncNiPXQ5fJ62vi+VVOR6mxY0LlGYoGLp+2rOLiX5XVlSUvNIoll4YLSBsHNzU99G5Bxuy6Jrlwk1MJMnZq9ylaygHejwRZJa2ZXHdophygsbk6kh+1VnPD6lzmpNKnfctoZS3T8NhmdEYEJa8cCd1hQIsaaspa47/or5BIDba3awSaKjVarHrq7ELorLzm6iWFc0vIHbF5yOEApUTLMlAO1e2w3LqH1nSmSZt7JLcaB7SCQqjTcqyzk2Q5MUDix9IrQUw3yDQ67yHXDCezX11OPpvU8JLfqYZv0ioNGGDMLcTEPL7QaCL0KpHUbqkLk/BQUVZiMUyxbkZxapf62vzMsNiv9Q/9tA5KjIa/oweu1HY2M3o/SMFayKm4MjFX4fgvb/NdvA9koS1grVH+PAM8xWw+cz0xPHLQ6U05BsfDjGoW66d4IIOe6GqlRzS5QDbWfHdCptCjOimlu+S3/dREsvTIxo84chkOu3YTIZExLVHtFjaso8zfzoNFq+iSZegJ1pw5DMNrkdvm4njEKV1ORd60dyjyT+VTMI2uaFOS5ghiiTlt70fFXH5GibgifGgZR9IA+Mgr2RLmyvotfs3Zu/ZS/8ky5sjMhHSF/KR1mKd6Xir7dVrnI5JhRRJvRi+cTqOEDtERFaex+oYKWXrizbet6j9kmZrzjLcV4UTbsk1uswayOQbA1QR33SoGM6CAx9Wd2rb98aGBPUji2ujSb04faMWIm205sb100WCQXoVYgpGVwJJansS3AOmKXh5tzJXoBVVIB+8XnZ25NWHX9Pw14Klyu+yYVN9WqmRiXhubi0QRbK09ugB2IqvpC3NlQ6z1gCODN8M29HeyRFhPnnqvycJa1ddw5icoWHB+0BxTksmxJVaz/v+2UjF9lzI8up0N2OotgxgYWO/+cliGxdjm9X0/D8NuKZhQNv9i6pemdXWyBc2otuwlTRI6AUm9KWUABCz70y0fe8qwzl4Qn3SSsuPB1YbBCHaDcqZorWkloiUdLjFnRizPp/oZ1CoUQQDSL1Oox+GsqLiL1vMrdm3uqI0Rbotc7TLwuqEILHl7A4x+I1idrtJu6bNHaQkKlWqDoUQ5
*/