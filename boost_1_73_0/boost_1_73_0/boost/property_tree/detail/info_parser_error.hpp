// ----------------------------------------------------------------------------
// Copyright (C) 2002-2006 Marcin Kalicinski
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see www.boost.org
// ----------------------------------------------------------------------------
#ifndef BOOST_PROPERTY_TREE_DETAIL_INFO_PARSER_ERROR_HPP_INCLUDED
#define BOOST_PROPERTY_TREE_DETAIL_INFO_PARSER_ERROR_HPP_INCLUDED

#include <boost/property_tree/detail/file_parser_error.hpp>
#include <string>

namespace boost { namespace property_tree { namespace info_parser
{

    class info_parser_error: public file_parser_error
    {
    public:
        info_parser_error(const std::string &message,
                          const std::string &filename,
                          unsigned long line) :
            file_parser_error(message, filename, line)
        {
        }
    };

} } }

#endif

/* info_parser_error.hpp
AGN1cmwtbWFzdGVyL3Rlc3RzL2RhdGEvdGVzdDE0MVVUBQABtkgkYFBLAQIAAAoAAAAIAC1nSlLEiH447QAAAGUBAAAfAAkAAAAAAAEAAAAAAABFNwBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3QxNDEwVVQFAAG2SCRgUEsBAgAACgAAAAgALWdKUoimnRAOAgAAYQMAAB8ACQAAAAAAAQAAAAAAM0Y3AGN1cmwtbWFzdGVyL3Rlc3RzL2RhdGEvdGVzdDE0MTFVVAUAAbZIJGBQSwECAAAKAAAACAAtZ0pSJowZJIIDAACgDAAAHwAJAAAAAAABAAAAAACHSDcAY3VybC1tYXN0ZXIvdGVzdHMvZGF0YS90ZXN0MTQxMlVUBQABtkgkYFBLAQIAAAoAAAAIAC1nSlJDOPVewAEAAHUEAAAfAAkAAAAAAAEAAAAAAE9MNwBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3QxNDEzVVQFAAG2SCRgUEsBAgAACgAAAAgALWdKUhl3ZOSXAQAAqgIAAB8ACQAAAAAAAQAAAAAAVU43AGN1cmwtbWFzdGVyL3Rlc3RzL2RhdGEvdGVzdDE0MTRVVAUAAbZIJGBQSwECAAAKAAAACAAtZ0pSscETAPoC
*/