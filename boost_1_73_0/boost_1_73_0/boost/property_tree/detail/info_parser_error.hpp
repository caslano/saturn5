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
vIOBj0HVReNQ95HUUZy14/n7UtxqXdFErmcQX+UehKE7aFuT3x+uIlcmFU8sHJFXNF68OK/a7wTSCwpzi0/JLzyBVN/stKLcvNG6X4E8+UUTZaZBaGuKauvL8UDNsqEWAK3ccqZpI7IH6epImKYDMuUXGJoH00bl54GIJ+XqdE+mx/PRmxG0VdHcwEYK3b2jsLW5ra/GVQvspvrfkp6Fflt5KFXXx+FnbqHiDws+Mn/0ZNJtteCCVAWF+aNgSqg=
*/