///////////////////////////////////////////////////////////////////////////////
// weighted_extended_p_square.hpp
//
//  Copyright 2005 Daniel Egloff. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_ACCUMULATORS_STATISTICS_WEIGHTED_EXTENDED_P_SQUARE_HPP_DE_01_01_2006
#define BOOST_ACCUMULATORS_STATISTICS_WEIGHTED_EXTENDED_P_SQUARE_HPP_DE_01_01_2006

#include <vector>
#include <functional>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/iterator_range.hpp>
#include <boost/iterator/transform_iterator.hpp>
#include <boost/iterator/counting_iterator.hpp>
#include <boost/iterator/permutation_iterator.hpp>
#include <boost/parameter/keyword.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/accumulators/framework/accumulator_base.hpp>
#include <boost/accumulators/framework/extractor.hpp>
#include <boost/accumulators/numeric/functional.hpp>
#include <boost/accumulators/framework/parameters/sample.hpp>
#include <boost/accumulators/framework/depends_on.hpp>
#include <boost/accumulators/statistics_fwd.hpp>
#include <boost/accumulators/statistics/count.hpp>
#include <boost/accumulators/statistics/sum.hpp>
#include <boost/accumulators/statistics/times2_iterator.hpp>
#include <boost/accumulators/statistics/extended_p_square.hpp>
#include <boost/serialization/vector.hpp>

