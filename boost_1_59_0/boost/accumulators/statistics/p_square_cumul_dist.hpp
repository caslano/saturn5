///////////////////////////////////////////////////////////////////////////////
// p_square_cumulative_distribution.hpp
//
//  Copyright 2005 Daniel Egloff, Olivier Gygi. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_ACCUMULATORS_STATISTICS_P_SQUARE_CUMUL_DIST_HPP_DE_01_01_2006
#define BOOST_ACCUMULATORS_STATISTICS_P_SQUARE_CUMUL_DIST_HPP_DE_01_01_2006

#include <vector>
#include <functional>
#include <boost/parameter/keyword.hpp>
#include <boost/range.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/accumulators/accumulators_fwd.hpp>
#include <boost/accumulators/framework/accumulator_base.hpp>
#include <boost/accumulators/framework/extractor.hpp>
#include <boost/accumulators/numeric/functional.hpp>
#include <boost/accumulators/framework/parameters/sample.hpp>
#include <boost/accumulators/statistics_fwd.hpp>
#include <boost/accumulators/statistics/count.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/utility.hpp>

namespace boost { namespace accumulators
{
///////////////////////////////////////////////////////////////////////////////
// num_cells named parameter
//
BOOST_PARAMETER_NESTED_KEYWORD(tag, p_square_cumulative_distribution_num_cells, num_cells)

BOOST_ACCUMULATORS_IGNORE_GLOBAL(p_square_cumulative_distribution_num_cells)

namespace impl
{
    ///////////////////////////////////////////////////////////////////////////////
    // p_square_cumulative_distribution_impl
    //  cumulative_distribution calculation (as histogram)
    /**
        @brief Histogram calculation of the cumulative distribution with the \f$P^2\f$ algorithm

        A histogram of the sample cumulative distribution is computed dynamically without storing samples
        based on the \f$ P^2 \f$ algorithm. The returned histogram has a specifiable amount (num_cells)
        equiprobable (and not equal-sized) cells.

        For further details, see

        R. Jain and I. Chlamtac, The P^2 algorithm for dynamic calculation of quantiles and
        histograms without storing observations, Communications of the ACM,
        Volume 28 (October), Number 10, 1985, p. 1076-1085.

        @param p_square_cumulative_distribution_num_cells.
    */
    template<typename Sample>
    struct p_square_cumulative_distribution_impl
      : accumulator_base
    {
        typedef typename numeric::functional::fdiv<Sample, std::size_t>::result_type float_type;
        typedef std::vector<float_type> array_type;
        typedef std::vector<std::pair<float_type, float_type> > histogram_type;
        // for boost::result_of
        typedef iterator_range<typename histogram_type::iterator> result_type;

        template<typename Args>
        p_square_cumulative_distribution_impl(Args const &args)
          : num_cells(args[p_square_cumulative_distribution_num_cells])
          , heights(num_cells + 1)
          , actual_positions(num_cells + 1)
          , desired_positions(num_cells + 1)
          , positions_increments(num_cells + 1)
          , histogram(num_cells + 1)
          , is_dirty(true)
        {
            std::size_t b = this->num_cells;

            for (std::size_t i = 0; i < b + 1; ++i)
            {
                this->actual_positions[i] = i + 1.;
                this->desired_positions[i] = i + 1.;
                this->positions_increments[i] = numeric::fdiv(i, b);
            }
        }

        template<typename Args>
        void operator ()(Args const &args)
        {
            this->is_dirty = true;

            std::size_t cnt = count(args);
            std::size_t sample_cell = 1; // k
            std::size_t b = this->num_cells;

            // accumulate num_cells + 1 first samples
            if (cnt <= b + 1)
            {
                this->heights[cnt - 1] = args[sample];

                // complete the initialization of heights by sorting
                if (cnt == b + 1)
                {
                    std::sort(this->heights.begin(), this->heights.end());
                }
            }
            else
            {
                // find cell k such that heights[k-1] <= args[sample] < heights[k] and adjust extreme values
                if (args[sample] < this->heights[0])
                {
                    this->heights[0] = args[sample];
                    sample_cell = 1;
                }
                else if (this->heights[b] <= args[sample])
                {
                    this->heights[b] = args[sample];
                    sample_cell = b;
                }
                else
                {
                    typename array_type::iterator it;
                    it = std::upper_bound(
                        this->heights.begin()
                      , this->heights.end()
                      , args[sample]
                    );

                    sample_cell = std::distance(this->heights.begin(), it);
                }

                // increment positions of markers above sample_cell
                for (std::size_t i = sample_cell; i < b + 1; ++i)
                {
                    ++this->actual_positions[i];
                }

                // update desired position of markers 2 to num_cells + 1
                // (desired position of first marker is always 1)
                for (std::size_t i = 1; i < b + 1; ++i)
                {
                    this->desired_positions[i] += this->positions_increments[i];
                }

                // adjust heights of markers 2 to num_cells if necessary
                for (std::size_t i = 1; i < b; ++i)
                {
                    // offset to desire position
                    float_type d = this->desired_positions[i] - this->actual_positions[i];

                    // offset to next position
                    float_type dp = this->actual_positions[i + 1] - this->actual_positions[i];

                    // offset to previous position
                    float_type dm = this->actual_positions[i - 1] - this->actual_positions[i];

                    // height ds
                    float_type hp = (this->heights[i + 1] - this->heights[i]) / dp;
                    float_type hm = (this->heights[i - 1] - this->heights[i]) / dm;

                    if ( ( d >= 1. && dp > 1. ) || ( d <= -1. && dm < -1. ) )
                    {
                        short sign_d = static_cast<short>(d / std::abs(d));

                        // try adjusting heights[i] using p-squared formula
                        float_type h = this->heights[i] + sign_d / (dp - dm) * ( (sign_d - dm) * hp + (dp - sign_d) * hm );

                        if ( this->heights[i - 1] < h && h < this->heights[i + 1] )
                        {
                            this->heights[i] = h;
                        }
                        else
                        {
                            // use linear formula
                            if (d>0)
                            {
                                this->heights[i] += hp;
                            }
                            if (d<0)
                            {
                                this->heights[i] -= hm;
                            }
                        }
                        this->actual_positions[i] += sign_d;
                    }
                }
            }
        }

        template<typename Args>
        result_type result(Args const &args) const
        {
            if (this->is_dirty)
            {
                this->is_dirty = false;

                // creates a vector of std::pair where each pair i holds
                // the values heights[i] (x-axis of histogram) and
                // actual_positions[i] / cnt (y-axis of histogram)

                std::size_t cnt = count(args);

                for (std::size_t i = 0; i < this->histogram.size(); ++i)
                {
                    this->histogram[i] = std::make_pair(this->heights[i], numeric::fdiv(this->actual_positions[i], cnt));
                }
            }
            //return histogram;
            return make_iterator_range(this->histogram);
        }
    
        // make this accumulator serializeable
        // TODO split to save/load and check on parameters provided in ctor
        template<class Archive>
        void serialize(Archive & ar, const unsigned int file_version)
        {
            ar & num_cells;
            ar & heights;
            ar & actual_positions;
            ar & desired_positions;
            ar & positions_increments;
            ar & histogram;
            ar & is_dirty; 
        }

    private:
        std::size_t num_cells;            // number of cells b
        array_type  heights;              // q_i
        array_type  actual_positions;     // n_i
        array_type  desired_positions;    // n'_i
        array_type  positions_increments; // dn'_i
        mutable histogram_type histogram; // histogram
        mutable bool is_dirty;
    };

} // namespace detail

///////////////////////////////////////////////////////////////////////////////
// tag::p_square_cumulative_distribution
//
namespace tag
{
    struct p_square_cumulative_distribution
      : depends_on<count>
      , p_square_cumulative_distribution_num_cells
    {
        /// INTERNAL ONLY
        ///
        typedef accumulators::impl::p_square_cumulative_distribution_impl<mpl::_1> impl;
    };
}

///////////////////////////////////////////////////////////////////////////////
// extract::p_square_cumulative_distribution
//
namespace extract
{
    extractor<tag::p_square_cumulative_distribution> const p_square_cumulative_distribution = {};

