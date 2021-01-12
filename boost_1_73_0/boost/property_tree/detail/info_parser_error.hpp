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
JS38XBPBEsNy48VFIvVRYgzO/Gmpza+czEA7eeApFaIoJTpbxDFzKkB4B5OS0ITPKN7GLq6p61V/NKzVgSowmlCNQBJL+r4fbDxDZ2q+MLIYiIwxY+GBpCuTkUoZQh18FJZDd4OoQNOsbLp2t8BRsu4j0fadV6HrzRciKz4Qj2AIQF5xb/XCBLIcYX4yBz6NoW8muPJW1okkg7+8uE6b/DsDgsBB66Nc28YdiUM3XuOUdv6D
*/