// Copyright Daniel Wallin 2005. Use, modification and distribution is
// subject to the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/dec.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>

#define N BOOST_PP_ITERATION()

#define BOOST_PARAMETER_PY_ARG_TYPES(z, n, _) \
    typedef typename mpl::next< \
        BOOST_PP_CAT(iter,BOOST_PP_DEC(n)) \
    >::type BOOST_PP_CAT(iter,n); \
    \
    typedef typename mpl::deref<BOOST_PP_CAT(iter,n)>::type BOOST_PP_CAT(spec,n); \
    typedef typename mpl::if_< \
        mpl::and_< \
            mpl::not_<typename BOOST_PP_CAT(spec,n)::required> \
          , typename BOOST_PP_CAT(spec,n)::optimized_default \
        > \
      , parameter::aux::maybe<typename BOOST_PP_CAT(spec,n)::type> \
      , typename BOOST_PP_CAT(spec,n)::type \
    >::type BOOST_PP_CAT(arg,n); \
    typedef typename BOOST_PP_CAT(spec,n)::keyword BOOST_PP_CAT(kw,n);

#if BOOST_PP_ITERATION_FLAGS() == 1
template <class M, class R, class Args>
struct invoker<N, M, R, Args>
#elif BOOST_PP_ITERATION_FLAGS() == 2
template <class T, class R, class Args>
struct call_invoker<N, T, R, Args>
#elif BOOST_PP_ITERATION_FLAGS() == 3
template <class T, class Args>
struct init_invoker<N, T, Args>
#elif BOOST_PP_ITERATION_FLAGS() == 4
template <class M, class R, class T, class Args>
struct member_invoker<N, M, R, T, Args>
#endif
{
    typedef typename mpl::begin<Args>::type iter0;
    typedef typename mpl::deref<iter0>::type spec0;
    typedef typename mpl::if_<
        mpl::and_<
            mpl::not_<typename spec0::required>
          , typename spec0::optimized_default
        >
      , parameter::aux::maybe<typename spec0::type>
      , typename spec0::type
    >::type arg0;
    typedef typename spec0::keyword kw0;

    BOOST_PP_REPEAT_FROM_TO(1, N, BOOST_PARAMETER_PY_ARG_TYPES, ~)

    static
#if BOOST_PP_ITERATION_FLAGS() == 3
    T*
#else
    R
#endif 
    execute(
#if BOOST_PP_ITERATION_FLAGS() == 2 || BOOST_PP_ITERATION_FLAGS() == 4
        T& self
      ,
#endif
        BOOST_PP_ENUM_BINARY_PARAMS(N, arg, a)
    )
    {
        return
#if BOOST_PP_ITERATION_FLAGS() == 1 || BOOST_PP_ITERATION_FLAGS() == 4
         M()(
              boost::type<R>()
# if BOOST_PP_ITERATION_FLAGS() == 4
            , self
# endif
            , BOOST_PP_ENUM_BINARY_PARAMS(N, parameter::keyword<kw, >::get() = a)
         );
#elif BOOST_PP_ITERATION_FLAGS() == 2
         self(
            BOOST_PP_ENUM_BINARY_PARAMS(N, parameter::keyword<kw, >::get() = a)
         );
#elif BOOST_PP_ITERATION_FLAGS() == 3
         new T(
             BOOST_PP_ENUM_BINARY_PARAMS(N, parameter::keyword<kw, >::get() = a)
         );
#endif
    }
};

#undef BOOST_PARAMETER_PY_ARG_TYPES
#undef N


