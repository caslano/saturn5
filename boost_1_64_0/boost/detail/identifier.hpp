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
cQKFi2n2apANkxg+EaqGiRCATWK1VyecxWrJIDyCn/wkA010pxspqld+RFR8/KrxCasLwxCgxN29PPRfj5tVPiKRPIwYv4h5YM0dHn4LUw+YBkqSTSMGIEkCe207ixjxl6TbSZzzQaCFAUCpq2kpw0xTZJwEFPIB4M0IaCSl380QYH8OIR4o8Wrpe0tsk2YQ+el8jFZcHauGvlqX6vOTHubGyn3V92xvPHrJMwC/mL1kdy2ozfLYAfD3XrWq8f6n9y26yvdMoLmK3rREDrWAtIwGOT3+aSpcLb1WMe5hRZuiq/ax9Q15XeNJOsht7YaWPwpa/kDR8ieQmXbPCyKQvycRloQTnU+d6JGxLWrBmvC3uPgrgHd7mcB2QBBmKyXMum+yuc3h1GN+ndLyqAtomW6m5Ruip7FaoRVhlKLnhkIlbHLEZWkJxXIcYqkxY7mZYIlu95QkSw9cBbK0zC5Ovy5p6HCQaKF4f/hJxRuA+Xyy6tOPColNuve8i+igCDlA/9SJ5WCjI6XkZjDclJCbIXDjiw3u9EEH+bBcLL+zjC362tkkK40wIVohXzlDT5uZBT/KI4tJLjaJYKSIm1I/2TiOo2BP3FLcB/Bsfyx7qyYI24lZ6D160WAHLoZN3759Mk/rHcw3FOFkGke7Z59IBJ+m0KnZZAeISAREZLoQkdOJpYn5YxcjDejMtJCZHl/SQnp5ALpm3pGIKKfQodxNdvvLzMjxyBJ/CLBAZRULJYViRbTnr+v5Oy2bZHpawYic+DZfZDj0fbHI0OiUbBA3Shh4hAypi+vRZeCJ0EHSQgq6+re6aNz0z2F8KexM0ezFT+OEMYrlxTTMiMZfQqND+3WVP+Js6Ny4JkCnD/dQnG2I81gzzvlPIc7zJZz+GdW+6Wj45tGC9ViwxVzwVFKwZ7RULBAmW+lgobaRDWLYv3+xdyTgTRbLpE1pKL2AlraAEE6DIBYoWO5U6jNAxYAoBUErIBZBrZBCUe4WBWs9AAEREPFCQRFELEWxCAKK+sDzPY8n3n+NBxYPniJ9OzO7++//5w9NAX3H9/IpTfaYnZ2d3Z2dnZm9dwewFEkbLxI4O4KbagTXFcB9ZFOwKLUVa07viqzy3RHkC/x7GrqX9lttsUTvJdCPsjK4oKmg39vNQM9XQQvRgrVBfkQDnbjuMn1wGWwgLfchQfvgC/00Hf5KDVyIDaw2NjCNNYABAvj1NMoY41h9cTfpBp6AqUEbTkpW+QfUp5+Pp/GNoxVTqlf8yIoQBu89cbSG5sgdwF2oMX31c9SYFv1XPV+gWmHaQf5/V8yfc94X8wdV03Izh2VMzJ8C0/zxQmKRMn/oQkeZP1NpnFb/JufPQjlOb+xCXs8RXpMq0/qIaT3ItHFv6kw7gwDmIMCpRoCzGMCq1zhneQEc+IKxfZlGN/U34tg7VhoFDmSouQT3x1+RY41w2zG4gekAFGAKNawXbi1ygCuIT33a/fuRTzNgmeR8ehvvP4J9wNT/SgbWlQ2GBlJI8KAGtcMGVJWmcx5NRx5dTL0YxkDRzjTra8Gj2Hq39UdrhCTt4zza/lPk0fz/GB41WwHveEueP4uMJigi6EOuupKnW+7UXrEluznX3WSne9N/AtUXANXvkFTPfRG5rg2jJt035WqDXtFPSukCVjpZEv0mzkpoktStki788CBGlvB4avg7GZJEoSumtBSGdYZfz8TAv+W2CFYLDxYSoutr/a5rHqFdcAzQvsGI9oM7GW93Echgz8fZpIWMV6ybOHegXwL+Zfs5xj8hBrfbkYniWBOk/J2z3GL5LiNEvvoFJ4MRkVRAZL0tLETIAkHi8so+XZ5ZSk2UYBP5xiaefYFNDC8=
*/