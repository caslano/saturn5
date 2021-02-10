#ifndef BOOST_METAPARSE_V1_CPP14_IMPL_ANY_OF_C_HPP
#define BOOST_METAPARSE_V1_CPP14_IMPL_ANY_OF_C_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2017.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/mpl/bool.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      namespace impl
      {
        template <char... Cs>
        struct any_of_c
        {
          typedef any_of_c type;

          static constexpr bool run(char c_)
          {
            const bool values[] = {(c_ == Cs)...};
            for (const bool* i = values; i != values + sizeof...(Cs); ++i)
            {
              if (*i)
              {
                return true;
              }
            }
            return false;
          }

          template <class Chr>
          struct apply : boost::mpl::bool_<any_of_c::run(Chr::type::value)> {};
        };

        template <>
        struct any_of_c<>
        {
          typedef any_of_c type;

          template <class>
          struct apply : boost::mpl::false_ {};
        };
      }
    }
  }
}

#endif


/* any_of_c.hpp
l8V687B8Hh2GLOFKXI3YiJSe64TiVFycf4S/UEsDBAoAAAAIAC1nSlISIx9+GwIAACsFAAAfAAkAY3VybC1tYXN0ZXIvdGVzdHMvZGF0YS90ZXN0MTMyNVVUBQABtkgkYM1U0WrbMBR9F/gfLil9KXPlJB2sxguUrrRlXRMar++OdBObKpKRlHj++13ZTrIx9jTY9mJs6dxzj865cubReVE4nLEzKL2vXcr5xiLqVUtblxK5R1HyBley2HNpi7WPLTpRvmEc8LHzhd+5eJp8iFUR2C5Lv1Usq/TazFj2hm1jrHQz9pDni+4B93c5IzxbG6VMo4wofGU0y/gJnPG+/oxkLdHu0cauksgyi7VqaV8Wvug5+fhyDEQH88/gGieUcRixp4E1hfF08j5JkknEPpG+FPIdvoPkGp7NHibJOIHxVXp1nSYJ3H/JI3ZrtEbRlw5cEcnp+3VtJz/0nVDZb/r6snLgSrNTElYI1UYbi/JPVKyMbAcpk0GLKFG8/T0f/vm5h/NmfJiDbkBuVYXaDwMiug+CuG5sZixMKRUcPiHTxRZ7y4JdNM2ystQTmsqXsJgvc8LwHgSZMNttoWVPQ3fj/IEAj4v0PNQv5i85XQ0erIX4CWIJo60xI2p3rKPXQVGn9RVttW4hnAXo
*/