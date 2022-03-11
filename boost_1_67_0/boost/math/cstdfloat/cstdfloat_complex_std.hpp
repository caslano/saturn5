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

      explicit complex(const complex<float>&);
      explicit complex(const complex<double>&);
      explicit complex(const complex<long double>&);

      #if defined(BOOST_NO_CXX11_CONSTEXPR)
      complex(const value_type& r = value_type(),
              const value_type& i = value_type()) : re(r),
                                                    im(i) { }

      template<typename X>
      complex(const complex<X>& x) : re(x.real()),
                                     im(x.imag()) { }

      const value_type& real() const { return re; }
      const value_type& imag() const { return im; }

      value_type& real() { return re; }
      value_type& imag() { return im; }
      #else
      BOOST_CONSTEXPR complex(const value_type& r = value_type(),
                              const value_type& i = value_type()) : re(r),
                                                                    im(i) { }

      template<typename X>
      BOOST_CONSTEXPR complex(const complex<X>& x) : re(x.real()),
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
      if ((x.real() > m)
        || (x.real() < -m)
        || (x.imag() > m)
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

      return complex<BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE>(log(std::norm(x)) / 2, atan2(x.imag(), x.real()));
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
      return std::exp(a * std::log(x));
    }

    inline complex<BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE> pow(const complex<BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE>& x,
                                                                    const complex<BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE>& a)
    {
      return std::exp(a * std::log(x));
    }

    inline complex<BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE> pow(const BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE& x,
                                                                    const complex<BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE>& a)
    {
      return std::exp(a * std::log(x));
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