
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/apply_wrap.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename F

    , typename has_apply_ = typename aux::has_apply<F>::type

    >
struct apply_wrap0

    : F::template apply<  >
{
};

template< typename F >
struct apply_wrap0< F,true_ >
    : F::apply
{
};

template<
      typename F, typename T1

    >
struct apply_wrap1

    : F::template apply<T1>
{
};

template<
      typename F, typename T1, typename T2

    >
struct apply_wrap2

    : F::template apply< T1,T2 >
{
};

template<
      typename F, typename T1, typename T2, typename T3

    >
struct apply_wrap3

    : F::template apply< T1,T2,T3 >
{
};

template<
      typename F, typename T1, typename T2, typename T3, typename T4

    >
struct apply_wrap4

    : F::template apply< T1,T2,T3,T4 >
{
};

template<
      typename F, typename T1, typename T2, typename T3, typename T4
    , typename T5

    >
struct apply_wrap5

    : F::template apply< T1,T2,T3,T4,T5 >
{
};

}}


/* apply_wrap.hpp
Gjj0UcWa0ydeGwaSSC8TbIz8UhAWbbP5SHyzh90ti/ud5POjgZemdAXFfAxLYjBFvOg5lM1vocABoLfeh/09N1x72o2RZBgnItav0C5g16W5zxzSbiowbO3/LxvYQxLsSPzUCylGd7YhdehUs1QCTN2fR7x5RWs4udvF5hSzbprtXd+K+F6S7o4S/9fd1p/wqgoDKmtBy6AKtAfZwR2MoXVSQ8FU+Z7kExHyOezB5nAC4HjKKycZZXAOoSEfn2KalbPKzgDjucT1I1JVINOnpRnRILhjcr6ZbVUJTiO7gXaZMFMDIcF32QoSgihM7Y2+vTYugeOot0KK5wvMjVlOBN0bRo4fJiV3fsIZxkhTY2iIT6OovMmMiSdGbK4BzSuCJtbEQg25D0Vn/RIMHWoFHEU2Jb4RNx99JZmM6MsM//c3YcOFp6M3DTEdyAcuB8EGqz7WNEsRS+JTci05Qf6hnjrscH+Q4kDxT8Cj/qOynC1s/6WdiDRnB007Dwm4LzBKfvgcdr4KTrAm+HQNAgBPWxWPAl+XCWvQtco1mUe27mYfPt+W36dlm7nkzQ==
*/