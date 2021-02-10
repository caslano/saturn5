// Boost.Geometry Index
//
// Rtree utilities view
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

#ifndef BOOST_GEOMETRY_INDEX_DETAIL_RTREE_UTILITIES_VIEW_HPP
#define BOOST_GEOMETRY_INDEX_DETAIL_RTREE_UTILITIES_VIEW_HPP

namespace boost { namespace geometry { namespace index {

namespace detail { namespace rtree { namespace utilities {

template <typename Rtree>
class view
{
public:
    typedef typename Rtree::members_holder members_holder;

    typedef typename Rtree::size_type size_type;

    typedef typename Rtree::translator_type translator_type;
    typedef typename Rtree::value_type value_type;
    typedef typename Rtree::options_type options_type;
    typedef typename Rtree::box_type box_type;
    typedef typename Rtree::allocators_type allocators_type;    

    view(Rtree const& rt) : m_rtree(rt) {}

    template <typename Visitor>
    void apply_visitor(Visitor & vis) const
    {
        m_rtree.apply_visitor(vis);
    }

    // This will most certainly be removed in the future
    translator_type translator() const
    {
        return m_rtree.translator();
    }

    // This will probably be removed in the future
    size_type depth() const
    {
        return m_rtree.depth();
    }

private:
    view(view const&);
    view & operator=(view const&);

    Rtree const& m_rtree;
};

}}} // namespace detail::rtree::utilities

}}} // namespace boost::geometry::index

#endif // BOOST_GEOMETRY_INDEX_DETAIL_RTREE_UTILITIES_VIEW_HPP

/* view.hpp
q1qIlqJA0iiLJxgUj5GlBu2iinfCLneQluoPWbu60korq0SK79iUE6kXO2dtru01bs171xcGZW9ARrsyWOW0fNdnd6C2u9b60ONcnLRS63WYJMFc+o3c/Fy3N//e3AHPvcK1/a2VzKskkUV/19zQQVFVWpORZy7vXedu+mt8u4s69E2GZU8s5Kmp9E7OnagaeOqyv/cn56PZ5PL059nF9PXl7GSC33u4XygxDWH/nSwOcFsgehK800khoEyxP4RD2jxYz7QraD9N31Mle5oXYpEJjEiEKnHPR3p/830Q2ltj9wTzFl0nerdGO9G6pdaGOx4gIPtvDYcGv28Q7ftUasRoe3tUF8gtA3gjEQhgQceUGTFWqQr0TpYRBEspJQCmRAucS0roYcknHMU/wVVrF2oDqjyJKTJobMUeKhnMCb1GYKoXINNShvgB4dpc4jSJHzROgNSxw0ERRRJRZiTStKTwIrQ5gouEGJQVDkrMvivCwRYhIBY4ffCHLAxLJC09znH8JuhgxCkrhQAolQSfqxKqfAiGsNpKOb0SBMUkmsKB+SwQxsdVljN2A1cx2zp2DPxVWHklSzRdJPFt76EMvfXs1/DoQItMvgKHXBCjM1+y4P7XsGE9rtUCEVtVSNoJuCOT3pNG1z7DDoDL
*/