#ifndef _DATE_TIME_INT_ADAPTER_HPP__
#define _DATE_TIME_INT_ADAPTER_HPP__

/* Copyright (c) 2002,2003 CrystalClear Software, Inc.
 * Use, modification and distribution is subject to the 
 * Boost Software License, Version 1.0. (See accompanying
 * file LICENSE_1_0.txt or http://www.boost.org/LICENSE_1_0.txt)
 * Author: Jeff Garland, Bart Garst
 * $Date$
 */


#include "boost/config.hpp"
#include "boost/limits.hpp" //work around compilers without limits
#include "boost/date_time/special_defs.hpp"
#include "boost/date_time/locale_config.hpp"
#ifndef BOOST_DATE_TIME_NO_LOCALE
#  include <ostream>
#endif

#if defined(BOOST_MSVC)
#pragma warning(push)
// conditional expression is constant
#pragma warning(disable: 4127)
#endif

namespace boost {
namespace date_time {


//! Adapter to create integer types with +-infinity, and not a value
/*! This class is used internally in counted date/time representations.
 *  It adds the floating point like features of infinities and
 *  not a number. It also provides mathmatical operations with
 *  consideration to special values following these rules:
 *@code
 *  +infinity  -  infinity  == Not A Number (NAN)
 *   infinity  *  non-zero  == infinity
 *   infinity  *  zero      == NAN
 *  +infinity  * -integer   == -infinity
 *   infinity  /  infinity  == NAN
 *   infinity  *  infinity  == infinity 
 *@endcode 
 */
template<typename int_type_>
class int_adapter {
public:
  typedef int_type_ int_type;
  BOOST_CXX14_CONSTEXPR int_adapter(int_type v) :
    value_(v)
  {}
  static BOOST_CONSTEXPR bool has_infinity()
  {
    return  true;
  }
  static BOOST_CONSTEXPR int_adapter  pos_infinity()
  {
    return (::std::numeric_limits<int_type>::max)();
  }
  static BOOST_CONSTEXPR int_adapter  neg_infinity()
  {
    return (::std::numeric_limits<int_type>::min)();
  }
  static BOOST_CONSTEXPR int_adapter  not_a_number()
  {
    return (::std::numeric_limits<int_type>::max)()-1;
  }
  static BOOST_CONSTEXPR int_adapter max BOOST_PREVENT_MACRO_SUBSTITUTION ()
  {
    return (::std::numeric_limits<int_type>::max)()-2;
  }
  static BOOST_CONSTEXPR int_adapter min BOOST_PREVENT_MACRO_SUBSTITUTION ()
  {
    return (::std::numeric_limits<int_type>::min)()+1;
  }
  static BOOST_CXX14_CONSTEXPR int_adapter from_special(special_values sv)
  {
    switch (sv) {
    case not_a_date_time: return not_a_number();
    case neg_infin:       return neg_infinity();
    case pos_infin:       return pos_infinity();
    case max_date_time:   return (max)();
    case min_date_time:   return (min)();
    default:              return not_a_number();
    }
  }
  static BOOST_CONSTEXPR bool is_inf(int_type v)
  {
    return (v == neg_infinity().as_number() ||
            v == pos_infinity().as_number());
  }
  static BOOST_CXX14_CONSTEXPR bool is_neg_inf(int_type v)
  {
    return (v == neg_infinity().as_number());
  }
  static BOOST_CXX14_CONSTEXPR bool is_pos_inf(int_type v)
  {
    return (v == pos_infinity().as_number());
  }
  static BOOST_CXX14_CONSTEXPR bool is_not_a_number(int_type v)
  {
    return (v == not_a_number().as_number());
  }
  //! Returns either special value type or is_not_special
  static BOOST_CXX14_CONSTEXPR special_values to_special(int_type v)
  {
    if (is_not_a_number(v)) return not_a_date_time;
    if (is_neg_inf(v)) return neg_infin;
    if (is_pos_inf(v)) return pos_infin;
    return not_special;
  }

