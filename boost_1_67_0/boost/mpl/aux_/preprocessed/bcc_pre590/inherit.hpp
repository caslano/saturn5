
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
PhD1gbbV8VuwOaotIheFfC+0j2gvyCS27W50W59MwSk6hYgj6uFatC9VVWzDrXWHuJRciYKUV+9Hv7IdD0GpJ6iPjvqKZXWvJQdYKzuA79tHoiQ+mbxL9DBF8oM+CFBZIdySqit0V3ahnA2wR3MoNn9oZNGQQ+ygKZSO/s0lOVAyAn7J9YN1zDYaG/X1K77foL8M9KcgtUSHZnZrClKUansId/IljAl38rUthbgjH9KVWrtSm63U5qTSqlYmqFXFeLbePwh9Ko5F8s78OnCwercLjAOSDyYa6oK4ZhemM4DaVf/nRaPI/Ezd3XtIJTA4jX5uKSYhc5QQMoX8Zym80Z7O1uCNwfmas5Q636r/0rXdJqBgJvRc655cMbGhsnhx4/929jXwUVZX3jOZAQackAGDRvlIFLRAEkADlhiiATMT1EwyM2ESXDFgi3aaYsvbfUajkgCdDOXx+qSuAqVd8PWDdxetr0vXdA0VYgLRBEkh8mNr1LTyVlZvNtmKRQmU2GfPOfc+M88kE2Bf/f3IPPf785xzzz33f4b5QyD7qOqMKj7954bFndMq7cNnoBYuPLFifw4ab+es/IuueqaxakRCtkEexAWr0KeUotU8Yh2fDNRkwKrbhK/f4KR/C1vqyH43293DHrej4dj53xIK7s5D98zsZkud2R3Z7l416KSo/SKq7e6ZbcDXokcUG7vbbgs7UTEm/q+wna+qRBVZLdXGFmVNxjX+e+Y979d/P4r+C+0355j4gS9GLAYS7DeB36J7MW8Xf/PDIZ3MA4hPoiPLtwullLKoC1+YFHbTk4YD/A0RbqvAj1M/R13RycWIqPlADwTb4evA92g9jEGxYi8MzPrJZNx2ks+6nVDIqmv0itBTd8CaeuNOqT+ByHegKMEpDvBgoaHE3MMLC03qwy4+Axs6XI7xDsCW/c3fiS0LhfmxkHSc2B60DiQQ6jD62gkVYy+CvQFMcPb/dumau1e8kQIR51OgPNSrj3Yc0fmiH72nA9kIABESL1QcNbqvrxjbMeWrxykkA0JER/7zjkzYtK9Bwr4cauhJngkimq8mBY7aInFqLPHBWGKj70d2xPt+35J435cuSej7jT1DAoC5bwjdiOtAm7digevuiKmEm5/LHaa+IfxSkGbQRqqCNm8WmcYomeKL2DUQyFkSssGXQeAsngwYWNP54rq5pvXkHEkxIm3pgqf7zIY48K3kACU7l79oK3BRJbcZ/zBUCFAkshN8XYHwsZ7Ikt9grEWz099wT6QQCa0l7AHZj0/5YIjGiO+CVcRScTmyKbQ0i5whdJCFb0hDM5eRX7anYXBfxsyC1XP++e+HdLYIQ4afkkfeP0UKW+PVPv97qtbKb7pUtV2maltN1a6najGk/6f/A/vBmiz+0W3JzzuvX7jC886Uv8bPOw/cdtnzzuMnYu8jktpegRSFV4rsWFrDr3BqS+w+/mP2O2GZMzvB+AofAFQZUcKe9Th/FDYXykIQV4BxIAmh/yz4meSm8g+L4zeVduOm0o4ZDsoYh1ruinhm24fbB414k2gHCcwe4B1PY53pWMQB/FlOrfw1/qxyYqP+CX4Cm2cbXUmuYb2L5TWs3biG/cFiuoZVb8dGJKnUNL5sM0Lj4iOESKfePxGxJZUxrGg5MLKiYnXzHkQ9aq29iW3eRL+UqZFmxIqzhCfTXvdtbsMjJf9mWablcF6r8fln/DTN33/Mvbx80TF2rWDoVwkAA7QTUWZqjVuxwBdLRup0RZLwH2A5T9AaO0lJIbn9eJktUELkyqE11pqjx2mNivl7rNZIzU4V1G2M1tiDJrLPDDjx0641rsXPLwokP2hEpBfuvEsezho34OenxZIyNjoI/apAHrII+ou/URA/Zx3j33w70zKKBBT316FtwZy+0LNF6HTgl1CbKNof+gcK2YohO7DuQOg5CnkUQ7Zg43whhULWUi5svT9URyEByoXdC4Q2UEgR5cL++0L1FDKPcuEI+WU5S2AcN7+LY1gZ+phC5pYg0uto54Gaz3Ze1h4QRUoxznv/6hwx4fvco084ayTQ5fsWs5YG+HFvwcWN99XUcvethhMJPBMPFbxLJInlWCwxyRofPvVaBAxSN8jSlZvbqAX/9rXTIj6p8lyovKTgYv2rLHyGNZ4ntFtS7jpHvhMY+R4J6dsY03uaulsuS9+eyTafj0eTeN2ITgIzUzsJ19s/X9T32VF/0riSvFgNwG++++4zulijiMzI/3bRKdco2qHzO5cZa7QUPxcsM9ZoDy7ZG5bRGh1PdSDOH//ffz+k73NQHeT4xjvQYUUkQqzp5f5OPb6isxdlXsp+4Zt4//zNoSwoemEw0zK63If4sTTHy+2qdvoTqMLnULdz/LEJHfnkHQHROW1bG7ugHuz+RBfCoVzWmrYPQvjXd4i+dkQH4JNkwN1nPhGnBBEmJUGbpp3EDLV5mWK3RzG/T4bu0o7oBReVmys0aoef37/nrB5pd6CvJwSKgnRYFv9sfqalfz6jNgZYFNP6mNaEWQwZUyQ8OD+ThAp0hKNtx6CArMoKVbHzodbWVotY4by8+ISuRtshUn3ggPpAqyhXdbczDetRvZ2UWgseMMqYBL3O341Dovi16EnRkU6MObufnmiPUR/oUh/oZtQb9OxALVaDPSGdnst0GenvOkHp7fLzJGRXd7+GY92qRjEo70gF3ku+gF2U7f1R7SChVaFn8woqsAL/YzuQjQQqKmSLZOoH1wzqw/LfOqiz7e00hCLEe9cJvUr27f8xGB+xLIqmadpWzBg/26Q2/HK/Je3N6C+xhoKjynfQJAuH11fJnt0m3WKmRX8mdGHGpKu3GKpKmpw/QhVktkFLqHnJyJfkKMv3lQlZvlLk8mvaV5jcn5EqmIn4fOlfhvTIeasySYwihU3Ex3ibTAHfwEFfzpdbOLti22lmgqdZlGbGzWkgmXaGqoLTAd+676wulkn0DM2wt9fP836N6zKDbT9Dw7dlD2HUi1F8E8a1xlohSJkkY6ZBaFiQMAgfPmUeBBPn6vvib6icoPUwq4skT0dczm+4NVPwVpHgakhgKATX58fEfkEPxuTG6cGo3IG5Xb6Q/U4ouq5Agg9oLYSXeVzICmqdizvmy20+bs/PpOahBbkkO46x/zlPsOxYrF1r2RCL7RKxYzrG5TRKOaDlTCz2dRE7rmNcw5aXhBTRsjbFiH1GxI6PlTxBMrOjp4nkXqW1ELAxJf6uSOyMJU41BBCpIZloCCjyOw0lAESgSVdb0NmASvOo7kB2VzNBssgnBYVzMXeGumUfKvZJCFKfb6Z/yQPJ84Qd+ny7ufBJ6vPk8C+1eON+C+yUKWwH1sGWOXw8t/MLXSXvmPmr7eHcfEoZvoE1UoqlDi3oCvj2n4aM/MR/XUCMkfH5D7g2xH0RqVuaRGaQIktQiiwpVmktEnTPXsJOxbYqc1m5Q/W6+Me3WNEFXEVAW76SN848Qrgl6vPxlOFr2BasPX/lrPBVhKHzmh09JXVswb9YJz2NN0YUT4wyoDYWkFzvlOzBjpRfcofzq4ayS/MrTevFVZ96RGoqrpx/dQqmZNW24PoR5N4nN9+CxULGTMLEbAlMDOhJF+3WHCnBbt8nOAuFfrAFmVhawySENtAEc+LP7o4xskUmRjZ9DppSSbpGub+/BfmSuntrnA9JGtVu0KhOobrwHjDyLNrdBXQNu6Ys17Z3UVu8p/kP3yCmMlYyIcnOThrsTDKhYBclbjsqOBb+DkLGKln2h9EEPrAzOR94VfCBtIY3kGIk5QWfIijvElG5X/QJWDfybF8izx4/m3h29DQpNipCEaR323IzzSN/Z7Y8Dogs26JHxKyKiXzktriuRKyUs+8O6cmYy9PLkzKXryalSupKn+5XBHNJpwESYb/+Gkh0ja7rprDdX+vGPHiumL/MfvWs/mLnU/uBf5hCT7xKDKZCMh3JWqY9Nkg+DtOe/vRvJAlePKvrVUzDVcz/xThAiSGaNjdhiP5XQ8IQ3bMIr9OG+v6dBhkfNhFbyc2h4Oa37jTZK/42N0Hfk4yBoIJj4ztDMTwixEDajZqGlibhZBiJUvgW6XOY/NXNEoSGFdEdjSRz/ZzI3BhWd6bfFjmuR1r2UgZ/VH/cS3oaQ/8d2nyH1CrlQIiwMjlj6BiO8evn4qmKeMQnczIT33L1TUQE0JbXqOTlBimTKufF5lpSQj+5ZC1NuH3pgNq/U3QnUjvLEh7PdmDhqi890rKPasliRI0lZfc7qnwBXp4DtLiTbwWS3J8mB6MRU6nLMySTIPKuLrPLfJPkeUrvlgdGER5pc8k7pZZO4oKx6zXJSmrGU5KFeHNGAVX0jVduiEg8z6RZ5Lzz8LCtYjp04fsFwsCisRNtrmK1pcqNRkfHyykOuyKFykZUnY1rlsDirT55lr8Dj45yYqdGWjbZBUKXWCrK+KgeHqOVWGUOmkKnKcdNghqRdkRmmWyoSYblJUVC9y3xvPNieWdFaElaNly2ENJVMFMhk40mD0tImojvUEIxBHlGjptNHH3I4OiWz2ipT4jUDVk22KO6EmfrPqnHmHJLpnCXq21BKcMnhcn4lFTSG8stTeJy7kvM2kH8Hyezg1YPeRE1IBCX0G6Xg7qROy0j/VUby9ismcJ1L+WKLbPxxk3WRANnKr+6D/F7Rt5X5l6J/7wvKzXvLp4DBCjvhBocYuQpvOA9ZYrsvObe5eP3fgZU12411l6+r1Txs9p0tjJDXJHAlpNLHmhQx9IMspQyNk8gC7ZvvDBEyiBxr1bmUe/L6ENEBiRJwZ3GPK08fYGOWY3k5G9nVE/bSt7G5dw+wT/fkHhrxAiAPbuRBEP3NrYF5cHsLQeoVegqZat//8pNUPLrNUDNdxygYW2mWGIOcbu5qgCcNnbJ1C8E4AAX3BoQX/86azAOsbCLX5ybHIbrtaUJMFwdm/fKJdGx+TU5eX3fimMACaGSEqmUoG9CAkCQyG+J5acLiM8vxpKI+f5T1q7LnDf4XVmZFj5vFmmdlppu9ZSFPGOWWRcFobi9gE6mA8t/xWIpsiDqVwh/0DOUt+A4JXa11tJDBwbElvLxpZy8LX80gJjWe4hYHudP/4fT0l9SY+Fv5aLfeblnXxzdU4wwOrcAFCzr0wbgsW3btme+sW3btm3btm1be2zbtnnmP0mfrKzrpll9b9rZEV6po3xb2zOH/X6JnDDK/B0zAranYgjl6H5yJ6NumQzCcJejCEUp98Y1gvaPYbJztwbRBl6T8Cdy4jR4JsljsCB0zgq8HyxL9hN5oTfoNy/PM8ivHhu+ZV8euqjHpnodQ2hd+fcbjBSzU0KCylU+5RBR+ME5JSbzvIHn8Y+98tpMvQfFk0QqZx9+0tBSRT6JDC6j96mMD6XvEyKDaiq7Yo/s2HH6FtUoHkLx1JEbVwSY6AG2UowhPk612DuXtSYMqRjyNyYxMo68GJ3dENK2vZuKBylpbjm0zYABVsp+k2dKK4NmPW1Qr1AZPeDfHzR8gKZXKDgbaYNtUPzBPrF1jk3CBnib2yajyjuABmA32r6LwNpFpsuZaZyRmwVpgay+znh/9LnVOvID1pbYZnwDPShopLALh/oHxZbqZJX1ZUnuwQP37IQY4fDj/dhsg5fR+mJt3xrpRl/VlFrV0sOG2aSBiTILlablRgvAGuvWaDrIilwEar16TVqtuf3/MLd7g3eiOGvqf7fmCg0lh/NZdcWegplEaYNCy01GEjzVr56nDv0xfWF6fKfCUXIHobvqcRN5Ue4+3z4ySHa2YD8L/EA9McAOxm7RA8j7QP0mcFhV/ykP8BLd2UAo805mlGHUSNqGL20GoLu5X5HwSY/WK8MojQpgJCDG4Q4APfKOYJMRXNkV+3aU2BaydJ7dFWuJvSj05tX1Zv+khapABceJXuCimfhI07DwjLsX97jEtgv2NIXKc8yGw4av8XeI8LHA5zNsCYJMn7u8GR5kIkiCI8GSijI/1Mg+dOfsINONhHl6iM31QeI4bIb2/SLfInPzWJ3dXWmEgbRNjPU9btLvKX/MO7MgBTtRhuM7rc9mkshDC3pB2Fs/4ZtF7Xv2j9cNmI7UEonjCdcnJLrwtdiGc1csgdE8w6R60l2p03pf4tGZc94Gx/iWBuISOzXx5PzeIRSWLNOLkIf9fpTRPwG9xitiVMBq8GdX55hC6nnVjlvAyiFF56tj+WD4Vq83IOVCg6Jk7969fIuSQthza+vW6OM3dq2ovPtr3rt8NviUlY144uJ1Zb7Yk3ohZ6ndiZVE45Y9eLhhN99kG+rU1oT1tbTtf3o2fziNp84Upcp2KWNP4v1T7dF8M+bB+ebgIfM7ZjmeXa4y8n2DG9uN0y3yXJkE8jdOrTFTav3GEV9R94ad8R45+lG0h3tMFJ1MES/TTSkb4gvsKfJAUxzha9kJmB29vLb0idXMq1Ut4o3XzClZSat8RuCWqtEjkJdb/lCx/MZq8c3R7NOtUXvQfIytVq1arVzmZ1AtN6GuusUP8GPy2kFdg+akH93RQ0KVZABz1IlglE/8Ff5G52sH8d0doq99H/GdHGKA34UP8W3YTVxCELC9rvj6uYSMx2/Mg8wJQytS+Kkxv7qIznt8ogRmkIXviz6G2y0pbJ3fOzX2Upthns9SKeJzFcCuA2xWO1aaO53KquFz1sjgxWdXGtAIoLNLrwms7k763YxZSEXdF3d9sBOaCByq9+TqgO8KkUOHpqOquNKc7knCYyEKBCLxhnoYmGgsPK/WMey6Ofo3PJdw0h12T3mYeXn4Urr6jt/Ev8f/FM6Uq1GAQkMcwXlv0Az0k0ppBMD80hdkWlO7f0wavdp0cq/JQLWD09v5yvXAp9qjU9nF3MeFkgtR9RpsqfL9wvcEF+INk9PaoZ6ACzi91SMp+wN8PqH8Yu4woLFGuJ/LF0x+YU+c31ESt3ir+7EN3QcJRN3HJZTx38QVqFgArFc8rFckNJydPanv6vHp+fuyVbLVe9gl6No2QEfLDRllmV+3v/Hy1vYUYMyAaLRCD2+/5H2DlC71FfMaSv1+dEkGmg7k+6PskdqMpFV/wTh8qdQv0FzBsavp/JXImXvEF17FTkBbjTtO5kJUKqvRTq4xenB3GNqXRJ99mdhlHxTjc3rb4pifazWzbzAHpVtxlhlx4zl/6ysLC/mBBmMqIqb+Dl4ErnoH08KFcJrvjW7NkolKT48PRFCWHiSsd4ZrF/VOlBnoz3HTEsKrRJ41BNzVjwujs4qe+WJMnXo5Ym0HvYalbWkeeGmPMaSNP4TThHrhgFx+d4U77mLsdoT3j0yxEc9ve7eUGZoWeAcchpHLEILWdg+xZ8SOVD3wBYlLBW9HXyM+PQvwL/kB52yX4qdLc4EmKb/RPDjmeeUInKyA113daWbMPDXLK99Q9tch5sLBDdZaMaVnG6IvPlTPqvk8QgE+TlI+BcoyiAZV/dLpycFi9OsvVhmhk+0US1Yx+1T87frLvdjJKPtB+R43P4CqHrKcmw8CPmYrmRxXPzqcHJfhl+OJHuTPAzAcmutJjj760h50NYmOy63h31yk6hnaDibfCxQiKCxdGYTUeWZ7ljOo+PQFCqiY5Uf5iLKuDJFzOC8E44beUdIGDRuUVT2GuGPX+wVKOcv0gh8vooW46QQPXTeKa45R6dnkp1EJmq5GysMsEpNb9uF/bq0ceGkObVOgaa+f4bh+Fdc3uHdk6Rt2hgySPf0JwPNm1VjA8qViC3DLWt6EeZaHLcsH22eVgYW74y2Uv6V8oRm8XC4WBtOu7Jq8Om3QePOoJrp6qIX6BvlV4FE6RTXr1DG1NJ3NJeueput+k4okXsebDAlDUD3vH+O+WV1Tzy+haQeva5rM1mywAooHWN7OWfvsRil6dRrPUCSvj8JZg0uRH6bM8sKuHKbGPaoCGQ0gFnYGjRWeltC55RbDy9QmAHwo87UXjmP5J8ORcci9leOMoe6fcCdQwPw+lFwqoG8BlXx82vuNnm+jM+hHEYjgmkC+QsyRsvPytZRb9qqVbPdtIM3+9R3vt/T6X4XT9YicblJeJyCatDsRXcSeLuPtN/tJ2mZAlWcWxlzkHh5HJ5oz8+tOfU++DGYUH9n29ddipgEXwdPd4o0Yh5KbVT+5uS3yv3pHeTNkAwSiMOsENq1ihE1A6GadCuydVJcEQesokXc6aPYBAyEXdsbXXOu4emJfnJSQJFEQof9aZc212IRBXiOSkR80a25czWV+WdS9K73ywsvEMQ2CqObYUx1XF0w4VgsP7yFjqEurHyDN+uPSlytEgrgAhWYc2mYEyuRr5DUPIlRMS1xWzo1u6ITaSKPcb2cEckRPMX6Nkb5o2BnjRspPuzIHEqFpyJb+IbDFDs4c+6yaasJ4C01vHo8dQlZLHxqnqjFLOep6Akx2170fIU9OPCvLbsWu7IHnTI16R31jYNK3LyozII7Zy7m2az22klF3DgZMhLIm6TWiBGvt88hZfEaFsifhcRVDuBXg3qAHu7qmtsvGk25f8ovQpw4P1jReOMUrS8TwPA3uGsbEAldPyIK0Md7STfvGaObu/MsFdWNcM1E5/899M1Z7YDNb4qrojCPs5XQfprYjtOqgdoYbfNJ2PtHsRWvPnj22LyV2wYLU7z20bk9/ZOGMkADo49CHS1yAQve9Sh4MCb6f+n2bFZ3gOIhYMRcrtXF0sKoo/akVUSJMFOVj+ZWxZFEc8ydFWIPfy+xK3viQSupNgoVXF9hLUmJarxnt9T39a0wy5fJxiM5EG5ru8CciiNQeqnngg5RD+uYLz/oSxvthhgwoRrgiUJ8kAGFHyPkLjyBSFpAYEhaKwoJmMII2fqR5cpDo+kRu4BfrJOsI3FmMCQu62okI/SsRV80t7wfMQb73vanWQ5vvnonsXp046Oi/k9sQS1PcC8LeMgtgFDPtHMB92IIP+cWZPeAsgF93runH7kxIVlXayAC+hLFZK5Gl5Q3XLziM5eEl9EbzQA4UO9+7D8giK9tRPZJhVDV+a49UFoZ/E9BkRExST0YlgVuN7hJDikzVGZQMvWdzGc5hCtEP8z/JfefzYo2m+e3rEqb/YZLYRo7ZVOHiktZaK8OkFGvxb2AJw0hSUyVJLuiMsiPQbb4tnz9xg34zpZVtzlu5fpA9bNTLU2eASjc6Mh4kptIKkGloDLNkY+U=
*/