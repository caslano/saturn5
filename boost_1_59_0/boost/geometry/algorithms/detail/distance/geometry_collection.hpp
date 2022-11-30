// Boost.Geometry

// Copyright (c) 2021 Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_DISTANCE_GEOMETRY_COLLECTION_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_DISTANCE_GEOMETRY_COLLECTION_HPP


#include <vector>

#include <boost/geometry/algorithms/dispatch/distance.hpp>
#include <boost/geometry/algorithms/detail/visit.hpp>
#include <boost/geometry/core/assert.hpp>
#include <boost/geometry/core/point_type.hpp>
#include <boost/geometry/index/rtree.hpp>
#include <boost/geometry/strategies/distance.hpp>
#include <boost/geometry/strategies/distance_result.hpp>


namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace distance
{


template <typename Geometry, typename GeometryCollection, typename Strategies>
inline auto geometry_to_collection(Geometry const& geometry,
                                   GeometryCollection const& collection,
                                   Strategies const& strategies)
{
    using result_t = typename geometry::distance_result<Geometry, GeometryCollection, Strategies>::type;
    result_t result = 0;
    bool is_first = true;
    detail::visit_breadth_first([&](auto const& g)
    {
        result_t r = dispatch::distance
                        <
                            Geometry, util::remove_cref_t<decltype(g)>, Strategies
                        >::apply(geometry, g, strategies);
        if (is_first)
        {
            result = r;
            is_first = false;
        }
        else if (r < result)
        {
            result = r;
        }
        return result > result_t(0);
    }, collection);

    return result;
}

template <typename GeometryCollection1, typename GeometryCollection2, typename Strategies>
inline auto collection_to_collection(GeometryCollection1 const& collection1,
                                     GeometryCollection2 const& collection2,
                                     Strategies const& strategies)
{
    using result_t = typename geometry::distance_result<GeometryCollection1, GeometryCollection2, Strategies>::type;

    using point1_t = typename geometry::point_type<GeometryCollection1>::type;
    using box1_t = model::box<point1_t>;
    using point2_t = typename geometry::point_type<GeometryCollection2>::type;
    using box2_t = model::box<point2_t>;

    using rtree_value_t = std::pair<box1_t, typename boost::range_iterator<GeometryCollection1 const>::type>;
    using rtree_params_t = index::parameters<index::rstar<4>, Strategies>;
    using rtree_t = index::rtree<rtree_value_t, rtree_params_t>;

    rtree_params_t rtree_params(index::rstar<4>(), strategies);
    rtree_t rtree(rtree_params);

    // Build rtree of boxes and iterators of elements of GC1
    // TODO: replace this with visit_breadth_first_iterator to avoid creating an unnecessary container?
    {
        std::vector<rtree_value_t> values;
        visit_breadth_first_impl<true>::apply([&](auto & g1, auto it)
        {
            box1_t b1 = geometry::return_envelope<box1_t>(g1, strategies);
            geometry::detail::expand_by_epsilon(b1);
            values.emplace_back(b1, it);
            return true;
        }, collection1);
        rtree_t rt(values.begin(), values.end(), rtree_params);
        rtree = std::move(rt);
    }

    result_t const zero = 0;
    auto const rtree_qend = rtree.qend();

    result_t result = 0;
    bool is_first = true;
    visit_breadth_first([&](auto const& g2)
    {
        box2_t b2 = geometry::return_envelope<box2_t>(g2, strategies);
        geometry::detail::expand_by_epsilon(b2);

        for (auto it = rtree.qbegin(index::nearest(b2, rtree.size())) ; it != rtree_qend ; ++it)
        {
            // If the distance between boxes is greater than or equal to previously found
            // distance between geometries then stop processing the current b2 because no
            // closer b1 will be found
            if (! is_first)
            {
                result_t const bd = dispatch::distance
                    <
                        box1_t, box2_t, Strategies
                    >::apply(it->first, b2, strategies);
                if (bd >= result)
                {
                    break;
                }
            }

            // Boxes are closer than the previously found distance (or it's the first time),
            // calculate the new distance between geometries and check if it's closer (or assign it).
            traits::iter_visit<GeometryCollection1>::apply([&](auto const& g1)
            {
                result_t const d = dispatch::distance
                    <
                        util::remove_cref_t<decltype(g1)>, util::remove_cref_t<decltype(g2)>,
                        Strategies
                    >::apply(g1, g2, strategies);
                if (is_first)
                {
                    result = d;
                    is_first = false;
                }
                else if (d < result)
                {
                    result = d;
                }
            }, it->second);

            // The smallest possible distance found, end searching.
            if (! is_first && result <= zero)
            {
                return false;
            }
        }

        // Just in case
        return is_first || result > zero;
    }, collection2);

    return result;
}


}} // namespace detail::distance
#endif // DOXYGEN_NO_DETAIL


