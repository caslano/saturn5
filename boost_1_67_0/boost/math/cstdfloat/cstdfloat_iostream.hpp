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
  #include <boost/static_assert.hpp>
  #include <boost/throw_exception.hpp>

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

      if(v < 0) { BOOST_THROW_EXCEPTION(std::runtime_error("Formatting of boost::float128_t failed internally in quadmath_snprintf().")); }

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
          BOOST_THROW_EXCEPTION(std::runtime_error("Formatting of boost::float128_t failed while allocating memory."));
        }
#endif
        const int v2 = ::quadmath_snprintf(my_buffer2,
                                            v + 3,
                                            my_format_string,
                                            my_digits,
                                            x);

        if(v2 >= v + 3)
        {
          BOOST_THROW_EXCEPTION(std::runtime_error("Formatting of boost::float128_t failed."));
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

        BOOST_THROW_EXCEPTION(std::runtime_error("Unable to interpret input string as a boost::float128_t"));
      }

      return is;
    }
  }

//  #elif defined(__GNUC__)
  #elif defined(BOOST_INTEL)

  // The section for I/O stream support for the ICC compiler is particularly
  // long, because these functions must be painstakingly synthesized from
  // manually-written routines (ICC does not support I/O stream operations
  // for its _Quad type).

  // The following string-extraction routines are based on the methodology
  // used in Boost.Multiprecision by John Maddock and Christopher Kormanyos.
  // This methodology has been slightly modified here for boost::float128_t.

  #include <cstring>
  #include <cctype>
  #include <boost/lexical_cast.hpp>

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
      string_type e = boost::lexical_cast<string_type>(std::abs(my_exp));

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

    BOOST_CONSTEXPR_OR_CONST int ten = 10;

    int expon       = 0;
    int digits_seen = 0;

    BOOST_CONSTEXPR_OR_CONST int max_digits = std::numeric_limits<float_type>::max_digits10 + 1;

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

        BOOST_THROW_EXCEPTION(std::runtime_error("Unable to interpret input string as a boost::float128_t"));
      }

      return is;
    }
  }

  #endif // Use __GNUC__ or BOOST_INTEL libquadmath

  #endif // Not BOOST_CSTDFLOAT_NO_LIBQUADMATH_SUPPORT (i.e., the user would like to have libquadmath support)

#endif // BOOST_MATH_CSTDFLOAT_IOSTREAM_2014_02_15_HPP_

/* cstdfloat_iostream.hpp
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
*/