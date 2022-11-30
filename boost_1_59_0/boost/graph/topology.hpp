// Copyright 2009 The Trustees of Indiana University.

// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  Authors: Jeremiah Willcock
//           Douglas Gregor
//           Andrew Lumsdaine
#ifndef BOOST_GRAPH_TOPOLOGY_HPP
#define BOOST_GRAPH_TOPOLOGY_HPP

#include <boost/config/no_tr1/cmath.hpp>
#include <cmath>
#include <boost/random/uniform_01.hpp>
#include <boost/random/linear_congruential.hpp>
#include <boost/math/constants/constants.hpp> // For root_two
#include <boost/algorithm/minmax.hpp>
#include <boost/config.hpp> // For BOOST_STATIC_CONSTANT
#include <boost/math/special_functions/hypot.hpp>

// Classes and concepts to represent points in a space, with distance and move
// operations (used for Gurson-Atun layout), plus other things like bounding
// boxes used for other layout algorithms.

namespace boost
{

/***********************************************************
 * Topologies                                              *
 ***********************************************************/
template < std::size_t Dims > class convex_topology
{
public: // For VisualAge C++
    struct point
    {
        BOOST_STATIC_CONSTANT(std::size_t, dimensions = Dims);
        point() {}
        double& operator[](std::size_t i) { return values[i]; }
        const double& operator[](std::size_t i) const { return values[i]; }

    private:
        double values[Dims];
    };

public: // For VisualAge C++
    struct point_difference
    {
        BOOST_STATIC_CONSTANT(std::size_t, dimensions = Dims);
        point_difference()
        {
            for (std::size_t i = 0; i < Dims; ++i)
                values[i] = 0.;
        }
        double& operator[](std::size_t i) { return values[i]; }
        const double& operator[](std::size_t i) const { return values[i]; }

        friend point_difference operator+(
            const point_difference& a, const point_difference& b)
        {
            point_difference result;
            for (std::size_t i = 0; i < Dims; ++i)
                result[i] = a[i] + b[i];
            return result;
        }

        friend point_difference& operator+=(
            point_difference& a, const point_difference& b)
        {
            for (std::size_t i = 0; i < Dims; ++i)
                a[i] += b[i];
            return a;
        }

        friend point_difference operator-(const point_difference& a)
        {
            point_difference result;
            for (std::size_t i = 0; i < Dims; ++i)
                result[i] = -a[i];
            return result;
        }

        friend point_difference operator-(
            const point_difference& a, const point_difference& b)
        {
            point_difference result;
            for (std::size_t i = 0; i < Dims; ++i)
                result[i] = a[i] - b[i];
            return result;
        }

        friend point_difference& operator-=(
            point_difference& a, const point_difference& b)
        {
            for (std::size_t i = 0; i < Dims; ++i)
                a[i] -= b[i];
            return a;
        }

        friend point_difference operator*(
            const point_difference& a, const point_difference& b)
        {
            point_difference result;
            for (std::size_t i = 0; i < Dims; ++i)
                result[i] = a[i] * b[i];
            return result;
        }

        friend point_difference operator*(const point_difference& a, double b)
        {
            point_difference result;
            for (std::size_t i = 0; i < Dims; ++i)
                result[i] = a[i] * b;
            return result;
        }

        friend point_difference operator*(double a, const point_difference& b)
        {
            point_difference result;
            for (std::size_t i = 0; i < Dims; ++i)
                result[i] = a * b[i];
            return result;
        }

        friend point_difference operator/(
            const point_difference& a, const point_difference& b)
        {
            point_difference result;
            for (std::size_t i = 0; i < Dims; ++i)
                result[i] = (b[i] == 0.) ? 0. : a[i] / b[i];
            return result;
        }

        friend double dot(const point_difference& a, const point_difference& b)
        {
            double result = 0;
            for (std::size_t i = 0; i < Dims; ++i)
                result += a[i] * b[i];
            return result;
        }

    private:
        double values[Dims];
    };

public:
    typedef point point_type;
    typedef point_difference point_difference_type;

    double distance(point a, point b) const
    {
        double dist = 0.;
        for (std::size_t i = 0; i < Dims; ++i)
        {
            double diff = b[i] - a[i];
            dist = boost::math::hypot(dist, diff);
        }
        // Exact properties of the distance are not important, as long as
        // < on what this returns matches real distances; l_2 is used because
        // Fruchterman-Reingold also uses this code and it relies on l_2.
        return dist;
    }

    point move_position_toward(point a, double fraction, point b) const
    {
        point result;
        for (std::size_t i = 0; i < Dims; ++i)
            result[i] = a[i] + (b[i] - a[i]) * fraction;
        return result;
    }

    point_difference difference(point a, point b) const
    {
        point_difference result;
        for (std::size_t i = 0; i < Dims; ++i)
            result[i] = a[i] - b[i];
        return result;
    }

    point adjust(point a, point_difference delta) const
    {
        point result;
        for (std::size_t i = 0; i < Dims; ++i)
            result[i] = a[i] + delta[i];
        return result;
    }

    point pointwise_min(point a, point b) const
    {
        BOOST_USING_STD_MIN();
        point result;
        for (std::size_t i = 0; i < Dims; ++i)
            result[i] = min BOOST_PREVENT_MACRO_SUBSTITUTION(a[i], b[i]);
        return result;
    }

    point pointwise_max(point a, point b) const
    {
        BOOST_USING_STD_MAX();
        point result;
        for (std::size_t i = 0; i < Dims; ++i)
            result[i] = max BOOST_PREVENT_MACRO_SUBSTITUTION(a[i], b[i]);
        return result;
    }

    double norm(point_difference delta) const
    {
        double n = 0.;
        for (std::size_t i = 0; i < Dims; ++i)
            n = boost::math::hypot(n, delta[i]);
        return n;
    }

    double volume(point_difference delta) const
    {
        double n = 1.;
        for (std::size_t i = 0; i < Dims; ++i)
            n *= delta[i];
        return n;
    }
};

template < std::size_t Dims, typename RandomNumberGenerator = minstd_rand >
class hypercube_topology : public convex_topology< Dims >
{
    typedef uniform_01< RandomNumberGenerator, double > rand_t;

public:
    typedef typename convex_topology< Dims >::point_type point_type;
    typedef typename convex_topology< Dims >::point_difference_type
        point_difference_type;

