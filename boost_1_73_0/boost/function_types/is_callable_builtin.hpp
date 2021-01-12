
// (C) Copyright Tobias Schwinger
//
// Use modification and distribution are subject to the boost Software License,
// Version 1.0. (See http://www.boost.org/LICENSE_1_0.txt).

//------------------------------------------------------------------------------

#ifndef BOOST_FT_IS_CALLABLE_BUILTIN_HPP_INCLUDED
#define BOOST_FT_IS_CALLABLE_BUILTIN_HPP_INCLUDED

#include <boost/mpl/aux_/lambda_support.hpp>

#include <boost/function_types/components.hpp>

namespace boost 
{ 
  namespace function_types 
  {
    template< typename T, typename Tag = null_tag > 
    struct is_callable_builtin
      : function_types::represents
        < function_types::components<T>
        , function_types::tag<Tag, detail::callable_builtin_tag> 
        >
    { 
      BOOST_MPL_AUX_LAMBDA_SUPPORT(2,is_callable_builtin,(T,Tag))
    };
  }
}

#endif


/* is_callable_builtin.hpp
AebBGXA6nAML4HJYCK+Hs+BD6s+jcCbcouYvqflWOAe+BS+A78O5cA+8EH6u9oqDMLfbvC95rTRkErKXzW7L4UpkI7KpGyuPkbGhXqsMaU0l368Z5YXKeyC/c5C9BHQRLOP8qq3Ien5XYmc3zGFgMJmXklVE2sH05jyL3HM7ElaX9yGSj6xGtiIRFLrxvDx2cu89uAku5l3C71GYFyMrkU3I24gVzXj4d/h5KivpkaSXvVb0
*/