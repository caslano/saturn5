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
YQqSuqbcGUy5VMO3FQ9J6UGBK5rb2QzO9Qe+eTuCz2qIhBHgu2fcsl6n3IpQ5h4WPYeDCOHMlSgW9nr6g249FADy/b/sujPBlPEEHDNfTcDFhoHLw91vLAApG4KWexLP676+mT0nGkz5ZEWk2ZXPwBf4nT1Ed1wqwP/Zzgvp8al2XkqSAtlhOy9/BRIVsvPiiqpw0wqVk4jSLad+AYK11uoth/ltN8FyrV61K8rtyw2Wyd+UyYpvgwntg88UC6a5rkMiDBxHejBl2Ao6m+OWqS/hSSSdwbFtYYlXrvzUyfYbVOb09oJc1zp7AeNwXSsluTCYcqganz9s50XtqWaISVRB7lUeRzECCCiu8YfZrGaahU7Zj0Icbkh+t5LsZlRj4EHe6uZqRoRw7pXJx+TKzC3UW2gMWaU8bNZhv7B7f0h2JFinZAVX8/OqXIovd5Rh/Y8gI1FgNG/z8S3S315GakFnj+tFORV1E+WjwZRKguerm7Dmdg5PL/gCy4IpXTcRFQkkgeyLY9VxUyTUR24S1OuDz1OEmv0F8O0jQxNoBlv0XE3dqfNMEF5jFsr7XPOZdcFCwSUiRuguh/aEJ8kjyOg569Vgyl9uxt8FBN8hXkE5wmcKl0cwZEfBMOUmVhFEDGet4BHJ+NTGQaSwRQNVUVesDPP4UfJd7hkQ7kRcQXpC+L3nUjR+55N0B0Iabr2zSf8O8kzNvRHIfv+N
*/