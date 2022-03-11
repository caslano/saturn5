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