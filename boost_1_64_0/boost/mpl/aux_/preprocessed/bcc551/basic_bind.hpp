
// Copyright Peter Dimov 2001
// Copyright Aleksey Gurtovoy 2001-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/aux_/basic_bind.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

namespace aux {

template<
      typename T, typename U1, typename U2, typename U3, typename U4
    , typename U5
    >
struct resolve_bind_arg
{
    typedef T type;
};

template<
      int N, typename U1, typename U2, typename U3, typename U4, typename U5
    >
struct resolve_bind_arg< arg<N>, U1, U2, U3, U4, U5 >
{
    typedef typename apply_wrap5<mpl::arg<N>, U1, U2, U3, U4, U5>::type type;
};

} // namespace aux

template<
      typename F
    >
struct bind0
{
    template<
          typename U1 = na, typename U2 = na, typename U3 = na
        , typename U4 = na, typename U5 = na
        >
    struct apply
    {
     private:
        typedef typename aux::resolve_bind_arg< F,U1,U2,U3,U4,U5 >::type f_;

     public:
        typedef typename apply_wrap0<
              f_
            >::type type;

    };
};

namespace aux {

template<
      typename F, typename U1, typename U2, typename U3, typename U4
    , typename U5
    >
struct resolve_bind_arg<
      bind0<F>, U1, U2, U3, U4, U5
    >
{
    typedef bind0<F> f_;
    typedef typename apply_wrap5< f_,U1,U2,U3,U4,U5 >::type type;
};

} // namespace aux

BOOST_MPL_AUX_ARITY_SPEC(1, bind0)
BOOST_MPL_AUX_TEMPLATE_ARITY_SPEC(1, bind0)

template<
      typename F, typename T1
    >
struct bind1
{
    template<
          typename U1 = na, typename U2 = na, typename U3 = na
        , typename U4 = na, typename U5 = na
        >
    struct apply
    {
     private:
        typedef typename aux::resolve_bind_arg< F,U1,U2,U3,U4,U5 >::type f_;
        typedef aux::resolve_bind_arg< T1,U1,U2,U3,U4,U5 > t1;

     public:
        typedef typename apply_wrap1<
              f_
            , typename t1::type
            >::type type;

    };
};

namespace aux {

template<
      typename F, typename T1, typename U1, typename U2, typename U3
    , typename U4, typename U5
    >
struct resolve_bind_arg<
      bind1< F,T1 >, U1, U2, U3, U4, U5
    >
{
    typedef bind1< F,T1 > f_;
    typedef typename apply_wrap5< f_,U1,U2,U3,U4,U5 >::type type;
};

} // namespace aux

BOOST_MPL_AUX_ARITY_SPEC(2, bind1)
BOOST_MPL_AUX_TEMPLATE_ARITY_SPEC(2, bind1)

template<
      typename F, typename T1, typename T2
    >
struct bind2
{
    template<
          typename U1 = na, typename U2 = na, typename U3 = na
        , typename U4 = na, typename U5 = na
        >
    struct apply
    {
     private:
        typedef typename aux::resolve_bind_arg< F,U1,U2,U3,U4,U5 >::type f_;
        typedef aux::resolve_bind_arg< T1,U1,U2,U3,U4,U5 > t1;
        typedef aux::resolve_bind_arg< T2,U1,U2,U3,U4,U5 > t2;

     public:
        typedef typename apply_wrap2<
              f_
            , typename t1::type, typename t2::type
            >::type type;

    };
};

namespace aux {

template<
      typename F, typename T1, typename T2, typename U1, typename U2
    , typename U3, typename U4, typename U5
    >
struct resolve_bind_arg<
      bind2< F,T1,T2 >, U1, U2, U3, U4, U5
    >
{
    typedef bind2< F,T1,T2 > f_;
    typedef typename apply_wrap5< f_,U1,U2,U3,U4,U5 >::type type;
};

} // namespace aux

BOOST_MPL_AUX_ARITY_SPEC(3, bind2)
BOOST_MPL_AUX_TEMPLATE_ARITY_SPEC(3, bind2)

template<
      typename F, typename T1, typename T2, typename T3
    >
