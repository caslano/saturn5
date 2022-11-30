//  (C) Copyright Nick Thompson 2017.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_SPECIAL_CHEBYSHEV_TRANSFORM_HPP
#define BOOST_MATH_SPECIAL_CHEBYSHEV_TRANSFORM_HPP
#include <cmath>
#include <type_traits>
#include <boost/math/constants/constants.hpp>
#include <boost/math/special_functions/chebyshev.hpp>

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

namespace boost { namespace math {

namespace detail{

template <class T>
struct fftw_cos_transform;

template<>
struct fftw_cos_transform<double>
{
   fftw_cos_transform(int n, double* data1, double* data2)
   {
      plan = fftw_plan_r2r_1d(n, data1, data2, FFTW_REDFT10, FFTW_ESTIMATE);
   }
   ~fftw_cos_transform()
   {
      fftw_destroy_plan(plan);
   }
   void execute(double* data1, double* data2)
   {
      fftw_execute_r2r(plan, data1, data2);
   }
   static double cos(double x) { return std::cos(x); }
   static double fabs(double x) { return std::fabs(x); }
private:
   fftw_plan plan;
};

template<>
struct fftw_cos_transform<float>
{
   fftw_cos_transform(int n, float* data1, float* data2)
   {
      plan = fftwf_plan_r2r_1d(n, data1, data2, FFTW_REDFT10, FFTW_ESTIMATE);
   }
   ~fftw_cos_transform()
   {
      fftwf_destroy_plan(plan);
   }
   void execute(float* data1, float* data2)
   {
      fftwf_execute_r2r(plan, data1, data2);
   }
   static float cos(float x) { return std::cos(x); }
   static float fabs(float x) { return std::fabs(x); }
private:
   fftwf_plan plan;
};

template<>
struct fftw_cos_transform<long double>
{
   fftw_cos_transform(int n, long double* data1, long double* data2)
   {
      plan = fftwl_plan_r2r_1d(n, data1, data2, FFTW_REDFT10, FFTW_ESTIMATE);
   }
   ~fftw_cos_transform()
   {
      fftwl_destroy_plan(plan);
   }
   void execute(long double* data1, long double* data2)
   {
      fftwl_execute_r2r(plan, data1, data2);
   }
   static long double cos(long double x) { return std::cos(x); }
   static long double fabs(long double x) { return std::fabs(x); }
private:
   fftwl_plan plan;
};
#ifdef BOOST_HAS_FLOAT128
template<>
struct fftw_cos_transform<__float128>
{
   fftw_cos_transform(int n, __float128* data1, __float128* data2)
   {
      plan = fftwq_plan_r2r_1d(n, data1, data2, FFTW_REDFT10, FFTW_ESTIMATE);
   }
   ~fftw_cos_transform()
   {
      fftwq_destroy_plan(plan);
   }
   void execute(__float128* data1, __float128* data2)
   {
      fftwq_execute_r2r(plan, data1, data2);
   }
   static __float128 cos(__float128 x) { return cosq(x); }
   static __float128 fabs(__float128 x) { return fabsq(x); }
private:
   fftwq_plan plan;
};

#endif
}

template<class Real>
class chebyshev_transform
{
public:
    template<class F>
    chebyshev_transform(const F& f, Real a, Real b,
       Real tol = 500 * std::numeric_limits<Real>::epsilon(),
       size_t max_refinements = 16) : m_a(a), m_b(b)
    {
        if (a >= b)
        {
            throw std::domain_error("a < b is required.\n");
        }
        using boost::math::constants::half;
        using boost::math::constants::pi;
        using std::cos;
        using std::abs;
        Real bma = (b-a)*half<Real>();
        Real bpa = (b+a)*half<Real>();
        size_t n = 256;
        std::vector<Real> vf;

        size_t refinements = 0;
        while(refinements < max_refinements)
        {
            vf.resize(n);
            m_coeffs.resize(n);

            detail::fftw_cos_transform<Real> plan(static_cast<int>(n), vf.data(), m_coeffs.data());
            Real inv_n = 1/static_cast<Real>(n);
            for(size_t j = 0; j < n/2; ++j)
            {
                // Use symmetry cos((j+1/2)pi/n) = - cos((n-1-j+1/2)pi/n)
                Real y = detail::fftw_cos_transform<Real>::cos(pi<Real>()*(j+half<Real>())*inv_n);
                vf[j] = f(y*bma + bpa)*inv_n;
                vf[n-1-j]= f(bpa-y*bma)*inv_n;
            }

            plan.execute(vf.data(), m_coeffs.data());
            Real max_coeff = 0;
            for (auto const & coeff : m_coeffs)
            {
                if (detail::fftw_cos_transform<Real>::fabs(coeff) > max_coeff)
                {
                    max_coeff = detail::fftw_cos_transform<Real>::fabs(coeff);
                }
            }
            size_t j = m_coeffs.size() - 1;
            while (abs(m_coeffs[j])/max_coeff < tol)
            {
                --j;
            }
            // If ten coefficients are eliminated, the we say we've done all
            // we need to do:
            if (n - j > 10)
            {
                m_coeffs.resize(j+1);
                return;
            }

            n *= 2;
            ++refinements;
        }
    }

    inline Real operator()(Real x) const
    {
        return chebyshev_clenshaw_recurrence(m_coeffs.data(), m_coeffs.size(), m_a, m_b, x);
    }

    // Integral over entire domain [a, b]
    Real integrate() const
    {
          Real Q = m_coeffs[0]/2;
          for(size_t j = 2; j < m_coeffs.size(); j += 2)
          {
              Q += -m_coeffs[j]/((j+1)*(j-1));
          }
          return (m_b - m_a)*Q;
    }

    const std::vector<Real>& coefficients() const
    {
        return m_coeffs;
    }

    Real prime(Real x) const
    {
        Real z = (2*x - m_a - m_b)/(m_b - m_a);
        Real dzdx = 2/(m_b - m_a);
        if (m_coeffs.size() < 2)
        {
            return 0;
        }
        Real b2 = 0;
        Real d2 = 0;
        Real b1 = m_coeffs[m_coeffs.size() -1];
        Real d1 = 0;
        for(size_t j = m_coeffs.size() - 2; j >= 1; --j)
        {
            Real tmp1 = 2*z*b1 - b2 + m_coeffs[j];
            Real tmp2 = 2*z*d1 - d2 + 2*b1;
            b2 = b1;
            b1 = tmp1;

            d2 = d1;
            d1 = tmp2;
        }
        return dzdx*(z*d1 - d2 + b1);
    }

private:
    std::vector<Real> m_coeffs;
    Real m_a;
    Real m_b;
};

}}
#endif

/* chebyshev_transform.hpp
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
*/