  //-3 leaves room for representations of infinity and not a date
  static BOOST_CONSTEXPR int_type maxcount()
  {
    return (::std::numeric_limits<int_type>::max)()-3;
  }
  BOOST_CONSTEXPR bool is_infinity() const
  {
    return (value_ == neg_infinity().as_number() ||
            value_ == pos_infinity().as_number());
  }
  BOOST_CONSTEXPR bool is_pos_infinity()const
  {
    return(value_ == pos_infinity().as_number());
  }
  BOOST_CONSTEXPR bool is_neg_infinity()const
  {
    return(value_ == neg_infinity().as_number());
  }
  BOOST_CONSTEXPR bool is_nan() const
  {
    return (value_ == not_a_number().as_number());
  }
  BOOST_CONSTEXPR bool is_special() const
  {
    return(is_infinity() || is_nan()); 
  }
  BOOST_CONSTEXPR bool operator==(const int_adapter& rhs) const
  {
    return (compare(rhs) == 0);
  }
  BOOST_CXX14_CONSTEXPR bool operator==(const int& rhs) const
  {
    if(!std::numeric_limits<int_type>::is_signed)
    {
      if(is_neg_inf(value_) && rhs == 0)
      {
        return false;
      }
    }
    return (compare(rhs) == 0);
  }
  BOOST_CONSTEXPR bool operator!=(const int_adapter& rhs) const
  {
    return (compare(rhs) != 0);
  }
  BOOST_CXX14_CONSTEXPR bool operator!=(const int& rhs) const
  {
    if(!std::numeric_limits<int_type>::is_signed)
    {
      if(is_neg_inf(value_) && rhs == 0)
      {
        return true;
      }
    }
    return (compare(rhs) != 0);
  }
  BOOST_CONSTEXPR bool operator<(const int_adapter& rhs) const
  {
    return (compare(rhs) == -1);
  }
  BOOST_CXX14_CONSTEXPR bool operator<(const int& rhs) const
  {
    // quiets compiler warnings
    if(!std::numeric_limits<int_type>::is_signed)
    {
      if(is_neg_inf(value_) && rhs == 0)
      {
        return true;
      }
    }
    return (compare(rhs) == -1);
  }
  BOOST_CONSTEXPR bool operator>(const int_adapter& rhs) const
  {
    return (compare(rhs) == 1);
  }
  BOOST_CONSTEXPR int_type as_number() const
  {
    return value_;
  }
  //! Returns either special value type or is_not_special
  BOOST_CONSTEXPR special_values as_special() const
  {
    return int_adapter::to_special(value_);
  }
  //creates nasty ambiguities
//   operator int_type() const
//   {
//     return value_;
//   }

  /*! Operator allows for adding dissimilar int_adapter types.
   * The return type will match that of the the calling object's type */
  template<class rhs_type>
  BOOST_CXX14_CONSTEXPR
  int_adapter operator+(const int_adapter<rhs_type>& rhs) const
  {
    if(is_special() || rhs.is_special())
    {
      if (is_nan() || rhs.is_nan()) 
      {
        return int_adapter::not_a_number();
      }
      if((is_pos_inf(value_) && rhs.is_neg_inf(rhs.as_number())) ||
      (is_neg_inf(value_) && rhs.is_pos_inf(rhs.as_number())) )
      {
        return int_adapter::not_a_number();
      }
      if (is_infinity()) 
      {
        return *this;
      }
      if (rhs.is_pos_inf(rhs.as_number())) 
      {
        return int_adapter::pos_infinity();
      }
      if (rhs.is_neg_inf(rhs.as_number())) 
      {
        return int_adapter::neg_infinity();
      }
    }
    return int_adapter<int_type>(value_ + static_cast<int_type>(rhs.as_number()));
  }

  BOOST_CXX14_CONSTEXPR
  int_adapter operator+(const int_type rhs) const
  {
    if(is_special())
    {
      if (is_nan()) 
      {
        return int_adapter<int_type>(not_a_number());
      }
      if (is_infinity()) 
      {
        return *this;
      }
    }
    return int_adapter<int_type>(value_ + rhs);
  }
  
