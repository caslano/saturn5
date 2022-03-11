
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/aux_/iter_fold_impl.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl { namespace aux {

/// forward declaration

template<
      int N
    , typename First
    , typename Last
    , typename State
    , typename ForwardOp
    >
struct iter_fold_impl;

template<
      typename First
    , typename Last
    , typename State
    , typename ForwardOp
    >
struct iter_fold_impl< 0,First,Last,State,ForwardOp >
{
    typedef First iter0;
    typedef State state0;
    typedef state0 state;
    typedef iter0 iterator;
};

template<
      typename First
    , typename Last
    , typename State
    , typename ForwardOp
    >
struct iter_fold_impl< 1,First,Last,State,ForwardOp >
{
    typedef First iter0;
    typedef State state0;
    typedef typename apply2< ForwardOp,state0,iter0 >::type state1;
    typedef typename mpl::next<iter0>::type iter1;
    

    typedef state1 state;
    typedef iter1 iterator;
};

template<
      typename First
    , typename Last
    , typename State
    , typename ForwardOp
    >
struct iter_fold_impl< 2,First,Last,State,ForwardOp >
{
    typedef First iter0;
    typedef State state0;
    typedef typename apply2< ForwardOp,state0,iter0 >::type state1;
    typedef typename mpl::next<iter0>::type iter1;
    typedef typename apply2< ForwardOp,state1,iter1 >::type state2;
    typedef typename mpl::next<iter1>::type iter2;
    

    typedef state2 state;
    typedef iter2 iterator;
};

template<
      typename First
    , typename Last
    , typename State
    , typename ForwardOp
    >
struct iter_fold_impl< 3,First,Last,State,ForwardOp >
{
    typedef First iter0;
    typedef State state0;
    typedef typename apply2< ForwardOp,state0,iter0 >::type state1;
    typedef typename mpl::next<iter0>::type iter1;
    typedef typename apply2< ForwardOp,state1,iter1 >::type state2;
    typedef typename mpl::next<iter1>::type iter2;
    typedef typename apply2< ForwardOp,state2,iter2 >::type state3;
    typedef typename mpl::next<iter2>::type iter3;
    

    typedef state3 state;
    typedef iter3 iterator;
};

template<
      typename First
    , typename Last
    , typename State
    , typename ForwardOp
    >
struct iter_fold_impl< 4,First,Last,State,ForwardOp >
{
    typedef First iter0;
    typedef State state0;
    typedef typename apply2< ForwardOp,state0,iter0 >::type state1;
    typedef typename mpl::next<iter0>::type iter1;
    typedef typename apply2< ForwardOp,state1,iter1 >::type state2;
    typedef typename mpl::next<iter1>::type iter2;
    typedef typename apply2< ForwardOp,state2,iter2 >::type state3;
    typedef typename mpl::next<iter2>::type iter3;
    typedef typename apply2< ForwardOp,state3,iter3 >::type state4;
    typedef typename mpl::next<iter3>::type iter4;
    

    typedef state4 state;
    typedef iter4 iterator;
};

template<
      int N
    , typename First
    , typename Last
    , typename State
    , typename ForwardOp
    >
struct iter_fold_impl
{
    typedef iter_fold_impl<
          4
        , First
        , Last
        , State
        , ForwardOp
        > chunk_;

    typedef iter_fold_impl<
          ( (N - 4) < 0 ? 0 : N - 4 )
        , typename chunk_::iterator
        , Last
        , typename chunk_::state
        , ForwardOp
        > res_;

    typedef typename res_::state state;
    typedef typename res_::iterator iterator;
};

template<
      typename First
    , typename Last
    , typename State
    , typename ForwardOp
    >
struct iter_fold_impl< -1,First,Last,State,ForwardOp >
    : iter_fold_impl<
          -1
        , typename mpl::next<First>::type
        , Last
        , typename apply2< ForwardOp,State,First >::type
        , ForwardOp
        >
{
};

template<
      typename Last
    , typename State
    , typename ForwardOp
    >
struct iter_fold_impl< -1,Last,Last,State,ForwardOp >
{
    typedef State state;
    typedef Last iterator;
};

}}}

