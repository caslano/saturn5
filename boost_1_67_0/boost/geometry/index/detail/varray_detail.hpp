// Boost.Geometry
//
// varray details
//
// Copyright (c) 2012-2015 Adam Wulkiewicz, Lodz, Poland.
// Copyright (c) 2011-2013 Andrew Hundt.
//
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_INDEX_DETAIL_VARRAY_DETAIL_HPP
#define BOOST_GEOMETRY_INDEX_DETAIL_VARRAY_DETAIL_HPP

#include <cstddef>
#include <cstring>
#include <memory>
#include <limits>

#include <boost/mpl/if.hpp>
#include <boost/mpl/and.hpp>
#include <boost/mpl/or.hpp>
#include <boost/mpl/int.hpp>

#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/remove_const.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/type_traits/has_trivial_assign.hpp>
#include <boost/type_traits/has_trivial_copy.hpp>
#include <boost/type_traits/has_trivial_constructor.hpp>
#include <boost/type_traits/has_trivial_destructor.hpp>
#include <boost/type_traits/has_trivial_move_constructor.hpp>
#include <boost/type_traits/has_trivial_move_assign.hpp>
//#include <boost/type_traits/has_nothrow_constructor.hpp>
//#include <boost/type_traits/has_nothrow_copy.hpp>
//#include <boost/type_traits/has_nothrow_assign.hpp>
//#include <boost/type_traits/has_nothrow_destructor.hpp>

#include <boost/detail/no_exceptions_support.hpp>
#include <boost/config.hpp>
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

