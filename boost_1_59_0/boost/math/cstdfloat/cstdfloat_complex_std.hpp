///////////////////////////////////////////////////////////////////////////////
// Copyright Christopher Kormanyos 2014.
// Copyright John Maddock 2014.
// Copyright Paul Bristow 2014.
// Distributed under the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// Implement a specialization of std::complex<> for *anything* that
// is defined as BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE.

#ifndef BOOST_MATH_CSTDFLOAT_COMPLEX_STD_2014_02_15_HPP_
  #define BOOST_MATH_CSTDFLOAT_COMPLEX_STD_2014_02_15_HPP_

  #if defined(__GNUC__)
  #pragma GCC system_header
  #endif

  #include <complex>
  #include <boost/math/constants/constants.hpp>
  #include <boost/math/tools/cxx03_warn.hpp>

  namespace std
  {
    // Forward declarations.
    template<class float_type>
    class complex;

    template<>
    class complex<BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE>;

    inline BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE real(const complex<BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE>&);
    inline BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE imag(const complex<BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE>&);

    inline BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE abs (const complex<BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE>&);
    inline BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE arg (const complex<BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE>&);
    inline BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE norm(const complex<BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE>&);

    inline complex<BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE> conj (const complex<BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE>&);
    inline complex<BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE> proj (const complex<BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE>&);

    inline complex<BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE> polar(const BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE&,
                                                                      const BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE& = 0);

    inline complex<BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE> sqrt (const complex<BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE>&);

    inline complex<BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE> sin  (const complex<BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE>&);
    inline complex<BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE> cos  (const complex<BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE>&);
    inline complex<BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE> tan  (const complex<BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE>&);
    inline complex<BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE> asin (const complex<BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE>&);
    inline complex<BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE> acos (const complex<BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE>&);
    inline complex<BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE> atan (const complex<BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE>&);

    inline complex<BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE> exp  (const complex<BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE>&);
    inline complex<BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE> log  (const complex<BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE>&);
    inline complex<BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE> log10(const complex<BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE>&);

    inline complex<BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE> pow  (const complex<BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE>&,
                                                                      int);
    inline complex<BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE> pow  (const complex<BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE>&,
                                                                      const BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE&);
    inline complex<BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE> pow  (const complex<BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE>&,
                                                                      const complex<BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE>&);
    inline complex<BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE> pow  (const BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE&,
                                                                      const complex<BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE>&);

    inline complex<BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE> sinh (const complex<BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE>&);
    inline complex<BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE> cosh (const complex<BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE>&);
    inline complex<BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE> tanh (const complex<BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE>&);

    inline complex<BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE> asinh(const complex<BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE>&);
    inline complex<BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE> acosh(const complex<BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE>&);
    inline complex<BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE> atanh(const complex<BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE>&);

    template<class char_type, class traits_type>
    inline std::basic_ostream<char_type, traits_type>& operator<<(std::basic_ostream<char_type, traits_type>&, const std::complex<BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE>&);

    template<class char_type, class traits_type>
    inline std::basic_istream<char_type, traits_type>& operator>>(std::basic_istream<char_type, traits_type>&, std::complex<BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE>&);

    // Template specialization of the complex class.
    template<>
    class complex<BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE>
    {
    public:
      typedef BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE value_type;

      complex(const complex<float>&);
      complex(const complex<double>&);
      complex(const complex<long double>&);

      #if defined(BOOST_NO_CXX11_CONSTEXPR)
      complex(const value_type& r = value_type(),
              const value_type& i = value_type()) : re(r),
                                                    im(i) { }

      template<typename X>
      explicit complex(const complex<X>& x) : re(x.real()),
                                              im(x.imag()) { }

      const value_type& real() const { return re; }
      const value_type& imag() const { return im; }

      value_type& real() { return re; }
      value_type& imag() { return im; }
      #else
      constexpr complex(const value_type& r = value_type(),
                        const value_type& i = value_type()) : re(r),
                                                              im(i) { }

      template<typename X>
      explicit constexpr complex(const complex<X>& x) : re(x.real()),
                                                        im(x.imag()) { }

      value_type real() const { return re; }
      value_type imag() const { return im; }
      #endif

      void real(value_type r) { re = r; }
      void imag(value_type i) { im = i; }

      complex<value_type>& operator=(const value_type& v)
      {
        re = v;
        im = value_type(0);
        return *this;
      }

      complex<value_type>& operator+=(const value_type& v)
      {
        re += v;
        return *this;
      }

      complex<value_type>& operator-=(const value_type& v)
      {
        re -= v;
        return *this;
      }

      complex<value_type>& operator*=(const value_type& v)
      {
        re *= v;
        im *= v;
        return *this;
      }

      complex<value_type>& operator/=(const value_type& v)
      {
        re /= v;
        im /= v;
        return *this;
      }

      template<typename X>
      complex<value_type>& operator=(const complex<X>& x)
      {
        re = x.real();
        im = x.imag();
        return *this;
      }

      template<typename X>
      complex<value_type>& operator+=(const complex<X>& x)
      {
        re += x.real();
        im += x.imag();
        return *this;
      }

      template<typename X>
      complex<value_type>& operator-=(const complex<X>& x)
      {
        re -= x.real();
        im -= x.imag();
        return *this;
      }

      template<typename X>
      complex<value_type>& operator*=(const complex<X>& x)
      {
        const value_type tmp_real = (re * x.real()) - (im * x.imag());
        im = (re * x.imag()) + (im * x.real());
        re = tmp_real;
        return *this;
      }

      template<typename X>
      complex<value_type>& operator/=(const complex<X>& x)
      {
        const value_type tmp_real = (re * x.real()) + (im * x.imag());
        const value_type the_norm = std::norm(x);
        im = ((im * x.real()) - (re * x.imag())) / the_norm;
        re = tmp_real / the_norm;
        return *this;
      }

      private:
        value_type re;
        value_type im;
    };

    // Constructors from built-in complex representation of floating-point types.
    inline complex<BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE>::complex(const complex<float>& f)        : re(BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE( f.real())), im(BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE( f.imag())) { }
    inline complex<BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE>::complex(const complex<double>& d)       : re(BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE( d.real())), im(BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE( d.imag())) { }
    inline complex<BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE>::complex(const complex<long double>& ld) : re(BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE(ld.real())), im(BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE(ld.imag())) { }
  } // namespace std

  namespace boost { namespace math { namespace cstdfloat { namespace detail {
  template<class float_type> inline std::complex<float_type> multiply_by_i(const std::complex<float_type>& x)
  {
    // Multiply x (in C) by I (the imaginary component), and return the result.
    return std::complex<float_type>(-x.imag(), x.real());
  }
  } } } } // boost::math::cstdfloat::detail

  namespace std
  {
    // ISO/IEC 14882:2011, Section 26.4.7, specific values.
    inline BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE real(const complex<BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE>& x) { return x.real(); }
    inline BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE imag(const complex<BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE>& x) { return x.imag(); }

    inline BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE abs (const complex<BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE>& x) { using std::sqrt;  return sqrt ((real(x) * real(x)) + (imag(x) * imag(x))); }
    inline BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE arg (const complex<BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE>& x) { using std::atan2; return atan2(x.imag(), x.real()); }
    inline BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE norm(const complex<BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE>& x) { return (real(x) * real(x)) + (imag(x) * imag(x)); }

    inline complex<BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE> conj (const complex<BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE>& x) { return complex<BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE>(x.real(), -x.imag()); }

    inline complex<BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE> proj (const complex<BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE>& x)
    {
      const BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE m = (std::numeric_limits<BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE>::max)();
      if (   (x.real() >  m)
          || (x.real() < -m)
          || (x.imag() >  m)
          || (x.imag() < -m))
      {
        // We have an infinity, return a normalized infinity, respecting the sign of the imaginary part:
         return complex<BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE>(std::numeric_limits<BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE>::infinity(), x.imag() < 0 ? -0 : 0);
      }
      return x;
    }

    inline complex<BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE> polar(const BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE& rho,
                                                                      const BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE& theta)
    {
      using std::sin;
      using std::cos;

      return complex<BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE>(rho * cos(theta), rho * sin(theta));
    }

    // Global add, sub, mul, div.
    inline complex<BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE> operator+(const complex<BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE>& u, const complex<BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE>& v) { return complex<BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE>(u.real() + v.real(), u.imag() + v.imag()); }
    inline complex<BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE> operator-(const complex<BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE>& u, const complex<BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE>& v) { return complex<BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE>(u.real() - v.real(), u.imag() - v.imag()); }

    inline complex<BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE> operator*(const complex<BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE>& u, const complex<BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE>& v)
    {
      return complex<BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE>((u.real() * v.real()) - (u.imag() * v.imag()),
                                                                  (u.real() * v.imag()) + (u.imag() * v.real()));
    }

    inline complex<BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE> operator/(const complex<BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE>& u, const complex<BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE>& v)
    {
      const BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE the_norm = std::norm(v);

      return complex<BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE>(((u.real() * v.real()) + (u.imag() * v.imag())) / the_norm,
                                                                  ((u.imag() * v.real()) - (u.real() * v.imag())) / the_norm);
    }

    inline complex<BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE> operator+(const complex<BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE>& u, const BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE& v) { return complex<BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE>(u.real() + v, u.imag()); }
    inline complex<BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE> operator-(const complex<BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE>& u, const BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE& v) { return complex<BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE>(u.real() - v, u.imag()); }
    inline complex<BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE> operator*(const complex<BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE>& u, const BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE& v) { return complex<BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE>(u.real() * v, u.imag() * v); }
    inline complex<BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE> operator/(const complex<BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE>& u, const BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE& v) { return complex<BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE>(u.real() / v, u.imag() / v); }

    inline complex<BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE> operator+(const BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE& u, const complex<BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE>& v) { return complex<BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE>(u + v.real(),     v.imag()); }
    inline complex<BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE> operator-(const BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE& u, const complex<BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE>& v) { return complex<BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE>(u - v.real(),    -v.imag()); }
    inline complex<BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE> operator*(const BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE& u, const complex<BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE>& v) { return complex<BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE>(u * v.real(), u * v.imag()); }
    inline complex<BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE> operator/(const BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE& u, const complex<BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE>& v) { const BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE v_norm = norm(v); return complex<BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE>((u * v.real()) / v_norm, (-u * v.imag()) / v_norm); }

    // Unary plus / minus.
    inline complex<BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE> operator+(const complex<BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE>& u) { return u; }
    inline complex<BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE> operator-(const complex<BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE>& u) { return complex<BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE>(-u.real(), -u.imag()); }

    // Equality and inequality.
    inline bool operator==(const complex<BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE>& x, const complex<BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE>& y) { return ((x.real() == y.real()) && (x.imag() == y.imag())); }
    inline bool operator==(const complex<BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE>& x, const         BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE&  y) { return ((x.real() == y)        && (x.imag() == BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE(0))); }
    inline bool operator==(const         BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE&  x, const complex<BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE>& y) { return ((x        == y.real()) && (y.imag() == BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE(0))); }
    inline bool operator!=(const complex<BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE>& x, const complex<BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE>& y) { return ((x.real() != y.real()) || (x.imag() != y.imag())); }
    inline bool operator!=(const complex<BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE>& x, const         BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE&  y) { return ((x.real() != y)        || (x.imag() != BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE(0))); }
    inline bool operator!=(const         BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE&  x, const complex<BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE>& y) { return ((x        != y.real()) || (y.imag() != BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE(0))); }

    // ISO/IEC 14882:2011, Section 26.4.8, transcendentals.
    inline complex<BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE> sqrt(const complex<BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE>& x)
    {
      using std::fabs;
      using std::sqrt;

      // Compute sqrt(x) for x in C:
      // sqrt(x) = (s       , xi / 2s) : for xr > 0,
      //           (|xi| / 2s, +-s)    : for xr < 0,
      //           (sqrt(xi), sqrt(xi) : for xr = 0,
      // where s = sqrt{ [ |xr| + sqrt(xr^2 + xi^2) ] / 2 },
      // and the +- sign is the same as the sign of xi.

      if(x.real() > 0)
      {
        const BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE s = sqrt((fabs(x.real()) + std::abs(x)) / 2);

        return complex<BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE>(s, x.imag() / (s * 2));
      }
      else if(x.real() < 0)
      {
        const BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE s = sqrt((fabs(x.real()) + std::abs(x)) / 2);

        const bool imag_is_neg = (x.imag() < 0);

        return complex<BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE>(fabs(x.imag()) / (s * 2), (imag_is_neg ? -s : s));
      }
      else
      {
        const BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE sqrt_xi_half = sqrt(x.imag() / 2);

        return complex<BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE>(sqrt_xi_half, sqrt_xi_half);
      }
    }

    inline complex<BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE> sin(const complex<BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE>& x)
    {
      using std::sin;
      using std::cos;
      using std::exp;

      const BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE sin_x  = sin (x.real());
      const BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE cos_x  = cos (x.real());
      const BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE exp_yp = exp (x.imag());
      const BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE exp_ym = BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE(1) / exp_yp;
      const BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE sinh_y = (exp_yp - exp_ym) / 2;
      const BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE cosh_y = (exp_yp + exp_ym) / 2;

      return complex<BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE>(sin_x * cosh_y, cos_x * sinh_y);
    }

    inline complex<BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE> cos(const complex<BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE>& x)
    {
      using std::sin;
      using std::cos;
      using std::exp;

      const BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE sin_x  = sin (x.real());
      const BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE cos_x  = cos (x.real());
      const BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE exp_yp = exp (x.imag());
      const BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE exp_ym = BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE(1) / exp_yp;
      const BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE sinh_y = (exp_yp - exp_ym) / 2;
      const BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE cosh_y = (exp_yp + exp_ym) / 2;

      return complex<BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE>(cos_x * cosh_y, -(sin_x * sinh_y));
    }

    inline complex<BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE> tan(const complex<BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE>& x)
    {
      using std::sin;
      using std::cos;
      using std::exp;

      const BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE sin_x  = sin (x.real());
      const BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE cos_x  = cos (x.real());
      const BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE exp_yp = exp (x.imag());
      const BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE exp_ym = BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE(1) / exp_yp;
      const BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE sinh_y = (exp_yp - exp_ym) / 2;
      const BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE cosh_y = (exp_yp + exp_ym) / 2;

      return (  complex<BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE>(sin_x * cosh_y,  cos_x * sinh_y)
              / complex<BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE>(cos_x * cosh_y, -sin_x * sinh_y));
    }

    inline complex<BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE> asin(const complex<BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE>& x)
    {
      return -boost::math::cstdfloat::detail::multiply_by_i(std::log(boost::math::cstdfloat::detail::multiply_by_i(x) + std::sqrt(BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE(1) - (x * x))));
    }

    inline complex<BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE> acos(const complex<BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE>& x)
    {
      return boost::math::constants::half_pi<BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE>() - std::asin(x);
    }

    inline complex<BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE> atan(const complex<BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE>& x)
    {
      const complex<BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE> izz = boost::math::cstdfloat::detail::multiply_by_i(x);

      return boost::math::cstdfloat::detail::multiply_by_i(std::log(BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE(1) - izz) - std::log(BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE(1) + izz)) / 2;
    }

    inline complex<BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE> exp(const complex<BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE>& x)
    {
      using std::exp;

      return std::polar(exp(x.real()), x.imag());
    }

    inline complex<BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE> log(const complex<BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE>& x)
    {
      using std::atan2;
      using std::log;

      const bool re_isneg  = (x.real() < 0);
      const bool re_isnan  = (x.real() != x.real());
      const bool re_isinf  = ((!re_isneg) ? bool(+x.real() > (std::numeric_limits<BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE>::max)())
                                          : bool(-x.real() > (std::numeric_limits<BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE>::max)()));

      const bool im_isneg  = (x.imag() < 0);
      const bool im_isnan  = (x.imag() != x.imag());
      const bool im_isinf  = ((!im_isneg) ? bool(+x.imag() > (std::numeric_limits<BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE>::max)())
                                          : bool(-x.imag() > (std::numeric_limits<BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE>::max)()));

      if(re_isnan || im_isnan) { return x; }

      if(re_isinf || im_isinf)
      {
        return complex<BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE>(std::numeric_limits<BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE>::infinity(),
                                                                    BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE(0.0));
      }

      const bool re_iszero = ((re_isneg || (x.real() > 0)) == false);

      if(re_iszero)
      {
        const bool im_iszero = ((im_isneg || (x.imag() > 0)) == false);

        if(im_iszero)
        {
          return std::complex<BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE>
                 (
                   -std::numeric_limits<BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE>::infinity(),
                   BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE(0.0)
                 );
        }
        else
        {
          if(im_isneg == false)
          {
            return std::complex<BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE>
                   (
                     log(x.imag()),
                     boost::math::constants::half_pi<BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE>()
                   );
          }
          else
          {
            return std::complex<BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE>
                   (
                     log(-x.imag()),
                     -boost::math::constants::half_pi<BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE>()
                   );
          }
        }
      }
      else
      {
        return complex<BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE>(log(std::norm(x)) / 2, atan2(x.imag(), x.real()));
      }
    }

    inline complex<BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE> log10(const complex<BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE>& x)
    {
      return std::log(x) / boost::math::constants::ln_ten<BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE>();
    }

    inline complex<BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE> pow(const complex<BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE>& x,
                                                                    int p)
    {
      const bool re_isneg  = (x.real() < 0);
      const bool re_isnan  = (x.real() != x.real());
      const bool re_isinf  = ((!re_isneg) ? bool(+x.real() > (std::numeric_limits<BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE>::max)())
                                          : bool(-x.real() > (std::numeric_limits<BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE>::max)()));

      const bool im_isneg  = (x.imag() < 0);
      const bool im_isnan  = (x.imag() != x.imag());
      const bool im_isinf  = ((!im_isneg) ? bool(+x.imag() > (std::numeric_limits<BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE>::max)())
                                          : bool(-x.imag() > (std::numeric_limits<BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE>::max)()));

      if(re_isnan || im_isnan) { return x; }

      if(re_isinf || im_isinf)
      {
        return complex<BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE>(std::numeric_limits<BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE>::quiet_NaN(),
                                                                    std::numeric_limits<BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE>::quiet_NaN());
      }

      if(p < 0)
      {
        if(std::abs(x) < (std::numeric_limits<BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE>::min)())
        {
          return complex<BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE>(std::numeric_limits<BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE>::infinity(),
                                                                      std::numeric_limits<BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE>::infinity());
        }
        else
        {
          return BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE(1) / std::pow(x, -p);
        }
      }

      if(p == 0)
      {
        return complex<BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE>(BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE(1));
      }
      else
      {
        if(p == 1) { return x; }

        if(std::abs(x) > (std::numeric_limits<BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE>::max)())
        {
          const BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE re = (re_isneg ? -std::numeric_limits<BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE>::infinity()
                                                                           : +std::numeric_limits<BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE>::infinity());

          const BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE im = (im_isneg ? -std::numeric_limits<BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE>::infinity()
                                                                           : +std::numeric_limits<BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE>::infinity());

          return complex<BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE>(re, im);
        }

        if     (p == 2) { return  (x * x); }
        else if(p == 3) { return ((x * x) * x); }
        else if(p == 4) { const complex<BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE> x2 = (x * x); return (x2 * x2); }
        else
        {
          // The variable xn stores the binary powers of x.
          complex<BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE> result(((p % 2) != 0) ? x : complex<BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE>(BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE(1)));
          complex<BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE> xn    (x);

          int p2 = p;

          while((p2 /= 2) != 0)
          {
            // Square xn for each binary power.
            xn *= xn;

            const bool has_binary_power = ((p2 % 2) != 0);

            if(has_binary_power)
            {
              // Multiply the result with each binary power contained in the exponent.
              result *= xn;
            }
          }

          return result;
        }
      }
    }

    inline complex<BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE> pow(const complex<BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE>& x,
                                                                    const BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE& a)
    {
      const bool x_im_isneg  = (x.imag() < 0);
      const bool x_im_iszero = ((x_im_isneg || (x.imag() > 0)) == false);

      if(x_im_iszero)
      {
        using std::pow;

        const BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE pxa = pow(x.real(), a);

        return complex<BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE>(pxa, BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE(0));
      }
      else
      {
        return std::exp(a * std::log(x));
      }
    }

    inline complex<BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE> pow(const complex<BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE>& x,
                                                                    const complex<BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE>& a)
    {
      const bool x_im_isneg  = (x.imag() < 0);
      const bool x_im_iszero = ((x_im_isneg || (x.imag() > 0)) == false);

      if(x_im_iszero)
      {
        using std::pow;

        return pow(x.real(), a);
      }
      else
      {
        return std::exp(a * std::log(x));
      }
    }

    inline complex<BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE> pow(const BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE& x,
                                                                    const complex<BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE>& a)
    {
      const bool x_isneg = (x < 0);
      const bool x_isnan = (x != x);
      const bool x_isinf = ((!x_isneg) ? bool(+x > (std::numeric_limits<BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE>::max)())
                                       : bool(-x > (std::numeric_limits<BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE>::max)()));

      const bool a_re_isneg = (a.real() < 0);
      const bool a_re_isnan = (a.real() != a.real());
      const bool a_re_isinf = ((!a_re_isneg) ? bool(+a.real() > (std::numeric_limits<BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE>::max)())
                                             : bool(-a.real() > (std::numeric_limits<BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE>::max)()));

      const bool a_im_isneg = (a.imag() < 0);
      const bool a_im_isnan = (a.imag() != a.imag());
      const bool a_im_isinf = ((!a_im_isneg) ? bool(+a.imag() > (std::numeric_limits<BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE>::max)())
                                             : bool(-a.imag() > (std::numeric_limits<BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE>::max)()));

      const bool args_is_nan = (x_isnan || a_re_isnan || a_im_isnan);
      const bool a_is_finite = (!(a_re_isnan || a_re_isinf || a_im_isnan || a_im_isinf));

      complex<BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE> result;

      if(args_is_nan)
      {
        result =
          complex<BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE>
          (
            std::numeric_limits<BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE>::quiet_NaN(),
            std::numeric_limits<BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE>::quiet_NaN()
          );
      }
      else if(x_isinf)
      {
        if(a_is_finite)
        {
          result =
            complex<BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE>
            (
              std::numeric_limits<BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE>::infinity(),
              std::numeric_limits<BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE>::infinity()
            );
        }
        else
        {
          result =
            complex<BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE>
            (
              std::numeric_limits<BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE>::quiet_NaN(),
              std::numeric_limits<BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE>::quiet_NaN()
            );
        }
      }
      else if(x > 0)
      {
        result = std::exp(a * std::log(x));
      }
      else if(x < 0)
      {
        using std::acos;
        using std::log;

        const complex<BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE>
          cpx_lg_x
          (
            log(-x),
            acos(BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE(-1))
          );

        result = std::exp(a * cpx_lg_x);
      }
      else
      {
        if(a_is_finite)
        {
          result =
            complex<BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE>
            (
              BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE(0),
              BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE(0)
            );
        }
        else
        {
          result =
            complex<BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE>
            (
              std::numeric_limits<BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE>::quiet_NaN(),
              std::numeric_limits<BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE>::quiet_NaN()
            );
        }
      }

      return result;
    }

    inline complex<BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE> sinh(const complex<BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE>& x)
    {
      using std::sin;
      using std::cos;
      using std::exp;

      const BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE sin_y  = sin (x.imag());
      const BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE cos_y  = cos (x.imag());
      const BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE exp_xp = exp (x.real());
      const BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE exp_xm = BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE(1) / exp_xp;
      const BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE sinh_x = (exp_xp - exp_xm) / 2;
      const BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE cosh_x = (exp_xp + exp_xm) / 2;

      return complex<BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE>(cos_y * sinh_x, cosh_x * sin_y);
    }

    inline complex<BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE> cosh(const complex<BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE>& x)
    {
      using std::sin;
      using std::cos;
      using std::exp;

      const BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE sin_y  = sin (x.imag());
      const BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE cos_y  = cos (x.imag());
      const BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE exp_xp = exp (x.real());
      const BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE exp_xm = BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE(1) / exp_xp;
      const BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE sinh_x = (exp_xp - exp_xm) / 2;
      const BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE cosh_x = (exp_xp + exp_xm) / 2;

      return complex<BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE>(cos_y * cosh_x, sin_y * sinh_x);
    }

    inline complex<BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE> tanh(const complex<BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE>& x)
    {
      const complex<BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE> ex_plus  = std::exp(x);
      const complex<BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE> ex_minus = BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE(1) / ex_plus;

      return (ex_plus - ex_minus) / (ex_plus + ex_minus);
    }

    inline complex<BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE> asinh(const complex<BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE>& x)
    {
      return std::log(x + std::sqrt((x * x) + BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE(1)));
    }

    inline complex<BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE> acosh(const complex<BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE>& x)
    {
      const BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE my_one(1);

      const complex<BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE> zp(x.real() + my_one, x.imag());
      const complex<BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE> zm(x.real() - my_one, x.imag());

      return std::log(x + (zp * std::sqrt(zm / zp)));
    }

    inline complex<BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE> atanh(const complex<BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE>& x)
    {
      return (std::log(BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE(1) + x) - std::log(BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE(1) - x)) / 2.0;
    }

    template<class char_type, class traits_type>
    inline std::basic_ostream<char_type, traits_type>& operator<<(std::basic_ostream<char_type, traits_type>& os, const std::complex<BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE>& x)
    {
      std::basic_ostringstream<char_type, traits_type> ostr;

      ostr.flags(os.flags());
      ostr.imbue(os.getloc());
      ostr.precision(os.precision());

      ostr << char_type('(')
           << x.real()
           << char_type(',')
           << x.imag()
           << char_type(')');

      return (os << ostr.str());
    }

    template<class char_type, class traits_type>
    inline std::basic_istream<char_type, traits_type>& operator>>(std::basic_istream<char_type, traits_type>& is, std::complex<BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE>& x)
    {
      BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE rx;
      BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE ix;

      char_type the_char;

      static_cast<void>(is >> the_char);

      if(the_char == static_cast<char_type>('('))
      {
        static_cast<void>(is >> rx >> the_char);

        if(the_char == static_cast<char_type>(','))
        {
          static_cast<void>(is >> ix >> the_char);

          if(the_char == static_cast<char_type>(')'))
          {
            x = complex<BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE>(rx, ix);
          }
          else
          {
            is.setstate(ios_base::failbit);
          }
        }
        else if(the_char == static_cast<char_type>(')'))
        {
          x = rx;
        }
        else
        {
          is.setstate(ios_base::failbit);
        }
      }
      else
      {
        static_cast<void>(is.putback(the_char));

        static_cast<void>(is >> rx);

        x = rx;
      }

      return is;
    }
  } // namespace std

#endif // BOOST_MATH_CSTDFLOAT_COMPLEX_STD_2014_02_15_HPP_

/* cstdfloat_complex_std.hpp
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
*/