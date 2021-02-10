
// (C) Copyright Tobias Schwinger
//
// Use modification and distribution are subject to the boost Software License,
// Version 1.0. (See http://www.boost.org/LICENSE_1_0.txt).

//------------------------------------------------------------------------------

#ifndef BOOST_FT_DETAIL_TO_SEQUENCE_HPP_INCLUDED
#define BOOST_FT_DETAIL_TO_SEQUENCE_HPP_INCLUDED

#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/mpl/is_sequence.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/type_traits/add_reference.hpp>

#include <boost/function_types/is_callable_builtin.hpp>

namespace boost { namespace function_types { namespace detail {

// wrap first arguments in components, if callable builtin type
template<typename T>
struct to_sequence
{
  typedef typename
   mpl::eval_if
   < is_callable_builtin<T>
   , to_sequence< components<T> >
   , mpl::identity< T >
   >::type
  type;
};

// reduce template instantiations, if possible
template<typename T, typename U>
struct to_sequence< components<T,U> > 
{
  typedef typename components<T,U>::types type;
};

} } } // namespace ::boost::function_types::detail

#endif


/* to_sequence.hpp
Htg5ywG3n5Gc9f6k529fNHIhbqTSNGLKDkO4w3y2rcAw2A0T0lgn4XjAIdVMmkZp68NjCdEWR7/pOuebtAi3LU0UzVmxd4jaVN5hmuEFTAdfkATx1SR5dvqqRylX0qKcMKR7xAZRihyNYloEFGuwNfCdUigUjgapbD/30OEXzptO71AfrbDHgZVUSCSH7e3iUOhB8IfiXwSrWeosVrNZJ4iXURpNolniBHXdkRS7GXFqtLIqV7V5A5dpGiceXHS/03lASxzFZ7gkcxTiwM976+HnYB7PQseXpdMTs8P6929oi/naETJRlCMSnsDfDnzPahI8sBkXD9zDeOb3DEcG93O1G7to6YfqSJpJuEzRRN93fsN3T1Xsusgl6j5VCTXiIEmucdi55izX3PZquDkCAkc5NUCPwrHdvOZMts3h6B/HL0WHb/ApmM6C99PZNF0703IgMBWNS/oXK/oyLMN0tVzAp2C2Cp0lt/h3YLr4wiy6og4gDZrubUO05oU3nK4WV4voepFF3XSgm8g4D4nrDNqrNIsusnk4j5ZrOqZhzrtewhZqS2RvN9gqzhochiznfUBuEoYQzJIIp+f7JXzfzeBiPyNgj2t2kDv/AlBLAwQKAAAACAAtZ0pSXZwpBrUEAABcCgAAMgAJAGN1
*/