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
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
*/