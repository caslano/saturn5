// Copyright 2004-2006 The Trustees of Indiana University.

// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  Authors: Douglas Gregor
//           Andrew Lumsdaine
#ifndef BOOST_GRAPH_PLOD_GENERATOR_HPP
#define BOOST_GRAPH_PLOD_GENERATOR_HPP

#include <iterator>
#include <utility>
#include <boost/random/uniform_int.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/graph/graph_traits.hpp>
#include <vector>
#include <map>
#include <boost/config/no_tr1/cmath.hpp>
#include <boost/mpl/if.hpp>

namespace boost
{
template < typename RandomGenerator > class out_directed_plod_iterator
{
public:
    typedef std::forward_iterator_tag iterator_category;
    typedef std::pair< std::size_t, std::size_t > value_type;
    typedef const value_type& reference;
    typedef const value_type* pointer;
    typedef std::ptrdiff_t difference_type;

    out_directed_plod_iterator() : gen(0), at_end(true) {}

    out_directed_plod_iterator(RandomGenerator& gen, std::size_t n,
        double alpha, double beta, bool allow_self_loops)
    : gen(&gen)
    , n(n)
    , alpha(alpha)
    , beta(beta)
    , allow_self_loops(allow_self_loops)
    , at_end(false)
    , degree(0)
    , current(0, 0)
    {
        using std::pow;

        uniform_int< std::size_t > x(0, n - 1);
        std::size_t xv = x(gen);
        degree = (xv == 0 ? 0 : std::size_t(beta * pow(xv, -alpha)));
    }

    reference operator*() const { return current; }
    pointer operator->() const { return &current; }

    out_directed_plod_iterator& operator++()
    {
        using std::pow;

        uniform_int< std::size_t > x(0, n - 1);

        // Continue stepping through source nodes until the
        // (out)degree is > 0
        while (degree == 0)
        {
            // Step to the next source node. If we've gone past the
            // number of nodes we're responsible for, we're done.
            if (++current.first >= n)
            {
                at_end = true;
                return *this;
            }

            std::size_t xv = x(*gen);
            degree = (xv == 0 ? 0 : std::size_t(beta * pow(xv, -alpha)));
        }

        do
        {
            current.second = x(*gen);
        } while (current.first == current.second && !allow_self_loops);
        --degree;

        return *this;
    }

    out_directed_plod_iterator operator++(int)
    {
        out_directed_plod_iterator temp(*this);
        ++(*this);
        return temp;
    }

    bool operator==(const out_directed_plod_iterator& other) const
    {
        return at_end == other.at_end;
    }

    bool operator!=(const out_directed_plod_iterator& other) const
    {
        return !(*this == other);
    }

private:
    RandomGenerator* gen;
    std::size_t n;
    double alpha;
    double beta;
    bool allow_self_loops;
    bool at_end;
    std::size_t degree;
    value_type current;
};

template < typename RandomGenerator > class undirected_plod_iterator
{
    typedef std::vector< std::pair< std::size_t, std::size_t > > out_degrees_t;

public:
    typedef std::input_iterator_tag iterator_category;
    typedef std::pair< std::size_t, std::size_t > value_type;
    typedef const value_type& reference;
    typedef const value_type* pointer;
    typedef std::ptrdiff_t difference_type;

    undirected_plod_iterator()
    : gen(0), out_degrees(), degrees_left(0), allow_self_loops(false)
    {
    }

    undirected_plod_iterator(RandomGenerator& gen, std::size_t n, double alpha,
        double beta, bool allow_self_loops = false)
    : gen(&gen)
    , n(n)
    , out_degrees(new out_degrees_t)
    , degrees_left(0)
    , allow_self_loops(allow_self_loops)
    {
        using std::pow;

        uniform_int< std::size_t > x(0, n - 1);
        for (std::size_t i = 0; i != n; ++i)
        {
            std::size_t xv = x(gen);
            std::size_t degree
                = (xv == 0 ? 0 : std::size_t(beta * pow(xv, -alpha)));
            if (degree == 0)
                degree = 1;
            else if (degree >= n)
                degree = n - 1;
            out_degrees->push_back(std::make_pair(i, degree));
            degrees_left += degree;
        }

        next();
    }

    reference operator*() const { return current; }
    pointer operator->() const { return &current; }

    undirected_plod_iterator& operator++()
    {
        next();
        return *this;
    }

    undirected_plod_iterator operator++(int)
    {
        undirected_plod_iterator temp(*this);
        ++(*this);
        return temp;
    }

    bool operator==(const undirected_plod_iterator& other) const
    {
        return degrees_left == other.degrees_left;
    }

    bool operator!=(const undirected_plod_iterator& other) const
    {
        return !(*this == other);
    }

private:
    void next()
    {
        std::size_t source, target;
        while (true)
        {
            /* We may get to the point where we can't actually find any
               new edges, so we just add some random edge and set the
               degrees left = 0 to signal termination. */
            if (out_degrees->size() < 2)
            {
                uniform_int< std::size_t > x(0, n - 1);
                current.first = x(*gen);
                do
                {
                    current.second = x(*gen);
                } while (current.first == current.second && !allow_self_loops);
                degrees_left = 0;
                out_degrees->clear();
                return;
            }

            uniform_int< std::size_t > x(0, out_degrees->size() - 1);

            // Select source vertex
            source = x(*gen);
            if ((*out_degrees)[source].second == 0)
            {
                (*out_degrees)[source] = out_degrees->back();
                out_degrees->pop_back();
                continue;
            }

            // Select target vertex
            target = x(*gen);
            if ((*out_degrees)[target].second == 0)
            {
                (*out_degrees)[target] = out_degrees->back();
                out_degrees->pop_back();
                continue;
            }
            else if (source != target
                || (allow_self_loops && (*out_degrees)[source].second > 2))
            {
                break;
            }
        }

        // Update degree counts
        --(*out_degrees)[source].second;
        --degrees_left;
        --(*out_degrees)[target].second;
        --degrees_left;
        current.first = (*out_degrees)[source].first;
        current.second = (*out_degrees)[target].first;
    }

    RandomGenerator* gen;
    std::size_t n;
    shared_ptr< out_degrees_t > out_degrees;
    std::size_t degrees_left;
    bool allow_self_loops;
    value_type current;
};

template < typename RandomGenerator, typename Graph >
class plod_iterator
: public mpl::if_<
      is_convertible< typename graph_traits< Graph >::directed_category,
          directed_tag >,
      out_directed_plod_iterator< RandomGenerator >,
      undirected_plod_iterator< RandomGenerator > >::type
{
    typedef typename mpl::if_<
        is_convertible< typename graph_traits< Graph >::directed_category,
            directed_tag >,
        out_directed_plod_iterator< RandomGenerator >,
        undirected_plod_iterator< RandomGenerator > >::type inherited;

public:
    plod_iterator() : inherited() {}

    plod_iterator(RandomGenerator& gen, std::size_t n, double alpha,
        double beta, bool allow_self_loops = false)
    : inherited(gen, n, alpha, beta, allow_self_loops)
    {
    }
};

} // end namespace boost

