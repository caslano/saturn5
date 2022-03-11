
// Copyright Peter Dimov 2001-2002
// Copyright Aleksey Gurtovoy 2001-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// *Preprocessed* version of the main "arg.hpp" header
// -- DO NOT modify by hand!

BOOST_MPL_AUX_ADL_BARRIER_NAMESPACE_OPEN
template<> struct arg< -1 >
{
    BOOST_STATIC_CONSTANT(int, value  = -1);
    BOOST_MPL_AUX_ARG_TYPEDEF(na, tag)
    BOOST_MPL_AUX_ARG_TYPEDEF(na, type)

    template<
          typename U1, typename U2, typename U3, typename U4, typename U5
        >
    struct apply
    {
        typedef U1 type;
        BOOST_MPL_AUX_ASSERT_NOT_NA(type);
    };
};

template<> struct arg<1>
{
    BOOST_STATIC_CONSTANT(int, value  = 1);
    typedef arg<2> next;
    BOOST_MPL_AUX_ARG_TYPEDEF(na, tag)
    BOOST_MPL_AUX_ARG_TYPEDEF(na, type)

    template<
          typename U1, typename U2, typename U3, typename U4, typename U5
        >
    struct apply
    {
        typedef U1 type;
        BOOST_MPL_AUX_ASSERT_NOT_NA(type);
    };
};

template<> struct arg<2>
{
    BOOST_STATIC_CONSTANT(int, value  = 2);
    typedef arg<3> next;
    BOOST_MPL_AUX_ARG_TYPEDEF(na, tag)
    BOOST_MPL_AUX_ARG_TYPEDEF(na, type)

    template<
          typename U1, typename U2, typename U3, typename U4, typename U5
        >
    struct apply
    {
        typedef U2 type;
        BOOST_MPL_AUX_ASSERT_NOT_NA(type);
    };
};

template<> struct arg<3>
{
    BOOST_STATIC_CONSTANT(int, value  = 3);
    typedef arg<4> next;
    BOOST_MPL_AUX_ARG_TYPEDEF(na, tag)
    BOOST_MPL_AUX_ARG_TYPEDEF(na, type)

    template<
          typename U1, typename U2, typename U3, typename U4, typename U5
        >
    struct apply
    {
        typedef U3 type;
        BOOST_MPL_AUX_ASSERT_NOT_NA(type);
    };
};

template<> struct arg<4>
{
    BOOST_STATIC_CONSTANT(int, value  = 4);
    typedef arg<5> next;
    BOOST_MPL_AUX_ARG_TYPEDEF(na, tag)
    BOOST_MPL_AUX_ARG_TYPEDEF(na, type)

    template<
          typename U1, typename U2, typename U3, typename U4, typename U5
        >
    struct apply
    {
        typedef U4 type;
        BOOST_MPL_AUX_ASSERT_NOT_NA(type);
    };
};

template<> struct arg<5>
{
    BOOST_STATIC_CONSTANT(int, value  = 5);
    typedef arg<6> next;
    BOOST_MPL_AUX_ARG_TYPEDEF(na, tag)
    BOOST_MPL_AUX_ARG_TYPEDEF(na, type)

    template<
          typename U1, typename U2, typename U3, typename U4, typename U5
        >
    struct apply
    {
        typedef U5 type;
        BOOST_MPL_AUX_ASSERT_NOT_NA(type);
    };
};

BOOST_MPL_AUX_NONTYPE_ARITY_SPEC(1,int, arg)

BOOST_MPL_AUX_ADL_BARRIER_NAMESPACE_CLOSE

