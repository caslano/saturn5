// Boost.Geometry

// Copyright (c) 2021, Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_VISIT_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_VISIT_HPP

#include <deque>
#include <iterator>
#include <utility>

#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>

#include <boost/geometry/core/static_assert.hpp>
#include <boost/geometry/core/tag.hpp>
#include <boost/geometry/core/tags.hpp>
#include <boost/geometry/core/visit.hpp>
#include <boost/geometry/util/type_traits.hpp>

namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{

template <typename Geometry, typename Tag = typename tag<Geometry>::type>
struct visit_one
{
    template <typename F, typename G>
    static void apply(F && f, G && g)
    {
        f(std::forward<G>(g));
    }
};

template <typename Geometry>
struct visit_one<Geometry, void>
{
    BOOST_GEOMETRY_STATIC_ASSERT_FALSE(
        "Not implemented for this Geometry type.",
        Geometry);
};

template <typename Geometry>
struct visit_one<Geometry, dynamic_geometry_tag>
{
    template <typename F, typename Geom>
    static void apply(F && function, Geom && geom)
    {
        traits::visit
            <
                util::remove_cref_t<Geom>
            >::apply(std::forward<F>(function), std::forward<Geom>(geom));
    }
};


template
<
    typename Geometry1, typename Geometry2,
    typename Tag1 = typename tag<Geometry1>::type,
    typename Tag2 = typename tag<Geometry2>::type
>
struct visit_two
{
    template <typename F, typename G1, typename G2>
    static void apply(F && f, G1 && geom1, G2 && geom2)
    {
        f(std::forward<G1>(geom1), std::forward<G2>(geom2));
    }
};

template <typename Geometry1, typename Geometry2, typename Tag2>
struct visit_two<Geometry1, Geometry2, void, Tag2>
{
    BOOST_GEOMETRY_STATIC_ASSERT_FALSE(
        "Not implemented for this Geometry1 type.",
        Geometry1);
};

template <typename Geometry1, typename Geometry2, typename Tag1>
struct visit_two<Geometry1, Geometry2, Tag1, void>
{
    BOOST_GEOMETRY_STATIC_ASSERT_FALSE(
        "Not implemented for this Geometry2 type.",
        Geometry2);
};

template <typename Geometry1, typename Geometry2>
struct visit_two<Geometry1, Geometry2, void, void>
{
    BOOST_GEOMETRY_STATIC_ASSERT_FALSE(
        "Not implemented for these types.",
        Geometry1, Geometry2);
};

template <typename Geometry1, typename Geometry2, typename Tag2>
struct visit_two<Geometry1, Geometry2, dynamic_geometry_tag, Tag2>
{
    template <typename F, typename G1, typename G2>
    static void apply(F && f, G1 && geom1, G2 && geom2)
    {
        traits::visit<util::remove_cref_t<G1>>::apply([&](auto && g1)
        {
            f(std::forward<decltype(g1)>(g1), std::forward<G2>(geom2));
        }, std::forward<G1>(geom1));
    }
};

template <typename Geometry1, typename Geometry2, typename Tag1>
struct visit_two<Geometry1, Geometry2, Tag1, dynamic_geometry_tag>
{
    template <typename F, typename G1, typename G2>
    static void apply(F && f, G1 && geom1, G2 && geom2)
    {
        traits::visit<util::remove_cref_t<G2>>::apply([&](auto && g2)
        {
            f(std::forward<G1>(geom1), std::forward<decltype(g2)>(g2));
        }, std::forward<G2>(geom2));
    }
};

template <typename Geometry1, typename Geometry2>
struct visit_two<Geometry1, Geometry2, dynamic_geometry_tag, dynamic_geometry_tag>
{
    template <typename F, typename G1, typename G2>
    static void apply(F && f, G1 && geom1, G2 && geom2)
    {
        traits::visit
            <
                util::remove_cref_t<G1>, util::remove_cref_t<G2>
            >::apply([&](auto && g1, auto && g2)
            {
                f(std::forward<decltype(g1)>(g1), std::forward<decltype(g2)>(g2));
            }, std::forward<G1>(geom1), std::forward<G2>(geom2));
    }
};


template <typename Geometry, typename Tag = typename tag<Geometry>::type>
struct visit_breadth_first
{
    template <typename F, typename G>
    static bool apply(F f, G && g)
    {
        return f(std::forward<G>(g));
    }
};

template <typename Geometry>
struct visit_breadth_first<Geometry, void>
{
    BOOST_GEOMETRY_STATIC_ASSERT_FALSE(
        "Not implemented for this Geometry type.",
        Geometry);
};

template <typename Geometry>
struct visit_breadth_first<Geometry, dynamic_geometry_tag>
{
    template <typename Geom, typename F>
    static bool apply(F function, Geom && geom)
    {
        bool result = true;
        traits::visit<util::remove_cref_t<Geom>>::apply([&](auto && g)
        {
            result = visit_breadth_first
                <
                    std::remove_reference_t<decltype(g)>
                >::apply(function,
                         std::forward<decltype(g)>(g));
        }, std::forward<Geom>(geom));
        return result;
    }
};

} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH


