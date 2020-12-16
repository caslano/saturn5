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
5yUMYT3yMvkPlrxUi+Ua6TzM0GuMxil3d8kZyKa/BD1W/+J19Pyznus9TLWDLOX2Sq8xftlAPo2gMEMIn4UybcND/WuUQ821LeIuB3c/Gu6arYww3Ryr4mY9br5XbspPuLmpxE3DZrhpWH7Y7Vlv+t286+bmGG4e9LnZZbrZGOVz00rcdIuknhr1YEK9esHx9YKC21MJ6svdAXrdn3Xdza4o4oifh1GPoJ5A/yh8Bm6HISj8aLU7yke1DrAW67l9dSZD9HptsUWujGlqlysR1I/0/Zb6kZ1Vmhx4gLbbe4T4i661XHB7Vzsk8WognuqjoohXuVO8SvMKs7l5qLDYNV7ir8FJx8uUTaVR9ng1I14VDvFihJKRX40MrqhjnFz6VtqAPvNKyhJFnDY7xEleydUbuUteib/mtY5XlbzS96htk3hF+ED4xJF47XKIF6sAy4pzSy/iFia5l8c1fuI/4qTjp/tUqfShAfN4McTvkC1+qupLDXONl/gLPel4mXXs7Wj7u30s8Tpqi5fMv5W4xkn5OZX3erMslze31/s44uR5wxanzKxFGWV5pWnm4e8LqplDwf+ptYFJEr+kGHv84olfZC3ip4+zr26u5xTjaZbtkRj7ODiReCbZ46lbQiNdtnovh7iPdtuXgr11/PpcLcav0k9IHShx25Oi01IeK3ntAzY8g7Sk2tIis2nu9VT81K91/lapp3p+skWcPU5bMUu3x+nCslz+L8kpK80sXFZQTbtOP8W4mW3o6Ti7PGxNfhXZ46bFob46wT1++D81eWjm3ex4M14ifyTvKqqJX17W0qw897jht27vCW6y+qjELUQ8BaOSyLtKe9zUPgY29hRmurdn8RdS63gRhmOerU+wy502mO2yx8u4MGlRQIm69291lDVueZacaJM1qjz3u8YtM6uoNMctXvizzgvsrYVMkXdi1zjuS3Rur54/usRRXnJc4oi/09NWj8gFlwmSd4ZhezSR1njlFWZkSsT4e2FGzd8MlH/2fej158OHyjU0MndhukmwuCnKoGD0dyDtRpfF4DqURWBdjrHs9ZS4iHmKNpfnV3m3PNjKF/gzNMY4YQfj3dKaRwVZyzx6z53Xf18f+SFuqaFtzTtflH5z8Dn8fy3qGOpm3jPXB3slT/333LSVd9TJys9twV2YW1uNOoK6xhvm+RUThcY73FHK8mkawbf4DW+4KrXqfgnTzSHcvNxMvXf+zXTz2yirmxDSfDVm4aGrXjXd1JdwFqOPl3f7PMJ5SvZLXBelqNQDmN8InxKzG1Av8PeDqFewa4F6FdVG1Guor7B7rKlf/aFW8wbMDf/JyBe19663qjuYNfCb6bmFb1UZS7kwn3qpz42nd4LssZDyzmttHy/3wc2htyzlXcKtlzQD13lU3NdtnOz23pMpL8HnoprJt9mzjXFylfjY3xGd73uq9xfDX6LEU8KRvb+PKfeEUSLtVNvH671/Df9iGXPxLl/zu3p1c4aPKTP1TIts6tfGPo4415gf+4st3c7vVc7lIv4jAr5jZWGt04t93cYZtjk/PXdPuFXGkuFt7X1Vf9KUbktTrxrfq/Gjx8b/iFTzekW41+lIr1JOr0ednOw0y4lnYMYzqtTP0na+ALai4lC/QQ0gTRW2NKVl5BUVGDfGlhaWuKZL/Pnvh31Y6dd5ivg/St+TKKEE3PX+oHJ3kSdX3wsrYZHqGLmL0fRn3AVp+o2F9yt3v/ZcKPv6crRf7ocl/4JlbutNY46zFvdZOc1nxljuZ9fx13ewEj8xl/hVGYMtb29vD0OMcfXbjvnMH3nsOeTFz7UOiV9pCy8re5zrOqTtbXdFSv+M/am3lZeVmXqu3A9pv+M=
*/