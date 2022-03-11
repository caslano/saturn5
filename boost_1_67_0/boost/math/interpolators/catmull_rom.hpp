// Copyright Nick Thompson, 2017
// Use, modification and distribution are subject to the
// Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

// This computes the Catmull-Rom spline from a list of points.

#ifndef BOOST_MATH_INTERPOLATORS_CATMULL_ROM
#define BOOST_MATH_INTERPOLATORS_CATMULL_ROM

#include <cmath>
#include <vector>
#include <algorithm>
#include <iterator>
#include <stdexcept>
#include <boost/config.hpp>

namespace std_workaround {

#if defined(__cpp_lib_nonmember_container_access) || (defined(BOOST_MSVC) && (BOOST_MSVC >= 1900))
   using std::size;
#else
   template <class C>
   inline BOOST_CONSTEXPR std::size_t size(const C& c)
   {
      return c.size();
   }
   template <class T, std::size_t N>
   inline BOOST_CONSTEXPR std::size_t size(const T(&array)[N]) BOOST_NOEXCEPT
   {
      return N;
   }
#endif
}

namespace boost{ namespace math{

    namespace detail
    {
        template<class Point>
        typename Point::value_type alpha_distance(Point const & p1, Point const & p2, typename Point::value_type alpha)
        {
            using std::pow;
            using std_workaround::size;
            typename Point::value_type dsq = 0;
            for (size_t i = 0; i < size(p1); ++i)
            {
                typename Point::value_type dx = p1[i] - p2[i];
                dsq += dx*dx;
            }
            return pow(dsq, alpha/2);
        }
    }

template <class Point, class RandomAccessContainer = std::vector<Point> >
class catmull_rom
{
   typedef typename Point::value_type value_type;
public:

    catmull_rom(RandomAccessContainer&& points, bool closed = false, value_type alpha = (value_type) 1/ (value_type) 2);

    catmull_rom(std::initializer_list<Point> l, bool closed = false, value_type alpha = (value_type) 1/ (value_type) 2) : catmull_rom<Point, RandomAccessContainer>(RandomAccessContainer(l), closed, alpha) {}

    value_type max_parameter() const
    {
        return m_max_s;
    }

    value_type parameter_at_point(size_t i) const
    {
        return m_s[i+1];
    }

    Point operator()(const value_type s) const;

    Point prime(const value_type s) const;

