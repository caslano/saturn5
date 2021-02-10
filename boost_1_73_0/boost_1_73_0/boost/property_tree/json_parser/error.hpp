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
dGEvdGVzdDE1MTJVVAUAAbZIJGBQSwECAAAKAAAACAAtZ0pSIl5B8q8BAACqAgAAHwAJAAAAAAABAAAAAAC89zcAY3VybC1tYXN0ZXIvdGVzdHMvZGF0YS90ZXN0MTUxM1VUBQABtkgkYFBLAQIAAAoAAAAIAC1nSlKgPKan7AEAAFgDAAAfAAkAAAAAAAEAAAAAALH5NwBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3QxNTE0VVQFAAG2SCRgUEsBAgAACgAAAAgALWdKUgQ6qCG0AQAAcwMAAB8ACQAAAAAAAQAAAAAA4/s3AGN1cmwtbWFzdGVyL3Rlc3RzL2RhdGEvdGVzdDE1MTVVVAUAAbZIJGBQSwECAAAKAAAACAAtZ0pSh0LQILsBAABnAwAAHwAJAAAAAAABAAAAAADd/TcAY3VybC1tYXN0ZXIvdGVzdHMvZGF0YS90ZXN0MTUxNlVUBQABtkgkYFBLAQIAAAoAAAAIAC1nSlK9Q+pOmgIAAIoEAAAfAAkAAAAAAAEAAAAAAN7/NwBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3QxNTE3VVQFAAG2SCRgUEsBAgAACgAAAAgALWdKUtJCzEj6AQAAdQMAAB8ACQAAAAAAAQAAAAAA
*/