#ifndef DOXYGEN_NO_DETAIL
namespace detail
{

template <bool PassIterator = false>
struct visit_breadth_first_impl
{
    template <typename F, typename Geom>
    static bool apply(F function, Geom && geom)
    {
        using iter_t = std::conditional_t
            <
                std::is_rvalue_reference<decltype(geom)>::value,
                std::move_iterator<typename boost::range_iterator<Geom>::type>,
                typename boost::range_iterator<Geom>::type
            >;

        std::deque<iter_t> queue;

        iter_t it = iter_t{ boost::begin(geom) };
        iter_t end = iter_t{ boost::end(geom) };
        for(;;)
        {
            for (; it != end; ++it)
            {
                bool result = true;
                traits::iter_visit<util::remove_cref_t<Geom>>::apply([&](auto && g)
                {
                    result = visit_breadth_first_impl::visit_or_enqueue<PassIterator>(
                                    function, std::forward<decltype(g)>(g), queue, it);
                }, it);

                if (! result)
                {
                    return false;
                }
            }

            if (queue.empty())
            {
                break;
            }

            // Alternatively store a pointer to GeometryCollection
            // so this call can be avoided.
            traits::iter_visit<util::remove_cref_t<Geom>>::apply([&](auto && g)
            {
                visit_breadth_first_impl::set_iterators(std::forward<decltype(g)>(g), it, end);
            }, queue.front());
            queue.pop_front();
        }

        return true;
    }

private:
    template
    <
        bool PassIter, typename F, typename Geom, typename Iterator,
        std::enable_if_t<util::is_geometry_collection<Geom>::value, int> = 0
    >
    static bool visit_or_enqueue(F &, Geom &&, std::deque<Iterator> & queue, Iterator iter)
    {
        queue.push_back(iter);
        return true;
    }
    template
    <
        bool PassIter, typename F, typename Geom, typename Iterator,
        std::enable_if_t<! util::is_geometry_collection<Geom>::value && ! PassIter, int> = 0
    >
    static bool visit_or_enqueue(F & f, Geom && g, std::deque<Iterator> & , Iterator)
    {
        return f(std::forward<Geom>(g));
    }
    template
    <
        bool PassIter, typename F, typename Geom, typename Iterator,
        std::enable_if_t<! util::is_geometry_collection<Geom>::value && PassIter, int> = 0
    >
    static bool visit_or_enqueue(F & f, Geom && g, std::deque<Iterator> & , Iterator iter)
    {
        return f(std::forward<Geom>(g), iter);
    }

    template
    <
        typename Geom, typename Iterator,
        std::enable_if_t<util::is_geometry_collection<Geom>::value, int> = 0
    >
    static void set_iterators(Geom && g, Iterator & first, Iterator & last)
    {
        first = Iterator{ boost::begin(g) };
        last = Iterator{ boost::end(g) };
    }
    template
    <
        typename Geom, typename Iterator,
        std::enable_if_t<! util::is_geometry_collection<Geom>::value, int> = 0
    >
    static void set_iterators(Geom &&, Iterator &, Iterator &)
    {}
};

} // namespace detail
#endif // DOXYGEN_NO_DETAIL


