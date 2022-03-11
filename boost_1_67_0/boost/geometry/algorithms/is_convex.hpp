// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2015 Barend Gehrels, Amsterdam, the Netherlands.

// This file was modified by Oracle on 2017, 2018.
// Modifications copyright (c) 2017-2018 Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_IS_CONVEX_HPP
#define BOOST_GEOMETRY_ALGORITHMS_IS_CONVEX_HPP


#include <boost/variant/apply_visitor.hpp>
#include <boost/variant/static_visitor.hpp>
#include <boost/variant/variant_fwd.hpp>

#include <boost/geometry/algorithms/detail/equals/point_point.hpp>
#include <boost/geometry/core/access.hpp>
#include <boost/geometry/core/closure.hpp>
#include <boost/geometry/core/cs.hpp>
#include <boost/geometry/core/coordinate_dimension.hpp>
#include <boost/geometry/core/point_type.hpp>
#include <boost/geometry/geometries/concepts/check.hpp>
#include <boost/geometry/iterators/ever_circling_iterator.hpp>
#include <boost/geometry/strategies/default_strategy.hpp>
#include <boost/geometry/strategies/side.hpp>
#include <boost/geometry/views/detail/normalized_view.hpp>


namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace is_convex
{

struct ring_is_convex
{
    template <typename Ring, typename SideStrategy>
    static inline bool apply(Ring const& ring, SideStrategy const& strategy)
    {
        typename SideStrategy::equals_point_point_strategy_type
            eq_pp_strategy = strategy.get_equals_point_point_strategy();

        std::size_t n = boost::size(ring);
        if (boost::size(ring) < core_detail::closure::minimum_ring_size
                                    <
                                        geometry::closure<Ring>::value
                                    >::value)
        {
            // (Too) small rings are considered as non-concave, is convex
            return true;
        }

        // Walk in clockwise direction, consider ring as closed
        // (though closure is not important in this algorithm - any dupped
        //  point is skipped)
        typedef detail::normalized_view<Ring const> view_type;
        view_type view(ring);

        typedef geometry::ever_circling_range_iterator<view_type const> it_type;
        it_type previous(view);
        it_type current(view);
        current++;

        std::size_t index = 1;
        while (equals::equals_point_point(*current, *previous, eq_pp_strategy)
            && index < n)
        {
            current++;
            index++;
        }

        if (index == n)
        {
            // All points are apparently equal
            return true;
        }

        it_type next = current;
        next++;
        while (equals::equals_point_point(*current, *next, eq_pp_strategy))
        {
            next++;
        }

        // We have now three different points on the ring
        // Walk through all points, use a counter because of the ever-circling
        // iterator
        for (std::size_t i = 0; i < n; i++)
        {
            int const side = strategy.apply(*previous, *current, *next);
            if (side == 1)
            {
                // Next is on the left side of clockwise ring:
                // the piece is not convex
                return false;
            }

            previous = current;
            current = next;

            // Advance next to next different point
            // (because there are non-equal points, this loop is not infinite)
            next++;
            while (equals::equals_point_point(*current, *next, eq_pp_strategy))
            {
                next++;
            }
        }
        return true;
    }
};


}} // namespace detail::is_convex
#endif // DOXYGEN_NO_DETAIL


#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{

template
<
    typename Geometry,
    typename Tag = typename tag<Geometry>::type
>
struct is_convex : not_implemented<Tag>
{};

template <typename Box>
struct is_convex<Box, box_tag>
{
    template <typename Strategy>
    static inline bool apply(Box const& , Strategy const& )
    {
        // Any box is convex (TODO: consider spherical boxes)
        return true;
    }
};

template <typename Box>
struct is_convex<Box, ring_tag> : detail::is_convex::ring_is_convex
{};


} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH

namespace resolve_variant {

template <typename Geometry>
struct is_convex
{
    template <typename Strategy>
    static bool apply(Geometry const& geometry, Strategy const& strategy)
    {
        concepts::check<Geometry>();
        return dispatch::is_convex<Geometry>::apply(geometry, strategy);
    }

