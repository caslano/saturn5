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
6a4TZP8ZBflWBKeusa3qmELqJs8yosF3JstsyJjbcf5PCemH9Swz/r9kJfb4xc0YwlBkxIUHeRSOADkuFHiHvwpVBO5CBib64CnAwukVTcLIJyI7e/t348b6iJ8hi1PmI7fj5ucMycOwDhRaPpunzmnMtItRHsYY9iL8aeSKijojSFJf23wo/mdPrlET+ODt6SeEtYxWLA+uHsATFoZpZ4YofIXGh2DVHJ1Qzw/BikLwmT5T64B8eNQvQVd8QriGGrE0SxzFAWtkF8V/vB2z/Hkj1sYdVHrcD26JijAcHQsLD8lHPhE1rcCFWC8U8BAn3DHYsTp/SHVmegC1Z+P/WHq5C3WyF0U0iAD8ASlpkPLi3Sgz8K7eqwGOd9MBpFmWHd+VCasI2+KR3xblAUUJZ0YjsMbTLXQFPklionEX3/P4+9LgFdC9E9sVG3IsRH0GvUotB0aE+khOfIXGmNJh2gg0yKFvlK2QYrfOIZMUaiW0SWdYH0eKiKGRU+HLZhgwS3u2sCnrfPuk8KNbDDThlkz4UuTlveOmI9gwAKYz+YJpNB7mr8gEo5D56g==
*/