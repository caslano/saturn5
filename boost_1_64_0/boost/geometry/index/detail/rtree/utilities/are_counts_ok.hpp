// Boost.Geometry Index
//
// R-tree nodes elements numbers validating visitor implementation
//
// Copyright (c) 2011-2015 Adam Wulkiewicz, Lodz, Poland.
//
// This file was modified by Oracle on 2019.
// Modifications copyright (c) 2019 Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle
//
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_INDEX_DETAIL_RTREE_UTILITIES_ARE_COUNTS_OK_HPP
#define BOOST_GEOMETRY_INDEX_DETAIL_RTREE_UTILITIES_ARE_COUNTS_OK_HPP

#include <boost/geometry/index/detail/rtree/node/node.hpp>

namespace boost { namespace geometry { namespace index { namespace detail { namespace rtree { namespace utilities {

namespace visitors {

template <typename MembersHolder>
class are_counts_ok
    : public MembersHolder::visitor_const
{
    typedef typename MembersHolder::parameters_type parameters_type;
    
    typedef typename MembersHolder::internal_node internal_node;
    typedef typename MembersHolder::leaf leaf;

public:
    inline are_counts_ok(parameters_type const& parameters, bool check_min = true)
        : result(true)
        , m_current_level(0)
        , m_parameters(parameters)
        , m_check_min(check_min)
    {}

    inline void operator()(internal_node const& n)
    {
        typedef typename rtree::elements_type<internal_node>::type elements_type;
        elements_type const& elements = rtree::elements(n);

        // root internal node shouldn't contain 0 elements
        if ( (elements.empty() && m_check_min)
          || !check_count(elements) )
        {
            result = false;
            return;
        }

        size_t current_level_backup = m_current_level;
        ++m_current_level;

        for ( typename elements_type::const_iterator it = elements.begin();
              it != elements.end() && result == true ;
              ++it)
        {
            rtree::apply_visitor(*this, *it->second);
        }

        m_current_level = current_level_backup;
    }

    inline void operator()(leaf const& n)
    {
        typedef typename rtree::elements_type<leaf>::type elements_type;
        elements_type const& elements = rtree::elements(n);

        // empty leaf in non-root node
        if ( (m_current_level > 0 && elements.empty() && m_check_min)
          || !check_count(elements) )
        {
            result = false;
        }
    }

    bool result;

private:
    template <typename Elements>
    bool check_count(Elements const& elements)
    {
        // root may contain count < min but should never contain count > max
        return elements.size() <= m_parameters.get_max_elements()
            && ( elements.size() >= m_parameters.get_min_elements()
              || m_current_level == 0 || !m_check_min );
    }

    size_t m_current_level;
    parameters_type const& m_parameters;
    bool m_check_min;
};

} // namespace visitors

template <typename Rtree> inline
bool are_counts_ok(Rtree const& tree, bool check_min = true)
{
    typedef utilities::view<Rtree> RTV;
    RTV rtv(tree);

    visitors::are_counts_ok<
        typename RTV::members_holder
    > v(tree.parameters(), check_min);
    
    rtv.apply_visitor(v);

    return v.result;
}

}}}}}} // namespace boost::geometry::index::detail::rtree::utilities

#endif // BOOST_GEOMETRY_INDEX_DETAIL_RTREE_UTILITIES_ARE_COUNTS_OK_HPP

