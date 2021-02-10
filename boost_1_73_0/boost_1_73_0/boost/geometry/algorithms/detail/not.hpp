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
VHcbYBm1C33CDNFrOxDwI9oHUbwcwQePg6Z00Dl9fXL4qlP8qnWR/IoukgCCdWK0EDj/pCEfOBwuBu3d9i97nAEsdCW4mHpdW3wOW6tupoWROj6YjnwA5jbmbnCQkRY2olVpITJCFwdHJUdQ2h46fQ0VZFACp8kFsg/ByQ+X0ESkKqQPAFHDwPiS2dTx70WwMVqWkJeTdDkLEfEYV7zAkGeiLmhBdJsmTHGhKUIYEiHxsrYC/bqtwOZVw4puMOU8No3Sq2Z0MHEvN7RjGeD37JMR3CWuPbaB9h5hEXKxLqQorzUtjrojM2Fy33ief1URWjQ3TXvFykAUC6WOn88hAIh8T7nJJa26NhlhFPG2U6wx2Ehq12oFgLtlhUcLRxVjmggSpGsOm2+NVCPneYGZIP+Zlb66BKJDsA64nGuutOmkXuF7+kgt46mJYOcXQQkpLeyGe7DonBpmtKiBfplUe7smWEpiTqLpAtzSjOcM5QIePJPR5RWKAsi6OkoAvCECEQc2bAlyxcERVgu0BaINmKGwPOy+OQYgWK/T7fWPOt23vXf9g+OP3aPj/QPTTnSFBZfbtZhvlo+mHEhx0oFoMM8HW9qMzUNI6PswqjFP+TYuD7ZVgEVT9tNymWPcp7nfAs3I+NaeYNlnQh1F
*/