/* iter_fold_impl.hpp
cf5mHHpW1IqO6AUbQsLMOYqOasV7IVbtqWLj2wlpI68T4lcpeGeHpamLSxfR8427+qq0RtUfz+7JJDOhzeRPpqBuk+Ox8zrUXHCggjVLTDMJkn1ykpZYMTeCO6loCcMlzpJSYbAgBccSzOAOSsXmD8AKPNiWr2U3ZHyPF5XOrlWiFs2TdyfpgT5S+SWQVxuJksoUDe2kOVa9QrhoXZBQ1j/OnBfcCHNlLohjbr1iVTLhaBtHbHVH5bFyWVjEqQD2s/0o3FjCYYPf11E+5cBwHcYu2zD6NDg3IhUKa2QcAXo1I5BLcGHgpiNBq/8qLIsPq5o3Du7zU75AzsSRNy4OXUtuyCbHnJq+BPnagoW3nAugYyEA6ZfMD7JOiXbe2hwdFGsuMf4oGUlW11D4kwkPSqPDZ0pd/pyM2h4sF+Q+677dKO2vz1hBvNVojT6gM+gLE/3Xiqxt3smDgNYpd97Jja5cS9e+CEyqY61kP2+mlbf9RFGBW/w37IU7cdJW2Gk7q5Bf1L+MM8Y/lVoiis+se5b0mdM6dXWCP63rfvgtQAoRi0kThyOlZcoef8JzqbI7QaV5ECbEQSkZOQIasXI+ZLoHSf01YoS1YHwHYMTKhDNtFCx2YiZME1syygf+e4xpmihYyMkYp25ByAAobONsgUIITYT0dmyDEqcmQ9yHAd0rbY3g57HEHwDEDEDPxThbBTZMwd8IGRYFk1kCNuygZ8H76bC9H6lYn+FDQRgV54kSBcISlZEJFhRMwRj1ZYEpSgLsDnDsiYjwmoiZWgpQAJiKjtEqByul4MsAcGkWBRGpCCwNKF04iVFz6LL+ghCGPaGIwFAxYdXMpJJnd24gjKm5xByfhG0GyE5gD5dc6oeErIcM0MEbDSGlAKyInAvn20EIzDejDEhzfmnCFfXX2YsIwbwzt5hBXtqwmEk0r46MEbYjXZSyBCEHvnUbCcEOaalV4pvzt5/xtyEQkPA0ORzcwKEkNAeEJZtLK/zzlgONEEbPEjd2rtDal1Y6u4qTNozIEkVRvqlXY60QihxC1F9+vNdrjjTX+rkjn+lpyIkmJWyiZwz2V/g3natW/CvAVKS8DkisFngaVKze6ATtEnHb375BPjMqH+EtJUlCf9cNnCfH+8OHyhXyBaaxYoBYJiMxFEZtDRuAfPb3sRKv87LpZTxeuq2UQZnTrqWLASclx9rr4jDU2e5vp/FiDYN1RiQWhItb+j/J6ZGUSt9Lp8YNzfY3d63E27E9yjda2ItKbmVn+C6piNtlmRWoP0RfAiAlNOMlITP+3Cacq/GSM/+GkmW0GpwTPFjjbhjS4JqhQbt826Nt7tQhl+cuqL6MV2BjGOrPZNOqUtY+Mu3VOewpMIoKa7nrCmNVTg3yVxhAx5bBOWoGAeCzhzEk6ttnDTjTeoPI48PBTCJOsBvB3ib/5YBMHSE3orv73zjOWPeZSc0R3fnMh3bFaBj5WWR6ohHf8LLdUV5K4l3xCdlVibb5DqIsj/Sr5FMBLHIithbbH5B/Lc3iKL2gzOyIUZ4cMvkmD1jkcOLm1tEqKiCv+9Qz8W959U8DGLvi9EQmJTkF6xRKCq1gLA+jBQYNy7xLkmo0YtFu32uDHCwX8DVzXyMd3ffWDpZbB+z66ztDB3fvJmsX9rgO5VuoYykpXeREqikNcAGFn2fgAIostRHllkY/SEZiOWz90Rg1hAxiy2YJmW1pK79Xv52KocrprqDL4XkBS4qxVhy8f9sP8r039ybI9cTUgSDPadG5TZk5ckCOeBBLmUm0vSC6WUn5hgt2ZfBxg8BSOz3yATWvEzhlD/4qzji1K+ntbbZn0VbCHB/QKawfy5pWWBPkeX9IWBcyS0dnuXSThpLpqDXyKLfNCrb4juVQ8lR/Y3nkp7vKGDZENHkZUH6aNm8Mor3+Voh3L2cqocBymGGmG3ogIRL5a9z82sKcthUJRQqJH16b05Bi9LSbUNitdLUCM8xio/BYVDFrsq5qyCdlzGaubuZxkZZCqAH/8kPjTNyr46pjf+v9lhq+qY3Pze/jI3HSnbwU6/JD9ngJAZ//PrdQty0iv9yQUbAqn3Qh/gwD9heDKHQ4fCpdV5DQqN6MtEJkYI7/S8SQl4oVDbXvH2II6ojBPR01N7HrelCC/xT3p99yEiz8yf6r61maJFcxXcQ6+hfvd+xURR/XCThUv7sAW+QPNM4+Db/ABevM5/iW6CSGXewPLci2DRyYoZT1nZdZ2nLMpkTmMGQaWOQ/zjrvt1fyrb6rHrd9lKe7TqqnT6YhAI0CbVN3KFjB6LaSQcJDqafqTNrDwoimD95EwlZ3uaKUbHeWb2srUeY4rgmFLpJ3zz7nSOXci3TCbUY8Uh9x69KToBLMhWZRe6BR1LwAp77taW995MutSrCcae58yz56U9Cs0o3u5E6CPAlpNgX2sKgaEocpG1iRF8ygiHmW7yukNQoijeq1dYc55YNzyMbaJcLtHMO5XGC057LXN8ZIxQkFj/CP1WivcENLDw9a4lmrh7hdh3hHyJ/QHYEI5mQ4znlgAzGWqPhJ0YYqZR2wxbmY/ujsxJkpqyIEWCoHmDazud2T4gGwzVWNf6BGEuQ29yN18bjBSVJ6Q5pN6ZttUpkDLLM1Id+RBvVZnL64Eho499Dc4aJx87q5rGg9pf0ft1E7M1DRda6NV5rVaJdeVm1+RxhBQI5+Es5gt8umRJyaeKPt1AK1b7P+MNvF4XvCqTi6YNSdK/4XAqVehKteZjjDupZIBbYrQY0Gax06dovYu3RNsVlT5f3wO0/o7yuor2+y6ksM2wzSz4lFhoU1l3XiuvXHnG31rxxc/yJtd91fxPY+GqhCKDTQM3Vudsi9jSALs9Q6Lv5cT80f62X/Ve8S3vLpLv/GpdZfHvlnhjruVbkaS6ciGjO7j8ow2RxeGgaeJHnRq27NKa4dUVZSj4AagYoPTUMvHUvDj221pwDlwQihdVBtkh3ksVUgfr2JCm92Jq42AjoXY3XStJGu5f6qrJITYt1Nnknz6n0bsak5MWOpBS/wxU6txsTIoYVOtQWwVQa8kcv+UUeK+fJgPqemRfGFc0xnzn4f8Hqlq7X0FhYvUNg145N3JyuzOhe7Tev6pcKaVKSOhj6u2JkMX9ZgZQr9qOPFRcHMp9cAMvRQmztO33Hqi4iiC+aH19EaV2nx2G9RXiYWYdvHqiT+gNP44I1g6vFZ1oIZcYEvqrbUFsKtaWKuZdnMHc0bNQHDxDQXHPAubdMUbrqJOgbgRG8ievGA7Qc46z6ntJOYlHBdX+svfyqTQXWd/HVQfzO3cEDeEOVqJZS21puR+f68w6+qWX+so6740TZ04OE+vlPJ73VPa+e6Hnr4pgmNoHuIaLV1zZ7cjypD4mHZnsNAneii9FfTBm3T4OjfmuCFh2vLp8xxXud+uCfbO5EuZxcHV5YzzPTXntCYIRKTQyUaq49gXkyD1VZx+o35lAZ2KBI4qjpzE/2X/ziHrfYhJd8AqjWAIPlmap6QHv32OviawmlHiEm278xXYlWMMRZBy88/l9zbhE80BHdcPMs5L7AoDPRGFyhQIXrIirJe5k0v4DmYwxAZvReRNO3g4vTBOpc6N06q0yZOGFK64QWjNfdJYb+Yyb2xR7tQKTyxTMw+/UmRIXfc0OGO83qUqmiAzBtGtxNC1zmwx1nXlmUAGFcrr8STv6OYhzswTwuWQZm2ssmFDBMZWNcHx45yeG1BlziHcO3bMH/QRKlCWjZDYemFxk0VjsbqM6p0E3cGvWO0NJ8WtJKDso+lLtAyZJk2TjFFlpDPP4HflDzt8khW+T4gnXzqH6EOKlyOuGHa006025APkDeew1y0mPxl3DTbyRxaksGuZR3wRZ3BylB8vgAox/RODrSrUMJfIoRo5NOxmOkFjbFzYviKs8T05PKMovUWVcEp0XeMF/RL0S/H1qlk0yyI7TXJkV3oN3hNhsHkZiOKOeUunnnzAIBNDfn/IctWaeZe9uSXlnWuHVvpJTN7+thhvgvRL3nyTzeXLY6bpHXe7Bk/wzQTTtEvpAYLSQO3kdS6JEQxRmE1IvfSZ4GZPPgFAk4te6uR+w5vpCsP8f0UIbMWOODLPOPZWg7R5gIk7Nm6puj/jXpUT3Rh9OhwQiHmC1GiNK0dHJrBmT+dtaTViGdVxnXhG0RM6edhn6AeIlD61O+mxujhIcWQxZ/h9JlGRfGz6L1EiwPPH4qCpk5fibN/UPEhE6AYI839jgh3XnsNXIM3xDAaL0hL8Aj4Mz/LvLwtbIMbHUcUaoMJwRhtWuUfBrVIuGGXmmzHPeVO3jkQ7hD5j58cL6aKKQHFRQ9Zvi202SdwvP7oSpJbbOoUoKZ1QKN7p5EH7GZdk/KnpqHGL6a8/TmLHgn9dDSM0eLRoIimeVWuCNYrxVUBdliCkJ4ekrjv72wz77j0FVXNdKM8I2AW9oTziV4245cAXVljyrbYTRF89d+hmDmQWZA8foomSCPqpjIecwUsyni9OLeLnmeOBAmIXQ8+b2KOk8ubmKafC8OaJj5PHOOQjDHemqd3nFqGF3znqcWK4e6WHWUmz1Kq96gJYXZX4UPs6mTn20xYegyy3FwXZmGBvoo075UqlapwXmKfyQQVB06fHi2ehFBt9W8MQ5+trvc9M5bUln2M+3Kgn0oWxSeShs45y10CRxoAyFzJohTXcC4e2ITj4e3ROfiVFqQ7uwNOSz1x0emiM8fcnu3OGx0M9H+sFx0tH9posyf5MO8wT9qDVB3/ThQj0Uhw5QX5N0xR0RDrkeZwL4ooxp9YLk/Kp96Ml2eu0DrhtpihbrHgzFUe+P4crBikvPwbEa+pHsXxhynPZa/EoG7ksuo6JOR3SZ0GoDrsH5Ex+HtWhzctDFRShqRiakHf5M8Ktz8M9q7a+6FzZN5Qn5S9rUng71ODb5DWg4dwFVIJagquaO+dp6V1GFgPj0vNGAAuchRnv/5e/0rb3FuShMRugtMdnMUA78WcWv/dih3OY/UitlayNxbsLlE6mFi1SsQGW6TQWFUw18znsenEVEhKOmERU7qfUUGi0xYqrh6Dr+e5mh7y7dj41Zewsrd9sw0/6db7vjvQpzTqfk/Kphks/0J9wfBXrNVhQW9xnCq7+or82TTpz8Wui6p8G+8fmzewhOt1j6wjk6nX8VOkZyCfKsd2uKyMSwVwPSt0QSX5rCXGpJz5jSZScTKnp7lAUTXekj+ByrP0NFqKs/QN+hTSLJcPUUpbLk/BaXO2SMW5y3+7S7Dud5NpcxIZDxPi5e0zSrHruybh2VOc4dUUH0on/LIzFSgLv9WdhKf2iP4q7zxWIeez31bVeFSx6CqXJDqJ5e0kUfC9TxxLTsSY1a0fQ3nOZaw1FtTlXUIA968tncPZvOpAUE7D9QE7bnF7YG1T+IROP3iZgy5zTnZsP95W+c7WdgVYH9EXJ3BVqL90JP7ZjWW5ebiec1sfGWW6715oSmlpQUPgv/kseL8za3YqiI7I4PWS7cpo1ftyPfQAVc6mx9kDVd4G01Zy/+g87xzlo0zx2GTRkReSmuFw+Ha8eK8yp13LvKkjuQK8wU4nsP1CUN+HVO9pj5INfEaMofRfLii9j3ay1GJ1fYRnMWzYh3maDrazr1EvDbYbzervsUC41YhRCFsaHPzDU2dT9JS5g7mRQgTEeyA80FU/zsR9H2QbfuobtRGl9KriEEdGk+XQ4PBhUUM+JbF9glakOCWyIHLGbHmQvLLWRg0busWgocfrZfs1A7Fcq81YV+me8ny405am42XLTAkvZ/yta1fV44w31BO+p/IKv9JOWTlSh/lynOT6ECZxG0be5279VYE92CcZ5dwCb3qLoPe4RmnJKVtfdeaDhYpTEKowXg2/1LO90ctVDyfo15U/H0KIoLPxSNxW2nWt8lnAcJHR+2IIpINp+PKHQSd6bDf/TGVJNuTkX9xIncLdWJDOpJH8NuBjT5W3rK1McnoqT9zZ4ql0nQtp60sjbJuhUPZp4FbqFi/eQFHw5dbrkc0CV8FaYhtdBmrkZkXLnIaHDRzDc8Hx4joH+JxG5xlBIjTPM3myagj9wc9z14rCbWYnWw3NFMhex9kediJ9DWw+uQ9W8HvO9Rj6uXkjSORyMFfrD/Ni0vackPVauRPuOdqPe58cvF5pmcTRMntjwvS8L/yfEHHLMFlqPAcK0+uRHeNrsZvVu6B72UZZ38zqXV7Z1sJdXtuBFJEp38/uERyM3Kpz9GnaTJsvz4lbIxop21Y/jqF3r+13ofpE1s16HxXSAbRybewfhXpml9tQ7iYaKk+iKEphXtPZBsrX42oIZU0eL8rUJHCxc7xTRRrwHJs+lHDH/JX5MNE1PM01jOeJsM+J7ZlOUpdAvpkIiEcXxEhZ3dwhhnXe7mywyqwinMkG6WvFatGENbFkKycn0xPPfTTaQZbT3RKV97TKy7fUOBj3+TgYarJ4QIMOFA02Xb9VUAN9jOmqclCAfpK8iTFIsecWyhfDTbTjbgpAURq7txMwxXF9RODQKjxjHZzq+WDaM7qzkDaM73h8m3alUf4h8DBtIRDToDoUhJ0dL7fMixPaZ/S7xBRQkRmfdelbMDOSujfP8IC5MtcujQPKpH1yBWzEYXPkfwump3uY+lbAwt5W7Qfdhvp5lZSIwzKdNG2SqeBrSG5poXh9eMrQgXaRfEGBa+MvC8KeeC3lwEFwmUAQ7gblmhQiZ5aSbNs1nx/4fxYkZHWwzHaK+3xycTbuzjYeJTbk92d26CJpyMcuQ/ofrJJN+O3RJHObaB/snqGsYWaFVtEqHtoDw+DjJK42cVLsl4FaOOGl9ZJrjojh/Zu/sZByZ5aXId+rXCyOCx4108nFkz2M9mKkZmJy9aaLVupYoLUQoppXFIDqyCd4AHn5wvFL5jFnImXZyD7dxoDBTdfrWIyrb5/qQNKvwrXaaKjsRaj97gr8drhwv9+ny6hCl1fAW0UuFA5C1Dte4vz3xui/HjrDQpNM4FQQs4Ls+Lhv0f/pRKmJidJ+qyUSScGT3Ua0puwcQiGhWZrtPySAMWYkcYmJMXTKeBDcSupLgSa4VFmhQUYK3WQ/3EoHplA8XwRgasXNrBelNuwOWSgJIDWhaXQHKmzWAZ9hL2S6j4Rno2/2M+QBakKuAGe7zGaCPyMgtQjaHxGu6tvXQD73+Pn2vlWhUAlPZaPEQql+O9EbA3/nqwHhOJXl8XMxIEIA8ZWr4C29C+nb25IZO8+eOMYyDe89lhpEwnl7tQYQOaD/s0Jupwfn4v7r8gARSJe1uEJERcwGlOcFNBKKwHiAe21ySxMYpT9dHKyWo9fyxPce0mF+f40Edj5tS6NqSBQp470WMJXAlB1guk140CkLu11I6lwaWjHY6Typ5cwbFOmpG2BZQ+8GrgnecMUIsz1L2twQ6fKPBHf6yhhcgZe2YIQiwJTTKH3q0T89OHF5hRRuziyfAqVY3iW7hyhNmXUO9UXr7SPhb38CxSPGytJ6ljGPwrULCSzyipuSc3jyyRkdGXYoWsto7PMVa4X/fBmKVTKyAmjUpm+Q8TJeV0oNCKogY/SkyLH/RcNj9KlUyXTduTubcK+ZhE1y6ABUwc24EdqOY2daO9EqvVAyqhfoIkH8V4LWW35EegOWYbvn8r/R3pcn1MJFKfYSi48ABCz70wKxxlz3g8hmmz+tSS9N3RbFJhqul7EOpuK61R50jxi7/e6HCv7PqBMUH1NtsU0nLQrXsFVN1W5NjYXu95yxy4N7+CfvTThSqlO7Ei+4+yHW8CG5Vul3WHJv7KWXu3fhGmiDSs7kVkjSnZp8RRhV9HAyj/RfjNlC4OUOIHTo6udoYAnp81pN5GGL7Fz9mc4IhAwHBh7k3RaX2qbc+faOhYeAt6vgUj+cCC2lAmQwEaoc7n/fom/61+w7J+HnrJeYUJ9hF7n9vL3QUGOuHpnnyt77o5NocyvMw6G62qS7gSyF0OJr0p2IxLXT2YOHr1vulhzpvBeeo8lu2IpL1NExuujFnvdtrkUeYtrQ1AeDR9y0PVOWQfsBxHWY7WOo0/e2Jxhmj2qoFFTZVrogfFzOC+6gbrR6A2I7FwYA9RVVPygkIAsNMsV3hizrKP7qDalMYqjVSeKqtnM0ebI9ESvEzwUfGi7y0p64RyzV/R0xW5gJG0mOZCbOWXXICvDIXHb8mF0VGMbNSHl+U2Be4AOKwRsdFKqg9QtpF54Aik3U5sP827cFC/sCYmk48ScwuQdskn0WN6AR6NLY41JA09lc+QkoDUZKfj8N2L6Xc5kLKiETbZj6OfOEiJqCgH0IzBOTHCT+jxtfz11YCR4ALYcuxHz9+As0qkZN5z5a9cHD13I66KLQtOX20RQrHmUl40FGGu40HRJDIn44j4rfif38ja0ih4l2sjljnSw9wpZ8IillU5nF05iGKgjtFNEIEjy+K9oEsL9L6C6KUdMhIjpX7nKrUyBe6UNOx7S0cKKXQrsxU0EPcOzYeUm/aubeizpCzDZqW3mWC3dwLb89/vjds1uvmlBWFagCZN43DHWCginHv2mUbX0MJVT80wW0XewUTsP1qLVmQ2EJrskJLqkIkteiZfaw8SsH3KkTX5CBgyPaYQHosJzCBme00Rjx3L3h72CgxW/iW50Mk28A15pxw3e8BFUMsQHvNP4oUDp9/AFV8WlF4cpHv247kJyNpbiynKXJkrClm458dfu1eN2CTZ/miS6Uo/nRGe/FR+7w2BrAV7hXgvClNB0LUQ5POGbfe0GfxScdb8q0KDnzLNOOymkeIqDiIUAyuhHwrmEy2zAyo2G78zRoB8rKHhMBdEghAWFIOtfVCoxboZzJv4yCTvlmxnz3WUamkWgKyc3ekCblIHDexgGyKkcQwKpNxmG6qUyuSg4innAHIYLZxr2YRCjqWYeOhrvjNRRaYXWXH8Hl6mKKmwccuxtojPmeVy2qXSaPs7edWxW4DSxtmYwvgqIIkvK6V2q2wDYpFS+0OoTGrJ4F98VrsJA2GES40lOyH6R/iqbFVda4UXGtccEses1iJW9UbyNvzTAO5mRA+yB8u4PMvKBiBEW3rLu+4eLgh3AZbBOHi5l3wiUQjx3BZJhc8U3nZ259XPY/CR53RQJOmnJ7womJYaUG/pE3XogOFh7EyKhxAre5/6A0lhE=
*/