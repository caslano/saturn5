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
    void assign(value_type value)
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