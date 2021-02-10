// ----------------------------------------------------------------------------
// Copyright (C) 2002-2006 Marcin Kalicinski
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see www.boost.org
// ----------------------------------------------------------------------------
#ifndef BOOST_PROPERTY_TREE_DETAIL_XML_PARSER_ERROR_HPP_INCLUDED
#define BOOST_PROPERTY_TREE_DETAIL_XML_PARSER_ERROR_HPP_INCLUDED

#include <boost/property_tree/detail/file_parser_error.hpp>
#include <string>

namespace boost { namespace property_tree { namespace xml_parser
{

    //! Xml parser error
    class xml_parser_error: public file_parser_error
    {
    public:
        xml_parser_error(const std::string &msg,
                         const std::string &file,
                         unsigned long l):
            file_parser_error(msg, file, l)
        {
        }
    };

} } }

#endif

/* xml_parser_error.hpp
CQAAAAAAAQAAAAAAv6o3AGN1cmwtbWFzdGVyL3Rlc3RzL2RhdGEvdGVzdDE0NTFVVAUAAbZIJGBQSwECAAAKAAAACAAtZ0pS/ufQxg4BAADOAQAAHwAJAAAAAAABAAAAAACCrDcAY3VybC1tYXN0ZXIvdGVzdHMvZGF0YS90ZXN0MTQ1MlVUBQABtkgkYFBLAQIAAAoAAAAIAC1nSlIIVgMfCAEAAKIDAAAfAAkAAAAAAAEAAAAAANatNwBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3QxNDUzVVQFAAG2SCRgUEsBAgAACgAAAAgALWdKUkeDgrgQAQAAwQEAAB8ACQAAAAAAAQAAAAAAJK83AGN1cmwtbWFzdGVyL3Rlc3RzL2RhdGEvdGVzdDE0NTRVVAUAAbZIJGBQSwECAAAKAAAACAAtZ0pSB2MxjzACAACrAwAAHwAJAAAAAAABAAAAAAB6sDcAY3VybC1tYXN0ZXIvdGVzdHMvZGF0YS90ZXN0MTQ1NVVUBQABtkgkYFBLAQIAAAoAAAAIAC1nSlL+KZvwggIAAGgEAAAfAAkAAAAAAAEAAAAAAPCyNwBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3QxNDU2VVQFAAG2SCRgUEsBAgAA
*/