    static bool apply(Geometry const& geometry, geometry::default_strategy const&)
    {
        typedef typename strategy::side::services::default_strategy
            <
                typename cs_tag<Geometry>::type
            >::type side_strategy;

        return apply(geometry, side_strategy());
    }
};

template <BOOST_VARIANT_ENUM_PARAMS(typename T)>
struct is_convex<boost::variant<BOOST_VARIANT_ENUM_PARAMS(T)> >
{
    template <typename Strategy>
    struct visitor: boost::static_visitor<bool>
    {
        Strategy const& m_strategy;

        visitor(Strategy const& strategy) : m_strategy(strategy) {}

        template <typename Geometry>
        bool operator()(Geometry const& geometry) const
        {
            return is_convex<Geometry>::apply(geometry, m_strategy);
        }
    };

    template <typename Strategy>
    static inline bool apply(boost::variant<BOOST_VARIANT_ENUM_PARAMS(T)> const& geometry,
                             Strategy const& strategy)
    {
        return boost::apply_visitor(visitor<Strategy>(strategy), geometry);
    }
};

} // namespace resolve_variant

// TODO: documentation / qbk
template<typename Geometry>
inline bool is_convex(Geometry const& geometry)
{
    return resolve_variant::is_convex
            <
                Geometry
            >::apply(geometry, geometry::default_strategy());
}

// TODO: documentation / qbk
template<typename Geometry, typename Strategy>
inline bool is_convex(Geometry const& geometry, Strategy const& strategy)
{
    return resolve_variant::is_convex<Geometry>::apply(geometry, strategy);
}


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_IS_CONVEX_HPP

