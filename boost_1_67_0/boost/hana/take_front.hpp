/*!
@file
Defines `boost::hana::take_front` and `boost::hana::take_front_c`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_TAKE_FRONT_HPP
#define BOOST_HANA_TAKE_FRONT_HPP

#include <boost/hana/fwd/take_front.hpp>

#include <boost/hana/at.hpp>
#include <boost/hana/concept/integral_constant.hpp>
#include <boost/hana/concept/sequence.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/core/make.hpp>
#include <boost/hana/integral_constant.hpp>
#include <boost/hana/length.hpp>

#include <cstddef>
#include <utility>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename Xs, typename N>
    constexpr auto take_front_t::operator()(Xs&& xs, N const& n) const {
        using S = typename hana::tag_of<Xs>::type;
        using TakeFront = BOOST_HANA_DISPATCH_IF(take_front_impl<S>,
            hana::Sequence<S>::value &&
            hana::IntegralConstant<N>::value
        );

#ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Sequence<S>::value,
        "hana::take_front(xs, n) requires 'xs' to be a Sequence");

        static_assert(hana::IntegralConstant<N>::value,
        "hana::take_front(xs, n) requires 'n' to be an IntegralConstant");
#endif

        return TakeFront::apply(static_cast<Xs&&>(xs), n);
    }
    //! @endcond

    template <typename S, bool condition>
    struct take_front_impl<S, when<condition>> : default_ {
        template <typename Xs, std::size_t ...n>
        static constexpr auto take_front_helper(Xs&& xs, std::index_sequence<n...>) {
            return hana::make<S>(hana::at_c<n>(static_cast<Xs&&>(xs))...);
        }

        template <typename Xs, typename N>
        static constexpr auto apply(Xs&& xs, N const&) {
            constexpr std::size_t n = N::value;
            constexpr std::size_t size = decltype(hana::length(xs))::value;
            return take_front_helper(static_cast<Xs&&>(xs),
                        std::make_index_sequence<(n < size ? n : size)>{});
        }
    };

    template <std::size_t n>
    struct take_front_c_t {
        template <typename Xs>
        constexpr auto operator()(Xs&& xs) const {
            return hana::take_front(static_cast<Xs&&>(xs), hana::size_c<n>);
        }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_TAKE_FRONT_HPP

/* take_front.hpp
oFntYHNmi36LwMKKtTfzhPb5eW65ogsYyo+PRbqpBdHnlFab7gG9qclwTnPFvV4vZw2+B2hMAe3yDHDd5bd8OX+5mAKeuEWAjBpEDfH178Cl1YTcW0kZZC9x1I547seaHFM+BGKJ19xiMIRCyk36w9I3pq7pb0BdEj9rfph98JVmL6xhwTyvgoDnOF07Gm3N25K2pGxgqcq5rixsUw3hnCKEjCDhGSXshNbQ9XepzvUGQV1LelUyJw3BzmuLglZOYs9uU4V9Tdr2H4V5Vbatg1yVqaU9qxE/qr5zfcFfVbc/UHqT7Yh4VeKJgShibhIU1GZmkZSC+ex133m5xKUbsxE221nE1G77u8HOPaOgjDt+ZHpjibrlOnrlBTIUJj1he8rOlW4wj+sBp/PA3flENsZ3dexhPKjjyMe/Eaz+imHVVC/yLcnFA9wl9avoV3oIkXZi40DO+cZO9ojtYGsizuubrWXxfXNpCgyTC2RHpFzkdEHlgzc+y4/ZnNjdiTaPkQS+tayvGgwvI13NvLJ41/Tku8sDmKF5+FO9/9ZvLF8dxv7R15ivvOC9fCp+t/XAzlImv5cNUcjE4RHdgqHvKqSUXjYN5BXEBYJJL1ZYxVnsVcuMoqg+jTy5vlcWGUC09dlsH9nBor8X5+4CLcdHylOYmQRV1RDuj+JdjpGOWRuYivf9PJUjvdMx92ocVwTjBlrWrrf/syN75PDOvDoEYkS3xL52ujBQYUbRZSPaBnNQY8lysw3l/PVZJfFUrqjmLXdZGe7fwP8Wp+0eYhUOIBAy+0gdSQuVpCIyKi74rw2srai2QhZvvRw2wy0j2pWVerJBocI9o5R02eGCJonq/olpru6eUjWlY4cXdAefSjX0pa4FXQqXStXNL5J/YSdJv/w64tuH/h1DftDSZZf5/be8zgq+wL6lPE+dek9iqj/izjSqcozN7v3FmzvR/ReTUul3Kza0y3mG5lYFAhuSiyXApVS3P8W1ghd87SLLZ4xOOnMnYhpj2rUIUOsEtulxbeiWi3NF+k9t6gnRXXzPmnOPnowBjGABbZ9+Umeu5yJpzDslww61CaXmK0EtpRmL+QnQG9TyOGvSOc7f741XivPvevg/IzIdFXcwJfXOX3g5oux/xuqrL8Ex0K7F4ajhaHaynwtLGXTdMp8s+NvHPiHGmNIVOFe4DPCaYE82lmRcmjk7si9UNiReUGt3NIWOOG6cbqRvxD3pL256buhB3YJvTKaCVgJXgoo9yrwZAG5Tq5XWJNpC2Dr6OHldRVNjJ0jUt+IecHxpLK/0Ox8rcLZpYrB9WO33lFKJilLqZKtfzx0pNE51beOf8E027DPpaFVUasLtr6/LkQ2ol1xFf0uvHOVInekWawmyvbY+4sX7q13/qw8/cyFD4DsgfU3+gizqy/zU/9T2ZSoe0+xb6RP0ZI4q6VT9d38I3RxZbWRGIe8K5TYZLAz/YAzm849PJlfagymiZQ/PA/JoLDD076oYRgXDfewRDjL1hERciS2gUzlZIAP+YfnjvCySzUphO8PcN2C9BuULCASCQoP8AvsB/gPiB+QPqB/QP2B+wP6A+wH/A+EH4g+kH79/IP9A+YH6478faD/Qf2D8wPyB9QP7B84P3B94P/B/EPz484PwB9EP4h8kP0h/kP0g/0Hxg/IH1Q/qHzQ/aH/Q/aD/wfCD8QfTD+YfLD9Yf7D9YP/B8YPzB9cP7h88P3h/8P3g/yHwQ/CH0A/hHyI/RH+I/RD/IfFD8ofUD+kfMj9kf8j9kP+h8EPxh9IP5R8qP1R/qP1Q/6HxQ/OH1g/tHzo/dH/o/dD/YfDj7w/DH0Y/jH+Y/DD9YfbD/IfFD8sfVj+sf9j8sP1h98P+h8MPxx9OP5x/uPxw/eH2w/2Hxw/PH14/vH/4/PD94f/j/2dPz4f0wr2zLtq52o+PCOyIvk+55jl6tB9W3I50uuiI2WQZ126TSGLtRE9qcSVWRIegG+hsmuQ/0r89oLCLES/YRNFr+GMnCuxGtdfEZjoCbc68V4OzB5rbYB3RFvODkbNGeKvw+KWx732Vh7G70y6uBngvShLj478SVthXt8Jj6ESgPMC3oapuF/EaHrpW9Lx1t0EjAp+vkmxe6nNbdggJVLct4F284r0XAXKy6m4bikhIQpnSHmxdMta3vve+TxVKoWP3Lx/i/rMMA8bgBFBWAbNl3R688MwyVJmTpv6sA/CJBQiLoYG6QtFkZzb/ppmgCxk3D/lWSQ+nFjqzFGEuHb1C06kRwwsLGEzSVo6w2wRzSuEXVGUVlPfQhAn2M30UD+DHGZKrTMscKGwCC23+cksw7ml7Fy3MuNYYgKJG8DNv8V4T1kqP5gI8CTxy3Uce7syCDBQYaNIyR3LpT05m+jOKIXotTh9mzGE8TXZZHt9wHnMf9Z8qDh8aXn19g0cOvTTPibbRb8IRkozPx3wdayeTOo447/tnKtcsu9dF09tCODdxEUbQTE1NeI2e6sgUTX1/UTZmfg3bAJajgJ0g6dDP0Y/94p0Jvp03C7hi3bfzOR/VnevXBqJYpezbopeYGiXgXXfTi93zz4TFW9fVnrPJo6mH1fiMoZgA7Icz2doKd51GVMD8dkUeSxFtx+8F3NRiVQ/VVBZebV3FFVUil2uY1w+Y5dJgmS3f8WsQfRSihqSHfw/hDzyEDxnKW9VXzWTG+AHUES/eRRd1238BwfrYk1jT27DAKmAXgXwDO+Mr0WqOm9Wt7ePN2+TXRnNFKRsejClcXRTgRXTHdNb0lTFnWvwOaczlbFhZDMkIt42OMge9qy/nr2pIMSnYGu8O23VchVDpfXo6nGpZwg0dw30o0f1UFRRVJsSJ34e2bRF5rAqv54QuiuxOx9eOXRtco10jqpbi/aDd+UUfzc7CxwRmd4rfNH3C+RPbNmt99FVSNXdki8KOlpCx0xt2iS3lf7xoUtvr3tMyv6TRiRq3rlhctLjoFfX3t8K2yEaT/95HPgefuOs+kAISTyWHdgnX63xwRKrjSvDkcKUNXO6/jk1u+zAaW73txCy8EfV73RYqNeCMWhnXNcQAhjrOqLxD7p5o1KQECXGjJ4ziF8aNUgq0uyJMS1S3PqAlp1jMqJ7o25IsdXqhcJqP7GSTYpYwumrtzEOcIKlDW6EG4arOosmIO68BqRdodzdvG2iqUbvpnalJZWXZHt8t+K2EnUfcM1SWqk3ijSw2Sc0420EXCE937zzGQPDtZKTxl3MF2KzvcPecWtKjhXr2f2jbMCpqceXLlpgm4+PHRqZWTphdRSLbeENCUTirPhQPO43pxNmxSW/0nKqbxi2UspMwLdHqIGWwL4rxlmjlIxeBBPfPrCMFZ9X5TFf8xF4Nch+CHSWqJbqyzb6iPTXkKAM2u/x3+h6qnhPa1t5WWYyGZxmWoaswUC7KwfD4b/NoHm14bclxznLxykyLmoHwHsHbGO+tN21OW3jOSLNzXnAa2tK+3eXASP5+fZmzVaR3UCvm79UZndgSu2GrBnJNN7aUT2/SaiwqbCnuAY0uRI0OpK3wrUUsHTtx318NwF/eohw7Q3uv55VmYwRoDG0W6fJKNT2BdDwGTST8XtMVBup1OAnk68ZAw536xGz0aWa5kgbYtu5wbaQIqqwjkG+ez2GfIlr5fgIZGL6Jg7IyIRbUIQ3lZ9hGE0bOTgEvRHw7snIzmy/Jrg6+lE1BIruxjaBiISCq1aKg57kwRbsFg3tnrGFWGr3QToOWL7mTCYRnQ0ZFc/nWbsksGjzDSd/GVYdNh+PE+8UOz+tGjwcJMys4fdf+FFikrUeTf0GoL+rkIKqvvF9nzwQwZls+FZI86EFQZUxosKOY4gY/GIeieG2deT0qLYK9ya3paLdEg8GO130l1lP9S9OntlubXjQ8IwoR9ygE6HqCbXlM5CCThU5qDIvrcdj9TKeiunIp6MNpp9ZYoRX3T32qzrfZVkvSOZtnhs/YzwqjL5p/v3Eo+tEldADJW/6Lcm+4za2D9ftJSUJ8/Qo5eqLjv/bS329t9VWEXGy7+jsAtfOTR2nPNW83oXjtqVHufL/3QGJ11SA7G0HtyNxdTSutuJMJpQ3/Tu4sqFMhzoW1A1zHgjMhzi3d6xpIuE3ffJ2ZmxMkyNwQeucIwYk8n385L0Ij957q0DmbJvLIpdkGJo2wWrzt8tPLNX/oyVBQJ5eQTsXjg4F+tufSlVB7LpAVbmfL1GPWRq4iPoQDFmpF1OYRJE+hXVm4b4nTONNcZoUPeH8bSrnxeLpCatd6cQ4RhOXgyWPedD9Lv1rubYoGNgaEkm4K02IbV9MtO3qvl1GaxN5sAUinom9+/+7seuiA1FBQhoGrJM0R1M7M7eD4J1U0kqgtInjqZqqSzEOXxs8B0tnB3V1mdAzqmTvpydWWy4XBs/HP5M+eHzSkgypm9cxgksTePt6DePvd59OlLZXY26gKS3OPrqqrLZ+/8Fkne1O/Kvp8BBv4rx8zjp4uAdxdT5fiz8wd5LkYmJV+JXagZMK6Md6KMZ06F3Ql4elll1SOKoc1lyZNKj5VsYRrKywdmcq9O5kSyheaX1V9t5x7cEKyHcQ6m2neL0kY2VLXXQIHV9qnENvst3CiFnC8E8B1/lOMIud4fBoktZO3rGkPXriHIf23cqZXRuVMKDfs7uu4uZXzXGK80OlGnNzBUqPl7zctm7BW+ebE7COJ/j0CLhy9VOgGvPkbjgdUx82YeAq9BvSEAzq4UDtLpD/FU02VnKy9d1jTLCQDKLYWRe8qj9bpXuNdv1b+7bvcDnvhdNHeIvytJwjUASLXYpJ98LdcKCr6PJxTTVsKZ+r9waeMFVHU90phGvpyTv7iMimhkniyeaMefEeIFhxmMKJbUtGH/00fwcmiTZc1AOeo1X2j+n2WQj2fWmLUrUZMu/WNiO+h3t+LLy/sMhA1x9HTvTMqXxg1d/PlFViUB0MY/3h5xOPbGbcUGAXdwjiiQVmd9WzA9zy6+HIathsl9OwOJ7cP55tei3kmrR0Rvy/7eOlnMnJlmoRmtFRAPT5qB0IEoCC+mSYGLOkAWl5Amb6u0I7flwKx7b3/huwCW+5Nq8GpEXzhzWxYPxBhFQLu55Wuilz1qEXxXfErPtTohZ5kT7hf8b9xll44FDjEvEVYQ3BmGO+J13O+7mSlEHHn0fLubBsq0q2XheavQrK4cSYx5bTBrP6xwvtSZjVLuTKfbihkNPcrtPSe5dxcf9Zq91Mj2HR8jdvz+EimS9vx+enxdmmfAr0fFGev+dZJ1gOwDUb03jcOxWQOe7u9mTy0TJ0Zc9i2Czofw0q7vuaNU2mKrpW4rgRSy5XPAyMnWopjN4cbm8X7EGpIrk/k2EtLmb/9toerHmfeUnuBfhvDNJSPJ3THHmyZU2YdGo0pt3EAaIdOLo9n++sChL8cCs32G85jZUQJosrrd/jIpCadj2cu/Np68SsmRDaZTEv4LtBvxM7tZ8eO9kAYz60bWJNMS5OFC1/ejlze1ekirwFjjkS5aWhPO9pzz9sY3jPt2N/prJ0reb+sOhMPZTI+AG+AD2kgAOf4yWP1sxTn2EcLmVdNvcguno7vntex5A7NeTcFWc+1i3KZWNeH3rZnNGpzYJH5Iz0oHtDPApTH8IiP9uinPFATcCFka9iivnZhv7Pj3t7oiXh9AHU1yy/L9R0xlWfLNqmnBb6qdcvsVO0MgVFs/vUNTWW5ZrtmT3IY5TDRYYuMdFcUXfzVMIks/e9YWlKcD15/HiI5WSQjtQLRUeo1eU7uEfDvjaABZdUkzKOXJ6LKMVV1uMK6WEPZf95mWfAi+imRdS3HxM/A7+9NSQvAvRSs5JbWrJ15R/Os0a2jzaePATVeF91f/ObJ0sum03b7wZ464husGyZ3DbmN6bP97TcXNlxMGSIEDzSBD2U4l1p4t1NnVPLfl9qPvlKnVRTXX8zpEwWNa+tENsnPrApeeh+S0nMLT8TvENlg1SHRGgMiw9a2zkwFog6KcvZ7UaEFIaf0fGHfXzTXAlvJASs2jvyO/bKaIkP59x7nxE8xXICa/OuXqeLj0mPfvGevBzMZU36SkysJC4grDRlTl9cpn2eHD/YPOfLptg1Jh22wm0uHWGKvbfvtEC/N62tnJJCu1D2ejkBNM6+oLveeSCC0D+9nlj7Md4gw+3q/dpj+k0JXKpwoGtVvNNVY1SBhuF3unqCoiAUqiyXWWMrsCpO+Qjyxiu6KrsKZZYwLfSHh2LOT/E/ivdqV2ylvep5T6IOeYRaj4joQPdpHFllR7ni6bZSF+NiMUbb6Slwq8bGWI/iyo+yyTVWEubua0WIgI3UGrMe+Yvs4UiW9KamGJHrLs+ZOoAPcRvFlx5Vx2fHHM9NHrc90N2wu88rbrCaYKCeimeeUpJCSD/K0c8QHZYKynV1e6vWUgO07tIcLQH1O/jmTkPXpFuoVLdASBA6bMIhfEpBdGnjbI+8Ctbc5DP9iGrQmwRagebst29tH/+uscBfxevHAWd0OGu0K9uWLQC+eWi+VX0rf7moXqk/VI23H9pJd7g8OOnKxKOnhQPG+cplcTXjC0FHYaDjnvbaHol4iEOkeCF5coPr/zwCKu0y8VdVf6LBpWoVnQUUDBxwzpWd3EfNbodygr39vErYK27uFgQpGoW7Cgkf+h4R4km5043Xz8fyJM32zKf/xkOEVKx46BW6vTOw/avfkLUZtxFXLgXz9auhU7QH1zRaUvEFlmr5sc1H3NCw1VV/vfcgsVyv9CkjcEHTlM2+HM8hAchUib0qEgDVn8h5GPuFZ3FI2S+DG4Tvw90J5v0b8tPM4XQ4JP4/a1m19lFdxkxYCfoD+La4VfRVuFQN6/3OX4InJzBaQIj76hZ+bRCfc5puSMGpxZJCnRuBR16m3TUyQyk3VlZyvcKw4bmoCQKlMUqFtSl5HWDfP0hJibqzXUq7mXZwzoFXqgKmRhYOnjv7wFfYr6wkOmrQ+ZIz8VX6CQx3zMGzzOoo0zOMU0jbGg5DTZccHprWhBlGZyTqKbTZVj0k9YxkY07/GwIYfng2PP99MvZbvSs1dnrg9dnYqh1WaoUxQ5YxVljI5dXnsIt2eurlxjcoenzo8cXwExjx1i+5B3km9nft5fSKJcht/4wLWXI0SC22GfILkb380lLEv4tDsrsFDvf1fbjhqkYRFRCMS1TcRJoecJflL0slEJfKT+GGzlJtJHpO0ZkVV6fSdYUUNmzp35dfSnKWi7JJUn0+IxVYTiFbSs9IHfAmKszigCljtB658xASLA7soVoZso8PAhyM5JXMMOGZ8wLW/7sIyKG5kOtiWb0DXyKx+ryLt9mbT7muuNXX16kjlXcuxAtSygx4ocdcoj6UfTgYs8EDRPqUyz2VDuPTs8AqS/z5pvmv3cNoda/YM22X3AfpYbT779sP/RdbwyPxNfIghHdkTYTOI3/rwVrSfQLgUnyF1VZzz+h3WCqV5BFoPHu33p+cff2CHI2UImiaM6CZAZZq6Jbl0HMoE/++nxenBxzkzq4RVVdNSSe9M1ZyrZcwjmye7Dw/LPUpG6yRMteqCuaEzwzsm5+4ceAOssyNcQyEWzBdwVSasld7wbFn2Iv5pXGoscBWw26jAsC7lmrNlKo/89mAPmrkrYXT5YQ8qOE1xerQ1m5ia5TUt4ZbADcW3m+cF63Abx0yRTPJnDWgP2TZEZHB9bA/+NaSjRCiZUhG0pyWtWwRd6/ZrMYIsNdlq/ObwxtGRtEdJqS7JUQozaxN/8Iv6KDNBaCvvWilOoPizuFu55wBebA/clfie3uKlMf6dxAeRAZjnK9UDz/YSPS4mb1TGOJdm1Woq2hC7BmHpVMQ5Fl2AebsnEP606Gn2VVvfACpjgF7rx6NyIniackGTEtNgthp1yfvMuAtE2PVTFHfKCNj5IESPbIXFtRZuidmYukKy+Zr+2kO/VwHA87xrn/fICHltJMC87eLL5NM8PrHt5d2KuNOT/LcQqT30tQ/jvtYzJG9IRClhCU7KrJmBVNwlbEnRktIxfnCYLhDCahCQIUVsQuJukF+vVp7PpqBdKewPybxnXbikooU+KMTa2tusJcXbkANlSwnOV4usAeRcpY9T3KzdTc/Butkjd/wFFE0EQSZPa5gU9t0msJtqRB9gFdXGsCcH1URY/hdz++Dr8sH+p8/Ai2baML8LDJv8d6cdMZVQ9oycIXu19qDqltJuv4Ib/vQe7uaefiuq0x4iu2epP/SLOzrC9soIhKAQc34Qg64GTRXGM7TskKuhvEMCR9h/Ao0aGkpFbErsFrH/QRw5SVjSugWYZhPS93NaD0hKRAZxz6FCcyoiq5aEltEuytnHDixK1PZZsfaooWStil3kI4AQ/beC0BW7rWKH5MaKh31TrTdLIa8MYBRzEhmAd4LJWtJrSF/aPodw4VvR+msTHIhgSiSXR3sBIUNjkNpI25GzhYvd3IL3V7/5Zn0sa1JOL6uf1L4flTw+c3jq+NiJeu8i0f2MB9VcY8RKrnsVAy4ihEWITTAAtoxm8WuMd7eVQVaLpDrI1o6oJdlrFHVPKiUAz3X/w4miTwqBYuNZqjVBdwqQEsxeDqVz+YvVWdbHf+OfLNyy8RVV3V8l3qDvKL3fngYY3d9t35JILEzY3DEDt/pxMez2s5KyU1kIQG9IS4plb6vp+hSNi6qDZVHD0T/LGC8GeBsIpY4RT3Vhgic1jS0CcLgtB7uM1BxbWYLTHGYpA7uMVu14W/ZuadzbWwEaEiCiKuOVx6yHW4fCibP1TcZCYpEhjiwe3erh6Hr98aQYQYO8+4pl+aX2iyBKsK8pWBwBqLPCfqB4pQMONaDEWckAMEKw5GUpdZPmeqG1AlwVrQDk94qFpZBzSxfqWsU5nursZW2cGtll41tBUYp8Ok9+ikAJ90Z2+4KA3WD0YY7NgKNh08KctclLg1im0rQsYiPZJSoj1RCkGFD6zV6YzgYUfwy2et7ZoJdV5uccC/u1hcv//3ztCloKvVqXpTzhcfNpr9QKodN3RI68R/bE5D5Zebr0oKWkyxShf1OK6gidoaBVJvUWXGQIGR+BNuRpKM2oIAVlkidZvLcm9JVmPoG2KwkFAmM6Bo/dWjKPDPxgWKe91XkrIFFcqNDtC5/ohf9YUrbEqAawgUrZs+q8grj7I/cOZr8rfgU=
*/