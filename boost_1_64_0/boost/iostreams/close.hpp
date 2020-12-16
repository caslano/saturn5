// (C) Copyright 2008 CodeRage, LLC (turkanis at coderage dot com)
// (C) Copyright 2003-2007 Jonathan Turkanis
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

#ifndef BOOST_IOSTREAMS_CLOSE_HPP_INCLUDED
#define BOOST_IOSTREAMS_CLOSE_HPP_INCLUDED

#if defined(_MSC_VER)
# pragma once
#endif

#include <boost/config.hpp>  // DEDUCED_TYPENAME, MSVC.
#include <boost/detail/workaround.hpp>
#include <boost/iostreams/categories.hpp>
#include <boost/iostreams/flush.hpp>
#include <boost/iostreams/detail/adapter/non_blocking_adapter.hpp>
#include <boost/iostreams/detail/ios.hpp> // BOOST_IOS
#include <boost/iostreams/detail/select.hpp>
#include <boost/iostreams/detail/wrap_unwrap.hpp>
#include <boost/iostreams/operations_fwd.hpp>
#include <boost/iostreams/traits.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/mpl/if.hpp>
#include <boost/type_traits/is_convertible.hpp>
#include <boost/type_traits/is_integral.hpp>
#include <boost/type_traits/remove_cv.hpp>
#include <boost/type_traits/remove_reference.hpp>

// Must come last.
#include <boost/iostreams/detail/config/disable_warnings.hpp>

namespace boost { namespace iostreams {

template<typename T>
void close(T& t);

template<typename T>
void close(T& t, BOOST_IOS::openmode which);

template<typename T, typename Sink>
void close(T& t, Sink& snk, BOOST_IOS::openmode which);
    
namespace detail {

template<typename T>
void close_all(T& t)
{ 
    try {
        boost::iostreams::close(t, BOOST_IOS::in);
    } catch (...) {
        try {
            boost::iostreams::close(t, BOOST_IOS::out);
        } catch (...) { }
        throw;
    }
    boost::iostreams::close(t, BOOST_IOS::out);
}

template<typename T, typename Sink>
void close_all(T& t, Sink& snk)
{ 
    try {
        boost::iostreams::close(t, snk, BOOST_IOS::in);
    } catch (...) {
        try {
            boost::iostreams::close(t, snk, BOOST_IOS::out);
        } catch (...) { }
        throw;
    }
    boost::iostreams::close(t, snk, BOOST_IOS::out);
}

} // End namespace detail. 

} } // End namespaces iostreams, boost.

namespace boost { namespace iostreams {

namespace detail {

template<typename T>
struct close_impl;

} // End namespace detail.

template<typename T>
void close(T& t) { detail::close_all(t); }

template<typename T>
void close(T& t, BOOST_IOS::openmode which)
{ 
#ifdef BOOST_IOSTREAMS_STRICT
    BOOST_ASSERT(which == BOOST_IOS::in || which == BOOST_IOS::out);
#else
    if (which == (BOOST_IOS::in | BOOST_IOS::out)) {
        detail::close_all(t);
        return;
    }
#endif
    detail::close_impl<T>::close(detail::unwrap(t), which); 
}

template<typename T, typename Sink>
void close(T& t, Sink& snk, BOOST_IOS::openmode which)
{ 
#ifdef BOOST_IOSTREAMS_STRICT
    BOOST_ASSERT(which == BOOST_IOS::in || which == BOOST_IOS::out);
#else
    if (which == (BOOST_IOS::in | BOOST_IOS::out)) {
        detail::close_all(t, snk);
        return;
    }
#endif
    detail::close_impl<T>::close(detail::unwrap(t), snk, which); 
}

namespace detail {

//------------------Definition of close_impl----------------------------------//

struct close_boost_stream { };
struct close_filtering_stream { };

template<typename T>
struct close_tag {
    typedef typename category_of<T>::type             category;
    typedef typename detail::unwrapped_type<T>::type  unwrapped;
    typedef typename
            iostreams::select<
                mpl::not_< is_convertible<category, closable_tag> >,
                any_tag,
                mpl::or_<
                    is_boost_stream<unwrapped>,
                    is_boost_stream_buffer<unwrapped>
                >,
                close_boost_stream,
                mpl::or_<
                    is_filtering_stream<unwrapped>,
                    is_filtering_streambuf<unwrapped>
                >,
                close_filtering_stream,
                mpl::or_<
                    is_convertible<category, two_sequence>,
                    is_convertible<category, dual_use>
                >,
                two_sequence,
                else_,
                closable_tag
            >::type type;
};

template<typename T>
struct close_impl
    : mpl::if_<
          is_custom<T>,
          operations<T>,
          close_impl<BOOST_DEDUCED_TYPENAME close_tag<T>::type>
      >::type
    { };

template<>
struct close_impl<any_tag> {
    template<typename T>
    static void close(T& t, BOOST_IOS::openmode which)
    {
        if (which == BOOST_IOS::out)
            iostreams::flush(t);
    }

