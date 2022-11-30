/* boost random/hyperexponential_distribution.hpp header file
 *
 * Copyright Marco Guazzone 2014
 * Distributed under the Boost Software License, Version 1.0. (See
 * accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org for most recent version including documentation.
 *
 * Much of the code here taken by boost::math::hyperexponential_distribution.
 * To this end, we would like to thank Paul Bristow and John Maddock for their
 * valuable feedback.
 *
 * \author Marco Guazzone (marco.guazzone@gmail.com)
 */

#ifndef BOOST_RANDOM_HYPEREXPONENTIAL_DISTRIBUTION_HPP
#define BOOST_RANDOM_HYPEREXPONENTIAL_DISTRIBUTION_HPP


#include <boost/config.hpp>
#include <boost/core/cmath.hpp>
#include <boost/random/detail/operators.hpp>
#include <boost/random/detail/vector_io.hpp>
#include <boost/random/discrete_distribution.hpp>
#include <boost/random/exponential_distribution.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/size.hpp>
#include <boost/type_traits/has_pre_increment.hpp>
#include <cassert>
#include <cmath>
#include <cstddef>
#include <iterator>
#ifndef BOOST_NO_CXX11_HDR_INITIALIZER_LIST
# include <initializer_list>
#endif // BOOST_NO_CXX11_HDR_INITIALIZER_LIST
#include <iostream>
#include <limits>
#include <numeric>
#include <vector>


