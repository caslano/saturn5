// Boost.Geometry Index
//
// R-tree count visitor implementation
//
// Copyright (c) 2011-2014 Adam Wulkiewicz, Lodz, Poland.
//
// This file was modified by Oracle on 2019.
// Modifications copyright (c) 2019 Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle
//
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_INDEX_DETAIL_RTREE_VISITORS_COUNT_HPP
#define BOOST_GEOMETRY_INDEX_DETAIL_RTREE_VISITORS_COUNT_HPP

namespace boost { namespace geometry { namespace index {

namespace detail { namespace rtree { namespace visitors {

template <typename Indexable, typename Value>
struct count_helper
{
    template <typename Translator>
    static inline typename Translator::result_type indexable(Indexable const& i, Translator const&)
    {
        return i;
    }
    template <typename Translator, typename Strategy>
    static inline bool equals(Indexable const& i, Value const& v, Translator const& tr, Strategy const& s)
    {
        return index::detail::equals<Indexable>::apply(i, tr(v), s);
    }
};

template <typename Value>
struct count_helper<Value, Value>
{
    template <typename Translator>
    static inline typename Translator::result_type indexable(Value const& v, Translator const& tr)
    {
        return tr(v);
    }
    template <typename Translator, typename Strategy>
    static inline bool equals(Value const& v1, Value const& v2, Translator const& tr, Strategy const& s)
    {
        return tr.equals(v1, v2, s);
    }
};

template <typename ValueOrIndexable, typename MembersHolder>
struct count
    : public MembersHolder::visitor_const
{
    typedef typename MembersHolder::value_type value_type;
    typedef typename MembersHolder::parameters_type parameters_type;
    typedef typename MembersHolder::translator_type translator_type;

    typedef typename MembersHolder::node node;
    typedef typename MembersHolder::internal_node internal_node;
    typedef typename MembersHolder::leaf leaf;

    typedef count_helper<ValueOrIndexable, value_type> count_help;

    inline count(ValueOrIndexable const& vori, parameters_type const& parameters, translator_type const& t)
        : value_or_indexable(vori), m_parameters(parameters), tr(t), found_count(0)
    {}

    inline void operator()(internal_node const& n)
    {
        typedef typename rtree::elements_type<internal_node>::type elements_type;
        elements_type const& elements = rtree::elements(n);

        // traverse nodes meeting predicates
        for (typename elements_type::const_iterator it = elements.begin();
             it != elements.end(); ++it)
        {
            if ( index::detail::covered_by_bounds(count_help::indexable(value_or_indexable, tr),
                                                  it->first,
                                                  index::detail::get_strategy(m_parameters)) )
            {
                rtree::apply_visitor(*this, *it->second);
            }
        }
    }

    inline void operator()(leaf const& n)
    {
        typedef typename rtree::elements_type<leaf>::type elements_type;
        elements_type const& elements = rtree::elements(n);

        // get all values meeting predicates
        for (typename elements_type::const_iterator it = elements.begin();
             it != elements.end(); ++it)
        {
            // if value meets predicates
            if ( count_help::equals(value_or_indexable, *it, tr,
                                    index::detail::get_strategy(m_parameters)) )
            {
                ++found_count;
            }
        }
    }

    ValueOrIndexable const& value_or_indexable;
    parameters_type const& m_parameters;
    translator_type const& tr;
    typename MembersHolder::size_type found_count;
};

}}} // namespace detail::rtree::visitors

}}} // namespace boost::geometry::index

#endif // BOOST_GEOMETRY_INDEX_DETAIL_RTREE_VISITORS_COUNT_HPP

