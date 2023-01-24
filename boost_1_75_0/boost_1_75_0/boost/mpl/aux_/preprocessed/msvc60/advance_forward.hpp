
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/aux_/advance_forward.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl { namespace aux {

template< long N > struct advance_forward;
template<>
struct advance_forward<0>
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
struct advance_forward<1>
{
    template< typename Iterator > struct apply
    {
        typedef Iterator iter0;
        typedef typename next<iter0>::type iter1;
        typedef iter1 type;
    };

    /// ETI workaround
    template<> struct apply<int>
    {
        typedef int type;
    };

};

template<>
struct advance_forward<2>
{
    template< typename Iterator > struct apply
    {
        typedef Iterator iter0;
        typedef typename next<iter0>::type iter1;
        typedef typename next<iter1>::type iter2;
        typedef iter2 type;
    };

    /// ETI workaround
    template<> struct apply<int>
    {
        typedef int type;
    };

};

template<>
struct advance_forward<3>
{
    template< typename Iterator > struct apply
    {
        typedef Iterator iter0;
        typedef typename next<iter0>::type iter1;
        typedef typename next<iter1>::type iter2;
        typedef typename next<iter2>::type iter3;
        typedef iter3 type;
    };

    /// ETI workaround
    template<> struct apply<int>
    {
        typedef int type;
    };

};

template<>
struct advance_forward<4>
{
    template< typename Iterator > struct apply
    {
        typedef Iterator iter0;
        typedef typename next<iter0>::type iter1;
        typedef typename next<iter1>::type iter2;
        typedef typename next<iter2>::type iter3;
        typedef typename next<iter3>::type iter4;
        typedef iter4 type;
    };

    /// ETI workaround
    template<> struct apply<int>
    {
        typedef int type;
    };

};

template< long N >
struct advance_forward
{
    template< typename Iterator > struct apply
    {
        typedef typename apply_wrap1<
              advance_forward<4>
            , Iterator
            >::type chunk_result_;

        typedef typename apply_wrap1<
              advance_forward<(
                (N - 4) < 0
                    ? 0
                    : N - 4
                    )>
            , chunk_result_
            >::type type;
    };
};

}}}


/* advance_forward.hpp
HxjZSRxvBruLjiugflQMRsrKwLmIooMr5UJ39tzITM++3np8pVXKADCAgZjR71liXpyraOQzO5mYua6Lci/LB3LF799/bgzehPF5yjK2R/7ofXi88+UnacrlmqekiJ90edt71KbhZqVH47ynH6W2NLKeO4iGXosIq3DILfsMRT321Akt9VkZO8G+BDKQUJ5ECI9ttDo6kn8R3fK9IFIXMJVy0CwaGxr6xjxsu/BnytjvKGeqCR4UU/oX02VrGVn0QagyVclhhhqAQbREnWjnwunOCXTt5EB5AvZwx3K3f0BC7t5420AWbHv20fPfaPVAFuxxyNETYE7zTon68/OkWqlshInC14mBd1PuJV7W3GSXEdM3OJbGBnp6G8seDjUOep92rK3lW8pv9/Jm6ipEujz2T4hGrS+HiWryyMm3UGpKOpqKu9g+ROUI6b2kzHf9ZEBOBlE7ZSoE++7vGU+j7SCGh1G1hReXYjq8sID/5E+PZXaxJC1+wuLC4AJfrAPf2eEanJYEfnbnrOQWlIyHpyA/p+k101Jb3MsiSbjgUprZ9rdSw4uNUvj8x+Gxvf3VNXcfr00PN+BhaQCwADFGkV+14v6DPDu/Ok6AZcVzHyczyQ0LXa0UzfdFZDpXmpOPuo1/YDNIV9ighCzn1rRE0KFy/jLDgOZluq0Pr042v+jHD1mFWUUJq6MyMuW4MrkEvSif72sANyXiOh+C
*/