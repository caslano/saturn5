#ifndef BOOST_QVM_DETAIL_VEC_REGISTER_IMPL_HPP
#define BOOST_QVM_DETAIL_VEC_REGISTER_IMPL_HPP

// Copyright 2008-2022 Emil Dotchevski and Reverge Studios, Inc.
// Copyright 2018 agate-pris

// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <boost/qvm/assert.hpp>
#include <boost/qvm/inline.hpp>
#include <boost/qvm/static_assert.hpp>
#include <boost/qvm/vec_traits.hpp>

namespace boost { namespace qvm { namespace qvm_detail {

template<class VecType, class ScalarType, int Dim>
struct vec_register_common
{
    typedef VecType vec_type;
    typedef ScalarType scalar_type;
    static int const dim = Dim;
};

template<class VecType, class ScalarType, int Dim>
struct vec_register_read
{
    template<int I> static ScalarType read_element(VecType const& v);

    template<int I, int N> struct read_element_idx_detail
    {
        static BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_CRITICAL ScalarType impl(int const i, VecType const& v)
        {
            return I == i
                ? read_element<I>(v)
                : read_element_idx_detail<I + 1, N>::impl(i, v);
        }
    };

    template<int N> struct read_element_idx_detail<N, N>
    {
        static BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_TRIVIAL ScalarType impl(int, VecType const& v)
        {
            BOOST_QVM_ASSERT(0);
            return read_element<0>(v);
        }
    };

    static BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_CRITICAL ScalarType read_element_idx(int const i, VecType const& v)
    {
        return read_element_idx_detail<0, Dim>::impl(i, v);
    }
};

template<class VecType, class ScalarType, int Dim>
struct vec_register_write
{
    template<int I> static ScalarType& write_element(VecType& v);

    template<int I, int N> struct write_element_idx_detail
    {
        static BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_CRITICAL ScalarType& impl(int const i, VecType& v)
        {
            return I == i
                ? write_element<I>(v)
                : write_element_idx_detail<I + 1, N>::impl(i, v);
        }
    };

    template<int N> struct write_element_idx_detail<N, N>
    {
        static BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_TRIVIAL ScalarType& impl(int, VecType& v)
        {
            BOOST_QVM_ASSERT(0);
            return write_element<0>(v);
        }
    };

    static BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_CRITICAL ScalarType& write_element_idx(int const i, VecType& v)
    {
        return write_element_idx_detail<0, Dim>::impl(i, v);
    }
};

}}}

#define BOOST_QVM_DETAIL_SPECIALIZE_QVM_DETAIL_VEC_REGISTER_READ(VecType, ScalarType, Dim, I, Read) \
namespace boost { namespace qvm {namespace qvm_detail{ \
template<> \
template<> \
BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_CRITICAL \
ScalarType vec_register_read<VecType, ScalarType, Dim>::read_element<I>(VecType const& v) \
{ \
    BOOST_QVM_STATIC_ASSERT(I>=0); \
    BOOST_QVM_STATIC_ASSERT(I<Dim); \
    return v. Read; \
} \
}}}

#define BOOST_QVM_DETAIL_SPECIALIZE_QVM_DETAIL_VEC_REGISTER_WRITE(VecType, ScalarType, Dim, I, Write) \
namespace boost { namespace qvm {namespace qvm_detail{ \
template<> \
template<> \
BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_CRITICAL \
ScalarType& vec_register_write<VecType, ScalarType, Dim>::write_element<I>(VecType& v) \
{ \
    BOOST_QVM_STATIC_ASSERT(I>=0); \
    BOOST_QVM_STATIC_ASSERT(I<Dim); \
    return v. Write; \
}; \
}}}

