/*
Copyright 2014-2015 Glen Joseph Fernandes
(glenjofe@gmail.com)

Distributed under the Boost Software License, Version 1.0.
(http://www.boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_ALIGN_ALIGNED_ALLOCATOR_HPP
#define BOOST_ALIGN_ALIGNED_ALLOCATOR_HPP

#include <boost/align/detail/add_reference.hpp>
#include <boost/align/detail/is_alignment_constant.hpp>
#include <boost/align/detail/max_objects.hpp>
#include <boost/align/detail/max_size.hpp>
#include <boost/align/detail/throw_exception.hpp>
#include <boost/align/aligned_alloc.hpp>
#include <boost/align/aligned_allocator_forward.hpp>
#include <boost/align/alignment_of.hpp>
#include <boost/static_assert.hpp>
#include <new>

#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
#include <utility>
#endif

namespace boost {
namespace alignment {

template<class T, std::size_t Alignment>
class aligned_allocator {
    BOOST_STATIC_ASSERT(detail::is_alignment_constant<Alignment>::value);

public:
    typedef T value_type;
    typedef T* pointer;
    typedef const T* const_pointer;
    typedef void* void_pointer;
    typedef const void* const_void_pointer;
    typedef typename detail::add_lvalue_reference<T>::type reference;
    typedef typename detail::add_lvalue_reference<const
        T>::type const_reference;
    typedef std::size_t size_type;
    typedef std::ptrdiff_t difference_type;
    typedef detail::true_type propagate_on_container_move_assignment;
    typedef detail::true_type is_always_equal;

    template<class U>
    struct rebind {
        typedef aligned_allocator<U, Alignment> other;
    };

#if !defined(BOOST_NO_CXX11_DEFAULTED_FUNCTIONS)
    aligned_allocator() = default;
#else
    aligned_allocator() BOOST_NOEXCEPT { }
#endif

    template<class U>
    aligned_allocator(const aligned_allocator<U, Alignment>&)
        BOOST_NOEXCEPT { }

    pointer allocate(size_type size, const_void_pointer = 0) {
        enum {
            m = detail::max_size<Alignment,
                alignment_of<value_type>::value>::value
        };
        if (size == 0) {
            return 0;
        }
        void* p = boost::alignment::aligned_alloc(m, sizeof(T) * size);
        if (!p) {
            detail::throw_exception(std::bad_alloc());
        }
        return static_cast<T*>(p);
    }

    void deallocate(pointer ptr, size_type) {
        boost::alignment::aligned_free(ptr);
    }

    BOOST_CONSTEXPR size_type max_size() const BOOST_NOEXCEPT {
        return detail::max_objects<T>::value;
    }

#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
#if !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)
    template<class U, class... Args>
    void construct(U* ptr, Args&&... args) {
        ::new((void*)ptr) U(std::forward<Args>(args)...);
    }
#else
    template<class U, class V>
    void construct(U* ptr, V&& value) {
        ::new((void*)ptr) U(std::forward<V>(value));
    }
#endif
#else
    template<class U, class V>
    void construct(U* ptr, const V& value) {
        ::new((void*)ptr) U(value);
    }

    template<class U, class V>
    void construct(U* ptr, V& value) {
        ::new((void*)ptr) U(value);
    }
#endif

    template<class U>
    void construct(U* ptr) {
        ::new((void*)ptr) U();
    }

    template<class U>
    void destroy(U* ptr) {
        (void)ptr;
        ptr->~U();
    }
};

template<class T, class U, std::size_t Alignment>
inline bool
operator==(const aligned_allocator<T, Alignment>&,
    const aligned_allocator<U, Alignment>&) BOOST_NOEXCEPT
{
    return true;
}

template<class T, class U, std::size_t Alignment>
inline bool
operator!=(const aligned_allocator<T, Alignment>&,
    const aligned_allocator<U, Alignment>&) BOOST_NOEXCEPT
{
    return false;
}

} /* alignment */
} /* boost */

#endif

