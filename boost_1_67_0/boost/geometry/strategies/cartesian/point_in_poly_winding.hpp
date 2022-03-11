// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2013 Adam Wulkiewicz, Lodz, Poland.

// This file was modified by Oracle on 2013, 2014, 2016, 2017, 2018, 2019.
// Modifications copyright (c) 2013-2019 Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGY_CARTESIAN_POINT_IN_POLY_WINDING_HPP
#define BOOST_GEOMETRY_STRATEGY_CARTESIAN_POINT_IN_POLY_WINDING_HPP


#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/util/math.hpp>
#include <boost/geometry/util/select_calculation_type.hpp>

#include <boost/geometry/strategies/cartesian/point_in_box.hpp>
#include <boost/geometry/strategies/cartesian/disjoint_box_box.hpp>
#include <boost/geometry/strategies/cartesian/side_by_triangle.hpp>
#include <boost/geometry/strategies/covered_by.hpp>
#include <boost/geometry/strategies/within.hpp>


namespace boost { namespace geometry
{

namespace strategy { namespace within
{


/*!
\brief Within detection using winding rule in cartesian coordinate system.
\ingroup strategies
\tparam Point_ \tparam_point
\tparam PointOfSegment_ \tparam_segment_point
\tparam CalculationType \tparam_calculation
\author Barend Gehrels

\qbk{
[heading See also]
[link geometry.reference.algorithms.within.within_3_with_strategy within (with strategy)]
}
 */
template
<
    typename Point_ = void, // for backward compatibility
    typename PointOfSegment_ = Point_, // for backward compatibility
    typename CalculationType = void
>
class cartesian_winding
{
    template <typename Point, typename PointOfSegment>
    struct calculation_type
        : select_calculation_type
            <
                Point,
                PointOfSegment,
                CalculationType
            >
    {};
    
    /*! subclass to keep state */
    class counter
    {
        int m_count;
        bool m_touches;

        inline int code() const
        {
            return m_touches ? 0 : m_count == 0 ? -1 : 1;
        }

    public :
        friend class cartesian_winding;

        inline counter()
            : m_count(0)
            , m_touches(false)
        {}

    };

public:
    typedef cartesian_tag cs_tag;

    typedef side::side_by_triangle<CalculationType> side_strategy_type;

    static inline side_strategy_type get_side_strategy()
    {
        return side_strategy_type();
    }

    typedef expand::cartesian_point expand_point_strategy_type;

    typedef typename side_strategy_type::envelope_strategy_type envelope_strategy_type;

    static inline envelope_strategy_type get_envelope_strategy()
    {
        return side_strategy_type::get_envelope_strategy();
    }

    typedef typename side_strategy_type::disjoint_strategy_type disjoint_strategy_type;

    static inline disjoint_strategy_type get_disjoint_strategy()
    {
        return side_strategy_type::get_disjoint_strategy();
    }

    typedef typename side_strategy_type::equals_point_point_strategy_type equals_point_point_strategy_type;
    static inline equals_point_point_strategy_type get_equals_point_point_strategy()
    {
        return side_strategy_type::get_equals_point_point_strategy();
    }

    typedef disjoint::cartesian_box_box disjoint_box_box_strategy_type;
    static inline disjoint_box_box_strategy_type get_disjoint_box_box_strategy()
    {
        return disjoint_box_box_strategy_type();
    }

    typedef covered_by::cartesian_point_box disjoint_point_box_strategy_type;

    // Typedefs and static methods to fulfill the concept
    typedef counter state_type;