/* are_counts_ok.hpp
q+OxsDtsDpNhSzneHfaCKTAF9pHjI2BzOAG2hHmwDSyH7eBS2B4uE/3fwI7wIXF/abYHma9BG5bnz65mf6DtcSbCK2ASXArPh8vhNLgS5sJrYRFcBUvgdXANvB7eDl+S/ubXcBtcA1+EN8KP4V74BXxRrv/fwh9gNYwX+5nd4HqYDu+COfBuOA8+AK+DW2A1fBhuhI/AzXAbfBQ+Bl+BT8A34A54ED4JPxF3jbi/hrug8Xz4FGwFn4bt4DNwONwNR8Ln4UVwL7wYvghz4Uu6H5F5CTDDph/pJuNUdxlPe8IRsJd+n8APCT9ehbe+T6DO9HV0SPTcNtdRN/kekgzVunzoC+coDB2ul4TrLeFSoM6XhGtlk6+OEq4TTICdYTNxF9dznNamZ/552NxDtiFJuGcucgTa6dQ2OisXBdvpXM2xrYidvc4DHK9BAu12pl5hb7sz6wqr/c4mo9AT+50b8duNHEOqTHue6uY2FtnK7w4wlF3P4iuttj1XX2m177kV917kGBKzmDwjGUigzc/CxYF2Pzm+uNb252HKMND+5/7FVhugJ3EnLbHaAh24BCJ2NkELOX4CroKBtkE3LTm9fdCTpGn3Ens7occ4vh8mXUUaEA9yArcXhrIduu6qWvuh266qtSG6/6paO6In+d1kqdWeaAfc/jZF03Hb2xUNsCmKXjXib1u0SQfsMnLMZ2N079JgO6PHOeaFUVW19kaT+L0HpsMaaNgcDQ+wO1pcVTfbox2QVLE9uqGK8yOxy6x2SAfi9tkizVkWbI90BUyH65ednV3SXcuCbJPa2iU9tKzutknDl/vsk6KzvNZGadZy9JAO/F4H7eyVbl9+9jZLM68m3bACLoabob/90n24jyE+O6YxK2ptmaasCLZnmrmi1qZpMb9P8nst3IYkXkJ7hf42To/jbrLStHW6u5TZ+SuDbZ7O5NhBWAX9bZ9W406HybTLQBuom/HbAz34VSAbkJeR40hSR/oLpAJZj+xDTiBJdN4DkUykAqlGtiMHEUdn/JF0JB9ZhWxC9iFfIU26YBcVGY8UI6uQjchu5DAS1TXMkYx4kEpkA7IHOYScRBIZwNKQfGQVshnZj5xAEhnMUpEcZAWyGTmA1CAxyedsoZ77O7u//7b9v9zykt6/lP2/cW76I27KwhyGSYIpo6ZMGTNpYvbwKRN7s17i8uwKnt2UnT7mz9XurewMtms3yYinr5r3GBQRc2hDrm3Sez2Tlmzi8PBwxZVeytoMwlnnrp5w2tsJcKRy3jraCUD3lHYCwlJ/rp0Ac079y+Gmdj8Xz1bCOeQvxUxrfp+ibL9yMuerFrgt80NFt7+2HzVbuX8KuwFtI/1dVf68Xj2XXofpqfd/uky5I1230Srj9Ro28jynQu9lXqjDjVbxDovV69f1vP7Llf9XYQvFXl0XpePV+2nlKf8wlxG+yK2+bJY7/OfmK//jYctkvWu8rIuTNCj30n5qPqxf3VTM9xbTNqRuHlL+Ayjnto4e/NvCsGWhvtVQB8ouSoeYiPiYsMiYqHDfvFmPb38g0d3k4jyxar+5B43jneR4OPU1GV3Xsl9Fd4xuHz2iXnhMeEy0YbzNFSXtaa/Znsp4D6RtyNyr0vS003Szo5/K5zB1zv6kIQbdi2Te+xSYiRjnmSqcFiBT6jgv/plU6x45Ho4XuNW8X70+hPaB22wfbo7l6LWCfvUvul1MXTV//n2VJ959NrHubfxyRLDtw2LOmTbQrk2ra1+1lbnWdi36rf3acFGJbsMB/rq96rZa66/r+NRzo8f6z42e61dGA3UZqfOrY2n+ZRRwTRc34h/1jdUsg2PwSuLzmvkv6pNvuab1taTzJ9fSTUo=
*/