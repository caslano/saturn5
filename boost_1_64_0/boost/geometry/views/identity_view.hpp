// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_VIEWS_IDENTITY_VIEW_HPP
#define BOOST_GEOMETRY_VIEWS_IDENTITY_VIEW_HPP


#include <boost/range.hpp>


namespace boost { namespace geometry
{

// Silence warning C4512: assignment operator could not be generated
#if defined(_MSC_VER)
#pragma warning(push)
#pragma warning(disable : 4512)
#endif

/*!
\brief View on a range, not modifying anything
\tparam Range original range
\ingroup views
*/
template <typename Range>
struct identity_view
{
    typedef typename boost::range_iterator<Range const>::type const_iterator;
    typedef typename boost::range_iterator<Range>::type iterator;

    explicit inline identity_view(Range& r)
        : m_range(r)
    {}

    inline const_iterator begin() const { return boost::begin(m_range); }
    inline const_iterator end() const { return boost::end(m_range); }

    inline iterator begin() { return boost::begin(m_range); }
    inline iterator end() { return boost::end(m_range); }
private :
    Range& m_range;
};

#if defined(_MSC_VER)
#pragma warning(pop)
#endif

}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_VIEWS_IDENTITY_VIEW_HPP

/* identity_view.hpp
f9e4DthjHPd0r352UtDO3e9znaT8F1jPMvf7b1E/r/2NenWx8lGul9QYb3bZ/h22/y7jatdzayfY32v09/q5rerDrdc6r5+hPM9x/M/Sn3doV8bPsy7Ujx/QbiP7O/udp9yfXWKcfjAiD+e7E23a54JwCt22r87xesj4wzjrknOdXxvdn3CeXZRonDZJ/7/RefwV1u/nBaOu21/v/OB4HNSPbehxXNba3zv0+2c5D5/rOP1K+RY5Xz2uHN03mB5j+1Ybh6xTT523lsy3v6/S/16hfj1lfb93n6bYdr1Tuyu2XbOd94aUh/7ltoPKd7H7Eanq79f9u4J6f7TNfmSozyPq8Zjzs37neKd27Xis+ajj8T31ZGmQTjlTfT/gPHyZcdXH1fuHXL9d5HtzHHflc8lH1J9l2vde/Y/z6D7nz6X7lM866/2bdndAufTb7jHHQ73f/mP96AuWf1C/mej+4q3ax5XakXI6YTtXOW7z9Ov71Pvtr9dvuR7dWK9877e8ucZnrovujfe9EeV+r/qq/m57tX7yhPo/z7j3bOO5ee6j3aDfPWy79lr/ec5Psc7zR5XLFufndPXDep7XHie7nnsqSXuert/4hs9v0S7anS8dz7t/pF9WT64OOe+8YH36jwW2a6H6O/dR3/t2RH7Ka2qQLjOemXZcuSi/Awnq1Xddtzm/HFPfFjhvX/tr9cO4eaf5b7Odm/z71LY89WmPcoqx/lepn+r14Zutz35f02Sc1+14uk4/4rp81oPq+VHnO58f+r56oP5evcrxUF9j9FOzTDdkqs+z9avq7dYN+p0R48VjyvOI8Ybr96XXOx/8Vn1yH+ZC651+vnalHFZ8S7mpP8cy9U9plvOk8qpVL80X832fq6db7N+KDfq7a/WDscr3WePMte6Xfsu42vHd+jP7GfET7v+d+Iz+9XbXVfrz3Zc67pOcD3+gfD+of/iLduP8Oe+A9u1+yl7X84sgnK6dpZ68wfEN6ae8/8hU23WdevNH5dpi+ycb9/xBO3ij+zT279BPXXedo999heV8yX6c5Tg6LhtcLz99lnox03j6745joXamn1yx3/wrff8ux/Vs40r9+eGDyu9+2/2U8duj2kuWccfnjbOXW0+yemx8dttjzjdl2mGn/durHGPc53nYcVbeG/WzSyPxSpL2+qzzZcj2vmA/vu488VH7d7fzxCrLj+xfH9SfWO4R5+tZ3a6z1+k3MsIpWP7evynX11mv43/oC+qTerZff3LNTyzPeXtOk3ruummJ89nkXP2B/vySM/S3Z2oPym/BcddZZ1q+6+2FV+hHHtO/6183O54njAMXxRrHaXfT9hknO85Lr7Od8fr1c7Wzo+qrcciWHuVyl2mc8vT9jerLCu199nTz6ffuS1e+X9NuFhrn17uPqj4fTPHzVPtpP3b7+e53THD94PuTHKeb1I/LzJ9p3KjfnzTTeb52gvu66nfEXr9hf7+jH/2V/dvuetTnd5+lPt7rOLl/seo+/Xmbfq9N/fD+vOe09y7fc/3+YGSevEy9z3VeOdP6Yo1T1P8TxuWHY5zPNxtX9rpeWa9eqdcrXL/scp13y5XqlevYqycbL85z/v6B752nH/mxduv3hY6bb/Zq5eI+76Ix+5/uvHymqe2+b1OQHjSO3JZhe1wfr9mr3uoX9mkPi05Y71zlsU491a8//2f94nLL/b37gNrto/r73b8w7tyl/5+oPkXGw/tH6qzfcm57g36mxL+/VGgftznv2K49s/Wz5+qP1JdJh5SP/nepenhbh3bzeu/rj1Z8z/FxnXntRY7DXvWgRHt9v3bVpv9/o+1bO8F9IftjPQvd1zzq+N9tPavud9xi9JM=
*/