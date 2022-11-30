
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

template<
      typename First
    , typename Last
    , typename State
    , typename BackwardOp
    , typename ForwardOp
    >
struct reverse_iter_fold_impl< 0,First,Last,State,BackwardOp,ForwardOp >
{
    typedef First iter0;
    typedef State fwd_state0;
    typedef fwd_state0 bkwd_state0;
    typedef bkwd_state0 state;
    typedef iter0 iterator;
};

template<
      typename First
    , typename Last
    , typename State
    , typename BackwardOp
    , typename ForwardOp
    >
struct reverse_iter_fold_impl< 1,First,Last,State,BackwardOp,ForwardOp >
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

template<
      typename First
    , typename Last
    , typename State
    , typename BackwardOp
    , typename ForwardOp
    >
struct reverse_iter_fold_impl< 2,First,Last,State,BackwardOp,ForwardOp >
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

template<
      typename First
    , typename Last
    , typename State
    , typename BackwardOp
    , typename ForwardOp
    >
struct reverse_iter_fold_impl< 3,First,Last,State,BackwardOp,ForwardOp >
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

template<
      typename First
    , typename Last
    , typename State
    , typename BackwardOp
    , typename ForwardOp
    >
struct reverse_iter_fold_impl< 4,First,Last,State,BackwardOp,ForwardOp >
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

template<
      long N
    , typename First
    , typename Last
    , typename State
    , typename BackwardOp
    , typename ForwardOp
    >
struct reverse_iter_fold_impl
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

template<
      typename First
    , typename Last
    , typename State
    , typename BackwardOp
    , typename ForwardOp
    >
struct reverse_iter_fold_impl< -1,First,Last,State,BackwardOp,ForwardOp >
{
    typedef reverse_iter_fold_impl<
          -1
        , typename mpl::next<First>::type
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
      typename Last
    , typename State
    , typename BackwardOp
    , typename ForwardOp
    >
struct reverse_iter_fold_impl< -1,Last,Last,State,BackwardOp,ForwardOp >
{
    typedef State state;
    typedef Last iterator;
};

}}}

