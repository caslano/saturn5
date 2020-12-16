
// Copyright Aleksey Gurtovoy 2000-2004
// Copyright Jaap Suter 2003
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/bitxor.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2

    , BOOST_MPL_AUX_NTTP_DECL(int, tag1_)  = BOOST_MPL_AUX_MSVC_VALUE_WKND(Tag1)::value
    , BOOST_MPL_AUX_NTTP_DECL(int, tag2_)  = BOOST_MPL_AUX_MSVC_VALUE_WKND(Tag2)::value
    >
struct bitxor_impl
    : if_c<
          ( tag1_ > tag2_ )
        , aux::cast2nd_impl< bitxor_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< bitxor_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct bitxor_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template<> struct bitxor_impl< na,integral_c_tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template<> struct bitxor_impl< integral_c_tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct bitxor_tag
{
    typedef typename T::tag type;
};

/// forward declaration

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct bitxor_2;

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    , typename N3 = na, typename N4 = na, typename N5 = na
    >
struct bitxor_

    : if_<

          is_na<N3>
        , bitxor_2< N1,N2 >
        , bitxor_<
              bitxor_2< N1,N2 >
            , N3, N4, N5
            >
        >::type

{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          5
        , bitxor_
        , ( N1, N2, N3, N4, N5 )
        )
};

template<
      typename N1
    , typename N2
    >
struct bitxor_2
    : aux::msvc_eti_base< typename apply_wrap2<
          bitxor_impl<
              typename bitxor_tag<N1>::type
            , typename bitxor_tag<N2>::type
            >
        , N1
        , N2
        >::type >::type

{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, bitxor_2, (N1, N2))

};

BOOST_MPL_AUX_NA_SPEC2(2, 5, bitxor_)

}}

namespace boost { namespace mpl {

namespace aux {
template< typename T, T n1, T n2 >
struct bitxor_wknd
{
    BOOST_STATIC_CONSTANT(T, value  = (n1 ^ n2));
    typedef integral_c< T,value > type;
};

}

template<>
struct bitxor_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply
        : aux::bitxor_wknd<
              typename aux::largest_int<
                  typename N1::value_type
                , typename N2::value_type
                >::type
            , N1::value
            , N2::value
            >::type

    {
    };
};

}}

/* bitxor.hpp
KMfA/rh46fTJ+2RfvSXWXXnG1QCfQ+Ug+W4pdl+lV5r75YES9kslHnJtlqlfTow3RCSmGekDLHvEvIwY2CRTYXTav0RbKfm8NX24rboPy7Io6WNRkWTExiwLtxk3MinRYBo20tznQ2VsTqWXGqLovVK+UafPp2v6fKqqzyvbCrYb79K8fKBNGfR0OT/Ha8bBHK8e81LyjpFl1Fq2aV43RmfMzBny+TXGRKTEyDL1Z9ry7mpjJY4lB3Ql8+O2Fv5OpJ9mTExlWYjNMj/tOJnE6+uPk1l7280bJ7OXlO1eVX+sSt9t5T9WZU8pc25V/fEiw7fdnPEiG1bTHS+Sh+D/ufEis6rpjxeZue1/Y7xI/fhYR/HDpY+bdY4XWb7jRUaa4pyX+o79/VKEsdYdSVU/eHVu5IDSx4cXNV5klQpyHSHXF1dJzUzxR+bpNxn/7Hc0LcfWeB07YgUlPgwrYgC64r3ohkOwEo7AymjE23A+VsFnsSruxmp4DGtibepwO9bFWtgUa2M3rIMBWBf7YD3si+44FuvjOPTANGyAD2MjzMDGOB89cSU2xdXYDM1x1HItINcIVzVx1Jjhiq2wDZLM8d0V5Hu2fP9W8rXl38GoTB2lHe9EL+wi7eiPd2JX9Mdu2BMDcBD2xHF4F6bg3fgQBuE87IPPYl98EQfgDk08x1G8D3/AwfgrBsu7GoegNw7FPjgMR2EIjsfRmIZj8GEciyvxAXwaJ+Cb+CC+g2H4FYbjnxiJXrTHRGyBURiIBhyL0RiPMZiCcTgP43EBqsYHlO/HtKXOcUmW45KCHTANzfE08l1TvoNe1cTTzJDjMlPyzcXeuAD740Icgo/jSFyEY3EJxuEynIbL8VFci6vxaVyH6/E1fAaP4bOYjxvwd8zE+tTlOWyMW7ATvobBuAMTcBfOwN34BO7F/bgPD+J+/B4PoBKn9zfsiW9hbzyIMfg2rsFDuB+z8SC+hxfwMF7DI9hBiePEwXgcY/EjXIUn8CX8GP+Gf8dD+Al+gmfwM/wSP8evMB9z8Xf8Gisp8ZrohXnYHr9FHzyHwfgdDsVfMBYv4Gy8iOvwEj6HqnEy+Y5WtnEyfbeVbbzL8G1lG7cyY1vZxq3M3Fa6cSvHlzDOyDlu5V87ruhWxxQtJlZoM+kkyY2XOviSwkkZpI2kbFL+NWc8kXNyTs7JOTkn5+ScnJNz+utNt+T5f2JafHmM/9dYxv/ztI7/x4Zl5D8lNiCHvbA8pwjQGffPXRkD5iXr8zUyl8+YaxsdlOVrU9aNjrlmfm7IjP54huqypFGSooovS32f/6Bsu6VsuznJQ7kI12xbM/5WsWXczHFWVPXnAl+//pkv6tffkPjXqn+Qm379c7T1V49bVILxF29V/V0q6dffqFt/mv8vUn8ZB8fR84xSj9ui/5ym/J67lNfzldI+P9N/HlN+z11K+zzsSdNzoC31v/+l+ucxY9YEfrZiVuL7Xzt6Hnbz3wtnvg8pf2PkHJ2luR8/Tk5T47EKTlDfZy0i3/2Sb7TkG6N+z08R+bpIPn/J1xXN47wwSb6Wkk89zstAyTcIm+FgbI7BqvycVx3mD5L8fSR/X8nfT5U/p4j8IZJ/uOQfIflHqvIbi8jfQ/L3lPx3Sf5AjCrhfd/lfzp/X+r8fWnR94K30EeOkfJJVf7FvWDSGFLGv5z3f52Tc3JOf+3p1lz/E81YDtf/yjX+x6qx/cfLdXe4XG88KO/Kz9ioG9et1KLYa43yjH01XRtJXT3l2nosSb7H8e535UG2g3hfpbaluFdQHvXVxOr+X4wRWtprptJeo/ynxgI9bLo2WlNr5hvPvhZiWOzj+3uz3CXrb/41UFFjhMa4yGc=
*/