
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
dGVyL3Rlc3RzL2RhdGEvdGVzdDU4MlVUBQABtkgkYKWSzU7DMBCE736KVVCPYAkJCVUmF35UDqhRU+CI3GTTWjh2ZG8LfXvWSdNWvZKLveMvu+NJFGGkSkfMhTKu8bx84/7HhzrmonxZFqLdWjJCyZOs5ECKKygx7DBcR1OjUAE7u+fjWpNO1LgedMYfrUFHB7zqCwZi3yQXsaGO8bFU5L3NhTWru/tb1ocSlNMtDt5g21mva9hG49bQGwXjCEOjK2RSDiioyretdjW/xSOmUk5m83L5WkwnZTkr5otlWr+Kzydp/VoOTXnmDf0STEa5MRaP4nv5vJiyp2NjlY4hzXvILugsF2/+7BGjbdqYyD0SmmIa8+CcPjCYZg8pQNANX4hZhPSpYKMjrBAdZHHjKRNq17PcYKftOphkpjZRryxHLE+aihRMl+aMmy548lXKVMmz/f8vcnQkTz/XH1BLAwQKAAAACAAtZ0pSgAx1wLwBAADkAgAAHgAJAGN1cmwtbWFzdGVyL3Rlc3RzL2RhdGEvdGVzdDU4M1VUBQABtkgkYE1Sy47bMAy8+yuILRa57MYFigJFYOTSB3prsEm7x0CR6ViNbKYUnTR/35GdbHqSSA6HI44q42TeJV4WVegbwXHgy1m0Tsti/W2z
*/