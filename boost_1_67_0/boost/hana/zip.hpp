/*!
@file
Defines `boost::hana::zip`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_ZIP_HPP
#define BOOST_HANA_ZIP_HPP

#include <boost/hana/fwd/zip.hpp>

#include <boost/hana/concept/sequence.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/detail/fast_and.hpp>
#include <boost/hana/tuple.hpp>
#include <boost/hana/zip_with.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename Xs, typename ...Ys>
    constexpr auto zip_t::operator()(Xs&& xs, Ys&& ...ys) const {
    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(detail::fast_and<
            hana::Sequence<Xs>::value, hana::Sequence<Ys>::value...
        >::value,
        "hana::zip(xs, ys...) requires 'xs' and 'ys...' to be Sequences");
    #endif

        return zip_impl<typename hana::tag_of<Xs>::type>::apply(
            static_cast<Xs&&>(xs),
            static_cast<Ys&&>(ys)...
        );
    }
    //! @endcond

    template <typename S, bool condition>
    struct zip_impl<S, when<condition>> : default_ {
        template <typename ...Xs>
        static constexpr decltype(auto) apply(Xs&& ...xs) {
            return hana::zip_with(hana::make_tuple, static_cast<Xs&&>(xs)...);
        }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_ZIP_HPP

/* zip.hpp
KMiVkLITSozfH5LXuTYhzqUWbBs+NHiIkzZjPkZWqv57yXgaNj2NK+I1GR2ano3pa6fb5MJ7/EGf6vqc8Oiprek7HB2dXZfS6HGck/nbhs5ilo1BJ9lt8I3u2A9vl5AEKBNUnGbtu5rtla+k1MdBX4dZso2MO9EM66/zMWBEahBfn9fwJf/QordvfPmJHc23RzXlyflia+aAb3C+UxUIbpB5T0/f5RWcZ8jDcJUTTHuN58Atzdwab8sBSQW2XOjzqtP7TjSYhDjy4r1p43ZaWn98pfQi3OdZ9WZJ6bbtGDFvYscCWFVtNlZpZ4ELvSqd2YN/FyTviu3AS4JWWD6zS5bODYIFNauYbQP2qYmaqumkXIQT8iIMN74vthuyzmacHhkMAcp3kQL/RYmzOHmwp4rJ+HiCUsGofsA7K2qU5YW8HCG3ZLNjMX3Oqq/p1dIrxPnPvZXKUekAGM+7ivmx2/rrUZ+J4ovygJnKwk3X/1PldruK5oDTR19j2I3tp1KMbST8rstl5Jyf9SvJAO4obolruqB2NUUKWLtHdczwEjv30fkcdvEpwEE0h0rLmNQznLDTmjlCis9uNwcGm1X0upQ5BdWPPF8iUSX5iNTiHMq5ln4ubk2923eBx5Hlb0KjCkM/07aDc8DqWCqq6pWj49DchfQN/o3LhxmJ9JGVIXblvktZCUTG3mTZtFAYhlNl+Ql2DwV50f35LIDPsoPokQgOD4C2tZv51iZO8tujWHt1U5Oi65OWyR3RLuajOYln+99GY5mMlc1sHvNq6PXzkm35J4fbxZMJJu+Co2SPXN3jE7XwceUsIfN3xbbxs+9p56CRUogKbvo2Be3L6xlTsQJBGBKdbgYKEqjg8du1eQiAMHIREAvhIky9sxYh8xQFwetBoFit4fM0M9HkGKCnfTKpwaO867DL3Yd4UiNOm91UrvKkg9z4gwjH0aYiqnc9P1fEeoKVsV8QBV28U0bby8dVxb8OBUhqAxzfyaKLxOnmEFWZGXqqUKnf1R8XN+oLw78kosmGcM8oyR/lOQeg74Um1SzkSGhWRVnNZxamnd3tdPYL1FlpOFVhBSU0TsjD9Ze48+31DubCT/OJO+DzhsT5haV18OAOi5r49DWYxI9aukTNaWZ6OEKuf1/1kfDRJTdYPU87U+8qcmWoSjEbbe/uNOsM+41v72O6NEn3vmUzWBIjyUm9amH/RulScvRJVaNaM3sHRDdFnGmCGRAMhlZO/koXiUl1FI3sN/Ctb0V2qcKwY3p8WAPcPtG+zqzBCIi/JEEv6ypUKLEpJANDUa9wi7+YuEanpPIuMJKgzfMIzOogkAkigTW0tDfFRVsvULg2UaONapUzO3o+0Jklq8+xdr0bSb2N5uAXQTAhSklxdRIenMnSUoqtOCYZZQXGvebF/kmdN3xN5OATZKBQ0uuY13Oxi4Z7fCuE5UyJk7y0MkrVM2eymZzECM42HClGVLvGhRAKBQrO6s07+pY06rwZm5ZmOUCkrtWXW2iY+blEredPa6K28bPqcy4z7qwqj6V2aUHJ+dHuoSVpvqiAjiH8ovzKB0FUSYqUfpcbZOdVKH5NOa4aTCtVm3xSD7MjElNFyTd20+IaldIUm/5GpZ3fZicRwKbH+svFGJkFiS+0PwOuiMUFTgy/PSmVSgV7rOOczZ0Z4xKc9aITC9eIQpuP/MPrbTFgXKCIl0hbEUM0T7CG2yC88ErEoHsiurSa7o/0p61dvUBuOmrCftYB0mqaxow/0bcIrqD/c+pJRSot2WXrEt9CDTHy3ATLSkpDaK7ePN/swNOJ8VhiUvDMU63p+5WHMJQSc+e5Z8zhVGjtGEylrxNqjQj92WGlWahISRvG5fDbnIQ90uh7Z+HV4+sB8o5HtK47eYnUVN2hLiB0rLzH3C5+8MnU6YuzEcMx3dNeTGzFpGNeSTMlg+YiTX1iSbPITrSToeKtjzaRZmwxDW2zoD0wtJtsaH0Xl7xGL3BxJZ5qzqRlrdP5lNngsV2rHvUann5cv9rMjxfzOiIWgabotJmYWl56s3EKetJcSzsU2Bn8qE7/vlv8pwtmbzFB7pnwpFEOeB9p1Op4CcfPcOYrT1ijch+AyaaN6Mh454MDJyB1Z/zp8nnMIPsoGRph53QThLdCVWuISP+JuP55qzE1ruZ98hc7KWpWTU0mxKQhKdV1QkVApHbgzh6eZ/YTFM38abkXNHzbAZzouiDmdWkJQjP40IaypIr0rRFZah2sTQYCAnTyCuclrqVlfkJQFbQn2lfzIkfJy0bv/Vrdveq15UnczQOyBObqbz+ShMBoX4L9pPD7UOKbieZGtJgwliQgaLlyBugxIciVCHlzyWc/MsNIZ9105k5a1cEZZYBsnMs0gKW173l1D01Keu8rXc9OV1lt9yo/8NJICjkI0/9leRS2tBNtDITWt3PRbNyprz9U1+bvkRTGiO3MgoXQuvtx0UIfDxLV+uViV2+eS81+JbLUTECAJtKhthqTUPbgtHQIKeRbma/SoqYhuIIEn4738cHpneTDkdjgPj1WFcikEBuSruCbctR8taiKg5Y3NxsYIxWGaf05CrDg//BogT5WZbKupjc8XvAnjhtk/M7JE/ZaD+jKf7ovzv9a+DOzxoK2GgbftxE7+IjgIlbcbz4Gzgw0+WBPDminnqjf0dhGYEqGh9ApkUaHNCPvoQAW8pW7P/CVErclTajz5SNSfQ/17xZDrQaPjKpKJmO5uQdO4emJry0L3/AWO9uqbkCMnbqwnFl6X6RUFOnKxpzdrM8VqB7o8YPR2Xk6gmfR19CAo82WG6+12gINWUGTV+5hr9m7m8/pMuLRNSJmdtZMZdYe4Ok4OH53aTRz0OsqK/DlYYT/sxrBQG8zf3NgOFro71NmqzOKxWV+/GLiDMRfG1WHiB+qIT2Kv/KaippKurbpyn0kX8ounKHeWPqlSRI3Q3NioZZlPfHm4x8GJOR3shgcyaBxYq5kl3Ez8srcEfxCpMwb3lyyXDMdzjEUYqeisYx/ygH9t8uvwwbawRf3Xq3VaFvhq434qEXg4+KaE+f6lvSWYGXHIqUN2MGL/NusMfmUDsbCKCpK3t0sQwxiWXO+8Er/cQWxn4cFQJPp6BxDbpP6GYuhkqn7l1BVZ/fEjoZwQy3pvnmKhNXJy1KYw8sT7uG7ZuamAN9YaJ3lefZw9QMY9Zm3u5Vy3kUqmjAJzPPYU6l5lZ7TdNcxGQFZS/5Wt0C/BUvAAJlwAjPUMqfceYmtPqfM8lZyo67IIxalnd8iY8fBpvM30IUVpKrFWWLTOPCp9ZXYHU53b9tF7O3x+KWvJ1sdWorv+fND0VfnT+NRiVPK3Ym76KT3kEJzasHdwQBlEq5JrexX/6qP76hqFSrd6qV2yo4olfTFZFYyiUbYVf1Hlo3zI9sdzbbdRNYrKgJ3mpjFu6wWYulZ35jJ8tYbLRWPFHHXj+Z7guYA9nkNJJE/1WOsuBEFlltrmQCiypW9oFjC8BhwNEANSyEeqYc7/YRpontDhw/zHo4H+KUWTkZoTgYYhAJNrlR5fGo8A7j205SdiFVqLRyfz2er8+OO2/1SniuPSdkrq4zBFaRdKBrOoFF3/dMisR3rzXptR250bh0YZLPHkeu5BJFkz8nzCcpH+Jx0b2T65/Fqd0ND8WqxjxpwF+K+8uGXPOViapLwxAODwJ3mU4aSp69JG3MHjBzjoenHa9mX4Wh0jVrLI194r2Ly2BTbocRG0Xhdx3g/d7qbqWUZqR25kTDtV6GUXKCWV+zUb6ztgDsSzhfWwUJ5rr9btAVgNbegpdTr44w5cTanYtvU1mT8e7flc7qu8zecUrN7jP/TmuI2CeVCm7hW5UsS6yEHlt+fEh/ojjoAHLbQX/DbKyoApr8ensL+3y/CIAAA6Qa4dD6YSXwhoKhvvODO5CboJ9+ABicWHxkbS2ubmz0JGwOZm2sTWVsrWZq8IpHfrb7pbGBAgOSPF3xehIrerifEVF5YZIJ/CJ611Nxd0/1OzMPtqHI0MrW2/hRv9DSh/dq/Rvu9mghjD7BWY1mrvoOJu9MK9AoNkDvN672nN9+2d7eaypYKFOS9v+GsRmKA8SF8gMJcSku/U1QAdShmdGWAemBww77T3o0gvfV5vthuLMO9FwNAAED/jqz3JSCvvmDqNADgXtSQDq3gH6uJulc1pKy3q7mSAGqAe//WGgD+uHu2wUqA/gQIazEAfwziEXIEAPFfNJwX4d8oWgHOEoNfM3dUNSd4tfqThh+Z+B27o/etMGzhqUNr02tLmE3EGbtdi4Gxh7wD/u5C6r5+ADXi+6rDN92JP7C1ycPrQ2uo71OUYwz/3wqLT7/1uY3tWUCQ6643KTAAuPfjX6zs9b+gj983YF9rfdbIB8B8o/23MbB18a+vdkBL4EwEOEBXtsN82Pd81vd81/d8Jve0vOya7CKCGvWIG7D4V7hqTvVqTtdSWjbJak4G9GpOMvT6OPjXAQsy9fo4qNeD+kvj/fTNzdnxQE/931b3fTu8FK3uZQCArzoOiOhHGt1TPlNMfeEAf1fn/Tmv2VU/Td58wA/IBf5Q7oTQcEfQFomqTYA2os+be78BNnz+taQ/ltXGwRiA+hQVdrsWfCGswUYAhBwYF40VW2HHe5G25OZhnaJctzXzO4Es+XImIjGg9Tb3CHwLxBmxffZCDEx4osy5289jNx/L+y6uZ6jsASA88TQDcPE8UmM/4EsWssRx+tryzDZ36H1cgbwDAh0wv7JnOl9r2xpBHkDrpjU3BwkRpSsXK1D/mY0KbBoP41dUTsiNOPutLz/Cdq1HqMvveHnyFIKa2vZ8ZzXfgrverK6t29i8eC01w/H70DYgAPMfESO38wW7/HP58vRkvwpoRhBbb2hfVjD+uSBy7AwRff4AZxhY/KpPnL9CPIljWwVPcozsmr/RezpfP8+fkbpNv0M1PIxDoDkPKvvLSGhLG0lc5oU+8ej/Fk/oHfn68CKOwD7wIpm/iYRV4F9TDHi2fg6Yj++hUZ9N2mNm0wwJwJYWbu+309fd2w1ULIhcNbZthgKvZ6utuyW1x/f9l889X1jVUCD9uL3wK2d9GeDdSgTc9wHsICJeJLQh9Ivm83uX2DbQM7L1LvOOx88IoQrCKAzNK4iBWxiMTQD7ukCUvEAguY64uJ7/waYPJA6I45dGpzgvZ9xcdm/7DwHUWEac5Ln7LInQ+SRQHFGwnqDyfAHKjHKyLf/PQ54feYKArpzAxlyn9hxhgqmUNXwQ5WEelft8uwdRHFHyHgyBmZnDvQ18XxUWcKKCf9OCaDl7aT/+Noh4QKR8AAUs+tNArZ9f469IFMFvfhKjfDDUr5z+nGxLT/O7GptGgOZTK6Z3fEGuIYWIuFzC9uGRv5VDa6CXefgHxjp9IAzWu3wgLNcJ7Ps0hHEA2gSIQzMnU1gF4xHkxxXkOPAfocuYCPxmPBXpMQYL5BKycGBmdjv0sdGprZyuvJakNgIN6wmEhyVtOHdLvmMwJ4ta8L80x2ACLGIRrGVKYRVk4hhsqHzsHyhOpIfoTGhK0mr78i9/rcPQ5s4Ff5qDu/RlAHAwJHu2Bb8GYGeAQBgFAzATGB2QGyOhL6U+UT8iXMIImvkDYOgLAFgwIFmqqnJb9wv/dmIBJH608/uQnyaIwsHS1zXffbjlyn00LGcsQfusPfxjVnp5dA97ZNexxMbgSTrV3wCcwkCYlR8Yc7U+g2O/AGe+nqcJLuzgSS2IfdZgyr53kJK3vPTvsL7QP52N878Fk534ohJ+Hanf75LL/wKVjELsKkn46zAwFiJkAwFwBz7xWwuD1R8WYQcGx7/mOJfR+D2NdrSgS+I2oDI/UPz3m0zmO0so8U8IMdHLbwnYGaGm4UEM2nY9njZgiM9zft2/8kAeGiCfkx3Ehf7N64UO5VtTuhCzJuBL7Hc/GYwFBIOTGDwMZB5SJYIr0c/oS+paeP6e/54LQHD4WCAdMXxQLoXGPXxUbqXv+AdP/UPLu9nzoW90DF/Puj/m3C8eknP5Dv9lPpuiXEqLaRD2I00U//M85mBenP1VDKd/Q+e+KMp30x4NGKW+aCiyH41yEquKEaBeBGTWvjWwSOIcArYwoKaytGWAHFoGfdbXAejiVw7k26kbXtMCVCPxIwwS9DfY8AOHjv/O5dvrGaI0NJW8LwYKuYSO0xjTWXk3XlVuGYyGHtn2NPCiDc8SGBuGuz4D4pVgxWRe3DMQBRsiFpPntvAHbIUimaNaX5tcGEwZMx7tnwDOpuW+6WQf8SKO9M4nF33YdueO0ldWhQ2U/1RhST6gJAYQSEtjQOcufpp/LjUB2R9ASOipjDU5GIkCCha/U5H6EW08d5B+FaUYVn2FjbAA2XFFyh/IGiaChj7WM9c5EwF6lPsSP/K//SI4MEYXS4v7BTCxwv0hUN7ABX1qpQZKoDhXLCCTqhB8gC6q9E+qduxb1DgqhGPk4A7oT9V5YpzgU5UPFNH228Hw8koV4HZVDCBgzQJOFrp3QWcw1ECYXPw9iXK/rCc8fRfz6YRQTA5adir4xBJxeNpE1ah54132ZDAkXArIe2xS8AVBnx+1uUvZ3SGsUn1D/RIc37U7sC9WgHUPcNdl/sJoZdbdQFaQAbANp2DxoaDoLsHkhAG22P1ocGFkHVBGbERp2BODIPhMQ3PJ8sCrmwHKmqu0VP2C7EDTyO+xNd+5If6JP/gneZbwXx9c7Cmqv4c+mqA9jYHRk4UcpHEQFoEqNACqdxpmcZU/hzy9VKBM8NLTvWmjKBigivap2hZl1nDiu8WkPSyibZP8+HI902+2OQCPE+x19wIQxdbPuG5AoO+c0Vguvw+J960jIuK6ZXYtFgLbc814i/tgsCKr4GPd4GOF4GON5tE522EuXgP8wvZKSkQorDYigV4xfyzFtuMFnfsOeMSk1eDnoE5u6I4Xd6ABEDNl0KKB/Eqg2djdGUYBYjb8dwRjLIBKt+u9evdQsOwaT/3afo72B40H+BEE4XjVab7m39Fae9ALsALwF1ZG5L+Mlr6RJqa5vhw8Yj+HNnDO371YhPmtlwWCM78oncQmRFulvpwXtfnA4m2Or/KtHr5P/0gvpnNaylmg/4eze4zRJHgXBT7mjm3tmDu2bdu2bdu2tWPt2LZt2/Z75n/vzbk5X0/Sv+qkU6mknqrq6ifpTgMKySAZCG82RYJjPsLcPIcRkIEIv/Ftw7fsZwHfUIW/kYgge0IevJIVHTCaEkgG94gSG2eN9AVUrl6IHEuxHC8i3skvbfYEUVXBDnfrCzfzR2784C9gvPI/A9G+6dDl8an0A4AEgikOLAM4EedD8VMT1cb1c3F64WWgtsQDr6ngemXGIfZcGTX3JMG9zVxfpl3AiT3QnCEuPOlPfw2j8Zz+mkbbOX9GP0RFf2wpgONzLces2d0ch8PJ19o0OUGUsbjFjVRN7sb7c2j9lRac0/iUx/So945997nz4HTrr9AbYo4I8TUY6g3RqAaObP5cIQBvWju7qIKs8zb9pcHRe3/asi1eAN2B9qh8KWoYqkolN7d0g30pbF7AArEWRDZke6qjD47iCGJaCZOfzBYMb2vXp9yNlg1+jS7G7fIJSSNMgOMNDBtYFACpAIBYtjsNL6vJ34cO+sQDVnMu93MRqu31p5U/mw3/yoOnRd69+ZQCdOF/5I3Xc9EV+zoQuYwMEeii4Ql59gWCQRT+sgMF9YxMPqi1WPHLcO3K+q5sDjwH7EQN98xZ3r5If948JroD7B7X3T+rtddBi8bsOAXG7IVu8zmAleNAkV4I3RV2CQXB8QMxvFYEQndJt11mC0og0qG9e75JDeQPW+MTFuwGiwKkIFvMvgOu5PtEdwHU9QBNfDiwdYUBs8BaNpk2oN0bo2m9g3yZs6nQro0NvyC+w88nfNwBO+JvkO8hv105x1W+MzBm48A7ZA3YSZwmYku2moJuCfiY3WpbsFC3+v5dNfWN1LeD1DkiL8L0BrTH+HrgJv61oh3aXpgASdR+OH4eZk/gYIUA4Z0AKmox8i8wroo5IrHZerj8eTyQHH9I2kdXkMGSphDMHIeyrY6poqR8+4pxHBhCHkATBjMsxMMOwIdrRVQcGRVTmqC+YI4cbDwN3T19T1AMRi00OyjfyI47/u0FyNstV19IBOSYtnxOkQGix0lYujycUBzRxBqNAlyfJtA0JR6/LlpZOMzcUKg4ngR1uhDtWZkwXd4fKoY6nIzbXdp/BMEZqyZSteVw+yayEHL+GQqd2X+Bcl9VqII1yK+CoDcbhzldV+2w1yneC4AB5WaBq74iEVgPrknCuSWoJCehfboFeTJJu72dUx2IfdtKP3sUeyQ6ymGJFHBhaw50Nrtws2v9L9zfze4e5OWV54H+G/F14STvck+t62dy5qNCCQQvIhFFzDLpIrMRc6KtAxepidMpYzjPJZogzfXpsxFToryLBmlzcGLDVCEnoPqaSVnPHooVSS9RIaxDj4GSV+dbKm73AusFKYuJjQju/QSxVrlAFM0+SszdTL4GLBRzFrD03gK+zvtVQufIL7NA9aDXctEKfEcu8BIY3w9ADkdjZKaMCQX5u9rrX+EvKjiLckZIJM9+pLdcAHn2Ts5861cw9x5C+k5PQ4XzLk/jhiokIRf5bhIiD2SSomcMGLYXizj3G74VPUeAEBe/zaH+wsk1oiAQPOx5faXN2pAYxes3hwZSfeOrG7qLog1HRC1jhMKDC1Fty/lU+0wG9PqVkS75pZVu2MH7Gbw1qjVxAn2E6VCYUhPY442yMSbfFPsRqoVcBkgJFl4Hc2M57ofht0J8/SG1h5IEFw/OJSqOcprVJ1G5RyAFGMe5Aqzj3IahNI/oH0CrZQsu07q+TNLz3/i9Knou71uWJFIpAQ3tPbCsD+ct598Gtjg4GPJF3YEQIXCDO6gGABJdQSXJaSxa3mCSeGI+uVnQLLXe7Vp3tMMo+FZHweKaKl6hpA+IWykprEnVb07i5L2CkyBGxvTGoBOhQZTHGKj4YNpxAN7xK0Smj0d+FKTLHky8INLH7wDymx4CRLd74uAPcg+DfLWgYv63GHiOjjeTTOseQ847Wnym1YHXashZzNvfvn9+IZh/ayY2ubmYLbpR292dCtgrzG7mD3SMukWJwbFI6Rn3psxCHLO9DquVG/mrhqM=
*/