    explicit hypercube_topology(double scaling = 1.0)
    : gen_ptr(new RandomNumberGenerator)
    , rand(new rand_t(*gen_ptr))
    , scaling(scaling)
    {
    }

    hypercube_topology(RandomNumberGenerator& gen, double scaling = 1.0)
    : gen_ptr(), rand(new rand_t(gen)), scaling(scaling)
    {
    }

    point_type random_point() const
    {
        point_type p;
        for (std::size_t i = 0; i < Dims; ++i)
            p[i] = (*rand)() * scaling;
        return p;
    }

    point_type bound(point_type a) const
    {
        BOOST_USING_STD_MIN();
        BOOST_USING_STD_MAX();
        point_type p;
        for (std::size_t i = 0; i < Dims; ++i)
            p[i] = min BOOST_PREVENT_MACRO_SUBSTITUTION(
                scaling, max BOOST_PREVENT_MACRO_SUBSTITUTION(-scaling, a[i]));
        return p;
    }

    double distance_from_boundary(point_type a) const
    {
        BOOST_USING_STD_MIN();
        BOOST_USING_STD_MAX();
#ifndef BOOST_NO_STDC_NAMESPACE
        using std::abs;
#endif
        BOOST_STATIC_ASSERT(Dims >= 1);
        double dist = abs(scaling - a[0]);
        for (std::size_t i = 1; i < Dims; ++i)
            dist = min BOOST_PREVENT_MACRO_SUBSTITUTION(
                dist, abs(scaling - a[i]));
        return dist;
    }

    point_type center() const
    {
        point_type result;
        for (std::size_t i = 0; i < Dims; ++i)
            result[i] = scaling * .5;
        return result;
    }

