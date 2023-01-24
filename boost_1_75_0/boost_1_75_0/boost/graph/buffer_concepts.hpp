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
xKWzWDu72B/HHxONP31l/V+cf6X+z8afz8T+j/af9WFzKBN9h8v7tngsf8uKOWTk2q+fNQRrDPxXDnaxLRxzZpE4b4tz5tX9yR7LT14ZVadoFzUq7WJbiDpYq+tw9YD7mLzu0vbVP7rU7zL+yOyfonbOv+vJ/xH7P5u3yQ4W8h0eMN8h9/Auj+XvWvdTva5fNAIS3RPljnn76LY42LN+MWxdOhNiZo33WH5q7JL6yxeUEO5LbIuVOIc8rv+/e+Oyx5QvJtRhNc4hpw/uYfjKlDU/wrAv3yX5AzyRnx6/4snkox3Wzp4MNy7koA67YcK3HUi+R7IpGTevekL5AOtxDil+9AAiRn5D8j2WTWm/YU31Cu1C3xL8ENm8I/rmpffIF7uOvthl5jtvmK+DRWHDSX69ZFM6uGUdZKAO+xNXg3HTKtibsAL2xC2H3RuWQVrsYtgVsxB2rv0JdmC7Jq+aB1ujoyBp+RxIXBYJm5dEQAKO33E4h6D8est+FonMKz57/yXI5fk+pfri8eqzB21NcUitOCfTsS6qiZ+th8m3IJ+f1hwXhXVXkfmgsO7DtW+t/DgnMD+J1i83cO1yFX3Vi9lsHV10+hBbx9fGTz4fzQvZ/QPgwLf+sLPn32BD59dg2Wd/ZL4/rf9q42c+NM1P5D/THI3rLeuti8xXK8HrKcY1fU38qesXsTmGycc5SZK/8UuS/wcmn34/qIk/
*/