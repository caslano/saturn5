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
#if BOOST_WORKAROUND(__BORLANDC__, < 0x0600)
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
oXjx4VQr+eh8kE72NWE4WrH3TxODq5qf/z16uTzwK7mpxffBAny9GMvR6S4dAmV7VdpH1aJw3MK9e0SCukalRbuX5x8HPSVrP/n2G83neYPpCfWIx7iAOzDidqMIV26s8ksLGkh/WHCwv6SLnjqYbg2janP+jiboHUMiasJBecPzG+lmPQiiJtY42xV1VDbtsQleFwSHY96B5HhInu2kayBD/MdTWDQtku+7+iIvzOxka55e1jRNKofDhg1mNDokCQObEyAQ2a6QZ2gALnFOU06zFhqhJr9PgvvVv7W9uxoGfzfRYDazJc0bzJpKW2p3k+t2gRCxnNz9e6R0dBKDwet096sJhHfOb/beNH8qoc1ELBpfTKeXrWX+8gD0vUFjxbtQafwOdwmhW34SSOYiHSTmvO8CBJQ4ADlNCrqC2XgWjL1NssczaDT7z/zdA7VmbjNCfbJMi/HK24pWEcZ/3CDduPxDQgIBU60vWL53MzuzpqAPuSCNnyoG9MxUuidabv0Pbl2z5TdrjF5XLReGjtvmF8r3o+kV9CbDLH1HbD27o2g2Iu4P6RKZax4VopKkVY1qDEkf/A27wYZRPmnhb+a97ly5fPiv2u+Xsz6ueQqq26vtGa9qUCze5YfHhz22vKuPpGjng1m5YpbRuqXbubYwa+C937mI7V/Uvb96j989t684P7efvruvn7+f/m6aQL/+3RQfit5DltgJSHYl6ts/5kefJ4CYElM815F44HFRyTVxpE2UlTXTHwbEfd5EmCPeo4EWHLrGDyVMxV90+dD69sIF/0J2+o09Plz+w4jjdUDD7lHrhUP9Drn8GFQUgMPXPZ90UypWzBXR2s900WoZQ6IEun8jnfAQzkxfeaCbK0WPK/Lg4DKqfGIU8p+xq2XOA4NtLFQdfyfqX9RkaDo0y3OcXHM5LK/wNxJVTf8evWH+sEIHODxfdn5RGPtmfY1x/ry+UrDccDAJgGTsAiPoGfX1Fd11b8jczelqiWvaJyYQ7835nAecedfdfqythMg0UIvdmTx0YSDnGMU6LDWscR4RPRygtMWPSGFmvmaFDOvRROeCRaaHA3dYwcjH1YoghQGH7Dx7snnK61i10biBo1P+PdYaseLIFUz8uuulLRTzsHv2w0W67MYOHPu9TFdrXLeqW+2SP2tdRz1ka+oO1SjZTWtQiE0oot/fSYqUbbg95LvD8LTxFdtZZkqacv7FrbuCgJpHRzrvtmZqaDvC4+HMtdsCn2vi4UF38071RM+eDjXr/S3xet0rK77NPncY3F7I+G8U+3Gx7nDP7XB6WPcNS7/vrIdtv/rJa392Dv3bt1k3wVnuua3ziISswmGwVchD7TGSfAdNr7Rp8U21bZrviLw2x2hjatybxhmrkgZY0V7dQsgmu4G/b1EHsrNv881zYArRu+fdknlPOHilg6Hn0TP5+K5ynuPjwFnrUvmBtFiuyHsoCQVua8ccJfrAUlB3j9wPUS78rDW5/76rIgngwFpeb/kh6obZS13pkceYBmTto6kxPX2s+o2jpjZPAL6HksZoVI4P76WTsLYfCbVOfUhurmNuxznakYqmTGE1nPl1EzK0S2ONc3q9BvpngTdObUDcAqWBIRi8AC5PfyxodZZqthg7Zi2pyDs90mPmmcUY3kmaslRjjHsZdMmLQZ1wKMZ64lBWrG7t6gTbyg8PpbEb1HUUMx+xA08aZ/vwXU7M/gaL+ZgNgqTqF+ca4VtXIh5gGHQHugqN31YsdJyWzuIKO9dXgOeSj7NxAjxKrJ0OvdPb0xMl89dimt7SVCEg8LCpojLvfuofYQ64YFg1ci8V7UnoHJCaPMIG+15G+bXgJzW6g+13EcAGJEnN4G7UL+Hd3bJPTIjxOf4JbT/Z0ZdmsbAMGEmAogzYNXIiJAJ3le5BNis7MeGnah1wsJ9d6eKZ013cZ3Y9Y54ul7hnIXRnyY8/cTiB0TonlNH02ezPVzYuh4lRJpTWTnUzixponWnML7fo6WAI7wCy1R5Zpg8/z9zOVc94B2QkjDvn1GYy9SeCtYir2TuXqTKLMq+iC7soV84QljSqGoHJtgAPonLVEi/YXfCjtADtbe7Yq1wcbR+pfO47ny4MnZJ7VV6Dp+BBDmrMVpmVxRPiCRkQ/H8P2Wy2gTPOlBOTcyikzGF4hb0MRHux7icy2vPcNJhMIU/KjK7DPr0ICr+YADuCvL0lMO2XSDu7Ub3nWOatD9yL56d6zBreu98EuqYHewO+EbsPnM+1P8n0JVp7f88FL3tPjW8+ncEc+WpaDff8jN9wdMvOYpiMPvIJXoZ6YPsrXTHgiL4CzXTFu+75i5tnDRkHhoiS8AHi/K3IQdZdPiSaFQ638mi1AjfpHBq/dezVXPLBCVGBwQ/3vMRzntvq0/ri6cOnw8kL51PMrYMid/N5++xGJ93eRqkNsSVVyOGP3NFXaXw1GHyrdTuP07jm7jVEueerblVFtBWvzjQ9XgdZpcIiFcIrKxKi2gIh5rBCYm+ZCnxwfPk+bPUCeO0i46/G79acp/UtgPceHMLfJiWQ+5mIAGIBeJ72bKyHZnY/17uNXl0Ll/n2tuQ8NwoRskPqtZwnzNl3j9GVJHrO52wHtw4TLbYMlaQBOC92TyTmD8ZrPLxCEBtg9Re/xQT2/XW6xeQ21QF0s4nrco2XHcx1pH7bSZoUlpKnKUn8DGlqideZwRzupL1NneqMYYBT8QEJbppN9fUn6fYquHuc7YnulfVZ0WJJBgLyZzs5qwZoXwNS3WGN0XitbZexzsPgEapSWq7GW5ds0ifnrOGcMjPTBw47wm2PG3y54CHNbnEHumg13NJpYlBfDGRv4gGqOt3yvZDIoEGhNx/qZ9W3sHebmVIbXC2oUM96Ye/MBboWVTk9FdYzPriahgyIEj/2CNRPws+mxmy+GYyRa8LaZ9N2oBxjsJ+O6+PJjTsc/wuh20PNOI6qNJN6uCx7U0WYUKYjE282pP8QFFzrfdoztUIO3/0I6x7xFOuNxd+RnpmwLQ+MD8KnkV7sUogy9XTHP2/ReXJSuTlsUcd7YkFnqXca8W17BdmIcZrLl7VGXQMeZrBapHvM6bi6fPyOzqyEIs78TqWraKVf8w7pJVaIrRZfkQ6ZUNHnofBjQcMogDWgxSojOVzpM4JU8GptLtKYjeA4yiUDAAk5O2UeEZy4kN8yXR55qXIT7d7xY3NRKQhOZ2eg0lJMtXwrqE0FItp0OL/VpKVs5e68e0GZ2Rj0lCimMivbHbAlhz5qU1auC8bfbp3o0Ty8fXPJo4m1nE79KBWIjfscEcbx5wa3d18iv1XGhQL+HbHW50mthFURj7Y/LvKAVZLcb/502wF8GOFoPz9+nwmpeFjKZuOQ8Hmh0AJ7PY0VvqznIOtt1LpvOrC247EGlcdvEEIIJzxthwcyPRsHkPVhCg/wEN9MkB2bHD3XmfaDiLGSxBsinoSoOtDKxQeHMK6Z0X2ccqmU1J5m5MZYteWlxg7dhSp6fWeJxZCfhhBbgSR2zRkA0/CeXOM7mziZfcHXJeNdPddlz4Wl3qFg4cGfO9z7ipTJ8h0F4hP4r7UWqaPosu1N4tfAmbI4Lm+XJQhaxxfGZ3q/l795eOccg6b1/9TWPiDwUPhpZx2011JvHM9ddfiueDsdWtwh34kTGQjhjirRW424N2WIHAnhmUrw5nd/rMbbLn/qJh1/soFGkjeGQkp+n+6Dp8+vnXWG7LIAXDR2poeB4k1WTbgcXvTA81FXwwzKfVMgVrhHQS6q0e8Fv/D2fu+ugrloTpq03bDKzM8MCKUU1yt26/IkWlRxHPU2JbYf8voGxVoyxUGn7gMi3jwDUZQ8ZaBiyjdt7t/lw+JM7UQ1RKHXozLJSfN4cf0riJ7tkcuge5jeIFn/11NthiZJzXmVGcVnJbtT63mpt9V0EGJvJZ1/lP0DR4+YaIPKJjAoyTSOnx4PpUn+ZT0c9+1oJhKNYnlV6dLwFquEzG5hBM7IDeSMf7RoR59Ken55P40efGk93qaCxNSrVs2B95I58oAGtdF0QvyqFrsSt7hdBKIKpj3IqMHABwtGUTYwAZpe7WhYzxrZBcICUXU2dfjQ/mlGjXu1cBCFh2Fwy1YfW3k6a+pHlbokc2XDdp9Celw7XrBukqn6+cILcDKIX+Wciv+Q1SFZETZ+iVOBe6VK8Q2WfHgMx6eU6CbqBkxrR++T78cE1PxPmmNBEsGInI2bSURY3Y0TMr5tb+HbxTL5XkpXBkjv0XpEfmXvO/hUMyzROig0a94JxL7xXoLS95GWdXPqlx1pfsod21GVvnVO5jpjS6yMGWYdmuIRT2tXVY2Qgmzwdw10IoJDSqMPBZIbrWuSeqhhNTsXHUF1sv64RFHPJjvHYZ+3/Ucgb4bqrHiaxATeuAuAI2K5l2i4DljioJl4V3+O4WQUWUBAdplKNEsc1UkAeRW6Vr0gxD4DqWfPk6/0cNFXRNiUzxngtPGw52fINrVDMx3RJ3j8VkaLNECmKtOFL3dEWnWXfC550+fTveIJ4faqdnWYA56rC7RlHi6q2J6YWxmJYhfKzL6m98Q0/4nJVVpmsWl3e+4qaG6IgXrXnkFU8k7d5J0FBr93WIvrHbMxtisCmsUk+r/VFFoMBb8DIzavRU4A0jltXb1TwLk8RHzH252fd/xXnVeFYT9c21QYSqwNLlmjN//f5yBLdxyPUO7H2Wr/bWSIZUObqZV/IwhhiDGjiafx1Etz348nQ6LdrnchO1UKlsY7Pf9xynJt4qGe/8cQeQ8UhS5pQTXtAKdPNrrfPkJNJ3yzUAtwUJVU7tc+rlpz6dVS5XmBHlhL/hTAOtQGhclkVinGmGeDQIfctVV+FQrD6iIKEdFuFJ2JhLho1BLmYBL6GYE/rUTIXdNH2An08t+4AxiVN8dyyO9tzsO2rfhhcGLHmGyN4HeKe+tYXfvWiY4Jsz94iCujhFVWtVkv4bBWfRI0pY90pPc5aaWlPpWlsuaaWnxTivtVfZhYBJkYH9oSBkagPtD8FEWFK62s33CMNmkzV+muN8S0yGC9pl4Jvt1929yg6Cx+y+4ksyQ8uhG5fEfVbdQx31q0Jb2K0pZI7n3pznN/qtYp3u+1fzsbaSk5zZsCa1DvLTIf0eAYKFElNm3pHNlRFrqukwfzAlYNHKBUU+IMyhHITKFKJQlBfvwpqtkQtg/ZMsELw9b58O/o4xPNQ3IK+34oYATQh39cnyWGddCZ8h1yseKepuXIj7kavwwQzKx0nhJWcFYsO8x645I9pfpSLLESPIeWl20r5mhjlOV/nLVzUXm+/ZzS4aaM1XpFYRr15aplTplbF0SljUEjiBH8kpUHPNbi3+P4g1GGKRpJMfwho51BhcxkK1mpbzYYE0Si5Gv+P4OQUR+yjyO/BB/8GpXROxnoW8+gub8l5u3ysQA8dJfl58w/WDgJIIHDyumTFdHu2vxdcRK5Mbrqednj+CAfTyUM6wsFozw6mdSSazJPRSZWgBPybtgmDLyV2T1n8RjS1B5wvABX/3HWVXtbSXllhTOez+nCiP/w19QHIWFpOKatwOVKTnVDKDJ8axh+RpaVKtKu6cji61XLBidkE+6hCAS+Edi6rcNMZQuUuJJYsdMV4V13CMJGGcJ3Rj9Y+V4dXeqt7wVqezc/OqNrn5ZprPDKpDJPHXVWIi3HTGC9LDtdixhS92QlDabx0uB1q1Sx99AjRy/cQv83zP9OjMnqiiUgUXT5UXVDNGU5z/RfHiyVTMQ++VoUeFwQ7CeS4UHkwdLPdq7vgE/kYhek6rKwND2aA1Rx1AWe803QaVZeiuGaeBVUnDYlt/s77op0cZp4/CcPUI2eXswysYv2xIc63+vFyXb4AOnXkxnFqdES1wOQqJ5wcKN4NgF2kpbb2Nc52+H+LpA898wjvkgHm/ppt83s2MX6P5W7NOrtMOpgLeck+goo5sivUKiZHQuL/BbzId5sF7iJJxfYLr2yRPbWJvjYuoU08eRj3ucWuIBekAdCPEob/yncWQ5/O0EaSAMpzLIA7s1xXeJSI31NQ4V8JLHaknH3yIcSeQDXNYeFvMNG8OOiztgQ/MOzaTvsqkoX+sNy9sdQr2Hreelp+senVQw3KVHlWg6FOp8SIEriMn05d9yUtYTCsi/Kgm8UorLaFFaUnEt8is3j2+2oSEhI6X2BVwHuxUj2ykFRJ8QfPmXsVXKAvu1ZH084mymgDm8KUn+1LxPiMlwmqRtxSDqtt3CLR00qZjjArzas/3KzdXjB+NNuatWD+FLq2buvvzCvrLgyr7akRnqCqesCUqFFci3Ti+avD0lFvqzmswfVRysqVjvrVHwgKOR6BKHmfw8OQw3ZH6xcNjiLgtvZhEaJC/oQF4pKuzt2mClbrGNujyjBi5YQDHKE0i40o36QSuhLBlFUOCVcsUJ88ObIr1CaWMWmCNvsB2pZw6PxhVA+YcKj/cNK73KqFtHBOcGUK6bczxtH57ZxVBgRmsNxPoQEcZ7ZTpM/iLDnTZzQaOoc3yS+y5A9I0/cDaJUuZAdAKaE/JPG+OkYHNUML/UVaEu1bx4SX7EqheISakimhcJhgc1IryJHPwtjmqwZvp/ttjwS+miJPoVltKE+Myo0UcsmCAy0B2jWEMzFuNDIL03rf5/WRWPMX1XXPdRlXpbKAu7E/foe1JW1Xe5OhL3cPgE6YX0w9kKMvPwPQIO1AYUpt4Hyh8+LDBmO+Wc9ApqIft4arI5QGtxX3EYYLkjaTYl6a946SDPyxnAqqmVTeHJW3fzcflxQXaUiuQoLlCzoBgF/idjjJudWXutd1SqRcPZ8h3LGv58jyTbeMuSwgX1COCPD1PfgJYZVrf2/9u03oa7kBCV5xszCxZ8R6t1/0vG+XpDVtA15ecah5unK2WOu29AFTQY9VIQxxfK32ar2+IyNoA3N/GBkE/GgB++vC+m6G6nP1HsRqFsRFuKE3lAU2vyREi9BCjqg0JcEggBlmG/1dV6mju/3O2Y2dqHeSOh9m3PFsC9DrlpoTXkZ6ZRt7aOeUNAOJYTFAA5lqz9gYB8Cj+8uE8iBNDzU3Sv7V4RisvOC7jWUoQ0n+jMQ7hZeaVDyEHf0u1U6okwCyqLyoakQq2IZKX/oKeIo0wiOdnZfyE/r9ybyb0MrrhsfbZJ5qW7Vs6SaNns8XJSvLkkBjZgzC8RTmn0wDhMOiMfFAy72yHFQ+lkli3twJaGXae46eqcZo1kvvG8458D8a4fihbr+HQFumwk/msOVP5B4dGgQLPvXavcrVQDLrxOB3VxxeasFJmhhufD1KRAIOTfOtdm7SbPZXvlhI70d4wnJbCNYe58wg7j6DrRJ7Ek7/OK5k/D9jOeHarjxWg3EvoFBYD6qzb5R1dieE9hjyAKJC6qvsqXroKkrhBL8Z53z48X+j2E7wVMSB0R1tVHloIyVuZwNMo3fNsqQ9YreAqvuI/1rMTf1QfGW7oH8PktlAD3GWmvkvYti5wHRimZYWujQIUWYOL8bOzwgdiLNZGYHkEcdnY7NWZOwiDwSsuxjKZxU40y1ee733cxB/e3wZ3n3S6KLGNZ/AgJqb78SnpP1Sv0/H3Mpix6QWFvIT359wRJYPbuFzsHHDBQljrUA45YjFjhpD+kgilHYhrBW28jdPIKfyQ7fZ9T5MC2RNzsT5bp7/l7jC6K1Re2Xe1JzDzzNZ0fkO+3Ro87muXWkHww9uIMCT2cX/AjMwdE4BxvBtoi4N6pETpni/RSmNHFAFlSsVext7/YFBpWCaZg2RmEHSD8aB0xEhAAALP/T0SLfk0kowf691O+qBJDBw2rY76avRMCmqF7RVGNmAIiYYQXef5sg1laSiOchKR84YYyjEWC5TXqukabP7T2I2AeDkABOaL4dazzzQAP59fR0tMhqxVoWu/xdN9uhMTXdDBGczqTlVdEe5YMifj4Lavop0wZMSnhQ36PKwnyCn9uJyHt5vu+IVW2zz0lOKqxwQ5qiYyaxdx55Z7ETbmjQ37AHl40AHST/LcGnHmAxcnXapVfRhI7mlOQt6WHkiTzJzdKrkm2DGF4CFEjEpbq+gKddz1knW2OXqjLBFMPWzo1JU8cYbl7/N9J4K/ab0nRiuIcnLOiJbBrWnnYQN0iSly+1azJ8drwngpTpxzaKO79Wp2DNkndpry+5oPql9gbyxHEHOIXtHr6ggCaEVMqAIxrMd/uTuvDm8xnYm9+nfbf600TZ+V7vYjWF2D6Q/nykmo4uOwQ1i7feAXc0KKa12RRkMcn0+e/wtMi1wdFKRKTAVZHMVvxOq2iHB2bIyxgoW15A7NgzAcm3JiZH5ymhwxOmfrm9aHXMuKparr4HjFTMy+2CzElhhEPOrCOPp3G3VYrQMZqv7jTd8kV+WqLKXNwWkq3b33Omzwlxl/j8tQdHSSDE4+uKAw82BrVxCeKiGxDTBGIAiBd58qZiHFEaVqZyZ86vL6E+o6O2Ind+ulC3nA8qLwhcMOYTGLD38+6gttT1wTZbbdYprzm0IQR9MRk8Vz0M+3KigDlvZa+9mFgKb3/db7EYMnJzaCzOV2vDCVxfLL9x4JJ0j38aHRUBXZS9lEZ7Y6S9znbs1oEejCe2tX8doIhUlUGRNdJesT7o/PF9VD9J406XfXh1B/KgrzM6Oak2gx6RoAlagBhKaSDivoJBOswtm+uS3kliRZae9QklpFjddz7E4P2Ec/u8bdh3ymiR1eudp3r2u/a7VmzL++O37lIyo42pQBo0OmDHzGbpxe+IocKutM8ZQ5g9zsPVpbNRHY/G3tMjEFzkOBWVzCM9f1xjVyfDEgBX3FhJPxgsxWT+1Wm73M1UPcyBgktdjhOIYvGiBK8AJbFr9sKjSNkelnuUJgK4fE3gXPczTt6APU+GIALuuedYPwzzuGYEyL6Xd1VbjWbOAjnf0QTyWLcjlHy2aNJuS4hDj0hgQ/3kMYxE6oDx7gFaaYNmZX5Fyhukg3hS6FLgBgmkrW/pAAFVY5wb0scEn/GFBI3qCDpR0lkSuB0bXQKL6/wov07hZC9D7JovvFIG7vVruefccfhYfT3XXp476p76nKK2mpcvpH03wTBZ6nBaGGgSY3GMfZrrRVYOh1sHVP2dFu3cuDgzygNSYNaJmUWSqRC9fnMUX+7tBC094AspI0Mzoro=
*/