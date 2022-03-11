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