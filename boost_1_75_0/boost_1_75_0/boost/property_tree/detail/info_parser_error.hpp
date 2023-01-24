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
Z8zCir2w3gsDIHPEn30KOfvELvRjn/mVYJ8rEkdkfy7Zgbc4IpcXVs0V276QI7J6oco+9Rn7SJKZfdpx9nn0TTP7rJiksI+Cw2753UkGZ2x5ZzZBvdRqOP39t8uAxaWOQEVWzSNz6kUgwSQCZ98wi0D7SWYRuGMSbVjk55JFAxHFuqTJcRoZKUz040yNXQp4cj1PruTJj3jy7ZnIRNwnM7hjTnTHTgARuaXrEHIgEaFPthd7ABks5tN7fpDHd9B8rto0a8fDXimZofSX5Sk6ervD29OHG6LXwS/r3EF15TKLf/wDyozF0nEBEq1bPYirhIa0VM50x/zUXzdUnLOwBXrnrNoCzTn7Y77eOSubjw22W24fpnDjUeRGkNJ9Cjcqx8Bj/ytwY34448bHVG5MYtzY5X01Lh/cQ3cOfM8JCj+q6xQqeRT8qQUVDyRtXhBAER/2p8ienCLfX+BHkXWqQJGjZnGFTJmOijThda6Qj70uVGkAqdPruvkfr6sU6WUUeWNm+U6abuCoYL5ZP+plGSOWkCxGkHEMmdqJGkEmy3EhyjydpZlV8c/wDICKvOd75gdaneXPkLs4Q4bO92PItyvBkD/N4IB8M5XWv87XrX+dfyuv2ciQn87XrX+drzJkY8aQT86owD/r9pqZIb3jjcHqi+MZP8axlp/dkU6DR50NeBr8938AURa38z8NPoDPpj//8VWzOFjHG8Xh
*/