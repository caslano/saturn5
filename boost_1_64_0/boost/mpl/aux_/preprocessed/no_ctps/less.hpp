
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/less.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct less_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< less_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< less_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct less_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template<> struct less_impl< na,integral_c_tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template<> struct less_impl< integral_c_tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct less_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct less

    : less_impl<
          typename less_tag<N1>::type
        , typename less_tag<N2>::type
        >::template apply< N1,N2 >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, less, (N1, N2))

};

BOOST_MPL_AUX_NA_SPEC2(2, 2, less)

}}

namespace boost { namespace mpl {

template<>
struct less_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply

        : bool_< ( BOOST_MPL_AUX_VALUE_WKND(N2)::value > BOOST_MPL_AUX_VALUE_WKND(N1)::value ) >
    {
    };
};

}}

/* less.hpp
kmq9pO/Dqkyx0tcfKmXqR3qGMg0vqVkmqiX/Nni3MqVI3d6tTNlSphrSJ2R8BpZSTxplikky9v7l21+rVSZ1/7e/9EkXJsOSIscbCm6d50h9rIFDrQPPCzbFKuV43IlV2uhhiVXy18lr/h5545d+Lm15zdf82prSeWOaZpXOG9MUVFoV0/QAjn3MS7+xddty9qs5+9XutV9tr7FfbUKJut+ETPD5vfqsGpEtvH7M/vf2q4Xq5BwIkzSuf26V6587sCHuxB64G4PwQ+nn2IejcD8mSH/Jr5hFypblp8l1TC85D1CmZ2X506TfZzo2xhnYDGdiJ5yFETgbDfgCknQZ+BLOkevTL+JWXIBHcBEel+vdl+R6t9Jv9zqWwZXYENdiE7l+3UKuX/eV69cD8D1Mwc2yXpRXzl1YF6m3UmiO3Too6/UZVpL+In/MwjbSTxSJ32MM/oDxeAJT8CTOlf6hl6UfaDOex534E+7GC1KekS5yriHnIPVJDaSvQJl+lvJclfJck/Jcl/LclPK4upjKUxjj0Q1TsSjOR3dcgsXwHSyOh+V699foIdePy+A16YfiNV1F9MJqWAOrS/9ODeyENbEHPoLR2AAN+Kj06zSW/lMfXIxNpD/HH1djc9yPLaQ/pyUelf7XE9L/egs7Sb9OZ/Skjrrgw9gVA7E7dsPeGIXBOBr7YBz2tTwrVs5ncLTGs2K9pb5roifWknqujYFYB3thXeyND2MY1scofET6ZdiGkp+cq2CoRn6NJL/Gkl9T2Y/8sQU2k/7T5tgRW0h/UEvsg62l/7KN6pmhWZJfDY1nhlaSfovKkl8V6RepitWQZOr/cJFzCznXYDnUAesv7bK9lLuD7P+dpH0Gyv7fGdtiF+yOPXAI9sRw7IVpGISTsC8+h/1wLfbHj3AAHsZQ/BGHoTtlCMfaGIGPoh6DcAQOxJFowFFKPhiLszAe16ABf8YkLMS6JaM3pqA/PoVdMRWn4VjciBNwP07CkzgZT+MUXOvqeD9D7tL87z/+t/Qr/I0+hfvdn+Acs/d/v8+goP0FBekr8FxGGyGFklJJy0h7STmkEsud/QDOyTk5J+fknJyTc3JOzsk5Oaf/nqkwKfGf6P83vhKlH6MEAfzNGAClf9/F885zALzlepIbyVUS91py722eey0txTDebenAPc/qcfy0r/kX/Jq89jV/+3062n0B9vt6tPs47PXdFLwvpqDjAWr3ednve7pl7Cv5ZGnvaaPOHK+1Z9zA7lGTWyw19VnU18l2RTe59l0Iq8pG6ynXJntj1UK6fK+POcfn+/8cny/Uee3GOTkn5+ScnJNzck7OyTn9H07/1Ph/kfHRf3v8PyX2/0sCW8Y9wW98yyhxT/N4eFNGSRL77+p5J/a/pVwbqCrXBSrLtQHdXyVVsdmMo8Rj+uKjw+ISolJi9Q5eFzDH8mZIHH9/iavtg9OJ5fUlD1NcrRTQmEfMiJREU8xzHXvLl/H3qhcy/s7l0QkS2yvxzua477KqGGgZMsYS67qagFbq3DifrRofS/nMcZmnsoHPqGL9Y2S5ORL/HZVgGgOtgsSAs3Bj3L/kZ3w9V/W6lM32+YmWOPMqyjxBuebyn+a1RWVNryXZxCvflnoNl20XJmO0DXctZVOvShHz32Y2ccKqMXrkogFTb4kRf5zUibyybfOSJiKj5uUbJ27OM408WWvt50rajNe3UcqwntSF4K7gwpplkNV2JE47bxlKqNqIjKXItmF+TN77BGIs20+2lTyMUb0PrC2cd6ypXOVZnG7mMY469Q7qEjagQ8/+nQs6ztRlGWNJnV9Dt7xjKl1nZrhGfgUdT4n8NMdTUrfNBW5517e+D+3InL8=
*/