
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
kJ3oFKOaNej2IE22Rf3lvCy87UhMm0kUnPAvxYy5K/RdBV+tv1/TF/xUElNf6I4CpH8v9uhKnoXivVrVt0hXepDa8+2FfZTpHDGz/W4Qpm3imIypAtePG8wM7wPV5Kmscv3sWVSEtS6FSbSlUdd6gGpY7+n6i49uvO6AKGk5Z7C6EIXmkmkrifDE1+UQGmr/RqTJsRRSH/7wbrcBUgUTxbRjVLnWYNQ6PKEv/8GOMJOrGb3eGBpaaiIcsRy6q0A0KKKPaDXOBALRlYdIttNJufBfIJn6brU4oonCdPm1D+S5WZitJLYQm3h4H0SmJHZtpS+mbRgiCz3CxlOnoexr+hiclVqukLl8zErd6id7Uvendy+/dK4k3GHKx57poUCQU6G2eQby4JRqsyZwyxnRQ8cWWG2bAVkxDgjjAo46g9gpQGzLxYVtR9Uv8tUthTwo5dAVS61q7rfYudEAhvVg1V/02JWN2UROAUE/RaE+WUnTBYLkMhE1zuNCT4gskxmfDUa41HECRmIPbtWL0GUiCTpY5o9QvTFU/XNi/y3SHvVkl+AOu3kLoVcc+z9gyuDagIRDlCIs+VDt1D5d+iXirYubhBXR5xuV260x8yJi5BHobJqZeGqCShDq/8lFs/1C4NP7Huj0psK2Mw3V/XiqVpSSWyFJ46wP1UB2jdIvCADK644YK2fZmWGOB5NgagjF+C0VOuW+wGnFlSGHokvNBUBNJkqn0uuXjmPipTfcxdqVRDF36a82x9349ygKgiJgN4u/KadtND/OTYnWrhS/2uqvFjxqh4DBtrDQ6ge6suHz5SARXAqNS3mjZO3u+viz9g8q7+z6Z+cbVHqtpv2kuTfPOMbxfuEWPhgc5NntR2Xav6NW7vfl+ukfz73OeQ6djUtKwFws3eYXxvsDA+M183vAY8Try855YtHErinkeMChDZsS07NPpO8FMqpq3hWCrFGEsqvwgPr3n2pu9EbUh+q2zwYK1L0+aoMUwE4/8M+AwoyvlWy7KCsK0LHzFW5wO9j9ZqPcHhyjVNgRU9m2Ih5+cisOrwepapjnN41+v41K7o2xY7/6AvgHC8Z133jf8Ate499MGBqKnhocObsjYnTn9+IQ83aVwHr2sxQLVwIIx00emZxr62eHXb2ZVdpuRAB0Y54FExACF+C4NPKxNJKxW1HocSj5gKOZHqo7ZIIDVGVuTXHUXTRS1LsXqGxmbFkUe3MimfLZL9zlFrhwx3VZ4qt4z2eQ21VUO9QKXBK98tUYiOIhFV8+kXHM66t9W10h9hb5va3XC7mtwGiS6v+NypqB9WxpZKn01mtKntqY0D4OMOasmdD/h5ZrK954y4Ceb6bvtukEryvHErzp4KKB+yrN/zIjuE6NPNLM0SHaa/VXsl3fD5mXBtoyrU1kZ8CvnGzMaaYNAhqe1Ji5Bf/sbhvSslEBQuc7m+P1Py0eeE52HHnAndB67IaFuWkrYhHNZlHz3BXpC9t0JrVshhrX3sbxdr+060XNND9xmtYVh178P43DOO9mlNOiJzBHG+PjUxUJRpjSVlBoj5ikWWF19ezbWvUXWzVdW7V87Y6mh1LocStvs1KR6iTHRyhC3wQS/d6ODP/KpJMgI0Kd08dm2Tq6O7Vwv5lsbdSvZe+cYr+Dv3Tqu9ZHlgg9QSa7VR9s/UR40WcAmp2drWv9Hn+ld6u7VvYJb+fRehGqzvFTo+u0DZs2LFxfEaREANvDu1qwsImYTznQn/LXp7KO5dMmjJe7CjDkYWNgRMl25ORcTxBPVu53mA5wIUnbYDuZYP7rBefb+u0z3gfpoQra95NeuG1HwWdHA8Y/afTikAOaBcyDTfXWfcBBMW3TPm3bPVOtymeyO56Pxwdsc6wnw2vWv1ZxZlnPEuhs0pP1GJ9Qq4wqXREjhdz6Q/bv/Ixs3cZYc6MxGDPycUy0sjPOkF2XgGarO/kr57zYhKYMJ+cu/UErZPh3mar8TexL5M1cRhYUQHCcY+Em2viwirO+x0HHwoC66TYNeKhFSiWHQI6gVumj9X2wtcXHSFGJQV72WB7orcki3MD61xmjWi7TLoWWrk/LchhFfRgD6WGimmGwBo9uVTbVIjYFfupZdL3ifvLzN79drhuOlZTmj7wfQb59Ih9JOmh3Umf0Ku9DliltN8q2fj0Gh9q5ZbuhdrfvY2chrcfhZx6zBXduwV2TteH5Cx+7D0S9g7bwLIcIGDG1644VH2gmqIQzPClFQwaj0ruN0WB+XSo4TTFmcxaGPR7vm/Kmu1exI7+OBTBafC7OoamHk26QS5NouilV53u8TUFcP/8VZIQNIy5OJAZ7USwEFpKudYNf66ZYTjj/UGAJeyNhpv37KjYGYbKA3CfvQkkof6r9Qzxg7V2WIzvlm8C7ROzQsazA9/P9ZR4BM9rgoN+FxNeWR+cpkxgNelSHSjcraFW6x++Zr0IPcOEURsVoWYoInuy+qhG+OQHeYsfj3z3j2jA6iNEIyJSC5v+ZoXIehz8JVnTOyrWWYq7G6rof8o+Rqhd6iQp2x55VOmVfNEZ1jdL6PtIyfJasBeifg0KlNuK6squqkvIiribemmmhrsHSnMGg/nq0z1nYOBzA46VGEatSyZgLI/rCEBAf9PB12zA+4ZR1us6Cvc0JBllabsMmNhDUjq7aWG6NNP3Fsiq0gmtyZ1gHmWu7VswIMAOJ7SDZ+6C0ugFz06M10aYGVGQWxUX9Wn/bvw94z7OttkPHv5DQdVHzmSI/W/8QcmdNEUybmi7WCXbiYE21gVlOMRpig4tKExKN6mwsuYkqmm/0y7/beqdphr+tLjJW4IeUrcfoNIiRtjBLzyWmO2WDRGLqFEhNaDC5xOeVLSZwGPCRmjKxuDIkiYXzewjI8Qvn0+8quoPvwuqPzZIf+HbWM5I8N+9hbHGFI4IhDP0DBIXuUneiSSIoyRgDNwy0SWqBFu4gIl0myjZcOK8QUp1Hsj+1QcHHWxNvfREad1tRWMHgy3D3J/pEaUh0gElM87RZhbz09Opbxm6usxp+2FulOh8UuyjURM7fRXmepnV23JA0RS91gV0eOFVBEU0Oe+N/T11uSJYYWfUc5J75ziLhNHx+GyOnGAkTf/VCmccw6PvE1npP36Kb7XSvX8ltP+/49r7+YCI5KD/JJ5jJwHmDRYCSh4WdtyQ7/ZjsVnywQSWw7Oqt974dXP6DyuUyye5ZNo3JsLj0RphuY2C6kQH+mBwi34VBFKfLxpP+3vHObGez9prcdHu4SVXDy1udHG7lVxyFFCZozg9OLNviGUGZdXkivE6eskXkb5sULiXhwz/q7/8SkWRaHMczPQP/XIKTgO/A9AnwmQYStYykdU678BBOx5/Yns8Xs0KpUKP5Ncv7v1E2RlyYyvY5MPXFex5B5LeNC42seQe1FK0RV77io+Dpeb4ECG+/Kmkywufr6AOF7vE+R9e8K43XWf8MBUpo8nBS/dSGtlpa8/5tXInuSjWkgbJDH4mTnnMJFLhRARsnjoDS1n2A4PCwUshJxZUcfuDP8W2sjTv03akumAnMrTLni2efjUlF7qT756DQ4VczFyVzYr+efOVk/0BxJ7WLObl8htq3Ec2qG3j42mZLIMBAl3NqddjipdBc/j43aGX5LOAtvTS+oQ+mfdxtL97LfTnez7OoKwyusvfHLOCNAuHftF5+YILWJlJsHSk8gqNnlp1arMMGSIRn2PGUzsm8BzOz3Hv/xwFZm0usxROl+gyb2p/hN6ytq4ZxHK3O+grcnl8Qvm5UNcqWKTu/hcJL/VldDlM8U+ymG3R9mg1Df39mtps3wPSxNf0THNIxdlw2YdzmxzY/1YhtifG72yhdWcasShyIhDMlUhNGhB8kpwtPxFKp0BJXK99aIqv8tr1IRpcbXfJv6uKdz7mMe3Hymny3isdHz7dNISYfgWP3Gzwt66hS5I53hlbd904T1CyC2KBcjOknrMKq7holVT8565TXae/b8eoLxyEuhJkVRZ4CiUUkPFQDT4ZxYl7Sll9wDWHG33+BfUP86RK5TEnfy1edWX107MKntdvMUDJRSUv4GZA+ziA6YciRRPbCj1eAZTAVVAGc0J1yVfKPPFpD40smUpFNa8Uw415L8wMF/HlcuMFce50iHvkcTftGf91beip5CoqijlGCFHa/QD5GQjcoUAxlSFhXfPaWVBs+W7pBm3bSWqfk6+xsDMrT9qSk1n8h/7uaaOscsVsU1eKKGEXTOe+Q/i0ovxc+P0YpXcNzYQq6CB+Lvmu8e62Oq8uPHn7DgjSbjToDiUw+qutQY8qt8i12QD8oLjN+PD6r9vR9imOcUsWQpncIf4YjFxt0eb+4N500o+2LENeGOiNZR/eY6liloU2zOJV8Jgf6da/9F2jPC7j0E2JStqqrtIsBJracI1+SMwRocFjwVgndSp1VlJH6a/g9xPVLtzCUK1KOitB88Gqbgq32TczpGEpC9+mqBAmxvzfDQAX+UyKbhSFDq1DR3hTADp3cX2fjVs2rxQVHOdGHjgyRGdip6Da4/zfwMHT76lt1fZp0hFicYbWuVDaJ+TeRrVGErn2WmLjDw/WwoLf5TvBvGks/X7WPjo9As9frXHl9Pwi/9ZdewahrJDrm2LEC5BDUKIhdVCExC+gzgiRGzr59XMyCIsihHHKUZqkihGUl9GFlmZYoAWsXSwE5AxmidH8rJATSe+AwmaBqvKcR/v5e+tRoYGkFi7nqVqjbhztemysB7wE/GL8/45qwrOlzQRbIfqscEVaYBmAvqku079HgCX+gLL2DVtukqLwCr3SK0tCOw2sy2IiS1q68Iq90yjxAkD1MKb0z+6tJ0340cBTC9MtFcfiencS2HoNKNS7/B/K7/CLPfb+ukEeT2o87gsf9T0GAt5+VuN6j7muCI87AlupDNvuOCMcRfjCDtuMYNXLirMdiJJmiZvVaImyUYTGm7ssE8ftnq5jKAAAs/9OVUP1mGcvRbTIPaxv0ClsCLveSKHKiqSDA/h3Et/3zI7/kCaB29Ilb8tYrPw8SbwGFV36KBH2ATK+DPnHvkjHBwoQon3Of24D0H5dTWRBcZwPYSb8fEgubUtRzDatPHX6vre5pWGubWG+/nQdN49wnt7F5Md8femesH1kKI9Kr+kR6CqcwOG+BNIVrQcUK73Hux7qV+ELWC9pghVEPca1L2zGFxn+iglpIIGkLc0b0tmPEHTssCs6Dd2wO6+H5HWEfbUS0uoG457PYeglq8bhUAbSXCnrniB6CckqP+SM/TH3Idi8KhW44XOWzIImmbHa8Z3Fj8h7JllU+tOir72QiBB3BLTleFXjquu7OiUXQxEFdd+MjyH5hs11p2mGv14iFlRW//aVWXf6l8vO8MaQiMtH9FY2sQIjdFcyqLfxI+P5Zl03OldRdeFovro0ilMf/2DPLFU2y7X+/LF6yFOHUMOITsq0V2EBan86oUl0y0wdjGbN44iOvG7u6gSM7SuMbyidXk7ngVXJRKNmwzSS3fG5byfXg59uxXfvxkdf62kJCvjkHtCX1vwlOvLp4sf02Q4ShRnz1bxAfRSA3NNeoiMixUEn+bdozLFvjm7ET/uxfQvXciw2mEu3NLEF46yeTXxYhkQ2lb0jiOLGDVPTmTymzTPMFMCEK8/Z0iafyeSW3EH0GvEk9czewqT7wF3IMKHrdULuDXJcFc4G/EpaaQ2Hsd0On1oLNoSepYHqZTtOuwvgJrrTT611i7powy0z3SZGbj8nUZ90ky+fMNWUXQ1zoxpOPHHCI/L4/8zKHX4nDaBOdsbOh2RodaBvWv/oGrT4m1xG+LvRMGhI+PWVE+NocPImDs/ur54pOSQWMV55xce0hcM/o7I7Ciwl8Gql1NgvHTXvplIZDxwbyhs9IG7+On+7TYGuuC2IXNQpn3oWeVur9ydAKOzYKyqt4iiDul228h1oTVAbideAUvLt5VX+ruPfDnF76u8FMZ+zmSBKy/6d2aBWzcUBsyeDeYnGgCE8T6T5TZxL9bA+cCiwj0q3fQhXjz4ug5ZsADfnPBKvDiRs4wRR71bnASiA4BiUucQpQfmzKgQ3NqdKpRy6Hr78uu4V3V080z9KQAt2jaJE+bYTWCYUXjHRgGLGhI6RovkGHQ8c1z2MRllalgqFh3Bm9M2uGUcBiHyXhzlg0alGAYIKtoziYa8lO8atc5mI76vf0qYDBQY9c5LMuSDuD71xrNeyU2sk4VqunvHgEwyPPuP6QiFkMqa6MOkYI+UynM2qap4mFkG7rIt5EN2aVdtEaXMZVvjJVejSaUx1vO7iePfdlsiplrVkw8Bemv1W7G4eFPekTf6XhkoXenBgS3hwO4zghPvmI6EdsvQjLv1GexF1znMjj+mZP9CBBFfAATReNDnMpacj3A38nHmK67JP0FdUkEO6/RBLsa9C24sTtTqFbDpIq+LuNcXj8EVH6pLv/BPN9+q1cbOx6Qv+W432YwyDHfmZO/3v5x9U36CadbImzKCAzYa4n/SO8xoGqcBxkB1not6CPAqPoIimVOw2XVCzs06jLkRCMSi6cYQrlg34OuhBJ3ALmJe3VLgNp+YqfAzt1L2D0HE1qxVTP1lFXqPvgtoI+e3OqusQBcBr14rPvt+hYLpQ31OJeTY2yDHOkeuypTH8p6IRxnr4lBqrb9nM+5r5JDNY6SopEtDiqXeJj61KLa238pcj3fWidqDPfgvYOmEKhSZDMugcaRKo/Fv0ia6FNdr+gIZbnzVRLlnJOxdJ+omX5lJM5rb35e5rruBR5xPYMfySAmcP0d1GnxxS/TnSxMYZ1LVJmH0F/PbjjR7JbOFZtfzOtVeO8g8Se74KSOwNGn7LzMrHBZrwq6aEuv1CxHfh7uLbMekNDmPbwpivk01D2Uk4/M0M1egOSQs7kNtv4DludEkNKViUcLJ6tPtsptNKuiRiz8I2CxI/8Kw6KD3QV9Av+kfJVgXAaFBRVWOp/12pX0BYMkqrVaVPczuwRV9BZS0GbmyWom5Nw/n/kCMh0EtrEbfljZvPXX/EtyuCm8Zh+qEjn81Tki0TIbqU614pE9b6pkORD1DVEWDnc+eeq2vXRXdKbcLZ4EqTm3v2YmuuZ49I9mJE91vBWNrHDMS0H+I4NsZjXmXPQQDeZytQCERUwEvcXR1XVvfC5ft4TExETXVpy0i+N6mOuKhTDQjdaLeRZwKZJqsAQY24DDITyJX/3oDAnL1deOpl3JhPpddDcmPq9WPgUHri978pwrjscASGIzN0SzRv6SbGlyGd61G20TbY0CDBMta52CgYtoIiX7JwL8HntnPuUSLttnMUfQ6/q1psxhwiOynfROIguOTjxybIxMrlJ6y/BH6WP/6EgJulNP05mQxLv0IdIo4XcMBAzj8qwg0siRhJJnUhpBJdrgcfX6mvsShlgiP7ZVRcbCyftlOXJSTuUZKbSrN8wq5OwO5gz3ygNdK7UnfHf/OeU0zers4QVdfqad51lsh1nHsV5+qpdGbxWtOcgZaRy8zP6I0iK++4kSV3WQ1oTLxTGQH7N/ffE7Ixk8wezHx7yOCVMOJid/kAZPZhG0fjEAkp6Fs/qn+tDRd8emELnOzrLzh9XljNDMhdqVHmYshbQblReAnI6
*/