
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/apply_fwd.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename F, typename T1 = na, typename T2 = na, typename T3 = na
    , typename T4 = na, typename T5 = na
    >
struct apply;

template<
      typename F
    >
struct apply0;

template<
      typename F, typename T1
    >
struct apply1;

template<
      typename F, typename T1, typename T2
    >
struct apply2;

template<
      typename F, typename T1, typename T2, typename T3
    >
struct apply3;

template<
      typename F, typename T1, typename T2, typename T3, typename T4
    >
struct apply4;

template<
      typename F, typename T1, typename T2, typename T3, typename T4
    , typename T5
    >
struct apply5;

}}


/* apply_fwd.hpp
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
*/