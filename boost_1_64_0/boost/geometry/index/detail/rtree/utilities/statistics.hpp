// Boost.Geometry Index
//
// R-tree visitor collecting basic statistics
//
// Copyright (c) 2011-2013 Adam Wulkiewicz, Lodz, Poland.
// Copyright (c) 2013 Mateusz Loskot, London, UK.
//
// This file was modified by Oracle on 2019.
// Modifications copyright (c) 2019 Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle
//
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_INDEX_DETAIL_RTREE_UTILITIES_STATISTICS_HPP
#define BOOST_GEOMETRY_INDEX_DETAIL_RTREE_UTILITIES_STATISTICS_HPP

#include <algorithm>
#include <boost/tuple/tuple.hpp>

namespace boost { namespace geometry { namespace index { namespace detail { namespace rtree { namespace utilities {

namespace visitors {

template <typename MembersHolder>
struct statistics
    : public MembersHolder::visitor_const
{
    typedef typename MembersHolder::internal_node internal_node;
    typedef typename MembersHolder::leaf leaf;

    inline statistics()
        : level(0)
        , levels(1) // count root
        , nodes(0)
        , leaves(0)
        , values(0)
        , values_min(0)
        , values_max(0)
    {}

    inline void operator()(internal_node const& n)
    {
        typedef typename rtree::elements_type<internal_node>::type elements_type;
        elements_type const& elements = rtree::elements(n);
        
        ++nodes; // count node

        size_t const level_backup = level;
        ++level;

        levels += level++ > levels ? 1 : 0; // count level (root already counted)
                
        for (typename elements_type::const_iterator it = elements.begin();
            it != elements.end(); ++it)
        {
            rtree::apply_visitor(*this, *it->second);
        }
        
        level = level_backup;
    }

    inline void operator()(leaf const& n)
    {   
        typedef typename rtree::elements_type<leaf>::type elements_type;
        elements_type const& elements = rtree::elements(n);

        ++leaves; // count leaves
        
        std::size_t const v = elements.size();
        // count values spread per node and total
        values_min = (std::min)(values_min == 0 ? v : values_min, v);
        values_max = (std::max)(values_max, v);
        values += v;
    }
    
    std::size_t level;
    std::size_t levels;
    std::size_t nodes;
    std::size_t leaves;
    std::size_t values;
    std::size_t values_min;
    std::size_t values_max;
};

} // namespace visitors

template <typename Rtree> inline
boost::tuple<std::size_t, std::size_t, std::size_t, std::size_t, std::size_t, std::size_t>
statistics(Rtree const& tree)
{
    typedef utilities::view<Rtree> RTV;
    RTV rtv(tree);

    visitors::statistics<
        typename RTV::members_holder
    > stats_v;

    rtv.apply_visitor(stats_v);
    
    return boost::make_tuple(stats_v.levels, stats_v.nodes, stats_v.leaves, stats_v.values, stats_v.values_min, stats_v.values_max);
}

}}}}}} // namespace boost::geometry::index::detail::rtree::utilities

#endif // BOOST_GEOMETRY_INDEX_DETAIL_RTREE_UTILITIES_STATISTICS_HPP

/* statistics.hpp
qmsnBuTNdPz49xb6SvlhVyH+S5FvV0naX/3g6+X4rpcMn1V+x/KeqY7cW9pfUJ4WKfsGaC8rP6dbunbvNsy9B9pz/xcnsC6GiCW4JiS4oxPcV+UnxHKP6W8BjIEQOfNX/NySQDpMP/FzFyS46hrBZwN7xN0m3B013dW+qlCPA4Pc7PWFVeuqnyKEgwFurHA2BrvxokfJgmIH4kRc1drbiH2KgtqSQj32VPetMivRZupetZ29ny379IyTPa5HwmnJmEcHtCU8WYW0IVJ3S5W7QQ5pU8SfR53RXEGajyFfm+lu1CDkXOUu6PFyDuwywn1fGOWx5GPRTXF7TNb8e05gWvMbWA5bxNJ2CueQ1sRYnVbpImxp1evXeyl3e6LfdtY3LoxKl3bU57+tuKNnjFffFd0x3NNzHXOdEfoU8dcycO8m1cF5Zb+sTsr+/egDXC8jaqx86/L5S5WztP3X89AK+vvkEjMsvR9aD+Xn7egjTof1bVeH01r2SiKcuioch8RXt9095LvbGcr97uhu3HuDaC8mwmJkASth1vPdL9U5x9jsZM9IZyO+GRWSDvzhY7PyVxrT1OjqLHT+Q8VxuNWGF+UXkh/S/3ys3N0l/RFn8at0pXAFp78tkrP3vdZeahL2Jc6mnGIwzXFIufuivlrpUjp9Ronud/bFqfXJovvi5NXr5mMN354A/WnLrL8FtXAje8Etse/XpMvenSB9i9I58V+FO8oZY/RW5V5m+SspCvDTRvlpGtFParTyUzylrFzvnVai/FAHdJnLfSbxF/ckwp+fs5Sf4Zau/fDeQ6d5ij5rfalym27p2m2Cyg+v5EcHFc9zjDRl5lBm5crsyZg4p9tY74wzzmVDltXRLnl3octLv7t4wJ92dN91rqEvnu3w+8nTfurBtfjBJaWFrv086rDur1Ottf5J1n5ckwPy+fI6uEOLlM9n6f2o/OOTT5SfNEvXfpyqr8mnrWyVLPsBuOddGB9nbnUTyz9RCSHvciS8ybVUesO+y/HCOcrezTgGXd8rOdTnWxxP0bc3dFr7NS2jrWwlcwOiPRZjoEv9ljZTfsfCOKSWtJmMuxXj0ROQ2kgdpC6SiCQhHnGfjNRD6iPeADZAUpCGIs8RZqNq9VEJ1vOoalu0Lm0N12V/vg/MPCdrz7sgvYshZsu0Wc+ePrPz/GbdfWan+826+czq+826+sxcfjN9jQ9qa7NOPrPLtFkPHV6W30yHd7bfTId3mt+ss88syW+mr+HQZt17+cw+StBm6T6z5/1mOg/G+c30dQ/G+8y69fCZ7fKb6bx6ym+m07Hab6bjd6U266rjMsZvpuMywG+mr3uG30xft4vfTOdpW7+Zjovbb6bT9n0tbabz9KjfTMf5U23WRedpB7+ZDu+5OJ9ZZ522P/nNdNoW+c102tbHajMd3h1+Mx2/xX4zFb86mJVrs15Kz9V6eshcKdmT0v5MaN+TUvp2xnv62Vj6e5tf2l7fey8ZAyU05B/rDBfNVbRpGR7io8dAFcHPzKr9aqDee2Gr21jxRygRxjhi74r03Kz9H/+5WdqNZHs7UuXxtyP7PKFlscMTWhabPPayWKv1dKUv13pPpV+r9R5Kn6P17kov1no3/c6dvCL/VV7V6BnfNx+rsoWV+J4Eliycm4x5sq2cpHhCy+cRGbPuUO4bx2YS9kvIV0hLB/UBuRbZjryL/BNp7Yw2ypHNyE7kY+RHJIUK1gWpFRVt9EImIpcjNyOP0N+/ivwTqe2uZZyOXIBcglyBrEY2I/HR0cZFyELkjuhaxoPIC8ge5J9IrZhaUqd8aWwS8i5mkqpTYk+OjDBSOevsDkasbRg9TDeaOdsZua5vjM1RDY0=
*/