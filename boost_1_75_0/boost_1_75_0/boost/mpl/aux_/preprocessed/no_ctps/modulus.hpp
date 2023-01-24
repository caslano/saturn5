
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/modulus.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct modulus_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< modulus_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< modulus_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct modulus_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template<> struct modulus_impl< na,integral_c_tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template<> struct modulus_impl< integral_c_tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct modulus_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct modulus

    : modulus_impl<
          typename modulus_tag<N1>::type
        , typename modulus_tag<N2>::type
        >::template apply< N1,N2 >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, modulus, (N1, N2))

};

BOOST_MPL_AUX_NA_SPEC2(2, 2, modulus)

}}

namespace boost { namespace mpl {
template<>
struct modulus_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply

        : integral_c<
              typename aux::largest_int<
                  typename N1::value_type
                , typename N2::value_type
                >::type
            , ( BOOST_MPL_AUX_VALUE_WKND(N1)::value
                  % BOOST_MPL_AUX_VALUE_WKND(N2)::value
                )
            >
    {
    };
};

}}

/* modulus.hpp
Q3MlWoewNYZQOqiIYj3bB/lC3zznaCNaJmLF+1S/rIKsRvNA6JaCzzR3jieOVyL74JOVbd21a8nz0sJiHcxn/7J+qYu713uTc5RIzXUsf20E6KnfhbkiIxThJXR/fZ3VjiY+CsaNXkKC18Dr8l9zacCIPI7TrODRYLYgtuAWFG1U7SQRmvntcvSFHwavjoNb0PhRjoMoImsdC8d7VoJa0I+DcXukTYjqyA4xm8s4Vy5W0VaxHbA8Uc5R1l+eYDihe7ItQy82k28NvTdwO161ajed9l07bQZuomouhB/QbvphxyBHs2/J6Pdpd3SGVileMkmUTnJJ/CiQNC8q5SeUi/kWYOXwR7vYgeqvrdYJB+tfBWwue59tLGZjBgbPOs+p2d7S4KXPTzl3MFPH6w0SunB7DokQn/PGetPZ4a1S4Waqsons1vdKu1dtvGD8I3zIhsHh+w666HTB7xfYIe+NO9nSOeBVZYJv478MYp5xDd5SXJpGvI6XllCbRb3hq8PHQbey0eg82BtrqgQhMb6/yTihuSh8X3w8mYane5mQcbxgL2V+uRo9KeLEIPGgXUtAzbOX4Bc7reo+TvEJmrtANw+QNn9tHU9ALfdWcp+ajeTui5JspbLK8J2h2A0ltkzhBBTa8L3XbDVUeirKm/DSm+GkwayI1lxBgcFhipTmVUbnQP4wG7wK4k9Hr6p6XL/NSdsWHOg7NSM5n08m
*/