// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2015 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2015 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2015 Mateusz Loskot, London, UK.

// This file was modified by Oracle on 2015, 2017.
// Modifications copyright (c) 2015-2017, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_NOT_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_NOT_HPP

namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail
{



/*!
\brief Structure negating the result of specified policy
\tparam Geometry1 \tparam_geometry
\tparam Geometry2 \tparam_geometry
\tparam Policy
\param geometry1 \param_geometry
\param geometry2 \param_geometry
\return Negation of the result of the policy
 */
template <typename Policy>
struct not_
{
    template <typename Geometry1, typename Geometry2>
    static inline bool apply(Geometry1 const& geometry1,
                             Geometry2 const& geometry2)
    {
        return ! Policy::apply(geometry1, geometry2);
    }

    template <typename Geometry1, typename Geometry2, typename Strategy>
    static inline bool apply(Geometry1 const& geometry1,
                             Geometry2 const& geometry2,
                             Strategy const& strategy)
    {
        return ! Policy::apply(geometry1, geometry2, strategy);
    }
};


} // namespace detail
#endif // DOXYGEN_NO_DETAIL

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_NOT_HPP

/* not.hpp
GXH2rxTlBXR/oZ9M+0ug/Y84J/+e+C6uFHc+iO8Piu+ySnGeAHJept/f6PcK/V6l32v0ez0ge4T3BucL4ijd/g7dDhCyxonvQ/Bt7Q8eb9Hvn/R7m3k5+/8LvCpF/MlyXh/x/02/dwNxab+rqFNuhW8RrbX1eyoN+yvfK6ryAnYxdjb2NXY19jR2NPaTdhleBZ4ijuS5F+Flmo19jF0OqVRviRGdTJtJu0mzTNveVbivg9dUEFb1xZN8T6SIr9JvaGAfLrcfrsI5MeG/H8O3OKdhf/qcRhniLhBx5+Fb1uv1og6U4ZjCV5Soc26C13MHBmlrVdwJXjA8jfFZ3zAwqVcF9J8t9D9L1VeGVrcNlX7+Ah8Te8Fk/VlFdJKPrvfinP8Gj3pYnW2pFjyKpC4lWMcRPJ6MuK9zWpUIi3QvE+neJL5XiO8eZQ9KK59LXIx11tngt0bEO1F8p8X3BvfNeRJT+XUY8Qo5A0h04WcAP17l2nyDl++HGVoOQ1fpW0uFTqvF9/Hie6X4Pl18n4HvL6A/59p63qMJufb5zDTdDsawmEdbuh1YvLe90c3DEI8KnIeQ9+3HTRxPvIcUslfT5Pdcz/B1e2oozcMWV3n8b0Hee6xdntyIPLkRNltaxX6LMPDKppQGPut+g1j3XlGVrdPXwXb63GR4v2YvbyV8q0PYv9V9811mrjzTHmucWed7PMV7CqZsmPep7A5ZfjdB7rt2j+r58APkewrgVxHydkI85O2E6RFvJ8zVbyfgjaqjZV5Rn5tv/ER3e/dvJ+SM48pmlTqvh/Ikz1guRj/6OKKVdJWxcLoTiC4sH+UeWPq2+Xii4glapkuhH3YSt8f67Z6od3tGeG2izngyj7thO7jOBB7x5F6EtfC7CvharjvJ9d0PXYhbLnz2QPEdF98T8C332Y4I2WfbVyXvcg2nOcVvK0Cj9/OmFY+w/bwDIk8vxz2n8h5v2ffdWBW8d+Zs3Ns9f1w2fRciffWev995Te3s2TMOxW5m91YzYLz7+U3scfbh5MpHNjZ5tWJv82kkO9k+aDeU96V4dzNDsL+Z9yN++SCKZPaKElqW3wq739Ttpffv3d8symNc6GCLVjaY4y2L3HFM/bilKls/niHqR4LL8Yd9U39JadbnTq8K5sFZKr8OQR9gctlQ2s9SeCXsMWBh7T0dCbQvPCdiYJgTAixmYR3JtHxf1MLc+QB/PmKrsFsFvd965JImept7+UK6Q25Rk9/uaDDaHuiJPiz2/MMW0oc3HuhwFwAn78bSe8ovQjn8nKNl3y+BLeuU738e9F8AfT9sdWFV8K27bVW2fd9EBzHdWkCFtRGdWu0dSMGWFxNNOc5cIo7xtXRyoKOvv7WX25ALDrD3rWTohXHbns/B/ttLhC2neyZG4NJbCeD5lx+WZf1o9ThR3+ONrUuJ52X00+8/bEe6L6/KdfdhOs27MulTyh1TNlTWVRGyroasa6py3ecz0KXO3DBAyt1RpeW6+uq6qmwfmMqPlXs95H5Jli/EEfdD27yUZeZGxLtJlNEr8R2+rkl52b6e1EysmT390OxM6VAwp+PLgve/S8X9StBvJ+Fvod8jB9N9u2M87ytVIo3inMmt0PU28JvvuTMFl9py3d2ZQNlrpiscEx0DPT2b7PbVMESOuq0/3RpwRRFGX8O0zzpfvhrhD3dB569VZfuOtaOzdePXAff7pvdUBd9suBfx7wPd0og8SbijVgmU0kRXJtlj1Q9HcT19v6inv1mVbdceUPXPt6rMT52fgW7fEfl7Y+lQ23w3wjYPIv73hG3uFPp8P1cZyqvOKIr9UPB7OJdfF1ifG94/Erx/DN7/Ddxd1YV6EG2PWIs=
*/