    template<typename T, typename Sink>
    static void close(T& t, Sink& snk, BOOST_IOS::openmode which)
    {
        if (which == BOOST_IOS::out) {
            non_blocking_adapter<Sink> nb(snk);
            iostreams::flush(t, nb);
        }
    }
};

template<>
struct close_impl<close_boost_stream> {
    template<typename T>
    static void close(T& t)
    {
        t.close();
    }
    template<typename T>
    static void close(T& t, BOOST_IOS::openmode which)
    {
        if (which == BOOST_IOS::out)
            t.close();
    }
};

template<>
struct close_impl<close_filtering_stream> {
    template<typename T>
    static void close(T& t, BOOST_IOS::openmode which)
    {
        typedef typename category_of<T>::type category;
        const bool in =  is_convertible<category, input>::value &&
                        !is_convertible<category, output>::value;
        if (in == (which == BOOST_IOS::in) && t.is_complete())
            t.pop();
    }
};

template<>
struct close_impl<closable_tag> {
    template<typename T>
    static void close(T& t, BOOST_IOS::openmode which)
    {
        typedef typename category_of<T>::type category;
        const bool in =  is_convertible<category, input>::value &&
                        !is_convertible<category, output>::value;
        if (in == (which == BOOST_IOS::in))
            t.close();
    }
    template<typename T, typename Sink>
    static void close(T& t, Sink& snk, BOOST_IOS::openmode which)
    {
        typedef typename category_of<T>::type category;
        const bool in =  is_convertible<category, input>::value &&
                        !is_convertible<category, output>::value;
        if (in == (which == BOOST_IOS::in)) {
            non_blocking_adapter<Sink> nb(snk);
            t.close(nb);
        }
    }
};

template<>
struct close_impl<two_sequence> {
    template<typename T>
    static void close(T& t, BOOST_IOS::openmode which) { t.close(which); }
    template<typename T, typename Sink>
    static void close(T& t, Sink& snk, BOOST_IOS::openmode which)
    {
        non_blocking_adapter<Sink> nb(snk);
        t.close(nb, which);
    }
};

} // End namespace detail.

} } // End namespaces iostreams, boost.

#include <boost/iostreams/detail/config/enable_warnings.hpp>

#endif // #ifndef BOOST_IOSTREAMS_CLOSE_HPP_INCLUDED

