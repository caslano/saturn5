// Three-state boolean logic library

// Copyright Douglas Gregor 2002-2004. Use, modification and
// distribution is subject to the Boost Software License, Version
// 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
#ifndef BOOST_LOGIC_TRIBOOL_IO_HPP
#define BOOST_LOGIC_TRIBOOL_IO_HPP

#include <boost/logic/tribool.hpp>
#include <boost/detail/workaround.hpp>
#include <boost/noncopyable.hpp>

#if defined(_MSC_VER)
#  pragma once
#endif

#ifndef BOOST_NO_STD_LOCALE
#  include <locale>
#endif

#include <string>
#include <iostream>

namespace boost { namespace logic {

#ifdef BOOST_NO_STD_LOCALE

/**
 * \brief Returns a string containing the default name for the \c
 * false value of a tribool with the given character type T.
 *
 * This function only exists when the C++ standard library
 * implementation does not support locales.
 */
template<typename T> std::basic_string<T> default_false_name();

/**
 * \brief Returns the character string "false".
 *
 * This function only exists when the C++ standard library
 * implementation does not support locales.
 */
template<>
inline std::basic_string<char> default_false_name<char>()
{ return "false"; }

#  if !defined(BOOST_NO_CWCHAR)
/**
 * \brief Returns the wide character string L"false".
 *
 * This function only exists when the C++ standard library
 * implementation does not support locales.
 */
template<>
inline std::basic_string<wchar_t> default_false_name<wchar_t>()
{ return L"false"; }
#  endif

/**
 * \brief Returns a string containing the default name for the \c true
 * value of a tribool with the given character type T.
 *
 * This function only exists when the C++ standard library
 * implementation does not support locales.
 */
template<typename T> std::basic_string<T> default_true_name();

/**
 * \brief Returns the character string "true".
 *
 * This function only exists when the C++ standard library
 * implementation does not support locales.
 */
template<>
inline std::basic_string<char> default_true_name<char>()
{ return "true"; }

#  if !defined(BOOST_NO_CWCHAR)
/**
 * \brief Returns the wide character string L"true".
 *
 *  This function only exists * when the C++ standard library
 *  implementation does not support * locales.
 */
template<>
inline std::basic_string<wchar_t> default_true_name<wchar_t>()
{ return L"true"; }
#  endif
#endif

/**
 * \brief Returns a string containing the default name for the indeterminate
 * value of a tribool with the given character type T.
 *
 * This routine is used by the input and output streaming operators
 * for tribool when there is no locale support or the stream's locale
 * does not contain the indeterminate_name facet.
 */
template<typename T> std::basic_string<T> get_default_indeterminate_name();

/// Returns the character string "indeterminate".
template<>
inline std::basic_string<char> get_default_indeterminate_name<char>()
{ return "indeterminate"; }

#if !defined(BOOST_NO_CWCHAR)
/// Returns the wide character string L"indeterminate".
template<>
inline std::basic_string<wchar_t> get_default_indeterminate_name<wchar_t>()
{ return L"indeterminate"; }
#endif

// http://www.cantrip.org/locale.html

#ifndef BOOST_NO_STD_LOCALE
/**
 * \brief A locale facet specifying the name of the indeterminate
 * value of a tribool.
 *
 * The facet is used to perform I/O on tribool values when \c
 * std::boolalpha has been specified. This class template is only
 * available if the C++ standard library implementation supports
 * locales.
 */
template<typename CharT>
class indeterminate_name : public std::locale::facet, private boost::noncopyable
{
public:
  typedef CharT char_type;
  typedef std::basic_string<CharT> string_type;

  /// Construct the facet with the default name
  indeterminate_name() : name_(get_default_indeterminate_name<CharT>()) {}

  /// Construct the facet with the given name for the indeterminate value
  explicit indeterminate_name(const string_type& initial_name)
  : name_(initial_name) {}

  /// Returns the name for the indeterminate value
  string_type name() const { return name_; }

