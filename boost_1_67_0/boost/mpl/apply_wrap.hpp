
#if !defined(BOOST_PP_IS_ITERATING)

///// header body

#ifndef BOOST_MPL_APPLY_WRAP_HPP_INCLUDED
#define BOOST_MPL_APPLY_WRAP_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2008
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#if !defined(BOOST_MPL_PREPROCESSING_MODE)
#   include <boost/mpl/aux_/arity.hpp>
#   include <boost/mpl/aux_/has_apply.hpp>
#   include <boost/mpl/aux_/na.hpp>
#   include <boost/mpl/aux_/msvc_never_true.hpp>
#endif

#include <boost/mpl/aux_/config/use_preprocessed.hpp>

#if !defined(BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS) \
    && !defined(BOOST_MPL_PREPROCESSING_MODE)

#   define BOOST_MPL_PREPROCESSED_HEADER apply_wrap.hpp
#   include <boost/mpl/aux_/include_preprocessed.hpp>

#else

#   include <boost/mpl/limits/arity.hpp>
#   include <boost/mpl/aux_/preprocessor/params.hpp>
#   include <boost/mpl/aux_/preprocessor/enum.hpp>
#   include <boost/mpl/aux_/preprocessor/add.hpp>
#   include <boost/mpl/aux_/config/bcc.hpp>
#   include <boost/mpl/aux_/config/ctps.hpp>
#   include <boost/mpl/aux_/config/dtp.hpp>
#   include <boost/mpl/aux_/config/eti.hpp>
#   include <boost/mpl/aux_/config/msvc.hpp>
#   include <boost/mpl/aux_/config/workaround.hpp>

#   include <boost/preprocessor/comma_if.hpp>
#   include <boost/preprocessor/logical/and.hpp>
#   include <boost/preprocessor/inc.hpp>
#   include <boost/preprocessor/iterate.hpp>


namespace boost { namespace mpl {

// local macros, #undef-ined at the end of the header
#   define AUX778076_APPLY_WRAP_PARAMS(n, param) \
    BOOST_MPL_PP_PARAMS(n, param) \
    /**/

#   define AUX778076_APPLY_WRAP_SPEC_PARAMS(n, param) \
    BOOST_MPL_PP_ENUM(BOOST_PP_INC(n), param) \
    /**/


#define BOOST_PP_ITERATION_PARAMS_1 \
    (3,(0, BOOST_MPL_LIMIT_METAFUNCTION_ARITY, <boost/mpl/apply_wrap.hpp>))
#include BOOST_PP_ITERATE()


#   undef AUX778076_APPLY_WRAP_SPEC_PARAMS
#   undef AUX778076_APPLY_WRAP_PARAMS

}}

#endif // BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS
#endif // BOOST_MPL_APPLY_WRAP_HPP_INCLUDED

///// iteration, depth == 1

// For gcc 4.4 compatability, we must include the
// BOOST_PP_ITERATION_DEPTH test inside an #else clause.
#else // BOOST_PP_IS_ITERATING
#if BOOST_PP_ITERATION_DEPTH() == 1

#   define i_ BOOST_PP_FRAME_ITERATION(1)

#   if BOOST_WORKAROUND(BOOST_MSVC, < 1300)
// MSVC version

#define AUX778076_MSVC_DTW_NAME BOOST_PP_CAT(msvc_apply,i_)
#define AUX778076_MSVC_DTW_ORIGINAL_NAME apply
#define AUX778076_MSVC_DTW_ARITY i_
#include <boost/mpl/aux_/msvc_dtw.hpp>

template<
      typename F BOOST_PP_COMMA_IF(i_) AUX778076_APPLY_WRAP_PARAMS(i_, typename T)
    >
struct BOOST_PP_CAT(apply_wrap,i_)
{
    // Metafunction forwarding confuses vc6
    typedef typename BOOST_PP_CAT(msvc_apply,i_)<F>::template result_<
          AUX778076_APPLY_WRAP_PARAMS(i_, T)
        >::type type;
};

#   elif defined(BOOST_MPL_CFG_BROKEN_DEFAULT_PARAMETERS_IN_NESTED_TEMPLATES)
// MWCW/Borland version

template<
      int N, typename F BOOST_PP_COMMA_IF(i_) AUX778076_APPLY_WRAP_PARAMS(i_, typename T)
    >
