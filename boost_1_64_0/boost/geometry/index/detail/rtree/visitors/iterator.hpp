// Boost.Geometry Index
//
// R-tree iterator visitor implementation
//
// Copyright (c) 2011-2015 Adam Wulkiewicz, Lodz, Poland.
//
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_INDEX_DETAIL_RTREE_VISITORS_ITERATOR_HPP
#define BOOST_GEOMETRY_INDEX_DETAIL_RTREE_VISITORS_ITERATOR_HPP

namespace boost { namespace geometry { namespace index {

namespace detail { namespace rtree { namespace visitors {

template <typename Value, typename Options, typename Translator, typename Box, typename Allocators>
class iterator
    : public rtree::visitor<Value, typename Options::parameters_type, Box, Allocators, typename Options::node_tag, true>::type
{
public:
    typedef typename rtree::node<Value, typename Options::parameters_type, Box, Allocators, typename Options::node_tag>::type node;
    typedef typename rtree::internal_node<Value, typename Options::parameters_type, Box, Allocators, typename Options::node_tag>::type internal_node;
    typedef typename rtree::leaf<Value, typename Options::parameters_type, Box, Allocators, typename Options::node_tag>::type leaf;

    typedef typename Allocators::size_type size_type;
    typedef typename Allocators::const_reference const_reference;
    typedef typename Allocators::node_pointer node_pointer;

    typedef typename rtree::elements_type<internal_node>::type::const_iterator internal_iterator;
    typedef typename rtree::elements_type<leaf>::type leaf_elements;
    typedef typename rtree::elements_type<leaf>::type::const_iterator leaf_iterator;

    inline iterator()
        : m_values(NULL)
        , m_current()
    {}

    inline void operator()(internal_node const& n)
    {
        typedef typename rtree::elements_type<internal_node>::type elements_type;
        elements_type const& elements = rtree::elements(n);

        m_internal_stack.push_back(std::make_pair(elements.begin(), elements.end()));
    }

    inline void operator()(leaf const& n)
    {
        m_values = ::boost::addressof(rtree::elements(n));
        m_current = rtree::elements(n).begin();
    }

    const_reference dereference() const
    {
        BOOST_GEOMETRY_INDEX_ASSERT(m_values, "not dereferencable");
        return *m_current;
    }

    void initialize(node_pointer root)
    {
        rtree::apply_visitor(*this, *root);
        search_value();
    }

    void increment()
    {
        ++m_current;
        search_value();
    }

    void search_value()
    {
        for (;;)
        {
            // if leaf is choosen, move to the next value in leaf
            if ( m_values )
            {
                // there are more values in the current leaf
                if ( m_current != m_values->end() )
                {
                    return;
                }
                // no more values, clear current leaf
                else
                {
                    m_values = 0;
                }
            }
            // if leaf isn't choosen, move to the next leaf
            else
            {
                // return if there is no more nodes to traverse
                if ( m_internal_stack.empty() )
                    return;

                // no more children in current node, remove it from stack
                if ( m_internal_stack.back().first == m_internal_stack.back().second )
                {
                    m_internal_stack.pop_back();
                    continue;
                }

                internal_iterator it = m_internal_stack.back().first;
                ++m_internal_stack.back().first;

                // push the next node to the stack
                rtree::apply_visitor(*this, *(it->second));
            }
        }
    }

    bool is_end() const
    {
        return 0 == m_values;
    }

    friend bool operator==(iterator const& l, iterator const& r)
    {
        return (l.m_values == r.m_values) && (0 == l.m_values || l.m_current == r.m_current );
    }

private:

    std::vector< std::pair<internal_iterator, internal_iterator> > m_internal_stack;
    const leaf_elements * m_values;
    leaf_iterator m_current;
};

}}} // namespace detail::rtree::visitors

}}} // namespace boost::geometry::index

#endif // BOOST_GEOMETRY_INDEX_DETAIL_RTREE_VISITORS_ITERATOR_HPP

