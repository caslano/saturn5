
// Copyright Aleksey Gurtovoy 2001-2004
// Copyright David Abrahams 2001-2002
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/aux_/iter_fold_if_impl.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl { namespace aux {

template< typename Iterator, typename State >
struct iter_fold_if_null_step
{
    typedef State state;
    typedef Iterator iterator;
};

template< bool >
struct iter_fold_if_step_impl
{
    template<
          typename Iterator
        , typename State
        , typename StateOp
        , typename IteratorOp
        >
    struct result_
    {
        typedef typename apply2< StateOp,State,Iterator >::type state;
        typedef typename IteratorOp::type iterator;
    };
};

template<>
struct iter_fold_if_step_impl<false>
{
    template<
          typename Iterator
        , typename State
        , typename StateOp
        , typename IteratorOp
        >
    struct result_
    {
        typedef State state;
        typedef Iterator iterator;
    };
};

template<
      typename Iterator
    , typename State
    , typename ForwardOp
    , typename Predicate
    >
struct iter_fold_if_forward_step
{
    typedef typename apply2< Predicate,State,Iterator >::type not_last;
    typedef typename iter_fold_if_step_impl<
          BOOST_MPL_AUX_MSVC_VALUE_WKND(not_last)::value
        >::template result_< Iterator,State,ForwardOp, mpl::next<Iterator> > impl_;

    typedef typename impl_::state state;
    typedef typename impl_::iterator iterator;
};

template<
      typename Iterator
    , typename State
    , typename BackwardOp
    , typename Predicate
    >
struct iter_fold_if_backward_step
{
    typedef typename apply2< Predicate,State,Iterator >::type not_last;
    typedef typename iter_fold_if_step_impl<
          BOOST_MPL_AUX_MSVC_VALUE_WKND(not_last)::value
        >::template result_< Iterator,State,BackwardOp, identity<Iterator> > impl_;

    typedef typename impl_::state state;
    typedef typename impl_::iterator iterator;
};

template<
      typename Iterator
    , typename State
    , typename ForwardOp
    , typename ForwardPredicate
    , typename BackwardOp
    , typename BackwardPredicate
    >
struct iter_fold_if_impl
{
 private:
    typedef iter_fold_if_null_step< Iterator,State > forward_step0;
    typedef iter_fold_if_forward_step< typename forward_step0::iterator, typename forward_step0::state, ForwardOp, ForwardPredicate > forward_step1;
    typedef iter_fold_if_forward_step< typename forward_step1::iterator, typename forward_step1::state, ForwardOp, ForwardPredicate > forward_step2;
    typedef iter_fold_if_forward_step< typename forward_step2::iterator, typename forward_step2::state, ForwardOp, ForwardPredicate > forward_step3;
    typedef iter_fold_if_forward_step< typename forward_step3::iterator, typename forward_step3::state, ForwardOp, ForwardPredicate > forward_step4;
    

    typedef typename if_<
          typename forward_step4::not_last
        , iter_fold_if_impl<
              typename forward_step4::iterator
            , typename forward_step4::state
            , ForwardOp
            , ForwardPredicate
            , BackwardOp
            , BackwardPredicate
            >
        , iter_fold_if_null_step<
              typename forward_step4::iterator
            , typename forward_step4::state
            >
        >::type backward_step4;

    typedef iter_fold_if_backward_step< typename forward_step3::iterator, typename backward_step4::state, BackwardOp, BackwardPredicate > backward_step3;
    typedef iter_fold_if_backward_step< typename forward_step2::iterator, typename backward_step3::state, BackwardOp, BackwardPredicate > backward_step2;
    typedef iter_fold_if_backward_step< typename forward_step1::iterator, typename backward_step2::state, BackwardOp, BackwardPredicate > backward_step1;
    typedef iter_fold_if_backward_step< typename forward_step0::iterator, typename backward_step1::state, BackwardOp, BackwardPredicate > backward_step0;
    

 public:
    typedef typename backward_step0::state state;
    typedef typename backward_step4::iterator iterator;
};

}}}

