
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/aux_/advance_forward.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl { namespace aux {

template< long N > struct advance_forward;
template<>
struct advance_forward<0>
{
    template< typename Iterator > struct apply
    {
        typedef Iterator iter0;
        typedef iter0 type;
    };
};

template<>
struct advance_forward<1>
{
    template< typename Iterator > struct apply
    {
        typedef Iterator iter0;
        typedef typename next<iter0>::type iter1;
        typedef iter1 type;
    };
};

template<>
struct advance_forward<2>
{
    template< typename Iterator > struct apply
    {
        typedef Iterator iter0;
        typedef typename next<iter0>::type iter1;
        typedef typename next<iter1>::type iter2;
        typedef iter2 type;
    };
};

template<>
struct advance_forward<3>
{
    template< typename Iterator > struct apply
    {
        typedef Iterator iter0;
        typedef typename next<iter0>::type iter1;
        typedef typename next<iter1>::type iter2;
        typedef typename next<iter2>::type iter3;
        typedef iter3 type;
    };
};

template<>
struct advance_forward<4>
{
    template< typename Iterator > struct apply
    {
        typedef Iterator iter0;
        typedef typename next<iter0>::type iter1;
        typedef typename next<iter1>::type iter2;
        typedef typename next<iter2>::type iter3;
        typedef typename next<iter3>::type iter4;
        typedef iter4 type;
    };
};

template< long N >
struct advance_forward
{
    template< typename Iterator > struct apply
    {
        typedef typename apply_wrap1<
              advance_forward<4>
            , Iterator
            >::type chunk_result_;

        typedef typename apply_wrap1<
              advance_forward<(
                (N - 4) < 0
                    ? 0
                    : N - 4
                    )>
            , chunk_result_
            >::type type;
    };
};

}}}


