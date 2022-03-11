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

#include <boost/version.hpp>
#include <boost/throw_exception.hpp>

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
            BOOST_THROW_EXCEPTION(std::ios_base::failure("Infinity"));
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
            BOOST_THROW_EXCEPTION(std::ios_base::failure("NaN"));
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
          if(flags_ && legacy)
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