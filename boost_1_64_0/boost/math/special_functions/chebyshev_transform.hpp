//  (C) Copyright Nick Thompson 2017.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_SPECIAL_CHEBYSHEV_TRANSFORM_HPP
#define BOOST_MATH_SPECIAL_CHEBYSHEV_TRANSFORM_HPP
#include <cmath>
#include <type_traits>
#include <fftw3.h>
#include <boost/math/constants/constants.hpp>
#include <boost/math/special_functions/chebyshev.hpp>

#ifdef BOOST_HAS_FLOAT128
#include <quadmath.h>
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
       size_t max_refinements = 15) : m_a(a), m_b(b)
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

    Real operator()(Real x) const
    {
        using boost::math::constants::half;
        if (x > m_b || x < m_a)
        {
            throw std::domain_error("x not in [a, b]\n");
        }

        Real z = (2*x - m_a - m_b)/(m_b - m_a);
        return chebyshev_clenshaw_recurrence(m_coeffs.data(), m_coeffs.size(), z);
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
/e90DSbviPytxB/9/H15j7pc7HiN+mMv7jfD9y61jKMeETrU2cIn9drE05eC4yfc8yQuiGvsyL4LvFeAj/7im/HMi/gleTP8gLwZ/JA3o19FwWnZN6Iv9Aj+e+hHXpFn5nvnj6gjQz+cP6GfteaHdSP8UN+FvjlnxU9WqB90qZdF/vPpR37afkj+BL2S36Yf+sDPyRsTv1/an6c5bltr3YaedS+lNnI84ThgP4GfMl/wfobpF6vFTz9WC17iiXaS8KL/g7z/pG4X/jhvQV8DPY/WtZ92o+Wcyn5KPRbx7fPUDPGdCT/s28DHuThxxL1I7LmE8ZzLZ+/La35EvTT42E8Ql9d5Hb7a51KuRx9I/CH3hY4b6qXBcy14+b6oP/pM16lxrgffGbZTyv7ne8tfM/9hp8nef3i/0RJ7Qpd6LPpzfgM/+o6Www+oUyF+T3ceqZv9akkCbzbceLgnCT+sM9BvtwSeQ7yh3xzHH+cI2KeC7VBOcPhb7vhgviJeOV9A/zck/Scwr2Pn5uQj5C8r4YPzXfGF3Rd4/UR8IN8VnrfIV0PnD6Yzi3HUTXv9O87nzoWcE6l/ieDI/5r6877Q9cnrE/gC6lzAs9Vxe71a9AY/6Ge965+YN2mpY8GfR3heY96k3x5a2Zl1JPQ9j1amfgO+qYeg/8fwx/019UcP3R2v/ZWP4bkm8rNf9neR+xro+Vnvt/pZDwMS+Of/cB0z6xf4wM/QF/rAn32e0ncIcO61eL1wO/0FZ97D3vn0Z9/lPH+e85eNLAd6xC7k0fEf6jeRZ7X68546X/Tbmn7EK/3I93geecD7cerD8eceapEXO6NX4OA/xOvN102feR+8rHvxI+rriLcxghO/nHvjD9RfQPdp56ne8j0Uvtvgnen4Plxw4upK74fxX+LojXS+U/3hswLP3M8RX/C/Wi38POZ9wfT0vX+vszmPhs4c33+kLhR7LRZd9Em9D/SoY0TP85yvamP7tRMcfOW8DnvQ8UBeDbzp86vHwU+dluOc83Lg650v+qP4ol1svnhGX3yPkY9n9DVbfKG/lRqP/J9Bl/ukokO/Ad5XbPX3iDom/P6PjKPe2vuEO+0PzzrOWE/xLL+blyG6/HtJjEvfX7nd8wHzAvrd6HmR+Ya4pD4Y/ZN3wS9bOM6+sh5K1eL/1Ffg/94X9aLOgHHch0R/fbyPop4O/VCfCH+1XAd6Cf2o/wQP97I8X1J3jj6ul3zgLdYz/HckbqS37zUOfjj3JG7Bhz3JI+NXp3q93Tbpv7S95AdvnuXAr5CD9Qd2Z92J3c9kvPqXd9yzngYv9xXgo5nogWeF6wCeMb4vXde/yf7axfvVP6pl/Fc+x2Tdgh2/U4vdwYt/cU8ZftkPIw/7Z/yVfBH9qTfB34e6/pB8G3I+ZvtwXgHfo22/wfYDzgUYv1T9aG9kPHksx2f630usoffwWVvjsdfp9ofd9lfmeeyHXfEf8ifQO1nP4OW8D3+Y7O9+U/pTh+BzOvLj2Hm6z8PvUMt48pr4D/eVsL/XGe1XSB7sTR4Nvn5wPfU2xw1198Abiy56Guy8CXzAD36EntA3404UHDk470Ze7pOgP+qAsOdp6gf/1DWiv1nOQ8/1eol8Mnx3t1+PERz+2B/AP3KBp7rvt/o8q/JgWupvhJdn5gf6kQ+DX+og8PM3hR/9rLf//N353pqmV6gWfvl+4Lc1fU603PPbMD1Dd6T1+Iv3Z409D8Ev/L/l7/QpykPTOt827GDnI/jOolfde8/GDz6yn5N3h68Njlfnq9/Df/Drxpbb/jsyEzrse12/mL5XcXfSTsB+4GG+Q87awkvLuhL9P2T7kFfHv4fQj/sdekafne0=
*/