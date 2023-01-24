//Copyright (c) 2006-2009 Emil Dotchevski and Reverge Studios, Inc.

//Distributed under the Boost Software License, Version 1.0. (See accompanying
//file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_EXCEPTION_0E11109E6C1311DEB7EA649255D89593
#define BOOST_EXCEPTION_0E11109E6C1311DEB7EA649255D89593

#include <string>

namespace
boost
    {
    template <class Tag,class T> class error_info;

    //Usage hint:
    //BOOST_THROW_EXCEPTION(
    //    bad_type() <<
    //    errinfo_type_info_name(typeid(x).name()) );
    typedef error_info<struct errinfo_type_info_name_,std::string> errinfo_type_info_name;
    }

#endif

/* errinfo_type_info_name.hpp
TUVEm8atFVDoKuh7A2O/4qxjz0lqfOzrnvi/H/uMXxoc++0+MXaw8bEDa/oLIWdKxTqfbDiy9q0LUfaJSTmA4hy6gdLOL24pYxox1+OTiFctWAhLgHkm2YSwHiCERVXUlEwRdM3vIpJb2VHKXi3I1VJ5PseQdqnXhqWmZMDeD4Uc+a6Dx3fmAo8x03JKPPazG+PROG563QAxcTMflo5xs3RqLFjBazHOQExhX7Eggz4nukFEVzxqAbrxTkZZ3PPyQN/g5y1nMSy0WJ1kg02OQfftF1CZIkF98YEAWtU1TvMiSLZSU3IVzgDapV2g8o1ZETk0Uc1/+WEdLWYu8QsxnecHc0w2KqujrJhXLIsgtLhfvf5uXn+WE9lQSpDUjs8F8hFb8iYM9Xuyu38miKZD0L1mLbO6rwa6t1rQvY1ENJvSO4Jwtlgv5khUebsgoOmpJW2Llqan3t+2ODHbf3UCHEQCAupkArpBJ6Abp473Lsun/6J8aYOcRfeQ3RJE4eVA8cz3cZsJEdSbAJagHyKA4gv6c6cY/J2x+ZUPxEOqrOTfXQ+Df4IsyQlge+iFWW22py91eCvj0mc85IRQLP98OhWmQhFvXGsObmZI2zbjfeVz/xjvP0g8O957/7/H+4dPaXgflWjD+1kBG95v6Q94f/dgwntr/gv++fy72OZf1uD8Z/3j+RfWZTY2/+7W/BPqt6liT+hDkYahJt+k
*/