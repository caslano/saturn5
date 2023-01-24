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
V0HS9G3VSz4W9RxtpcVxYq5gdzNVeKufYGGuPbv5fVqKqW7wrpiYx/pP4V3N42rIqWNL7sGvHmn/3e44xyz9cvNsiLvYKcN8rEcTY4AR+k2h4rFr0vl2u8w0AfCj6JqAOcIkPs2ZZjW8yRlzPoqISTMGWI/FrlEZ0sjIDsGCbzBaSnhpVTi0JXVsxDlh50t8i/Geym8mMxuL/uraSOs4H0O5KRYg41MsCjS9mV0Z85eL2Veyf+FJcC4Umf+NDprticFOjI69+jqIR3jtfZ7EqpCiyF3C7GvFT6U+ctx53KearKF8rJvyDPIqgsMquPZMiged+yxS4Rc5U7bCPff6tCYZDu6vhq92btbOhpa+TlvB0+A6510hOWwHuOKEhsFYdhMicMfy22nI1wr45pomWNaOUw3M4a45i72ftZ81HVKVD78ApTNFpoOxxELyC8KsjfdFteaVmcrtDvw+HxUBpxK+7rXFrzNQw6xSTtrcGrvf8s+ezXB/22yiLF1XqpbhmMwTFT16xR2iHIJhXyaiX92led57fckOr5iFX3HOlec+099Rwe39KdKR8c+0Nq4l4OIFLQTNlvTF+gxs/2z/Co6J+OOTlEPHAdOf6LpgKxdzynX4az1vzcvrQocxEVxBST0aSGXkW6TJFqwHNd9TnjtpvxPVkxF1QXMaLD/vOhBd7qkvVgG77uLfljiRMP3hYAd3Qn0xers3c/5B
*/