
// (C) Copyright Tobias Schwinger
//
// Use modification and distribution are subject to the boost Software License,
// Version 1.0. (See http://www.boost.org/LICENSE_1_0.txt).
//------------------------------------------------------------------------------

#ifndef BOOST_FT_IS_FUNCTION_HPP_INCLUDED
#define BOOST_FT_IS_FUNCTION_HPP_INCLUDED

#include <boost/mpl/aux_/lambda_support.hpp>

#include <boost/function_types/components.hpp>

namespace boost 
{ 
  namespace function_types 
  {
    template< typename T, typename Tag = null_tag > 
    struct is_function
      : function_types::represents
        < function_types::components<T>
        , function_types::tag<Tag ,detail::function_tag> 
        >
    { 
      BOOST_MPL_AUX_LAMBDA_SUPPORT(2,is_function,(T,Tag))
    };
  }
} 

#endif


/* is_function.hpp
hattlubbVSZIntpYXEA2PX2CdsHgk6bQcDvU8EsIbVUzgs/fPgX36diZhk3678NWcX1HRmATErJ1m3TLw0LX8oh230qbtIk2qfV3sUlVfYuQFxKNtzOkbyF5WbuBhd+++pb9oG/5FIUhhe3T7qdpnxKehmu7rIbvUylEv0/DtX1aw/fppBDtJOEVlooKYp/C9R/sElhaODWycMGEFk4pA3znVa/mVVvwLB8dpN1IipiADmkOFwmhAZQVKMq1EqwZjADV4nehIdXE4OXKJ19gjFCW1AGATJUseFjekcI6V32aOii2xIesJgr8zSUx1AO9Jbj9l02qzY+4Mq0Ve5OTFY8tASUlnUaqVr94VJ/uu9XQ+17tYadXB6vkr0WQvxQOqx7BOjLhJTSu9BYaxQ1wJ+MNsEPIdhTTWJP1CQ1Er7RH5dSVilJSWThGf76yvdSSb9XhgIHa7c03UrtKrWhtvp5GChequS1A7bRBOfSWHV4UXBB2pOB/cTnO4kPBd6oUvCZSpeB/st8N17DzK116RxXIvW4M7RCycC5yxMBor7kSxbVsv+JaUzHPgeBGWcfjpp+l/LmNFcuFEv1YX0xXefm8cCR/P5Q/syRs43WoJg+QSABL5ZX78Uq9+LMHVY7jPy0Sl9M68PrKM/QcUozWepz/JzGKbcPQDr9oYlSGufxAhtSCFqsnVaV18biENEpOg/F/HtC7GqSBq8HM
*/