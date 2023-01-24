
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// *Preprocessed* version of the main "or.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

namespace aux {

template< bool C_, typename T1, typename T2, typename T3, typename T4 >
struct or_impl
    : true_
{
};

template< typename T1, typename T2, typename T3, typename T4 >
struct or_impl< false,T1,T2,T3,T4 >
    : or_impl<
          BOOST_MPL_AUX_NESTED_TYPE_WKND(T1)::value
        , T2, T3, T4
        , false_
        >
{
};

template<>
struct or_impl<
          false
        , false_, false_, false_, false_
        >
    : false_
{
};

} // namespace aux

template<
      typename BOOST_MPL_AUX_NA_PARAM(T1)
    , typename BOOST_MPL_AUX_NA_PARAM(T2)
    , typename T3 = false_, typename T4 = false_, typename T5 = false_
    >
struct or_

    : aux::or_impl<
          BOOST_MPL_AUX_NESTED_TYPE_WKND(T1)::value
        , T2, T3, T4, T5
        >

{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          5
        , or_
        , ( T1, T2, T3, T4, T5)
        )
};

BOOST_MPL_AUX_NA_SPEC2(
      2
    , 5
    , or_
    )

}}

/* or.hpp
/ABSSu6SulcfDOuuyDeq0flV1iMTlWSLWhp5oo3DhUzogcE4MMrbrX20P+YIdoquZzrO1u7f23FiJfGyLe8wkPIzTsbqEO1KLfuK5M/+M5s7OcIyYOtuNIwT53ciIh+v+WD5q4jBZqC2iPyary80nynAq840HathyMA1t1ym5BBydMKjmZrLPvW4RzViuwkvl2H1A8nFSUqUllLgi+kQxRQF5IBIzRknBss4/nITkeAlkbZYwWMaojt6mZow6ysUJ5SK83GgjUOU9J5DsUMn0KOiw7LOe+gqsKnsS4hHtA2YfRHb16PAP5ylRWocWRWdq0EFkr4feHB3ENzKadxp2Z6DRs4xcRO4ueSzQW+JDhVGSS334bseJfB/p1fh1oTAA/ZgWt5edZ59/lhgEn2/OxVk11ceOHDHXbpCLC8FYIeF/Ro8wpSWrD0C3hweROsbx5D2780SAAZiBkts+1W3S67qfXw7eiY6dZZW3XdOan2gjS8wb1/Yx4nGs92SDwTcXU/XHx/7QzwuvA43vg55bHW0E9mOZdsJKqwhEXTmNzM0oeW1ZuKVudMU409Lt8kHwj9pDKqXrUQTueIuwxlxC22fblgCbmX9kt+yg8Ik3lC/QRQN5uClZNoXlp/5kyR3aOY1HvnmWYF/EU1Uf9J+U5MtxbJXjk/GZVURLKaYEeukSx7Xd7v3PUuR5NPlynNWKjRWCXJRatMi3Jhs
*/