/* arg.hpp
OvuHWz5Iq29jbobDDwb57DPVGQc0r9IJRreSOktCR/U91YjWww9PCb6KeBHkNrYN58z5pNd9wRvS9MnB/gsfCjOP727nsqUzlaq0dEsHuLvH5hnIv1oaJO7dEyh/xveMHNEv8NXLtpy3R+VhNay1onaHtMhXvuzrbjOo5lgYmTlVu1dae56n7Cg3z69RGLTsToHbjZwiqXEkwAy8AJ/EN9ntFX8j5K4BMLEnyNvXiTbuZs5xB5CLtNW5q1atkKmTPngrFSVPheYJwaPwn1KcWrfC2REL59OmwvPaHRaDct9DtAgP2BxkOjA52FJe/6tzOPAtsPOkG4MfKJ1elB+CM+4UHhHkvQIhep6mCNMRtmeOj3MzMf9pyOl68Nr9XxX3gyRLwQPotqWQmSoUs0DlCW0cE8vs7r64E7RBXX4p7D76pRaWsscX8L6XENaV+dhXnwPgRQxaE2PLlmKGmw06Wrk18X7OXgSth+P7Fv79hzj69U0S4YFw/7Jf2kISKsBd7usmYahrXsx8VlymLEnTRQi5pKO+S32jJb6GafjPE4louRL1i4FB8fs+4UKt2k+aT/HRcvReiNyvzZHmjYrHm8qVppamz0XvNpxafaa7ZkrkI9/mENcMPL0EbreYAesoV/BKmw8Gz9EO4TbWeJRaKpOzIyvbRH4kdq+YK0/GnGStzgsfLF+u2wweH1id2I7vCjPwHDQXEryZ6WbwLvC/yjokayQeC+1h908k37L1KurDSWJn3qvF7DhyoS5fuXpH2oNtTRmXTBrhUC7nRlmIbe3qwbLRSJ5Navec8TA5HRI01qg0lAzqCQ5dPnTGYhnrYgU4DaAzZu996SBx+9GhGrXcKoRDRfrcPNjgmlM0lclsb5jgCmgfWwG7C9QISVaIOChxTTWtNQftjHUHzXGMc2Ef08psDA1r0WPMe1vVufZFiXxocKo4mzwemHo4wj6f20ymmGzHAjxMC0zKVHx0wSGjwXeNd4+OU7LCgfGWTfqK1WFXDmHMlfNgML7Nm8Jgp3mVWM4Wfqf0zXjz1eYzusuJyevPIVoBtn+VtTIhGNfP7WqR7iPeyx0pgsefxPNiAYi6S++ZifcRFeeIg+l7OUxlu/QrDISzYn8lh1b6K8p7ObPRnqxGnApTp8idPw0PiqRDucY425dUwYQFsPZap6chIg0efjoVGtCuViUATvQys7hNpHLrFvIt+CAFSfWFw2t0NwEn2weKbD1vorG99r9bO0DivGOyAk82i2UhCTOJVtLxD+/mdD3YIVlILYUMZuvJQikKPZKLFtujAJkuwrGuwbMMk3BguBDiooTKCLfJVgTytvnirXy52aU5oiPNq2z9Kb0oMfEeureDczwZ2lvhFEOVny13/vpzgJ1K2k0bNsLIBIi7JJ6qxz7mjWLSxT3UB+2zoJfmxXgaPbFegY9t8d6sM7WSXdIPm5HdnKgGcVyx67iWVhmi1nr4jlzByQZp4tmT4xCAs748u4Bac5iwnBIHcGeXqjA+BgH25VkJt5WzcaASqPG2gpkfcpWVKp0ZroM34nnZL1mkVhbSO1C3YQFW5q9F6h4jN9BtGYgAhkiDE9NMaEOj6wenZD7FMr0QxD7xhs56pGuetYbgCYSVVpxPHHB49FyQfdJKjXfq17a53iY7WMgXSrPHhvazK1tlbdCXZGy657Urudc++YQBUAMT8w4s517qjIKZidN5kRgMhoyeKNMdgcVBwbIWH4KZHVlsuBacT57U3VDdOgMyW8Kx2dFbcf3+8OlH9fngLLL35QCcqdpbTZRHhbdGfiSn0op/oG/fIfOu0CgdbrxjUArxDYZ5GtXndPv/A0eAuH99WOI8nfy+RoKeHFAOTXxhg/e52gAOmIV8kjc6YqfZJhdb3cRXzm1sYJUFa4zyY9pcJPvBOhdf5uCNzvDhq+Er+d+9y/7Lx4fdMjoAVuEPz63x8UdUIaAfhpFfvA4HPbLM5YtUYbVOCEOiO3zqnLwPYhNFr9JbIGyOPp5Jcv7FTm06LXbhA/sRaRyvnMuqZvO6+WwXQSgtWyCU+PnKOY1se5fYPKklkeWm5VDFJvhf+2c2w3/wTzym3k+7jPItG0FwYBe4e5r97k4V0rTcw7cj68p3ofzM/s+9xdu70ekI/xHqcxb/6AQKGJbmQtURn+qRAzqyU2WQ76J0HtXyBrvZ0rfmwmwU+XvpCsA7KgTTxP7rXBq7Hp1JAsu6UsKdMMrqbMQ6vnhvMuFltHeRYAW6F0tKCezei94zv5fZdN2zpoGed48PfOr9wZGj5Ypr4DbxmPmg/YC55PiWbvsTpMvyXv+d3YbX8GgGPBk+6POBoA5CDn7RAGTgCL+6nixNsl/WFHDPhnJj77wkwg9jeFCExxV0Ee3h8m3ytPDlQsXZcZZoCQPGqM1EJ04K3g6shxeuTIXvgfpww9AT0ALlZjjzxS3WybiHYe3MP4/Am68R7F9UWRfBm0SkJ1nLWNDUj/wCfJiLJBZqo6LleITUgn0UZ3hr/RjFIHfDv0XoZh90tFZGSvAR0tEa0u533zPDxEI8dNg7fX6B8BfLPyrmfUO8HoiYmL4ityZVROBta0WhQ1uYRxeqkmujxblwO9cBvlfryOKosavGNXbjcdVEflDTWL70wKEpbUK1+1TEA7UKLV46bwIkA87WwJdKusNXb5Szwlen2Z/sTpZyifuq8Oh1cl549EY5Mzz6HaU0rgKUmHmxd9BMPLfnD/bYO409qj08aA7/ztygXAdTflo8Pipo2Uzj7R33O+RpXVaTOGI/YzJJtJuHBy1lafSnMX6hnPcZ1E4S0f4Y7i7CiFu6N0/rkrRs9pcZ8nyW9C/1ikiagvo0OpnEexm9o8K6eG8T75J4F9qq8fmufmy0bx9P4VAlaIpvAKouln9OQc+7Q9AX04M5puw29RfXfZC44XXwXP44bmOoxIJWtDpDga/i+Dg2kf4Ab0fBbUK+c/5PdxUl2ae2F1hNqfaoqA8QGK8McCy9PhTBXchKgG+y1vEm0l3VLN/rgpW7D9EqRlv34Lk3yG46f/48eFlqCKmLR0mK3z9RfCwCFQga0+I7Q/8fyorzF2nIS8XRMaLdrwo9gjI03Sd76rhRv2iBnBNc3f+c+EJ6tTk4FN0ZOBQOHIoHpOQqJ72MGepPECN6wPBEDYtzio603lYS8vXgCqhW0PWn5yip43bIpwC/nHlhf/xLg6YPWQOsesdZeVmAf0eq4w9ZMVwboCLDYF0navKmqElAf8DY1NfRJTaihdakrn/o798m9vd02s6iw8MTdTivcIiO7c1ATRrq2XCrzcRbJSAlAxgI+9MJpIcjBFeMAh2fXkEhCdG0bSKoOKIFRCtsJiMSqSMN9z3uBkm0592ypyeePyMem1nehIPgPPGMKWj7/bOJQZBOiJHddjNp98jLKZi2egMDG6APNBXiwWKS2GiSJOkR2dJPhST9ke/9fs9k+MDf89gQNgu1jfeb5dz2Hmcekv66uQbQaPsz5OzguX9/znQhk7Yl/RQaS8drGzVCNf5CwKmfyRDZIpOcSdOPE0+GbhOJMcjFWINCB+S0iICEbQaKIOKf0vmP/mjy/RQRqbEgk/xA+NVmIlq+iZgYzoRwEF9jCwkjYAnfTpyimftcIVPstP1gN9ouqgduo+DZBlCN6MKitApjRwxxnoE44xS4jiTj80yq35PqKyr40WLtI1IQIXKVqvt2Ur9RWGSKbIp9+JsbR1JVeiIV5olgGFPxgj5ZfcYmqc/Zm//c+ghwj4DQQQ2R5DZ4/mNkri6hBG44fNXcurAu0mquU+8pKjLVQRRmUS8vLkLUNEobPuogpDJ/alq8k0vB5ysZ6TjeemvcP33X1zZs2PDh+Z4rGfz1nvM3W16v6Dj+8O87RjSiF1jDZEg90X+rjPNx/gQWoCUjTBkLLvz6T6E2Q6jk4jnqPmbfgu7ejI5izMHBf3tGfKHz4ETS2x7jG1MG6FmTOA7q+oT1A+qLCNsHhMEZ7WbGh6pzkfoz6g+uEsYNH2UtErlO0f3eBDdR1ue0gtYmvVUa36Kefm0FxYs+Fy+6Xy2lEiTm6TM6NrME51IeQ1qOtqS34RPGt96kt33GNw2ag95nx13xaGXb1F99TGXz/ojtIctJ9SaoSsTmtpxknl41lwA1eyPN5tGIrUTNgFfLKH9DvfwxPljeN7rusVK2eM4lV7smuAVrU6v6+V0omY69Ez5qE0AwQzqcjxRx3mt52x8MYkwIEnGAQI/HiThL/MGyCYMt9ZLlNzXBggkjIEWuVt4sINsm75Dnx7QO4TAciyyWFslyNbLM7Auigj4s4Dy8IeiFXc6F8hJ6OwG79SroKOBk5+TpjoxUo2OghMc5c9z7jjh2BydGzZGAvYZ6+9RIWRE08UQA71pq1Ifx7Tcoz+LKmUCN+i0KlTgK7739EKGhDO9KThyzfpHmseq7SYDZ2zC9uhjeWMtAQC2lhzMcfSbNuwm7poy19HOlF1XN8pCA8RyFJg5vPvT/1KJ0fJMUt87eda+csF+A/WCTcT+QJtoPzhJg9RhvsVlikWUZxjHhw0wZcv+v7AyIUUG/jcqnA2JE0vduHZqW16if+xK23YawQrab9bajK3tsuVbfCw694ku9UHG8/zg2MT4atGf3R1P574P2wLHvkVjn89OQey/9ER6psgvbR6er+shjdtT3K4jlP4/yu7Sm7EHk0UIZeLX40B3aRR06hhI57H2ccsgTORB3fkD1QrwLP8enu+6guzyKW4egSK5Yn/0gTmNsupbHnu12PWUexk9rGAfst2r/dNxPUFeoCnrp/HJy1qSqfypIhGyhkM/FEob8XV45Rf8V6EMrglnPwgFSvw6pSRe2zJLOgEWT7aFeLPo9WacJFiGSiAP8W57A0yP9WAcvI7fdIQQQa4pbfaaeT5vlv5/cXwTfTtkeVxbz63o/PGji+UfxN4u32VDX2x9sFlwJwma5+N2HmuM4UPwpJ2mfoKT/5PmfIz3cjqxUmb3jWWJRh33q9b+L+8P1aUnT6fSLSvCdBH5DFYhmYmUcmrGMUyMUURIRpmoW/jm11ZosZ6qNNxalTkh9AWj+06c83/nFkljpq+fIX8QTgrHRSgR2vd4GZz3RD3EV0AGsLYoZayK1R8laqxd2L9ixWMtg1HMOm8xa1FjfyBGHsmzkSKGyWK2+AeFQreo/0U43hjf9KK8Ivxnjb0bqj9ZU86iPXFmgPNKnkd23QMyId4Z67vNvxibAMvMOo7Ayq5p7oSI7XBaNZtcS/hQSToIlK/T3UXn5VPi3ZuaDvz2/z4DHU+fD/wHvCMiEXXDq1O8p3EXx2v9jmNCZClhlYbSMCC+N7xL97Rybav+ETRM2mUabvKi00aF8obTRpdzJs6HXa3xq5UFYqL3CpKLkOBpVoOlcug0OGKDShgJ5Ht7nlREqGTa8fiyN+YZ2QrCGgnQ2JzzbF2fq8ESBmikzKVLfbT8RDB0+QDXle+ktYZRSCE8f9t84IjY7WwqOn5SOdI7XH9pu37IYKlDa6LR3lMJD8BKRK8PxqlgoT6QMYG6UxOpSSsc+QpI6Jj/UMdJaiD6/YtUUshUtjQ72+SmzPozWjyJhDjMMSJxFWSJT92jLjSFTnSFFb3U8BWE4fBRDKWBMWdMx0nQ9YkS05lJskdq+LRTTHB/r28CkHZH+7Lv29BNitNWk6RjoVXlGyWn3EUQq++DCtJLj8PjDHn5x0iImPEsT+/Hisd2fgN8SQpK2bvK+OuyP9XHFifIQxSd6+jYURIlBWx1vvzb1jPCoFJsWxWlaFNCmJGHJhZvxdjvHVx2PCASbvoBYBr94jTYj4+0TWfv+bFNCKJocXn/+Lz++GDPKn13hL5qUaV11puw2vATk5XNYBiZ26v6BHhqbAt/24gayYXNsCI9aZCuca9m83gUk1A2U6fjxcZowpjILlSWC60+iszySwVrOv0fOXQrEoXsXrywk6JzNCJ0DG++B52m8XEnjVRFYVhfxuIJlJw24Go4LD/FOV564rUczIJ86v9gOv6N5OobqvMwtAlp0OMWeDd4HkN2zJAbgwmJjqXRhuh1z5+VNZb5IrSs4/6QBFtNGkVPycE28opzJ9rSIJbRmQxh4B3k2oRpXhQ9hj5jk+S+hf/cNzBEtkz5tEkPsJBtgZeCQCJIgyBUPMnwsiH+Mj/SJE7Q+U8uXUGz/medjV2KZIqYBH8RiymhLib98TgAGaR7qoOcKPbj5XHGgxqviZJskrrjYJjyyfNX8nlWxUw3xKjSMgwtIc5/oRPkpycRPo9IG86juD+xbfo9XUFfsW/AWyf1r+5Zf49/DwkER9JzLoqwsrS1U7uHLC0ml06hpn/BVg0fxJZZV3Mc9o8xeDGeW2sjyGpg5rrfR8jlxbVho4u04BO7D8vXcF4TsuG8jwtP4NqGqRpkMi7ndJSIs4r5CijCbIsyhCHPx9op5RtXW3KKEn5zkslkeMxt0RsyJsoWlBXXaGvX8Z/XvOp5y+K492w7h9dFF+auwe8ForAXejdEMZbSYeHUhXw71GWXeMYJFrgzyso3MO0oWAYVowg5LZy30i/2gZ8x+0DvKHyjsGXTM6PGFxgLBzDbdydUbdSOxZPkj4vGNTemvU/2NPS4LPLQfAYGztsCSiVbQHXO0ogkXSbSimfQrdPH/HKS0SfEgpGsZBPHKR829vghI2/1EZ+LFwITwgRo/de/fT64PYKa6aKiBRTMnRg1EfILbc4rQ0+cMg9JNXEYV3txsUsjUFJUhxOqymdSHHUUmnX67xv76WU6iv56n/rr05jPX0DUj+dg1z0/dNYbzcer+wbL1/snInbh/RH4lifu39iHUMZjYpVzJSCDA3w1EIutiiL6/bCbrQItcbglC+NYANYT9sAyxDH+xjn7X40TpCMIvSpxZx1ICkSTa/0l89vHF64KIT8HfQI7EvsUM2/UhRD2g68aXLdSmrS9Rau+OQ8jysR9uorxl/P0hzkXW0Yy/ShvzbGG126KeJyTyXLWbefYw717m2ce8+5nyfLSjEuKRL79frKAUY+JTcE38RAmZQ1IkgiWgskYukgYRjKLOn15kiizLidRJkZUzWe0J8vAQjk5j9QeY90VW38U8r0Q93YTk6Dka9fRm0oVKH/k3aTkT9fRTIzwDrJYM5GpRyzra4YvXaJVG7L2GtWG/wgDgxqk+ngO+eGXwu/rMNJhwHavjadeKtFb2q9XiKVMbpFj+xpmUDL+rGyEZfxIL4h3YATyCCUMZflTbHsvFUVlLgTiGcJ4H/PB9/eZDJq0PCiG9VoN8eqRcp8Mj1FSUjQIE8fmFI29gTcyiKUR5iaRPHNH1cNmvKqm7xrT8H4SQyJKr6ZQ+996Wak4w3h5seaFmP5LeSIDc+5FiwknVeX2RMHwUomu1fHz24/LHi15DzoQWaLSh8IwWo1qLhBqwtbZTo3hcXCr2DIWqQ7FQzI+f82VY5RDSS5rLeTO0SjSoPXPGq7yETOoamHQJPAPPjUn30V3rxuEZEEhJPWF8OOpqfLABvgAbZGR7ofAamx/eXGiS7aFZdTVYJShgx/SEFzuxH4SN9/G29BIRlGXthSwzVyCaRWT7ftR1Ip5wop3OBvuQL857xe+ZVDX7H7W5gZR2XN7+7GINq4D0QloccEKG0CG76YbethSiXZhuv6n+Sy65ny0jO+6Ls/B6Srk7nnNCaKmq+/7BgE+d3n+Nxv5XFZJ7wjFsh9qeU0Ro7vYtu+gi1hrXLb1r3Wb0/xI0DZvIB1LACi+Fw+g7/h2IBy/ztZAqCrmIWoHvGAHxLcHcYe02HVsMp/4ckcs6kQuFiJZWWOkjeWDbJyS2GfEL27TtfXHf+PaO5/XGGwjS/JeT7CHrfPyyui1H+HjLm9HdKKgfy18YbXQCEc+JkhGg45QTTOljyhmm9GtL5CmciPzxIDkir4s8hq9o3xt0mAvLYqchNdoIQ8oBpgwy5RxTVI0C9A7yWpV7Bnj9ueJTrHZHpHafP5RR7dO3+CeYd3dxP1OG4DxmyiWmjEY9++agoud9V5wwejd/5CQ0kYinS1hE52+CbC/kBHBDCITmx/KbNSeUyh73cDPQwJcithJ3b2t28REogw+Tytped2+zndfugLUeKZju7ofQw8yzl/e6lSeUTLd3tzxLrPFQLi6w6gAarszNFpiqa9DMulF9e/b4rcZwHh94cGo8kruzUCiHhgxZQweeiQtavBKraIKdNZq1/tQzJlYls4pmHLdJ8av7N05FT2BmOj3xo7yp6AnpkmH/WGXA+0l1TxuIePeqD+YmTFIqZN5GKFSVQm57BwySSnqmp8XusVf1wNSL1L6Io7E/bqLgfTHck8VWOijDW3MMPuz3qoXJ9E+jBhfkvzXNGKTyMzX801h8oK4kVldHWK9BDv3si3pUOuVbhhDIgEDXED+htVRztlkXRNevfgEkRK4dScUMjfdDuCvd6YtntSz2lnu0OcpbVNi0smBUO2J2AkTnAZk/soX0uJWZF/IQlzb4fTPuG2/x0QuneVkhFIa3AUPVaH+xHrV59f4LmUuOs60FeNdwmu0oxOv7KhkvMgTGV27IFOf8honzu0Sc3yhyfo8gKG6dwVHnnKK4o06hb3yjsoCXy3wHWYy8hMYPpuYivlwWuQf4HTABZ/SFTH6+C+GsCGIbyeo5mUUpGF+BEExntckCBdBpEm2rnKabm+M7z+WP7AYysEFDokN6/rdWPTZ0SeZCPH6qxQ7RMCVeaw25VXX/r5xZ2lCozEwwb0tvEaATdaF8NfonJxRfhgUI2iGd51Q81SFpcVT0kfWW8eBTcXkNX74QJVRPCBV1Z1xNHRXTkzlqEZOUz2OnNby2ePo9U6en+AVa/L0ZpKKIcV1+8s0Q60NRwa0JnBlNf17E32dUoRdK87yn5HjUNHT6GYGI6yAXAlKilVEzhvHlVqAssqvVt8wpPvMwf8hC9zwgHBE4YZeKmqxvYaau5AUYNePn87/4aa5pqvQF6dKL+i54a+L6Yli8vrd+gvquSF9f/Hw+8xrqu37i+jZPWN8AOg+wAjOJUeQvwDZU2iq1FtWUnNX8S1VZufMGvthqeQOorb5l4SOz3a1Ss7oGAqrVpaYi4WXtyLj2WePOIKhyT0D20TIpl6CPDXWcpD3Pp2uPsBdxV9taZnacbsrh5VZ5xj0=
*/