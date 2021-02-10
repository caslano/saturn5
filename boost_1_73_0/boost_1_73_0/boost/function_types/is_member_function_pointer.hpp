
// (C) Copyright Tobias Schwinger
//
// Use modification and distribution are subject to the boost Software License,
// Version 1.0. (See http://www.boost.org/LICENSE_1_0.txt).

//------------------------------------------------------------------------------

#ifndef BOOST_FT_IS_MEMBER_FUNCTION_POINTER_HPP_INCLUDED
#define BOOST_FT_IS_MEMBER_FUNCTION_POINTER_HPP_INCLUDED

#include <boost/mpl/aux_/lambda_support.hpp>

#include <boost/function_types/components.hpp>

namespace boost 
{ 
  namespace function_types 
  {
    template< typename T, typename Tag = null_tag > 
    struct is_member_function_pointer
      : function_types::represents
        < function_types::components<T>
        , function_types::tag<Tag ,detail::member_function_pointer_tag> >
    { 
      BOOST_MPL_AUX_LAMBDA_SUPPORT(2,is_member_function_pointer,(T,Tag))
    };
  }
} 
#endif 


/* is_member_function_pointer.hpp
fQWblEyC5IW6J4ICvlcso7WkORAJOZWZYCv8wWpQJYWCVRRGYbQIpp8cuC9ZVvY4W96CLHlb5VCSDQVBM8o2HUxDhAJeIALi50wqxGwV47WL4SkoKtayh9FJkEpyIBvCKrLCcERBqVQjfxkOs1ZUeJJhzjM5zHaEuKVaf3GqBWazJlvgjQLFoZXUAW3vwJrnrNBPpAgXm3ZVMVk6z2lhwDofcgGSVlUPh66Myu4IFOKeLUdbQoPZM6UfktdSR7sv+fqVIdLaAxWtqDEc0oJ2OUfiHWjrnApjb4jYRelZNpS/UbLn3HPgNWYFthdDENuwIpJJB26CZBzOE7jxZjNvmiwgvABvuujxLoPpOWqDYVQB9KERVGIWAti6qRjNXwX/pv1uuckYRvPZJIySNI7HaTQLrr3ETy/9xUUw8eEI7MMT+KOtjdBtsCu20hqAY/fo2P2AC/pXSoncppIqXW38orAkYsdjmHpXvvW1AMsDLDMWT7ANwcrf0W0n8QKPj/ZAWlUapHgxDaM4iC23LqzvWJ1VbU7hVIfvVFl+tEykjOP6l1kN9A7sl6iXCmXzlYwc6/+nRFYSAfs6v5qs6d6vJrFzPx7NgigJwqkVESwc6e2g4axWrL7VUiOwLIKd57KIzAGxZcXLo7sQFFBz
*/