// ----------------------------------------------------------------------------
// Copyright (C) 2002-2006 Marcin Kalicinski
// Copyright (C) 2007 Alexey Baskakov
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see www.boost.org
// ----------------------------------------------------------------------------
#ifndef BOOST_PROPERTY_TREE_DETAIL_INFO_PARSER_WRITER_SETTINGS_HPP_INCLUDED
#define BOOST_PROPERTY_TREE_DETAIL_INFO_PARSER_WRITER_SETTINGS_HPP_INCLUDED

#include <string>

namespace boost { namespace property_tree { namespace info_parser
{

    template <class Ch>
    class info_writer_settings
    {
    public:
        info_writer_settings(Ch indent_char = Ch(' '), unsigned indent_count = 4):
            indent_char(indent_char),
            indent_count(indent_count)
        {
        }
        Ch indent_char;
        int indent_count;
    };

    template <class Ch>
    info_writer_settings<Ch> info_writer_make_settings(Ch indent_char = Ch(' '), unsigned indent_count = 4)
    {
        return info_writer_settings<Ch>(indent_char, indent_count);
    }

} } }

#endif

/* info_parser_writer_settings.hpp
crH3+vE36VxCqCmRE2xK2Do7ZqagGZ4Dp3cPg09JINewDMLzU6acfsAKzCJZPNxW/lmky+4X62jaMDFtrJkCQC4PEpU9SL62WRGDRKI5q0MSljOrowqbuAt84QYIW/WQQhhYEKNCR/6e2D4IjHmI17n2iWvtTy57Gnn5w9PRBzj8nOiutyktsLV/s92m1ZOqLN7CJvXduiQg8JkbUKwHhT2nb3l9CoGfwC3KppcY2B7vTBJZrA7i1Srcsn5luaAEHsVyLbT2aRbOeCEi4ra6MK+FGYgXtsDWSHVwTtHHHn3Du8l/EzlBEUqujQEdvWULN92UWSr35Tuq4Ni3WOZIZHyYpyJ/o1QJEo9oEP2u2yUYiTSBas9Khd9GQLmz0yK+QAFzd0lsg13Uz8wFoi5br+nm8ryuqEP6U3aJZlfZ7ugn4gQEHeTf1HTRQBDz3kkrBqGgDf8LxrcR96acX2vFoykmldtBw9/EChhiqtMlB3e0QD0jYCXoShovwHfRjAn92aNvzVh2fH1sTHAjINy1xTFFCTmebpamEvnutrItk6ynznYnvdU7jGexbA==
*/