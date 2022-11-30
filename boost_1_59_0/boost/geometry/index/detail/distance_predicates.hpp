// Boost.Geometry Index
//
// Spatial index distance predicates, calculators and checkers
// used in nearest query - specialized for envelopes
//
// Copyright (c) 2011-2015 Adam Wulkiewicz, Lodz, Poland.
//
// This file was modified by Oracle on 2019-2021.
// Modifications copyright (c) 2019-2021 Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle
//
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_INDEX_DETAIL_DISTANCE_PREDICATES_HPP
#define BOOST_GEOMETRY_INDEX_DETAIL_DISTANCE_PREDICATES_HPP

#include <boost/geometry/core/static_assert.hpp>

#include <boost/geometry/index/detail/algorithms/comparable_distance_near.hpp>
#include <boost/geometry/index/detail/algorithms/comparable_distance_far.hpp>
#include <boost/geometry/index/detail/algorithms/comparable_distance_centroid.hpp>
#include <boost/geometry/index/detail/algorithms/path_intersection.hpp>
#include <boost/geometry/index/detail/predicates.hpp>
#include <boost/geometry/index/detail/tags.hpp>

namespace boost { namespace geometry { namespace index { namespace detail {

// ------------------------------------------------------------------ //
// relations
// ------------------------------------------------------------------ //

template <typename T>
struct to_nearest
{
    to_nearest(T const& v) : value(v) {}
    T value;
};

template <typename T>
struct to_centroid
{
    to_centroid(T const& v) : value(v) {}
    T value;
};

template <typename T>
struct to_furthest
{
    to_furthest(T const& v) : value(v) {}
    T value;
};

// tags

struct to_nearest_tag {};
struct to_centroid_tag {};
struct to_furthest_tag {};

// ------------------------------------------------------------------ //
// relation traits and access
// ------------------------------------------------------------------ //

template <typename T>
struct relation
{
    typedef T value_type;
    typedef to_nearest_tag tag;
    static inline T const& value(T const& v) { return v; }
    static inline T & value(T & v) { return v; }
};

template <typename T>
struct relation< to_nearest<T> >
{
    typedef T value_type;
    typedef to_nearest_tag tag;
    static inline T const& value(to_nearest<T> const& r) { return r.value; }
    static inline T & value(to_nearest<T> & r) { return r.value; }
};

template <typename T>
struct relation< to_centroid<T> >
{
    typedef T value_type;
    typedef to_centroid_tag tag;
    static inline T const& value(to_centroid<T> const& r) { return r.value; }
    static inline T & value(to_centroid<T> & r) { return r.value; }
};

template <typename T>
struct relation< to_furthest<T> >
{
    typedef T value_type;
    typedef to_furthest_tag tag;
    static inline T const& value(to_furthest<T> const& r) { return r.value; }
    static inline T & value(to_furthest<T> & r) { return r.value; }
};

// ------------------------------------------------------------------ //

template
<
    typename G1, typename G2, typename Strategy
>
struct comparable_distance_call
{
    typedef typename geometry::comparable_distance_result
        <
            G1, G2, Strategy
        >::type result_type;

    static inline result_type apply(G1 const& g1, G2 const& g2, Strategy const& s)
    {
        return geometry::comparable_distance(g1, g2, s);
    }
};

template
<
    typename G1, typename G2
>
struct comparable_distance_call<G1, G2, default_strategy>
{
    typedef typename geometry::default_comparable_distance_result
        <
            G1, G2
        >::type result_type;

    static inline result_type apply(G1 const& g1, G2 const& g2, default_strategy const&)
    {
        return geometry::comparable_distance(g1, g2);
    }
};

// ------------------------------------------------------------------ //
// calculate_distance
// ------------------------------------------------------------------ //

template <typename Predicate, typename Indexable, typename Strategy, typename Tag>
struct calculate_distance
{
    BOOST_GEOMETRY_STATIC_ASSERT_FALSE(
        "Invalid Predicate or Tag.",
        Predicate, Indexable, Strategy, Tag);
};

// this handles nearest() with default Point parameter, to_nearest() and bounds
template <typename PointRelation, typename Indexable, typename Strategy, typename Tag>
struct calculate_distance< predicates::nearest<PointRelation>, Indexable, Strategy, Tag>
{
    typedef detail::relation<PointRelation> relation;
    typedef comparable_distance_call
        <
            typename relation::value_type,
            Indexable,
            Strategy
        > call_type;
    typedef typename call_type::result_type result_type;

