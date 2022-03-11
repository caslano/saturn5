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