/* iterator.hpp
SqryCnRjpu/DKpX/Tj2X/xHldwnhowe324Sv9ipXbhJjsl2t6M/0PcgysYqsXOmviqFT+X052h8P1UmYlVCK0d9WXKHyubVT6brs0vR5sJuUfUpc8PVy5HqF8EviRYyjvbKGRZdt7mXlBWVWWczlWrpOBY6zsmYo+4qgtS5eaR/eUWF/Ed0V2/vcS6TdkHue81Sb2foMGuvSckYB9vxOgckqT2IC6sN0Tuw2NwjAjbRP96r6NRzdd3+qYKz7lvtSr02SsfjF5poJVQ/26v53s9Irxd7XfrnEXuvq+X1rLP0OF36WayVEL0xMiI5LcNU2lF0i5iuQZUF2XuzaY34Lstyya4iF/ZlJ6tiI/f7nhMG4X4pYz6QLW8u7AC2++LSvL/GpfXVVQnSijs8a/LbBblmgncTnCexa1dfxMSLFp4u05WZ89uAntb6OT+3g+LSW+FyOm62mm6iFdyZERSdENU5wxiS4oszfrmj6Xdx1wk0FstpytyXQhS88r4RneMlz65pbeWFif56UeDaUMjL9zCXc75Hb/X5U/B/F7BiyUsxNsx3oR5EVYqbTExSHQn8cVhFXdZ0ozPKR2wPM1TtOzLKRlWJumnVDH4+sELNI13nCq/PuUEJyLRVeMWabvJJXyQu/CHkWl7FWhw+ssvKFOZH1AV7cZQasid2OPI+8gLyIZCIvITvk9z3iNnjtzX0Bv18OWHM2V94jRlprk+nyrznj/red+7wFO54tsWcwJWv2n3f51trIs6GcB70T85Zirtsh8bPH5VtTqp/RVPj7tLn1TJWGGc8kcl56+GeZjrip0m6O/8xixu2Yvo79WaQZdnS18l4i9JmCuKtxfImy188FynwNZrervPGPZzFXYxHaOcz1GEXFIdPpM7ePT/BDn+pbiyR9rcSb9l3W6dnafmVHeUi87e2+x4yDvpa6ijrb+TWzrcY9YyClr9tn1w8F6c3ft+vlQfpdQXrRB3Z9tuiM69V7jkHynqOkkVUBh8l7zSHIJNxkHLS955AXHL7XHWUzSko4ZbsgP/h9hx7fj1D+z+RJXe83I2F6+O8i9f7ncd99Vo01xHJGdmD9t72jy2hsOZ5pQZXFKtxWWukoLy7rnDU1v3vg44zse6DjLvH0+ZkZ/r2LvB8RN8fdM8n3Horr2O5bPNnv26D0JMqGVNdJYNdKejIP+dPD17LOgQkKnx7xQ0iR06PdnPD0+N4rHpD0vCeBvSvpMT6xpadL9x6BKYqYJvH33s+mSdz8Zmna1NQKZIwENlrSlPqpLU3dO3epXposf1GR06TdjPkN0qTaAyzlPBYkBbkbuYY0LdVpIi0lZb6GoKCCZzdD3hkkqHZAtqKyLqnThn/9LvMM/R7K3mb8Sbm5xmhhxEt6xR8mQe/79H4dDyn7G4y28n4pU/shh+zv0mi0/XsWPaDcLDc6S/s0XPtrHOBveimPbeJPv+8Tdw69ft0r7mMNyRXVy+CHbt33TfVrSYe45S/gBY3k0wjC/1a5O1+vKR2VRL2SdvK1pOrtI9FI2soE1VbaykPv83OG7n+x0PtK2Pp/5Xawoft2yUPLPFOb6zzSaxdTXDVfM1bTtWHh1wRGWjN54tYohl8bWfM1luHXUkZeA7k+xjT/3Yh7Cl9qMs6T3mXiW4c+S0uq+RrI8GsII68pnew1zZ+cWXHoviVjB7b8x4yhXy8eUT/yWsrwa1AjrUWs+RrLmq5d/K3XZIZfexl5DeRXcjYSf+rZ5nmHdX7USvldzO/b5XcFv5fL7/n8Xia/l/D7Wfl9izmmk9/3mP2P/L6C31vl93p+6zPv3vbt1Yhd0Fks18uaySUwCd4Aff5KfsbfzeLvFvF3a4C/peI=
*/