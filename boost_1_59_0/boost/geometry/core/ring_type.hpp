// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2015 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2015 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2015 Mateusz Loskot, London, UK.

// This file was modified by Oracle on 2015-2021.
// Modifications copyright (c) 2015-2021, Oracle and/or its affiliates.
// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#ifndef BOOST_GEOMETRY_CORE_RING_TYPE_HPP
#define BOOST_GEOMETRY_CORE_RING_TYPE_HPP

#include <type_traits>

#include <boost/range/value_type.hpp>

#include <boost/geometry/core/static_assert.hpp>
#include <boost/geometry/core/tag.hpp>
#include <boost/geometry/core/tags.hpp>


namespace boost { namespace geometry
{

namespace traits
{


/*!
\brief Traits class to indicate ring-type  of a polygon's exterior ring/interior rings
\ingroup traits
\par Geometries:
    - polygon
\par Specializations should provide:
    - typedef XXX type ( e.g. ring<P> )
\tparam Geometry geometry
*/
template <typename Geometry>
struct ring_const_type
{
    BOOST_GEOMETRY_STATIC_ASSERT_FALSE(
        "Not implemented for this Geometry type.",
        Geometry);
};

template <typename Geometry>
struct ring_mutable_type
{
    BOOST_GEOMETRY_STATIC_ASSERT_FALSE(
        "Not implemented for this Geometry type.",
        Geometry);
};


} // namespace traits


#ifndef DOXYGEN_NO_DISPATCH
namespace core_dispatch
{

template <typename GeometryTag, typename Geometry>
struct ring_return_type
{};


template <typename LineString>
struct ring_return_type<linestring_tag, LineString>
{
    typedef LineString& type;
};


template <typename Ring>
struct ring_return_type<ring_tag, Ring>
{
    typedef Ring& type;
};


template <typename Polygon>
struct ring_return_type<polygon_tag, Polygon>
{
    typedef typename std::remove_const<Polygon>::type nc_polygon_type;

