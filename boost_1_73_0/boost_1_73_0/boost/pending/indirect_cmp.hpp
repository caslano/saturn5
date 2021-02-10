//
//=======================================================================
// Copyright 1997, 1998, 1999, 2000 University of Notre Dame.
// Authors: Andrew Lumsdaine, Lie-Quan Lee, Jeremy G. Siek
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//=======================================================================
//

#ifndef BOOST_INDIRECT_CMP_HPP
#define BOOST_INDIRECT_CMP_HPP

#include <functional>
#include <boost/config.hpp>
#include <boost/property_map/property_map.hpp>

namespace boost
{

//: indirect_cmp
//
// could also do this with compose_f_gx_hx, and the member binder...
//
//! category: functors
//! component: type
//! tparam: ReadablePropertyMap - a model of ReadablePropertyMap
//! definition: functor.h
template < class ReadablePropertyMap, class Compare > class indirect_cmp
{
public:
    typedef
        typename boost::property_traits< ReadablePropertyMap >::value_type T;
    typedef typename boost::property_traits< ReadablePropertyMap >::key_type K;
    typedef K first_argument_type;
    typedef K second_argument_type;
    typedef bool result_type;
    inline indirect_cmp(
        const ReadablePropertyMap& df, const Compare& c = Compare())
    : d(df), cmp(c)
    {
    }

    template < class A, class B >
    inline bool operator()(const A& u, const B& v) const
    {
        const T& du = get(d, u);
        const T& dv = get(d, v);
        return cmp(du, dv);
    }

protected:
    ReadablePropertyMap d;
    Compare cmp;
};

template < typename Compare, typename ReadablePropertyMap >
indirect_cmp< ReadablePropertyMap, Compare > make_indirect_cmp(
    const Compare& cmp, ReadablePropertyMap pmap)
{
    indirect_cmp< ReadablePropertyMap, Compare > p(pmap, cmp);
    return p;
}

template < class ReadablePropertyMap > class indirect_pmap
{
public:
    typedef
        typename boost::property_traits< ReadablePropertyMap >::value_type T;
    typedef typename boost::property_traits< ReadablePropertyMap >::key_type K;
    typedef K argument_type;
    typedef T result_type;
    inline indirect_pmap(const ReadablePropertyMap& df) : d(df) {}

    inline T operator()(const K& u) const { return get(d, u); }

protected:
    ReadablePropertyMap d;
};

template < typename ReadablePropertyMap >
indirect_pmap< ReadablePropertyMap > make_indirect_pmap(
    ReadablePropertyMap pmap)
{
    indirect_pmap< ReadablePropertyMap > f(pmap);
    return f;
}

} // namespace boost

#endif // GGCL_INDIRECT_CMP_HPP

/* indirect_cmp.hpp
JhMPpoknS20qdEbdG2HI8TUddvLovqxJkDX46uKo34tMy3kp1/5WFgK1Is8dZwqqMWU+ZBg24mKCByckN7f2xuy8qLOOuaPVyR2RrY4DoJ667Qzvh55u5YtjbLncjU3cHFbJxCzSWw6yc0t4v/DVRJu6m/Kfaei/n1AwswpBK4hmbnw5jQnKQKi6mAs/tO9Ouj8xTEZNDUbeOS3ukZ/qK1MwQlplt7euEJASE7AB9ZFeM4gPtsxYEQ2ZCy+bDV9U7lmY/NlSUq14LXoGcqbbaUAgqfPJDOUAlIFMwsiQmMGZLv6UwTBXfBVdMkE9SR43rsvr1fD2QXXHWdQDwZxcG4odPtB5u6l9ciGgM4khYixQ6o0oyy+w12rlhY53VfG48HNzc31TUHg4Xm6Y4NlayokCvBeFH8ZlpSbngxV14sKWBFsqjWlsdKK4gzFPSrZVy0dthbc6MWXWnXGSrnSjcJpsV/T51EyziuPRRoXPKDTbaVLrIrlKpJ+YMzxTLjPdGk4oCqtSbsX9kU7qoKz6w5rYzDZnnXhghLEHV5uTKiYW0Ro3Xe5VOnTRXO0wsCZAk4FIajXrVvR6Nm8KnQGGc4+dAWjOzsD7XGfwjTngIXUJxCSf7szJGvwSVxHou6Ex8aiJXm9lXXrkoiPu
*/