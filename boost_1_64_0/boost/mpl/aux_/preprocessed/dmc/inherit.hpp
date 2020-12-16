
// Copyright Aleksey Gurtovoy 2001-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/inherit.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename BOOST_MPL_AUX_NA_PARAM(T1)
    , typename BOOST_MPL_AUX_NA_PARAM(T2)
    >
struct inherit2
    : T1, T2
{
    typedef inherit2 type;
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, inherit2, (T1, T2))
};

template< typename T1 >
struct inherit2< T1,empty_base >
{
    typedef T1 type;
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(2, inherit2, (T1, empty_base))
};

template< typename T2 >
struct inherit2< empty_base,T2 >
{
    typedef T2 type;
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(2, inherit2, (empty_base, T2))
};

template<>
struct inherit2< empty_base,empty_base >
{
    typedef empty_base type;
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(2, inherit2, (empty_base, empty_base))
};

BOOST_MPL_AUX_NA_SPEC(2, inherit2)

template<
      typename T1 = na, typename T2 = na, typename T3 = na
    >
struct inherit3
    : inherit2<
          typename inherit2<
              T1, T2
            >::type
        , T3
        >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          3
        , inherit3
        , ( T1, T2, T3)
        )
};

BOOST_MPL_AUX_NA_SPEC(3, inherit3)

template<
      typename T1 = na, typename T2 = na, typename T3 = na, typename T4 = na
    >
struct inherit4
    : inherit2<
          typename inherit3<
              T1, T2, T3
            >::type
        , T4
        >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          4
        , inherit4
        , ( T1, T2, T3, T4)
        )
};

BOOST_MPL_AUX_NA_SPEC(4, inherit4)

template<
      typename T1 = na, typename T2 = na, typename T3 = na, typename T4 = na
    , typename T5 = na
    >
struct inherit5
    : inherit2<
          typename inherit4<
              T1, T2, T3, T4
            >::type
        , T5
        >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          5
        , inherit5
        , ( T1, T2, T3, T4, T5)
        )
};

BOOST_MPL_AUX_NA_SPEC(5, inherit5)

/// primary template

template<
      typename T1 = empty_base, typename T2 = empty_base
    , typename T3 = empty_base, typename T4 = empty_base
    , typename T5 = empty_base
    >
struct inherit
    : inherit5< T1,T2,T3,T4,T5 >
{
};

template<>
struct inherit< na,na,na,na,na >
{
    template<

          typename T1 = empty_base, typename T2 = empty_base
        , typename T3 = empty_base, typename T4 = empty_base
        , typename T5 = empty_base

        >
    struct apply
        : inherit< T1,T2,T3,T4,T5 >
    {
    };
};

BOOST_MPL_AUX_NA_SPEC_LAMBDA(5, inherit)
BOOST_MPL_AUX_NA_SPEC_ARITY(5, inherit)
BOOST_MPL_AUX_NA_SPEC_TEMPLATE_ARITY(5, 5, inherit)
}}


/* inherit.hpp
Ob7dYAHsDufAHlDOY56fxL7iPB4q9oeL/USxf73YvUHsjhC7N4rdUWI3SeyOFrtjoPTz8lzEOa/o5w/IcTsII+Eh2B6+By+BVfByeBheAX8t/eP7ctyOwFR41FDPpc/b1/MpsXcatoZnYFv4DewI/wa7wbMwAf4dDoffwRR4TtrFP2AB/CecA/9ljCP7gsyzemkPJUjpk8brrzl+cEfxM0787CTzrJ1hH9hF6qUbvAp2l3rpA8fAvnL9vQzOgP3gLNgfFsLLxY8KJF38/Ub8iIQ7PeJkT5fzaqb4kSPzu7nwauiAk+BsyT9f6qUILoJ3wC1wHtwF58OX4AJYIfG/34cL4VG4BH4M74In4HJYC1eI3ythXFjdPLFjDe+/XBPq8z3AhvnhBsXILaz9z84P76Ks+xG7eeKy2uDMFR+sNc8X12DTc844pDT0e503PltbN3fcFTve5o8H83/XHHJ6aWhQ55HDT5nnknueMs8nF5aGfm9zyiNO/WfmlVeVhv7gMXa3accQOYGE3UtbQ5KQHGQVsgs5jpxDou9jzxGSghQi65By5CBSg4SvZY56beM+o/+mzw8x/6+95ysY8f+6y/z+wC76/P6YoaMT0xLHpIwzzvFr6VqSbp4i3cjE8cy3ZuVqSXtLup3mdKyfTUkcN2Zokp6QT3vS9ojhntaZViuYs1hpU6fWrSk4nxp0jedVKmP3IQ/IvJ6HQ4Gs1y/tYr9eP16xnn4RPodsVtidqC2r9388d4HiHU9lCnsL+U+cyl6A6ycWKGLvRdvMxZevV9gLcD4+3Uu9Fivm4xdrc3WqcgYwJ++Ky3Taplzpkr+qYfqzvttVtkpr2dzrX8Ksx3CJNq/jaZvW4o9N1/GLU8w9H1TY6sx/Sj1sBbpfJk7RVjJlbv0GsZWILKVc5Z62nBPsmVn5AdrL4ya7lXGOkiyM6wWKwup+89w/cMQmbmHEFrNfgfQJZ70c3/gLrG13WQxl8LAXyP4dV95dZR7+HYl/tQ+uIO8Ez7wdrMwv9CeO2Pktjz5ojduXi0eTHe76fgTrWufruT5j1uSMgizYXOKIOTgGU+S7K1Zfjnyvke/T5fs5SV8g38/K98keZd4lZZ6NNENykVWUueQhjzKzEsWfeSt97p48ivPcZYxzldHgH78xj2x+z9p+yby9PKtGwdXkFfFw3bv8CvL6p7FohOto2pSMPKbExKcIP3zqhwXm7PQ5or+IfalfqT+PWHuzZM5Lvk/Nn0UVmY8B54RzTukVp4+MeUTVzTFFlJm/r/L4/p7H9z/o383HKEUxr1+qnftbDfP6cpz8afPuY+T/vP5VrjU+Cl/Wkk+1xRe5fgQwx3pvAP7o/X1TxT4irb084prvrV/dxLX0vYepWmF7A18SdNv1r4sFXuxfIefKHpmLXynn7lJkM/YdbvvaKScniu/+KkpsbyIPLWCinK9uHwzH45x+vphjH+Y4p+jdsQ8fJC/JSu+nRmJsjuc5JMf1einbQJnHbyl12wKZrfXzjzrLVndxKJjpWcEB73lcQZny0NBs3yi2K8R2lNiOFNsJPmwTnbFB9l19YM9m1rJvxX76o6Z3Tf50aNIErnNF9Ee+93a57D1MPgUzzfa2N7PGoXyUdCUqe6w5KAog/qTYs8TvNdZ3dHPrPcQ29Mp0++NThg4blTb2ekuVu3a3+fTH2LbWNbfW73bslfthryjX/7I/LmU3lrVPC2td7yBdlW/brublt33OY1Psz/wYY+xPc51UKPzaSfpaP/ziZacB+yTtgfYv7zo11NGICKsvz6AXsc2nL87WGcj5IMfIJh649LMR6r4oXvyx9AQBxmilDvDBvM+za0vrOfEsNpPtbNY=
*/