#define BOOST_QVM_DETAIL_SPECIALIZE_QVM_DETAIL_VEC_REGISTER_READ_WRITE(VecType, ScalarType, Dim, I, Read, Write)\
BOOST_QVM_DETAIL_SPECIALIZE_QVM_DETAIL_VEC_REGISTER_READ(VecType, ScalarType, Dim, I, Read) \
BOOST_QVM_DETAIL_SPECIALIZE_QVM_DETAIL_VEC_REGISTER_WRITE(VecType, ScalarType, Dim, I, Write)

#define BOOST_QVM_DETAIL_REGISTER_VEC_SPECIALIZE_VEC_TRAITS_READ(VecType, ScalarType, Dim) \
namespace boost { namespace qvm { \
template<> \
struct vec_traits<VecType> \
: qvm_detail::vec_register_common<VecType, ScalarType, Dim> \
, qvm_detail::vec_register_read<VecType, ScalarType, Dim> \
{ \
}; \
}}

#define BOOST_QVM_DETAIL_REGISTER_VEC_SPECIALIZE_VEC_TRAITS_READ_WRITE(VecType, ScalarType, Dim)\
namespace boost { namespace qvm { \
template<> \
struct vec_traits<VecType> \
: qvm_detail::vec_register_common<VecType, ScalarType, Dim> \
, qvm_detail::vec_register_read<VecType, ScalarType, Dim> \
, qvm_detail::vec_register_write<VecType, ScalarType, Dim> \
{ \
}; \
}}

#endif

