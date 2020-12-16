
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/greater_equal.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct greater_equal_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< greater_equal_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< greater_equal_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct greater_equal_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template<> struct greater_equal_impl< na,integral_c_tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template<> struct greater_equal_impl< integral_c_tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct greater_equal_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct greater_equal

    : greater_equal_impl<
          typename greater_equal_tag<N1>::type
        , typename greater_equal_tag<N2>::type
        >::template apply< N1,N2 >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, greater_equal, (N1, N2))

};

BOOST_MPL_AUX_NA_SPEC2(2, 2, greater_equal)

}}

namespace boost { namespace mpl {

template<>
struct greater_equal_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply

        : bool_< ( BOOST_MPL_AUX_VALUE_WKND(N1)::value >= BOOST_MPL_AUX_VALUE_WKND(N2)::value ) >
    {
    };
};

}}

/* greater_equal.hpp
w9zYYjf9/9Jf5f/34Y/8I97/t/z/lo9q8QGGf98qHM90kdcT+fuZMX8PFFX4Qv76FsNfH9A7/Ldqvu9G+RZzBpnvsOJLTmCO3uk9VX3XCH90IS7i2mp93yiif4p84XnQ0j8ODrfWENjW1F9sOeCC+ru28Q2ynbYjH4e0KlDG7KY3ZJP8eGEf3gr5iYMOQm9Ftcew1bK9gs87FQWq+F1+nw4hu7Ziu+PglXOY32j/En+oTtac9lH6+y5dNa+sej6sep6jdj5DvveuQ+zrFZRVVNcEEvJXmr53U9fg1Z11Ncfo8hXVBNr+dl9ruhqka450HY2MGMjv29t18U24BGIYovpQG7qzUpx1Tx1q1+2vLp3xx+puUEHHSfdcnTdddzB00+WnV80oTcSnl8y5E6l/R9v302RDo2kDzgNyl7XHBvO7ZBWGn8CME3hV84wvIztZ5+0wM5akxJ+IH627odea0I98I01rb9RUl0T5TUbL/+/T9wvLFaeTv2NQt3nRK/LKT9E5iXr3NGJGSqoqy1jdItDaNcL0XSyTbUN0TAaF12MdEWObvuvX9nFJRO9oxQq8K73N6gv+GL3qlO3oD452uOsOuOsOtGPdgfqgr6T/oV0Ov6dL8e33TpxzTt29I4ck7ytJ1kfT2roDizwa98BbHd4vf0lzki/DdM1R9tYc5SD4GhwC34Bj4ZuwEDbDEvg2rNZc5mzNZZ6tucwLNZfZAD+EN8KPwnORHTQe0jgJu4LzcFkau/XRnNoGMF0+hd5wI821Z8AdYH9YBjeGR8nHMFc+hcUwE54Ht4C3wwFwOdwSPirfwvNwEHwdbgvfgYPhp3AI/BluD1fDth1gChwG0+BI2B/uBDNhDsyGo+F4mAunwjFwGhwLD4V5MJU67w47wT1gFzgR9oF7wW1hARwDJ8FxcJ/IXL/GWRoTZdrm+ufruB4vn9NCOEm+oX3hIlguH9Yh8mEdKh/WPHi65qbPgIjnTBjW2xxXL79J7/nSe4H0LpHei6V3qfReIr2XSu8V0nul9F4lvXUejb/gHOlVbFUwXSe9DerH16sf36B+fKP68c1wNLwFToC3wr3g7bAYLoN+eDecBe+BR8NGw46pQ+Pbcb/sWC47HpAdD8qOh2THI7LjUdnxmOx4QnY0yY5nZMezsuM52THTo3EZPE52dIY+2fGZ7PhcdnwhO1pkx5ey42vZ8Q0sgN9CH/wO1sAVOq9/gHPhj9KfjzRK/97SvyYcHfax6vydAtPgAXBreKDO36ny7RXBibAYUi73SI234KsqNx1erXJ/kY/hV9XvN7g+7ED+TWEK3Ea+mRHyeY2HneEkuA4sguvC6fKFHQa76rrRDZ4Mu+u6kSafVzq8WT6xe2FPzemvB1+GvWQ/1JiNY6FvRWUE9WsMJbu313EZKh/NMNgP7qjjMhyOgCNhLtwJ7glz1A9GwflwZ7gA7gIXwdHwEpgLr4Zj4c1wPLwb7gqfhbvBV+AE+A7c3VhP5Ue4F/wZToLdsH1vuBncBw6A+8IhcD+4MyyEe8JiuC8sgSXQC8thaaTfaNwIhzj0m83VPpnyeQ9Q+2wpn1QWzIZbqR8PVLmNiF/lvqtye8CbVG65yj0YpkEfzITT5UP3w+3hIWrvapgPa+DeMAAPhjM88k3CmfBweCw8Qu0/C14Aj4JXwqPhLbCO/+6Fx8An4Gz4KpwDm2E9fDxq3RKEf89EWvXtzMK3M8v9Xo67jom7jkl71zHxPZuS0Fom587Cf4o8h3yDpB/J92+QAsSPLEQuRx5GPj3S9T24yU1ucpOb3OQmN7npr0kpyEF/if+/eJXf/bfeYxw1kPnKoG9f7qPCmgCvm3r6653FhXqPEfc=
*/