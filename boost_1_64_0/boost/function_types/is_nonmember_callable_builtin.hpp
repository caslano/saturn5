
// (C) Copyright Tobias Schwinger
//
// Use modification and distribution are subject to the boost Software License,
// Version 1.0. (See http://www.boost.org/LICENSE_1_0.txt).

//------------------------------------------------------------------------------

#ifndef BOOST_FT_IS_NONMEMBER_CALLABLE_BUILTIN_HPP_INCLUDED
#define BOOST_FT_IS_NONMEMBER_CALLABLE_BUILTIN_HPP_INCLUDED

#include <boost/mpl/aux_/lambda_support.hpp>

#include <boost/function_types/components.hpp>

namespace boost 
{ 
  namespace function_types 
  {
    template< typename T, typename Tag = null_tag > 
    struct is_nonmember_callable_builtin
      : function_types::represents
        < function_types::components<T>
        , function_types::tag<Tag,detail::nonmember_callable_builtin_tag> 
        >
    { 
      BOOST_MPL_AUX_LAMBDA_SUPPORT(2,is_nonmember_callable_builtin,(T,Tag))
    };
  }
} 

#endif 


/* is_nonmember_callable_builtin.hpp
18sa6unvfDM04vzADMwslQO1bWdFMIaFPeJiXhrf1bM9Ve67xI5jCjsUrfnrv++5XkxRN9I300JDVqdeJ38nUEzQJjJ4Jyp8Czhfz5N/pcv85eQsQ3gly50JuXf8zD+wAc/6eS2oBqpgdTxJbYch1oxFmbmdxceWRDenHB/vC7kQkuOEJOm27OrFGt+vI3m4Lwd2Uy9g50XHC79L58cg07N4w8Az0UXjnlCIkrGcd965jXYkKr1CpUnyrI0Ze6WxGuPjxdS5kl/hTC06bce0YO7XF/OJBbf/TdED705e6SIx6slnOs02k6/fM3dJNN5Lx9BlFzgrGwLAqTS2a1Y0SarjYmlbo1FBZ309/FZPYxmHZCqTPVApBRohso3DgpZFTUV87s7q49oH9AUhE0xat0GEUwq7yF7QtiXteURwAlhD00z2jbhiyAJMlCE9vhavBC5vcNpR8o1/zxlDV9TMkAZtvYPN+f38hEofae/8o0MvR1PttYPtBkP4JekCdMakDFUiZEsh1ic83FolVbiGEgLCjwdwAxby4RqO8S/GZxHSpD3ModhaVu2S/Q==
*/