namespace boost { namespace geometry { namespace index { namespace detail { namespace varray_detail {

template <typename I>
struct are_elements_contiguous : boost::is_pointer<I>
{};
    
// EXPERIMENTAL - not finished
// Conditional setup - mark vector iterators defined in known implementations
// as iterators pointing to contiguous ranges

#if defined(BOOST_GEOMETRY_INDEX_DETAIL_VARRAY_ENABLE_VECTOR_OPTIMIZATION) && !defined(BOOST_NO_EXCEPTIONS)
    
template <typename Pointer>
struct are_elements_contiguous<
    boost::container::container_detail::vector_const_iterator<Pointer>
> : boost::true_type
{};

template <typename Pointer>
struct are_elements_contiguous<
    boost::container::container_detail::vector_iterator<Pointer>
> : boost::true_type
{};

#if defined(BOOST_DINKUMWARE_STDLIB)
    
template <typename T>
struct are_elements_contiguous<
    std::_Vector_const_iterator<T>
> : boost::true_type
{};

template <typename T>
struct are_elements_contiguous<
    std::_Vector_iterator<T>
> : boost::true_type
{};

#elif defined(BOOST_GNU_STDLIB)

template <typename P, typename T, typename A>
struct are_elements_contiguous<
    __gnu_cxx::__normal_iterator<P, std::vector<T, A> >
> : boost::true_type
{};

#elif defined(_LIBCPP_VERSION)

// TODO - test it first
//template <typename P>
//struct are_elements_contiguous<
//    __wrap_iter<P>
//> : boost::true_type
//{};

#else // OTHER_STDLIB

// TODO - add other iterators implementations
    
#endif // STDLIB

#endif // BOOST_GEOMETRY_INDEX_DETAIL_VARRAY_ENABLE_VECTOR_OPTIMIZATION && !BOOST_NO_EXCEPTIONS

// True if iterator values are the same and both iterators points to the ranges of contiguous elements

template <typename I, typename O>
struct are_corresponding :
    ::boost::mpl::and_<
        ::boost::is_same<
            ::boost::remove_const<
                typename ::boost::iterator_value<I>::type
            >,
            ::boost::remove_const<
                typename ::boost::iterator_value<O>::type
            >
        >,
        are_elements_contiguous<I>,
        are_elements_contiguous<O>
    >
{};

template <typename I, typename V>
struct is_corresponding_value :
    ::boost::is_same<
        ::boost::remove_const<
            typename ::boost::iterator_value<I>::type
        >,
        ::boost::remove_const<V>
    >
{};

// destroy(I, I)

template <typename I>
void destroy_dispatch(I /*first*/, I /*last*/,
                      boost::true_type const& /*has_trivial_destructor*/)
{}

template <typename I>
void destroy_dispatch(I first, I last,
                      boost::false_type const& /*has_trivial_destructor*/)
{
    typedef typename boost::iterator_value<I>::type value_type;
    for ( ; first != last ; ++first )
        first->~value_type();
}

template <typename I>
void destroy(I first, I last)
{
    typedef typename boost::iterator_value<I>::type value_type;
    destroy_dispatch(first, last, has_trivial_destructor<value_type>());
}

// destroy(I)

template <typename I>
void destroy_dispatch(I /*pos*/,
                      boost::true_type const& /*has_trivial_destructor*/)
{}

template <typename I>
void destroy_dispatch(I pos,
                      boost::false_type const& /*has_trivial_destructor*/)
{
    typedef typename boost::iterator_value<I>::type value_type;
    pos->~value_type();
}

template <typename I>
void destroy(I pos)
{
    typedef typename boost::iterator_value<I>::type value_type;
    destroy_dispatch(pos, has_trivial_destructor<value_type>());
}

// copy(I, I, O)

template <typename I, typename O>
inline O copy_dispatch(I first, I last, O dst,
                       boost::mpl::bool_<true> const& /*use_memmove*/)
{
    typedef typename boost::iterator_value<I>::type value_type;
    typename boost::iterator_difference<I>::type d = std::distance(first, last);

    ::memmove(boost::addressof(*dst), boost::addressof(*first), sizeof(value_type) * d);
    return dst + d;
}

template <typename I, typename O>
inline O copy_dispatch(I first, I last, O dst,
                       boost::mpl::bool_<false> const& /*use_memmove*/)
{
    return std::copy(first, last, dst);                                         // may throw
}

template <typename I, typename O>
inline O copy(I first, I last, O dst)
{
    typedef typename
    ::boost::mpl::and_<
        are_corresponding<I, O>,
        ::boost::has_trivial_assign<
            typename ::boost::iterator_value<O>::type
        >
    >::type
    use_memmove;
    
    return copy_dispatch(first, last, dst, use_memmove());                       // may throw
}

// uninitialized_copy(I, I, O)

template <typename I, typename O>
inline
O uninitialized_copy_dispatch(I first, I last, O dst,
                              boost::mpl::bool_<true> const& /*use_memcpy*/)
{
    typedef typename boost::iterator_value<I>::type value_type;
    typename boost::iterator_difference<I>::type d = std::distance(first, last);

    ::memcpy(boost::addressof(*dst), boost::addressof(*first), sizeof(value_type) * d);
    return dst + d;
}

template <typename I, typename F>
inline
F uninitialized_copy_dispatch(I first, I last, F dst,
                              boost::mpl::bool_<false> const& /*use_memcpy*/)
{
    return std::uninitialized_copy(first, last, dst);                                       // may throw
}

template <typename I, typename F>
inline
F uninitialized_copy(I first, I last, F dst)
{
    typedef typename
    ::boost::mpl::and_<
        are_corresponding<I, F>,
        ::boost::has_trivial_copy<
            typename ::boost::iterator_value<F>::type
        >
    >::type
    use_memcpy;

    return uninitialized_copy_dispatch(first, last, dst, use_memcpy());          // may throw
}

// uninitialized_move(I, I, O)

template <typename I, typename O>
inline
O uninitialized_move_dispatch(I first, I last, O dst,
                              boost::mpl::bool_<true> const& /*use_memcpy*/)
{
    typedef typename boost::iterator_value<I>::type value_type;
    typename boost::iterator_difference<I>::type d = std::distance(first, last);

    ::memcpy(boost::addressof(*dst), boost::addressof(*first), sizeof(value_type) * d);
    return dst + d;
}

template <typename I, typename O>
inline
O uninitialized_move_dispatch(I first, I last, O dst,
                              boost::mpl::bool_<false> const& /*use_memcpy*/)
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
        destroy(dst, o);
        BOOST_RETHROW;
    }
    BOOST_CATCH_END