struct bind3
{
    template<
          typename U1 = na, typename U2 = na, typename U3 = na
        , typename U4 = na, typename U5 = na
        >
    struct apply
    {
     private:
        typedef typename aux::resolve_bind_arg< F,U1,U2,U3,U4,U5 >::type f_;
        typedef aux::resolve_bind_arg< T1,U1,U2,U3,U4,U5 > t1;
        typedef aux::resolve_bind_arg< T2,U1,U2,U3,U4,U5 > t2;
        typedef aux::resolve_bind_arg< T3,U1,U2,U3,U4,U5 > t3;

     public:
        typedef typename apply_wrap3<
              f_
            , typename t1::type, typename t2::type, typename t3::type
            >::type type;

    };
};

namespace aux {

template<
      typename F, typename T1, typename T2, typename T3, typename U1
    , typename U2, typename U3, typename U4, typename U5
    >
struct resolve_bind_arg<
      bind3< F,T1,T2,T3 >, U1, U2, U3, U4, U5
    >
{
    typedef bind3< F,T1,T2,T3 > f_;
    typedef typename apply_wrap5< f_,U1,U2,U3,U4,U5 >::type type;
};

} // namespace aux

BOOST_MPL_AUX_ARITY_SPEC(4, bind3)
BOOST_MPL_AUX_TEMPLATE_ARITY_SPEC(4, bind3)

template<
      typename F, typename T1, typename T2, typename T3, typename T4
    >
struct bind4
{
    template<
          typename U1 = na, typename U2 = na, typename U3 = na
        , typename U4 = na, typename U5 = na
        >
    struct apply
    {
     private:
        typedef typename aux::resolve_bind_arg< F,U1,U2,U3,U4,U5 >::type f_;
        typedef aux::resolve_bind_arg< T1,U1,U2,U3,U4,U5 > t1;
        typedef aux::resolve_bind_arg< T2,U1,U2,U3,U4,U5 > t2;
        typedef aux::resolve_bind_arg< T3,U1,U2,U3,U4,U5 > t3;
        typedef aux::resolve_bind_arg< T4,U1,U2,U3,U4,U5 > t4;

     public:
        typedef typename apply_wrap4<
              f_
            , typename t1::type, typename t2::type, typename t3::type
            , typename t4::type
            >::type type;

    };
};

namespace aux {

template<
      typename F, typename T1, typename T2, typename T3, typename T4
    , typename U1, typename U2, typename U3, typename U4, typename U5
    >
struct resolve_bind_arg<
      bind4< F,T1,T2,T3,T4 >, U1, U2, U3, U4, U5
    >
{
    typedef bind4< F,T1,T2,T3,T4 > f_;
    typedef typename apply_wrap5< f_,U1,U2,U3,U4,U5 >::type type;
};

} // namespace aux

BOOST_MPL_AUX_ARITY_SPEC(5, bind4)
BOOST_MPL_AUX_TEMPLATE_ARITY_SPEC(5, bind4)

template<
      typename F, typename T1, typename T2, typename T3, typename T4
    , typename T5
    >
struct bind5
{
    template<
          typename U1 = na, typename U2 = na, typename U3 = na
        , typename U4 = na, typename U5 = na
        >
    struct apply
    {
     private:
        typedef typename aux::resolve_bind_arg< F,U1,U2,U3,U4,U5 >::type f_;
        typedef aux::resolve_bind_arg< T1,U1,U2,U3,U4,U5 > t1;
        typedef aux::resolve_bind_arg< T2,U1,U2,U3,U4,U5 > t2;
        typedef aux::resolve_bind_arg< T3,U1,U2,U3,U4,U5 > t3;
        typedef aux::resolve_bind_arg< T4,U1,U2,U3,U4,U5 > t4;
        typedef aux::resolve_bind_arg< T5,U1,U2,U3,U4,U5 > t5;

     public:
        typedef typename apply_wrap5<
              f_
            , typename t1::type, typename t2::type, typename t3::type
            , typename t4::type, typename t5::type
            >::type type;

    };
};

namespace aux {

template<
      typename F, typename T1, typename T2, typename T3, typename T4
    , typename T5, typename U1, typename U2, typename U3, typename U4
    , typename U5
    >
struct resolve_bind_arg<
      bind5< F,T1,T2,T3,T4,T5 >, U1, U2, U3, U4, U5
    >
{
    typedef bind5< F,T1,T2,T3,T4,T5 > f_;
    typedef typename apply_wrap5< f_,U1,U2,U3,U4,U5 >::type type;
};

} // namespace aux

BOOST_MPL_AUX_ARITY_SPEC(6, bind5)
BOOST_MPL_AUX_TEMPLATE_ARITY_SPEC(6, bind5)
}}


