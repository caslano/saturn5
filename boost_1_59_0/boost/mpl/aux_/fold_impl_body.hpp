
// NO INCLUDE GUARDS, THE HEADER IS INTENDED FOR MULTIPLE INCLUSION

#if !defined(BOOST_PP_IS_ITERATING)

// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#   include <boost/mpl/limits/unrolling.hpp>
#   include <boost/mpl/aux_/preprocessor/repeat.hpp>
#   include <boost/mpl/aux_/config/workaround.hpp>
#   include <boost/mpl/aux_/config/ctps.hpp>
#   include <boost/mpl/aux_/nttp_decl.hpp>
#   include <boost/mpl/aux_/config/eti.hpp>

#   include <boost/preprocessor/iterate.hpp>
#   include <boost/preprocessor/dec.hpp>
#   include <boost/preprocessor/cat.hpp>

// local macros, #undef-ined at the end of the header

#   define AUX778076_ITER_FOLD_STEP(unused, i, unused2) \
    typedef typename apply2< \
          ForwardOp \
        , BOOST_PP_CAT(state,i) \
        , AUX778076_FOLD_IMPL_OP(BOOST_PP_CAT(iter,i)) \
        >::type BOOST_PP_CAT(state,BOOST_PP_INC(i)); \
    typedef typename mpl::next<BOOST_PP_CAT(iter,i)>::type \
        BOOST_PP_CAT(iter,BOOST_PP_INC(i)); \
    /**/

#   define AUX778076_FOLD_IMPL_NAME \
    BOOST_PP_CAT(AUX778076_FOLD_IMPL_NAME_PREFIX,_impl) \
    /**/

#   define AUX778076_FOLD_CHUNK_NAME \
    BOOST_PP_CAT(AUX778076_FOLD_IMPL_NAME_PREFIX,_chunk) \
    /**/

namespace boost { namespace mpl { namespace aux {

/// forward declaration
template<
      BOOST_MPL_AUX_NTTP_DECL(int, N)
    , typename First
    , typename Last
    , typename State
    , typename ForwardOp
    > 
struct AUX778076_FOLD_IMPL_NAME;

#if !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)

#   if !BOOST_WORKAROUND(BOOST_BORLANDC, < 0x600)

#   define BOOST_PP_ITERATION_PARAMS_1 \
    (3,(0, BOOST_MPL_LIMIT_UNROLLING, <boost/mpl/aux_/fold_impl_body.hpp>))
#   include BOOST_PP_ITERATE()

// implementation for N that exceeds BOOST_MPL_LIMIT_UNROLLING
template<
      BOOST_MPL_AUX_NTTP_DECL(int, N)
    , typename First
    , typename Last
    , typename State
    , typename ForwardOp
    > 
struct AUX778076_FOLD_IMPL_NAME
{
    typedef AUX778076_FOLD_IMPL_NAME<
          BOOST_MPL_LIMIT_UNROLLING
        , First
        , Last
        , State
        , ForwardOp
        > chunk_;

    typedef AUX778076_FOLD_IMPL_NAME<
          ( (N - BOOST_MPL_LIMIT_UNROLLING) < 0 ? 0 : N - BOOST_MPL_LIMIT_UNROLLING )
        , typename chunk_::iterator
        , Last
        , typename chunk_::state
        , ForwardOp
        > res_;
        
    typedef typename res_::state state;
    typedef typename res_::iterator iterator;
};

// fallback implementation for sequences of unknown size
template<
      typename First
    , typename Last
    , typename State
    , typename ForwardOp
    > 
struct AUX778076_FOLD_IMPL_NAME<-1,First,Last,State,ForwardOp>
    : AUX778076_FOLD_IMPL_NAME<
          -1
        , typename mpl::next<First>::type
        , Last
        , typename apply2<ForwardOp,State,AUX778076_FOLD_IMPL_OP(First)>::type
        , ForwardOp
        >
{
};

template<
      typename Last
    , typename State
    , typename ForwardOp
    > 
struct AUX778076_FOLD_IMPL_NAME<-1,Last,Last,State,ForwardOp>
{
    typedef State state;
    typedef Last iterator;
};

#   else // BOOST_WORKAROUND(BOOST_BORLANDC, < 0x600)

// Borland have some serious problems with the unrolled version, so
// we always use a basic implementation
template<
      BOOST_MPL_AUX_NTTP_DECL(int, N)
    , typename First
    , typename Last
    , typename State
    , typename ForwardOp
    > 
struct AUX778076_FOLD_IMPL_NAME
{
    typedef AUX778076_FOLD_IMPL_NAME<
          -1
        , typename mpl::next<First>::type
        , Last
        , typename apply2<ForwardOp,State,AUX778076_FOLD_IMPL_OP(First)>::type
        , ForwardOp
        > res_;

