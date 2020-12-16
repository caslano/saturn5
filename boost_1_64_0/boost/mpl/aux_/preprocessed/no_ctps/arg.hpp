
// Copyright Peter Dimov 2001-2002
// Copyright Aleksey Gurtovoy 2001-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/arg.hpp" header
// -- DO NOT modify by hand!

BOOST_MPL_AUX_ADL_BARRIER_NAMESPACE_OPEN
template<> struct arg< -1 >
{
    BOOST_STATIC_CONSTANT(int, value  = -1);
    BOOST_MPL_AUX_ARG_TYPEDEF(na, tag)
    BOOST_MPL_AUX_ARG_TYPEDEF(na, type)

    template<
          typename U1 = na, typename U2 = na, typename U3 = na
        , typename U4 = na, typename U5 = na
        >
    struct apply
    {
        typedef U1 type;
        BOOST_MPL_AUX_ASSERT_NOT_NA(type);
    };
};

template<> struct arg<1>
{
    BOOST_STATIC_CONSTANT(int, value  = 1);
    typedef arg<2> next;
    BOOST_MPL_AUX_ARG_TYPEDEF(na, tag)
    BOOST_MPL_AUX_ARG_TYPEDEF(na, type)

    template<
          typename U1 = na, typename U2 = na, typename U3 = na
        , typename U4 = na, typename U5 = na
        >
    struct apply
    {
        typedef U1 type;
        BOOST_MPL_AUX_ASSERT_NOT_NA(type);
    };
};

template<> struct arg<2>
{
    BOOST_STATIC_CONSTANT(int, value  = 2);
    typedef arg<3> next;
    BOOST_MPL_AUX_ARG_TYPEDEF(na, tag)
    BOOST_MPL_AUX_ARG_TYPEDEF(na, type)

    template<
          typename U1 = na, typename U2 = na, typename U3 = na
        , typename U4 = na, typename U5 = na
        >
    struct apply
    {
        typedef U2 type;
        BOOST_MPL_AUX_ASSERT_NOT_NA(type);
    };
};

template<> struct arg<3>
{
    BOOST_STATIC_CONSTANT(int, value  = 3);
    typedef arg<4> next;
    BOOST_MPL_AUX_ARG_TYPEDEF(na, tag)
    BOOST_MPL_AUX_ARG_TYPEDEF(na, type)

    template<
          typename U1 = na, typename U2 = na, typename U3 = na
        , typename U4 = na, typename U5 = na
        >
    struct apply
    {
        typedef U3 type;
        BOOST_MPL_AUX_ASSERT_NOT_NA(type);
    };
};

template<> struct arg<4>
{
    BOOST_STATIC_CONSTANT(int, value  = 4);
    typedef arg<5> next;
    BOOST_MPL_AUX_ARG_TYPEDEF(na, tag)
    BOOST_MPL_AUX_ARG_TYPEDEF(na, type)

    template<
          typename U1 = na, typename U2 = na, typename U3 = na
        , typename U4 = na, typename U5 = na
        >
    struct apply
    {
        typedef U4 type;
        BOOST_MPL_AUX_ASSERT_NOT_NA(type);
    };
};

template<> struct arg<5>
{
    BOOST_STATIC_CONSTANT(int, value  = 5);
    typedef arg<6> next;
    BOOST_MPL_AUX_ARG_TYPEDEF(na, tag)
    BOOST_MPL_AUX_ARG_TYPEDEF(na, type)

    template<
          typename U1 = na, typename U2 = na, typename U3 = na
        , typename U4 = na, typename U5 = na
        >
    struct apply
    {
        typedef U5 type;
        BOOST_MPL_AUX_ASSERT_NOT_NA(type);
    };
};

BOOST_MPL_AUX_NONTYPE_ARITY_SPEC(1,int, arg)

BOOST_MPL_AUX_ADL_BARRIER_NAMESPACE_CLOSE