/* vec_register_impl.hpp
zGf7TwafDUltentWUIecJMkpefnupuRpU5am4GQ6TvIKrzz6NEHXO0iX5t5XbHJNwzKJT7+0WB/aGX91YwkAyr+hOFJWNUcjsAGgYgVZFVr4LNgDEcw0kG0tCeMtluleNlq4CuONh1GDSulBUFtTH2a0Dum1y7POzmdNPi+OyXtOVXUMmA8TjicWtmHc1JPiGRV8FrQQOk01ub+XK4FIc+iBq1gseZGoOwGaLNME4bYS9HZT6GUWJHZaUqNugCfHjjEKg6SdrI+gLj+mllCPH75g2NDxVIQ1rhw3gtbyjipM7k/yQb20A9+CpNPq9MprKQ9IlXnz7IpnieHLNMrKUSNDO+5dVXkVYrCWIR/Oxz0raZhYU6ZT+XPgj01JEKqrMo4tLC906424FH03o5qCGi5nfmcjBhqQrMy3ve92dX5qWOuGDvSaZcqAQqVChZw4EMbGqqUVuABtNSfvImpQpSuG0WkbmVR0EZ5aqDBAD3BCg0VsTvRvDHhJIOcMNDBvvBRxQAleFSnbwJksFNxqwduYLV47j6kdoR5HUzG85Zhi0Q8so9/V+iMmMnr3rps4K0llNgvcVU7u8nzHvCV/G+UUU2yY4wQ8zYV2BCfn1TEM2gBNy22ifycCZDGxgfo2ussnBW+K5syB/4C/CiAiU4wGu6/EEUwFBp22CmuFzs4NPGrZmt6tjUliow1gUO4qh+nskhDu9kE5bfordeySmk4W++tRz3SnZU54z3Dz3OEJQ3q0FqAR1+2R8saakNouA5E4TSmrqHErfuAnrGrENQl5gTOBPTKGVavZoPLvDM8YwZyPZRmF57dSGdlBeUY5WxErfq5zGaVM2arnFIrEp6lzYQsXXIrAkPPN74t2ZPuwm+VNwtBcQZQR3JuoEeUDMtYpHLfgCq6ZldrQXqFk2TQtolN/W18KOSjP6e8woTdgFIVIFAJrrjYK+aov+B7P8iJ+TWNvlDP2JZ5nqisK9rTku85GhzsUSglkqguNLVHKmxzcsHvl9CqqUnqIhjgEMGDDaM66d2OUsZzDdMnCtI3Tuw6UZb+G4vrzvHQFmbJsGWuvRECbGZExRlNxOexhuLjiKTOivFfCmkfHzFx9U2HdPRdguHalaMP0VXoENTb4BNUXAOWwVuW1lPVHzqVCXcOK9pwOu4gWDYzfFEjN8Ix1/ouHSMtY1kgyGwiFIBZQjX4eKF+keRk+NdFm95+7WVHH+5XkzFp83amYEvuT8j2gel58huWn67i9JBa/MWuCpXtBVaB9V2pub75u2HoBm9Z+V1Iz8V0ch/guPCrwYw78DHupbpHZ1KtJRVVuz2qUgGIOoUyNVE0YaULknMnrHe41KzAP/zQIndUCcCJCOcmTuE5fwxbfkE++rThUMZS28Bry4OA7Umjpj8rLv/l0cqbdX0Pud/0OR3JtcNkelV2KmXvhJtdGUctsCjwme3jizA+x4P9EKtQcVnnoQDkbcv74vCk5WCzI9jZNvch1K7BLuJz64KFpQIWNaLr7sNC4czexPw6WxuqdOqwKFMx/wwO1hkkp1ulXLpRl90BqYhLdwOJ75TDPbS1cLPqurl1GAJFmo2oZHSw8JqReKyQGJpmRAqQr67xO9vYRwViW39HQn439uOzbtBRpT8jxYGPGjNkUTNnv1oWJFQknb1UldA3bW0S+TQggdiVDilJnnKuiP016mNQzDB25+pAYqJ59bcvFBqOY0UJ1cOQ4FawwYSnvb1mGt3Onc/OlmqBO/L4b5ZUpF9OxVJBGqBlPi8/NnUevB9Js5EPjvSXydAjcoxDwyQcB8c+ebwrPixeDcDR9ZsLcS/JELMxa0bQlQH1822o9B+NKXvznsU3q4xytTdsB2gyG3ixWfBbu0IW2HYS1rSl9Vm4VgSv8XrfJcI/q2xFXdk7wdpl8PkPXJ3+5SvDLzZ+aaFm0H/m52CFXZB5dKEUQSjgCVe4qMUaOl68cns3B+Qr42K7tn/2vhDvCqcLpYl260wlq51UeD/fNwncdIl+q2Gj4gR3PcL0gJA/hSEz0XQdSN35Fem5FgOwx34lFGA8X0DPAHTy7gHuvlvsG0OFzmpVHbO6oDxMVzdh2Mfw2AUgcjHkdyBpsOXP/758FGlIRRHjQXprFFWdaj5TWXF+WJ+y/BEW9z+3Xv7a3EwAZnL2+t91qagjia8R9wEJyeDt1ZLRI8HLycvDwSFSjcHjgQIl/DjAWI5puNjWaNfIjNYYiC52rnfkubTWrPlZRVjstmi2fs9My+Pg7u157fL13P7aJXdkZ//unkCMvg8uNES1YIQAdE373H6sRvqSDQFF4a7vkqCHLWWD6yH1T7BZqo1ClQoDKcRaVcGxKjDXIhiF3scFFADwWhfCK/kQ4XVYleA8LUGUleJiWMpp4M9Go0ZaIahkQJIxDsrqHJX1oBPzui95Z3dil2pH3M3subNqxH9ufbT6WVQ4/yPAook7/Fug/mAwirQEHdVqS+b3XpdPcDAjQDAvWU3nyhICXuuZ101mBLAeAFCEwRsKNFvtVEEFlddOcjufmjurqv0X5NmbPKoDkAHHb2RYo78N5Jd0mhqoG0l8QMbrWYw3TCPPwuUz2xKh9kKIeGXAGxLTc5zib0TZ0qQK2NUDZI6zojnrWJUPoMtx0rQCMDPoZEoTHkNd/703iI4pfgxoVKTlGlVr2U94+hw0y5/baQKMKmPZQDvodL1bxkmE3YSlsr3TOI5NbyEIMM074rSw4qbAfEgiyMUPdh/TAKPpV8oYUi/imuFiXCeE9/zZIYRwpG1QaHkn4MxXgN4l5m6nGk5ymP4w1iMHFBzGpGJ0m2cIW1PE8UhnDoIcbtbzDQo/Im04W41sXEjVyI9jpVKE4ThXn2VtrBzQjYGNshCBhqViHiCINbnB+6MEIe0iqZOi/AhHbDOzKDG/Yc9Gh+6Tv5Uo6UpobdQTooJOCzZYwm21/wI8qUxntLgeroeoLxucNHYS0/am4rvQ4leldn/mQyijMpDhBKKN1iLQRWKmF+zP+qVggYIsdMMIHascjbdINmFdbD8KGhP0DHkYqxolEAlyhh59VQIIXfA5oTHAltwVvpuA/O2BtOOZbitW6Koa3QsZIV5m6oYfvCgIdQ9++9gS/9Y4eAK0Z0kEZJkCYFT14fb+pD4hnxGKGLOhdLeCp/waldhPy/OOLMhgZqV2Y3/jUn0myJx+4gLT/I8S6FDNyVSacVryypik0Ise2qMdsNl8Wnp90J8Rm4yOnBlxxDlMM/Anmt8oD/qK2huo5CNI9ToLzAmZ1HAfwGQ92n9cv6MAwvhk9PGS+ZmnXjTda+rdkaYgtr/4m2pq8M79+WcPpVv2rSO9vwSCMyJtaL+rDDPHWEqx1VSsBTScFHTWbFcxZ7mAH+ZEAcJYGset/GdgywO6klGfTS3pKh/tRfPNN1TAqpWLkMhuGA36gdhQK8wjexylTvo7DUd5p1AfeG8UcnOxZH/YPVg9ziEi8gTlXTr6YWZe6H0wCMEyUDpiMWII7k5hEgpVZjTSJdKrYAruXOAILHCB+OUEKvh5pMPYwKsNvi8/u5WzHqVkdJZwQhzAJNswpkigYT69SeFE8RXs9ioI3JBZZPFJO2D7Q1zA8DahQikvJG4EMfhEE8ZwctKIkp6BeUGwydB9yh6QGJ0SQnJXkJZ+8Fx5yNTMKNW7Qzv+0kKWq/T1nkrtZyE7ntLCloP08Z1f7GdGklmZTYgGqIEHZAXkPp9FNrLE9CHrgHmqYwJJ3AAFyZ+eDWWSyGPM1ng5YVdCivgsmDZ+i4J+OAPb4KihibIAewrfkAVvCVBrm1LxtZHxp8ajFojEDnDu4iTylmzMp0Co7mFcmGctsMFKFQ220XJJge+E7q/bzrwWtJl5elC510OoXYbt5AXWzKM51frq2HHmB/x0hg680oYxXvWIlyLu+NnCKQAeX5KANBMDJLWwhpM20gFTCyTgxhH28xJFJPKs/2Cab6qPCRkxKOaVhPa6huiQKbK0gSOUxSGF6uanhPUVprUCXZXNVQ1GHfvaoJbuICWqUws3r6LYnkQiUjQUsZUNHd78P6aluzBsLPAZEMmQf+7AdUzZ0fwXY+jw34npEz7C8heC+SMQMyGaosqSCeq5ldx2ACFTDZAg+/CScWTj7rWAXj7na2IlUdNj8BgOBjGT03kAaygUzamgJLiBlL3cYB16QJf6IN6BIFzE+O36iMbD6IXj3dQaMgET0WvGoJ0FxCPF9CGUipl0Co3e31KQ1Pljq4b/HBjNrcMpEDTK4hErj6kpyYo5k5G6NTFMhp/x+uYEaG4GFc+nQiPVxY0NxgOE9gknmYXHFUSIKrHFRRVQAvVRkuMvkgkqQ7fCEAFoTbgASGhB8gpKJxEZm1QoToesBFcPheIvGZukIad1RhHhkxUp17mDiT1ILZc4aXa5JfLOyo2L0yEZmTQ4uPCG6NuivsYqXzGvAltqA+EIBpMUFI8Ana/oa2XL943cheMH4wmrw3v3hxUbF6tjGCG6ACNp/b8QmSu7AjFT9IBfwDGr/zsTZG3ACeGD8bnAkYtkOzmXy4dZQ/4mT74unnAexY7QFLEUyYGV0uE6nECGnWwG/KyKnmlQ0Vyvi78svNlISGB/THhOMOYI9EJuwqI/PvAKLabZO4dQeBKa4wzFmNHJiAauauNyfEOmGDaefuN2fBGI7/BIfWPIsVYglkNJRqVTg1aAFayEHVgJJ+sAecCtL4aiC0Lcqc2hVvAhObXpa/7atD+mUMxJYIafA5wkquosfKZxGY3C2m0vwHBvIBgf5g5U4pwU3ESBPfcJNTwoTso7TFpPiDqJadDODZqBOYRiIMiarWiJKGBVPmI55kxd6MDYMHxOweEx0G5Nv2VbrCwWTV2w0ChMW0yhxKccRsra58iekC9YDl8J7F+jTIbPbAq/WLaJ2xVNAqtdfcB596gDdEgnfEyETIcNDhXADgL3mw9Sjm+MAdBfcmjAaY/Uk2DyL4mXLQBfC8DcDnAdZrrdjrD0RmKMMrz/y+xNDr5YyB0QNM2NDQ6SsR9gD0gR4NRETyPhbS/JDvfoHxdfLmico9DNQgxiGP67oZ07L+MPH/kAGUAL3DKQ1kmC+Cy4B0IoTcAVD2f8jZn5vhp4iS9oAwk6PJC5VLEfDGJWFA3B3r1xmRphnRlgJBNgoqIDOQFo8Ze7Om6q0rxXvT8ksFZdhKimNKzHSOFQcHmBWwAxXlONP75iBVTauDMavWDB3+eVVlSOZZYPJEMHUslMB57CXGeIQpxE0p8rfFzSOg15ehr2EuUehwn5NFidG/Dc6IAC8C06hMJMrdBGzRi91xEL9iokwHAj1KtXwuJr/yZ/GPsmKqnIlor8PnnwlQrhuQJSS7mrg3BfsKWoxXiWDCWDZVlzKs298/q8F8HQfRIGFVRBAL5itXuU8ap6ciqAfqJmuFNMZYh6PxN7ACWAjGJnzN4uOPNaRcB30tABoAGjdDGccKl4X+pfYqts5/8O4yYrKDegFSpwuYwOtrEKiMKdbz9tyyN6j/gPBUZnBX+b+X44rsr6jsnUu6H44seLILAzDzJzoPBAt3nCgLXjBkAUrgI3snQDiLE1tlYR7QjCX571w1p++3Bi0eL7U9BQtIne0bo34IIlKzaTExBq647l6Ta28lS+jWHticDHD+ON1+rkgIgJM0tJFj9W5vCiCKNsJQZnR46M5tpAcUfsKSlUT+GCutbovsh44suOzwf3XBYV0CBIB74PofaZkRyHjyxIqc/RUUcE7Is+UYTMvRp8FNEkORN8AsgT0bwg+aOlwyTsy5LEXq8rI3ImJrf3WrzlcJNKaCXoXP3mmQBleKOhDC8jQNIlRCye0JBLuYHAYOWdoMTE58tA6mP+Q5uI9/c34tsHpSpBmND7dNGbEsdMxc+0gpdgZ88KhqNaIUZv0vKm2ri5ipk+MWrZy1cO2bHMPBP757fAfF5ZEPm87lyeGLhPnIuQSII6Nuc/9ALPE9jFz6PZxPloMbCBWqfT62FCNGWSCPi6tWNAeD8T3Ia8h2tvv1aiKI1bcgimvdpONhp0D+yi+99gq0u3B/EyJiTeMTY1DpTL3fYBo4WM1Lnf9FiitZkwW895oY9uvnZNlzBE9TJ59OwQYTr9MPdi80YNN4woN+zZqIxCVjNje/I0nNMO/90V7IBsedCF93VqYbsiG7pL+kW9ywLTDm64Vde5ohfC3VRKpESsrrUmEMDEwLLFhrKk/ObBwcO0zQarcoMzo6UIZgJLWb3RqoEWZwI+NQNg4jjONlPO80517YOhWDmHge2lmOILjg0e0wFznmCEumnlzQ5hvQQFKEARQM78SCY7aIm7uzc1xgbi6Zff6EByImcFH6CGTa7vYCoa0hcKiwL+ixlEExWfTBlKiNz8zuJlcssAcyL3Dhe7TzDUtYlmkoLCy5X6vYg/4y7vFn7nXvbiP1/o73Fe+zPc/ByNueSAphOiJoNOtZro7nV9pYchyyKQwYHHCSGIU12iYPDTiU/kad+CkoTaYwyTtxeUIwg4UoYwB6XSUkQAI/18lkJ+ONgVR56G8338knv/iuKFdLA9xng28a9wdc7zYN03tXDizj7YfvHWaLUYvYLxmlZXTs3nQkc5wvxep2M3LpxwWv7noyLDP2Y5d90ZIyt7rOhkLQSMkcMdVWXGmJiWOHnPKCxgg0UYhdMBzrpcWmuF0AHCqqJWpsjEoCKGyrw8jnYlSQEYyu7lbBgHaAVZWI/Iyi6gZylF0o8kI1zk4moA5UWnc7TJwSu4NuuXpxyZWsKNPcy5hJr8FZQRYcbCG3LsikAsi5+VBgtoKbAnP10JDGQoMEHKIOOFMdlsQWWlGEnNqkpwkLXob+/NVNfYg/yFxZOlsheonE+QYTiw8gsmMZ8IWeIUwki7OaQoQx+2ni4OVmy+mMiYQKzTZKgla7skZK241AZQ4/SxuWdHZ2jTxqfJ53tl++BfQ5byhzkWSABlaUflF+jk+VT18QYv9zC77CsvPJd7e1v5Q1r6cG2U86PRFceFSrXRllFpZBsVSP+qWPVknMY+WiTpcmDQmSmp0vFoI0ttZe6uEWYzZUXc+eI7KXSwogJ3qXD95e6/TlbTS4SH7wDcdy+CQeSxsMnlMnVqVVm71sJncgZ/97OFeXnr/ZjWC8RIOnXj46mH7vi7SF9y8mPlwk9VtvmmMf8LZ1XX3ttZcCZ80hRgRc/lhym+0+b5HeT5U7ptYrTzDmaFtf7sKqvTtOthx+0YiTTdxJT31Orjfrle/GxF5ykruHDEX1D4fFPAYkdcrO3psQJVeY9RK0jGspVxld7xbDNQXicFEyelkuvN9DtZFiH6QkCbTASOdDcywT9gMNZt+U69Ba9xmGtEju17MC1Qtok3CrCMfU9rwtjLQkSV6D6EwerP3+yAgxZjzbouXEiHpImgOJE/NRKh0clc146hHNbKWr6NzDA+8XqP0t5hZ0yDaB0ejI+DIy2rfI/EihdeSaOuNmoGgpwwGORjRjCEwDL8iIk4Gi4WSZ37AlVVH7697c3Y9/x4TTG9+cWTpfVsftRT1RfB1K51OBkxpm+2mzjRFULln+pndA5+e3mVm/HpyVbSuZb7kkMxtrXl3Fqz0ariFUuNXxm2R2XBX
*/