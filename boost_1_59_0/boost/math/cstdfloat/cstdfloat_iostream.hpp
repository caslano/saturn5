///////////////////////////////////////////////////////////////////////////////
// Copyright Christopher Kormanyos 2014.
// Copyright John Maddock 2014.
// Copyright Paul Bristow 2014.
// Distributed under the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// Implement quadruple-precision I/O stream operations.

#ifndef BOOST_MATH_CSTDFLOAT_IOSTREAM_2014_02_15_HPP_
  #define BOOST_MATH_CSTDFLOAT_IOSTREAM_2014_02_15_HPP_

  #include <boost/math/cstdfloat/cstdfloat_types.hpp>
  #include <boost/math/cstdfloat/cstdfloat_limits.hpp>
  #include <boost/math/cstdfloat/cstdfloat_cmath.hpp>

  #if defined(BOOST_CSTDFLOAT_NO_LIBQUADMATH_CMATH)
  #error You can not use <boost/math/cstdfloat/cstdfloat_iostream.hpp> with BOOST_CSTDFLOAT_NO_LIBQUADMATH_CMATH defined.
  #endif

  #if defined(BOOST_CSTDFLOAT_HAS_INTERNAL_FLOAT128_T) && defined(BOOST_MATH_USE_FLOAT128) && !defined(BOOST_CSTDFLOAT_NO_LIBQUADMATH_SUPPORT)

  #include <cstddef>
  #include <istream>
  #include <ostream>
  #include <sstream>
  #include <stdexcept>
  #include <string>
  #include <boost/math/tools/assert.hpp>
  #include <boost/math/tools/throw_exception.hpp>

//  #if (0)
  #if defined(__GNUC__)

  // Forward declarations of quadruple-precision string functions.
  extern "C" int quadmath_snprintf(char *str, size_t size, const char *format, ...) throw();
  extern "C" boost::math::cstdfloat::detail::float_internal128_t strtoflt128(const char*, char **) throw();

  namespace std
  {
    template<typename char_type, class traits_type>
    inline std::basic_ostream<char_type, traits_type>& operator<<(std::basic_ostream<char_type, traits_type>& os, const boost::math::cstdfloat::detail::float_internal128_t& x)
    {
      std::basic_ostringstream<char_type, traits_type> ostr;
      ostr.flags(os.flags());
      ostr.imbue(os.getloc());
      ostr.precision(os.precision());

      char my_buffer[64U];

      const int my_prec   = static_cast<int>(os.precision());
      const int my_digits = ((my_prec == 0) ? 36 : my_prec);

      const std::ios_base::fmtflags my_flags  = os.flags();

      char my_format_string[8U];

      std::size_t my_format_string_index = 0U;

      my_format_string[my_format_string_index] = '%';
      ++my_format_string_index;

      if(my_flags & std::ios_base::showpos)   { my_format_string[my_format_string_index] = '+'; ++my_format_string_index; }
      if(my_flags & std::ios_base::showpoint) { my_format_string[my_format_string_index] = '#'; ++my_format_string_index; }

      my_format_string[my_format_string_index + 0U] = '.';
      my_format_string[my_format_string_index + 1U] = '*';
      my_format_string[my_format_string_index + 2U] = 'Q';

      my_format_string_index += 3U;

      char the_notation_char;

      if     (my_flags & std::ios_base::scientific) { the_notation_char = 'e'; }
      else if(my_flags & std::ios_base::fixed)      { the_notation_char = 'f'; }
      else                                          { the_notation_char = 'g'; }

      my_format_string[my_format_string_index + 0U] = the_notation_char;
      my_format_string[my_format_string_index + 1U] = 0;

      const int v = ::quadmath_snprintf(my_buffer,
                                        static_cast<int>(sizeof(my_buffer)),
                                        my_format_string,
                                        my_digits,
                                        x);

      if(v < 0) { BOOST_MATH_THROW_EXCEPTION(std::runtime_error("Formatting of boost::float128_t failed internally in quadmath_snprintf().")); }

      if(v >= static_cast<int>(sizeof(my_buffer) - 1U))
      {
        // Evidently there is a really long floating-point string here,
        // such as a small decimal representation in non-scientific notation.
        // So we have to use dynamic memory allocation for the output
        // string buffer.

        char* my_buffer2 = static_cast<char*>(0U);

#ifndef BOOST_NO_EXCEPTIONS
        try
        {
#endif
          my_buffer2 = new char[v + 3];
#ifndef BOOST_NO_EXCEPTIONS
        }
        catch(const std::bad_alloc&)
        {
          BOOST_MATH_THROW_EXCEPTION(std::runtime_error("Formatting of boost::float128_t failed while allocating memory."));
        }
#endif
        const int v2 = ::quadmath_snprintf(my_buffer2,
                                            v + 3,
                                            my_format_string,
                                            my_digits,
                                            x);

        if(v2 >= v + 3)
        {
          BOOST_MATH_THROW_EXCEPTION(std::runtime_error("Formatting of boost::float128_t failed."));
        }

        static_cast<void>(ostr << my_buffer2);

        delete [] my_buffer2;
      }
      else
      {
        static_cast<void>(ostr << my_buffer);
      }

      return (os << ostr.str());
    }

    template<typename char_type, class traits_type>
    inline std::basic_istream<char_type, traits_type>& operator>>(std::basic_istream<char_type, traits_type>& is, boost::math::cstdfloat::detail::float_internal128_t& x)
    {
      std::string str;

      static_cast<void>(is >> str);

      char* p_end;

      x = strtoflt128(str.c_str(), &p_end);

      if(static_cast<std::ptrdiff_t>(p_end - str.c_str()) != static_cast<std::ptrdiff_t>(str.length()))
      {
        for(std::string::const_reverse_iterator it = str.rbegin(); it != str.rend(); ++it)
        {
          static_cast<void>(is.putback(*it));
        }

        is.setstate(ios_base::failbit);

        BOOST_MATH_THROW_EXCEPTION(std::runtime_error("Unable to interpret input string as a boost::float128_t"));
      }

      return is;
    }
  }

