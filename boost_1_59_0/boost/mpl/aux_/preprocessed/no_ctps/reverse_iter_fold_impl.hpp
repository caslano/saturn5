
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/aux_/reverse_iter_fold_impl.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl { namespace aux {

/// forward declaration

template<
      long N
    , typename First
    , typename Last
    , typename State
    , typename BackwardOp
    , typename ForwardOp
    >
struct reverse_iter_fold_impl;

template< long N >
struct reverse_iter_fold_chunk;

template<> struct reverse_iter_fold_chunk<0>
{
    template<
          typename First
        , typename Last
        , typename State
        , typename BackwardOp
        , typename ForwardOp
        >
    struct result_
    {
        typedef First iter0;
        typedef State fwd_state0;
        typedef fwd_state0 bkwd_state0;
        typedef bkwd_state0 state;
        typedef iter0 iterator;
    };
};

template<> struct reverse_iter_fold_chunk<1>
{
    template<
          typename First
        , typename Last
        , typename State
        , typename BackwardOp
        , typename ForwardOp
        >
    struct result_
    {
        typedef First iter0;
        typedef State fwd_state0;
        typedef typename apply2< ForwardOp,fwd_state0,iter0 >::type fwd_state1;
        typedef typename mpl::next<iter0>::type iter1;
        

        typedef fwd_state1 bkwd_state1;
        typedef typename apply2< BackwardOp,bkwd_state1,iter0 >::type bkwd_state0;
        typedef bkwd_state0 state;
        typedef iter1 iterator;
    };
};

template<> struct reverse_iter_fold_chunk<2>
{
    template<
          typename First
        , typename Last
        , typename State
        , typename BackwardOp
        , typename ForwardOp
        >
    struct result_
    {
        typedef First iter0;
        typedef State fwd_state0;
        typedef typename apply2< ForwardOp,fwd_state0,iter0 >::type fwd_state1;
        typedef typename mpl::next<iter0>::type iter1;
        typedef typename apply2< ForwardOp,fwd_state1,iter1 >::type fwd_state2;
        typedef typename mpl::next<iter1>::type iter2;
        

        typedef fwd_state2 bkwd_state2;
        typedef typename apply2< BackwardOp,bkwd_state2,iter1 >::type bkwd_state1;
        typedef typename apply2< BackwardOp,bkwd_state1,iter0 >::type bkwd_state0;
        

        typedef bkwd_state0 state;
        typedef iter2 iterator;
    };
};

template<> struct reverse_iter_fold_chunk<3>
{
    template<
          typename First
        , typename Last
        , typename State
        , typename BackwardOp
        , typename ForwardOp
        >
    struct result_
    {
        typedef First iter0;
        typedef State fwd_state0;
        typedef typename apply2< ForwardOp,fwd_state0,iter0 >::type fwd_state1;
        typedef typename mpl::next<iter0>::type iter1;
        typedef typename apply2< ForwardOp,fwd_state1,iter1 >::type fwd_state2;
        typedef typename mpl::next<iter1>::type iter2;
        typedef typename apply2< ForwardOp,fwd_state2,iter2 >::type fwd_state3;
        typedef typename mpl::next<iter2>::type iter3;
        

        typedef fwd_state3 bkwd_state3;
        typedef typename apply2< BackwardOp,bkwd_state3,iter2 >::type bkwd_state2;
        typedef typename apply2< BackwardOp,bkwd_state2,iter1 >::type bkwd_state1;
        typedef typename apply2< BackwardOp,bkwd_state1,iter0 >::type bkwd_state0;
        

        typedef bkwd_state0 state;
        typedef iter3 iterator;
    };
};

template<> struct reverse_iter_fold_chunk<4>
{
    template<
          typename First
        , typename Last
        , typename State
        , typename BackwardOp
        , typename ForwardOp
        >
    struct result_
    {
        typedef First iter0;
        typedef State fwd_state0;
        typedef typename apply2< ForwardOp,fwd_state0,iter0 >::type fwd_state1;
        typedef typename mpl::next<iter0>::type iter1;
        typedef typename apply2< ForwardOp,fwd_state1,iter1 >::type fwd_state2;
        typedef typename mpl::next<iter1>::type iter2;
        typedef typename apply2< ForwardOp,fwd_state2,iter2 >::type fwd_state3;
        typedef typename mpl::next<iter2>::type iter3;
        typedef typename apply2< ForwardOp,fwd_state3,iter3 >::type fwd_state4;
        typedef typename mpl::next<iter3>::type iter4;
        

        typedef fwd_state4 bkwd_state4;
        typedef typename apply2< BackwardOp,bkwd_state4,iter3 >::type bkwd_state3;
        typedef typename apply2< BackwardOp,bkwd_state3,iter2 >::type bkwd_state2;
        typedef typename apply2< BackwardOp,bkwd_state2,iter1 >::type bkwd_state1;
        typedef typename apply2< BackwardOp,bkwd_state1,iter0 >::type bkwd_state0;
        

        typedef bkwd_state0 state;
        typedef iter4 iterator;
    };
};

template< long N >
struct reverse_iter_fold_chunk
{
    template<
          typename First
        , typename Last
        , typename State
        , typename BackwardOp
        , typename ForwardOp
        >
    struct result_
    {
        typedef First iter0;
        typedef State fwd_state0;
        typedef typename apply2< ForwardOp,fwd_state0,iter0 >::type fwd_state1;
        typedef typename mpl::next<iter0>::type iter1;
        typedef typename apply2< ForwardOp,fwd_state1,iter1 >::type fwd_state2;
        typedef typename mpl::next<iter1>::type iter2;
        typedef typename apply2< ForwardOp,fwd_state2,iter2 >::type fwd_state3;
        typedef typename mpl::next<iter2>::type iter3;
        typedef typename apply2< ForwardOp,fwd_state3,iter3 >::type fwd_state4;
        typedef typename mpl::next<iter3>::type iter4;
        

        typedef reverse_iter_fold_impl<
              ( (N - 4) < 0 ? 0 : N - 4 )
            , iter4
            , Last
            , fwd_state4
            , BackwardOp
            , ForwardOp
            > nested_chunk;

        typedef typename nested_chunk::state bkwd_state4;
        typedef typename apply2< BackwardOp,bkwd_state4,iter3 >::type bkwd_state3;
        typedef typename apply2< BackwardOp,bkwd_state3,iter2 >::type bkwd_state2;
        typedef typename apply2< BackwardOp,bkwd_state2,iter1 >::type bkwd_state1;
        typedef typename apply2< BackwardOp,bkwd_state1,iter0 >::type bkwd_state0;
        

        typedef bkwd_state0 state;
        typedef typename nested_chunk::iterator iterator;
    };
};

template<
      typename First
    , typename Last
    , typename State
    , typename BackwardOp
    , typename ForwardOp
    >
struct reverse_iter_fold_step;

template<
      typename Last
    , typename State
    >
struct reverse_iter_fold_null_step
{
    typedef Last iterator;
    typedef State state;
};

template<>
struct reverse_iter_fold_chunk< -1 >
{
    template<
          typename First
        , typename Last
        , typename State
        , typename BackwardOp
        , typename ForwardOp
        >
    struct result_
    {
        typedef typename if_<
              typename is_same< First,Last >::type
            , reverse_iter_fold_null_step< Last,State >
            , reverse_iter_fold_step< First,Last,State,BackwardOp,ForwardOp >
            >::type res_;

        typedef typename res_::state state;
        typedef typename res_::iterator iterator;
    };
};

template<
      typename First
    , typename Last
    , typename State
    , typename BackwardOp
    , typename ForwardOp
    >
struct reverse_iter_fold_step
{
    typedef reverse_iter_fold_chunk< -1 >::template result_<
          typename mpl::next<First>::type
        , Last
        , typename apply2< ForwardOp,State,First >::type
        , BackwardOp
        , ForwardOp
        > nested_step;

    typedef typename apply2<
          BackwardOp
        , typename nested_step::state
        , First
        >::type state;

    typedef typename nested_step::iterator iterator;
};

template<
      long N
    , typename First
    , typename Last
    , typename State
    , typename BackwardOp
    , typename ForwardOp
    >
struct reverse_iter_fold_impl
    : reverse_iter_fold_chunk<N>
        ::template result_< First,Last,State,BackwardOp,ForwardOp >
{
};

}}}

