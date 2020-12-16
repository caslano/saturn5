// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2015 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2015 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2015 Mateusz Loskot, London, UK.

// This file was modified by Oracle on 2015.
// Modifications copyright (c) 2015, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_UTIL_COMPRESS_VARIANT_HPP
#define BOOST_GEOMETRY_UTIL_COMPRESS_VARIANT_HPP


#include <boost/mpl/equal_to.hpp>
#include <boost/mpl/fold.hpp>
#include <boost/mpl/front.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/insert.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/set.hpp>
#include <boost/mpl/size.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/variant/variant_fwd.hpp>


namespace boost { namespace geometry
{


namespace detail
{

template <typename Variant>
struct unique_types:
    boost::mpl::fold<
        typename boost::mpl::reverse_fold<
            typename Variant::types,
            boost::mpl::set<>,
            boost::mpl::insert<
                boost::mpl::placeholders::_1,
                boost::mpl::placeholders::_2
            >
        >::type,
        boost::mpl::vector<>,
        boost::mpl::push_back
            <
                boost::mpl::placeholders::_1, boost::mpl::placeholders::_2
            >
    >
{};

template <typename Types>
struct variant_or_single:
    boost::mpl::if_<
        boost::mpl::equal_to<
            boost::mpl::size<Types>,
            boost::mpl::int_<1>
        >,
        typename boost::mpl::front<Types>::type,
        typename make_variant_over<Types>::type
    >
{};

} // namespace detail


/*!
    \brief Meta-function that takes a boost::variant type and tries to minimize
        it by doing the following:
        - if there's any duplicate types, remove them
        - if the result is a variant of one type, turn it into just that type
    \ingroup utility
    \par Example
    \code
        typedef variant<int, float, int, long> variant_type;
        typedef compress_variant<variant_type>::type compressed;
        typedef boost::mpl::vector<int, float, long> result_types;
        BOOST_MPL_ASSERT(( boost::mpl::equal<compressed::types, result_types> ));

        typedef variant<int, int, int> one_type_variant_type;
        typedef compress_variant<one_type_variant_type>::type single_type;
        BOOST_MPL_ASSERT(( boost::equals<single_type, int> ));
    \endcode
*/

template <typename Variant>
struct compress_variant:
    detail::variant_or_single<
        typename detail::unique_types<Variant>::type
    >
{};


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_UTIL_COMPRESS_VARIANT_HPP

/* compress_variant.hpp
p4KhbKX+C8zDBbO6bLweDVuzxDccMQITJ+WeL9//JcbTry0eiJ97tl/IDvZkV9mpkTH6Bog81O5hPN3gmgeRAZ55vWgDbyEPhy9xy0NwnL5uZuhr24s2gKDwtfYyYPJ5kvZ/4F5i5gYmVBYZYcZZfVEO2BPzfFd27ucnQuZHwJ1h5+oFzuN3JGQu3gtrDFd27rlC5jng3rQQ3Kpq0gJOqFDSzdqMKMvx7hLsXfc2nv5ysZOdTvDsPwv2bLBf6XRhN0UbOPwk/ELufWB/48ZWM5rSXWnIxsMc8ov2dgPyMKrLLQ+53+OV/k/7Yq/Bpb0ls2kWGywxls8Ce81OF3Yiyab3lvP//WAb6M5n484Ad5ZLmcezuV/bivLO2x86XzeueiyxYzHO8m4H/z3n+MKyjy/a+KoHGE/v59K3onHShzKs7aX/F9j3OMucrX0L9gqw57mxo/EIB1vUdSYAn06Xuo5kc9+3RBvvBbdtiZWrG2soBoZT7tho+PvZyzwSZa3rj8F9YpGNG46ppDNjYQuZJ5dCZ2Yvc1oOtDH4sor39nLBXWrjVowz7KNoL00zXuRck0aC8Jde7MxDSiXnUrWVpewFfzn4V3c5+fQuUWh+3sJhKyfqvq4MfiBO+VnH9E5w85xctjHdL2QegzHGpd01Mrc7KT/ysLZTfrb3imhzk8Yi7ohTfpKdTohUQqlGBr6Q/S3wY258NaZy6IwFu3ocbFTsc8ZgeQ11eNY6XwD2fDe2yvM+l/Zv5bD96hZsipFAAqeTCepthhlgfSgdDTPkQYw185GH1xx50M3vcs4V5R48EO90JzecyMZZ1sUlos7BXmhhTyivHFtRpkWo0Et+EHyMxx2EubslH4jPwWSHJ9jPgP2Yg10e5NLny/g3FcbT3Rb26MCE8lItA2xjrdCzzwN/Hzm3Gn2gko77OWIJCOau442nf15sYhLQn46zMWeB+W2PiRnjkVPUbUEl/J5MTH1hpMVsiEZoB0UJxRpzv4ci9R/g97nzCc7jNyv1H1WIE9dl4ten1VAq3KQwcmeAe5qpTevmrUz7R2IcWbca+k3RlytLqyrHGEE61DBtdzPYbguZTwN7rlifjQ+OlOYMDHbrol/1gXunmUvmDBz6VBn/5WDs+4p5imFOyspcBuamwvZq3PhAqbbBzTAXlPZPNZgL9piZE5NktcDyTpD2T+A+YuFSpWpuSQxcUcbBCZh/WrhjovFQLOdMIesjYM6xMOH5wyCr3P+phT+gnctsGzIb3J+F/mhMefUEzSaWkTl0Ivb3xHhcdkg1bbqEyJaPjTkDzCttTLLjY2Ouegj2UG1MsqNjY7aBOcPO9PPJ+TmYK3damUWM/SVyqPH09l1mpqpGyF2UY00o7V/BfchcvqlwsdLUEgorLZGRDGxRzrWT8E63sTnH/gVgPmdl+qmYWfcng4cZTy+wc4sLNTQb9xFwzzZzqVq52rOo28LDjadXLLJyOct4NphPmGWNRtQQUx8S65AdjzCeHtbPhS9OtFFNZ+qnMMVvk/5P4A+x88PRJIUjYeOLci+oQ4xZM1+Nh7UNUQ6/LzF2XQnunWZuRE0rakQdwVTnQuaNj4TfgI3NNY6Iuu4At8D8niC/WfrPT068idiUohGFI/n4Gx9lPL2FhU/tKxaLhhSaCTCVu5Qf/I1d+UX+UUx80ebyFOPpH8z1HlLTuuiN4RaOuhfs6WB/7cYO87BLRL1PxtNdLmwqcn2+gMkgRz78wu8R+Vj5z/JRlPs87CzKImQ8/alLPXD1f8GeAfZyO7toT7Y5jNT/1BtP99jZ1O2423472J0ubO62nxeGnVWXkz2Ybb8D+VjhUgaD1fbzIsbTb7jkgas=
*/