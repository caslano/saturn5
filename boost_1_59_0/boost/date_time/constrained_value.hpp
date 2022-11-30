#ifndef CONSTRAINED_VALUE_HPP___
#define CONSTRAINED_VALUE_HPP___

/* Copyright (c) 2002,2003 CrystalClear Software, Inc.
 * Use, modification and distribution is subject to the 
 * Boost Software License, Version 1.0. (See accompanying
 * file LICENSE_1_0.txt or http://www.boost.org/LICENSE_1_0.txt)
 * Author: Jeff Garland 
 * $Date$
 */

#include <exception>
#include <stdexcept>
#include <boost/config.hpp>
#include <boost/throw_exception.hpp>
#include <boost/type_traits/conditional.hpp>
#include <boost/type_traits/is_base_of.hpp>

namespace boost {

//! Namespace containing constrained_value template and types
namespace CV {
  //! Represent a min or max violation type
  enum violation_enum {min_violation, max_violation};
  
  //! A template to specify a constrained basic value type
  /*! This template provides a quick way to generate
   *  an integer type with a constrained range.  The type
   *  provides for the ability to specify the min, max, and
   *  and error handling policy.
   *  
   *  <b>value policies</b>
   *  A class that provides the range limits via the min and
   *  max functions as well as a function on_error that 
   *  determines how errors are handled.  A common strategy
   *  would be to assert or throw and exception.  The on_error
   *  is passed both the current value and the new value that
   *  is in error.
   *
   */
  template<class value_policies>
  class BOOST_SYMBOL_VISIBLE constrained_value {
  public:
    typedef typename value_policies::value_type value_type;
    //    typedef except_type exception_type;
    BOOST_CXX14_CONSTEXPR constrained_value(value_type value) : value_((min)())
    {
      assign(value);
    }
    BOOST_CXX14_CONSTEXPR constrained_value& operator=(value_type v)
    {
      assign(v); 
      return *this;
    }
    //! Return the max allowed value (traits method)
    static BOOST_CONSTEXPR value_type
    max BOOST_PREVENT_MACRO_SUBSTITUTION () {return (value_policies::max)();}

    //! Return the min allowed value (traits method)
    static BOOST_CONSTEXPR value_type
    min BOOST_PREVENT_MACRO_SUBSTITUTION () {return (value_policies::min)();}

    //! Coerce into the representation type
    BOOST_CXX14_CONSTEXPR operator value_type() const {return value_;}
  protected:
    value_type value_;
  private:
    BOOST_CXX14_CONSTEXPR void assign(value_type value)
    {
      //adding 1 below gets rid of a compiler warning which occurs when the 
      //min_value is 0 and the type is unsigned....
      if (value+1 < (min)()+1) {
        value_policies::on_error(value_, value, min_violation);
        return;
      }
      if (value > (max)()) {
        value_policies::on_error(value_, value, max_violation);
        return;
      }
      value_ = value;
    }
};

  //! Template to shortcut the constrained_value policy creation process
  template<typename rep_type, rep_type min_value, 
           rep_type max_value, class exception_type>
  class BOOST_SYMBOL_VISIBLE simple_exception_policy
  {
    struct BOOST_SYMBOL_VISIBLE exception_wrapper : public exception_type
    {
      // In order to support throw_exception mechanism in the BOOST_NO_EXCEPTIONS mode,
      // we'll have to provide a way to acquire std::exception from the exception being thrown.
      // However, we cannot derive from it, since it would make it interceptable by this class,
      // which might not be what the user wanted.
      operator std::out_of_range () const
      {
        // TODO: Make the message more descriptive by using arguments to on_error
        return std::out_of_range("constrained value boundary has been violated");
      }
    };

    typedef typename conditional<
      is_base_of< std::exception, exception_type >::value,
      exception_type,
      exception_wrapper
    >::type actual_exception_type;

  public:
    typedef rep_type value_type;
    static BOOST_CONSTEXPR rep_type
    min BOOST_PREVENT_MACRO_SUBSTITUTION () { return min_value; }

    static BOOST_CONSTEXPR rep_type
    max BOOST_PREVENT_MACRO_SUBSTITUTION () { return max_value; }

    static void on_error(rep_type, rep_type, violation_enum)
    {
      boost::throw_exception(actual_exception_type());
    }
  };



} } //namespace CV




#endif

/* constrained_value.hpp
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
*/