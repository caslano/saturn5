
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
l9Fw8Sawri4CRGd+Z06EEyHuCcDF4CkdtQSZYDjVj5b/Hzg318Dyd3c47O52UIY8kUsXhJ9LX0RzY7HKbizE1NmoUnwgAq3Hi5IL7dMx8pH4LBfaazsBRqhfgaWqsi9Ey4NCK4OaLsdzRkxeASOIiuUhcFIcL26OU8FbQIMNJjd7w+Ea5L3DKjBuCBr/bw04r+/HpKVuBh8UcDmk90Opa0z9Xf9zo6V6o2Qzu+N6WPUxmb6RxBEWhKpZcb2KpX+Lg7hCNGiY9hksLKmKWbs0BkhAeb7DRr8eyAcV6fwDxzC5Wtv7kZS1ur/huI2dPm+UlvW9viFahtGKbxxvpWWx1zeFllXYG6Jly+9sjJaN+azJtGyGp0FaJo/6/wEtW8K0bGRxk2nZfXeGpWWf9v8/oWXbxhEtO1L0P9OyyiILLXutCGnZK+8RLft0XBhadnKslZa5MhUtuyzTQsuGuBulZcM7NEjLrunAtOzt6xqiZY9dp9Oy8n/aIsR5Y/9XWvbSf0TL3GMbpWUvNUTLnhjxP5OV7iNDaNnUa8PSstHXEi3r8r83+tGIEFrW/Nom07LZLU5Hy5bcLmnZu7cDLavZR7TMfTfSMtfdDdOyG6oapWVjs8LRspFu32w5EmboWXwSLPLontUU6vbWGQ1Rt+/ytLx17TXzAjgEPLE65BCwm2zgpUHBB5nmMUA89x30+DBsljc9gMQKQzlj1C49
*/