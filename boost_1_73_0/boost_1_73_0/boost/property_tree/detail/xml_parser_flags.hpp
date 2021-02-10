// ----------------------------------------------------------------------------
// Copyright (C) 2002-2006 Marcin Kalicinski
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see www.boost.org
// ----------------------------------------------------------------------------
#ifndef BOOST_PROPERTY_TREE_DETAIL_XML_PARSER_FLAGS_HPP_INCLUDED
#define BOOST_PROPERTY_TREE_DETAIL_XML_PARSER_FLAGS_HPP_INCLUDED

namespace boost { namespace property_tree { namespace xml_parser
{

    /// Text elements should be put in separate keys,
    /// not concatenated in parent data.
    static const int no_concat_text  = 0x1;
    /// Comments should be omitted.
    static const int no_comments     = 0x2;
    /// Whitespace should be collapsed and trimmed.
    static const int trim_whitespace = 0x4;

    inline bool validate_flags(int flags)
    {
        return (flags & ~(no_concat_text | no_comments | trim_whitespace)) == 0;
    }

} } }

#endif

/* xml_parser_flags.hpp
CgAAAAgALWdKUrq6kKi2AQAAZQMAAB8ACQAAAAAAAQAAAAAAuLU3AGN1cmwtbWFzdGVyL3Rlc3RzL2RhdGEvdGVzdDE0NTdVVAUAAbZIJGBQSwECAAAKAAAACAAtZ0pS/OMc9NABAAD4AgAAHwAJAAAAAAABAAAAAAC0tzcAY3VybC1tYXN0ZXIvdGVzdHMvZGF0YS90ZXN0MTQ1OFVUBQABtkgkYFBLAQIAAAoAAAAIAC1nSlIAESfrMgIAAEEDAAAfAAkAAAAAAAEAAAAAAMq5NwBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3QxNDU5VVQFAAG2SCRgUEsBAgAACgAAAAgALWdKUgk4VD2yAQAAEAMAAB4ACQAAAAAAAQAAAAAAQrw3AGN1cmwtbWFzdGVyL3Rlc3RzL2RhdGEvdGVzdDE0NlVUBQABtkgkYFBLAQIAAAoAAAAIAC1nSlIqWpFt+QEAAHsDAAAfAAkAAAAAAAEAAAAAADm+NwBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3QxNDYwVVQFAAG2SCRgUEsBAgAACgAAAAgALWdKUrKgr0x4AgAAvAQAAB8ACQAAAAAAAQAAAAAAeMA3AGN1cmwtbWFzdGVyL3Rlc3RzL2RhdGEv
*/