    template <typename Point, typename PointOfSegment>
    static inline bool apply(Point const& point,
                             PointOfSegment const& s1, PointOfSegment const& s2,
                             counter& state)
    {
        bool eq1 = false;
        bool eq2 = false;

        int count = check_segment(point, s1, s2, state, eq1, eq2);
        if (count != 0)
        {
            int side = 0;
            if (count == 1 || count == -1)
            {
                side = side_equal(point, eq1 ? s1 : s2, count);
            }
            else // count == 2 || count == -2
            {
                // 1 left, -1 right
                side = side_strategy_type::apply(s1, s2, point);
            }
            
            if (side == 0)
            {
                // Point is lying on segment
                state.m_touches = true;
                state.m_count = 0;
                return false;
            }

            // Side is NEG for right, POS for left.
            // The count is -2 for left, 2 for right (or -1/1)
            // Side positive thus means RIGHT and LEFTSIDE or LEFT and RIGHTSIDE
            // See accompagnying figure (TODO)
            if (side * count > 0)
            {
                state.m_count += count;
            }
        }
        return ! state.m_touches;
    }

    static inline int result(counter const& state)
    {
        return state.code();
    }

private:
    template <typename Point, typename PointOfSegment>
    static inline int check_segment(Point const& point,
                                    PointOfSegment const& seg1,
                                    PointOfSegment const& seg2,
                                    counter& state,
                                    bool& eq1, bool& eq2)
    {
        if (check_touch(point, seg1, seg2, state, eq1, eq2))
        {
            return 0;
        }

        return calculate_count(point, seg1, seg2, eq1, eq2);
    }

    template <typename Point, typename PointOfSegment>
    static inline bool check_touch(Point const& point,
                                   PointOfSegment const& seg1,
                                   PointOfSegment const& seg2,
                                   counter& state,
                                   bool& eq1, bool& eq2)
    {
        typedef typename calculation_type<Point, PointOfSegment>::type calc_t;

        calc_t const px = get<0>(point);
        calc_t const s1x = get<0>(seg1);
        calc_t const s2x = get<0>(seg2);

        eq1 = math::equals(s1x, px);
        eq2 = math::equals(s2x, px);

        // Both equal p -> segment vertical
        // The only thing which has to be done is check if point is ON segment
        if (eq1 && eq2)
        {
            calc_t const py = get<1>(point);
            calc_t const s1y = get<1>(seg1);
            calc_t const s2y = get<1>(seg2);
            if ((s1y <= py && s2y >= py) || (s2y <= py && s1y >= py))
            {
                state.m_touches = true;
            }
            return true;
        }
        return false;
    }

    template <typename Point, typename PointOfSegment>
    static inline int calculate_count(Point const& point,
                                      PointOfSegment const& seg1,
                                      PointOfSegment const& seg2,
                                      bool eq1, bool eq2)
    {
        typedef typename calculation_type<Point, PointOfSegment>::type calc_t;

        calc_t const p = get<0>(point);
        calc_t const s1 = get<0>(seg1);
        calc_t const s2 = get<0>(seg2);

        return eq1 ? (s2 > p ?  1 : -1)  // Point on level s1, E/W depending on s2
             : eq2 ? (s1 > p ? -1 :  1)  // idem
             : s1 < p && s2 > p ?  2     // Point between s1 -> s2 --> E
             : s2 < p && s1 > p ? -2     // Point between s2 -> s1 --> W
             : 0;
    }

