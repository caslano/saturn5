
// Copyright Aleksey Gurtovoy 2001-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// *Preprocessed* version of the main "inherit.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename BOOST_MPL_AUX_NA_PARAM(T1)
    , typename BOOST_MPL_AUX_NA_PARAM(T2)
    >
struct inherit2
    : T1, T2
{
    typedef inherit2 type;
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, inherit2, (T1, T2))
};

template< typename T1 >
struct inherit2< T1,empty_base >
{
    typedef T1 type;
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(2, inherit2, (T1, empty_base))
};

template< typename T2 >
struct inherit2< empty_base,T2 >
{
    typedef T2 type;
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(2, inherit2, (empty_base, T2))
};

template<>
struct inherit2< empty_base,empty_base >
{
    typedef empty_base type;
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(2, inherit2, (empty_base, empty_base))
};

BOOST_MPL_AUX_NA_SPEC(2, inherit2)

template<
      typename T1 = na, typename T2 = na, typename T3 = na
    >
struct inherit3
    : inherit2<
          typename inherit2<
              T1, T2
            >::type
        , T3
        >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          3
        , inherit3
        , ( T1, T2, T3)
        )
};

BOOST_MPL_AUX_NA_SPEC(3, inherit3)

template<
      typename T1 = na, typename T2 = na, typename T3 = na, typename T4 = na
    >
struct inherit4
    : inherit2<
          typename inherit3<
              T1, T2, T3
            >::type
        , T4
        >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          4
        , inherit4
        , ( T1, T2, T3, T4)
        )
};

BOOST_MPL_AUX_NA_SPEC(4, inherit4)

template<
      typename T1 = na, typename T2 = na, typename T3 = na, typename T4 = na
    , typename T5 = na
    >
struct inherit5
    : inherit2<
          typename inherit4<
              T1, T2, T3, T4
            >::type
        , T5
        >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          5
        , inherit5
        , ( T1, T2, T3, T4, T5)
        )
};

BOOST_MPL_AUX_NA_SPEC(5, inherit5)

/// primary template

template<
      typename T1 = empty_base, typename T2 = empty_base
    , typename T3 = empty_base, typename T4 = empty_base
    , typename T5 = empty_base
    >
struct inherit
    : inherit5< T1,T2,T3,T4,T5 >
{
};

template<>
struct inherit< na,na,na,na,na >
{
    template<

          typename T1, typename T2, typename T3, typename T4, typename T5

        >
    struct apply
        : inherit< T1,T2,T3,T4,T5 >
    {
    };
};

BOOST_MPL_AUX_NA_SPEC_LAMBDA(5, inherit)
BOOST_MPL_AUX_NA_SPEC_ARITY(5, inherit)
BOOST_MPL_AUX_NA_SPEC_TEMPLATE_ARITY(5, 5, inherit)
}}


