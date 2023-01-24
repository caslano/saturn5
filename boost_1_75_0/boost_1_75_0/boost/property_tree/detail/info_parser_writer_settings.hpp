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
zyfz5XWf2jkMp+Wioy/68qZ2tghZV8G2BbmC80q+Qk1gGdAyH+xfINY4LbBc2Ha5IB5TO9vgd9Qnyeb6CpBp6dOs+AK4y+pA/Us5gtAFb4+rVuDsIdAbUh6rQHBRabjoK56aOCSzJptunZQPDkBwgaUSxWGt8biapM0Te7opO9wxE5irYB4bxfkdNKE0BjNhU+Ho069CAn9S141b7oPbVzbDYI296YrWhz9O2p6hnLlDE6qphwPkg5j5b8bMdCyb9YW9GjPTJLsbDqlsHdNP0r1+qJzeqcGKbjrWBGOT0ibI3twMldbwBvHpEJ99dC4uNE8YEpOeVU+y3pzLjlWbbb0GqVkpMSMTGz8lY/bW0rnE3efmKuC5bc4iaAV5rlY4CaKXpJgXFi3/EMK2EEtTyFv0vo7vyO1o6h65hx8oLJ6GDTwIBC8dhHAQlgJB7XR6L2sovSB6+6en4KzBQnkdeCMQHWR2owfy1YbmYuwj56L/30Tdycb488ns51l116urcNLkbyAPaUupHcDESoio8B1zFeCQqkMYaH1HMqousjKqhj/aegHk5QwCx7pjj8bL6XTnCDpxT2wKD1KUxy0VkzThXjqo2z57cTYazkJk7rQgRUPkc//SpKnWajfUHHqmKCHbv5Xtr+azT8s2iNkcVjBUefEIVuV5IUze4M9wto4b6ptG8zOsjXh9sU+dazkUcFh+/F/WYP3i96Z4
*/