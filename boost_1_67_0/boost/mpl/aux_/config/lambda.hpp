
#ifndef BOOST_MPL_AUX_CONFIG_LAMBDA_HPP_INCLUDED
#define BOOST_MPL_AUX_CONFIG_LAMBDA_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2002-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/aux_/config/ttp.hpp>
#include <boost/mpl/aux_/config/ctps.hpp>

// agurt, 15/jan/02: full-fledged implementation requires both 
// template template parameters _and_ partial specialization

#if    !defined(BOOST_MPL_CFG_NO_FULL_LAMBDA_SUPPORT) \
    && (   defined(BOOST_MPL_CFG_NO_TEMPLATE_TEMPLATE_PARAMETERS) \
        || defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION) \
        )

#   define BOOST_MPL_CFG_NO_FULL_LAMBDA_SUPPORT

#endif

#endif // BOOST_MPL_AUX_CONFIG_LAMBDA_HPP_INCLUDED

/* lambda.hpp
Y61OOXvpANx3ZR1Dlkz2ijAvKW1kr23pQNYxvc5tMk7m/tc475aLbyiC+yWnSvqVQuNukj8TzSartCASyfBUaBVZVT75zPEIkgKjCGIuDbcBhr3BvY71uihHM5X/6SmgLMxU0q/BXcyaEDOFrIvKuqLhsgdnMGTH5HoVcKMSaP4CMpbml5xsnxAd+49FH1DbR7IqsFzKilai+Bh+UcC6yuHJakfHNYH++wX91/mvpJB2Aoe+inXtIxAOEN18ngBBQsAh2GtA8JwGHNxfAXfKL90BN4D7X8V6i2kkpdQNOdHsb+CNC1nvOt5VEevawLsqhvsr4E75JUpCQVud0TZntMfZ/kd5w0JG5AKaFzGiFZdeJDnZTe+hjC69RfRAtQHuWgNcKQ3c0VYcrzO8kvVSB13UQY+pAwJ3rQGulAbuaDlgawWjY4j17qY+yCVof7MBb4sB7w5+VQ738eliCvaGVVGp/KFQUUEKWWfhFYMprqbFnb9zcILSTTTBcjHN33mFQsiAzz5f4K4HWaqYq5C0iCI39mTFlRyyACOQeMJ40t05Hrax5cA8jWNoDsXlVJs65iBg3zwwB4N98J6gXJinqBimsyElTEea5NKdGp/bfpT0W5EH2ttsqC3z2qHjfliksPE6+yN5/MYFcuCAW45n+nd70QIZ7P7li8jhvIZNSUfGtWpAEmWRonuR37gWHLnrsBAceao3gxPMXZ4J4jsS+h5Epn4k6hmRNM569z5eQ3TPQuTv42WxyA3IuCUmiRPI/Dde8MNBfDtqWn+2j8hW2ccALTyUzZWmGNfOgL6yRhGV5MDcY+6Dayiy3IKvH8jUM9sYL1Ghq3fRgzxR9nFYVPOewy0MxHjEF4IZ7Ual4nh4NszTbrgcSIt/bm9zCZH7Pylywybkel0ouRloTZGXrgX7//H4taXj9zFXBuSK0gyRatOQehKReox9lILUxhH/VEjl/OtPN5rse5mMKyEnF2xYAkWbiO5TAL0tCijr2q0kHcayqwdeBEpqh3MFpQQ2iNKKbvTPHCfN33/zH/df7/3pbyeFHIzwZsDd1x2XVbnNJreJ/PVym30m7zX0vXvWHknTDwaUG2FAuDa8dm1Ig5PrcQdMKum+w0uApfjPvpUmJ6UfL0lXWZxYYqgsNoqkQep2jzl5dV48hRWnoqgl46iwkQ+7z2CX195X1CA55CFtqh/scF9Ygp7pXTXo32hH1uO7WBViMUieWqXs6GvuA/MF4c/fD2qOfC5fdK/7Mncus0WOCN878UAfugvlO35WbWfHjo2Ic/kHerQnuHva1TCRucKgkK0FP+91T2AX+sPlko9uA1GHbneHtW7Jy7tezdsXJqfJHGRtRm3A++VqHjY4KoHd4wY4fOo56BUR4I91uIeWaE4059ApnXVzbKU40SBGgUX59ssm9ZK2fqxm/XIm4SvmSeh+HgEbywZhECRqu9+HZjZMksImDE8Qe7AcUzREG+1+5X7vMlQFkhHPwQsfBfuBigSUww8jC+sC1tKwbOpp/iep7O2T/Bc/qvvOdfXhISOhp0cMroAVKCkvUzkje7RW9EUDNj+AL8qPJGCJsuNkPGr40YuCT1IuvLSM9CSNTp58w8Ky/Uxyg9BNcvtZfVd4RFLCicwHJOZsug4gCTaHN+diMl5lcvr8oCVF72EQB3iBpCzVKqdM3o5cP79nIIN+3h3fP539jWwui77wF83mUtscyz5+HA0u+Yu4riq6H5VD9Snmlo0JZU3MRrqjUE50TUMsa0sRev2fuu2g0LdV0NKqnJBXb5PXhOUnKqPEEnG7JM8OVcy/z1I++2QcE0dkx4g3Kh8EynOUGL2jW+iTGLyj63jz2U0hS58fs+KwE03yUarxQip5uYebgajazlGqZU0lSmTKSx8jhpgU5UcLCMkCuq8RUHKXi9q56XMrfRbSM04txEJuC6t5J5Yl3a4GM8WiTfZH/jvyi5xeNAP7HE6PnleVgNcMg2REJkE0iUtYOzlJO4uB9izlpRbMDKLNiu5V2oMzzauovfYHmwCLgSupDt2RYiCyLZpsIOo7cDx9/ZGymmZEcHS+S7pi0cLrIMWoQgxNiOdqeE47zZUQmU9zK5POReaFZkjw5EVn6ptCObBFl/j4ZEfbmiX2Jp9+Pbo6qBnjT2u5EuD/PXj+U1gHiBULMGOAQGkrg8uRRI86sZ6k0GHR72DolxrOYk/aQOzF5GpZTp6VArgcUl1yzeVmuecEaXSo+jlVD1qfciry+RxcbxLu1k6lz1JCG7glmnPhw+j9ORGtslCyMB5kRymfGsdetvh1N5AEGSVMM8gdHMYMHxGQX4F0kYpKAhFXavIBLRZRReT0Gz4VWXx305RvH7MJoWqNQxhGErTRSarXd8L3R9fYYlkvHTcivNaU6hcr9Ity/aJCv6jkF1jej1yb1pRy7wsOKdDfNVq0V6g02ngII0xXF+ICi612kbrsiWKF/fdKjC5sP4HHdDttZlj7h7KJCJ2QPcflmpfCOXBnNq2l1zDPQuMhjCGuSbpbYIgOLnwfmdMqAaSdg5JGf5hXlD3AAGzXWMVos0UR1lxR8Xjz2NmqCjqTLsgF31TfZhGFkVYjpFvx4WxewmVuQGl8wUHDzTAQPHBRTwECj2sZcFJzuonTuPA4hUn0JFpbqT1dW6FflOsXK/SLUv1C8wKZYT49WK8Hf5CSH2/SaqXk50D9GS5Kqltkie5C1MJtidK1JXiC78q7DYV32Z9bSlGxXM8dT3S/k9bF5LKCjj5lA+EF7RNqeB50i04/+grhzu8VvIaMCT/rp/BvJX7ye783HXlpRVG2GTHQrWIT92/HfVAyDpxVM2snsf1JW4D8z6lCShjduIfQcXtCdXScAeJSdi2y8r6XkXQ5Om634ppCNgvjz0r1iONKd4uFMSorZmGSHb8Dw3DpCg9x2wDTAOssgLdh1x5GVTwvBFEEt8sGtXRAFYiGsGZm3AI9k3qehy+iErBAzcvFhBiD4Sy5SmRVNobMIXqVS8AHu7TolDYSzanFWjKRFgTQALkNxZkEQyYzJEBnsHL6UKE/DgQS3haASSpYQJ7n7lERY/oE7hm/JYrmT0m/o+mgwqRuW4E5aIhNxpFlwVUDtiMd77tngP0TJFiB+5K6hBUAdHp/uSaAYUjA62LSH78EXH4ptCrMNKwi1ERA65DV59e3H77K2ZJ8lY5tUjugGgNNFzBSSRspQFuuzHkvjjqUZhvDXCmouuCWYrTOstUtQRyKT5dOdSVifB7NarmmNmm2KgsuxtHnfwN+w+CXL+ICg33SXkxZiCjwALcHwqlVS5jF1rjMu6Ozv+1BChcupTBBOJBupJoP0TqbkUVx1n1VhS0hdKLTfbokw6er5ZesxV0Ij+WwG5k1ZMF4WHZPBXe1rwR5AT45eOcojAguU5yg1sJOSfftwhysgLZbUWMaCMh1hXKVi9W7gnnJcJvRb1NoL73vLEEWCIpJMnxpuylIxdivfeaUBaVJ7XBRfWCyO0H06SJi35Abi76CJ5fyvfdBZK9qYfdwLfE5Q0v8H39UVUBkPbvVhcu9igJGfCFqo8/e+B+AncNICjjgq1r4b7vptznKqzmozWwxN7+dunzyZZ3qSZyGVBINAaSE3RJQurSZrB7Nij4kGMSODcN5ejNMeOdJkBvm4/TA5CxkDyLe3oDLjF56La+XjLNdyNvBjjd7zryC9+DVrxCf/AryyazJFZyTnBU4O+VdTk587IDYao2kmnwOSG1dBDLhru/rgRX8PAje/V3zeTBVhP14Ra7V0UGFQSvsZfQyR8erApWq1kJqrdAbj9l6C7D3bDG3psTJ2ZPw1w+coOwRyxLhRazKFbLWBjS/0LcqInYDe9Ci/XViHMMLGV3ACofDwW/jQd2mjKH83NCi6jN5KxpZCzL+2GiPWaf6kfJ5w8h3kbb9cZcU2+XW+FnlG8CbwMQot2Co5dPod8BeQVbRF9s1pHmj8fqmTS5oRlOd5UxPusLe3Lwp1QNHi98AHiDinmzEpdrOd1IkhWa5NdxCUuTPwmP7rh8fgxw7R28Qzsj2J+1CyxOYVJyvdkziWmmK9qiz82wmiOkemoz5GH6PuVKV1HnIiOrrYVr7LeP8TeHfHEBkwuGGND4iKjfTWXGoDZNsbJo6XvQbZha9oN7MLhRqWjNBHz/5tRACNJV5O4mNIN5UUPD4CqSwz9NZFsqBM3uhFv9VgJU711HLnhtInsFdy7iHM4WxSXroNnRs4ThDymzE0SMXUWzVeC7qEm6UZhn9trXxPs9/yFb8djNaiuwl/b5oXYVc5ZSr9GSc/Awp15IWdOGTGI7fjf7a0WoVKNJdvJusk1knfVHJ5sfzbgPP99E+ITl2PU3ubzt+/D4wt+7OA/gfGT35KCpSgdViu5zaoPRQL/yqMcE6/jp+TXlRXHz9Di8w0vEVm9bQWpgQc/rfATi7iw9qTsc3ASh74e+/tD8hK/nPYlxZTXfN19P/yyDfa+bLtiJ2Ho7a5nGv3RIuZd7c9omsx4sAOy8p62GLlI7OY3UrRkVWVw5sXV0F87pB5JR8aFPTMqnAk1bgvN7gwiqIqTewqiLZWwi7ZvMmvm/W025oKoQNsVkOFG7iu2K9tn+glTX5Xb0XXlwOfw/An1cx1ye9O7nYM+dL2Siyb+SjsMauKJf+bATXM9z8ok/JvliEURBckNFmGIM0HjRnilnjlNjqXGStMmSK0Tf79OKPmCGfQHPDgWnjNbBMULONOPTOZ8ieLM5zdDKueEg7jSQ6jXThUEE/GNzeVdqww1/EYhDWOj2o+K0mndzpVPIzJrqXP5nuTeEpb0PCvWdZ5qRGZvs9MFwL2reHBeBWtQLq2sPP3WxkJky19xc0sVUomYZ45oBIDjdM43apD6qo+UBXeJhLYDvydmhR3B+Smf3C40d4do4PNJd7GPHbulUejqmDGMUhODEE2hOXeIocRCvxN6wmDhMubj/C27EJ3hI2hj3aGIe13oIMYg49mWej8L82d5Qe2oZQGO3CpnbCdkzoKJrE7bA3FRB8BH3/d/BRAwq0gYdvnWq0nfkwO+uTaFlf0r95sj0jRuozEMNI+8r5rS8PpMvjzGuLZU/Ws81A4Nbtb9LfYX/bOmiyv0msVprS/nam+B9ufxMn2d+kDPY3u4SxXTO0wYmaDe4s2uB+yf6UYoMDADPZ4HR8Vv4d+JTM+KxktZVT4vPH/0/4jHniSCMAQzdS6eLrGY1vI6RWTmcxnoA50hF7EwIQy2gxbo2X9LerKhmMAX85Gl6HUUmXbjSuT7VvcnpE+QIb7ewhmx9JPA1NF7nevoahxXp+Kt7eIbEHUJeBYjZitKRf9zcCGrz+B9eNZ4iIZBzziBJMk88vxTwi1wCILZoGwCuiTfMM+i2Y7SU3sMdENOxsE2PC1ieeF+RqG0ug14JGnTvHIzm0IPMqWo8ImQIv1M+9dltKPMvuwRT9NkzMnH/7QMWkwtmmZPGYTZjCwwcHTmWsb3H832dc3wLwo37lO9Pl5/grhonGy05H5hN7TnmqIlejmyyjeehPrHzWZtTd+7mVMjaakmCgq/r4gBVob81Y++//ZsQa2MYHLOE51KEWOUYx6VoJvKBlPi9Q1cUTfSQzo0U3h9kJMus8OlvQos80JWTwQEpj1GxvbqbG2cqXJjWmCHi0Kb6poEmAhOZb6lEKXHcLnQOfASGxPmQNWuen1dqaKgvHqUz2llKzvtM+hXwbsXOuYec1hCoyH8VTPfMfKg5gHzk6PuCp20AeUn5ipeNTZ52sPMPVLAtvQCiQON/k527AFj0odEwi24zrgyIeGngjXLBGBTguP7kdc9UPXDr2ehzmbCBKUq+8o9UBjM+z8OaACV2fB6ADIZsBc42IGQuUcWS7AbeRSj5EEEoDIYueA4+KeKelRHF03qBizqBM/NqkSRjIKFkjJEIwV4OkzhUwshq9NamHwan4Qj5/o9+fRp4lVvYN5Uc8o6HPnL1v5TyK6EWOZ2//bs/cjv7IV16/G3N1jbxAubrWNhnLlSWCd3CveD5dRuQpz9kiIe/OE7aMmQNMlakT2zzlmXvdkDQ+vqc+uL49PiKyKxigq5vlq1zmTEYBdkJxC0Y8vqaczxwLx9/3QzM+XfWZTJBYbwMtAKmvkj0jfHuEb6EZzTLnxQSma29/R///AaOqoSibPACAQ0vMnX14VNWZwG+SmTDCwNxg0KBjmdrpml2DRpOnDRC7wSRDViBMPsikbRLobsCBpgurk8eQBDY+k9FcL0OtK5Z9SnxwxX2CQmvVurGAJiYl4WMt8rh2rplBVLQXk6VxG+NY08y+73vOZE5mBqz71/4xM3fO77znnu+v+573ev7Gv8qzovmCJ82/qgWiTmZunLHtBB6/S2mpwit2eNeFTWwe29uKGWmcsUL0iUSTUp0ZC72Rlw10aTsmpObr/Ot1VNyNPfPynk4dXe4+9lEP1xoOVOjdT30UITut/tIgN8LlPW1w4oPuF5ZeRBtY/Imr9zS+zX4MAFtFc8+TAyaPxfvBZ/ioqH585oAA618NiL6A+4golXe9gP6MqshRlJh9uDARzi1jG/wU2q2QmU46QcaTl44vIrx7AmY81+Esmk6NcTTHe1oeLa3gOufBqCk9/npL8M0UyHl3tPYtfPsEPg6eo//5M1z4mflLKL2nbWL5eU+nQPT5azYnB2yYpnfFNPF3eE4OyIj+IOYEO2ec7Ej27FH5+4nnIaG7Jotxn2NdtMTqYnRTjPrlAbbuw1rSy87QFj7AKs0hbt3TtKLcZvE9Cf9+jUu5zcucBovvx6Reo6NB/YzI269IHQB8/c02mG28/Wv27/XmhVsXCsxw58ho6osptByGXmV+8zeiA8V1sbh1jjTnb2igxQe9gsIbvjHqLyXOn1n0hxpsWLlx0Zjk7RVsvpWGI02NZ4OaQlYKaRCNmRNz0r48s1I4XgNjqV4QN0gspNbFxtQZs6SQQdiMPNeg3S79N+FIJKo/yfbPfnFQMBnTkSral2pJjVfdejR1RnWr1KzuNOGDL3WOU/1EXzOcw6w+WDp/h4YrR9xrUtmTFTJ6X6Q/+JPlpLdTbc+nt1Y12u3uA2/3cPNiFcp++8FUbiPS7uI1uMSee6KT3FPQZmZPKj8EdvunrDZ32venMtuUZNNoGE9XB/BYH9roB7ovVbRI5P0i0mzOi+j9TxmkS3fidnudPZv7wob+omGyxJ4vWzp1pjC2sYLtimH83Bef7okasdpPx5vY4X1WDd2Bxw7xLbSo82PcFlXM/mS1PTPe+GQlvdqditSJDyKtlPwCZ8xEJqbdyFxdM7uM2RykV0BsMFP0r01QhkCLBnQAXOboN2IXs8ZuBS+UDbHtO55i3kpL7FlUJnDTM8xqBfVOQu7x85f5mXTijqrALH00rCZ5Z/R5fqaPxsb33oOz59tDKSVvPjdbfxWn0TCnHkpH8mXz6by+ZSvbYRgamDW+Lj93dX0b9/PSlVSy5kJm6R+lXEkpqyGpfarh2i8/v82DSudbCjxNQ+k0RDoM7MckJSqaJZwvGTPhFkW66jREzoXqw3Al+9eGccv+XIL/0EpTvDw4QWcWvOHdC3A1ObiybWHwZrgKDmv950+df09f9OPlUpw+p3bZO0aH1EzB69VP8FhiSrMcCoSM0rwjUnSuEXKYgkuQrWyrBTYnuNmETsOharuMF7eE6uwmfo9f7lkuBdvtJhZC4E2IiwaCzUsEQfIfHA422WX9Qe5/Q5Lz85ieUlPQBovm4B2xADG49FAAK15Im9l27M0ZTqJPVxZTLriSvelmU41++9E0Ke+ksnZqyJGDlRNHOO3yUHojXINTzrnnJK0mX6vJ9TfUajWFWk2BVlOiNRQNpW385rOSstqgrJaV1WZltcn/EC6tcVmQWqGYoBHBclV5iL9aMe0EnfdMUVflKo5cdV2+Up6vugqUmgJ1VaHiKAytKgs1lKnrnEq5U3VV+1fVKjXV+mNHpyPqqu2KY7u6rkkpb1JdHqXGwyxJ0Pzw4QOk03SArnvouofMvDBFO/x+5Kf4sK/rCfz2/nOL5Pn21kaxmfATm9f5y3Mq1HUtTn2+nEYxVhwtowvp5CVdzhlytLCJa7viaP/q+nU1euO8v0zBjpVfl/iw2Xxlfcg9Vh31IXdBs/PMOyz14swPj/8MK+Xm3jvpjzzkyKS3JTqybDabpOyyKrtsyi674shWdv4fC77NoLTJSptZaRML3qUUxBf8SKmNlT2axNDqx9TSsZFSuHUB1APFUUTzBg3VdMa1y+z8A1QEXqSlmUxnDkZgpbwQqoxSXvLIWmvXnsOUGudC+qlOY1Ya5qvrs1yV2NfdMCZJs0rZiqUMXm7BU2zQweadUzKUHQZlpUlZaVbXWv2OHHzHpLNC32ZJix64xWIHmbm4hTSsp9+Whs8G1QfxzTzgfK0+0Qu1s8ZZqbctwQ4OxltUojFtlZWd1sg5td4M1SpXTVOdZnpDC5rc+7pabPDqCzyyV09tzlS9OLWG2I1eo6ot0F0qa60q1PL1VrVUZpqDanm28gRV6RpoBu2qw6PQEWL1tPJEzI6CvqV2OuINR5rv0jfUwNXJyIp+9URz1pCjqaOjAzJ++5DDQ/pojmyqEmunEuut7WpKo7aE9d5t937Z+w/zRtQ3lPopfWyxHmHVsoFXUqicDhPUz1coMuUyr5i9qVRdM5UGq9JgUxrsSnk2HTJgNbSrdCppBZ1VOx21VD0b6pQGt9LQqDRs5O+mxAKtUpbw6rnKQCqopbITlcLVQd49KQ0ts6uV0tDOTLNQ/J+kbgVfLatsklcMeEyq7FTvNkTOknreG/QquicncUslk9bq/V1zY51V9GWCh2PvLYWAKBSukp0s4+Xoevf37wvGUTuMV7ZPTa++VX7l+RMaQG7Hb/9h/N77EnxHy6Q26/9jmah+jC9mo7c/hxcJyzBoWTK9bjEd+mmlzKp0H0AL874W+Hb6/QeYmFFdL1dU6qOtSyXVj8mFiWJepGvxigHLblK07u4Bx2XdKGXZM4kp6z4I16oP3f178bqS1qUUInQHUhup4GMAtHFMXqoq/b5jyPU32wm7DYuelWiDcM7MzpcffVge973IosZtnBZ043/PapXKhAVXUaEOKrLqw2vlmefhO1opDFApyBrLG7T3+C+vpfF0QXz29nU=
*/