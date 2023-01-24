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
1Ai1B6sLrYuoK+ww15ljv5naHyi0irL9bvvjNtL2pwDENqKu0OdOxSYMP/RnzRuHXSJnZq/OPwtxvO+239egXCPx/O0ZSNzXqdHtJ5yetsIvzmfUtP3xWK2e3A/lWXEXcRdTA/7XvtJNzsK6kdNevrA5yXKcZEysF5DdNkRBiIicV5DfvmmoaKxAe1QGrHNc5zBsVu3/1spMds7jXbgQCSBOFfJ5EvLMgD4aD35D+XCpudEyaSa7IUPCrbRmIt6alDrnO/qHh4mD+y9Osw6u9SLppFN/a14yDlMPp0queBIxMXXXxqenzrF4G0J/j02iS/8ktvXyjWCCIIehItey7j/lT1+QpKJP63w8Rs6SK9ug1B2fRRr8izFk2TrIeH6uNhWFLbDY66JueH8kHHkwX/S3XzDzD7toECcnk1JbeSfnqRUlEWdC8y0b0cf+SzmAAGUyhDQ6L1Ezr4om7+mXuuBfUXqQhQUHzEEJEAUHG8mS9NCF6K2jL6dtyINwsJV71tP9WpQeJY/1egTK9vxCN6i1qLNVL47Gp7Pg0AUeu95hOHuWFuYg9KK6WFc4HL+HTlN9+GOeUOOijS++yd1RikbEm8kkyyPxxH1Iut/FTgZ/uZdArKOa8TWc4UoWLI9DZ3s+IArMp3jnQgGf3n75XlbTWm+yUrPdWxMW5tzWbOJpLL1qpDcim8mZ3nTpFa1crkAa2PpA92pfs90t
*/