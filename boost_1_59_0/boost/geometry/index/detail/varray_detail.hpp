// Boost.Geometry
//
// varray details
//
// Copyright (c) 2011-2013 Andrew Hundt.
// Copyright (c) 2012-2020 Adam Wulkiewicz, Lodz, Poland.
//
// This file was modified by Oracle on 2020.
// Modifications copyright (c) 2020, Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle
//
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_INDEX_DETAIL_VARRAY_DETAIL_HPP
#define BOOST_GEOMETRY_INDEX_DETAIL_VARRAY_DETAIL_HPP

#include <algorithm>
#include <cstddef>
#include <cstring>
#include <limits>
#include <memory>
#include <type_traits>

#include <boost/config.hpp>

#include <boost/core/no_exceptions_support.hpp>
#include <boost/move/move.hpp>
#include <boost/core/addressof.hpp>
#include <boost/iterator/iterator_traits.hpp>

#if defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)
#include <boost/move/detail/fwd_macros.hpp>
#endif

// TODO - move vectors iterators optimization to the other, optional file instead of checking defines?

#if defined(BOOST_GEOMETRY_INDEX_DETAIL_VARRAY_ENABLE_VECTOR_OPTIMIZATION) && !defined(BOOST_NO_EXCEPTIONS)
#include <vector>
#include <boost/container/vector.hpp>
#endif // BOOST_GEOMETRY_INDEX_DETAIL_VARRAY_ENABLE_VECTOR_OPTIMIZATION && !BOOST_NO_EXCEPTIONS

