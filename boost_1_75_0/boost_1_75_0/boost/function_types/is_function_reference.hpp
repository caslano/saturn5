
// (C) Copyright Tobias Schwinger
//
// Use modification and distribution are subject to the boost Software License,
// Version 1.0. (See http://www.boost.org/LICENSE_1_0.txt).

//------------------------------------------------------------------------------

#ifndef BOOST_FT_IS_FUNCTION_REFERENCE_HPP_INCLUDED
#define BOOST_FT_IS_FUNCTION_REFERENCE_HPP_INCLUDED

#include <boost/mpl/aux_/lambda_support.hpp>

#include <boost/function_types/components.hpp>

namespace boost 
{ 
  namespace function_types 
  {
    template< typename T, typename Tag = null_tag > 
    struct is_function_reference
      : function_types::represents
        < function_types::components<T>
        , function_types::tag<Tag ,detail::reference_tag> >
    { 
      BOOST_MPL_AUX_LAMBDA_SUPPORT(2,is_function_reference,(T,Tag))
    };
  }
} 

#endif


/* is_function_reference.hpp
hZfDq7lsCZrEtnGYkpvts2Y62L4ZFmTiIfrh/zlsze7O5i7kQFGevolc4CFvCQEvRUCCbhlvyFUT5YyAFrJN3BUHAghtkYmdAw/0ONXFurtaD0iOhUCHLeN7O3dCj7QLL/SM5GbMlPMVEsXd4IYesoK4FGDsoHnznMVUaC65AZ0QhBzYRyHn8hx1S+eILd1MWxrh8/gYvSdQuOYlAHEFvD1YNxDby5b+twQtlDHGD3JKj6MHq0AD81SezOMLTv3ee1Knm52WEDeMMnIArpbv6qbLyJHMCPH0Jrsn7SyTTCdPSfcMYqy7s16e/jC6ekyX8Q3mzpDllP9gbOtRatgyTIfmGdaklBWwBW60Adg661LclC1BZhYq7y6M0vHD9Hl7jPaGs83rP73J/EKlSFZxrKdKKabR7hu1brM+1vDROhW1zxVruPtoQ6xhzObnE2sYXZzaFGu4oDE9UKzh3lqs4XjfOuCnCJZ9V7NW1UDDj40yBBo+dYkh0PD1UyDQ8C62qFr8eQgP/fdOdfaJyA3eFqFaCphHCen1Ab5HtODQz/8ujASKrsG48lDoJyQ0OaSx8Tx0iUZ0IEm631MLcq7PUP2tDHGsb9MN1DeO9biRgeNYy7/F/p/HsX7tYr9xrKcDEVXzmuWzGRTEQ7hGTReP0eUaOHrZHexfDoTKc7jtRRnJh9LdD8KrbIiqx14VpM95sCjL/cEslBc/IJn/
*/