namespace boost { namespace random {

namespace hyperexp_detail {

template <typename T>
std::vector<T>& normalize(std::vector<T>& v)
{
    if (v.size() == 0)
    {
        return v;
    }

    const T sum = std::accumulate(v.begin(), v.end(), static_cast<T>(0));
    T final_sum = 0;

    const typename std::vector<T>::iterator end = --v.end();
    for (typename std::vector<T>::iterator it = v.begin();
         it != end;
         ++it)
    {
        *it /= sum;
        final_sum += *it;
    }
    *end = 1-final_sum; // avoids round off errors thus ensuring the probabilities really sum to 1

    return v;
}

template <typename RealT>
bool check_probabilities(std::vector<RealT> const& probabilities)
{
    const std::size_t n = probabilities.size();
    RealT sum = 0;
    for (std::size_t i = 0; i < n; ++i)
    {
        if (probabilities[i] < 0
            || probabilities[i] > 1
            || !(boost::core::isfinite)(probabilities[i]))
        {
            return false;
        }
        sum += probabilities[i];
    }

    //NOTE: the check below seems to fail on some architectures.
    //      So we commented it.
    //// - We try to keep phase probabilities correctly normalized in the distribution constructors
    //// - However in practice we have to allow for a very slight divergence from a sum of exactly 1:
    ////if (std::abs(sum-1) > (std::numeric_limits<RealT>::epsilon()*2))
    //// This is from Knuth "The Art of Computer Programming: Vol.2, 3rd Ed", and can be used to
    //// check is two numbers are approximately equal
    //const RealT one = 1;
    //const RealT tol = std::numeric_limits<RealT>::epsilon()*2.0;
    //if (std::abs(sum-one) > (std::max(std::abs(sum), std::abs(one))*tol))
    //{
    //    return false;
    //}

    return true;
}

template <typename RealT>
bool check_rates(std::vector<RealT> const& rates)
{
    const std::size_t n = rates.size();
    for (std::size_t i = 0; i < n; ++i)
    {
        if (rates[i] <= 0
            || !(boost::core::isfinite)(rates[i]))
        {
            return false;
        }
    }
    return true;
}

template <typename RealT>
bool check_params(std::vector<RealT> const& probabilities, std::vector<RealT> const& rates)
{
    if (probabilities.size() != rates.size())
    {
        return false;
    }

    return check_probabilities(probabilities)
           && check_rates(rates);
}

} // Namespace hyperexp_detail


/**
 * The hyperexponential distribution is a real-valued continuous distribution
 * with two parameters, the <em>phase probability vector</em> \c probs and the
 * <em>rate vector</em> \c rates.
 *
 * A \f$k\f$-phase hyperexponential distribution is a mixture of \f$k\f$
 * exponential distributions.
 * For this reason, it is also referred to as <em>mixed exponential
 * distribution</em> or <em>parallel \f$k\f$-phase exponential
 * distribution</em>.
 *
 * A \f$k\f$-phase hyperexponential distribution is characterized by two
 * parameters, namely a <em>phase probability vector</em> \f$\mathbf{\alpha}=(\alpha_1,\ldots,\alpha_k)\f$ and a <em>rate vector</em> \f$\mathbf{\lambda}=(\lambda_1,\ldots,\lambda_k)\f$.
 *
 * A \f$k\f$-phase hyperexponential distribution is frequently used in
 * <em>queueing theory</em> to model the distribution of the superposition of
 * \f$k\f$ independent events, like, for instance, the  service time distribution
 * of a queueing station with \f$k\f$ servers in parallel where the \f$i\f$-th
 * server is chosen with probability \f$\alpha_i\f$ and its service time
 * distribution is an exponential distribution with rate \f$\lambda_i\f$
 * (Allen,1990; Papadopolous et al.,1993; Trivedi,2002).
 *
 * For instance, CPUs service-time distribution in a computing system has often
 * been observed to possess such a distribution (Rosin,1965).
 * Also, the arrival of different types of customer to a single queueing station
 * is often modeled as a hyperexponential distribution (Papadopolous et al.,1993).
 * Similarly, if a product manufactured in several parallel assemply lines and
 * the outputs are merged, the failure density of the overall product is likely
 * to be hyperexponential (Trivedi,2002).
 *
 * Finally, since the hyperexponential distribution exhibits a high Coefficient
 * of Variation (CoV), that is a CoV > 1, it is especially suited to fit
 * empirical data with large CoV (Feitelson,2014; Wolski et al.,2013) and to
 * approximate <em>long-tail probability distributions</em> (Feldmann et al.,1998).
 *
 * See (Boost,2014) for more information and examples.
 *
 * A \f$k\f$-phase hyperexponential distribution has a probability density
 * function
 * \f[
 *  f(x) = \sum_{i=1}^k \alpha_i \lambda_i e^{-x\lambda_i}
 * \f]
 * where:
 * - \f$k\f$ is the <em>number of phases</em> and also the size of the input
 *   vector parameters,
 * - \f$\mathbf{\alpha}=(\alpha_1,\ldots,\alpha_k)\f$ is the <em>phase probability
 *   vector</em> parameter, and
 * - \f$\mathbf{\lambda}=(\lambda_1,\ldots,\lambda_k)\f$ is the <em>rate vector</em>
 *   parameter.
 * .
 *
 * Given a \f$k\f$-phase hyperexponential distribution with phase probability
 * vector \f$\mathbf{\alpha}\f$ and rate vector \f$\mathbf{\lambda}\f$, the
 * random variate generation algorithm consists of the following steps (Tyszer,1999):
 * -# Generate a random variable \f$U\f$ uniformly distribution on the interval \f$(0,1)\f$.
 * -# Use \f$U\f$ to select the appropriate \f$\lambda_i\f$ (e.g., the
 *  <em>alias method</em> can possibly be used for this step).
 * -# Generate an exponentially distributed random variable \f$X\f$ with rate parameter \f$\lambda_i\f$.
 * -# Return \f$X\f$.
 * .
 *
 * References:
 * -# A.O. Allen, <em>Probability, Statistics, and Queuing Theory with Computer Science Applications, Second Edition</em>, Academic Press, 1990.
 * -# Boost C++ Libraries, <em>Boost.Math / Statistical Distributions: Hyperexponential Distribution</em>, Online: http://www.boost.org/doc/libs/release/libs/math/doc/html/dist.html , 2014.
 * -# D.G. Feitelson, <em>Workload Modeling for Computer Systems Performance Evaluation</em>, Cambridge University Press, 2014
 * -# A. Feldmann and W. Whitt, <em>Fitting mixtures of exponentials to long-tail distributions to analyze network performance models</em>, Performance Evaluation 31(3-4):245, doi:10.1016/S0166-5316(97)00003-5, 1998.
 * -# H.T. Papadopolous, C. Heavey and J. Browne, <em>Queueing Theory in Manufacturing Systems Analysis and Design</em>, Chapman & Hall/CRC, 1993, p. 35.
 * -# R.F. Rosin, <em>Determining a computing center environment</em>, Communications of the ACM 8(7):463-468, 1965.
 * -# K.S. Trivedi, <em>Probability and Statistics with Reliability, Queueing, and Computer Science Applications</em>, John Wiley & Sons, Inc., 2002.
 * -# J. Tyszer, <em>Object-Oriented Computer Simulation of Discrete-Event Systems</em>, Springer, 1999.
 * -# Wikipedia, <em>Hyperexponential Distribution</em>, Online: http://en.wikipedia.org/wiki/Hyperexponential_distribution , 2014.
 * -# Wolfram Mathematica, <em>Hyperexponential Distribution</em>, Online: http://reference.wolfram.com/language/ref/HyperexponentialDistribution.html , 2014.
 * .
 *
 * \author Marco Guazzone (marco.guazzone@gmail.com)
 */
template<class RealT = double>
class hyperexponential_distribution
{
    public: typedef RealT result_type;
    public: typedef RealT input_type;


