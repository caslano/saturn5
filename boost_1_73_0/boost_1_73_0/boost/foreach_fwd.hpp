///////////////////////////////////////////////////////////////////////////////
// foreach.hpp header file
//
// Copyright 2010 Eric Niebler.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
// See http://www.boost.org/libs/foreach for documentation
//
// Credits:
// Kazutoshi Satoda: for suggesting the need for a _fwd header for foreach's
//                      customization points.

#ifndef BOOST_FOREACH_FWD_HPP
#define BOOST_FOREACH_FWD_HPP

// This must be at global scope, hence the uglified name
enum boost_foreach_argument_dependent_lookup_hack
{
    boost_foreach_argument_dependent_lookup_hack_value
};

namespace boost
{

namespace foreach
{
    ///////////////////////////////////////////////////////////////////////////////
    // boost::foreach::tag
    //
    typedef boost_foreach_argument_dependent_lookup_hack tag;

    ///////////////////////////////////////////////////////////////////////////////
    // boost::foreach::is_lightweight_proxy
    //   Specialize this for user-defined collection types if they are inexpensive to copy.
    //   This tells BOOST_FOREACH it can avoid the rvalue/lvalue detection stuff.
    template<typename T>
    struct is_lightweight_proxy;

    ///////////////////////////////////////////////////////////////////////////////
    // boost::foreach::is_noncopyable
    //   Specialize this for user-defined collection types if they cannot be copied.
    //   This also tells BOOST_FOREACH to avoid the rvalue/lvalue detection stuff.
    template<typename T>
    struct is_noncopyable;

} // namespace foreach

} // namespace boost

#endif

/* foreach_fwd.hpp
17k57MJ8+9BTTNjdOmYJ9BwTf7UOfObxDr/fBzpsETu+x1HPfQAMB3hmWeScxeCLEXrXVUzje2g4Cl0G0IRMuMatHwTgbyDFOAgo5kxGI9vpmhPQaoHP8oY3NPa5f0AfqD6OohTcM0lpEFB0LAQWhLmWCaNeaxQG95lY8kYp742mwy5oTu6TlK3AcxOur8/8lUeDnKWi9UC/HE3REu3CtDXEUJNNNeLPYVLuwbxwQeYRTHRbiZnDzmDaNeQg8vr90A02HkDgQ7ik0bangfnHRJ+YhoVYgoAwBH0yZMwTLgUOLsaoRIbn2IXRsUdSsivVohwIUI/LBX54zdDVaewuITbTZV6FMcFhnqG47nk+gsmB4DLzgC4S1bozuhibg+r2brRagy+XJC6NiWWOhnxMMIvo4YzH6g0EE84a9eBb6iPzXN2T9fWi5Ubh3F8g0jFMI5nHEGoroLI5S9L2LneaIXFpwjjIcvKwGz4fBIKHhNvO/HCepxo/fQred8WUTdomvA6j21Cr1eBO3YEZdy5G3aF+YRAggNZ1fPVba5EkdO03RIu+YV509UHWailmOWtUk9Nd7yyZe22KHz2AqbH3SVJ6ZN+vmeX/ByREl1mA9M2hbdUQAu3JX/mwedDkXWN4WX4AWk5ImgtVBdkm
*/