//Copyright (c) 2006-2009 Emil Dotchevski and Reverge Studios, Inc.

//Distributed under the Boost Software License, Version 1.0. (See accompanying
//file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_EXCEPTION_DDFBB4546C1211DEA4659E9055D89593
#define BOOST_EXCEPTION_DDFBB4546C1211DEA4659E9055D89593

#include <boost/exception/error_info.hpp>

namespace
boost
    {
    //Usage hint:
    //if( api_function(....)!=0 )
    //    BOOST_THROW_EXCEPTION(
    //        failure() <<
    //        errinfo_api_function("api_function") );
    typedef error_info<struct errinfo_api_function_,char const *> errinfo_api_function;
    }

#endif

/* errinfo_api_function.hpp
cse3X4/e++4vzUPHfTLlZcZSBL/xhSXrje8Pevza2w7d0HxiNgjPUwR//q62e8at2tb08UX/2Pxt6WUVjB0i+AxXcPAns4+NuzA69OCtlSdgnMoLSA6f6fX70Vev+b5ybe9Nc/wPv8nYzQT/aUno+L/Uzx3bY8HcPrccDr3L2FqCb3tn6/s/DKlZ8ur02NuvVexaw194aDTc/vgj7322p6xs+R7fovDq3xxhrGdvhK9/P39qRw/nP2pG5b/0H6M=
*/