    static inline bool apply(predicates::nearest<PointRelation> const& p, Indexable const& i,
                             Strategy const& s, result_type & result)
    {
        result = call_type::apply(relation::value(p.point_or_relation), i, s);
        return true;
    }
};

template <typename Point, typename Indexable, typename Strategy>
struct calculate_distance< predicates::nearest< to_centroid<Point> >, Indexable, Strategy, value_tag>
{
    typedef Point point_type;
    typedef typename geometry::default_comparable_distance_result
        <
            point_type, Indexable
        >::type result_type;

    static inline bool apply(predicates::nearest< to_centroid<Point> > const& p, Indexable const& i,
                             Strategy const& , result_type & result)
    {
        result = index::detail::comparable_distance_centroid(p.point_or_relation.value, i);
        return true;
    }
};

template <typename Point, typename Indexable, typename Strategy>
struct calculate_distance< predicates::nearest< to_furthest<Point> >, Indexable, Strategy, value_tag>
{
    typedef Point point_type;
    typedef typename geometry::default_comparable_distance_result
        <
            point_type, Indexable
        >::type result_type;

    static inline bool apply(predicates::nearest< to_furthest<Point> > const& p, Indexable const& i,
                             Strategy const& , result_type & result)
    {
        result = index::detail::comparable_distance_far(p.point_or_relation.value, i);
        return true;
    }
};

template <typename SegmentOrLinestring, typename Indexable, typename Strategy, typename Tag>
struct calculate_distance< predicates::path<SegmentOrLinestring>, Indexable, Strategy, Tag>
{
    typedef typename index::detail::default_path_intersection_distance_type<
        Indexable, SegmentOrLinestring
    >::type result_type;

    static inline bool apply(predicates::path<SegmentOrLinestring> const& p, Indexable const& i,
                             Strategy const& , result_type & result)
    {
        return index::detail::path_intersection(i, p.geometry, result);
    }
};

}}}} // namespace boost::geometry::index::detail

#endif // BOOST_GEOMETRY_INDEX_RTREE_DISTANCE_PREDICATES_HPP

