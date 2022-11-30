// Three-state boolean logic library

// Copyright Douglas Gregor 2002-2004. Use, modification and
// distribution is subject to the Boost Software License, Version
// 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// For more information, see http://www.boost.org
#ifndef BOOST_LOGIC_TRIBOOL_HPP
#define BOOST_LOGIC_TRIBOOL_HPP

#include <boost/logic/tribool_fwd.hpp>
#include <boost/config.hpp>
#include <boost/detail/workaround.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#  pragma once
#endif

namespace boost { namespace logic {

/// INTERNAL ONLY
namespace detail {
/**
 * INTERNAL ONLY
 *
 * \brief A type used only to uniquely identify the 'indeterminate'
 * function/keyword.
 */
struct indeterminate_t
{
#if BOOST_WORKAROUND(BOOST_BORLANDC, < 0x0600)
  char dummy_; // BCB would use 8 bytes by default
#endif
};

} // end namespace detail

/**
 * INTERNAL ONLY
 * The type of the 'indeterminate' keyword. This has the same type as the
 * function 'indeterminate' so that we can recognize when the keyword is
 * used.
 */
typedef bool (*indeterminate_keyword_t)(tribool, detail::indeterminate_t);

/**
 * \brief Keyword and test function for the indeterminate tribool value
 *
 * The \c indeterminate function has a dual role. It's first role is
 * as a unary function that tells whether the tribool value is in the
 * "indeterminate" state. It's second role is as a keyword
 * representing the indeterminate (just like "true" and "false"
 * represent the true and false states). If you do not like the name
 * "indeterminate", and would prefer to use a different name, see the
 * macro \c BOOST_TRIBOOL_THIRD_STATE.
 *
 * \returns <tt>x.value == tribool::indeterminate_value</tt>
 * \throws nothrow
 */
BOOST_CONSTEXPR inline bool
indeterminate(tribool x,
              detail::indeterminate_t dummy = detail::indeterminate_t()) BOOST_NOEXCEPT;

/**
 * \brief A 3-state boolean type.
 *
 * 3-state boolean values are either true, false, or
 * indeterminate.
 */
class tribool
{
#if defined( BOOST_NO_CXX11_EXPLICIT_CONVERSION_OPERATORS )
private:
  /// INTERNAL ONLY
  struct dummy {
    void nonnull() {};
  };

  typedef void (dummy::*safe_bool)();
#endif

public:
  /**
   * Construct a new 3-state boolean value with the value 'false'.
   *
   * \throws nothrow
   */
  BOOST_CONSTEXPR tribool() BOOST_NOEXCEPT : value(false_value) {}

  /**
   * Construct a new 3-state boolean value with the given boolean
   * value, which may be \c true or \c false.
   *
   * \throws nothrow
   */
  BOOST_CONSTEXPR tribool(bool initial_value) BOOST_NOEXCEPT : value(initial_value? true_value : false_value) {}

  /**
   * Construct a new 3-state boolean value with an indeterminate value.
   *
   * \throws nothrow
   */
  BOOST_CONSTEXPR tribool(indeterminate_keyword_t) BOOST_NOEXCEPT : value(indeterminate_value) {}

  /**
   * Use a 3-state boolean in a boolean context. Will evaluate true in a
   * boolean context only when the 3-state boolean is definitely true.
   *
   * \returns true if the 3-state boolean is true, false otherwise
   * \throws nothrow
   */
#if !defined( BOOST_NO_CXX11_EXPLICIT_CONVERSION_OPERATORS )

  BOOST_CONSTEXPR explicit operator bool () const BOOST_NOEXCEPT
  {
    return value == true_value;
  }

#else

  BOOST_CONSTEXPR operator safe_bool() const BOOST_NOEXCEPT
  {
    return value == true_value? &dummy::nonnull : 0;
  }

#endif