#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{

// NOTE: This specialization works partially like std::visit and partially like
//   std::ranges::for_each. If the argument is rvalue reference then the elements
//   are passed into the function as rvalue references as well. This is consistent
//   with std::visit but different than std::ranges::for_each. It's done this way
//   because visit_breadth_first is also specialized for static and dynamic geometries
//   and references for them has to be propagated like that. If this is not
//   desireable then the support for other kinds of geometries should be dropped and
//   this algorithm should work only for geometry collection. Or forwarding of rvalue
//   references should simply be dropped entirely.
//   This is not a problem right now because only non-rvalue references are passed
//   but in the future there might be some issues. Consider e.g. passing a temporary
//   mutable proxy range as geometry collection. In such case the elements would be
//   passed as rvalue references which would be incorrect.
template <typename Geometry>
struct visit_breadth_first<Geometry, geometry_collection_tag>
    : detail::visit_breadth_first_impl<>
{};


} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH


#ifndef DOXYGEN_NO_DETAIL
namespace detail
{

template <typename UnaryFunction, typename Geometry>
inline void visit(UnaryFunction && function, Geometry && geometry)
{
    dispatch::visit_one
        <
            std::remove_reference_t<Geometry>
        >::apply(std::forward<UnaryFunction>(function), std::forward<Geometry>(geometry));
}


template <typename UnaryFunction, typename Geometry1, typename Geometry2>
inline void visit(UnaryFunction && function, Geometry1 && geometry1, Geometry2 && geometry2)
{
    dispatch::visit_two
        <
            std::remove_reference_t<Geometry1>,
            std::remove_reference_t<Geometry2>
        >::apply(std::forward<UnaryFunction>(function),
                 std::forward<Geometry1>(geometry1),
                 std::forward<Geometry2>(geometry2));
}


template <typename UnaryFunction, typename Geometry>
inline void visit_breadth_first(UnaryFunction function, Geometry && geometry)
{
    dispatch::visit_breadth_first
        <
            std::remove_reference_t<Geometry>
        >::apply(function, std::forward<Geometry>(geometry));
}

} // namespace detail
#endif // DOXYGEN_NO_DETAIL

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_VISIT_HPP