  /// Uniquily identifies this facet with the locale.
  static std::locale::id id;

private:
  string_type name_;
};

template<typename CharT> std::locale::id indeterminate_name<CharT>::id;
#endif

/**
 * \brief Writes the value of a tribool to a stream.
 *
 * When the value of @p x is either \c true or \c false, this routine
 * is semantically equivalent to:
 * \code out << static_cast<bool>(x); \endcode
 *
 * When @p x has an indeterminate value, it outputs either the integer
 * value 2 (if <tt>(out.flags() & std::ios_base::boolalpha) == 0</tt>)
 * or the name of the indeterminate value. The name of the
 * indeterminate value comes from the indeterminate_name facet (if it
 * is defined in the output stream's locale), or from the
 * get_default_indeterminate_name function (if it is not defined in the
 * locale or if the C++ standard library implementation does not
 * support locales).
 *
 * \returns @p out
 */
template<typename CharT, typename Traits>
inline std::basic_ostream<CharT, Traits>&
operator<<(std::basic_ostream<CharT, Traits>& out, tribool x)
{
  if (!indeterminate(x)) {
    out << static_cast<bool>(x);
  } else {
    typename std::basic_ostream<CharT, Traits>::sentry cerberus(out);
    if (cerberus) {
      if (out.flags() & std::ios_base::boolalpha) {
#ifndef BOOST_NO_STD_LOCALE
        if (BOOST_HAS_FACET(indeterminate_name<CharT>, out.getloc())) {
          const indeterminate_name<CharT>& facet =
            BOOST_USE_FACET(indeterminate_name<CharT>, out.getloc());
          out << facet.name();
        } else {
          out << get_default_indeterminate_name<CharT>();
        }
#else
        out << get_default_indeterminate_name<CharT>();
#endif
      }
      else
        out << 2;
    }
  }
  return out;
}

/**
 * \brief Writes the indeterminate tribool value to a stream.
 *
 * This routine outputs either the integer
 * value 2 (if <tt>(out.flags() & std::ios_base::boolalpha) == 0</tt>)
 * or the name of the indeterminate value. The name of the
 * indeterminate value comes from the indeterminate_name facet (if it
 * is defined in the output stream's locale), or from the
 * get_default_indeterminate_name function (if it is not defined in the
 * locale or if the C++ standard library implementation does not
 * support locales).
 *
 * \returns @p out
 */
template<typename CharT, typename Traits>
inline std::basic_ostream<CharT, Traits>&
operator<<(std::basic_ostream<CharT, Traits>& out, 
           bool (*)(tribool, detail::indeterminate_t))
{ return out << tribool(indeterminate); } 

/**
 * \brief Reads a tribool value from a stream.
 *
 * When <tt>(out.flags() & std::ios_base::boolalpha) == 0</tt>, this
 * function reads a \c long value from the input stream @p in and
 * converts that value to a tribool. If that value is 0, @p x becomes
 * \c false; if it is 1, @p x becomes \c true; if it is 2, @p becomes
 * \c indetermine; otherwise, the operation fails (and the fail bit is
 * set on the input stream @p in).
 *
 * When <tt>(out.flags() & std::ios_base::boolalpha) != 0</tt>, this
 * function first determines the names of the false, true, and
 * indeterminate values. The false and true names are extracted from
 * the \c std::numpunct facet of the input stream's locale (if the C++
 * standard library implementation supports locales), or from the \c
 * default_false_name and \c default_true_name functions (if there is
 * no locale support). The indeterminate name is extracted from the
 * appropriate \c indeterminate_name facet (if it is available in the
 * input stream's locale), or from the \c get_default_indeterminate_name
 * function (if the C++ standard library implementation does not
 * support locales, or the \c indeterminate_name facet is not
 * specified for this locale object). The input is then matched to
 * each of these names, and the tribool @p x is assigned the value
 * corresponding to the longest name that matched. If no name is
 * matched or all names are empty, the operation fails (and the fail
 * bit is set on the input stream @p in).
 *
 * \returns @p in
 */
template<typename CharT, typename Traits>
inline std::basic_istream<CharT, Traits>&
operator>>(std::basic_istream<CharT, Traits>& in, tribool& x)
{
  if (in.flags() & std::ios_base::boolalpha) {
    typename std::basic_istream<CharT, Traits>::sentry cerberus(in);
    if (cerberus) {
      typedef std::basic_string<CharT> string_type;

#ifndef BOOST_NO_STD_LOCALE
      const std::numpunct<CharT>& numpunct_facet =
        BOOST_USE_FACET(std::numpunct<CharT>, in.getloc());

      string_type falsename = numpunct_facet.falsename();
      string_type truename = numpunct_facet.truename();

      string_type othername;
      if (BOOST_HAS_FACET(indeterminate_name<CharT>, in.getloc())) {
        othername =
          BOOST_USE_FACET(indeterminate_name<CharT>, in.getloc()).name();
      } else {
        othername = get_default_indeterminate_name<CharT>();
      }
#else
      string_type falsename = default_false_name<CharT>();
      string_type truename = default_true_name<CharT>();
      string_type othername = get_default_indeterminate_name<CharT>();
#endif

      typename string_type::size_type pos = 0;
      bool falsename_ok = true, truename_ok = true, othername_ok = true;

      // Modeled after the code from Library DR 17
      while ((falsename_ok && pos < falsename.size())
             || (truename_ok && pos < truename.size())
             || (othername_ok && pos < othername.size())) {
        typename Traits::int_type c = in.get();
        if (c == Traits::eof())
          return in;

        bool matched = false;
        if (falsename_ok && pos < falsename.size()) {
          if (Traits::eq(Traits::to_char_type(c), falsename[pos]))
            matched = true;
          else
            falsename_ok = false;
        }

        if (truename_ok && pos < truename.size()) {
          if (Traits::eq(Traits::to_char_type(c), truename[pos]))
            matched = true;
          else
            truename_ok = false;
        }

        if (othername_ok && pos < othername.size()) {
          if (Traits::eq(Traits::to_char_type(c), othername[pos]))
            matched = true;
          else
            othername_ok = false;
        }

        if (matched) { ++pos; }
        if (pos > falsename.size()) falsename_ok = false;
        if (pos > truename.size())  truename_ok = false;
        if (pos > othername.size()) othername_ok = false;
      }

      if (pos == 0)
        in.setstate(std::ios_base::failbit);
      else {
        if (falsename_ok)      x = false;
        else if (truename_ok)  x = true;
        else if (othername_ok) x = indeterminate;
        else in.setstate(std::ios_base::failbit);
      }
    }
  } else {
    long value;
    if (in >> value) {
      switch (value) {
      case 0: x = false; break;
      case 1: x = true; break;
      case 2: x = indeterminate; break;
      default: in.setstate(std::ios_base::failbit); break;
      }
    }
  }

  return in;
}

} } // end namespace boost::logic

#endif // BOOST_LOGIC_TRIBOOL_IO_HPP

/* tribool_io.hpp
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
*/