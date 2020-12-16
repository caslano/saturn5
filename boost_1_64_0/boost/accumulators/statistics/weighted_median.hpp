///////////////////////////////////////////////////////////////////////////////
// weighted_median.hpp
//
//  Copyright 2006 Eric Niebler, Olivier Gygi. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_ACCUMULATORS_STATISTICS_WEIGHTED_MEDIAN_HPP_EAN_28_10_2005
#define BOOST_ACCUMULATORS_STATISTICS_WEIGHTED_MEDIAN_HPP_EAN_28_10_2005

#include <boost/mpl/placeholders.hpp>
#include <boost/range/iterator_range.hpp>
#include <boost/accumulators/framework/accumulator_base.hpp>
#include <boost/accumulators/framework/extractor.hpp>
#include <boost/accumulators/numeric/functional.hpp>
#include <boost/accumulators/framework/parameters/sample.hpp>
#include <boost/accumulators/framework/depends_on.hpp>
#include <boost/accumulators/statistics_fwd.hpp>
#include <boost/accumulators/statistics/count.hpp>
#include <boost/accumulators/statistics/median.hpp>
#include <boost/accumulators/statistics/weighted_p_square_quantile.hpp>
#include <boost/accumulators/statistics/weighted_density.hpp>
#include <boost/accumulators/statistics/weighted_p_square_cumul_dist.hpp>

namespace boost { namespace accumulators
{

namespace impl
{
    ///////////////////////////////////////////////////////////////////////////////
    // weighted_median_impl
    //
    /**
        @brief Median estimation for weighted samples based on the \f$P^2\f$ quantile estimator

        The \f$P^2\f$ algorithm for weighted samples is invoked with a quantile probability of 0.5.
    */
    template<typename Sample>
    struct weighted_median_impl
      : accumulator_base
    {
        // for boost::result_of
        typedef typename numeric::functional::fdiv<Sample, std::size_t>::result_type result_type;

        weighted_median_impl(dont_care) {}

        template<typename Args>
        result_type result(Args const &args) const
        {
            return weighted_p_square_quantile_for_median(args);
        }
    };

    ///////////////////////////////////////////////////////////////////////////////
    // with_density_weighted_median_impl
    //
    /**
        @brief Median estimation for weighted samples based on the density estimator

        The algorithm determines the bin in which the \f$0.5*cnt\f$-th sample lies, \f$cnt\f$ being
        the total number of samples. It returns the approximate horizontal position of this sample,
        based on a linear interpolation inside the bin.
    */
    template<typename Sample>
    struct with_density_weighted_median_impl
      : accumulator_base
    {
        typedef typename numeric::functional::fdiv<Sample, std::size_t>::result_type float_type;
        typedef std::vector<std::pair<float_type, float_type> > histogram_type;
        typedef iterator_range<typename histogram_type::iterator> range_type;
        // for boost::result_of
        typedef float_type result_type;

        template<typename Args>
        with_density_weighted_median_impl(Args const &args)
          : sum(numeric::fdiv(args[sample | Sample()], (std::size_t)1))
          , is_dirty(true)
        {
        }

        void operator ()(dont_care)
        {
            this->is_dirty = true;
        }

        template<typename Args>
        result_type result(Args const &args) const
        {
            if (this->is_dirty)
            {
                this->is_dirty = false;

                std::size_t cnt = count(args);
                range_type histogram = weighted_density(args);
                typename range_type::iterator it = histogram.begin();
                while (this->sum < 0.5 * cnt)
                {
                    this->sum += it->second * cnt;
                    ++it;
                }
                --it;
                float_type over = numeric::fdiv(this->sum - 0.5 * cnt, it->second * cnt);
                this->median = it->first * over + (it + 1)->first * ( 1. - over );
            }

            return this->median;
        }

        // make this accumulator serializeable
        template<class Archive>
        void serialize(Archive & ar, const unsigned int file_version)
        { 
            ar & sum;
            ar & is_dirty;
            ar & median;
        }

    private:
        mutable float_type sum;
        mutable bool is_dirty;
        mutable float_type median;
    };

