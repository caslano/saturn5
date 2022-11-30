#ifndef BOOST_MATH_NONFINITE_NUM_FACETS_HPP
#define BOOST_MATH_NONFINITE_NUM_FACETS_HPP

// Copyright 2006 Johan Rade
// Copyright 2012 K R Walker
// Copyright 2011, 2012 Paul A. Bristow 

// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

/*
\file

\brief non_finite_num facets for C99 standard output of infinity and NaN.

\details See fuller documentation at Boost.Math Facets
  for Floating-Point Infinities and NaNs.
*/

#include <cstring>
#include <ios>
#include <limits>
#include <locale>
#include <boost/math/tools/throw_exception.hpp>
#include <boost/math/special_functions/fpclassify.hpp>
#include <boost/math/special_functions/sign.hpp>

#ifdef _MSC_VER
#  pragma warning(push)
#  pragma warning(disable : 4127) // conditional expression is constant.
#  pragma warning(disable : 4706) // assignment within conditional expression.
#endif

namespace boost {
  namespace math {

    // flags (enums can be ORed together)       -----------------------------------

    const int legacy = 0x1; //!< get facet will recognize most string representations of infinity and NaN.
    const int signed_zero = 0x2; //!< put facet will distinguish between positive and negative zero.
    const int trap_infinity = 0x4; /*!< put facet will throw an exception of type std::ios_base::failure
       when an attempt is made to format positive or negative infinity.
       get will set the fail bit of the stream when an attempt is made
       to parse a string that represents positive or negative sign infinity.
    */
    const int trap_nan = 0x8; /*!< put facet will throw an exception of type std::ios_base::failure
       when an attempt is made to format positive or negative NaN.
       get will set the fail bit of the stream when an attempt is made
       to parse a string that represents positive or negative sign infinity.
       */

    // class nonfinite_num_put -----------------------------------------------------

    template<
      class CharType,
      class OutputIterator = std::ostreambuf_iterator<CharType>
            >
    class nonfinite_num_put : public std::num_put<CharType, OutputIterator>
    {
    public:
      explicit nonfinite_num_put(int flags = 0) : flags_(flags) {}

    protected:
      virtual OutputIterator do_put(
        OutputIterator it, std::ios_base& iosb, CharType fill, double val) const
      {
        put_and_reset_width(it, iosb, fill, val);
        return it;
      }

      virtual OutputIterator do_put(
        OutputIterator it, std::ios_base& iosb,  CharType fill, long double val) const
      {
        put_and_reset_width(it, iosb, fill, val);
        return it;
      }

    private:
      template<class ValType> void put_and_reset_width(
        OutputIterator& it, std::ios_base& iosb,
        CharType fill, ValType val) const
      {
        put_impl(it, iosb, fill, val);
        iosb.width(0);
      }

      template<class ValType> void put_impl(
        OutputIterator& it, std::ios_base& iosb,
        CharType fill, ValType val) const
      {
        static const CharType prefix_plus[2] = { '+', '\0' };
        static const CharType prefix_minus[2] = { '-', '\0' };
        static const CharType body_inf[4] = { 'i', 'n', 'f', '\0' };
        static const CharType body_nan[4] = { 'n', 'a', 'n', '\0' };
        static const CharType* null_string = 0;

        switch((boost::math::fpclassify)(val))
        {

        case FP_INFINITE:
          if(flags_ & trap_infinity)
          {
            BOOST_MATH_THROW_EXCEPTION(std::ios_base::failure("Infinity"));
          }
          else if((boost::math::signbit)(val))
          { // negative infinity.
            put_num_and_fill(it, iosb, prefix_minus, body_inf, fill, val);
          }
          else if(iosb.flags() & std::ios_base::showpos)
          { // Explicit "+inf" wanted.
            put_num_and_fill(it, iosb, prefix_plus, body_inf, fill, val);
          }
          else
          { // just "inf" wanted.
            put_num_and_fill(it, iosb, null_string, body_inf, fill, val);
          }
          break;

        case FP_NAN:
          if(flags_ & trap_nan)
          {
            BOOST_MATH_THROW_EXCEPTION(std::ios_base::failure("NaN"));
          }
          else if((boost::math::signbit)(val))
          { // negative so "-nan".
            put_num_and_fill(it, iosb, prefix_minus, body_nan, fill, val);
          }
          else if(iosb.flags() & std::ios_base::showpos)
          { // explicit "+nan" wanted.
            put_num_and_fill(it, iosb, prefix_plus, body_nan, fill, val);
          }
          else
          { // Just "nan".
            put_num_and_fill(it, iosb, null_string, body_nan, fill, val);
          }
          break;

        case FP_ZERO:
          if((flags_ & signed_zero) && ((boost::math::signbit)(val)))
          { // Flag set to distinguish between positive and negative zero.
            // But string "0" should have stuff after decimal point if setprecision and/or exp format. 

            std::basic_ostringstream<CharType> zeros; // Needs to be CharType version.

            // Copy flags, fill, width and precision.
            zeros.flags(iosb.flags());
            zeros.unsetf(std::ios::showpos); // Ignore showpos because must be negative.
            zeros.precision(iosb.precision());
            //zeros.width is set by put_num_and_fill
            zeros.fill(static_cast<char>(fill));
            zeros << ValType(0);
            put_num_and_fill(it, iosb, prefix_minus, zeros.str().c_str(), fill, val);
          }
          else
          { // Output the platform default for positive and negative zero.
            put_num_and_fill(it, iosb, null_string, null_string, fill, val);
          }
          break;

        default:  // Normal non-zero finite value.
          it = std::num_put<CharType, OutputIterator>::do_put(it, iosb, fill, val);
          break;
        }
      }