#endif // BOOST_GRAPH_PLOD_GENERATOR_HPP

/* plod_generator.hpp
X0fVXxfVX7jqL0L1F2nTX/b10vuLUv31VP31Uv3Fqf56q/762PQX8pO5v8VP6a+f6q+/6m+wms8kHInJmINDbLZPserv46dsH76GMt8bn2B5NNEuCR1wHTrje+iCe1R6n0xb+y/4U+nb/7bq9y764X2MwD87mLf/zzgHf8ElKr1Ups39ZxOxN8z9f6T6L4Npqv89LEct3It18KCaj0M4Bj/GsSr/JTyu9rvPcDV+gu/iYdwry63j1rhZ+rjFatwTatyv1Lhn1bhfy3HJV+OWqHEvqnHPqXG/UeOWqHFjiZtq3M1qXFfsosat4CTyq2BFrI5VsSdWw5exJr6CtXC9TFvXp+CWvh/81fr8oNbnqlqfP6n1uYF5eAvHq/xp+ABn4M+4VtvOuBPvYJFWrs8jcds87idPGfehGveRGtfRyTyuE+ahC05Q+dOxLM5EL3wDXfE9dMMDqlw/L90xj/v7p+yXY9m/GuDz2Bh/h7E4Caeo9ALMx4X4Em7HyQ7W/sXd0vtPU/0PVf2PUP2PlP2TVv1nqf6zVf+jbPov+hv9n1D9n1T9n1H9fyX7J636/0b1f171/7VN//n3zP1/8JT+X3A09/+io7n/GRiLM/EllZ6Pc/BlnKvOE7PUdh+vzf99B/Wax9y/Jz9nqv6HqvPYMHUey8JEzMZZmIMrMBePYh4W41j8Qesfr+EE/Bmfx8cybR4/mYj9s3n8w2r93DFBjf8K81AbF2FdXIaJ+DqOwuXq/LQC1+Eq3ICr8aBMW4/XGg/M49R/yvEaxP5YFuthea0OVsSGGIDB+KxKB2IDJ2u/sarfhU/pdwbj19Tm28Hcbi5G4jzMwfmYhwtwnkrrrzdUv1Oest3/oM7Xl9X5+gq2wR8wFa/iCLyGY1X6eZXWj/efzf0fesrx/oo63hep432ZOs+8jrnavOPzMt88/2txOr6BBbgCd+BK3C/LreN2/KX0cdercTeocbeocd9R426V45Kvxn1Pjfu+GnebGrdQjivL9e3k/Wvp2+kNtZ3Wqe20UW2nTWo7bVbb6S25nWRa77fgb/T7jup3m+p3u+p3h+p3p+r3Pdkvab1fy3e3M+dP6XeX6vcD1e9ejMJ9OB7340QswiUybe23+G/0e0j1+4nq96jq95jq91PV73HZL2nVb5FQ3xGuvqc60YFrn7Y+qt+5nMbK4ctYRZtHrIuvYDQuwnR8FSfhYiRPLMEtuBQ/xuV4DlfieVwtzOOvxT/jm/gE16Grif0Jy+EGrIQbsTpuwrq4GTuZ5PKo9SAel74eDibzerhgFXwW66IbRqM7pqMHTsIyuAg9cQt6mczr4WMyr0d5PI8VTebx/U3m9QgwmdfjGZN5PapgOayKlbAaVkdCrkcNk1wPlse6HvK7qDH8KesRqrZHa7U9EtT2eE5tj7aYhu2EeXu3x4XYATdjGH6EXfAr7Ipfa3OGN7AH3sWe+BCj0YnliEFPjMUK2AurYBzWxnjsgAlqe+Tr37ssv89Z7q8NtesMav9uljGf937GKPwFR+Cv+Dw+xKX4CAvxCd5CB0+R34I+HJH5kekYlV6NTngcXbEYK2JFB7YPVsYq2B6rYUd8FntiII7DujgLnXAV1sczGIwNHFkH7IshOAib4BRshpuwOX6EoXgHW2J1J9YfW2NrjME2mIZtcTq2x7exA36MHdHkzHbC2tgVu2MEjsUeOAejcA32xG0YjSXIfOjnDfndpHj6KeeNhmXM18dGWBcbq+0SglqdprgEQ/ENbFHG3O8y/bs15TlG9huiXR/V9m2qXj83w/rYEpsI6mFLbONk7r+tej3aDmPwIxyKHXE2huF87KJef3bDUxiF5zEGv8NeeBEj8RI=
*/