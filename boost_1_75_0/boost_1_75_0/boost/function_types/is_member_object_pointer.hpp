
// (C) Copyright Tobias Schwinger
//
// Use modification and distribution are subject to the boost Software License,
// Version 1.0. (See http://www.boost.org/LICENSE_1_0.txt).

//------------------------------------------------------------------------------

#ifndef BOOST_FT_IS_MEMBER_OBJECT_POINTER_HPP_INCLUDED
#define BOOST_FT_IS_MEMBER_OBJECT_POINTER_HPP_INCLUDED

#include <boost/mpl/aux_/lambda_support.hpp>

#include <boost/function_types/components.hpp>

namespace boost 
{ 
  namespace function_types 
  {
    template< typename T > 
    struct is_member_object_pointer
      : function_types::detail::represents_impl
        < function_types::components<T>
        , detail::member_object_pointer_tag >
    { 
      BOOST_MPL_AUX_LAMBDA_SUPPORT(1,is_member_object_pointer,(T))
    };
  }
} 

#endif 


/* is_member_object_pointer.hpp
ouFt4ejfuNDXldroJw2MxcJajbHgftJecQaWDfOKMwB+z47Uo67w5MqGlXybxGL8gOEFene4VaSFKXwMpYNMz+B6nT955UQr9ycXjvgpHL24fywovPOpoVITKdlTVARJ0aENTj9a52Xe2I7SZPLxHx7qN1iBhknIiRR0JbdU3OuMI0H9BOi/ighbXivgOrWCgDEKnDWtrvUjQ31DuQ8ukCXG7egjpQwY2pbFXXOBn8X1M6blW1sd0893+YypVCkcwgZWJB+baRzYe3e1ZWCJfgZGku69j3rH/NHxG0Aio7SxQvicLKkhWWE0tIINtgIGcOVdXNoKBx4/TTqBd52XBIGhQ/+bzSVwweL0TC/KJFa0V6a0IbP3VnO5Jd1c3i7C3rvWFekorgzOgGydEMiZoW8wWd7KYTBXqQ4VuJgPskZ+nnFJ9uLNSl66exykRnfmIzsNerRMT0a940Sd88JmZ89/uBu6A8Mp5GGstuWvocHihkxpGKQDJ0kKdgN4Zztcd6CgDH08PR34EWe+sQ3o0KcRNfKCmq64051WygPeOEB7efIOJvE26/RMTXfAqnWgil1EmhsDOd2ghg56OFYjp0zMeNzhnUv7ZhfZ6bgCxaDI3Nwqvj10hz98u9PhwXAT8szpRpRLvqMtKPd1l0Aod3CCzzi9cO7lTXqcO4VhIvQ4tzzbB+eUwuRMLa4Kw7KqzN41rWLZaWB9Pe/N
*/