/* is_convex.hpp
rYjET5QJnhb7bp12CWmf5AYaDsMfFqeR/+JvANV5TOsitqkyWEa2annagpxe2gR8GxfecjtkQU9Lm2U7zbydDZ1geFAU1cLc12vJqjxCWkYHNQvnrggN2A3EG+yo0m9jukwuE8eoIGg2gTZqA78xQTF+MagCfWovl180Oam3pfiQjDAV4pcdA73StIIMi/P6T6M52XU6KKseVVCcB48DXZufTQnsT/5Ho/sn4EftJxAaDaNHT9ygTVQpbsXA2daxMWZtjdvyOGhjEn9F3M0qphmGg4kPR9AtwCfAKc8X2IbHiOQq/5n7gzPBxNT2YeeN2Tek96SnjII14Gd9Iv6+zXovRmQJ25kpL0KtnG8Jbbh7e9sBXp6HR84OetnQNQbay6shfuUz+JHUam5Qrtq7icwGUNJo5Mo6e2wzuvd0Z2V25+T9n2K/hAOKBUs1czHNB0Eqimtkp81mzG0zlC3N7aC8iyKPKkY/i9Qt2/Y5HSfeKzG7zYfmY2uKf/zey9T8bdPZbNyrKUxjPce4dujO1/Sk2HiceKQgAtYacJx8wl2IuHiyiWSzcrWKmgqeXY/blFW112n6e2DLp+E3ZJycu2j/ECBuIxKdZVYCTKCeIVzMl2xD/K9Uv2MdFHU9UiLZicZr7W7Ltjc7XXA9JS3VhERaI/vedVYnemWJeEqpippdXusi197wEoczhrIElbwYnZ/ybYirwGMXCn+MhQik/1yuFt/eIAV5IdPAQ5pn3Zw1KtdYTUMudXn2eI3lj2VsU2kIlcnzeuggUsJ3gxSXTJw5LftMH4HNnlVv4AHfPblBeEJB0OWf1Gjnhba/Hk5hnfTcudZ4Tb0VbMyfKVgYjjN79jOGsIz+2CQ+VU1NBDJDjPW8l2WntSNBZtwgnYY3gZxK7leDmRKwnnjd6py5LbeRz+YLdEc/mF3Ba3jVFBIyhs/BZD/0Fwl0p/+Gl00qMa5ExQ5Sq/8bdhG8qWmA45DLgpMl7MneOUIapq4XykJ0OlTUANCADLxN4UQXtYEu3aJ3Y1OtXgX5yu4VP3gS+k+9SOtI/9SsnE69p3xjL+6+AeIc9rGy43kzCOpTCZPF6RxzoRsQ51aruDqnCeOAldjLhXWdNSQ0oHzZBWxTwxV2NFSsnjSbRTo+cl/mpaK/MUtKTw866vSmfqDW8TB6tCoMF9k8MRai0o9N2+zqYsIF+VriiPJgLVgaR9SD4xvPZ9Wa2CujrdUA1zZwjVocXFkH+B3s3n9+EtUCTWERwA6h0rdxMHNA04VQgEdZ/t1ACzVEnKGIkF4fw4Cx1QoeaT/Mn/9ZX0J7spoVYOj1dY89InKXMHaXVQ5CyBJXniyzaQK5mfnvJpceFyt9itvUxqmNA0jOcyZKICGhAKArNEb8eIx7n4iu6mBcl7IMTr4gRQU6BVp7JQi2wNT034H9JhR1pM2GyZWnq5xXV3ffdpDnx4bsubFb2AKjc4cIwIguyy/7MOtB9JONN2nmsHLg6XRMGLXuFble0xqtdg9aZXCjRsswqbRTa+viWuolVEvsq0S0/KysKkoXoah1QpcxW1ZtNtrZPqAP43NZ0BeF/DniNAs+nts7FnUTzX1F3KaFufNfG2x6uISncSfUISqjCchEcbE5jWdCT5GehY/zDL5ZGtM4xom0Y4lA5wknVHytGqdVNsw06iQA9/US46QjMVottNDmGM4DU4F0c9hBYROl/W4IbI6jnyuDL3+gn/KwxrJuvZDS60IguPy2aMeZsFfRvgGWmt3j9ZsY8WF2eNVCOxgT4oHNiWFeWtExQptEg8YgubVEK7JKSlX7fE5W/GfGnNt4m9U+vRJ/iFk8vzveSpETOOvpNh0574cXfS6TOxyAz5nHdR3J2RCsTY4ngbbFDTqUxV8sqgatgrQk6CJ29BTAZDLqDtYlp0uwJb2z4DGIncqt/YOKpc22uGrJzcCYhjIZfxor3pD2GctNmF7NCdgPrZrRL6hxRvkUqOe05vY+55p3sCE+4ALsPWVjADi73+i/2X7GJwiD5RDFhsTixZ6HxLfix/J2trZQrvVsSZPhlrh1r5TslBW4ZyAX7QndD+08y32L+Cyvc6G30dHHBpv3QKJB81IaR5wOOvcyjCa3jqka/zuTU9Rqn1PYoRagwy9nWsbT+MJD3aA1kGuAW3PI9gTksrzB5YgniRhOU1iNvzm2elP0SsIM8ByAei2sVDacFm5tc8UKlC6fte2NlzP0ayWGhRWMCc1E/Jv2YylaG7sMVU7KRg5ZviEhy9fq3y7aUyXhjK8pjrWoAz5EpgqNShk7C8CghDqaoa6I6DdsdCeeH3N1hGanAZyrbPZf67IVYpbZUlzJPEuen3Uwfx/b8BVYOuPQ0UcIPHSGMuNkEeOFJ2FUNeiYXbVc4zOlNdEivlBiemth9InWmVwidk7oNqCfjiG60nTyJJgpwisGoROZhiUbJrKT40ZENCRr080Alsuid208FJaEZfjnxUHHZyCnYGXxe6P/ZglC+SipPWm9fn3tie9PfPnsHumzaAgfHOZPD9MjYqbHcVkbFTCALWVtTv7VxAmwhB0p5V0LQ+iQvUY0tKjEbbjDPfUCOp+ldKa4PyBbD3Ix8lnjbkm4CkxAd4Umy2ycK5/aCHSEDA8uyLn8e4VDZjcGeW0Mv0FaZ+OtsnNxFB3y7ftUcTr2XjR9xgap+s9ZFtd3VGmE0vmz11QsagVJcXvdfKtRcUG7iTeb/2X2I6n+uWxVjZq2zJ6swcNmcp77JOUBYTs3Fe0E6o3VWdGAATrbWW0oMfiotqH5Euh+laJ2zOu+u+qoxdWr38W1Q22zqCLyHK+n/zTqvf2S59nQcHH8tES+FAdQhOdiO2tt5kfPSN/krn8/+5IRyjbdy+SYpjQZfMzyEP+2ECUEGeeof9dvDCxKnVxchSM+2honNdqQful3CZ0J3mF9DO0Q89DYlXjqn35JltlGy/iF8KQy/ETp2Y92nb3NQAeWs5d6e/GAlb05c2jVW4vHwNBRsp9O0c9DIWEfoOsyH/QZsu0rIKm+VD2yrBulbGU+HWfPM231qESpmsti4tT/ptDCH2vXOrMOdyUHUPfIXp/GNuMSrSHYGZYKOy+oLyMm+XTHPbbA23zNzFQ0UfDZVU7P31zomtEVlF9U9BHnW6Zzxty5b9eDi2KCOO+GykrknkxOjqoy1W2M51j0BrqmDVpkwLWwy3PZlvzH8RlJagRqFWyZO5RSpxNFCPJpdLJL8sbum8t3JCTs10rifFjzMuQF7EIF5qZb8PC3UntZ7ELcwOi/xavgeFSW+ThrUbAdoh9+N6qDF7gm2QAfrH/8ngv1zozdIjvBbN1FJhz51MW7Dn59ezGrIDhnyqHzLC6inEpZA11IfGN4d4eEZI9s2dThFVfn04J2XwWcgQAlrxI1IbFLOdyen1XLrCE9uZhDl8VP0xJSjbCAA12SGQlIKsjznb/C2BJM8iAdGcJ2C3TMoBPgkuh9ovm9Mw0hrmLsl16LA+bui6gncmZ5aXSogBnHrA3F2gCimGeiaTK4lb5ituNBA9o0iDF2x6lxabX50MmmlfWbLG1v6J9JPiKaEtcZjzNnMOd3ry+zV1/WNz+rYS9MudlRJACT8gGSvKfPekhM0cepyHsiqYGqu9SVM/eCz3PKcBPTOsvVsis37rDTHZL+CziCXlNw50uK1SxH6yGbRSfVljBlMWU+ZVmIJS14Z/VL6EvpCzwHSaxr3gfWE8ljpPAotIgYH2gnMdzaVgiSzx8SUqHvTYGeRAlnhi3p0HoCb97jTyrAO9qcpjX8yhDP2uzVfzq5/srpmjZqWt1E21q1pbh/3r0gv60hYKC2O0rDyMP81DBVpkpMV/757lZ17+l2ZhNkRUzfU8+f0dm2ubEyiqRlfqQ/TOEUIenMYG7AZBPq+w9vwg/fpZ7gr5GC2wGZg7OsRg0hgZVzEVpF3H6dCynf+dzjYq6iQaJHuhgDr0GyTtAearuq9jV3tvOpCNUqtUlelpS6oPigY7A3587cnIU+GBSBr3lVzPVlBWFrhkuDVY7U8WqCVo+1CLFUrvHMgky9unz/Fd6RzLjGd8N2NvirfJYccUDy0HBxbN9M7OtJriA8h2zQgpLXF4jfd3BM0kjPIfdNKEItMjHv6oy6BdLzIUtVL3ZJdbHXdaxiovRW6k3m1F69SXatxtbrqMzSLH6lutUVv014g1ebYVvqFlg78SoTsKnLIgJYTZxcytuZI25PhnlEjy0pBrWJ2caUKB2sbtx4unJFfzKb3Z64Z6Bsw3XU8Xtpx1LTQI+dONWTMwv2ZPk7EfN88s424JZEMWAXnw4zWmYZxWSKITG5f3vojJ5OYSzyqluW0zzsGYIQEc17b4H0zsUjuPOvQLGxy5qQK6zKN3PYkdP/Q/Fh5CcbGlXMGHlN2NYAX+cFXmvYIF4dNa4ni8gO34LdFq9uwGdF4Go5YF9OaZIKovsqUkOqxsmqIPP0zlOtraclnA/+zSnGj9mzW/jk9ETGDlns2PffIs7OpFlH3jXJMapxR+exViNoOprnEVMC8uPK1P7sDswjCA1wD6QtLPqkaeObNYPWtOogBCtB/I4JWfw5b6AdOaMTE9nqkSfEQZr/zEGoPNidMO5eHpnoAIlh51j8aUtHvQpjMtjWS+U5xOg7mK/eJtZR8orLI7iPYGnARKiZEow0wrkyo1FAPcDcDFbIzTooQBhRVDLR8vYBDn3PULXO0AJ5KsIyxiK24WTdb7310kwfF2j/HQfZZ7Z8lKZdeOQ/rFiHj3JgytgVAFfVwduaN/DZoTr/EJJS0A0/Jnp2lISoZ2Nc+/amxZdJt8iAj+BCI9+qYksijpndQGII2drDHp/fPhvbId0byl1sGMHERGhDmNeST0QFdWyVZ19k4cL5pebZM8CbrvmW6y1TgGalYAZDN45wMRF0hPagMH5k0rCFHiz9h6k3Qy0eZl89vIqvWjSvTUvWYTtSb7/WnXIv/LcCx0ubJh72us2BGQO5b3q+BH1Mdh9I+CBuI/KYCrScW3Gz8OrHLBiGgBnEqCUMLetfVC7FRhtdqKN9hPMMS8RCx8spI18JYND0oaIdApM74LaWda5dlYV4YHUncabWVK4E4je8LuIF7djv/vgGbuUSTsJ7QK+YGzrzJ3AZd43oUaPmoOVC+zZkRNW7zp3LH6m3mNAFb/s16+hmqAGDsQWqPQVb0u5VvuF++/uBoZkhFA/j6Q9e7Qe/4veEpzFGMsfjhwCW7inYWXo3/hta2MrelQW5M1ZRZlGzWbR8+o+Cq1ptNPNqql8dDlz01Tti1kjpX8IBvOx4onVet6I4FNEpnjMEjzQf/l3Ln2LT/3JZRZewYV62i0WXkpwy/g29D8jhGXg7HpzBPqQRIolfss2J2IKcQTuhtZuoQBWlSVXgHHOujimgtH83XIOEqKN3cfVkEhpnZZSVAo04E5WnT1FbtrC2EvnPkHLF9/bmu3Iw6utMjvEcrgXMhqw5c3WDro/1ldQ5XdopZwaaZVra1e+stWdXT3sY369yE9yMkN1zF3ShB+e8E0COOzqCIU6RpaMzqcFkYFWpAQLrNcpsieaGbsc9lfrm8bqAPJt7YET0/vJJIeRwMfez2zaxmGVATR4dczKBNJxBN4C8PYKN2b6JI8VWpzkzM+ujdEd5WE+Y1n1V1fKAldv5uV8bYhZd9E/zuv/s7PlcQbzxl/kJxot+Rgj7yG8K2702AFNahX4SLHTOXx33uAV2znI0PP5pBpm+bX3/j/Gha11cN3I3nk/B6WfB5ut2ujQsKd/UhGkcfSrqQpT2VAVH+QHZCYP5oiE9tq0IFaAPtCY7Hdc7ZjYPY+2342mgAtxclTd6agY/4P14bdIy55o1LwtTWti44BFK1uyBw5tUe4Sm4AMSTFER1iG/mbPvH0aVOLZzhPpqHlQ5a9AZj0BVNlKRygnTLHl1dNe2so51QwPCNLQy8aTg7unqp+XOazQeNmUgemkSxSyLhTI1VoK/wO+2Eh6M8LWlaWgC9FFqnI5hgqIOHDcB3hIf3Zwa2hmxvR6ePSBrZtbiRLR5pRi+clL9Rl50/lmQYB5z+Sjv7T96Ioh6Sls6NuWIt1mRy/U366Mvu8LR/airQ5etrd/djqGDDea1N/C60AufLfp59CPx6+yb2g+XUh9j867Jj2JyY24G+3fCOqQPm5s/NZJmiQnhQuPDGusLTZ6yQL96KIlM6uTg/ulrHlfvHdh618ysgm6Ct8HbTm0n1wZjRuk14zt/QfwYul8TGejOq8/C/AwMo1MCNDUwJixaOz8yeKiZukK112xMX53kOCNVNu1ZFgefF47DylX+27lboiqTOhOVz3XmfTD7qPy86qcs1u/2dGcV8Dbu4RSFKmycG0yDToU3xXAKotiDnRpwinLF70duotyX2PhXvqJRW8UMqJgwF1ANWTKe2jPqVwsccZXiWg3kwsv4nv/WB7Pr4OrjSumfeOYQy2KaFll80SKLMDsZztPzeYXuyeQ7PgMRWTcP1NCA3feiQtxbseCQ/gZKXg01/tIALT1KBZNyFuuQqUo6j87YqYKtxDoPlTxlme3OU0MQUQq5ECnBzGQ4N4kDLRCXUX6UUsxQLXzK0/g6lS/6JwGowDrdvvXNMMsL26WtTqLmmRiEJEBKMlBRp1mGp95E0W3G8vaFe0fwL6LHhnRc7vmr6meG5rYeuIzG6ZDfA5VvteIOHS89iSo2TMYgiRuPZ2JTN8z1Aoao5Mtth3J7Z6cfNanLUpvPhi1BSlsh8b6XbqNSmMs1fhvVMcLI/QUrn2WByiQl5KI2KOAWXCqzxUgkIZsQ20TgFJe7nVhL3J08ShkGWWHC0qqrRbTnxDELU0xPxNN/97GK8hwM01paiObIjpTveeZhsg0/fh/2A9xbgL9Fa1iXRnkdSWa/3cZI9U7gTvcO+5UBsLmMcf6xnyk0M6rAtERX5myz2g+xBNHhxY3TOjCXCadvwXKIv5VujOVAm/EE+UxMOwTqBjGr4CVA2FNb424i+cL7iuQx3tHw3GjNLJBUXSW7wnOFM/tzfpAnpIAk82bznSgWAX0771mA5XyTCSDR0VBdToA58mxX60ly2HS2NTiVgGgt7dTECWVNfbD01Ony2Ka4sbshco69GOlgWyQO1INfM/qjTuDdu8Nh8mqjG4hyn8YyKXIs+1Dy1udtyVl291UUt9R/blANZJFSEK2wEXqa+0grM9HQyCBeIqeu5oW1qElYewOaTnIcOWS5BoHjhm70OD1VEpZRUROqZ0XqNSEQ339++TfD/yfz1BZAxRanZhi46neXmf8T9xe05PPmw8OHfBiGKFJCBi6ia7vLwBR/WFxk/j8NX2gOEVyDFqQQtiWaoYerOlpNpL1uwJSrRGeIz5KvvpyzKWcn9vTEg6e4paQzP4hsSKuWp+6jBzSSUoi26/JrRNDif9rx8Yutolpc8QMLczKLpq2rtc+GXrXV2ayycqfHfLKavIl0R6UeivF6zH88XMV88OBmOmtgbTHJ1QgFlJ0y+8NNO/l0lKqVYbpCODN78Q8bkgxI55bt3OeHAB1sa1as6zkGeOByyrLXf8M7M5hwu3TJtP2bQnv/a09CZBFWchAuEoNzAYt9q/i7aNXFtrSxa/NA6yHsNqQO+0cIZIe+4CTRP1ky7WgyfC+m78DUQRHrjXVVybGvw4BBcxI3ND0ziJenT4+ISMyf7zmi89ZLTjWILzrpYDC7zi8wWlv5S96tqnNg62Y74GP0X0KL/OASogsS04eAjxJyzJKs3uKLy59JE1e9V59d4I/Aha9nsRmzoPg+dOMqUTS8v6MUjRkaaD7cC9xmvKwUFgIjhFifcOt4l1ARBiL5gVLqSNXYzkQm1gVf47q72MLL00Tj++WqAcQ3gE1aF6lgPYiRikDL4O0SoulS6PYqYHKukvaxSzlUf4QTzY1qoWWTwyLGJhAc4G13SSJ1UdUkloBcaiOrVYs6HxWu7sSZudM2qJj+iduWz1LxmOlaGEFsYrcxp9dIh61HW5KX5kzQ8eSVyOLMM1zAHfZYdSwfw2uIC5vJqyxBejzCtMKUOQinll0WS07fCWP6wWToMfE92flyk6sGBD8sxe4ChzpCmZLCqVLdeS9FWT3VxbBqw+SeRIhRFox9KJws2ncgHBICY3wmXNICfKPDhEzFMUF6joKdimZtY+ssUsef+TPmbj058Glvz0TGTTJVvM1PZL9cAn+V//qN/6C1iD1zmpgADzoXBZ4ZOz950l+QvMM7vwaPGEJoUHJrSC3HwpglrmK/roq2hEJ0NvBsT0fEvO8TH2m0T2wMVpbk+/Li88Ern9rXi2LDz+TLQB1W2PfO0NlCtYZ6jcvki5Y7UTK8GrS5LULZelnXYhEVz7zQhWKnUGrP5ADITR+ZlzFfBheWQwVYdjJ6E0h/c7uQLH4rckMQS39G9Obj4Hswa4HWKZCyGAMrVGNa/7QNXN3oauzPB+WgwKpUVqV+Pfqeza3MGx7gT+dt00y7KB8LmtOQh4JGiptZe+Zm4W0xOyUbd3lBRrVrGThdOFnXzkDr00tXEGfit47ccuiTzldszOMEYXnr3ceb3ytcn3G5IIyEaZIo5blRFIMrVvQUi/xsk3AcbBFb2Cf16yWIhP5RizS7IielhYRmIGxh56kqqsVJU/kX3wdhTtc/pcXyfWZ+3ZsxtQA7Ov9R34ji+xbto5aXjNPhjmK8eBaV15yiNAVAlRlrKKtacUCyyFWXGYUAxocAenB2Y0zIefau0JBivZ42vJ0w5+twLWOy1nr1/rTDRvmH5DlivywKkcprTcqAGRfWT6AVCWNnIGJHYsMyJRXfV2aK4cfVXwD1Sd9uv0XIzN45hYhnvQg2cLJzIpkxbmv7Bghx5/jXPqqiUB5U/3WE6u7Q27ZElF6C/cohPg8Cs5fC6F3je83Opt6ZGHL090bJHvq4eZTtGthIhyWiYog06cSY1qmX/co+pb2+qGdAzJ8nn38HxG6MnBq72x5Zf2QRRh2xiypcP9lzqGPJIZbJydjGSmzx3PCRL+hXyVspIaLTYGi+y+fde1YIX5e1WJb8zLLJ6CETspZJLhC6Jyo2cK58nxGK4DYoQvyaIRW/QclwZwagHli9ufVGWm/ZPonkaJPKKEhDXta74MPzkcgOTTQ2q69bnMWMsGHbUzo=
*/