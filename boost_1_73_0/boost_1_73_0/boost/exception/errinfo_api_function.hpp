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
Yqt+iJ0qtJ3EdS6X3lRxlIsaRVJF6XyeOKOBSShETREqAUrWNP3f+xYELclOx/lw8tiU8eNhsfv27TK6atHTP+wjIoajRz8z/zvDB89m06g0/1KJ+/6G2ewb1T/YeIXnDxx1RNtd32aH9EO7vtGB3zULZ73h77PZDxx3xUbynyPefDXjrxipd4b952a5KfXXzNHB+SGd/PTTK3pGz49PXrXpnSy0yil2qrhW5dc2vUn9yN8zeXsbWfVLm5QjmUd7gJNMW7Jm7tayVITvuU5UYVVK0lKqbFLqa/yjC3KZornOFZ0PR5e9wa9tWmc6yQLOxlRkM1PlKWVypahUidKrGmYpS0dmDgTgp9o6YFZOmyLC8YqcKhc2wLARMreG5ErqXF7jOOkoc25pXx8dJVWZ4yZHqUnsUdK4Isrc4t6tLmHNQm7ILB05Q5VVbeL1bVqYVM/5CRdhcFld59pm7a1ZOLBIj0xJVuV5gMNWrWx9BUVx8FabV9IS1mvHD2sKy6etM7PYWwi3BqB5VRY4Dm7ButTA8W2qilSVfr13RHNK8LJ3+SMh29qekilgFbU6MfXiFl1Lq22bLnqTD8PphC4643FnMLmk4XvqDC4D3sfe4B24oXFqSep2WSoLK0rSi2WuVbp3+B+a6SKafKDz
*/