/* distance_predicates.hpp
QAuRBYeIy/L6xx0i6QZEXBSO49+0Y8VZ0fSIA47aSgRM2bIkbCHMh+1Vo1BM+vJ5eXnQ+EWnmQsgzuWloYRJQ1u8NGQ09nt2lzzgBEqWsyZKGBWJd8Ig3WVcNNriOZ9P38jbTvewCrHD24Fp7k1hStumAYpF0R2yr3sVt1TPU86ZZ8KBy9k1CjEpJJfoYrhaRTrnBCX/TFeew6xp3DgSxbEM9FtKFocNPOBG5H9uA+r/FkBQzVALqVvgvbT5JU27pSA3JtPjAMu2G+SH28lgISxqxyoE0YxibxFwiL13GCY9INm4ouGyQqqcV4QIl0fm6nq0/FHG1w13NRcgDKRpxv7Xgt3g7h+FnaemONJ1o7lciBsSFXoDQfgP0PYgZJ3vai+cxIB98KN80W1C7lxw/09U5dOGCbJGBnLlSw5r+R6bjRJg75BpEQVpkx7sezhhuXvQZ4ab94lPdm5ZlNA1O71lo7Daoe8QdIVVDpUjJpwYvpkfRccRRVmjJz3pMpON1g/6/SeLWL6p7E132edCx9StPLlegtFHw9kPIFPFDz1lmoymGUBbFlrNzs7ExxrPBowbmP8dD/vEj9LOG484AIirZqz+qyB06dMb2p1PF50KvPlPaqZm9M5RnsuP4p1b12/m2EIGvk7QP/X+C/oI0tRo8LgdxOiZ7g/WeP3uZUeCqG44hJYDBATDy6raI5eu9sSH5bJTDdt+VYtypXvl84wP8m0jyav8zhf04o3A+hAkuPm60yS06MwjbRYL0OzeKZXQcKrhF+KqlFLu9FfThR06VSroyQc2KHy9hcNeSCz5E5FZWIs30LotpCKohR5BlEB4sWJsLAw2DblNx9wNFN867ocnD/RPhy0rsoobFGlJwWST7ntpP54vHY2jfVD/2WvXikZE6AaNXRUVWBP+ymQ43kP3V6/3VpZeFZG7oRfzMnp896bV0VC/sUly+utdQ0Cy51/P8+aj2egNu/1ddmPfx5noQD9OTQekXQD0QBRmSntzMOaHbLwlaYCwDDy7pAOb1zKMallG/eu7+EIwIjizpIPzXUvM1QgiKYd+ek4lY/p+h/lCkxIOyN1GHcd8/rE5EKJs3GZffcPZUeYV9qBSDS7WFU4vVHErLDfXWqUcKM5DkmLND5bFcobCmUgZ0n2PUnBaaJ7Bf0cgyE4h4JHUGTfjHBJ4mY5+W5NJLKd4TWs4TdaoarEU2qwvKR07oDjh4z1zARU7i1jumzw2l8NqXDKlYQ+fBHP/LNVi0EubrUHRHO0yQQUqdoE2nEKasyM117ZOGxne+Dsz9zTEqf2hh5a0kpYpQUaljz5OcFY2fULEfpxZUQy7DfTC/cFefXa2B7soI8vHMjbP1mXPlBazpbp9mDnJbVsjqKWYZVBYqalpyn/uTXPDH2Z5giM1OHEQpUhWJwnUr67gvDtdoUCkBYq+jisynVoxo/aSG+fZviPIFmYb6vXhYvFzZfJufQuT14quufu1TxQlrPE/zcqHZtllIYVhISy4ZnWiOoYyGrflPVS0lrFw85BOczL5qHy36IOBSerXIfhQzk2c7E6w6eBxori2q/KWppKKRUiXKJr+NW0VLjKHPzUXaZeuYr2ZyF3UzJu+GRnc/HlJKE7FX6dwRtroRkLJg9mugKahJ9v1HA7yFNPArx6aY7wdvlhPShxZQLqudJhphww+7Z93PboqyVt41S1lak34x47VBRbgABu6rOKzfc4DSiomz8D9mqjO6T1SGCUOFddPQ/cFUmV4taVOmSe72f5HSfgM4Z4ZZ6tC1YL8rcIFRsXPOYmWEMiSoUW7se7pq81wNmsFJYG7iwN1yRnK/6zNJDOWaoxKFpucXtvhEMQwUyObavDv4ro32NAR+8jmDosKhMrJFxrmCwvXo9/sISf9tKr24soR70j0D46Tc28XtWMmpRyxUA+u5FF81jHyqg6yBY9uw8E3U6fm8ZGjV8SIHVat6fpFvUAnzQ5/4wVv7fAzG2LkAk5HQjCEbST4XkU7sZF4+QIS1xdNy3FywbZz3STs4uZMI6NtumBZO3AI3qkhqI9DkqPCINK38lSKldRsClOp3fsCFMds6aascYE5SD2kDqPn+qZCrSO7REQwYRhWyjm1qCieFMyRQ87jDwAXNDxUFqcOiv0AndzaqrByj12PZJdWlta7OgMfx1gwdUtFx77l7flB2EYZLtMbo+zFBg3maeCRg7HCyvl68TVStxm2KPit40khPUKFm3a7Vklgg7ETkTVxMuzeqjBziFamhrc6jvEU7vgFXiovn8Kc1fAEtYYbJkWPtXDZyHhb0UgN4/gCM8KibLMUlaxmuI2HcvYWwYn0zqN6pkEwczvzxQiOBHJFFBrXHEc7QITccsfpjHe132Zg/xb0PK4Vjw1FmHLmo9HXVkUbz6ULTpNK9YmOo2C9CeL6gPeh2pFBAKGp8+6FVgkm8wCHWepJ2bmY7hKuSdkqi4SnJEhKjW1cYLFNGqtqq7sn8fiJNiHhJENzZrY+conOWMQB+dBEPxfXuo1Zpe7ueVgs1bl4ovrH4pEgcjFnCazvI9hDG6CKFj+4SAuYtdOrR+frTiPTcI+5qZuYmb7YrWj+hi30/I/tutuXbiPTpM/C9FBmJXZoDL6ZqrI8yxM+E3FfJqrD++5UJXIkO/DnwgVz9APRiUIMQTiRsvPIwFPB/IYPl8T4l9kCtZAy4+RlC0Gg4eypbWoVhNXHj8uuW5N+qKqfnucHgCSp3ruKbwpfVfPJV77Kzkc7JtHNVWVzhhqgiAePZFVQlAVxtIEEi4YYDRI4Flbxvrxj6GW6i339fVG75feV7O4Jwp5Jy8sIWmvNfQ5WuSXtEyg4W0xMjCZo9gRqd7cPvzRE2uW57RfJt5LWyQ/XdtpHz9UuxzLi0EV2xzdfibaFp2cU99IDGxrWOmMWz/y78qFoHzFpz9r6CuEebzCDOCxuMaxXmtiqGAIR7ocQvxsSSmhoKr8jSBxJkD2inx1p0OqBN47JhhautCxzKoLuSmtaRxfVjvft96vdeoV5a7cOCzvScRviJ4Vt1emm/bTH5j1d03rDfFTVP6MKTA2bgWX2Tz5Tbn8R2gLUbnWdT+od+c+cEHb35IxLwA1z3NxMSJlrNgechjqa76A/TqNvWZY4m93geFsbwXjOxt40Aw9dOi1LILokNbwozICiukh8wy93XbZ0w1DdDRXeA3UdtgpVnvDU6v/YF4TCZSK5GNdLKwN67itTLBwkvdk7IV8xZXUdSrF8DYPmj+WZojJIdQjlPG6iye/ddSXc8cBQXvVBeWE3hcyeePd1eiRpfXBfnrcs6BbfEWdkGBQHA4vBT3OP1DpZG0VKCnaw87hmMU3Ja0LSpb/OmHcph2Npw2V+JhXIcE63mrsqbQVdu5684bj/gZ0jjjl5YWxvLzL2d8wNnz/epKnHt8CfaGCZVzPQFHGQn+TPeXM7S1zT2AFad3rYsM4IHPts1FMv93zIx06YKSCYWBoqpGyURtlYL4aLf2S8H990+HJ7LG6Wir3Af2VLYTB+RqnysYgg4eIqnvYaSEmkiSfHaA/JZlvQqTeuKgI4ioMbtmEmqg4zk5QHi2RrmZvOw0xBDyezCFzaj4kYrWedKTkYP5foMgNoR7KO9zc6GVg7kEhj6WOqXcbsDn/6s548lMJvF1SxzIpnmGy5GpK6MZTWSbCwOjc1SipohD56t9nE/aunB8qJ+MQ4dOpCR5aRsQiT+UpVdb53DnJKMN8kNldXheZMe0SyIHP7SAlZcjcsuZJllZPD5rQK3nQITaaSWhcHaEqicHK2SBdOM9Z1CHhl5+S7H1bXDFPW+4wRGevWtMNaHswxRGYoPN1PJNi/qt0Z3BayE5GYVljQMWNvnp9ij44oqnDg5idy02MVbS/qyoD/rihFhDykFIm2qiDoDFsMKTugKMAocKQsyct1SejKvlsDqwlVUz/S7Lnxpoo3oDObaBmbd4Y49iIgKkkeGvTP6FbBlJ84WZHNBBqhY6uBN3vP53cKpnVk3ozCDsYV0gCUqhFOkyi/0VS86Vbx2NGGNU3jJnLpyolY/LcBFf4nAq24inw8rx+blLKdRVtYt1dtAfs72NoVrrS4R1LoJUlOdqHcZnrVrzHdOXs8HDmIVDG07FJN0jiBkE0QlyCaN3Oo4sWBOmjEIkw2ut7O0yKGO0WgTXS+c2zRu/1A6bBR0bmaW6p6aLYYiUGFaNA8ROP55EO9UbPN0gPuL9yQLlyTvUWiMc9ie8Ckgi1FCBeZk3ub+fzkYtLBC/P7EOxG5zxjq64QrRprDlGcFid2hmF8ksAptZRoWAllivkLsywBMgRk35ORtricJPfIEfx6kyx5DWF2ZoTFRSFLveprBgO9H0zfMth3eGZL7Ja8H5KnNi3r1FWs+nRV/bwydhB5YjCCm4Q85Xo8z7yI8rghOI7Efap8uko+C1jXIjLoPVZ8RQrAxmwxSvlBFikl9cs+A3FwMjNSci3+I62e25ggw6p/NdKXy2pIk4MXkFGaO4HyOG9zgBWS6zNonCTx/CgyKgRSubwyDPGqbcN5Cr4S3Oh5zfOWwHAXZAWzVJdORbiJc1PNOoj8q4HDJMSp2xVsW5i8wWUWO/gDwqLJrHLnIX4uCiNjwxvHXJltcYk9HIsbzbL8baLh6CKjsCbm2H4M+mccozmhtsoFmOUz0ZAD4LE2h3ipyfK5tiwE5SW5yAxLSeEIP4QUbfgyf0dyHLWwu4mtTZKpNR5KOZL9UF0p7mITTPtx9klL3NiE+mmqFWmdQNPRON2QRcAUNIKCBJk9zBrgsjyCjnChaKJ1kNFVrgRx3ZHvIvFtODm0synje7Ub6GAinIiDuMBsI2+XVZZfRk/xcAbpMg+6fWCZAKw0CTbrfiZAeQJ8tq7b1ExW+u2fDRiXQBjpy8f+vPJd8o/wsvAVzLRQm/IOz+R3/+82038+s+Vqhgxa4paCl6ncOt4cs8JCK2esNeC74BZ9tavos/VrIEiG6NW0KCmxsAhNE+uiFCBoJ7fi0/5K2pBIbf0q/MqWTyyWoaosuB5IeVWLDGfT7xkmRD4M+iHJR9OhlH+xy76O6zD7u/J5TjHB1Adf6goM6x2k9xlQ2PUWnRM5QmjMV/boWNxUX7YnDBxUx4dhKhNThDrkAtKaoRo0uI6O2CoHz9sG8FmpM9haOa9JKB0qvakmS2Y8s6uE6qvQfO/CVt/I78z44ti0AApYy64A7jbOU98a2mU8lg5Y8JADGCAL6zXVCGcsLzEqX9+Z+XeVqmqxuPBkX1bzbTN7q086sEM4F7fos47lTjAPISbkXtzNt801Q2TZsW19iVNOupfVPzAQf/7mKWt3adtYrrurvr6tXrX5TP70pw3xRDeB36POhcO75f+zw11kGrnL7Thj72zBY3wYM2AVv9nsxSexd22I8G756f1y3z912/5y40/7Wl+NUXr9Jr7VPcRfvfc4/dyWfzv14lFddXfBMyHto8XHxZDsTcDoKyrgK10L5E43hrvgt3MpggCJQLRAR5KtegUu887i3vh4zO898cG+djm46RH7btvr8Ttk/qxt+4h7QY1pQWVQ34MV9uOEnLA3beWvvIQWLj4PnXFGkGmy1u4OrGPLpuxh/+StmPbn9mwUJl/pFuP0a1L2Y51u0PxZ3w7nEia6Rewah3cDrRo6dtzqacCpIWZq9m/Il1IhRime4iSfxIjLyN2RIVpTfE5vKlZrns4PvcIamIzvIJExJQCyyVNOakQml6LWTy8nz8IS5hLFnOkSReA7Gz3U8dIVihf9k9w2ce47xh/AWKxzokezIkqKDbEO5xMVAL3k9WGWdeEE2uWoOFk8n6ZU1jhWGt7HR2vt2pQPtbNILyHaTdcEUob2/riSwDwfDZnzYVeZLmKoDeLmbkaLlarP1YfZkb8msN+25mKssK3hGOzc8dz57/0+15GjwV36aJJMkp+MtkHwc+ZzNlGnsr68XU1xyHYiB5GWMMus2xWMmVSlog7CCbqAVvIoTo+c9mCQMwT5jQJj64Js5iSR1mFGkXGLAvdqgdXyo+eacJngwBl26QhWlm7gqCsI1bFQlcITZ7EOJet+1jMbZBIO/iLs43x5Ve2y1FkxH6Ny/eNc5itdd2iOqoF789+bDsphkLoDcpZgEbwU3KVG1LWiILMTd7t5nLmviMqT4SbZ1mblX70FHSejZufj3Yc9o38wo6O8Lt4z9Xou3Qj/hs4HtFY5ROCJdJaWjEtad+gJVynKiXyyKbUxVCvVCNK136z4ZOs5lxC5Q7GyQPrD/khDJzyWVk43k1GaqHxj3CLoU2tcesMSuF25I4VB2BAFnTjKwFzkamIIRIJczNLeEfPTsrCjZ5wVQlZ0H17UNPVrLIy1LNxe3MKHga9sHNGknGgf+MC16veF8txMYmsa659wmpoQxECkEc6x+8DR86htUv8V+Q6u8PlJQpFdgFHsIRWQ6tRWiA6idxxWN6RkBF1pdq+//uK8soAW4c18K0zTpo1HtZYLhEkjpk6J6ArbKUuajuySRaHMgwj28RFIL8txLElUZKZWrYILNztC6ZNpSpf9FjMU6Ip1GKDPekc33BzOOjUQLLKrXKDpppeXmWLvus7f6reiFgT3SD7FMyl1roZ8y2fudgxnMGurUWe1x4B0o4E+rfBNpLR7zVCpsP9bdFtXmsqOEO+4OQ0ygVnN6TxUGtr5d61+ILgbCJqzeQWnzx0nf5SxrRalYbg8nL4rzWANBH4ZNkKLKX3Rpl01M9hgtK6BFipU+t/I4DO6Fx9NyWx+OxiuvoAkCXNjeOClw9U/NbcICyL6onPkFSuKilLzkU0AACz/0+C17D8wni2mt5PZgkrlYBCc4c0QEhY3VplgZxNgJjX5FbynHe0J1DDPZ/3qDhuD12oLV82wkhM2gRtcf232iBsw96SmCXIFqQnkNXn+aq+CyfKO21f3mBQ9FgpeLW5PhKRRmpNplqb4/DMlz4nw1aoJatm/EdKZdoejGz6C5g9bD4hblgoSfoNaNph53xzysT7RNnVHeWrk6HCuDg7g1SHCLrMr6ohNEpOngmqc56VbHr5zlbE1pyIlw4g5vdh3rzTS3sNzdJpMP8gQ3X1IjUn9+43YiByUeeOaybMMndJUPNFilOVENPmejvl2Xr7kW0JXTKu7j39NXRe6AQ9d4cqW4QtC5IjsfVGwstCSsceO/EcMS703GFLJyN8vk6wuc1i1i1pl1IE7WcYr5X78TT/RLakOTW48nIx9vPwTpVp/UZEk3E49uOsRSEkBfatDXkLEsvVuBzisuUGEzT0qRs3prQvTXFUmqAkmmDKFNIvtFd2rag+Dtjrs23bLCJz4CArVLbqmW5ag1ONbxYdCABlE8+RANARTnHXVUdWYNiI4jmQAKSlGtTpKOjSyFArIY7G9us35TKIfsjFtlKVlCI5dQ8z2I1LP49lJ9c4IGiqKxKs8s3SWifT8pgKQULtR6n5N9ObqdXpnnS78GQl0veJ9/U3H+g1IpS9OygQng/HK7RDHCxv0ALdbSEwNRZYpQjXewFhtUWUQmWIjBjcVWpTSU07Jf2xW0CDlnVaSts67PjTqu/rVeQ4NG7peLhCdhonFDcJA3mRs4sax2v0NvV8yqSBH/VTu
*/