namespace boost { namespace accumulators
{

namespace impl
{
    ///////////////////////////////////////////////////////////////////////////////
    // weighted_extended_p_square_impl
    //  multiple quantile estimation with weighted samples
    /**
        @brief Multiple quantile estimation with the extended \f$P^2\f$ algorithm for weighted samples

        This version of the extended \f$P^2\f$ algorithm extends the extended \f$P^2\f$ algorithm to
        support weighted samples. The extended \f$P^2\f$ algorithm dynamically estimates several
        quantiles without storing samples. Assume that \f$m\f$ quantiles
        \f$\xi_{p_1}, \ldots, \xi_{p_m}\f$ are to be estimated. Instead of storing the whole sample
        cumulative distribution, the algorithm maintains only \f$m+2\f$ principal markers and
        \f$m+1\f$ middle markers, whose positions are updated with each sample and whose heights
        are adjusted (if necessary) using a piecewise-parablic formula. The heights of the principal
        markers are the current estimates of the quantiles and are returned as an iterator range.

        For further details, see

        K. E. E. Raatikainen, Simultaneous estimation of several quantiles, Simulation, Volume 49,
        Number 4 (October), 1986, p. 159-164.

        The extended \f$ P^2 \f$ algorithm generalizes the \f$ P^2 \f$ algorithm of

        R. Jain and I. Chlamtac, The P^2 algorithm for dynamic calculation of quantiles and
        histograms without storing observations, Communications of the ACM,
        Volume 28 (October), Number 10, 1985, p. 1076-1085.

        @param extended_p_square_probabilities A vector of quantile probabilities.
    */
    template<typename Sample, typename Weight>
    struct weighted_extended_p_square_impl
      : accumulator_base
    {
        typedef typename numeric::functional::multiplies<Sample, Weight>::result_type weighted_sample;
        typedef typename numeric::functional::fdiv<weighted_sample, std::size_t>::result_type float_type;
        typedef std::vector<float_type> array_type;
        // for boost::result_of
        typedef iterator_range<
            detail::lvalue_index_iterator<
                permutation_iterator<
                    typename array_type::const_iterator
                  , detail::times2_iterator
                >
            >
        > result_type;

        template<typename Args>
        weighted_extended_p_square_impl(Args const &args)
          : probabilities(
                boost::begin(args[extended_p_square_probabilities])
              , boost::end(args[extended_p_square_probabilities])
            )
          , heights(2 * probabilities.size() + 3)
          , actual_positions(heights.size())
          , desired_positions(heights.size())
        {
        }

        template<typename Args>
        void operator ()(Args const &args)
        {
            std::size_t cnt = count(args);
            std::size_t sample_cell = 1; // k
            std::size_t num_quantiles = this->probabilities.size();

            // m+2 principal markers and m+1 middle markers
            std::size_t num_markers = 2 * num_quantiles + 3;

            // first accumulate num_markers samples
            if(cnt <= num_markers)
            {
                this->heights[cnt - 1] = args[sample];
                this->actual_positions[cnt - 1] = args[weight];

                // complete the initialization of heights (and actual_positions) by sorting
                if(cnt == num_markers)
                {
                    // TODO: we need to sort the initial samples (in heights) in ascending order and
                    // sort their weights (in actual_positions) the same way. The following lines do
                    // it, but there must be a better and more efficient way of doing this.
                    typename array_type::iterator it_begin, it_end, it_min;

                    it_begin = this->heights.begin();
                    it_end   = this->heights.end();

                    std::size_t pos = 0;

                    while (it_begin != it_end)
                    {
                        it_min = std::min_element(it_begin, it_end);
                        std::size_t d = std::distance(it_begin, it_min);
                        std::swap(*it_begin, *it_min);
                        std::swap(this->actual_positions[pos], this->actual_positions[pos + d]);
                        ++it_begin;
                        ++pos;
                    }

                    // calculate correct initial actual positions
                    for (std::size_t i = 1; i < num_markers; ++i)
                    {
                        actual_positions[i] += actual_positions[i - 1];
                    }
                }
            }
            else
            {
                if(args[sample] < this->heights[0])
                {
                    this->heights[0] = args[sample];
                    this->actual_positions[0] = args[weight];
                    sample_cell = 1;
                }
                else if(args[sample] >= this->heights[num_markers - 1])
                {
                    this->heights[num_markers - 1] = args[sample];
                    sample_cell = num_markers - 1;
                }
                else
                {
                    // find cell k = sample_cell such that heights[k-1] <= sample < heights[k]

                    typedef typename array_type::iterator iterator;
                    iterator it = std::upper_bound(
                        this->heights.begin()
                      , this->heights.end()
                      , args[sample]
                    );

                    sample_cell = std::distance(this->heights.begin(), it);
                }

                // update actual position of all markers above sample_cell
                for(std::size_t i = sample_cell; i < num_markers; ++i)
                {
                    this->actual_positions[i] += args[weight];
                }

                // compute desired positions
                {
                    this->desired_positions[0] = this->actual_positions[0];
                    this->desired_positions[num_markers - 1] = sum_of_weights(args);
                    this->desired_positions[1] = (sum_of_weights(args) - this->actual_positions[0]) * probabilities[0]
                                              / 2. + this->actual_positions[0];
                    this->desired_positions[num_markers - 2] = (sum_of_weights(args) - this->actual_positions[0])
                                                            * (probabilities[num_quantiles - 1] + 1.)
                                                            / 2. + this->actual_positions[0];

                    for (std::size_t i = 0; i < num_quantiles; ++i)
                    {
                        this->desired_positions[2 * i + 2] = (sum_of_weights(args) - this->actual_positions[0])
                                                          * probabilities[i] + this->actual_positions[0];
                    }

                    for (std::size_t i = 1; i < num_quantiles; ++i)
                    {
                        this->desired_positions[2 * i + 1] = (sum_of_weights(args) - this->actual_positions[0])
                                                      * (probabilities[i - 1] + probabilities[i])
                                                      / 2. + this->actual_positions[0];
                    }
                }

                // adjust heights and actual_positions of markers 1 to num_markers - 2 if necessary
                for (std::size_t i = 1; i <= num_markers - 2; ++i)
                {
                    // offset to desired position
                    float_type d = this->desired_positions[i] - this->actual_positions[i];

                    // offset to next position
                    float_type dp = this->actual_positions[i + 1] - this->actual_positions[i];

                    // offset to previous position
                    float_type dm = this->actual_positions[i - 1] - this->actual_positions[i];

                    // height ds
                    float_type hp = (this->heights[i + 1] - this->heights[i]) / dp;
                    float_type hm = (this->heights[i - 1] - this->heights[i]) / dm;

                    if((d >= 1 && dp > 1) || (d <= -1 && dm < -1))
                    {
                        short sign_d = static_cast<short>(d / std::abs(d));

                        float_type h = this->heights[i] + sign_d / (dp - dm) * ((sign_d - dm)*hp + (dp - sign_d) * hm);

                        // try adjusting heights[i] using p-squared formula
                        if(this->heights[i - 1] < h && h < this->heights[i + 1])
                        {
                            this->heights[i] = h;
                        }
                        else
                        {
                            // use linear formula
                            if(d > 0)
                            {
                                this->heights[i] += hp;
                            }
                            if(d < 0)
                            {
                                this->heights[i] -= hm;
                            }
                        }
                        this->actual_positions[i] += sign_d;
                    }
                }
            }
        }

        result_type result(dont_care) const
        {
            // for i in [1,probabilities.size()], return heights[i * 2]
            detail::times2_iterator idx_begin = detail::make_times2_iterator(1);
            detail::times2_iterator idx_end = detail::make_times2_iterator(this->probabilities.size() + 1);

            return result_type(
                make_permutation_iterator(this->heights.begin(), idx_begin)
              , make_permutation_iterator(this->heights.begin(), idx_end)
            );
        }

        // make this accumulator serializeable
        // TODO: do we need to split to load/save and verify that the parameters did not change?
        template<class Archive>
        void serialize(Archive & ar, const unsigned int file_version)
        { 
            ar & probabilities;
            ar & heights;
            ar & actual_positions;
            ar & desired_positions;
        }

    private:
        array_type probabilities;         // the quantile probabilities
        array_type heights;               // q_i
        array_type actual_positions;      // n_i
        array_type desired_positions;     // d_i
    };

} // namespace impl

///////////////////////////////////////////////////////////////////////////////
// tag::weighted_extended_p_square
//
namespace tag
{
    struct weighted_extended_p_square
      : depends_on<count, sum_of_weights>
      , extended_p_square_probabilities
    {
        typedef accumulators::impl::weighted_extended_p_square_impl<mpl::_1, mpl::_2> impl;
    };
}

///////////////////////////////////////////////////////////////////////////////
// extract::weighted_extended_p_square
//
namespace extract
{
    extractor<tag::weighted_extended_p_square> const weighted_extended_p_square = {};