/* iter_fold_if_impl.hpp
rk+46E5+iUXWK+feJwQwo0NMTwHjKs1ibJVLIHLpL6RCCbaaHwzYs+6+B8VZXJa+4oUEkoTdCq7s482DOPR4l4gFLYOI/kAbhBbiR3hzh+rw15iw5yFaVu8yJLf0o4XYD/gcmmEh/DuRT0GbwtRpZN/b3r0PX8mRAuFq3b42FwCUtp5zCFAWZ4dXlWhN0JkzCXDyh3dqVEOA+/LarBH76oeMibB0GyY4sFMY8n47NlQw5kDw4g9nlgyDjEBWTbRM856w/GsdwA5E4CXy1RXmTAH4roacqhMVdNssoZM9m2iuRkKgKp9w2xf7GB+CMJgMGfjlceDMwPCPo9tPgPk18k4AjkLgQJB/NZlVkcr92iGbhfFzbMtBiy1cxi1HV9rGwQTjQtzFi5ZQPk5mEbyzkXGVUw4nF1xxMI3I8MZGJK7CCQlmjQM6mFPlLaGK9GxoGLV02erJmhJml7GB3UGc33d9ahhGGxHEhrxMFc9OnulwuZBP05uiEC6OrvAFl+T3gHgcIN8U5RPoa7eqAAos9dPUV3e77XnyvyGV2utaEKtZsfVDsdvWAm4eA9GzJjb3IV8DrbXTR/ybk72AegC51B4oGhsssn/7EWa8wot/U68IwLCgvid8iD3kYboRCEiGm8wFMO5u+Sz0t+pnVArA7cP0yUp+psDzD7gqg4thG6c7gXKrq/WdXGMi4MHcglsURhT9GWArVSszHsSi4L5/6JBox4R2/gA+UUbvJIXQbEYahg5RMDl4u0ALeofND5zmkkabiVp8im0qqxgCeq+SWZ6VoiPPVXS6TKpx3FlYJJyyDwVWUAftCYu5KaNsWeB9OuQoxclCO6wShmbVV5TIC/j8NkEzTxEz9KFSu751bG8s2SEpUKwOr4icnUJwJwX9lZVwT1JlM/zfzg/Omab2FEm1PUKmh01j0PYCsxIyg8arOVNPFZ46JxpF2Sa074QPtCkxu/9OmHIIplhF6sdI83RDur3xmdKx0Q8iVa1v6TyKhTK0IJz7VUG65aEsMFRWcnUD4ytdhLy0qkqDOkb1LKWS/AjY1/8F0wqTR2fXtn43O6dZpe1CQseaHPh4JqWtYs0tUFRja9HXsgaU/FVzR6MX1zh0eqOrMqtTIHGLER1p+LjQ06ZfmQFI/KrzIWGtFtdME8G+il8pbWAJJCyaw58XK7pEHFQUfKiCGOsWc2tR4Hg8+eYVGg/0Ma6S76M7LVpIw70dQkZYOalGTtO9BQlaWjjj6wXolbOF8PFoOK88IX68ppBLJh8/hiqgHdABbgkaC7+b0elwcP5J8/OBxM07w50BqbIK1noW/3l9x3kaJn7PEysMm5aNL9yyLdDjIfp26KV/PIzdbFakGxvODfBJPR+ZYLISCI1dd/0ndP0wBhmqGA3fUYry8eUkDKySApMABg6nISdWmK4jbxC5uirwA4B8GH5K1gVE302vfsk3RhU6EU2o/yFKpeb8JZn/SV3M5ysIIKCzgK1DW1sbNvUBMoDfoErrNtt8nXGxsMYx852sO2CW4kvOapKhPos6VUY+A5qYej2A6PyPcTaQuUIaRIA+D3nr7AhnBcDgkYByVIqC7ZRt0Gs7SVXAFCHZoo9p4z2nEhvczerObUnMN6wuxe3ln6rxSI3DYzxCD9SreT6T2UgBCx38X2nKh9RbJcrBa5F7wlD/JJrkgYlGdlTdwZoudWJ+CRumbKuDwzYqFzyIA/aCJ67Pk4ToeDo9QwoMFDyRe7yOKmul+a7G7zLjIit3Ac/EfG6CLkXjDnOrJtoX15te6uY/P5DS13W727CzNe1Z0NlMoE3s/lSaX1/IF83b1p+Z8IuYxw1mcW8NRdWC99LpZM4Rh5CHnVZF1sI7zhZRgG6YL++rNekM/PJn/wzq7lLe3EUhe2I3ZVMDNFzy+h//fQj0JRQ9jzzzGcZoFAWm5OyxxokX3xuRt41jnLeMFwnPcBCdjTfD0TSlhXgDY/0wq3JW4FCZoq4B8hDkGTbr7/JskR/dZXs/V7XkL1qakPGYl3kOfoMMPw4AIwXvj8PvxYuKuXcNzESgWYqtwQGV1Cc2yXNv2LGnbiNvJsVUC2velrfCYLogmCWLHc3zWm3geXxgl8JbJs4RWojBZWGunAhM+Vydup+X0hokW6YoNLxThl6bgblYZwPD73UOAKAu6VZfCnDcho0aL+rHSOfi0MQp2oZQRaXjelgQFikwAz3b5GqVKdWFBK/encJ2vrs5hLskyb4oUFptZoHKcCzOFkoLw2G0qXna7ixtfyBvjyimWtwMnUb2PGF9WCrpsRNqC7ZTs0Os20ewKuwiE11gckreX8Z6NeSOopaZHp7X6nVTKwRWtTYaShpqQ3xB4JtusJ1Zd9wmodz2g4/yyFECG5mQb2ZlI1/Mx/ve0hrpigYgzm/30sLwvRQRYfNYhiGn/h0ffPVx8/4C/h6UK9bwUkTcJNfd09EP4eWNtz3L4kFxz90VVB0c8QyIleL9yNdl8BidAANf+2ybpTw/mEPg9ofyhjN+GGNtAV3i8kvIOp05bhIoeg64FVqda1j16nVrs8/bpJDnSPW7FHZl4HqT5oRo9cmxJcbcjXHtpIOxNZu022M6y7yVdanWZ/VHlJiYUxk3FqpOEoMxkiFnYN+ai+++YhJZ4B4GtF9t2XPHqoZwxW+IRZ1KWM49WY+ZOdD8uM7XSto2NdmvmfvWiBsicaVFWWTPDUpJDWXAu2E/zsVC0aw8k+AH39SIlduU0I2ReV0KeDRsO4BUtKqJnvC02oDE9ZQUKp0eOFB3uvKdTR7NBUNmphv2unyy23nTlC6OvzfkyeAv66ZN64L8K/n40KS2ra72D662wLUBTXJrdpg1re3UkoVJeEaqIs5YIsvx08rHB8LYshIZ3aXcjR7D4O1RiWvfeVBTUzyONGX2wHj4jpOUSxX6ciXUXrSDWJDTguAJSM3aMRkcLNoObWQVwa7XZRjuYop2oDA3xqasCqW6xhtjx2X7+97t47RfzZbrnrU5DeuIjna5v1U5ZBHnscst/+1wPSNAVdj9GZcKqsK4zYUlLMXOcKBC9Q/HF/8pfFxPahk/70T45903y/DHw0ul8R9fICv+gFcEK/3FotmldhSl1O2I7UqnbebkOhy7m5XziZxg/Fg0MuJQVZK28MY3THZhvEFY8POo+lsm1zeFH9Y4YYblCe5tK5q/VKcuz3S9tuTkIn3ywfy516GokWlUoM0iYl2S8ah8OBOKMRVFEQE0F89eWSv6P828kadjQu8OhwPolm+QpmePC12tZcJR6hvnrRosEOfwfjd+dbufGrAOMqdDnTbbg+TSqLyYm/zu+JQgjufZoC7FAfsHeTGIEAROat4466XlewHdBM4E0sW59dA9BQ1q1NuFRvcq0wbFEtqjc7h6wc16uduHqnIa4RRG9R1rKCaQyiBNBfo66vtvvtDK8+3KI3wAKgvSWvCiizF2iKfFaRlNBFkf20qKUP6xYVsLjO/mx48PuiXF+TlyI2clnLL8JeRLkR+CyMaFGzmNQ1EXEICqklLu/JZExcyRSRhZjgHiNHmh4a84BbFZiTDvr06ZfOlicyPxV/52rfgtA5xL62dwFWsmkoflrT3pr94CIZ6lgckmiYN0nvrsE4KfyV2BDkeYZ5mRXVSBbg6yOobAZQp0uHrJwBifU/T144KP1oL1QBH/koUdAseL9VtXQIPX/y62yJlw39LivdXRalIuP8Lc24JIn1gqn/t2TsCnOoiugZebL0gXq312pFbT4esa/3y9eG365hx/3Jw+zQtfkBbvOAy+lmzRCH6jKFQJnB1VQcJ9XE39gOU4l9RFbujskV9tO94Fc7RNs51BRtwiV4KTyHfQm0mAXx3eIXQF7Vftc7GgKEYiVzBiL8EALI5yPljMbogosHqZxmwPGneQQFaHrhPszklSnRtsMh5SZKhlcritpdwbI22kEX3622//bYGDAB4WqvI0AirHhZbKYR16fCvCqJguc8vymQdazgB2niBEL6Hloc/9CjwFn+kjA52rL7bBOBcWYpv18rmCfR3Otdraw8rk/GOQxBZ2t1BlAf5YQbW5OrHm5TMFyAlM+5JwQJjPotGCcQ5fzuwjdz7K3Uq4RtKZskIJ9mnhwQ9qhzI3CLaq1PN+ps6bZ4OH+vmVdhiQrFa7WdNtchiI4kpOchmO6pUi65xdFDBn7cxdlo1/51F85wGnwIsxWs+pAq/zjPjZ5/fuG1WodFekWYPLP8c+Y3vpK9dpB3pwYI+q0F8XEsmjmYp5cnn+zifTsX4cj4DP+Jc/qgW/3j8CxMGoJxrUQYKXVYoOUYwq0vA9LuieiJ5+FG6StphvpgfOp5iRf3qs18WkUoYHpr4eSTN4eaJqEWQAhY0kdKjOmJYwnJ/XnvZb2IoPM0uUV1JZGYbPnqUkGVJvaNLV20C8WQeVgpevKVO8ZxgLSddHy99kcCySjoRwqQi6zOGp7TgxWje38RKB1GDXYv+TvO98c+aYm3Ok5ZhOxbt69WGt/UCNNa4UL6c3ed4wsgKyvd7b0M6tk9+xZgt/NV/1hPzOFQO6aZWS3l7iAtSQo8DdisoPh6l1sYJhm4jhNoD0XhkN6G25iAZzMaZ9BpgzpGlhc03N7HTlztolTueAkjx60ulx50zvaA2wk7D/2bG9aXgqH5iP4jo8W3MFuADlkhKNRhWXaD/305B5LD/8tSly3mPf3wZAti0ErHk1mIN4PztG9dEvU1ZviLOlpIG0bWHcKhOMLMo2y8vZ2//DSLDJUBoEzfwx8gH5EXIoSFgK7AwPQoP8yvIT6QU+1rae2q7TTJ6IbvHvRybgKek5sD7MjcZuGZ7aC1j9RFHMPV4DJdufwhGpNZ8i4bvwetJmeYOCFA+lxDOZOSEuuDKUQqljCsZCFTPOUZOFx+TfWGzLGVEM1yCbKLpdU/CwT+CRgHa7LbrFuVmNccJnK2aDr6xTGDe75AXcXi29M+DEBXBEDeozRQzeKpQ9Dt/3+LR10jZjhIVLL9MN506IrYZAQkZKxAK9kchPhk5tTBc4mPOeYTkOXjDzEPdRPhFCF7qoeDPrkyLD7SnuHf2TSVCyMjhzfyqg9LX0sXnJseRevnj2+HDQhfLuwKUhZEjjky0WoImGZxfYy8CPTeup7xXtaSDqFcqEyElY4gIz0AB46ieuz3fIFoWmTXWM+4Sjxbpdy4MgvUy3ZlqQKNjH0v7l5n1L8oETcl4zSfoBQjxbbIinsV8cVsNh8uamX4BD3V92zoi+f3j2Wn/Tfkycc2x4V1b41vqy+O/B/sLTcDKUbzvmAtc2CjxdvCY11lhrZbc3vtRlfG7kKKTk6DyLsazhxojHqRb4RHrxpNKW3nq9Ng8o/un68LmGdzvnn1PqxWjTs1wKH3MNl5SQ6s6LWY1nJitPVRJfgc+Bdv2kiuSk2a5fXm/SKTNF4BTjMhBV6U0F/RwtBNOjsX8zWcKLecbxFyQ2EXGSnM85Hzzr+N9VeCVOj2PAJSBnz+1on5odPGYpL9GvA2637G7kWDq1Mzmjvi1Ieb6UeYTHHY9EGMHE5Rf5fTc6WYZvWSxZRFjeRgo9a1/3+13j2d2nGWb2dYTymq6BgfyCuFIlPmCU6eZSHjYgs0TYNrpOy9kg9X/ef0Z5gNxvKcDVxf13wIgu5Ef57Gk+UDpta4+4XpVLdFODFr9146wKk6YElRvWI/bW9rXONW90gqVYX73jV6/ou5PTd3LuNxA/fdLj5V3/Qfl4GLD0xHq9c9/E7L7A93BH2N94svvbr9y8oE0T1VsJ11fiSnXjJ9/qiD9lRxW8ghaq50G1G2RuV1Y5M/jybVsXHzhMh0ZO5iDnsmgNGDusoh54l8TNQ9ckP7RYRtivjNOEWqPagus3mkt3Ia98XkJp3N96XnmljAHJmjX6nmuIJaaAWbITsZi3Puab12z6bzi3A4bOJAu1hwmmHtKXAjnL0wA/QZP2Vj61y+0Lrkv986WiRg/kka0jlreFG1uCM2AS8DhuPiqCi/OMbAOPuPNpyplZ3Hp/HUjhK3zOLYKTTGD2t+0qOoPy5606gwrAHbNoD7ALPP208V2fwFwFRREnQv48p98W3XBvbwR6vIkEkQKiABks9hXysGdKfyZCg105FdvMD6+OimYimD8YWvA/FRGm4MRvw5zxlbML5Lfhd/ozlc9R79XVxm2/7NkZuArxjo1le1vwd67bc8w6u/r0jwuwJgt2X+DblWstwuSNVZHa4gyFPyMlAN4gfqVfuaaZAJIaEgZ2Cx8d++lBQllsJKqhrXsoVJ6y+Wi9DfYDnAqmnjKmqIIQ0/d7UTWnxbKEjCO+H+G7/spXzoVk6wzIlyLVX2fhKDm6rVRXV4/x+gEBKikTqNnznIqbrvROUoNSYMVDVxImDsWLC0cYkXZrmhhk4SpOmfgNtsock4jh+pOYZNyhIPXBZ7yhE+RbkPuRP/Pfgq7A3k7acHaNPOCcQgiyRC2INZlylUyHzizexfQ1M2buVZ6IJQX8Ea5SEQdEROJ4ajTsvepWSZPdUdT4yKbkJMdakWImnQoG8rACHhEiXySkdCmXHVSBuA0lIHWnzRi0AIcZgI96ILSz7GEgFzN1l1NqeRQZ+jKy0mzcBQUBf59NfQHfNntR7FmKvXTOAcsr6L7omapwNJlMQ5VGbA3chzkWEaQNz+RwtH4I/1Ur7jBROMPub8EYmS1jDdvLpz8ejr3rVe/oXEEMk5zkamVWZZxGHfq9eQwtwDQCuY6SIrJQ3tfoJ9O1GWVthowM3/B0h5sgw7PEjfyr8EKf4ZxYc/3bpV6Ni3vAY7fLTOJmaWOAKW12PtzZ1141OtQP5lf4FOqJ7m1zA4HKhwvGU40vTsTWymHdkVEyzBDlYx9qxe1+LXHnyv3kOruG8l553j3zMnLJHK7Tsf/uqJQBbCos/Jqi4BGzQZuf3svtx+V0g6CBxQVcK1e2zlimPxuEqA429WlhA9mOI4gP/8JAsnL0gHLDuZoP9xfdJpDl2kvElYkpbcMit4bX2Tq2z6PPpIYe5BymKVY1TSpADb7qiVutLAKZUa6MR3W6OOkCKwNbj7ll4FjHloodhYhfUh2b6nKNT2lN00PUzssJT84Quw0V/iDjtZQ8qw/478ywoxs4unGimhaV3AE8Bo9syWOlObk23rKIvmrAADLX1dzM5R4sEBf7X5J5f3+aA0qpRH9Q2eyKDoqVQSOhf8B10scA1PbmXWqQuvj2IFJz252Fz6I99NJesV+aFxGu08bzVWgMtlCeoDakhmrUg58ZWuC+0mo4/A7i/tt3ir0pfXVqRoH825JW14Mr9iL9Ab9l/XenJK45h1MvAjwefh9hjy/P9FtKIMfbV5/S+dnFRk8R2JwTrbO5ZX+fU4vMe8a/kJvn3PZ3+Nkuyyyhg/G+CTETLvNMW2gLMWFfSm9bJRD/T6zzepWeS1TD4yJSNhVDaCwmtZrOdZNNRYS4l2qUliSucc07l/OlJo0/8K4xxaEL7ues5nj8P6jIM76gvCwyUrhYoR8nVBu3/o6brv/CYziTFBgFmq0zFbwhiyAFIbnGL0wvoGoIJefbpKboDD/0H0GH1tbwcgzZhgwdxrvXmGrBBHBOEK2j1guZUmGXmtsIkWbuWkAh
*/