    point_type origin() const
    {
        point_type result;
        for (std::size_t i = 0; i < Dims; ++i)
            result[i] = 0;
        return result;
    }

    point_difference_type extent() const
    {
        point_difference_type result;
        for (std::size_t i = 0; i < Dims; ++i)
            result[i] = scaling;
        return result;
    }

private:
    shared_ptr< RandomNumberGenerator > gen_ptr;
    shared_ptr< rand_t > rand;
    double scaling;
};

template < typename RandomNumberGenerator = minstd_rand >
class square_topology : public hypercube_topology< 2, RandomNumberGenerator >
{
    typedef hypercube_topology< 2, RandomNumberGenerator > inherited;

public:
    explicit square_topology(double scaling = 1.0) : inherited(scaling) {}

    square_topology(RandomNumberGenerator& gen, double scaling = 1.0)
    : inherited(gen, scaling)
    {
    }
};

template < typename RandomNumberGenerator = minstd_rand >
class rectangle_topology : public convex_topology< 2 >
{
    typedef uniform_01< RandomNumberGenerator, double > rand_t;

public:
    rectangle_topology(double left, double top, double right, double bottom)
    : gen_ptr(new RandomNumberGenerator)
    , rand(new rand_t(*gen_ptr))
    , left(std::min BOOST_PREVENT_MACRO_SUBSTITUTION(left, right))
    , top(std::min BOOST_PREVENT_MACRO_SUBSTITUTION(top, bottom))
    , right(std::max BOOST_PREVENT_MACRO_SUBSTITUTION(left, right))
    , bottom(std::max BOOST_PREVENT_MACRO_SUBSTITUTION(top, bottom))
    {
    }

    rectangle_topology(RandomNumberGenerator& gen, double left, double top,
        double right, double bottom)
    : gen_ptr()
    , rand(new rand_t(gen))
    , left(std::min BOOST_PREVENT_MACRO_SUBSTITUTION(left, right))
    , top(std::min BOOST_PREVENT_MACRO_SUBSTITUTION(top, bottom))
    , right(std::max BOOST_PREVENT_MACRO_SUBSTITUTION(left, right))
    , bottom(std::max BOOST_PREVENT_MACRO_SUBSTITUTION(top, bottom))
    {
    }

    typedef typename convex_topology< 2 >::point_type point_type;
    typedef typename convex_topology< 2 >::point_difference_type
        point_difference_type;

    point_type random_point() const
    {
        point_type p;
        p[0] = (*rand)() * (right - left) + left;
        p[1] = (*rand)() * (bottom - top) + top;
        return p;
    }

    point_type bound(point_type a) const
    {
        BOOST_USING_STD_MIN();
        BOOST_USING_STD_MAX();
        point_type p;
        p[0] = min BOOST_PREVENT_MACRO_SUBSTITUTION(
            right, max BOOST_PREVENT_MACRO_SUBSTITUTION(left, a[0]));
        p[1] = min BOOST_PREVENT_MACRO_SUBSTITUTION(
            bottom, max BOOST_PREVENT_MACRO_SUBSTITUTION(top, a[1]));
        return p;
    }

    double distance_from_boundary(point_type a) const
    {
        BOOST_USING_STD_MIN();
        BOOST_USING_STD_MAX();
#ifndef BOOST_NO_STDC_NAMESPACE
        using std::abs;
#endif
        double dist = abs(left - a[0]);
        dist = min BOOST_PREVENT_MACRO_SUBSTITUTION(dist, abs(right - a[0]));
        dist = min BOOST_PREVENT_MACRO_SUBSTITUTION(dist, abs(top - a[1]));
        dist = min BOOST_PREVENT_MACRO_SUBSTITUTION(dist, abs(bottom - a[1]));
        return dist;
    }

    point_type center() const
    {
        point_type result;
        result[0] = (left + right) / 2.;
        result[1] = (top + bottom) / 2.;
        return result;
    }

    point_type origin() const
    {
        point_type result;
        result[0] = left;
        result[1] = top;
        return result;
    }