    typedef typename res_::state state;
    typedef typename res_::iterator iterator;
    typedef state type;
};

template<
      BOOST_MPL_AUX_NTTP_DECL(int, N)
     , typename Last
    , typename State
    , typename ForwardOp
    > 
struct AUX778076_FOLD_IMPL_NAME<N,Last,Last,State,ForwardOp >
{
    typedef State state;
    typedef Last iterator;
    typedef state type;
};

#   endif // BOOST_WORKAROUND(BOOST_BORLANDC, < 0x600)
 
#else // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

template< BOOST_MPL_AUX_NTTP_DECL(int, N) >
struct AUX778076_FOLD_CHUNK_NAME;

#   define BOOST_PP_ITERATION_PARAMS_1 \
    (3,(0, BOOST_MPL_LIMIT_UNROLLING, <boost/mpl/aux_/fold_impl_body.hpp>))
#   include BOOST_PP_ITERATE()

// implementation for N that exceeds BOOST_MPL_LIMIT_UNROLLING
template< BOOST_MPL_AUX_NTTP_DECL(int, N) > 
struct AUX778076_FOLD_CHUNK_NAME
{
    template<
          typename First
        , typename Last
        , typename State
        , typename ForwardOp
        > 
    struct result_
    {
        typedef AUX778076_FOLD_IMPL_NAME<
              BOOST_MPL_LIMIT_UNROLLING
            , First
            , Last
            , State
            , ForwardOp
            > chunk_;

        typedef AUX778076_FOLD_IMPL_NAME<
              ( (N - BOOST_MPL_LIMIT_UNROLLING) < 0 ? 0 : N - BOOST_MPL_LIMIT_UNROLLING )
            , typename chunk_::iterator
            , Last
            , typename chunk_::state
            , ForwardOp
            > res_;

        typedef typename res_::state state;
        typedef typename res_::iterator iterator;
    };
};

// fallback implementation for sequences of unknown size
template<
      typename First
    , typename Last
    , typename State
    , typename ForwardOp
    > 
struct BOOST_PP_CAT(AUX778076_FOLD_IMPL_NAME_PREFIX,_step);

template<
      typename Last
    , typename State
    >
struct BOOST_PP_CAT(AUX778076_FOLD_IMPL_NAME_PREFIX,_null_step)
{
    typedef Last iterator;
    typedef State state;
};

template<> 
struct AUX778076_FOLD_CHUNK_NAME<-1>
{
    template<
          typename First
        , typename Last
        , typename State
        , typename ForwardOp
        > 
    struct result_
    {
        typedef typename if_<
              typename is_same<First,Last>::type
            , BOOST_PP_CAT(AUX778076_FOLD_IMPL_NAME_PREFIX,_null_step)<Last,State>
            , BOOST_PP_CAT(AUX778076_FOLD_IMPL_NAME_PREFIX,_step)<First,Last,State,ForwardOp>
            >::type res_;

        typedef typename res_::state state;
        typedef typename res_::iterator iterator;
    };

#if defined(BOOST_MPL_CFG_MSVC_60_ETI_BUG)
    /// ETI workaround
    template<> struct result_<int,int,int,int>
    {
        typedef int state;
        typedef int iterator;
    };
#endif
};

template<
      typename First
    , typename Last
    , typename State
    , typename ForwardOp
    > 
struct BOOST_PP_CAT(AUX778076_FOLD_IMPL_NAME_PREFIX,_step)
{
    // can't inherit here - it breaks MSVC 7.0
    typedef AUX778076_FOLD_CHUNK_NAME<-1>::template result_<
          typename mpl::next<First>::type
        , Last
        , typename apply2<ForwardOp,State,AUX778076_FOLD_IMPL_OP(First)>::type
        , ForwardOp
        > chunk_;

