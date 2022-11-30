
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
HPzZcXIYv//RL0/BQS2aLxdboSAd/QPPqF6HxXaEZshkdV3DvQ+T94OzqWwyVkZuWy7U3t53OkOgzGihpai2IJy5KhCUp7OSx5WkY1OVW0HL5VIz1ygdVfRZMfb04yChrpO7Cr8i9N8vbiBp+0HllcBkFjpgFwQl+9qmGBYcThQggtxQWiAbVQJToEsJP4Z2Fjo4/MXwiBdJl3Cz9sUgPPe+5rlQS+KHjr50XPPR3XkxRp5mMBMdNO5mgdW1KVffvL7CSAa8H7HHPT11+MdUctw8VNo6VW0lUKYNKRhpW7HJwNSS/uxB4hIQOl95Hg4KG3GD/D2rR/FfrITliTv+cXgjdLSF5zQ+y3UtL7alkUYTZ2Uta3CJmP8WzuBAmmRkDaviPzNwWzOwhtWaEq9ZSmMND2ufseMz67TP5MEzR9ZDSXQNaygoSap+dsnw6ueVDK9+Qcnw6heXDK/+Hiipu64UiVZp3tqHqoepj8dt32FX4hyPPWtbg/a4fUZ73D6uPW7XkjuGMrIeA4HSN3Wl8VQSqE26Vyn7WlN2p1LWoymbrpT1asrSlLI+TdmfCWcE5efCTzeF8S7N48msnR+Rcvoh4lY3fao67CcpJRa7ShSlBL9KwbTqOgwrETMXFmrcENHdlB0l11PFJKKwT+lVrmiaq2p08NCPxCSL1OGF+i6+vFpfCq+7TjnyC30XZ02+Ie38rxpDfkZ/OTg189lZac1+SYyk2nW/xftXpbGxDO9k/08RZG+CQhidfCJLlLKvNWVzlbIeTdlMpaxXU5aplPVpyr7ANNSbiTCOA2FMyNrZCmKWsw3WTtF2BC9zo066U/KGWZMFgTdPS2IHVtKWqKT+UbhGaSwSNLeLRNVLRMJ6bEkjZcsewkES95HsvQdRkBRdK0YDYwRKzxKxLVDIHTyKJdFW3Og2OIAPEg9K4hnYyTDUx9vHvPDzfOMDBkMxBrCIluidnDuQnL3wouPjxhIDGrosjatuMJDCwYqgPd6+5ZI44E/zp2PSd8kpx6ZFCGLJuUfenZ5LYIn5pNAWD/sNjeIePLq+Z8qlT2pTbVWN5mImtrha/wgL4qb4guBXaxQDiQ3xelcjXq+0mlB6pdVmWBNr9tPgwGp7JQyf1Fj/0UYRneQfmYQKzjYYmf2BHJ56xO3B9Jro/2LJ5TlyZWBWojk8c4ar3N3ofR83czPeFgeYUy6DQii4lIW6Tqi7e4NIaDWyUak9kM+rXu4OHbsO1R/Amx1ZavWh1uvQwK28gWJq4QC28OusRAv4DBTtoDb2491fwclOSE1zYJwQxUvsCC4M1UTQ0sy24O49I1QTFgKT2MtNIlqhOqITGduKl84OfHgim7YPwwa8Hcx5GGeggBDaVAUNEQkpaPbI7x3rjvW/Tvr4jljQQa1MYqHiEnQc7YjOVBpiZSVUOzT08ndLqE0mRrgUZ6RnDMWFx5c41Rlt5cvO12gu55NasEydVLySoFtAnUr4NinXiTVHY9Vh6Cg/FwOmvevxM2BNxM9GIHvcnOiInMbEDox6mEy4pouRh5LEFpyWYN6w09TCITEJVPtyjwFYTqjUGWHZKoigiIYnp9mVFFeu7ZiPkMWT1magBActcA9mZ4VBXkyDjNquCPc1qErhaADVyQ27MnXBwh7NHa511PIrwQKSPVdrD8P7tYfhvdrD8C7tYZivHF5tmsPLoHNA/o8w8oA8K4w8IH8njDwgDwkjD8jXOTQ3EAhpmWkbLGrAgYf9rzDMfQetWc2YJfYH5JDyA3SBe5sQ9m8ObzoN1IVn6OlNx7NeOaY1zCTOSvYx0Bo/MInilsQpjq40boXIjGAjgV8S/YaN0d2EWYDuNj5g56KTOQcHNOFDWWo0TX7iqHv9DZThNEyOVt+H6r4PtOq+A1p13xtadd9L3IEvPl8vjhjL4E/wt4W8+Ws40CqsACg7CSTOyxVvReCbaU7prfn4lonHANAbwTzisoGDty1TmHZ4IWRP/FhbDdsFXcUv9Pj5Mbx9JxSG1yLnjbJOMuUFTHXtuL9HM+vaaaqSaDD4RDL9Bdcl017QlUx3weIl9+UHioY1MRN/71OSiNHarw7JadQhtrkMyqGs+tQQFVQrPe3Q+8f5lXk7xht/gvFhdpz4f9Cu0ke0q3SVQTPx92lX6Xd0VuTtOizrVB2W9brOirwgjFj19eicsCH9wQMUIAIUzP50JsZZWDWXIGMob7gpKgU4wcUZcTMA5fzslIV0HnuZGGFiDkwGEHI8LnJC7ZRb4QTDxNjKI13xR6webLYZblfC/4eNuQm8/I4EXr61pTs2MoZZYST1sAVSsQARLO7TplXsBLK4tbtH50v15HvChLbgcksla+IBg5Khx1dVKf92eSZ6RqvZMt6nGOqsvRiL5wLh74S8dYKiq7Bq8NktyfbFGkxisGYwlXR6L6lwCpiXPIpUL0Fd/l4xO1aGM1RrYQFtgu3iRerdilBNgdDYgGEKwczGBpovGEkEfc4UkkBkhh+MlI6in46CJPY3sJAHLyLoD/oToXHTb3DLXZPJ25c8jvwZlXLTjVo3owKqpZhiIdDfG+ti0wuPF/XAqcFaXZVozSTNNKWUhWO+J+mgtxLGvIntJj4pk+1Gtih0jVyPkSeqvbb+6ZvYidZ+U+2V9U9ntUYtWALcNDnBsjWYlJWM4CDxk3a7MFbJkafl/7ZQR5fU5Aey2ZE+DADz0fI5Ibdk5CaGNb5fPLVDg59cPzp+ssaLMWhOvZ/OTMRCuj0+XDpPvpkp9G9HT6jS9NBGkxDIlZ+/hHkwEcDOJXcM5QjtmxDA16CA+PNf1O5v6Yr55rHSBaxiseStZ757JHGL5NwqeZuy6v+IE1CxgJXOY77F/pjkPCOJXaz0HvT47HJLXozzVhLcvGrHs8bZ6/+RR55rvQpLuZltxjL/Rpd8ixVHzlLZSHCsklgrFxVoAlpqmbeZi6hAwl0w9GfixNZDBNyLAip/F2g4dxEIpfG6W7MVcnLulO+HjyXPce8W5qxn4la/gNijzoPM2YS+mwc9kvi+5GxR+iy2MOeuMuDJD2KutRXp8cwdNTbF5qqY29rF5om4SBwJq5tiYvvp9N7Jwj+/IfRSYgo5YMuFrauZ4s1hpHCA+kLhTPhrFJslryyJMhN7jeIZHqsuNlOY+qkhR2QvMezO80ZnM5shOQeAV6pwsZc2pBG75Boj9w8uElGmlurbRRsOK7q1t4s7z/O8LgIOz++PdCcSueBo9jswuw7eeud2mg8jGfdnC8CFcZ6s5jbiE6aw7bVLUZath7/RJ9n2Zlxxm/dgENOj9MRM7RP++X7BDePg6v85TrDm6cQdyhegNFKhNrKRqngOGzGz7TvptV3417dAJZCKefGtqIISBgHFovpiJ5JG+t1XY9EHx6ot3gmo1oU1jl7h3xVp9CE75X2zgPRgNcCa8C2WxD2wFkCiPsA2H4ZqMV3IHsm5DzYEybtf3m+AM+35VULgx8y5xeFscjjrjc6tSypW11Qri3gGewnTmZM20eXPwOXcLtYSntJpZsQkA5i7AeUOaRMhc68ABnaa+dgr6sqVxF0w8NlEO2ryo+j3oA5yo2pBOg7k02jksNL1yPbNp9k1sc1bcVTy2ead+L+dla7Du1b17paltHlubsIRzCbh6kSsixIu9V/NQXcPBb55uYltaZsKDzVFpiIwNnYrdAWj153NICtuJnw/sTlUUwvC7VYm1sNYSN4I8zZJYhiESGjMtzp0LCNqhD2gcVVaBqPdSfKGUbBLZ0PQi6OEB95JehMbZmJnYpND3AKvwB5TE3EMFX3yfAZUGp067OYdIIgZN+TXYmqNsLuxwgQ7j5pHocKkJlGopSQK8Hkcgxo19Rn4jdmMDzqmk0DRz7kL52QxpejgO8RN6CWKFakZohDdtpGQxl2yNBFVZ7AJNcGHS84+JILWYtgDKPkThzUvVuTRUzFHu1HcikCyzvNLxPoXjOjxCR/SWqw8vVF5GgYu/sKxosgLGSyCuhiqzQi7DCG4wy4DO0iRuPWFZ4s+fuFpIoAybrI5Ia/Ab7vf5GZDsWltaFqatpNk7F1798P/Hp6B5YR84ToNgbiLeRbQ9yPbMgHexeN8JzwOywFtSS6UoRq9faG+K55QeIKrUhYm0jGpJ9j+zMIFW6t+vriyKdvHiKdK6INFc9a2f9VKVb/WSlWk0FBFYESjDG38Llw1YBVl+cxVwFbnseLZRoS7kbzncWAHT11vLDW4KQZJln9xq0aduo+iug9TVPd53DxcbsQEUfHp0AEkHs/9xcIkBepTt44SEO21KTYBlDC5FFlVpB9zPsL/LLWD4G0KJ4r+eorfhcclz3wzM+EmhmyGL53dy17bBQt8JXpS4MUS0aYq5BKe46bhmDKVNhAxoYHCMCXf8HlUf/H2CVpGbjgeAKUpD9wQ2hgQKDd2BvH1qhWnXP2eYvV7FqleFHPhtTsJM+QGVoegTyiKxm1EOaqNqEW9E4kly6oae8OY8hvzmjadhk4+q9fJrG17tNLcy1pprkEbwveMgYtRTxoUFIg6BBljhxDMjL2GCGWSaArMYIe6qAChspiE+FeS0xS9mXbtaWxHhN4J0yOICCZ5TSjyY0jaX3Pi1MmPRZRQ2BSY03h8XAWfNw4AcR6PMnmOhjLPy2ehDiQ8rAAptepyjqo4RhdzoMfcr3J493uChdip4BwkmlITxf+RdPefuJf4zFC2EgMAO+UOLJjOKswro0uAH8WUP+UcQqBTPoL3Ss1QVlZOEb5vKG9nriRZsIkfLGw6GpA75Tr4ifzta5dydEXDK+92668skdyOyPyMscQeuXP/qOtK194/prn/jjFM+nPf5eogm7DXgpvuynTK5eNWnTVHBpSMmz6vpDJ7JsIrUvggJ0dZf3kgBcbATPbqKuDP2PaH8e8bq+Gv5M2TnINRG9tchmWvuujOA3hHzEPUq6DZh9T1kD2xf6q9UfAwKnXhAIhERUcSiS6ESurad0LlaDBt+jIHfQ0cwDj1vP/Dxx577HI/0O+pq+xq6+e5xquXayk3FgKWorEcZSSbsdO9UgW5WDSUIyh+BlgKJblDSGFwBysWB12qqsN5MXklnJSn4RM8lNaiqDZOyp9dzlEdoLH+U5eV+i3lbrXNj9QyWzlZid+F3/gpv/tCn6ZnvdMd09Nq2HXjj6wj4m/GQ7x3j0G8j7yDxMsdZ/9g4ue1jaeXs1FWcSuIr8D0DhJtU6ZzOxDogOQcQkJXiFx1oN0Vr0GH3oe09J4/Cj7qOOz8y8ftNr6qPAW538LqVnNCZnWr6MLE6h6mi8HozWzHA5z+2Q4ifclFP02YGB7dX+x4qNZY2BoYpTPFPgS4ALlVPCO7bkpeCtCnM7QUKJljrzIX0GMexoY4GEtBOsZ8DAho2Cd/Gypg3oG6Y7gSkIwaBnMIr2UIzZtu9MiFwqpLOdxl30bx2iWXOKl9H5/1Dno4ccvyE39JEDdm8jopL6baUKXAIWH6sHDiJaLc5cSgwO8vL2LtVqy9XG3xvy6qLRbzGPGTF3mbn32eg8i07aJMtI1fIcvl+1PQtsL/vaShhwVjKUvMFHUkBdskZziVkmxuSuqoVMKN/nBfptD/MheHI3LzjPicEWlMYQ0bcNKPPA5/QZhsWEe/1uNf7d7m093bIhTPdLtmb4vI34cW/Nf81/BgUNQRSEI2dswBw3zSAbVeKYo8hxmSnGFWl4/5scquFV15Dlj8a+z37GNHu6NTEi2S0yoFeyRnrxTsw4glYP29A+1iFxqF28Uz3B+fpvtDsvoFu5QQGX+a39jo7fHE7bVd8p8/yxH8GZgjGXj9f7mQw8eiaTqF4xtxIJjYBmOxZQt+d+1WPhZbaulXPf5VBwLtXq7Rx2LNLKoyDat3Q/X+DD+KJiUX1G0RuklbYpc89Vfduh7hy9K1OHvJ/tU1nDTG8OsZRwxaRqnim0derJs+BemyATcEEEobcPm7XAoyWgusKgoPpqh5nE14GIjmOSKTjQrRBOjXE/iiCqkTghfXVheGHxoZbxIP/08ZMvMt2Hb0fZ09GMxgNF2KVSOzo+FEzOomTXoDujs+f6o7tEDnus7S+dActYY1J+M1fSP/ZmJ1U+PrBS36QRxV9N0nJlzSd1ypw12cvUZb+CGcQ0RDQqyft7OTIXZUfDz03dJBNlBciV++LQljpz6b4PL43P7T5znC6Ph44/NfW/HWxRira4Z+DvdfIwK2UkgPp2KkeYtOvJmZ3M1+BgOiNlmmNrlMbXKhGisxJ3R0SyblKAwd3UoXk2gu11JA1N6HE5cH4pffCH+yJFOgFdp46HCGQfhgLpR/+VY8I41Jmx9SjS8dLa5aqXUG+cCqcu6bKzJpXzALtBNYCj+tQ5E2FpzEPkAsWwqTRC61Sp7QfS3GJu8n1LmvpSnsRUppVJov5+yOxaTSdL+Btcu3wXWVVGqS396NSRwsUqkNlvYkBZexwh7F2FpDlbzydcrxIJXaq+h95rNJpXlS6WygbXTQknwFJAhtgL4I8uPGq7FzGZRlQbwIMnMiDcNZ1B2fEweUNBS9s7p4KgbTOfE8BnG8J1yFvpmVWpUq4Qvlm5KrLBh/lWsFyuywViq1chI1C3y91mrP49l/szzi4PGFmhiQTvnmvXqMmAVkDVqZayzsVVqom0nACJrhmGOTJGcPu9+McnAlZlxiK4A0/pe5a4+OskryX9KdpJHGBIXYYE4TNWogOINGRyKoiLYPmGCTNolHCc76ZDKMIqd7fCVAaJLQe+nmacDRATk6GndhRXF4CCckwIFEXiGwexJJJOtkmQ87R+NsExNevVV17/foTnencc7uWf4I/b3u9926detW3ar6VVcRzl/UtDrlM6m6tIERiMaY36pgIxa2a+tRJ02QLg3l8og1ZBbXpertDsvfcBp35cASa0tTDI/8dmbrVG0PsDPAJi6UUSs65ketqCvnIHS2k1BxtvtJXUMN6fAZ0sbok4pw9btpHL2ZmPLpR4GzzO63jIghUd71uN/AyuE1rcUIAYZPO7Ghws5ifM2zfqukUyfeGhdpnylNutJ42dUfYPytSdq4ZAZWDab4m8j1bOJobzgaI0Xy6XWBoChzwyqmfIh5MBPhL1v5EP5eOflDVG0SYbjcexMJ/CEivr+aHBs7YPfe8IBd7hKNiQ9Ydy/mClL0bnmmIWgIUghKkvugwW9BtygWUs6QYGgOJvpT6GfCI0qu4XBWY/kAS9GO9/rwB7q4zeKcyEcq1vKRIgU8UeU4erRFa7SKGrArjbaoEjJLGkCPmA7DK6fHMXmBRg9XJiJtuM8YBUkOhJPkgEqSh7WvX7vuQ06S5fiDk4SfEyQpGpwk/FEdSaqpAbvSaAhJFGbMUQhxo0KIUco2Ypp756zfEUIEq1g0V5L25daH1ePJGGhP25R60B5bVywqjyqyy0s3BtSM0439VlGrjAI0EKlLxKmMoOgMSY1bMeae8ifxRQkDfeiCQF0nJ/owkAkj4ARlAQyFgxQ4SKTcUCP+R0R42nULL1xe2eTMYI9lwn8jQcdrBD3ULstfWyUc1XVPgUo0o4zVLBKFR3xLeJYuhmUZCXi2h9Us5eF7WE/9OrZqUzLmo8x4HnhH5vZqF5WEJoejMPH/0mfVl7a8
*/