    point_difference_type extent() const
    {
        point_difference_type result;
        result[0] = right - left;
        result[1] = bottom - top;
        return result;
    }

private:
    shared_ptr< RandomNumberGenerator > gen_ptr;
    shared_ptr< rand_t > rand;
    double left, top, right, bottom;
};

template < typename RandomNumberGenerator = minstd_rand >
class cube_topology : public hypercube_topology< 3, RandomNumberGenerator >
{
    typedef hypercube_topology< 3, RandomNumberGenerator > inherited;

public:
    explicit cube_topology(double scaling = 1.0) : inherited(scaling) {}

    cube_topology(RandomNumberGenerator& gen, double scaling = 1.0)
    : inherited(gen, scaling)
    {
    }
};

template < std::size_t Dims, typename RandomNumberGenerator = minstd_rand >
class ball_topology : public convex_topology< Dims >
{
    typedef uniform_01< RandomNumberGenerator, double > rand_t;

public:
    typedef typename convex_topology< Dims >::point_type point_type;
    typedef typename convex_topology< Dims >::point_difference_type
        point_difference_type;

    explicit ball_topology(double radius = 1.0)
    : gen_ptr(new RandomNumberGenerator)
    , rand(new rand_t(*gen_ptr))
    , radius(radius)
    {
    }

    ball_topology(RandomNumberGenerator& gen, double radius = 1.0)
    : gen_ptr(), rand(new rand_t(gen)), radius(radius)
    {
    }

    point_type random_point() const
    {
        point_type p;
        double dist_sum;
        do
        {
            dist_sum = 0.0;
            for (std::size_t i = 0; i < Dims; ++i)
            {
                double x = (*rand)() * 2 * radius - radius;
                p[i] = x;
                dist_sum += x * x;
            }
        } while (dist_sum > radius * radius);
        return p;
    }

    point_type bound(point_type a) const
    {
        BOOST_USING_STD_MIN();
        BOOST_USING_STD_MAX();
        double r = 0.;
        for (std::size_t i = 0; i < Dims; ++i)
            r = boost::math::hypot(r, a[i]);
        if (r <= radius)
            return a;
        double scaling_factor = radius / r;
        point_type p;
        for (std::size_t i = 0; i < Dims; ++i)
            p[i] = a[i] * scaling_factor;
        return p;
    }

    double distance_from_boundary(point_type a) const
    {
        double r = 0.;
        for (std::size_t i = 0; i < Dims; ++i)
            r = boost::math::hypot(r, a[i]);
        return radius - r;
    }

    point_type center() const
    {
        point_type result;
        for (std::size_t i = 0; i < Dims; ++i)
            result[i] = 0;
        return result;
    }

    point_type origin() const
    {
        point_type result;
        for (std::size_t i = 0; i < Dims; ++i)
            result[i] = -radius;
        return result;
    }

    point_difference_type extent() const
    {
        point_difference_type result;
        for (std::size_t i = 0; i < Dims; ++i)
            result[i] = 2. * radius;
        return result;
    }

private:
    shared_ptr< RandomNumberGenerator > gen_ptr;
    shared_ptr< rand_t > rand;
    double radius;
};

template < typename RandomNumberGenerator = minstd_rand >
class circle_topology : public ball_topology< 2, RandomNumberGenerator >
{
    typedef ball_topology< 2, RandomNumberGenerator > inherited;

public:
    explicit circle_topology(double radius = 1.0) : inherited(radius) {}

    circle_topology(RandomNumberGenerator& gen, double radius = 1.0)
    : inherited(gen, radius)
    {
    }
};

template < typename RandomNumberGenerator = minstd_rand >
class sphere_topology : public ball_topology< 3, RandomNumberGenerator >
{
    typedef ball_topology< 3, RandomNumberGenerator > inherited;

public:
    explicit sphere_topology(double radius = 1.0) : inherited(radius) {}