      template<class ValType>
      void put_num_and_fill(
        OutputIterator& it, std::ios_base& iosb, const CharType* prefix,
          const CharType* body, CharType fill, ValType val) const
      {
        int prefix_length = prefix ? (int)std::char_traits<CharType>::length(prefix) : 0;
        int body_length = body ? (int)std::char_traits<CharType>::length(body) : 0;
        int width = prefix_length + body_length;
        std::ios_base::fmtflags adjust = iosb.flags() & std::ios_base::adjustfield;
        const std::ctype<CharType>& ct
          = std::use_facet<std::ctype<CharType> >(iosb.getloc());

        if(body || prefix)
        { // adjust == std::ios_base::right, so leading fill needed.
          if(adjust != std::ios_base::internal && adjust != std::ios_base::left)
            put_fill(it, iosb, fill, width);
        }

        if(prefix)
        { // Adjust width for prefix.
          while(*prefix)
            *it = *(prefix++);
          iosb.width( iosb.width() - prefix_length );
          width -= prefix_length;
        }

        if(body)
        { // 
          if(adjust == std::ios_base::internal)
          { // Put fill between sign and digits.
            put_fill(it, iosb, fill, width);
          }
          if(iosb.flags() & std::ios_base::uppercase)
          {
              while(*body)
                *it = ct.toupper(*(body++));
          }
          else
          {
            while(*body)
              *it = *(body++);
          }

          if(adjust == std::ios_base::left)
            put_fill(it, iosb, fill, width);
        }
        else
        {
          it = std::num_put<CharType, OutputIterator>::do_put(it, iosb, fill, val);
        }
      }

      void put_fill(
        OutputIterator& it, std::ios_base& iosb, CharType fill, int width) const
      { // Insert fill chars.
        for(std::streamsize i = iosb.width() - static_cast<std::streamsize>(width); i > 0; --i)
          *it = fill;
      }

    private:
      const int flags_;
    };


    // class nonfinite_num_get ------------------------------------------------------

    template<
      class CharType,
      class InputIterator = std::istreambuf_iterator<CharType>
    >
    class nonfinite_num_get : public std::num_get<CharType, InputIterator>
    {

    public:
      explicit nonfinite_num_get(int flags = 0) : flags_(flags)
      {}

    protected:  // float, double and long double versions of do_get.
      virtual InputIterator do_get(
        InputIterator it, InputIterator end, std::ios_base& iosb,
        std::ios_base::iostate& state, float& val) const
      {
        get_and_check_eof(it, end, iosb, state, val);
        return it;
      }

      virtual InputIterator do_get(
        InputIterator it, InputIterator end, std::ios_base& iosb,
        std::ios_base::iostate& state, double& val) const
      {
        get_and_check_eof(it, end, iosb, state, val);
        return it;
      }

      virtual InputIterator do_get(
        InputIterator it, InputIterator end, std::ios_base& iosb,
        std::ios_base::iostate& state, long double& val) const
      {
        get_and_check_eof(it, end, iosb, state, val);
        return it;
      }

      //..............................................................................

