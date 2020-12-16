
// Copyright Aleksey Gurtovoy 2001-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// *Preprocessed* version of the main "inherit.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename BOOST_MPL_AUX_NA_PARAM(T1)
    , typename BOOST_MPL_AUX_NA_PARAM(T2)
    >
struct inherit2
    : T1, T2
{
    typedef inherit2 type;
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, inherit2, (T1, T2))
};

template< typename T1 >
struct inherit2< T1,empty_base >
{
    typedef T1 type;
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(2, inherit2, (T1, empty_base))
};

template< typename T2 >
struct inherit2< empty_base,T2 >
{
    typedef T2 type;
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(2, inherit2, (empty_base, T2))
};

template<>
struct inherit2< empty_base,empty_base >
{
    typedef empty_base type;
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(2, inherit2, (empty_base, empty_base))
};

BOOST_MPL_AUX_NA_SPEC(2, inherit2)

template<
      typename T1 = na, typename T2 = na, typename T3 = na
    >
struct inherit3
    : inherit2<
          typename inherit2<
              T1, T2
            >::type
        , T3
        >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          3
        , inherit3
        , ( T1, T2, T3)
        )
};

BOOST_MPL_AUX_NA_SPEC(3, inherit3)

template<
      typename T1 = na, typename T2 = na, typename T3 = na, typename T4 = na
    >
struct inherit4
    : inherit2<
          typename inherit3<
              T1, T2, T3
            >::type
        , T4
        >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          4
        , inherit4
        , ( T1, T2, T3, T4)
        )
};

BOOST_MPL_AUX_NA_SPEC(4, inherit4)

template<
      typename T1 = na, typename T2 = na, typename T3 = na, typename T4 = na
    , typename T5 = na
    >
struct inherit5
    : inherit2<
          typename inherit4<
              T1, T2, T3, T4
            >::type
        , T5
        >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          5
        , inherit5
        , ( T1, T2, T3, T4, T5)
        )
};

BOOST_MPL_AUX_NA_SPEC(5, inherit5)

/// primary template

template<
      typename T1 = empty_base, typename T2 = empty_base
    , typename T3 = empty_base, typename T4 = empty_base
    , typename T5 = empty_base
    >
struct inherit
    : inherit5< T1,T2,T3,T4,T5 >
{
};

template<>
struct inherit< na,na,na,na,na >
{
    template<

          typename T1, typename T2, typename T3, typename T4, typename T5

        >
    struct apply
        : inherit< T1,T2,T3,T4,T5 >
    {
    };
};

BOOST_MPL_AUX_NA_SPEC_LAMBDA(5, inherit)
BOOST_MPL_AUX_NA_SPEC_ARITY(5, inherit)
BOOST_MPL_AUX_NA_SPEC_TEMPLATE_ARITY(5, 5, inherit)
}}


/* inherit.hpp
g3vBQwgNFqgfiw5gCkLXYerzsgD/nodQ4dtiLf69DWE7/rYS3/cvUH+YwYW2P8wG+HeLheoXsy+YgtAJ/85aGINPDNyzAmEtwhMIuxD2L7R9ZQQXqb+MFiB9Zhifm13lOpgCtsK1AnAFQpMk9cXZkz41nsC1nQgDRqh/zr2L3D421tt+NsymciJCEkIKgtPvRim+l+P7OnAzQu1k9cOxA//eK9/F7wbY5Krofjk6Jbt9c7TCvSnJnj46jM/QIfj7Rvy96KpIfx0Lce1mhAq/HZvx750I+xHqLFY/Hi3ArAvwd9yTgjBgcdV+Pcro26NosfokXbFY/XysA59ASEnBPeDBxbbfjyZL1PdHEpiBEO4DZAw4D9cLwJvBQym4H9yLIH5BgkttX6dN8O+eCB1wPQtcjDAG/9641PYbsn2p+kQtW2r7EDmI7wfwvfEylDHCAIQshIUI6xF2IexHqLUcZYIwACEDoRThZoStCPsQglejPBGSEMYhzENYi7AVYQ/CQYTG10A+hCEIRQgrENYj7EAoR2hwLf6OMAZhJsJKhM0IuxEOINRZgbpHGIFQgLACYT3CDoRyhNrXoV0g9EXIQChFqPnUfGo+NZ+az3/3J4gw6Ve3/58+9ZKCovwxJXidY1r7MdPa47VNcQLwK/gA6NoQ+9RDZZ0t74qMau/0AtAMfz8Xfy8dbv/d7QVAbctf4vAjmMI9ox4IAYRkC39DHMvNuXXbNrrGFp/d8gPgSl/0M/je7y5EP5vvfdY++jsf3mf5f713QeL1F+j9jkK0d0qivzMx3bwj0mLosWfvvPuL17odujLtoRZ/ujDaOwrR38nQvV7WNdvAkLC93gd5Zv9hS/cSH+ErYI/yHYDHLH1m+jhYghvXPog5PkLibK4zY1hjOnwJcl1Z/ZrSez0ZbR3J9aNZO1a/bjTrxRjWivRJyLWhe11orwljWw9uR3CuA1tVtf7j2i9yzWev94Jc31W1puN6jus47zUc129Yu3mu27hei+4H0ap6bWbWZVyTcT0Wm4/EVld5rsG4/gpfe0WuuyLXXNWvtbjO4hortvWVe21V/boqlvWUvY7S9dO+B2vWGzWfmk/Np+ZT86n51HxqPrF+fpv1f2pxUY5sAPxr639Zuy93rN13+fg8l+fS+oC3yNq9q1m7c8luTI6ImavUwkzjWi3CNlk0my20zVNpe2gV/piRlwpTE24/NelZaoSqEe0+GRtZOcVweYeiqbBvz+ti2JvXw+zk0eYmv+fCCka4XYkCft+L78fjQW6lDxv+XaVw23LdzKlxe5ZRa3C12GXp5iwj2MBRsxvV2r4QW1xHnxdpi0sKw2nfvDavmVgd5XUr0s4sKRLzmS5/F0V6I23zMH+0H+3Ko22vvLIdjPHwx7dGbBGd55nH1PH5+Tnx2E5z5q2Rw8ZIWmFeW0bmmT9bRnY0fE6ljCdTRispuoypeRN+ExkrbC1tpYzZlraVTIS10laiyJidV1St/aOq2seXSDVNIvGWLcKPVz23jRXTOpxlPI4++o5lGR+DcJfYl4kifzH6YSz+GaPkgfbmqmzjrr64k/KlUb5UhOvw+zKXfDAUPMHYKYpZLukr8isrrF/MS6B9DPb9BeA6sWOV7EjPWPe221xsNiRDdVd3j9QBTe2ysNtgMKwNsg6loGgf3tUGEw+LbIP3QeYhPTxljtnel1s+u/7uacg26JCtNSTJ9pCtExv6Jj/9DYHr8fsyl2wFaVMLM419YNwSw1gTqjuxt7c+pS9P2kY17d5cq/AjtY/XqCcr7YHJl3R+L+c9UyrHG3ssqeccl4rSijIt25/Lqnosq0K3/s3zKJcylss01tlUhI1SZ30qyyU=
*/