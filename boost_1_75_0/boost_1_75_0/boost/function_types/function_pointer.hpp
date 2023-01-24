
// (C) Copyright Tobias Schwinger
//
// Use modification and distribution are subject to the boost Software License,
// Version 1.0. (See http://www.boost.org/LICENSE_1_0.txt).

//------------------------------------------------------------------------------

#ifndef BOOST_FT_FUNCTION_POINTER_HPP_INCLUDED
#define BOOST_FT_FUNCTION_POINTER_HPP_INCLUDED

#include <boost/mpl/aux_/lambda_support.hpp>

#include <boost/function_types/function_type.hpp>

namespace boost 
{ 
  namespace function_types 
  {
    template<typename Types, typename Tag = null_tag> struct function_pointer
    {
      typedef typename function_types::function_type<Types,Tag>::type * type;

      BOOST_MPL_AUX_LAMBDA_SUPPORT(2,function_pointer,(Types,Tag))
    };
  } 
} 

#endif


/* function_pointer.hpp
sxiPrXBoif6s4WaYSzpShUqtQqWogKRpHq9Qp1WoExWQnP2HV2jSKjTxCsiZQp17eR1ZvyWKazBCXs906YhmEACfyyp7Ct9e1lF3lE+9gtjSi3Rs6aMYanInO5XzGE0uHAiUQ1b5UkmYw3BvyUo9XzSbsyOdGEmVV18ADCzz00LkYyXjlhqvb/3DJ/mHHeDDp/iHz3Sgkcrazm2cZTVMvEkrquVFTV5kwiygraMFldpnL/PPKvlni8W+VmwzZiE3+n57gM1sZEOq8HDYCoCxf4u85+168GTrZ4lUtphT2Y7xXuxjunsC4x/NPWmq70HktRt9vi7hX0f4/3obB9Sj7anaTE6gf/ci0LODiUAvNunmII9JoK9T2sPMQ1RuSnqBg2sTZz67t0fmkxgnV3/9KHFAs/jiRcZDCpQt9orHVAySV8RTJwciCWPrNayuF1gt4nR+FykYVehfnlmGB/bdqlDDCEM0uBspa9hornG4mhm34juag3w0Zj+j6cNHc3+khiPyrc9jPzf6tBSYrcXG9vegxi7iUzMFqVOjP9nUcvnUTLxDzsKZS1pwUM1wi18EH6shOISVmW1JLXJ/dYLLWsoR81KtOrK0NuD+8Le+LW4fYeHukBFgHAHSbGbqCT8wC+UzzRMwK9Fg1tKdpumMIEFILEWMQ6mCdShi66CYS83B3PiD8gPoJusyA0fZf7owAHkI6izR5ksqFFtF
*/