/* close.hpp
fQP6VtNW1mh0Pr4Bnd/wajidzwzR+aEN6PycEDuHuSF2DsuC6sQe2k7ZAPKAXjXJrBMbgusE9uPAkGJonRiia4Ph19FGOuuAlq/MWQe0fJO1dYB82jr7sLjdoq8TGxpuq58RntlKfRhn14cycXsB6yzcDr216sOVwvOc8Qyk3BO61Sykn/1ap0cR2JAzdaf1xnC6MyREd2aH6E5ZiO5MdtjIVPvpg83xT92nxjGRf2OwrpQZEejIxgjbyY0R2skin12PIzhjpX5ZsZ6FkcXgFoGAvkRk3YHbgfdBFuUhspgTJIsSw0d9fED4ql3mOUgrXdqzkBiWy2En2EedWiXuT7u6Gkk4iyNJJz+EobcP7KNeLxX3TS7sF8V61JZa2TKM4LOLDOX8I+q82I5lW70fzx8VfxtdCdzfhVF0iUH3Wri3fE3OJnGFnJ9k16u3xP9cVxM8GYtybWXIGUW0T+08q4jnFfG5bctadbNtgvZODehHuq0SDdun7bIpXD0r4R4Sp73a+CB7tZqzjIxgG4BtE5x1bIO5b86Mm+c7mAZt52YPyZ45Ky87M4K6VrcpsvcP8tl16LtjrkOZQXm7u2XAo+QZNJV5M14PzdtQTd6G6vIGv5HlTeWjrtrvBZ3FbZC1t8ixb9Ir7tnGOWi7JyHl9fUTrYV3FO/RU8m9l/Zpj7b53wN/Dansk/a+4f2Wpv6d/3o4/RvqkLtqn3wjQ76c77IF5jOzrToqd9hAmTIjW16HxS5tbnHuTHVsarcXN4qfPCNLJOLSt1vOMrHfUW4TtwnGcHDqykn1WyapLrD70MXiNhr6FGPb8Pu7DxRRP6nKa1q9errM/E/95Jn/xnVdEObmBEOxr4qDDHLLCgOmIh22DC15pYqfHKM5/o/Vy4vh6vPcRdxG4qSiJg3qiNPuqLonl4soQ2xgvoB8VWy2911LnzXDCH3voV3GzfXYod8cmd3Lis2N6qexx7yh8fC0oDxWcdGaD4GfADzCMUpVSB7nBI1j59h91i7hO2Tr67tyPxVn/CfrbWo48j3X3kf8hrj9Feu/NOcTav0etYW8VdyKsNaslbZPpl+lzYLphkzD1pvvxH09fKfgmdJv55eAvZ6+m33zF+J/j8G+++h7GNM3dIu8axm0CS/97D9MYt/8AxAkffGtSVa/2/g+94Et4dq8OSF6MNcxXvOF9LXMu72Pc2LYfZyN3695z0rz+dpXv7n8SJcrtz04+/Z7n0n5V8vofs3/5/2a1G2ZYxjJdf+B/RWcw+X88siQ/RW/4/rKB4AdgQ8BzwU+zPWTK7iu/xHgr4CPArOBK4E5wErgFN6b8VVY85GcYzXjawlawPgmgK8F8GKgD3gp8AKu8ywGTgO+Yaab6yQLgNuAhVwvORO4H1gE/ILrPL/lOs8jwCu4fnUSMAaIe+6f5DwT8A6mS90/uYrrS5/g+tLVwGnc17AE+DzX2/4RWAN8iel4BfgD9zGkINwNwB7A17g+dhPXwb4OvBC4GTgO+BbwEuDbwMnAd4DTge8CrwDWAK8Bvge8Afg+8Fbg08DfmvfM1xJrToHzKiOpC4uYrwGmPIADgU2BZ3D/yFks12HAAuAIMz6uF17A9cLLuF7498DRXP+ayfXRF1AeWcAXgRdy3esg4Ku85/5Ovi/j/YLpU/d3ZlD/+ir5KSf/ly5nfkq5L2MOsDfX5w4HXgMcw3W544FLqJflXPe9EHgawruV65R/A5wGvB14O/BO4ArgPcDngIuBLwHvBW4GLlHyU7cpfH6+YH4OkX+O/T4A3SZ/vOgzLu47Mf3v4P6TXcDjgR9x/08t1zl/CjwfuB84juvZJ3H9ei7wc+Z3N3Aq7639SOWM/3I=
*/