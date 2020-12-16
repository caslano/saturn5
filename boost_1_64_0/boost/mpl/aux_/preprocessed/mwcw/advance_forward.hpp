
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
o/+/Cev6lu3f9v7/hlb2k1/J/n+/euQHO2BT0hNyTPr/Ayrf/29tvoz9/2cv0/9/3Kz//5iF/v/zZv3/p836/3826/8/aNb/X2xF//9jlez/P2Sh/3+nWf//XrP+/y0W+v+LzPr/91no/y8x6//fbtb/f1Tr/79k294gQxvhGzu8fh2of2vDKt3Tt0/xHz+/rP+f3+V/d/9/4TtXtv/f8d3K9f/7vqv1/1e2/9/OXn635feccqCPmu909Svf/x+IwbgcQ3A1huIL2AsbSv+/G4ZhKPbB9dgXN2E/fA37Ywvp//fEgTgYB+FDGI5bcTAewSHYXvr//XEYjsEI3IbD8TkcgZ9gJHaR/v9gHIUJOBp3YxS+gmPwKxyLff5i707goizzAI6PQeGBioqKioKKioKIt5Up3hciKuYRCgiDIDiMMCAamuaRlSallW5ua7uUaO5mZaWtu9l2UVFLRWWbbbRZaxttZJRalvt73/nP8M4wgzOG7fU+n56+zvDOc73vHO9zvK+M/0/DRFyOC/FVXIRvYBKewWSc6cf4P87FxbgaU/FdTMMP0Ig+Mv6/EJdgKmbgrZiJj2AWforZ2LUZv+kwAU14O+bgn9CM53A5RjMIkYtLMA/vRwu+jfno34LxfxyHK3AVFuKjuBJP4SoM8Wf8H6fgaszDNfhLvAlfwrX89xWuwy7KdYVwAq7HHNyAu3AjPoeb8Au8BTu2Yvwfx+CtmIW34d14Oz6DW/E43oFf4zZsxfFdjH3xTozCu37C+Lu3YyRFPN5BPEAsI57Ux0z0oId/a7is5//ZGSl5Gdb/N9b4/3ea++4Vym+ccmJLuddNOOdPyS8EaO/zHzuZe2JlGzm99OL8sjfpZGdoz8Oczg219yuTc6RQXmMyWV9TI+f8St2194zqGcFrTI7n52elHl3kN18nYj+lHi/Wq0cON7fy+PzcuQ6teZVypy7n+wJusd1HgOgj5YjktcWu809Kyb34/cXcleGxvlIGzfms0o6k6dgmUqYWUqZmxCjSOlavTMbc3Jxcr8ujzWuH9E/slONoB3EA21U456XeT9DzviTJy/H4cHMviVrN8aO9D1tT3/rtMFjZNy85l417B7J/VpiSsnNS0jxuj4FSRu3xUCF5+kl/jQ8OZbs99fLMNOUZcy0/5X3Fvm/wfXXeg/fVWTfvqyLppzkh+/U4cTjb1ZQ518NkXOFRHa5s8/jL6rkCB91A9fGL9sfR9jp2DqB8mvlDxQGO9xChDZT6ObR5tZQ1UsoaLvs54BXnstLzk5RpMS7L8/j+dq72cclVTvd+lM/O+Hr5UdLcTGPBJRz37j47z2r2sbJNrQeflbb3Q7T8ZGwl7wd/4tVsV1Wv3HmX9H6wlb2DlL0HsS4VxzaskrI8KG34APHJvvzv1XplseQqlfPoGKMc2MbxmKF95D0h7wGL8ljznlFea3Lqby6Q8kbJfVgscgOYifK+Hovq55y1vKk5JktuSqrF6/2sfQ+anD/PzFIH2+OB8h6VMnFDNjWskzZcTbyW7cyvqWWyfuHkWzKzk9JN3vTjOx+DFmJ+nlH57pJ7Ojp+Hyr7O1Dz/aRuKOkFab6jHOrmdB+gTKK2rily388/K3WRtJXHH8hj8nfYP4WcZyrht7J/9mEU6YS+rraFsdCcYkqTNgjzog2kX9hh/5yQY8RkynT8fjI79glnOvUJL3V8f7I/HftOebn0S8vfB1n3QZXDe9yp3i2shf9MjoFPiNfx2pgKtd5L+ACy7/tAL+rt6vPHtu97sD/lPWmrL+V1+t5xrJ+0l4wXaOujqbP6WZ9u3c9zlfLL94HyuIX0f7KNvf94xCX0H3t7r0/X10T2vp+4sfo=
*/