    ///////////////////////////////////////////////////////////////////////////////
    // with_p_square_cumulative_distribution_weighted_median_impl
    //
    /**
        @brief Median estimation for weighted samples based on the \f$P^2\f$ cumulative distribution estimator

        The algorithm determines the first (leftmost) bin with a height exceeding 0.5. It
        returns the approximate horizontal position of where the cumulative distribution
        equals 0.5, based on a linear interpolation inside the bin.
    */
    template<typename Sample, typename Weight>
    struct with_p_square_cumulative_distribution_weighted_median_impl
      : accumulator_base
    {
        typedef typename numeric::functional::multiplies<Sample, Weight>::result_type weighted_sample;
        typedef typename numeric::functional::fdiv<weighted_sample, std::size_t>::result_type float_type;
        typedef std::vector<std::pair<float_type, float_type> > histogram_type;
        typedef iterator_range<typename histogram_type::iterator> range_type;
        // for boost::result_of
        typedef float_type result_type;

        with_p_square_cumulative_distribution_weighted_median_impl(dont_care)
          : is_dirty(true)
        {
        }

        void operator ()(dont_care)
        {
            this->is_dirty = true;
        }

        template<typename Args>
        result_type result(Args const &args) const
        {
            if (this->is_dirty)
            {
                this->is_dirty = false;

                range_type histogram = weighted_p_square_cumulative_distribution(args);
                typename range_type::iterator it = histogram.begin();
                while (it->second < 0.5)
                {
                    ++it;
                }
                float_type over = numeric::fdiv(it->second - 0.5, it->second - (it - 1)->second);
                this->median = it->first * over + (it + 1)->first * ( 1. - over );
            }

            return this->median;
        }
        
        // make this accumulator serializeable
        template<class Archive>
        void serialize(Archive & ar, const unsigned int file_version)
        { 
            ar & is_dirty;
            ar & median;
        }

    private:
        mutable bool is_dirty;
        mutable float_type median;
    };

} // namespace impl

///////////////////////////////////////////////////////////////////////////////
// tag::weighted_median
// tag::with_density_weighted_median
// tag::with_p_square_cumulative_distribution_weighted_median
//
namespace tag
{
    struct weighted_median
      : depends_on<weighted_p_square_quantile_for_median>
    {
        /// INTERNAL ONLY
        ///
        typedef accumulators::impl::weighted_median_impl<mpl::_1> impl;
    };
    struct with_density_weighted_median
      : depends_on<count, weighted_density>
    {
        /// INTERNAL ONLY
        ///
        typedef accumulators::impl::with_density_weighted_median_impl<mpl::_1> impl;
    };
    struct with_p_square_cumulative_distribution_weighted_median
      : depends_on<weighted_p_square_cumulative_distribution>
    {
        /// INTERNAL ONLY
        ///
        typedef accumulators::impl::with_p_square_cumulative_distribution_weighted_median_impl<mpl::_1, mpl::_2> impl;
    };

}

///////////////////////////////////////////////////////////////////////////////
// extract::weighted_median
//
namespace extract
{
    extractor<tag::median> const weighted_median = {};

    BOOST_ACCUMULATORS_IGNORE_GLOBAL(weighted_median)
}

using extract::weighted_median;
// weighted_median(with_p_square_quantile) -> weighted_median
template<>
struct as_feature<tag::weighted_median(with_p_square_quantile)>
{
    typedef tag::weighted_median type;
};

// weighted_median(with_density) -> with_density_weighted_median
template<>
struct as_feature<tag::weighted_median(with_density)>
{
    typedef tag::with_density_weighted_median type;
};

// weighted_median(with_p_square_cumulative_distribution) -> with_p_square_cumulative_distribution_weighted_median
template<>
struct as_feature<tag::weighted_median(with_p_square_cumulative_distribution)>
{
    typedef tag::with_p_square_cumulative_distribution_weighted_median type;
};

}} // namespace boost::accumulators

#endif