#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{


template
<
    typename Geometry, typename GeometryCollection, typename Strategies, typename Tag1
>
struct distance
    <
        Geometry, GeometryCollection, Strategies,
        Tag1, geometry_collection_tag, void, false
    >
{
    static inline auto apply(Geometry const& geometry,
                             GeometryCollection const& collection,
                             Strategies const& strategies)
    {
        assert_dimension_equal<Geometry, GeometryCollection>();

        return detail::distance::geometry_to_collection(geometry, collection, strategies);
    }
};

template
<
    typename GeometryCollection, typename Geometry, typename Strategies, typename Tag2
>
struct distance
    <
        GeometryCollection, Geometry, Strategies,
        geometry_collection_tag, Tag2, void, false
    >
{
    static inline auto apply(GeometryCollection const& collection,
                             Geometry const& geometry,
                             Strategies const& strategies)
    {
        assert_dimension_equal<Geometry, GeometryCollection>();

        return detail::distance::geometry_to_collection(geometry, collection, strategies);
    }
};

template
<
    typename GeometryCollection1, typename GeometryCollection2, typename Strategies
>
struct distance
    <
        GeometryCollection1, GeometryCollection2, Strategies,
        geometry_collection_tag, geometry_collection_tag, void, false
    >
{
    static inline auto apply(GeometryCollection1 const& collection1,
                             GeometryCollection2 const& collection2,
                             Strategies const& strategies)
    {
        assert_dimension_equal<GeometryCollection1, GeometryCollection2>();

        // Build the rtree for the smaller GC (ignoring recursive GCs)
        return boost::size(collection1) <= boost::size(collection2)
             ? detail::distance::collection_to_collection(collection1, collection2, strategies)
             : detail::distance::collection_to_collection(collection2, collection1, strategies);
    }
};

} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_DISTANCE_SEGMENT_TO_BOX_HPP

