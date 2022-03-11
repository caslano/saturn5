/*=============================================================================
    Copyright (c) 2016 Paul Fultz II
    is_unpackable.hpp
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_HOF_GUARD_IS_UNPACKABLE_HPP
#define BOOST_HOF_GUARD_IS_UNPACKABLE_HPP

/// is_unpackable
/// =============
/// 
/// This is a trait that can be used to detect whether the type can be called
/// with `unpack`.
/// 
/// Synopsis
/// --------
/// 
///     template<class T>
///     struct is_unpackable;
/// 
/// Example
/// -------
/// 
///     #include <boost/hof.hpp>
///     #include <cassert>
/// 
///     int main() {
///         static_assert(boost::hof::is_unpackable<std::tuple<int>>::value, "Failed");
///     }
/// 

#include <boost/hof/unpack_sequence.hpp>
#include <boost/hof/is_invocable.hpp>
#include <boost/hof/always.hpp>
#include <boost/hof/detail/static_const_var.hpp>
#include <boost/hof/detail/unpack_tuple.hpp>

namespace boost { namespace hof {

namespace detail {

struct unpack_impl_f
{
    template<class F, class Sequence>
    constexpr auto operator()(F&& f, Sequence&& s) const BOOST_HOF_RETURNS
    (
        boost::hof::unpack_sequence<typename std::remove_cv<typename std::remove_reference<Sequence>::type>::type>::
                apply(BOOST_HOF_FORWARD(F)(f), BOOST_HOF_FORWARD(Sequence)(s))
    );
};

BOOST_HOF_DECLARE_STATIC_VAR(unpack_impl, unpack_impl_f);

#if BOOST_HOF_CHECK_UNPACK_SEQUENCE
struct private_unpack_type {};
template<class Sequence>
struct unpack_impl_result
{
    static_assert(boost::hof::is_invocable<unpack_impl_f, decltype(boost::hof::always(private_unpack_type())), Sequence>::value,
        "Unpack is invalid for this sequence. The function used to unpack this sequence is not callable."
    );
    typedef decltype(boost::hof::detail::unpack_impl(boost::hof::always(private_unpack_type()), std::declval<Sequence>())) type;
};

template<class Sequence>
struct is_proper_sequence
: std::is_same<
    private_unpack_type, 
    typename unpack_impl_result<Sequence>::type
>
{};
#endif
template<class Sequence, class=void>
struct is_unpackable_impl
: std::true_type
{
#if BOOST_HOF_CHECK_UNPACK_SEQUENCE
    static_assert(is_proper_sequence<Sequence>::value,
        "Unpack is invalid for this sequence. The function used to unpack this sequence does not invoke the function."
    );
#endif
};

template<class Sequence>
struct is_unpackable_impl<Sequence, typename detail::holder<
    typename unpack_sequence<Sequence>::not_unpackable
>::type>
: std::false_type
{};

}

template<class Sequence>
struct is_unpackable
: detail::is_unpackable_impl<
    typename std::remove_cv<typename std::remove_reference<Sequence>::type>::type
>
{
#if BOOST_HOF_CHECK_UNPACK_SEQUENCE
typedef detail::is_unpackable_impl<
    typename std::remove_cv<typename std::remove_reference<Sequence>::type>::type
> base;

typedef std::conditional<base::value, detail::is_proper_sequence<Sequence>, std::true_type> check;
static_assert(check::type::value,
    "Unpack is invalid for this sequence. The function used to unpack this sequence does not invoke the function."
);
#endif
};

}} // namespace boost::hof

#endif

/* is_unpackable.hpp
Wa/OCT1ICn+goJmd/vqlHcM//ePaQsalAuiMV6M0IEh5MZXbzqb7Rbm/P2gCmHN9E0ugKYOJjkXXomSX0Zvyo49RgA+tmB2s3VP3WfPwZknFB6rF1HJvcV6+MIcOZWse4Vx+D3sIz8QsNXaD+OQZ8BICrgAFBBv3wOaRMbusao4Foqx/qvyCqQpx+DCleE+2BaxfO+A2EGfDWbdR5Z+tlZgfRAkZYilzFRudWSgdTVS4+Rnx9yPVW17Ao1u8xG9BJtSzcSE9CYbqFnmmomT/GzoOf4ruPAvIeZjL3X5WefLNAHr2CIZjQEnrbpO3LfyNVEG7kSgq/L862KRJzlufZuhtbseFJgg5yYVgtKxlz4+5oMPq7wg0iCFzhPukaqNiSOI3epPcK6IRcASJvjAjMgDRRKwjCNLSEdyXil8HUQcV0hDggotPc8JbUxIIBrYZpr63tio2x+zElc7BVkTUmvLc/KdWGX4zoY1/oqSKn7C0d/dgHEC2ZekJXt9H70F97Qiif5ui6aBmAaFsQFy8Uwc+w8KkGVDlZabongJwbul4xPqd2SZ7P2JZwOM0FvbJvx5KYY8r7p3ve+825SxAwBrSQNS2kNx5l3ZwlZQmPBlEN0Pm9tfBNrIDzbK5lzuIdTtlB6/+x/lEuBp8h192aAcURXzT4yq48r6JqQ4lMDUrhbLh2RsEDA8zkESG7jYvBsF6lXQ+0ZYlxqgith9bc0w4CTQKI8xIGNbS1DfUrud/vJ9DsQBJwMLQUQHSrPc+bJTodieT8e97murkQCZgGjYHsSbx0hYpY/UlihjkCLU2IrxduJoViyFCtz0HmEUlWsxK4+zT4E4Cd3kQGtmR/aQqfOSONkAHSWz8SFKst+GzuSK8GcjEiZBFFPgwzgfjdm9Q0+ViONHSB5OEbqArs/wwetCjJlZsdVMLRjQhRiZZwehpiF8N0CA1g9174fYf5vM6UoqE7mYONDjOqFPJyoCSfybHnKCxNjOMAe1LjQEK/vI/OHu8ldnJzRW4RDpUZTY9y+3xOCNCN7Xyt65Jty48klvNi0hX4+9AydQhA7soj22vSv8npYmaTbxNtwzyLYC14LJpD8o//7tNbx48wXh4LTU0s6BZ27+YPNhdqh0T90r4Fm3DZsU86W1ndtRp5454AZWoBmbXamqFnbe5gTXiq/GZEmwL+Jt1o4zdRciwDJMGEgVK6WS8wVZwuB4lCF1ynITH1cFdSljZzBtH4o+g7sQr9fn30gpb2Z4LzFlI+aRfw5ubRb3R3StlxznDlaRC0zIKHTxTkl/X6ZJr8k1u7Mk35wznl3OevGcDZQyT/gFnpN54h5v9JPFCzEwHtMC2yWXIOE1uggtrX9061DS12QoNvPtpA6nSxul15gn/JkHmYj8CUHv5SaJT8tuwWDvocNazQfni4g8+ukfhlSyfLcb6hfBqS5Nj2IUDV/YHEWrt7TLxImsqecxGtPLJeCqXWC74scKBDnKjfl5bmm8oWeMYAXbGF40qET7zlddAwvNASHoXLL+Z+wsFt1UyXrZMjd1KFMcwRgoZe9VYEwFjh/sPX1akitYLU5Rljv+M6SDgzEj8uN/1RwVvNTKQQdTE/Plk9bZ6KUYmw4Mu6UyYmduZ5E8nivWHGwUwndB3rkz292qorGBcfgBYzSX+CSPlu5d/WIslU7sVMdum3N5HITkauE37jL4wFWOcht2T+RL97OJZOlrYlsMPw0hfVfmDhwxhUBdjwmq3sNnf4kiQp2WkiRJwAlI8VC6x/OoBnjaaDVTXwcw2Lsn9rI0Jr2dqzX0cgvJ6pJiUNP2rIdFocrDgw4Lxp+qDn7u35iSu/c9/bZPo/HipXpRFZz1Jhr+FAH9kOxvsa72ougoz/ybctE3pkb5RDVMENyj2xW5a3eIqWsputTYNhmOxrAv1TMJWezZR19aC8m7B6Z+UUHCBheTyHW8DR38lDikwMLinz6U8KYKMj/RDqiUs2Xa36YNzd5f9+x9ybqNYuwTyHDV3p78fqVPJvfa/ZKgP2mdA9BCsYLn/8pXhPxrHwT11zHkZ7sUoLc7LiCGuHSrgIxeEJYw0Yv7snRA+ltrhhEgXnPr2FpZA9C/vZ3d7sx7gDJY7CJa4bKg0TZCRMG1jdCF7URPAKI9K3rKhAm85cRkrttK1WblmSDIHDTRWLy/25ioo0BTurcoKbL1YRBN8nGAhGk/6hAAAAnLRSoOhSUAQbkrXQQolcTAoHlQKnQ9pxJlHO4J9RUyeniRrlmPhv23it1SgJ4c211IfW42rpsJVKOaksNrWVdozEWMFJbNcwMCGSqSjKZWBO3CngoUMLb2XbjdEYujttjp1cFQaXjoPAGUZy2ylx6GRmbOvUpdxmS8trEl4/1z4gLDwA6V1SLSeBd0d1Hd6jrfkf91HTl/XjKYtR27rA3AQnXLsrUjIYHNrxr7GcaeIR+JAzKBXQDOviicyVthIABwXDzMhavGtt0Oy3ogQsZ3AGiOHmA8u5rKQYGyyEYhWAEqlo2riuKoRouAXKxxJB4JBBr/wnF7EXK6c5nPpUA3pMbHIWLENbdVjTC4L1Cau1JQAIPvz687vLblYdjvVcltzj1sbFd8aBS3qV1igADKbLYfZ9cmKwLJQhpSyyRVBABRNEMk3ax1arHE4/AtsNbh5+h33kd2wb6CqHfZAVjAgLkUu/vvDZb/DHGhe279yKJdP9EQciGPH3yC8LgDiIRpU7aoWykIJis0VryCVaJloqQGGoGeKFHYo7MRzTJo/AIw+3VvF5vH7cd2euh1dy6NbSD/dscqzbue4wTv5AasblmLOyqoo5wByZsTeq6+z7SWzVVErLqwccxm1ptceIYmeR6+vwTYWLRK1Icpbqnv+/gmD11nQyntS3CCvmnAZzONJYyTYVy0CznVjBsUVMDBYQwNzClgEoDQBONC95zy2XXjT3nyG+yDR1AoRgR3QMATXm+wYjR3QP0klY+e7NJ0SKXl7BZKxZGjVhH+3Bp1Q10hb8KzZpqJP7TvohH4y4PjQ+O1AEqB6EpDSCRUAGI8gtYGPpsKDWui+2wY7/z2h0oHSwzWGf0NrxGiJFvuv4IVa/ulw0zjwgVU/dXb8lqSj3lRCjQmCv3zeznPcQ1kwDgAAAWYBngQF0RFvA7YloM1Qwy1442uIeo0LQE36VYL5GoDQuv2rzYuOGBghLgQLZC53MPjF+ktSuywqTT6bB12nNkZXOcXoTa73zEkC3Lbd7S40pYuQ8PULm6rmMevL/PziHIWWhDJU9lVtahhGVfTdZzkt0DwB8CJH+ATj4qD/sBYEIh16OPKewAsLrFfg/Nx8/gZRwdlGM8CUbF2uJbTYfytdUjfImJ4Cnb723nlfeym5hgwA2iCrNz1yoE+B6Azb3DCCFDxTEb14vRZnUMWbJYCR/rrXZzZqJK0/vUtxgijA1ob3/UpDyZ7GmZVWMhIHhUcIuqGregmYex2hS40FdPAEnr82F+g4fNAngcmth5hKAPTnl8lJz0w2H9X5xPIzU+cCs8RJL9mNdXj/B3NduPLHuKQlBZlZJW3IRqziNEJXdSGly3/fow9bkkxwM5OZiiIRUl64bpDfvmkWpoQ6VXSPCBe+uaPGIRoU1Z4ah2GhBMADUVoIQqzLumICqiCg24AjKRlPNJGPL+/w0gDA1kDTp+N/IG4shSWiTk18bTW40rluTNTTefWIs5RYBQsMWOAjir6iwtyA2JdSQWMRgX4YRysNaY+FiZpOEq4CogmmhMCrnNftWSkVvsgswUigMj07TpZ2IEc4MCI3A2IaiN6zMpr7Iq27lAsxTqtgvjRlQsr3JqGjobzuG/vEbvQiE/pGVFBaCV6z7/D11p03n6DP1qvOtkfqsTQlefOyhAjOwxFCgBEITDD4AA6CAgkAeXVTZTbySaAAaWvFpYJ1Tj3TIYCmUC79w4l/0+e7u20iWnd2u2migmq0AkUFd7nlx+684AVtOltQAdKXi/vUJIS75wn0NKwk6BD6oMtOO8Ql2Fq8+VPWvlZccZLPd0U+GD16reNaqMOqIRoU5ZaRCEKxEGJ0bW1ecaQVTVgCKUNCbKAV6ETpgw/NcnQNhOb+t8+u6Vj8sglTNOosyxPgO3qys6nJCig74tswAFW5mCFmamxscijtcynv3LdrobijpX0zqdAmzCsxkaFbV/I/B/lgjsCeHUYTXBHHV4WBrCr0JXf5bkYjBog2JkZlAEcWAGRJ2A2S0mMVicvCarrvelrDQ9Bwn7vaS2+UK0WdPkk/vcdGE72nEw7nzv+TvjJh139f3b42yLfyXo1nhpkKdAmvSF/8ZN1cMpyBK0DipAicC5FmnQBBi0CMbYr2PZuM/zh1p5/8ffcpMxhiS+75Lhz7AHCFD+wAWpKUGOyaFAClWhSa0tEusJjZrK5bwfqEx6Q9qGSbBGmV+mXtKOWFS/olmkueJOO2XNasbp5Yz2loc/AAAAGUAZ4ECdERbwAEm9Rmii5jU6XNxKTtX52hCPfBKLvBTpxnvo/q/mZspKL/Bu3APAN9/8hjftlQ6jjN2lXNKovpXYMPBji9SvWx8uG5QPsrxGh37N2eZE0bEUxJF/OyW3qg1b23jFPwbh0kqppIcPry3KeGqrJHZ88kanNAH2sg/SiJzaMMBVahfCLBTC+yuvCBaYUCxzVAXruKpDZO3dJvxsZaZf+NBwxXGcw2eTfDjU+nFGqwy+CIPrAdn+T4I65KHx1PcLD/eZT3nsL1qvRiBJYYMSO08NwzX6bpl0VXrzHjNu8IELkoHrl5Qn/cxTewhbjO6tKba6iyO4om68wH5xfE+8VNsbgSmsn0N4pfj8rTsx6X65yX8VD/cBo35vZGCnXW5YknBSkI+4jZbv7AA5mxNtdqpbV7Zmf6BbKGi5lznFE/qEne1wRZsm/a0LIVb/HJz+cIEX0Ql7EdA16VdQDAigtJhypRMc1af4SL+SsIHYfd2t+M4SsEqPQCLH/LKlPW7XHrdNsJkbN4vzFsL+Z8Q8AhGhTFmpzLIRnAPJllhaUsZpQWD1+gjfcSOBdU9TF/p8/vufVPo+LJobd5LLAc4tNJPbebDndGeq4dABcs6NNqDFUckbExHQpuI1W4kUtgmR3QuuNcjyi4MLN6QEarzg4F50G4GYRrzM4yyt4ZJHdBqYgCoBwzAIpCW0iEsTkaAYWSf1fUzEboSnfvapIYkCEUwEFcrhJBVLBCzpCZ8JaAEgNHGW+6wR2XtE3+c+U/taTniz2NSAqpXKGKGFLX3uFG+lU4qJooz+b3cJT51k8OlmxL5a2shqS9kVYGEwDFQBu7NV0WLoCxGG+4e4j6gkRdD2R3y98u+fgJIWGVcDgAvWcid68sZKKffQkK5FZW9OunwneC+C9nvhzyzjFMMnHt7GP9MMYMdMaWkWQps3pQzc1J4wqr2pG/IRoUpaKYQYEw3CxECKADSVIm1W4BpUYLQCbKJDHstBhAHIJSgcj8skqVXobvLkfgK22elfW41LY4Nbq+1TyDXlxph1kqqtM9ELqA6ITw/DRKAgmlxUweV8KKn7/jVlkj3AkAVEi4fkisAQyCjwZudPy6D67nGXKRZYlDMpmGZAsoKCIbqmWtEu29TjeCK1oCyw5MDMAFnxU0Al+DOiM8OJSvfozw+/LKVBACVGh5NnKSw4BFRloCKfY5yz4OM32MM8qF/gJlayTxnb2fiYZOtay1ZKi5upBSNSheVsbHOQCFQCq4DQHAE0UlgEJCBTzbTQDl7gC+maU5xQu2tCfmTWygAB83MAABvRDCUIri1TeZ4srycuMmH8V/Fe2D+HoL4IVpEWUZFcuNTzQGWLtighch+lcCsFt9TR0AAAFnAZ4EDdERbwimPQDd76MHa2d3C1d7nDd5jL0XdgHxIHlgqD1k0n3CR263lInIsER9x7otMdb5S1iV8akVWQjeZXvIxy9/1zv4VS/N+Myp+lghmuQU/fxwzamq4zwUdTJxYvXlLhWAi8K8aW+8QtuqpSuRanJ9ngcVHV4wD8+6lMy17BvfKyG1KTiFINqbMJxIoQ8g1UNxa9zT1oCY8zdeuypgArVpe7YtVNDE6spPUt5fnqUclqeE3xQ71IwMVyuUPnYnwgxJO4i9FiIZgNGEB8Suo84Tljro3zx1Fh5Pk9T/l2zoyKuGBi6Odl8GWyvGeWW0zs/iCJ93Jxmj8dv7XhbwDFYZCwaa83o6OIxqhgGpSmPUjUp0Yf+2RKSFNS42DAttwVylx95BbLQyA8rg6kIiftmQgEPCiQtgjpGUY+55nyL519ZbFxyEguXA7cUrotjb2chXEmjYT7iNsV9gYpH86KhQGJAhGhTNppbKQQoCJrULKDUQq1RhoBVtAx5DJ2IxFYW7jqWZEaQGOVBQfOTAZo0GE8je0lxMTaP4pkw+g5Er4f4tidpnZs3LagoX6UOpaCKk8TcQ9/6gyYeUbcud2MyAQZAIG4zHA63HI1o/FO2TzTdXu0eFmiMqbhl5dpUcDldIK9o5tVfa9uXTUwtlkwU9Jgr4+SRZACmIR3W56FVnUgUWIpu6jPuP+3MHT3fq2qNV/4qXoxVmsaWeeqsaUk3kC6BUtfqsu5S9G9XhnrsrJCx76y4JK1mtrpWZL0RWAQaAVauqOK4A0C0LCyee1MsWZcL/O+VVfHlOoapBo3HoiEXymaGitJz1ocEQYhtvEodZijhLnyrXAh1uAACsUJiZyJnDbilljCeZUXs5GKlMu3BfnBa6h3mvLV16Tt5gDiEaVL2iE0FnwFgoUQhBF0apkmqiQIStgFuKIpDRASOQHdzeWpQJg6W5uy2MiRhcDt6G5qZUPf8/C11VSS+nOsZaZUM50dMla8A6TF68JkLs4xnoB7Pa7/0ztKtmarnYCuIhMZXahjzI84kFIFcSRQkXCUTuEOQzEqNQeSpTAiTTVxIUUqFtToZgUALAg1A14hYNp1Mlm6D8e96M1VbCvcaAN1otRBSAUMwGl4OBZ4O7LnbE5UeJW88CxhS2cCggFJaiDAswsEEzyzhb9IGtC7MIvD1yZac7jD1/4FQzUupIwH827S15V2KRZBiCzQdiAx/L9gJqRMY6oJiIUQkcDZ1yfAAsJKqbAO2+rk9Dcy28Kz0TefJKKnkc3UXHVAADnU2AJIZAI6GdOEsDPEB1fOiNWy9nQrjEp+zm1fTFoXQkRVKEySjdMpChMpX576RU6vKd+7GVUr+VonA3vOsATXIA5Z5LD7BKLbNhjugClvpPu8Zf8az8vk+ssPyjye7astDOQbbuw6MtTjvd/YDtAAAOFEGaBCFMEtsABOhexXosBucafI1DED/H4I/oEbiwp8XcreI2dYRxu2OxZJL5htIy90s+TOIhOM3M8PoYc0f+T8jURQZ7fgWC7Xwqb6slagG1uCtKWJDGIFGs/5K2efNZLSnwSD1+CyGhKubjF94jnf+okUj+jaWVtfsZRFd81HbHNKOy1/VrMioQChCYtzeb9mC4eQUJPSPR9ceAPbMocAdeQWNgRvHnL5nQxRih0av7i+YGfqwqrAw4OyJ+CWeDQSgzVbmJv85jgo4JMUy2F+nAtRYZ4Vxy7dVOqUC5RIEDZdyzcyMmztDxhtIz6okK1CkMcbSXZaV+UqW6G/0v2RTy/bNi/VKGOJjyqZsq/B9l3lqWRZJxZzduoot+d6jV+YUA0Nce8NWNs1B/k39yX4oZXab7ZdpoxAdmpXo8BfADAKFvAw2GczpJ9cpYWJ+aM7fJoaER0MammK56vyBlLHGpPgKJlBRuOobjn4S+8ptYWhdicutUicUy4Op4FE9FQDZ7YXapPbDg6iVgg9BmsSzQ963qVIbaOJSpaE6nIRNVsnN7RT6+zXdodCO489E5xTTPp8tzIrwzFgrcBb6eqe3tKPFYUZtVTsAI0RoxHR0k5bA1/gYVB0NO5RpfSpTp2ci9k8fROZvBNdunDhyigKX2NK2orIiAO7LTUf6ay4tz7ZzyjTEPInRel+3/tu8kooeRS0adBf2IXMk2LVhRPxLntg2McbiUluRkvlTfeSTQohjj5IxbcPx5KRbN8aw4yNWduUPlhO19y73Uf/i+t3eTP51nk4UmmHGL+gYXETAyUla1as5wqw/iOZKydhN7Usn3YNucJlGJsn9/PSq1uvMhygHOurEegmcRDHZjx3keNNtWIY7d5/oMCaXyx1ELPdP0TVTzWNxEg2uOT7a6Ee05jGAy9x/DObKOGhcg9dqBJ44XD69tpI9PwY43ZqO7HZC3oUE6VE2eM2rKKaK0lCaO1T719iVoQHXmR/mFEp3SVtuTOiolXzREqJML9aPvyG4DRNqXdHC8aLiXbnUV0f56mTPk++ChVGMea8FVgz12w0PlOW/AGbn6jLdZr0k8MSnPgBG91n4rLFXupayKrfU4KJS8R/5SxC6gEw9VUW7qF76SewGQvAQTvsORTqzlxtnBiUMboXiU7BbGXOTb6WTyHgrEZ1Hn6WeyK1qVFOc/xETTv/TiGRktmE/g74pym0nRWcZ6KiVEmoAL1smLdq4RpfJO15MFbhNMItWRJ6bfqWVebAZy8j2XrN469dSCNjCTthhaFVDx6fhL2SZmIZQN4jl06nJJE1ndwOsXqbFcOLKH5Jd7L+LYfs75gOuNgo2FU6VRfItevtUZ4RJIuIgEhW51Kp42roo5nTQjO3xj9VxPFibe8DcMNFfk7O/w+EjZxRqbVf6oqQNLBsce3aAXPFhTuMhnHkQdQVRWvwvIp2WCyD9SUlTH8/0tzY0i3Jtprq9W2scuPUSm0yj+bTmaXDFLh2MxRhXHTEljfEJvXabT8aW/PAbEquVqNyaUkKZr18sokkiiOg2uh1L87B+Ufs+F1Ftk8tyPD9L+iPPfqDXFGkgKTSyTDOMnaWpMCRNCC5Rc6IbTIa+KaUbg1hdkz8n8lV5SWvix4vzN113G+Vn8JyIm+goQWDGVwfecqyTHyJecR5DPRYTZ9pTyy3unNXCuQGVUpAuF4KPW3J/lpFYnzOO5jr/hpU+RX7Eoxvk20ijaMJlt9uBCLQneR3G0ZhCpLE2UAKvYa6o6I13eq629+Cx2Dpuqg66Yv93nXtu8wa7HgLITVsgk06IqZbTTon2083m7P9Ftq0SIIJjY/fNJv9UyU21FMkgIuCM0KkfqIanUas92ouM/ZU0=
*/