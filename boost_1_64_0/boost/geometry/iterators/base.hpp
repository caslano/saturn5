// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ITERATORS_BASE_HPP
#define BOOST_GEOMETRY_ITERATORS_BASE_HPP

#include <boost/iterator/iterator_adaptor.hpp>
#include <boost/iterator/iterator_categories.hpp>
#include <boost/mpl/if.hpp>

#ifndef DOXYGEN_NO_DETAIL
namespace boost { namespace geometry { namespace detail { namespace iterators
{

template
<
    typename DerivedClass,
    typename Iterator,
    typename TraversalFlag = boost::bidirectional_traversal_tag
>
struct iterator_base
    : public boost::iterator_adaptor
    <
        DerivedClass,
        Iterator,
        boost::use_default,
        typename boost::mpl::if_
        <
            boost::is_convertible
            <
                typename boost::iterator_traversal<Iterator>::type,
                boost::random_access_traversal_tag
            >,
            TraversalFlag,
            boost::use_default
        >::type
    >
{
    // Define operator cast to Iterator to be able to write things like Iterator it = myit++
    inline operator Iterator() const
    {
        return this->base();
    }

    /*inline bool operator==(Iterator const& other) const
    {
        return this->base() == other;
    }
    inline bool operator!=(Iterator const& other) const
    {
        return ! operator==(other);
    }*/
};

}}}} // namespace boost::geometry::detail::iterators
#endif


#endif // BOOST_GEOMETRY_ITERATORS_BASE_HPP

/* base.hpp
XgGPwEoYSKS9wxAsha1hGWwHW8IuMBOeDFvBXDjUy/WHw2EezINT4EhYBkfBZXA0XAnHwfVwPNwA/+Rh/gL/Ah+Ab8NHxP4S/I55neF6+Cf4vjmewL/Cj+Eh+Hf4EfQkcT+AHeDf4cnwMzgQfg7z4BdwPPwS5sNmXq43fBn7efAVWAR/BSvh1T7Rg6TXUnGT+2MKrIroRUuwnh9uga3gNtgd3gaHwx/BM+GdcDq8H86ED8BZ8G5YBmvhcngvXC3hrrLCyXOMrF/C+TGeY16Q54z9sCN8Sebjv4B94QG5b74M8+Gv5P75W5kHDNJrgrQdiT8B9pD47/dZ5XoIjocPwzK4R+ppnV674l4fQ4/kdwmXCDfD9nAr7AV/CIfDW+AoeCucALfBs+Ft8EK4HZbDO+DVcAfcBO+C34N3ws1in9jgufdv1pn3A5d74+fe4+fe/6/Ove/+2dd79v0QfSyLj+3lYYoxmzDPYj7HtFmFO6YQU42pxezHHMF0Rxnk2NXxM+7xX/wX/8V/8V/8F//Ff/Ff/Bf//W/9vobz/2ovm5yvOS7n/8ekGfq7cYY3uscwBTMH82kGz9Nz7HsMVUYkC/LZuNj76UQuW58x8cgZE33eR4dppfdEnaHs07Dr76aVls2p0t+sXqf8W8i3nvR+TL03bLTyn27bbz97IQlq+bOVfz+9V3Os7Oft3oS9mpmyH5EyYddlcnyDr9h2Xr8FpgjzD8LvjVGX1umegtmlJbPnu+xNFLlMXc5XlH2Ce91qmdZ6f+erUjc9DE/M+p1HmI9UmBPETri5Ut/O+tTh31PhgzHCsw9R6nf8MZxFa6iO+8oew1/L2frXJaKDmL8TPn+u9R2yoqrKpbMG9J9F+7R9G2xZH9sZbgkb1Pvqpiv7RHv4vrpOdfjXlX8L3BOtMyj6+9mfKP9TjZZqZ6hHzuNav9xS/KTuOymXBX3teflIyQb0PsUfK/sKYgvYZRz5v93Kv3z3nauj7C8ao5rwrUbr/Cz1Im6p2o2yN3KPX+y9dk3fU9fUvX/Haw9e7L1wbnvY3PY0uu3Zc9/rWKD28qW/uHfLwrLX98x/s/n8qpnh7W574Zq+x6+pe+di75Fz2xPotkfOba+g215Htz2EbnsF3fb4ue3Nc9vj57Z31HWPqNq/V2PIfUvulWZfbQ7XSuc6Tb5LNRy2giNgFzgSnghHw17wdDgYjoXD4WQ4Gp4BJ4j7WeJ+DhwPZ8AJ8AI4Ec6Bk/X3h2TMl/tOfp3vm3ST71P1gBijJ8yFfWA/2Ffy0w8OgYPhGNgfToYDYZHlLu/1ZDyUMTi/znu95gQx2QKeCTPgrTAT7oKt4QMwGz4CO8M98AT4DGwDfybu+2A7eADmwIPizvt/3kMd/V3V8XpPtb6P9yu9q/qmvKc6PNwTf1cVf1f1tbyr+jrfU5XzrulGzNPxd07x39f8S8DM+jc9/5erY2/qkf8rP/MPIYd95Tk1T/Z2d5BnfnVuKYO+NVs9Q5Wbp/tEl1xM3STjPZGwHfQz9fdSj/5MLXrT6uoa0fmaKd23ANNC9ui8Q9gae75EP5xTh431wCd5I7zzG9N3KvsIo4M8h/mUnFKlos8w3q7CDDE6kR957pN4MmPqo8jH/3Hln6vrYGgjnnnl29tyxkrnXZ939Cl3lTdH3ayXtYUJEtl4zHvkKbVY1Y3VVArmlC3C3kz0HFI3S6LPjRKWq52u7Jx6xM5fHvE6utbnBC2XpMvdWtlH2urFVJ5CGeR5uIXyPwMtER5bmDmLl5K5iB6JTBXm9EY/r1Ie6oXySB2m1qtDZ311Tqjfxm8hH+XO+qKRu9YXYY+9jev81tHhdqPsa74d01r4V/K11ZE=
*/