/* aligned_allocator.hpp
UZx+s0QiJJSlgyIipQKREUgRGogaLx1tLh2NLh2NHjqKmI71oIPiIXRxEmWC3Z0cAOGxCJkkcwhYLYNdhJvCETdUne8HzzQ5BNpAQPRKasyutlBtc1NEY99sp7C/R4J/lwBgf4ggVrkEJFwCElEi20PFXB5B97pUrIoI/6G0TAVqgwpkChWUKbEltfdSEbBTVHQzFX0005Ci4gCy0FdFgkkijKjoT8kATqv/qCSsdkl4UpPAKRf7yxj7dRp7O1OY4s4/tKM5sIf/kCw9ZBfsgTrQhhQfEE6SWvUSBRgF6cEruhNGfG8kuEcPYYVszxCWDk/DOPatSyHgoaOU6ejzSqFVSFibGgGBDj0I4ghG6GgVM0lLgd7p9UphPTs0GRionUzMDvRuKYNyUiSUYzwHErRFR7V2HSspxR5SrmZSerykNAspHZqUYialWUghEaU0e8AIbn4pDEmTIuzC4yAgPZTjaQX0VeinxKrQVelxXMqxR9+qVJgKGaOQgy4nGvBwoFqPO4idnCvRIgPtqNlIgyGhBN0K7tGtEGUpYjCyiZgtcKtlnp6C7S0K+MURdqETeGyDrnZHDL14qmNvBwbi4lOjHAimHf2A20PkQPGlh5guw5Lh4swJ9FLqQXQ/Ueb2E4x+5gPMnMP7hp4j9g2d6Q6unLok405ujhENoY7+QdeiE5YwFCLkMRaisZruokAHufyE28/5DyGizyVirSYCKcJfQggfi6AlalDb03VP4RfcewV36UEYd/UssmLmnzEgkshIovU0ERWI6aSXBkaiJ9xbN6MWI2840gRWpkcvREER/PtRKeh2KVilKUBKU8BsoBjH5g6HZbHSG2x0CinrdbBhgx7JhLcl1kj8I7F5mgwbsVs62MDQGWOw1PhE8WDF/APGTgMHKqAD7n7jW6ODCCjSxKR6HVCBoZxLRbseb0VYIDx4ARXIFCp6vQMvkAD05yK6SkkBmpQa9jv8yDfQU+ghCUY2A0clQgXc/r6jUtHjUtGhqUCKJDDXYxQBIsErCD0SibiC4PF2ShCUGWESJOROC+IyWJAWBMaLKEV0hAoiiD24597j1QFjDo7+CH9jt7brYxXEZR4SilmXGtNS0CMMKHhqkAESJBOOttc71LC9gevV7tAiwQJaSWMM7YfUTmRJnzFgpEHLDOyVUmwGdM3mqwlHVwwc3Ej0igSoE6vOIYdRysO5/RiVEAWk3/XIdKdangL6yBT013tHFrbXLS2G8Qj6rWzJ2Hbz0h16/IAOAnk82kBHIabEHcVuDDX0gAKvweQ3YlQytbvgnkf2JJOk5LRzSOaz6SorQzFjc1TpRSYD3x/S60gGwMoSU4R2JMtqkm3soG3EP+Nm2IKPtSeu+yyF6YttA9GErCxFarffIUtV3kWxaP3I9HrWDf70Gta1gfQ61cVF6TUtWS/7HqdvKU2vbb23LL2+FSnntS3e9zz6Bdn3LPudU6toemVNyWobUejwNbUql1qpkzU8bLDyZ/49q7PHf8d/x3/Hf8d/x3//G79DP029oIF2lDtPXaJPlcE49KWo2k2HxLzHvmtd9btj2CM031l+Kspx5AxubNqSVOF89irK2UA5JRhRMjRE2ryzp81ZcCp/aSuXNkHHZu1ImptoL5B1jd7/DADbssxG2uZj0zafubRt7jLs9Sl7q9vmCJkiIqqYN/ToT+5cKlQdfJcc6rPd3BQ2kzGFdTiEi/tBXMGdr6MCCCy4czsSvCvoT5xA0SZqe98paAt2UEk7MmhNfrHzlYU7klGd+2mqphZSNYfYsMy5baHLkyVRmmCIqrUIDnnnFu13qgBMlM3GGBfZxJFYLiALXyejMtdEpIzYng7pKpH6o6Q=
*/