struct BOOST_PP_CAT(apply_wrap_impl,i_);

#define BOOST_PP_ITERATION_PARAMS_2 \
    (3,(0, BOOST_MPL_LIMIT_METAFUNCTION_ARITY - i_, <boost/mpl/apply_wrap.hpp>))
#include BOOST_PP_ITERATE()

template<
      typename F BOOST_PP_COMMA_IF(i_) AUX778076_APPLY_WRAP_PARAMS(i_, typename T)
    >
struct BOOST_PP_CAT(apply_wrap,i_)
    : BOOST_PP_CAT(apply_wrap_impl,i_)<
          ::boost::mpl::aux::arity<F,i_>::value
        , F
        BOOST_PP_COMMA_IF(i_) AUX778076_APPLY_WRAP_PARAMS(i_, T)
        >::type
{
};

#   else
// ISO98 C++, with minor concession to vc7

template<
      typename F BOOST_PP_COMMA_IF(i_) AUX778076_APPLY_WRAP_PARAMS(i_, typename T)
#if i_ == 0
    , typename has_apply_ = typename aux::has_apply<F>::type
#endif
    >
struct BOOST_PP_CAT(apply_wrap,i_)
// metafunction forwarding confuses MSVC 7.0
#if !BOOST_WORKAROUND(BOOST_MSVC, == 1300)
    : F::template apply< AUX778076_APPLY_WRAP_PARAMS(i_, T) >
{
#else
{    
    typedef typename F::template apply<
         AUX778076_APPLY_WRAP_PARAMS(i_, T)
        >::type type;
#endif
};

#if i_ == 0 && !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)
template< typename F >
struct BOOST_PP_CAT(apply_wrap,i_)<F,true_>
    : F::apply
{
};
#endif

#   endif // workarounds

#if defined(BOOST_MPL_CFG_MSVC_ETI_BUG)
/// workaround for ETI bug
template<>
struct BOOST_PP_CAT(apply_wrap,i_)<AUX778076_APPLY_WRAP_SPEC_PARAMS(i_, int)>
{
    typedef int type;
};
#endif

#   undef i_

///// iteration, depth == 2

#elif BOOST_PP_ITERATION_DEPTH() == 2

#   define j_ BOOST_PP_FRAME_ITERATION(2)

#if i_ == 0 && j_ == 0 \
    && defined(BOOST_MPL_CFG_BCC590_WORKAROUNDS) \
    && !defined(BOOST_MPL_CFG_NO_HAS_APPLY)

template< typename F, bool F_has_apply >
struct apply_wrap_impl0_bcb {
    typedef typename F::template apply< na > type;
};

template< typename F >
struct apply_wrap_impl0_bcb< F, true > {
    typedef typename F::apply type;
};

template<
      typename F BOOST_PP_COMMA_IF(i_) AUX778076_APPLY_WRAP_PARAMS(i_, typename T)
    >
struct BOOST_PP_CAT(apply_wrap_impl,i_)<
          BOOST_MPL_PP_ADD(i_, j_)
        , F
        BOOST_PP_COMMA_IF(i_) AUX778076_APPLY_WRAP_PARAMS(i_, T)
        >
{
    typedef apply_wrap_impl0_bcb< F, aux::has_apply< F >::value >::type type;
};
#else

template<
      typename F BOOST_PP_COMMA_IF(i_) AUX778076_APPLY_WRAP_PARAMS(i_, typename T)
    >
struct BOOST_PP_CAT(apply_wrap_impl,i_)<
          BOOST_MPL_PP_ADD(i_, j_)
        , F
        BOOST_PP_COMMA_IF(i_) AUX778076_APPLY_WRAP_PARAMS(i_, T)
        >
{
    typedef typename F::template apply<
          AUX778076_APPLY_WRAP_PARAMS(i_, T)
#if i_ == 0 && j_ == 0
/// since the defaults are "lost", we have to pass *something* even for nullary
/// metafunction classes
        na
#else
        BOOST_PP_COMMA_IF(BOOST_PP_AND(i_, j_)) BOOST_MPL_PP_ENUM(j_, na)
#endif
        > type;
};

#endif

#   undef j_

#endif // BOOST_PP_ITERATION_DEPTH()
#endif // BOOST_PP_IS_ITERATING

/* apply_wrap.hpp
fS0MA8Q9erERqiGka/NQKy8/LWET7Syne+hvgxnDwvHt7dVASxGnCsFeSrYO49soZlWHiA7GPmULr5dt71giXynverP1GeGO9fwdJdJT0W3CQO4fdLJYk360Kca4LarEpL7eKiPd9yO6dOlQI5RNXNORHvTLZBbvxVsu3B9NapJbGPLkjKlTcc9h/GddNbxPHZehoNxvrvcSovipQqDGXFfx01/3uS9HhX+WaD45UNmPSseZsJe5d/ZjmZub41y2qGIk/M0y4eLiInjXRzQa7ya/pfzmA2ugbrKKsn68pLqAWUoGxU0wY/3b1zOjQPq4oiqxn5QlLJKSdL+V26seBiuueQvqBxlvAgF61Ow7LgmCLnpYBdUsJGbvU9rAFGEnN75rDjGKqh+ljivwp00z4lSrvx+6jH+ZpPbuzkt0WqwpPJJg8Mk6cYd5C55vdA9kMZ26q1IyNoGHBxJFpAJ8KbWZwArQcIvp1fXvoQfQi/sZNqkzP4zhWUYpAIJeMRx0seoa7gtvYHJVib4YYQI8CWovcah/8nt4TpWofBp5dfhJNCvbde0+iZvEyyrkV8GzKtUvO9ejswdt7umjycluOOX7WhpN/EkL58LYHPheK/2s/lySgHHPGtoszMBEvPTaA/+87fFYfLw/4aqCV9dOyN2NhyQ9I3mpG/avsof3OvQIzjmyhnkFS9O7/ekNSdEIWtbm+aJxnQBqkNMCC3R4PYaZqVdMUZiIB1RcfCMaL0ypz9a9bW22rJB1zRkGarxL3ZYTV71OJafaP9jle/5aEq1XvOfKrdfcdBOveUCl/6/AX0KnuMFMKCftbpx3c5uPLnB+9d/aP49wxB9XlfmE9PSZya5+mLCplHSuhyc8JzBHKnfv526kr3iLlLXR/RzbkB6kU0TRUCH/eO/dW643BPF4BAQXlyXlAtyaq08xUiQlT3uTBaKtN1059XIKoL5xwYpTLXc7OyNdF4pGOgZlRYdFtJqjE6bgvwqUf8DZ79fIKniUuquDdoqU5TOBUudck0l40AKJSjL8rlmD9QB4jkPhHojq10bS2jp7iRLtR4vSIg85/8xvbu4BqkbBbd01USvBpZgpAcVwaU0mmS7qm/T0jQz1jk7OPCV4T0tTVmlzc3PpCurRbzpFY41ruPS3+TsNPHx3bZMZMdut4QTiLoifp/z3jpG+1xVnfevM750WlBi9F7KysNMzmyhnihrg5R0Cu36bWSKt+++J63t/bQZpg0bXuz167uZyWkagHR39Z2a/0MEMZ2fVwsQYPhR+qc/00l3lHTA/MeDDcMPvssi+/xwDebtM3hEcLP6VYcWLmFEq5taNNdJhQEL8OkPEFQBQ9aJ9TWsWsCqNlpMuLS1dTM7YlZcnKtFwAILtZTS7/lxwPjsPTj4Y49JKnAtb6IiaogEAXAPMaFnylhvbMYhIL1M2iLuALdYQP2xgUUvCuFC1WUzouWHR+d6u0b2GU8PYTiAAAAhoD5fEDL5/rKx1ubvhexwWNbIJsN/QHgFh+6ZFcX2aqSuT4CckIc7pwlvtxBPOkOG5vYOWOpbjeIJ+XaUpa2tDMCBjd9mEYdG39GhSGiYZFUarkhLiafUEvpTrEM76xZ8uXzkOoNM6G81WCxQpeRvE3RCG6sx6S9kZ6JtTy2NJ0kUNrJjQH9jrPlKn1b9TM6l7B4y+nMVmfjSWuelpLavND/94X9cTnqHtYjeN6lTB1rgfiT6o4JNdxjZvPLnrnuLzc+RddfPbnvdPqdDublclMd9IYsc2X8zpleOSTESAxIMvGTr6WV4eI89dFp3kX3tdRpFokSdO9UFVDl/tlrelmgdgL520bdrNT3fjAl6SRZC93VtLt4KBxcXZxUmjAGtFEz29X4kLx5klV0E7efQSfwItnkte5zx1UgjlMASOYibrNzb63Hwr8iImlr24Lnnwb1tecq5yisPFn10W2jF2hURvCG5MPMRaYz0bY34Jqkgy0LS7QHUKIOZgKto4O1C1PnKtYrPor9PZIbTtZrqUyT3IPmr0y/hbWS4R8Oibgl/gcKB2EgxvkfybRLVHR+VYvH7RVl3OJzTnJqwLyb5YS63kf9ljoWVg8N6jviSeZ2i8uDx3Tb7VAgCQJKFkZDw/Z7Qln7toa+Ts4Jszbft+CKQv0wq2p+0m9pnI5+WxO9lU8lqYb/aegCyVW12dQIDEEdGRndHR0ZFZTd4+VEMqVKZz6sdnX+KhjAQqvA+dv5utR6bWYXvOufa6urp+X1no8uEIGAmu7UD/QH+Y0bHfQ0pKCt3o2ONIZTj/X6FeyzWBHKA1NJidnZDYWCvYwWSkuM9OfkWk8HNhX6G8TycT9R41lRJWfpdyhOqrFuNuNldDKn+mLHf8v28r8761QBO4HU9OD8+ZwRKpBQUFUS7/IqioSl7SlpC2z8gKdw6ijWOqJLFD1B+sJWrOe851/ZS/MCR1dkJEB4W/+fykSqewKfnlympF3s10gP4aRKvNZVC1VFZM/oKRLi0jw0JvYfnynt+hF18DT/DDjwUZP60bWcT47CqoSY51byOi/S1hPEhFaXh/L/XDh4UF8w+mH3LSfljqPHe1ut7UAmCGVI8xkcftlYQJbKysgnijfvir6ngasfg8v41e3N7dBs3BcKkeR6N1uRv+jkqxvmZnL94kuj4dOnLArfzu7/oM9qKjabx48qserZhNd3d/Xc0+VD3kdeTgYJVQ4pE/87URQjgb3iMzPOlV2VJGRW03T2n3u6zMKCcY8eTaBXhW4ufm0yheiozL4OHvBOlz8NhlPa1tKMbrtkQG2Bq/mz+aT0srgo4uHB6MhAxi3y2hXxNSUc6vco0C2fL34J1XgTe5mPgpEKXMZ74ePgLb+Lukk+vJezQI2MRXXIGRdt8C8HxI7fe80T+qZvGsBh7NCJDdUACPRls88jbySTwCl11P86+AsLzkXDm49VVn/JEkz5RWX4/J8ikczwHyoXn7tOoa6oyQSUHwSHJP7X987v43ZuJN9MAtCX2KzW08tztogC2LQ2DO5jKh2rYHVRyNgnQflx3uIWB370STzfXOVp+c9boPSw5wnyM4UMgV5D2elyvAa9e5Ctp35ehS9YOihfVPZTZ+XE9dWrQmg/m/ty1rKmvw3Pq4LH7hU9mCV8fb1jvY+vvulOIO/syn3RU1PXPpt+0qm8dBRZ4VKl1pJ/f5WvPUfBi3ndCTuTWRONYqR2dVAju6dWoAlO1X0B1O3iHrvj13zuSuZ0t0c/cUs9PZ7u4BlaIZu+7TPFb9dbYV8Zt+64OUWGMGtX7Ag2XV3zhP7HY53f2wM1SZXxXXveqR1HZJV33G0UwU8AexBk/UuRKlgnofhm9fMnrtn9VzxJtetGBHFja7sn0jdo2MvPJfKq/BVvbEnmim7tcC4E4xWhDFpovd6Hn3Pf566azNGAJPaXfT2R3wS/NzW/yFzcEt08Z0EB3dF3hPiie8qTrqgCpWwRNSVspc/iJ7q7SRRKsMY8uhDkVrRGmzujFrlEcp5tKq7Rde3048SRe3Qf/BKVlErhGGxfhvnGajeBS6zxEmcb1GAXRoBK198x74YaBY1uFAUisQLstxFZ8VJ6vbTEov5nqu21xqaOeWuZUGkbzd701nbxJz22h56WJcqGAFTp1+VOoQP0bObChEXFopxyKRT1V3MI9aYRuTZVAihnnoHYY7tT7zpDVmDYn6tVkoAfDTKJF5JGcGodq1afSva6sYD3LVhkURG9/aPnbg+9Eri+iwkOZRIrOk/mmvtm2OqJzk6lFicFR/OcNF0ZsQW15cwIh0zLfUPmVXYaVHR+aFL9Q/An9/r3pJxkC03fDWUxr3fYl/ORv/hZ0N9uuGq+6heo+In5tfa5WfZBKT8fdjPKW/0zwXq0FnVTyW3F9GHLII95O0s3QMyn5c8Cdb3kpXixNQce/i+WetxSZ5yYVnDWLm/Ys15C5Srp6u8uWfud6ryoL9WLKK2vIiHsWE5p7B+Xjr8nEZrTbG44Yb9+JeFMrXdtPJoAnM7KL6QazWt1/dZiBSaGhoJKSkoT/deClUOwv41nENirp00vdic3aZBwcH666A7Eb1VcIvY/GGF5LL/4on/TXlNeX+pqr4B/vFuKmO2WHS8bblXBpmMaso6Ty7UZu5N+beF2X7Gre+7heqTfMdm/ppksF/fFSD/DCyjoLbPp5Et2DJfhNRqVv4hUyUY7Pnj9pme02tWWm9bliF/nnO/NOJUuX+Dln8Zbkfn3misdZuFDmcLTq95MsAbNqQO1jPrrplXzkXKoRvLL0g7zbbawMvYw0XS0j5TyeiDktLBd6ThPMyWtsXUNdaECIspsgXgzN9dXXdL6ljqGedHB0RMhZQxsh/TjCs/IW56TjZ8Wpj/0nXOOp04L1pQkVW6I4FQDCh86bVTjMhC0gJ8D85MXralhS95CAUcHQ8+pQ/V164GM+Vw/6mmgu4ruPvsesa1CwsnC+h+uks5O6bux8bG3pFeznnomgHL1aMCiWcfENzx0BEQESrkPYXDdPymPT7SkBdyx0vj+v792eVy09X+8Nzp102kpKSJuQPuaazc3lJJIT+8yNdtOJ/uV1tFL52k5gvfnJ76MqsJ/1ovXedUsY0w1nzRQi0YmWl0E3NyszJuUkBODOnmpcLXtWqMRrvtJCurs69/zXtlNezwsLmqtlJzdHmmr/RE0QWVklvzDszsdca46FlsfIUK3++5/tQxpa3OklYDnXZ+CYopRy70SNdWfM7y/gjJ5bkfSmA7ebU+6zNsuv+dbEfjOjFmZbaxEA0otS2dHi47MbqGF+zmrLFZbnBOpvzYL4MHZ28a/mb0nf9TdY23oMZNoBgLO1QR82pQsaf3D9hS8TgQGHxw6N7w/wp3+qpWhsFjc3lYrucedjL+YWJ80cziz4toOcCtrd7kOiX5dmy2pEAwWmhr2U/uG/Pu4KiSn9ObGzoOQbYVW2ERREIOlG+K4ykbwZFIRIwD5vjDSxAK19snHy03ZMK/9B+LLx+V1qf56xZKbxXV0KiKh7Oz3c+JWBeC3uMNnvj/VOKyUjRWlCwsWpryzT2llZ8CHb3c0CWewWZNxNal3j802N1DZCodgndeC3Y+HMrA5Mi9oG2XfgMQRVtwBU8THPwnvLPQ8k7MKnf285rBjSYlu6TeeJGc2tr65wBV2fGcUVPSVYfjT8voin20jj1GZYpe3Em0iTYWdymDXK9+So5n7dtW2gIzsys+fNi1DL+urTUe1Oc44DKDx0TExN957RtfsoV4OrT6MO2naDdEAQX1gPAvWxMv2Bj0QTNy05u767b2isXf1kQ74IXT/b3T04uF16+ywPWQrdMgHcJ5CO9J6GhPaGl+QcecRpMpdNX59L+NAebh4clM3cveRfAJm87aiG3gxx+MfYEBGv/+Rr2oPuq3wG28gepqoT8ovkUJSNRWBVQQkL4UaVA6aWhif0Di4GFD+B5IiyRA3r9j5wHq9aGgCCIYJe/+8ULf28F+9+l0a6O/v7+8i5aWgo/vfemey3k/qYUFoYW9vUUDJ14dXXx7jcMojeP9QCdtUbFo2I+JI9GhUTkRJQMlvffDj5oy2uVihUqvIeUDx6W91u/zxd41go3ejPvhY8frhVPQAj/mjr+g4m2YqPOhaFRPX+mPMkh+cpv2zmBdB988MyTML+jEXzfo/P0LKCFoAD07X9ydgHtazap3DNpCo1spxo+cZMTkiFiv1ON3Ou9gtj1y4ug/K5rR6GL0WLPwRXjSNqh2eEKlEybBGJvNIjju+DVtYtNg/at3SgstxYA73dTl3Jwi2D8+4smIs/U+GeJD2y9dwYhZkyX9Y+J83E48ZfB8WbRrchFP+7vfpJMkDSHxystShuog3/Sx7JA+rI8MSnqEeJrBQiOqNafqwHNVKZ946e6f3nEs8Uan/0CcZ1vM/qG7fEVWuEoqmGf1n8fsFod0N+PebIohZKzkEnFJG9FLrIwYrxxZ9NzZ3wS9iWpmIqjoeUx1SeR+zMROEj+RFMtw/QuQuAOpIgAXW/VDoXzfQ3GOL5mmUsm3rJFU5vdUqzaCPR9g8Oq4EmqQFwtF7vCOshAqpJybGVTWaOU8uhBUeEaEr6lEHGC3z9kg4uv3ZFvRMQU9/ui0Ty215MVp548Cv7Hy00EHIZPZbLp8J6PXZmClMpEvthZ8d/3SDUBKoV+9882dNwKpH0V4qqRpKp8Dj+OyJRWeZQr2vnIpkg17VvxjKhYR+vNQlk1Gr7WMTys0CU7dFENlbUwz3sQbp+KFC95oDdoihYfrnn/hJjE4jX+5hQlVYlspzGtZt98ryt374Dru8QgV7Tl8pLubJD9RFGtzJ55RD1ls+sLjqdhks7IWQzbklDCmzDfxU+jPqYJFCNealDDuJegyVEP03BNKGGb5mqiZhanR1BrX/6bUMtos5hvy9iyZeE4rG0Co58ocYn+qd1sfP/A4fDyXo0lV4VTiREz9MNo0s+h3/jYKdulYVwBwiWRnGxvb5j76tRHi/4Uv1Rj8LOxkD9lUbq3Z5tQJc6QvtU99SJYnuIgpStXvchnwWPTKuCSY3pgLFXDE1V0KaCNRZ/UfeEQGxj2TiPsLDnfPmJtcHZUQ0D1c5NwQ6qzvE+6XG4q/RspSh3GV4T+FzKm17qqnm14b4r2dHK/kTTjyu4cs3+ZK+UsFvhATRmKVY67wLGG9ql+uC2jIiHK2cx0XOp7pxGW/RshDOkHrhd4EzppX6P3pQTXeCQThllN1n5/3NzfHz4eoGBkTIxXwqYoeygSk3ySNucef/e51u+XeMv+ZxzKT/wRZGa6md6on9oxWtN9C/+Mon5yQBTYPYaab4b/zXGbvmbTyWQKf9wWm6N8Vdhzg2dcSe9emxVL1fG2r4ax7R0w5s4Jo9UcfxhOhyh/C4xPVLF9LtUoyCBfM/HCNDj6jdFJtaNlzRjs8FdutRpNqoshTtWHJ1zL6iyqw5EquNurMX1zQX3NsWP4HPqNOmn17UXb9Ys86Y7hY8hN2ExUcJgRNuzcuu75CEBXpq/3MyOI7HZuYSFYoWhbGbB6EbcSC0wuL2eiymwEfqk7533pqPJt/wJk7NbmeK8cdJvPXoENmdzK5whyZABVmAyENzOp63XRmPNb7GsaN3x/cun7tBiNfeL06ka/nGEhE8jRLrQdbGfeMKb9NF5L+n0FsFp+7grXffVQuLf77jg48uz1K42DCUK6F4G6JtcbHSmmVwMLros1FuP8fh4jD4KPce0H/tC5xoH0x8/Rqa9zmwxA2jHfXYxNlvdYOt0YF4uUqcKtrQ0royE8/GOzvzzubjWsg+qzgcrUORuTz/Cb9ttT1OHwgQ8/yjTK3q/bSD7+q3L/drCgJRiZFhhoEH0yEsgkznNx3eMN/FNkZVvsarH6NecqxMOmWb138z//Bc7k+4nw+gWQilJyHj5s7rwjmsKj7kTU7WsXpOM7PPEA+/fYYw7MvOwcx+3mVpXkoZeclpTaX4ujTjSNi7DZ3WaqAEBPie2ku78uBImfG4suRc/I6jQ7Uy1KFF8PpXADDL/KVp4/OH3PrrzfhMWcDV3E7YePs1P8WYYygYkkjm+dRr4wTVKz7URB7oiJmzgrhwbL9pvAkJOTUc3FdkEp92+Q3ovedc/6d0btyuzvC2lDXQaYiLqD+cXWwFQZvuyyskIvFQMs70Hh4RYEiTfQpfvoCNH7u8TAb6cXcaEp8h3FrpZzFxbK2UpWlnVfLXdri3VZ+aWuxlLGeLFkBNPhvECQb69mjCA2Gt+IhCaDyauciFcvZcgsbRfetQkcUWar4QhmvpuY2ptopdRk3UpDYbm8qvdB/9laNU1o7X0uGJ3KF13AR36zAfhb5tnoeQzZ/plrESSltQx0EklUA4VW0HMQjV9tlaNRJ6b6KhqkYPurB/I9ZjI9von7XFD/In0lrG6GMqL6HG0pzxBPshtTrLibjGJgnk+ig3ZYYtWyppPI7pto/92u8a8j58ifPylsbGyYeXmT0LGJ5N69w83Kyqqbzoio3tKuE1gh/GukbO/gsDX4nbxKOCkhPt7S0RHP09PT0Miob2qK6PyDp9tnDo4uyn1WuWPV+/M9pTYuUVMi974TZg6pn36b1cOEK8E8EUy7oUAB3ichv63rRhTWd6YUb4eifcWDlSov2LQ9ZexV/UhLJqM3i69JgpxlrL5hJv9hC7kYwCfxtOT/oIf5zrSJ3kh9XKegBS3UOM5NN+A1qyYV69WNgK+Ri0LEPJESXfL9mBzGbxUNUieV7azGOPfln4MiIhrJclZZ41TjyS7tBBlqExSVQNz2ERHWZUdpnsxYtg0PuobJVtarnwRrVd4DY6ZU1FzEzAsf8Gao8NREweG+f80pjBERCn8ZXxoyqPxIe8MjXq1SMWBs6mEe7kvMXxIQxwIKYrvqGiTxDRZ9Ao33gx5wWKXvBkC6tCnmb9Q80xS+j8iUYL9jHfERje333voRLlBjOi0XDyJ9ie3EumpB+XvsjZIBHSqPcZvSvEoPDJfCbFo1MITqw0AiK0svDnuoBCehZOgPEjYKVZriEJVtkhWjn/c5yvoRmLFoUyywIga1xsS1EsHR9y3y3N/TKqzUJlKYoyvuu8sT5uXgaQNtKcVR6lkibxQndXK9CdIuy3RS++LFE7dUzvnn9g93/Pdfm46LDCc8pb7k4ZPzihWvOTAslgFTJQzt23M1KWhEsrtkrPYtL9PW1NRcXF6GAoGylbxeDl3k3xXpdbK2438dqv38PavzgzakrU2s5PfvQi7exHnXDmZZ9IeHB04eHhXlBo6atBTfl3FRx2tuc+lRBRIcL25+6OlRmqkoG/G8eJtzoZEr6TITNO0hTFPtRVr+Wlsl6AuR45trXYuPEdnN7G2rSts5f9Xn5uY2/YMwj49ryCoGbk8WZ77B37ydOuwwSSgdprN3dFQYP1s99FuK31Dl9l1Zjz3Qlrx8uwOUfAoOzGHlenLPzDFFKDMtd1eVdr/KB2xEd0au1I5RbPym5trObgM+hc6VesHQJFbGOehJg6ta4RypH8mirZi+6eFcdoHXg73itoc0Zqi1mVK8zw4ryGyZXh+RrGbs8itPw9X/0X7/FFXNMD9uuG0m8uod4Ro9vQVAmGNM0/1g2DrtbH1wqKZSXZdoJD8nVzy18jey3VfzVnlmmhaMEH11ROxAx+KHwvc=
*/