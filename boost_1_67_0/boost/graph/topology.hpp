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