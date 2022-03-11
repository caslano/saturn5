/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_NEXT_IMPL_07162005_0136)
#define FUSION_NEXT_IMPL_07162005_0136

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/next.hpp>
#include <boost/fusion/iterator/equal_to.hpp>
#include <boost/mpl/if.hpp>

namespace boost { namespace fusion
{
    struct joint_view_iterator_tag;

    template <typename Category, typename First, typename Last, typename Concat>
    struct joint_view_iterator;

    namespace extension
    {
        template <typename Tag>
        struct next_impl;

        template <>
        struct next_impl<joint_view_iterator_tag>
        {
            template <typename Iterator>
            struct apply
            {
                typedef typename Iterator::first_type first_type;
                typedef typename Iterator::last_type last_type;
                typedef typename Iterator::concat_type concat_type;
                typedef typename Iterator::category category;
                typedef typename result_of::next<first_type>::type next_type;
                typedef result_of::equal_to<next_type, last_type> equal_to;

                typedef typename
                    mpl::if_<
                        equal_to
                      , concat_type
                      , joint_view_iterator<category, next_type, last_type, concat_type>
                    >::type
                type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Iterator const& i, mpl::true_)
                {
                    return i.concat;
                }

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Iterator const& i, mpl::false_)
                {
                    return type(fusion::next(i.first), i.concat);
                }

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Iterator const& i)
                {
                    return call(i, equal_to());
                }
            };
        };
    }
}}

#endif