/* geometry_collection.hpp
izgymrZL86tDGOzliznAabpa7gC99/taeHJkL8DEpfdyFY2grAEVu0/cidCdpnp1nww/rOWECOVrL1fx82EOGbWtaaaBVWV94wPzWLGDshpqOYqQeNuTpyMeYt4dLI/NBBfmyfb1jDb4ukdrPWn0n0F7dK4M7j4JhleS/OMTYqln59aX/BwrlJIsyduJlrZFRhjHVtJmLz1+nDeUNnsFnhY6HW5x89Y8g0fzaOzVWvflMtudKFiXKJhNBeEDWVz7c7ZRUYDRf7uWN0L350SUAw65+VGEYeMQ2UexKDcBdp0MQX5vwywwOi3WXsfuKOtRbLRTasXSRo5S1SNjjk8b2yNuHQHOkB3/MYc038TIgPGDj7qfAeVrRqDOWbLYk1bjZhehCMDZ4izENQ9cas5neVQAb2k5py7ncDgXcxRH5ndkJK+YrYHfGjxFWs4JKqRuQhOmhVKXXdbbtkbdxMHR31Ru1b5P3f71v8Iwkjr+jnKjasLS0SPc58sI5Pc64p2gvxL6m5OISO4sQGD76Rw5UN7nslbpKE8Or86ZFTDPgBeMtq9IoBX0+zmLoHaxunRpwdI7AhWZoxITxqaVvdma4d+JZ082vEdkE3HuxKvWiVobxF0RnlA9otxBz8QgaqybCZMU/TqaU+5RVSZ99zfLh3X/wnRfIrn6BIZ74m4ZJrLsrPI1yKP+1hF/66iMOMryKVZmI73YXnWNkgA5EhzKygy6GxrTYER3X1x2RKBHwqfQ3yQFetrJl++V6RICkkW5Y0IQ6XU62s1Hp9Z8nTo15W5dWZWj9oo1j0GJxezDf9+F9O7irtQvvcZufFp3ExXZL4t8Rtx0NVjcx+Gi4NBaR9rSL3Ni/y3EZnKdAjuZ91wedBfFXcV/KV8lVnxnvPYC7hst3pzSdOa4prvdniyOKg2IJLibRr6Z9TcjMU00oClq78kb4foyrnB+fiKnhCTRdcekwha4lM4/ZxokF7RI6cl4OkjsQ/sBZnwqm/yVzf7Ktf7KFv96vs6znm/zrGf3AJVzpay3ahzX88sv4np6aok7O/Nvce7sRmq/WKNVMq4T2l/Oa1Afl7ZaiA8JnMjhCOaLFPEEZdBYGvxtLf62Zn/bWv+iJrFidib2ggWA/vleEn12cod3bpDy6L2+ZL+R0GpVKsQ96U397eB5jsd8097MVDGUijX5NrHzEckV+dsc/pWW0l+wZulWdVFTrXi3JKGDbHYoMzSXhT6aX8ZFWqKxa9Qqs38T+zXp06OaESmaE7Oo5SUxE6vFUb+P+wsR7nd4GBfmjEO4Uwegs3yN4KUuoKlpCixQ3ADIMnT/37kWWumrZYWrJgsYV6t+Ij4BvPvOzM81+qstyv3wRqV+7L+tSUSqRjVUKZ7ppQeuzy16KFGd3TXreHOshANkl8h42yzC//FOifI6BpTLCL+JQ99hfXGm6nuaqCj0opkdZ7y9MYs48G6Owb+6CUrpN8WTiIJXQGMgmSmDKD6VrVE/Fnlo/4dKrfh236imvcrOmD4W6ZSaDIwUorNijOgsld71vVYOdW9Xw/VudtGqOEvEfw5kGsJCnX7i3ePN0fQI/euZcjtNR9wYIm6b8ODlSJSnwZHpIZydfQ/r9GDMDIusXzeGEalcmRqwXsy+7sxwhU4JGX448LCqu9lFYblfXlvL1X0CcKKvT9ui3ttU0Gtc6KyQV/zXAYnNt+qCNslPPT5sL47FWflfMHtCT2WvicrIzgr6b8wC48GvIyMawskjjmBDfUn2jdvW8W0GcNj5g/2DQfHbdTLaJA5qwSvIUZXejGEpWaU79xNP12ZZtxe8XSxj3V5wjOr07OMcjjq/9HUsYu9UsfhNCBaxGersZvpQzMfrdDxyKA4c3+PXLX7daqWZcKq+h2WAYv/8Ev/8OcVdxDDbyzVvrn8+nET651eovg3SFtyp7qM9bFcR92u+WeP62U+7+DstWv+D5tilcBkkjXGR/Cb2AhwFQzK4tUTz3TpH4xHOr2C75flWNluQXae1xt0Uf3jIavC/DljHzPz1Ios6H476aTYR0DUoZviGjIG6NI3mdaFab1XPwQMLsgMLjcZAyxRjoCINnnnq4HyLGpQOeYweix5fdoXmLiyWLuGJjREH38kB4K2NzxIsRUeLdLxJQ/2bx8TebNgZH84j4ce5tDXXezdzEO4VtLiWl7Y6lPrSB5u911Avf088iMFrL221K7fQc47BW/Z7aEKUHNGRM6p5jLFL1PnUqpJOwkjspGhCYpqaFfdYVct+lXtJWnhU+i10cHzbDx+UnjP55cSDzByskczBy3dK5sBhSD3AePmumbQ6CvcdRxh4izoDJwGL81MFJA4W36JWrm2gJf+mN5/6dXnjph/sIsK4MY92oZEp5RqO3Njin43KTv7UwFzNNElFmzm0/X1rCdkzRfbfjEKiZBUwj1rZDEZRyfVvhyyuLmpm4ZioAjFhpQ2xf6IPJQtgXgU6jqi+VlAJqdVQpoFFPyCmgI17h+gVsR3nHqMVVbl2ObhRj9G3t04GI99A3Vhd3LUqiXbyCRIaYEbhtys5GvmilmJNDdGmvIIqSR0FyBV3vrgrdi31nHJnTdZvDnJ7L3UDGspVy7tTVJOQKF4MkXB/t8UQWFQoynrOa767zSnYnsnWWlo5Bdw2+HB6ucJjDFTWuSknMaD4M/RZqybEA+zanBQLIiv1+oYjHkC3eKB0VRNbDnHU8FXN3tNEpsrOe6eobWvLzit/x9StcOYyd4jDSvHACj0G7WVjjD0052rlCnXR0vLYFLWyTl10R5UuzGS7cUeEdQMHqZtSZ/T3ESPrjBay/938sn3KFJH+AbxUFnf5aPtr4FteADen3ddE0IUrTBV+xu3x4yESb8bZ208IkW1lnW6bw9BA1GRREy3yHI9BnC5kneQ0aPYOiMNn+QRGXS+Jd5baRijN6q8sgdUUsSI9lVZG5w/vYwKEYAwISOpvsyYjdw8iyef+gwRp8MExguRj1E0MReCWNGIodPIDNw8mmGKtXuXHMU+yMYfHvn0z2K8f3i89jA8Vnym9V04gh3MnFkMceJuHeKrHFcKpuN8b8XtH4+fu1SHheJ3Qw/wm9eH90Aju9db7/tVh8HUrgdsKa8VfaEGqUzwaDkX2MFAi6hTfv5LcTwm4pYQa5r8uz9npWW9EFL3O+hbRfz/bA6iuUxASp2KuLGqTpbir44ztp13EaCP5I7CYlU4j4uV6DKz/oHbk+efJvRgHTgxs7a8bWEVra3+J0wqJ43OLH+89rwWWZi3zrxwGe+l78LTBe58eQNki/N3MdaZRDW6/S4i/Xszxk7+leQVlu4VxHmsTvkYNT0N5052jGrTA15W7A64TbiTt/ZdRjR5Qu0m8sReKsBO+rmHxEB5XDsOqi96+j7f7HLX1nrG+B+bjI4NYwiWHfK2nDLaOD4lbOvk4/SP84RydByIuui5A0/jCD8FFB9oKCcYYW+efE2NjhWelAkVaKVWXrKB1/oVw3HDANYxMO8Axf1gcp0+JUf5Ws92QooCgXTD7Ceqb5H/n1zZefAtB+4dm7Uht4yVjj9ljjzPGHm3xx9Wr1O7lyUdO6Rtp4SszZcywrJYZpent9OCdWpq+Ab/xYygdzYobboe2pSfD2UtQYqbeP8W/wOxfYPEvsL6OyasNbHqKhRP207Ceb73tCJ7XKB03E8UL8pltFZ6m5+KBhp71uJ5e8uZrzf4nt7FSADGEofFFHav9q5r9q1r8T7Ig8SQ7xn3yCZZ8lGw2c4lzayTfLP//Vf3uD9P0fehNqH55YJte4BPzURM6+ezfiL6uR3+h5r1lD03P+qf1txJ+e0p/u4bedG3vu70zDWL9fQlt73BPirYXKI0GXspjUlxSr9VoNCPqPM4LaMRyuKtatJyNEGC9WQEW95JPCZQZ8lACqDuWLs6tmDlRb1WDacMZPLd0wyT1lFU2KzXcdkMD2q5slk3G5pa2tShFk7bsvZyoaFKv+Uv5GQ3++9yRZakdwWwspQzfTsygQZmK87RFynVVljFi7nFv335ptFkcVoAVxXVUnPDiy/jA1j6HRlkbqH5avPtvxLd5RwOuIVbmeIf83hN+r/B7T+kWON6hADOaHP5JBX9VcKsScB0sPsMfqLxsvQf93sOIAIZNz+pu10E3UfwOMF3zlQKXqDe5QoGX2YFLvfSsTwhErT5MsoMK6V+tjhRUnwq0dhlV3MncAl/8riH62UIoqMu9RX7ju2sHLaXtmx9DC11uoDritPjyYvV2cUN7niHg2u7GuH74Q+L97m1RTdq9zbpv1y7cvqx+ukbdt0V7FA60PAaUrKaSAWbW0ePAA3l85kD16Q2J/OCoJhH706KYwCWylZRTEbZt97twIane7yJQjqgfjumE4lNk1wjK+tyPjK26dE/aUmIPDgg/IYNVEwJj+04VjkmD+SzvFp9pQCCkUq9dMVXGLKVeh2LypK36tQMiDVFosXga7Rq4i7fXsL/sgNeaYJSZSe4ySpX6Hbr7pOK3AutekHcd+bChbLet/SfgfNxmWzs8j5c+Bqyg5KnrMJaqKmVqlfcilI5ZEgePfD+KrWvVdcA0TLYPXSgg0pBrcsFnvjqirntCz9EOjRSMwJqSWPzfTEV/wTYJtiRR0ioXeAwN3He1m0WiPxKDdPJFNLPuKe7YaVv7bySrb5dCxRyPUd3Hw/+0SUoiqskzAzmFNH4SWp1btngubMH1VdYRF7rjVi6zsbA8FzwGTtWOcK8yPUaPUU9gT0QPs2+cSzxXww0/8b+n1X0kGTSxW13ZAZY09om2JhleSqbi/mWJFDnK6yeGcaF9nDCBShdtb+VwvDXlfwg9sOJMon/wCOvZjO2+13EuhrkSdx0H8Sjuk3hdzfBvAmyBwZqMBkMyTy+RVtlZJb20zUHNXEbNqPyVr8viG8luNXmyl3qubcD//JWKuKInz1DKq1a5WpIliZBYr7ueMUCl0qAe8E8Rq2nvxKav24tC9ZLSxC1EGvMJ4W9/EBhocZPdgLM3/y8jo5pW9rFuRFjp0EN+cKyPdYfQK7TqSVtd0CP5nCpbx3VUTemsU0eON9va4fRkF+hiQyCAqsQLfyJ4dOARB7grR8U9355poMwhZP6EMms9xlrGEq+gkDod9dQHOpDvFntaphrUN/BMi26OLKJ/230Tc0RXwczq9j15Bqqn8TVDkjZXEgsFYeAWDIv739CJFffl5D20jiXzFTiB2qZyN0/o3WwdFXvvJDLICaVLaSl/CrdQtWxqFAgME1dUU0v/g9KerwA7Ax1IdOt9+7jGapCPzIzdUT8a7/Vfl6ALQ7Jab6be+qnXzmuNI0QzA4EQ3l+m7+lLs/YKXrVXUEjLuYOvgZAIU1vAHWu+Vc2QFcAQ4dFmKdHcSPB4Da6QO/AtWL62Hef1NvHWxG8n9Lc76e3k94BlEsVv26GzoolPbsYnzMKo806rPwM3AE/OVwXVb50+G87rK9YWNBAwamVHr+qvofk9hXF880fZBvlIFaaLtCezScT2lgQ6Do8ysLjQt57KxmAztCI5GP8bvHDemz2q7e3AZQwjjSpjwy/xSExKOlgcnkSjcpHKNaGPj9O+m8NllFsDHQeT6n//V1z/FK2IIFO0m4lHuspF8OEd9GFtw2ctHdj53MzmrEfdYs4S1jPm8eGSW1xHr43rJBPTpLMDidGmifkbs+VheALY//Mn6HtFHq1W8YN74hTKY9l+43PElS3HAVd4JxZlPbHx4r5XacUSN73L8CGOTrozWCKY1gAeX3xYMqpRqVPC/SoYfQt2kOodricguk41GnpxVHhtMTXeesq3J8tTRNiaMN/lD87kzbAWq71yWKz5ExTu4i9rk42h+bShkA2LnwQe6xhQpvseNBuUKVTDY5GZfHnZmzOG2SReOwmZvQFnDjD0ytmA8Heuw25PrgYpbik7qg/Rs3ozLqrrONEVkSwz4rCMaEdtr7r+7huxKFf7RrIUu28kV7mkuM834rBtDgbmab4hkmeujGV6Lo9leGbE0jxTlxZrDQ1uyHr7NG9ILKPOQVfRLf55CqGkVqt/J6jiamUqd0lA37B8HAGXNlQNEmVDW6RMK73frKSLZwZmGnAGcEmcMffvTAwz4BI8MIscGHX7nFp9Sl0y7N/EJX/2BEuAqQMZ4IF0B+ZPNhAaxuIanW78mFoGpuf622H0E2rs6uoy1Iq/PoBDXXZuJVa8OqrVqrMATO1tOVDomdLx1durJ4yTdSuXLEwKfGg3Jgc+zMZ5WrLbOxx5xtUtE6HjPyahc/H4ZRDDKbFVZK6wGggsFhoXTnL9O5w4thGxVVYs4is9Rh7gNhmakAeJE5TvEA6VQ/FtdBYZpZtnq/jdSiu8f3CPEtoTSkCfiWz7F008RsScJtHtvf05uArQw9QLFi676m5hxj5N7XHrktqOl2m/gbab1FZrgy6yPfMyb9mahNE8SPfqValnWUkNraSGfDeDhhmUj2RzLFVl6RWs0p5CDZMswCd1EL+jWEsfNPNmc4ZJqlrwoaYB2/qGZqRvuAUmaGKkL4eIlwNySIPbk+YWzxrssId+lMAIW6Ye5cFA9YkaDw6V9fV5xpO1GgvSCUX3P7CxoOBwNwBnmKkTjZqB/vOOirpmIrTi+LZRuMp4M3nex8RSrL1k3rtB/UTtEdO+yuR6eW19h0bcxRniLvhQpuuNPGhUe8TJIsJo6myYShKd1Q3SjnBhOPBfjcI/ocI4/+wRr1PpWupRo8Gsl8SdnRSWn49u+VDLuxRmjmD/syT3P8b7T87y53O+NLiYfxuNH0If+/K4z9FT2cJXJOLS372LWCqwJp9trqY0yvr7G2zZkyElx+IursbtllKnfrRZqUu8444z4zJJ9eSSMIj8YaqdqiruKk/UFu/zI4tS+6xLuBBi9lTPBOs5TlSNN3fZ5OIvPlQnfkg7al2z2Uzg8F7le03WMFN1W2Cmne47d613umqU4josKjLc4vtLZ45ZTnus2yPfIbr37btS6V7bC0SUcDCLc1fXMN/J/N1B2PoNB6qF2FA3zUDlmOKJxVS2AUeJjRYoMqoFU94ZS6fBnQ/BqaK07bTyDeJ7qxAqoWeZcg3fhLVWea9vtNMXHmNsJq3xG4lAx3J5ue88T4/TOROvIx9rTCm/RngArf+AWlddw6Dm177MxPPRu/Qj3v8HV6uTzTJHAIBDS519C3wU1fX/bHYTFtiwC2wwJAFWXWtoosYmKOsGjZCXQnDDxl1oIfhAXVfbosxgVBLATZDxuoiKLVZrtUr196vtD+uDWBCCUDaK8lCUIKDRot64qcaKEMtj/uecO7OPhPb3///5kN3ZO3fu3Hvu65xzz/kebJIjVPv8x038ynpUsGAjulFs5y/tGipp6wXS5UonxhY8ouEJTaRTi0+HlnpaihVn6Om3QJR9ZP1JDQj/oBPPJorZ4uLSDu9xEC/oQEf7G55G28LohqF9qFYdAX4InTL4cNpMj/DseqpMaUek+YhmX9PB+mBtGqblvIKeEv3xjFJ4shuGRM5aSIBbQ4JazpPONF0NbqAVFh8/9S6w3ssIUtLKz4WXJDvOESrEVv7Ml97Kne+mt1JtPqKDg19LbSyHNrZjG//8PyltLGeLy1PbmE9tRPvztNhw
*/