    private:
      template<class ValType> static ValType positive_nan()
      {
        // On some platforms quiet_NaN() may be negative.
        return (boost::math::copysign)(
          std::numeric_limits<ValType>::quiet_NaN(), static_cast<ValType>(1)
          );
        // static_cast<ValType>(1) added Paul A. Bristow 5 Apr 11
      }

      template<class ValType> void get_and_check_eof
      (
        InputIterator& it, InputIterator end, std::ios_base& iosb,
        std::ios_base::iostate& state, ValType& val
      ) const
      {
        get_signed(it, end, iosb, state, val);
        if(it == end)
          state |= std::ios_base::eofbit;
      }

      template<class ValType> void get_signed
      (
        InputIterator& it, InputIterator end, std::ios_base& iosb,
        std::ios_base::iostate& state, ValType& val
      ) const
      {
        const std::ctype<CharType>& ct
          = std::use_facet<std::ctype<CharType> >(iosb.getloc());

        char c = peek_char(it, end, ct);

        bool negative = (c == '-');

        if(negative || c == '+')
        {
          ++it;
          c = peek_char(it, end, ct);
          if(c == '-' || c == '+')
          { // Without this check, "++5" etc would be accepted.
            state |= std::ios_base::failbit;
            return;
          }
        }

        get_unsigned(it, end, iosb, ct, state, val);

        if(negative)
        {
          val = (boost::math::changesign)(val);
        }
      } // void get_signed

      template<class ValType> void get_unsigned
      ( //! Get an unsigned floating-point value into val,
        //! but checking for letters indicating non-finites.
        InputIterator& it, InputIterator end, std::ios_base& iosb,
        const std::ctype<CharType>& ct,
        std::ios_base::iostate& state, ValType& val
      ) const
      {
        switch(peek_char(it, end, ct))
        {
        case 'i':
          get_i(it, end, ct, state, val);
          break;

        case 'n':
          get_n(it, end, ct, state, val);
          break;

        case 'q':
        case 's':
          get_q(it, end, ct, state, val);
          break;

        default: // Got a normal floating-point value into val.
          it = std::num_get<CharType, InputIterator>::do_get(
            it, end, iosb, state, val);
          if((flags_ & legacy) && val == static_cast<ValType>(1)
            && peek_char(it, end, ct) == '#')
            get_one_hash(it, end, ct, state, val);
          break;
        }
      } //  get_unsigned

      //..........................................................................

      template<class ValType> void get_i
      ( // Get the rest of all strings starting with 'i', expect "inf", "infinity".
        InputIterator& it, InputIterator end, const std::ctype<CharType>& ct,
        std::ios_base::iostate& state, ValType& val
      ) const
      {
        if(!std::numeric_limits<ValType>::has_infinity
          || (flags_ & trap_infinity))
        {
            state |= std::ios_base::failbit;
            return;
        }

        ++it;
        if(!match_string(it, end, ct, "nf"))
        {
          state |= std::ios_base::failbit;
          return;
        }

        if(peek_char(it, end, ct) != 'i')
        {
          val = std::numeric_limits<ValType>::infinity();  // "inf"
          return;
        }

        ++it;
        if(!match_string(it, end, ct, "nity"))
        { // Expected "infinity"
          state |= std::ios_base::failbit;
          return;
        }

        val = std::numeric_limits<ValType>::infinity(); // "infinity"
      } // void get_i

      template<class ValType> void get_n
      ( // Get expected strings after 'n', "nan", "nanq", "nans", "nan(...)"
        InputIterator& it, InputIterator end, const std::ctype<CharType>& ct,
        std::ios_base::iostate& state, ValType& val
      ) const
      {
        if(!std::numeric_limits<ValType>::has_quiet_NaN
          || (flags_ & trap_nan)) {
            state |= std::ios_base::failbit;
            return;
        }

        ++it;
        if(!match_string(it, end, ct, "an"))
        {
          state |= std::ios_base::failbit;
          return;
        }

        switch(peek_char(it, end, ct)) {
        case 'q':
        case 's':
          if(flags_ & legacy)
            ++it;
          break;  // "nanq", "nans"

        case '(':   // Optional payload field in (...) follows.
         {
            ++it;
            char c;
            while((c = peek_char(it, end, ct))
              && c != ')' && c != ' ' && c != '\n' && c != '\t')
              ++it;
            if(c != ')')
            { // Optional payload field terminator missing!
              state |= std::ios_base::failbit;
              return;
            }
            ++it;
            break;  // "nan(...)"
          }

        default:
          break;  // "nan"
        }

        val = positive_nan<ValType>();
      } // void get_n