/* arg.hpp
vfMZ1rsqZ738lK1xzcXMl6Ihrya/gy7ztnib5zZJ5u1kPkjm7TGCCCSqSt6tPG2SHgkUy+k/UNF0z2KHiqlKm/k//lY//1ycaV5+e136PpS00PfB8JzZAXk6P+gePhf6uPo/7Jfk71bDfeco/R/25LSZphb5vnOb/bn7P6Tty+n/ELjPdN95G50sc89ZZurXUC5nWSvjsuw389+z3si0rJWLqZ/E3tz9JCqw7KxpWQf9vLdpvj1lmDesx2+CHxnaYmzzwu5Fr1iMe9HT8vSRyH/vudwHKusNYMXq/hWVlLp8WJhn/zpKTn62HJMzpR9A2Num/at0iihWPwA/VD9H/zx1rpU6T0udJ6TOyLdMddL5oJiv+SB1nfn7HhyV/P1VOY4votL3oGWsqU6l84G+Tuei1qkret8D1T3qlva/aX9XVe1//aAh0sFD9q96n+vHx9jI9ow3jJ+n67YrZ3yMDFnHC6ZjSNY5bbz+x8vZPrnGL1kr9/HbSF8na7m3PWa7cRtJJwd5X3J4iO1UUD+HjCJuI0v3t6db6Afh9n/YD+K/vb/DBH1/B4e20W/Z9L8z/H2rXy8mDqw/5T+gX8OBnH4NcXn6NTwn+esuaI1dVff8rZJyp6Sc+p6/N+VembfRAQ9gPYzDxngQXTEeR+MRHIvHMBhP4Go8ievwFG7G0/guJuBxPIOmfhbSniHSHnU/i4XSnkVoh4uxPi6V9izDZhiNbXAF9sPVOADXSD3WJeV7gnxvoB62Dd95UJkaSj1NpJ4WUk9LbI2t5Hm3xq7oIs+3HU7H9hiJrrgPO+JB7IRXsTN+gl3wJnbFNOyGD7A7WtEWd6yEPdEee2Eb7I2u2Bd7YT/0wP44AT0wGAfjLByC0TgU1+Aw3ISeuAVH4E4ciQfQC4/hKPwUvfErHIN3cCx+j36YjoFYhm06Hm1wIlbBIKyBk7ARBmMPnIyDMAQ9MQxH4xQMxKkYjuE4DafhSzgdl+IMXIczcRvOwh34Ip7Al/AMzsaP8GX8GOdiOr6CP+J8OR5m6uR7Bc6W484Gg+W485J+A89jZfTGajgWG6APOqMvtkR/7IrjcCQGYCAGYjhOwJk4Ee/jKp18x8DTUv8zGGXsf6Lqb+KEvbAJ9sZW2Bc7Yz/sif3RCz3QGwfieByEYTgYN+IQ3IND8TB64gkcbrwHt6R8D5HvJ7SLsry+5HxhkrQrGO0wDGvgFKyLU7ElRsj2mIb9cToOxVk4Fl/EYHwJI3A2vogvSzvn4Daci7sxUvovzcPT+Apewfl4HaPwK1yM93AJ/oJL8Q9cjdY8lzVYEV/FqrgOnXA9euAGnIAbcTK+hrNxE87Bzbgct+GrGIM7cTu+jTvwMsZiMu7EL3EXpuJu/A334AN8E5V70fdhRXwHa+AhHIGHMQCP4CQ8hhF4HF/GE7gQ38N1eAq342nchWfwXXwfT2EinsNz+A+8gNl4EZ9if1/C8ngFHfAqNsBkbI7XsQ2m4HP4OfbGmzgAb+Ew/AKH45cYjF/hNEzFOfg1LsJvcBXexnV4B9/Ab/EAfocX8a4cn7z+5Tug8t3QcHw6K8cjKtMPcnymox1mYH28h63xPnbBf2JP/EmOz19wFGbhBPwVJ+NvuAL/hWsxG2Pwd9yDD/AI6vRjQwCeRSv8EEvjdSyDX6E1/g3LIst05bAZlsdOWAF74jPogRVxOFbCsWiHE7EKhmFVnI7VcAPa41asjnuxBp5HB0zCWvgV1savsY68rztiJtbFX7Eelmb71kdrdMKJqPRdSu9oXWj/pQt/8n2nj6u/Up5+Sg/dR0nVP6nQvknWnayL3DfpUfolPc4+SQX1R3LoVPi9pS78zWAijFhF7CE=
*/