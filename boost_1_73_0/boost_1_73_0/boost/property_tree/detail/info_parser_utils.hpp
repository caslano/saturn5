// ----------------------------------------------------------------------------
// Copyright (C) 2002-2006 Marcin Kalicinski
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see www.boost.org
// ----------------------------------------------------------------------------
#ifndef BOOST_PROPERTY_TREE_DETAIL_INFO_PARSER_CHCONV_HPP_INCLUDED
#define BOOST_PROPERTY_TREE_DETAIL_INFO_PARSER_CHCONV_HPP_INCLUDED

#include <string>

namespace boost { namespace property_tree { namespace info_parser
{

    template<class ChDest, class ChSrc>
    std::basic_string<ChDest> convert_chtype(const ChSrc *text)
    {
        std::basic_string<ChDest> result;
        while (*text)
        {
            result += ChDest(*text);
            ++text;
        }
        return result;
    }

} } }

#endif

/* info_parser_utils.hpp
YFBLAQIAAAoAAAAIAC1nSlL2p9mJXQQAAD8KAAAfAAkAAAAAAAEAAAAAAGdhNwBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3QxNDIwVVQFAAG2SCRgUEsBAgAACgAAAAgALWdKUqhJ/P7kAQAAbwQAAB8ACQAAAAAAAQAAAAAACmY3AGN1cmwtbWFzdGVyL3Rlc3RzL2RhdGEvdGVzdDE0MjFVVAUAAbZIJGBQSwECAAAKAAAACAAtZ0pSJBsQ+UkCAADzAwAAHwAJAAAAAAABAAAAAAA0aDcAY3VybC1tYXN0ZXIvdGVzdHMvZGF0YS90ZXN0MTQyMlVUBQABtkgkYFBLAQIAAAoAAAAIAC1nSlKbzEPp5gEAADcDAAAfAAkAAAAAAAEAAAAAAMNqNwBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3QxNDIzVVQFAAG2SCRgUEsBAgAACgAAAAgALWdKUmEfkOBLAgAA0gQAAB8ACQAAAAAAAQAAAAAA72w3AGN1cmwtbWFzdGVyL3Rlc3RzL2RhdGEvdGVzdDE0MjRVVAUAAbZIJGBQSwECAAAKAAAACAAtZ0pSDK2hRMcDAAC5BgAAHwAJAAAAAAAAAAAAAACAbzcAY3VybC1tYXN0ZXIvdGVz
*/