    typedef typename chunk_::state state;
    typedef typename chunk_::iterator iterator;
};

template<
      BOOST_MPL_AUX_NTTP_DECL(int, N)
    , typename First
    , typename Last
    , typename State
    , typename ForwardOp
    > 
struct AUX778076_FOLD_IMPL_NAME
    : AUX778076_FOLD_CHUNK_NAME<N>
        ::template result_<First,Last,State,ForwardOp>
{
};

#endif // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

}}}

#   undef AUX778076_FOLD_IMPL_NAME
#   undef AUX778076_FOLD_CHUNK_NAME
#   undef AUX778076_ITER_FOLD_STEP

#undef AUX778076_FOLD_IMPL_OP
#undef AUX778076_FOLD_IMPL_NAME_PREFIX

///// iteration

#else

#   define n_ BOOST_PP_FRAME_ITERATION(1)

#if !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)

template<
      typename First
    , typename Last
    , typename State
    , typename ForwardOp
    >
struct AUX778076_FOLD_IMPL_NAME<n_,First,Last,State,ForwardOp>
{
    typedef First iter0;
    typedef State state0;

    BOOST_MPL_PP_REPEAT(n_, AUX778076_ITER_FOLD_STEP, unused)

    typedef BOOST_PP_CAT(state,n_) state;
    typedef BOOST_PP_CAT(iter,n_) iterator;
};

#else

template<> struct AUX778076_FOLD_CHUNK_NAME<n_>
{
    template<
          typename First
        , typename Last
        , typename State
        , typename ForwardOp
        >
    struct result_
    {
        typedef First iter0;
        typedef State state0;

        BOOST_MPL_PP_REPEAT(n_, AUX778076_ITER_FOLD_STEP, unused)

        typedef BOOST_PP_CAT(state,n_) state;
        typedef BOOST_PP_CAT(iter,n_) iterator;
    };

#if defined(BOOST_MPL_CFG_MSVC_60_ETI_BUG)
    /// ETI workaround
    template<> struct result_<int,int,int,int>
    {
        typedef int state;
        typedef int iterator;
    };
#endif
};

#endif // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

#   undef n_

#endif // BOOST_PP_IS_ITERATING

