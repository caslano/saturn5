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
95BYd12jFTIIKUCucHt4rk4yHuX3buSoe4xxbXQz4tLa2IPExtQ1WiAeeS6tX8+8zqvu2sbj7uAx+kXWWFzHJRtfxIW5LZC4dGXMPt31mfFMlNfYj7i5dgukP5KLXMX1/wRfQ8x43BDd0NgQnWq8i1hzA33Xf0Oubx/XPyRjvBfU9ZvFjuXffFbtn4a/QchNyN+Rj5BvkI6M+y9HtiN7kM+RaBdPEUhvxMMzdj9kErIAWYn8NcptvIV8g9R3u42eyBikFFmI3INsRz53n2Lk8ty3BLk32m1sRF5B9iHfIJ4Yt/XMofOroR6TbmqIzqyYoGcC/U6qg8qD25nX4wjjx/5M0JqmYjC08u158u05Yx/7/y1wjOAs8Tcc211pxleubY7gZwSPjNXa1Tf99eZs7tpqvJdIW9mkqW+8N//R+IT4U4+3j2d+AzOMHqLzRkrpTSN+y7tc2bv1eLhE6fWNBMzU/lASjwW+eETNXxjfk02XO5gxiQuOh5572keFs5Z6OjDstT3wLOWmkfWeQq6zjut8k2Sm9+rPA74J2NzswM13ppu6Czvod9dBbqpw863pJnnh5cHP/UvQ0wLGsjFI0wjjWKjHsvzW41l+IzJmrcZ4dUWE8W9SDcawhY3tfc++Rv6+Z3uj0DHdQ41Cx3TxfjM9rpjvN9NjobF+M92Xtfeb6XHPtw1136PHLrf6zXR4ZX4zPXYZ5TfT18hoGDoebKXNuuq0uRuGjhE/SAkdI25PCR0jrksJHSMuSgkdIxakhI4RL0gJHSN2SgkdI8anhI4Roxro8aC+7idebaavu9Nvpq/7mDd0LPkHv5m+7o1+M33dyvp6DKKve5vfTF83sX7oWOXLemImY5XntZ6u9Kpk+9gjI8zYY3CYsUdmmLHk2DBjycGhY0n9HSIxTc8bUH9u5MZka1Cp5+MXTMqZUVyeZW6wxs6Vx/0+Evi+LrGlZTHLQZqE05Ix94cv32XDv5vsotyNkneTPn9pum1e2Byd/8x3wvVIyzpEvauMKU6gTfm595XSTtneW9reVzb3YP4L5p8HjgFXSfp9/psjN5D+qub+9E8uKNcfeWpJO8+3BHm/L27Vfuh1j5v38m1K1mjMsD03rGrl38OxNtIbmZ9M3FLDxSUr9zJzGYbEqY317VPy3eenjbK7xFqDovc/l77Kdt5BMuyv/HjQ9bu4EmUvffdFyt6tyyxN2vWK46R3buB+/rKP5SXW/WNLf3prmQdM4CnQBVuY+9kHpb+Ug0DyCkqp8JeVFIT/7iZ+TjO88m52pdJ3G1243jyklvUOUOfZUO2nld5z9RalHyJ+jLuQoHe28q6M+1G5+5j5wvHGNYiVv/q7lR4L9GlhumuLfraqjyuUv4+C3BfJOIX7RNmfT17U02OXcyWMGNLgK4dW1djPMegeUHq63mO0hPCx1/VSxdvWDu2UsmkodZNg1LqgKoe/bFgTlM9MsaKCrFmlU8oLwpWLuG+o497aU/Pv1Wa8Okq8tp5qOZwo55uOlXjtbOGPFxMwwq6l2a/cDOU7mUPHD3/6HvjBenfZNfAe+EbZ1xOdN/tppu7U38GW4+fUapWHO8ny6z8zo1PQOqMUy97YUM/+3JraJrRPWMwNnIl7neYZU30T6I7bJgX2ByltLYtGUs5JyKWEnR0QdklBQVGEeQvirlHAvIXcGZP0vAW7fXmYszTEXtePdr+gftjnM6jrB60vUte0tT2J7eQcSgm4DbKQdM8NTPeMsG2vzGvLkzzw+YnVfeDdSg/b5ojbtoFnTuj2YpGyayy6Due45Sl9jMyFy5O5fvpet5V37GlB97WU9xZ/umlvc/IjlLe4axixvMU+YnmL/b+tvH0=
*/