    /**
     * The parameters of a hyperexponential distribution.
     *
     * Stores the <em>phase probability vector</em> and the <em>rate vector</em>
     * of the hyperexponential distribution.
     *
     * \author Marco Guazzone (marco.guazzone@gmail.com)
     */
    public: class param_type
    {
        public: typedef hyperexponential_distribution distribution_type;

        /**
         * Constructs a \c param_type with the default parameters
         * of the distribution.
         */
        public: param_type()
        : probs_(1, 1),
          rates_(1, 1)
        {
        }

        /**
         * Constructs a \c param_type from the <em>phase probability vector</em>
         * and <em>rate vector</em> parameters of the distribution.
         *
         * The <em>phase probability vector</em> parameter is given by the range
         * defined by [\a prob_first, \a prob_last) iterator pair, and the
         * <em>rate vector</em> parameter is given by the range defined by
         * [\a rate_first, \a rate_last) iterator pair.
         *
         * \tparam ProbIterT Must meet the requirements of \c InputIterator concept (ISO,2014,sec. 24.2.3 [input.iterators]).
         * \tparam RateIterT Must meet the requirements of \c InputIterator concept (ISO,2014,sec. 24.2.3 [input.iterators]).
         *
         * \param prob_first The iterator to the beginning of the range of non-negative real elements representing the phase probabilities; if elements don't sum to 1, they are normalized.
         * \param prob_last The iterator to the ending of the range of non-negative real elements representing the phase probabilities; if elements don't sum to 1, they are normalized.
         * \param rate_first The iterator to the beginning of the range of non-negative real elements representing the rates.
         * \param rate_last The iterator to the ending of the range of non-negative real elements representing the rates.
         *
         * References:
         * -# ISO, <em>ISO/IEC 14882-2014: Information technology - Programming languages - C++</em>, 2014
         * .
         */
        public: template <typename ProbIterT, typename RateIterT>
                param_type(ProbIterT prob_first, ProbIterT prob_last,
                           RateIterT rate_first, RateIterT rate_last)
        : probs_(prob_first, prob_last),
          rates_(rate_first, rate_last)
        {
            hyperexp_detail::normalize(probs_);

            assert( hyperexp_detail::check_params(probs_, rates_) );
        }

        /**
         * Constructs a \c param_type from the <em>phase probability vector</em>
         * and <em>rate vector</em> parameters of the distribution.
         *
         * The <em>phase probability vector</em> parameter is given by the range
         * defined by \a prob_range, and the <em>rate vector</em> parameter is
         * given by the range defined by \a rate_range.
         *
         * \tparam ProbRangeT Must meet the requirements of <a href="boost:/libs/range/doc/html/range/concepts.html">Range</a> concept.
         * \tparam RateRangeT Must meet the requirements of <a href="boost:/libs/range/doc/html/range/concepts.html">Range</a> concept.
         *
         * \param prob_range The range of non-negative real elements representing the phase probabilities; if elements don't sum to 1, they are normalized.
         * \param rate_range The range of positive real elements representing the rates.
         *
         * \note
         *  The final \c disable_if parameter is an implementation detail that
         *  differentiates between this two argument constructor and the
         *  iterator-based two argument constructor described below.
         */
        //  We SFINAE this out of existance if either argument type is
        //  incrementable as in that case the type is probably an iterator:
        public: template <typename ProbRangeT, typename RateRangeT>
                param_type(ProbRangeT const& prob_range,
                           RateRangeT const& rate_range,
                           typename boost::disable_if_c<boost::has_pre_increment<ProbRangeT>::value || boost::has_pre_increment<RateRangeT>::value>::type* = 0)
        : probs_(boost::begin(prob_range), boost::end(prob_range)),
          rates_(boost::begin(rate_range), boost::end(rate_range))
        {
            hyperexp_detail::normalize(probs_);

            assert( hyperexp_detail::check_params(probs_, rates_) );
        }

        /**
         * Constructs a \c param_type from the <em>rate vector</em> parameter of
         * the distribution and with equal phase probabilities.
         *
         * The <em>rate vector</em> parameter is given by the range defined by
         * [\a rate_first, \a rate_last) iterator pair, and the <em>phase
         * probability vector</em> parameter is set to the equal phase
         * probabilities (i.e., to a vector of the same length \f$k\f$ of the
         * <em>rate vector</em> and with each element set to \f$1.0/k\f$).
         *
         * \tparam RateIterT Must meet the requirements of \c InputIterator concept (ISO,2014,sec. 24.2.3 [input.iterators]).
         * \tparam RateIterT2 Must meet the requirements of \c InputIterator concept (ISO,2014,sec. 24.2.3 [input.iterators]).
         *
         * \param rate_first The iterator to the beginning of the range of non-negative real elements representing the rates.
         * \param rate_last The iterator to the ending of the range of non-negative real elements representing the rates.
         *
         * \note
         *  The final \c disable_if parameter is an implementation detail that
         *  differentiates between this two argument constructor and the
         *  range-based two argument constructor described above.
         *
         * References:
         * -# ISO, <em>ISO/IEC 14882-2014: Information technology - Programming languages - C++</em>, 2014
         * .
         */
        //  We SFINAE this out of existance if the argument type is
        //  incrementable as in that case the type is probably an iterator.
        public: template <typename RateIterT>
                param_type(RateIterT rate_first, 
                           RateIterT rate_last,  
                           typename boost::enable_if_c<boost::has_pre_increment<RateIterT>::value>::type* = 0)
        : probs_(std::distance(rate_first, rate_last), 1), // will be normalized below
          rates_(rate_first, rate_last)
        {
            assert(probs_.size() == rates_.size());
        }

        /**
         * Constructs a @c param_type from the "rates" parameters
         * of the distribution and with equal phase probabilities.
         *
         * The <em>rate vector</em> parameter is given by the range defined by
         * \a rate_range, and the <em>phase probability vector</em> parameter is
         * set to the equal phase probabilities (i.e., to a vector of the same
         * length \f$k\f$ of the <em>rate vector</em> and with each element set
         * to \f$1.0/k\f$).
         *
         * \tparam RateRangeT Must meet the requirements of <a href="boost:/libs/range/doc/html/range/concepts.html">Range</a> concept.
         *
         * \param rate_range The range of positive real elements representing the rates.
         */
        public: template <typename RateRangeT>
                param_type(RateRangeT const& rate_range)
        : probs_(boost::size(rate_range), 1), // Will be normalized below
          rates_(boost::begin(rate_range), boost::end(rate_range))
        {
            hyperexp_detail::normalize(probs_);

            assert( hyperexp_detail::check_params(probs_, rates_) );
        }

#ifndef BOOST_NO_CXX11_HDR_INITIALIZER_LIST
        /**
         * Constructs a \c param_type from the <em>phase probability vector</em>
         * and <em>rate vector</em> parameters of the distribution.
         *
         * The <em>phase probability vector</em> parameter is given by the
         * <em>brace-init-list</em> (ISO,2014,sec. 8.5.4 [dcl.init.list])
         * defined by \a l1, and the <em>rate vector</em> parameter is given by the
         * <em>brace-init-list</em> (ISO,2014,sec. 8.5.4 [dcl.init.list])
         * defined by \a l2.
         *
         * \param l1 The initializer list for inizializing the phase probability vector.
         * \param l2 The initializer list for inizializing the rate vector.
         *
         * References:
         * -# ISO, <em>ISO/IEC 14882-2014: Information technology - Programming languages - C++</em>, 2014
         * .
         */
        public: param_type(std::initializer_list<RealT> l1, std::initializer_list<RealT> l2)
        : probs_(l1.begin(), l1.end()),
          rates_(l2.begin(), l2.end())
        {
            hyperexp_detail::normalize(probs_);

            assert( hyperexp_detail::check_params(probs_, rates_) );
        }

        /**
         * Constructs a \c param_type from the <em>rate vector</em> parameter
         * of the distribution and with equal phase probabilities.
         *
         * The <em>rate vector</em> parameter is given by the
         * <em>brace-init-list</em> (ISO,2014,sec. 8.5.4 [dcl.init.list])
         * defined by \a l1, and the <em>phase probability vector</em> parameter is
         * set to the equal phase probabilities (i.e., to a vector of the same
         * length \f$k\f$ of the <em>rate vector</em> and with each element set
         * to \f$1.0/k\f$).
         *
         * \param l1 The initializer list for inizializing the rate vector.
         *
         * References:
         * -# ISO, <em>ISO/IEC 14882-2014: Information technology - Programming languages - C++</em>, 2014
         * .
         */
        public: param_type(std::initializer_list<RealT> l1)
        : probs_(std::distance(l1.begin(), l1.end()), 1), // Will be normalized below
          rates_(l1.begin(), l1.end())
        {
            hyperexp_detail::normalize(probs_);

            assert( hyperexp_detail::check_params(probs_, rates_) );
        }
#endif // BOOST_NO_CXX11_HDR_INITIALIZER_LIST

        /**
         * Gets the <em>phase probability vector</em> parameter of the distribtuion.
         *
         * \return The <em>phase probability vector</em> parameter of the distribution.
         *
         * \note
         *  The returned probabilities are the normalized version of the ones
         *  passed at construction time.
         */
        public: std::vector<RealT> probabilities() const
        {
            return probs_;
        }

        /**
         * Gets the <em>rate vector</em> parameter of the distribtuion.
         *
         * \return The <em>rate vector</em> parameter of the distribution.
         */
        public: std::vector<RealT> rates() const
        {
            return rates_;
        }

        /** Writes a \c param_type to a \c std::ostream. */
        public: BOOST_RANDOM_DETAIL_OSTREAM_OPERATOR(os, param_type, param)
        {
            detail::print_vector(os, param.probs_);
            os << ' ';
            detail::print_vector(os, param.rates_);

            return os;
        }

        /** Reads a \c param_type from a \c std::istream. */
        public: BOOST_RANDOM_DETAIL_ISTREAM_OPERATOR(is, param_type, param)
        {
            // NOTE: if \c std::ios_base::exceptions is set, the code below may
            //       throw in case of a I/O failure.
            //       To prevent leaving the state of \c param inconsistent:
            //       - if an exception is thrown, the state of \c param is left
            //         unchanged (i.e., is the same as the one at the beginning
            //         of the function's execution), and
            //       - the state of \c param only after reading the whole input.

            std::vector<RealT> probs;
            std::vector<RealT> rates;

            // Reads probability and rate vectors
            detail::read_vector(is, probs);
            if (!is)
            {
                return is;
            }
            is >> std::ws;
            detail::read_vector(is, rates);
            if (!is)
            {
                return is;
            }

            // Update the state of the param_type object
            if (probs.size() > 0)
            {
                param.probs_.swap(probs);
                probs.clear();
            }
            if (rates.size() > 0)
            {
                param.rates_.swap(rates);
                rates.clear();
            }

            // Adjust vector sizes (if needed)
            if (param.probs_.size() != param.rates_.size()
                || param.probs_.size() == 0)
            {
                const std::size_t np = param.probs_.size();
                const std::size_t nr = param.rates_.size();

                if (np > nr)
                {
                    param.rates_.resize(np, 1);
                }
                else if (nr > np)
                {
                    param.probs_.resize(nr, 1);
                }
                else
                {
                    param.probs_.resize(1, 1);
                    param.rates_.resize(1, 1);
                }
            }

            // Normalize probabilities
            // NOTE: this cannot be done earlier since the probability vector
            //       can be changed due to size conformance
            hyperexp_detail::normalize(param.probs_);

            //post: vector size conformance
            assert(param.probs_.size() == param.rates_.size());

            return is;
        }

        /** Returns true if the two sets of parameters are the same. */
        public: BOOST_RANDOM_DETAIL_EQUALITY_OPERATOR(param_type, lhs, rhs)
        {
            return lhs.probs_ == rhs.probs_
                   && lhs.rates_ == rhs.rates_;
        }
        
        /** Returns true if the two sets of parameters are the different. */
        public: BOOST_RANDOM_DETAIL_INEQUALITY_OPERATOR(param_type)


        private: std::vector<RealT> probs_; ///< The <em>phase probability vector</em> parameter of the distribution
        private: std::vector<RealT> rates_; ///< The <em>rate vector</em> parameter of the distribution
    }; // param_type


