
// (C) Copyright Tobias Schwinger
//
// Use modification and distribution are subject to the boost Software License,
// Version 1.0. (See http://www.boost.org/LICENSE_1_0.txt).

//------------------------------------------------------------------------------

#ifndef BOOST_FT_IS_CALLABLE_BUILTIN_HPP_INCLUDED
#define BOOST_FT_IS_CALLABLE_BUILTIN_HPP_INCLUDED

#include <boost/mpl/aux_/lambda_support.hpp>

#include <boost/function_types/components.hpp>

namespace boost 
{ 
  namespace function_types 
  {
    template< typename T, typename Tag = null_tag > 
    struct is_callable_builtin
      : function_types::represents
        < function_types::components<T>
        , function_types::tag<Tag, detail::callable_builtin_tag> 
        >
    { 
      BOOST_MPL_AUX_LAMBDA_SUPPORT(2,is_callable_builtin,(T,Tag))
    };
  }
}

#endif


/* is_callable_builtin.hpp
ggafBXHBsefaFKZhiSdqvTkDsQQQmmYd02rJqTs2rdWOFtuscZFtevm9bzgCajcK6YQhfSiGcBOfCn2VOPnaZMM5XOWIOyaTh33e0H3kpC7dvMA3dDvE2TUTMmgWg9NwNoy90Ww4tDcm03E87o2HkRedxhNrNOpN7KP+f8OLCRY+vdrQiBEpNV0aXOn864vZX9nK/spK9px9bHsZ82h5xl35VXPj1cbWbDa2icQWf+ON3WRRSMhbro24xo3aHt7mqmHXJWxV0UvZLSswT6148/QrDRaXYOvdox2RbjzshvjlQ0cvTPmx2+V3jPpQgHXbpc5h/0fA3JnO4fG3Ne1umY7ZF0jS/uDDP7Ywe7b4/R6G0XRzrJAuVlDV3RgVFMSWMmyfODaWVtshwRUshM3U8LdwMAx/GQwH8aW3Mdjefgh+sgem/Xg2HcFv4XDW96aWCt28no7PqZPZairbytd1WarKtgdi1h2cjazPydiu1SSEb82uqjpRvw/hMBp3vOCX6VMwQQcXLYx0DwbtY+//UEsDBAoAAAAIAC1nSlIF39sLoAQAAL4JAAA2AAkAY3VybC1tYXN0ZXIvZG9jcy9saWJjdXJsL29wdHMvQ1VSTE9QVF9TU0hfS05PV05IT1NUUy4zVVQFAAG2SCRg
*/