//  #elif defined(__GNUC__)
  #elif defined(__INTEL_COMPILER)

  // The section for I/O stream support for the ICC compiler is particularly
  // long, because these functions must be painstakingly synthesized from
  // manually-written routines (ICC does not support I/O stream operations
  // for its _Quad type).

  // The following string-extraction routines are based on the methodology
  // used in Boost.Multiprecision by John Maddock and Christopher Kormanyos.
  // This methodology has been slightly modified here for boost::float128_t.

  #include <cstring>
  #include <cctype>
  
  namespace boost { namespace math { namespace cstdfloat { namespace detail {

  template<class string_type>
  void format_float_string(string_type& str,
                            int my_exp,
                            int digits,
                            const std::ios_base::fmtflags f,
                            const bool iszero)
  {
    typedef typename string_type::size_type size_type;

    const bool scientific = ((f & std::ios_base::scientific) == std::ios_base::scientific);
    const bool fixed      = ((f & std::ios_base::fixed)      == std::ios_base::fixed);
    const bool showpoint  = ((f & std::ios_base::showpoint)  == std::ios_base::showpoint);
    const bool showpos    = ((f & std::ios_base::showpos)    == std::ios_base::showpos);

    const bool b_neg = ((str.size() != 0U) && (str[0] == '-'));

    if(b_neg)
    {
      str.erase(0, 1);
    }

    if(digits == 0)
    {
      digits = static_cast<int>((std::max)(str.size(), size_type(16)));
    }

    if(iszero || str.empty() || (str.find_first_not_of('0') == string_type::npos))
    {
      // We will be printing zero, even though the value might not
      // actually be zero (it just may have been rounded to zero).
      str = "0";

      if(scientific || fixed)
      {
        str.append(1, '.');
        str.append(size_type(digits), '0');

        if(scientific)
        {
          str.append("e+00");
        }
      }
      else
      {
        if(showpoint)
        {
          str.append(1, '.');
          if(digits > 1)
          {
            str.append(size_type(digits - 1), '0');
          }
        }
      }

      if(b_neg)
      {
        str.insert(0U, 1U, '-');
      }
      else if(showpos)
      {
        str.insert(0U, 1U, '+');
      }

      return;
    }

    if(!fixed && !scientific && !showpoint)
    {
      // Suppress trailing zeros.
      typename string_type::iterator pos = str.end();

      while(pos != str.begin() && *--pos == '0') { ; }

      if(pos != str.end())
      {
        ++pos;
      }

      str.erase(pos, str.end());

      if(str.empty())
      {
        str = '0';
      }
    }
    else if(!fixed || (my_exp >= 0))
    {
      // Pad out the end with zero's if we need to.

      int chars = static_cast<int>(str.size());
      chars = digits - chars;

      if(scientific)
      {
        ++chars;
      }

      if(chars > 0)
      {
        str.append(static_cast<size_type>(chars), '0');
      }
    }

    if(fixed || (!scientific && (my_exp >= -4) && (my_exp < digits)))
    {
      if((1 + my_exp) > static_cast<int>(str.size()))
      {
        // Just pad out the end with zeros.
        str.append(static_cast<size_type>((1 + my_exp) - static_cast<int>(str.size())), '0');

        if(showpoint || fixed)
        {
          str.append(".");
        }
      }
      else if(my_exp + 1 < static_cast<int>(str.size()))
      {
        if(my_exp < 0)
        {
          str.insert(0U, static_cast<size_type>(-1 - my_exp), '0');
          str.insert(0U, "0.");
        }
        else
        {
          // Insert the decimal point:
          str.insert(static_cast<size_type>(my_exp + 1), 1, '.');
        }
      }
      else if(showpoint || fixed) // we have exactly the digits we require to left of the point
      {
        str += ".";
      }

      if(fixed)
      {
        // We may need to add trailing zeros.
        int l = static_cast<int>(str.find('.') + 1U);
        l = digits - (static_cast<int>(str.size()) - l);

        if(l > 0)
        {
          str.append(size_type(l), '0');
        }
      }
    }
    else
    {
      // Scientific format:
      if(showpoint || (str.size() > 1))
      {
        str.insert(1U, 1U, '.');
      }

      str.append(1U, 'e');

      string_type e = std::to_string(std::abs(my_exp));

      if(e.size() < 2U)
      {
        e.insert(0U, 2U - e.size(), '0');
      }

      if(my_exp < 0)
      {
        e.insert(0U, 1U, '-');
      }
      else
      {
        e.insert(0U, 1U, '+');
      }

      str.append(e);
    }

    if(b_neg)
    {
      str.insert(0U, 1U, '-');
    }
    else if(showpos)
    {
      str.insert(0U, 1U, '+');
    }
  }

  template<class float_type, class type_a> inline void eval_convert_to(type_a* pa,    const float_type& cb)                        { *pa  = static_cast<type_a>(cb); }
  template<class float_type, class type_a> inline void eval_add       (float_type& b, const type_a& a)                             { b   += a; }
  template<class float_type, class type_a> inline void eval_subtract  (float_type& b, const type_a& a)                             { b   -= a; }
  template<class float_type, class type_a> inline void eval_multiply  (float_type& b, const type_a& a)                             { b   *= a; }
  template<class float_type>               inline void eval_multiply  (float_type& b, const float_type& cb, const float_type& cb2) { b    = (cb * cb2); }
  template<class float_type, class type_a> inline void eval_divide    (float_type& b, const type_a& a)                             { b   /= a; }
  template<class float_type>               inline void eval_log10     (float_type& b, const float_type& cb)                        { b    = std::log10(cb); }
  template<class float_type>               inline void eval_floor     (float_type& b, const float_type& cb)                        { b    = std::floor(cb); }

  inline void round_string_up_at(std::string& s, int pos, int& expon)
  {
    // This subroutine rounds up a string representation of a
    // number at the given position pos.

    if(pos < 0)
    {
      s.insert(0U, 1U, '1');
      s.erase(s.size() - 1U);
      ++expon;
    }
    else if(s[pos] == '9')
    {
      s[pos] = '0';
      round_string_up_at(s, pos - 1, expon);
    }
    else
    {
      if((pos == 0) && (s[pos] == '0') && (s.size() == 1))
      {
        ++expon;
      }

      ++s[pos];
    }
  }

  template<class float_type>
  std::string convert_to_string(float_type& x,
                                std::streamsize digits,
                                const std::ios_base::fmtflags f)
  {
    const bool isneg  = (x < 0);
    const bool iszero = ((!isneg) ? bool(+x < (std::numeric_limits<float_type>::min)())
                                  : bool(-x < (std::numeric_limits<float_type>::min)()));
    const bool isnan  = (x != x);
    const bool isinf  = ((!isneg) ? bool(+x > (std::numeric_limits<float_type>::max)())
                                  : bool(-x > (std::numeric_limits<float_type>::max)()));

    int expon = 0;

    if(digits <= 0) { digits = std::numeric_limits<float_type>::max_digits10; }

    const int org_digits = static_cast<int>(digits);

    std::string result;

    if(iszero)
    {
      result = "0";
    }
    else if(isinf)
    {
      if(x < 0)
      {
        return "-inf";
      }
      else
      {
        return ((f & std::ios_base::showpos) == std::ios_base::showpos) ? "+inf" : "inf";
      }
    }
    else if(isnan)
    {
      return "nan";
    }
    else
    {
      // Start by figuring out the base-10 exponent.
      if(isneg) { x = -x; }

      float_type t;
      float_type ten = 10;

      eval_log10(t, x);
      eval_floor(t, t);
      eval_convert_to(&expon, t);

      if(-expon > std::numeric_limits<float_type>::max_exponent10 - 3)
      {
        int e = -expon / 2;

        const float_type t2 = boost::math::cstdfloat::detail::pown(ten, e);

        eval_multiply(t, t2, x);
        eval_multiply(t, t2);

        if((expon & 1) != 0)
        {
          eval_multiply(t, ten);
        }
      }
      else
      {
        t = boost::math::cstdfloat::detail::pown(ten, -expon);
        eval_multiply(t, x);
      }

      // Make sure that the value lies between [1, 10), and adjust if not.
      if(t < 1)
      {
        eval_multiply(t, 10);

        --expon;
      }
      else if(t >= 10)
      {
        eval_divide(t, 10);

        ++expon;
      }

      float_type digit;
      int        cdigit;

      // Adjust the number of digits required based on formatting options.
      if(((f & std::ios_base::fixed) == std::ios_base::fixed) && (expon != -1))
      {
        digits += (expon + 1);
      }

      if((f & std::ios_base::scientific) == std::ios_base::scientific)
      {
        ++digits;
      }

      // Extract the base-10 digits one at a time.
      for(int i = 0; i < digits; ++i)
      {
        eval_floor(digit, t);
        eval_convert_to(&cdigit, digit);

        result += static_cast<char>('0' + cdigit);

        eval_subtract(t, digit);
        eval_multiply(t, ten);
      }

      // Possibly round the result.
      if(digits >= 0)
      {
        eval_floor(digit, t);
        eval_convert_to(&cdigit, digit);
        eval_subtract(t, digit);

        if((cdigit == 5) && (t == 0))
        {
          // Use simple bankers rounding.

          if((static_cast<int>(*result.rbegin() - '0') & 1) != 0)
          {
            round_string_up_at(result, static_cast<int>(result.size() - 1U), expon);
          }
        }
        else if(cdigit >= 5)
        {
          round_string_up_at(result, static_cast<int>(result.size() - 1), expon);
        }
      }
    }

    while((result.size() > static_cast<std::string::size_type>(digits)) && result.size())
    {
      // We may get here as a result of rounding.

      if(result.size() > 1U)
      {
        result.erase(result.size() - 1U);
      }
      else
      {
        if(expon > 0)
        {
          --expon; // so we put less padding in the result.
        }
        else
        {
          ++expon;
        }

        ++digits;
      }
    }

    if(isneg)
    {
      result.insert(0U, 1U, '-');
    }

    format_float_string(result, expon, org_digits, f, iszero);

    return result;
  }

  template <class float_type>
  bool convert_from_string(float_type& value, const char* p)
  {
    value = 0;

    if((p == static_cast<const char*>(0U)) || (*p == static_cast<char>(0)))
    {
      return;
    }

    bool is_neg       = false;
    bool is_neg_expon = false;

    constexpr int ten = 10;

    int expon       = 0;
    int digits_seen = 0;

    constexpr int max_digits = std::numeric_limits<float_type>::max_digits10 + 1;

    if(*p == static_cast<char>('+'))
    {
      ++p;
    }
    else if(*p == static_cast<char>('-'))
    {
      is_neg = true;
      ++p;
    }

    const bool isnan = ((std::strcmp(p, "nan") == 0) || (std::strcmp(p, "NaN") == 0) || (std::strcmp(p, "NAN") == 0));

    if(isnan)
    {
      eval_divide(value, 0);

      if(is_neg)
      {
        value = -value;
      }

      return true;
    }

    const bool isinf = ((std::strcmp(p, "inf") == 0) || (std::strcmp(p, "Inf") == 0) || (std::strcmp(p, "INF") == 0));

    if(isinf)
    {
      value = 1;
      eval_divide(value, 0);

      if(is_neg)
      {
        value = -value;
      }

      return true;
    }

    // Grab all the leading digits before the decimal point.
    while(std::isdigit(*p))
    {
      eval_multiply(value, ten);
      eval_add(value, static_cast<int>(*p - '0'));
      ++p;
      ++digits_seen;
    }

    if(*p == static_cast<char>('.'))
    {
      // Grab everything after the point, stop when we've seen
      // enough digits, even if there are actually more available.

      ++p;

      while(std::isdigit(*p))
      {
        eval_multiply(value, ten);
        eval_add(value, static_cast<int>(*p - '0'));
        ++p;
        --expon;

        if(++digits_seen > max_digits)
        {
          break;
        }
      }

      while(std::isdigit(*p))
      {
        ++p;
      }
    }

    // Parse the exponent.
    if((*p == static_cast<char>('e')) || (*p == static_cast<char>('E')))
    {
      ++p;

      if(*p == static_cast<char>('+'))
      {
        ++p;
      }
      else if(*p == static_cast<char>('-'))
      {
        is_neg_expon = true;
        ++p;
      }

      int e2 = 0;

      while(std::isdigit(*p))
      {
        e2 *= 10;
        e2 += (*p - '0');
        ++p;
      }

      if(is_neg_expon)
      {
        e2 = -e2;
      }

      expon += e2;
    }

    if(expon)
    {
      // Scale by 10^expon. Note that 10^expon can be outside the range
      // of our number type, even though the result is within range.
      // If that looks likely, then split the calculation in two parts.
      float_type t;
      t = ten;

      if(expon > (std::numeric_limits<float_type>::min_exponent10 + 2))
      {
        t = boost::math::cstdfloat::detail::pown(t, expon);
        eval_multiply(value, t);
      }
      else
      {
        t = boost::math::cstdfloat::detail::pown(t, (expon + digits_seen + 1));
        eval_multiply(value, t);
        t = ten;
        t = boost::math::cstdfloat::detail::pown(t, (-digits_seen - 1));
        eval_multiply(value, t);
      }
    }

    if(is_neg)
    {
      value = -value;
    }

    return (*p == static_cast<char>(0));
  }
  } } } } // boost::math::cstdfloat::detail

  namespace std
  {
    template<typename char_type, class traits_type>
    inline std::basic_ostream<char_type, traits_type>& operator<<(std::basic_ostream<char_type, traits_type>& os, const boost::math::cstdfloat::detail::float_internal128_t& x)
    {
      boost::math::cstdfloat::detail::float_internal128_t non_const_x = x;

      const std::string str = boost::math::cstdfloat::detail::convert_to_string(non_const_x,
                                                                                os.precision(),
                                                                                os.flags());

      std::basic_ostringstream<char_type, traits_type> ostr;
      ostr.flags(os.flags());
      ostr.imbue(os.getloc());
      ostr.precision(os.precision());

      static_cast<void>(ostr << str);

      return (os << ostr.str());
    }

    template<typename char_type, class traits_type>
    inline std::basic_istream<char_type, traits_type>& operator>>(std::basic_istream<char_type, traits_type>& is, boost::math::cstdfloat::detail::float_internal128_t& x)
    {
      std::string str;

      static_cast<void>(is >> str);

      const bool conversion_is_ok = boost::math::cstdfloat::detail::convert_from_string(x, str.c_str());

      if(false == conversion_is_ok)
      {
        for(std::string::const_reverse_iterator it = str.rbegin(); it != str.rend(); ++it)
        {
          static_cast<void>(is.putback(*it));
        }

        is.setstate(ios_base::failbit);

        BOOST_MATH_THROW_EXCEPTION(std::runtime_error("Unable to interpret input string as a boost::float128_t"));
      }

      return is;
    }
  }

  #endif // Use __GNUC__ or __INTEL_COMPILER libquadmath

  #endif // Not BOOST_CSTDFLOAT_NO_LIBQUADMATH_SUPPORT (i.e., the user would like to have libquadmath support)

#endif // BOOST_MATH_CSTDFLOAT_IOSTREAM_2014_02_15_HPP_

/* cstdfloat_iostream.hpp
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
*/