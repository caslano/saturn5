/*
Copyright 2019 Glen Joseph Fernandes
(glenjofe@gmail.com)

Distributed under the Boost Software License, Version 1.0.
(http://www.boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_ALIGN_DETAIL_ADD_REFERENCE_HPP
#define BOOST_ALIGN_DETAIL_ADD_REFERENCE_HPP

#include <boost/config.hpp>

#if !defined(BOOST_NO_CXX11_HDR_TYPE_TRAITS)
#include <type_traits>
#endif

namespace boost {
namespace alignment {
namespace detail {

#if !defined(BOOST_NO_CXX11_HDR_TYPE_TRAITS)
using std::add_lvalue_reference;
#else
template<class T>
struct add_lvalue_reference {
    typedef T& type;
};

template<>
struct add_lvalue_reference<void> {
    typedef void type;
};

template<>
struct add_lvalue_reference<const void> {
    typedef const void type;
};
#endif

} /* detail */
} /* alignment */
} /* boost */

#endif

/* add_reference.hpp
P+qqt9212to63IvLzMvkdA1hWHv6991FzYQ3Rl360KlSYKtMcnfXezua2PwF3Edgwzfhr/2ve0fXEBGjBCqrQWjmW6RcecOUsD6odPUQ7t2bECpZs5AMzBpkOsxyf80aZjjswKQ7aa2TPC3xgaSTaHVp20TTixiFiJDiAjNIkflKUdpSWRl+/hq+S8Q4l/l3wMIv9Az89vzIpsVrAq1VZvnoy82HKspxwvzVJZFZN/CfDbji08BkJn7U8pPaaIx6zaBzf61sh6MoAEgOEdijZgRfMDEcgcubltTxFMEW88nvQZl61OKWSkYGEHj9Z8Ug3DcxN696VEPVE5CCD82TsS8UlRD6sB7aJmPWdi3wfSIxL6dYzWPmKKvt3OjLTOhqAHnV4/jy1UX08MRj8OZCaXcq3QLDjheVA+5y7K6sxjwr+/egrS4e7WaunHd7HhwY556ndgpHFg+tfXr279N8R7NnJfZVXsd2WYembWkHlaazxwTWd9vRkttjV84RaWd/UAHEPqqLp+9lV1RjvuJih72L/Ypxpz1aXcvJRcuHz1INO91W804OrwbtVeuDiinN7pNSUmsPldP7+CNaZfCOirgqIiuiauoxO3hzOFTQVXPJo37uGSO87eK8UnqPwHfs5RL2ULK9ywJu8OpzoxdnN6JVvMsAt8kFZ7j5E2K23BxDXv43QVn3pLp2Wo8YZBWBnp+iXv9NFEkSr1rvgxjQJGKNHm6FxfAXOND6aveZLjSwNm2Xtp6F6Y5syueJlS1n8/gFr9mHqbALp66jcYlxNlzIrhCeF6Ja0gw0uW4zn/Hs3bzBID51lPhIRqJhWYiUizzufUb8BB4mLy7YtUFJ0Aci+Sg+PJUEVtrDQ+WLRO+/7tltUOtxhM4u3T4ug6LxtBA9FGFnyBcXYb8oSaAOkuT60k6FqHtrpA4jF3pCwSW+nJM6lrvKUlTDldAm5IYjtpguP/oEKvsEg39D+OaYDb1Ay0fFMSR2TG/yh5Sh/1yKLXtMw6QQ0obh4davHDgXLMRk46zfKp1LVI5oKMId8lDCiYcgtQU9kM7D1hBDYHxLlMSKSdDqqMyyMjpVrCF10JX/kx8b6nJ5DvII80rhnnXMtOE+al95HlqM56ATygrgQOlgUTvRTeuxB/OF4BrH5v5nT/bwPkIVnpppA2dOPMUiOIhjy8EtB95NMqJJYNj/NHaD3Kch5rj3JnaFbJLZ6/DPMboeZ5UvDAO+PWsljhFyjXVVI8aCYoi9rSMEIIE7yBP64YRuGoo9PZIb6SPIRezyWAkIDU5LE8gX0OgybcSRynQNbqHWHE/dW6DK0WlqOYVYe7zBkBzemEYhW/GySbNJE0QThRnSSczJzCnMqcxpbAKZMsGa1168TjwFrhrQCOAQAMvvOL9CuMixw7HSMcwx37HBsdCRqVsNahlrGUvd/UCdwQbGBsgGxwbJJAe6b5GoTiYf4j1VqMmtyahJyGPnM+t7bh/hQ+4gbqCgSWZEcVFxSXFZcUVxVbFPsV9xQHFQcUhxWNEk/YVJhNX9GxnISQwhPo+AnlDiIi4MoCFMKCAsrCFsyopH08dQx9CHLA91D9QNiA9QAKAJLXq13tlgUqn0vku8q74rvOu+axyXHhcSF3C5Nt7ZI7YitiFWHVcBu/2UMQyccGb8cgDZXq2QoRM0Rmp6ujKgBSXaXqOQxbMmRmfaH5NJp3Ntuv1ywgXUSi6sJBnXwfbCdsB2wnbBdsM2wDbClvjV8fXw1fK1+5XxtfDqZC0KQs0AcSBukPdfETlSewjja1vmoKryjNh2Qu0HOZf+5uPmkvszxxvnEecQ5xJnkDPkOdI5UmJoYqjoq8hrmUv5i5wfZR87AXQd3llDpWJhCVV9jla6Fbrh6/4aqHi3hqUrnBrckJeet503n1scaADPUBaCB6z7NRL3HM8azx7PGc+dR5Knawt290iTpvPExcL6cF20EH6S7qynQXNq7eSGcof0coeQ6XHHNMf2mEfG/Vj2r1NlajSh6lrCjCp8MUH80ghBbjGE1Bneu5HCEEW0PCIhnUR65j/uABuFEYpI+f9o6ColJDBz/3EJ0Ad0lXaNWikMUCySeOrstdg5B17+t5rTVSPMusy+y+79+jl+ln+zUTU7tgMxIXYAMYV3nHOMd5Jzglcq3mPYaZhnaBNt1CjUKMIombcuCjMg6DP0X1egmWlL6pyqeW/WzHm0YJdlu2jTvUCZINAsyhZOTo3IQBhAV/8Srb5CiBKUOfLUor7pM8shpfyFW+KFP4NZZXyT+TYDHBVgLWbde5vHoANs1XuRR6EibBmJ247xKDSLjDAHGuxGpsU6Q4k8Ma5z87sYemMoGneHeuvgSubZ5SP2nejQ6Fn8HUPZof7sxTODb+yS/m29OAasb9jQUdBR8RKyhapKTdzUPGThXXEo8j/VgJVbDmNr7iYwBUiLcGjIUmIIT1rPO08GTyZPFk82suA+KD20OuA31DRF4malm2zXAjvJ9ySEbIpUglS29H/pYql8qWrpeql3DAtsBywOrEAd4M3kLaItpi2hLaUtoy2nLaFt5K2iq3F5guZYWOkYbAJyuB1lU/Ih3+zcTl34y3IRJKeSBuFNzOKBFozG87ITBxkJBQkJB2iTtyzesCFay9eRQIYVUo0FKaDmJDnea8vt/xVXVZwLMziWpMg8809GsLzDVlAJszjWpOg8+5sf5zSuPbebn4MMpztuPe9PUpaC1lioOraFGC03T0qUvrdW1E0kp5B2OSaXkeZRC/c3Kk8aGIpVC/M49ogipfjQ/mS4FzQKZxgDN+qqUe487EwgJOVLhfwjCVx0kIL7F8C+bO9DVBaE8jrjzYPkKr63NDQerYBJvZMeyIPFcxEZFoYwLDY8x0bkUn4Pc4iyL78fP04dr5yQwckVUJlaIs9IVZ6t3QDjAXuKMkmtTNOeUVy1OlU1VZFGV9E6tVRVtCxbU6wh1RRiBruIWVvmoq2T5CXveGz+3cFSpJHdw+YTsBHXoiLAecl62HrH8mzSZX/kcuXi5mrn6uRq5vzoBEya9R3xkhTc2O4L+jl3C7sdXlWRB9bE0V8+vxDaqmtnh73w3dwQxOaGdMm40w7sjO9N5BL5lPSxcGi5oN5dH2RKAYd+4wjrjOyA64D8JnancExFHfpzbfy2jGAR3scMOgqgkeJNNxDeMlGz/tV1Anb831Nx7lz24kMXXE6jsUneS1M3oTN2p0bDFeMG6LXLhebgRN/y1DVUzVTINpysr+GvNk7qNWUy3TAm1oFrz90Ma+742KORdPni2cwhoBoSaR6KP0c/bBIuvrEvsn5BW+AwvIm9lMXbmt74ThdNn2gkl4m4VMbYGuB4dpdkX6igYWTuFJK5nU3DInSoWkQfzVTwyVrQ2QsC88I9yYQlvd8lKDmHDJkMtlrtdityVgtKCKHTKn2Qs2UhRfDBo/7j0DmT7n5nuYtpVyrKbm7RFC8qEU1TfBrqQTpzUpqySZpz2sXehGFihDQ10aU4c/IEvQ6Sl3iueK55LmTOfznidabbcJSx13BXMVdw1zGz8G02WzY3Nbc2COjLMlU2+6qU70cnhrZVirXttgfDIQ6uzHjsKW/qhy+18yEELjQWPcKfnVeFldDCaCSzctqF3G2PPtN4xMAqnqZtUJK4Xp4pV1k0Of9Sd23PLfx2YokdZeqd59NA9PTthamFGoTraNK5Qq4igOy5AlSFKaH6QpHSQedLJOBPaug1Dap8M3BTKRKnxftp+3kyPoJ6Wbp9PKc9pc/k1in2sFeZSypldAo45NuHtdLtqjXUBjji24WfJXiZ7zQOuo3dPk4YByyTtCVb076IE6+oLFEm9M5iwC+3QV8+TE1H9ZwXivqqKIzq57QAywfq0nmGy5ezrD3AXwKNS68rrdfwXZLzqb7ZeDUuYRmXEZmbzcnmjl6ct5ZXiLfzrNyK25rb8tPwUUpfxH2kyHyfp/G6HviyOCidUzXhez9B6zkoHVsOOUHnLhcvd/dYL4TOhS6CDjDBE+vpu776HCN44SoSxYuBvNxHHlqR84g/4jd+D+/K6Tp0Y3Yrn6kCsClmQDZiDla1w6YY20aVizpKJtTZZcKRFVazCW5oe3WzL+QakKLcP9hEPxAjg0MsfTKLzAaQKiYYrKLSyEqoW/w4oqmUsKo9NtPBssmDiquiyk6kZrxTB48d6HbPqlxkmVzTr2Q+ZO34ZVdLbSJs84jqT+CMh7peFDNBBAjv3GBiGsFhRALj11/6eMLd2pVGiaGLB4baBEviERvDmXDBGDe7WxIKQweC19/ZOZxf/XOlErNkMWUSNXZqEcw6ZlJJFMQ7aMiZPcc94Dz1i1Fxe1NilZ2/PYglQ0ewJzm0RqyxWHH+WsmSNeNdNfOK2H5b6rEfe3qNdhvqUGidsvlCO97QRROLDRVqSe6+4zFwvpErKkFlzUKLX+8yir3qPf2iOWuI6K56mevg3nX0cWT8a3t3AULeQFkGqfP6npXHFYaNgLaYClNQak9H2yDtvIXYNNSCaUEe1lsJPUQHPv5S9ADhc1zq46jHcZYwQQwZLX0bci1WQPaWADUajzNql/9yvT5x0CaL4vdsFSQXzJgAegotBArCJOYx+KjzzLvZho85Amk34j3kN9ax7ajym04qvYcKQoUIDP5zMlyZGJ+wIHS210DDicryk7VreseY4+xojuQLak78lTXFzHNZMHsMHrq6v4UovzNKdrHXJvI7HlNnNVHe08DTXQ5wFbksUlRrZ0QVWiUe9jx+74SmlFPl1J9hejA1pO4fUSo4rAxxgdDFAsImGOONkq+ZX+qOgK6Me11db0yYSzcW6kLqB0Lt7aa7JeZ9P0mKgDm/Oh2WAoJFFy5A9o7BHyYOjKRhcK4aKX7cge+6R8fQKH3qg1R0Xigt0QpZ7F0yyEdtGzrhAecmrHeAsekZQjD2gUcekaslYY3Yu5ttBT6zSTcDOYFrtB7XcgcZsO04CVcolZ4SFP27VDk5AZzOabMPWHpaLJr3RrpCruQUMWaYqpQdCZ5zkXlx8gQE0CJ5TgpY3JLWs9hZinQMY84tc/E0cSeROxpcG8VqfYEcE6Ulc72fwOgkBK7y2q6bZ8ubz+zCQb3Y1kxXmnvwmhNt0e/gCfToieyXgfFfzei6XEdarZZE2VLcu9KY8sy0gGs483z/3X1JEt2vdZbW/OghzHwkqHR1mEDjDWypzaLypoSpSp1RC3CDZWUk/65X2YNWsHTnh4ftwueT/KRwPwpRpx545hhyZ/EVS8JjrAgpvSvn/Q21c8qcR56Pm6ZbHcsuWofoessMKZ2yYtrMXAPv53Aftx9ovOpB09Xa7rOH8DCCuHCq/WoXHOwT7Im9FrbeMEQDnkDyIqgzx/eZEjTGXrwOvMxSHsebh8poKDBmKmU7L7NjmD8vTk3tQUqXC3ZBrnpsIRTQsyGO4aPC4AlMgSAj4YOmqX5zIdXpWrKG9VH4DI1Gg//V3E1bKLat1MtYGXiMTi4WwgOqYxXvp8Fhzh7PNzKj/wrgO+2TIHwvfziXNqYFuAO4Q/7vdCALwSwwn8LzR57fv6eGUgAmX7metj7JLTmKOb5hrnYWrC8Ch9dl2R7wWL5oHk+oRQ9wfYteNjqg+SvR+3AbSYESBM3oK5aQgh0vBxSeXVH4L8Om4QfpsMvuHUH3mSJ64G0IcJMi9zpiBptyuCJq31ZUuRQroChLa1WfEUJZcWcn1x3xNdud2iR4+tN35hc1SZIT5b7Tsmad+tqyLZRVMyP7tR4pvN1GY3LIgsoeiBXQGDaZay+XEnUYh7Tpx863OuPvfi3CEfiTt+b3IXJQeGZa31XFRKcouWtkPPiVr2RN23nA8gtVCEt1bsUkvJF3EE2Dc7IhZw02SmUNFaIm82LwCcE48rj3SQm1qWIdrt/3Gcit6x2CLh4w0xUI31LChO3LHvBDNRfQ17twAGi6OsEL5DtDVZUWgqua71rKcr2qUqgzSw1tiIHXF0E0BHMpu9WQrYtdZdobAljdhg76M/bFzlsqiPYQIZo61aDdW4LxZXuQ3nJhUYQh4vZhQ8LliEorTaA4mY7Dj5Qj1w3XbBzxjETnbtdyzMbsb0NLQYQ4FxktjAa4kMQKRPRlbL/IWgQ0m35qOit0V5CDVTM3o8Ldm5AlzPvK9sr4C43yJfT6kGxM3jI8LdhtZ0yvDYRnNORqB0jjWREuW+mYOO1ofMo+qWlqIjIskY3iZYIZ16NuF4BXf+3eQpUsDAIeB9+w4PBz6SF4oij5Y/WpFCh47Cg40RDeO8Wrq7vz8fnZ9X+PQc9dnBpEF08WVXOADh3RWSVXMLnSzmdVdSmWy5qyreZTcSIrDAbpea0ocisIg0YUAA7h626jpgZrE6AhIvZpkVDI5GYBRCjLYBcEiNGfheYmLIrS8zV1zRY8EjJiiuYkcpZXZEfmRu8n59IHJsPmk887FapphMYOnkgypPAcCe56Lkt4NvUtryj/3mVhfIMPyP5jxT0KcZWhmiI+m+utDm/Uo2iYruJbF5VuObiPsBcXHBOUQ8PS9mZjwffOJlXGjz7kFlHV+8oHsD00EwLSvTEqgoo878EHL4NUGSOVvND8aabybkr6RHV2oHDM3qVH53nuf24scK4WlsJIsfcw0o8lTzGsSJdpmjZL2IbYl9rHSxFvFO9B+u8SlA+I2WMvP9LaB4qNpTycmLiNHFlE5LJOnzEjS03VIZ/HiiHjKIYdP955Lt6mSJAMua+9nH6237LQv1oGXNjPzxHGwrOBxj/IeW4X9J8FfLc8bk9hRlG5CzVGrxGtRY6ONtY3Ka6avrzmC7MAcX6LINn3qVuZbI5U2bqCohkjONfbA536xJhHdTCERZWGY76hQLth4eNlosWGAvhwhaEUsgDwYYnc6Dd1erEP1iSwU32GumQwo/f7bVyiXZjzSEiTtYQgDSShIDMGyFGcTxHUDSm7XY47L6hZA1aZZCHytRvLnTa5iE1ZLtI3oav3rUwl+4NimBYZHvLy48N4gUSHbtyqQQNryYbmIyQuZs1/FxWcjOayKVEd4okL7W8i/bwv4eE+zSlEnexBuzk4NSddtfGI9CckI0LRMxLxL1gdNmwpcmy+KX6tMo70ixwJ3R1Zs1d0Jxlr6fYoYaaaJw04oxJ7O6uMyrB0BOXeBjkC3psOzwA9Msqs0OHjxrhyZnUDmXbstQwotz1DbIRo4OhPxO5moMSa0TktP2JyE2fyzF/s0bc4V+iqPJYJNjDy4Glj4w7oGbXIGDxkJYSbt08sqhshHCV9A/f+kroZRJ6aTjv/gGAYZCvgj5wWKwn26typ6XNK3L7rkiDgvr6cCXYAx8M78XfSOA2sDgZkxuUsKfgGwKiidtt0UZ0qFjGSmTIMEJ/lDgwQ/sUPN1b7xgkh99y2c2vwCTan5M1MNyLkrllMH6FOKVpec2ql1lnTmG9rmRAfffPhMJp2w4BC8jNdL1x5ue0RHXi1sUUNmby4awYuumwqKh023PipUZZMeSuvXXuJj8nJ15SeOXFLMcumJrXN8buYDvRsuJ4RkA3FSK6zlWWXhjY7VZTGQsn1dDeob4pZEfunKLSLmhE7RBk0mmXTNS7E9ag9OEo1c3XvONQIGx+rWrxHfCpzuLbSQBY7cRlZdr/1RJsc1nJkKixPqUyHFqdF3zWnxGw8M56F1GkTlrNctu9RCBmJL6PFcJXgjLPbiVc78sCPLpw2wK6nNh49Yu3yqUVFNlc/ZogmYlPHYUCYZCobXIF5h0+YlmZUUS1xSGgbn+yNoqXmiyvsmLU8bdLfIbE24EddlFShoUwlgsZT8y5QvGtfsagtLLJdwZc+Lqv9FxJQFEYdbSoH2WxZI576oLA/d1DwPTW41tiYYnpPq3A+T5JpXzM1HMFtIe+efgRP5moyDPeu0pzB9WoxZKfp2qqd1txOg5NO2Nnm5A0XhYcfE9MK1sMkDR8jV8pgWeQWm3PNuuHBxcflUTtOQjeV2vrVVb2U5Nbu8HjFu5AeK8Tp5KBfWF7V/FyLRXDJ53Jlmex3wNRXfvxkPAHZjNjf11d30qKOwJtj8WhGKq27hXhP3efKIpvz81PsXpMXCxsZbj7O3S3RsE/B2Nn4feOC+4vgFAj6EfOq7rlzrs+dx29EA4sLDGxH9z2kzvrz6OLUvrChaDNCvUCjMApWvFOg5GQ93JOT61FRL9kJff5fFdm0A1f2+ok8g+sUE0P0MiVhM4eTtKHLioIWYSqpArcqk7JRVsBzmcaHZeg0tDH6ucN4HKLk8bHVuvy6svTwWirW0vzHwz/RUfQwB4fIofZ/gMS8sfSS8wpJ1Art//WzhUsQwZx0xJgTmaq92ci4VqsFcedscjJVYLWcL4DiLhqC7gSmeY2HDlAHbR+gW+DPYJeQI7Jjt6VhZ7szloNsgw8E0uU98y2Vy86yB6+br3sNoykj1IS0GCCZApwIwAchqC/cP+krd5j1ZoSOCTFZ2n6G7s+vOLOGlU5DExN1oElSJxNvtHZ/6ZiGvmfMV6nkto+q2U1TcnG9YH3Hr0U7304mZJa2IQDpr3aTd2Hr8EouynQPhdQpDj2rQjPRtWjCBq7WyWjp2FTYPeyho1Ckq2ozAY2yEhHZgy+FHlbPhNPLzBLVsRoajaMkgu+JviHjjTK5lzPZtRUlv+Vdw0fVN4HcS2bEwCJYc6Ho2t2rH2mbP4R9YS+Tg+LT8nfx4fMX808Bc3vwk/KDM9GMaaZyyccqXJ1EuTBhMoeIn7b0PmNasVB6jMZ4y4X28lz/t7VcHPdDekdxaaM5QccjDMmjnvIPPzT412RjCBxOCXT2w63tIBeUJTxAlycBhzcWCjNwN5z5MmheP/RlAua7nofJQzJUiUARIggNhRXdCIFJ7V9zHy+60AXBVtpAaL+/JapExstgpVJ6K+9Hi9+XUW83PsQrEBMArBWsQzqA08Egwlk/BG1PvxcIqxmy5ubm3R1ukeeV2uBHAng6u+7gvnvUcwwX9hgJZlkh2Cdp6M+WVqAjMjdXEXIOWBYnTW/KbxOzKiUmDuJDjeQN9yhaxW9HyCFDm3dWVxnFexc/GTdYMo29OaZjKncKqYKY3Me/EypqJ1dORZ8D0BrInuwOmemQtm2aacJg6PMf1d0f/FrVvAqBdA/J2IcC4Dzbjh8e7k9YCA495bUbtoPBQfs=
*/