    typedef std::conditional_t
        <
            std::is_const<Polygon>::value,
            typename traits::ring_const_type<nc_polygon_type>::type,
            typename traits::ring_mutable_type<nc_polygon_type>::type
        > type;
};


template <typename MultiLinestring>
struct ring_return_type<multi_linestring_tag, MultiLinestring>
{
    typedef typename ring_return_type
        <
            linestring_tag,
            std::conditional_t
                <
                    std::is_const<MultiLinestring>::value,
                    typename boost::range_value<MultiLinestring>::type const,
                    typename boost::range_value<MultiLinestring>::type
                >
        >::type type;
};


template <typename MultiPolygon>
struct ring_return_type<multi_polygon_tag, MultiPolygon>
{
    typedef typename ring_return_type
        <
            polygon_tag,
            std::conditional_t
                <
                    std::is_const<MultiPolygon>::value,
                    typename boost::range_value<MultiPolygon>::type const,
                    typename boost::range_value<MultiPolygon>::type
                >
        >::type type;
};


template <typename GeometryTag, typename Geometry>
struct ring_type
{};


template <typename Linestring>
struct ring_type<linestring_tag, Linestring>
{
    typedef Linestring type;
};


template <typename Ring>
struct ring_type<ring_tag, Ring>
{
    typedef Ring type;
};


template <typename Polygon>
struct ring_type<polygon_tag, Polygon>
{
    typedef typename std::remove_reference
        <
            typename ring_return_type<polygon_tag, Polygon>::type
        >::type type;
};


template <typename MultiLinestring>
struct ring_type<multi_linestring_tag, MultiLinestring>
{
    typedef typename std::remove_reference
        <
            typename ring_return_type<multi_linestring_tag, MultiLinestring>::type
        >::type type;
};


template <typename MultiPolygon>
struct ring_type<multi_polygon_tag, MultiPolygon>
{
    typedef typename std::remove_reference
        <
            typename ring_return_type<multi_polygon_tag, MultiPolygon>::type
        >::type type;
};


} // namespace core_dispatch
#endif


/*!
\brief \brief_meta{type, ring_type, \meta_geometry_type}
\details A polygon contains one exterior ring
    and zero or more interior rings (holes).
    This metafunction retrieves the type of the rings.
    Exterior ring and each of the interior rings all have the same ring_type.
\tparam Geometry A type fullfilling the Ring, Polygon or MultiPolygon concept.
\ingroup core

\qbk{[include reference/core/ring_type.qbk]}
*/
template <typename Geometry>
struct ring_type
{
    typedef typename core_dispatch::ring_type
        <
            typename tag<Geometry>::type,
            Geometry
        >::type type;
};


template <typename Geometry>
struct ring_return_type
{
    typedef typename core_dispatch::ring_return_type
        <
            typename tag<Geometry>::type,
            Geometry
        >::type type;
};


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_CORE_RING_TYPE_HPP

/* ring_type.hpp
/s0K2MzRGRnxk3+5xoSl0fbmGERbuPtzEir3F7cO6w2o1Fk0pGlMIYE4pTxtWEYIAopiTZJ/BJl9JdiskxiXZzHmCvoT5IJLMZ62N/5IJHFhjKN8VcfPmUnyR5tQ9vjGjGZDGrLvKuAMMoNatM/wvJC/qRq7k/yYlOnl7eYviyXQo/qWdIB3ZraoiycYXtNYkoaqBfk2+GQooLNmFFoGZtqgBJpF+oZCAM1KDxUK0oU4zQN2ysmLMOh5LcARDyGZt4nRg9a7djzuzYi14PDtm4nxSwPwVkTeR1rjHisarOPhVT4J02ZITSjS+j9f5z+FOsNccumz7f5HpUCbux83QnFf+NAazGxAZ8nnDuJPKSTRhGHt1DfFiM433ceVTdd2xFIGQ+gxiiUQ+06lnnaHdaOIqDhSV7ye23mUZcW0cw3Db+TZPpKe4JBLUbZQFEdJfjNKTZC8VWfpGX4VzrLIPX4/GoGZce8uxIM3qnzgcM2uxCdycVaYPy5BBj1VMSR/0zmOhKnQg+7F2UjOjDtn1pW1ha3HGYO5n+EYj0x5GS228OSf/uNJMt6eErvRrVvfCHxZqocntZunRRuaf+5zgJUaUZSON3gG+vjza068mQerq6mWttcfP2mcvf7fcTdRbDVDgsxEXsElbXDCukcjk3FUnoiN1OsON1d7tLaZUIwWO3HmnvZp+gRoNwfb4miQhn+p5l9Z0oLv4HXMTG+2+/qOwmt/PfSA8DzxQFb3z3ykVhbF5fXN5Q1mhUZ6uInmsGTqsA6lVg2P8M7IEoddZTUSAzwlM+/JfDm5x21D0d6trngyr9cULcy43B370cLCE7pP61NxklU9aVSHvGhy21IqDU9dE1H2RFAiY+X+9z1lDPnWOcbg7b7MmcbTLrRTBqhICUQqfbg2oj5embTTj/fUlKSkJu+fDgI6JJJIi/5MaFBPRbsEPQVddIf7oXHpHOJgfADZ4tGTzYEs2UqI5YSUWnMw0hVCCB3fLDo+QE8WIjxGDbJNVgCqvDQ2CioUp27RicDvwx47gh06hJoSaYej3xfV+ozfe5vyv3e4U78DL93TzD9VP4QBJn9RVxsmyYtMACB3u6BbquDBc8c3Hg6GqcPUPj4z0alg2PrqiEKSYvllHkIeB5JQCtUgqrJ9BSY3aihJ0beYFjJTo9NNM3k2QzdLsktPnLs3raQwr2uuH52lsvwXjPo9tBZCrlQKiavqMehtY+1eHhIWKq70vQvi/z58f6niMMZMS2hN9KPQlGTdczNTXR1eotM00sx6H12eXDQtLGytM87bP69eFx1BpefVv4G9pa572HsF8uPDQb79yjgBDBQkPAAQGChC9vQpqf70KVkG9CnX9dHfAf/w0378OjV6sQhEO7BgkUaa8GhJJDdgUYzyqhtsFssJmwOMtsoNW4+jWYuDvMLaCtmvUc04iY4vYN+AiMFsU/1Qzu2+8e/D/dqr+LdX8G8v4d1fwro+h3R/Dmp/HdT/P9p/+Nsre9dS5/ztKCTGG5N+I7AZP+zsIhSgRnGc3s4y9MOBsJUPPVJ1il05AM6PZas1EDdm9YKhrrKwAZ1UGvRL8gEg6eH3wv/twZ0u912FHSc7rwcREcmT1YlI2A41RbG366mJF9jN1Zunhy9ZFtHKImo2/b3n1g8+CaiZMdiGpi+vivpyYl8XF51aZOoe9S/AeARI/4CQjx8CQsSAX3wfvmI0xNx+jiLoUfXTYUJfW336NYki/U0c7wUNfQkVQyunt/DYjZwEZRQ9fQXOPSB69loKWvsH1y54HOX+d7862PlqPXdZGF64nzrIFL++uKW9F7HnOWfTtx6JP1B5kOEH/a+TMqTJAAagwJfa1Vm6gL7vGGABYZh9UiCBb0ihpSWGgI4GRBjF5yoYryIOcQkbnIwkd7omRU3gb0H0ibZD5LaktIluWfvOQsJdnp1tJhDSxLUlzLXSA10e8/IKVAjxTOMrtvj9cYg2HvOXhLfuYw2pQI7xhhJQaiTEDIigGcx8MfsSTaVAOJbzeloh+y1EzRBQ5PdA+dFwnhA0hAJIzIjq1creA75IBOx6TeFiZCOg7e6W9TCn+aTswXi3vbuZmabp0Z1tXSJ9fdeUhIli+rqr3DzME9XVYKle3uWagp+UJjooXSoi3oJGApYbedsBGLazzrxytPiIcHPYdJlB7wNUh+hCGFJBgNLuPBS0gnWPO6fD/MBpz6gvxN9TksVpzw7q+0mnFzIxzl8VMpHwQqvjn+eAdBkYo4Cdvt8iH+m/nw7Q0D9d+KYTliso4V6qmMraJe0x7HZAw7QR32vyIIb5QqI7q935WxjBbQO9N6Q1rqb4A6gGYMHv+Gt57dg4uRWVd7SUNM3dhTnXGbeebGTN7GkeT6sVKqoteSqGtRR1PnXCXnzxJKONNkxGP78Pz923H53WKMYnOaO2E5+euLSrTJuvX1usIbip1PC9GRV8CY4pTg4yFmzxHV73d+jirC24ce/Hko8r3BszYJiOsooHDCOqYu3Nv945cKszTCyIUH+8mlbh9y2ehjmU7sy5sY3ns4uVtVuH1zOaX3P7HgrZfWW1TpZN52AvtbUzsTKDNXWC3zGPprs1Fj57mZZAlCF4MFoPDNNyon0mPJ45XjR1tuASSa9g2hyZNZexvkRToPGGIS47eintQADr9GhcSSB2bOe9iXYMBD6DNUsAAiz9020dWQUSD0soRDMr3U3cziA7W3bEWiSmLhjKyTs3Oq7aNeLDLB0cXnwWwQDO0x1tDuZdnQWKwXztqw4jY8K7ejV/W9TZJYdf9cmtOCTH2bBFZM9yWIdQNR0qnjYlwQN5V7q+J/TI02lqBR2eWPEzyxYR3Teid31rr+Q1wsTu8AJiqwWyzx3ZPStSH6nDRD/URba7/bzxjbYQoVilPCDSEuSoRu/4bbcibee+c5/IsXhcbwMoGAoKiCi5bZeAofX6PW5JDhH+JT9c3DAlVCnpPUj1wnIh60JaNYc8KCgEwtB08QxojYnG4HTiyU7Et4J220o6gSozokT570IZzktK5mA6pKJMaAb4tphO/17/V8dbxKvOuvz3DDEANQHTwvhh03jUakyDcnlVJ/13Yv+d7m47ybxNOFp18GOwk0xtOpRL7lF7xJipfeF9Rw3SYqYATUtEQAmQGQHr5hIeO0nfcdMPuFWFfzckFKvbtKidVucPMl4xwUIW4n8r+Tw+eBS5OKu6M7iyvwxYWurCzaRshXSWzsXEtT/Soq4uSTQo7GKuGo04T0UMtVAOiM2ivjcKH3CTL42hJZ5DLFYrIsghRNVEESiVkIupKNyPvVAeiMP+hb0jeokuvxErSy1EVekNYVot1aID0/l3QsmjD9eUk1jl57+I8Q++BcwiQC8vChfLWlSJFqjzaB/feBongJniqgrlCgfxD/OIPgmcvFS8WqyJLozJlL8VoSakyWHoV7X68EMrvfBraUmtr9XxH+/UiB+1oQ6UJEo5RPtQvoCsi4XVYfBn1EYW9hk3qEXq+txG3jebkoRmZmUTj28zLKtAMcT1KEBQlDQoYbJGNhA2tdJJ/BY7bEyhmto2hbP1PXzqh1AfROuUnmlAqTYsLB3t4876bRQExQJYJlG9JY18ounlbuePzsvs2cJNBrC/iSsB5QNlA1sPFY6Rzx5t76N9qxTbzp8NKddUGJsBdmZgY+pe8HcjsWcN7Mx6Y978LQavT+GPxe5wkGmhqdB21NbifdiA4zSCckdfR6aK6jCfAQ6/tAqL7Bp3RQlGWDxeQ8r5UIWHaQP1Sr0BnE1S7EPKcHYPMfZZV8P6w1K9voN+P1zkjSP4bSlO9D7iLqjZrAL/VPfmVwgeVHd/xCrLcqpyu1BKJdFiVZtHfd2shORkckokeF39WhhnREjfmDZiS8FOpQJxfTNyT62Pzm/DiBgK+dTuW7L188uEXTXkpTdMITnzgDUHA06GVb6c954iBfzD7mbL6li4kvFELZtGFbSOX8UFLhxTh13EUFMNYepwUWox3rYoPOuABWJu6cqTCRvkOReJmqKJD4LXjjrDxr7VH9HqycQai3HV5Fl177MiRFhaSKoAqIHrE4fPviOK31t2kDRFP2GyNjDhVMn9lCw9P9sbXhXnBC6wW+fpVahIix0gm4qyV7nU2NXP7MusLCqWXB4JEUosx01JH1lILc82WSIVIu74oAMFWWM688RqeLxbx6GdsfDs7yYgtuilrxtd7aGLvLbZCqTkUfTwtX3LRE+Cbv3bRIuWTm7eznT58rJQ2CQfdB5/nbfnqrB2flWUo071+fY0hLB2rm4Zc+/vyNpykOUO0Y4t7sczCoF8hgMkEyy5cjrvK6RSDnMQ/uWannjKech5b9fEHnSsbHW+0NTO4ziHgBFG/9QSeXwPn26/q60UYRaoZYOnxETpN7tcv3XuvJJE3AhEzHcy5YAdtNCrQHMhtFfMktGc7R6Lzi15s82fP0L3v8t46gncsOpDrMS0cfPZBH9kve14avRDuh8wICwkw2N/Z0lnDVvgsMx5B/b39VR7Ec/W/DSPq8Gw/myaoIaEV+dUIB/JMg7MgKeE3ILXWgZHtef5DjzEevA+c/1YzK14dnvy+u4UfVj8dpLSYiuztZTLEEgNZCZFTHCE+0RLNxJnTh0wc558pZg6Q75FoWOI2jQ0U4Daod7cIAxwIRm5L/ckOjOBccw4cekgqgiKPLYUoWpBTh6ipLzgubtQsI1x1VuI/SuR5L/M3j3m63apLI7LYvJoEfWU4RT/SceOBXFxGxT42swmneea35R68Y20vQ2UpCtJg7TW0c6RMQL/7bIbZ4URSpqGmoGqvJy7rhiJ/F2ubXUJ3VerfAiEbHZoPwAhrvcgTOzDM89Ay+JDjWu7j53RzUBCPogFUejUu+lfIBD1IUPmKsMms6BrR5/JpcoxTLhGa/PO8lfSSLCBtGZadnRuYkYBkEpw19fh3VKOK7Xy/YLRvoXvJTRAjSiem93yCH+N7QUNfZ/yZigZVBjiyTkZOnqd2vvoYxO+lbfkQ5aVW2nNy3Of+PAmz57AedRN9MbJdH7JFKDrSr8rRdtXqbPgi2zTD3znsSUUp87YtHo44errqal3HhdQr1PnGrUlgtcRuKElNYPlhdu6qY+/1iu+yFFddNpyseHJg/DQ4eyul0hwFMCPhl9SHenafF3v5TY1QDAqMWIL6qkEbtnX3hPd5y3SL6ozAT7lDoM9ZROM5xC/3ahLfzzwRuxOXHlQtGz1N1pdKP+c3TzybORmF/f1oBkRDMEi9+6DgeyUGkNodGDTOIiVevDu1qEK9OMX+Rqx5vSTr2fhFAy77hw6OONVwts4/P2n+lGINyulJYgKX6qqIyHiO37RBu9wQPy5SlzoIvhpKP2FSOJfaOHS19HyHnV5s/HP1FhvfXhtgOjnitlok89gob+RjJmJ/vhSVYyEPFQFFCMEEJUUdEUooA225WrIVnPYPyUr7+zSHMMkFxH8casUJNVswfEjfpDRDacucJsyC+eiUSYHbHSDo0AseUR66xVeZqMxPRJ2TOFa+uQdjNi/SuV+tTAEhBz41HfBm6zd5dcWXKMEp1qtu1rzy7CURyVD8vRx22EJqyofB3/uNPjm2GrTW1nO9E5r1IHYGANZ5872CBtFSypDCTRNKt/IX4zQ2ThgENU1ZmbZt+jHLLTpSYmYTwLCKQvvmudSpHtC0HAucLI65ZjmO9T8T0vMeXr+8z5+Af5GkoQtMeiq41gRrJ3EokSIM0l3ZF/NIuUj8AF/vMYGKfhpWTpyl8LlWFJyo5tcb4MFu3V8/cAGSCgWd29QWrd/cbzHZZ9u7KIwgh9xWb8roDI88FnEHlz5d6YD8G9S/4f/kNfi94/P3Jor0+WF3u/llMNYyNrRaTgmmAOiOQ5S1xuk9BfyGKsdGLwAvEsNYh30EUxgiDazGG9j6PWpubVn+5RCZk/vtUl1REQVNEOjoNHbyOqa1tmE5LmDWuXCbeOt1gPl7Adz7wvq4OSpArsU6zWSzY6ytiGpdjb1260GKqGvX93dA/7co8Yc5uwo584T9zim98t1H//Ro9UPjEYskGVztZlnRXG/S/2iTbdwE9AlpkgwSR+8ZUdBXatmaPVH8eP4pdT1xYmxZ0XSPWbgTajizVehO6cIUuXJFzMJCFuuFokfq41cXglKX4yHtHQbpIMkdxiL6remsg1fm9vDnD3GZOUvfTz9mAbWhUUR47H/IpsJezAMxnIV3TTUEiW5Rz3s6hM2iuK8iYuEGl4kY4puKgF08HYCQ2VdNBIju2gMO0ZSYDfiC+r2+MmLBUP5e9y89X1cLKXPNY4aHVgC+OfapUm5MXG4/EcyjlVCsSs+nOZuuQwSL3+22gC4B2UEztf8yJg6NDJdCmt44B+4KblmArrlsQ5Mbk+ofY9Yj4L8B4uZG4MRcb42398rHqMr3RbGU/DOihWl0vHTRWp8j/ez4lnzpm4H5hNk4jj/dsjYy5MacXxzxu+v3nbBBb35s1NWQi+osUyGUtsoQ3Jj9NlsevGWSrwJ65z7xZMLBAy1FVBSY1KtfyQMToe/DrMe8ogjgionid5DF0Uk4aLSR7RDOSnIL6yyHn62NU1C+6R9JqT6gNRAFqApN4+nGsqAAqorDPBm757fV4EYYy4CpehB5Y+JmK2UuA6Y7tuci8HBryHncKWI42UE2W/QgxHVYZdlIvB8tu+uql11H3dGm+MtE65UWDLsulOFFh5jEqpDqn9aRDP7yUeKr6HerwS+DFwe3pNR8RDDZOR3gIw4OyAefbjbZM4wcnZ0+Y40UtRkcntwpXq44PEb7k3byvBOCymS5vi5nd4eWXLnO5LRyjYZY0mDFF5Jy2Rm5Ch7AzHs1x6J3YCXMyKuwsP8iw+qD8tjodpKv80lzgErv7UCOPGz6PFaQgh06FSBr58NCkWLyDi61UWkouXXGBbxSyXDpMyzBHMhTfip74w9tapgGnCAOmjy6TPzAW2rSNM6Ev5kt9suZhHVhwZX9lqYn0xHh1/PuI+uOoHXQE+f34LER6/8SHvFSSX1YjEbA7si9ZTNuhaWOIb4hTUI3QhsU6flWE5Ny3yMmp82enyGB/fP1kPwvhNq9GVyW0FAFqA8KixEy5H2Xc6VNC2L4tSECsColgMYzNusIKGgBC5+SNdsEDqEZIKJDG+Laz4EX6ZgB01IoYTuSzvfdH62lwWPFBsTf/Fpp7DXMkeCoETMFBjb0H4uP+EW656SFO6VXWM1zFC8MblRuRdGDkPUQ2a2XL7EAbA1/+4Bykcwqpz1Lsx0yxhOZen70JtNHM38WK7EwjwUrkbUWgEqo7yYA/MVwV4sV9yk23rp3Aff8D0ufVUKyu250uUmNxS4ZUALfKMQ2C7WiV8gMWYQ/4h2CZqXzzIBljdMTlNZHocYaesgh8AtrQhOlB+vpaRbW1HuW50H8tVYS7xKS96Rd+xVPbciPDAxJOV2lEbtogtlmmpRY5gw59ywdM6a6LEZ810X56yVaL3nJ3bobjfAeXMcCSa0Mob22/p2IYP9ho2gbkiCIOQPouZz0b6P2k+rK9Pu9hOFQgpbfyL/StSpS/TwZbDXZf5YnzbHYNMQrTzXli2qURfVS+NmTkKyYNCJEVWVbH+atSBdU2cX
*/