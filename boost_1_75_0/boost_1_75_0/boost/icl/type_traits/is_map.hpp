/*-----------------------------------------------------------------------------+    
Copyright (c) 2008-2009: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_TYPE_TRAITS_IS_MAP_HPP_JOFA_081107
#define BOOST_ICL_TYPE_TRAITS_IS_MAP_HPP_JOFA_081107

#include <boost/config.hpp>

namespace boost{ namespace icl
{
    template <class Type> struct is_map
    {
        typedef is_map<Type> type;
        BOOST_STATIC_CONSTANT(bool, value = false); 
    };

}} // namespace boost icl

#endif



/* is_map.hpp
v4HV1CclA04rgO1HqzwaYtmUrYEEkKwhi09lTVMz+I02pwqaMqdhmuyKhbpk3YYGnEyPwbSeo3YUljFIvyZUHqbpDZI/ph2d7a5qGkORvJGTIBSc5DO9Pwm6ZYW7STCuH0NJqMMOWWJC0CYToFGP61+Joe/GvO2htWOodXUYiDao7p+HHObriAmRHfu1Mpk3+eVrcGDWmPeYrkt+Qtw6fFXjxuphw7WC0+uKRjJxIMBq8GfswrXqF53fwkJxsZ+1EYawN+q+2kKidCs7LkqTRopYSim9ta5s17K2gHC4C9RmCREsh7yyqqKBxLYhM0TDP9+PG2wLT1beumrfp+T/o1pK8aKoP6CL4rfZMBfuJcMDN74KRR5rXByrE0of8iZE2CAfzVLRq8FvgT1KzUro5hRCG6Cjf1GWzUZ1bnSRCth64wHc80lq6ts9PQsqrPzIxxIkXxijof7u9NgivWJM99hf9WcUZNeNKPFiSqvwZWTyj/Aq1HFk26Et+cwOi6BYdX63Lt0hwp/fxaJG5nUmvpHa7dvmy3IQxAqI7vJ1aUKFurDccIxWwBvzqzSfxlAjheZDm+bBXkDyRvCskAaCrOGf81pIzMn9tauEGDbX6aKI1QXtHL70xVHVC/HSMblOYvp3LosvMsdvsZdcibl7HHXNqsK80g7TQNbC1e+0hzV9QapFTFVZNzyb+NJgXmldmj6Dm4uDsytPQBct
*/