
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
MnN8sW4d2mKwKpjaJnVCxFHv/BSsdUz4V51sh3jF/MDS7pV2SIco6rWpfmB573HXQIEH7dDYJ37xgMuziGEa75HOzbEIElVIe8nklhRpB93APcYMuoNOZOmMgpD0ZKXwebiaI9Z9uK55R38Von1TvASxLWClNIrK0ApbjgKugETkMrVkCLUPQ5oAguZwCRXgwqjrCQgxFX06GNw09AitSoBEvMtxYjkzcMvR526H3TfZMxeOkKM1z0Pdl355ZvBMNil5hODmK/rjLRyJluz2H4fK+jraQxDVWNbb7XqiChPmfQLcCauSKvaO/ExcTPgJ36qcp7+GTMUgCevhXtaAZW7je/AdSXVCxFl5m8TZv2YyoaNkf8P8oobJWFajBH23E88ccT6En8ZW3wHICYCWMJpdqQ04VRLKYLKbuTMVEs+Szt1PhHSaKAV1o0/3WPWlOEzzyOVoEbBgjg2tGBmRrlmUZY4v0NMTFeHKPRXzGp5SHBiYD5VTmkqinZ732zDoUFH802dH6X7jWLGUB/vRN2IoE6EgdFpK9dSpF+tD9Bi49QZcb5W6hnglSg==
*/