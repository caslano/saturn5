
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
Mj28i4NiBMVjyJFsLkFsPIap7DfSbB+EXRI1fUwi1dEg/jHqfz0ymRcq5Zip51sJ5Ph18SV+CzRKm5H++31/SudBAAPjm2l+4by3d/RJ6dz/1LTtxj14fFoEA9JVgzCD66dVDk0CTUgu/pPfrLKmTSeVBIwOnDdbaPrWYLcvkVqSVLt/2Nd9qQFP1FRD+kx+fYy3YthlPIs3RGCqUzWh8JQMG4zRUgWEWjbyF2nkF9rqlkpi6CN/h6K+CKE0kw5hs3rP/IL+g1e1YUIfas9ADSkbUoLrqWmsC7FJpfC8oPtTwKYCiJam/zKg/dZNBCB339WAsPFXhiHuaLlDqjeR3QEvqf8QHOG4IHqajc0A1T/HXsZGcZ8WqqVkz5KnUDafM4EK8lLRT0INy7+UREyq7YSIxSK86EQM6v25lN8rmhwl32efG2AjlygzltRkDahXKQnSgm8+M/rnOxQ4B0baAtwcRtiEjDWyb472jNNYSqrmsQZl17+naiq0OURO39s9E+SiIC7ix2dE5Thvrx8zlVK/HHUUeBcJouFaDa2Ilqtx5jdg1hXSAOA0ug==
*/