/* fold_impl_body.hpp
1YOjpIbuFqZUaHgCTZy9zqtuc3LdBgOiaShNydEfBwk5DFF2W4N1yOtVm0M93Cq2//zjYDPbC/dkmE0vCuQyZyTjhoIbMsp73TOR5DVlaGv2wctkElLpXFvXU3DTbrX+4+hd817uuHCZ+ddB3xIDoBt12SmYIexIa+Lza2a/raJ8c6pZvW06rBFR08Jv+p0pTt727u94RK26THuUbi9DqvIiESGi0KOtbAinuCCDgIJEZYGBgv4LRO4uzSqtCm4WrrOPoN9Ub4nowW6geET+s8+sT3gmWhCduFfiw09wC0oMZvJEgYgSWhOp9OkoTZ7ewgRdY6jqG6oES4ju0UU/xKQh0iSqANqBSqSsEs7gtFA56Y5BRfrNsNcjqrrXft6OHw+g8j+NJaJW8mOyTxM+NyFLD1ZKETKWkVyzkOgpv6q7Zl3EvYm0imx/ipLvFsGGRhkfqMf4jef4CqhhXOmAipW/HFDMdk6HViXTJkGGi2xJWwx9Qjc1S8UqhAsJ7YJxwwgE9j4hqq3pvHl8/lEnIgoUrr75EA9uww3VO4YS5WqlwjCi2Pc7rOhhe+PstpRJ91Ta8Sl6AAIXnGndfmYLW1J6kvaCtytsxDhVajPNDBaA3YR1wZLdpM7HYKThJG4oDC6d6hYPuOA4FgbwPesioXpznPUjhyw1hswQHRBG1r1OGA+rBUnCCPYAo/CusJOuQZ+PNI2j99fA2FbAPe2L/9i3M9GcclS5m8gEdrl6ekde9/lzO6uchfCg3ggobsAI6J8lDFZLsn53NZfWt2rNI2a5cZFiH/nqI0kD3Poo0Pr41IZRJHujrQuFDM8AB7tuBvCWJpn+iy8RpUz67jAVjBBwS5RKhebRn9bLVrqQ6qIX+FfnGZU7BTxqrmFIPwCSSOq1EwXZLWhDkOoA5iGk+87+8v5y0N0eyQCnKHk45rSpU93Tiz7i6dS/BXWfLjQaYYRqxgeE8yZjfGnsW8oCJ7nBDFCUVrTnlaKIKmJQO1VhTmBnGZpglRQFvogJ5jApyDnIj7N+8CixUKm8VrR7qTZm6Q0VqVSyNDdoXBUWBuUVk2fF5w3XmSOV6p+e6pJWEYVSC5ssrsChahjq2GeDzAB3TXN1AkFvOB5tiAazULEJ0Oy9yAbKahdX1z8YxKeD29v45cnsAjECKpNWck+tTEgJZjCgKlDMSCHISpTs958exGOHiWos8/TfHVljdv8HbICTfwTO80k6u/uywlAQqNXusxfTxmb12fWuK6vvmr/XKaaqXEsj1Br1WXQrcwHs7IUo4D0uG7eppEQJNidv3p64qm2o97sevT3Wfm/CcTjhPfiyeGC2dFegMg0sXozt4oFoqxBiqZtoC5+Vzfju9ssPr/193g2YkZg9yJUnM3to9V0Ps5BuDUBTM+krCGd+38rzBAhdDGc323vBRa2ArLmETfg+tAySS7RMWO0ZasbIeaI3HeXeWQ1X8Iq0jqjOOl9EX8M15+h8MEzICzGaMLt1bjBQPPpKDZB2m/5uIxQdOHVIZXQXJ3TeauAICsUzaWES6ANM3pln0RjjLrHfenQXKdk6syo9KrbYffZzS6RUImNKuFQIR+Hi6pJhGnGbHS5YRmwqac5MBKfkSpkvRdFiHk3JVdsXyE0XqRQLRd1ya01movJ/vIecaw2XEJyN86SD8VJKxkkhRFcVHamNBRxv3tygTLx6ldj3PVf7yCfPP2DX9ZzGxLYIt3cH7u7uOBwOlGIY2zCNnE6jGcgWlmbFO2ETIv3Gc5iOdv4p2e7nzCNpj2Ywg+10iFekmLEN6qiW7Wzyr919a0vwbpihqvMCbvN5fv4drKLxtRrbX2ZPoUUSi1IjVXUTUCU55vKGlM14dnHDy29v+PjDD9Eysu22eISSPVlGhEQnW3LKpBX0YbWKy/lrxcXqE/VMdT639u+HRaProOd9dJmH42EX/oB0uHqfYwmH18eze+cXo7PCm8x3XMBqqf+bx391nutjBmt3s7po9XNF+OzsqtQ0u+E/3neG6dQMmBkXT1cb7vkQcSJE7+ijaR/H+v4gDhdtx46dpw+OLloZRhcdIQi7aJo6XRDCWkRP7FzeM//OHgHDb2MM9N6x3URUd7Pmck6FlKfagiSTk4UdudaepeNASolpygxTZkyJVGDKiWmaGCdlGpUhQ8Ha/Go5Md6/poxvmfyOIJGUrWXxkJWSE+iE84YxlWLeQU5W/5Wqp9Da8DaQVJrfjvVzE3FMJqi9wjuYBc600nwttjftoeis/YuqGbDDODKOI9eXl2y2Hi0DY2WWf/nF11xeXnL16JrtdgcIaapV/yqM95b9KzhrNoBYY8xKbisYX8hVzCvlXF3xYsa1Ts8m8Nfuia3E9+MHMy9F2jRodXY2R+eaqzZS71lY5zjEIlVhIZbW49XXpXmSGMaiWk2Wgb1SrGbR7pInjxOqwi9+9YJ//7Pv4WNA05HoPUPxpJKtNRWWsWtJHsPzVo8mlauLtzR7mfOj8FBFYDZe3xWGPTDoXtzZ+5lHr+Ktdct7N+u2lJHAuUfXxmltvNfn07oYu/V76/eFsZRKWdd5t06TSZm22qyGgGcp5vGoiXgFL2QSxWHpyGBgc9TesmIIk1PICeesb1cIsO0cXRfY1JY0fWfi9zGa3JQEk0iV6vXYDgf/LmGYXViZXVQnQmypxjq8dlM7E6xPiWGYOI3K6TQyTiOTCodUOB4HhrEwTIlhKoxT5jSNTHlECQwTnE6FkhM63fHmeAenA6nf0p0ciYlQTJE3a6YkY5THYqJfuQjZSa0TqkL2WnAu0NKiDTBvve4bP6dNqDNOTQVwnTNszKnDUSz0SyN9iGx3e06nEXEdb2/uub7as+0cl5eX3B8nhuOIc/eowLNnz9hsjC80nSamkvE+ksVZGFKVDsVYiyQtpjM9DnROiMGfbWYtW1qKscOTM2/S+5pMUKm77Hkt43oRnIHIFS97X2nBvFDWu/m8GN08nvN7KrY5h171tdZdt6lEIAIp4Ythoz4GJCm73Z77w4mrx4+J3YagI71XRlVTUignci74rkclLee6wrlkdT7vuwabEzY+jXi4zhK2DM3DcGwes2LX2Xh7zRMsK8MBkCuw7eTcgLVjzVrUD8IxxNCslgJYg9uNHCoN/2zAuWJlG1YXZRbSewupnMii+1GrbBv+I4qFXiJ4Z6zR6JUuiqVbRemCmrHpPSFC1zv22956kavQ9z39JlqKPnpCjDQeRq6RfR1SqjXh3/VR8mQiaG1SzTfTMsnjcWAqeS5FOBxPHIeJ0ylxOg4cUmIcE+OUmTIMY2FKylQXzxQ6hsORaQTvtgQv3NwcefX2jtPtDR9+/1Mk7kjDCSkO9a4yssy0nrJl5LR6PU0d0QBIYabMU4ghEoKbK8ZTMoPUwrF1Cjq4SiVQoSTbUq1o2M3Dp9X977xnGA5o8lw/vma323B/e8P9YeTxo0uC8/jdji54A8RjtP7r1YhAWzhlDpCLEwixynoY38smZfPuzINzLuBae2oJuCigxUQ5cWTKexMra4NytvhUjBD6IBR7X6ixPNxqnJeHGavmgdYK9HYVQsXWPOIimVz1hxIqnrc3I4dpIMaeK+/ZbU7c3NwRugtSGcGLBZKyZiSvcK45jKmLV42Tt/B2zNttFAVYhYxiXlTDkd7xYpTVOjj3nB6OQft3K4ltWcLZI9V332uOQvNIl+fmrhu6AqQXmAuAEERmkFkEq/4uaQ61zKMwsDA6q9ruGobTBbrgicERo6eP1vhw13uiD2wrxuMi1lO96+i7juhCTc1XtUERUrEbXYqC93P2Yo4hVxf9XTFvezgfqdRKxgwpG+v5OA4WTg3WYnkcE8M4cRrNW5iSYTyptmXGBYsZXEKNd4BmJU2W5r/YCnkcuXv9gq9++f9xePOakMwQxNgxpglnPj7izXBPa71qFZw23WRnZRtiN1/E9I1sU3Dz7uacq33GFuB07Tqb61sLZCnE4LnYdeQkNcQ0edboPNfXV1zsPFfbCPlEjJ4PP/6Iq8uOLnru75uoXMDtAscpMY4nfAVbXQXqU0ozzmM7bCGlXGujHMXK/5eJqYUi1lFkTBNpClBMrI46BsBc4d0es9fgzr0Fm/uu4iZLB413Pae6SErVzqnBx/xahaJaRXsTRXO09jkV+BVnNAsyqRQ675EYGY6Bm7s7Li4uuPv6czZuMKnitMVLILjEMMnSqXjVTspiwWWM7Hf1mCo5sT3OF/7718A7Bvg7Pl/es5TeAfXnSGI+QgWYzz+jeu5xWmH3gqS8J9oGIHi11HugaUJD8MEA5CpS7yprOvpAFwJBrG6rq16UF3tP542HMimkKTGmCRl9lYAVPAc7cdckW8/bPLfsztZHog/VsNlvy7QAf4cBAuslAZAKDEmZsjJNhWESThMchyPDMDFOhSkLp2FiGM1QTUUhCTk7xmxGakiZVHGbaUx0OIre8e3rr/nm819xf/sNdy+/ZOM6pqPn7etv2TwZCWQ6Z+OBK6gEppLOjJDXpepZqJPNVTJnNfaN2Ni8UVkTSFkWG6WVU7RMmLGk+z6iwTGOMJWJ3nfsukjvlGdXW3a9qTjmdOLpJ5/yyQd7ttstL7/5ksPdLYfDgVa1H7qINtJmrWb34sxTFU8p2UpivKPz0XbmXMtsxPCbXDLaGNY5k9URxFePvHpCbTH4JexoJD5pxmJ97bTMkIUtD8PUtnkZ5CBQqSYtwyYVjyMXslRyLRW0rmTRetNIjrkbSpoSffTknBmnwotXL/jk+hF//mf/D8U7OnfJmE0KI+tIZulrRwunyGcL1Azpqoi1YX/1decWBYWHYZuqUhxLse6D9z0MW+V9IZe3DN87xns+jzqGNWHViIrNKqlaWVS168s5VkhFVmUwIkK4utgshqYahigg4i1tidSkVGGaCkmmKnQNqiPNZfXIbEhyZUv7ml2L3tGKV2OwCRucufhdhC5Y+NZH4xqlrrB3SpkSBWHEERT6oHTOJq0VkHL+EGhA+6SmiJAopHxCFaaSKdKxkYQLpv1zezyZpyLClK2J4sZ5pExkzQSUhDCpKRYWL2QdkUn42Z/8KWF7yb/30z/i7rc/4+dfvmDQkZe//gU/+N5PeBsueDUeue4eM2mghDuEbo61287RsBxVrf2zlNiZGmPKo9EfQi3vkFKbBtiUzNNYWdw2/jFGxqEQu0LJR/rNJS30OB3vCcFxud1yOr5hdx3prh7z7e0tuy7y9378Az58ukOCsb9TSgbWCxyOd4zTYMLrVXWwwNybrpSC10z0yi73qPuScfiYrt+Ry2skb+i3UJLSRciaIQaO6vBug2oiSUGy0ktP0WxqiVKzWGLhnsOhKZ8Zn7P6MBEgzhKtBvC3nmSlgr7VqwR7Hysw25nkb5MzhVZ0uUw2nwLZH+lcRxBvJMsIux5+/fPXTPJbXn7+S55/+ily/Jp+9yn3MlJyoPc7kh5Nv6edr/plkVs0vhhRzGubsZiVYVkboyWrZ2ulPYo04ibLffKtb1mlrHBuZMRni378YmAaQC7OkTB8yamwHF5q1xkhu9X9aPZHmzlaNpg298P9kIBSC0vtxVnUSB9YTmepUVc9n9aPrB3QZxusLkScU7wXQuVFuHbTM0QKWTy+7YRi3IzUXGfvmCY3G0dcABKxdgfws3t4DoxJ3ZVzlTY4npJltMZcQ5FCLglXzgeixea+YmGhM8+QE0y3BZ0SrkDIzoTOdhtefPE1stny2fd+xDAWXp+O+NhzvXuMn5Tf/OZvePzj/4CL7QWaBqu5kjh3wGxGqIEfD/kbJet8/U4x70GXGr3GFWmtfZohSymx6XtyGdhu9uw3Ww5396SU6LrAxcUFmiacKFdXV6RUePv2lo9+98fsL644jhO9BHCOaaxhlgTQgK+hYKxFwJOawiJY1hMtpHHi6ePCf/6P/zP+xf/8Z5yOd8StUnzgMI3EuCE0gTJV42CVYtdTN6/G0RG7ScskLg8zOkt4fo4HKcseLEvDAmkZreUxL+R1aFHercey5LM9olg56mk6EcMVji1uusXzml/97F9zuBj4yU9/j4Qgt99wGH/N5vIza7aQ7wzbWZVpzMZ0Prd1AqYlLRYm/UPgebn2xfuz451n1sybdLNRmceAd6rT7PkH5zcf36yn3b/33A/O3v3u45wnBeEwNs5PBTtdqeJfbpZlhMpQLUJx1hxQam+ilKWWYQiq5jtpyngPQU0Q3Cy7EorF7Wb3szFPnfULy6JMYnVS6ia8KuqtK6nX0cI/31Fam+Y6qRoCILLEnaIFcSbDMVVLP4y2QAx3UCugLGYUUw0XVM3S53KqwC/W0NE50wISbCGOps2zf/oBTz/4hJuXn3OXLKvVba94/njDl1/8hkff/wMLrXRkE/dEH0g6cRymavwWnGftDbmZBWPkTyeGWTXlxFbAKSKz9kwpWlMQphO928TK9B4Zp5NhdH3HpvN4N7HfXxKc43g4sdte8vrtHbc3r7jad/z0939ECIGbmxvubg+MYyJNQE3tjqejAf+lEdSg844Ye7Z9pIuJv/355/ShJ4TIUE50fsMwKVE70IkmZzsbl5px8VR9nZmzsxSY2qJ9F9toC2XtFdhzFSxtGNNq4jfs4n3pbFlxmtqxWS1nlYKnA29Fty4n3PiSy/gWd93xw598hi8bjnf3PL6+5HT3LZo+JeWIc0fmDqorb65liv6uxxoTXRujxdNYeVSsoaD3j1t7tNR5rkcpqtb84cHmOL+XWuL04HiufqeFZ/U5tfc2z7/Icp8ECLm46gG5GeBzQQoYzgAAIABJREFUY6NmrzwNkSoDCi4GuyVqchii5pqh4LwBdpalqa2V3crd1LpgcGQxQ5ScEd6s95f1kJeilBgRnwmlinJrRGqBY6PPTzmhTuhdVa+DGfQTp6TBjEuuNy2NI6noTEJsXUynqbaRzplOU02dg0gwMp0mkGzV4scJp4UPPv6U3/zmV4RyQkLH7esbnj3e0W/39P01Pm5JqdB1G7ILpHRimNJ8G60y2+6a1pAKmHWAZjDUWQdWnVXpSg11LZlgWkSm1+1CBf2dWvmM9/QxLnpQomx3gav9BX0XePX6LSklbm9v+eEPPuHRxcZEzHLmdDrN7nuI1hEjBE/w27O2MTlnhmGodXjK69Lz5c9eQn6EBI+mTJkSuxAhJ9RbmB+aYJ5zc4ZwFu9vOZZKM9A6TqKQqxF+uNXO/kD7o/aMmxeKVOLfXI0ttA6p3/Ww8Mjma6k1V1NQJFm4TBnpZaBzN8ROOOan/Ojv/Ud8/vNfoJLYuAtc+RrNEKQncY+v9ma9eOe/y/uNxUMb9a7BXUKz93lA9p6HV/p+Y/RvIVzX98h8P+Z6tfeA5K5lGaUZourhtuuqxiporjIRzt4sCmNz2SpT18lyMLwQUpp35LlDWlFUiwmtdy2eLeY9lURwNdGErwr+tshTUWQqaGgYyXKpKgXvMzgMEA/BPB7vGMfEcRoZKwiZQqRzwiYGQNCSid4zDQeyOuM+VSx1GjNTUcYpMSV7PmmxAte6E1obnMQ4KSnZAEfXRi5ZNw213uO7rfDVN5l+ewE+cDco+8tPyOIpTGTdkrTgwoTTnjxNM86BLsDpw0cpViQaO4g+oprnsohWluIRsqR57nrv
*/