    /**
     * Constructs a 1-phase \c hyperexponential_distribution (i.e., an
     * exponential distribution) with rate 1.
     */
    public: hyperexponential_distribution()
    : dd_(std::vector<RealT>(1, 1)),
      rates_(1, 1)
    {
        // empty
    }

    /**
     * Constructs a \c hyperexponential_distribution from the <em>phase
     * probability vector</em> and <em>rate vector</em> parameters of the
     * distribution.
     *
     * The <em>phase probability vector</em> parameter is given by the range
     * defined by [\a prob_first, \a prob_last) iterator pair, and the
     * <em>rate vector</em> parameter is given by the range defined by
     * [\a rate_first, \a rate_last) iterator pair.
     *
     * \tparam ProbIterT Must meet the requirements of \c InputIterator concept (ISO,2014,sec. 24.2.3 [input.iterators]).
     * \tparam RateIterT Must meet the requirements of \c InputIterator concept (ISO,2014,sec. 24.2.3 [input.iterators]).
     *
     * \param prob_first The iterator to the beginning of the range of non-negative real elements representing the phase probabilities; if elements don't sum to 1, they are normalized.
     * \param prob_last The iterator to the ending of the range of non-negative real elements representing the phase probabilities; if elements don't sum to 1, they are normalized.
     * \param rate_first The iterator to the beginning of the range of non-negative real elements representing the rates.
     * \param rate_last The iterator to the ending of the range of non-negative real elements representing the rates.
     *
     * References:
     * -# ISO, <em>ISO/IEC 14882-2014: Information technology - Programming languages - C++</em>, 2014
     * .
     */
    public: template <typename ProbIterT, typename RateIterT>
            hyperexponential_distribution(ProbIterT prob_first, ProbIterT prob_last,
                                          RateIterT rate_first, RateIterT rate_last)
    : dd_(prob_first, prob_last),
      rates_(rate_first, rate_last)
    {
        assert( hyperexp_detail::check_params(dd_.probabilities(), rates_) );
    }

