// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.

// This file was modified by Oracle on 2018.
// Modifications copyright (c) 2018 Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_CHECK_ENRICH_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_CHECK_ENRICH_HPP

#ifdef BOOST_GEOMETRY_DEBUG_ENRICH
#include <iostream>
#endif // BOOST_GEOMETRY_DEBUG_ENRICH

#include <cstddef>
#include <vector>

#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/value_type.hpp>

#include <boost/geometry/algorithms/detail/overlay/overlay_type.hpp>


namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace overlay
{


template<typename Turn>
struct meta_turn
{
    int index;
    Turn const* turn;
    bool handled[2];

    inline meta_turn(int i, Turn const& t)
        : index(i), turn(&t)
    {
        handled[0] = false;
        handled[1] = false;
    }
};


template <typename MetaTurn>
inline void display(MetaTurn const& meta_turn, const char* reason = "")
{
#ifdef BOOST_GEOMETRY_DEBUG_ENRICH
    std::cout << meta_turn.index
        << "\tMethods: " << method_char(meta_turn.turn->method)
        << " operations: "  << operation_char(meta_turn.turn->operations[0].operation)
                << operation_char(meta_turn.turn->operations[1].operation)
        << " travels to " << meta_turn.turn->operations[0].enriched.travels_to_ip_index
        << " and " << meta_turn.turn->operations[1].enriched.travels_to_ip_index
        //<< " -> " << op_index
        << " " << reason
        << std::endl;
#endif
}


template <typename MetaTurns, typename MetaTurn>
inline void check_detailed(MetaTurns& meta_turns, MetaTurn const& meta_turn,
            int op_index, int cycle, int start, operation_type for_operation,
            bool& error)
{
    display(meta_turn);
    int const ip_index = meta_turn.turn->operations[op_index].enriched.travels_to_ip_index;
    if (ip_index >= 0)
    {
        bool found = false;

        if (ip_index == start)
        {
            display(meta_turns[ip_index], " FINISH");
            return;
        }

        // check on continuing, or on same-operation-on-same-geometry
        if (! meta_turns[ip_index].handled[op_index]
            && (meta_turns[ip_index].turn->operations[op_index].operation == operation_continue
                || meta_turns[ip_index].turn->operations[op_index].operation == for_operation)
            )
        {
            meta_turns[ip_index].handled[op_index] = true;
            check_detailed(meta_turns, meta_turns[ip_index], op_index, cycle, start, for_operation, error);
            found = true;
        }
        // check on other geometry
        if (! found)
        {
            int const other_index = 1 - op_index;
            if (! meta_turns[ip_index].handled[other_index]
                && meta_turns[ip_index].turn->operations[other_index].operation == for_operation)
            {
                meta_turns[ip_index].handled[other_index] = true;
                check_detailed(meta_turns, meta_turns[ip_index], other_index, cycle, start, for_operation, error);
                found = true;
            }
        }

        if (! found)
        {
            display(meta_turns[ip_index], " STOP");
            error = true;
#ifndef BOOST_GEOMETRY_DEBUG_ENRICH
            //std::cout << " STOP";
#endif
        }
    }
}


template <typename TurnPoints>
inline bool check_graph(TurnPoints& turn_points, operation_type for_operation)
{
    typedef typename boost::range_value<TurnPoints>::type turn_point_type;

    bool error = false;
    int index = 0;

    std::vector<meta_turn<turn_point_type> > meta_turns;
    for (typename boost::range_iterator<TurnPoints const>::type
            it = boost::begin(turn_points);
         it != boost::end(turn_points);
         ++it, ++index)
    {
        meta_turns.push_back(meta_turn<turn_point_type>(index, *it));
    }

    int cycle = 0;
    for (typename boost::range_iterator<std::vector<meta_turn<turn_point_type> > > ::type
            it = boost::begin(meta_turns);
         it != boost::end(meta_turns);
         ++it)
    {
        if (! (it->turn->blocked() || it->turn->discarded))
        {
            for (int i = 0 ; i < 2; i++)
            {
                if (! it->handled[i]
                    && it->turn->operations[i].operation == for_operation)
                {
#ifdef BOOST_GEOMETRY_DEBUG_ENRICH
                    std::cout << "CYCLE " << cycle << std::endl;
#endif
                    it->handled[i] = true;
                    check_detailed(meta_turns, *it, i, cycle++, it->index, for_operation, error);
#ifdef BOOST_GEOMETRY_DEBUG_ENRICH
                    std::cout <<" END CYCLE " << it->index << std::endl;
#endif
                }
            }
        }
    }
    return error;
}



}} // namespace detail::overlay
#endif //DOXYGEN_NO_DETAIL



}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_CHECK_ENRICH_HPP

