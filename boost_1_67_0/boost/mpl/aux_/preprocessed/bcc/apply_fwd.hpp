
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// *Preprocessed* version of the main "apply_fwd.hpp" header
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