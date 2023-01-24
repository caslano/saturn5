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
UJTOSWOQXpJnMJEf92U9kSjwykB3AvZEDhuOa/dF7BJcTP4z63TSZvRI55S99q15ioo4r6V4nIdor/0bbqnECZ8Th3Nepiqk+Od4ZS9yNhcmVb1/TLlfnwLeg6I3dY/cORrNRn8cJsuCAFgeXRdMxxV8BK0EZALqUSA/0YA2yszq+NVgeTv8eHaYKB0vrTm7SN5I/cdbZgfn5GVB+NX4Hihr5VB48KH+gTPe5/geJRo3gt5BBr1D2HH84zyX4smSKWZwe1P/F23vAh9lcTUOP3vN5roLJCGBIAsEDQZoIBETApgneZbswgZCCAQ0SIAkgiLEZJeL16QLleXpKqXqq639qvbtW2u1orYCWnVDhAQUCNhiEFuj9fLE9RJRw02y3zln5tlLEuz7//++D83OM/czM2fOnDNz5owCAb1IJHL4tr/hww/YvLOCPP6uQz4Kqb9QvnAHg2KwXe6SvPd04l4obqMX2BQ8WEx8/gO0N0qaKy8UKWMAjBdmK9hieUWv3OZRNExOkOR7vvAoWlcBWQkRPUG9eyrArwGGdE8twP+xNgJ+OXH5v/hlV2UNRPTglq1T/nTPWmjIKeCcIMNLlOHQTiNm8FzSuUa+kKX8P1pkw9BGKHy8MEl5AJ2ZCuoeEudn2x501eF56VY8mznumf0+IPT8e8cC2bwaoKmC4D2TofClkdAE4iE65oXJCj0Qbn5Zn+kIvglkv1XR
*/