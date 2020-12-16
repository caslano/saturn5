
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/greater_equal.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct greater_equal_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< greater_equal_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< greater_equal_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct greater_equal_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct greater_equal_impl< na,Tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct greater_equal_impl< Tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct greater_equal_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct greater_equal

    : greater_equal_impl<
          typename greater_equal_tag<N1>::type
        , typename greater_equal_tag<N2>::type
        >::template apply< N1,N2 >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, greater_equal, (N1, N2))

};

BOOST_MPL_AUX_NA_SPEC2(2, 2, greater_equal)

}}

namespace boost { namespace mpl {

template<>
struct greater_equal_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply

    {
        BOOST_STATIC_CONSTANT(bool, value =
             ( BOOST_MPL_AUX_VALUE_WKND(N1)::value >=
             BOOST_MPL_AUX_VALUE_WKND(N2)::value )
            );
        typedef bool_<value> type;
    };
};

}}

/* greater_equal.hpp
5FVWgNFmtybHjbLm34eDM79aZvgQ28m7L4M4wvOdWInmZK/3ySUQzv4XmChX3yFnJL/lZN2WJd6rz/+O6fm1jTGOTUkwGZNTk/Jft852/zv4vG2M93KGBeVezrQIPum9HEuKJfDlbGfAdzl7g3K/H28X+engs5xU26gCL8e53oOCWY92q9d2jwr2Wa70SRTtvVx5/2LgZZR16bXNE0zjtWW73omZI8tuJfvcrcQM1m26Y9lydMi+dhmOjUqyP/keB579WBv7OjoY8VxHq6QdZFHtGW0sjMPJZ1a2nk/9/GKMTUg2GeNTk+PyPzac62g0D3lxlpK8yrEyISk5Jsns2vdH1Ne3mevYuIflMo3+TrvEr1k+n/stxLsfj33yTrs/pc+rn3E0n9v9nUd+RyamxMYkJqakjEm1yHbtUjiwfjI8j209s6RK8r6lG27i2E5MsdH5SXIMM64i74hKY/lJKaZUekWJT7A61nsZ6atvFn+zmu368F6G2zBfU2KiPs/N3p9NNo9nO8q7irT9eVQv/Q/9tIVVkj4CrUwfZzXH2CUTzvciWbT5mB3XAm39Gb53rL9fQxzDnWX4Nxk2yvB9EY7hx33+/qrP8DsybJXpD/l8vvYRx3CaDDeTYdaZPtzxiPf0A494z9/qM/0Un+kf9Zn/cz7Tb3BN733uiSzufG6S/RvX4EPa/nLMY38ZTWcnHFfafnJdAfZt5/taH2B+8QmJbBFLYoLdfcw5rg8xVkZ59fWdEh9vM8t0J+WYlb5/3P3LyXVD69PkAPv8LhY8jXFhJ9zvTjwuyzAnm7Qyu6bNkWnf9Jj2iM+02jpLPe74u6m6Yx1+5jOcfMJ7uMKP3sPDXcPe6zyshPS5JeeUtjiEdXTyS491rvWYJMdmqYuu8yLlzh7kc2Tdas21DWR9OY6rUYx3nwcd20SOYTnHyDlHjpEOjvka5so+df1X/vchHvzV0+vac2q4Cc1ME33IXR6+jllHmq0BlMf/PsS20fNrs5jjmkg5QnzGRzj7t5Xy6YtkJVaRMs+L8JiH7IxVpNyef4uQv3meV3OkjGVlm5XEWG2B33iUkZWpvbdUfymjlDXkEsrqPr+6+1i0W2OSbfFc07y2pYxP5LRnynWMOLadlk+GF8i2bO0z3Mc97HX9y9AKK++eLC0uZBrLT65yy+qixLK/hl60zKUc/U2d4vMew6NkuDz78+Kf9X/XibyD7khlXIh7XDODc7qTrnERhgKsT+c7se1EjM2WykZLjLHZjQk2oylB7+fpmnKL9Dn2uMN4R+8uXQ2ucSyPcV26DuzRuatruzBe63MpwZ6Qkuz8TsFovY82bcYg+6XPOc+978n5zb2cwtpybusR2dXnu29IGcfK/Ea+Nx0ktHPHnK88tkdqsnb2CLjPM89zxXmfc0CVbO9j/oy0ocmrzyb/fQwVvK+ogvblVNA+mHgkkfHtw82/TBo2sn7Q2JEl046a9/A9VB//2dxD73YyJzw+9fTE2LW1VhcpeF9Ul6vPJv99ZuXVJ1fefUhtS9TLO/uXkPjMY5NiFnTdcayp9ZTezorxTwzcHlz6nt/X1Fr3aa26j/Vsl1cfVQXvG8vxTLfcV2MJIsvnme4B0ofPQCyGd6Lzc9HyuRoyrefnXizC53AdVsNX0Pks/hz53CBZnuez+PTTkl4aj2IHPIa34w8YhcexL57A/vgjOvpmkntMKOenb6YRBud0RIDTdZDpKuYzXXQA03Un0mW6VvI3zzYNp4tSbvwFK+Bv2AD/wKZ4AW/FP/EUrjLIfY7c/2QR2nljqcwvU9o0rMTKuAqb4Gpsgc9iJD6HJnwex+ALOAezcCG+iGtwLa7FdbgNX8ad+Ao=
*/