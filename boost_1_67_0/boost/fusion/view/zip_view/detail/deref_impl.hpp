/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_DEREF_IMPL_20061024_1959)
#define FUSION_DEREF_IMPL_20061024_1959

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/vector.hpp>
#include <boost/fusion/iterator/deref.hpp>
#include <boost/fusion/algorithm/transformation/transform.hpp>
#include <boost/fusion/container/vector/convert.hpp>
#include <boost/fusion/support/unused.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/type_traits/remove_const.hpp>

namespace boost { namespace fusion {

    struct zip_view_iterator_tag;

    namespace detail
    {
        struct poly_deref
        {
            template<typename Sig>
            struct result;

            template<typename It>
            struct result<poly_deref(It)>
            {
                typedef typename remove_const<
                    typename remove_reference<It>::type>::type it;

                typedef typename mpl::eval_if<is_same<it, unused_type>,
                    mpl::identity<unused_type>,
                    result_of::deref<it> >::type type;
            };

            template<typename It>
            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            typename result<poly_deref(It)>::type
            operator()(const It& it) const
            {
                return fusion::deref(it);
            }

            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            unused_type operator()(unused_type const&) const
            {
                return unused_type();
            }
        };
    }

    namespace extension
    {
        template<typename Tag>
        struct deref_impl;

        template<>
        struct deref_impl<zip_view_iterator_tag>
        {
            template<typename It>
            struct apply
            {
                typedef typename result_of::as_vector<
                    typename result_of::transform<typename It::iterators, detail::poly_deref>::type>::type type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(It const& it)
                {
                    return type(
                        fusion::transform(it.iterators_, detail::poly_deref()));
                }
            };
        };
    }
}}

#endif

