// ----------------------------------------------------------------------------
// Copyright (C) 2002-2006 Marcin Kalicinski
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see www.boost.org
// ----------------------------------------------------------------------------
#ifndef BOOST_PROPERTY_TREE_DETAIL_JSON_PARSER_ERROR_HPP_INCLUDED
#define BOOST_PROPERTY_TREE_DETAIL_JSON_PARSER_ERROR_HPP_INCLUDED

#include <boost/property_tree/detail/file_parser_error.hpp>
#include <string>

namespace boost { namespace property_tree { namespace json_parser
{

    //! Json parser error
    class json_parser_error: public file_parser_error
    {
    public:
        json_parser_error(const std::string &message, 
                          const std::string &filename, 
                          unsigned long line): 
            file_parser_error(message, filename, line)
        { 
        }
    };

} } }

#endif

/* error.hpp
UHWpPL0W/Ap2UFH/g+A5UCgHnjjOC0PX2W5CvaQQZwbapJIzF0Kn09n79AIsa3C13ywNYVsG2zDUiGmZZWj+g0WtpLHiJ8aO5mEhUc0cDwN4dW2tO3+lbnMWS0FR6rl9mWCzCm7GtXktN+R7o6pua6FOrE2wrX6Zz5FztnlzVo7P78eZaXYavX//3f3w/QFQSwMEFAAAAAgAzDSJURCpSQ5JEwAAN0MAACUAAABjdXJsX3g4
*/