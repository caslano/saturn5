#ifndef BOOST_ARCHIVE_DETAIL_INTERFACE_IARCHIVE_HPP
#define BOOST_ARCHIVE_DETAIL_INTERFACE_IARCHIVE_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// interface_iarchive.hpp

// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com .
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.
#include <cstddef> // NULL
#include <boost/cstdint.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/archive/detail/auto_link_archive.hpp>
#include <boost/archive/detail/iserializer.hpp>
#include <boost/archive/detail/helper_collection.hpp>
#include <boost/serialization/singleton.hpp>
#include <boost/archive/detail/abi_prefix.hpp> // must be the last header

namespace boost {
namespace archive {
namespace detail {

class basic_pointer_iserializer;

template<class Archive>
class interface_iarchive
{
protected:
    interface_iarchive(){};
public:
    /////////////////////////////////////////////////////////
    // archive public interface
    typedef mpl::bool_<true> is_loading;
    typedef mpl::bool_<false> is_saving;

    // return a pointer to the most derived class
    Archive * This(){
        return static_cast<Archive *>(this);
    }

    template<class T>
    const basic_pointer_iserializer *
    register_type(T * = NULL){
        const basic_pointer_iserializer & bpis =
            boost::serialization::singleton<
                pointer_iserializer<Archive, T>
            >::get_const_instance();
        this->This()->register_basic_serializer(bpis.get_basic_serializer());
        return & bpis;
    }
    template<class Helper>
    Helper &
    get_helper(void * const id = 0){
        helper_collection & hc = this->This()->get_helper_collection();
        return hc.template find_helper<Helper>(id);
    }

    template<class T>
    Archive & operator>>(T & t){
        this->This()->load_override(t);
        return * this->This();
    }

    // the & operator
    template<class T>
    Archive & operator&(T & t){
        return *(this->This()) >> t;
    }
};

} // namespace detail
} // namespace archive
} // namespace boost

#include <boost/archive/detail/abi_suffix.hpp> // pops abi_suffix.hpp pragmas

#endif // BOOST_ARCHIVE_DETAIL_INTERFACE_IARCHIVE_HPP

/* interface_iarchive.hpp
P1Ultzfqi5YHKfkKdivVMGTux8//3/j56zheitAc+urBzZgYmr9RtcLTBVMdFqfaww0C7Ja3PEywNt393PhJ/ZzbnzUz80ouqfY8q+ZskR6dORh3u658a3MuUb8z6/lTVkb+XasNjGvzLyn+2DG1en1E6qWjs52E35FueNTN+3S03I3NOPPFJcv1qwt4Aw/Pn0mo7/bbp0HbKXY8UrZRZs8U0Yr5zT+/jVl+pWXjCxx7ZRPrsemzJ196nMNcTPKrvrbNCvPiZKRzcYvQ21vLzEP30gN3xYRW9cobV04tu+Laq5jV2NNqf1tl87xNx/gZyuIf+Tt7fZYe+xZj4iSybu2S9dlXRPxq9FWV1SlpnGZs/Z0pegu+++lGjd6KtdeOv661/PJz7Mf+/3/c/9uv9+5p21C/IGp5xYaHczgX2r+aE3dvpsm+o4/i57jf/zTdfTn2zWG6ar3Q+mmzMdr7RcsyjalbXSiOX+ak9LyYstNiyYFGzdrwgdfRnt3rq+SaS3LX9waoTi0cYidPIddpDCyCZ77uz3yY4Wa5tDDmrqy43eiVq8MrpkHE4T8cKB20ExJt2/x7cWZLVj1MOXsgwSP7dVtykmjThQaPcJPHyxa9iTY//4yndmRuD5O0FncQb6ytfWvL52/OnBzpNArJ7mxQSuX9ob5fGHOcZ75k8P68r4MLbRfrHAxP+zlOt9f9zZbqfE4Mup69/YTpBckpcUX01R/O/Lit3bTgxNp46/tdbxUiv8yL8ZM/8zH/P+b//13+MxGUX88dfhzT/LH8bxVn3ymBnm6egaErI+Pfnw4MXhYStPzPl4MLZf/2+Y/xu1RPVO+fAlmxYgXauHEjMjQ0RE+ePEGlpaWIz+ejs2fPoq6uLnT//n2UnJyM5s6diywsLNDjx4+RjIwM+vbbb5GTkxPi8Xior68PhYeHo7S0NOTm5oZUVVXRoUOHEJfLRb29vUhWVhZ5eXmhGTNmIDabjUJCQtCXX36Jqqqq0KZNm9DJkydRcXExSk1NRWvXrkU9PT2Iw+GgK1euIHt7e2RiYoJ++uknFBgYiObPn4/q6uoQjUZDampq6PDhw6ijowPZ2NigixcvoubmZuTu7o4CAgKQVCpFt27dQhj4K/m8efPQzZs3kbe3N5ozZw5aBlfvenp6oq1btyI6nY727t0LNzFfjIaHh9GlS5fQsWPHkJGREYqJiUEKCgpIKBSOP4ju2bNnqKSkBH3++ecoMzMTtbe3o08++QQ1NDSg77//Hpmbm6P169ejuLg4BNcXooiICFReXo4KCgqQWCxGTU1NSFlZGcG1iKilpQUpKiqiTz/9FNna2qKgoCB0584dpK6ujuTl5ZGGhgYyNTVFDAYDff3110hJSQn5+PggFRUV9Pz5c6StrY3evn2LXF1dUWNjI/ruu+9QbW0tKisrQ6tXr0a7du1COjo6aOw6wIcPH6IjR46gBQsWoDdv3qCwsDA0c+ZMdPToUXT16lW0f/9+tG7dOpSbm4s2b96MFi5ciDIyMtDs2bORv78/0tTUROnp6eju3bto7HqfRYsWoWvXriE5OTn0ww8/jPelqVOnory8PPTy5UsUGxuLWltb0ZYtWxBcf4kePHiAbt++jSgUCnJwcEBtbW3oq6++QikpKeizzz5DSUlJCIvFosuXL6Pp06ejnTt3IjMzMxQdHY1CQ0PRzz//jAYGBlB2djZKSEhA1dXV6N69e2jWrFkoKysL/fjjj0hPTw9duHABWVlZoXPnziGJRIISExPR7t27UWRkJPLw8EBMJhOdOXMGBQcHQ9IYo0ePHqFVq1ah/Px8tG3bNpSTk4OWL1+OTp8+jXbs2IEEAgEaHBxEQ0M=
*/