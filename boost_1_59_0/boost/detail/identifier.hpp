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
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
*/