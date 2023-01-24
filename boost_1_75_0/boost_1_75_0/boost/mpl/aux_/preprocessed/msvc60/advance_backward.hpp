
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/aux_/advance_backward.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl { namespace aux {

template< long N > struct advance_backward;
template<>
struct advance_backward<0>
{
    template< typename Iterator > struct apply
    {
        typedef Iterator iter0;
        typedef iter0 type;
    };

    /// ETI workaround
    template<> struct apply<int>
    {
        typedef int type;
    };

};

template<>
struct advance_backward<1>
{
    template< typename Iterator > struct apply
    {
        typedef Iterator iter0;
        typedef typename prior<iter0>::type iter1;
        typedef iter1 type;
    };

    /// ETI workaround
    template<> struct apply<int>
    {
        typedef int type;
    };

};

template<>
struct advance_backward<2>
{
    template< typename Iterator > struct apply
    {
        typedef Iterator iter0;
        typedef typename prior<iter0>::type iter1;
        typedef typename prior<iter1>::type iter2;
        typedef iter2 type;
    };

    /// ETI workaround
    template<> struct apply<int>
    {
        typedef int type;
    };

};

template<>
struct advance_backward<3>
{
    template< typename Iterator > struct apply
    {
        typedef Iterator iter0;
        typedef typename prior<iter0>::type iter1;
        typedef typename prior<iter1>::type iter2;
        typedef typename prior<iter2>::type iter3;
        typedef iter3 type;
    };

    /// ETI workaround
    template<> struct apply<int>
    {
        typedef int type;
    };

};

template<>
struct advance_backward<4>
{
    template< typename Iterator > struct apply
    {
        typedef Iterator iter0;
        typedef typename prior<iter0>::type iter1;
        typedef typename prior<iter1>::type iter2;
        typedef typename prior<iter2>::type iter3;
        typedef typename prior<iter3>::type iter4;
        typedef iter4 type;
    };

    /// ETI workaround
    template<> struct apply<int>
    {
        typedef int type;
    };

};

template< long N >
struct advance_backward
{
    template< typename Iterator > struct apply
    {
        typedef typename apply_wrap1<
              advance_backward<4>
            , Iterator
            >::type chunk_result_;

        typedef typename apply_wrap1<
              advance_backward<(
                (N - 4) < 0
                    ? 0
                    : N - 4
                    )>
            , chunk_result_
            >::type type;
    };
};

}}}


/* advance_backward.hpp
OR6JeSW9cTkoA/zUbZAH+7sCRyLKbEMWSXDs9p5hhksLYvrCU4CsXOViKRu3Yv3XE30ZWMoYAuIUaMofnGJGyxyRmkp/HLBWe7cmoZzZWbw1VXbMRp0LJNo+BbwK7EkItMj86qgAJnNHkyU3PwTF7O+OJ/OgohWT5YVDkTlrV92OBsGeXzIKJ0UGXryw7xxvtnFzu6Zn1OW+G0d5502nBcDVJ9s/d3UZQTyegO+ncwImbuvoy167vIAYf756Xfos9FlQCJZHvHZbpUoAH6K8ukrnQL1k7SYBELl04GIEOmTnt9FO28hL5AMqjBdUuV33zJs6PKI6PvtiRv7TH9qGiz+jkQOV3TGATgWrBS+UN7HKZfRNiQNnnXiRRKd0aFfWYYSJyR6fvhEGAYjZSn8/NYRp0/+5Ap8On46oCVdLbwGugquCt4Oj6Nf9gmdMvovcHxdkKbKM3M2H4Ihgj7CJYQ1vj9xsl7vWX+bSeeeLsi0U5U9atBVE8YWtv2rjLZ4D1lfiX6gCNj7RHt4kJZWVkg/k/xCFSUlGyeXfIOPKfca3H6oJ+IwTL+mL8nQaIxkxqL/qNDIqz8wRcGx39R6bVirEEgCgmc+R0d4zmwgjFrPOl4VkFf65wIni2PZdnpmM/P578Se7V2WG5OGTYrOGcmIFDIju0ITKBxrVQp9Z5cITbL0jYyrLOOzuBbIdStnYoPAw/BgGTRTISr/o
*/