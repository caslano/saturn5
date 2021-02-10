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
lQfXcrEkFbhzGsO+PoxoiGWLZZPgDDwLxJQGbRH5fAb7M/Nkl34vARSkYWEkgYLPcNA4LmlnJjzyxAorUVFl2abFqFIsTNuMer8lqFHXcBLxGzj74qRTQpsDU6QFj94GultRD0i6xIikP6I+qWcR9pTEBGCJqzfSCFBzbH0s+Cn1YMpwpHARV2EyZxGsmBkxWhZ1XV3E2gh4//Zgik2pbhdMk7jYG9PbBZWp2UYHhintO9StewmHlApuqyb8hQRP+oPDpsmuNe7/3B32SPtydEGGvR5x4PQzfLRR93lr0Lnowlx7eozPTvu8NYJ9pQNP8rhjDE21EkzKksUKK673kShBDJllpVmyc3Ibww2pSORsx4wq1sMHa1tqBXr9iy4ZdVsd0nKcUf/fl053XCk9vEcsQzxG61IWXEKFk8mo73T1Cnv4KlB2uhddp2s/pmZweXFRgeHX7oB0/9sfO2Y91Cvm3D7OCuyGYIW4AgMds7teGSLuW6n7P3yG/uCn1kW/Q9JIE3y47Nrweym3Szcv+OrYHCDjGVM6WI5uAiOkkhmVfu75ys7Zt8o9yw022WewNue2r6re6kKsOpgFLbTgOK70e5TnWOA5qQ0nJ3DYNOnMrNtoOYFNOZG21Wi8f/v27YfD9/X8KpgJgJM/
*/