/* check_enrich.hpp
cyebl/8E29rJmkdL8vX79+xfpcHs+jS29Fn1nEIRcnaxTDl5iHH9XCw8rh99eIhtulU+Lkc9yAZ8lM4857N/EctU/kFMdQf9OMJ/qJt/ulLsnTvSXgp+KBNZ5HC9Pm0ugxpsjjHIxWd+oe+LxXBFxe/Xm4djk+whMA9KvCKvv46ORFpbbMgOksvxTeRKjxoZ5xUBO2qvTx6yjyfbbHQ9/8xAHZm9Wi4OlXPuNY9SyTd61zI22nUrGbYrpM2OjVou/r+J791ofh8QA4Zj9o3esY1NKWh+mvdz+Ljm1lzzVGRfC4t9ZtC5NWI/cfSafPozmn/43nFzc10xOrGKvpFH42esu+xkb7Oay+p0G8SYVauy32vFMlWtaeSXz9D7LOxghHpnYc+aR89a2/Mx+kXfWSmvvlCNfToklhSP+C6tNXq1MfM1ZiF73pwfpKdVJsnjU7HZ3+uT2tumt/lZ8XmDX7zb2B7rzz/SmX1/4M8fFWs5tjpWjD9N7mKOjPHcac+yIeH1A/byPmOfw5hVq2ge0q2XerDtbPxmNbT+m+X32fnzptYGzZNX/L5pHR/YQQzs2e82YEvI5dl22nSAnRc71txsPtagf6/T1zjy0o7G2lApm/iYL51YmR+tYbzHeO/71gDe1ybB1rbC9GwumxcvT7Mm/EC4HhWubZQUO2ViY8jxj2zIWTFKe/YhOEMP5H4h8U3lo+bgWfX4vWxTkvrZLrn4ZDHgbHZsujh1llhQ7nDiOfVIazXPPyOfEGtPoXcD79DO5da3eovVhvJJFcQBfG92MaDrrRHJRU5Fil3tBcgvr+Bvuz8iTiWnH3qpCXp2tSFyKfO8qXd99Ro7aL9o70b6F6mOvosfjhcPihcnfRb43rnvRsm3YuayAfXEZXki1S/Uz9qZe5+xxeLyqTUCMTxfuYWc2feEH+wB2ScmeNycUd/JF8glu4vNvSt/SGw7xFrJRPaAPtyxTYwujhoRKZddqi7CFpWeqm5IPln6i4e2sOWrxOFTQr47xI6JjytmEXtZGzxSiVwOmtvD+XprmxXYv3T0NZ5tHFRMLqSdu/UpNJCu81MvsCnp6WyjBj6T5Sl36oO5+oM6JPsdjHxdHCo+jxD3HK1irrALaQ6ak/z1/XTkW2u888XDd8635nIjfZdfFpwljvf+J1bwVdrQR+w04SG+X9yaNRN5zZTnsRvRctBdeel7d+tnf9CvZLE1eXZe45i+TGxrrxq9nz6ePKqpu4sXtx4VS9PDVrXYjlPqI73ZUXOwzkq2Rgy5IoZu0aVRaqP96un/F5GO8cH3spMTtZ8capaTZ41ls6pQwYfVKNmd5DTs6QBxzFQxuHn9wQK+idyW7NYec2I5m7ezklolXzK1qDb90ZqVz8mIf1ofX+Z3HuEfrK9Nd+zJyWwx+e3j694hw4TbxZnP+WzJdxZkP8nk7AY+/H1zhmzznTEGIbl1Z+3yvAnTjbW17IxznFsvrjvCVnWSM4fkhdPZkz3ybHIrt4A9eYFc+onH6VrFY+JrsX7G6eF9VerSajT1E/WP73rP+49az3yskTxGfXq1uIq+BCXC+2iXqXsOEuv2NU7sbfMIdVe1qVfJrnhp9m8y/zlbTGNfzMtPGce7zFXt2U9nHxQ/DmkiBtpJzubcmGg5qTmTydpfch73WgfJwjd1MKcL30/HS5ibfdhXPnfSw3wN+zRQTv6JPOimh/la8juALMXYcDTLbH41lVdVDPxNfDF3bvkLef7xOXrAtqThd5mUoHl4jegx+5lGitXaGpfO1gHCNvmzCOvV5vkL8pEv9Teztp2hf54dg3Z/dlyfnh4qF6c7FUeIgdaQz810gy1/Tf1m/DnH6ca94p0=
*/