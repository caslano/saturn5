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
cHh47a8boTsXnnsrqEmsUMbIN8CKzu8IGA/dI3F5gIlP/K3qxKdjZdB1/TDgS3EBvDuuJDbkwJ/lfme2Zdbp8AhbrzS7hQMGZ9x5emUeg6/LQBvBlO3+Fy9fZ+DCxfNDHENwpobp3s0ACkdYOVT2VWTl00qS17ORwMjMjoovf6w63DoR/qHhLG/Jf7F5oL5QeAf/qx3GvgP1804ZQHVco5cHiv3PksGFCUcNE+f/lQyU//0NQMzIxYzVw8oOrKlnqyr5MVfvM0svCwCRBgAMlmTcsIeTfuwAd8sRrrO6b+CGyHNdKEyEbQlOQLX8Y+qxn0o46MOl20WI5DGidoHhV7vAqC5LbksxJFScfXTrGKXy480McIscuh1C7Hg7v8/xdDbXcRaXhf+0/ovzc8rjdDXpJ8mmpEnaVhBBIjLeGWK0XwUVFXWvQ3xs7GEliGKuNxr2DmugK6XCizmIb9or40X/L4hkxVskzGdR/J0QVoEEA30Xi3Oh55e2L9X0n/ZtKB6DVfDl3l5+NfALKLWY7z+mSQOeBNgpAQQTHbiJVKxjfYO+GxyiHO8imXtHqN8nT3Wu7nwPDtoN9bOgT897r0+afLgct6Bt1tRh5/dqBM70191Z51hIkNNGfpAzt4LLio08Li3HrbgX0yzZxTY2ZZV+opOZzStGG/zhmouYC7APWInTAU+t8/tNPyDh7VvRC2T9Nb3RBtUD3TW5
*/