    /**
     * Constructs a \c hyperexponential_distribution from the <em>phase
     * probability vector</em> and <em>rate vector</em> parameters of the
     * distribution.
     *
     * The <em>phase probability vector</em> parameter is given by the range
     * defined by \a prob_range, and the <em>rate vector</em> parameter is
     * given by the range defined by \a rate_range.
     *
     * \tparam ProbRangeT Must meet the requirements of <a href="boost:/libs/range/doc/html/range/concepts.html">Range</a> concept.
     * \tparam RateRangeT Must meet the requirements of <a href="boost:/libs/range/doc/html/range/concepts.html">Range</a> concept.
     *
     * \param prob_range The range of non-negative real elements representing the phase probabilities; if elements don't sum to 1, they are normalized.
     * \param rate_range The range of positive real elements representing the rates.
     *
     * \note
     *  The final \c disable_if parameter is an implementation detail that
     *  differentiates between this two argument constructor and the
     *  iterator-based two argument constructor described below.
     */
    //  We SFINAE this out of existance if either argument type is
    //  incrementable as in that case the type is probably an iterator:
    public: template <typename ProbRangeT, typename RateRangeT>
            hyperexponential_distribution(ProbRangeT const& prob_range,
                                          RateRangeT const& rate_range,
                                          typename boost::disable_if_c<boost::has_pre_increment<ProbRangeT>::value || boost::has_pre_increment<RateRangeT>::value>::type* = 0)
    : dd_(prob_range),
      rates_(boost::begin(rate_range), boost::end(rate_range))
    {
        assert( hyperexp_detail::check_params(dd_.probabilities(), rates_) );
    }