  /*! Operator allows for subtracting dissimilar int_adapter types.
   * The return type will match that of the the calling object's type */
  template<class rhs_type>
  BOOST_CXX14_CONSTEXPR
  int_adapter operator-(const int_adapter<rhs_type>& rhs)const
  {
    if(is_special() || rhs.is_special())
    {
      if (is_nan() || rhs.is_nan()) 
      {
        return int_adapter::not_a_number();
      }
      if((is_pos_inf(value_) && rhs.is_pos_inf(rhs.as_number())) ||
         (is_neg_inf(value_) && rhs.is_neg_inf(rhs.as_number())) )
      {
        return int_adapter::not_a_number();
      }
      if (is_infinity()) 
      {
        return *this;
      }
      if (rhs.is_pos_inf(rhs.as_number())) 
      {
        return int_adapter::neg_infinity();
      }
      if (rhs.is_neg_inf(rhs.as_number())) 
      {
        return int_adapter::pos_infinity();
      }
    }
    return int_adapter<int_type>(value_ - static_cast<int_type>(rhs.as_number()));
  }

  BOOST_CXX14_CONSTEXPR
  int_adapter operator-(const int_type rhs) const
  {
    if(is_special())
    {
      if (is_nan()) 
      {
        return int_adapter<int_type>(not_a_number());
      }
      if (is_infinity()) 
      {
        return *this;
      }
    }
    return int_adapter<int_type>(value_ - rhs);
  }

  // should templatize this to be consistant with op +-
  BOOST_CXX14_CONSTEXPR
  int_adapter operator*(const int_adapter& rhs)const
  {
    if(this->is_special() || rhs.is_special())
    {
      return mult_div_specials(rhs);
    }
    return int_adapter<int_type>(value_ * rhs.value_);
  }

  /*! Provided for cases when automatic conversion from 
   * 'int' to 'int_adapter' causes incorrect results. */
  BOOST_CXX14_CONSTEXPR
  int_adapter operator*(const int rhs) const
  {
    if(is_special())
    {
      return mult_div_specials(rhs);
    }
    return int_adapter<int_type>(value_ * rhs);
  }

  // should templatize this to be consistant with op +-
  BOOST_CXX14_CONSTEXPR
  int_adapter operator/(const int_adapter& rhs)const
  {
    if(this->is_special() || rhs.is_special())
    {
      if(is_infinity() && rhs.is_infinity())
      {
        return int_adapter<int_type>(not_a_number());
      }
      if(rhs != 0)
      {
        return mult_div_specials(rhs);
      }
      else { // let divide by zero blow itself up
        return int_adapter<int_type>(value_ / rhs.value_); //NOLINT
      }
    }
    return int_adapter<int_type>(value_ / rhs.value_);
  }

  /*! Provided for cases when automatic conversion from 
   * 'int' to 'int_adapter' causes incorrect results. */
  BOOST_CXX14_CONSTEXPR
  int_adapter operator/(const int rhs) const
  {
    if(is_special() && rhs != 0)
    {
      return mult_div_specials(rhs);
    }
    // let divide by zero blow itself up like int
    return int_adapter<int_type>(value_ / rhs); //NOLINT
  }

  // should templatize this to be consistant with op +-
  BOOST_CXX14_CONSTEXPR
  int_adapter operator%(const int_adapter& rhs)const
  {
    if(this->is_special() || rhs.is_special())
    {
      if(is_infinity() && rhs.is_infinity())
      {
        return int_adapter<int_type>(not_a_number());
      }
      if(rhs != 0)
      {
        return mult_div_specials(rhs);
      }
      else { // let divide by zero blow itself up
        return int_adapter<int_type>(value_ % rhs.value_); //NOLINT
      }
    }
    return int_adapter<int_type>(value_ % rhs.value_);
  }

  /*! Provided for cases when automatic conversion from 
   * 'int' to 'int_adapter' causes incorrect results. */
  BOOST_CXX14_CONSTEXPR
  int_adapter operator%(const int rhs) const
  {
    if(is_special() && rhs != 0)
    {
      return mult_div_specials(rhs);
    }
    // let divide by zero blow itself up
    return int_adapter<int_type>(value_ % rhs); //NOLINT
  }

private:
  int_type value_;
  
