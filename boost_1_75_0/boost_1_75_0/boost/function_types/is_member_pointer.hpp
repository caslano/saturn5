
// (C) Copyright Tobias Schwinger
//
// Use modification and distribution are subject to the boost Software License,
// Version 1.0. (See http://www.boost.org/LICENSE_1_0.txt).
//------------------------------------------------------------------------------

#ifndef BOOST_FT_IS_MEMBER_POINTER_HPP_INCLUDED
#define BOOST_FT_IS_MEMBER_POINTER_HPP_INCLUDED

#include <boost/mpl/aux_/lambda_support.hpp>

#include <boost/function_types/components.hpp>

namespace boost 
{ 
  namespace function_types 
  {
    template< typename T, typename Tag = null_tag > 
    struct is_member_pointer
      : function_types::represents
        < function_types::components<T>
        , function_types::tag<Tag ,detail::member_pointer_tag> 
        >
    {
      BOOST_MPL_AUX_LAMBDA_SUPPORT(2,is_member_pointer,(T,Tag))
    };
  } 
} 

#endif


/* is_member_pointer.hpp
wmNys/zyND2yoXHXZVMB2bYAsk0AZBtMyOZBZBtIyKY4e571h2yvC+vY4RqyLVWRzcmRbbPcdSog22AfZJvg2wjqMlWceneIQLRrVbR6eYhV7wH15BCRIaE19OpoOwd67acjue7/0fYd8FEV28ObRoKU3QSW8KQFiRoENYolGMSsJrorG4iIEBUwCsaoKAESCFIMJpS4LsSOHRUVsWGlQxClCEKUYhDU2G+I+BCQKuw3p8zcububkPfe//v9CHfvvXNnzsycOXPm1LEN0ti6jY3i1xkDGsIvGBGjyyQrfm3r3xT8uqltQ/g18x4zV5oSWU/7g/j+mCs3KkMm4k8PsPNSTlavw6ZxIAAyUACCyiAKrliQ5fsNds5eghGVuq1z3WIkT0POXOj0tJwOP1uN1AcA0Y4izykOcwftD1IUkEy2us9UHk4xve9pQ7ZUy9JtFByjBM5Os2+Mt3FaMxhxgVqzM9DwdotMfVbfMt3dfmxCD7dggjPi0Lj3Z3AjrBO3SW5/2w0AyEslDgRorTjfow+26OMl6UXJaXY/UOBGa3tJq63lBmMoZFtBZgVN4sZg8hXn/R8lYgOzSxw4VRnZvS8vboUxWrYaGyc4bPUTAFnHiq0h4GzlgTWNeBspfsIy9LdFfOiWjZkqSdcHjZ8Pp8Cow14gw4nGeUkJYpYgOFugCsMfACcbJYDfZtjFK6y8xAtViO89FbECXS4x
*/