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
r7Da+cXa7hojRn2LcuUDslWtUW2q0xA63cBcXDN/QVnjRiblxy+ClGi6vz1gW56wzLKZ227Li7rt3tBtt/g1kh0eEhbBWxnYrwEMBQmd4QmGYks0qdIZVpFGS2i/6e3YnKXNczKA8mT66rmC2ptfT3TRe7F899C7T75n0XshJO3y8DPkfeAcKhAxNTxETXydqiDeLgNUCBErHAIFUlTmKpk92sdsr0xeIE75BmyInrhGGn+e8VXr99L407LrsysiGZTIQ92k8hO129PeevVxzkRtGwQBIG3L31rxy0sM+brMfMUIJRMuFCxPYavMsDkiTPGmATlRfWlWxMiRVe9uWZdGSSiB3r7wPulyNOw+LeQBVg4ApFi1JUnpmgCOc48MTKd3S66SxQfEB/mojBOxbNqoFHSGGRvxzWqKUOR6h3kAH1FZmQ0tvtnPzEjTSjunPSbTjEnTMSvLPTsg9qqCXNaCZjdlqhzu+By12OLIWpyBHwfh+xtahigg6W0AybADQUuZmTxtZOoSn2mZJVNmG5m6xmdaYmndhuLu3quOdphQsqy0915V2EZUifeabpaobvZcnxtJo5DrdSMBYALG3eIJvNBE1+u9arUFRHcL9FGhepNpMbwnpDPPS6ySnI7oMP02NHUfxznqaaFEAWpdLuu0cHBCKNg1C3mJpelvtJGaP2gEe5ANxB+25xsoZS3Y3ksBD5kBesOH7Ab2/GgkTK1EMPp2JdW7jn4DCEQ5CPRT4ByMoPS7EKMnxaEJMXjS6zLxijEULtEwibuacT6WStTryAlNENcWp9PkPCSaIWgCAa07D/RHWpNe+goGzx/WTCk98Vv3w/8ixuNjxjxzzBjrpsMH69Ro3v7+UvR9NZ4X5Gp54Ap6U06uqtieZiWJOZGrX0SjBktYFgkWsr7X1Fbnb0W8EO37WKdNbn5X1Nl57zoW2wu/RNVVoPYc87xPQgeWt7QUQUvm97GZ6AkzCzLOiL5Cb94NuwamYioRL78+956cJDGF1Llyg2KP2CUVLWHDsj/s99i8skGC7UZD84OUGOTVExJhpbbfMrwr/0G0wWt66HTTH5uc0YJD44OGBw+IDxoZGmwCte1ybzXwtFxHJdgzYXRJgFOyyN3iciUkjfjQ/qbjMwjaJfRLqV9LSxnwPZR0NsHJNL3LqcG2TfAXSvAFNGx9uUW4m6KYwoW9VKBnqw6k5AFKztX3LrtJ7u/JfXl/uvcK8DQy+injV9e1xsLLlvpqHXROqDm2E5jNGAlJUlqS5ERPl+YlOWkUp0OPCdNXbJv8zo6O5VQVJFMGsqIHW7480b6WL1e0q/nlafmKTs7bqYSpZE5SKvyMZnZEoHUTiT0sgdiLe6vMNFVogNHNeKfQApLyBxDIBF4Lec3ULW8RyySyXp8E1vNe9ktKmciRmfYDIjF6wvRLsCvou9Sgx1ZZuCqE0pXqu9TB3SUjSXfp4l2Zljoz/8jRITOnCOkTo13uVfxYuTkJk043AwnSbaa1w0gxAIS6z6KYbJoXCVJpNBeBnlAPlFZKSJSmkX0IYiyNQxJ4jJKVGkGQrtT7AFG1HLZCvHTZ+LkehI+I5tiqw9v6gxWD8Nkc3UwB2SwBOU5XbfIONHqd7zCG0f8J9H8S/T+D/s+m/xfR/+0/PPv8Saqq/PHbYhJSOhR0IbRaMtWl1g9+sZHVTJPWJjFaG87L8hc26mV5UC/LI1uE6pI3KZAPqhOhRbKpLost9kCsbgnvYEXAw88KHU4RAkvoN+SMjqGyi4zFmarzEw9SBDQwkr+L5bdvOH/7ojdrRd8w1ASFRUp30bhNIL6tsiaFJ6lqc8ubvN/81hO833zZ80lUd7lM00ua9X4=
*/