/* basic_bind.hpp
grkdyPiX24+Mh7ljyH0rd0Lrzj2h83HnLoqr89lctYnrF7PxeizH12MNdmMUG7EX9+IINuEUduEs9uECNmDShetVM+bjbViJndiEh7Ebd+EwBvAotqD8ZiCI08RvRhmv3oAnid+AxkWMU5iGt2Mhtkl5MYw7MCbHwV7sxIPYg0dwEKM4irfgBN4q5Uc/LuObpB5K/vvX9fIL1ivHC08rB59mLyXOryLmxULDWBTLmCsny3sew7C9SPqTYaSKVEi6SMVni1RIvjjInFzki7AKcZzrTZziVYg4SzxJ3h9xKaG8JQlLOr966RStNUavuLLIFLyfeAIOozxajmIiHkMTJ9Auzw3okOcMdOI8unAR3fraXa88kIRygDS05Ge6mIH5mIklmIsV+FzcgS+Uvowvkt8EY5m8d8bLpHz4YhzBzXJ8LJff8+AWOd5l69XlWImPPNecej8ESxeTzqkmlWoTrLi24riJ5XHNurj2zriOgbjOY3Fdx+O6Z+J6luMmp12iTSmNq2riPjcW93k9cVMH4lojcTOOxc2cips1Fzd7KW5O6qXagsK4uRVxN9TEzQvEfX6Hlu/b4hYOxC0aibvxWNziKfEptPwxId5GlrQhIWwrNEYvT1G9FSlqXObFpy3qFcQfs9y6sv+pFQ5y6j2coqqOxLe1EuPp+vPr4mmPXXjuME8G9POQabTo5whTtej7iJndou8vZkmLnseblS36ecusa9H3JTPWoufzZl+Lvt+Yw3o7lzmh43bzhF7vMhda9PzYdAT1fcG0kPcaZnlQP++YNUjpzWhQz5PNnqB+vjGHkPct5rGgfo4zp/X2pjkX1Pcrc1Hv5zIdIX2fMrND+r5plob084dZFdLPAaYvpJ+jzFhIPz+Z/SF93zJHke+/zOMh/XxlziLf55mLenunqcL6udPMD+vnTrMM+d7MrNHpptmh4w6zN6zn4eZIWN8nzUkdt5szYSkn+el0t6n26PummSda5Ic8N5vVyP3cDCPPz2Yn8vxs9iPfJ5pjyPeJ5gRynzdnkO8TzQXk8jSTIvr9gJkX0fd7szKin9vMGuR7PTMc0c85ZmdEP9+Y/RH9HGyOad3mNPK9srmotzdNW6t+fjHTW1evl5sZH/oame/jKN6FMu9/C44T34+zeCsu4z2Y1sT9FfPwdViON2AAIyjPA37Jl/ibcQTfhfI753fjJPH34xxei0Yz92FMx8NYjDdhJb4H5XuQu9FH/HrswhAOYj/K88EwHiP+Tjke8SMov6Pow2nSY3gSR+R4u3iOkeNhL5ZgI8q8/zqsJv5WlN89vBEr8E45Pum3YRRvx268Q46L78AZfJPkv5v7OFq4C8twEOV3B2/HHcTfK/WF+6ScOIADuBuP4gE5b+yQcmNA6i/A/EfqBw9KPtgu+eAhqW98n7QjtuDxwFNrXPx3LlUZlnI4zuNdDu+Us9er0UP0Af4tTIy0isPrVUk+9+rO1fPn/XHxPHHGp2Lb4dV0H/cP6T9+tEhvwJL4+scs8TH5yCsMddeLDRW6KD48v2/uXD2nyFl5d8344aj40vnyPYqjBjmeI4CMA44YMs45epFxyzGIjE+OUXFlaWDAHCfux6kvnf/47Vdnbkg7ofPbkI/kt6ECKceGGuT4G6LI8Td0I+PIhiFkHNlwFBlvN0wh48OGeeS9ygbj2+fL+LwhFRl/N+Qj4+6GcmSc2eATVxY/9235XVUDxkjfj914AIdxH05iI85iBxoPnq+aMBubsRQDcv/HFgzjEezCIMrvgjqxj3gIRzCMJzCCC9iKSQ+dr9qwENtle/Y7iBXED0n+eK2UE/diD8ZQ6vmwlPehJ1DfT3ZZsDvrfij5OpwB5Pk=
*/