    /**
     * Constructs a \c hyperexponential_distribution from the <em>rate
     * vector</em> parameter of the distribution and with equal phase
     * probabilities.
     *
     * The <em>rate vector</em> parameter is given by the range defined by
     * [\a rate_first, \a rate_last) iterator pair, and the <em>phase
     * probability vector</em> parameter is set to the equal phase
     * probabilities (i.e., to a vector of the same length \f$k\f$ of the
     * <em>rate vector</em> and with each element set to \f$1.0/k\f$).
     *
     * \tparam RateIterT Must meet the requirements of \c InputIterator concept (ISO,2014,sec. 24.2.3 [input.iterators]).
     * \tparam RateIterT2 Must meet the requirements of \c InputIterator concept (ISO,2014,sec. 24.2.3 [input.iterators]).
     *
     * \param rate_first The iterator to the beginning of the range of non-negative real elements representing the rates.
     * \param rate_last The iterator to the ending of the range of non-negative real elements representing the rates.
     *
     * \note
     *  The final \c disable_if parameter is an implementation detail that
     *  differentiates between this two argument constructor and the
     *  range-based two argument constructor described above.
     *
     * References:
     * -# ISO, <em>ISO/IEC 14882-2014: Information technology - Programming languages - C++</em>, 2014
     * .
     */
    //  We SFINAE this out of existance if the argument type is
    //  incrementable as in that case the type is probably an iterator.
    public: template <typename RateIterT>
            hyperexponential_distribution(RateIterT rate_first,
                                          RateIterT rate_last,
                                          typename boost::enable_if_c<boost::has_pre_increment<RateIterT>::value>::type* = 0)
    : dd_(std::vector<RealT>(std::distance(rate_first, rate_last), 1)),
      rates_(rate_first, rate_last)
    {
        assert( hyperexp_detail::check_params(dd_.probabilities(), rates_) );
    }

