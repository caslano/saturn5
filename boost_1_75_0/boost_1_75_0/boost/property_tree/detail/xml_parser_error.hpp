// ----------------------------------------------------------------------------
// Copyright (C) 2002-2006 Marcin Kalicinski
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see www.boost.org
// ----------------------------------------------------------------------------
#ifndef BOOST_PROPERTY_TREE_DETAIL_XML_PARSER_ERROR_HPP_INCLUDED
#define BOOST_PROPERTY_TREE_DETAIL_XML_PARSER_ERROR_HPP_INCLUDED

#include <boost/property_tree/detail/file_parser_error.hpp>
#include <string>

namespace boost { namespace property_tree { namespace xml_parser
{

    //! Xml parser error
    class xml_parser_error: public file_parser_error
    {
    public:
        xml_parser_error(const std::string &msg,
                         const std::string &file,
                         unsigned long l):
            file_parser_error(msg, file, l)
        {
        }
    };

} } }

#endif

/* xml_parser_error.hpp
qr9uCEp0u/M++4YJmg5XS54dCx9QQKEx+NkTUEyb930Z++dd0p+iVMslHfDZO2URv3XyFYrZBZHZvrBxv266hLYp92hmSPKsMXSuXjK26hRcDj8W5zVmgmXHb6celC20N61Lcm+ljvHNqeRjbboMecjN5lDf+jfxvtIVO5R+s0wIqLHXFSNqH4uombWh/QBZRE2MiJOgsAWli47v78ZXcLxUlH7w2b8cDzKdVPBiY2w/7Bh04JdETURjPe44RMvI0PXjfQUQg8Kt4cot/KQuoKOfUKC0XY57EtsiNy/ZtqCQViiSy0JxXg71gGbaCq13wI892NHePkgQDFTCOhXziE1UKqFxpQvjSLvCUbuyr/lsOQPQEWnuOykwbk7Lbn71pMCOIVX3+sv1ZdWFrwE/ixCEOpT4yKpam71M57TAbaUbHSqZIhWAfcJRAbmA0U/Ll1l+mL3PHjEB7UEB+6DCfBwKkN9lL95mePFMluFFsniZ7MXD0/Qvrje+aCU7zF5c+JL+xdeUF5mtLgWn0DrxJdqfIksx9P20jgG5GsthhiGHtCzN+qrvy+jNyJ9Q/BKx8gTZ0edwMVWhdTpYktkCmzz3qjpbYJYyRk1Tel5CrEdUY5gfP4N6iPvOZz6OPI0dv94OO8kat8HRSqlLHh6bFyl6e0WJicPDMyNwcAp/4csqLW0kSlGit0+kPDBKG4PYLbfuh4Cj0ZxDGV3J
*/