//  (C) Copyright Nick Thompson 2019.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_INTERPOLATORS_DETAIL_CARDINAL_TRIGONOMETRIC_HPP
#define BOOST_MATH_INTERPOLATORS_DETAIL_CARDINAL_TRIGONOMETRIC_HPP
#include <cmath>
#include <stdexcept>
#include <fftw3.h>
#include <boost/math/constants/constants.hpp>

#ifdef BOOST_HAS_FLOAT128
#include <quadmath.h>
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
6A3su4ft4ppgTmDvv1gTLNss5KW7b9VLz7FeOpZ5IY8tZ/LYbLDCZ+toQh0wWId633rxvt06OvlFve5dveim7ne+taRo8dKxzz23Ze/7hvl77/tv75lX3dL62W3eM69rW/WyKpVKpVKpVCqV6u9V/+v/i4qKK4p29fX/tpOy/j+03nS2xB96GaGsHR00M7BGNMeWYhSID4wN5BXk+HJDcYChpOOsn/2md6Pp7ntf2/uZT0v3K0p8YtaW14NeaK+vuO6pvku7THpu6EXrT2rxSNF4Y9Zyr8VG6g5rUxxpkfx8EDbZ4UAY6VwLo2AqbA4Hw91gGmwF06FT/nDYxmkvbAePhO3hKBgPs2FHeKysLRgNE+EY2NXpI+wOj4c94DiYBCfAnnCitCdTfa1KpVKpVCqVSqVS1Zsawv+XF/wP/D+drO3/F4j/72SEwWdhZ4T8P6UC6wNaBfKOGpmVTnsDee0DeVnp2celZ400NeICj1if3/2tx0Z/8uBdE6PumF/x3YRGv+xYXKDKSJvC2tqKdJ78vL/EBZJgI9gTNoZ9JD7QV+ID/WBL2B/uDgfAVhJHiJU4QpzEEdrCNIkXDJF4wXAYL/GDjjBDfH+B+n6VSqVSqVQqlUqlqnfV//r/iqKi3MKpsv5/V44BSEcJAoTFAJZJDKDACCUGUDZdYgCBUnYNwMWBvAz8tT2uluND5PglOe4lxy/LcW85fl2ODzY1YwVrrfdf9O71fVtu/GHi98fM3K9H0zWv7VisYFqEtD2sT91JRRGhnyuDawkiJGbgglmwCRwlMYNsiRkcI2sKjpUYwWiJEYyBbeBYuCc8TmIDx0tsYBxMgONlTUEu7AK9sqYgT9YU5MMkWAgPhifAXnAy7AOLYD9YDAfAEpgMS2EKLIOD4HQ4BM6Ah8OZcDg8CWbAk+EIeArMhGfCbHgWPBbOgWPg2XAcPAdOgOdBN7wA5sC50AOrYC68AnrhfBhp+EdjISqVSqVSqVQqlaqe1DD+f6qv2AYAdnn/T0dtACC0f/Ry8cXzjFD8f6Zf/L+UItt6+Fn+mjGAuf6aMYAl/poxgGf8NWMAy/x1xwC6dXI8feqYWwffNeW4G4be/uxtu81/InnHYgDfR0j7w/p1KGmV9PVAs3m9gJOVCRvDo2FTiQU0k1hAS4kFxEgsYA+JBbSWWEBbiQXsJbGADhIL6ATdcG84Ee4Lc+B+cBLsBj3wQIkNHAS9sKd4/kPE8/cVz3+oeP6BcApMhT6YBsthOvTDI2AFHAanwiPhifAoOA2OhLPgKHgaPAaeDsfC2fB4eAYcD88M8/4e8f5eeCHMhxfByfBiWAwvhSVwHvTBy+BUiRVMg1fDk+A1sBJeC0+D18HZ8Hp4FrwFng1vhefCRfB8eBucC2+H1G3uhdRt7oeRTj0ae1CpVCqVSqVSqXYpNYj/93mL/x/z/3R0C/P/FUYo/r86+AxAoJT17o/PqOn9X55R0/v/NqOm93fNrOn9Y2bW7f1zrPe/aOP1HU59ZNC8nlc/3M37/LDVO+b9KyOk7WF9OpDk38L8/wjYGI6ETWEmbAaPhi1hFoyBo+AeMBu2hsfAdvBYuBccDTvAMbATHGs2e/99TE3vf4B4/3DPnwcPgfmwNyyAfWEh7C/rAg6VdQGHidcfKF4/Tbz+EPH6Q8XrD5d1ARni+TPF82eJ588Wzz9GPP9x8CyZ958DJ4nHzxOPfwK8BBbV8vpT4FXi+athJLxTvbhKpVKpVCqVSqXaSTWI/y8v8P0//D8dreX/q7ewB0BSmP+nlH3ef1AdewAM38oeAFXW13eP+vbHV5dXzZp5RqNbjjsh65gd8/VVpKRt2AOgJ2wED4aNYV8=
*/