    /**
     * Constructs a @c param_type from the "rates" parameters
     * of the distribution and with equal phase probabilities.
     *
     * The <em>rate vector</em> parameter is given by the range defined by
     * \a rate_range, and the <em>phase probability vector</em> parameter is
     * set to the equal phase probabilities (i.e., to a vector of the same
     * length \f$k\f$ of the <em>rate vector</em> and with each element set
     * to \f$1.0/k\f$).
     *
     * \tparam RateRangeT Must meet the requirements of <a href="boost:/libs/range/doc/html/range/concepts.html">Range</a> concept.
     *
     * \param rate_range The range of positive real elements representing the rates.
     */
    public: template <typename RateRangeT>
            hyperexponential_distribution(RateRangeT const& rate_range)
    : dd_(std::vector<RealT>(boost::size(rate_range), 1)),
      rates_(boost::begin(rate_range), boost::end(rate_range))
    {
        assert( hyperexp_detail::check_params(dd_.probabilities(), rates_) );
    }

    /**
     * Constructs a \c hyperexponential_distribution from its parameters.
     *
     * \param param The parameters of the distribution.
     */
    public: explicit hyperexponential_distribution(param_type const& param)
    : dd_(param.probabilities()),
      rates_(param.rates())
    {
        assert( hyperexp_detail::check_params(dd_.probabilities(), rates_) );
    }

#ifndef BOOST_NO_CXX11_HDR_INITIALIZER_LIST
    /**
     * Constructs a \c hyperexponential_distribution from the <em>phase
     * probability vector</em> and <em>rate vector</em> parameters of the
     * distribution.
     *
     * The <em>phase probability vector</em> parameter is given by the
     * <em>brace-init-list</em> (ISO,2014,sec. 8.5.4 [dcl.init.list])
     * defined by \a l1, and the <em>rate vector</em> parameter is given by the
     * <em>brace-init-list</em> (ISO,2014,sec. 8.5.4 [dcl.init.list])
     * defined by \a l2.
     *
     * \param l1 The initializer list for inizializing the phase probability vector.
     * \param l2 The initializer list for inizializing the rate vector.
     *
     * References:
     * -# ISO, <em>ISO/IEC 14882-2014: Information technology - Programming languages - C++</em>, 2014
     * .
     */
    public: hyperexponential_distribution(std::initializer_list<RealT> const& l1, std::initializer_list<RealT> const& l2)
    : dd_(l1.begin(), l1.end()),
      rates_(l2.begin(), l2.end())
    {
        assert( hyperexp_detail::check_params(dd_.probabilities(), rates_) );
    }

    /**
     * Constructs a \c hyperexponential_distribution from the <em>rate
     * vector</em> parameter of the distribution and with equal phase
     * probabilities.
     *
     * The <em>rate vector</em> parameter is given by the
     * <em>brace-init-list</em> (ISO,2014,sec. 8.5.4 [dcl.init.list])
     * defined by \a l1, and the <em>phase probability vector</em> parameter is
     * set to the equal phase probabilities (i.e., to a vector of the same
     * length \f$k\f$ of the <em>rate vector</em> and with each element set
     * to \f$1.0/k\f$).
     *
     * \param l1 The initializer list for inizializing the rate vector.
     *
     * References:
     * -# ISO, <em>ISO/IEC 14882-2014: Information technology - Programming languages - C++</em>, 2014
     * .
     */
    public: hyperexponential_distribution(std::initializer_list<RealT> const& l1)
    : dd_(std::vector<RealT>(std::distance(l1.begin(), l1.end()), 1)),
      rates_(l1.begin(), l1.end())
    {
        assert( hyperexp_detail::check_params(dd_.probabilities(), rates_) );
    }
#endif

