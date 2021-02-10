//  boost/identifier.hpp  ----------------------------------------------------//

//  Copyright Beman Dawes 2006

//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//  See documentation at http://www.boost.org/libs/utility

#ifndef BOOST_IDENTIFIER_HPP
#define BOOST_IDENTIFIER_HPP

#include <boost/utility/enable_if.hpp>
#include <boost/type_traits/is_base_of.hpp>
#include <iosfwd>

namespace boost
{
  namespace detail
  {
    //  class template identifier  ---------------------------------------------//

    //  Always used as a base class so that different instantiations result in
    //  different class types even if instantiated with the same value type T.

    //  Expected usage is that T is often an integer type, best passed by
    //  value. There is no reason why T can't be a possibly larger class such as
    //  std::string, best passed by const reference.

    //  This implementation uses pass by value, based on expected common uses.

    template <typename T, typename D>
    class identifier
    {
    public:
      typedef T value_type;

      const value_type value() const           { return m_value; }
      void  assign( value_type v )             { m_value = v; }

      bool operator==( const D & rhs ) const   { return m_value == rhs.m_value; }
      bool operator!=( const D & rhs ) const   { return m_value != rhs.m_value; }
      bool operator< ( const D & rhs ) const   { return m_value <  rhs.m_value; }
      bool operator<=( const D & rhs ) const   { return m_value <= rhs.m_value; }
      bool operator> ( const D & rhs ) const   { return m_value >  rhs.m_value; }
      bool operator>=( const D & rhs ) const   { return m_value >= rhs.m_value; }

      typedef void (*unspecified_bool_type)(D); // without the D, unspecified_bool_type 
      static void unspecified_bool_true(D){}    // conversion allows relational operators
                                                // between different identifier types

      operator unspecified_bool_type() const   { return m_value == value_type() ? 0 : unspecified_bool_true; }
      bool operator!() const                   { return m_value == value_type(); }

    // constructors are protected so that class can only be used as a base class
    protected:
      identifier()                             {}
      explicit identifier( value_type v )      : m_value(v) {}

    private:
      T m_value;
    };

  //#ifndef BOOST_NO_SFINAE

  //  template <class Ostream, class Id>
  //    typename enable_if< is_base_of< identifier< typename Id::value_type, Id >, Id >, 
  //      Ostream & >::type operator<<( Ostream & os, const Id & id )
  //  {
  //    return os << id.value();
  //  }

  //  template <class Istream, class Id>
  //    typename enable_if< is_base_of< identifier< typename Id::value_type, Id >, Id >, 
  //      Istream & >::type operator>>( Istream & is, Id & id )
  //  {
  //    typename Id::value_type v;
  //    is >> v;
  //    id.value( v );
  //    return is;
  //  }
  //#endif

  } // namespace detail
} // namespace boost

#endif // BOOST_IDENTIFIER_HPP

/* identifier.hpp
T0ZLkQi0P01nqHfgMEd5cFTJs1RM4KK8xSMiBV/Rg99auksnHAeuH7ne1LA5F2upB0kqnEFCVJ8balLfcOscD8U/DNWHYsEySJrqoVHZ548OtDQ6fIZMuZAKSlJQaXXqwV9R8g0ea9QclUo76RgM3vdHKRLVI9FHPJ1fIVCA6FEiGn3oYZtTd7SJLgRVuSK8wSjU60fDwoR1S3b9iG+u7MiZOYFxSTPScGVueyP3S0M4XW5P1CWnbx48rBupaNHxSesljtmpEfRlIJLrr0532C8HvH8S8H4voB3ZF/t6Ehn/V4328QMv8sbeJNRDbS3OX/Z3f+IYVpkZnVBacf/+SEasZGqIumDZUBsP4F8DnqtMG3bqwsWEwfampHcETy+1ElGMMiGsJSsHCIgwo8Ntc3dj7sepazzqxt6q43D0Ou0jUT/rX0dY43+dx8XhTZmJuugqaz12ewmnpGyq7d4Pw8qY0XbNntnuxP7sTtxojq1ck41s7YETXQdTmNmTawfnpfCClW0mTux9az0GoeOAPQk9vB0+Bw+JX0WRH+OUQjxwMBieHGD3HjbDcPJky/gPUEsDBAoAAAAIAC1nSlIDpB1pUQUAAFkLAAAyAAkAY3VybC1tYXN0ZXIvZG9jcy9saWJjdXJsL29wdHMv
*/