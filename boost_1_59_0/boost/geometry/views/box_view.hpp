// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// This file was modified by Oracle on 2020-2021.
// Modifications copyright (c) 2020-2021 Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_VIEWS_BOX_VIEW_HPP
#define BOOST_GEOMETRY_VIEWS_BOX_VIEW_HPP


#include <array>

#include <boost/geometry/algorithms/detail/assign_box_corners.hpp>
#include <boost/geometry/core/point_order.hpp>
#include <boost/geometry/core/point_type.hpp>
#include <boost/geometry/core/tag.hpp>


namespace boost { namespace geometry
{

// NOTE: This is equivalent to the previous implementation with detail::points_view.
//       Technically this should not be called a view because it owns the elements.
//       It's also not a borrowed_range because of dangling iterators after the
//       destruction.
//       It's a container or more specifically a ring of some sort, e.g. static_ring.
// NOTE: It would be possible to implement a borrowed_range or a view.
//       The iterators would have to store copies of points.
//       Another possibility is to store the original Box or reference/pointer
//       to Box and index. But then the reference would be the value type
//       so technically they would be InputIterators not RandomAccessIterators.
// NOTE: This object can not represent a Box correctly in all coordinates systems.
//       It's correct only in cartesian CS so maybe it should be removed entirely.


/*!
\brief Makes a box behave like a ring or a range
\details Adapts a box to the Boost.Range concept, enabling the user to iterating
    box corners. The box_view is registered as a Ring Concept
\tparam Box \tparam_geometry{Box}
\tparam Clockwise If true, walks in clockwise direction, otherwise
    it walks in counterclockwise direction
\ingroup views

\qbk{before.synopsis,
[heading Model of]
[link geometry.reference.concepts.concept_ring Ring Concept]
}

\qbk{[include reference/views/box_view.qbk]}
*/
template <typename Box, bool Clockwise = true>
struct box_view
{
    using array_t = std::array<typename geometry::point_type<Box>::type, 5>;

    using iterator = typename array_t::const_iterator;
    using const_iterator = typename array_t::const_iterator;

    /// Constructor accepting the box to adapt
    explicit box_view(Box const& box)
    {
        detail::assign_box_corners_oriented<!Clockwise>(box, m_array);
        m_array[4] = m_array[0];
    }