/* weighted_median.hpp
eFMWxtgn/D5JuA4ehq+CQcneQYXKoF7eQROUQX28HurOmrtcij2f9Kv+iDvoolxk877LhVUqC1VZY5fLBOu2a/MLi9UeslrbmrW36I6BxdomuFgTpjjpqprV2d78fBaXaMgSoNLB5p29+GDT8duNIo1PqH1G79MDw9TpPn2YsBven5+2k9ma3WKl4VBepd7v//TL+L9gIgxVb0bXX5Ga5RuUiWe6A1fg44kt6Sp6OsDY4JGLv+H4G8HXVDt8k+ibkUxbqgespBw0qwzl0cfqVpyKVMZKhyCz92aglqdp/PGYz6YMVLU5cOHkAX7xF/TSyhA2Sp31LQgF8zL54AXtg+oNbIlBQZP7PGU6pXp2W91d5OBPK8GVQv5hzeA3VAdK8T4ts266PuvIqiHGqXxbk4jlbXNlfG8tvorR10Sbyd2DzVPe15TyKg75A40TrT71p/04yexuiAOwnyMu5LOZ9Jn5VZ71ln0uyxE01d3SmfGttSih+U24tBuaULw/0AScrx4lcxvKPByZHb5HqdCQLOplSOD2IbWIRj5GztC15DbgNGlc5EfAZrsyfnJnSpckWm3Ti3jXbBNbc7UULOsSbb/tMz5pxQVBR7g3NqRtUtPGxZvIXLonf1/QBafzC/GN1C2fqufydwXboCSoawT07RFqPPKbrZ9T/Qv4l/N00Dw6js83gfFzt1f3/0j01hBsRHN4JJK/rm2Gqzemf4CiRXpxXofA2u9yl2HtA0VDeYCMRpVqz6GO1gf3sO7nCkyWn6vASsyc9nP/BLlAkmw0hqq3AhZ7qUtOAqrPaI1HiQD1OYD0gk4QX0PnLF+mHUJcZeZDiHeQV3ybblRfM7N673jUBQNUD6HzBF78nvnyeFYeNKO9noWhG4KYZw6MEiO779UNtYDozVu4lphhZ4jTP62nancSUIPzCaJKHaJbBaIUHaI6tatA9JU56FqHbqv2LiHYpMa1bEuaYC2+HAnYCey0HThlN6CgTrvJi3dIsndIISW0oHyxer4Y/S1ay9jLO2QCheMpYys9uaX+Fsdvvit+8g7p41WmcPsNkC6CZixtZJ1ER5nXD7DQ2jEwO12yUG9AvOGTSfiE1p21yI03MZSQ7zaoj+A7+WKbSbP0vRqZGDiCJoGh4VU7ALuwddoFnPqGHTeHgUoiS2Czp/zAHZhg6dyskqzkS5TycjUOLxmwEQZtUOJKHqCUsyU2D6wyqNA7KNm6bDAI4qulTxEway/SeWlDJqCvwO4hpYV12bDY8j1xrTYiEBN4ieaXtLK0R6iPvNf2Sdvk9bzMB1+ORLWmHpPHFrSJFYTC4gkQ1CL0Jw0jyDJsFyeYPunf9N/fkV5/lDxb0pEHf+3SQ+Nj8Tf/4oT/abvYE/0Rv9YxjF+zdUC4Ef9lk9sY/M2qT7Zm0RecKDAhRhm8os1G0/W5z2qbdfFmAL92bxOwTvMcauFuiakgaJTJPVSjbj1Eu85k/aZyirsz+ZjeNRuVbyyzRco3btjRbPnG9PYB+cb8xHD5xuD/hHzjS+uJyDc6JQRlDkO+1GUO7yccU76x85NaXezw4RfNkW+83CpY1659el3DE44u3xhjqGjkF6dEvmHwN3JdoH+ntw4/aapWn+IWbcPh9hTxoEMzIxpN41POLPZFITJAP+O96lLxQoJOmfoLD80ol5dvTz/oxNA4A0NzgMpJbiszrF5djFZrJgIprY4isb08OlwDyskSWxfPNRwcsYLnutMC5f4+WO7meIPEdpWx0P18hg6Qw49kpd9vOs6z2Ob8AvQROl8T4bZMDBV7O3Sxt3XaXI1lzc9BpLEXVQdZR7TEl0EJ7oY2HESL/7i3NqCt8XFLafxNQQmudK4=
*/