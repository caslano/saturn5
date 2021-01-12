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
Au0DnK8LLCGn8af7YCZ3d68d88/kq507qTPT/RvlXqm6J4a8k79SieN+4viuxHFOzPSA339jdCcnjXbYB2UBbruqqFPHAl8ypG9LCYTqcEnOokVL8rzt5rWuEi5mb3sgf7RM/iz3GRiT7S8MJJsyd3uiBYvmeMLZKfFLMHt25Lsg0jbMGR+j72SbhHl7TFFMDOmROq5hzhCFNI62sUPaxm6Ue+ZSEUJtIFPrUm1nhLjdh9tQ
*/