/* advance_forward.hpp
wcm5iM9DOwQFvgTynJEHtwxmhAEjHTojlCSL89EB08PggxEf3YKP9jR84Avc0VxUR4uTdpKDRVp92kn9bL8s5tdODh3hICQ5oy9aqGM/PmwC0WeRJDWoRfnZGX+VXVfs2+yr6tuONG+DpkG0lOfiG6WZlnz8hsab8ffDxmOTwxsJhsOO8KxUVlhauarEtSeZdqGksRKRT+tpY6odIJiXS27ESaDYlLLJMpdaPHnyejuF9qZ9zD1VLZsuk/Dn56Rl2qWF38fyrILGAdoY5U1IqWsS3/kUqe+jKUcjn1/MeF+uxQsFVTnO6jBuMWVNFX52R+xrPc6FvkcF6T9sSEo/y8rmBxAV8DPu3oXnFmzFVu67pwOT30ZrsVzVnDaGQXaQINWfOoiORL/0k4yjvHCUXuFm9sssKhkdd2/GqtCyyI85Nvv4vshuum6AA5hFUzoIkdIU+N7NliQiZSyZCj0xlv0C9+IOtO7bwDPliDucalkzKG2bybyOA1d1N6Gd7ZG7Mrg1UH85YgEo/eA+kcnEvRmt3TjbqppTQzk0vm0bNpSDDRqvkx/6cBjM9JGcBjM7uJ0ob4i95ffjTfbzhM1sP08ZkWGJVCZVPUDhMppEuIx4tNn4dhi+oV1Ajh6gwA4xin+AcTSrHFEtfD1/luV8hW6Tzmo/0Ct4C29yVhdRbKNm+VU8WDOBgfRDe3dOEBMlwn9vBScDm4yPclq2Ic3NA4YMFVi6BNlsNZsEbUFLuSEwqepUmP7szkkW4ZHZmjSyUQSFhihl3ar/JkZiI4Oon9vUeawKVpp1XOP1yiUS936OHg3ZZWtXFg/EwGuQoxSOIRyDTqxyWUKTdLWVsg82UcCGZrqbmuXOP2tao4h6YhU8fi+H9sl4FCsTRpNM3amLDu6NFmjETAVHcL1L3Uap+7M+tVmGwUMlytYM78+ER+XWga3JlMW2WErIyRSa9YmtaeIrTZ5gWu/yhsJJ5wfWPgSdtnAF6hKeNlb0z71GohT4+egPe7WktwaTHu8d1h+K11cy4SrsT+ZXuu3tZBZmz4ERTE3m+IJrKb7gvSswLuDoQyA/1koUX/AERQrsfwdK1lsoXUDWg1hyCktquim+oIeeasOS2pANn1pEJe9AyeojD1LEwXIq2QUlSREY63fuDUt9n1ZMOR85lVkeuH8FWrPYDfAGShM78qbNUq6uQUbYfvxOjaocY1Z+fSuUBS16YXcjFf73W3hjGS9L8LIqulFdg8yxlfBDKc7DLKVo0sJIeovzfFpuB3xLDcHI23/nhCvhZ4dieNHWxflqYZ0xksZ97Nax3DCflMwr+B23cy7HwsezlZJz76W+z6ZokS8yKyjwbg6/2rDfZqnQn7DwslehrPoTZzVaE5TcbtjCC3Nd9a9ZwssJSquD0AKLCX4vcbv/mzbuFF6wqQ16Jnyjgef1qrXYnywKLRjMFD/u3m8T+pLAW51OWATG1ACvmRwyM1/G+mdkIi/KnYjmQJMK95/XPlSIO9hIunlQAe3DyOHJZlazQLwCOcvnJyZLVbcUKF2BQXvPfHgOnayH5fmDAyaeaxt0pVUyK63dZqVVaLBdYzHKHj21pAEBcjQufGJclOf5+bgYwVvTpDJS/o3UAV3OB7T3APVXb73NQg2k/DIPA/xPwzCDJc59TQc/d/lgJFspWuAJ5Wd5NpEqz0YRAk/ALMDJx/YAARitZh4rdB6HJpjg49c/8crjl+cL30ZrCIqcL/esqtNTegdAr41n9gh0Jw/CjnOaxffrIdqp/erh564Mym6K80z2dPOVFnOcbtyvp36h1/jZ28I1liwV6RKLPwwPXEVi8es4XStM9bc/6RWBhddSJK795sDCTQ3p8obz9tlqbp+8tPj486q7s9z7hpX9MeMoioJyeABBsjSKpgujDBl0ug2DETkjs48HziGe18c+GMDxKyWx4PQsB1c5q8/y4/xwW8EdODqctXsovpQZDp6BeaAxg10hv0WltPK5DviOcmGPap/k87L7jp/TyNnZ3Yn4dR977ANCRdgDS2/YhNjnDj/LWo/IiOnYkWRo1qUIVtmDPDqs7raJH/MZ02GC1+rejxxmJ+ZBUSTuEgz9fBF59kok1ugWF3ZLFjlVF554wvWvmYXutidGvWHtymY9+2yW2z/h6lG6aTnYKTXFLd+Ycbz/NuaY+s+bvv/KCaQb8qBixsq97Eab3o9yuFNv9A4cteGOrjFdWeoGLiJ2pjibYxecsSW74A84h90dGZl6L3RDF8RbsQu6/fzwo9XHTh2jLrDpXdDmZ5G1VJQBO5DqTnjZ2RKEsc/ia1abGYBiGKC7ffwM5bCXreMEswP9OzfgQGrysds5QSlg304Q92Y/u36t3s2jhkLcJcMJk5sDm8x1ClhP/ifRT0Lf5gFW3PWlXlZ17BxpHhFPjxWqPRCoXr/B4mPn+whpI6zFcNHWdQAILPfTLQm8hJgx4Rfgkt1L40ic36Fofd7dYw+NjTzcc8kMsHFCsY2KvzZQVogTgGIrFV82jKCoRpYl/EB4i28B+7eWvTzgU1k7FLm3edmjvGSCaH5PnY/Z/30vhxBNTHbULh+7k9+Zo3fUHj/7+Hl8t7lKP4VrajHZEUV7tr+D51eUD1E3bnJHgV1mR4Ekpmi82WvAZbj1abkbKR5Z9HwoS6PNk3eFmHPR8+Hc1do+slE/iqqC5nVWL7sskNAm06wpuqG7M+LucM2T3Z2FmXyC3goCOC3swPfSd7FSu8e0tbE03lhioWTz9tiM8/iFub+4Qr4Ejoj1Bu6DzY8drRdpOdXGtXo2022YG1BiLbttem7A/vVifyBh79BnvSI3IG4XmP1PYi/vFskVsw+U6bkBQ8bVCL+aZZDKjmfj5iMvD/GEm93GrUv4raOMW0erjQ9m6Fe/y6+OMa46XsbZXXgo5PSy8bu5aWYaFpXCP3laDnyTp2EDa7n/CI36CjawTGLK8NlQTfIv5vfrT0aBfWmX7Ur5Ru7dsMYUD3QY5fZMvIbZMAUntOaOPZirBWVJuRH5YtXnNK0CdsWFffwzpxdUVPtPMQp1bqy4zlLhVSidWmAlHnHwpMoVMBgD456i87JKin+E5k59YdFl3cu/tVkGu8sr6yXKJVUhsnYHLE4MYq08vRadY7+gBN5kpWlFCz7/bgQCx7yP6z7t1dRiaxot0NKaogWKfHAVQWGf8QZW7pExf8duaAFlbA/JpAsxaz0KoyBYzCtVprXBb3XLdGo1EqGVGi59+YXwRa8fOIccnuBExOPhYw+k0xeezTXtR/OGs4dVSqq7HViUKxNs7aWmpIYIm7bdSg0cyNuOVv12/dR+D/voXT5hgrxYCBJ72JtQjnLEAQv32H4VfuNe75Pdbcph+eFWuuv1Ji6EkS/SrBaUTDoCc7vx3Pz5WvKHgnd6QvmxlK9Fz/9kDqz/mvMZfJHCy071V8h0WUK5G8WCjEOw0S2jZyR4prA4cshVeHnVMaUyET3/5I+Cmlpu9Svvswe+0ajBBnnwlD3jx3YZhPtOeZEd7ajlkuLuloscXRnwSKSqzeKM3qOJEJTAafxwmmGUxghkaeH9zzb/Jrk+Hck12X8wz+4w8VLdiEBW1RyoxmfgEpI+gXJ04BJaURChAG0bnYo61jq8uzQwczsiCcZ+fgFDQ55XolgatFKxt4j99rMLmkJ0YVsUaIbCs87qj8mmZIHyGCZgeMk+gJBNF/110F9pgPCYbOKFJk1dh3cqPX5SAh+yH9VUehb2/6/JjQxK3xx1VCugp0JLFRX59anqZPjJfDwWplVZh1eDmr9BgiWKvTcVOiSKRYqK1XMB0uvzMxd0lXh23U4bx2rRr31nk24MUXwm+QqwKI7ysoEdfMkaikd/qDkdHr34ml9cMZ+zIfnyncOkTa/fLbTpz74+l6pNM88fznHvyvAPUsS2gHeFMDAJKLctqUYa4jjpLOzZnVyNpB/FO3g76FuqzkJkJylzz8DH6W+SlbgHTz13QkNVx8L3m+u2B3yD6s4ctu5x5rrf326zdD1danq7u2b0ium2yFxDdsA/qAZp2BrqXjfV8BjUcHoa9Gophl7HJwj3G/hS4/l+bjtDl1gfFLDv1vHj4KXwKbyT18AIYzeKci98GnRQdWd5X/LHWY+g95svNe2KanSqPa/euz01/877+anxgfZsT2OfO3LN1djLthsJv7e/aETMrsUNL3o0NIrAckEr+QigUQuFkk93mjXKB+cPxRNGDkqnE4syLKn5O86w70PrBL/D9yQ8fpXoS4tc8zjStWMbxpcvSxv/OSVfBPnzKYvyVBCuYF0JYeapG1i5p1cL5ikJ5oEvaLLAHBuXtNyfU7ab8OigneXDFXVuhgIX6BWtIG1UOeBFb0VESQ568VQ5MMi2dryiHHa8zdycoHgGYBZvaLKJjLEik2x+7AFWYxSmzVeyWsNo+mE3z7tTT5yEvhNpXEvAhLFK7VqOZrGVa61K7XP4ozzP5we5FN3IiigtZxCP3ZtQ9IDm/tHsNPlRqHH3uTMskcYXqP/6Q3lKzUaydXsxiSoyAUTqgKhcQ7VAOycHzOrTOABO98If0/h57pqrkG9Z7Pu9GAi4AD/KHHQyuy7m3NsEvevz4/w4dmcGYqKCo/nwGTzkmFwn9vISeROyJm96gf4i++zkNnEG6NCPVIMTobYdv+7WjCPVGuzJgk1PYeoizApGg/SuOttIcqcjzfnz/9d82bnDPF9m/YMJ//jqVeMfUT6+6TWMweBSPA4vIshPDVCQSheMGD5M/FxEWzb49Yz517kNrT8STj1O4hUioVALhpwN+C4FJVLoJrlE6hobeVKyhK6LzyMvSn3a8hnLlmzT56rInxzpnjNofrJ/2UZ2RAzL342n8+5zsrsfJ5cvJZHzpS3IFChK3X0f9SV8Xpp+PJkz2kD7lcoepepcME/2tMpl7WzlvTDLb5DdjD2C32BoNLGl+O0brAw/rpfdHex++DajkmVUNQUzQfGTK9vYHChSPpvxP7UdbWxTVbTtu5RHqLxu3TrmAlUiSqwhg/1hlo+OrKMsDjtMO8xsSyKZY4mRYKtgNiB21bxcGxGZMmNMUBIU3e+NP6avJaxbkGyDuDpNmIaYNzEqJLJS5p7nvvtev8dmglled++5555z3/0459zz7oc30aW3eqetSfEpADAOsUvPkK0p02IVQWgRI6gBAAxkctwUP3x/COyMluH75Pe8Tr4oIRFB5aB/rClabXyLiN3T/L4tvGsrdt/kj9h5VyN0hWYiZKD0Pb/DC/COJJaFnMtD3uGl6/cJKxj3p+S7KeUv0VtwT5LfRy6pwj0/8UcMkXcCcgZ6Vw+Im3ax+hK1I4be+6aEvNdWfbDI956tA59oQgmJbMTR1kIYAjDhHu0r/PAz1DhQgv6mqiWMjxwW+jwWap+/9PmS9tvKV+zIx6enpIBF8b6S7aV6ZUoI/ZhfpYbdLG/OmSrK+48NJKfqt83Xp3XRkIDe1eb4dYu+n5F5O/He3YzJ7o1p+Fdov3Xk1seCzuTOgZwNyga8rVNeHRVgSekYlzSpSoY32PBdgM4D1CNNFl3JWWL++3D5y9ujM1C1tcxni1vLXySiaH1hJ3vi6CaQwSexoIQDf6vnlZB0JRlLkE6T79IXg7jxxFuQZsfNFOlRXCYDuFtMZLcGj9Jo4C7PxvFeJCeVY9bWzAZX8kYFEviDN8bV8kiVzuE+Tb2DDRrq3QZlATe5tsYbV84PkNP1wWX1HhQwgRmZE0V1UV+criOOZ+4TJwvcuMFjOjx8kfjrrImhry9ceHp2ZjyNR4UZCzPagc3coNBhHbsYLddoOphxbnA0UmGPNH78Dzc4dnCCzBxDMd3QKx0dHbO/Qba08KeFSQ9ZwrdaZ2eE9HImjacysWXCLQtzA8cE0cLEuEEPsiaxcDD6KpSKmWKSfmFG54v0rrz2tiS1F27op/3jtunUov0DjJQ2qfL0aHYbgTxq8S4DTErVPajyoF7wtljqf+YGQa8I68mpjUeXOUOJOXtwPRY8/d8eAMTZeV94IrgKC/0XiYafvQex3Bah5T27mPyiJSgpsUq9/w8Pkx7pvxpsZ+tGYA58Olq0vh00aiiF3nRLT4T3X+HJSptEnybilIjIYr1xqbJxuE+WWVoskChJLohGXPME26hiR5zaTG6aLinpOuBQDs/j8Njhqb2Sf4eHB28CYfJkpAmFRqS/OIGF8WTGui75uilPgVjzxXPK3w7lr/2OlN+plpdvRbSM0dIQYumFZnShKQ3vQrS0zgxc0IYmsvAcfG0WH0tm4BiDd7gOzzw8vxa8D63/F7B3NTGrK8LRI6+Fegya7oNk9UX3y+Efu/3HUVg6/GI/UL/DnbuKhJ+RFRgZakhM18+MwF/CdAeP48vcuTEk/IKs4zUkqGMmyO4PY8RQ3t+lYRKd9p2cxnTH0yqej+o0DJg4pmswvvrrYtZYCeoyfDEWMgNmgrCQyeTz2UEWXgBhTJjUpa3pmhgew8OzSai52Smr4K/53tde3N/cLEwa8CGW3ww/J46BQGR4D8KHEX8I4d3IZ2tFwUf4Bvmazp1I1pLNyNbKEiCbBUJrZsIPOl+WeijkAy5II4JUXQ6ysg0F/IroVKIuGg2JpIFVoC1f2j6TL23X5GXRUw8TJHBhE10Il0tvBdDjeisLE/SQADl65RVyzyNs4VvmKIItGXys3j0XrCEbWtfy7jlaFgCvADDXO0py7CI5HNkkJccekiOHEM1xRvbei4P3iJsjYMZVhKGD9ft4I+9EygEMWW5K3rWEZHVmFAE2HUcqPvDSt7rEhnvEp8UC4erMGCzCXcVwQN/UprCF5lTZ5o8xP1RNXnJRexbowefyW2ZbQR3LwA2KLPMa6pnAWiqaIFRBQ856hgunyaJCBjBK5XdlEAMO8tbbszWcCpaRWjLgGsrDlgysw9uxDykNkwputk0FN8IcHVsoFajYdaXemUgWtbYA+6q4IqW0lpnwLGqtLLkHNNEOpVSp4APaxmvAJuJSHWHMftMelMcmXz+VrV7KeSquAvXcfSZ7GIf+5AKKucBCo/y+emj85LMo9J8ujfn/xv/L/8i/YXH+eSaBagOXf7TYjIXSfz1Lv5S5FWQjTUZVHzfwQWLvP5uxzNHClrk+F+gRQ32FbuaiGYJ6/tIByE7PXyL2gJHsl76h03hEOyXhi+frk52sB9fyh1lcu4A+MRB9YsxRJ2VgfmszEKJYjKV0SZG9vSFfzlSXkhOFRniJ/YReKPDttmG93DmakFyTNr6HVccpDP2AW5FQDham5AzvYFXxA4B6EOP7JdlbvRFzMG6Po66KTs3+yTVdmr18S0r8YghsAEfKNMnr/aQ2Lqvn62AG8NsQkAM04oYkrvhIS4psTfwsDY1mhAmpHfFNyJ/NVDwe/gW21OHYmjAAgENLvF0NdBRVlq50KulCiqSQBkEDRg3L767RoIZp1ATsThQTujukA2iCzgqbyXhchS4IPwkwnSDFs9EZZQQP7pkzzu7i2RlknRlF3DPmB9MRYgjIKh7YkfFwtDKd0fgzGDBD773vVXdXd1enuzHOUdJJddV793713r333XfvfaM6H7rTnA/9VzgfTM+mNh+umzJS+xED3PeEQCql1nc812D2nWjt
*/