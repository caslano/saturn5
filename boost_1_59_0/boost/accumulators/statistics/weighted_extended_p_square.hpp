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
CRpnmKK7bz3zjxCKNnyBrzY4u0HSWjGvZAZsL+HuQ3ckAOxwwF5ohHjEQMSff1h/mvrSwLRunpjrL/W5rIvJDef1dSyxf6XosnVfoD2vqFXPafFnOh0m7XKeh3e7+FeQ+7xvUe6JGkj2DHzCUZ4bkLkv12MV9L7FmnW3pSsDRnp8f+minJP2aUKEyO8SkQkj1+xDMEJ6vzdm6COAwCBzbj71hayAdIRdttv4ReT9iLJ5XKWttQmX6yCOZzOpl/gMIQOh2PBrFd4Yq+9j8MRbwYRjV01Fzj5eCD3IwLozLLAmQQ1YfE3PoW1QkmBfM9Oz4WNqtm9Dzrr3DhCLmI06bFdcdeihJCok3Hx3U4JuvdkKifvElLm+7jdb65AuOO08iangF/K27EpjEVsxZVbVbyZpaIhdjN9Y4BIC/v2MVsc9qIJsF9lxaU9XglICAYXJb8NJ9sI2sg0rt8ed80Q3G8OSCpN6ZuIrNEDR4GqI7ACoIGFLkmS3ZUO5385ECM4MfZrBS5A30NL2LE8b0EFejRtFbI8RV5B4CKwo25pvNR4hzW/Q9RuXmctil7WiiRH6lpnbLOtzznX5f61+C0CYDz8Wt15dI+hXuVTJGj37/MkTl1K3Wfy7jZwbh5/dQN6GaCE4v1S0kHg3ZxRiZz+Hy/3Cwul3NfdV7ejmpNDGwdSMIRGD8VkCHAQckw88T694F0QhZAk0I0RCsC9umdcYRjADhCb0R4jgtB+cyH0ThnDe2NsGqhDKCKwfREyc7CG4slaOCMBRDWZMK543UDawGEGx3da7WiuXXIFhgla76RBeME/sfoHiI/YYc7+EQqwaIKwgT6FvJW7mh6cVGpPrqe0ZRpkJagIg4KBioL7BOfMGD7Y0KBKMN2SJUcUnpmNDUXEn1Dr4c7cbkIW5NSJfRolCdi9S1Z4hivzY0zyr9qliddpDSWhi9kk3gE3xGOs0hlVepDq7cgtpYPZJRf7DFn/5aiWQFgZgyVh4JOaslQopPq8p1PhMqe76YXt0aZu/A32Z/IjlXq1u1XPuK7GgiCk3zm+vs8Ruc2QDMI8Bexpzew4zXancdIncdLHcwxxV6SzVvbuMX0cRhYGqdLqAJAVpFFWT85zKmLWJXQfQogMY2FGUxjxWKNcxS5UDwmBBwXW05CX4euegbloYy2Y3CylkAqGdN8wIT5kJzZcHzWXCoG8EL71aLkYLPEmhXy8pDON3OGZjTT3dWKqKQ7Gc6fs8I8ItIH4DgTArOhP8QRA6VQAa++PXI5FgG4g1iBtoSkhK2g3ED4HtAQ7vloQgoCFLILOh60hEGrIaSYITbe13PnsOPBgXSunQ3bx7OoEJctNWNAmvutG51/l8v3disxvnrj5iLoVDzaSHIZbJpZJpX5IbHnT7dNEZXsaWajDMTEOUT1Ej4n//VZjf3KlkyWnUj5F/MdRQig8p3+OjLNgatw9d1a70c1G36S8Im5lFSC7upjyEeM7NhCUOP2QHc8Fr55u8E+GJl45nSzig1gnJROBMp04+QYOXyHRHeOOWTZDLjVwAF0PCpfemJZJ19BLzg/Wj9M0zy5rETBgBt+Oo0JoYmlXeQqDyTdfNTSx4PlbNlkxjmcfPfjPl+IeyUddzzHG/btnlr+OQE6Wx0zx67KZcH55OiMyEPHI/EbPO1taM355NDNnvN+X3sW5StMaTgSqu0lx7ua5x2UxeCWtjU6klsmkAaTYsBRUsGXSskvfF97+Bm/3+UAZL+uMNCZTaWj9KGr95hEU7XJX1jyoDZmPQzAaGsX+aoKxZJplwdKH0xk5syDezqX0YXCdfnXXHw+fqKSNLErZvzCZcez9NskgaL2QD8JVlyXrXjmK/Yik7rLQqn6y5GHbyIRNHyTdFeRXYL7em07YWlq6YK6/bqs9Td91XAp35CfPCTL9kl/N1NG9R6ifRB01UAu5yE4fwMZQSCUp+eeJF52ues3mZeEDeARrVhRQoHidTAKQiFPyizr44vg+9k0yDtiZPs7oXkf6CsCdiFtg0QcfKprcXoQX6Ru9lVqGP60087tHyPkVNAzDEvCShceIK1TxeXXuij2G01d5oUJKaPr9qYavns2FheApl0eFeP9GkL2bYMtG17hqpUWISbFAU4EcLqO82+NJCdXJCfmKj1zk6SCHxYJwYnUOOu5bNI6haElARY+XUEWPFkjL2qvSagru3Pxf7TD2Trauaq8cu2FpEaOw7QIW83+SozT5wZCDs1uAxsNZ3WTLzjXekv3gPJdltYheFw2138/q5hHj3Rv3Is3f9zpe92fyp6FoNeWKX4AH7hmGMKVZpk8fandQfqzaayDDk50iZfZOGTt8OJ61/zJrJ0Q1ptNbyDnaLNwo9ofkleUtcfG6TIZlEcnRpyblkiV1+7dzanjyzbUazcXB117Orbt6GI7I3g11ErnD7j1Em23MI7VbfId+hKj3Wkiq9WNJOtk3bAM/ebE+9gw9dqbArCq7R0oEGAQ6CNgaq6ErPlWHCCRpaTogCHlO1z1pB24Yy4iY2XS1xCSYogsModng8luNF1w3v2ueqtWwPsqbnrpOmxhzKJzcTVpbGget01nvXrWB1bOSX7tcjdFy9QmNEP3sKpmPpI+kT881Zl2VvuBLjJyzvpXI1agdIo/FMYluaAeRFgL9uVg10Vk6ekqqNabfbh8PDRDGdeTJFQcT4+f8HtkK4sshoAIBDS+29dVwmS7ImjNO4u7vLi7s7jTfWuLu7OzTu0LhD4w6NQzfu7tq4uzbyvX3mzJw5d2bv3N39du/8sUVVZWVWZmRVZGQ+EfUj4i0W//FcG5x8LlXBKPj2BhpGtHJpYmvs5OxoYmADC7yyM7SEZWEmZib+dcHHxyQKvOFsYWcrZuBsQkwtxsPCzMwNYGHhArCycbCwMTCzUzEzU9H8pZqdIzE1sTCQhAmxormds52TuZ09sagKG7GcgZGF7a88DZOcnfEfpADMzFzM7AAuAAsbCwMz219IKTraGbsYmQBp/UdSpsAO/iAlIPC35wX88bwqFp4mxCwsTMp2ds7Ev8qVmaRtTe2If3sn4LWYFh+bCEBYhF2MWRjYP5s4lzi3MDc7KxsLNzuAhUuEVZxZgJhPVJxZhEuUjYtZFAB8XTFWETZO4AYA1ucUF+fkZBbQYfrgYW/CpKFsYsqkrgUgZiEG6DC9N7E1czYn5uICPtrvHAUBbqAgSMAzxBsoCN+vLDC1AwEFRQEBBacFHtsgoBDWIKBQ3SCgMBQgoHCkIKAIPSCgyPogoCgTIKCoZyCgaK0goOj7IKAYvSCg+dUgoAV6IP8wZk7OBo7O7o4mprBsAC4WVlgKCnEFCQpFMQkGACMnLMWP7YkZ2L9jk6KBmYkTMetvPPntTUQNnA2s7cz+YCrr38mAnYstkJlMshbGTlrsv9r8/vq/UfmjCfsfTYQdnUXs3LV+MR0AYAFyn1kHSMbW2cTW2YmY47du5UyMLQz+oZKigSOwzu9PpmziZOfiaAR8Us4/nvRXp3/0yfFHn7+zH8DBzsokYWHtbOLIJGENlDUxEyM7Y5M/xsR9OUSd19F4CIEP9LwbzjzYDmNYT3LvI083F4sYzd1rDGr4j/cK9VRiLIEESyHqD+So7n4dL7fFlueBemhbb+dEILsrHBOfrhk35DX7uc+JFL4Qhr+8Bh8uvwZLpx/+vK+9QyVytlhNrGaeWQ2y0Xy0eEHzcbnCuHO/V2BrD3p5+/yzqjr7je8R1gvnnhHu+BwLcedIoWqgXOGb0DF1rcnHF7FmClNOWz3deSodHevG2zKGuicJXt7vwRpqT5mRr9nzQuoEAiqpFXUliXhIUfd6E6oVGjnzFhVXVE/nVDefDzz8vsVcSyN9Hlq2mmBtlnlH5ibITcggOFLvhMzrgnJsfBZzRw8KQ5UKE9hHks41ohBQEbqn39L4JPGsN8pUk2VVsYYf6ykWII7zaST9tHJ56YIgXjnolqjS6JyayBaf4SPVEfw0p2svHaVtzSZ88buLvTqtYvcJ7jZHwRq5rvDPs9wK+GCP8ZHnClnNmBGvzo4tc/UupA6CFVYDvdjJzzefSNan79V13l5O9bI4+aSHWBrEiPXLhD+Vvm/iF1qIoe6WTTQeu18ft1OoSPxuJU4Hj/Ss0YPDIpHxNNrWnT2KnmrTi2qdpYA6uG88g5ZkyMSFa3MVIxPoUZFD/yFZd/OIfUMmb6qYDn4IdGKP3HcZTnZWiOgclBI2YjdI0AbBMG2ITyX++zhcq2YTmmicmRv8vA8/TvdEC76YFZntejTxJKh3DIVveEBj31ewZCnf4xCq6P1PkkH4Y6Z+tZSgOoArmIoY/gqBJstWs7CBkluYB85bSEAaXUP55Ag4FhIv6GIAJntT/TXHMxY1SteAD3JcDACdoTHz1Rl68prJGgfTZ8y0Xkopr2yI9wPpCpqF5lBuZ0Dmic2lzbfFk+4fe6IVikf4znRWjGMnZlbo4gJWpvrrGgWj8d85jUNlKAlbfD7AwfbTS4Vq9dYsz0kgodtm87cLSDmsHMAma7GLM2zf8/lzEKbR90A7oqtqHwRs5dqEb9jX1MMsVR9yQzSA3REFVfXhgo5dvmLRY55DQOHoBD22OjGCj7E9iphR5WR3amHiJiJwYgHcR8sKjGnVTVDJ+tO4e4TE7H2mYZdH22Fpe7mEXKTzBLEJPW5rJUOGMoO/srjq+zpnf/Fy4AAL6o0SVFzPkPsaTQ5P+7niBj/2MhwP0ebOWCROKa1HsTGtVogE7NEfdYbgpyELf9gQbhrSoobVWDDUcuGmNPDNrptb+DReT4ZKrBA9Y0HSR4QjdZzea+rGyA9n3GSjwOOTkvBIhx3MYYg4+02NVWnE20vBmeJRfIldXtVwuSPENbhy/TnZAj6WpUOcGjd2UBr48wNKk5uRIt7QIQizu0JfvDM17NwM4sOg7uIx9T7LE0QppR5zdoi3kCsGNNMK8sMFSOPCR/W5qDIoVPd1hMO0wxlQRc0Kcha8WJznA8Tu6wXzzB5vZxRakGpKkncFEnRbALJpvha+s6aQM878LziOG1QkMHSlV8QT+fJGJYk0UFJg6XIAT3WNTFXsMGJxrJowd5s9cyrznmiUNSxxcf9EjXNzH+QDblZIMOiWqYrpNlEDYmqveyFylr1MY7v4hn7t1LRPark7710XYzsb9wBn1ZoZ1r5jA9BuHdGQ8dSfTqPMt0CURXSsTYyq85RKvqd/3z/zzMmSz+9L34UZOSxr5QtlTYKh9lMSaqvs3gFsxHUeghXKm7aINCXCYd2MSaL6qsBLScYv6ytzia6Yl6XQGYJYRLvbetwrtSSAdAqdJpiLPLfYNwrVWh/U0K1Xm88envQU8MDBDiPFCn7i4ajRVOJwVSTjrr1azOxVoSnXSKiRngOXyAHJwTmfNvp0z7tsPPHu+7NRWPX2T1SI2DPqFv9vXRbvz7m9zmSDvo4jfysbcgDtyhOoz80F8dAzvFgH2zAjiP+eXFooGagND2lLr2iG941Uj31+7vkCJ/JTYBB2rzVKlvg7kR6JkLMFnQL0dJ7ogISztqo85B7To/tkk+tvgaa1LXjfxISF34fW+cL2KbfBwUBAR7iEGBpgXOuxqNekDuqxPLdiQsJ+WkskGeVIIbOGANxvI+RDqaRdVmKnq5vGCd96zNUgvl5kY3gavcUXLCwFV83R2wleIZb2yRciHRs2e96asny2uwAALP/TEmrBrvB4uSbk5K7G1RgL0/wCCnlhNc+T8eb9c2Jl4+2S5Nzv+f50gvP55fFO8AqGUukfAJvzD+ASd3eWVHEGIhXwWlIFADwDlR1nRxcgZgkI/NKHjFRMnLWYgGDO9MHE3ZlJ2gYIgSJ/SUT/kkjrMGkoGFqaGDkDW0vbMBNz/QLMX+3/2h/XH/39RXX5S3UmFRdD51/538gwiVg4OymaOIra2djb2f4CYi4gbFvbOarYGxiZMImZuFoYmShLivwVX8VEP/wFXf8KvsCNjYWZSd3C+BcSA1iYpEwszIDKOBDb/wDgt8W3TRBkGQlpCaAe9Es/Ap7eVkBEQd5BQUFDQb6DhoaGgXkHC4+OAA8HB4+DioaEToBLREiAi49PTM5IRUxKT4aPT81JQ88MYGNjI6Li5udi4WMEqnC/iIDCwMDAw8FjIyBgs5Dgk7D8T29v3SAo70AGQezBQUlBwFBAwVFA33pBMH571D9t74DF6Mj/sRTkVynoPy1F+cfSZRB4cFBgL+AoIIIgOd0g/x4b9NvSP8gr939mEwCAGwuAmYudmY3rv2QTsP+PbYLfSAFYmDnZWf9G6n/eJgAw/webAAD4B5uA+28mAUCYg5uLS0JcnIOdg02Yk42LW0KcW5RLQpiNRQwgzAIAmgScnCIc4kBbgYsZwCIsJiomwiUuzgYQFQOwcouwAzhE/lOTgI3tv2ASgABNAehMENB38CCgsO+Bx8//TM0HmmCAfyMtn5OVmAXwn+v4v1f539fwWTlZ/oWC35g4IiMKQA7NIT6PK4K12U9YsRaHTA0Bt23lJSXll/F5C0l0GpRb42BwfpC6ers28wRgoS0F+r5byPFQgvCyfycy/oPQufbeVYlWAKY3O5tVDrtbWDJ5ty+BDrFbS1XzCgVjZekGnaBIqG5NkwYiZbOHI4vAWoRk0bQ0yGm/6/vjx+5eT8N2UvVNycr+iPLbeRlZ6P2AJt1IxZyhjfdm17a6Z6Ml3HxM+kSdow7vBNWVQr7hCsRhhc9O0X9HsV+j6bZ00Q+6lYE+ToaVkmJc1pXk4x7enuKmtT7rz5u6PcwHz2XOTD0hi+aJRthWPGRGTG4SyJAfKQBWeOWccIomkD25Twx3feIIoxplMi7h5A8nnK1kTo4fPFY/DUfbUWt05RGYuj6KNfzUwmpW0ndir4DecVY7U97CfTiFFmxvVRJrRXMkMPCDj+y27N1ZRBn3jyRqkkfhpMuy/IDbt72QbeKImggB+cc8Cy/zF8IxpDa/J9v/dXyTAIoMsEgC8FfM+l9EvN9nsw2AGPC7rW8DnIKA/wQHRQycTH71zqQpp6CmrkinZuJobGBrAIQ5JyNgbQNb5193nbSAtulvs0HcFihnFrZmTNLGQAm2cPZgkGKSN7AxAT7732D0lwAzM32wU7W1+CWUxIC/m32/qP3xINz/lwAZwM32Ox5zsv4NjgF/QuMzEMTf1lUQ47+g0v8vWPwbjGKASIODoICAogAx7hcGYgGXOfA/gw0oFPT/AEh/geOvtRIMBAiOY4rN/xys/glW/f3i/3+Ut5xADeffhrd4v1gF/ifVAwwCFBwaEgp4kxEZBAQcEvId+B/sBwUDh0BBV4KEwlSOR0UjUVFNyJsGCBcY5Nf9mfM/ZUtdrK0kzng6Onnw1E7lvGQ4yplCcLDAWJ5IljVqTYvFiigp/QbP+gvICOdh2rJ47y1OOGxxTK6M8MwUezidSnxP+YPsR5gSEeq/6Ge0zHS5Zvd8NUkdCl2aZZZbPdxoU9BfZRnZ+W59hE155ny+VlLzq7FBkws8mhuP29nMIid83SPzCk/o77TxQjW9P9tkieMZ7i8y3tFduyJKjJVTwpmHoJlkwieYasNv3ZBOBZGaFpB3DxZcschwxaijyJMqEcjvdZRiKQ2RS281
*/