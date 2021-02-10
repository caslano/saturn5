
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
RpPhxOuKQJVDExCeXE8uBa65C/hLi8oULY0e6Iidpp7QGtSmLxpdYa0bCigxwlCVtm0LU41CUojZ2+YzX2/lLCpsN1kuxJmaRComSQQmu+bg9S/hYv7wGOyvKuF6Tjhk/yan6xN2no6Vxc5ZtqVtsKiZHPKeMO4J94XHHZHBid9bnoDqB1pQI+esK20Voi6fgvi/Xl3UUrBdfJK4gHaotmRi4BhQ4hzOWeUYlnVL9sgSlxAHinuQeDdj8LlpK3ENI26f+gdQSwMECgAAAAgALWdKUrcRL2V7AQAA1QMAAB4ACQBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3QyODRVVAUAAbZIJGDtk89u1DAQxu/zFKNWvQFml7aUyIpUChWcumxX3B1nQqxNPJE9uyU8PY6T7T4CFy6xP3u++SP/ooWiWBOpBO18w2nZ0/jCoY4l7B53m/zB7fYHaHW+0WoOhku4xGcKRwpvo6sJdKChG1NAbcSUcI+2Pfg9coPTAb60zrZIv42VbsTGSUTnhcHgzWqN1SiEuV7Vsd2/wak553+hwYoPvjZhBMu+duLYJyNKu8QHsuSOhJZregcf7z7df3748vURVusP1ze3//W/0lrNHGi1cJGBeegceVmAsVmkkJgxKkEaGZLh
*/