  /**
   * The actual stored value in this 3-state boolean, which may be false, true,
   * or indeterminate.
   */
  enum value_t { false_value, true_value, indeterminate_value } value;
};

// Check if the given tribool has an indeterminate value. Also doubles as a
// keyword for the 'indeterminate' value
BOOST_CONSTEXPR inline bool indeterminate(tribool x, detail::indeterminate_t) BOOST_NOEXCEPT
{
  return x.value == tribool::indeterminate_value;
}

/** @defgroup logical Logical operations
 */
//@{
/**
 * \brief Computes the logical negation of a tribool
 *
 * \returns the logical negation of the tribool, according to the
 * table:
 *  <table border=1>
 *    <tr>
 *      <th><center><code>!</code></center></th>
 *      <th/>
 *    </tr>
 *    <tr>
 *      <th><center>false</center></th>
 *      <td><center>true</center></td>
 *    </tr>
 *    <tr>
 *      <th><center>true</center></th>
 *      <td><center>false</center></td>
 *    </tr>
 *    <tr>
 *      <th><center>indeterminate</center></th>
 *      <td><center>indeterminate</center></td>
 *    </tr>
 *  </table>
 * \throws nothrow
 */
BOOST_CONSTEXPR inline tribool operator!(tribool x) BOOST_NOEXCEPT
{
  return x.value == tribool::false_value? tribool(true)
        :x.value == tribool::true_value? tribool(false)
        :tribool(indeterminate);
}

/**
 * \brief Computes the logical conjunction of two tribools
 *
 * \returns the result of logically ANDing the two tribool values,
 * according to the following table:
 *       <table border=1>
 *           <tr>
 *             <th><center><code>&amp;&amp;</code></center></th>
 *             <th><center>false</center></th>
 *             <th><center>true</center></th>
 *             <th><center>indeterminate</center></th>
 *           </tr>
 *           <tr>
 *             <th><center>false</center></th>
 *             <td><center>false</center></td>
 *             <td><center>false</center></td>
 *             <td><center>false</center></td>
 *           </tr>
 *           <tr>
 *             <th><center>true</center></th>
 *             <td><center>false</center></td>
 *             <td><center>true</center></td>
 *             <td><center>indeterminate</center></td>
 *           </tr>
 *           <tr>
 *             <th><center>indeterminate</center></th>
 *             <td><center>false</center></td>
 *             <td><center>indeterminate</center></td>
 *             <td><center>indeterminate</center></td>
 *           </tr>
 *       </table>
 * \throws nothrow
 */
BOOST_CONSTEXPR inline tribool operator&&(tribool x, tribool y) BOOST_NOEXCEPT
{
  return (static_cast<bool>(!x) || static_cast<bool>(!y))
    ? tribool(false)
    : ((static_cast<bool>(x) && static_cast<bool>(y)) ? tribool(true) : indeterminate)
  ;
}

/**
 * \overload
 */
BOOST_CONSTEXPR inline tribool operator&&(tribool x, bool y) BOOST_NOEXCEPT
{ return y? x : tribool(false); }

/**
 * \overload
 */
BOOST_CONSTEXPR inline tribool operator&&(bool x, tribool y) BOOST_NOEXCEPT
{ return x? y : tribool(false); }

/**
 * \overload
 */
BOOST_CONSTEXPR inline tribool operator&&(indeterminate_keyword_t, tribool x) BOOST_NOEXCEPT
{ return !x? tribool(false) : tribool(indeterminate); }

/**
 * \overload
 */
BOOST_CONSTEXPR inline tribool operator&&(tribool x, indeterminate_keyword_t) BOOST_NOEXCEPT
{ return !x? tribool(false) : tribool(indeterminate); }

/**
 * \brief Computes the logical disjunction of two tribools
 *
 * \returns the result of logically ORing the two tribool values,
 * according to the following table:
 *       <table border=1>
 *           <tr>
 *             <th><center><code>||</code></center></th>
 *             <th><center>false</center></th>
 *             <th><center>true</center></th>
 *             <th><center>indeterminate</center></th>
 *           </tr>
 *           <tr>
 *             <th><center>false</center></th>
 *             <td><center>false</center></td>
 *             <td><center>true</center></td>
 *             <td><center>indeterminate</center></td>
 *           </tr>
 *           <tr>
 *             <th><center>true</center></th>
 *             <td><center>true</center></td>
 *             <td><center>true</center></td>
 *             <td><center>true</center></td>
 *           </tr>
 *           <tr>
 *             <th><center>indeterminate</center></th>
 *             <td><center>indeterminate</center></td>
 *             <td><center>true</center></td>
 *             <td><center>indeterminate</center></td>
 *           </tr>
 *       </table>
 *  \throws nothrow
 */
BOOST_CONSTEXPR inline tribool operator||(tribool x, tribool y) BOOST_NOEXCEPT
{
  return (static_cast<bool>(!x) && static_cast<bool>(!y))
    ? tribool(false)
    : ((static_cast<bool>(x) || static_cast<bool>(y)) ? tribool(true) : tribool(indeterminate))
  ;
}

/**
 * \overload
 */
BOOST_CONSTEXPR inline tribool operator||(tribool x, bool y) BOOST_NOEXCEPT
{ return y? tribool(true) : x; }

/**
 * \overload
 */
BOOST_CONSTEXPR inline tribool operator||(bool x, tribool y) BOOST_NOEXCEPT
{ return x? tribool(true) : y; }

/**
 * \overload
 */
BOOST_CONSTEXPR inline tribool operator||(indeterminate_keyword_t, tribool x) BOOST_NOEXCEPT
{ return x? tribool(true) : tribool(indeterminate); }

/**
 * \overload
 */
BOOST_CONSTEXPR inline tribool operator||(tribool x, indeterminate_keyword_t) BOOST_NOEXCEPT
{ return x? tribool(true) : tribool(indeterminate); }
//@}

/**
 * \brief Compare tribools for equality
 *
 * \returns the result of comparing two tribool values, according to
 * the following table:
 *       <table border=1>
 *          <tr>
 *            <th><center><code>==</code></center></th>
 *            <th><center>false</center></th>
 *            <th><center>true</center></th>
 *            <th><center>indeterminate</center></th>
 *          </tr>
 *          <tr>
 *            <th><center>false</center></th>
 *            <td><center>true</center></td>
 *            <td><center>false</center></td>
 *            <td><center>indeterminate</center></td>
 *          </tr>
 *          <tr>
 *            <th><center>true</center></th>
 *            <td><center>false</center></td>
 *            <td><center>true</center></td>
 *            <td><center>indeterminate</center></td>
 *          </tr>
 *          <tr>
 *            <th><center>indeterminate</center></th>
 *            <td><center>indeterminate</center></td>
 *            <td><center>indeterminate</center></td>
 *            <td><center>indeterminate</center></td>
 *          </tr>
 *      </table>
 * \throws nothrow
 */
BOOST_CONSTEXPR inline tribool operator==(tribool x, tribool y) BOOST_NOEXCEPT
{
  return (indeterminate(x) || indeterminate(y))
    ? indeterminate
    : ((x && y) || (!x && !y))
  ;
}

/**
 * \overload
 */
BOOST_CONSTEXPR inline tribool operator==(tribool x, bool y) BOOST_NOEXCEPT { return x == tribool(y); }

/**
 * \overload
 */
BOOST_CONSTEXPR inline tribool operator==(bool x, tribool y) BOOST_NOEXCEPT { return tribool(x) == y; }

/**
 * \overload
 */
BOOST_CONSTEXPR inline tribool operator==(indeterminate_keyword_t, tribool x) BOOST_NOEXCEPT
{ return tribool(indeterminate) == x; }

/**
 * \overload
 */
BOOST_CONSTEXPR inline tribool operator==(tribool x, indeterminate_keyword_t) BOOST_NOEXCEPT
{ return tribool(indeterminate) == x; }

/**
 * \brief Compare tribools for inequality
 *
 * \returns the result of comparing two tribool values for inequality,
 * according to the following table:
 *       <table border=1>
 *           <tr>
 *             <th><center><code>!=</code></center></th>
 *             <th><center>false</center></th>
 *             <th><center>true</center></th>
 *             <th><center>indeterminate</center></th>
 *           </tr>
 *           <tr>
 *             <th><center>false</center></th>
 *             <td><center>false</center></td>
 *             <td><center>true</center></td>
 *             <td><center>indeterminate</center></td>
 *           </tr>
 *           <tr>
 *             <th><center>true</center></th>
 *             <td><center>true</center></td>
 *             <td><center>false</center></td>
 *             <td><center>indeterminate</center></td>
 *           </tr>
 *           <tr>
 *             <th><center>indeterminate</center></th>
 *             <td><center>indeterminate</center></td>
 *             <td><center>indeterminate</center></td>
 *             <td><center>indeterminate</center></td>
 *           </tr>
 *       </table>
 * \throws nothrow
 */
BOOST_CONSTEXPR inline tribool operator!=(tribool x, tribool y) BOOST_NOEXCEPT
{
  return (indeterminate(x) || indeterminate(y))
    ? indeterminate
    : !((x && y) || (!x && !y))
  ;
}

/**
 * \overload
 */
BOOST_CONSTEXPR inline tribool operator!=(tribool x, bool y) BOOST_NOEXCEPT { return x != tribool(y); }

/**
 * \overload
 */
BOOST_CONSTEXPR inline tribool operator!=(bool x, tribool y) BOOST_NOEXCEPT { return tribool(x) != y; }

/**
 * \overload
 */
BOOST_CONSTEXPR inline tribool operator!=(indeterminate_keyword_t, tribool x) BOOST_NOEXCEPT
{ return tribool(indeterminate) != x; }

/**
 * \overload
 */
BOOST_CONSTEXPR inline tribool operator!=(tribool x, indeterminate_keyword_t) BOOST_NOEXCEPT
{ return x != tribool(indeterminate); }

} } // end namespace boost::logic

// Pull tribool and indeterminate into namespace "boost"
namespace boost {
  using logic::tribool;
  using logic::indeterminate;
}

/**
 * \brief Declare a new name for the third state of a tribool
 *
 * Use this macro to declare a new name for the third state of a
 * tribool. This state can have any number of new names (in addition
 * to \c indeterminate), all of which will be equivalent. The new name will be
 * placed in the namespace in which the macro is expanded.
 *
 * Example:
 *   BOOST_TRIBOOL_THIRD_STATE(true_or_false)
 *
 *   tribool x(true_or_false);
 *   // potentially set x
 *   if (true_or_false(x)) {
 *     // don't know what x is
 *   }
 */
#define BOOST_TRIBOOL_THIRD_STATE(Name)                                 \
inline bool                                                             \
Name(boost::logic::tribool x,                                           \
     boost::logic::detail::indeterminate_t =                            \
       boost::logic::detail::indeterminate_t())                         \
{ return x.value == boost::logic::tribool::indeterminate_value; }

#endif // BOOST_LOGIC_TRIBOOL_HPP


/* tribool.hpp
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
*/