/* next_impl.hpp
35fnsbLw0JSS3Wy3tAv1JCq5a41HJ5Xk9L/aJE+at6AKy6KmsmnGK0y1jOpCF0Nweq/VhVpSQ+sM/6UgsXM/qCFH661M6eMYLHXGJDpk4Dpfuk5kvD8C9HUNhX9rVDOwYubFIZAQ1oTZOVbulOUPVz5pCLEA2kPXz0v1Si7doRLNT6a2nPmFb3zndFtUtDT7mmuxWxQbUDeW9X3Md/fuVUv+ekZP1YQdFFjrSRY7YbiIiGWZ9Av1daJ0PHR8u6wJkJNwxwYfDTc4orQuWt0fnSPLrSG+Kg6yT8HCQOiVldw5kW2y+WshVctV5PDUsFffyyzu3c2OwhsdXyGmBP0MKTtvro2Z4mgoKtnKc9IfwMGKPlPQm9POGT1glPzcyIgY7abCAzTEc5mCJmoj5Qq2CUMRHiNNoq7lWtjUCJYb1NIWOm3X52wAWrtO9S2qu+pXaFx+CKAtYBdHDTyIMp1b5B5+NRxh5suPjXDgiay8qT3CU39sai1MlxromrR8oOtV7BgXrpgu5cp2/bLIxBxm6LnpOCUnyWNCbiz5fHqWCrDayLiFtpYd8cgguS/zZtr/KPf/bG3+mD/63I1DBKzt9Jd4Lcl+IyJE3oZ5va5bOiHhDXzomFbyP64k9bgUOW0cml18G2Imvr5v/uh3eJvofouZ2oJv9VclffR/3/z5Oej/ujrl/zfbvfv+pv9rXEWlYrvWsG+YcTkKKfQWBWISySyf4vElymu6rD9C37v3427okb7/61D30+Pm06+ljz4z0scl/9efXY4Mivrvf2xyB6JIvPEuNdbgGvjNnS9/ZXOtz0nkdCEbh6+0kFNfhFTwU94b7/41+eqVo8L97qv3+jLYGoN3csJdyD/gvuW9tvnZ+1r98eLwmeh33JjbyrAv6HFdqpHzumzxtxYmt2/hpnbmsXaH1slKyPc46b6xLbKpssFuTx6ZdcF28bEZL8i2++rXCBx7xRkx9QFM0iX337ukSc2f9EsL1oGzh4OnoB9lnAPTDIUm3p3ApSJJ37vnx+tNmO4o9DP6JfjWofvSzru+YkcpFMkFAkYxsQFX3GJEzRmJGNKMGgWnh9r0IEjOopTae1e28CJSP+48n0Nj3r0D6kLvWYazxMN1xEY9n+Gzc81+tBl/ZLSB8vjyykK+Apin4fel62x3vzn7AveqVBjv01A/ea9T0WHa+m0kalcvyt9V+XbR9hBponguKDVLgKqjqzG8i44lHK6WcqDtGJSkm/ovwp7aXS4FU+P6gZi7SVQnrODGFop9yVtWVwAvU8VDZNheAZWdIorhFF5F3eo0KY/n8gBhWDZh0Tek74BpRkyOP6usnqu8+HfT5sfT+sMX7wf1obpAcwSnCrvaTShSjaFV8zsEC7XYpoNnYc0rFHoNA6Q5jYOiX+7IQ+dSOgcVTifiZHO04UIHLfZp9kon3OjdVCZ2z+WqrRdB8QSARMap7bsZiXis3jFR+zE3WC8sA2UkKehTZ3RssAySwIvwgxiRAzEfzak0+FBi1aL9LNMrewrjQ1pZKTfb8hbr9myhvIyTJ47wPGSdClbg2zCHDkCA8O1VgrS5CpHItlALRQTRqx223bOOhWwaV3VPsjveOefGWaIE72R+DvNoQYX3vsl1zJnuXgsXFEKtA2wB74tCmY+FYzgtrIxmhuhWcGAqo9oRrntYepnPQUoaO0j73eSkmTURb/5GU8yknhAtZwLsKhMdRWq53ZqSI34101MMO5sM1SXNYdyHT7t8qw9dxzdfAL8atc6mjcsnmT4K250iH9eswO49HawuCvO12mZ+Rj5z7zXa1YizVON9oopWZTAKyklZc6He2JI2H7Ue08UQ2rrEyueuaW7b3wWxmrDqWdq5wMHrpm2nl5v9nM5omaG/tR1Hod5nmsrYZKk4IBX0eHpQ8qnCcpqgm1poB9Srs1RWtYeomTd1L97iEkF354lO4B+Kp4+50/jnDMESTdGTgCJVSMXD0U+VjMsjlDaj3UWGQ+GJ173vzQcbaeJvMTo+j73VYFsp9iddGu0YKu6xR2Ytf5/OppuNd9tLXlSmZjfKFCM1D8ZvnEuchSzHVQIqUAlnIyNS+1VRa0UjX7QNegqxlBqmqnFCdSUGx57hRmP6adinf56Fri+SBGXL2Vav1X235D8/1OXanXls4LQ7JVOQ5GssrloIV/QSmZmt0SvMKQWlQ9Re3kG67tXnVVdUy46fHTHmM5WpIYnkXDvcQU1p2phica38iOfrG5HsR8Jd5h8fz/iplhLRZItO+LNInMNkxZymVuhllLrjiFq5Bq5LdOg71DTwTy12pOWrK5ZuSl3RIlDLWp9tWF1KfcWwejivkkrcvwwRTVhP4BkxeIV9mq+v6rDuVIDTKTM9cBFpyQkdG/e1xARB7ZaoU+Amb+I3pFpiO0O8S0DHAefu9JM7iQ2Dd70ityi0U6iR1XyzGmcn9Ttx7EzXmvZQXiGP5pirvHUH6UkxLx0zQqvekyU5ZL+la7bNLV1m36SkU7XCKoxtJnV26OGf33rU9Ryav81RG+ClVMEyHmIP92jYmVxu443skvmRBCqBpQdmlDTa3gOIUKgNRlHfMLI9NWvohMyRmReU6qAG2fc/7TG1ORLvfRZba5pU/OV0mzs4j6qr2O3q344mHqcR1/zOl8sb7YJ6F5zif5ZKlA1+0+HWFDlT88VN4MG0YcRuK+uZJ0RTbPaM0kSF/sMmEB3God7yBYyyoKmrraDThNBoXkCrofZ7eVN4fbufhoz8n7yHa3xuzrl32j7CI9/WpS+utDiwNJwwmFo2FNN2FBUJvjzMpLLij5rd9FcgbEWtIH24ntEC2uD8jYo1tLWR1QSNZgbMA+GC6HdtudUdyIzeCqv0WzLonB+tfiK/bgQ65/45J2htrpLMh1fLTYlWdP9EG5wp6pSopugBNNHjTlgyt4DKYwP0NgLukLgH0djnCyaxUw+/+WlbY52Dk6GXjXpi267qPFGLcyGcnzmZZ9d+E3FkPxZzmXdw1qyER59dS1dmEFTOlZUiJorx9jXGDMrqk6yaI4haXvehcasPBxVHMBMeDRBQZ/DDn48J99VWvB6QRcNhT4jahSPNrZKfhdGS/0JByiP3XuOPccFVoWdN+1C8+LzgOMMXGSv/XdOwZyQDfDWR57LE9wV0sjAVt9kgcjemUtsh7wfFvzr4PX/t/rvn/0Lit2grok0spwj5d2b3XDLdlgCHG6Lw+pDltcgHJ/E2n/GJRJSOgRqhlpcsWytGpfMuBFd1nK16CKmb40/1Is+dm9UEifAz2sfZ0seKw0bV8Ls/6f7Hx5rBM333Tfnn8berj21/f858n2QMlFGb+akxenOe97baCJ/B2gqNAjvhCs+YF/lOI1vDVQslne/1ET5/NV2VW9O7P9e/Cj7rGLz88H95Kf/yOf/Po/vM4X33bCz7YELo4e+X7da4ruj9e7ju/RGGpQZmlxokN7r91T+8BTG+A/xVfqPqyxKF3hg2eyFy0ReNRMVYfH7lk0HZ/vq3pxu9qqb7KteXrw7+d8HhV93P/2S9ytVdbxZfEFqnhD6fufQF3qT5Wz55kcNhCFiHOixdTulrh9TI0+OkxbfEwnrD5fcOgw//1qfY8kk77GdYbfy+sc9FSkqJGdz0LZJTooD+xkeTf1L/z6WA/2yOjPwCVQ7z0/ylifeyufwt/o9JmrPv2bVuzoV8Yb3URb3USw9Ey/sUjfe1SnLG/bF/9j4+BbB864ijio8458SPogy+5NZf1YnBzMm2xb26C8HtjAQTFJf8PNiMbV4FFF2Zk7fsVfugSLZ2dumoenEG86stsKB4W/EWNCrY3a93TDf4UXE1NcnL6wxZ6l3awKu/jizyfh/PfGavW1D1pV/AXtqpYfJeKRi4mL5rGfvOacZW7SKgUdY8vSxqaR1ron28MNNGZa9vdv2G/jBo/RtRZbV8lbrhQeF5tfFb7eOlXoR6W86RWIaz1GCeidtUxaIfLoUCdtlVjBqnmBU+DMwpRqAic9Jg19xITqjdyirheFL4gW2BIYb9GHtSrcGW/PjoY/TEA7LhIben+T5PsQM/+M5DO+nCxMuh5cg+2fCLY/TUCIxjthBBGgnKFUbwXjtp0tx0Jzthh7Tjc0Z6wyKZvPbRc5vUOZk1tnZ0eCbPO6/i9tr2ecPmd30O5edizsg5jQKkUv/y2N3vqkIxQw92MqoGVXWMhX9toLdHU/fdFWGO6flV2ObnfiFPWM+aH+81cJ8VIKRFTU9T+losswVDgfbrSNiIztyYKeoFxfO7FBJfW7/IK4lST1UqcYEVmekOPRGEUAp3gK6TFQZD22/pzb249lwmXCfkW8vztFl77DgoAobpqWj6bDrKP5uSeZWN/fq8mmZuNiSeDqGyFagUcqQTit4Vjvx8v2LvYg5mgZ3qdHHpj7dSMlmFYlgbZ8LkzbZSJ7KqKa+wK15v0+uxVhdxJijVb2lmmQwaj8xvHTmdNj+xZxvMT+5a+f0CYwW1/OdFa2yIgll2HjzCssU1SOa4//lN3loPSWO2QsY+khoUA+y14UBitHF/r/+6G8YwZJH8nfV8l2FiWlg7TvFZ+/sc4xoa7Lb+QEDTrQtIWZYsV0i++r7TsyJxgZ01ueCCv7QuyR4HIRiyyDmKZ+JjKPYaGEF+SSyIvNHiAh2ITk8s5IlzOKYUWyFglxgDZtcH+sxyl8UoVXQsGE1J3wcxm+uukRvylqhVdR7OHOFAAgAQtv9RC1AFl1MMoQgtmTw1mNukHMiJgk1UVgF7j7fEdFoVnI0kIPHnO4202ltlnwMt/Wjwvbkm6dmNYJi7GloBfkxTQ66ghw952LgbJ3cHAWaO5tKHAzibv8ISQbnbqGqdIBX0R5XyU5CpUGxA87a+YiceKyT2HS3wntSlzPirHpQvIVvbbRBbmkbmekg/M+NtuehXAoialyfceh4GHQSOjlHO4N3pnLQDMRYhu92p3DcXvduYDeHx5wAD0AzSUQ1xhnoZi2WNpSsDFXQ/tiZmCJGhMlhHRyDil956RP9w4T/ro5qBA7/FS51j0cm+4tITR+DM+vGpQqB85xvw70bW2XiN207TlVyqFdriycH+Dika4JwJcSG44vOWwQ6OLV/QGlhLNr6qPY8VCbW9avu931l3oEqWd9zaRulzIagMvTb8MH7hZXoEyuR+OtP8RZGkQzKL82jpGz9Eu5XQwe9NuWbPVUFr/Hc8Qm6yfH1FEttST6R4PrJYZoY982RQmkDoPiyvyx6ZZzkCz0SVcHvZYEZHuRBd+ahd+EucMzvS7DmzOCyBz88rrN8bPl3BSzXVzv3lI84es2HZ7xSn3Y4Q4b+Fx2GJttVX7xRKmeWEtwGnsKtEkIsP/CzlKEZxnEUi80dDBhbMe7Pq++qL+eHb8ZO2t2UZc23znBqD5RvnkIpDEJJPxQgIslO5fTXZxrzePiDFeC//Ly9KuR0xQxa4OoJzQCoHpT56TojtCsWiOY8iSZFFz0juHabUtqTnSc37o03Njfo2tHIN+UT8NnbOLwk8XLOUfxeZlD5407HPSZnuYYKPUjGKZ6gUyglhe5AbwX9q1YZeUJ2ayfM91dhNwR56fT5J8bJsmFi4V7bL1uh2zUsvuCJcxknz56ZEKv4ViFy/Uvk8L15GPWrhSJyx04YDnVqzMyq3SKqnO2d8+FEmQ8wrTCa8AWSIg0H5eyslPXc/ffHut8zWukwAAyz80yNq5+IJLVQFwzcU9oi63U3+/tG8ZUNl6Sq+9H/59OmZm/ouB1VIunyukfvE2R/IHmbAfYLCbzNHh1Gf2jjRo3dreZD78iP3s6IQinbDwXGnBof9pQLqzbZwjTM9iYk/6O7tauPn7QpK7YKEVkVWJeZKuejF1bA3WsHUt2h1WoffuUT9A2g8QuLJ1E+j1R/B/zyVSRgu4iKmlxNm/5d1PP81D5H5//SPoOBC9I1TaV0LCPxr2JFFSBb+l0kjI+mJTusQegQIMg1YnqNkRVBGL7zktDUMsNWNYvKl8SMmKa0LjDvaexYi8Xt98Hh9enqKJTfwz3+WWPpyxf1y1Ha9pHh3ZteWk5MTn3u7seGs33ypz/PgHu8lf3mJdJpzdCJ0FfHXT49bP/XVz7Uuwtff5E3skmeLlCTJZ9dPM0Rh7I0ZCUVwWblqbMdz/DPG4vd4HL3F1ktHyF95TV88HdrRQ3qLQHL7tRGzswPr6CGXKDnZxwbsYc79Ju4vJrWARZHNvgSkACYvN9u0E702uSTCOgtBXV8FDN5iyh08AIXMFXDkW40zvCw1AOQGVVxSOalYj9JApOX4VmHPeMCKrIlAB2Ox8D4MsZwIAbg0Vf85XIOsCXo44GaNLDZhoAsI8QE2dVKzydMH8aPXQECJS+S3mANrNH5sgGg1w+vc/2hhtcSgnzM/df4+B/Wi8RReRLUQ18euQ2pbbwMDCgHSTs/7LNJDPaguhaQWSnkFKyFn0rgm8sp50GSFKzRdu95QEIjYaWMAUPKMOSxgtsTKr4qqwAoTtWZWMbnIwkpDFFyIlH5ybbjx5EihCmgI3BfFEg3MBySCmYdGf8lDkpLTOMcYE+VZi5ButLIH5kRCSt5UvFE2YJslKYfnAbTvf9f+vsAhAkR6VwwwltRr8MribS/xYBnygql5+AMmk80xWcmPoQe2XE2J37YrGgzI54lSS8pZdE0DLP8EwS/ytjxZmhLBTJexSAoD7wWCBL7zis2YQWrTb5fJN4tJJEI4JWZ+cTvs7rWFpBUlcRaJ0n9EwpycwSg5bxpVgR3nopZrH6+xig6z5m4AJruZa/8ZPXKJP89XvC8OtMsJcIRBz8tVI+Ikh8ESTiTYT0ZGmYiAioQnJ9AemalXTckksHDIqxJh4J5NPTkL9BV4KvpSs0H2p7JnkaxuOxdmdbnkXFOic/qwOEaAwK9kyNI+AQjDoZAudRKQNTuBs9uhO8GdJpLOukGXEKvk62y6mKqC+aACRGTGs2fGTnS11zffPjZLaDVPeyWEnS4bskaAyKw8tYgJZRMh6AHPQ89ZRAJpN8AIzVNiza6oZGy8wbztf4hqp/vDZvRBmHKPtTGjJPFImf3KbiiHNbZG5aGJRMJWciS+W5jYRCfHjeNy8s5WKPYxEFJswi2k1CuXX6nhDcUlWTg5JgsX/iLlfQuCyPJqY0SiXSVMZPNhiycWnjYaw586o/3DxmtWbA+xsNhlknTEnulCtRI/coHBqH/f4YgCzVx4v/N0YrKTc6h1FXlPSpQHfe2ypwtLIiukmV4LPaq9HWhc3VOMKICOANCxbdu2bfuObeOObdu2bdv23LFtmzv79n1t0tO0f/1t0qTqH7KCM0GCWJjw4aTRjOtRGfXJKAa2xEO758SEt/KEUk5QrD8Z43828ad4r6xjXcP6VWZ6uxJ9Vy5RiPLzYGGqZdR7JqzkM2P/MCeKXV248SOnCzcGs7GmyhokCyb3O75uhE21naN90R4qTOKpzEzr/6UmZwyVAxGetk2A3BdREOkL8SoKUchymLwZX4+rH/lE+xzeTZFc6F71duc7rDPbxubKQDrJLa57OvjC3EdOWywLoOkgln37KYm1f8PnExJpmUVA+H5ZXNIqBLIjF6GMCUP32Es9vbPDQCWKODjY3pEcwSDmWVZ7Z+0/5YTtElLWy/UCDk2AMuVZrwIf3DPqqcJKMzGCR5GXuzu236O2lFikd3ktM3VKXYrv052rg89W+jr8ckjnAb3hfHm1tkmubLkfZpUk570Zta6yKVUKQaDlhqGnTnUeyxMDWwiYNrqpBEk2WVsg/RLB8JJxxghOAdtibY/MXX5e6ag4BIK77Zz7qfn7OnvrC6xSFbD6BdVla/Cwg16RoPYqfausLZ9ZwSmWd3HpK3OscqpOTjQtrVZuiXrSgHH6gL/Bm5TMSFlNdfC917xY+ObQbEz0Gmi0oy+rNwUP5DpUIAEvSnvTu/Ryqof//w8k6d8gzEJnGhQ9opNRuBJzybxkDfdLRs5A/VX9Ed39TxX870Z3+7xcDFJfu/Qnz37ikPwBZZhQvCP0/5bhJ+zfhZcl7QJhIUXlj+ev4xsVK2+/ZGLPjL3OJEdLB8S2ahDOMV4F12ZW1570JGbOKKv9yITWXd+2PV8vd9/tYPDBXkL0KjgFtOjN57oDwF0ozvlZNe66RgAgnZup+R2pHy8bHcz922iZexgvXZmcOKmWbRageULXbCH748j1tyoIZD2QTDN5LVil6VGz8zFoHmLE9N2/wGDkUBXSu1H40qCzjL/cXok2nhDlM/u2BRLvFCTz6vbTB+6rNxIy7MoPIJYuJ8tWOtZqy8fsPF+IzoVui0Yo4kYOQenyKfIC8wvq+Bg5mSeZOXltNBX5IiX5rPqsHbMasoXxGbS6upoZOQU55bKVwWf2qv2Gd5r837dau3w3FgluHQBh7RlWcWv39SxJfiwmcCxzTQ1vIv03W+2JGdxnLN/V5WlMlQKG/aVUcPq4IQEvyRhq/pjKoR9PuYUB7Q+jNJOAIeDsfWoOP2gfAkFRLB0YABqqDpjMxxVRGCoNbEQqIOSgtGieskjbuwV7oI3iAwyw0BDgZCleGfHdXwJD7mHsyOvMQPHej3DLj+oTq/prctd8cT3g1FTa62KsGiqb3Ew7tVz379Kbfx6fKRx56yDFBLpNQ25MgwDluwIWAJ4MCFFBPIbBUgb+wPArjTp+EHzjyA7BaGjBPPoxK448cELiyVhoodI38Jf5wUJqCQFJ9UrChJAGkiFHtCjyXSmRAlAVY8nDCNeVSPJT4BCa+13xar6fEVKW1QNTpFkdS6xeWDJY7xgLP9YRUPQpwTpmsoCR0pRE93QY81DU85JTc3NjFCOTuxVFuex2wOZAGFWvcmcYgFTFfz6gVG/PIJNW11l2wzBRZCTaVATucwa8KIpfY4tElnjUEJeDoMwcTGQwr/MelJbu/uDEPVr+aOf/ZNo1f28YPWW6oFLTV2mXh4aWPjadUqSVqGlT/qkYVdlED2Zj4Jf1hqZ8q3SqzuWmoQjHpRMA+ZMDRVukn1Kw9h33JG5IgAMAN4vCJIlUNTAnVS45oAAGOUQ/hmxxDjpYaQuAlJ6azhoQHEqrOHw4pHLtUEwJxUj7k34qYpqHFASQN1Jr2M04LYh7G9E6cUATUMQ0MZgEMmkaaXZbCi8UsYuqOjGecfxAEls3aBY=
*/