    BOOST_ACCUMULATORS_IGNORE_GLOBAL(weighted_extended_p_square)
}

using extract::weighted_extended_p_square;

}} // namespace boost::accumulators

#endif

/* weighted_extended_p_square.hpp
cbUS0lGej7q29NUBpA48jZrC4pnfM/X+ZPpZUEl2NIFYu70oyv0Nt5aA0VySaTxSN+hvA/NxR6NZUS3KcEfGWJot6nDHxlhhL0pwR5BM0DTQ2zIIBCqa0dYnLbpwB6fUZtjiMVpY2HJn/dqtd+KOG7PCtYWtMNe0pRDI0Gwg0ho5XKRsTs/5mVqrvmR97OKGKJCU05da37DEd2zgRiqQa9jNYj6yKGnL155eZZxWK79kcezkhtCeaNhXTcNTb7Mo58bcHms4YW/MU5+1OGaL2x5aZdlSv7J4cozuRtsetTY2X+u9qOfG2h63NkFqjFHv1RxbZUW8KHXz3jtd6Cd33ZgtqneyUD+plXJt1bHsDY53ptAvkMVE3d4S6rHkDZZ3RudPI4uaOrtj1xtE76TOvnXLs9qTY8MbUu9c325hc4FFpRvM//iy8ZL2sc0N2spIl8VG3dmS8A3cY8Jzr58luBaw5HDsfoP0mPTcd9MAd0wu0JuY/XWYcM9gK2jE4DfDwo9xNHso03oAD2SpA9NhNOu8pIPQYVz/PLUD12Fs5by5g8RhwvlH3B4UvYPqrFfgkqWD8ay//ZK0g/asz/tSuIN1YtvP/gIGA+pDumVC+lt1Pe52D+7O0YecrBfVIxofSkm61yfYg3RJ4UNH1h9+ienzkaxP+pLNh4lsYOAS2YcytzduL+keRzglt7v0Avte1oc/t0f+TkE4Kg3KDuXNHds7b+3Inti+9EQAdDN64gIGlXfnOsIWoPxd31h3S8+pnzT8iERycnsmIFYXxU+2fugiabkDE3v456j37H6YgHHWXcY76ic1P0JwNqCnBqJ9UXHP5UMNTgUM1IS7LsU80fhxAPocflfcVz1x+wmAgzeGzrbcL7meSLtSN0bOtm8vke6CO0jnvx7dI3YliPSS7cadK47rnaq+EFQeggKa1pKe6F84/cNERnK3Jy7x76KeqF/Y/UPBw4DtlbujJ7QXGv8o8NjG75X79iehF+HXAP9B9/OcJ6quqLNd77uBJ+wX+tdo/3HwJgBac7fwRNyV5j8C3t649H1CeqF6jXgd9f8Nhm7cnT1hvNC+Rp3tId2J+X2jpaZUjZA1SPxIMZRIWZZIc5BIkaGWOisKpLOQjynqV8MuK5tVALI0xevJVRXNqxGXVc2iP2V9GKLdkSMpilWjLWuYlTxkcE1qkxcqAqmxlrXMSh8y7gRimMvC0tPtyFPQM0kWfZ9VPmRFg6n5kscpwxBvqpav8bGv2JQetmv6vfV3zndPxZjTMtbJnHpEVDEp/bLbxcjTEtaJLh2cupmUiilK8SWytHK0sjPFhGoRnOqZ1ClyFtO21rGc2gxpu7KXxSjWgRr0mrKoxUnFwDKp8pTDIslp0wMc6wiXcpdMlzaXMJcSl9RGDX59fml+bX5lfkCbaJuKHo3hR+Y0llQtmTSZNLk02TR5bRltOW1ZbfkFGcZim+KjoqNi4iLi4qyirGLNaeZp4IHWAfeB2wH6gdIBy4G9dYxLXKNWm3abchvAS9RLpTxtXvaoGG1a6oDiwOQA0zqpUXeZUohBiEaIRYjCLgWUDEoEpYISQCmgJFCaUbxRslGiUapRglGKUVKzbI28g4yDnIOsg/yZzEqxe/Ft0W0xRhFGMcm00gGVdVqj/jKVL5MvpS+DL40viy+FL70vtS+zL9VJSldKV1JX2o2siIyInIisiDxYBiwHlgXL+8v4y/nLPhbDTYsdxCfjSKj0wOMnvhfHi1QJpXExeatuHoFYkD+IF/MX+MOJOybhPCXeiFMlYTMl1Yh7IuGdQOVDqe3ynkSSdkrXBdNQkmfK8Oq9kCTrlP4Vpq8k6BxVHl5CBRIV/zbq27dIvwIwAXksNlwfuSq5aYEKTsQPOjxkNp13mJ/7PrEZRL+n6qNj04vGNOvjZTNSeI/d99GxI52p5FvZFjybYjadEtZM3ztVSstI3QKN5Igl09h0xuE+QTaAxjeEAjWNiNAtc1VmoETVd+yoXlPHSB1KJdzSiJk+wi0Fx1QdhnG8vW/OfZ5bPo6BP1SYsPEjdrZM68QNKFlw0yJG+nC35BxTfugZUGlF2vS5bnk5Bv9QXf1oj1fRy2za9ENzlcYe3/2bQJ/hln2d1CrVfKR3n++W30WAh8pslKtp5yI5d2R4768tzDpZWzz93sIttosfHuK2uMqRpb0zW4QXlR5KgqxG71kj03pHtnAvyj0UbbFronh6s7aYL5o9pG3xzyJvex+34C7yFyncIuN6Wer0jzHJopR7S7c4LlrvxH3ou7AAUQ69RhdVd0o+rDcRZL1xW7QXDXeSTwx+2OAokd7cLdY6wIf3SH0UCckRChY0zrqJoUwjkZXDmZUjYbbDuk5wrfnZzDyJxCOKkBInjtbWVXF7+pZE/RE7SPOf27bObKpHiMGfuzfV04/uqe2Dhjv2Tu6t4avqp9S3qY+DvjuCS6z6TqLow/dOMugjmHwMt0mPI3CQbUgglLxVNHYo1CnhQ1rUToigDiklRkr40K8dTKiMZ7KgHilVXMrA0PYOMlTCM9GnQ1AXRKmcohxfOkQ7TDs0s0PoFCGoDqJOG7aA2nrGCmqzpO0NXe6geAYa0GsPoe4k7QBbpf7iYSShpvc4nhE+5T6ZPm0+YT4lPqkdGsL6wtLC2sLKwoAu0S4VIxrAR9Y01lTtwbTBtOG0obQR7UHtYe0h7ZGFQcYdm50jyNEOMYR4JwuStaMJZYYC77Xuue/d7tHvle5Z7u09Y3ziOrS6tLuUuwB+on4q1WkLQ0c7aFCpe4p7k3tMz6QO3XVKEQYRGhEWEQqHlNzk3MTc1NyE3JTcpNw0QDwgGZAISAUkAFIASS1DNSMOgw7DDkMOI2eDKzvuO7eQ2x0MCMYOCVTpnsozrUN/ncqfyZ/Sn8Gfxp/Fn8Kf3p/an/nf6NC02yGRQZFhkSGREfAgeBg8BB7xH/Qf9h963IGDit3HZ2t8E8ct+SqpFkLJGFnAkFnAGGbKoCsHV5yfWMWpRsSomFwix1HcOi1uXdaopsdol9wsJ1DcmVh4l2xQHDytelDkotVGZ5hiL+deHD6tflB8pfVA55si2FejIyeKzHAvJ4PMiEldfqX+wAiXvJ0cOExeLBpBHyqXgKUdmRLCrkNY8E4zjP5XCuawjEUyux5hYbRmP/12CvKwhEWiUwe7bkaBgqaSSgk9LQMt/UwKoVwEu3pGcTKDxbCtRSy7Nr32Lv1lCopFoFqZBj1qSlIKsFiqTPMwWXLYdAfHIsKp3CnTqc0pzKnEKfV/gVWlY0yxSTlKPkohTiZOyUrOStEcZh4G7mjtcO+47aDvKO2w7NhbxDjF1Wu1arcqtwI8RT1VyrTn6Y9S0Ialdih2THYwLZLqdZcKBMsFSwSrBfNtNUEaIDWQFkgVpAlSB2kbqRhpGKkZaRmpGmkaqTfT1zA60DkwONA7MJ7RraS4p9wm36ZgJGOkkAwr7VBZpNXrLxX6VPoU/BFsiU+1T75PmU+xT5VP4bFml2aXepf2Db0I3R8x0YswgunADGB6MKM/3R810D+mwA2L7cQnakTIaZY4aaqFMlRElpdnlleEAct1gXBN+ZlV3GrEFYqzJUCOptZlcbuyZjX9CrvZZqBAU2dm4cOsQVPwsupJkZtW+3fDOXuge1P4svpJ8Y3W43ffOcG5Gj2gKFr5PVAGrQKTq/xG/bECbnZ7NvCQvEk0piwUAAos9dOYQKQdNRfCr0NSgK4ZXvZrDvNQxjWZX4+kMFZzoGx7DvlQwjXRq4NfN6dASVNZpbSMtpy2bGaOEBjBr55TnFpucWjrGsuvzay9V3Y5h+IaqFemVYY6lzQHbJKq0jz6c903vcZxjfAq98r0avMK8yrxSm3TENIXkhbSFlIWAnSKdqoYlhgVsWizaml/T/ueVp5Wllah/V27XLtMu2LhO+OczdzR7NEc8SzxXNZs1pzmIfMh8Frrmvva7Rr9Wuma5dreNcYrrk2rU7tTuRPgK+qrUqW9UHY0h3YodU1xbXKN+eeuQ3etQLhcuES4WjjfXjNXI1ctVytXNVczVz1XG6AC0ACoAbQAqgBNgHpLWU2Fw3eHcocyh4qz7ytz7nO3s7dzGLMYcySHStdUrmlt+muFfpV+BX7lfiV+1X75fmV+xX5VfoWnmmBNsDpY+7ZM5LtIuUiZSAX4O7gcXAau8P/uX+5f9jgHdyh2HZ85+02Kq8RRcTqExiayBJhZYhNmCdTVg6vKT63imiayUWws0eOoap0XtylrmtazsWts1hOo6kwtvG80qAqeVz0q+kdEtvh6/uGLb5PgWI2unigq8F5PBtUGk7n8euafsrHcOsQFaHNh1r+aMJdl7JK59YgLY+b6rbebkJcl7BLdOrh1swoU55QmS6xpgbTWM02EehHc6lnFKUCLZVu7WO4/59uu9WUTil2gVpmmNWpTUhOwSqpi7rBRctn0BMcuwq3cLdOtzS3MrcQttVlDQF9AWkBbQFkA0C7arqJfYljEvMAyr/Ul7UsaMM06zUb7izZQ21rbZuELY5NN01HjURNxI3FTVmNWk+Yy8zLwROuE+8TtBP1E6YTlxN4uxi2uWatdu125HeAt6q1SsTBvfdSEtix1QnFicoJpl9Ssu1IgVC5UIlQtlG83B5oFTYPmQVOgOdAMaMFo0mjWaNpo3mjKaM5optm6xsbhiwPQwdrB5uzLSpN7023jbRNGI0YTybLSCZVdWrP+SqFvpW+Bb7lviW+1b75vmW+xb5Vv4clc11zXTNfCjbXIFxGgiLWIDfgLGAi2Btv4f/EH+ls/NsEti53Ep85GKLmWOBtOh7IcRVYfZlYfhdkf6nrBdeaDqnimiY8Ur0q8ODpb18Udylqm9Y/srpq9BDo7QYWPVwadweuqZ0Xu8+37htf2Xu6d4evqZ8W384/7vteCazX6XqIYh/deMhhHmELltzOPR3BX21eBD+SdonEHoV4JpAtR1yHCOmQFGHPhB7+uMR9kfJOF9cgK4+YGDravkR8kfBP9OoR1cwuU55QnSw9oD2kPZq4JvSKE1XOL0w4tHmz/9Oy1WRf2Di6vUXwDjcq0D1Cvk66BnVI1c0dXkg+mzzi+EX9En+nX5hf2R/qpXRoi+iLSItoiyiIAsChYBVACKGJdYJ3X3k/bTztMO0g70t7XPtQ+0D5a2Ge8trk+ujq6Jr4ivs66yrrWfGB+AD5rPXM/uz2jPys9szzb+8b4xXVpgbXBymCAv6i/Ss3CwsHRNdqD1DPFs8kzpm9Sl+5GwZ8Tq0SkWiTfYS53Nnc6dz53KncudyZ3ATAJmAVMA+YBU4A5wEzLQc2Rw77DocOBw9HZ/sq1+/Xt1e01xhXGNcmD0jOVb1qX/kahf6V/wZ/zssS/2j/fv8y/2L/Kv/BsDjwHngEv3B6I7IscihyIHIH3wYfgA/CR/77/of/B4zXcg9hzPIjzmxia5dfP7CEUxJH5RJn5xGEmRLpScIX5CXac7ETEitElUhyFrVM/v1g3susR20U3SwkUdiaY3UUbFAZPTe2bu3C3ERjG2Eu5F4ZPzexbXHE/EPjGCP5lWdD9luheavAtMSYV8IrjgRguejs6sJ+8sPsbYahUAiZPZEwI2yKB6TuuMMJfMZj9MmbJbMsEZtFc/YTbMcj9EmaJjh1sS+mmClxKn0oIaYloCWdiCKUi2GbSLZKJLPptzWLZFuh4dgkvY1DMAlWtNQhRY5JigIX937kOoyX7TbdxzCIcyx0zHdscwxxLHFPrZnlXeAd4F3gneDd+dP+Y1LE0MGfiYeHWIkgjSCNKI0wj1ibQJtIm1CZeIGCMsYk5ij6KIY4mjsmKzorR7GfuB25rbXNvu22jbytts/w74n3ix4ZHt8fkd555wqMYtH6pbYptk21Ms6S6pUVTQaCgpaC9oIktF4gTxA7iBrGBuEAcIB6jT0acRuxG3EZsRlxGHM2ENcQOBA5EDoQOxGcEKzHuMbfRtzEY0RgxJP1K21RmaXUri2Y+tj6mPkAfSx97HxMfax8LHzsfs2OuLq4ujr/bLRCJEIoQgwnARGBCMLE/gT+RP+FjDFy/2HZ8AmeErKKlkzp7KH1WZFlmZllWmHWmriVcQ36GHTc7cZbiaIklR0Pr0k9b62Z2/Sy70WZLgYbODLOHUYOG4KWpY3M37vZ0wzF7S/eG8KWZY4sb7sd03zHBGQc9y+53mfeWg++yMDmANxyPWXCj26OBu+QN3dEZoZYJhDxRYyF8ix9M0bnCM36NYe7KOCfzLX8wi+UayNgeQ96VcE707OBbyjZV4lL+VJpBm0mbMTNGaBnBN5NtkZppsWvrHMu3wMSzl3E5huIcqGutlYE6ljQGbOiv5Doaldw1vcRxjvAs98z0bPMM8yzxTG2dFVwRHBBcEJwQ3Ojo7pg0sDQyZ+Fh5dZOT0tPy0zLSMvSTtfO1M7QzlpIZxyzGTsaPRojHiUeyxrNGtPcZd4FXmpdcl+6XaJfKl2yXNo7x3jGtc53LHRMdGz4dPtMVvIsZByNoe1KXVJcmlxiOie1Lq2aCgOFLYXthU3suXI5c9lzuXPZcrlyOXJ5AJ8AnAB2ADeADcAF4GjJqMlySHfIdMhwyDpLXxlzH7sdvR3DGMUYI9lVuqRyTmtdWTXzs/Uz9QP6WfrZ+5n4WftZ+Nn5mZ1ygbnAHGCe2wyRdJFMkQyRLHA6OBOcAc7yT/fP9M94HIPbFbuMzxil1OWMsrhgopc3H9KVS80stjjQlUrNSEmZI68w0XLTKqzs11Wsz7TkGgGC5igrLLQqKud17eqXLZtGgLkpSTsjw2OH8XNsFepae5UsuoYNbRauE4cJcxwV2lpnlcK6vg3Q+iddLS1yxvSUXNxhFCvJ+gLd5/qHKOEUV1xcH7GcXFam28spZ3w615Sd1BR8tREGhmH8+eQFmT7XOc2Hyeny5UTdhmEGm7mLhmG5EUYGOci07pwmdZPeXEH9Yaau5pwFNAiqRkczYKmVxsyQJP+hqLd8V0MzdUxbTk0ndoKhrLo8JJwEx/1QJbJOhRCPQWmNWT4fk7rhEDgCicQhShiu/BrP+YZXDpd7RbVsJYWek0GzfFpMt3BvXnOcvqxaX0VVTTtLc0dxaFsNQ6N08ses8xw9p3CK7ja588/KcgRUOTXTTzZCyJ7i5R5Vwb29h9BhvoLxLktFwSDnNczs0hKgyJzYg4Z270MZCz1iGgw+m4m9rh0yGUeLQbIGU7Y+pdwIA1A+mX0/F2VTW13YSgy5hrlsG3Uv1ap4HHOJRI2/QZxRwEJLcuhNVnllmb6OlqGRJjMrU0XgYWPi4WF5H65Fgw1ueLn+d4Efy8LZKW3WuWBZVY4K4B5Qp7Jx2qUsg8vCS9P1xKB9Q45BYU9HSTHDeXaATqC12kdVVlJ3p5KdraW8uoQJFaegAKh0X5kYOVyut8YiWNpWVOCWLz9e6XrFKsKKURf6gy70Of0MgzKWvP8Rb1c/Hd2YP+DAx0d4I47gaAKDvB96f//t87df3xIAfjiO7xwptjhzebdMeyNw0Cle30Mx/psZ7GsoB2O55Zh2noMtk1pZ5BK9gWHUwXJmK3Wxxc9WhuJLksqxMEc0PXXXSFBBeT5tyvIhNJHPFVX9B9FMcQq9AZs+SNNIqKJAgbHGgBPbVla3StHEaCzIabImUdcijyBqFb6mrCLZKo0ZZi7+OOq77tvRYl1cV46+1XosY1U9o/q88vpZHRXt4GG1+e7PwdwN+b907gUL681NNBXtXOd+tjZfl7n0A5eYPGYxw0VYqaXAZH3En+sGVGzZcPRVxWv0dLQygGAsfZU3WmVq9LImhYN+WW0IDYzDSmyWJCXXBb/g3FLlGfruXHRRRvrobXR2yTvvzjksWKzf3XxN3/796e7rAR+LNfpNZj4fKIStV31i9Vcjp7mlbBMnPgt0chkaOc3euio2rGJrw9fs+qW8aod+RAgnxskThfiXYNOEgELWr86TDH8JUyVXXV0LSVkL63sm55BbpVAetuGs71cfPRx3Phhp8UkTxqBV/QyLVeJqHBbb5T27nDMKjL7lbO2nikduFgXaBSooIBexUMdHDJai3ysoXJTJI5tTohShIzh1lN70kXpFhhs5peMZV+zN7rN5G8lkPGGlaZj20Ruo7RqbuShKIr+TC6/mV7ChvoH5TsfImhCHFIxsp58tPlC6m9hXpjaQlpqmmdZzXMWspA5N1uihRh/mb0U/rNtAGXUt0zJUA2KwxCtIerpGaGmpozLAwikG3zI17AW3Wp4Y7I/gGJr9P+8RcEQeYACAQ0vtvXVcXcmyKLxxd3cLwWXj7k5wCx7c3d3dggd3C8GCuweS4JCgwTW4O3ybzMwZPefMffe9e88f36JWd1dVe1d31Vqb+q0hRv2k4mH80kIWn16KO2sz8hPj8Lm3n96mv3MOykwirt1iDWOLUplMS1SMslJpnhujLRwaR9hT6Sy73RRTMPA5C3zPXSYS8ynvCo0wuFeYNhhPQRh5QtWLAwo5QbcZV++9vQEcFx6CaUpKdbyLtSpRhk4lKSdHcWZchjblB16nveAEHiju0/zmDe8Xcs3cU701ZIsvSs4Teqs0Nn3a35/tJpfoV1l8i4/jSZt4QU29OSPg7/z2mzmvphUvRMJ97ptDtnbyL2efeFxluBHRSr61edom73FBvzqt7q/N7ReKpNXWKdZQRmJ9k6GmpzntYaK78WmuIcujm0/QEMEB4IDqILCKusq8CrtKvYq7KtInHh6FRqXMtQEOkOjwXd+V/GdBHIXEg++6HZkfwrX24JLIA/ZJ4+vOkDuGvyKRCD2A/a1A7EH47wQ5cd6n8XYCJ8OSHdeDnCTXmxRL3usZvyUykVyLH/sU0CyRjeZc0Cifb+Fskl1QNKDCoMKgbVHIC+JIEAoTiuuEN8E6EDoAV1VbT6Je26GdMIh0iA9yxl6uuQuCgp3bmUquBrrY/Uij1tUfSWLR6P0oo9vVmQ6uBqbYfTqJh/7BTtxrHIpHw3X96LuoeD/gCdPPRKrqRcivGV2eGC/tyDdEtvoNoTtyGAgKjVz9PLZhJ8Qb7giIi7PqAvYPIGQxCwsa2vjrvowV7ZtF3uHtsC3xtXbyO/eJ4pDtX46lhCG7b+eGjVyOkaEQHY8poRCdjoUQtwyK4pAUR/Hb0F3UVcxMZhsqeEXy21Aje5k=
*/