  //! returns -1, 0, 1, or 2 if 'this' is <, ==, >, or 'nan comparison' rhs
  BOOST_CXX14_CONSTEXPR
  int compare( const int_adapter& rhs ) const
  {
    if(this->is_special() || rhs.is_special())
    {
      if(this->is_nan() || rhs.is_nan()) {
        if(this->is_nan() && rhs.is_nan()) {
          return 0; // equal
        }
        else {
          return 2; // nan
        }
      }
      if((is_neg_inf(value_) && !is_neg_inf(rhs.value_)) ||
         (is_pos_inf(rhs.value_) && !is_pos_inf(value_)) )
        {
          return -1; // less than
        }
      if((is_pos_inf(value_) && !is_pos_inf(rhs.value_)) ||
         (is_neg_inf(rhs.value_) && !is_neg_inf(value_)) ) {
        return 1; // greater than
      }
    }
    if(value_ < rhs.value_) return -1;
    if(value_ > rhs.value_) return 1;
    // implied-> if(value_ == rhs.value_) 
    return 0;
  }

  /* When multiplying and dividing with at least 1 special value
   * very simmilar rules apply. In those cases where the rules
   * are different, they are handled in the respective operator 
   * function. */
  //! Assumes at least 'this' or 'rhs' is a special value
  BOOST_CXX14_CONSTEXPR
  int_adapter mult_div_specials(const int_adapter& rhs) const
  {
    if(this->is_nan() || rhs.is_nan()) {
      return int_adapter<int_type>(not_a_number());
    }
    BOOST_CONSTEXPR_OR_CONST int min_value = std::numeric_limits<int_type>::is_signed ? 0 : 1; 
    if((*this > 0 && rhs > 0) || (*this < min_value && rhs < min_value)) {
        return int_adapter<int_type>(pos_infinity());
    }
    if((*this > 0 && rhs < min_value) || (*this < min_value && rhs > 0)) {
        return int_adapter<int_type>(neg_infinity());
    }
    //implied -> if(this->value_ == 0 || rhs.value_ == 0)
    return int_adapter<int_type>(not_a_number());
  }

  /* Overloaded function necessary because of special
   * situation where int_adapter is instantiated with 
   * 'unsigned' and func is called with negative int.
   * It would produce incorrect results since 'unsigned'
   * wraps around when initialized with a negative value */
  //! Assumes 'this' is a special value
  BOOST_CXX14_CONSTEXPR
  int_adapter mult_div_specials(const int& rhs) const
  {
    if(this->is_nan()) {
      return int_adapter<int_type>(not_a_number());
    }
    BOOST_CONSTEXPR_OR_CONST int min_value = std::numeric_limits<int_type>::is_signed ? 0 : 1; 
    if((*this > 0 && rhs > 0) || (*this < min_value && rhs < 0)) {
        return int_adapter<int_type>(pos_infinity());
    }
    if((*this > 0 && rhs < 0) || (*this < min_value && rhs > 0)) {
        return int_adapter<int_type>(neg_infinity());
    }
    //implied -> if(this->value_ == 0 || rhs.value_ == 0)
    return int_adapter<int_type>(not_a_number());
  }

};

#ifndef BOOST_DATE_TIME_NO_LOCALE
  /*! Expected output is either a numeric representation 
   * or a special values representation.<BR> 
   * Ex. "12", "+infinity", "not-a-number", etc. */
  //template<class charT = char, class traits = std::traits<charT>, typename int_type>
  template<class charT, class traits, typename int_type>
  inline
  std::basic_ostream<charT, traits>& 
  operator<<(std::basic_ostream<charT, traits>& os, const int_adapter<int_type>& ia)
  {
    if(ia.is_special()) {
      // switch copied from date_names_put.hpp
      switch(ia.as_special())
        {
      case not_a_date_time:
        os << "not-a-number";
        break;
      case pos_infin:
        os << "+infinity";
        break;
      case neg_infin:
        os << "-infinity";
        break;
      default:
        os << "";
      }
    }
    else {
      os << ia.as_number(); 
    }
    return os;
  }
#endif


} } //namespace date_time

#if defined(BOOST_MSVC)
#pragma warning(pop)
#endif

#endif

/* int_adapter.hpp
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
*/