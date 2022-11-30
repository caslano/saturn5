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
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
*/