    return dst;
}

template <typename I, typename O>
inline
O uninitialized_move(I first, I last, O dst)
{
    typedef typename
    ::boost::mpl::and_<
        are_corresponding<I, O>,
        ::boost::has_trivial_copy<
            typename ::boost::iterator_value<O>::type
        >
    >::type
    use_memcpy;

    return uninitialized_move_dispatch(first, last, dst, use_memcpy());         // may throw
}

// TODO - move uses memmove - implement 2nd version using memcpy?

// move(I, I, O)

template <typename I, typename O>
inline
O move_dispatch(I first, I last, O dst,
                boost::mpl::bool_<true> const& /*use_memmove*/)
{
    typedef typename boost::iterator_value<I>::type value_type;
    typename boost::iterator_difference<I>::type d = std::distance(first, last);

    ::memmove(boost::addressof(*dst), boost::addressof(*first), sizeof(value_type) * d);
    return dst + d;
}

template <typename I, typename O>
inline
O move_dispatch(I first, I last, O dst,
                boost::mpl::bool_<false> const& /*use_memmove*/)
{
    return boost::move(first, last, dst);                                         // may throw
}

template <typename I, typename O>
inline
O move(I first, I last, O dst)
{
    typedef typename
    ::boost::mpl::and_<
        are_corresponding<I, O>,
        ::boost::has_trivial_assign<
            typename ::boost::iterator_value<O>::type
        >
    >::type
    use_memmove;

    return move_dispatch(first, last, dst, use_memmove());                      // may throw
}

// move_backward(BDI, BDI, BDO)

template <typename BDI, typename BDO>
inline
BDO move_backward_dispatch(BDI first, BDI last, BDO dst,
                           boost::mpl::bool_<true> const& /*use_memmove*/)
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
                           boost::mpl::bool_<false> const& /*use_memmove*/)
{
    return boost::move_backward(first, last, dst);                                // may throw
}

template <typename BDI, typename BDO>
inline
BDO move_backward(BDI first, BDI last, BDO dst)
{
    typedef typename
    ::boost::mpl::and_<
        are_corresponding<BDI, BDO>,
        ::boost::has_trivial_assign<
            typename ::boost::iterator_value<BDO>::type
        >
    >::type
    use_memmove;

    return move_backward_dispatch(first, last, dst, use_memmove());             // may throw
}

template <typename T>
struct has_nothrow_move : public
    ::boost::mpl::or_<
        boost::mpl::bool_<
            ::boost::has_nothrow_move<
                typename ::boost::remove_const<T>::type
            >::value
        >,
        boost::mpl::bool_<
            ::boost::has_nothrow_move<T>::value
        >
    >
{};

// uninitialized_move_if_noexcept(I, I, O)

template <typename I, typename O>
inline
O uninitialized_move_if_noexcept_dispatch(I first, I last, O dst, boost::mpl::bool_<true> const& /*use_move*/)
{ return varray_detail::uninitialized_move(first, last, dst); }

template <typename I, typename O>
inline
O uninitialized_move_if_noexcept_dispatch(I first, I last, O dst, boost::mpl::bool_<false> const& /*use_move*/)
{ return varray_detail::uninitialized_copy(first, last, dst); }

template <typename I, typename O>
inline
O uninitialized_move_if_noexcept(I first, I last, O dst)
{
    typedef typename has_nothrow_move<
        typename ::boost::iterator_value<O>::type
    >::type use_move;

    return uninitialized_move_if_noexcept_dispatch(first, last, dst, use_move());         // may throw
}

// move_if_noexcept(I, I, O)

template <typename I, typename O>
inline
O move_if_noexcept_dispatch(I first, I last, O dst, boost::mpl::bool_<true> const& /*use_move*/)
{ return move(first, last, dst); }

template <typename I, typename O>
inline
O move_if_noexcept_dispatch(I first, I last, O dst, boost::mpl::bool_<false> const& /*use_move*/)
{ return copy(first, last, dst); }

template <typename I, typename O>
inline
O move_if_noexcept(I first, I last, O dst)
{
    typedef typename has_nothrow_move<
        typename ::boost::iterator_value<O>::type
    >::type use_move;

    return move_if_noexcept_dispatch(first, last, dst, use_move());         // may throw
}

// uninitialized_fill(I, I)

template <typename I>
inline
void uninitialized_fill_dispatch(I /*first*/, I /*last*/,
                                 boost::true_type const& /*has_trivial_constructor*/,
                                 boost::true_type const& /*disable_trivial_init*/)
{}

template <typename I>
inline
void uninitialized_fill_dispatch(I first, I last,
                                 boost::true_type const& /*has_trivial_constructor*/,
                                 boost::false_type const& /*disable_trivial_init*/)
{
    typedef typename boost::iterator_value<I>::type value_type;
    for ( ; first != last ; ++first )
        new (boost::addressof(*first)) value_type();
}

template <typename I, typename DisableTrivialInit>
inline
void uninitialized_fill_dispatch(I first, I last,
                                 boost::false_type const& /*has_trivial_constructor*/,
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
        destroy(first, it);
        BOOST_RETHROW;
    }
    BOOST_CATCH_END
}

template <typename I, typename DisableTrivialInit>
inline
void uninitialized_fill(I first, I last, DisableTrivialInit const& disable_trivial_init)
{
    typedef typename boost::iterator_value<I>::type value_type;
    uninitialized_fill_dispatch(first, last, boost::has_trivial_constructor<value_type>(), disable_trivial_init);     // may throw
}

// construct(I)

template <typename I>
inline
void construct_dispatch(boost::mpl::bool_<true> const& /*dont_init*/, I /*pos*/)
{}

template <typename I>
inline
void construct_dispatch(boost::mpl::bool_<false> const& /*dont_init*/, I pos)
{
    typedef typename ::boost::iterator_value<I>::type value_type;
    new (static_cast<void*>(::boost::addressof(*pos))) value_type();                      // may throw
}

template <typename DisableTrivialInit, typename I>
inline
void construct(DisableTrivialInit const&, I pos)
{
    typedef typename ::boost::iterator_value<I>::type value_type;
    typedef typename ::boost::mpl::and_<
        boost::has_trivial_constructor<value_type>,
        DisableTrivialInit
    >::type dont_init;

    construct_dispatch(dont_init(), pos);                                                // may throw
}

// construct(I, V)

template <typename I, typename V>
inline
void construct_copy_dispatch(I pos, V const& v,
                             boost::mpl::bool_<true> const& /*use_memcpy*/)
{
    ::memcpy(boost::addressof(*pos), boost::addressof(v), sizeof(V));
}

template <typename I, typename P>
inline
void construct_copy_dispatch(I pos, P const& p,
                             boost::mpl::bool_<false> const& /*use_memcpy*/)
{
    typedef typename boost::iterator_value<I>::type V;
    new (static_cast<void*>(boost::addressof(*pos))) V(p);                      // may throw
}

template <typename DisableTrivialInit, typename I, typename P>
inline
void construct(DisableTrivialInit const&,
               I pos, P const& p)
{
    typedef typename
    ::boost::mpl::and_<
        is_corresponding_value<I, P>,
        ::boost::has_trivial_copy<P>
    >::type
    use_memcpy;

    construct_copy_dispatch(pos, p, use_memcpy());                              // may throw
}

// Needed by push_back(V &&)

template <typename I, typename V>
inline
void construct_move_dispatch(I pos, V const& v,
                             boost::mpl::bool_<true> const& /*use_memcpy*/)
{
    ::memcpy(boost::addressof(*pos), boost::addressof(v), sizeof(V));
}

template <typename I, typename P>
inline
void construct_move_dispatch(I pos, BOOST_RV_REF(P) p,
                             boost::mpl::bool_<false> const& /*use_memcpy*/)
{
    typedef typename boost::iterator_value<I>::type V;
    new (static_cast<void*>(boost::addressof(*pos))) V(::boost::move(p));       // may throw
}

template <typename DisableTrivialInit, typename I, typename P>
inline
void construct(DisableTrivialInit const&, I pos, BOOST_RV_REF(P) p)
{
    typedef typename
    ::boost::mpl::and_<
        is_corresponding_value<I, P>,
        ::boost::has_trivial_move_constructor<P>
    >::type
    use_memcpy;

    construct_move_dispatch(pos, ::boost::move(p), use_memcpy());               // may throw
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
                          boost::mpl::bool_<true> const& /*use_memcpy*/)
{
// TODO - use memmove here?
    ::memcpy(boost::addressof(*pos), boost::addressof(v), sizeof(V));
}

template <typename I, typename V>
inline
void assign_copy_dispatch(I pos, V const& v,
                          boost::mpl::bool_<false> const& /*use_memcpy*/)
{
    *pos = v;                                                                   // may throw
}

template <typename I, typename V>
inline
void assign(I pos, V const& v)
{
    typedef typename
    ::boost::mpl::and_<
        is_corresponding_value<I, V>,
        ::boost::has_trivial_assign<V>
    >::type
    use_memcpy;

    assign_copy_dispatch(pos, v, use_memcpy());                                   // may throw
}

template <typename I, typename V>
inline
void assign_move_dispatch(I pos, V const& v,
                          boost::mpl::bool_<true> const& /*use_memcpy*/)
{
// TODO - use memmove here?
    ::memcpy(boost::addressof(*pos), boost::addressof(v), sizeof(V));
}

template <typename I, typename V>
inline
void assign_move_dispatch(I pos, BOOST_RV_REF(V) v,
                          boost::mpl::bool_<false> const& /*use_memcpy*/)
{
    *pos = boost::move(v);                                                        // may throw
}

template <typename I, typename V>
inline
void assign(I pos, BOOST_RV_REF(V) v)
{
    typedef typename
    ::boost::mpl::and_<
        is_corresponding_value<I, V>,
        ::boost::has_trivial_move_assign<V>
    >::type
    use_memcpy;

    assign_move_dispatch(pos, ::boost::move(v), use_memcpy());
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
        destroy(dest, it);
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
            destroy(m_ptr);
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