    template <typename Point, typename PointOfSegment>
    static inline int side_equal(Point const& point,
                                 PointOfSegment const& se,
                                 int count)
    {
        // NOTE: for D=0 the signs would be reversed
        return math::equals(get<1>(point), get<1>(se)) ?
                0 :
                get<1>(point) < get<1>(se) ?
                    // assuming count is equal to 1 or -1
                    -count : // ( count > 0 ? -1 : 1) :
                    count;   // ( count > 0 ? 1 : -1) ;
    }
};


#ifndef DOXYGEN_NO_STRATEGY_SPECIALIZATIONS

namespace services
{

template <typename PointLike, typename Geometry, typename AnyTag1, typename AnyTag2>
struct default_strategy<PointLike, Geometry, AnyTag1, AnyTag2, pointlike_tag, polygonal_tag, cartesian_tag, cartesian_tag>
{
    typedef cartesian_winding<> type;
};

template <typename PointLike, typename Geometry, typename AnyTag1, typename AnyTag2>
struct default_strategy<PointLike, Geometry, AnyTag1, AnyTag2, pointlike_tag, linear_tag, cartesian_tag, cartesian_tag>
{
    typedef cartesian_winding<> type;
};

} // namespace services

#endif


}} // namespace strategy::within


#ifndef DOXYGEN_NO_STRATEGY_SPECIALIZATIONS
namespace strategy { namespace covered_by { namespace services
{

template <typename PointLike, typename Geometry, typename AnyTag1, typename AnyTag2>
struct default_strategy<PointLike, Geometry, AnyTag1, AnyTag2, pointlike_tag, polygonal_tag, cartesian_tag, cartesian_tag>
{
    typedef within::cartesian_winding<> type;
};

template <typename PointLike, typename Geometry, typename AnyTag1, typename AnyTag2>
struct default_strategy<PointLike, Geometry, AnyTag1, AnyTag2, pointlike_tag, linear_tag, cartesian_tag, cartesian_tag>
{
    typedef within::cartesian_winding<> type;
};

}}} // namespace strategy::covered_by::services
#endif


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_STRATEGY_CARTESIAN_POINT_IN_POLY_WINDING_HPP

/* point_in_poly_winding.hpp
PCJnEjsYeeIu8SyjiY8eIMR5okYEox4fqjn2W4IOzR1B44mNkzXiFMYigxxr/mh3+8Hk64ZX4vomkEGYsrUO6MPwQeiKvrb5s7UW9i3GAhtUPrQtT9WooUPPFkpzxqP9jUD2WnPtLtMTOyMuvn2J92RBDfJUgSitSIBzVBsSyh61JDpKEEQ6vzwiWfx7ZFPerVheS3Zffrs3mKbUPxgDRTjJiMoTWlE3DVy+K0krAULlMeu/Kmuz5yPFrxRVKu/VREdyNlv0lpLOpzRgpkefXKipgtWpyK4VJXmaGMS5S1uWm2seFlFIT6DpLumMbqfHKx+PQeN4XQPCBiPMTKU/AKavEhFdycH2SsAmYnprppIHBl1PiFG/N9reF6aIg115rFXfLyiqtPg3ZjQsf5iHbahnYwJTdQA0Dc4PNQSu3YfLpTaAw6PrQ95cJQPBfKJf4427Jlsxh5u+L4KcdIqByOkvBLFfoIZ83iBjkLZhta7UQHdPSutAuc6YscgKuC0mThjdcMwtglnIOadBCPjTuJCdQ0ZbXWgwsBHI+S0i8SIT/UO/YDwYuD2zXn5/P7RYGGQEPgssAj0D8aqnCkpB/4WHIWMui37/lIG0Go9GnCZhs0HoNU4eaiqxh/HQ5l6LRiLqYN2A2nuXsMJ7g3HIvDtjaLG9HyS9ry6Sx9mFdy/tmXJxREntYqzcTisUne8F6gyDL0vTq6wHgftWnL/IAi3kVtQqSLa5PKwCpNnfF/nPf7w/bPTO/KBrE5tXa1MmcPCi7mbQsKL0ZMn/KuIewgrrPPSOK69bTCm4qlGwo7ja54URmwOwo6zQeDYKLL4xw0y/FvsaLIvXYNkHpzUS7N6V+gtO7UD5XdGbuwpOrfJrFmFzl2TOHfLebjSFiqOliCr+uMWId8Q6di1+aW2gzUsmDUmwb4eSbeVzxLn47uf65r2da5Lpw68IPZDOd4X+oTOnnVfPJhrryl74fLTFmTbWMwioeRyebsqQLJ5uypJEIUtikaU5niK5nmH+I5mP2Jrf0Gw9Y6q+1j5Upz+mY0TvTzf3gr4JGqq6bnwV+dXlAKntUm5ztf5QqGcglejdlkkpWpZJpAzFQ9Y+g1A4qh0tufkk7vGogTNZNJruvi4Ur48eOTdYSywLv6IRhxdXP+Mj05EbyMyajhfjV6qtfKZmCWYvMyGHZBJWGjMTc8j++s9jC42ZTM44A/Fv5EviPLuwq5CmYyB6Tca+7+ZgRVQi2SuySMoRJXYta6JyWDwan6hbDm/JIe5xSt1jvE/xE2nc3t2XmTS2GJnlifmf7yKuRG5vVCcboKdxciRJ30hhn1qH8/5RpMiCKjc/uspxiPZxkHBuAunTWxNZzcWU5GkkZ2N6beyH3ZijDMyLUUzpOkObjOb6+3hNY0SzEbwY81jYOkMaHOxJUOO3xoW6epFpDfMRDT4mtxhmNWbV1VUea+NgDuNhZU7jKg5j/XWGNDvby3eV5VUfZuNkTmNiG4zJkRGmfo3ny6XVVfVsRvwRDTamZyjzS8WUunoja2PC7Pqf+P2Yryc8a5qVsHora+NYxep6F2bjUU5j5X8xodbXzqq64PCYuYOusD/lru1kyouSlD/FjZeSdIujnbsg0NSeaGodJ5AamFoLQ9xnsUVA5O315O0KutGgdK43UDtSsvUBqbW0dEs/5oHJ+1N0Rx6Ku0qGaGpy+sU1fbwLWYp807Do7zGO9IJ5xacRjcc+gzO+5G0Hcl0Pnk8gL0iqSfEqlae3xJe2FqegNXKzTiK07hbtwtJRWnHfZf25YtfX/oZn9nX4+wic5hhPC2Z5vNK3FWOhTuPZXYqS54zTZuJINXEmGrjtFq6HWM4mHwvixslK8dTrf96X+mv0ToOMG3Yz1kmbr8dXi5GCy8K+UbK9sPwRb4zuJWpEwW9rK/Hcozq1lB4deblUWXH8PmtbT+DtKyfuj9Q/oCghSYcDIFLBTCG5hgOEZRPVkjESFl2gJKlLGQJy7JbfwA55DYpDz4nXR5uLGrmvOZi5e/lc+d1GdV3FC7geBKXqLFMEAzVtiofPmQ4u0MWimWxDmuxn2m9IvwLj/Bp3LvF9PV+2nWc4Xzadp3lPtl/0Mo991gQmHd+DLzRk6Ia0v8mUVoF5iSGnCXT70rGhvRuH+bQ+u7VwOACHNQiqLdeBvsZE21+RHNBnnJeA4nVh6+vaB+OtnR58YZDNCGYTwapZSIgImf+OHMGO5NBedbIGdTl00nU5AEe6P1t/3cOp0ckBF0o09eS+wGCimQX0DjrvTswgQVlCxlAAWcstCOHn30AGwoKu+54c7R+wXh+XPvrxtPHfxHfOEJMrWfEORuCxqUrwiClNQbWEY64Z0+wY+9wS7zNL1bIMZPDQtM+/Faiho6cxb8IMSDmWx4pwpmUMYs3TohOGzERM5lj8Gy2obtpP/Of7Oka2cccB90CZf5AwnCa4b1wieHrD4W1et+UuaDMeUSB4Jr8yWyZa4kcFXMQcbz2CirGb7UiXl2FNmakNPH+h9ghJXsw5torXeLsnJag3rk99Scl8cPeFw9OThwzB7OQIVqyin6dFtWlvEsCNxL3lz4Qb6dyoqgHf1+J9vDs4pmmwZouiFRPGaw9sXNfGPD9tfSrMPA99wdhEhG4FLDhvZKfbHjFjvVVl2KYa13hESMxf0qImmEgV/E3tqcvwhKgZhhpnQer54MI/C76eo6NXp8anrO9f5jBcd+KD0MYjDEYszJAcSjLERgvXt7mpm54FGvq85doks52UpYVqCb77XWYisj0rYHQhzBjBuqiopMvgQgPV/ufs/sa+9m9CC7DJMiRIsZSm7ucgKW7tvg/G9XAiJqQ92nuzoZgL/N+T8wlhND/LVapu3RmGaQ1e88phjybtrKk9cZ/+/SP1Vgt1duk9WoQ/IMDz94hRrKzyFX+3guI/NAicNl/nI3BCyk+xoAAk8xVPwymmskkN03p4I4fekjmRekGhk+5VkX5yxpPyl4L/NJLouY+nDE2i9OngMf15Hj7lhocCPCAB6pQ7grgUkvnp0CTsO4KYPSd3Avl+gwsVsI0DWIkYuwEA7FYI11qlff83zU44O2ye0y5EQvIF8gPMTBp8fGvFvO9SWQzlVGzRTCtO9aMvRkl5FiVllQBNUKE9UH1YqTyiSLF8dvAvuhxpgmLZB4zjnZ2y/OdBCo21Rs5motBvP4EJ+QrKqtrGEDj/QdDyAxcG2LTk9qDkAGomVfmI4jYj1Nj0PFjyW1+AiWAlyE7TcMgTYx17Q8zkqT+twvtUeT1+iZISgp0QdK9vJUe8xJsJwsO/A/6dq7YTniWsK6gd8sZCKyLrxrh41K+0mMiQbPbabID6ax5rkSCB5DYOIGwsgifAPouS7mEXRuCUkeuwk0jxloTbTQFf89+iQhFA70hnOMxkRbRODN28Vh2Q9C4/mz4YPCcw72F/R+8lITJgfv1oRpbktckN4UicBNBmjsUlQPzPoH2Q6QT3TzlPFR+FZ2KOJCMfOOM3m0/h45MupAvhAOhBQn80DSicerndRlXHFXIeoDJ1QsWFaimdrME5EoNrJFMzCgNeevTXLKIOzH4N5K6MSbF5VMrJZ5rhBrMHZpiPc//EjxPrR4mRSLQCv3D5X7CxUcwziNewd4w2tkdysXyxNF5IPVCfBSg0KaEmpCLIqk+49hk1ICk0zklsv4dDsZC+Fq033KPSM8dqb3AzKDC+Fgzk2MuVjz+5YWJn4RKVfGgrOAHzff3iYiYRuvueGklwApYQRGBY77Y6VSF+CFtDrPTEdRmgI0lN3jx1xjAcl+cZWjE7P5qjDLK9w+GLPrxKuxWIT4RdeP6dN6IVV+TETgsHN0Ui+iCRPRKMfgASceC3pMhOil5P7YiaBSyIV9oAiy46otQ/BkTrpBHPR+ROFui1wXggc2ad/JFbM1VbRckd/vfGp9u8I6ioE1l3OqlKf+EO26xsW84wlY6OLsE1epIWaVA7NOsnpKMkUmXN4SJYU4tjFjMkEzXEKtPWZyKOwxargWnUaR7hiXVSYzMkVUk1mxf9VBYNCCAn30TPOP918ZKGWEYQQgDXp5KJqWleYlWam+BS64xU7D7gzgWKE3IQLbWsE1DGj+lQ3tGQqt2n0Z35OH/IZJJy25DUblUhljVnyoLHw4EgrB/w5rNfPQxcBVKWSpDWUAWGLk5g1ns3Z2pcNbrcJJ5DIX0kfp2ONzU2ikpzEc+1lRWCXE488hI/eqLqnzW4c+/YUOYLJJ5uQyeWn3kHt1UZNyHNYDlA9sjAlqXvyGGS4IKhnUXo2K+7AxEQmb/8I8BzrtEhe8jM16n+AePrs8C792DdbB46CH9qAeBITBc4oQSgSJf0LwekRa7sxpr9wY4YFfLBdIyX1pHjYeuiQdUMGOxE6krRtZfdAkY9pOWW3l5Q6RRYxEMgq2hZjT/ff3ZnbRSwKQRb73TtiVnfEdOg8kRi2GjetyVRAMrfKkS7VTX8mL8j2rox3tBY6JeD8Ow4gr3ARhJXxJZyGGjbMNjOWceFa1guDV/bL90GY8tmVzlaun+QUM2MCWCaJq51F1EmW4+VQxQtJYBKOkL04UZIGJWQ1aTNxCUY7HCelm/FlgF/UDY1+RO7iYW5bzO9lxN2f9PhpqPdM9WsS27nHLiu2n6p28e+z4prQrEc9oStECgRG2vBmEtZK3RKtZKwUQh4U9QlGMMbUG2JX/opFK0pHVXzZ3OqK3CxU2khX2hQOz84rTetS7zynxu1SHSHvDKZheGrDwwu/17zYfKYwoOVBZjkcucl77T8i1ofxKWj7sqOpaRspFg0RcrPUuDlv7hs1itvGmlcm1CGDowIfBhiOisl7XHyCvA68NZEFFE5xxelHrWYu2GlntJEd/68IsNdCwyOLO5A4sYvigyaI4tU2SJAVmy5o0TTCNTPFzBxIRprhO7qU9YovYf3WUXm4IHgBNsc0tkeFekadicqCKdqQc7lNpS47MEJhbBNNllad/iYtPtLwHdt8tmdkMfJEcmh0qPPSpa2Tj59JFMUK0Kk42P/swiDxQtDirghsHoa9qSw2TkkHEiRefQSIh+H/GEKFjUmoSLo7+W+vLzIsSFbyPTF6CXUwtFJdMgtr1dQlelpXviI3KjF1l0+JNvxGwHyBKrdh+B526U2iNd/iSKdpu0YDncL/X7DTkq6QelMBt9oJ9obT4c1KrkPh260nsEgNPsoSHV7phXdyujizNjmfc+tIm7CwBO4D9bxK2oKBXu9fewkPqfYpxBdwm2Q7opSlwE45OcvB+uWhOT7nv/Y73QRHmt0rebpeNND704A+PrYiQwNkXmtd0cpvD4h5NgBi3E9xMYoXhmq1Tt212m+rFT6q7poroQFaEFZlRWqonzzoEaYDH3Dv7TKMe8o6d9hqRDaCCTFNCPbCYjaz7iJGx6VWMmcYpoAzkfd4MdFp9Fs1r+yqtp95cW+vTxsBTr6y2zO+lxwtIIXEHcSsgh99aevTiOsR9xcuPRCVknEovJwdUEtpckph+4NuyIm4QRwNUvQe3ei57BsCVm9tjANmzU3EC4SUnJ7AcrHKvoMaZLkHDGNgioyg3jbz6Il7wCh+jItUAuupAYf8nYAynfwxhlDeQwZ7QSEPMQ1JwhEwj1dgHDQDsBErKcb9Bil2FHm2woEuBylCWtsKItHW1Dmz9OACgu8IfgHXqKg4E2iPyzvPJs56rCjGD0DQdGq4NRKYbJ7C6XgJ8PviOiS/5bT0KQqemlw6nnJxz8NxWnEYL8XhLg37TCGnJ5mQqwI7zlsFJNDl5mrAesg60kyGvWt9RFNgz3/YcCeT4UUGnUr2Rs4YWcZwnIclAR+rzrRbF8F6regkqdjG6w9U2jiQ3OASaV/CFp2KsHVG0bSYBjRFoRmJD2O4rl65zcOrsve47dwEQEknvvxhF1kocjhTpnGNc7h12bucR5VzfGX5oamphlstxzWzlD7VCxDtXfUmjFvDYvbR/+EKrG5W2nyIOxUfqRBSV3sS5vMZNqj3PO8uubj90MJuHJ62aZBT180cFiNVh12ZpB7McXpRY6bSiytNcsA2cKq0gU3/LyKU34aRMcVvorOkzowacoX9oU/9C7bPmvQ5GBvRzPKiE4k3EZjo1pD2goLWNrn+1Oitg4GVlUsv8lUL4gPU41snx69IsRzE/NAL/gMbOfoC6P2TdSBaxr8DdiuUdlPiyKRpPS1hhSC1hue+sU+JppREeozXJuwbyYs7/QR0oPIk4Bz/EMx9Aivj7lYbWfHB+cpUn32aajeyPJlF9bPU6p32jpP0ZQWQoAICdKe2TbtdKxGPog+pxq4wA5FGkMMlSNIZkcdUrtwtH/EMVbTd6W0SAQsQpH6PpZwynbPnKL3FlsarIwtijZfscg4FlTyI6C/ZoSoxmRSp3fIvNnxxeWki8m06ZYuxkdbzPrkjcZZeGS3/KiyCN+Isgw2COrCbQm7lboXMxArI8Cny1+Hynsey2AbXeCdrRlSL9vKoxAfhLdP63QntHgWrCwb/rgN+lrRv8iyIIhbsfwHroNlBfLLSwANKsFUQpdP+ZptxZ79eiVUfOP+AoyGqac1NxAHBpMKdwah5u/LitxuVN58h/ZgxjNvwhW7A/6mDEa4mRG88qFwwnDfFYCYMIK1LcAAFvcMmCDfM9oDB+TK2dG+lOiAWsqtpl+ic4YLq7UkDsMfx/AQj1tcGmKXSic4Z2oCvTfLpq3hsQrtT0EASAAZZGOzDC0Nx5YaoVWkgJzE1C0ZnqniyZ7li1BOuGGgtTVVy+RWR//UUio76r/G5dTPCNAy2pddnKcJgrG0VmVS3act5TyNCL7Ca+aU9vX5Zv8AOaoeFnJKAybexfUmuCiEJ1CXd9UkEf7E7epx3toBxumXEbBl1L690qmY3TSjILyEIaiEvrcDiW5iVpaoVKZJsCAMOcopqCaVTnRIx3vNQ+zpH0BlrmlKEjyv5Fd2hH7QyigYMT0eCKVlMRykRyvKnjuSbWyN1IF9gppw6ImSPoSgQQ9mklkSYTxmYDSmVGCAs1E10ukwHBRTr1dKxKFupat4G0nioUSI0zfpDHSLfGMxVLrdIO41apaOMuwgFZICv8aKZ0CxeYQA8p/52H/o9LHhdg1gmXaG0WPlM7aF486vWLbxznKJw5Rwa8/bLAv4nDFCZwpXajZnti1Am/yDgT+r4iJNnq0NTES7ci8bXGdrradVWT3KHVksKeUotCU0Tu9MqBiSxLR5MR3owHpvwPs3SZqR/tm5uHbwRJKWBYk2fJIJ18FcUSHgPYS45e9vZkVeqsVpqXruOKr6TxkEcZltb1UEvrxQHxPVtYhU1iOgMAbo5bbEHJU4wpsh1VQpVCp51gACLP3TYmjqtfodDFdxM9TOHvPtpa5lK+cu/IRa5aiGAZIuY/brWkZ0DezzWkyXSK0+hD1AisQo2r5fHCbkG5GwUnooSNbZgJMoLzCJ+pmf2gFjy1rg3QOyZ8DS12OxVndLZ+dTEXjImhHKl9XGhskGrS4IqOUQIK8TCoFIdA+sFPJPib9OIUiASz3Su+ss2fGX8KJVn1pvk6+kHXm4xUhlb+gSI2hw3rZ5fBpAKAfcbKLtIrJZtZvhX7S+0coHvt53J8wavZL0d1/keE6UIZrqtYUS4+QNhwEHZSZi3fhwetc2Qj+crW+gLlW3LTQhTsQPUrUhLXUWY179RZdPV3XndEBprDNrfwBuMaYZhfy4j1NX4m67ghXwU1fq7uvCFbIuIR77duj9tz/XY9ex3xl/9WnEHk3KGFnjN4fVWi/0/+XunZLBEjA1Ncpvj1NZOz7vYVuCEyTqdQhzfimMqoO69upAi8yNg44RkASQ5/Y3oISnBTzakA6WXz35+AO7va1TwOlo1KfBeVotPOjWle544o1gmZXIqrIc7pcmC9mgpzIL1/KVuIpQ6pnGub1l4jaG6FrfXZY2IPHnK5zhc5/0B5dSofQZ9YmR4kQmCfq14ovfDUE4xLiuPGBq6aLrUZVQLfF+QieC8LkPyEJKVL0IG7BBhIQDPX6SQ/gchLWOdiH9Y/nbuifWbDJ80ioXMengVOzf4S3yTbrNO9hP2ons8wFBpjUvZwD2mIcHCnoWOJXpGM5avGb22LqjTDjcGjuGcC6Ewwyr3OJo4AECQuA637hxu0tOhhoM5epwHsMf9CdKDiPc4YeAWBfMzFCHueEAq5g+j6wtqE5snSxujEL+vUJrnjKnSqX0sdbpgr/M7oulw7XCZFd2qYbfB1R35/mtUlm/iuspE1j+MLtjuekGcdPnw9/lMuqgZNpXcUnd4fp0I9UXrV1mu1IcxRCWbwF1GQCqDNqDc59ZaDZ2zsLSXEK3k5LBbX/Kjd2bqSZEcbaoTzReKV9Y4u7MIOlRWrhU2BECvo11yBwmgTSxYEXB6/Of2MnR1cLGDec8BNO2ZyMCPWDbIuw92y5JsDTn0RE2YN/nRI6VjQnXoRkn7hASLDbShCTAXiDYl4EW+nwbdjx/mbjcnVq5KUtA7/sJyg+tkDp/XzGa7IB86DNsvqIza6xIdVFqB+6mTZRr09xHaAaQInyBqHOeu+bIS8pBqpfOVoS6fMxVfJEkWZuQObs6gXoQ58Ua+A+AbGEuW78Q1/o706aB/zFTB7RXWmSexIYiDBXHeliNw8J6IPu/bU5AS3daP/qJsIpJFichKQ/xvi+acoCvcFVyG1L0ki5UmAP0B5JuXKqzAWDqOJ8qEuFdYP48zvoOQjL6xPno2avBKVMv5BYpewAin8U+eqtiYw3N2jqQr0Kpl5XF69M8AncfU0U3wcCBWss954Oj5CLy/qd7ZWdGZynpagSqTgIVPuCCe+4hc7C7EijsyOY5zug8bU1N1WYuJ6ub0TiKR21wQ+cpjdVLRlwjrBwsnVtxauUbyvrLpYLHA1V9whS11SmwieJhi3DQIfMU+Qly8VFHnUic4Jmw2cy8C5xtzcW/vazY2731QrGJscCvHMoOlyzTtkc92tJ/hZ8PF8byU8GmDwb24alU8Rjf9SAE4hqbm9eetShLWYx1bA+lD+yIj3xbiBEjr+sSXNXGdmkWFF9EpV1TGz/6oQWEpkRWgmGNErhvTzYwNn1FaNP1lvNZxR2vMo9A3esWZk/MhOsPxbsv/r1CgqwIv/ny+to5UyxjG6XaU9cBBO6oGnw=
*/