    /**
     * Gets a random variate distributed according to the
     * hyperexponential distribution.
     *
     * \tparam URNG Must meet the requirements of \uniform_random_number_generator.
     *
     * \param urng A uniform random number generator object.
     *
     * \return A random variate distributed according to the hyperexponential distribution.
     */
    public: template<class URNG>\
            RealT operator()(URNG& urng) const
    {
        const int i = dd_(urng);

        return boost::random::exponential_distribution<RealT>(rates_[i])(urng);
    }

    /**
     * Gets a random variate distributed according to the hyperexponential
     * distribution with parameters specified by \c param.
     *
     * \tparam URNG Must meet the requirements of \uniform_random_number_generator.
     *
     * \param urng A uniform random number generator object.
     * \param param A distribution parameter object.
     *
     * \return A random variate distributed according to the hyperexponential distribution.
     *  distribution with parameters specified by \c param.
     */
    public: template<class URNG>
            RealT operator()(URNG& urng, const param_type& param) const
    {
        return hyperexponential_distribution(param)(urng);
    }

    /** Returns the number of phases of the distribution. */
    public: std::size_t num_phases() const
    {
        return rates_.size();
    }

    /** Returns the <em>phase probability vector</em> parameter of the distribution. */
    public: std::vector<RealT> probabilities() const
    {
        return dd_.probabilities();
    }

    /** Returns the <em>rate vector</em> parameter of the distribution. */
    public: std::vector<RealT> rates() const
    {
        return rates_;
    }

    /** Returns the smallest value that the distribution can produce. */
    public: RealT min BOOST_PREVENT_MACRO_SUBSTITUTION () const
    {
        return 0;
    }

    /** Returns the largest value that the distribution can produce. */
    public: RealT max BOOST_PREVENT_MACRO_SUBSTITUTION () const
    {
        return std::numeric_limits<RealT>::infinity();
    }

    /** Returns the parameters of the distribution. */
    public: param_type param() const
    {
        std::vector<RealT> probs = dd_.probabilities();

        return param_type(probs.begin(), probs.end(), rates_.begin(), rates_.end());
    }

    /** Sets the parameters of the distribution. */
    public: void param(param_type const& param)
    {
        dd_.param(typename boost::random::discrete_distribution<int,RealT>::param_type(param.probabilities()));
        rates_ = param.rates();
    }

    /**
     * Effects: Subsequent uses of the distribution do not depend
     * on values produced by any engine prior to invoking reset.
     */
    public: void reset()
    {
        // empty
    }

    /** Writes an @c hyperexponential_distribution to a @c std::ostream. */
    public: BOOST_RANDOM_DETAIL_OSTREAM_OPERATOR(os, hyperexponential_distribution, hd)
    {
        os << hd.param();
        return os;
    }

    /** Reads an @c hyperexponential_distribution from a @c std::istream. */
    public: BOOST_RANDOM_DETAIL_ISTREAM_OPERATOR(is, hyperexponential_distribution, hd)
    {
        param_type param;
        if(is >> param)
        {
            hd.param(param);
        }
        return is;
    }

    /**
     * Returns true if the two instances of @c hyperexponential_distribution will
     * return identical sequences of values given equal generators.
     */
    public: BOOST_RANDOM_DETAIL_EQUALITY_OPERATOR(hyperexponential_distribution, lhs, rhs)
    {
        return lhs.dd_ == rhs.dd_
               && lhs.rates_ == rhs.rates_;
    }
    
    /**
     * Returns true if the two instances of @c hyperexponential_distribution will
     * return different sequences of values given equal generators.
     */
    public: BOOST_RANDOM_DETAIL_INEQUALITY_OPERATOR(hyperexponential_distribution)


    private: boost::random::discrete_distribution<int,RealT> dd_; ///< The \c discrete_distribution used to sample the phase probability and choose the rate
    private: std::vector<RealT> rates_; ///< The <em>rate vector</em> parameter of the distribution
}; // hyperexponential_distribution

}} // namespace boost::random


#endif // BOOST_RANDOM_HYPEREXPONENTIAL_DISTRIBUTION_HPP

/* hyperexponential_distribution.hpp
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
*/