/* reverse_iter_fold_impl.hpp
VoNKUJOqKaLTxz7EiAH84tqXm8hr/HXHbY2TQv13A72IxX/KakalYLiUVeRqwO1o2llcMbeMXxkH2/kAlInoDW9WWjySVjl2gKzEIWuEExKebW06VOEkKww7lYDbm5C8kz5JCvot0WvGKbqT6PKxN7vyY4so0/keqSt/po6onP/l5y32rrngywCcUzpFc0pnBGT9QOsVVladxYU4aCRAq4aH1szzy+1TcvsMi567qeX2nFtxuD2utHlwtVjrkgQgmkLlbF1SRFZ3YbDu4tVs8QUwGLI4hXmucpSDHlmcGRCnMNdVhIzmggWgCWQAo6OvEXawT5sQjgNzfvZNA004KFk0hQBbvHyQysVxHzsL5RRGo1xxS/5w0YC4EGpswwmtvkfxTA/fUD9unTmYy7xKIwDQWCgB8ZZYfz1WdlMzAjZjlAfmoNzPQvXUTKm1md1/AQ/r1/S9NwCAQ0vEPW10W9WRki3bSqJYCnE+oGkxYMB74pAcHD6VQggoSU8jR5JrO2eLw3YLe1Rtlu0pEuUjShMcQ965cTaFEgoBDqeb3WYhZbOLG5wPgoIFFgcvGNYUs7jFBZfe1II1Cxs7wfB2Zu59792nD9sse87+sCy9z7kzc+fOzJ0Pes036DU1IhWjX32NfCcMy9uOJGg0xcqgqNGA8Y7JmK7PSxsIkaUQ0pFmrA1A0ZL3UvfmXu2WfqVyHC0Wr/LIKSzbQQ4zWolYxvtsH8jNEyd9NlHd2GgIaiGmqd/5plJCeTzR2HEc4Wox4dIC/QjajXQAFwhQarc0sKb+VZEWG/BXFwAeSIzAv/UZAr/HBF7xOJ28Rkd9dHCjtCRDjaZsnd6z7y767Bkn3/tCfba3/V8I8ccP2AaIGQLbH8Lk/+6C75EEmPtZMQLMPHnXFzK3zsDPt3E3d6oByAcfOVPswbNOnoeN5/uWYnmNXnNbw2Mqz70yJYG8bcpv/CLfkRKIrHtThu5YSeDe9l+QYp0yg84W0o+DpA1Qrjl+9Y8XZEuJ/c9PF8N+Jb4O934++QpseZQgVEB+RLUdBi0b4R46fiDnePzW3wY6zaU4/BGYZPFvrk1sKE6MJaeLEcN7cjFwavE7YT3RUYgaJq7U0TxmFpaQA72qo3LAilgy9DBzLejj4bPHC24V/26pErDXxZcW8BdGDk2m/0Q3lGC36jllmLyZdolSn1Ss+1T8EszA+U2/6D9WfmzZI6S1FSun112fMk4V8ReeXAwPU/2bP1+WC2/b4e+UiLrL8W+0pxLnAPxHKkAT2rayRHhPeIver6OKH+Kf/1Z8y63ncGga/oobL7X8Ffc6qGpRVSV5G4RrAksu8uULzPW4p9zz/YetHzXfe9ioZNaxK51TzD5VwK3hvHQ8Hy0ALwxU2+Z2OhxW/ayBacAv+6UeBXwazpLrZ0+nX2pbNmRqBBPsumqsbxzSsJ3sbtJjvNs/wZc0u1h5I0itznCspP6dSIgW/1Gt9VOtdbwn0FmL2LnkX8f0EOfwibUnO4IZ3BqAOT+K1ekrG3H7oDG2TJ+3Hyd6JQt8yl73ZzaXsD6WzPrPbHGxnpFyfyZZwkAHcGnlLDBuXTCac0HTQUx8Xu1iq6rDAMygqZVILSMwvDgwyK5hQc6aPl0cHCod95+56btbfIv7OlbprCmrlftfSJZo89lqV0eV2980vsW7GJSRUXik/0SyVGtwseBE/b9t5LvqlNg/QY/5z05db71eb+G3vjhOVZyJdwSH8WyVSM7RjvuoT5+DPl306aZPj9MoTasdr3I6ildE7zbz1+d9btU3Cc6atB56fe78YgHsYMmSnhDo4UF3C+bNH/aUOfjQr1/Q2XofG2Br3GWrQX61jVf8eJNe077ppvscbS9joCXf9DzqyQgx1U3V+3ruxR+io0r8WjYXyINVyG7aSP7w76JOyoxqr9VsJRrVgs3iZxllXakQKi8Z6Ndtd+kTG+9zbIRXn4b/xnfjb/lNar3xDc+q/o88+rQdxhfpiZ+geMp2luwBLQZM2gn4MVFiuoGjT4fRFKB/vBmkIYD6xLeoKkKWbwYEMbASwcg/gVYY2BU/8FiiwXyQ4ZRw9R5WJ7swX6luqTsS4he9MJ5/VpFfO9TxrCimvycXackMS1az1hu0JMyYGi05wJK1WnKQJZdpyV6WXB5zask0S16pJftZcoWWTLHkSta0UEseA3ZtZK3H4C8Ff/3wl4a/XmQO1joIfwPw1wd/mUZkk6pIGAeNNgqwgZbo4u/19SOvw9KN/o2QWBy05JCWHNaSXEtmxbykoqev8u2gLsEkXNw0jLYAVqP2xJwR1uQOhdHbsZjQWxcrQ0sexT//lbusqJualr0/1oppurJA/dmaLgV/PzTxl7XhT7tlFKMMPOiptKSJvzvhI+OnAS07HMHIBSEsNyakGgv0aiBmgn0aWDVN/RqOZ0DD4t+DWrCfNXGtaaAn8KhjOeCi9Qmt9YDWul9r3QcWFZhNVz2O0z7uZvfiNB9ZdFWrO3EO2+Wm2dQReDTE7t+EdR3eYIF9aBEFd/CnfTK1j0RKTG/ko74yc726uYKm/lWPo2iJ10W3NaB+lLZinUIsuDuMz7nDeI6REc6SGUx7wsI5AIa3/WLq28F6juCCNvaed/eJsbdnZcL8s3Kxo0BvrNevas14d63AGIJ9NSKLHocESKuCp+3EMp/+5D5vRz8t4E+wRV1sFwm8RYfJOGtEDZQvOH9MBxsQ9X06yrpPcLf3EK4exyL89Hl4thM1djrrPdQNU7ArzIfOGxP7wk1pNjPMmjrx0xeJlUafw2CfwMEQf+xCNLhWiCBdahESdoci/C6v7OajNE2fofZWd6tWoNPU0dbUv+NPZrw752McPSZu8HOALaNbG6SibMZmG2ie4y2zP6FrBXJaIFP/ci5if1FmQ6yJTwd1Ilv79D85NE+FQM8ePOY9dMOCkhCux/yt6jGdDaBlm3MeqxUcDPNnqxGDuN9TZrvAtUAg8qFqabDOjbBgis2JMEcIsFhNwzoW5i01BhYrVCwurxRtfVRclalYdKn4dZrt6tt6XNt0zPP17vw69ch7J5Dh/wDT9+0Uz16MATdaMP0ft6Tf/sjY/XBdB0faTs9MVvQE0jOF39Czl1/7zy9Qtl48IVTWByRv0lBng70WZo8PkBOJLWCvsVWL9L5QDOyArLADdoRjgAqcKhH4AhZLo2BOYKVMJOZshpkMhOwHQZfi8TMIqNw184h65ewQfvo/SbjqT42Usturm421LHEutpwA+pfNVtw3j/Jdf3pDr0/tHbl973FKeUlMCJ/nDj6oLh4kLljwCf8r8fkw9f3dW8pLf+cf2HwmzO8plYv7yKUsuJ3/TXmZsVx17f6r+xzdxvN2emwvnkcvzhWbWRCbBy8QYtNab+SqFHNo23Ap54fPWO48qZ9iurE8u5fOmnqG3H9T5e26YutVoArzg5Ie1gqqYpcWOCgbX6RgKYYJ7x+Nl4CSNg6fFf4B+CxFZg3xO9dQkh9oDLd3BPfzu4Jj0vXUZZhccHRfkHTQtShB8HfNevp9JchrqjiXAftSq2zX42VgbmoLQICDulLBTpzgPq2UBQ7CtXDmZc0Nqq1TMBw2keV1MSV9rMtoptBZaEFqPj8vu8/AT1rFT1W+Rk8oIDd71haYhfh6VRyBBRO91GFQNchH/f3VBla+0xEc4jevGxOB9OZ+Ch7dtY6wcJHYDxjil6wfE6Ul8KnVuVUABVaH+JU/GLOXFsm383LGd2aK8Ul7sicw7LCPytiMpb2NUbIesMYqXEiDfPxzTMT1wRDWtSU9WOeZBbLxxSw4BJOUR0Lh6KaxxxzNxm7SwnxA5WVVMMHMy6omGU+P80aci99ytb8M67QzzNa69dfz7OkrDyvx1v2TxFsH3Ozjji0uUDGoYy+YBKgYnMt//TDWQpnp3bkc55SzBEsprdQ21PJTTvraqG2o0+fFgwccsZCICQ1H1y7H8ARP8IDDKCVhFJx/MKQWmBDxuzW2GhvMyGvDw9Gbl5tpxOxBhKs+1Zb2tIgGnFo7tVym3rkataLVqNehRs1QNSqEorXfQJ8YMButXY4NQ+us5/fQD1zONOob3ENPdFnR3fo8H4yCzxRjJZ+8dkctP+MQaLijjnK2avLjVGunSNv692/kpm0Jet1zeKp6/lqQyznXdqfLcbRspWNrfIPlob9sw2qS83dg9MiomDUySJOOntISFHEByi1WGnez8CLgA1DkcJUuaWaX7YP7RcOWFvrnML37pnTxyJF15/v13dgSho3Dq9v1xLZopaNiKy8556iOR0fh1e2njKPZs4/q+fJnzv33T97f5W2qgvo8Dvuq21zxJebI/S8lVoNxSzx0PQ2suhnHhb5wnFE4runsV7iQ6ohEhHcU4P2VgHdFQXiHD08VHwzqt0yTrdePE9h3urzbn1RDAwTR/D3eduoDQ2RzmWQzjqP2nxWKjM9+BqwYoe1UGYT2tr+HdwCqhqlFC5gxQGwQSu7mlsZIiF1Xo/dpgSG8SyV5mSC5q5H+lQKrhoFuiSHBRm5V+HrUnVFfDoNUFW/N4UMGAemDsM/DSUnIfXeBYJEBGKL/XfXMi/IMsBRv173tc80zTy0w2Wq4/ZR65qdw5ivS5+nC9BkuQp/hovQZLkKfD2z0aVooSeQGS3NU0qgWabRwmjRa+H9IoyqFRnNMrPrn22lknTlvvp1GXvNMxXw7jawzH847Wqh+3tVHVPlXgFy85gFakDav7AmMyhWbQuNA5YjuAwEfWxBzRDtpBVoZRFF4558Z1nlgFJvLoGhwg2S4NG/fvjs6UfOowwxEFmELgWzUdeGjYMLuXWFUmyyzalQHRtkyGdRMnNLgCbXor8NLL7cVFs6BwBdiq9x6XwEIJrtLwn3QWbC0tMDfg0fs8U4FJOhpCngCIirajWgGIzU2m2LXiFpOx/pqvmiP0NtsgRxOExNq7Hw9Fj6P7tiz1whiJ9+n7M1tU+msmOcdsh1NMZ4skt88ebwEMgV//4u81Ir6l7Eawgn2cV7QwlT645T1xvGV9Tq/FZP4khPUiVkquVbERRkpEnnv7pm0ZLh4f8PRKeOnaMsgdNkjRlXDti3LsWQrpcVG4TeIiKo1B4R93LBMsY8b6sQP0ZZwS7WWzMIXVoFdeGBN9KSAKfCBjoOlPWtQSXLQdVVFr5NXkWRq8CmSqUGVTA056gWibBoF1GU/uKNT5ue8TXG0ILVVfscGhkOy5ynf9rMxsyBH0BM921FiZvfBoa1oaVxz+oju70nc0iLq+g/x2Q/I6WDnZqPo4rddZhSSSfYqZiwZ2CwP1NrqFPW78/fEZ0q8GV7JiUKHC00Ld47++OnRKef/xzDn+C4AP7+PI0ahwBoS3QDcE+ZPXmEIvJLouYATKynNSVgZ5rXjR7Bq0M+k2HKbaUq3RDfoj1GWBF72+59KYy5HdLgV0SE7PNVFQ1c8DPMW4Rjm+8WNrqlvTHyNmMqaanGBc3SAlB237OTRHMk6bMMyoBiWsMn6DwaOTclvJF+zApWjst6DFG5SPvoaxS9Rtu2S+LVmOA4OL3YJ/dw8/KAIMcQfIiHIHVHxYCnmooonD2MPrAmZpr7eEjzcwIa3/TXKXRmNwJW9n+tU8Qkjeo6K3CqQ08PmNvkQSf2LdgvSsQyMSQxgR+ssROxLgVkOWWIGu9d5297/AuYFXYUwbU3OcsSXmkZ+tB9YChutH3wReL6lumOdoyRMB7G6a3NEn7coZYyKF8mCsQUFm5QBmE9i8RFBn/OfU+hTV1geAIwdgWGU0plxIaVvc+E0legaLianh82s//al1M/NHTYpbOanKVRumYTKJSqVqQ+nQWWDbwpxe5hak7zCHZ+JIi4K1JLI7JsoVJCumHTPWj3Y4OkhitcJUNKUW8nmClMrx2Yrc8vI5lKiIcpZIBtuSy3DwwNq18dSAsDHXtHfgNdpf+t02BWCXPIVigJzYxFYXvJ3xGNuWqBQ0OAXpdeGkMEZfvXIEd0YMRutT4FC+WAKEP31ZslWwUzHDY6SUDOyVAz9BshT0SwwmdBDMrylg141A9jBEx2GEyGevvSw/sxMLPJFv3EXiP/w1S6QfKhSzxKorZLVIRX9eoaqX7tN7mBNGXpjBENmuSxoFxxlRiesAQvuc024s2CsWqA3WrMBzPQMRu8Zy2ogI1TeXuJk5ONRbI/mOENzuX2YGjZ7lEo5MOa/F2OuJKlu9l/DwBBCthXmLcV6hof/i8R6+/eoiXOm/pT/JUtIJjJSKmmJXoGY5mZ6UHNzgUfde/KILkR6Uz9R4E02pjM0oHxiiaDGQBl+nBGQcwwiDIb5SG8XHjqrOYTbdrzODXSaa9EJZjDP9HbJqLWqEI3bqOKp9KE5S209M0dtPeNTG+p4zbA3YCOCOKy/hcREKIGYiId3/N0WHloBDx6ttTefxOP1Kf8nQGK42kbiKovELZLEjCzGSpWvZhfAOKBaBABKjuu5frnTMcV8K1Q2S1UYhLx8V5WXy4roC7AWgLDc+0meSjtUTFQOWaLy3f8fUWkJxnBHQzXfqIl1zNYUqqVErIY4QKzt8N+6KIML3Cetlyy8jfcEBkVsv7RgykjNw2ZsVh9n3IgV99BQLXOnnICSF7vlxXYUktxOelCRSmHQfjduQB3qixgNNtVmu0ZG64ASiWgk6ioxXzPCHc0ksvsiSmWgCpLnK13sNb0PZXatkNllKvu51JTU0py2TV9KtAOGpRslzc8V6J8lJU6OaE/zdz88opvR/9gjOOa0OvbE6BG9H4D0p9VtpJIF0+JrTKQmWJ0fL445FSlEoh/u3Q33Clqk+faaY/rIuawpbYhp48Rf44ly8Vwl2QOzK94yjk8TW/mPoeyKhir+m3sJER6SUAYfYgMS7BwmGCiASeDDuUw3mya/5CMp6RRGdYtO3vLiykJMJzLH3vxEqH0X0VJBGxm0MET40cWGuu9FdGy6jyD1SZJl7ZI9zeuyuEgkbiVoDCU85jTdYiEh3+HKs/5wRB+ZxQJpOhKyE+xrNoLRSoH8MEy3BNOGJMaDMz+CtcR9uWzZhvGixWDbPUKwLTQnGpA7FBFPSX9IvOAFeGwra1qsrBlpsVbaC+hLXqgKEb/MVnnAY4nl1YZYLlVXoP+djBbyueW4mg9USD6b3pykG+a14c05bmj0CblPpyUwVJPvaRdmazTle0yMjMq1JDzNZnZNdN3lj1hNvMgazpuxg3zJnwjFf9ko+HWQT7QZEtZjTuMLYs4W4DAPSiIesZURKOUjTSImPjBoW1YxwMXctqD1+DXjed52zF+3g67AXTcduBMnc+C+QcBdNg24RU3k+mnCLQzq/Itsnq6eoiu0oH/t81PRn30s/Rtgt7pN78bzgv5ZOKx4PNROEDB0DYb+TCnAw5K+6A7EXsDXEuI/6u6SgsBlLXAEtfThSNzKaceCnhBmA/BzOKE2Gd2Mj2ryYQA3/8M2gV5rpVafBPixTcJBmfDaExhy2CuWk4nrwwCt94WJW45RXgWeiEgw2OVlZJdNApqWCH/4BWNgFdMZmMU0K/8oRgZY9xHTeMWo3F9tVEuEAPZhXNlsMaoZGOJquJTUZ46USveVMbYAlrta+8FjkmjPnTDGNvNLEe2WD4Suf4o2QFqA
*/