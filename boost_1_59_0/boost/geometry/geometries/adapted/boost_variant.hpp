// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// This file was modified by Oracle on 2018-2021.
// Modifications copyright (c) 2018-2021, Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_GEOMETRIES_ADAPTED_BOOST_VARIANT_HPP
#define BOOST_GEOMETRY_GEOMETRIES_ADAPTED_BOOST_VARIANT_HPP


#include <boost/variant/apply_visitor.hpp>
#include <boost/variant/static_visitor.hpp>
#include <boost/variant/variant.hpp>
//#include <boost/variant/variant_fwd.hpp>

#include <boost/geometry/core/geometry_types.hpp>
#include <boost/geometry/core/point_type.hpp>
#include <boost/geometry/core/tag.hpp>
#include <boost/geometry/core/tags.hpp>
#include <boost/geometry/core/visit.hpp>
#include <boost/geometry/util/sequence.hpp>


namespace boost { namespace geometry
{

namespace detail
{

template <typename Seq, typename ResultSeq = util::type_sequence<>>
struct boost_variant_types;

template <typename T, typename ...Ts, typename ...Rs>
struct boost_variant_types<util::type_sequence<T, Ts...>, util::type_sequence<Rs...>>
{
    using type = typename boost_variant_types<util::type_sequence<Ts...>, util::type_sequence<Rs..., T>>::type;
};

template <typename ...Ts, typename ...Rs>
struct boost_variant_types<util::type_sequence<boost::detail::variant::void_, Ts...>, util::type_sequence<Rs...>>
{
    using type = util::type_sequence<Rs...>;
};

template <typename ...Rs>
struct boost_variant_types<util::type_sequence<>, util::type_sequence<Rs...>>
{
    using type = util::type_sequence<Rs...>;
};


} // namespace detail


// TODO: This is not used anywhere in the header files. Only in tests.
template <BOOST_VARIANT_ENUM_PARAMS(typename T)>
struct point_type<boost::variant<BOOST_VARIANT_ENUM_PARAMS(T)> >
    : point_type
        <
            typename util::pack_front
                <
                    BOOST_VARIANT_ENUM_PARAMS(T)
                >::type
        >
{};


namespace traits
{

template <BOOST_VARIANT_ENUM_PARAMS(typename T)>
struct tag<boost::variant<BOOST_VARIANT_ENUM_PARAMS(T)>>
{
    using type = dynamic_geometry_tag;
};

template <BOOST_VARIANT_ENUM_PARAMS(typename T)>
struct visit<boost::variant<BOOST_VARIANT_ENUM_PARAMS(T)>>
{
    template <typename Function>
    struct visitor
        : boost::static_visitor<>
    {
        visitor(Function function)
            : m_function(function)
        {}

        template <typename Geometry>
        void operator()(Geometry && geometry)
        {
            m_function(std::forward<Geometry>(geometry));
        }

        Function m_function;
    };

    template <typename Function, typename Variant>
    static void apply(Function function, Variant && variant)
    {
        visitor<Function> visitor(function);
        boost::apply_visitor(visitor, std::forward<Variant>(variant));
    }
};

template <BOOST_VARIANT_ENUM_PARAMS(typename T), BOOST_VARIANT_ENUM_PARAMS(typename U)>
struct visit<boost::variant<BOOST_VARIANT_ENUM_PARAMS(T)>, boost::variant<BOOST_VARIANT_ENUM_PARAMS(U)>>
{
    template <typename Function>
    struct visitor
        : boost::static_visitor<>
    {
        visitor(Function function)
            : m_function(function)
        {}

        template <typename Geometry1, typename Geometry2>
        void operator()(Geometry1 && geometry1, Geometry2 && geometry2)
        {
            m_function(std::forward<Geometry1>(geometry1),
                       std::forward<Geometry2>(geometry2));
        }

        Function m_function;
    };