    sphere_topology(RandomNumberGenerator& gen, double radius = 1.0)
    : inherited(gen, radius)
    {
    }
};

template < typename RandomNumberGenerator = minstd_rand > class heart_topology
{
    // Heart is defined as the union of three shapes:
    // Square w/ corners (+-1000, -1000), (0, 0), (0, -2000)
    // Circle centered at (-500, -500) radius 500*sqrt(2)
    // Circle centered at (500, -500) radius 500*sqrt(2)
    // Bounding box (-1000, -2000) - (1000, 500*(sqrt(2) - 1))

    struct point
    {
        point()
        {
            values[0] = 0.0;
            values[1] = 0.0;
        }
        point(double x, double y)
        {
            values[0] = x;
            values[1] = y;
        }

        double& operator[](std::size_t i) { return values[i]; }
        double operator[](std::size_t i) const { return values[i]; }

    private:
        double values[2];
    };

    bool in_heart(point p) const
    {
#ifndef BOOST_NO_STDC_NAMESPACE
        using std::abs;
#endif

        if (p[1] < abs(p[0]) - 2000)
            return false; // Bottom
        if (p[1] <= -1000)
            return true; // Diagonal of square
        if (boost::math::hypot(p[0] - -500, p[1] - -500)
            <= 500. * boost::math::constants::root_two< double >())
            return true; // Left circle
        if (boost::math::hypot(p[0] - 500, p[1] - -500)
            <= 500. * boost::math::constants::root_two< double >())
            return true; // Right circle
        return false;
    }

    bool segment_within_heart(point p1, point p2) const
    {
        // Assumes that p1 and p2 are within the heart
        if ((p1[0] < 0) == (p2[0] < 0))
            return true; // Same side of symmetry line
        if (p1[0] == p2[0])
            return true; // Vertical
        double slope = (p2[1] - p1[1]) / (p2[0] - p1[0]);
        double intercept = p1[1] - p1[0] * slope;
        if (intercept > 0)
            return false; // Crosses between circles
        return true;
    }

    typedef uniform_01< RandomNumberGenerator, double > rand_t;

public:
    typedef point point_type;

    heart_topology()
    : gen_ptr(new RandomNumberGenerator), rand(new rand_t(*gen_ptr))
    {
    }

    heart_topology(RandomNumberGenerator& gen)
    : gen_ptr(), rand(new rand_t(gen))
    {
    }

    point random_point() const
    {
        point result;
        do
        {
            result[0] = (*rand)()
                    * (1000
                        + 1000 * boost::math::constants::root_two< double >())
                - (500 + 500 * boost::math::constants::root_two< double >());
            result[1] = (*rand)()
                    * (2000
                        + 500
                            * (boost::math::constants::root_two< double >()
                                - 1))
                - 2000;
        } while (!in_heart(result));
        return result;
    }

    // Not going to provide clipping to bounding region or distance from
    // boundary

    double distance(point a, point b) const
    {
        if (segment_within_heart(a, b))
        {
            // Straight line
            return boost::math::hypot(b[0] - a[0], b[1] - a[1]);
        }
        else
        {
            // Straight line bending around (0, 0)
            return boost::math::hypot(a[0], a[1])
                + boost::math::hypot(b[0], b[1]);
        }
    }

    point move_position_toward(point a, double fraction, point b) const
    {
        if (segment_within_heart(a, b))
        {
            // Straight line
            return point(a[0] + (b[0] - a[0]) * fraction,
                a[1] + (b[1] - a[1]) * fraction);
        }
        else
        {
            double distance_to_point_a = boost::math::hypot(a[0], a[1]);
            double distance_to_point_b = boost::math::hypot(b[0], b[1]);
            double location_of_point = distance_to_point_a
                / (distance_to_point_a + distance_to_point_b);
            if (fraction < location_of_point)
                return point(a[0] * (1 - fraction / location_of_point),
                    a[1] * (1 - fraction / location_of_point));
            else
                return point(b[0]
                        * ((fraction - location_of_point)
                            / (1 - location_of_point)),
                    b[1]
                        * ((fraction - location_of_point)
                            / (1 - location_of_point)));
        }
    }

private:
    shared_ptr< RandomNumberGenerator > gen_ptr;
    shared_ptr< rand_t > rand;
};

} // namespace boost

#endif // BOOST_GRAPH_TOPOLOGY_HPP

/* topology.hpp
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
*/