    const_iterator begin() const noexcept { return m_array.begin(); }
    const_iterator end() const noexcept { return m_array.end(); }

private:
    array_t m_array;
};


#ifndef DOXYGEN_NO_TRAITS_SPECIALIZATIONS

// All views on boxes are handled as rings
namespace traits
{

template<typename Box, bool Clockwise>
struct tag<box_view<Box, Clockwise> >
{
    typedef ring_tag type;
};

template<typename Box>
struct point_order<box_view<Box, false> >
{
    static order_selector const value = counterclockwise;
};


template<typename Box>
struct point_order<box_view<Box, true> >
{
    static order_selector const value = clockwise;
};

}

#endif // DOXYGEN_NO_TRAITS_SPECIALIZATIONS


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_VIEWS_BOX_VIEW_HPP

/* box_view.hpp
Zy0QvAYVX8KgCAaCeqCnjOdXOMDn7eC0QWOv0/2xYKL8z+Pon/IINOvlaxcFf3jI2BIvVgcVQpTpo5mphHlcB02UtTXzSQDjTZSLavF3cahQKTuqgms7cs/JPlIP8MeCYhI1i+aaDI8EUPZ5/NoiHvnAUVvey7GuesdqY0LRC31NgkxbEgJFppK3w9smrEd0UJsBAllxejAFHT561+IFRanOV3LuoHfVRljxEMzD9ZECR3e/o7iK51zp+BZtH8SCEn4elzmMUrjMhLpfX/x8XERdOtxsAr9DOkWuQ5L3b7GXJeQ5DlIodDRC6TSMpTA/pm9ZCO1i72V3wdV1Uh9yPQSvER9MEoimE8ac9+Pa90m8GP+cAPXmxaQq3tqnpgP90QktYhxXS94pr6MAHx7Y0HfbCF1EwFByvmQ0UjUjkPyuaXXAX0+c3M6rvZeiN0cwcTc7fzvpMl/d8AcMGOGLzcRhV7lEHE0yWp/9kC+ICqjp2W8FLLs2VE63P4FapyhIpuKy4w/crzV2iPv4QdgDVt2HOqS/7VmXifkmjrp0R3bqSHrvq85uJ9PIOiNgTpxD4JUo6fLDLg9XqI2m2RJB9+0Y+xCChVFxmJPgGRLzeeHq+8MEBjKGlBhTMX7wWNZH2HPiFGbrXo5JgH2s3FDVe0RPV1yEiAEiexIWaI7KsIHnD2+FO3j/MeszIjhryDlPiF2hAxpDIfGx1GvGPTivVjeVu06hkZz/R3h9m+F+QRGFXyH9fVq6/N1TEtBiG6NCs2fmURQwPRokajq2loaAedUx180CMB1mhiN/NUFRQMxQl5CYXliIwGdlnz8GACjTqorjzvFJ2+iQwNh9rIUNJ4ipxq/pb5TxB0VO4r9CA5rL9qAQvkrRH+QpIUWn9sqPCetwmtRteoX9jpiOvDLL4BreSA9BLuzglp+CtWZwsmV42T2uCDrIsUKCakkLgQOyFsrT8ZYMNT2il7ICyp3yxkTybZN/f0tPL+jrTLl/dNPbqVeM542S7tiOsOP/OCxsLscAsMoI0MdSPVAgUpFsjxPNTe5XzjX2zhtZaGKCd+436H6HxzpjjF9qonWGfqKxLSRORL9jP5n0T9r6LZKlPlGZWPuwlLWgOFdpU6U6nw7emfPX8V3EHZ2ekwytkDpT9AgUKEXCN6ez+qNQ4WtlLA9SNqNZ3WSQnp70CV6LPZsTk/oWIdH7PXDEPHV7WDE0WjQ0s8ftEcR++18FDwYvalwXEyBULus343W4ZmasQOs44R7opM41Ejb+JPJx3akoQnykuX6GE0Up+wS3DWdH/FjQsO4k1SyaLc97p/ZGFEP4q6YR6xatZPooMy7mLSbQQu6rrCVodBFpSSWWzK8z3mM1x535hKrk3Km4EeRiy1tcqr72qIJaWDLUVNoMmmgmbQTVlo0gPfi1B/JtnJr1urHJpO/NZGF0+X0yrfe6VIZzbbECWkQXd24iTgr/QNw/phrkLdp/LYpuJXpjk+EZTKUK8ASI8fjNN8QwfIHE+wRgfeWRNjHtKLsDDdiFqTFCdWTV+tAHBJiPllpJHpwQVgBeGvsU0l/A0tShgKrR+ZX8wTmMdyOjSB4zEXxVkhnnCmpCmuQJzeUepe+g1JncHv+H1He6U+xlUA5+bjF78mSK17xY20Rpgus/Vpd4yL/E+fdw03hK9t0YlS1bAKcM9kondvfAMEKEKRMpfJefW/9V9vumCSWNATDPz7TIT6NaArDuCpFeEAsj8QiUCmDbpDxwb+zdE6O1NroYOGdHCnxTZvhbFfs2bK6lHvdv1FzNgG3Kd8q9VL4yO4pmDSzDutUwGefyIcQ+L5KNw7q6ZQVs1bMcjWGB6GBtfb6GeFmr4KKQ9zUmVbrBZzsaK3yKqT1Qc/RcPjkSDLYInxustHn9V1HtYdcxIJIqszuPwIcJUWdOPkOG9ALi8B0gWb+rf1Ky8+Q8cfQkHVO4KVMF/jiskTmP/9Jpw/ag7bOm5ZBpEg3IBB9ImypPUK7X1fTBZRDPVJDXarNe6XG6uRPIPVKH2aGrh6BcVjCDlOSpFMjhV18dkhMb1klKzES/8RkAqy8mBdbyZyTQNOLT2a3yv7WAE1GUfZb72T2GOr1YU5/v1EJmeAQu+8B5sFFoU3rmFMzNiSg5755A7TuwYgkYbO0J/vAMTyn/8kqwk8BBk2lGplS+8HEgOYtxnnO689MqxjB2Cr2AS+QEj1Xd0odlqyjUfbujvGL75LwmFe1cmjPb9rX7o/HGW1gmLoRLyy+3EHVn8yv5Q9tQFo4v+d1p/RjJGTVvAS32AI4BnYaygdhp/KSCPKDGUbOyu6fBg2X7SVOqmIGYYYR1XtWw2LlGmd1L0dqFAAAs/9NpAP6U+WTO08zFWQSJirR0Gkxl6lSju+q/NxlG88XA6Ue76E6cbZ9PCLUloeP+6Z1O9gQ5mu2sAQ19i2cHIjUToS5iBYLpiWLYw6rRRKqQi+yY8kFcMMu6WK0AR84kJcIgwcBlosiiMTgw8JPVhWkUDpxwxTPISPC3RxHQHIFbwkLAubfKSWHFhxktYwRN1ZBqMU/b5Ow/IF5/bqZZJQNxD2/6Up5UE7u0Z1G5IHJA+s2CVbZHONrb0cdBQmwXIoVb7fd3W+sylQy9bbAKCFAE/Xm2BDVSfah1UxiOh2wf3U0rZb47kDs/tsoBt756GDe3RIkx1dkpMZAFZVI+HienTvnNf3IXSWoR9DBnonIN9fOflSGgueQxoN8IWShgUclhNEaoOg6KslopmGeGIXzHo9MFUzX5ivuOCZ6umvBzG4oxW8R5vMDNd4+OcxFhw0fpj7zPmV4RrCm2IIekql2S+vZlJSThAlLxg/0rcUDkUe9Gk5Sm3NStT00nLwmGriiGe2KywkLYBJYaDc9rW4Hsmx+MzalDtf7yUrrUX7GYxKZgTtXN7fK6ITcfPSDW3TH25PL+oVF1yiYID4c7HRYE5dRezs/civSwQBx67WFCh1AJEfVGJIetR9ykmU02yoK6dDN2wSRP5/a2J7IlVgtuIBFOeOIAyxcX7273r6BZ9WNdOF88u+Ee5Tcnbl6HgCnGtpWDLwRo7PPImuQJz1TmtYgTzly0Xm2s7TW7gA51wwqiBSVTtL3CbnoKJL7R9RuU98HH2oSEqlaSf34JbvVwuLhCXI48va7d0Dl0RvcG4rFFcb8USFv+vKW+GZoYPCrr4B2Jug623HSPbrgxan0K2yzj8pvitcc1rmFRcXEsa/8ZNNZUrlusiUwNpDxqz8wie0Rqc03cXj/VJYDRcBpsqP1bd8k8tiyGinQoKq5MWqvo/+6FL5ysfvDyPorVK5QD+TnQ5n2xQRzkxcLM2wC4AAAA9Av4F8gv0F9gv8B/QfyC/AX1C/oXzC/YX3C/4H8h/EL8hfQL+RfKL9RfaL/Qf2H8wvyF9Qv7F84v3F94v/B/Efwi/EX0i/gXyS/SX2S/yH9R/KL8RfWL+hfNL9pfdL/ofzH8YvzF9Iv5F8sv1l9sv9h/cfzi/MX1i/sXzy/eX3y/+H8J/BL8JfRL+JfIL9FfYr/Ef0n8kvwl9Uv6l8wv2V9yv+R/KfxS/KX0688v5V8qv1R/qf1S/6XxS/OX1i/tXzq/dH/p/dL/ZfDL8JfRL+NfJr9Mf5n9Mv9l8cvyl9Wvv7+sf9n8sv1l98v+l8Mvx19Ov5x/ufxy/eX2y/2Xxy/PX16/vH/5/PL95f9LMhlra3lmKxJr9ILoMsCSb/iPl0Xan5Mu9AbCVDdzrsvLqmiMYw302BqBh6NArs5onvF7sP5LyhPjixMPd8VAuXgEKBPEJNok38XY5/bqzl0jTy+ydwMsF7v8KVpvgZBe0KxeyXQjB/r13nDW1onZIvUX+Er7tuoPyRM2LGxAv83k8LFCjXt2lvZHQktEjyAfAAG4yv4uFQWTMijhuRO5LQYr4fpCptspXq5sZmunbNrc1fo5MON/P6uHDK9Z7LNhtSkKVO8WTK84A3Dcv0+qcBrWeDI47ijASnRcQCYkfMKbWoFaVV3ssd5cSHVo3mX5v8Ymp1eqQ++QcIkj6+aB9vfqmX+Np8HXVdKZyLeUWvnqJxNoQSdqVaq2/UVHBOb6IMC/iaWnVpUKo00vNRA7OBDtaAB6JYPxysu/nvwElJ6BfdexiTiKS9JA23WFquhDrfkNtgDfu9/MLJmQz37yC7jNVCxFXd8rQL6fMgammqWMUlr3B18HdpZN3RvhRFc3ixKqP/6JWLOFyrEWXFp5wMOhEl0Fclrid5H/41udp4VT6fmHvbi3yOfmFn6kP8qXtk6CP9PkMBEBD0YcIy19mO5mQGAaQsUZJTZc/jltYW7mJcAywXpr32BqFlVcbARsWb8Alzbm6jmAO4ofYriAZ8kblMLPU76xYXuPrC5fHXoPPX2B12xm6wB1ko4yVXkpaNpJtjDfY4qkO7+aJfborZqX3JW49V7it4tIPhTohoIhh3Yd3YQXsYHdgKfZUsTxtyGTjt52GZUDWcOt9Lk11Z8iQUrs+WWQlwVlnXLDEkl+WUvrZM+CPPpIec1V97HIqnwVKwJQtFBTbNhT6MBdQIKjSfTs4QUG0VydhwLZACi2RqGcsP4TDC8xv2iFTkfskNegbD108P7+kaT7lUHjOTx0bpwBHCPL6cL3EmDMwS0PuEim1NK1Ikap2w9wCnq7NHVHoVVgHeuf0JbwKqwtfmDE1iuK3qrZwvRtqPF83I+8N1s35vPaIr7BuIQ8F1r6bLJ3jt9hzPTfIUHSFI7wQCj/U2ByQkQK/gW1IM8MMO0rn3fycR6CsYGMwa5LrSqhNYYkcbiyyEmwscMUDm2/3tpWttwT7F7knhrGgYp1Ge+DUsUfKJTBKLWmj0PotUu1FasRmS2voqnv0t4fV+vnG6HML738KZ8HUOvng7KpHoMhgMyvJA8casvG2sCRB+vnHxVx+pJv8swvC9/AWPDVy96Xf8HWz7nVC+rD7mwfE3iY+o0/Q9JfbB/SCDhTpj8rL9lmjTdrKAOm/FfNP5lTPWgNvI9Sri0Ole0gpIdUm7e7RWzu95pjnbX7RTYqx5mMEbgdzEc8jvzU8Z3iNYwpDBlwmy2RQ02DM2rRA8vzeKY1mK6a7UL2EfeLPhVrxovg87/9EjrXU47oplBm9iEfjhAMGkr07QZ3I0WY92lYRvyl9hjeGQMxlrE8ySivFsZoO4SDNcRhKmscJOjaN2GAdoBx/HVUYY4lfgTAG9ZRuRjs4QTAZpcu97fDsxIJN/Ydz2MugI8WyS6i3B0aUN6lqTdQ+8EDQ+TbJkqgDhhOm7MtlKMUH0uNK/5AB/Cf26IIXLXkc4oDah8tI69ACbVqVffdaEBt+UAUF/G70eciST+FNLHcUH7CBVnCFDWR1OQUoh/4n76wcxg/ScWg4OFXJwwIRL189Lc6FKASNUX0cvx965YeHFUcQ8fho0S9T8hUgABCKnDKZMJeysijYw7LVV1MrACWn8wyCP/QnHA3x9jU1+ZvtTJ9uUOdqunKLdGs2qiDOkuM2/CyVkPiSD7DhhQOp8Bkx2EVLc/KSJ+axud+OMrkrLI5DtHlnPOCba6LmY41hcI/tTUMHmig2SHBLjhuXIcM0fWmDbe4g5ZgunI8frjw52+4y3lpgzejF8+sjpQ9CGnu1vGjsNUUFNWElESkcPHdU32VlN558DsM3qtXMWHqEH1AXel3sAQsUXhN+D6NXLDLeYXKaUULsNwAhi9PnSoqifDTHw3ME9DFobhusL2ujTfdQ4i6vd/w3xTXvie+N7FET9l1/BHJsXCP4ozPilP4wbTr6ENzPei9Ft8HtcMh3kKbcKT8WKXCIwjbU8QgPzxu/GzO9Ghbjo80tDif76dzPX2+iS+qj9wZHAM4siAFWYpB1FeaiCqUFp4s/+YGceMvdPwX2tJIBhKOdbf3cAIL2qmcy8pLhGnoOApniG2sMkfe4WCgQhGbxrfpu13/MWCIlkCYlyPTU3d36yEibId63ge4RI1uhRlP9E/rNwvGB+RwVpidRVuqHQSRMU7fRo+4IUeTLB5qFGKNr3f0ZBE4G7dodajKOWOdfYKbplka5xeL5ctvKhXmkEbQMOIRL/f37DR+Jt9KMe9paFsQvQD/lPCRSqD/JEqZQL/zv2ZXvP+8moiMVjF8fe1t/YR9u6lBeiHMNj8cKbQF9fI0A8VB+GLv+tYF6S1xdAfRv6Tcug72CjFPs6bchr70BKMf7F81LqJk2+hoQO70uKIN7+nkKv3zdfcMubOCcVL5p1fOl3OnWAkIiLR5Gn4cph3Yr8rxausEPBVTmKWSN8QKsf4iNCFL6hVNb5ACtVOTyQEN+7LSG8tQBYAxfRuJTZTxxvXtLRG0bDnMBwwPqfD3EgrqPFVaWJTornGXf2imDfDVogvBxwkU+JZ4a5oL4V8sI5uPTxuEz/t2B4bPI8xXKsPin083Sp8Usf2T01gUduu4Qvo93EdA+0UvvBiin+C08dVQMKbkEHBhGVCdzbBnBKNwclR4SzqrYXxe9GPAq7h3RZ4jwOhR9XX18paneZRhITImNCa6ulwaDwTeNRFHtOOr469VmOOXueTEUnwhMGRW/MHQH2Qfrg1+1nn2WdifsdauH4rb/dgsgGLfhdzmUk3a880fA2+O95Ofr/fdd0c3b/XXvr78zzX3/CdB3Do+GX9bfiwpxq2oAY43/7SLQKiLgYVpX1fv13HM3xPm5VcND3evBvOwfXw+mCcoxrMlA1Lj83mr0C/okw7bQFrB3KqkY/OHsh92/TOwbu28iw4F13rIcMlFnPANupupELFo052WgHgmsxI0PoAWI91HZGGQ9N3KPpMNeCiL3kwhlK7MW1LTXGq9meXoftYeyArz6fvKtc3aleJ5yGbDcMimqdNabB8QYdTbAHVn1hkWtublLNSA8nacw0VG95pAfvI0FpGNBdwTlkm19BWa6Y0rKQnPKe4Zk6VM0CB/wMIpyQUX7datX8cn9M/JtE5VSctcIJJr+1xxRAkQq0poh6IgKpdAv2i0thVqji4+MvLDWAN8ugvC3/KLSMZbSbce38VXkLhK3NFc3itfcXS4vQ9NYhh1iZKKv904ryqD+7AOFoDbt8JXU/h7gD8XU911+Xbb1/bNj/v1BdE8D0kVHtpply6sT/sPLGh3/6645JAz95auOGN6sTNvXR8QP7e2w3o7XwZsxxKxAx9jS5O/1zYFftr4Sn11X+b5fd9BvrsemyphVbKqxORz5q7O/E481nPwgsxaI/W3u3RbS0Hx72Vs4P8VH0LGCRlYiJKLlFvUtXA7SyEEQbvdK9QZnIKinWn7IbIGc+G+IhxEhsqBMaO2DDhxPOXGMJx3wZnhvGFzhwL4G/wQSvEb7cqPBghkz6WhIHbMKxSxwXdZ+sKXh4fgtKxJ8Hbywdv64hCWhr/NzD0QfS+AYJ+5oQBH08CnObzh3nrcCpPsCJ2xTH2eK1bE16kyjTrbLw4RwRLmNBEaCCs97W7CBlYis72ywUxXrxM3o89MXuxwXnHWTtnmFJPRYnOIWlauE5dQ9ZaqwG4xPL53GxpOg8Gdc3T6C8PHrYApUXWkRpZE2FSmPCTOc7QaHrPcZd2jBBL4Cq8/EadKvLdjJzja1AwTZWcQ31JAxHxDROPJ
*/