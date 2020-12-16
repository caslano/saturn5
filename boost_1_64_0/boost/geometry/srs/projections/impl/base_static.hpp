// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.

// This file was modified by Oracle on 2017, 2018, 2019.
// Modifications copyright (c) 2017-2019, Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_PROJECTIONS_IMPL_BASE_STATIC_HPP
#define BOOST_GEOMETRY_PROJECTIONS_IMPL_BASE_STATIC_HPP

#if defined(_MSC_VER)
// For CRTP, *this is acceptable in constructor -> turn warning off
#pragma warning( disable : 4355 )
#endif // defined(_MSC_VER)


#include <string>

#include <boost/geometry/core/assert.hpp>
#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/srs/projections/impl/pj_fwd.hpp>
#include <boost/geometry/srs/projections/impl/pj_inv.hpp>

#include <boost/mpl/assert.hpp>


namespace boost { namespace geometry { namespace projections
{


#ifndef DOXYGEN_NO_DETAIL
namespace detail
{

template <typename Prj, typename CSTag, typename SP, typename CT, typename P>
struct static_projection_type
{
    BOOST_MPL_ASSERT_MSG((false),
        NOT_IMPLEMENTED_FOR_THIS_PROJECTION_OR_CSTAG,
        (Prj, CSTag));
};

#define BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PROJECTION_F(PROJ, P_SPHXXX) \
template <typename SP, typename CT, typename P> \
struct static_projection_type<PROJ, srs_sphere_tag, SP, CT, P> \
{ \
    typedef projections::detail::static_wrapper_f<P_SPHXXX<CT, P>, P> type; \
}; \
template <typename SP, typename CT, typename P> \
struct static_projection_type<PROJ, srs_spheroid_tag, SP, CT, P> \
{ \
    typedef projections::detail::static_wrapper_f<P_SPHXXX<CT, P>, P> type; \
}; \

#define BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PROJECTION_FI(PROJ, P_SPHXXX) \
template <typename SP, typename CT, typename P> \
struct static_projection_type<PROJ, srs_sphere_tag, SP, CT, P> \
{ \
    typedef projections::detail::static_wrapper_fi<P_SPHXXX<CT, P>, P> type; \
}; \
template <typename SP, typename CT, typename P> \
struct static_projection_type<PROJ, srs_spheroid_tag, SP, CT, P> \
{ \
    typedef projections::detail::static_wrapper_fi<P_SPHXXX<CT, P>, P> type; \
}; \

#define BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PROJECTION_FI2(PROJ, P_SPHERE, P_SPHEROID) \
template <typename SP, typename CT, typename P> \
struct static_projection_type<PROJ, srs_sphere_tag, SP, CT, P> \
{ \
    typedef projections::detail::static_wrapper_fi<P_SPHERE<CT, P>, P> type; \
}; \
template <typename SP, typename CT, typename P> \
struct static_projection_type<PROJ, srs_spheroid_tag, SP, CT, P> \
{ \
    typedef projections::detail::static_wrapper_fi<P_SPHEROID<CT, P>, P> type; \
}; \

template <typename P>
struct static_wrapper_b
{
    inline explicit static_wrapper_b(P const& par)
        : m_par(par)
    {}

    std::string name() const { return m_par.id.name; }

    P const& params() const { return m_par; }

    P& mutable_params() { return m_par; }

protected:
    P m_par;
};

// Forward
template <typename Prj, typename P>
struct static_wrapper_f
    : public static_wrapper_b<P>
    , public Prj
{
public:
    template <typename Params>
    inline static_wrapper_f(Params const& params, P const& par)
        : static_wrapper_b<P>(par)
        , Prj(params, this->m_par) // prj can modify parameters
    {}

    template <typename LL, typename XY>
    inline bool forward(LL const& lp, XY& xy) const
    {
        try
        {
            pj_fwd(*this, this->m_par, lp, xy);
            return true;
        }
        catch (...)
        {
            return false;
        }
    }

    template <typename XY, typename LL>
    inline bool inverse(XY const&, LL&) const
    {
        BOOST_MPL_ASSERT_MSG((false),
            PROJECTION_IS_NOT_INVERTABLE,
            (Prj));
        return false;
    }
};

// Forward/inverse
template <typename Prj, typename P>
struct static_wrapper_fi
    : public static_wrapper_f<Prj, P>
{
public:
    template <typename Params>
    inline static_wrapper_fi(Params const& params, P const& par)
        : static_wrapper_f<Prj, P>(params, par)
    {}

    template <typename XY, typename LL>
    inline bool inverse(XY const& xy, LL& lp) const
    {
        try
        {
            pj_inv(*this, this->m_par, xy, lp);
            return true;
        }
        catch (...)
        {
            return false;
        }
    }
};

} // namespace detail
#endif // DOXYGEN_NO_DETAIL


}}} // namespace boost::geometry::projections