/* inherit.hpp
kAe/YaaihM+6rrmiLb+zolWyMLdv5Jk886IKGqpK1QNFengepkU4LSspQQBVmvtVLXV9Nw6ZMU1ZoiyExJHBH1ufV6eKkA3i3MKEB5zcaSmtr51WaTxLxmWQgFWcikl35rWs5Hfq4XiMnK1NxaxckxpuHdPczIly76Sb6mLAOAblQuDvPP2YeRu4ItZjb9pbtc0cEqZBOEc42puCPtHRwecKrxhnFjuTcfYvehnny0ypMfaaKb2xbDsK2dW392fpm6bN6wwwiCRRiM/oFuaioOjltoTDLI4zP+mNdB1Uq/oH2EPUbKxIwEazeph9KkOH8MGDEFB5R9cRqrtQ04Z3p0L5NE4XaNIgXQVC6uy0DZSiKJn+W55wAfBsriWZIwqQPTSaxmsXJX1v3IWCkkDT2o8Wuakef3Nmss05x6rjIxvDaDwJLO+8WamxITBXSBDHldJCkuCkpXjIpy226bLpnFlTWVBlEAqw+zm6r5CE5xqUZFdCU6P79a8yI3XpbkmdjwLVqd5fiIuHakgyO6dnIHZ8Y9L+36URXTdvdZQjNAPYdjxWnZWdne5WIgekqEZTpvrwynFQ12nIm68SJs9gCsqYfGxzJuZ53DME3BQMk5orNuu84WNScjqjGAPXPcRxsYVpa7m1ZUl2/UNMMHII9NZXnMsFcxjnEgNBJGHd9IK+SNOSXhLXxeq4cO7Gs+e+22cEfUFV4jQmbKhk0o7pUaOC74/J5WY2l6WVT/bzY0muIqrbwvUZzi94M2QEH+CtOljM1PKVEnJPXMVjIoeuZkdXcv9KC2+eF3gqZaHfzIS48ZA5GULuSjrAfc4l6CELIVfPe4fLZ46TO4fw4B3BFHsAYGEbLIOW88FBJJSZO3UdeZwaVULUhjZcEv5otFsirC1MRO2b9jAwzFlKszU1fq3uQifru9wda/X9ZLhjBkGphLc1Dv+R90BPAxudxqTU/Rrh1UgtdKcsqTWaOd4dkJ3CviGn49h0CGIiIGBbuheHAjrwyTlKIZnk29RSXPoW52h9HE5dFKcqWwfzBFLC5hnqmBwy0y3flLH7HW/8mm0IASdFlKVUI5LXYDRD4GhAQjlHsu6GJFYXXzhBwpneNFWMkFPXgpcjQyoL0ba94ybNiRMcIQWxkZiKIolEh8exOmHPnilx5ATg6fg4LfY4iZQcC26mpWRAZhosF7YqbyVl+qBqLbvQtBiqcBRoMsu9cY8B3GnzozaLeBoaTgJnl4mz2iyOxs/PRHQjZt1G9MizKLS++Svk3inkH5JhLXnQeyIMlYHr4sOn7KT0r1gNALPjhXW1cSvVV2q76L6XocFfNCEjns6vqjECLMIKlIi82rqmyedYRjhXneVY7h2nqTntpVKdhfXQDCWcFRyx+f23I2xBFh0w44eiUmJmnlOkezRvqWZ54yW8YA3BZLsRsDTitohy3J8tMRWKy0f6nCQzjzWOaVy0VGTZJOIknrxsgszQEYlSTD1WSB+sdPVGXO1vPpt9tmrBrx0nPuGxu+sXh+cjDylMvQnnx/NTzBg4SEAqZqG7YtGL0QpfUTi4AX249ZaU7nPRZQJ3rC5ZbPf4B0YfnnnJXzlGo7AXLhvTpu9wQHJGPJBlyTgMWonurZ40bSM2HyUsrUzGhDKh34fAyC3yyln9rKo+sx1ry3HIXEcQsIfIYmxP+jrSMP4XBaLvvur4vZRNgUQz+/d75R0qfIpNenkoJKxj/Jq5xZoUDEP4dHTbWAd/ch0pdGWyb6fq3X8KYNA1MLm5b3umcFevYFgKXiuHRH2iS9T2IevvDDF/3h1ckUiKN9raoLbvx9zXEORhL2kp7yDk3lFQ1losoUkYG3Sba/QkQ4Sh1hJNOfwwg86noXZY//5Cjw9cEUjeaYiZf5JyGUnZJddNNTQFDVCKcRtxvDM5AmcclCmQ6sKoidxGD7lhpOQoIe9SFACJiNq8soRJ1DJcDxf1RWYu33OoupyWUq+ZWjsdSCSEBhpW7lW4cZgKToayl6583rSdpbuEId4MTXP5lUXhrUDkNqILvFulhkkllYzf1yavxnxXdbceTqfq1Vx4cz0IE/IAwAmwcTE0PehicgYB/qKiim6OpA7/Ffvp/1m5Y4sBkv/vG/mRWjGErEOFUtpzFpXmMddhMjKHecOEtWTF9eeKSKbHQCGQcOvI0X0HBFlZpgopgtxXmJElw1MTuJWVuKntwob2+L40xPbZ6AYlZrLj+bI/obE1vhnRbnWrRIOd0QnOwPHCb6IcYFl4LSqcWagKaLFqnpBt6O1D14Vdgmx7NwLG5e3MF2PFOhNtZ5OOiTa26W7cCQEtn+6CAmH6AC7q7bF5RatuHr97icqXzd3qI8A3zkjczxi33EJrHRJnaMRoPGDv7BnASgMrFwjza3bTywWho3ETRTNwMimu6jELJq9RaWX2ChzSPdNZbtEV+ZXMZMUAFrnKfcoApno3qAbkBBUChcBG9gwy9KBAIcIL3rcxwvLRFTzEETPiuNvK7ZQ9LQe76zGRecgEHHuyz2PqdsdPcWNjZXCvTOK3ubZ4dncMZNi4rnSdJlthh7z9m2rfGnLqEJ2swMfB244deZ6C1C3XOAQE9wLqRaHPOdShNoQ2dA0AuC/fLu0MfXgI+b6gwcs/wYs1VYbqISG7dMCh8ZbSRowzBfj6PVTM+BqXyME4eH7pbrHDxsv7XTzkrps09KUuBoV3BacFpKGYxicc+RmZuVqbgZuAjIIulwnSFmcMqS7eam197iZPXmyT+8+pGnRwJIQptBrhScOr3JFsWa/3InAbk4wQ9i8FguLJsUY41I5p6c+7qa+/SmbbmmlldrGUKuqIa/Fz9cMMO234mQmW2PjCiTC8wPah1+C8tWc1hIupUPbb9bPhgmySmH3J+kxeLHBDNVArKDP/aaG4zG6DhMW7qsOOE4swPqOgate8gauMWtKo08lexzo+EDu5yg6/CTeI4UehGwN1hNpUtoAddjocC0XLB80Wu9FcII9yPbIocwYDAuNuYqMve1QImEyYgKaL+dTrwzAiGnBre7ayifc2ItBPXKZxHUgnxywGKfbw7Xfv6H1O1krOUbpQSnBJwI4pQTcb/fcJ83GzaD5EN5M0Q9NhgXPUQ2fSghN5IrVVEVEU3WTBO+YIcdB0OfDHiqZPIu2tKGDLdAAikNHquwGJSnxZGe4Cp4KhqsGrw4fGIXOJETtty30Qk7Xo7iu93aRRfrqZVVnuaaxGAni7XdIwCdzbvlDI4qqYimTDYvRTt93iT++JXMELzb6eP7mV3pxBHGXEVzGVmHq3q5V567SeFOY+1O4Erovx409HBeqLGilKAo75Vn6+9fWSKKeTsgGOCAIf6h+BsONJZO5ou1PuyhAk9Gnz0svhlGqmf+tx4YT0lnth2nLu8qQn/q601/y8c3LgQh3RKnHEy0E6YxnOXV7EddBg15NYjB2/lIXNuKtPD6LtFmNWEt1nxGgcXNlMgQXcgB9h8W+8zESl4rY7pZmhUdvwRmvTEI58GDNeHt38Qq5yAPDnFlrhEfSgXgDUSJhnImsZ05MSOUfJO12453Mb+YGVZ6L1sFpgLkRPq2xBcyCPZoCnDgUvBQCITDRs2qSVkRqtwSswKYKzBp87qnJr3r1HLloZicuZdYnIyEiSL2sfCw8/4XWum8uzIpe6HY3im0W48QIiK6A8L5sKMxgAJTXF9mb5FBCBRPV9fEh8aqBcIdjTAouIqAR5P8bvMhFbCf7oaZ0z/QJqET36LWowvtzCizerxgaFULf/7pTAsoqCcJnbWrcpq6u0LQXT4+BbH2OqO5n3c6t290nDIlV6dd0JmVRZZJiEUpTEgi0DkeCd73xrcgWjfiXQdVIWd6XOJS+mdj0kKRYtrMhTzETm3urqc6ppho6IlOZdtHuP9MqKrGhb3Jr0w6SnDd886dwxjvKZ8j3qhM+yuiREW1FwYxTQYahDgd2qgKlzXJu9iD9xkhLlONUIa40lWzMTs7WfE+kufYNEk15W29bZ0zDwdrbYR9bkqcsdLICHv1VeT+fqayHLwiAVdclzLv477khEpKzJ6MVuCmJvNXeLC/OSQ6Y4bYBlSFgcuVYr1k5xGYIljivRWBDI56kTYAioJ6yjwWTVLxFaNam6ojsejCGtxYVOxHy9w+nJMnMdI16pOxeub/qCUaUbTov7MtgUsCSnA3faWqy0elHXOYlinqWakmay8TIvVCaHjFQLdqa4hFK8op90AO8NokH3GIQEsnwVkerYEZ3rUc+xZGCDN00apu1J0+ZCcXdRehHNOBXoU1zRcPQyCi/7pAszaHblQRCr9NMaicJ9pWt16gQNQ41NjIreA4fNRUbRSCfJXR0SV0giqO8+vGnLZddAvD/w9Ux4+egiVKN9WftyUU6iZumOrrP5FirWZgkilRCWZmU+PKMlnCq5kKHnjEbC7Gyc37LfkIoDkhi6T3pLPfVhsaGwX40VPPoLAX7zQ2MjTU5zw24kxrDgMgVf5Vi77czVcNdpjfzYZhnG3jMhnleU3U3bwJs25+wXGMzh6mMxxBzgsRSWG2quiF/pPeXImAXut1usu4qNt7y+s65PMGikzuO7h1EXjclAGUE9EwcrS7Oab21B04KwnsCAt8CDj6GjgKxvgnAiqTc7r3sMcMJzTmvg4kM4eBAJkTiiYqQpBb0wp17Fm+lUt299JIHVsxmp7+IbpPvgO7taJ/KzMwnjjMCb0hxczL2DzTHcH/Y40lX2Rqpze6ZVyXPN/LiGpKlb0dGXyQh6Bc2HGbGadBXjECb8qBSg4RT1kOosTCcTFGQQuCtD2Rm5ClK5sM9PRFUmznFtGle7GnGP0URTzfAwqNUdkSyJG9bnDNilbWENGsNpFIWbNcU9FfZITXoBa9nbpLIek7CrCT++WrfKiCLtaDUx6no3busyLqoYLi56r/ybbRdzQHwa6w5nCHI6QQgW7a6J1DDI79UjVt+lUN14V8YHeJvpviZaI02M38hU8Jv7qqP7EnNJ/815bQCM4K557ehYkNscLAzpvkRsNzJmlQOHOT4t3xFdPx32A3OgyB2xL02z7Xc61ZcSi/cJJu0pVlcavZqmGcKv1jANYSQOR7HttDQiD7MxLQwAxo/ELqliRN8egcT8Y8poeb17OR7oVroy0KmGOKHzC4yNzIWuh8lHi60BumC8kNoBsGx27UsGs/2CVMikKohsfuzXLDic0fGb8HB4VDxCayKq/V1vV0a8EA59T07RDbgdy5CUzB8D+iC3bww0huAhLuOpsdWxZuXXr1J5/KOljAx0nMAYDbfFHErYOPWqzmqBorC9DNX+aMAqsEBkzY8sVi6mVSU7gCdVapbB4mA1pfT0FmCe5dPjq82oF5IzGi39+3LG5RouekHf74ZqQRY96+rdit2fK7bac+l6xvGcWMQCcTFHBkOEgN8C4GDN0ItR5p8PhnjIpCep6M4unYyopazh5DfhXjj8sUVXCI5aHEJ1QjWpR5QVo2HW3+gkwt9t0I7Y+mNOuabOdlufXKzSooaQi9eax2D6aNwChacletcY6IIDHvuWnduznTm+1aj2i87vG/cZiMsrcK1UoODJG4vlPpChTUvv0GmzD6+sYFelM7wJ7UQQVgoIVWJA3NBS5BRRbHJBmkdAlltrzcoVN9GdQYW5cbYuU/v4zwJhBXZN5xr0Xb1dx2IhqaQMZ5c08H9AALqF5gygMrCJRYimgSlwHhRTeSxn3CDlkj5qtxmi0SrlFHSc61jHjgCGm8t7aqssPDnjoG/SIkDjoGZ7lHmE4lXN9oe4c/wDWCfNHPINMC9QW4aGScxhteZhSqMbZhsh2CWvz3Q9QN4q6agOC9OCZRXr8aqYBkro3a+oowAgwztlZY43rxneEV0sXrPQSiYrr8Ampfz1+BwQ29ak3LbxFHQ9dftytZHn6SacFtfMAKMsbD23bH4hXDF1dIt3/i9DCB6Eb/tqLCLOXwf6SAfh+cZwgsDGuwQO9GpVIYakM+kRSAVePpnviaip1aQwKYqADDmuYWWVdaqnaNdFuU2/985A92UhUco5uWdPW2RIywz+EKbLP/CAeSgqurNtX/QjXLGPABUjmTmeN5GtVA070+z8oQiZo+6xFTUou5F8xTBHcoMmnkm3C4E9SQz+73eJ7QyX0zIt/LhdrsZl/gaoM6ven5I6JGkyXtSswsfzo7DlRpHjrVg5aPbNau9+yxnojcW/1Z1dd6bjoxCMEWwz6A24028X1QQ8ojzY0BcwNBU2qQJGoqqs0a7eyjzIzhDGSUM7rcxE4fV3rw/AbyalJuRHmDAPC86GdFqkkmdToAS6mV0LFKWczGs9CzKZHugaaoae5k0HJxFjMyq+Xkitd6DRMNsjeU5jPESo3ljx4DApY9DyX49647ujvvHVS3oHSm6y+h6Z1ua6ghgjakpGZWhisaBGfHT7zJQUigKUN3zMM0fhdd1bUYLcy+e7tdnVZXpJdeZkofu6pEZADM+HXIdAgaW47kFqdi9ZFzMq17eCyd5aBnd6YuiGClzm+zTuP8GhRk7+GLzJATSflBoGHrncx+y0r2m1bcoNgKHC54fUo5LMQQRpNLk6o7V4WsXwOJ7aYyWSZf3Htk9aO0XMq9sMKjSJbrqBZMzlIHkpCxBiuz67RZIusKGcPzmjljwfOzmkgqIVnO7W7CtVbqPjfpCaUoTh68s9p2mQK4CCZkWUP7uhsmCNvxPqJXA0V/qvcaMTvJwYyDqp3YGoDVXg1GWOgaqgIZPqiwPc42PonfIVW7DTpQOioMEh2itmrcSiOBEzotIG3RFO44/7YFjf+ht0odQPaoEff7HgxoNU3AXyd5AZytCuWPgq2cdn3mZFy946jELrNw2araqpPanZrpVgRigMeVZ8vtat8MYU1IPkVXrwEB5jo6CaAqe0pBm+cI9EsGNkVms7a+wwa6KT8gvKRnqqdvV8EtKoSdala6zJNqb78LeLudo2tFvldguTzexjsWD2ruT0Zt9b5e+MtLlnYBfIXXDhhslWfoYTKVgXbiF7KQl32gOxzz5oN5GybCrONQ5ScLLFXGWG77IIrxzektP27wVaD8DBdBEIQxLnKpW7HdY/DlUrL594WjO7MII77MCPb4/BdlXjLSeFzysk/TNTcpd0+/+Rn709HVjqsm7NIbXX9S1HhoKJZF7A80AERml8LcxrZs9e4N0yPzRgsKUnJ2tdA3Ax6qntcBCz5Ua481S7BzagVvKaNI5GpoTct9fNVo2CvXeh7TxsJQTbjZYOVlgJvrgvCTsVuryT5kwKx/CLhjNaLTyIKJki2hFm9QcsIuGySwQPiCLk6YZ7PEN5tTJuAAUBd3Ha3UYbP2kFX51lPtPbM2vAyM+JQSOZumXIYZn6qmg75AIxhSlJkjrp4ndtUU+id2Y01DmLiaucE8naHQ7PR4Ntk/5LwGgkoqRpJ7x1fBjCAhcEGcbocNSOB2QdoIeYo5UFbpbUupk2qGoIdLe0OJUdOWaeYE6Ojc17k/iaDW5agqRxOTGYPb1+D3dzlpu6dbkWqmiWpL3dHo7XDBpt8LD01Z17iJA2xuDMPV4ZO4fbpTM2zs6M2e/07gER5s3gmTDz1mUi2mNRzvCnJKRYbTRfEp01gLosDY9YQSa6
*/