/* visit.hpp
qLElfEsBLmSPnsJZUp33JRYkLF55ULL/sQUazYD0LxmwEXgmKyLiLeJuHPmVpBE7pEBb+CevP112fwT///8uykNLaalbFyI93QmsoX9EmYlRF53/1i8mUx8MyC2KCwQRV8QEuODBAgNiwrLULNysUN2imGz3w0+sW5KRUrFdHx4+qQXYgocjyXVcVLTxQduSNrXL5c/J9szJ98rr2/vGR4d3z477ZdOKDqPHF1o327hNs0uTGS4UJRbyHpF3IaMbiBTBvygjMC4FbfR5z70ZGFk4POF96BjIWwFCSpDbNT1GeyFs6vSoZQ4kAaBQ3u+3PbbwWmOc0QkRh72xsX16M3Wzsn+ReUf2dQ6TNtHE4aR1pdpA4gZzFHlEqNtTswXPa3xgVApjRirNOIl9QNDo0WbmV2KQer9HZjK8b/PwgLMFdrPM2LKh3D9CUA1nd4U4feweDF2qAg+rGnJ2dXB9wUZxs7mZCXc9eDOEWNiEVehfc8I10HnvdvrDGISRZuc+j45aKPrjr32KY0LMvS/XN5BO/PIhaDAf+quNifosJdxa2F5k+bUTYX2C6y897za3kaLTum8s7iP1yF3QN9ZnSzsjd2V6t7DaKvR/9L1XPgluqtyGRMEThdB06np0vT421S8iOOuzyT3IrXY2MBO6b+ZvjFZCfJynNxwVGr7W68blZXekXA/CbIeF8NOxvXZXFw66uGuiMRovDnI9Mi4GVnR66oldnVeAxxQtvTlbykKchbVynnlhoJm67Gjv8prwfRAbvEcrhjwIQZSnnxwdPZ1ohfCuSsS3Xzbix8Dft5ssWDPD0l2ozsq6YprhJz9FXzJko6+Qu/UDm9svl9KXyoBnPj3ftu5Pmy4KRKY5vs4uAmRu1H8kxdyUlFPUa5Su56lH7zuVMjWwK9VLs3V1FpvOlURS5hXuVYJsvjdxRUdUtN6Z5+kdlQnrzFQfeSykdJIYeO/XhhlxDc4LwtFp6z0NoDp53Qt+qA/y6elHuFQxt3EaVJW9bvzPs3hEC6KlZtI+97thj3PwNphb7tl9nORbsjkZJIITl/+Vl2q4HaU7K7c5aZzntydxO3SoWqvZcbrvZbV3CPJWXinWOmn+xCeUxXG+POEyfG+16VTM15vQ+hxYLIafMADZbr2ZaF0GxyR7/57T6oY6ejRUzhjLHiP2FKEW0GRhqDM57jRauFN6fNjrn73BdS2V1jRZo3dyMC17sn1oqzf6WPudJ63Yjhs8TW9WLzpMYb5vBx1rTF7a60tM+be2/lL2ROD8SB326RTgyXLSCzDyDJRfPAymlvaHZIV87bRyvs5lIXOubMkoohNnkXUzvK+dXWjlbHUYzg9XqjE+rDVk93x9Dzd4pytrywxTra6XVDqbeRncz2EDf0ncCNNkenNUCs4WpdovfcCcMNgGWemyPrR6G4vc9HZHiG5xZVV5MV/X+oQIjAwi23p81V88hO0lhQhwNN/MqaU1nY7tYtfVCFulLS2k23UoHsW9Pz6hc3aj34/7tPx8Nhsa3YhCT+2xnzyHULfz8JicNpTwunrLXOXWh06uCsbgZO8wvnn34JrSwke8f38PKmO259x8XxnsTIWJklj/OEg9XtP2sPEuttauJDelROPQcKFn4EtPw3H4MLj57EyDX5QcBXdx26xqLuDNn0Uv6W5+PEaKrwsLMqrUfLXpLl0ztzCQhtRAqDsehH5tkLNc1Vq/47q4uw4ny2R9bNmSP8F2eT6oyN5/hBx3IcPLXnLv3vtwNPHiqj9uk2m/veO9xQS6fPlGs59hwEpRQU2jE4LiGuO8kiI8e3BPU1lt3hmPsODRnhj8LNxFRlezZCfDLfsxcdyfiSMksBPBu6sUYt7ychfM+ykBO4wOi+kbYf0DoHuQZ4bsnppyO9VPkq5XA8lIS0qMbrt7zYk+O6PSqBIXHX/nXxFYZcALg5d+gCh9RIy2tySibGLCd4OOO26HiGTNfWyTGr/I7+O9wq/0csPVrnpnaN6VNK3jIg21hN+8cIg91zNk8WIZfKhIBuEtPr5bINTlyeaR+EGTrMXQJP3iEjG88Q8rb2K7joVMFe2UVooyrlVGXNLfCpBXJhmnEhsxvP1gkz/LAXHX+74hJOjhlEc9+GTTIx96AT2092TydVgEiWAA0wKKBSoExPQFtQP6FpsJyIRGAQjio78Fq4VbBbECdQY+8KXYpZsCfoUoBeMBt/C78ZXshecDtoNuhXctCytnzAXKBnAH/PL188VHAIkEXOTDQAAdBBzr/dcLMgmCw0dDB54KTwWWDFwDbOmHpMdYq0i93AFEBkhh743gCs8GmQlm4evY67YLZIf6ivmK+krqa1NyDvAPsB2Ih882l5cudXw+uUb9qjjZbZ+al/Z4hRf6vdy+tdiXd5ZOhasmwJu+0IKLTmVRdqAOT8w3CsuhhsDZJWNfKwTPWp8RyT4cPaAbN8SQ0ojmpH81VehG023ciGWGP8d4J+rsVWjVM7j24+PnO88j/2xiDv50k1QHXfdBZl72558TzIYc2uNCMKy6+j+aAuyEdAS0HCwuAuZtk8lIO3p9Z+K0BwKrNZrnrwkEhF30wxNbCHss6zP1sr8mGXE05hLSDBtAISXDkGh9qdSvwcNExSKWBU/8nmOJOQNMgvLZTuirzglTL1RfyEM0megAxHzUsgXuV61wW5DJEu+qtKVXd9DXN0DzjQVIPYvNGnsN1/6c2hYvFYPR70/rh81xXrPJ3RmH7d9s+FuD2lZrPgnSotkscO6OLGNfkuwqYLkQJ6J+0acf7rmBJRe0bV/iD+xB9hHvd1Z5MOOf8XkvByRuHswS9xbz5mVZPkqvFL7bpwpuHYGSnyiN8zQK2O/mgTrdgQXWcpEPZIsVMPVwt+TICzU6Vm0+OLRJL1Xp87zrKi0KNcMKbh7/yBM2lJsUYnIZ3LacjG0yhlWqRbvzr79bix3HD9/Q9zyZ6Wq1DstkJI+S15mfYhTDGZbm2xPHPuDN837Evg75ZZVpXg40r2lkdSi9C1keHyDBGqIVZ2V8UVfBFoEDFGdHfA1ywU6ZkmK7ysSACYr7eGtRS8HxMqK/gYwAj/im/s29bOxdd/LsjlRSKd5OWvbUc0ac0Nq6Rc8uJjvS0Sz2DdMOev00HdyPONhbPpNklBS3zpThjD/keSk3qXfyRIV/pt+3zVyVtxWecN9Jzd/tYGbM9yQWKrbJx+kUiLU8uMcERYJqjIdoZ5C15WiIv1eqTYobHJ2JEp99PLl6n2vKvqQFug0XLk+0Qe6EvZBGWJfkEJxLpxE0r8BsBz/yiG/NvzflNxPHX7S3w25hZctSt+StPBphs5Sj0HdxpnwpbBp3LARX8QxpN+dWwS9PnXyjl7ROJC8HT9nbOEoYPLhjs8CSG2T8JBM0N40ouXjJcPcmn8+mZAO3cK/2/CjN+dwqzfWYlLPRiNqxh02Qa2G1MTm+caU0tGWOHCHR6B44wKZgt20OH+nQwNu/8aTk2LklT9S0VZ7cY6Wwtn5GScYoyTvvz2dMXGs9HzkgpABqgTmW7TH4T4hryezNjxalTZy0ZU4dcdGk2L1hpVi2bo4eNSvVbVkquOHLOr2EVW3ge2rj55NyrrfCF4d9d8gi11jumHdua4HZYU4WBV9wFrfd+M1ZH8oTzDE35WkySkv9uKd3ZA9ZryJ0l8iPnMV/9MBi/5xdM2yZC7JK52/4nAQ4RbipL4uN59sOHLO1sBPXkbv6SvfZvLhZgB5/i0zmEWkRty6Zu25fxZ8q77WBThPPaUJXE1o1EGkxt4qcCiuLdaf0BLAzk7yWIXHj28HONojdh+Z9lBZ9ta2s53hU/V7SmQm5e3d4R2aM6mI1ZAMIR8hnX/QOG55V+tKvU6VH0R/JMqpnsQ/06cwe7le7gbiQ/iIwKsZA0vSZD7HapeSqyM4RGULh4vKqY4P3TFJD3jOprVlqCrYvCCc3z9jNM69tbWCCPDdtGtUe8VXlZ/l1r+d3j+q81PH/wXfHiFy+lAqINRUhBzIjx4k+/BcSMZL8eEdnZl7r5r+MgIgcFys0ykArGB1V5ZwNZY3Sb2M4LOuGhfERVuLH6MJtlgdD0u76V9EOq/7yWd21PdfK7cx/wHgU6QLTSKxFs8oZ+y1Nim52pZtMN3hLz2EtC+xZZ86kEaPSn3LCRoGVtGIpgSmvkV2MSyLOBjGSJYza6yF5yyqStF61cxeqyBbv7vFFgiFdW98ZKzLOHPG1Jsk+sEsCKSN78hZCkFMkzZQtanrN6O8cB6gW4DEA9WzVlqO/pOeZqO7D3Iu3HqmryFoUiU3Ag1z50HM4fZoZBvIxJd4j6TwOqRehBDKfSKod6GZlKwgu0Z1NjhHLXNSfTEhntEYRdPAEO9nma1+06NNBQ7RPkVF4oU9cEdrucOKSMIy7hX/fhpz2WdDVsXpQU5LoLqmlj+EtEP4BWgnF8wC4BYpmKgQjXUjpHH9pWVp5l4M895LMkGvIp/j1LpDT/YEmzlDNuNcYCTRHOiB3BEKt7oxoH4n+pmh4wFVMSKzXQx4/qkf2eoZnR1SYnV1owMLKopwirl1gmjKZQk+tIcafrW2mQz4Xk5DojOas9F/DDDSZ+CEZsPNYotNg4FaOjWE6U7G8DRZfQBOOG3ifMa9d/jvCoK7cDRQKHh4KFAGFQ79ZZL/aB80gx1ofllrXZUHG4jlonEFz8SBoavV/pGbmJQ67y7OXbpYM2z4dD0eufNZaPtrHFXBHwhxQ06rGNMF+wsDHSyqcE6VDRp1bH9KZ8F5pmCMLk7KDHL5Un/NPekmnYh2gMGuB4JpYLZWTNhBQ/EaXV2n/lCgRxp6l3EHBOxklGXjbylsgiTv5hyhNEi/LtiNbb9HD5nI2VZc6Ddx7BGi+nZoRyd/THzkCeArIDNrqOQpVuMJfDOiEbQef7BugBVt6On15QC8aSCXiDmu1yLYCXF4XmzhSx2uEZQT6D2s43Bmf4CaCj5DuFOBvXS9QLtArSCucKz6REPgk6DMQul8InP42wCBQg58gH/DsAd3xGB+HHIgVMA84lm+2KB0+YDIOoqn9VSjpHcGVOPg9wjFUlpjpPd2ZAN7fmPieWvymjvgRMdZ7Njd/LnFPMZf5gEeirlEfhLWZ6sY6UqnbFQlxFrZy5r8JX0vniSoKCeoCQsgrRMiBj5WuFWtJR8+IdJke5pLq1woDy8FGPzVcLfoDDBBySiR17Hv8R5bLUO+GmmZMZmQulqBN8rLl0fGSlAiPN8q5oJIDZMJuIsFcZB5OlCTxaoTNw5TjkXOzIsjCEeBvOJgEK258uKnlJsFbZwo/dxRShVcRIbiaIOTXxqv+Kg6FeCkCi0YThGuJJcTCXSRzxpMwYWKhw7loyGjYeOVzQcNlS5s6EebwFZTcuZwXZRut32PIZWnTmdIDssSwxZOcAplqUnrToIqSwgVjGKDq0sxtIg1BcJvUZFgGpcUe2kaSVcXw9ETCQoEL9WdnCi3LGio5CVnEInFQxWgbVP6Uw5Br7MsqW4M/2EMyLIOlwspuphYHw7mqleLCNmxcsU/Pril1T9nIN/WcGuIfPp+f07wREWEU+LkfNcf86b5H4V9+yL3kL3zLforXATgg00kn8fZffeqozRR20Chum25JpZPDWmnbynaYVm1VGRWApvXFE49w/hM/eY7Hn/TM2+Db+R44pjbq4NeTg4DbO1EcOIpM+8Y1URnoMLQALlUX3VvifiVN4Fzbn3Uf938ZcXb3z3VbNTF7aPItkr0HwGe+r2rGdpNRaLgx5OPwmy4aDpcqSl48eHG0vK53N7J+dA66HpCyV5ZkcfCgrgMYe8CvPs7dpO07aHnvH+l6KoFedE+2bXJOS8J0lhcOjosycPEs1GSUgKtORG2674TE7F/bhy98crxfuVojdqZe3BluGG8EZBPXnEVKwUybdi8iC22Udx0y0dS9JHvDJPe3tBDZ7M86jXQt7PaRPFhN892tyLszFhSjqddcHA+EZGiPwMLdYFIctlJ5sSh2jyHY6At7p75aYdwHjtwWaQqecv9C2VwTsdEn9k0py3Gj3e8eL/shCxJubhrYGUAEZTj+Vqg3tbCeRgQYNrVQplT3bJnY6AcF53P6wvL+xH/DyMBg2jtGCSvFBCeLvTOy0YMMTXlByrT5vNrbjXMPuvgrXhN2Y2U60N4B2Y1/DeLuJnqEl/zepKwGbiG1n86VQX8WxhV7X+Ww3NqvEuzT9t40usixgFB/M++2GH3VKfH6neg/tlrh3R56Z3Rb3l6n07rdp/Xar+cDHHaUD5fiLdvcmN/h+i+SD2iBJioBC2Tvh/zjdXIkrKpgMjBuDo6guyJDoOPvOWH2TJnSDCzyMozujYkPxpmbuoZ/j4BExNoedv1R3XCMM7linBIVD+NG2NzwICMTTvJoCl+kfKli8nYNUDLhf4c1M+VGHz1s0dYWTByZkHTDdfR55F4iJFOs2hS4lcLQhRSXcIYqv/HHTf0+eZYBPmVpBUQGxikxkpaAtGKDLQ46Meq39LACm4kRTo6pKyRzfHNukK9wHaALS6Pbp+ybUbIb3ne2pijPYOObUTMrCaaauzvsp1m6+x6gWbjb7ush/DbpEVSKRtkquRv+42DnubIy437zHhbLyR5nWd5HLX+KC3JS2Ncz7wGm1cy8pTqOqsgd8efg2LcAu16sTckuKJyrX9fcHZ3WbThA8dvL73s3HCUTapMBdKUVYsYGzYa6zSZyIt5eN9wdjdwl037A+GVOZjgq9ilqKZ9X/WcCeMV2n0EzBSBS1XLojZ+htQRl08zuC1WL1k6042v97SH1rH2pr8ZZYnKdfhp68/kH07NB/1D6qhy/MkIKFBhMV1tMaQduleslIzCl8ca69Sqn6yLnwKJXW2kSM9ofW5WF56D8ZD3VSRf34fss7qJNs+/I+2mdkZamJaSKNpulz4f/eX6lzPrZPGbixFHgZRG+7U68Y6HnMOChq8n2IJw1RXiGUrPx5AzdM6Kh10lBi/Crv/gJw2YafxMK9ARYZktmmhlNj0rFLqV3KmJLMV5H98Dr1TL+uXi6Q5S59Q2qGirT/ViT/Ms90/pYopQXVBWgWuaOlby+l/xHJghPK+jeG7hFtQ8WRLVst91P8TsrghM69Hy3Z50Tuza1ueXnpuwsyii4kEyENnBxveHkq0mJIp4sLF+h7FRaGvJvFhFk3gHRX6g8CHuHQLnAbQQBiL+BsQWCrtdp/Guf0zcvnzU/Dz3fM05Z9srHDSs6lldN1x8eOw0bVcIGsL1WEpqO4K7D67jqPQm1eIwWxsR0O5Ij6YIiK7M+6kWbB/kYagn2P6PgZcyPnrZ6KrLwpsAN2e7upzamescSyUCVNCS+GHGAVApjBEdHTHA+7m21wd1nYMFbqmnpV+Q1tGuuVi4m4Jfjdk/g8CFLsymyI54L3rKpQ/E5GeMXbM5N0d4GWMl2MluGzMAYA2teejMxzI9MPmYD17d/sGr/Ei2nQTjLGkzx1vc99YaLHyjAwTg+NnrMyQvyqsVsFc+C0VACJDs67SqPpGq8w4E9Gt9tLOLoSbJ6vqdSVhTc7IA+4arTceCqyZefJBVhac/ADk+kjXeJxYwxP+6MJxpiQUV2voS2dG4Zs4tEaVqcFTHpgdbz4vqB
*/