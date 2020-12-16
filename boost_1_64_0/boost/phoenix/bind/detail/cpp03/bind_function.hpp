/*=============================================================================
    Copyright (c) 2001-2007 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#if !BOOST_PHOENIX_IS_ITERATING

#include <boost/phoenix/core/expression.hpp>
#include <boost/phoenix/core/detail/function_eval.hpp>
#include <boost/phoenix/bind/detail/cpp03/function_ptr.hpp>

namespace boost { namespace phoenix {

    template <
        typename RT
    >
    inline
    typename detail::expression::function_eval<
        detail::function_ptr<0, RT, RT(*)()>
    >::type const
    bind(RT(*f)())
    {
        typedef detail::function_ptr<0, RT, RT(*)()> fp_type;
        return detail::expression::function_eval<fp_type>::make(fp_type(f));
    }

    template <
        typename RT
      , typename T0
      , typename A0
    >
    inline
    typename detail::expression::function_eval<
        detail::function_ptr<1, RT, RT(*)(T0)>
      , A0
    >::type const
    bind(RT(*f)(T0), A0 const & a0)
    {
        typedef detail::function_ptr<1, RT, RT(*)(T0)> fp_type;
        return detail::expression::function_eval<fp_type, A0>::make(fp_type(f), a0);
    }

#if !defined(BOOST_PHOENIX_DONT_USE_PREPROCESSED_FILES)
    #include <boost/phoenix/bind/detail/cpp03/preprocessed/bind_function.hpp>
#else

#if defined(__WAVE__) && defined (BOOST_PHOENIX_CREATE_PREPROCESSED_FILES)
    #pragma wave option(preserve: 2, line: 0, output: "preprocessed/bind_function_" BOOST_PHOENIX_LIMIT_STR ".hpp")
#endif

/*=============================================================================
    Copyright (c) 2001-2007 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#if defined(__WAVE__) && defined(BOOST_PHOENIX_CREATE_PREPROCESSED_FILES)
    #pragma wave option(preserve: 1)
#endif

#define BOOST_PHOENIX_ITERATION_PARAMS                                          \
    (3, (2, BOOST_PP_DEC(BOOST_PHOENIX_ACTOR_LIMIT),                            \
            <boost/phoenix/bind/detail/cpp03/bind_function.hpp>))
#include BOOST_PHOENIX_ITERATE()

#if defined(__WAVE__) && defined (BOOST_PHOENIX_CREATE_PREPROCESSED_FILES)
    #pragma wave option(output: null)
#endif

#endif

}}

#else

    template <
        typename RT
      , BOOST_PP_ENUM_PARAMS(BOOST_PHOENIX_ITERATION, typename T)
      , BOOST_PHOENIX_typename_A
    >
    inline
    typename detail::expression::function_eval<
        detail::function_ptr<
            BOOST_PHOENIX_ITERATION
          , RT
          , RT(*)(BOOST_PP_ENUM_PARAMS(BOOST_PHOENIX_ITERATION, T))
        >
      , BOOST_PHOENIX_A
    >::type const
    bind(
        RT(*f)(BOOST_PP_ENUM_PARAMS(BOOST_PHOENIX_ITERATION, T))
      , BOOST_PHOENIX_A_const_ref_a
    )
    {
        typedef detail::function_ptr<
            BOOST_PHOENIX_ITERATION
          , RT
          , RT(*)(BOOST_PP_ENUM_PARAMS(BOOST_PHOENIX_ITERATION, T))
        > fp_type;
        return
            detail::expression::function_eval<
                fp_type
              , BOOST_PHOENIX_A
            >::make(
                fp_type(f)
              , BOOST_PHOENIX_a
            );
    }

#endif

/* bind_function.hpp
x4955bYwndylDSbxRMK4vs4in4uE4Zf0kYugH32SQycOZp7YDvo8/s/rki6dGIg8VqYEhmuD34OVdEe+rrSgGQ9tTrsiY9FRQ0z7u6TRmZWmvTMraCSybsOX5RQNqhpMKdglpJU9+UrRfAxrBTjpnzw95btbZPx1VVENN+BJ/aymsPHL9g2Eu6mucJdfauq+fryP8LHL64Th3elX2MsuwQx+z1MV/rJLa5SR8E8jfPSS18i87emEi90+YBmKz1DYyy/XNe+xFuHjtzLMmHTLfoVd0LLYlPH2EUoTuSzmfnFmwsWhbrHl3BKYPdNRmNYQUAZzaCYKs39S6uHtB6MwU1DuKYzI4/B65jxvfUEUdro9KOTa9sooDLRb+vu/ijDzbllwvd36BsJHNgnznXoP4eZtDubb/T7CR20/SD+VpyVo/+GGjaRAvuvU5DBjugSGsjUYcz7wVIEJcWLcaRtH3MK4FTLPnnh+c8SPcC4/9tkJcMMRBTWYI4SJKCifizGmuRezOtg4SJZtlrAxhZjUuD2EiynE5LWE+9fvpU+AP+AbuRLh87rgXAVnda7fl/dmc1ZCZoY/npt6WFEM7UMPDg21pjrivOV0GIOBaELZsEPm3Prv5rxhxj/0ppBBmsfsI4lOF3nkuY45S+XzHwyWgbj4PKrpXb82ZZGuI6PmfGblIpk+vCEtdck6kwu5MrYMz9sJJy9S0OxCCVkHLKzhu3dyZkLxbGueR77jniMRW0phnc2Gz4fQyi0c6A3TGRHr/Z47TR1DX2Dm7h2dJJCRMfEzswe5P3wqldineXX/JAqHsgwfNPuTXdb+ZD1Zq+bSea9a+n/3JzW/XRa/YjJXyuWq+Wq0y+yo8prN1vCrb9/su36kdjVr4Mb7lIvkPiVvJ9I+ZfDW0+Rq2EHvpLePTJN1cE0Gugv6FOjnfPpwCCD3P+7C757OvoqxLxeBFl4bIy2N34sV3VZ7jO0UJ4BokUeinP/Su2kcZMNMhY5B/k+g3Z1o4aNQI8NpjTEns2xPfOoKosUfkRp5l92DsNGqbXBz9yRc9FEq2z5XEm7eJz/FPsMKwtOQSh4HpiyJq4ke351NvQ1fQ9hwdzaYsysJEz7aN5hdqwgTHmpMOW9crTCXP1Ezc/79CR95nMZl+Nm1hAsdpzFm3RrChLo653fugYSJHDbYdlnbRbh5jyc575MPcfCmFKzb2x6qMFR39BCwnhN6fy/vDzyPrg+w316SfeDQiOT0LOj1kO/Y+LD0wX5alC8yFUaO06+OwgVOhnr7g98T3JtQ2FBIPl/C9qAa2p/bRDiCIdjZZjw+yPOAnMhB6mibYSqwo6ZAHCf37b2a5gkaLR/3Ghvh6YpGMZGxXaZGW+l7NLVb0tUmIOc5a9Mmp4Q8p58maIGTf8fM5VY6SAUPBfRTk6cn6b49y2nnTrJvhTAU2sYP6JNMD/ZjgmlD+odPfYgxNEdqrWYb4fMWH39/Zny0E8LNfoxxfvegypgenYRkB9m34JZIfpQ9Wp0Yo1HZ1v4op4nqesZGywr9oEt7dNmMfU1yAoPNTNBRarjtjiJz0adW5BkXjLWdGXw+YM47ZXlHlDoN7h/HOEp6ZfjsKQg+qJPpgz6njqF/xfCRRTP2wOq32+efXjmdLVQylf/Xvugjfp7kly8lSzmvUC3matEGRju4iOM7NmE/xjc36uoHjolFmuctlozVZKWRzWS8Wi6aJ4xz5oN/4crPzITyGfN56nLPWTy9ZKacr1cKlfgYRSX1G5uc2I+/5fH2/ubI8HQykdT81r1D+p17yWLDKxTKmVKMYYVqoxtJvpDq8UXfp5zrUfLLZJO5bK1Ry5RKl6/HyX37nHrUMs4=
*/