#endif // BOOST_GEOMETRY_PROJECTIONS_IMPL_BASE_STATIC_HPP

/* base_static.hpp
EVJ+ud71m/58bmIn3iys9IUNLnwIJ49YQLDvpm2UcJmIq2JokCO6qaW2uPNaz7y1k+b1zS4fx13vQt9F928JF1f+qIffPk+u893ctcIQ/lio1O3p7vqoW/4h1l2V7160o1yrB96dwFl6ppufm9EaYhgrtB0Uc7wXaNutLlgQhkHV3eJzSzPq3RHg1ls70zkcJT5KYj1nr1uA34rR5xKVB30hs2Wn1296Bvb1DcPx9sl1qw+OrVFuMvbxFylf2cbWKDcZa5QHqjHgLTFJ8yBFc3GLN8e+Qb9r2xKwt2Nn6TRxMxAfi7bTPM3WgCwH2syR7kb5GIszbVS+uIPZrzU4x5bWT1JXRJ3LlXzUE259DibURIZ/g2kn4x9Tex1J6e72JIGuzh9Nev+I5bn0Gv29D8+4PGcYl6j22B04TmIrU9mc6Af6WwXsezvAqTcX2JogKuH4q9KV74PWq7KZ/EERCHHhl7a4NtL8qWyrhDlJbHvF6f12NU8NMNutqXE/FuY7FV39uwbpe80mXP/dk5ZQMW+Xrnu4n3FjUP33TxSv4WBeQ7u791wY39O3a6BnGEP8zkHN1AdNvjHC+umEmqun0X7aP833Oh7itkdWZEHqHFr2bStLPrvjHLbXCr8Xz20W+0Cggu8DvF1/u87BWkOtzS9jbbg+5JnVxupz4iC+PdXfNTTUs8OlY8/Kvg9l+p9k/eThRj8ZbcFl9JNHqH5yOeNxKbt/tDHuJRT959W7SWOKPqn7WUBeg5HRQO1nszET93RuOdHirXtS1T3eIutOq7qvaJn7XG4hY09G8c8F+FTW9alZbCz9HlHMfb/HfJdI+BhgOt5D31CTfqjHgxx4m+dG2M+lC8YnLA04nTM80mjDgrF+faSyY9GYu3Q7lBR8I/TXc7ulv0FA64mU5/0UPG8SzztV7tu0a5/MZHxwqGfAzYnZMzKMvzyF7UU2e8hdrvgh3XbQZ+mfFbZn70XpGBxs/0/ergS+zqKIfw1pGo7Cy300aGilxIpQCpTaQts0SWlKm6RJWgoCaY6XJpgmj7z3enDZKkLBWsolNxSQQ0AQuURuRKxWhIJcAnKKCoIgtCIgOrs737z/N/leklZ/5vf7fnm7Mzs7Ozt7z84uN+FZPP6sxPFtO++EmfLHYP/8xNxUmzpJtamTc+lTbeoUluep0I7WqTXEalUHazjNtyBNTNlVnmbLtKyD2E7tGVCYFvayzxChMO1oyBiTL/70nF3ld1Aug/sxDPCXH3H8nQH8nRABfQF5naXa7Xe5rGdyu13HZf3eoHsOlU11B7Qsqpy3sMbnDmNwj2k9z99WM/0NTP8c0GcP+pXzoD7PV/V5QS59qj6/z/QuZNw66QfS3Rm0dzZkfIjA+CDtHva2/bduLsb16TD3+8cH5vTsF0Lmgc7CGtvFpYF5GT3t5VthoxNfFY19YTnItBxkeoWq8ytZhpdznWxkGV4F6SeDnfc1UCc/UHVybS59qk6uY3rXM+4gdxzJxr/vG6lxV8XB/DYvzVt12SaulyLhjuqNKEe7T2VubdgM/ICVWeg6dwd80Zqy3uzr33DmUY019P4GTKPSQXmMuIVpr/8/zZt+RPEVyo/vrXYNaEcwc5pusRv5rbEfg7yn/JdnbfsNKr+AuAJjT4Ube5L9/R7sT5FdWmt3r2lm/juGtwd0o4HWnTVuW8T9tDS/EDgbjsb62rv8vUCieYI3nWndGaDFu7jBrW4V6Xi2fXdW0Jfu3a6OZT8e33K6x8Hcb9934ggc75saG8RGQmxo3Pu07uhZ3phAMxrfRiVi0vv2TNY0CXGIltEbi7O0e3nUEBObCjSok/OLco8mkd29zgbH6lKd/J7oLZU=
*/