    BOOST_ACCUMULATORS_IGNORE_GLOBAL(p_square_cumulative_distribution)
}

using extract::p_square_cumulative_distribution;

// So that p_square_cumulative_distribution can be automatically substituted with
// weighted_p_square_cumulative_distribution when the weight parameter is non-void
template<>
struct as_weighted_feature<tag::p_square_cumulative_distribution>
{
    typedef tag::weighted_p_square_cumulative_distribution type;
};

template<>
struct feature_of<tag::weighted_p_square_cumulative_distribution>
  : feature_of<tag::p_square_cumulative_distribution>
{
};

}} // namespace boost::accumulators

#endif

/* p_square_cumul_dist.hpp
bEh0dAvDerk3jSmQXq5olz03r+S47D9bTtzLEdPjhJRHcY9wxrQ3/W5qWOdqxXTZxiYQQIT2TlzBJDmo7RaK1YZy9t3uYWxqBkpwa2d9YEXruYNbe7rv+vK4lf7hsTmg0SnbicpJ0GY5wx2qdOQTyG8A5+u4/HN+SIt4nuRVuDiRaF8dhif+7d2NpYYK9WkiL7XuxcDwj3r4yzsApQ9G5zXDSbYAvw/S7szJfhtXqmrMpRAjrCXMUoMgid8FdttAhiwd//EMOGJIz1z0UnBBrLSr8h3qB6GC1YtiAvILogAELPvTYZoz0uqbMDZSCjLTTGbsUlYkO7tJlKvsoRp4/mW36WKwYTfcPfzdIsAOPIYXMnQ+dZWeLfRJ08lxN3Jr+BhibC6P3TcnIq9w3F2//s05fvXanmRYI+t9zoLKPahLrYRgumCFURYBHkwqy3pksxsiCV+vZo0J7+75OqXusGPcpySYS8ZnZX/oqw+pP6ZBhJOeWA6Qk2PinO4qyeC7FFAopmA5pRjM8w6KFBP9Q23Q6GxFqoP5zNDBprs7LRuw5UCwUGJl6vax8Ekz+Q4acCZSGmyEuKEoLnOdmGbOMPSu++LElcHKgrVxEMNEsn1BgNIExXPhiu4LzWhxbtHbXFWWsE7Fvo5TBH/W8M4L0/udvoUupNxJ8Q7l4GvpBBdRwaErK0eyPlJWBRg7SlaPe8BmY9+VZrDoU+bKQESiVf4g+y/9hG/QIl7XwJWZxx+6m6rvk0Wwfya9npqtES4OROJKt0nmPPLHJXeBQQxJKBKOcE6boN0GUZu7isasyhS1XNLG/BAdVu6kyGDpUnJO4klUPGqcDXXfqmXcJOptabwwobM48r/CLaqh0yyGObvn0GBQpuP2Z95bE5RKt5Y0+ea2yTGVrHJ2r6rGCvuQorSdbOpoBLjMG747BqLHow1vOSWEJ6xNuJG+W8oMj+Fp+Hmm8y1ftaCLJ0DKr6DaWXDGSUjhLvu68TBs94gDpGwJGLKjE9t9LcKVZqRwAvf2uwi1tD+1noQuXUuwITYBW39WGmR/HxBQ5A9B6l0Uu4a9f9ErWc514wy1ROyFql1rBs8vH8ISvaVAXsSH6MAaYpwp3ObiOYrIjl5/sE1eAUrdmn1yAOyxDjPzWKYh8kcEm8gJsLR9R5j6bsYzZJNYMkIJSvEKu786M5TRb3x/fsm23y8PuQ6yn+mBu0neTbR4f00y8wDTCg0CCAov2FhkEw09FQU80QEe/HB7I+P8e+jGNQSkCKe8kgVhVD+fJjkaIwogAfbXEpyT0mza88if7OlEC5/EdD8yX4zdj7lb9zxqZlbTzXQlzMHpkn2hhHNKQBD3CR5rvMUisA25J17xOzm1288NCi4vQuyZdsbeM53vKd2eLqpEq8JubGp6QI3hB/A+CCwgATqqLvxxCRxDhD2dTIlMuxA21ibpvvN4gwnrt0dclFZVr1XbTTjuEJd0yZ2oJGG8YIjhhUjParmu4hbHXLMy0ptpZJmS2Xkgj9o5T7wwMTnpMMYA78cnJ+OU4C+wlnBDgn0YBC8CwZ5nqirku1jAV47D77sBXiEkmYAb4aGQxTs1r+A3+UTia8S9La/qn3TzKymC/F4mKdlL6hSYLL6E8Gw2MM7xivy6f8RDhh7iBUdoTJ6awLFh7JHBmIqsP2FulAJMMLZ73u9OwN27Hzz27ScYvzjDL7qWaIc15ZjSBTgjtOKJYQcPnN2/JHIMArscTj15+F/+GgyK6rPJgD8eq7MwDladNJS8H+RbzXsK5pwn3H98ojuKJLDcSCE2Hb9Evgn4tdY02WOwVcR+uUvBKoedjNhXyuUkunRl5fS0eE6GKXjIOxgP3x3KpWyx7NX8oPvHqbeFnx3uZ6PN564Jr6Wwi/D5ZpDJkEKwYzDPx13JDFG9eTDPbvo2chXifO8tQi80iAgpI+UD+JDNizu0zZlpYdUEpgdh3zM4SHnSzm75lpfoDsNt6cnztieH6gljRwvFzBfhvvKeS+pV+FICP95Ty5mq2/XTueEj647tqdCDqHLpLpTLFi7SKkQjYcVcssTklld0gwz0BN59bNlX6tnqUbG5odl3p70/Diw5KX7ImCtqQiHYOumB93OiEPZfuFZtoXAj7thCmyEvNGcNJtkLd9s7NmXtfVJthqt9okuqJD9V+gWom0X8CL8fAWO6JnRJsqFxR7phsF/s6S/o8wq0KyZg4DvOIEhQcJl3ya/p4vS0co4hbh1H0vnVWXQfZYosn71XPxh+v7t5PqH3Dg6h4UvXRGoJbVBqM4zlTfDTx4vhYQCGWDtFEdEHZmdGXtgOI7GTuq3zYI9egYXruggL/+EQSLlKhpmKY1saKoygCYNTi4XJsE3OpzUKkBp7TkCKmxn6uPzgPvnqWBwag4igcdJK6HkbAUSVDYMU46LAepKk1yupgY7LpH6rVTTRoVV8E1/SOTOOZvmcwa876a6X05P4G5HsY8pNsR01OhvSdTnt0jneY1uDrlsBiddu4ZBFa492TQ0FUxPekEJTCvVsQ/ZDCc69NZAFvFplKOOc5idwx4Q9c1EhTEdKc2UzyGHQwa7sv6uU12u3zsXxNW7QG1qSp4nNlv4I7i/QcB0LOnMyjTNBV8tcqpF79Lz0toFox/hNfOcPTBTctRnYL02su1d6e11sUe8FF5ieTW0ECOaYcFTMxBva3uiBhIG6kacGBeu6ZwPjSULsNxcjFPmAj0v7NQWeeZFv8L+hHT+qOg88tEnsv6aflGOyIxNjvPKmOFluqrdI4KlNZZNhMqsKRlfQFfTz3qUQWwSvTrjhlAdw+gj1ktvOO240DKwJKsDxP7FRiybTJm2j87k2gY+r7ICcG/ZXUQ2DC6+uYQ3k08VEJ99tgvaF+9I0eOmcV5UzAYAHjNoXoJxsL9mjoQpArgPSocAdyfGCIdmuqLqGT1BMorneNmaS2ksxE7SkV4fydMbwj6PJpodLEutoIYFOchPbeQlXGqFjm7Fy5WhciSsy17AIqqsIV2jgIMCNgtyyX89pYjLozr78hmvxtHd0gwmwYfwFzYqnlpsL7xq5lHyVRVrSOMXRndxokBDYgphvCMEOfjgi3DCSU1ik3ah7uQTr780T04MabGNN6S4pElK8ZRZDgiydAZhcanWhFeuOFbSB3WmZeDHU4mpGKxb4U33pvGbkodLz2epYMgBQo0e854qD40/ICevn640u3rRij2dPn0meFCZyOGAggg9ZnjEjL4bIUhfRa1Vr44QvhaqUTxHvRSauTeBIYfAbT6caxL7dUvITzZxatB0CTB+yOmEAcyPDEi9qfeT90PwpNlxgTI1yiP3w0btetDodEMtkqkLsg0kByRqdRzYYwpmbxwCIUOOzW+xDrO3KvSzYAZgU3fB3Oi13wL+TDSaqEwpk9S8T+XElqUvG4rLesj7t8+WRjZq/l681D8773ozv8t3LpElA4KveuOhuwBkl6Fid9EpQ1HzeY4EloSe7i9LPBXHH3gqNYiI7gJDg58LKfPynSg2/ubykH3FdDUEdQEAd+M2ZpDNFWPO66fI79Z2UnrcpX1ekekUzwEe74+lXryiEZfUjJ4fdy5P6oTJn0YghXfCkE92os07LTsu7G3iJiYAJ4+IGOsvTnGwJlllevkdFnhQ7xgDk4673jmHcyxx+T2PNuwpkciYwp0AifulsGRVtvIRqCMbU3LElz5guP8QdC2c3gWK/qboz2Pbrix5Anfjwm2pm8LINdje567HE2eEauYWY9U8uF130l3YvoV6lm0wRYsCI/FOMyxf4PxsJllACP71wOCzZd4PblEqQL5/JVZ/InemS+sAtgHlnekKq0M5AeGMcMMxRTaNH84RwSgFXk5t7AXsl8kAIks6QvN+UANF0eaaLwvGrkvsSLt+57nsDbpxb5N1IgurqGmrCzgF4pYe118tpSYpHDVgZgcpL8cCAlzGYrewRz9C3eVf1+gHT7z5WS+mn/JlqVmLulUguNvZw/wKtDdmp/BTNpU1qteWnrzDrytajeAnn5tRDxcgENUKShEwh8orLopqvB2sMTCenN1XPpAeTWfLvpPnW8OAWLOzY4s71h4IwNh5nvRsH03NOY5SHBL2pdibh+EjyhTzWu9OFmKTJVtIr1tu8fCvuxfEj5P0w4nzMuTs0N6ok/Y1FcSY1jM54/b1P1+by+kU3n9jCrePN7pR+qF/dcJ7/CN4tmdnYPQ5n98UROoRLmAl0px24YLDZ7H6y7vei6P42x708P9qfsav7+MMnLWhrsGRAj5DM54QmVlVi5btw+gXGgp/KDpsKLfvqhmjsqtlYtQch2fa9OCOtF/5okIGoT90MXWghmcPd6bfsgMA7x4kemGvUef58ONmv1ERHFy9k4QissYhSoqhgHu6DkCHbZ8TBmcnIw3lOwTx5OR/Aykh+mM4t75d7VF6QG2U815Pw3ULbW/1RzuDV/ErFfBjg456eXACWYq/x++wtEEevDG9cYDpRiVICkPBKKTIaKZivG4lngO+97mDX/L4s73AFVV0HLcU/zQRC131Pg+Y9WTcIuriaJ0+GZZ1aHp5uls7cXmY3cDnIYb8gAN/S9wYAWKkMneBiUueu9GiMEW61drJ13fOgWaSGLx00idhid10sCYQEi63siRdsgjTESoiVRRT0FJ5SvjDw8+96anTP756R6nkPePIsdass4QOJcpPH65xQxjqu+CaTcykb4i+hSVuah/vgYzbVl/TrcrNJL/xofCL4cBy/YgzjfdfbQAEAai5eGUu8TYU8JGH85Jdb5MfoDF85hH+73NzSxwJ3bw84kQhavrKo1Hy3N6r1+NOz2In1CW7NQtRuO5uV+d3cvEUR8O1MerKOP+sKYlDfmssmDbX1JIHQi+7UgJ2d10KsDoOknjAq4rhDVqgmxwTrV1DCO0O0YDfawZPSXTP02lHRU6E843Uvt03Fi764U3L+iUWy1t3s/fcCRw0qzSb9ZtIUMiHGMWH1FskukEMYDPEbuHysJcHIlIYLORcRorlvLsE9M6gQVYQy2HaajXCA5jN8eyt1r/IYOJXcky8ESCd/YDSFcfCD8QmiNEyCvetuWFuTU+ijYwm71dhuFpwsEqMtvrSL0GVgDb3NJw5JxUKM/8ArqR9+t/vNzUDz0Evwi2m610nxqG3E6MdTOYk8ZSwgdnB0koHUm7awQGUEOU15qr2ZN8H+e4dOrYG1D2XzMGL6w6kJgVCXXVjQHfjjd7giQ2JZ3+iQDbKjF8ILkggf14eUzV/t08a/9zkKND/UCAL4OfEui6geZdOs5a6kxQWUiucqZdpNJvZdTW5X3uS9FbSJP1V8KCPJ2RuTLXdhcDo97k6R3cnOU4nlHpzU3gQb4g8iB1N4n/h52geh+qvh+2kcZNvz7rOAWLYHFx3KJMmri4RJB0Kc3lnU8DRPNi62h3XnP4har0+u1c83Ddd26fYN8D0ptjwcIZd72IHidE3gTAffuFwdiVbX/nw6fKgeCygLajK5VLXhfNyvGlgHPW3nKuwsxgYJjJ7H78cIpwctscIZNQWAX4wxGWxzDx8nBL7YUKit8VoiT7QERcaX3DdFt8JYdODO5UvK08VELrmCrkx7lhTT+dgfUDR+JdKaZr3UrIOCYe4n+iJLl+r4l1m3mXNOyfW3vNBWzzpCKfZPaVf4nBKUGp2qnTRz+L+JLKMdctXyFjc7mbEmAgQT6sXdO+D6m6VVDOtfLb3dM42wFp4qeY0VC79h9EUFxuWT/3CdPJoGTzR2mUuy06Tpo/JipWenx0hgnZcGz8fjDxx2N/AbRH41A3qqommZbuirh2PKQcVHRRYox3zUUxPX9OW/NCX9UJfW++6Te0K7twMIbqa5Hul6XuW1YeRB/XxWOt63FUVy0vWItS/XIXutSsv18hM9hDUYE8BeO5GBa/Py4loEH14EpCwtl2YcwvqJDp4sX2aK4PAKXsYhqqq+51RdBt5j3XOQ7KxiomPUuk4EqipD8BxLu0Ts4H196zquFGu2QQ5oEreKTMM5/ug3Ej5XGdQ23UFjDd1dMwgGk2dbJaRPHRv34ftPPEKeqHF97HwIgxv4xCEW7/63XNz0vCh7EOVJzBsCAFHUkagWi2oeKktAhuUkmBO7pQ8L2P2PmM53k0K7IzlPiArPMh2Xg9OI5qKjS3RLSMsfIy2Ct1PtFtenRSuLapRontqRq6SO737fKJPWwFXzpjmc2espr9wfUyoTi2Jk5mnxtboUDSj7EsdDTlFtR+W5L/2JtH44JCtBZyjSnAnEaMfQIq1P9R2YqYubQ8/6PrO8/316uaObrYHE4kgEOrMgdJ2vkUp+mzdCx0k/lUS/waqMR5bQsoxF+vfpd8k4nmtI7QHNLqFAJgGBwP448fnU9btkQo7GMTvTKRZ+yxgxd+xpjeZm+83ZYI46gifnfhF9tbegkkRg+bkiA331xd6AXjqfu2bpmEKE885sw0BBliDUgLg99eLoAn11gOEiTrLFbcR/Z4of/SFE0gs4QvZuj5RnVcxrbw19FVSiXfqA1s7X+K3yvdWMNWNQvqTgKcgUvy395qM0ZMMFqQzZkoUBTihJK1EhWL8+9I07MIpcG60xgPn9PbBUiqwVmwrnbF524Dn99e5Om+Ur5+i1UvPFNFQssETdA3o3f23jjZiF0Yb1yei89VG45Ri5Ckm0mdcLuQ+gJrOfoArMbxdX3rbEXan+cKdtyTO7sKo53+Nbj9H5xJALpBJ/uYabIniqCat22OnHMNvQazfuP9QAvb8GNjhUu9srCfNiamwn1NNsU229Z3TVYJhITVieL+/bnRWe98Em63TAkSsB2em2abZPBq0m9aRnbWi4loLNS6vdyIUJ1zyaqSzunF1KvSqGlPzT1Sdy2hIsrrXR9uF9LIhVfkzkAGXDt37q73aqV/D6T8GpY70X+bTZGTuZeIzV6xH3WGSZchCyqGLgkNPJ2JomAEUhCVQ0lIeSly7ZaTKPlIESrRiNNmcbp3529yb66B9w5giAhDXen+rtN1P+kmon+ZFbj0KSwxSGOwn0LgLXLdi1MCcW9kgyOqXnwK8cEEemCFAxamJdYeOg/0Ab8UJ0dNhQcryePvxyT9Z593NJcbW7xvOSaTXd7ph/icjb427I89f1ZeIDbblXucdN8S/QF9FfX4oTGhZ8LhhtZh8Elen5P8+PviuyjMMzqGhS+zLhA3I+ptTN0vy1QMOU398zUyByfVvV2Zng8nWFY32oYqRiiQZl1F9a+wdKZYWi/Wgl492NOQ5Ot+u2287c3M1A6o8UbVZGpmPsShbWcnxdntIvn4sEHrRE6WYi2h5oU7Xney+670V8Ak1aErcbKirtK6znPb0UfFyu6lRcITIqctpqxltM5z900lPSmOnLc08rMx9Yl3eYai5/fO2KTN1usiruPm+iabI6e2dlt15hb4KzUn41XlFRWVXNwlq5f1HD6HpBu5Du7TG8CRnh755usEmfZLz4dRVbmYlsKJM6mWmgra4xM8pb8qIiS9t4k8hEQ1fvZc3PC1mquZQKgfUPSTTd7ZkctpidfUcVI/omTqk1jZ3WZvArwTJQXJ10yZ03rZoIrUUDLbVVvuI+1auXGYrZeOWA3FRPnHffvhQuDRu9NdLW
*/