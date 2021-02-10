// Boost.Geometry Index
//
// R-tree scoped deallocator
//
// Copyright (c) 2011-2018 Adam Wulkiewicz, Lodz, Poland.
//
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_INDEX_DETAIL_RTREE_NODE_SCOPED_DEALLOCATOR_HPP
#define BOOST_GEOMETRY_INDEX_DETAIL_RTREE_NODE_SCOPED_DEALLOCATOR_HPP

namespace boost { namespace geometry { namespace index {

namespace detail { namespace rtree {

template <typename Alloc>
class scoped_deallocator
{
    typedef boost::container::allocator_traits<Alloc> alloc_traits;

    scoped_deallocator(scoped_deallocator const&);
    scoped_deallocator & operator=(scoped_deallocator const&);
public:
    typedef typename alloc_traits::pointer pointer;

    inline scoped_deallocator(pointer p, Alloc & a)
        : m_ptr(p), m_alloc(a)
    {}
    inline ~scoped_deallocator()
    {
        if ( m_ptr )
        {
            alloc_traits::deallocate(m_alloc, m_ptr, 1);
        }
    }
    inline void release()
    {
        m_ptr = 0;
    }
private:
    pointer m_ptr;
    Alloc & m_alloc;
};

}} // namespace detail::rtree

}}} // namespace boost::geometry::index

#endif // BOOST_GEOMETRY_INDEX_DETAIL_RTREE_NODE_SCOPED_DEALLOCATOR_HPP

/* scoped_deallocator.hpp
pA7VpQFmb6lE7XCsgkdCtbkXKewy1dLGBxPG6RA/xevHhi8XmmWpUe7mmgl5Ls0osniit7+tCdHBtfLMCNzxJpcFU1g3+o/DaDYZfBKfp6NoeDSKZlF/GsF677sVR2f98Sd6QwA2tkHEJuvKEG4ZjLHXwNfoGSYEg0yVz7lOWpT0r2q9krnwYt5E6BC7iPFd67ZNrbd0eEitx0n/SljSbv9/OqWSyS46UwxGD9jcMua+XvBUdTw8uvx4dDk6O94jrpfc3Dcnm1R5wYXfWJwTnxeDhPYV39XOTt1Z8d+aDMVTQWMgGlwh7+2SkLeayZeQgDbX65aj19lb588vISHqVoiOhrSos9IFTzBYcUvt0oRR6l07lMQ4DQaJulGZLXIF8M2eSBmmjKpe6SxxXXbVu6fuzS6fKnb7yqBQh2OaKo+eGugHsd+1T+j3fHIRifP+3+J0MovEYDIeDwfRaDKe8UTAemIhQQziPorI5a1IrfNiIzz3FJkXs4gmUf/sh2igTcrsxTweRBFnI8L5/Xj551IxrzgHgoP2B5Ys/NHR5fj4bCgOqM5pR5uufo96nFmMi612M7VcurqLc0CavVAorRCPx3gVXtSWTdmr33LGoWc2sWRPTf7RElVLYQKqHGcvEl3ObRVmvDkgAnqX
*/