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
fbP+/h11Pz4G7gNsiQTXOIdEK8ZTfYwwqgJU3n14+Z77FcBpuuzKWCfSVAvHjkH6dsOY6aaR9iBegt7PT7LDZROwCcBaIP1uxj1mlsb7sfOHdSGaa/0yXRqx7n5lE+VKt54lUflXgS98YmQrpV/JUX2bfnOdsT5i+z/bDPK9k2j7JuSDYho28RdMqzxhutGmran0vWFBi0E89msMXia6BuJCTvkDScOdFiU/p7mJzaU7AEaFQtP8Kw/ueJKL50ZAlnd+AJd+6p5FOfddvoMm7MruKKVnrOH6CdxF0lFXvSvZ3VbKO4plZ6RrpqdZ3ifZ3XpqhThwiXXxW3OG95gM2ZnEAlLF42OjIdj8PoUwKeU4Ulq58bEmLsENqQn9Z0D0Df4qjfG3hGutn5rwQSg4PLK0VhsGm4LGKFabpE2h7dm9CJrtAKmY9gDSVy5ofjlGITxVzJkfk8ZhbkrTIw6x7d1SURM4CxD7I7wbstYITTyzfryN0seIzcOjzCb5VavTqnXL05r1z6ZNzxydEW8eiG9QboqPJiCg2s5PwDFEChzlwXoFHji6Zo0ckvqIHENggDihR9r+bFpQ6s/GI/sqNMAL30jpGeY74hG9++8Xgoi3crXbmcIZkG1x4N4ptO0Cg35c3bYlIHZKlGb79ENy0PB6a8MdQjNOs6H58EFC9XAm8zpTLWssMCSiFuL82rXoQVEt6xBBTmzdKpC/
*/