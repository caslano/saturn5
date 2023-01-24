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
5iU8ZRWOO3+/XphkeH/CPtPfu7lyz6BjXLssoKZf1kCPrcovI/PBKZfvW3XnJ7K4LkfCV0uxUqi4sbjdbEjlTs/9a61+vimGivVhsu6TzeMFLZMgn5/p8tfZJdD4lKsFPZMkhq1EMsVzfyVFujGajCmni86GHdNMPOgqoP8utt/nfkySheCEIDZ6rU6iMgnRZaGzkR8jTkOm2MdkPUU9bpXjE+rw/iYqFfzJRZ7OrSSsysEmoH+t4+r3nwFEvCxeX6Iyw5mxJnWD5mMTN5dpmqMIUlEGUV9jzqvEpLL6rlu7VFspSFaNL0sWZ18BYJtnIN7cJvq9qYaMFNOKMjbhU8ly6Q1D5f3U7uNbu6OrocDDbE/ut+16Pe4wn1WFdq9Jrtf1d8yu6cqv9gO0NVc8KHTL8pSSIJo+5N5NSGu7JP+LV0WbMpp2hfSZsGJ7RNzBQxGHseqS3+dlRoIwYmd9RmXQzD3bjpjz9Otmu+hx1o8BIltx91oxzK5gu6Yfe0zFwRe8OLrsPllFSJ4QzTNtDR6TK6IAmwpv4vIcXtU0Vu6mz41adOZV4f78PhyYc+YzjgX1Qz23m3w4Lre39rQ4MivDXACZY9FGY5us3fT9zs/7StnQm+2yqedapIRS48Scx21GDXKNppNxbc1uDPdSQqu853BE+7rfqfxQxNGu7rD+dVoLirZe8UPUskjzjspQnwOXA791qleb4YgJ
*/