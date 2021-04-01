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
kyDONS9HlTwrjAyyMrPKRmGDLSo7meVvhKGFpl+/zbYg4f3ebKFuxaD6L5IZfgc45wO61Ymdhboy6uyFbWslV5kOB7zJCS4f2V6EMB02YI79v/hUvcpm9d9OZrRXQhK8TMZj4F9SALWDw+7qEU3zzgEcI/BRMN1QgkC3lxvS3w4wCc6LfuCla4gwZZ9Gl9lyrDHuOmOSgjXVkdsi9ozIwvbuF45KxkFQYqozlaYrgQZXSsOu5Efd/sIV3PL8IQQj9ckFG62FQRvmve2O9HN1oWc5oynCZ79vf3CbPr094T4hel5Q60T9aXwecT3ysUZK0kLIKqjWHv93rnyRNNBRZD7RhgPOWnTa+coN6rE925tX8cWO/EiH28Ykjz+2ZdpV6+rJP656zvfErQZNkNsXu69yp9U9DymDYmp7XYrS+yCibaG4lBotpvF7aNbQbBQk7rfTiNBJUor7Rp3ctcg8TXAE0kOII6vgAH4EjHrNX43wV5bzIUhK6Iu5wSvWDnoEfEygjtQwE70fabJtsroRG3p6lLzggv0GI/yh/JjSu4ZQh32j9JIuU/dl7Q==
*/