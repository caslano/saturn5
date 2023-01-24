// Boost.Geometry Index
//
// R-tree levels validating visitor implementation
//
// Copyright (c) 2011-2013 Adam Wulkiewicz, Lodz, Poland.
//
// This file was modified by Oracle on 2019.
// Modifications copyright (c) 2019 Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle
//
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_INDEX_DETAIL_RTREE_UTILITIES_ARE_LEVELS_OK_HPP
#define BOOST_GEOMETRY_INDEX_DETAIL_RTREE_UTILITIES_ARE_LEVELS_OK_HPP

#include <boost/geometry/index/detail/rtree/node/node.hpp>

namespace boost { namespace geometry { namespace index { namespace detail { namespace rtree { namespace utilities {

namespace visitors {

template <typename MembersHolder>
class are_levels_ok
    : public MembersHolder::visitor_const
{
    typedef typename MembersHolder::internal_node internal_node;
    typedef typename MembersHolder::leaf leaf;

public:
    inline are_levels_ok()
        : result(true), m_leafs_level((std::numeric_limits<size_t>::max)()), m_current_level(0)
    {}

    inline void operator()(internal_node const& n)
    {
        typedef typename rtree::elements_type<internal_node>::type elements_type;
        elements_type const& elements = rtree::elements(n);

        if (elements.empty())
        {
            result = false;
            return;
        }

        size_t current_level_backup = m_current_level;
        ++m_current_level;

        for ( typename elements_type::const_iterator it = elements.begin();
              it != elements.end() ; ++it)
        {
            rtree::apply_visitor(*this, *it->second);

            if ( result == false )
                return;
        }

        m_current_level = current_level_backup;
    }

    inline void operator()(leaf const& n)
    {
        typedef typename rtree::elements_type<leaf>::type elements_type;
        elements_type const& elements = rtree::elements(n);

        // empty leaf in non-root node
        if (0 < m_current_level && elements.empty())
        {
            result = false;
            return;
        }

        if ( m_leafs_level == (std::numeric_limits<size_t>::max)() )
        {
            m_leafs_level = m_current_level;
        }
        else if ( m_leafs_level != m_current_level )
        {
            result = false;
        }
    }

    bool result;

private:
    size_t m_leafs_level;
    size_t m_current_level;
};

} // namespace visitors

template <typename Rtree> inline
bool are_levels_ok(Rtree const& tree)
{
    typedef utilities::view<Rtree> RTV;
    RTV rtv(tree);

    visitors::are_levels_ok<
        typename RTV::members_holder
    > v;
    
    rtv.apply_visitor(v);

    return v.result;
}

}}}}}} // namespace boost::geometry::index::detail::rtree::utilities

#endif // BOOST_GEOMETRY_INDEX_DETAIL_RTREE_UTILITIES_ARE_LEVELS_OK_HPP

/* are_levels_ok.hpp
/jGyB78qD/daSOECW5ltBYDnthDmh3axb5LIOxl8gfELPEt98H3SYnHBtp01NsrZjhRvUuTrDB9Ew8aASga5WecktXJWKolXy9IGq2OjiOrEP4mC4I5ImPUkzMiVXx6eI0mZ8c6BBPl977hugZLpR4sDuRhl4CSRRTLp/sLhSmLzuFmL0cjvkUl18U9rbqcUJ26+8IqnEjsGlGpJmIDz/pc7gslZRN9PGvvoGSsr896+advRkDk0matXcNP7dsmrPXLXUkYPQiiqHRBsDj2+4tkKbbE76SaAwvHBwzG35xSN3MUFBH4GJQZzgnc2L2yTD5ACKN73QtDKBw40v5g2SzqPAT8ZfhnU6A68JQ4PVf70mHaTSwnxQlwv2bAIUuOPDpE8Q15e4jQZMltJFim0l0O/sz84RIqx0p+TFjLRKQU08ayTpPF7qQEbuJcaeKZf1YFd2GtAUhJGfc/V2ErBb5bDkAxwgJz78vQyJ8MoMtPgpMtIasJYOvE09nyIK508dpaTcJC8IZcm5pua3P7aR96c4Q/l0gt0Jg8OnCekweNrpu7CX35DVZArgU6riyX1nLqlDcnupjHKvFFqDbi8CXqg6YSi47J0HiJMKVPDy7+xBysNEQR9VO9DW2PmzSqvit4atRdbM/4dslR43N7G2ufGocPtOPZEJ2ucN6qge6+Dsq/h76GjOMyHlTYvj57nFZLX2jVz0I4NwH5B
*/