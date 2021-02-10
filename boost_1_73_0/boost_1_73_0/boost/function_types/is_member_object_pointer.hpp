
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
pdsld6wd1zktSFspI+1lcfb9OLzyh66U5ZDlaS6JhmOdZvUW0HrDBK/XtFawIYLpJra0YqnqOuZzKxXYnbO9mywYSmiPnOHkUFxsNabBQ1edFLq7lhUUz3OI6cki5T0X+UEjuEI/zNsUVNvs9uAelW3h+Xe0I9WRF8c354OjPUweUfUUIg2qPSNaPdiZtAtqRhme+47SxoDqRkNKieDYtkAKbFkdsOMZ+9Lq9Of2tbnw5pPE8qRuq4qwWs/DFd9Qsx3NwiQchZPYii+SyFATjyKz5f/pXUUT36it044pxW8vlMVqpgYoAlYM9OIe/IXS+Zfw9MKz4PDhgC0L1eAwpQ8EG5y6GV8PNZ82gr2J8F7J2kMcgnSYVUTc3WFdnwQjsObvCfRUJEx4V8nOUWB9XxKBkxfVvO5YeI2cVZTUbbPb+ttyC2b49a69YOKdBZMgWVhennf/cMfu4U/uoTGY+cl8NoVrbzL3rRlVOLelyc1Pw8ud3Ltaax3Ktmm4MPLrjObTy2l4M01D05naAeXk4FS1epB5koYX6ZV/Fc4WPR4O83v8t2S1bIuCZUy3Q0lJA7IhGe0kZce+D94kDnHAnc1el2V+NglGT6PNRnUjd69MvHkyTpNF5Me7besfUEsDBAoAAAAIAC1nSlKX
*/