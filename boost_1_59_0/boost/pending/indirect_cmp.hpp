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
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
*/