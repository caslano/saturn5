
// (C) Copyright Tobias Schwinger
//
// Use modification and distribution are subject to the boost Software License,
// Version 1.0. (See http://www.boost.org/LICENSE_1_0.txt).

//------------------------------------------------------------------------------

#ifndef BOOST_FT_PARAMETER_TYPES_HPP_INCLUDED
#define BOOST_FT_PARAMETER_TYPES_HPP_INCLUDED

#include <boost/blank.hpp>
#include <boost/mpl/if.hpp>

#include <boost/mpl/aux_/lambda_support.hpp>

#include <boost/mpl/pop_front.hpp>

#include <boost/function_types/is_callable_builtin.hpp>
#include <boost/function_types/components.hpp>

namespace boost 
{ 
  namespace function_types 
  {
    using mpl::placeholders::_;
 
    template< typename T, typename ClassTypeTransform = add_reference<_> >
    struct parameter_types;

    namespace detail
    {
      template<typename T, typename ClassTypeTransform> 
      struct parameter_types_impl
        : mpl::pop_front
          < typename function_types::components<T,ClassTypeTransform>::types 
          >::type
      { };
    }

    template<typename T, typename ClassTypeTransform> struct parameter_types
      : mpl::if_
        < function_types::is_callable_builtin<T>
        , detail::parameter_types_impl<T,ClassTypeTransform>, boost::blank
        >::type
    {
      BOOST_MPL_AUX_LAMBDA_SUPPORT(2,parameter_types,(T,ClassTypeTransform)) 
    };
  }
}

#endif


/* parameter_types.hpp
9DmCwfbtaKsSRtvSHMzuMlscn1qK410LhObBFfAJS5E7nlqj73ElrN72AMVXo4XHXQeONK1EizNLGXXvNJz7pDNim454s/AmxBkbdtx3Hpn3GqTT9G3896eGHxy28Pr2u3x5+Bw6+h6TocIXc4817RnP+zNCLJKr1kzl88AVwq3dUNxRXSImDHPi8k1N/PJ8JeZvCBPLTl5F0tSvInv3BZ4a5Y7Ky4b83qjCmFWSfat3SsPBcfixuLfckh4NzzxzbnA8wZ4XJLwSjZmxsCvH72xAwKhNIvpQIpOVf/OfzTFY31ORF7JnU6ffYLEs9ww0b/TBluQwPClojpMlzzBp2FK66F3n9NRiXuzegBkn5nKNTjKspxUIa5vdTT36fJFkd5+/HH+LC74rGZd2E1uurIOtdOD275PZ69de7opxa9or28uiHC9EFK+jkVIN4kIPIGBmNlVWvqb9K8F//4bIldFruFo/UOTYPuf+h0XsMqeeKr+2i6nzzvKnXjlMXC/Qe/JWOf2IPo9ttIF+0kCqXrXhUTctuN9ZyfFvo/DggpCtY+wQK7oz4MhH9oh6I9yqF+CNWMmHWQKOzfYI7eGD8KXkGM81FDJtmiJcrH7i9alIftfyZbG3nbx9XwHLdDT54KQvXeYtFO9HuXHx/Qj5znQhPnc2EYbBXbFEwV7Gv/yCjxUhcDcNwuD4b+h3azymnGpizS6uNH4ZL+Ir/1HLU50LbAaiS7atsG88hIfGltjTehpmKiWJf/enQt3DmkEiE202mQlblX1sfHdTtJuUiDmn5spRCwdRTzNDdnncDh0+PpN/xv+HhRNTEXVfhwdr/Nh32BQ+mLNZDhr7FyMjamT4QBPO62aE3jaaTBnWXt6wnI020SnCdftaHPP0xNqoycweHSr12rZl1O1mctakARh8Ik0O8mqJ8BeRostFd1h0sxVfDQ4zZdNf+eTOLcYt2CGNdKvxTOTI+AQt7K7RE9oGK9nuZyZLj6/nxaSH0nLkJOgWGyMvZhSvuTqgnacyerSeyq2BddT76YYJV9pR6WkPKKT44UfFK+F/347Nnj0UGZtn0XFxXtP/qIepdzSFU5cfjI25Dm3vUDwc14I6xhE41KZGBM6p4N/gfJF2aRXmv5nCCX/CYeBpgAXqM1GrvVqeWmTNzndaikAzbTSO7yHHfj3Hk2ov5OikUIwIbI4ZXpVYeUIXe2e34tguTU72bCinO94gIm4yYmK6XDYtkJVHK0WwbRXz2n4VR1Zq8/KiV7h8qj1ueigKtdH+TbvnZcb6+zMsY5ac+H0FO3u1YemrYTxj8JneM1awZ4fVvPZ9IUpt93JS0R8uOeskgiIj8W2bsijN0ULe6i5iSevP8LLbK8LqVfD92AW5yGstMncflrrGs5v45WAMMJrKY7eiYP90ARLaqooWk0qYIyMxMzUXixTXS9/F5/nvEeSJ3OEwnlQvjJt4kdKY5dJ+sSE/XPkjdnEryvepodJYA2vFDxacPciFCxVlWrtbTHBbKRLbNjDZrpXsamJBpd7N+MfFBF16hIuLEUpw8ssVGXaaSHOUcvWIB9A0sMQ6o5bYMy4cZSX1dL/9TiRYvEZMqjb3LtnBo005NEDPFV8cPkhjrxO0XFMjDtePYFA/NfFjZi1sJ3QSjmWTOX3cWGaWfoJZuC0TjmjQa81r+bJvG25J3wbH/OtYNMQeOTKJ79q/kAkWK1haNoN93xbgVOkB2fNme5xIaSOU5jvyTaIdTj3/yPshhtjs9JahGZ/krlWb6HP+q9R/05EmHc+zbGUGOn7oJf9TTUSpDBHB/ZbiwLQnfPatBCPyt8rqkRtwLtOB9aq/qXnQnEoHlTBjVzLX/Xw=
*/