    RandomAccessContainer&& get_points()
    {
        return std::move(m_pnts);
    }

private:
    RandomAccessContainer m_pnts;
    std::vector<value_type> m_s;
    value_type m_max_s;
};

template<class Point, class RandomAccessContainer >
catmull_rom<Point, RandomAccessContainer>::catmull_rom(RandomAccessContainer&& points, bool closed, typename Point::value_type alpha) : m_pnts(std::move(points))
{
    std::size_t num_pnts = m_pnts.size();
    //std::cout << "Number of points = " << num_pnts << "\n";
    if (num_pnts < 4)
    {
        throw std::domain_error("The Catmull-Rom curve requires at least 4 points.");
    }
    if (alpha < 0 || alpha > 1)
    {
        throw std::domain_error("The parametrization alpha must be in the range [0,1].");
    }

    using std::abs;
    m_s.resize(num_pnts+3);
    m_pnts.resize(num_pnts+3);
    //std::cout << "Number of points now = " << m_pnts.size() << "\n";

    m_pnts[num_pnts+1] = m_pnts[0];
    m_pnts[num_pnts+2] = m_pnts[1];

    auto tmp = m_pnts[num_pnts-1];
    for (std::ptrdiff_t i = num_pnts-1; i >= 0; --i)
    {
        m_pnts[i+1] = m_pnts[i];
    }
    m_pnts[0] = tmp;

    m_s[0] = -detail::alpha_distance<Point>(m_pnts[0], m_pnts[1], alpha);
    if (abs(m_s[0]) < std::numeric_limits<typename Point::value_type>::epsilon())
    {
        throw std::domain_error("The first and last point should not be the same.\n");
    }
    m_s[1] = 0;
    for (size_t i = 2; i < m_s.size(); ++i)
    {
        typename Point::value_type d = detail::alpha_distance<Point>(m_pnts[i], m_pnts[i-1], alpha);
        if (abs(d) < std::numeric_limits<typename Point::value_type>::epsilon())
        {
            throw std::domain_error("The control points of the Catmull-Rom curve are too close together; this will lead to ill-conditioning.\n");
        }
        m_s[i] = m_s[i-1] + d;
    }
    if(closed)
    {
        m_max_s = m_s[num_pnts+1];
    }
    else
    {
        m_max_s = m_s[num_pnts];
    }
}


template<class Point, class RandomAccessContainer >
Point catmull_rom<Point, RandomAccessContainer>::operator()(const typename Point::value_type s) const
{
    using std_workaround::size;
    if (s < 0 || s > m_max_s)
    {
        throw std::domain_error("Parameter outside bounds.");
    }
    auto it = std::upper_bound(m_s.begin(), m_s.end(), s);
    //Now *it >= s. We want the index such that m_s[i] <= s < m_s[i+1]:
    size_t i = std::distance(m_s.begin(), it - 1);

    // Only denom21 is used twice:
    typename Point::value_type denom21 = 1/(m_s[i+1] - m_s[i]);
    typename Point::value_type s0s = m_s[i-1] - s;
    typename Point::value_type s1s = m_s[i] - s;
    typename Point::value_type s2s = m_s[i+1] - s;
    typename Point::value_type s3s = m_s[i+2] - s;

    Point A1_or_A3;
    typename Point::value_type denom = 1/(m_s[i] - m_s[i-1]);
    for(size_t j = 0; j < size(m_pnts[0]); ++j)
    {
        A1_or_A3[j] = denom*(s1s*m_pnts[i-1][j] - s0s*m_pnts[i][j]);
    }

    Point A2_or_B2;
    for(size_t j = 0; j < size(m_pnts[0]); ++j)
    {
        A2_or_B2[j] = denom21*(s2s*m_pnts[i][j] - s1s*m_pnts[i+1][j]);
    }

    Point B1_or_C;
    denom = 1/(m_s[i+1] - m_s[i-1]);
    for(size_t j = 0; j < size(m_pnts[0]); ++j)
    {
        B1_or_C[j] = denom*(s2s*A1_or_A3[j] - s0s*A2_or_B2[j]);
    }

    denom = 1/(m_s[i+2] - m_s[i+1]);
    for(size_t j = 0; j < size(m_pnts[0]); ++j)
    {
        A1_or_A3[j] = denom*(s3s*m_pnts[i+1][j] - s2s*m_pnts[i+2][j]);
    }

    Point B2;
    denom = 1/(m_s[i+2] - m_s[i]);
    for(size_t j = 0; j < size(m_pnts[0]); ++j)
    {
        B2[j] = denom*(s3s*A2_or_B2[j] - s1s*A1_or_A3[j]);
    }

    for(size_t j = 0; j < size(m_pnts[0]); ++j)
    {
        B1_or_C[j] = denom21*(s2s*B1_or_C[j] - s1s*B2[j]);
    }

    return B1_or_C;
}

template<class Point, class RandomAccessContainer >
Point catmull_rom<Point, RandomAccessContainer>::prime(const typename Point::value_type s) const
{
    using std_workaround::size;
    // https://math.stackexchange.com/questions/843595/how-can-i-calculate-the-derivative-of-a-catmull-rom-spline-with-nonuniform-param
    // http://denkovacs.com/2016/02/catmull-rom-spline-derivatives/
    if (s < 0 || s > m_max_s)
    {
        throw std::domain_error("Parameter outside bounds.\n");
    }
    auto it = std::upper_bound(m_s.begin(), m_s.end(), s);
    //Now *it >= s. We want the index such that m_s[i] <= s < m_s[i+1]:
    size_t i = std::distance(m_s.begin(), it - 1);
    Point A1;
    typename Point::value_type denom = 1/(m_s[i] - m_s[i-1]);
    typename Point::value_type k1 = (m_s[i]-s)*denom;
    typename Point::value_type k2 = (s - m_s[i-1])*denom;
    for (size_t j = 0; j < size(m_pnts[0]); ++j)
    {
        A1[j] = k1*m_pnts[i-1][j] + k2*m_pnts[i][j];
    }

    Point A1p;
    for (size_t j = 0; j < size(m_pnts[0]); ++j)
    {
        A1p[j] = denom*(m_pnts[i][j] - m_pnts[i-1][j]);
    }

    Point A2;
    denom = 1/(m_s[i+1] - m_s[i]);
    k1 = (m_s[i+1]-s)*denom;
    k2 = (s - m_s[i])*denom;
    for (size_t j = 0; j < size(m_pnts[0]); ++j)
    {
        A2[j] = k1*m_pnts[i][j] + k2*m_pnts[i+1][j];
    }

    Point A2p;
    for (size_t j = 0; j < size(m_pnts[0]); ++j)
    {
        A2p[j] = denom*(m_pnts[i+1][j] - m_pnts[i][j]);
    }


    Point B1;
    for (size_t j = 0; j < size(m_pnts[0]); ++j)
    {
        B1[j] = k1*A1[j] + k2*A2[j];
    }

    Point A3;
    denom = 1/(m_s[i+2] - m_s[i+1]);
    k1 = (m_s[i+2]-s)*denom;
    k2 = (s - m_s[i+1])*denom;
    for (size_t j = 0; j < size(m_pnts[0]); ++j)
    {
        A3[j] = k1*m_pnts[i+1][j] + k2*m_pnts[i+2][j];
    }

    Point A3p;
    for (size_t j = 0; j < size(m_pnts[0]); ++j)
    {
        A3p[j] = denom*(m_pnts[i+2][j] - m_pnts[i+1][j]);
    }

    Point B2;
    denom = 1/(m_s[i+2] - m_s[i]);
    k1 = (m_s[i+2]-s)*denom;
    k2 = (s - m_s[i])*denom;
    for (size_t j = 0; j < size(m_pnts[0]); ++j)
    {
        B2[j] = k1*A2[j] + k2*A3[j];
    }

    Point B1p;
    denom = 1/(m_s[i+1] - m_s[i-1]);
    for (size_t j = 0; j < size(m_pnts[0]); ++j)
    {
        B1p[j] = denom*(A2[j] - A1[j] + (m_s[i+1]- s)*A1p[j] + (s-m_s[i-1])*A2p[j]);
    }

    Point B2p;
    denom = 1/(m_s[i+2] - m_s[i]);
    for (size_t j = 0; j < size(m_pnts[0]); ++j)
    {
        B2p[j] = denom*(A3[j] - A2[j] + (m_s[i+2] - s)*A2p[j] + (s - m_s[i])*A3p[j]);
    }

    Point Cp;
    denom = 1/(m_s[i+1] - m_s[i]);
    for (size_t j = 0; j < size(m_pnts[0]); ++j)
    {
        Cp[j] = denom*(B2[j] - B1[j] + (m_s[i+1] - s)*B1p[j] + (s - m_s[i])*B2p[j]);
    }
    return Cp;
}


}}
#endif

/* catmull_rom.hpp
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
*/