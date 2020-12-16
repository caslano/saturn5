// Boost.Geometry

// Copyright (c) 2017-2018, Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_SRS_EPSG_HPP
#define BOOST_GEOMETRY_SRS_EPSG_HPP


#include <boost/geometry/srs/projection.hpp>
#include <boost/geometry/srs/projections/epsg.hpp>
#include <boost/geometry/srs/projections/epsg_params.hpp>
#include <boost/geometry/srs/projections/epsg_traits.hpp>


namespace boost { namespace geometry
{
    
namespace projections
{

template <>
struct dynamic_parameters<srs::epsg>
{
    static const bool is_specialized = true;
    static inline srs::dpar::parameters<> apply(srs::epsg const& params)
    {
        return projections::detail::epsg_to_parameters(params.code);
    }
};

template <int Code, typename CT>
class proj_wrapper<srs::static_epsg<Code>, CT>
    : public proj_wrapper
        <
            typename projections::detail::epsg_traits<Code>::parameters_type,
            CT
        >
{
    typedef projections::detail::epsg_traits<Code> epsg_traits;

    typedef proj_wrapper
        <
            typename epsg_traits::parameters_type,
            CT
        > base_t;

public:
    proj_wrapper()
        : base_t(epsg_traits::parameters())
    {}

    explicit proj_wrapper(srs::static_epsg<Code> const&)
        : base_t(epsg_traits::parameters())
    {}
};

} // namespace projections


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_SRS_EPSG_HPP

/* epsg.hpp
E9GgXoj14yqhtsqJiBwRYk1yt1YhwZaoOnaBH73reXp7edapb81MCGTVAkHBqvzMgfxk30/wClNuACWExChN0LLr7nG99boy/JfXVvYfOj/R8dY3oj5IlrLvkcA3tbytdVRDVUeNReZf1JHmQ+cJ/oIdOqLjP0yW/kMfaSZOWX96oTw74qB6gsxkbzb/YbKUfV0f6umgJrvtKcsc54VV4FJvdq8J01rHO/BCDspTaH/zcMtOfblST23Fevq/DsqTdTPjD5IhjfW7IPWs44Mn/P2Px4W+tiA8tfPUOfunJL3j6ig63vpZiQ+SI+v4sFcvTNY8fWx5fzfwVra2E6fgmqPtO9wlHJQnOFfZtoL5ILnSWL+DsdWaJy8lrZHnrSvlFmKItS8tg18s4KA8QT3FDzd/uIrSWPdNrmzNkzKeP628V5etASIY8mR7x624g/JE6smybceHyJnGup93IWu+6ijvln/ivMCC8ATW/eyTEYx/jmt/CbGWj4gPN3+IDCl5su5j72zNE3yy0PasM/xpA3unWM9P8Le7g/LE7Pf+QXKpse7V52bNozImHtvdYW+2dhBvrPNz1/yOa4/WN7I/WH4Mx2Sd1VfVWSvRyNoO/R04ZpBPTnyQUUNJci2SpwbKnCJviG92qgPFVWfr3E/v8DpS9gUYnDD0w/QwjfUbmwHWfClrikFhE/tlayPhYu1fGfCLxRyUL0slKdvOfaC5ksb63c+81jw1Ut6h99KssJ59RYK1/c1w4PzP8tWa/lHRHyJH/NyvPS4y7mgc1/bkq+5xH2TQ01i/q5LHWkfKY0braqaczk51a/imh3WOrvyug/Jk++DKh1x3KN+ocbHmqYkyh8jfaoT1Sooongt5yt4uLTLBsonjh5kCZj8vBPnSWfPVVNk/wbfmwmxtKa5a85XowPHc8m2mDzsNzM4XfL+rqHU930wm2/J1nkN/sZ6P+cD5svso1wcZAfnxwiTmMGtF2+Y7loterXxCYC+f6Lh+MQZl26J4g0diowbVQ7pbduCKN7SHUTvE28uSDEiTl6d3vbqN63p6hQyPsSRrcGRcbOQQiEtJ2N9axwaJFCZtdBMbJX3/dTlBjWRvUKGk6O+kp5fYzaQn581j/rfSq+/VwFJ6EJmSXMsPf7/seopDfz+t2ZvEODC1fFp7/DdptU57HJdYPq3d/5u0QvtybDPg0+oiPOrYnuKE8c2B1/IhPfALcAEbPnPmuIjlOC2+keef1so7EyEe17K1o7hqXbmbNQ4+ryoL9Q8y+/lP9egrjufCdVfl44IfaIr6H/JTCL4zm8vtEvbrc1zEsl0+3mybwxrC/GmmYFdg88mcx412McpExie3bzNBmpW9J2Wa26nS3EkUz/8f0+zQKYKSvkEkfQGq9HUWabr/mD5HTBMs6VpB0tVela5uYor4j+nK7dOaJc3zSJo7qNLY9X9Is2PPbUp6U0h6O6rSFyySNf9teh0+zbGk+RVJc6AqzV1ESt7/Ns0On0LgPcnWrpbxOKyTKs29xaE2f53mLcrevIYOA2Oh1xrg5mftA57/zCEu+fwh/GOw9Z035d/Op8zBd7CNlcCJLfv0x4toVZSzoLSN+92O4rUdsKV6afXvvniA9/0g9jkkXIvN6Ua8vw4v1y8iFnz5jxR87xKsK7GIPLUnY1rgBqKzNNVeGyawAcR+P5mZgc9VgS0mFvew8V7MAzxxs53Y5NPyHckkT3W4drGRzzAtH6vT+cK/N5ZLGlhZaZZ3HTEtYO7EipfcchjbghesvKymgVnW5S8H1rGZGawUsfMmr2CsW7DG+aV9OvPpQ5spi+kKMpzl2UIMB9aZWNJ75x1Ws7ywr5em2tvDFaw=
*/