/* count.hpp
5nling8fh0ViPkvMK+BmeKWYXyfmi+FWeLOY3ynma+BL8I9ivl7MH4R/hw+LfgRWRck6Bn73lHZ4Jb8PSDv8MPmk1qnADPhnOBD+BWbDJ2ABXEl4k+EdsBT+FfM58HE4T9xdC5+EN8DNcAN8Gr4On4HvwGfhfgnnH3Ab+g/wORhrvqOEtaFpnwJfRk+H5vV7i/lA+CrmmfA1OFrMs+HbZnzhXjgVvgNL4XtwNtwHr4Tvwzsl3LvE/3p4wKxv8EO4BX4M3xX7Q/AwehVcjf6lmBtOxtpmvYfHYCw0zZPhN+gN4bfwDGher4/YD4Y/YH4+/BEOhx6z/MV+GYyFq8V8t5i/D73wY9GPwIbwG7ga/ijmcS7aG5gIm8H60DRPhS3gqfBG2A6a/k4X+97wFNhP7AeI/RCxHwVPg+WwPZwDO8CF8HT4FuwKf4LdYPMoK90toOm/PewELxDzTDG/GPaCufAMWAJXwxliPxf2hdeI+c1ifgfsD+8R8/vFfCMcAl8Q/TXR98AL4CEx/0L0Y3AkjHVb5h5o6g3gGNhKzDuK3hWOg4PEPFP00XA8LBDz6aKXwyx4lZhfJ/pSmAtvFfM7RV8LC+CjYv6U6M/CQrhbzPeJ/iEshp/DqdB8cJsGU+FKmAZN9x1gKcyAZXAwLIfnwsvgxfBGWAxXw0vF3+VwLrwBXgVXiP1qsV8HF8KNom8WfavoL8NF8DW4GO4T809E/1z0b+AS+CO8FcbGSHlAU28AV8AWYn6a6J1El+dOmdtP3x3mufM5ee58CbrhDnnu3IQkir9Z0l/U4/d68fej+PsJtoHOePITumEGjJZxbAwsgLGwGMbDMtGvEP1GmAD/BGvDPbAOPAbrQjMSiTAVJsEMWA8Ohl44CTaAl8IUaD2/yzx6mBrmDOhdEv/XYSzcDZvAN2FTuAc2t3R53pQ58PCskOdN3JHfag9AmAj3wd5wP/TtVV0i/uuo/LTvVT3NfO6CZbAnLIeD4Aw4Eq6FebACzoSz4TVwDrwRXgFvhVfC2+E8eLf42wCvgZvhtXArvB6+AG+Cr8Kb4VtwGXwPLocfwzvg5/BOeBSugd9LuJIvMgebtjdMvnxcy8qXgzARHoL1lC5nHxsyRxpOFP+x8Dzx/xnuPPBz2BEehf3g13AoPAYz4XdwDPwWjhVd6j/zmCPX/79LPdgp9f+VgPLOFn+NwqSrfl0rXV6ozqKF9UU3/Rcic8V/W/FfC44X/x/KeOsgdMNDMBZ+Ar3wU5gCq2BD+BlsDP8BW8LPYRuxl/gy9zVyOSRKfJNgIvTAeqKb/hch+8T/YfFfB14u/o/Usa77JewMv4KqHOAQeAxmwm/gZfB7uARGEf5t0A03wlj4NEyA22AtuFv0N2FtaNULmfsIW4epF41wZ7IxjIHNYDJsLuXQEnphC5gK0+AplrneYz1Dwn9YhW/fY7017urCtrA1bA8vhF1gFuwKZ8BucB7sDm+AveAtsDe8XfS7RP+j6PdZurRTMp8Q9gnTTu2V+vmOtFPvSbu0D3aAH0DT7QGptxWGzKmDGyW8BFgs4f2RcmkB18He8D44EN4Ph8H1cCx8EF4EH4WXwIfgQvgwvA7+Cd4GH4FrxN0R+DxizX0j7nJ9L3xCrv8X3NWFT8G28FmpT1thN7hN4vMiHA1fkvh8BCfCHXAafBlWwL/DOfB1eKW4uxq+Aa+Fb8N74V64Hr4Pn4Efwq3i/kW4Gb4Ct8DdYn4EZhoy5wxOkvTEwAGSnkO4awY/kfR8CnvBz+T+OCzt9+cwV/QjcAtSKeH2k/6gvpmPEu5+qb8HYCP4IWwDD8Le8FM4BH4u9e8LuAoelfr2tdxv38K/wu/hTvgjfFU=
*/