      template<class ValType> void get_q
      ( // Get expected rest of string starting with 'q': "qnan".
        InputIterator& it, InputIterator end, const std::ctype<CharType>& ct,
        std::ios_base::iostate& state, ValType& val
      ) const
      {
        if(!std::numeric_limits<ValType>::has_quiet_NaN
          || (flags_ & trap_nan) || !(flags_ & legacy))
        {
          state |= std::ios_base::failbit;
          return;
        }

        ++it;
        if(!match_string(it, end, ct, "nan"))
        {
          state |= std::ios_base::failbit;
          return;
        }

        val = positive_nan<ValType>(); // "QNAN"
      } //  void get_q

      template<class ValType> void get_one_hash
      ( // Get expected string after having read "1.#": "1.#IND", "1.#QNAN", "1.#SNAN".
        InputIterator& it, InputIterator end, const std::ctype<CharType>& ct,
        std::ios_base::iostate& state, ValType& val
      ) const
      {

        ++it;
        switch(peek_char(it, end, ct))
        {
        case 'i': // from IND (indeterminate), considered same a QNAN.
          get_one_hash_i(it, end, ct, state, val); // "1.#IND"
          return;

        case 'q': // from QNAN
        case 's': // from SNAN - treated the same as QNAN.
          if(std::numeric_limits<ValType>::has_quiet_NaN
            && !(flags_ & trap_nan))
          {
            ++it;
            if(match_string(it, end, ct, "nan"))
            { // "1.#QNAN", "1.#SNAN"
 //             ++it; // removed as caused assert() cannot increment iterator).
// (match_string consumes string, so not needed?).
// https://svn.boost.org/trac/boost/ticket/5467
// Change in nonfinite_num_facet.hpp Paul A. Bristow 11 Apr 11 makes legacy_test.cpp work OK.
              val = positive_nan<ValType>(); // "1.#QNAN"
              return;
            }
          }
          break;

        default:
          break;
        }

        state |= std::ios_base::failbit;
      } //  void get_one_hash

      template<class ValType> void get_one_hash_i
      ( // Get expected strings after 'i', "1.#INF", 1.#IND".
        InputIterator& it, InputIterator end, const std::ctype<CharType>& ct,
        std::ios_base::iostate& state, ValType& val
      ) const
      {
        ++it;

        if(peek_char(it, end, ct) == 'n')
        {
          ++it;
          switch(peek_char(it, end, ct))
          {
          case 'f':  // "1.#INF"
            if(std::numeric_limits<ValType>::has_infinity
              && !(flags_ & trap_infinity))
            {
                ++it;
                val = std::numeric_limits<ValType>::infinity();
                return;
            }
            break;

          case 'd':   // 1.#IND"
            if(std::numeric_limits<ValType>::has_quiet_NaN
              && !(flags_ & trap_nan))
            {
                ++it;
                val = positive_nan<ValType>();
                return;
            }
            break;

          default:
            break;
          }
        }

        state |= std::ios_base::failbit;
      } //  void get_one_hash_i

      //..........................................................................

      char peek_char
      ( //! \return next char in the input buffer, ensuring lowercase (but do not 'consume' char).
        InputIterator& it, InputIterator end,
        const std::ctype<CharType>& ct
      ) const
      {
        if(it == end) return 0;
        return ct.narrow(ct.tolower(*it), 0); // Always tolower to ensure case insensitive.
      }

      bool match_string
      ( //! Match remaining chars to expected string (case insensitive),
        //! consuming chars that match OK.
        //! \return true if matched expected string, else false.
        InputIterator& it, InputIterator end,
        const std::ctype<CharType>& ct,
        const char* s
      ) const
      {
        while(it != end && *s && *s == ct.narrow(ct.tolower(*it), 0))
        {
          ++s;
          ++it; //
        }
        return !*s;
      } // bool match_string

    private:
      const int flags_;
    }; //

    //------------------------------------------------------------------------------

  }   // namespace math
}   // namespace boost

#ifdef _MSC_VER
#   pragma warning(pop)
#endif

#endif // BOOST_MATH_NONFINITE_NUM_FACETS_HPP


/* nonfinite_num_facets.hpp
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
*/