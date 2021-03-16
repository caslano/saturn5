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
Sgu3vbNOKzpFDS0TUqZ18dMKW/Wrq88TfsZInuhmlR/mib2tNJs2mRY8TJvuoTz2uO8Trssa933tvlh19bDg4br2C+Wxx6GnlRamdy87nzVGWRY8PA697bZH8GWfcL+tedLXTrPq62fB7fpGQlbsr2TFG5AV+eySQL7RReNGnBAQslEpUn50UjrLv8X6KC0Z/n4lzjqaUiYs+2adsKcsePGshiZlq78ubDGpYdj7Dpwnw4LLLDLtzTjr2qyfBPM=
*/