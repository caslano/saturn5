//  boost lockfree: copy_payload helper
//
//  Copyright (C) 2011, 2016 Tim Blechmann
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_LOCKFREE_DETAIL_COPY_PAYLOAD_HPP_INCLUDED
#define BOOST_LOCKFREE_DETAIL_COPY_PAYLOAD_HPP_INCLUDED

#include <boost/mpl/if.hpp>
#include <boost/type_traits/is_convertible.hpp>

#if defined(_MSC_VER)
#pragma warning(push)
#pragma warning(disable: 4512) // assignment operator could not be generated
#endif

namespace boost    {
namespace lockfree {
namespace detail   {

struct copy_convertible
{
    template <typename T, typename U>
    static void copy(T & t, U & u)
    {
        u = t;
    }
};

struct copy_constructible_and_copyable
{
    template <typename T, typename U>
    static void copy(T & t, U & u)
    {
        u = U(t);
    }
};

template <typename T, typename U>
void copy_payload(T & t, U & u)
{
    typedef typename boost::mpl::if_<typename boost::is_convertible<T, U>::type,
                                     copy_convertible,
                                     copy_constructible_and_copyable
                                    >::type copy_type;
    copy_type::copy(t, u);
}

template <typename T>
struct consume_via_copy
{
    consume_via_copy(T & out):
        out_(out)
    {}

    template <typename U>
    void operator()(U & element)
    {
        copy_payload(element, out_);
    }

    T & out_;
};

struct consume_noop
{
    template <typename U>
    void operator()(const U &)
    {
    }
};


}}}

#if defined(_MSC_VER)
#pragma warning(pop)
#endif

#endif  /* BOOST_LOCKFREE_DETAIL_COPY_PAYLOAD_HPP_INCLUDED */

/* copy_payload.hpp
aGNE7fUZ1qg1iNP5h4nV/jn9o58owMiKs0F39ewcLVe4O5RsJOtl4CbhvKN10NhSwgr+e8tC4qiZQczTtm37RGD/j08kSjfDk0mtraOJh1ZUvAUyDxGyus4b3e9vnbfzeOSoptfTiUVOcC1RjC3O85ViKaaUYokiKMpSQbrdL4Crd38t5ri0bLuqZlKFxEnAXb2PjuQ85q9MpiemmHuOITzrqRCXqc2X66Xq27fJ7RcX1eeHmraEVLJ5qslAX4/HIXbrI3/Z500UKovUVbKeQaalbre7TYjL25Uqc/pQ4+LmTomIxm0UAhhbHYydRg4RKDF9MYmX8MpYEw53jtsPgvoVX+zzVnj9sKOwrADcPmvwm/C/9S8gKctoXoj2OL3spwgcSgkLcZQDjCioKCAlsjcKD1X0Yj/83wkt71ZUin5/NEb0XbKgB6IwJYkgRC96zLqScIQi2dKgFl0T+JJA8jl/K7niHL/9IRcb65q3n1uUHYigG3LXqkSfRt0RhCohJDE6PYATtNdFrda2vctoYEBBVAW6BysG85in9sHrM5fxWWvv/wTfx3eU18Xgdmx9f5l9TBfvdjeTI1BbDp7749x4Sbq9jNZTbpjIgJaDYnUSWq1YiiUo/XF+K/j8ChsL6e0P2TfBPU2LulQOt86PflJSof7bGjoTSN/b8jWgjgXbVNkWe1O5X3PfHr0uDMMnux1zvgeh1PshbUtk
*/