/* invoker_iterate.hpp
pZp3Out90YMm+DxkHk7vGuMxEV1nwQNJKn/Y0ngf6qs2t0oj9NB3IMuKoG/Y1dqjYz6G4djz4gjXGePqJhGOBHY9zOEECJF4xapmFmzE3VqRhJIKnR7PaybHgn+bigTpzltxGX21i6CnSrtwDQ38XIM7Z5d3K9vU43heDwVqWir6eJODbkXei0kdi8ZVr5iSA8qsTREd8miC2Q9SZv9TOmxG+/2MEbvxwm8q7NNFhQyCyYhAchp1Evrs0SRJlBUZiRllsG9GDMlxjFYbA2dLL99VBuV9wacfANHwtgKB5P8+DF/p8fFWHlnh6M3aIYHWaI8CgQhNoxCkBIyhI3CABDNIkoe0hrlG0gVSjbYQEWxHbwjpdndjTZuislm5VPJBSZDS2gLXInpDkgkny18FO1ZgKC8Pb6JboSDUIJj5znU63d2Rnff9XLt7fb89a3o1uZ3OyGBmNpudzkb/Abx4NSVws5DIu7yEwh+yK2PFelowhCfVRKB9c8uq3y9irBb5nM8HHwcPaSqo1/ETMkTAi7sqjd6M4lGB9IJVaniCFyFNqqGoiDNDfb0THYjVRs40i6er+kJ/OqxVtyICi79XMHLGd6YyhEoL4LsBfi7YIWsMNHzYn+p9S+N9oI9pSNuHkqvaCuUxuqEndgIYOwRYKfRL8oPMMSHQX3e3czUXZYMEwAl5i4BAEjJC0uTz9b5Nk0TTyYkc//itUTeRXllFnTp6jcL3zjlu9a41dZC9Hb0BaBLyQYgCAzThtFhEeh7w+bIB6YZ9rp9aWF6fSo9k3Y3YwroM8voQ4fiNMg8+cNMHuTEJHuOLCvG7hz6cw7c+hjwTGOR5HmA/sHGkpyW5Igz8IKgE7w44xNWowXvBAW25sItDYpCZS9a7H5kNUl/YFhKR9pxFViejmcHSB2xOe0DWkuwAqyqUqD6VwCkkEyZUzEeYt9LBoDQTjXPHpME2GsjAoGlD+k+rxxqj98XCiKfQJcE6gGOkyrSrcwSSz4SrioSznI5xZ6pXkM67tAKlbH5H7p7SmdfVoKUF5nWkQMfcChRS7gAPg+o8RPxm/8ntR1P/q1L/B2/ENPEsZ+WDxNZyP+ltkZcjYmujlR8jjELpKhfEttakJY12laOHc8UM4TZs/fVWyJA0RwjQ4TAtK+ATZYwLTl02dAbT5hJZ7pBgD2RAc8vxrfFbAULghekHuRasxNnmsptCrtpVhLh6FIJWITZz+lrmefjNBcDqSN9hz6JdPKuT4baIB6LPfCtvvg8+lNMF9bYdhui8QJQ+fyQh0iic48AuU1Xh4VR9pxSOjvYpDbfLJluYrg0QWztfuYRKxUoLTwTXf4MWfhco2MjVyhdUET9fkrQL5piQNdbMyJQopKXpyu0BGYqFKa0PqwSsjTj1QGOrPrNAenrRHZLhZVVPQVuBur+E5p6f/j4H3PXgtbMGD3+PYbHUEHYF4iLB0iZ46n0UTmWj+RxuJUYXr4n+MX+qRCWzm0bo8Hu7F2mDSwoK/r5x8nNeXwH9uBl7UO3e9L7R8tiVqxyZc92qTpGcasik9QIi/2Ffuhg5ejAWUTPRzJFZsQgxPZM/og/yywbKj/mpDfPr5hrMc+rITu+xjfPrRvhHdXwP7qHNpGNdBqMeHhhAx+57N322kkr+fhR9LNjSu/ee0UUYZ9anO6XVUEin478aTViLsff1TOhyi8yoGdLSVUsWoJtHWTJI/+wOBHBjmIpHbkQ6aRCeffX806ymJE3Y3Bvrj1kM6ixpWaJdodWD2lXuHq4UsGlw+bECsSIFt28BK+DSApiYEZ3N5HFc62BFkc8PAPWFpwdg6vWH9cbNtyKOdhY9b3bxJDdgZ18XUeZpJgouvYVWc5z/WFHtDn3ECU+fBEf4PDPG9FyXoFP2gTnRjdKXK9K34HD8D+050YkzhwUda8Pw9D0TmNqMViCGXXHCaiLS7/HEO4ULJq/3g9AvxuF68AL7IqzxDLDgiUTvl7LlleEx8iInViqmxpGQ4orQU4nF6WnIoTwNKOHZjMFnYtqqOsJ7I1fSSrg5WG6Ea2zCBOVOMYgpVzBxJTd8xBfDWCIXHVC+nw1/FYI9ASes30VFbDciT2/MatP3zXfXAtQwJC/dJHYJnyHUojiW1ThrlGMAqtIAm9Z3dlikz7lRaPyrjQ42pZaQ1Omg4vAgapmroqwfQWWn4XAQcx5BmzhUewGgJV0Pfs5bn3/sInpg4dP4P9XWifCl5KHWQpNOBDmozZsbBFEkaoYiVDCd7bn58IvP3B46wFZSXXFCxHG2ke3tw35xcLcFZznodgyiWRI/ME8izERrFGJtrz/aDRpR4EVMM4cxGbAW3YbBstliNBp2jWWsKbCGsLOnyrjhn9zGANuhiO6wlx/O1FJISPcuTWSv7Ie/T+c+ZvcIXJ29rLtxt/HIn86GY5C9QsCpmcEOm2j++SAEkPbFmOiJg+UrXGKGZ/X/mBllH04pvnRBiPzmAxeiV6smLgdCjWP103vMEnwtre86OYR0pxKfj54dUoV3YT04DUHQkXp+iVK9UwK4deg6av+DKz2b52nUq3XS5TPrUprSuC3vXMRO1o9tLWzGu8FY2bU4RcJQlAqwajJaQnfW75/5RP1i9hwOEDJojbQZ7kx5U7+ASqTbTQSR/I5pJoyz/GauTaiFPs0qK4tApgaVuyc0LqHCxVsVy9B/2rzMFVQSPXh1h9PLDdhI8hjj7J505O7CLezIFBbkemjNCmRubItOERtP4BGsHTnZHLEalsWzM8FL5r4OxDC14PDW1lP4K8edm2psgB1zdBbjLZUAdQpx7MPjx5Wx4fSQxILt9zZeIybsRHSKGbQX0ne5+nnow4IqM911K+g1w6Ng/cCROfp1UZFQQMqhkyi4dwBtklVEMKHJBUMI5bc7y062DfhNY+CLp3/UXk4UvF8YVC7SkTwNHoYvHCIzV7UVxSg7Iu6AjQSCMxdrUEz63id6AzWKxty0NammFwwTxA1csV37nLZ3X8xKulFScomNxrcGg0hFBKCWzQVJqE1gKSSAGuaUPnVPJug2uCCSW3EB0u2NbLfADYzwnmMCTCQwBO6Gq4Si0ITZTUKNMxhUkdx3qdHELS5nHxhmZafIRAkOin1Pu6vDDNN78x/OpJdU1LJ3HFcmvCOixOOnfw7gJti+39q8dXe93L1QquTALVyHd4EkXZ6Z4iOvlErBJpauobXdz4FVM8HOAN02cA1AvxNiexNuDDdAPjzs282r/ZtPIHoju4d9iGKrPGVWWbJHcuNgucndJvP4zNiLtf9n4Qg0TKAyqcAn2y1LCWDOK2VACgcJPbgQcvUQaAiSyNCFIFHEAHm8BBnRUhkIutI1FOwILMjvk/l7DaBgBsivnQuzvQD+QYXpqXVFcemkdWIklWf9A0mYahzjRt0dU7S9LiyPmFRHonYtCkn/XqUioz0lGHKAlCjMzGiMOq5GlpC7jIN+TWlPwNWgIum+4BFmzRW5R4snDTL1byR73b44JjjEyCOTHEuy2Ml/xVSl+vqs2914jacTN3df9KupgbykeC9NUkX473rkAREbqinzhenPEny8a2BMoTZ1GRFWkj0yV4rLAKdNv0DKfHPAPNT0U6lbzwrUIPf2GxspSnG0BHAVMlQL5wkZdwT2nM/hsA7uJSpVY9asnmZ61YV1PFcYqmbKWOotFct8BtyY/lAt/xxJwX2KzgYHz8XkbjKCTntxh1UL8V4p5epuSsTEcP2NnW+RKSHBUg9ebBn2C3R0MxBCdsl45OGi2070OnntJwaYh7rxSrsze+s1+RZW0S8h1wPoXaCTIi6vB+8/xezf8FgUk84VxmeIqHMkEjMDVnqWiX8gHFb0q/UHOOG3UvoNncfNFYFCMJioL2pHSaSlTZD81UMAAy6K2e7XthzMNYIEp8vUYSNBjPHISM8dleK2zWlDSd1DdMEJGQDUov6pwBqSIQhm6FBcl3xQn06S4CL7e9NcB25BvjsCozEIQkSLJIgLZXQjNwl3SV0K52B8SIDHEuv2h20yDFu5cA5bVAoXRVKzsYbjp4w9jm8Vq1AG26aJm9RPwGKQKnjAGFl7UvNolLBQjGL9a0NiCXvU6hQe3MMbqYZxD1HlbWmuXay2kQDtfn2c+Z28jIQiqW5/9RMmdJ2D8ecY2niLDLX8VrN2MZrm4VTsuc1D7RlO4AOdRgYHeCLitxU7kvKYFBa3+NX1PSjPwJei6k5EqeVphx7DN5iggd3HUHwsGDIc14lxrWu1AUoGuXhyoWppUo2LAWg3G/ONhVWVkPazRB6pVqQGshU+r2lsBUSe3x1mpTohbCPTZLGRskumx4ajv0ZUptPsi+cFcXt/8Rh/lR9j8hQuPJGnvt3OQLnyKlBkma1LyvPLYTqt22SWS/+Iw6lr0vneLZuvd+4hLgWuaPVat/NnSQ6tf0wVvsx+hRIOOycBtlGXR5OLwujRuO8LZ3H64CGMj4HHnmkK6Vf5l1wvBBEthCJGJcOn7lYPTjVN9owRTZB+xbq5rgCRu/8L9w6dJn3PvFxBhBWScT0GyZRdrEhDoLm0PkrRd+zf5nU3OIP9QQW3QJGxbVh3MxJRdzlvzVfH1ALTGMPRJSWt07MIME0mL10T8YBcdfYm9SZBdrhvMJeCuT0hxBquoDwok8OPTowZpNs9LkqQlP8k7H9iOCMrIAy9TwUChniXJoz/dgEIjjho3eHQ1dXbT3EQ069jnzk81h6mEz0vH8qmjlZNBdMcpdSCHc1j9yNjBrj4jPCM25ssuukBWkBYnWbWun0ZT0+mejPmuA8+MTpFTMZk1oa2xefnK2j96d1Eu3DVRZ8EExDrYAnKt1+3NYptRWEB0fV8i+EU0ynVC5VsaUofSx6ZFpzUlRYyqfDx4IO/h7c32nfAFZR5neOYDblXyDG2UqxmX9Hv6htHKtJEcmnfKq9GigPZ8BsuM8rCRhwd0ZqyZA+rBy+sJ7u4qrlxvsQlNFpgPrrpGNkdUNagkGlyso0iq+ZOAHdx8bWIlInZ1Gk7uCJqOSKmrcPCF/VhQK5wyOwwBPHStML4/jp3YU0xFv38HVqFlmvIPJtfO6AJvgEIFuzgzZMiaZVoNPmIvL7S9UY3cjH2r6f4vWrF9GXtrp0M6xN7A6eks28O7TU+nAIP5U1v8d3ewRg0ESx5M++5QnePJISGf/9nz8i7JFDLe6Bypf+XNiAyrb6FUAgND0+C/QIcfJHlJhRKm7fRwgDkX14tSUV2+yWkXhEdP+AUTjmVcc57ecNlQxOLJxw8ncEOTNOe0LYlPiP8q+TLp9lboiSd3qeNMh7wq5ICjTKtYz6cUJLn+uLh5Y6+k2gweO4IcOvTeGkdNukZUyI1zuXTpB7ko8XAilarkBQM6rY5kwAGLPnTS1sijbilEoXgzzZRXlvN58RGjuapEXWdlFt5Td2hOKexjlmanCYNeMu0PwffToEJ2NrgmY39XfCajW/7deivwlscdzdpBZ2HdG9HbX83KT9g/yoqyTgtWkeKfx82KF62VeRoibppB6iPvX71nriRzZHDMVo0cVvmg5UODwz+9mm/H9hXWb8f0hfzAT/UT4V6GCd8nuIpjyPULczfZrbvC3aLa3/n70W+zX2AF+AFcstrfwepmWDHosFFgwiMjaXqSfz1fe8HJLzd2ogaltlmAHmU53HzjEBhhB8NwBXdLvjQmbtfmo3XA8tkZMNwrmfm9iLQy6tm1LszBrhEryv7zLp5zGOXRGONvLSyTIbhkQVMp7TfB/Oj9Uh7BLeGqn5sB+G1h/TygwWONVU6FtGywo6QpFlAR3fa2u6OQLlquvcX0TA+CKx7XudjcBe6xffGPvhL8LW17wfzQ37g92JpmaXgf6VgLxfkhbWtdJAL5Qa+/dCFe+vavrVvG9SFervaazPkYJwHcAP7K/Mml4ewxvaORuGirTXvtecaDn+15OrNTXXe6rF8tx7WliFbI+maHufAfOG/smw5mib/MTdNprP9y/2Ts0FQPmXDfDQwchFKbzHm3uGgKMCNRAV5hwrC25qJLXsoyxF+pqUja1i5bUzdm/L9QWw0AaWkY6qmGJi+nmKN3Ke2A7fSPBVtZ/qwTAf1H8JWTowH9aG1agXZSrLX1fUG+UhDhyj0fmqq1+dHl5wU8gZJsc3coW04pbK/YskFRn0cUKXiej7Cf2vNGosSii5dCc1+73oUl+cCU4IrqsUUK5KDP8+t9aI6dsKKP4TztDVgSoQdTpIVh3PHujVUCy55LkpEWcFAhbTlUCwlkgn/XWoJP5aSVUnilFa3qajPt0N4rw2TUWdxBwtD6tVKmo0bokMOL8Ziowqm/Hf48JUEFoATAW4Ub0Jk5QoAqGtn1PdFT5KCgWyKiabXY5Wu0GO6osydY8+ks3teL7FWFVLRcsaM5Mes6Lyc2wd017r5pDaog0Voh2MSiPnVVScPYZKqaDbmIqTU1ITYBhlHGLjrnQjTV/AavYkT6FnCBf2cvLTCY32qTNMr3sUeE5NXI8o6teuHJMeDVdalYAdLPXEJOpRM6QnJdDS4s0i0Z8dq41g+oupCl3/vucK3/thaAqmZVZOPdCIfAiGyvAmO18ga+Vq5EUD3ULuZoVxsdUJVfi63/LWsXXm2r11p6ki34hiuDdoiY0AJoLSjI57lZsH3kon9ScgdxqZjxaBMWd9Qd25D3bOx4eCuRCG6TiZMPQl9jeX11Bxg8TJ5YY5cTbFlbebHgXsTyHgG98Vhr9qsYpuv2nE7pmXC0RIZRMtr848XCM0l0L89qcq6X+S//tuTp8YN21oWvQ+w03ssIVQgX5qDcPMbx1JppCZRvQqEKvXXtIW7KKURyOuqc6+bUWUqFSovfr5oKY6IHkTYpdXShrJT+1b2lsVp10H0GPvRl4Rg4M+ZNAcT9cEvvRfKIe3WXj1M298AJpr2YhjhcGgpA6W+aLYxkWiWvdJlhdui85leoYqhU+1IKPHYkfU64vW6OZ5ZTtrzmE0iLXcEuAlyukthpsmCL7Q4JRtUizvhSLVnlHbM9nHVyaTtBf6JhzGPxIv04wI+SXcos18U+nNKNKNI0QUUB6ZgscXxEF9JNX5bd3l7tkmz69pwlnheQGtUan/pHC2l7RzOCRVoKRS34ahmZrvkTDO1pUCrmgMYFgmvOwrWCeDjzcDTEh30aNy0gLZx2lUBr+eI+paRmgxWN/LImXZiOLXHUh8T6bZ2hdHpzrkbvCt9K1UBTt0PoDFALnAWwAYs2zPnWB2JgLBCvJibIPDWZ+hCkvNBwYqh9uv9mGaAFfbBMeUYMezZJ5rVSLME7B643g/sEkFQx6YhVqcl9DX2WvXN7i0cPjsYoC74VPyIa1CA2v+Kxsr2FcghjcJJikUlB+X/Q7oWQcqPfzWs9B4ccx4eQ7VEQmBhcdgwf6qfshtOQfXSy6sAoxcINl+58Q4IEhfcSUmi2qwfcc0/OD4SSNFXppqSm3DrtlKE9kR5hSRgEnzNwlNlisrrwjfS4otLxHpVaL14oqhwaGvw4mOXgO36dqLDkf5WfSUtbMetpzurDZLKN3tbf9EIdeScobRSfsVMtQf8BJbfip5LQCBkZa9QpEKpbaXi6qLt34AtrWYKo1M6mmyrk+uqYlTRSTd16dFhnWKln1G9EVpaf9q0HtmVSor7zlnNi99PlkSPW+vSr8LOUU1Xr6xteVmwk7ea8WH6AhoLv+QrQBHoiGswe7zXPyuYq7cVfyb05O9peci8hHVjZt2Oxi84qYfxWQOJ6XpPlpQBhmmifuS4kBS0g6TBb5nsIAJulX20k0/8T8MZyiNKiDrTRweGxMmzQfaevp83XCjrymZiN0alHPGLmSGch43FthkI2EoN7ZljyyztuhHwfdd66VbaiJ6G0eno9OdOMjHsJhLMW0wKzEIqUVMkOzYMtnCRQrLAbXyVxmNaK+sUnxqtEXXB2O/YXlUMOFek0DMPb2Nq1nfu9bBSqUYIIKXuXMImadvyKSRv8qFEcmnDxFPzgQ2AZdBdA0KAAQ182JJIHSMujXcMMNRpXbzEczlPoFMuJk1BfY7+HvaGyJVUq8MN7jywbDCCZgyN1S6o8iaowE4x7nPPWDHh91yNa4QH6rzuE9XiyOlfZMSlI3d1G7TNJZGX/QYC951EhS6Lgzga72MHkE8BR6t8pqIF3OkWj3ryqi0VB4sr5Cd49JR95sPJnIPej6NR9Kf6P+pDPvcBUxJxTPg2Wb4gbg7IMGf0jI3O8f8UZVtmSAAhCVIV7428EJMo3xTay6s45e7vYlwVCO2hwMmclQjvEW+gLnWemXZVlMqroAK+UaBLHxest8glCBrmskB+7xqu1HwMGYizoVYMc1nN0w06G7uJ29ex8Go0m2GLUPTnFWyCeFcwSeegj02LxfJC1eqx+SIey8zjjTvILkarlHpkDt9g0B3hPLBgq6/xMdUtlBen1i/iikhJ+Y2DNhbijtbj038RPJwyIWGdi1PiM2Cw52R2swMitxJHsFvNFcGw84Aj7PaVMtJ4w+GqoatRyRq1+ajgv39Pt+q/7Q5G2XTzOc2BIoPdea0//5UDS6bvxN9U5FgUJHiGJqvaFjeuzjcr9ZMNaMXvrie7yk5JouV4BkUiv0caZJOZJDIecsxVX+fgTDui3Cbyiw2xyNa2ZukzacSHDzuhcGkKCEfL98LgY18W6jARdNcWzj67Tca4pmtJB2Jz67BbU9nXxCjvVW9m8jVpQtVYOpjtQ/yr1hOYy8ShuTlvPJY8KgCgyiU1VR6du2d7Ed+uE40jQqSA0mzzp8EKaBUnSHPZSqsN78TjYQaV5a6cWlreUK2DNzVTqhVcOyPSybNSiiR69LBJWnFBQKOoRL3SJ25lMCtFEMigvwbjinpDZn7WVXP6rY0qTF4nDBZAsrXBtY276tXbB9vFvhF7Vcl/o2/BVtIo2YBWQq3SGI6AzEfUqTmeTq4t3E0bcLraelYsvyJtlMu30fDwSk5B+DI3yaYV2UcZPG1dyi1pkt6QvTMlAegnpnFqPYsGfSkgiPV5++Ga5Tsm/rQfKqVPXzJcxJUyySZFFMDREL1r7bSpaK/l9azaUGYEHUejgmnr3CsZuVVZS4oXQfHjnhnt/92JK7gFdGpGhoTP7f9mf5WEx09CvBSyWWqAdpFH56IcNxeja18ICF2OJBoIhNNHcbQ=
*/