/* deref_impl.hpp
4+9OJWS6z7ldO9Hr4r35j/fXMoXf14Z5z09zuMED4K7fGw/4LWmvg+Rd3jKW5sfvhGG+CFCDBznGYiEmN2eBIesuj5WNwwDCxdINvdPq1GcKzNTs3AVMHVXEA5SurvQkke9x05Oh3hAaNRIHLgtJFIWGon4edrh5K6ok1Xpds4aA125XYsjF1YFHkmbCosewZHPyVoiSIMoBBktTQt5dX8Buhtjxq4Toxes4ZD/jTefiZuokVoXgtcJ1G4GuuEhNFU2wumwqJ2ZRhFkFT6pVjEdhiNAmSZJ7bar5JBgcsZq5MPrRQh+tCaFZWhLRgb/F0JzTzK740EaU8lbcwwxijtxSAOBL/juLA7GOO8QO8TAF4iNsBCmlDoyn070qvki/vIsj5Pf47TnZwNLF5/i97Zj/Dcj2j3YO8jV1WeqdYTVnd/25Tnteo6R7op9SwtHR35cUByhudwzIhTabGz7Jo2NhedGSL8wjG0DgywWn4GfExom0iJJ5jyz/PqfVD7pyMRCjTus1Vk4YxWrJPKxylAsEkSvKBOzlDEJ7oZp5L3QdTbWFH+Jfs91dKckPl63BJHSUC9IxiESWh8OZhCLWhgWPmRKqOo3oQjwl0YNRcZTrBUfWzbmbSB529QHOkxZlOZF6vjnQOZJOb1hp8XRA3gQGq2jUBlZ1D+dB5Bpv7Ihu+ebVg50aZ6qag7vXUnWOp5XTRjWJWpzlHUkj+dsgsiU11G3BHORh+b6kntYUJnlgxMKFGnfDciRFCKHctd5itSpEsfDcEr5V4FmV8WMaGBljvCeuUE6lp6/TkSbkVE0+y0ALQBgvwTD1JK4uxiKrRokHVP7VVyd8CTMWbhTXDCXuxDBQiQvZFbccxqGh05kZNnmZqd+Kj3SRthoqgJ3CczyencUDG6BaixZn0mMTK3LdLv+K7FBJ4gjDgyZMlbh8nhGxnvn6Iwsg/SXdvyMOT/EUMu1loB+Z9DRSWE99PJXfdWK/laRwHQt38M7ILB/sGPIrR10Cx451IVHGpfnNot10AJbATPiGE7lxvv7R+KVQbMLtvR7R6cHAB0EneV8bDyrV2hECx5BMe6eHwJLTjC/GkXOweJmTXN37EDPujQ/hwBKGUl2MoJI39N2Wf+XPoMohYX+xKoE8nQRmyBSylc5++2uRrSlcIebPfACJFyjidm+lETeeOeIfUXY/lz/mit5LKy4W2CajddOuIXLGaozOBu3TscmZARMH4ykDkVkxt8jtlt4xRUUkg44nHtNTf1cnGfAoKvGbvNiSi9/ijI19j0N37TPWA49WZONGKmZq70Y2Xwm3eMG37t8MV+WCPuagAUMoKDsdWIg5N6GrT5r3Y+k954nftSmTLHIohjsP9/dLdkwvETDG8T84gNIbANbM2SHuf7T7m/yTiP8rjt6hD9n/FAdK4b/9s2vzVJZIoeldXiZnWDI6GpMG+ff5BAkNCdokf2CwopnNSRoZKsvxXApiLwl29ZwQuHATmrGTo7BaEEPmbUwW6HvfVjjP2IJt7u0UfOTc+qg1W6/61ah1dQAELPvTdn5Mxwt8nwvc/32V//F72n/tvTsYjp6Vr/AHAP6kN3m+zO3ax37Zn9zOEjSMbE48tTyeun8br28Q5Wy0ggBgAdsuwIT/6HAw4eQc8ocYYfadAsCMHElGtAM+sJs5s5cedIcJqIc/6Tq9PdPkdJutXME59CfOPzPcoynbtXu75zwLv0uTSXPU4uotQRxYmWLKJErEPAAJXKZ4QTF7gZzhBMaAOHadD918FO6sOfC7u99e/bkTscafrKjA5HuaywABDRwaSBvvDKfy68Kb3JuA8IdqPoG16l/4b/s79t64Tmx81z5jVdBOwAC0dkvQFMsvypkT0IAg0ICcXaICxITl3T52CR5vqF86XRbv6o7Webmm45uejaxQBSqxqqe2H0mQipax/Po3j2bxfQkYAJeaj6wHLn/E+eHATOfXi1vKcfeoeLo3d53f4tNE6nHWRFQ5pX/4z74RQNycx6M9A3CMumpa7zXCN4eA2DBK7GI6E0EqJhAg2Uc7m0OKwCQEyvgnvTw17aQfj3GVp/L+lm3EttvVDYuNYG5Mu/Iat968E5ckEoi3FQCQhMsLg53lpIyNWqqVWdxW/SvGJ3zF3WE7/tZQ22skOZvRLsvk13aE4hQb+toomd+0TjV/es7hIV72SKYfLzE7Z0dsVwSyAHKmYEsiHmFtc/zkdXnhx95vS/gqRZZAmCYwCVBKP3w/fQASWOKzJs2+fs/u3dmvtSVe2RsgP+u3YP3cH6dXJX41SXmrb0HJ9MzkemjWeRqvstFgYq+ouKOwWmyFOflD5/QhyUgs1wOVbr4+/nY3ndt3zp2EyXo6izVXw/h1a6lMbnIjNB0N1u+MgL/pPIh41iOCnJNfr7lyp68eZH0nViL2XPyTdTiDZDpV+QQNFPy0Sjano7HtnNCZ2qbrb4JlIpjOIhNoqp90lEPH2BcNFb/gZia53biGKGw9uRCj8SyTb3N8/AQ0lmezSN69WCDugt6uVjMej0OtkAuVU9WqeKWSRG3HqKrITtZNLfnIwrjfxLcLXbfzQr/A5TB4D4TlzqDDsPawZAYLj62F+nW1NmkAOgawaXOXv3QZ2YlMnzVNnxPE3NaToZpDI/L6mu/h3Q1Pnv+IEdqvy+INNuV8518KgNa9CvHQBnjyDdtyrq/FnBMJQYJabLicz2TYxCuBYm1rLTyLukhzAv3NzuxO19vBueZE8VyVaxZY7KcAgR1JxZsIb0HNosXLam9Qtou5dT3LGWU9fWowh3g5bGLyMoYWynYP52+LBdp8JDH29wR2+Bnd/T7QufW/uxYwD76BTone77mHuaTELtsacc4KbC8rY6sCj59l62GY6kAq7qpC7S72QNxwD3suKmnf2r9+idEjnHtukCyH+n5y7/2EDogH+GQC7q7WG28z1jkke16fzhdre/y+3hXiA/7+3MQffU2mMwhA3LnaGe79c+m9ktztkaGfQ0dnZ+fP+KjAh7b/3/Te7y8lltu923ACv1sWqXzQIGjmCBTyjL9DNYO8L2Cnklb4LZxp91YB+t+6TPbZAAKClu84Rm3TKCdLQeIPaW4fOIOVbipBsVGdBjP0SX2tfVE2meNK3Xa1SspotUjpyoQ4JYTsuAAkqBKyhYYXnyvTGu08+7UMaZmFcJqSixGp7Am14amlI2w0JARMm4LWxofscITUl54s5j+GTdzmtZ8xDiGR7Rc9KIpkhipBgTbeDhnaFqdBgbh+idD0WTbMdMCkzr5oEj+jSsDNTmuA+inwRPVo1Gy2xme71lROkBHUfmgHebcay84a45oY0gBnsSSiDM63KcVtKHJn8fkKXy4SJD0GFu+s737DArWIxCJkExH3U+8ijODsUkcRlBJ+BOWpoZVb6tS+FmTV036augGwQv4imrvSA3AYCtgE33K14w4iW6u1EvS4GBMb8hRhxPCF87OA7zwItLCQWMpK8EZgCmk4v/TeG/dgfy1iwyE4oqEWO1PDj44ke8hMKGrHnPcFDJuOh5MbbMrwtJGoGhWDPfrV4qWRRRoet64dnH0cXksnOnjOS7iq1tKe2ijRMbYibUMJlSPWkLFQl2O3uOJXujz9OI8SYA5icXT7m34U1WGweqAy1w21ZxOUvtIeEWdGBZxBcR1ntuUI0VY4z+AnxnWPnU1b5+9kQ4Z38DoUI18/+e8uZFP5ftk4GomERBbVxnAB+Ll54IM5Eeebp03ek/2OFoQRawT4SeYbQqsOHDIUd6IpnXuLL2MBbYzbOmYSnmTvNRhK1y6YpPwTrrWUIjCOxmhJD1AlDdTNcXNZQ+NsnVbDT9YRr5O1R+ZnwYlMFH5N4waImCWR4TGKmWGUbu+PhWVTw51d9HXjRyj8wt4qEI503bjN4OHth3OhhrZyMFKV8IPxSu80mO7toJLz4bevZFLN+owtuwTEjhAQS5BLsxIrEX1QvUU1ZlHoFhrJpj2ZzKWXdnUk6VmIxs7nlrE+No4FkiIa7ZphRN2VpalxlvAyh9K6wJcs5yQAJDczDYoAfMyUZJkymbgCJ1y8NQa5Q+ScZT8tSZvWTs6Ze4RzS3gI4YtuAwXTIlVHkBEmKkkoTxnAsTBb/hld0agrL7Hgl2H3QOJBUW875oP87J3UnaNrbKC0pDUzoyNJ0dzhZ9TKr5uQmCLtxiPlq3Q/4HCnSPjjqrkWDLHjBr0enXGapabYAUq3i2qmFGYVjNDK5aBp6MJnuDvV0s75QrdP3BvbGdeMADaxJLmco9gj5qj230Vv55TZR10uHQOq4zNsB2SaTg+bie24dPoL9Z0eE+sRIweSIhiLdbabk03FN5kdU7hcflWjbs30Ge3Oz9ucEJmIuhp5YhtDbyb1wcGF056fdOL5mtXplzSLeFLYoboof6FUklxHtoxg087W9OEZTLqnicUi4WDqeZFUX3u/3z4IfB47fzShH0LFD8HUw+q5laB1t9+bZTLcCjsVVn9v5xhV92XSyJX7up5uFtmmEp6K5q7mSdl5FKRog4ZahABgp6uUH8kgRJ/Pb/2fQfu+CMvyBPy/wzVq9X3Pp7M58gWA938oQFOLFfDVHm+gKvxBHv8QpKmN8W78Z87lX/pZxL/1MyQT+er/ad1Vxv9aV6JgleyIOHKfuRpAjx16I8xAtISKylCA2oF0qbQDkoLcJd7oYKmeJ7zdOTMQ6hHyevpb7g5BlXXOXZvfYAzsxOgk83Q6W1ZcNCc3ly9Pljy8ullrb2R8Kt531z8iYmz4172Pv//P+f39/de6zYuip13estXz1d7e3qUPvz8bVtj+2dOTC3eu/K75CcUxVnh0dLR7dXOrnijvxuamd0Jmfqop78rlc3pERE2zGwNxVlLMZCr8vJ4vI//2LF6QMJ5wArYudFImaPkSkbh6dyKbUhyyrEsEfCC80cWa5XWqSBTUbxEXyJrHBCNMSGWb6+em1jBCPCGret9P+QRg2ME6NNLUIlCsEbX+9uWs2sXomKq1qu4Kpel1IcTPTBEPSSkEy2rTVdfMzBSmBsPrY6K/FELEv+EG53iFmRoIyzcb+pbs38aUof/EXYIaXTw7QUIC4xNjCjMeEe0RuW+LQBJjBoUjgsrqMYYYjon0iYCKLO8RJSxlcn/LJIyIVkAuuEQ0Y/jreWd2NGOAtuda1xooxtJI2olp0qIzaFuHTzDD924VcAsI+GdmKrz3+BexHtZpV/fY2yuanijtvtaSHOiIVqWennBxcUUeO63b2ina+oRgkjx8wFHH2F98pzb9Ap0nAuMJIWS7270l+2f/LJ4Gw8PmYCQRLhiu6V2/uSGDGCTIiApbH0yY97KCOARX8UsXuqHdN8RxfacAuvZHtR+uIsl5srPbVFz9LKFiJk446K+vZCbugIgHpAckQr8dvnDCryDK0GJ4HXSVcEMLE6F/7hwRFkwEMqzOlMn1DhEfGH9AhBCT2ZXxn+8f+H8yfSI3LuGUQCrhxX6doIWScEJbBQ0vAxvW16HNr/K2WtJK0QROAXsYt0N2zv9xHgLyT8L+dz93uj+5+p/eW4T9Vxyy2Ph2pEFGWFCMPRAwai3TMtDmQrct4HLR0wBYGwhsks5+4MZRvxycPr+c7EemXaEkAOk5VHBgIL5dceQ5RjQlQ0DEw0NKNUixzTacPSCMQ4Gdw2wbr7nw94lrOV4BfbO3HEjleIdOyz2hzmOdE1BIKozUJasmXlvp6fUUf8A3rH2jnvR521h3yf8FZ8f6T/r8931xDoYz/w/+N1AM/mv8buvJ1ZKOq/GdmnV5bS/+87GtF4whOwo0Ggpf6xt4GGkRB9Y6JDA0aRn7NUxgCOIPFEkQMDyAE8KLv55Uv0YExNOIGc9qSKszkHGTmfftlZrpiBAdMRZTNVHxT3UseR4ldmrdVVVTnI69M91IWEKAvy+tvV/DNZd+CHC9v2IEPi80et9nfS6rW3ue3i9r/b9Ssxm+pSYD/N739nd7H2d4dmHNXj5qt3q+2ABWWHO13Z8PqztsH0YJS4k2WDC6QQs/9ICzpTYXyL7FUdAI5U1k4ICQQhhA0FgLGSsMKSkUG7wkcsKnYJLiJb5840QoDVCESaIiJCkItkY7LV6CLDJx3T+dpoIsRc2OxtBGSzipAyohgALYS7Je6Y+gFJAgZFLQFgFUm0O5vbLgDXuccQIq8Di9tPvxd2GnfXZKgjfmu59IAw3yO2HcIUTUvWN0gPjrNOZhe3GjYIPzK8Ih4xbeNgFb1lbusGOX0IMGSAB839eZ3+rovVAyNcahGe4oDKA25WlfRNrdF/OGg7rwkTOOL4BekpnkFsQjv+8jdqTwEbNIpkEwacU1vhPxZhRTwEJZeMFVMpAUBABDxCsMieBdLoVzsSWRZQvQBAAyxFy3EWv0rJnr4OPxXZEwEzx1J36RvTraJL+H7HW03UEpugjELzxHNzbiyElHdOF33ryDSppxSDRu7n92jaMK36zOsGfroBAmcXTWeHs2rrNCjZVY4zSCFVibuYEQsWaiuC5wGXcxATntdRTjFB3JraBuzfI8hK6HFWOYvjCrJC0VRHSwABhW7DYltckr6NR9Yc3UNxOI0HCr5yuEAYbNIR2fb1VKUKGyh2apk4PUchsJne6kndiKjI2IxrCx0mdVhuVqN4dJilhyixP3p8hjnTWbKu30RTGx3KF2QJQ/SNrNhQvf3HVxN/hkbFK+v2IcXtsSEjJzU4PhpC3UjmcYY7tbnpkbZ5Sh+Tttk8zNVkgJ3RH0VulsKAFrktPw4e5JM9CEmVoOr4ZmVqrCaXJmVZkDI9taWBv952T5TaSeXhXRpgKMaUCHLABjsz1Xl93BJPu7cge7VBVGFh6QuzYzaKEkPJAHWo5KP50yeIGD5lVQC5V3wvK1OXCCWc5LbMRrh674oUtJ7HH5LJUb4d63HOxPXn0vaarQbU5QNbGkSa+ujURcSC/q02v9Rlwel9jJlv4paSijRP6yMyJA+0fj2qQ+w+qqVqcZeKOVzrJ7uqWIBilJEjkVL5jKnjPrRbwPgZSs8G8rqP0kt7spw4ccKj57QQBlJIpKGW5QnnK3CxTNCdT2UiKO7sRwckgmUoAwWmRnKVjxYOz+44NFFyhjEko2ZObIGpkuQyXNueBgfvrlivSktd9vkRRa3SB6uoC784AzrG7S+M+8rTd+GUhWY6M1XhejaonXyQvOfCBahdxKH/jXknKHCK5Lj7fzuem/MfhXS89ueGnUtVy+5sNUqrQ8YJ1aBq5SC5HmoJ5l96U1RdrWmkyxSfxl4I0qOnvIlxfD8UGLx0MkuBr2AoYGFVODIq4N8pjkClsO05QeUPNnyL+XmK4Vo0pChn6JwBumW+K5HSJPDulcf/L5CnwUH+bVcLtnIebXuksF5+RgS4XyQvkONcBOFRU0hJYDiNIJV1DpF99Q9tBzCSNJm1eNJDAVldqVFjL8XRSZUQLewMfpZLRZM5yj0WOPt1C8wYKfnUu4gWgBGgmi4wC55qvAI81TERWQx07lJ+2Rq7dc4CYNG07UqmhR62bTEs8SEZnDyg+6WPMLUOULxfprIEEE5psGfjw7TA3c/uPGVei+mdumg9AmK06xloDAqwJSIiBMUlt3IDxFbRBCgZUzbTYFEB4LkiwQcnfd1wUcyRPlMrImsDtSHogLABx30te61W3yqHBAXIWZsvt1QcL1JztOdyoVlND5cnIXIiKCA4fXMpHELzmlTJWk/UReSRpqrtLjdjx1MHWIIBAcNKjELeC2O95TG7oZxxasm4ViNcN0uRNbhlbl52V6i+p6BGC8YU2V/N9Og4H6tXgA9z6H8Jy7pHOXpKRboCpvPyDpcRCr4SkepRlLcZI5AuAmEqAb1XAry7oFd/0gfjllzbLE00fbX0vce5R/ahzKZYSQOaBV2sZ+wkHkA3h+zBlOUThriqd4lchKToqVom3WCmnzOvj1gP3PQTXV2yEV6zDQkZWV+dRjK/n0gSzewsJV42cTCMqT1O/Nkpu2zBjVzSsypdqMSaBCdqEArHHGBMZdmCh12/gnURv7c/dTJivIjcbN18rICSXw1Ld2H+VB1OFEAOzDs0FGRbPxyWff3fhDDyZJKeGZ9vltF+PKpN72eai+mo17yZH2dF+r7bnu3+zKidpw1H9e+V927FudqTxwR3tuP6IpDj0SO9ta0ouVz9voSCWS6t50J1mFF6tqHvYRC6gcpBMyQSW+ISDpZQr+/EiTqrniXnzww2MM4mqGG63xez6YfHDyCQRAKYLNrCOBL0i5vGUk631P+XxHFcdNa6lsAWkgmRAJN8BS+quHuFMtZvYNYy6/bsph0Y64dfo+/L0/jI7GhCgGp1ieQPNNaoGJcwDG64SXLTmuCnh7BStevur+w/aG1kjtCeqGEw8JpWTZoKkrWdYFEoAgsvr6xVm+9XHb+9PY6X7rh1hj0AuVlGc1uARbFkCyjuTgtVovQ6Es3wj7m/d9Vs9v1fUsqmNYkiITYhN1GwzAVJlkLkUlDDUJTznOgt5hgjnKGFeUEE70c04h8DaOY/YS7/WZwdOIfcn5XZ5jmhT4nMR/e7NLBuh6XtHxtzIzEB9kcP/pz7bveXMfnwy9XC0+fW2qX7zJ+NyhACpW+WQ0/AsWYAAQ/Bt++7U36/fonP8RrWGv53/NhaDqS+yMhS9wjhRk1Ln+uene84gHztlzh5Pved489ZGVLeV0aNZXRMFncNEhQPgWHihavvLxSDD2HYI7OMWFpUu11NpFH6l8ISiFDnDlWTeMRs7yETWEPrHy0UMukWamoyzFpJMpmwOXMgMwsGh+UrUWSkl7FhI3WEIdV7g3EP3TGyR3q4BSsZiALBdCWdCkNpqI9nAtkY018lYInLEqlUr32oeq6Y+8hgj3hBoDFki1J9mH5AUJtm9boSnFwUpMmmGIp7cJRoz+OlYGtHxp4kc1/HbSIQgzaIK2wDw0B2xJIzuBSm/64f7Uagk6+gypqsASIfC88MdNS5cRHIiUdAj/2gTFb65y8n2CAKWfqoIBxB5J7tl16s8QHCt90rcJJhSxdeBDAWBnKCQDMCUxx4FiaySAAUWjMEkg40+ISEAtHfhSv/l9p6g4g0EHYqr/dZLkXPKxRWtFhdPalQ8ZwMi/7vFr0xcgJJ3t4OdXqiZonrtd0JTICioI6tmzbmPXCl0=
*/