namespace boost { namespace geometry { namespace index { namespace detail { namespace varray_detail
{


template <typename I>
struct are_elements_contiguous : std::is_pointer<I>
{};
    
// EXPERIMENTAL - not finished
// Conditional setup - mark vector iterators defined in known implementations
// as iterators pointing to contiguous ranges

#if defined(BOOST_GEOMETRY_INDEX_DETAIL_VARRAY_ENABLE_VECTOR_OPTIMIZATION) && !defined(BOOST_NO_EXCEPTIONS)
    
template <typename Pointer>
struct are_elements_contiguous<
    boost::container::container_detail::vector_const_iterator<Pointer>
> : std::true_type
{};

template <typename Pointer>
struct are_elements_contiguous<
    boost::container::container_detail::vector_iterator<Pointer>
> : std::true_type
{};

#if defined(BOOST_DINKUMWARE_STDLIB)
    
template <typename T>
struct are_elements_contiguous<
    std::_Vector_const_iterator<T>
> : std::true_type
{};

template <typename T>
struct are_elements_contiguous<
    std::_Vector_iterator<T>
> : std::true_type
{};

#elif defined(BOOST_GNU_STDLIB)

template <typename P, typename T, typename A>
struct are_elements_contiguous<
    __gnu_cxx::__normal_iterator<P, std::vector<T, A> >
> : std::true_type
{};

#elif defined(_LIBCPP_VERSION)

// TODO - test it first
//template <typename P>
//struct are_elements_contiguous<
//    __wrap_iter<P>
//> : std::true_type
//{};

#else // OTHER_STDLIB

// TODO - add other iterators implementations
    
#endif // STDLIB

#endif // BOOST_GEOMETRY_INDEX_DETAIL_VARRAY_ENABLE_VECTOR_OPTIMIZATION && !BOOST_NO_EXCEPTIONS


template <typename I, typename O>
struct is_memop_safe_for_range
    : std::integral_constant
        <
            bool,
            std::is_same
                <
                    std::remove_const_t
                        <
                            typename ::boost::iterator_value<I>::type
                        >,
                    std::remove_const_t
                        <
                            typename ::boost::iterator_value<O>::type
                        >
                >::value
            &&
            are_elements_contiguous<I>::value
            &&
            are_elements_contiguous<O>::value
            &&
            std::is_trivially_copyable
                <
                    typename ::boost::iterator_value<O>::type
                >::value
        >
{};


template <typename I, typename V>
struct is_memop_safe_for_value
    : std::integral_constant
        <
            bool,
            std::is_same
                <
                    std::remove_const_t
                        <
                            typename ::boost::iterator_value<I>::type
                        >,
                    std::remove_const_t<V>
                >::value
            &&
            std::is_trivially_copyable
                <
                    V
                >::value
        >
{};

// destroy(I, I)

template <typename I>
void destroy_dispatch(I /*first*/, I /*last*/,
                      std::true_type /*has_trivial_destructor*/)
{}

template <typename I>
void destroy_dispatch(I first, I last,
                      std::false_type /*has_trivial_destructor*/)
{
    typedef typename boost::iterator_value<I>::type value_type;
    for ( ; first != last ; ++first )
        first->~value_type();
}

template <typename I>
void destroy(I first, I last)
{
    typedef typename boost::iterator_value<I>::type value_type;
    destroy_dispatch(first, last, std::is_trivially_destructible<value_type>());
}

// destroy(I)

template <typename I>
void destroy_dispatch(I /*pos*/,
                      std::true_type /*has_trivial_destructor*/)
{}

template <typename I>
void destroy_dispatch(I pos,
                      std::false_type /*has_trivial_destructor*/)
{
    typedef typename boost::iterator_value<I>::type value_type;
    pos->~value_type();
}

template <typename I>
void destroy(I pos)
{
    typedef typename boost::iterator_value<I>::type value_type;
    destroy_dispatch(pos, std::is_trivially_destructible<value_type>());
}

// copy(I, I, O)

template <typename I, typename O>
inline O copy_dispatch(I first, I last, O dst,
                       std::true_type /*use_memmove*/)
{
    typedef typename boost::iterator_value<I>::type value_type;
    typename boost::iterator_difference<I>::type d = std::distance(first, last);

    ::memmove(boost::addressof(*dst), boost::addressof(*first), sizeof(value_type) * d);
    return dst + d;
}

template <typename I, typename O>
inline O copy_dispatch(I first, I last, O dst,
                       std::false_type /*use_memmove*/)
{
    return std::copy(first, last, dst);                                         // may throw
}

template <typename I, typename O>
inline O copy(I first, I last, O dst)
{
    return copy_dispatch(first, last, dst, is_memop_safe_for_range<I, O>());    // may throw
}

// uninitialized_copy(I, I, O)

template <typename I, typename O>
inline
O uninitialized_copy_dispatch(I first, I last, O dst,
                              std::true_type /*use_memcpy*/)
{
    typedef typename boost::iterator_value<I>::type value_type;
    typename boost::iterator_difference<I>::type d = std::distance(first, last);

    ::memcpy(boost::addressof(*dst), boost::addressof(*first), sizeof(value_type) * d);
    return dst + d;
}

template <typename I, typename F>
inline
F uninitialized_copy_dispatch(I first, I last, F dst,
                              std::false_type /*use_memcpy*/)
{
    return std::uninitialized_copy(first, last, dst);                                       // may throw
}

template <typename I, typename F>
inline
F uninitialized_copy(I first, I last, F dst)
{
    return uninitialized_copy_dispatch(first, last, dst, is_memop_safe_for_range<I, F>());  // may throw
}

// uninitialized_move(I, I, O)

template <typename I, typename O>
inline
O uninitialized_move_dispatch(I first, I last, O dst,
                              std::true_type /*use_memcpy*/)
{
    typedef typename boost::iterator_value<I>::type value_type;
    typename boost::iterator_difference<I>::type d = std::distance(first, last);

    ::memcpy(boost::addressof(*dst), boost::addressof(*first), sizeof(value_type) * d);
    return dst + d;
}

template <typename I, typename O>
inline
O uninitialized_move_dispatch(I first, I last, O dst,
                              std::false_type /*use_memcpy*/)
{
    //return boost::uninitialized_move(first, last, dst);                         // may throw

    O o = dst;

    BOOST_TRY
    {
        typedef typename std::iterator_traits<O>::value_type value_type;
        for (; first != last; ++first, ++o )
            new (boost::addressof(*o)) value_type(boost::move(*first));
    }
    BOOST_CATCH(...)
    {
        varray_detail::destroy(dst, o);
        BOOST_RETHROW;
    }
    BOOST_CATCH_END

    return dst;
}

template <typename I, typename O>
inline
O uninitialized_move(I first, I last, O dst)
{
    return uninitialized_move_dispatch(first, last, dst, is_memop_safe_for_range<I, O>()); // may throw
}

// TODO - move uses memmove - implement 2nd version using memcpy?

// move(I, I, O)

template <typename I, typename O>
inline
O move_dispatch(I first, I last, O dst,
                std::true_type /*use_memmove*/)
{
    typedef typename boost::iterator_value<I>::type value_type;
    typename boost::iterator_difference<I>::type d = std::distance(first, last);

    ::memmove(boost::addressof(*dst), boost::addressof(*first), sizeof(value_type) * d);
    return dst + d;
}

template <typename I, typename O>
inline
O move_dispatch(I first, I last, O dst,
                std::false_type /*use_memmove*/)
{
    return boost::move(first, last, dst);                                         // may throw
}

template <typename I, typename O>
inline
O move(I first, I last, O dst)
{
    return move_dispatch(first, last, dst, is_memop_safe_for_range<I, O>());      // may throw
}

// move_backward(BDI, BDI, BDO)

template <typename BDI, typename BDO>
inline
BDO move_backward_dispatch(BDI first, BDI last, BDO dst,
                           std::true_type /*use_memmove*/)
{
    typedef typename boost::iterator_value<BDI>::type value_type;
    typename boost::iterator_difference<BDI>::type d = std::distance(first, last);

    BDO foo(dst - d);
    ::memmove(boost::addressof(*foo), boost::addressof(*first), sizeof(value_type) * d);
    return foo;
}

template <typename BDI, typename BDO>
inline
BDO move_backward_dispatch(BDI first, BDI last, BDO dst,
                           std::false_type /*use_memmove*/)
{
    return boost::move_backward(first, last, dst);                                // may throw
}

template <typename BDI, typename BDO>
inline
BDO move_backward(BDI first, BDI last, BDO dst)
{
    return move_backward_dispatch(first, last, dst, is_memop_safe_for_range<BDI, BDO>()); // may throw
}

template <typename T>
struct has_nothrow_move
    : std::integral_constant
        <
            bool,
            ::boost::has_nothrow_move<std::remove_const_t<T> >::value
            ||
            ::boost::has_nothrow_move<T>::value
        >
{};

// uninitialized_move_if_noexcept(I, I, O)

template <typename I, typename O>
inline
O uninitialized_move_if_noexcept_dispatch(I first, I last, O dst,
                                          std::true_type /*use_move*/)
{
    return varray_detail::uninitialized_move(first, last, dst);
}

template <typename I, typename O>
inline
O uninitialized_move_if_noexcept_dispatch(I first, I last, O dst,
                                          std::false_type const& /*use_move*/)
{
    return varray_detail::uninitialized_copy(first, last, dst);
}

template <typename I, typename O>
inline
O uninitialized_move_if_noexcept(I first, I last, O dst)
{
    typedef has_nothrow_move<
        typename ::boost::iterator_value<O>::type
    > use_move;

    return uninitialized_move_if_noexcept_dispatch(first, last, dst, use_move());         // may throw
}

// move_if_noexcept(I, I, O)

template <typename I, typename O>
inline
O move_if_noexcept_dispatch(I first, I last, O dst,
                            std::true_type /*use_move*/)
{
    return varray_detail::move(first, last, dst);
}

template <typename I, typename O>
inline
O move_if_noexcept_dispatch(I first, I last, O dst,
                            std::false_type /*use_move*/)
{
    return varray_detail::copy(first, last, dst);
}

template <typename I, typename O>
inline
O move_if_noexcept(I first, I last, O dst)
{
    typedef has_nothrow_move<
        typename ::boost::iterator_value<O>::type
    > use_move;

    return move_if_noexcept_dispatch(first, last, dst, use_move());         // may throw
}

// uninitialized_fill(I, I)

template <typename I>
inline
void uninitialized_fill_dispatch(I /*first*/, I /*last*/,
                                 std::true_type const& /*has_trivial_constructor*/,
                                 std::true_type const& /*disable_trivial_init*/)
{}

template <typename I>
inline
void uninitialized_fill_dispatch(I first, I last,
                                 std::true_type const& /*has_trivial_constructor*/,
                                 std::false_type const& /*disable_trivial_init*/)
{
    typedef typename boost::iterator_value<I>::type value_type;
    for ( ; first != last ; ++first )
        new (boost::addressof(*first)) value_type();
}

template <typename I, typename DisableTrivialInit>
inline
void uninitialized_fill_dispatch(I first, I last,
                                 std::false_type const& /*has_trivial_constructor*/,
                                 DisableTrivialInit const& /*not_used*/)
{
    typedef typename boost::iterator_value<I>::type value_type;
    I it = first;

    BOOST_TRY
    {
        for ( ; it != last ; ++it )
            new (boost::addressof(*it)) value_type();                           // may throw
    }
    BOOST_CATCH(...)
    {
        varray_detail::destroy(first, it);
        BOOST_RETHROW;
    }
    BOOST_CATCH_END
}

template <typename I, typename DisableTrivialInit>
inline
void uninitialized_fill(I first, I last, DisableTrivialInit const& disable_trivial_init)
{
    typedef typename boost::iterator_value<I>::type value_type;
    uninitialized_fill_dispatch(first, last, std::is_trivially_constructible<value_type>(), disable_trivial_init);     // may throw
}

// construct(I)

template <typename I>
inline
void construct_dispatch(std::true_type /*dont_init*/, I /*pos*/)
{}

template <typename I>
inline
void construct_dispatch(std::false_type /*dont_init*/, I pos)
{
    typedef typename ::boost::iterator_value<I>::type value_type;
    new (static_cast<void*>(::boost::addressof(*pos))) value_type();                      // may throw
}

template <typename DisableTrivialInit, typename I>
inline
void construct(DisableTrivialInit const&, I pos)
{
    typedef typename ::boost::iterator_value<I>::type value_type;
    typedef std::integral_constant
        <
            bool,
            std::is_trivially_constructible<value_type>::value
            &&
            DisableTrivialInit::value
        > dont_init;

    construct_dispatch(dont_init(), pos);                                                // may throw
}

// construct(I, V)

template <typename I, typename V>
inline
void construct_copy_dispatch(I pos, V const& v,
                             std::true_type /*use_memcpy*/)
{
    ::memcpy(boost::addressof(*pos), boost::addressof(v), sizeof(V));
}

template <typename I, typename P>
inline
void construct_copy_dispatch(I pos, P const& p,
                             std::false_type const& /*use_memcpy*/)
{
    typedef typename boost::iterator_value<I>::type V;
    new (static_cast<void*>(boost::addressof(*pos))) V(p);                      // may throw
}

template <typename DisableTrivialInit, typename I, typename P>
inline
void construct(DisableTrivialInit const&,
               I pos, P const& p)
{
    construct_copy_dispatch(pos, p, is_memop_safe_for_value<I, P>());           // may throw
}

// Needed by push_back(V &&)

template <typename I, typename V>
inline
void construct_move_dispatch(I pos, V const& v,
                             std::true_type const& /*use_memcpy*/)
{
    ::memcpy(boost::addressof(*pos), boost::addressof(v), sizeof(V));
}

template <typename I, typename P>
inline
void construct_move_dispatch(I pos, BOOST_RV_REF(P) p,
                             std::false_type const& /*use_memcpy*/)
{
    typedef typename boost::iterator_value<I>::type V;
    new (static_cast<void*>(boost::addressof(*pos))) V(::boost::move(p));       // may throw
}

template <typename DisableTrivialInit, typename I, typename P>
inline
void construct(DisableTrivialInit const&, I pos, BOOST_RV_REF(P) p)
{
    construct_move_dispatch(pos, ::boost::move(p), is_memop_safe_for_value<I, P>()); // may throw
}

// Needed by emplace_back() and emplace()

#if !defined(BOOST_CONTAINER_VARRAY_DISABLE_EMPLACE)
#if !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)

template <typename DisableTrivialInit, typename I, class ...Args>
inline
void construct(DisableTrivialInit const&,
               I pos,
               BOOST_FWD_REF(Args) ...args)
{
    typedef typename boost::iterator_value<I>::type V;
    new (static_cast<void*>(boost::addressof(*pos))) V(::boost::forward<Args>(args)...);    // may throw
}

#else // !BOOST_NO_CXX11_VARIADIC_TEMPLATES

// BOOST_NO_CXX11_RVALUE_REFERENCES -> P0 const& p0
// !BOOST_NO_CXX11_RVALUE_REFERENCES -> P0 && p0
// which means that version with one parameter may take V const& v

#define BOOST_GEOMETRY_INDEX_DETAIL_VARRAY_DETAIL_CONSTRUCT(N)                                      \
template <typename DisableTrivialInit, typename I, typename P BOOST_MOVE_I##N BOOST_MOVE_CLASS##N > \
inline                                                                                              \
void construct(DisableTrivialInit const&,                                                           \
               I pos,                                                                               \
               BOOST_FWD_REF(P) p                                                                   \
               BOOST_MOVE_I##N BOOST_MOVE_UREF##N)                                                  \
{                                                                                                   \
    typedef typename boost::iterator_value<I>::type V;                                              \
    new                                                                                             \
    (static_cast<void*>(boost::addressof(*pos)))                                                    \
    V(boost::forward<P>(p) BOOST_MOVE_I##N BOOST_MOVE_FWD##N);                    /*may throw*/    \
}                                                                                                   \

BOOST_MOVE_ITERATE_1TO9(BOOST_GEOMETRY_INDEX_DETAIL_VARRAY_DETAIL_CONSTRUCT)
#undef BOOST_GEOMETRY_INDEX_DETAIL_VARRAY_DETAIL_CONSTRUCT

#endif // !BOOST_NO_CXX11_VARIADIC_TEMPLATES
#endif // !BOOST_CONTAINER_VARRAY_DISABLE_EMPLACE

// assign(I, V)

template <typename I, typename V>
inline
void assign_copy_dispatch(I pos, V const& v,
                          std::true_type /*use_memcpy*/)
{
// TODO - use memmove here?
    ::memcpy(boost::addressof(*pos), boost::addressof(v), sizeof(V));
}

template <typename I, typename V>
inline
void assign_copy_dispatch(I pos, V const& v,
                          std::false_type /*use_memcpy*/)
{
    *pos = v;                                                                   // may throw
}

template <typename I, typename V>
inline
void assign(I pos, V const& v)
{
    assign_copy_dispatch(pos, v, is_memop_safe_for_value<I, V>());              // may throw
}

template <typename I, typename V>
inline
void assign_move_dispatch(I pos, V const& v,
                          std::true_type /*use_memcpy*/)
{
// TODO - use memmove here?
    ::memcpy(boost::addressof(*pos), boost::addressof(v), sizeof(V));
}

template <typename I, typename V>
inline
void assign_move_dispatch(I pos, BOOST_RV_REF(V) v,
                          std::false_type /*use_memcpy*/)
{
    *pos = boost::move(v);                                                        // may throw
}

template <typename I, typename V>
inline
void assign(I pos, BOOST_RV_REF(V) v)
{
    assign_move_dispatch(pos, ::boost::move(v), is_memop_safe_for_value<I, V>());
}

// uninitialized_copy_s

template <typename I, typename F>
inline std::size_t uninitialized_copy_s(I first, I last, F dest, std::size_t max_count)
{
    std::size_t count = 0;
    F it = dest;

    BOOST_TRY
    {
        for ( ; first != last ; ++it, ++first, ++count )
        {
            if ( max_count <= count )
                return (std::numeric_limits<std::size_t>::max)();

            // dummy 0 as DisableTrivialInit
            construct(0, it, *first);                                              // may throw
        }
    }
    BOOST_CATCH(...)
    {
        varray_detail::destroy(dest, it);
        BOOST_RETHROW;
    }
    BOOST_CATCH_END

    return count;
}

// scoped_destructor

template<class T>
class scoped_destructor
{
public:
    scoped_destructor(T * ptr) : m_ptr(ptr) {}

    ~scoped_destructor()
    {
        if(m_ptr)
            varray_detail::destroy(m_ptr);
    }

    void release() { m_ptr = 0; }

private:
    T * m_ptr;
};

}}}}} // namespace boost::geometry::index::detail::varray_detail

#endif // BOOST_GEOMETRY_INDEX_DETAIL_VARRAY_DETAIL_HPP

/* varray_detail.hpp
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
*/