/*=============================================================================
    Copyright (c) 2001-2007 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef BOOST_PHOENIX_CORE_DETAIL_MEMBER_VARIABLE_HPP
#define BOOST_PHOENIX_CORE_DETAIL_MEMBER_VARIABLE_HPP

#include <boost/proto/detail/decltype.hpp>
#include <boost/type_traits/remove_pointer.hpp>

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4180) // qualifier applied to function type has no meaning; ignored
#endif

namespace boost { namespace phoenix { namespace detail {

        template <typename RT, typename MP>
        struct member_variable
        {
            template <typename Sig>
            struct result;

            template <typename This, typename Class>
            struct result<This(Class)>
                : result<This(Class const &)>
            {};

            template <typename This, typename Class>
            struct result<This(Class &)>
            {
                typedef typename boost::mpl::if_c<
                    boost::is_const<
                        typename boost::remove_pointer<
                            typename boost::remove_reference<Class>::type
                        >::type
                    >::value
                  , const RT&
                  , RT&
                >::type
                type;
            };

            member_variable(MP mp_)
                : mp(mp_) {}

            template <typename Class>
            RT& operator()(Class& obj) const
            {
                BOOST_PROTO_USE_GET_POINTER();

                typedef typename proto::detail::class_member_traits<MP>::class_type class_type;
                return (BOOST_PROTO_GET_POINTER(class_type, obj)->*mp);
            }

            template <typename Class>
            RT& operator()(Class* obj) const
            {
                return obj->*mp;
            }

            template <typename Class>
            RT const& operator()(Class const& obj) const
            {
                BOOST_PROTO_USE_GET_POINTER();

                typedef typename proto::detail::class_member_traits<MP>::class_type class_type;
                return (BOOST_PROTO_GET_POINTER(class_type, obj)->*mp);
            }

            template <typename Class>
            RT const& operator()(Class const* obj) const
            {
                return obj->*mp;
            }

            MP mp;
        };
}}}

#ifdef _MSC_VER
#pragma warning(pop)
#endif

#endif

/* member_variable.hpp
OFCQHyotNN1e8UTcj6WlN3p40IUvOMS6Wbxd0q7YO+HJa5EmIWtJzZdQJHbxXYytIe3Oq5a1ELCsslalT30z+xt7SR/0y2+wPbH++x8PJGHegkSb8E9s6Abzv1O3FE7VFxRqoHRZpswORP2Q92DGSzsoxu4Pd8H7KlQBdXPRWoehF2gqfd3PzqfsiwQx2qfufuO1s4C3nlPOixcUl4sXpU7PS/v7IoYh6rsnbZU3tCs2z+8PhKI+T46c9suQx1RXt2+mpEzLIFhB2dSSw/Af62035iQ50LUX5VIXu9rrBoc80TsqXuBps19mZM9azIodwnTdQ8UKaTyFtgLczsle/ex1KXST+bOvvToin5xvf9r/2qddduB/24SHKu/krx7TFwYQrm3LvGI1UV8TXLTkFYK91GYvz1kuro6iH3jy7MBs9c2y5myonij3IN9KMJdzsnuZWAmnJFuC4K7YbkkeQACocn56ldh73VIvuWUeXx3K7N+5C745AoM9mS6uLhIFj7ldy58vaq8T+Hvtp8/ukny9fRanzff2GZaHqA9t6iJAV9P6lk+6iNCu5ZVHLnDKbn57b2BAZQ+gVTUa4L67Db8y/VDZCwCEp99nepg8gK4AWFu2KcddCyAo2W3tqlo3tPpwf2eh2arXSPI8/YwJXG0vebNI2NutPgKfHjYX1mv9yDvSfzikE30LHlgbqaE2eIrsHg7EfYXXT3bvyX8AfxBMUcvFOMjyYgf29PyrgNhBOoP+wrGen4aMPPfeBBMRQahDofivhiDJ+t5dAOEbl3MfVGVmZWm7bbmzdr8nc1lUpcF5Vz2duMIpX29IxDJfb1akPrdtquOiERhQ31vPVS2QsNwLkahXQCl/mhbBA1AEUdgiALHtg1yd+YzV9hrGE159t5AJj4yEawz1znWXVtaenl6sr5od53xtk/8+LK1bkb9tY0Kx2aAgXCjgHejy3b7BmiPNDZLzEHHX4sP2TNsZFGLJcXlxLHCcVln7bOx1MWHHZ7d87wCsPgYDTnij+zbKXmcjXoRburrPQLjGdtRHrbz+HyXJp1p4/WOYCfI3MNrVHsPTJLShw2Xl8k98qzmJB9FEWIDFaVa+y2Te8DkmHWKDK3wM1/jbrhK16vsWo8Hyi3jfubm8TdEI8Suvn9AjyrNHrIEttJXX8ZjuNV9sWc7BYFbIHZYwRkBBDBTnnA3dUAk4T9iSZabbd+Ux7lwWb9WdNYfNuKL030SrE7rwwhVyUQgkRhWQMr8Q5L/U5z2Tm7COn2A8uZtH0QcsZSCTTmftqHhLrll1m14EjYyGar254495IUyBQq9NxP+QYE+ggk76/6Tyk7Q3IJMbRU5aXeG3mYcuvigMZGJMwQ9nygjJ7ZxHJKKkJK6jtboBXyAMKzoSFmW5iSs+S6PA+RtjPLXHrzeSIfH/xQlO7ZUPIZs1wENEPyyP7oiOLS0Px57wv+nYuJf4MjjOFIW3ALxa4jYJmYUHphxvl+8sU54D+pKyAVDcc9x/gOgXI/UH287Uv68vFqZtdS75IP62wDDy86olAP45xUrmVRVswrdOnKujX1FGX++JOj+hYu1poqhcghLfiAtPRNey/eiOUDLEomadXpj5fYtJxqvV85AUoeS/g7kz6SM82W7dQNziMrM903yzU/hyRecXuTQtaeC3ZYx7G0Kkv21oluCI2KOw1NGffrXzWncNlpa8AfPAkMLISUY7Pj1FS94E2oFR6pvlzUG453D/AAm3TfmzklWoIF2XrPfJt7/MkZefA5JafTOyoLQrZuHGn4B3EbTbR9yEUMacUCWoQP+Wjt6oo5X4nku1AkXCQ9TgYVYvt9Fwb/SIi01ckDwJ34dUeaJZPW6jSYBDYwB11jTieVPuQUio2vFXnb4ywydjXYm3jxYZXBNXHXPP36LNPQdhBdC3MddnJRXbqV2JylK+4w2KSDcNFVsJckHc3rPx86w5f4HL/850ktHX0MyaHtlM3D5qaIEOOGkCbNd1YOM2uyk4sncN+gg3hlkAhCBmFwHdUR8Rwje/AK3BuExSxnX7IA5AEXUuLVkiEuoojxQfhJRmudsv6PfsjUyS4QepC8CHlb/v2lXbmXWRSZZhASQx5E4uiAeL4kNOfqrzIvUtCKzkntPgoRwLtlMVPci8PWDDvNK9W6WdJkinXNov8HiR1J+dDgp0Jn/J/t2b8i9SzK7CFA6sTv7yOFwIiPxH3VR4Zcz+UiFwX/SbWm8D2CPseW9Argz+9K+u9Tfg/cvwcAsY0FFTEniXWwhYiei5U5117p1vCUwiBKP+012bmQ4L/DDb6yAHxbk37F4DBjLcT+ME1I1W30ONC7eHI3qmOWGllodlvf8aEYQJnpwxVboHtBbC2iALa0PnLDQ6cGdf5wXqNGv6XUaS7CW4k3xJcPRovPof8SdAIibYcoar5bepQ4+CaExPQig/F8+eWSDDv2OGpX3CbRZqu0Rif+08ykXATU1tt4j4N/38IbyKaQDK2goUQ/Ij2bXl54IYQPpPYdVwxxfcMWWE/CUUpe4WFFjUCHutacBXAWKjVIAAIeDWgcvXqOnY1k1Lw6tmmor9MJoKy084boMoY60TezTPnj6in7dALciwPQXpkQ3nD/WumAJOhW9IJZuo1dFyz8zjWHQHz1toJYKQS8FP/u8pgp0HcVmh5De0hGR3v+tJyCZS5PlnVxDiB2eEhAf+YV9Srx8JUFYcAdAeqemGpzDotCHOA6RYqn8+33BYFO8aCu9ykke/RTNvy+h/nLPJfvQbW1NZ6Y1t0AemYPWzQhT5xPpJKar38sN4+fUCoDgOPQNrAZ+mYkK58pGV/QKDb6MqE3lnn+RWs78AKT8tQBRCPDBwt18io9R6aEeaJWTbePtVMHnW2k7KWoSzU505EQ3Rwc6firGNdXrC8S/3ixbeuPp7ioGjqAJ65lc452LhF/ekq1yVwEBEPx+Ckb6v8p1MuFPzRdpv6WbiBC05ZqMJRKaMCWmQZCGDYQBo9YiIVdTk1ZuzgEH2yv3JjazHiDQ+YLXo8NmSmHU6P+23PFYeeuEqnRbfa9gHbPdym4T3hJNoM19QU63XNtRPqgw/ab9Z9zqSExMuRZpl95Q+QvGqkweIcM7NwjkYVmTDaxhXVNDPfgTlnBQBISjeFG1B/8CPZLd54WPN9qSMy5fR3O2euQMHa904jMu11hlGndHmK2cAACz/03Bb7NdHEaT7HsL1xiSltVBpvFB1PeqQ7gpgNOK6b1wHBHFdxVwZTeCLeRWa5yWJ7Xw4891oOZg68o9YSgO+KpDQ8ic0MM6oUXLETMWsDZbQxV/u6k3j1T7Ccn77nS/qOUeRY5Arl2ZosFkriwNif57OCgOiH3GgIGnV3nbY3bne7puyqxP+1ITlr3k515yEnzmcwORSoX6FJ9CYZ2EnaYfoiBL1s3f1/S86ZrXfb77VcSi6N69+C/2uOTFQfMM89DPvBQHPhoEXnHOLcBX6FQR0QymgIEFLiplhgi4I+nX9Zrrjyv0OnOddDaFYi93nOJ4xShwDtc/znN1EsA/d5VgYbBqCbPMayRO2c0XHMgP37QKX8wAl/hxiS23uKJPfkIAejx1DZI9/byKl62tOFxl8xB5b41vF0oHPrhWaqzxndyFHPQLPQmP1QiYvlwpAdxsxt+xCMZTOGjruMqrft5I4jrouXQTHJLtxKEyqrucSTPY4ffqxbhjjubgjJJupNloh7oarKvQ5ZYxmm5uIqdAYF3+m8gdJRHIUMCn+wVrxF/XnfNWfYImdHoxLlJgzlTbrvu6C028fcmBp9t3n4iwoE0X6Z34oICS/4txAqef3jox38YIwp8bLdc5nHy5DEparbxN03yi2SFhcC/c+r6670GgcIU18ODzvVP7l9misXbyBoCZbcWW6pwxl/ssiX/FMPaAYNUAlNVzBeXixB0j6OzqYHv91jnMYBqWw2HgchlNOsVML5g2X4cKCmuPi1qqpKVazqUkZ9K/s6tBFTMafhJJDIi6RiHqvaDhyweaGVtTAX09bs4MNkoJHSn029aUmHpr30U3hJffTGyjlwp0dq/+SGOiH5VmnsGxatuH6Yc8Xf/ElXzNe1J3Os66kbj21bvHag/rGo0+2miuTuSfiC4EpHeMSyGNVthl6heEmkTuAjOdQMpCF2qL9fql42EzFIG4cKtXWw3MKYVoRCnc0lZ/6rK7HFbKJBJUMhypYXE8RWYqJMuLH56d0XyCuB+IdAZlIwWfwu/f5xbe9/oq3fz8BKue8mHIId6qzw94kk7Ug1AMcuj2EuNWbVoSwQKuKvv7GN7ZeCDRGEzAxl0HzrBn4jneuGM7BuLKO7hdutj5c+eZl+itgBP3shRBaO0bvS1svJEqj8zKcotcumGT5TcyAgM3yMUbPx8khJvV4RPXJPFBHC5c83Wwf2WEjOB5lD3jMieV3+b+bg9UD/MgHW2brYVLw1uH7sUmSsqNe1EfecGMl4DKBJ3V/S24IBZumFgR7AO2d9QJBxV05y+lba+PBl3mWSij++SjQXf05TVFIWwnA1d+SWTkCCPHQXXk0TfYvRT+TA9pq4ipkVT5K4kz5KfUGmU0QtNzbU/n9eIv4u/xF7rK9wq23KSr9tUSma4NrenQCPEdncpkeeKPRG+X98MYkkMZSHW0GYnGYFfTnKjQWXoUSJAp3eFeYJtvqTUTeztoKVdlnxUDxJl3Rz9SAPuiikWZerOdHbpA8E5X78a8KUMSKV5uUX2hCUCeyKdJMxuVHzsBsZfdt2zSaXkq8A/FuZfiREcSbefaPx4a3m6iGckCwIvxWJF4xwDgifh1tT6ZRlsWwyB/98I658/d5rBvqeIGsPgapiWYLX10NrKcs01c+T7vTl6EJjeLH+y0/G+0vTXKs7ZjVT9Hd5wz9qsQjNzk2F2G6uk6eXjXxsmRtWtjGAAvMky/1woM1Cq8eE0p69n1mr5xkts+6/nlJOPsZr8uQU7IvVU4Lm0pOEfFtfpzSeQeuvlvqdf2uonuTeHfwXA18JP5zp29ujNqiZD6I1nLxPhUaYuY3/dPzSlDmsJcmh8SllEWVcLdaQ8Kj4/Ma0ouC9R+wv2fEGtR19jHjIcOHguZF5fsH6/kvs86Jt6Rv4G1mv6mhO5vSrt7nyRQee/px177hqZSVT3Nf9GNzJTSXLI4LjOCMdmF73TWlfKJtZaUOjiagj7CKdDgvqsMixdNnr+i/+izVJ3iSggMUxBI+6pfpHXrOF3fXGuBXBm7FNUa+sY9php6Kl9nd6dXb6SIR5/763N/Xj0ge/CIpLod/Tvac1z3XXEyFbjqweQZw0gW6te/6ox7dlJ5HfQM3cC7XbXOuPC/E5F4AG18+1uWDU18eqoQMegMXFc6Wr0RXwLMxxsdsekyrqJ2lvSsXAV09m+ajZ+sXQhjWPycbmgzfdSbX8QGpXNLWoB7h1ShaKy26Y+1EjTgI+SU9ULRjeiFrQmvWXS22fPQ6AU6Jx1NdLCLruTRj/iU3z66IAFVdx9FRCmvlTtFJeaq81Yd9C9rGEgncxkVInf1BrldLFvTDivh/sYGYEBYbsntq/xs81Ohn97301uEDL/jnsuG5MkB99M5MWJw6Jw0RrwGqsP3pGqRIhSab5WuumIVQlgNJEclrgOtonr8GTGhWQIRLEJHoIuZqjH4BZZ0rScSzYqA+oqieuXLtnYfuo+Af3wKrg49qaa8B5g0bVxPJh4ZWlg3+sQRM5MJzn6KP5GxMIo+4ZhzSPmQ5alixu6r0b3yL4YmwwrlYIdAGhBhjiSIxpxeXv0kKeuf0vYo2lOFA8pV++QZmf3iolhIHfPnV8kontzVBpSTX/dW3pPIZ24JNgNAnmMBadNdBRXtaMoQjUk03JXB9XP4AUEVvTZYh25qquPZPMblptpExxzQaGpm18EJcmGk3QOaUbAD9JDT831Ihja16H3QgxvME3TFKhQa5dExp70v291QCs9EEvtU+fZR5dotwWQq+q91b2aa3zmPO30B77OczAqRcqEM4JjNeoxnJJGxZIR7znvl8o6LnEBm3gmLaSGeyqYAvg+2JtkIgHsxjidLdjVG+57yXjyo9RZxlY0YXNXzRcOBMxm1NjrlDv0qZjid7SNo4fY93CR3xp46njx+M/aM/E5uWlsRylf64YWAy9tfP5exxUCQ2VZobTqc72ZvI/GF7/PoR2PoB4Xj0ezm47m/r+9lruGVJGX+MKe7aXM1Ux/hlc0lKstiCX3V8hdEjte89wGiPhuEcTCuRxxXPdYYHcaE+K6NiaoeADzncJdTSwFgCT7R+J82VbkQ/ssB8zUBdvKlQ5/KbK5SGEQPzAFTP4gFGvHOHcA6aFX5ns4thcnlKZbRjISFTVtV56uc7zieF9Q6vAntB0xc/+xS1QgcJ00uW1ucQ8ii3Ff/9Hj5cckaXj8dVx9S7DkjWKG8rdeebjBtnO1sajyLbjO4TmafgdLNIFgeiflXtFbyQyWmCXt1vZIG6OFO0LkqEZftq9AoRt2OJZqKcfWvpSHZQlN33egUjsPWw1opbiDFQ6jSrU+plaA1WMzp9sEm8gb8TGHu7Bm9pBPpAhs2htQ1APOtSP/cwLt8CoDEh5tTHaEoLCe90lQhRAmgtoysjqfu3wgOT5f7IdaO2lxOTXqTJ8iGza8A6gjyLA0M/p1HYm891zbue7jp/e0BkziR6/MRMG1K8ZKo896zLOF78lH7hbhoDmYR+xIhdIW5+yRIA51wp3ONpUeBRM9yDYaUKnVwaeNG4eJdv5vdN+dX7e9VNvssIC3gdUZSLfHtCafuGM7MoQo1JPTD+1q7FdfItWv6VIsc5KXSDTviPeFLRVC89Gb7bwpMCMFN4ZTnETSWBDBpIZx3PImqC6KdgzoTvEDlsB2brf9Rnv+A3q2/S7bNohia7WLOJqlSNbWH8994uE4FAhhlAa+V9SIB/dAwU10EtvFsKSItuD+10dGgY6MA5FwnHZFqRQc+WA6aiG96KSmoOQ7CTEsWIn+fdXBO+1264d7u7cn6p9QcgH46Djp+MniFx06lX0wtG7V4Cx5VPgvU+OubHOA7NA06MK72HFU+C/b4H0duhtwuv0Pwu8VAofT1YzHZ6CGZBLCfyF9NFO6va2t0mbH/TZy4v8q5YvHecd+mB8kPL+W09NY2pg3geV4vIYWwN57PFhLipw/NRbM2Ofz1hJpcjUMhUHHqe15jLZGpujPZYOSCP43BX8gcfuNBGpYxaJigEJjjG2R0K4lVxrUSzJhQiJziGkokCZkoLmeNAapW22TEyqZ9KfvwMmvkdu1cgf7b383e2agggiiYENVfWtZ4g1cIF5+7W5HZrwo+Gs5AGVUSLnQRYYEb5Qx1Xmq3kH85bKEHk3dhr6auwMXzvXa6fm7PbVacwyKph3fHukSgAgtSp6qANxOc/D7VPgdI4YC2XQyrMpvE7a0YnkYeo8M7h63mxHrfdHwtnXsNA5s0RUObq1Y1pPwFQq+9qd/Rkt1NNUqTHwqDIaeYSmk3u3bn7jzEZkzCF4/xuuWfyL9pPpiHQb09QVOj2DoASguFx19vo9LYlcgENS1TKfQSEdH86956alGBsyWE7fcn/5IxUH6DwisEDeloK7DuT7qKS71wve6EeUAhfqZUQ9EN40Q0YB5zNWwbq/5O4dmWaaeUBXK5n9N44/pV8FTiizL+Eok7W9/HFwp0KoZQKE2Yc/TDLUkCItcV6ewi6lHR2efVGzUZqWKVz0IFfg6J7VpsHrIe0zBRAoYQtmpgGUCRDWoHW2cktek8NoBr5HyT7GbC1eaP8i3Z/goAtlGklYCgQ95zHIvLOybPF1pJ3u/iN2Pwu6t76FnoD5rrfEnQt+23r3h3aIio75WkTIIYz9xw5I0ZaOPIjY5h/7qqlXeHlMJAyHfaTv7Grova9ojw4BjqIzLdjWgi+BRgTrBHTVQLoVkRnetVe1lF++BMjb3TU0eVgywlRx7hIhD1F7LFPF3A0eQ7/oY5yTeeSFweSNBdaim2PNkFxs7jM7thL73qlWyep5/KJzr1jT2HrdJr6ViS/mJVv/SZ0LVU736/wRGlXdDkOQlscxHpgRGrO346iZlZ+zTxHmk0MtWD4OiW8b3+YYmzDyNODWuOfAfjrn7XU2HuYDrx6Z4xCJxPps9WswyZtlB7qEA0/eCoCRzXPJk74zibUzHnz9wThm6SVHnoFo8UlHdZsTEsBcN6joiSKZP/9LSzO2MdIZ3FNrnqhyYn0yTarkOWXjK3tbkp5eUG50H6KN+/gB03ekg9Ft0St5dNK4PLq8okyZqEiGpoPNEJd8KzMWcI4cB/Qp6IK0tOtT3x+Lje+FW2f/jGwl/TLB182Tkv4cTcFyvqhZZGzLrkU2nbjgfNT7SAIs961WvuSUO7jF7Zatl1OfZZvlOjvDSseJenWwKy53APdQWKmptHH26x0lBizLaYlPQBJ+S1awlbR3cA2dL+JmoEcG8JkrtmRih86OE60cyxyItqsuZuyZxS0a8cfZNeZPuUCHtraHx9Q/xZFCuAs9+PKix7Li7kVKAYpsM4UihHhJ55dA01rRiSpji8KNDXdt2urShyMdJW/OFXVQ4/suhR2RFC7zFJ7UG62GgzEoaitqJD0FADirFi3fDxU8PDb7DOau+QVP17oNBlLbKb9QSY3ID5luMw+DqL07iYmbPm790WYLmMXxIju8EW9+AWMP50QY0+7URFjqNpmKq/Evi1XCclHaG8d3450caerhyrST+VFpzSUx2k95Hv/iBrI0/m6NyuqBIZEe8qn+ELd+Y6R2Zx0BzYL2zRRWz+7hqK13hg8gENd8nU3NMNEfTmm8vRiG5mWKsHOWb9AUqkJKLvyzJf+A5tlbeZhhpVtRAOOHaqLgAHKJtXxb08i2lDoqBGvwvMrziXoGqr4zMWYpXVIrdwWHpOt1oZ1tvgEcHe/nDirLzvy5YfI8DmzQYXDXpP3amk2ZIc3YUtpQtDHXYkO6XhAC/exp6YR1wBlVRtcWKe66yAaSGF48sPGj+Ea+o2JmLPbYuHWZ/nz9obZcmLL6BH3IjsoKojyCVDwVhTN+OWZGNepck+kif6iZa8D12lfxQ6KMRCg6iqD5hWzV4p3mZ5dfN6zXrzUizdJdLjdQ+iTxlYruKvD6kSz27JaPSKJ6hW09x3/8izGHkTg88g=
*/