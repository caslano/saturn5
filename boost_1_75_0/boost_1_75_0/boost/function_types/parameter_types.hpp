
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
imWLDd9yDZoIFiXnZEJEZVENmoW26Y+PWQol37CTxwf4EgADsyPgs1ApDqsCzfD2RNnkVkfRaUKCA4ZkEsMutkCrM+aqfE/rGG28fstpR3PbxXI0x+Q1YTTnX0qjeRmETuxL8HJqItOLsqt4WXcp2oVyV7gX+PYMeNsFxUVyNvJFrS7fS6WW1XgDNAUpAgUryAwF9aSCMkqebl1eJDsGe+BpO7bpEurYpEgdhi/FU1FXZx6kPMMLdbk5/gfGJucwRIL25aGjHrqfXYlOtk/TIfvroj4EyBu7TkrTeJ9K5sduYm0iybCBbQzNOa2UHoA4eIfIe2wKdy7XWD6cAZpnAjSPAco1AfoMtdtzpPHTMIml7B1GI+889YmTLTGe5ygWXAaAnWcCO0N/C25TWnWIhhrEd0DLKv8qukigYaN91oAIAhPp9o292KVT8sB22SnNvgP3pRYBZ+debTBoVa4lgos7KIKL5jq372L6IM+c2gMXwyYVK+08fBzEXNug2ZlMbFXDj8bjQQGdQKd9BpuSKS/DPXpWf3KHKhVXcZlIl7F0ubc/sWYtBlOhW/n+xE3Iox26iW4zqfSV/PZSvu7g12fzfSe+ruTnH/M1pj/lQLgxOP4/76FL31Z7KE3GtyoTgnna3H6Rnib8G04TvttefhmQT+VMF2U6VG5inEiK1oLu52ESAVwyAefci3Tfd2vc/Tw97v5NUSwsJWO2
*/