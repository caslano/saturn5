//            Copyright Daniel Trebbien 2010.
// Distributed under the Boost Software License, Version 1.0.
//   (See accompanying file LICENSE_1_0.txt or the copy at
//         http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GRAPH_BUFFER_CONCEPTS_HPP
#define BOOST_GRAPH_BUFFER_CONCEPTS_HPP 1
#include <boost/concept_check.hpp>
#include <boost/property_map/property_map.hpp>
#include <boost/typeof/typeof.hpp>
#include <boost/type_traits/add_const.hpp>
#include <boost/type_traits/add_reference.hpp>
#include <boost/type_traits/remove_reference.hpp>

#include <boost/concept/detail/concept_def.hpp>
namespace boost
{

BOOST_concept(Buffer, (B))
{
    typedef typename B::value_type value_type;
    typedef typename B::size_type size_type;

    BOOST_CONCEPT_USAGE(Buffer)
    {
        typedef typename boost::add_reference< value_type >::type reference;

        BOOST_CONCEPT_ASSERT((Assignable< value_type >));

        buf.push(g_ct);
        buf.pop();
        reference t = buf.top();
        boost::ignore_unused_variable_warning(t);
    }

    void const_constraints(const B& cbuf)
    {
        typedef typename boost::add_const<
            typename boost::remove_reference< value_type >::type >::type&
            const_reference;

        const_reference ct = cbuf.top();
        s = cbuf.size();
        if (cbuf.empty())
            dummy = __LINE__;
    }

    int dummy;

    static const value_type g_ct;
    size_type s;
    B buf;
};

BOOST_concept(UpdatableQueue, (Q)) : Buffer< Q >
{
    BOOST_CONCEPT_USAGE(UpdatableQueue) { q.update(g_ct); }

    void const_constraints(const Q& cq)
    {
        if (cq.contains(g_ct))
            dummy = __LINE__;
    }

    int dummy;

    static const typename Buffer< Q >::value_type g_ct;
    Q q;
};

BOOST_concept(KeyedUpdatableQueue, (Q)) : UpdatableQueue< Q >
{
    typedef typename Q::key_type key_type;
    typedef typename Q::key_map key_map;

    BOOST_CONCEPT_USAGE(KeyedUpdatableQueue)
    {
        BOOST_CONCEPT_ASSERT((boost::ReadWritePropertyMapConcept< key_map,
            typename Buffer< Q >::value_type >));
    }

    void const_constraints(const Q& cq)
    {
        km = cq.keys();
        k = get(km, g_ct);
    }

    static const typename Buffer< Q >::value_type g_ct;
    key_type k;
    key_map km;
    Q q;
};

} // end `namespace boost`
#include <boost/concept/detail/concept_undef.hpp>

#endif // !BOOST_GRAPH_BUFFER_CONCEPTS_HPP

/* buffer_concepts.hpp
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
*/