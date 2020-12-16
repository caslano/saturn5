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
Ay6FveGdcDhcBkfBu+A5kufB9XAKXA7Pg3fD8+H98AL4ALwCPgjnwsfhDfBpeBN8RLpzj+r5eQxugGvhJrgOPqv7PA83whfhU/C38Am4U+G9r/D32LXaEe/bi7goP2pjlik/2qk8DpNuVwfpQnXWfltdYC/YVe1INzhY+2IN0b5Tk2EvWCAdsYukIzZP+1BdJ/fzpSN2o3TElsCj4N3ab+t+ufPa3dXl64I9p/bzeemCvaD0Uq/Vv7fvHfPX1rHnwn4jlN5Rqn9nqP4tgrb2DNaVrlgr6Yi1lY5YP+mCHSMdsOOk4zUKTtG+TRirBwWwSLpeJdLtukA6WKXSwVogHawl0sFaBufD5fAG5ceN2r/pZrha+6U9rviul87WS7reKp2x96Uz9ifpjH2ufaa+hLP5/+/wUvgP6ZJ9D6+AfH6ZTlkIzoEp8JcwSzpeteBoWFfXe+x5UX8VXK787oRZoPzm3WDP21Ll453aj2yZdATvhifCe5SP90lHcLV0BB9Wvq6Bs+Ej8Ertm/YruFb5+YTq0UZ4n/YtW6P9yp6Az0j39Hn4nHRmN0OM5d9W+Kp0Z3fAbfAz+Iby7034DXwLkljTnQ3Cd2Eq/B3Mhr+H9eEfHHtvWXi80yx9raXr1lG6bv2l6zZIum7D4Z/gCPg2PFvX58DtsEDXxXAHnK7rC+Bd8CJdz5bO3aW6dvf5eiL1v2ufr/+kPb7eTc34t+zz9RX3rVMFHTHMcEwhZi5mBeZZzI4qFdcP+znm/0cXFYyb3PnHz/9H5ve/jlvb/676ve9jDsK8irk18rJZ4c3vjxk3LreweHTuDIdftvcdLnEkXo7fHtAKQ9/bA3ubn/Hjp4325uhuNvvGvt/98ovMG48iNQX5RY7/HL3cK378FL/c8RZD5NpP3dxdT3+ohvMLTCT8BvadzjxMJHoKfwff8rFxAlb1SP4ucvfb+x7ycSaGDo+Zf2iMMadM3dDvGDKccupt4wR17YRw++bW93RCfnrf35F8q6t8y47//o7LD+QW3wbmVulQGJH4mnulIbKWZ4PlAW1p7+j1Tl2/3St63fOe6PXNvbVWT3VlTsixXx0lqDbmo2zeVbhXXRk3paAoN5IEJrDj5z2Q+NYR/B7YeeiWFoUXieuyxLh6eisrtI/9yVhmwJPgRbjZFBfXgvz83HHJ8fT2Vf6Nue0XOJSQB2G6B/z2+1aYqucDvHoeW6O77N7oWvyz8J1c1+Xfv65rPBKZhZEWqEdvLRBI8X0GFE78nDBFbvluda4t9baq49ZVo5nl/H1HQl1OHkPKrEB5uHV2gFdnHf86K//feHWTeKpudrd00p9V3Tzm3sS6WVLG/pIy9ut0/Z7st8fZq34krN2+KBitH3z7Wf0ovM+rH1MmFRXzzCTXj+Yq11+a28nB7tSCy53oeN7B6HK009pQ8kfhjad/nu6VleT+dUZ176GVEfs9jEdU8asz8u9fZxqqznxibtZRZ1Kc9ZiH/OuNwvKvN19RRl6baukvnlmYO5rGJFavaiXZO176H7Swjwyms+trX+pf9eT6Z+YuXasuxtkl1kkrNv2y/gV18qsydbJhQj1NTH+27pdoF613r1i6+c5TPWyxMrHedlmZWG9zy9iXlLHfWsZ+Rxn7Bvcn1vvD7k+0H6nrAtlPLWO/7n7/52RlusMvtn/zKZgLCaP0Ae85cZv7uLo4vmDqGMaMffsF8ptQd728S67rvu4LpxUUF4wr8F3zLvf+z4afDpfnvnpCPY7Nv640+1qezs77cu/OKX/j1tcKnMORWGeUT5Kn+dSlxLrqpdvkWcl12MpyucWPeSaV9doH3LKt2Hi9/7h8eePvBz7e3fCDAPJrD7s=
*/