/* reverse_iter_fold_impl.hpp
WjyHIiLq1CYeYcGWJrVNAIoxxUiXl8+Jr7LVrw6KUhvRDoMltE1SInyBiKKUDowTKUloQqp5cfkcDMEpCh2CrobCYxylbRR6du3vCK6mKbPMPR87KHPrTXU30yg4esJaKkQEe/XVs3bdMqKnONlZpxxVLhhPYie6a3ruGX4hI/RzZ2y9We77YHWGfFCI1q5+eQkNRlgbY6dmbH9Tn331dHcnSDlhYc03wI7ut2EQx9tGn8RhQpqIcuYIgLRMuN+0cp9Gt0GNDcZp+vhGI4d6mK0GrGHHPJbEOjHOAd7UjsJ+coGjJIuWezVOQ59JG1Sjm8rjd9PI0ExaiGGsh05OhNcYTRJhKklk5ZSjJo9F14geGM6SbxDS7X/Scvu5CEb/GaCw66ugVICBYGLXnRkFRN05SecAmXeGrKnduB/wE/lZqCZy0OYBPtWO9JrLhy/baWeEXPold8XnQkRLJlSAld8FSFNcpeSW30Sh5j53a+k1jpC6LbEZEJcT4eEWo/PyaOvYgwah0TENoiVLwMSkZwYcrR5SOvh3wdophcSerG1PK+AOA34zOed/ga9lqZb0gfu7/vsv4E/gn6A/wX9C/oT+CfsT/ifiT+SfqD/Rf2L+xP6J+xP/J+FP4p+kP8l/Uv6k/kn7k/4n40/mn6w/2X9y/uT+yfuT/6fgT+Gfoj/Ff0r+lP4p+1P+p+JP5Z+qP9V/av7U/qn7U/+n4U/jn6Y/zX9a/rT+afvT/qfjT+efrj/df3r+9P7p+9P/Z+DP4J+hP8N/Rv6M/hn7M/5n4s/kn6k/039m/sz+mfsz/2fhz+KfpT/Lf1b+rP5Z+7P+Z+PP5p+tP9t/dv7s/tn7s//n4M/hn6M/x39O/pz+Oftz/ufiz+Wfqz/Xf27+3P65+3P/5+HP45+nP89/Xv68/nn78/7n48/nn68/339+/vz++ef2Zxe+sWIjlSvWnyJnoDz69NzlDS9b6nLJ+4IClclyodwSNKDIy3GNNLRuJ1bD6yOByO3VLH7Cd93DkHTEXMHO/dPHUPiZxm6z8VBXDZljnAv1efte4S8T4Ch6ew+4ClSDnhj6xs/J5aeBmhsuFCaM6G66QiKwfmwrxTR9l/F/dItFmb5kULuFxd1MAwpV4HJJrXJvstaY343Z4FDPVBp1sbCOsllPDKZir78cFNhWeVlGtTrrXBDOKk6n+PaNtXUf9IpGkI6Xurwuu1+ZT+BvegmnzRuRKD+njorjL/C+c6M8A6tdbgFfcSjxX2azwiVFuiUGaJl2gylJCPg/hOKvvpHWloSzzhoyNHmFGFvi7r40PdXttyLZ1/Y8nLFaWOJ6HTclZgXYyjxhViPzXppd3H37y1NBQdElCo1PEN2AQctCcqJtUIejGgxPQvsUPRROBFa4GCDJPb2lfkhX0/LKd+k/yoT+vHchhAJxHaFSv2WoK4emmFWB8AArdpyWYnOpBTCQpuoBmBNZStFAm/xA3cK/V1Yi4cw1yW9Kp9q9hM9Sxu/jR6xEeDrrlwezzqSBH47g9WQfLPgC29dc80+MHuk0pepr9rWLhl+eJljvZW1OeGSvrc5kbd2nSWGPesaZM6oTvl4mGzIhhbLt3nxrUG4IYvLd8UlP+LaHM0P57IJc+RhBkC+rsBMPBtvKEKPKa85ThYChVF9vFbmGfvlzWGVU7rLzLcIss3vrJHZZ8u/4wCj6OicZ603qRDF/mwY/vIls8rcCzj9wiIdt4WbSDmpW71AeHNuVvEzLu4OV9QLx1yd0Dqkd95DaF5Z37RZyHyBVty3YpFWPdCdjJ4+X8mcLbX4wlwJutfc+bF0/htt4iS21Q8BC0BzBAg8QqR1blwgAaWOZ6JoShD3UsYZrhKDgj9fubKbmgMBYYoyh06UlRPvz603heTfJvdlC/Pvka0nYDDwiflJnd3Cbksc0z3uMgyir5opLaPHf6RB10Xwta2ZkXD27xiCz1Kyb3mfb9Bfeg/hY5v22CmVkKbbG/0ZZ9nFU0rTN7PRx79dsuwPhDWSk6+ZiSrMQsULb5YvW+Kzqur89VpCtsiu6D5z+iguPiVZxGDu6PH0kCh3yMba24ZEs1yWNliaeE6zxuUia79O/CyepJWSh7ueAvy68q0vDEZg78+Y+hcpoao4obRbsdMSYllGAM40MpXzQT2ONEl2e/F4VJflI/bkyXoNsJyyN1dUwaAZd20+t83kTVFWzcojcTJp4vBBxPZ4HcQ6UfF5w0s31r83R7IE7hqQt6NKofSJo5u5dVqwZsRfXtVSgiH2psmeeS9aorLpVHyQPXyF7/4Y8kJiVUF2zWghlsvKMABLtwsYeBFmTplZibcdQKj1Twx2/HyXx8MgWkpV1v3VA9WZi5VmGRqUprmj9qFx7Xcsq5xNVeKrI5GWu4DQMvpBoxQMwk567EM2LjD5jtI61EBUDV7EMxfiIPINvSPzc0riGo99nWfW4G23+H8fmFCxMzy3hbePdtm3btm3btm3btm3btm1b5/tP1VRq0v30qpWbTOYirER76jWLTdsxuonsYGGe2X1be07lZd1frCVcWYIbeTyqfri/TYhiciCwtw8KdbEpZxNn/yAkYykOblNobaDZysgE2bZ3RHiEP+c0jrAhw21/PD4xVH0iY59249EXWV4vhEjLhNPQuHXqOFe8kFn2UXG2IZr4mA3D9Ozo96Cm2h5dgJfq/r34gjxcYDbHBrEPgTqdg3rUZmqeGpJJKqqb13Ck7Ph67mEJOovz7wXJjez8xv+2YSPfpagHXaAN10BrDxp8vzRWX2E11p6lrxVvcvDU3ORkfA7PCiXd0FXuKl2Bv/xYq0Xr0eoDJrROesv2KCuzg1IYEoXrP0PLpoYcVwY9E2L7q4NBeZom3+h2jDEYEGfw4EajHIPvo+3Ufs6W9zZV3nHrxDr0Wrl6hVZ955f/aZoAg1r3Eo2f3qhNb78KI27VWTRBi1lQ9lncHtvVE3AsBWf7pnP8PvsZlbDcCo6N08XsS0XFGF37NzUJadlOm11sWJymcSdHkMXP9amO6Trx9wnZCmr+blMgIE5V8b02A1hKkBBoVc1LJ0sJuFD6wnaPgo/ANLywbxFtuxTkCx9g2HMa13bHPKUxdxg91d7d5AlxDmHe+8XvVvCi8a2rH6ZvVsMnO2P02R9Se1J4khl7zy9SxeBQ5BH2uDsf8COlcAKMBhWsW9ufWIkjWDtN1V6KqvmUf/qWffIWTM0RpwyXwOYvUhHuWO8lSHp3hGfLr7XbYzYO1NQqDBvNswGtt6GPhYNlIs5vcIC2aoFs+7ZTaDigY7g9sYNuYF7K5MaQmQhBVxTs2X7HaT+/54XOjwDIAPZYBJfRJd7ZKE6nmWu+pY1D9isFTMpyoxD7gJOVyHVnPTr06vvkFjvAOaLe8jXv/cPpYElUX9AbbAJ6Jiw9f3Q5ZZRbYr4llSxbQCUVEPm00MBSjgofGNGvj9rgTW82JLK2zrNHNPLdZ8c3tkAEQnTApmOJAc+mZAyip/xQMuhDL/SMauzU/tEVGs3J5kk6XpsviPYW8aAmZSZLzwbczAIVx3UeQat6o9KsIQRtniXDh8s2KpaIn1GTtRt57vaLfzdPNZn7IZyQ0ZToXxCxiEXksoMJp61x9b9k00vnVDgBvp4NHmW4qkFkst6eYzt3as+78Ws6v4n2bvX4KGCyIAuV8S1/gxe3PEIRt3B7WxcmfvsDFl2GNUKMs6Tfb/P8tAsVIG3T7dFbs3RpellqrHwk9EOD5RGG+pbQzMvC29dq9jMPfI3Tzf8p4rj5O5gHucH78bP7I7LTY9cr3FwGD8ql7dX6SSH7QHIXY2ZV5T0Kn4Vjta0O/htt1Az2tO6sfTgQ8WdaKPmGAhsRUASuuY/B+y5An5MWnLEBV8HQG/HuR1aacgEbTuLGr1nk7ameyi4tWbqfrzSj9ch5CKsXb1QrmQKZheyLbaENxrbi7fFnKl+aZL4JEF7KR6Br72VzSGbufw9PbqfpaeBaNM7YQfoxLczIs+aLcfZa9WQU1qv9Jf1N15bzZWiZog+JvH+ZIHEE+JzT9ZCeK8YuKhDBQ9LJQo31s3/n9qufqJGd+dT/e7HHdZLqiMclHyf+WBW+ezaBmga0tBzNUeaNPR2fa22jK84Lp2NQB0udjvoS9AiF3Okb3d0zOSO7vVvSdYUlQ+AQfwqGuiJmH357bxemRMR2gFMJdMWap1AvcPdv4rzcshSzBh5MkjYcIIUVEkDM3TisSCI9VKRPbtXL1f86kWjVew3BcLNOCTRARGQzVHZ3dcXsi3HET3nQwiQcsP7QYeKO+NYlNLvX21yGA2WCAr92LLfOWjRZP31r09By6qQ288lx4PXymfHezXvK/vSaPYDe17KAkHg+Qj5G2ZVxATdfHBN7hqAHWTKs+PTnkNwZZci037l1rwCACSShdLd8TftHV0L5zEkGVbwTwz4Z/0K0iEftsB4CQIPJCRwhJzZjPyhrZo2plnxUmXpQQbrVdHk/MvkVwPRx8uNzRpr8xjD+pTUXU/fRvLuX2bNrJv69gaTyWpb23vgzE0ZX/Kcvec73o/d8AnAzWb3QIGf6T3QcjGg+PAi7oP2RyvmJvxaOl70DjlfB+6KgATq7TQVwlN8Gs1nZlAQmcCkLp6/3zfSVNUgAVTAPeTVjyDW8dhnEoPbxK62XKYPXxnKJVeSP6JibNoUVso8lpRzdrmrylfCH2/UU6bPId+tuYDY82q3kl3+n7XMb74cnhGiG7D2VkSE07Hs3d6j1KRyN8Ru4CeH3SPJZVmaIAr96FaoGBdMsqAZJTOKIbgvQMlZSycywXH/KzYA5Wi/NHO9JLAfTDDJUTTHjTWh2zESmqzEy6Z6wg6vGUbmFDFbOShWEeYurj7w57yj9VdJuhSDhkyWa8Yz3gXvDodZsdMC/93rJMAOf1oPVlYpyW/CwmnmBQTCJaeFAUQpPTzVn01u0f3/tGO5j6HPwaSR29NZmjgOzbUGRfJdhktVv+RLigijvHkFu6NP7tZfP0/tdKGD6dxEPOyjGPPGWsa/NYjIJbZAM8OEcxHiGM3JYpL381payhxetumDpkoHPlGK3+0XI2Lz5Jc4Z2nMsEDM/4tKjU8l15XU2InFO81Uov9KyV5HpUUVvpOZ583SNae5vafjh1+LN/JIcfWWRuQefgOg0wrNOVQuzHMstTZQeWd7jPsO73m/j4Xiv829RZjJjz3O58enkRuijp243Q7vXiQrcmOrD6735oj5+BNoCs9HdQYOWTtDzTRyViFTgmeHnJFa699cSppDg4kiANZ2762Sg/DmiL2l0FjiiAG+E0C3kmi3T0G1QLDd1RfTtWSfW/3fw+0f0qJXOdYDAKT8WrXKTjWuaGs+2VVKiA8AnaGfa0kX18hh07cWvhgfWXXklxS4RMoJ+KJpkQV2oBIqWZjlP+j5J1FoY7NDWaI94Jjrvn2JXZq/sy9KmR6QN2BFbRsoDA43qkaqUzl9ni1aN80gglIkgIaQtFKAgukyyspDXxvRqcydBfHDbWfbXbhabH6Tt1BuDx12v1xzP29/3noKsYz91WKeoxL7yY9KRMVgX3CspHy7FQfo3CblTN40Fmx36TNlWsYLb/XTkT+ewkqBxraJiiF/Pqpnawd6KSGQP5n9rMQmUitiIH/r79+n2mlfGw5dAgSmztRtw7FKobhckU0Gp6YhZRO9lWWKmn/VYevNasuQhwLvl9SZl8WkO35eNoiK6KCKI26FXQVLCkPjqo1BBEdM5pS/CQbBn3NzbvkoXX4DhA9/PmR68zeoeFAPahggwtNem4diqd82Qw5ZVtuDXFUV4YKou/zVIoAxseJ/xuC7h7O/lKg6tjR+p+G15rKW5a4mUe1YRuwqJ3EYbJZS4DKsn0sKHuJt/IRin1Xy46Por0bC0per+1E+wWjfMMP0ja/sAEzKp0MiyD2HE7zfyu3iqBwVlgNIjYa6YLZNyNpVnBYUHl8xMYairVEIm5xps6D7IX/jdS8WqaO9AjUym9YnT7r75z7Smj/tyl7rSBlM1iz6UAxzuIg+qWnu8awyxZuM6QjQLVsakuSaDiu4uQ1HFaODQMyKUQcJbpz3MNrb5HPyeR0kiadb06ON4av3ehM6lGdI3ahMvZlfi8ujR/OdUM+RSfrTIAJJAcnhMTIsiaD/vBE2/13mBrfIHgv4pZv3e3DmIoRYVVkcyEBWEvdNDwnmLvkJVjE1PjE1f0C3o4VrpC4+gfWO5ZIv02pTpnz4Gw2L8XtVrUUnsnpjf06qbeW4YvR6e5Po0k/MiFmd+oywy4KbecIW8I/y3YpeW0cI92Tp0ffCxhuREzn0B6gyX5vpRM3ha6yjQCXecHwU10oONdj16YyM18tSQ+WWy/go3Qw1m7bmBBFqkj/corfH12ubni5YD6NFhCaZL7L5h0aFgLcAthEsVxdmeUERj8isBOxtYwKHRRuj6audoN+5CSScYhLsx28WEHhHNp21zbvg3jMvp9QlkDavYVd++MhkXGLpVMEHM32eZ+WJb7KZ5kCgbxVT5APgKCwHL32/VckhXiBjbYmR0nLagFaoVOkWpWLXpMben9DyGVUxiZ28qwBcokvEHSoi9EgTbehflEdYZS+2e6YHbWb1ezukP+Rx4a77j84BBsyplDbafPX9u0b9nSTeNe39TDC1crSncecntXpOie5x3P7xvP3PonbN4Xj7kLuGlQ1cfTWKyEFYMXFFcXISAWsO07NayxSbckV8YQIh+Oxw81TX+HFX0lA6r2XMjzqzSC8c3Y/y7hNiWjTct4N1Q7XvZnN/ke01IXabv03QXPjb8TsEBiajvEjOLivWKcbOSslkyL3/vhSFf+pIz7ri8EfkyKtPSNJhvtpNaO43Yz3LxhOcOzfI6/8ssp9sXm9kVPZ2jv7rfvUTo3Z881F3VwLck7ftfgbC2GcKyAQKf6hjZPvEZsnpF3iQP39UUvNcU+OS7MJeI41XeN+RvPirrSjW2lbwBYGfcz3PLsqtTR07BvDghAd9y23nFT3rEHXxrvqsCA7THopkhUtmFxRGhMhbSI70AlMF0+dxEm3ajRiPPXAqaueR+be450DnbMGrCrVozjioTDip6srlG/w9n99cb5bMhz1NImqfgft7sYm49fb1lKR5L/Yac+vt7xXhjnxXGRDXe/tgr9mti7NrFgUpMdRX91ibPFa4Ky6zcs+jUs+j+2pWn5OviyPX01LPm/555xGxkIFBrIumr1P3kf+Qer6CZc+0k/cS5Ilj8ClL31N6KkvdbTe2dD77PS5tlkM/UbUoNiajDJak4x3ua4EBolvesDu59J3jJD6n5kv/wxMKzOIbJXMLNIA6PRrXBwgV+bxIyl+KW5dh9r3K9bcmiObmled44/di/trHu6yuOZb5z+q5sETfnNtTqsXKpDV4GBH/DNVbOfMHl4trnuNvAmbaM0j389BOc4afL18gOYqbQdqni8QUc/B53v2+7LgSZ0/fmC6KKtRaZbB95E3ITMtXJawKricQ0VeVP5JsJe8y/U/ymyo0AoGhHAsW04IUyQi5MQhmn5tFpEicXm1R7skmukE1pZOc4c2mopuMUJ1IzX3BGn/hPRW0WqlzBIN31qnDXZTjqdXWC4bfz9EfwQfE/Jc1F
*/