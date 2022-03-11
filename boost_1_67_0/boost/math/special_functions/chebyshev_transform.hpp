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
uT1hFDYaEH2n3saaW88KxOgMSmXG140GEbYoC8Yj1+dGU0yY0UIZ0cbnWN4n2JQL1gavLa/G3n1YwhLdT1jpzrDKxDOERranksMg2SinUOZdt+UkZnWDi/9cAj5+WiUobdnUqdJAVRmzPsKdnZ/3bPWUazlYWqA3iMRvMGcb/Tm4i4I0zShahm9kTuFU8nDHJPs7BPrhj4gjYreG4Uex6CXxMFY7U4lfKy6Cttdtpw3U96qGkzmuGOuUhg3IMjwhtSnWCQ7nFiu8vq+mtbIV9cmD3umoNykgE+HsCQ0NrcuweP9DvYjdoc2+DZhe+ciP2fbaUp+Nhf5qA520I0p39bRQ2PzDxWWmMHjPA1dlU9l+DVvRlrposgUDo8pFQv8St7PdxdPjYeWkJqtEfbx+H62v2Cyls8to4O3i9zhKB8CSIvKcIhah4ppY0SlSf35mlNHUVU4P7ldLSFyryFFuC9HrilOeKTGXljpBns3sHUPgsMrZVVUpuH9aDoKN8SxJPTEaFy1sFa/jj9L3ooEKRfEXJ8hht9WyFhmshrbZVJLLWWL6cV8U8S1J9K8C4PGeef0riTNxYDtNFa6Ykk2bKKJuGrK5CIMeQlaXgaJP61wmnnotTGCuRlVeMjcvgWSjNl35gmwKRN275m5ZfeESt0OP3/l3icxKa4PTFzqcaQUCt/EjHanRiL0p6P3LLWnnHzOIqHWtIoZmHyiA7kT8yUUQTM7s6AK8nktUwzfWIT0gAAhMxIv5uW4zBzXURk6Bvs3mkERCzFPO1+P6f1XJpotQLu99I+7ON8J2UgpRwsl3e2v73mtZikg50uvg1eRCarMO3WDk271WyqWOEpKHgWsZqGOnOWft05ND2KUcIutd9XozXbVA+X9rBcyK8DFn9iH8Wrq9nmtKCLVSqXntXsDitP9l0o0UJf+MM8W4PSUJX99rKsxop9uZX1J5yNXYk7ow5XEWzObKjitczDy4aHXcuqLddMrMI0nxg41GdMhrYdQ15BvuTr7r9C8lKfhDB1yT/FkxQRoEKCHsc90rmP1nTLtIJVuD9W9yTzmHLoFS8+QeilrGpmZ1hF6CXQEZ/tsqyJUhsrbzMRyB0PTCcCC6JZqE8kX4wELxHLXWPAlDyPAh/xz+7ErTUkEVenhGPoFF6wl0olao8M/lREf8E/AC5+3eEZ1XK57O3pyiehqBisoMdk1llKJp9DK2a3iX+oibt6zLEt4EPrR9/VgxiiHdfXp7mTUbyaP4Iduz/DBdbZLTx0KozghhCDxaLn2h3lvI9I399ys66rD2CSbh3JL0d5EhK0e3kHKL+CHaxOhq0YNcpPsoaqdkULOnf44Q4UN00jwlQ0HRLoVX2nsfco8l4O7bbldDVgiJtMc50XuiaaLw9jvd/c2q2UX10uRF65K8vG3/GCpCW5OhMBPXVj5seIMLQGsRI+6UZ59LNWvYPKalIC+VgoYreV/L59e+6gudVJL+slQIFpY8o28Jeulr48KGS+cIaXEhGoDgVoMpTUyg93M9cKelP806+BUzxPVi0Pq85JtwbbNuXrwYbCX1wbrm9TUQEhP7uP1pVZFXz7WrdX6TQvAu0WRlYj2JhLE0Gpmy17IJ3j3J6qI5MVyMeCyIfksfNuyMFE4PJmobCvtnyPtkw0tOjl/CSzdJ3M7Q+AP4GuZIzeppzN+M5tubzulCbhaHF7peKpKVp8rGhkmAspMFa8dHVyDEHS5k7LMdyOvXSajLQeB0bQPbRcnYiQCGkClBrYcoGdMPWBCYCX6uysf3VCfLQEKIdXXAG37Co7D0uk7oFTNNr54EQXOk1gOmizreVo5Ayjv/Xpzihd1KOtTaczsUp1SMOCoMEimfuHBRPHvDSFH7FJfGEwwNCe5VMJ+yLyyYrL6XJ+/zqsN9NYqW0PJo60fGzJ72/PtDHdiBbHvJaLv8ppXu79DuFD/4D8jbqPmpPDfr0RUzFgG8ZxsRakhzXXstMEKRokUsy/OKi9eH83iVQVu8mdaNP+jY3K3u6qhjyVQo6FjKI1s6/GVWdp2O6/V7LOd3EBeczrzJsRE1O1geTIaau+nvjiqu8HNE6C2lAlrLfcuYKDDBU2ehvfbK7Eu5uGVIYa4iFm9pO3qHmtBETP7aVboBi0xCjwFyHIyj6V411WSZ1gw2Azl9WSRZR5dWgYgAEkQZ9Zy6DLby0OhVgrhI2q+vCLC3WNbuOYSBajRKVlxBo3E4gJ5qWNMyj+tzD3oeX4uYd63VCjB3eNvIP+9u8gkNcwyubqvVtYE2bl5Y6EZp7gSjIdaMV+Gu0Khn6LxFpH9w/RrpznNzjMi/i9BGz3cR5NXzxSFe0AXrYOKOBtS/8jNUfH6+3ZMYlEf99YnDXAdxSvz4H0TXkdLBw477FwqodjVAAq1qWKIrrU+37yhWOF2/Qw6dBZwTUCV2JvCQ0lOQtGAigAgi3mDwdila3tnwvl5D/FvUEtPS8YPChIwL5Tii6oNLaHn/XMqKLqbfa+VhjLsH35IX5/RsXDfWKxU44pDoCwhLl+L9DYYA6YQwQfkC6sxTJvZ+RriYeMTRwosDv7JaaQYH2NZw3rnwYeek8WHJuE+c9doStYE/zTfzoO8GkjAAuLf9xExWo1KQFzfnxxdCnp8S49BU4pOzWaJQQb7cHTwgxbdSrzsJJmXmJ+QSKLmToTF9+5dlJq1ASFCLSnDDG+b5MnuPuy5FKHC6t37Pi87ClSXIQbdubkiDciCxRnzpPcV9bwMgegPmx0IOZ/kuFLAlPCPiDucOdj7Lth8fJB7qvr0qpTrDhU4d44X+huMlmYpDLbpdFMUsZpyzozzHPmvgVHu2iYX4nORQXsdoJCrINBeKCuqA/cLdzMBshjvLFCAhB6wY3kNBXREKJyHmAyQWGhVYtfwIiAU1XSStEMbHr+imXcoAtTKr3Huq40jA/6Q+LRFmMJGnF/21UP0R9EPxnNH8kHJAcSeSFxP4t/PANYzlNlIGQDTmw/S67Uis5F0wYOa6z7k9egBDldnn7Jp8wMSJ77AyMGsvSUOAuJhb1/RcLos4110EH4xsjjR6EMlIYFK5gu7fKPOkhQe3UVj87fTKJNedkFVN//FAU5ftVfWG6YtUcqLJeThskIuXlbCNLMJaB/thlrZQ8T9uC6t0WSNQu3beAQppMLQVN6aBkexy4LeTXsLRuHzgZQopGMrtIzNdM7Zh+2lplc9mLIoDehq7KrXcQi/E675n1YhDz15JNPGdLXgjXgn5HqJIw4M34nmf9wu2u1A35Pm9BzFkKijHY5ikttT9vA+IwBcoK0P/sWFM+RBQghMs3zDEVPbLl79Sbttm/G1h4QLBXW9lC3W4bnGZZF1vG0dPKV6GqMyVnifPwovNq2UVkK6YXi0iTlEJXT9Enzbjt9YynijAF+ilP+Up03AOBe68zKC8GaJp+eTmzDhDo2OZgA1693aNFxZZNJcvHeqbXmiPWrQsn6Mo74p/QwOy+2wfnm3P7zQk/o7i4+QrenhQjPE5TPgTu/moSgSzbIykEnJRuuvmu5lBCXYELSgthee0mjOaTIRdfXQtAlND6MiqNyUcix/D/ftjktnC62QTp75zeFFIfH1HfGq/mAMNUD+T7PVPiU9iigjqH4F+WhzLgEkrCeBfmu4isBabwI2ruCZOnI6XBMXX28wPmuNJXm6ApRrJLJK/vqNPeObzgyKdRpffutieFsNsNNgOSN3ntpyL9zUtkxOa92bqz88AcOP4dQ/X1Vz8Gr0K8ifxqAODfxgLOl7aTqF1RkE2un26OE1itYl4z7S7vWUWzJvjwPJ3rf8u17nKh2cXwCB/oB5Zi1/9M2p77Z1DJ42dg/IU77u1P5zehUd3R4h9J0mqU8fLGF+Agm+E7VhykFXNv15TkJFLx4f0dl80XJP9uFY3hLwlnufPmYnwP3XMEZgqZXxaSnO6acjaG9+N5bnWeiKRYWJqNxS9UTMEcB90o/q3prualPu1tiTSIl0lx8e4JoDJkFbBad2OvUK8BXi9M4zEuJyNOL2rZ1UejXwIkXU03Iws0zZNQyEV5GYQg/e+WWsRJQcn8wizTuWyfGCCOWliTzHlZjQFIjBi6LbXfKTJe3iNQg9erGCUFRltcNkNvCuiEXqZhh8/a75+yIAsq6TX7wESMfq02e9Fo6uJOAibl/xOpkadtndjtpVaj6NILQhqRE7FcXtbPtAQS+DJzazY+igp/JEk2B9oQe9Ad6bAvLktnrjSkEZJWYszvoVQOR5KpMAV6RY7DONY0gJgHt3RUAFNATnnWiQDy3K2X/9Ner6px5ea0sDevOx319xRiwZo+a1H8ekDjlKMTpUQEfXO4+33qFwU9mTUijqKcJUxY9gx9qfjMXEcwvfpUr9/2UIjV866TfzgmaNLLUdfeD9mX7JatWxdwuPfw568k4BS0DM+lPh1ZquzHM+VQ16vBcjSZIjWGuAL6S11DWEF35MVB+SFhx8/OZLNVbfmK7vlEzFWpuSVecfs4HVnKzZQ7ZYtcvrVwTcEcOHE/P7pl4vNwrYexTsLv/5TXlS6jxcokmEnG2bQPyvn+x2EYSi9MkRHt6/ioXVoA9iVKsMaqZyqRmXlLhzciymNbtlZcsu27LOoFIKk1Rga73EWYCaOZKZrhkpKk/zhWq6OTc+h57c1jk/NyG3JgRy9RP5081xDNHLOGTZu5Qz4zWC08snebuiL2dUpcFXz/tW59zwXyL6f3reQCKg32wC/iQWGSc+fl+ekF9jBPT/lLKG6qRF5cYYzEYNXlT5u4JKHbGrNSc2m3bWwecq3BI12Gimp5gaMpSOXNnq9Y3v22yG1H4uYmmnnC51S7GgHL/c1RtEB/ew/xt18VUa1DxN5xRNfBjkB5NvgtieXWzVJ7mdhGER7wYpszt5X+9/4dwFhuqie0v4asZyPsrWdsTfWV5vzQ6qKCptLOi7sSR9H2rSLP3I2CwLFzV3oYDhnFniNMGgex14vzt9vgy8SrCVY5TbG/uTG6wdFXDuI1ZddFNzuYtd/PlPlzkM0hu0fNFvcA8MWRlYW01JNMLIfE3h9WdqguTSPscHi8uFnOa0YN5T8Qpo7hGukQ/czrSozYrsjUBWLkgRz7J7vergBYU/PIpcTr3n9ZHRfdYAt5vV26fYm5HRYbIMxGb3SRhI31OsH7cy9awRsYhfZ6EqDNlSwGeDVAvQraRpXDouqDOISUQ9Q3u2y+C+dojoBdyFeKT5t/GvNpE3xDx5H2A8TLKhdezTcvb5CUPeuKLDPLbieOHRz9eF19Jv1KI4o8jV//Pxh/c2kPHy1wfPLHyyS464uueetgBOcsABItalIbbc52F4JJTpG+MBRGG64TdoREUJADCXj4Yag4Fwp8BP8nKziXl4gNesJ5s5PckoLCqgmLw1V0lO0FBnWSvegO+D2dUIzePl6N3GwfvA3gGhz0Us8jGM1U9NsvvgPeaaCIH1sgfuV2SWXiFzsiC+GMFGGTvnzww3zRSpWddgd+fp7QSDyYx4HZbqBEMQwZr8cYfAb0++m4EgMaItrZcgAEOVnfb0ggzZS2bOFyehggY5O8v2U4cRPVrJfJ5sUJt/xx+4n8CzkHG2b++7E9AfqXGBPN0RJvZ9mU69BU78JILkJD3XPNZpAoygHtukdCrlcOfl60BdHdeGRAf5ma2KBDbIyYAZiyY3T3xBDjH5myXrhEeYENDk8vtBkoxgBWSKezpn+1RN5MtmUsCikTGGTZn+3aTCPbk0n70irgcI7Xx00iFAS3N63OzQadNkZzrHJJSD44TMK8Udgv2O/W4xnnDvRWa50W3Z/GgllVc69wo4HiQ0D3NKGedYwnOiLcNbl5YJQxxKtjSUsPF1xfULyRtHqkfzBJwJmjOKD41z1e0sRnujYGLl7OQlkk/LI+mYgtEdBaA6373akPRLAeCuF4hbhfEqlO2+o4AT03bq8iuB70f/wt/Ek023EnsaJrjEQ/ytownRFhrcEGhpfp6NA96YKzngoJoaYXbxAqAQRH+uyVgmwVA6bhS9ndyM1V9HivzhIMWxYa5DiPLP1NzUyNg/IEXF+ZfHnzTpm1QdrH9m9BE3eBwe30qmHFrFYr64cx/J8UfaqHtvyuibamaExEEFPCW8dii7ZODWlV8+cJF/MSQLV/bkU3ozeT8t7PouXBmkjF/74J8lg4mkBf3KTOcfkwTdRFib0wE8KvxBlCje3wO4fAmWhJEGR8KMsDL6T1RBKqzL8iZhsJLnJoAWc2PEnYwmaLkPWosPD2BRzws8wl8KK4oZ73WhAA9YpP2mk/+RK+4qCMsl8EJM60+WH43F2JbKp7LGGPtl2Y1VZ/82505XZAUokuU6bPkII2HPuU0eA570vpXHssJbEI6gQOIK4iJHrNGlX/uUrIya7DG9tWosf/Lm+6tfzzQZ8P8s/N+KQR2YVmJJDjbzhQTXgjy+9+k5z0i/MPOsChieIvxqlO0uWKXlEdjreEeefrJ4dP8eAWA9Yt6b2lN0cAp1FHT2v2tNPHiGnGV9/x3JIIO49tFSSmUjrrGXfM+e3X46DjrdZ4fOiIPAfSGQwyOkLkt4+PANEHKgIPWKALTzxysIiCStKxT5bRGMzO61TWR1XiU7jZJSFL4fDWzAJMCy5M92rxbj+zaAtDe+tnqgQkmmGX4yRwgGb5BjxI4pmOA5NN3pR5rrb3XiU8qqfzj6RNXbjpI75aGs4O3s5kfvLOpv7VL/CIBO2Ff9d9tBY50mxywS0fgU/9OErwmwxN8i1xoOQg4+gUarm02TBPBteUFSVIP2I5NJCtWQmLvByQOc26c0aPvFIVqm9SCAxPgKjEy2q2xmy3/awIIplmQVI2ih0tk6hM6MF/SzSQNtI5woIfwVf7sP8uvBMyN/uVittWr1hYwE6hX/RDhk40XX6xyeg8z1cp51FGLc5LZU4iAig4LZcPcLLCtlqpJxrC1blh5kJ5dMU2T22sw8D5pf5WtOfrFyOQ3xW0GHXfTwy45zTQNGlZBLl1/W1r8Mf3+AXcqeQ6bsX1MKKwCvG5UbXbJToPhKVuSdiTpFQYA6Ox9CEpvGPkGZ81Jzw9nZOgRMetASE6AOwE3JH9XzWhRcMQS1/R7zbcCXoBHtbEkGFsckbLb0j28l9w23DFRMhzQ0mmD0l4BNUp3tTCijlaEEY81ThE+5DunS9JrZ8l2QeeQs3FK0i8Oqoj5AHUEjbAOaCUklWOQM1123Ed6Uc8s8SLnpBe+ZUJM6/G25fZggb80HpXMfi8+Ojsvqc8Mh9BKlIX15zpcsvB1jPkjCUYU1RcmuVUkWJJREMuTFHe9cen1xhCTKCjOLw4mEgMcbhT98cH0JKlwBnFx/XP76ED1YUKKeBTGlOj0GxmKDiFIjrsr4GcUKIPTWSnYWWvImGB9pNWQ5NDLyYY1S2lIEhJPz2CtAz3MdQhLi972ds09Na7U/lU2OKWGzCO8RGvqJRf5BsxT7dgYbp7UQaY1+qVAdWwtJGwFx/fHNxszm2TMwA62FiR30zN/K5uGmRzaH+BlWx6L8FgS23ZnjiTOEUVAv5TZHQbgJxr64Aa2WaMeEbk9Uqw2VTD9rlvdqzKDxI8npWoztlv3PS7/b96FybIsL7T8O8IOdE1RTU4pepJ2FCS0I06MviTcYVrHF2FtMUoHwSMJKYUfojBCzeDxeUC2hzsKbJOxKAizzb9RpvB97MeJZLLscs7Jl6wVd5GknTW83oBIqYqjOdfFTaDRWl2tj05pYsgCSTppdtLvr9Sd/jZsKOYXIuw2xHkTbZZinndQfvDpn34WeaFFUp9j3F2yEAt/g8KQCYjJ+tSF3oUnwIqetUlupr7tco7HTCY1lWuEFUIN7jVx9UDu6PN729iRo5PJObcysREOQB1NK6TvbYE6SWFzL2vDD4IA6mgUY9/1NNB9f29qWoB73MDqKzFKYXTxYtWOCSV7z3XdPjMz4rRQ35EKM/3Dm5qpHc//1HGKJO1SWHYoMNV4Z8cJ7e6DhEgpmA9wksnUwVvX8O/0pS8e5n7I0OPzjVnWNiSfq9r4gvlc0b23rmubo+On3Jm9P6DyK7B8Rd7b9c3S6bJ7pYYT0iXtZMEjSjMjnFoRrhmDgF3VMpgmrnJaayP3hr8GDEAcXeyuJsmpPNc08xWIvdBrBRfIYFPnS83Qvf8Z4GJ9Xr9GZFGW7URCJ+2LM27Zr1mXtImUyYXBJSVvAxR8gHUtQIGJAtesYEUXQ8HCUQcDY/TgUm+4cMUvDFZz/3JNzrKCieun5lndj6C8pHocn9RxdzWxZYCChHex7eFnbO3aXbxjmIguiutOpWLlsrxHU3NRzYdxgYLW8gux6K34mzT0/25WqoBMM6BETcNjEXNF1EaJdkNihPny3HSWeSiu+7m1qqabqspCyyVKSkXERCIQTV0jI85o6twnboowv90O7UaBi41QuntJwxQwSDSVJQUcX4kEEYB5p/z1nsZKurxHZXP0UwRHrU997b9mJO7GqEJZM29fmrXnKhTkUoDjQet0ehKUonsmNSW0mswa0JQTh/VsrDBEKdTtA5Ukg2fQmt+GdhrYgvg4e6XB8o/gI89C6RPaDa88un3IuJuQquNUTkdTTjQI/VkVToDBvmPel9iV9fPLtvl5++X+4bPe6P7ofpxJvdgPEebArpxGjzyHc3vkg/mggPihxKJsKsrE74klEm6fR1AUQACNiZDwFahFE39Yg5WOd4PeAVCo1PyTmlC4TcgUuP+DuxTL0YxyPl2Wo43Wt/NUJUvw5qTVQe6tHBrV6qgoAk1LDD15239FZdfaVJPrfBo4jGmbn14hZPba4FAlrmOMmqHwyOcsROy5x9WbbkdMTYaICUcBL4ZzPvngYIMa9SVD77AWUZIvingXHXsYVM8kDIlg5MUWt23MuqmFqqYUWIG7suamvrpTxbOF55XQMkKdmoq9SD5cl9PlMVxuXlThrt4UIzuoxolVdciaOYN3UFokacu8GlqN/pnRBgtjgETKxSQ2BKMJFWneaf+mrdCGGt4xYojW+RExhkM3npsdne2bEqmNZpLKLVFgOLR6eRMzLtVU3Jmi7kZilW3P+pXTEdHd+J1TnW7cHYbSFZVFOPjH2sbLX0blyTgNthyl3hy8bACNyYA7BEgVNtBxl0ubYKj0x8GWgRn88W3j1rBqZVTV8=
*/