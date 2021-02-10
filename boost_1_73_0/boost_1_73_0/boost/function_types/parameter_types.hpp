
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
eZVwOCc7NeWyC8eqjBWu75rfox14lyEZcuTEjmnkXcZKeEf29n+3pr50w864F0S90dAJGGLNoFBCGmIBEh9klecHxAUhGaWUkitvm0JiS45bdeE0G03ZLbjzVKISjxGRsCrLFyKuxROesio3kKpyiUWGRHKDwyMXKeSEHKPkEJVM6kJh9RLT3aA7oF1QNVPkrZBc11UQI+kWnGKVt+jyA5LJmaW9HTCiadDdO96fpYHvODd4BoZhSFTbtefVvYK02m6Aqik2KeK7dWj0ezOJ1IAesLYshhXuSmM3rC8EnrAhkvhTO9NkVpgVJMwwrBUEpmdBcx6YXHcOzIjFNC2bskaZkgBNBDY5o0rsJkWOhOBQUNdDiqApa9X1W66Di6l49MimKpMmyfdKIGhKppVG6jY+PsWH6OyFhKXEhq5kvtqHzk9J1GvQdcFjXMOwFiviEkNdTRmTbqMctimHtFElRrpHTZJUYJ1TioPL7zX/7D7GXGqz78P6FCLhuOf1Xq5QEeq+mM2aFfKafpmsWi4KpKW5cEkbxr6m9Way1vivtOHL7aCsPo9IiUEwbEHcc9xODflE83I2G0xns7PjD+yExZ/SU/Yx+XhydnT6kZ18SNmnQ354lh4dJ0nKT5MT5hLV1y5RH650xfKccAqv
*/