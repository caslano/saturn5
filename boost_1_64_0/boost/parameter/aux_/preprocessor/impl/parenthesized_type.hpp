// Copyright David Abrahams 2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PARAMETER_AUX_PREPROCESSOR_IMPL_PARENTHESIZED_TYPE_HPP
#define BOOST_PARAMETER_AUX_PREPROCESSOR_IMPL_PARENTHESIZED_TYPE_HPP

namespace boost { namespace parameter { namespace aux {

    // A metafunction that transforms void(*)(T) -> T
    template <typename UnaryFunctionPointer>
    struct unaryfunptr_arg_type;

    template <typename Arg>
    struct unaryfunptr_arg_type<void(*)(Arg)>
    {
        typedef Arg type;
    };

    template <>
    struct unaryfunptr_arg_type<void(*)(void)>
    {
        typedef void type;
    };
}}} // namespace boost::parameter::aux

// A macro that takes a parenthesized C++ type name (T) and transforms it
// into an un-parenthesized type expression equivalent to T.
#define BOOST_PARAMETER_PARENTHESIZED_TYPE(x)                                \
    ::boost::parameter::aux::unaryfunptr_arg_type< void(*)x >::type

#endif  // include guard


/* parenthesized_type.hpp
sbqz7DCp9LP/KF2jWvzF7XojS8PZfvozpG0s0+P/Sy181l8ktncof+bD09TwqYOWVvQ5ae+q7+a+fSD53YXf1O7PPEVvR9kfpB/IBE6hFrxAVJ2BoJ0NOG9LjbMBpT+jaMuh+zOieTYg7OCw11mUse3LYDAYDAaDwWAwDp//X1rZmAIQlTUA4YwBLDT4/4fRGABIgxwDWCJtwLE1xwAUZ46r9nEAShtT2zjA2PZBxwFo7nbA2QAtKJUaOAuO4AJj2ahUsoQexe7MzHFn2G115v1f8r1/IO389Qe8Tc5et/7Uwulzejz8+Ja9kY9HkP1P7SekFAij/W/cB1Gfh0vtgXai+MZ5uLkU3wM2kw9e24cBYwf185HXwz8eyZhA9laTmAIp2MpjAwwGg8FgMBgMxv8J0ff/Z+dYbeT+PwJz/5f9j/f/Kya7c+k2+KshLbebRC/IMMg4SLB527O2gzV7Ef+Xbo+uT7s4SvsDJu9g25TBYDAYDAaDwWAwoono+/9teU7Fm+2R6+uPzBqAFRgDuIR87J0D1gA0hNxrwfl8Jr+PXfGgBgqc84qxnIrqcx9uzRgR1t5w/xU/+1bpZ585+/Hrj7nxg1cWlFf09+3s1zDycQjym5OOofsgfvPjyG/eks4ZTAQvoPGLiTtMR8x3/t4OU73GJYp4XILBYDAYDAaDwWD8SxELGR5V+9+HKIrN7rVnqFvQR2MPQNXG/zZR6PPoE8jGj6c6NIV81wY2YkOjje/wKP6iZGfDxld8HrsQ4e39XgZOhqQ+qeblyTN9doY3ffjMZj8P+q19wdm6vUv5UTkC7N0ksnePp32yk8Fx4KE74ZvfyTYkg8FgMBgMBoPBYDCOLKI//x9L329TRubYqs7/j6mH3V+sr+3XzjQCG+zt+9Uz37T183ace+a1ur0+l6KVItzz3jSbf7K0+TOuvOC6Rb9PuufuUXvW7Mz8/Vvd5qe8UIYgNn9zsvmPpTOyEsjmL1Lt/TK2+RkMBoPBYDAYDAaD8c8hFuKMqv1vs2dafdleJTsHk+phj9scOUqOPI7e458MUK8xgTrWA8j7qRgTCHJbGXK2f73AAcNcgjFB1gs8g/TmAw3kmQHVquFy4zj9TK02de7JZxHx5g40x72BUK72JxvszXFbs+wBewPGmoKX4/hg5fBkWJ1VxQi7HO1qKccQKsdEKgdULJFC5ye2QTn0uRVyzYTDmu243a7U0tz+MZEbzCbwQei8MjH8sZh0U6h1FJGvi5g3SQ3/8s5GWY2ey990/VNvjnvlzeXpodZjhF4vcWO+Gh5/d8eiXys+uct010bTzE4Nf8TaABneoXD8ojZTBn68XLm3b6PfnFeGXkfRfbIaPq3AsrGk4ISJw9pMPqd797/2hF5fMUaWf8HeHRl5JzZ09u732lmbVm6uCL3+ZKccw7L1dfyx69fsZmMWX3bpmocSv4/8fIbg50uEXq/ydb7U582OmdsXr362sPCbZt8snZiG9RgyvGPfNa2KP71/XdzuZm9sbTMA6zbKZXjeJMtXDT791HnKqtzX9jxx7OrQ51eMkHq7rt2E1ba7yxbdMeXy44otB7Ev5Jeyvp17pb20cNKAotQPno+/O6nV6Vj3IfW2dMBdPbac3/Oq3fNPtBSYm8zVxvLoM06fubUB562n0VjeIFqvMhispTu+lnTXU7obKd1QStddaJ8hMGQivXtRTIkESmemMyBbgFNo3cxSOpci4EwKfY2Ma72pxjoZ4xqZojDXyYxbb6pz/45t1/nXysxeH3ytzAKEG9fLpO3COduQubt4/JPBYDAYDAbjaED0/f+Z2V7MtbdFwdZXbfW4JH8ZS/j3I4PBYDAYDAaDwWA=
*/