    template <typename Function, typename Variant1, typename Variant2>
    static void apply(Function function, Variant1 && variant1, Variant2 && variant2)
    {
        visitor<Function> visitor(function);
        boost::apply_visitor(visitor,
                             std::forward<Variant1>(variant1),
                             std::forward<Variant2>(variant2));
    }
};


#ifdef BOOST_VARIANT_DO_NOT_USE_VARIADIC_TEMPLATES

template <BOOST_VARIANT_ENUM_PARAMS(typename T)>
struct geometry_types<boost::variant<BOOST_VARIANT_ENUM_PARAMS(T)>>
{
    using type = typename geometry::detail::boost_variant_types
        <
            util::type_sequence<BOOST_VARIANT_ENUM_PARAMS(T)>
        >::type;
};

#else // BOOST_VARIANT_DO_NOT_USE_VARIADIC_TEMPLATES

template <BOOST_VARIANT_ENUM_PARAMS(typename T)>
struct geometry_types<boost::variant<BOOST_VARIANT_ENUM_PARAMS(T)>>
{
    using type = util::type_sequence<BOOST_VARIANT_ENUM_PARAMS(T)>;
};

#endif // BOOST_VARIANT_DO_NOT_USE_VARIADIC_TEMPLATES

} // namespace traits


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_GEOMETRIES_ADAPTED_BOOST_VARIANT_HPP

/* boost_variant.hpp
VCvLyYJo46fSpz9yLaRVzx3A0HlIaRRFEpvNs3Po4GP1ww3m5erYdJLAU0wD5fwNGZsWIVGSTgtnMCPE00Rjx7dUk9VC5XJlje4/UzbsRFb1e9Qm2rq+MhFpnAaHEVV37I2QLpIaCZJ8fBBZr33GsOrv9xJ/UdOeC8JqPlDO9vd/XA0qT+yxRhlw84VCyyrJ4/AgBSXhRL0WEtLRvnoTUe2+aZKsAZl1KRKnyLW3PNwvJANVOCSVuMWLA1O3qYFItC5DuDnR1MFVZ1AujzPNjj7cVdVOMw9jYsUqc5zSjx3HMBxRo6AQoxL0SwSg1qv4Urdn99ID6GEVAkYqC2/aknta0DJdHzo5cES7ZURak4LIhP1JIK3zLaFyz5+sfD/TU8Q7B0NaDM/DIdkxDCx2VBNi5ijOxE2vqhQ1UFdz51tqj9jLYklCRJ5WxnrcUMP4c09xIidQgtDLC4uVvXvweefrNUEmmbYgqtDM23jh4XIGGmp9rEKbq5nZP9+1ltCuAWMuSB1Mnl6v8OrUMRZZeZAINRGQAqE7Q2uh42PdZDUpedRzipx8kFzSaC6hHzmqQAmhaTTrroP/SFeK7pjAk0Vz6j4/TX7Kbx2w6CZ5LPqfh3/T1Q0KLzi5kHX4ZFezhDwNuFL648FWHgcxEGrRwqEZJmoiAHkbeQ9Jv8zshjCDyzbNEXBcEALZjub9E600bxqHGPAyRul5ejLYMrrxAbvZu4No8+0sfKWMSDsN6DRHawTc4Guch0+z8sSdVE2Qc2KRtAN+WaeWR9jcviIlEPolzwGniWkmSGOnAp+/nX201dvp0rTgquZ16u8kOCCT9yWhXGK1FQaQCgBQs/qwsLjoN+D1VWKrN8HSIjvRYunCKXv1h1ymVvzahCbKtw3XY6VugG9bUb9Gr0yQDJRYKEQcAKm1S6QQSrCwQEvyOlN1PCqDQwy05EwjbdpGOpnRMoIAuefEiS+H2F4bD5FxM10st9jtwUp0W5hk+SOuqk0BFMbSmUZl9E3+g+qHpAcv11vpDdHRH1Fj2v1WR/tI7UIAbaiJKimJFpe7A6lDSf0ip1QUJIDjZHwg6AApZuKl0vklsQA2zNdOm8N3L326YWWv20t8G+fBF2iOC8Vx2sesUVVP42jjhhEZPqrvOrZHqquDro8zC0gm8MVVqTaKnMOidGmlMo0j4Fo6hQfowc6EBeBHC4kNd4yCEULrhMDahMIx4S0j2AjZd/WtkxiIxgSQg/pVgJgVSJCcrdk+Pseq3+v+AYDAlTTkM/gvARDZVCG/0D8efFTBWBvguhQC6b/Mx2DzNpAZxkkkxfTIRCRo9KD9oSCPRIfRiJ+lmvTSOpMBnHQnqwJh1YDT5UjGeRxkKysaGVyVAKXslCmqghKgZS4GOmDyypeZuLzb0+T502VLU4WLgIo6CWkonlC9fLCRiSgegK4MoSAshD7TYUUO0sVCUudLdc3gspMi0xapS7THNa2Vok2h37B76MQNie49pEp7UM/MkZcQ4ftH5R2Ads5PQCLIeFn25aOWOEdB19tehn/KR5PI7jF1MOWp8gC6MoaBEbAaDWGYBENPz+EmrxGGcyaod4Tl/RtrsAn3YmdH/AI+EgUvBD8LTm4H2rOK4v9gzuZZbTKU7gHiMfJX+5TEAY7ri/TG8vJHE+SPYcNNDNG9wbPeieqNfVDbUk/k/hvjwJAsWMF32qjACYGonHwQJTPPYb1dIC5NOkj99n+7csUUg2QeixvfeKPyWs9TZXZc2z8tkvQ7fTmfV7CemNpWCUsGLK17rs7jI+lY/FftMLbAQco9JP5Se0dsjhX+LkV22i1Q1D7+ch8C5pA/BSet0AS5QjqcVoFXV5s2utKQkLYofWOQ/DxdawAIRg+sQQpEr/B1O3uErzVf3ehtxYlsU/zjrYZ/zffV3oPyRWAf4avLcMHGGacLZauvpZ59a9ULW8SHBLJD/LZrvgl/FEtZyj+C+rWleYwB6eWTu/umr9uMl2nh6cneA6e92fsGsxPXYy8tyKcnvq4nfofDF8Pj5o2nDcrHHkcHq+L/+FN3PvU2y3K+KXn2KrH0OLu990kmVd75qdXbK5572vj1WnMrIlj6HTraaR/3JeHNCJByxUnyy+/Sbc/feQNlDooXPNXpLTlav3CXir5Kb+JZKs3lQpLXgFaoV4EEb98+IN393sVZ+0vljE/i3pGrPaxi8L23T+ipy0yVQ4PRiy/D/dx8FXAaKyQEGuQ9MGfbAVGoNrb0D1qRwY2sJ2BLKpvOZJ7xpWU0+Bst4OcSdvDkmbSAJo59Szywhsb1pc0qbjIzj8F+nPR5GI3AnY7H23vqd6sG7GvQefryc2Lff+4Tlf3tZ2PnfP+3IYdu74cvx4t167NFF0LBg/PDR75tnvEt685jZvqDq7n82buzJ/78G+N9zU8Xj+TC5urOn/wQo5goJ17qJ0cWY1JSorqp/p639+meq3bn2fZynF//ae3dZyPfiap748XWs1KmLgYy39Lu27hGv0wvoj/MubeopqQ89aDbyfb7Dtsiw8ttszbF3vAJOWaWNBF3oteurXJ19oz5Ijnu7l5wojUwbnZYXNtgMoDeufXx/OLWlH4EOH520mzWeG7FeEwm2F+oL2zRSi58GZ8iVbaCgHcuu3dZorsmV2STe9e6u2sj9tveFVJeAu6lVvwfoBtgLjuxPaZa9q587q48hDsCayY9iP05wW7jhdOABT3zY73GS/dsM5CoiP5peowrg0RxJnf7PStI6qZmJz7+N+Holci1F9+GE5TbFz79a6O3JmLlLju8cqW+OR1Ss35u7IdM7C1i8sfiLSYtoPp0Y0/P6jaeBKd5L6mik291j7iLm/6O2fV0L78KPlx1Rzdub6+f3WssU5+nzaF8PHf2btZVhAPP5qaSHt9NUpuP2RgNpU5zNrpcp39v8pEZu0lZ7LtfAw/Zo0539hVpd7XKYb5qVU6P3dDuhZKea9XmjKt5qowlvL3LhNnDwtS+3Ws+P4oqTeY6m3fwMWgyvJ1PiphMzNlw9FAMCmqb9BXzgafORWPyY2d7DhtHNV5oHa1at1x+yBgOKXWAdTH5dgXVXTArA0lz7VbgU6y495GR2zqSutGL8svuYZvLpB0reMogmTNbpz94FjBjH5VDsGYHPbx8ErMtglCDNJ9y+xQWLmsRqhcuOjdOehmaexXzsiqKj5m1M/c6bs8vjN5vd/tEi6YpguO1G/fIdbv+yKlvj7fS2rlT55AXJdsd+/n+2bMfx52Cv333DqdLaLqTc2OU85mjscuZ51TC3b6F9w0oJMMC4XLQruT37kmb9E/poZxxy2iqANpnTTcXEJCkylzlmR4Eom//ENdATTTNW/C8hQ5UCUsW3CkQYd1lZEOvWajZeXHRmgllsTbQf9fHLDWmnb1Lfn7bdOojCOfunitk9vYf3v5et3Z2fmTOHFc+bbAcoGscPNRduqrn976fPPqheD683dbLLiGnTxxdO//hBdTxs6zTsHrxQIw1IgZxPeTUNmmKb+WE4/mkj6o+oI8J9BQOCwsyu+p8ZbBwfz3m7uxfo98BXYHj/55DhRM8GJhJYB/JdEMG2kUINpEd1Hqr51RD3+NdQo6bZSnW7eRgb66CD/EcS/GyK8x1TTl8/EOgPsrxI38KiessR27edpYt3ALkhv/ZOoHlYqsNWJ+ffAqrdAC4ts26HF8u8Q8jySN3MgBO/Yc+7ZoIX9ohXg9sQI12DatztZtaAV8fd+VtYjuOKxBlncM7XqmLL2A30zcVrha4B8dXCGFcuzdzI/vh7KOLQ8vYN/QxWakO1HGO5VwUQU76bGStBpGTz+FGHJaCn0hvP3YxWXRJb5p1Gqe6RU0MsqGVyKukbOokKUPiaeWkpUHRNGahze47k2+TVJgPgUrFUfVRhh4f/u3satzikemTHJXdyvqJ9FD+7GTlcj0hDkqp3nTuys+SFDC5gFKAQVs5Md1huZzU3IqUEHduPlcf+7ayqI/7ZB493BXVwpVrAnVAvUFqmR+f7kqRF/1tAJDkGYkRt6tkMl+/tlA/TqNoIhFvsUqzb9pPUKD0fqcUvl2dAsis74LJrd1y3XI+fFINGxNaXudRrTUPwzYzbV2RwTbFZdtBG8HfW+qChS29to0V28yki2tAB93uDvqdOcOA5O/59UAA2igK3YJ2Qi9wmyofqMhtH/beDN+LBsJcmEZDlzOutERckcRSa3av+fxy4eqll2PM2z3VakE/OgfzmKtZuKHWUaKjUy7CVVoTpNW8sEYDJczdHLtyqgO9GB3bCI3Y0fE5TvoP7j9NmylK+lm4VsWuCwtUW5xpHiRipiSCCQQuL6wNCnIUFHGqWNluGhJHyA3OLFCJX2rT7UKW0877fsETqkWPbEwpqtSxw9stzrVZxxBPi6CHoHeKayLDZaKxSIk5M8kJUl1YJJ9FImM3sP9gq41WDzueu1kjkst1jd0yrdqrH8za0Mw/DoiIm6SOk7lsmEmy+zv1T7VUN46KlYWgR9Qkp7P8pNSm3va1GsLd6kdzN3E0un923bPBHuAGZ6vbAWtTxbtFjmKc0bO+c3+nHX9/r3spf9Vn2DqQvNaqdru9D01GEZy6m+aVTNbc8aMwbH77gEs6Wla4Ud7eY6PydYSz9gqWyRDMTBwoiQvRLFZcKR+z5aZgON3zUsyNie/x6UoU2mNAUtPtwJ3huAT0RIXNzc1P7iun79EqM/DCM3VC2Q3kSU/fvP6PsnOIFYYBku21bVvftW3btm3btm3btm3bto33T14y+0lOatGLTnrRSdWi0y4uqJAEEPTPDw8Vu93XFnbOva2FXEV3/noPkFUAlkHRUYGZ8tO/JO+eD5VHIzOnOxpaXgxgCdXar6+P9l3JhZxfBgqR6SACl9kqbchgpmcNfI6QL9LPLy/HbjGI6lGYGByud3pbWYlSXQIERu3hxDDu5+esTBmFMMODMMZ4G4ImscXkQ0OttXoMpoOla0D8QIYNpEbUIR7yAA+QkA47uXyLwI9g82JXGRFaI9iLWuNiLdLEsCeIUfyzYz6W/4A8dDZoQVOCD9z4qSRc2DSnro4v+5H/rcZHQK7mv3Xnow1GQ0wqi184addYmS5YGxLnDjTAg2rcJP4iFV6AqaivERSUY4fSD+TIsonbSO6QY9oofef0o0KKqg/AIVsnBScSSeDUu5hpYC6Wg/AEojJDwQIm+JIkP/tQpzQHyrDCFATssf1b9UQ6Vmuh1eKnC6gfkBL+1oEAE/Acf4nlWncn1rJ/Rp8T33qgcz7B3fPmA8+8tMhDVyMCPKOeAHi2jBZiwIBh6v2lP8Ag+ibt+9JFlztcAfxUI0eVFCsMQXyLGQhBcCOShFz3lKdOUtenRh6QuuXzkg6K+gOyD6kJa0eag2tHCqIIkgL7NRMCFyD9nSNDe7dTgR8aMOQ93zN1fVly9A4wVMGWxyTo0NiHWQOKVnJtKtQ0s6sDoBlXFrq2ZscY16urSk1NxdRC8CruFWTlQGFAAcTTbQgyz1qVsd1m/wXJ5SACAuLbGAm7NvsxfvxEHENbcag9epPzG1zw5NXdhefHTyfQ3nN2dXWtQvalPXtInLM+yYsI/VccLhAU7yvUzKsIgHvGZowM4k/cqXhCjBdmgGQNQ4JGD8IPqo4D0p1vNH6liC23NqiaDAmEAEr4VqkrK4b8L4QsdFhRoPpNBPSbr2C0fEC2VFkY8O/NYayqsJKUajQOAHqoira0mqiE4E8OM1RNV0ZWXTojLyQiIijtwU/110dIRUrhmm+mO/oP7dcmEYlF/psPQCf/DseT/X8+wF/zeHgrjaz++7oMky8oFBSoJlg5JrPY7CdNLLZAziwh+ddMENwM29xKgqAJOCDGh1COmgcRJ4lKFVlOQcm7gQKIGImdF1neLgDIl0YORRSn5lHendGxNb2dFd/4Pvb29d2SdjqrYTqbzeE0m8G0YDXlgJJJPQuk5a8iRUegwyKaPtP6Ua0r1qtnaOy6IT17aU/vYu9g4mIOsQ+2RyAMlT7j4kltWhYn1AxS9DtfTZmUKiHHgrGohJmToAJNBxqerS8BwX++qNSySX0/b4UI4xmjP02qcuIWUj1goXKSUC9RBTzczAliob9iTBx4xheezfTi34Q3DmG3X4wEh3QujQawYslICIwbj7hSHUx8VgjiT+9ESTxA6UeiCClqFiEsJaSAXASeLk2GE42WT8kPofiYAipFzCQAz6QPTxhIizwRYYew30gFMg5DD0M2BUGACRyIkgWibvaR3EipmX/oJfu6opLwbW5u6WKi8tE8uUHW19YPFizbI5Lv6q8CyeBUNLD4KN9OyYVRQ2/BpB+GOQ8bCoirCqY4etYVBnG+UP8CBVI/G2mzYeCBP7+N5QCFokyNJMjW7C8KpmwsmhCqyFdtUpAYKV8haMZISIgrKg7JTMugzSlvhMnu8RCAyENvx2QaLEmzoqKSQF9nrMlOK1oH6AOkKgQZeA0lLwRrPHUPLWJJcBB/Cyz+HiQgITWICqXmJGkRoyxaSEbsf+yrwbIzmsEaN3bhdlwE36/oMWMEzKvVu2H16tVdiqPv7u+qaMchX1fWn2MzBafOo8tW79JNtGTHoV41dvEA5ogjS06n9wtIHb4sGHTqObPRb/klk62OYSwczR4JEVD0aRPiq0RWH7NdBxCne2SPFseGve4WOhFIFeEF0e+NjRSPlYRQNVrNcMXItW20s9Edwyz1iqtOFjdfNXutnkW8dsvWwaObtjFR+RHnfXQO1LR0QMeokcPahH5LW63pPqKgKFXs3nVTBSUakEu0VBu0SiFErm5TCwk++w8+bY4CmGhZMAoCf74QyQanXd8Y9FJ8U1P32Jg4gsBeHyYeOFstR2CQwN3eOqGREavdHNMcqDl6nlAhhvQSpx7QvP4+3txon9vXQ4X0bRUA0mofLKMCsSKqBgX6wYeaF4XoewnKGkB9JHvRiI4dQtqvnzzPKHumGPhoJSChEN47qF6cHzldDAIAFUGP3TIbyerf/RePbZ7/rAXKH6R8VLCZ8sfkHZgX3/YnIc1DDMARRUTwAnR75j4tWS8CgfxfsGp1k6JdgaI9n7KdgFsEbQPvfZviX34l/+PDZ1lQpsPGV9gLxDgaMjnACBq92TYIE8Dp6LgW6yAjghOxLCNK9zJdg1r9lHzDfmchF1h8wFpYUH9OjteEi+ws6/6kq/oNnNlr3nje8URn4ImBFek27MyCPMI0pfN6dDl0f6NSzbinIVpSiwnX97f/fCyFrWmB4kCfP28sWHwiMIElECi9aNqI079mEG7fItVRRCwO92Ku7neQMoAMMTcSThZ1i0MQwB/15rl/AfHj2SXHWe5fVsX1kBigu40OVi32ggfBY8FKlyHZsXgzNQm3kdnxJZTeBxzygQoYcCy4/SQYmJYk78XzRfHzCWUVR9wyJhiVT0iV52MM6n2QKvJSnQBrqHWR1VOntPsAIGNInu7fQSpGcMVsGLCAeXpT+ZBCyPDdlr82b7QV+3yqEHbM5XwZ4yKoKEr+DyGloEUDleLJgJvg6Ax/AFIalgI4I3OayOgQ9/AwilMCp6LEK0vUA4mR//bj6BEgHgmFx/xtT4E6K+eVF+DJyPCsEggAWW2HmscRVZsNGqi5
*/