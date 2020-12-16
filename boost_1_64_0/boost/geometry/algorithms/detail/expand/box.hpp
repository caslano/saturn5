// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2015 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2015 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2015 Mateusz Loskot, London, UK.
// Copyright (c) 2014-2015 Samuel Debionne, Grenoble, France.

// This file was modified by Oracle on 2015, 2016, 2017, 2018.
// Modifications copyright (c) 2015-2018, Oracle and/or its affiliates.

// Contributed and/or modified by Vissarion Fysikopoulos, on behalf of Oracle
// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_EXPAND_BOX_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_EXPAND_BOX_HPP


#include <boost/geometry/algorithms/dispatch/expand.hpp>

#include <boost/geometry/core/tags.hpp>

// For backward compatibility
#include <boost/geometry/strategies/cartesian/expand_box.hpp>
#include <boost/geometry/strategies/spherical/expand_box.hpp>


namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{


// Box + box -> new box containing two input boxes
template
<
    typename BoxOut, typename BoxIn
>
struct expand
    <
        BoxOut, BoxIn,
        box_tag, box_tag
    >
{
    template <typename Strategy>
    static inline void apply(BoxOut& box_out,
                             BoxIn const& box_in,
                             Strategy const& )
    {
        Strategy::apply(box_out, box_in);
    }
};



} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_EXPAND_INDEXED_HPP

/* box.hpp
oKxXCzMc7hw5nZdkODQZ4DgWaTidQfdlbctyaOLg62e7wLPnRZdILNHttSzDacvYa3mA6/Y6LODE9npZhLO94vBsLx2P7XVkgOv2ekXA0e11VMCJ7bUiwmN7rcxwyF4N7n2ybbkKKG7Lu82Oxh7uw71j3snvdD6LKpXC1Zd7WM73vYbjpjNfVh75E7pp7Jdq8HOMb83LYrjWgm6a9f6b1Qh/yG4YR8D/c5PzhZq6Pp4T6Kg18tEgoHXSyHKcI3By1Gh+GmC0zoz9NMDYUfNo7IvxylN8McBcfW7VMK6n7GuWOBQssYsFti11r1bX5pEvUOveOqp70Rp0vZCjsQe67iNMOn98uY+LMYRubhw06ojbzgI1/3fSeBu1kW+RnOtuk3mYqA8qOmwL8iDbI9Ly7bHh/UCJ+UGLUu8HWzK72beDOb7BgdiPt2yb49PXQstnN7AW6sm+fVhD/SigvzjKrE9bSFa3st2MrMm86XP8I1Q7vQ7pIEuYlmK/4SB2pIl8ly2Gyx9gQ7oaA6No8I12gDjR3poxK0d++ifxcVTecfkawmi4jOXROeBxkmOawHmQ+IjDh6v9xWGouboZVZvj3WJxo3+Z901Wjjsvh+QdCFtJHszxT2FZNM/eTBi6tLFNtrA+b6+3WBLkPS4zzY05zlMhx1nQiWqlFOnjjYwF92U1cgefqyMWVerJum1uExMjiRLfeo7P1u23IP/nmLo9A34aKzsdsp9AdmsLZE2mi4Myi9ujtn2cOmaeafW9pqvv6J4VTg08J3gPcNwb5G4N8vZ/H+SWbJovdm7W/ZzkPGmP8REvP1/IzUUWfoxkub+HzGEXMUaXWYh6+UFgNmctsv2m5Rct2OjzYqvPy0if3FY8n1qLbSypDS6xYXbczoQR9wr4MCdVsT6vZ+ovYZk7LDc5ObUuhBH9isdMa3Ddi+GIc/Wek9SGK2NAKY/X2jx+u8XmMcoHXbzX6Deecv9AqTKgjTWbo3p7I9LYdXfYb3v476zsZis7W8husbJLhOxWK7vcyBqs3+WBjXAaTJTbly5tOzSq3yeH+XPvniCdE9IAPGe9zcvcHkK69If8mezb+Bp4AyPVCXm/zDcgK2MD+7BI4xfYgzxYLsAvHMnapOxOhIUMHSKncRfJ0mSc7G4rwwzVt517rCzZUgzmWfeS3BSgfxLOBl8XOZ5KWp1aonyMjA+L/bBe1tbetmzZMsq3jAdd61BLVpacjHgjWXtLNq1kvJ/7lPtINlalHHvuTyAfQh6gIN+ef0WyWlutDQEKtXZ5JjuDLRZj3B8s1l4o9UtbPWTli2Eux33YyYjLvn0vp5Rdun+18nrZfFlHRGIseoywBPe7FevQJl1ZxmW8GLU0nfcsVmRLWEdPIB4ovDiGr77S3k9CPlbsH0YSuI5xIPhG8A9gW6leU/oFkwHU+ylxcq9WBqg/+Sc45rvTOvR5/7Jt9ZADSbZAyBZZ2S4zWNYO2ZjhtbDsIstbImRXWtkNQna1lT1tZI33B+WB9rQQyjj7odnavbSdSKc8UFi1sn0EtyBMeCtifwRpS7x39xnBHcHzIUNV9N2TGLow4qTkSm14UswPT2N+FK2z0VuY497JAs52/xzwoUGAa9AKRF2/0ctLVfRZwZzpZo9tbXjPqNVddUA9Z3b5bO17wlCcd4RvT/Uh93yUYl7KaQeb5mXEK8Y8TAv9yxjlEv6s1rEbEr1yo9+DbLkSxKbUiU+q65FbkI+uTpmPeP/aSXFejYE8Phnj+HzM+EiMo7PhtvmOGMdrVeZDbMWMP9PzUIsk7105PPTOdaoj1o8V84bq1fEa7URG6slAvTICE8DErl28NDcMfQAhtxLn5bBcPkY=
*/