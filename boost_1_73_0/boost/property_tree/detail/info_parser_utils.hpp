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
Ni13aW5kb3dzL2luY2x1ZGUvY3VybC9lYXN5LmjNVttu00AQfc9XjOClrUwCPHETorQFIiBBTRBUQoo29jhe6uwa7zqlXP6dM7vOpfci8YBRsXczc+Z2Znbv6txknNPex8N3/cHe5GB3dDR507mLPW34/HZv5989HdqhG59J+JvgwTtofKjtV079ZcIi94vCP9H6gvdNRnq0Vvk12aabVX7RVlCZtFae4Q27Nxn6Ir7Jfz1o
*/