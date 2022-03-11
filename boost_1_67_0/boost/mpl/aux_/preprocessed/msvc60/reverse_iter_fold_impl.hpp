
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

    /// ETI workaround
    template<> struct result_< int,int,int,int,int >
    {
        typedef int state;
        typedef int iterator;
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

    /// ETI workaround
    template<> struct result_< int,int,int,int,int >
    {
        typedef int state;
        typedef int iterator;
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

    /// ETI workaround
    template<> struct result_< int,int,int,int,int >
    {
        typedef int state;
        typedef int iterator;
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

    /// ETI workaround
    template<> struct result_< int,int,int,int,int >
    {
        typedef int state;
        typedef int iterator;
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

    /// ETI workaround
    template<> struct result_< int,int,int,int,int >
    {
        typedef int state;
        typedef int iterator;
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

    /// ETI workaround
    template<> struct result_< int,int,int,int,int >
    {
        typedef int state;
        typedef int iterator;
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
Cl2i3qZ4phzyz6nOH57C5HyBGCQfiz4xvrUZYfNmri/HonlagXrfYHjDyxW1Yv6m7qrDiBQ/vawC4xtu6Hqa14G1VIvmHT9a7sFw0GHij9H/Nrcu0f88qYA/yoq/5sJZSCoQh4QVkxn7j3lYCgOYKQJwbg8CjiAiqK4pQJZJ1ftGllGuUNIKSQt+7IgxVxaOsRtTsrdOJsQJrR++xlZSB46m5eC7U3U2QNZa+jBOaaNqOG6r9q8Y67m0NbshCD7xxzqv9O+7FIKU1KEaoSmYgnHmpU2KYrOOYLwX+BkAgd6afuLl+omAmXn0QdvtF4Wg1xp8j4QPLYrAql8dPb+JywrCxcOOPs7EJcAJDReTPWuqv8OIv7z6z4EYvgewjcdPgJtdEDqYyNMPOz0UbX0sWVth+p/2YQxFF3nHXrjLHLTvACF0t9S3AHydNYyjlAu5onr5htG0erJhuY6BP4RoKwp9ApFNZbbtAjEWKJooEHttlZLQIo78y1Hb8+wmradvYrHGx325cBf3/sCeNmfhcxfe4anksyfBvpc0IYnHCPOJLVSRHuDQh+iLFWScFUWkEeY4yBf5z9uB/pB6UpYr84uqk6hKLYylQ57OLLwC2EtBwl/wYf1LC4ypVR5HL3dC+63Yk3pfzb4dnG63kTHJ0yKCu0k/5NHvGrlq3httLPnD6fh320XXCs/qllSZRIszysd/IS/S0CgW/EttJnUn6Zl+f9WCLlw6KkXr05Ys2CGTPq+bNvOPbWIUgUhPQKZ7949tn1hTCJbCyt+CSOjhbVLz99zYpRhzH3XjOmvgP5cFlpSQ51FhX3CbsDNUkKJRHDgAckuzI5qIlX1fYX6T8ZuDwJ8lrOAb9CXwWPYm/X6kTmbFtCYcN/bgq+xglI/5qQtPA8xgJt2tZ24uhRM1VuAUuZoldf2ulOGZzZJBRFaDefUz72lhBZsKDnNcwTDD6RTux1tTg+di4p8NFmGIKb7RiXYkZJwntjxRW9hdyObdiOjbongLloaThcLj4jKuFXcckX36ve9eVtFsWIEIxhl4Xa07J/pCf/KWFyHW8oUk9HzdaT9a3t/1P1aA8jVyV8xzeQ/+jfLgi39Sd1zsLy+HCcLA+d8duPfZT1kbV/a/rG4OtYXk38RT4Sp54fD+mSv3WpU/Ncqgvudtz878pWp85/N8EjjZLgD41pWIpkec+uFVEXihsV6easyIBjf3IB7nP/55u0HKCYzJD2z/iTFfZ01tgnqPjhNwgFaay0rJBn17K1z2PMma9cEb46vOrQjk/JlH7Cx/GjBXFvr4IrxEoYF1njt23bJw53u66nuq27MUn8Y17VD5RKjMp9aGfgcJATA+G48Xvbfc7F/YDT4Hz3iOQlO84aFdiqUxBv5trS2vFc6Yf7BgOmcIZfOLyeVB9McPnqVoXHs/o27VS0O0GQu6OnXiiBiNadD/j5dG/0gf/eMd9vlrqDGIpdc4avJUWbiM8GAw+Bh6x7CcCWj/qJgnWi34DpRku/llEDQgOrt/biZGBeNLMYfpR4chCn0fk2v950yRTmQktgRX6OQ5fsLsKzOs0nkVH2S3eaMukmuMc5VSeQJeNy+VwMJnwWvytpoAE4/6N8KE6mnjBjPKDD3lLPXYnWZZqlBvUnbIY+5jt2V7U6wQfdHVieP4E2Cc81bYMcIczx+H8/COeiYpGzs5+8OSbt1k4Mz3R+odqI/tzD4HMH2fD/jAsC0piyiEPACFa46AaAw45HELkL8M4hgyHUmVRXOndgN7kzWVy52mbSeLkBaSUMaNl6RBUuXyWGyciLFiuLInXcoOjCQjdMt31qiHx6JnBo/S0gopi/30jYjfgED/OEgyA5hqL9/7NV6dBLIuqsRxmXXPv5kIsUrPg1gRIETqDQGsMvZE8/fvRkPYFFLfeQvkYZftiQIhD3WODeTzQT5XNxgvr7EfChN+oNsrfNkun9KVkRuGJZUQYrAVwQ0MAR6jLyz9O8kWxK5Np06K5EC3VU+O/H5ZqZtVxalJv9qYWHZAtlW08YzpLZak4kC8NVgSmW+KffWKOrGxO6Nt3xO5hg2qFCXl48JfVDB2yH+/ZB2KKQkVUWlzTWqC92/GU6oBMv/0L30hnX+/q7h+M9UHiL0d/HZHdVvlWgd3b+4qR/2c5P1XvhZki3iUs33kjzvU9o3C8ztS7kUx0AhZv5pE9uuoUM830EnyO5qdc3H4keHEE9azkEtfrvBg1M0tenVv77JO+eXecS2FJxrmRKEaf0w1uDg0UToBr4jwq+kJLzNvgsjxOn+543Hq0soAAiz90yKVrBDcaa/CozWcUJqRggT4JAE2yU7ORTOcffYW1DqoVLmYQb49fnQuoHbXS/WmTFL46GHxewrzbAJhUPa7vzX9thPPHVICnxRImZtOIwsx3NaEsLdJCl0fY0oHI/4BFKxZQ0sxwP8+8kTKIXr3VcOxsZZDsjdpWDGKQbHedlwX58TTowKG16eQY9C7aWBCmd230KV48eXJ8G3uUY7vTBWtYpi7rOztau6rl5ZQySla4BZHlL482J11kFDAVwhtMvs8A+J1cgcB3fX4jKlNqKcv23c2TQH0hU8ZVqOFiJJVnH4K3xpf1kfKpJ896ZXbJsDZ6qCLSyhaqwSq/aU3DDqlmseTD8VupfImRHstvyx7kGxZyrM7f3S/yc/EKL+sQEpRBwP8hHN21HMOnEOKNc+C8YLrTpiQSE92aYEi2fOP05VvsifrqMXc2F14o+mONr6vEcrDvvWxN7MKEhsBq68J2dJXTv38wnUjTXzT3uSjHBCC+tw+MF/sJifagv8c5TTixEfJ/5LEErA6P1H3zZAlShV7JAF4frJJKKsObUsut7i6euTEH4uac5Isc+/vap2pdfqsJ+fRgnHvVZHp6ih6ltUYo1WVo3v0dPlonPMyzhFxUVRVL/aCd5itHGhE12NJcgvYrL+nG4P0TNsBM3+wcU4ptwQPuvxEl0apM3UuuLO2/6jYHfg5dvZt6rwsPBsZzyJLcPBk/tmG88K7+fKwplNYSFBad2oEejIA58W4Te/Q7UP2ZuYHLBDp+alVZxhwz1d0AEQMHDJOhCwji6qNlL8Y8/bDwYDxmd8T8PYQBMfNMGhoQIMg0wPdvyIlRw/dh3rmoxHDvvQs3GRFkTLCN3+sT/DHQcldWyHA3VUf/s1f/B1K7JtvobpkGcvrB282Bg07JLNzD1HRBh/dxPRvEHchdEGNmx5/acHuR5xtyBMS1woUJH36AOL6rvsDY/HZgnWu5Z9MDEwNYvzLLvsg3cvdz797XyooZmnv9Z7X6EMVBdbcC7tmPGjFa5HM9WhVmIIkePQPjYEq0/sp82d4wqk7Xm40F69XXGc92d96gSYogAfxhB/BtKZNZ3Uj4ONF/4DnwKLqigK4YRdsDB4XE073JpG85Wa8w9cB6Zvw8GAetGYvHt3j1SoazVBdvocqTaGcVzs4jOQdUR2k5N5e6HCiNX6ezFuQT/a3WXU83TqVtpDlIP01yIYFFuCcB4R1YoXYDVqjJH5i0hkKkbpShJ5VjwTfiUqfoXxxpv9fq3m3YYCO5nCnjNR23p8/17K2toZqXNxCtomFakXU1EXUZlZ6TA7weHg4d5zwL9hSi9T7qnGOSNEz23R511EyP88SVqPciopqiXK/P+HSjV78+eO86mQ1rcdpXzPd6Jd//N5ivQLuuZoStF+p1r3qplADO2GWhV5vkjUKN3OVszoNulCZHApOHasvd2jD+aW3BXazrHXg3uoR2WX7fCMsvxThv/oSZ0bQlOkxrvTgpc/TxGsH/lsmg+NGS2xYI6XttE0FMOZKRLJX1g+k9O4mOjD9Z7QZ1dBT8L3a5LilhDWiK1oNQuFYgyP+oP2jmfVZIfIk4eyI+wy5LWLV33mnJ3cV5tSHty6sb6CMNTp2rJOFhzqvCWj7I1wiSO2L82Vq6wU9QFI8i9T4mIZVFueeok5no+q/jSdt8ZpZfOt50ni+6D3hPRazWW0auXF/mQzFK6tGVV8B9RzNsEyE8xLwySXd/eM7Tx7AJN40zA1qH6LcDWnVrY6fCc9OPN5mcUn7JUo/kxR7PKSr9l0l5ys/7LBuo10BnwI+Oq71eHXwheLe1nPcd/2dDZsE7xP8/85DuTIm8J/KHSnyHerpX28QBxk176xyOIPBkdwBwT8g+AAjBRXBh95gfcb2F8OhJ4iWI6izu6sTnM/IsfWbWywCVtisyguAdit11bkyqA2+qxd4j2BjlHLt9jKsWpbJFWtDcRdxjP0ncNJ4eYotfjx36p9KnWmjzIvpDhbIpTj5988Br5pQeaVTiOGI6iP55T1gdOHrTI1fFzcvTXA4WsA7eUye3qky84X/EgSM/Z+fZIO5c1itc5wl8jHi7fM5DeYlHyAY7BatGRh69eMtj4IC+9JP6W4Db2pb2TvWVxHvsOquUbRF/rBFdmmCSTMPferczKi4NRK+Oy1MF8wF2Kgtxp+2Z8w4H/SZDs3yC90IQeS8iki10ypEQ0g/D8w2aUGwBWz8Ys8nkdPqOYuWO3T4V/7qrOZD4hM74Re++qf737ereuJUL4w6VZ+quAqhim7AETeTE9Ln9BhQt/Kne/aaOJX3yM8z6XXPN5U3tcugSvxffsNmGTg/OAtSrtWpyewxJ6/ddbMAX+OuxfyhzFt8dxTP701lNABmu4J8iFDJpPlFx1zL1EEsfD+sg1cBdH4fxy51kPv7V+XRw/KejKWciRGtJ21Ld0yluJq6UdQqPaTvhRAJcLTikbdQQx5BYF1tRFdMCop4JupEBO8pmBUUOWutUf/sHw4fPXvcZ3Lzcv93lvvBzn/3z8kyofNSvaPxRMgxgp5IyqY0gmgnJPX1zjhgCJzyiPXWVBW/lp/i2yC6yTQELtEmZME6LhCNPZkN7UDwu1B695ujhupU+ZZc5dAzVTpI5xImkoykuW9ZStDl1vzWwH4JWhB5AEi8sTaD1J2A6lk3bxQMo3j+EGv96isv4hv0XURYiGrr0/Muep28lct/TDwDxKTdWtaLH+0U475XBX/U0b6f/CyprUbwgR+LsCbZg9Ydbo+E7ka63myKfQvTc6OGvXq9hWk8gLVJrHxAQYyj+KU5nbp3CnhvCjbaP7QozDHz4aruUm18up5BXdsxGH4yTvsUmr51Ux7G4fqQtC87kaBt2b1l8NuRhoxtXRHLA8YsTsUT+X+nFgGCjpZ10u5uQ2zBxhsLeM87qOzNJTIBVqycw6f+V6oZccoKsqI06mCjKt6AvMx9y/QkiAgVuenhcvFDRRNbK3Kcs+NioVVHofZDtTb4ZJJzWt4Y3Ko6xzbcbeItIkRisga1BY4tOz6lu+/ZeyvC7H6vFQfH/gT+zLFE1HdSctr6MTCBHkX8C9J6S48hoW5rc2YWTk4xG2/A751QKnuHZ9bG/19jvkpr/9aUW6ziUO9D/ai4MTanxYdc6Jz0/4bPe0GkD0JMzioWhE8yAOSpx7Sh+WQ/26NpIxQEG26gJyx2BfPBe8oV6Bp0PYeAfEgukSnNKQpmLfNrd+bXY8DAn+hHMJcwisOdMDu728C3z3s8NCBGz08nSWkUybJbptL++CHhSj6YjLXBFEb8o0VK11nvXiWUqaTnS0eh0PU3iXpj48IIEQn+MYVZEr3qm16EU7jfZ5b/G30J7qJBXUu01720KXVfDqX7SLYnoN4pshjdQL84H+8U9NPsdBjO8OxfzDpsvuFCMqqpzj387kSF2dZWUfwQQgW6VWrxxzXTDb41jJGpg9QmirzffY2uB9qP37NZeOsWd6EgYOILTX0TyE2jBWT+dgtYDqQ6qcOFEArfFshADMpP4/0I0xlLIzRROsoJnr0dU8426F1GV2Zclb1duZUk9f6PTq8KioMJtsbdNUCwBHcS3BYJFiBYcHd310WCQ3B3d7egC8Gd4O7uuuju3u/W/V//qumZ6vMwVdPVZ/o8nF1Y27SaURKTy0zjcV2szyXnXgYpbHC4m+0f1xG3dReaw3bv75F1roBenpXOUjsRuwKYTthX5huRpqU9vxnvOWR0VtIdCh6mpfs7dxJKcWbHc0kAc6oaCXumEsGNUVO4b16qpKkoui5zWQw3/DuWO8fScQFuhxN7fHqzXZkz1bdXA62R5bBHkH/ZrsEWIhZ5/04279Jxl8NQV8tdnEAHwdqAJ8bIBi/JmyC1CfsfDvtC/7Cwda0+gYZudxGfltTL2VEFr+7aatejhuSgStYXDG6quBmJ/fZakzeL5tyUVaShnPvy6beXgFx+O6aPxoHvBFhzs9CjxRqILsGtvZueanHJWBrq6x8wRkDsd6e8Et4tS9aL0mKjPalbIm3iII2Ixb8+uuzolIGGbfVoSE0Yo/Wame+IKOoB6yYXVsctjTOMM9tPltXvzDSO8JJhrhm01DEmi7gW+cgUms4SmjV9TWFX2AYW4OtKmsXDIc1o2ayaxFiFPsM/f7umpFsfcTZJ44Y9VMghxhYU22+K5F8wDIz3bx56nNrGB5LtWbu6IVE88fICFMnSNv6KR2UmeYV+PaVXY/ynZIUiCkzC2Nlfk27zlmC5omtnoACdcze88/vEw+4Z1LSByQWt0/ukdPc3C/LqHWORd6Po7kEXHfqUoRtUG1+5kG4PQ0laIt3h0MR96khuy6XMgY8lTWQut9IckcfSIjp45jCM5MCC6Tdd01SZWpX9Tmz9z0Is+oz1eO+h3aLuD70B/nJdTrA/sj6MlpNJ7XUVbQcYetOEd47doPTcjvbNt6mdobFUY0Gy1sTLoTK5/i9iKNnpu3YoZly0SlPxZHTdmH9vOT6sn1d9cstw7gCp4OCPh4a5csk5sQ5f8SlubYaPda1z+XjFHI2RvjV0tTrJkMZe6seXuvbjlO59bU/+tBIzcXi8SLfdnaflVMWtUVb4RqOewPb/Fu5sK6z2C/KXzEDdcYtXR+bYHpr5PNLH40yGWXLXhgyrlWiMQV+CUwuN6JukctbpiXLDkPSZkewX20uLvKCqz3r8SmV6tOraVtJlymmV4N4tcHyHrjaPej/LaiaZmQVzUjtSRJw1wJJse0ZUSG+2PCn9efmHibBC6omAc8a+isAzu3rPYh7pacSdbggvhL2AEwFS+VMGxJ4nOw8HuTEvhsBMtT8G7cT9nIBA6aJ66cdOYFi+sqRhgb5VQ9DO6F+RfpoCSUKkdmBYASXWWl5lU4BzXa8bYRFiPHCJRYiLzxF+JwXuRz5n6sNp3MHMDDfsNYfZ9l1N6DepVSXvrlhfpsM9UtuhVjQFgxyD/spHUDKCB2aWzp8FvUCRap9GLHcoSP2EyoDlrV4XWVQ5x2VtT46Y3w7ueTB4ZkZh5d2WzmjS9K6HmHHcizGdUyLtWpk7y9/PTPEuoBtNiO9mu/vXmJaUmiXaE67fAkGQLXxW+2AJgE1S7Hwmghbk9G9ihD/zEeocpKBfcghD4Bxhx6j3S+eCkJ54qbwyROVZ4PRatKVP9n/IXe9nI5+0JamGrvq4DSqhJ/3yBxD6ETO2sQNmhtVyww4fjPc0IM0lQRZdFfoVhyAdtAlRLsPeFbyZSoQFamXkGYQsp7ndvSHlp+KM+D3jCE2RGqMe5ZGtUsSPr4sUua3VpMJ2WjMeMnNKB3oxj/4UStcmMiS1EKVah6JWQts4Wlz5Vv5inb+kWUt3GuPZJPUerpVR24PdjroYvOI5vuWWJ7lZCzrOXDhW11mtmM9wHHpBbnhYO8XM4U/lpIu6Ca2OzJ+1t2iRvx7mQacF+mkvpUexEwtRbolpl9k6BL6NWmTG7LK38GYqZGfGYpflf3I4+KQu5pnMB5rEu+Xw+llp/Ed/rSgXLqcAZl1prOBk3XJBbXSZb4dCHgGesQiWaRGtV9rLBWQiBaAL5XfNmopyNkdi3WTJ5KCaHtd6w9gPrkF9zVrYYBCcA2rFtSTr21R49R0FC9Hz9516joa+dERctxHM9CfyBVb2exNBrHEzzIUnBfZbLNexyp7zo/srIIJ//TrROwmlUR7jzm2iUdGuFzw19rvi76fPOj4cWUZ2uXKoEUlEcRz47ufiy1bB3ACMqI+DJwOoZCdSPK9bBZyIkA5zpxcNW3k7NLdvvR8RZP35O/A+cbFJv8f75Owe3+OZ4mIZKfGthQqBG2N/MlPqN+V64Ee+btfhiaaz5fAvdnwQ6w7tV+ZCftbpwyW4Dab80Dtq0ReBCKJ89vzU69xpgkqApk/vbESf2Xv8ka26jKdwWrCQB1EiKlhcpH4h71qorFRoZ2HPKEhs1qjQiyFzbzdpdhn7h7VNkCwc1DvJB3q2HqhahjZbElRmlnQQ70sIBWhGWKUbBhHTP1Nmca5ToNVrGSVtNOqIdRFGTGFTUd1oixjNA9pt9DpQiESvVJhkJo+hdIP/MttoP6K9Jin0Tt2R5f1hRkdO19lx9cgL64n6a1p0/HWkvpai6iMj0jDOC9Jcuv2tBYNGZi6WRAdI8RcZNzlThlUbLgfgBX/ddTAR3qhCmtEniFQr0bFmFGEjgaP7qOg2GJIVtlOA6R0XvpU/ZsfTsPzNEDOoyIuu/h8PhtR77IvTv33yh2fU8u78hZ5guZmx8tqABDnZF+rN5l90HkFN8xePJrthkjIq9rjzqJo90nfHCx3azNc/hUQGmVfrzzv9XAt7Sqwfs3qp7JzxnnmDt1dJ6QLhGSDtq85//T/Vdzkn+lwit5sxl2f54YhxXP99P3aA4hesvFwevbFg/3iw13ScQC8HXmsFpCgE+qCZNhKkD8piFCoKtVnR/nBssXPk1YPu+zEgOKQW1P5u8v/7TG0XIbjH6QxOaF9vLPntty4vn1H7KQjIT8Hpy9PIqHrvZI4DpX7XyBxoidSBrVj5Tsm/YrRqlHRpqpfDrn9hPqBr/yvV6RKnRih3DhZDVQ/DfFD9wK5foDyAt4sQQBPSyaNXrvYZYlpaMKWZMA1OCEdvS9gHJxiAE1LBCUh+o3h+o7ngBEzutgR1cAIEnBAHTlgFJzj7jfaAE45u2xI4L2ktwAm14IQwcIILOMHYT07WbxRQ5EA7ckH7H0QMTvD2G/0MxgP6jb64tCUkgxP4L2lPwQnHF7QDl7Sbl7RaRfa0+etSW60R9o0RdOtSw2tSvutSQitSZyNrkr/XpDzXpNLWpfYuaEMvaNtXpQKjW8J+rkuBV6WW1qUs16Q=
*/