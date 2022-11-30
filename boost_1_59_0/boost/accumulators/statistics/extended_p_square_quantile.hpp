///////////////////////////////////////////////////////////////////////////////
// extended_p_square_quantile.hpp
//
//  Copyright 2005 Daniel Egloff. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_ACCUMULATORS_STATISTICS_EXTENDED_SINGLE_QUANTILE_HPP_DE_01_01_2006
#define BOOST_ACCUMULATORS_STATISTICS_EXTENDED_SINGLE_QUANTILE_HPP_DE_01_01_2006

#include <vector>
#include <functional>
#include <boost/throw_exception.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/iterator_range.hpp>
#include <boost/iterator/transform_iterator.hpp>
#include <boost/iterator/counting_iterator.hpp>
#include <boost/iterator/permutation_iterator.hpp>
#include <boost/parameter/keyword.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/accumulators/framework/accumulator_base.hpp>
#include <boost/accumulators/framework/extractor.hpp>
#include <boost/accumulators/numeric/functional.hpp>
#include <boost/accumulators/framework/parameters/sample.hpp>
#include <boost/accumulators/framework/depends_on.hpp>
#include <boost/accumulators/statistics_fwd.hpp>
#include <boost/accumulators/statistics/count.hpp>
#include <boost/accumulators/statistics/parameters/quantile_probability.hpp>
#include <boost/accumulators/statistics/extended_p_square.hpp>
#include <boost/accumulators/statistics/weighted_extended_p_square.hpp>
#include <boost/accumulators/statistics/times2_iterator.hpp>

#ifdef _MSC_VER
# pragma warning(push)
# pragma warning(disable: 4127) // conditional expression is constant
#endif

namespace boost { namespace accumulators
{

namespace impl
{
    ///////////////////////////////////////////////////////////////////////////////
    // extended_p_square_quantile_impl
    //  single quantile estimation
    /**
        @brief Quantile estimation using the extended \f$P^2\f$ algorithm for weighted and unweighted samples

        Uses the quantile estimates calculated by the extended \f$P^2\f$ algorithm to compute
        intermediate quantile estimates by means of quadratic interpolation.

        @param quantile_probability The probability of the quantile to be estimated.
    */
    template<typename Sample, typename Impl1, typename Impl2> // Impl1: weighted/unweighted // Impl2: linear/quadratic
    struct extended_p_square_quantile_impl
      : accumulator_base
    {
        typedef typename numeric::functional::fdiv<Sample, std::size_t>::result_type float_type;
        typedef std::vector<float_type> array_type;
        typedef iterator_range<
            detail::lvalue_index_iterator<
                permutation_iterator<
                    typename array_type::const_iterator
                  , detail::times2_iterator
                >
            >
        > range_type;
        // for boost::result_of
        typedef float_type result_type;

        template<typename Args>
        extended_p_square_quantile_impl(Args const &args)
          : probabilities(
                boost::begin(args[extended_p_square_probabilities])
              , boost::end(args[extended_p_square_probabilities])
            )
        {
        }

        template<typename Args>
        result_type result(Args const &args) const
        {
            typedef
                typename mpl::if_<
                    is_same<Impl1, weighted>
                  , tag::weighted_extended_p_square
                  , tag::extended_p_square
                >::type
            extended_p_square_tag;

            extractor<extended_p_square_tag> const some_extended_p_square = {};

            array_type heights(some_extended_p_square(args).size());
            std::copy(some_extended_p_square(args).begin(), some_extended_p_square(args).end(), heights.begin());

            this->probability = args[quantile_probability];

            typename array_type::const_iterator iter_probs = std::lower_bound(this->probabilities.begin(), this->probabilities.end(), this->probability);
            std::size_t dist = std::distance(this->probabilities.begin(), iter_probs);
            typename array_type::const_iterator iter_heights = heights.begin() + dist;

            // If this->probability is not in a valid range return NaN or throw exception
            if (this->probability < *this->probabilities.begin() || this->probability > *(this->probabilities.end() - 1))
            {
                if (std::numeric_limits<result_type>::has_quiet_NaN)
                {
                    return std::numeric_limits<result_type>::quiet_NaN();
                }
                else
                {
                    std::ostringstream msg;
                    msg << "probability = " << this->probability << " is not in valid range (";
                    msg << *this->probabilities.begin() << ", " << *(this->probabilities.end() - 1) << ")";
                    boost::throw_exception(std::runtime_error(msg.str()));
                    return Sample(0);
                }

            }

            if (*iter_probs == this->probability)
            {
                return heights[dist];
            }
            else
            {
                result_type res;

                if (is_same<Impl2, linear>::value)
                {
                    /////////////////////////////////////////////////////////////////////////////////
                    // LINEAR INTERPOLATION
                    //
                    float_type p1 = *iter_probs;
                    float_type p0 = *(iter_probs - 1);
                    float_type h1 = *iter_heights;
                    float_type h0 = *(iter_heights - 1);

                    float_type a = numeric::fdiv(h1 - h0, p1 - p0);
                    float_type b = h1 - p1 * a;

                    res = a * this->probability + b;
                }
                else
                {
                    /////////////////////////////////////////////////////////////////////////////////
                    // QUADRATIC INTERPOLATION
                    //
                    float_type p0, p1, p2;
                    float_type h0, h1, h2;

                    if ( (dist == 1 || *iter_probs - this->probability <= this->probability - *(iter_probs - 1) ) && dist != this->probabilities.size() - 1 )
                    {
                        p0 = *(iter_probs - 1);
                        p1 = *iter_probs;
                        p2 = *(iter_probs + 1);
                        h0 = *(iter_heights - 1);
                        h1 = *iter_heights;
                        h2 = *(iter_heights + 1);
                    }
                    else
                    {
                        p0 = *(iter_probs - 2);
                        p1 = *(iter_probs - 1);
                        p2 = *iter_probs;
                        h0 = *(iter_heights - 2);
                        h1 = *(iter_heights - 1);
                        h2 = *iter_heights;
                    }

                    float_type hp21 = numeric::fdiv(h2 - h1, p2 - p1);
                    float_type hp10 = numeric::fdiv(h1 - h0, p1 - p0);
                    float_type p21  = numeric::fdiv(p2 * p2 - p1 * p1, p2 - p1);
                    float_type p10  = numeric::fdiv(p1 * p1 - p0 * p0, p1 - p0);

                    float_type a = numeric::fdiv(hp21 - hp10, p21 - p10);
                    float_type b = hp21 - a * p21;
                    float_type c = h2 - a * p2 * p2 - b * p2;

                    res = a * this->probability * this-> probability + b * this->probability + c;
                }

                return res;
            }

        }

    public:
        // make this accumulator serializeable
        // TODO: do we need to split to load/save and verify that the parameters did not change?
        template<class Archive>
        void serialize(Archive & ar, const unsigned int file_version)
        { 
            ar & probabilities;
            ar & probability;
        }

    private:

        array_type probabilities;
        mutable float_type probability;

    };

} // namespace impl

///////////////////////////////////////////////////////////////////////////////
// tag::extended_p_square_quantile
//
namespace tag
{
    struct extended_p_square_quantile
      : depends_on<extended_p_square>
    {
        typedef accumulators::impl::extended_p_square_quantile_impl<mpl::_1, unweighted, linear> impl;
    };
    struct extended_p_square_quantile_quadratic
      : depends_on<extended_p_square>
    {
        typedef accumulators::impl::extended_p_square_quantile_impl<mpl::_1, unweighted, quadratic> impl;
    };
    struct weighted_extended_p_square_quantile
      : depends_on<weighted_extended_p_square>
    {
        typedef accumulators::impl::extended_p_square_quantile_impl<mpl::_1, weighted, linear> impl;
    };
    struct weighted_extended_p_square_quantile_quadratic
      : depends_on<weighted_extended_p_square>
    {
        typedef accumulators::impl::extended_p_square_quantile_impl<mpl::_1, weighted, quadratic> impl;
    };
}

///////////////////////////////////////////////////////////////////////////////
// extract::extended_p_square_quantile
// extract::weighted_extended_p_square_quantile
//
namespace extract
{
    extractor<tag::extended_p_square_quantile> const extended_p_square_quantile = {};
    extractor<tag::extended_p_square_quantile_quadratic> const extended_p_square_quantile_quadratic = {};
    extractor<tag::weighted_extended_p_square_quantile> const weighted_extended_p_square_quantile = {};
    extractor<tag::weighted_extended_p_square_quantile_quadratic> const weighted_extended_p_square_quantile_quadratic = {};

    BOOST_ACCUMULATORS_IGNORE_GLOBAL(extended_p_square_quantile)
    BOOST_ACCUMULATORS_IGNORE_GLOBAL(extended_p_square_quantile_quadratic)
    BOOST_ACCUMULATORS_IGNORE_GLOBAL(weighted_extended_p_square_quantile)
    BOOST_ACCUMULATORS_IGNORE_GLOBAL(weighted_extended_p_square_quantile_quadratic)
}

using extract::extended_p_square_quantile;
using extract::extended_p_square_quantile_quadratic;
using extract::weighted_extended_p_square_quantile;
using extract::weighted_extended_p_square_quantile_quadratic;

// extended_p_square_quantile(linear) -> extended_p_square_quantile
template<>
struct as_feature<tag::extended_p_square_quantile(linear)>
{
    typedef tag::extended_p_square_quantile type;
};

// extended_p_square_quantile(quadratic) -> extended_p_square_quantile_quadratic
template<>
struct as_feature<tag::extended_p_square_quantile(quadratic)>
{
    typedef tag::extended_p_square_quantile_quadratic type;
};

// weighted_extended_p_square_quantile(linear) -> weighted_extended_p_square_quantile
template<>
struct as_feature<tag::weighted_extended_p_square_quantile(linear)>
{
    typedef tag::weighted_extended_p_square_quantile type;
};

// weighted_extended_p_square_quantile(quadratic) -> weighted_extended_p_square_quantile_quadratic
template<>
struct as_feature<tag::weighted_extended_p_square_quantile(quadratic)>
{
    typedef tag::weighted_extended_p_square_quantile_quadratic type;
};

// for the purposes of feature-based dependency resolution,
// extended_p_square_quantile and weighted_extended_p_square_quantile
// provide the same feature as quantile
template<>
struct feature_of<tag::extended_p_square_quantile>
  : feature_of<tag::quantile>
{
};
template<>
struct feature_of<tag::extended_p_square_quantile_quadratic>
  : feature_of<tag::quantile>
{
};
// So that extended_p_square_quantile can be automatically substituted with
// weighted_extended_p_square_quantile when the weight parameter is non-void
template<>
struct as_weighted_feature<tag::extended_p_square_quantile>
{
    typedef tag::weighted_extended_p_square_quantile type;
};

template<>
struct feature_of<tag::weighted_extended_p_square_quantile>
  : feature_of<tag::extended_p_square_quantile>
{
};

// So that extended_p_square_quantile_quadratic can be automatically substituted with
// weighted_extended_p_square_quantile_quadratic when the weight parameter is non-void
template<>
struct as_weighted_feature<tag::extended_p_square_quantile_quadratic>
{
    typedef tag::weighted_extended_p_square_quantile_quadratic type;
};
template<>
struct feature_of<tag::weighted_extended_p_square_quantile_quadratic>
  : feature_of<tag::extended_p_square_quantile_quadratic>
{
};

}} // namespace boost::accumulators

#ifdef _MSC_VER
# pragma warning(pop)
#endif

#endif

/* extended_p_square_quantile.hpp
RDJTOm9/xs6pvV5xXrXH8peQrE/vrW4nftfqVVs/EKH4uGNQR7VUJpc+YMdSTeLXXv3rrovfUzBJkSNG6FwXjdfsN/7uQuYh2ki39PyupnL5HNPZa4v9RVLRQEt7nwkE9zgWEzwVSPJr92LFjDX6fcDdI5DKx5MFnZffI2hPqZ9IZVodMLKilMStG6MTHNLtss0KfPaXzaA8mgFcHf6RXZbG1nV89z2zfGkKrxJLfCARJTGs1V6Y2z/MJ92kD0cC7DDX6DJL3Eb//0n3AYbs2XAlRLnuoESQ7Fy6svy+yBlovbl5s9ow5yJ/6sxk6OZOcrnnFdTO/KUy0AhUtfk+3TedrB+HKt1M8DcB2sXPEIXozFW3t+BGz3orNY1INjfn84xO5J86eyLIK5fGRzUbkbfL83JUGXZN91QlzE5zqWS8zhy0bzu7O+WJlgmSLBy4V9riO3USxpo+oZ6p6d2ddgymmU22pRMmRudAgdadD2X4uzkmvXcOPcmghHcYyteehBubw7T0P4oaHBNjmGkG6Odes/C1aUgmkJ6avdN1CvKSCLoHxEv2VIILtCDVBAPpNn9E3FWhT31bNm/VBNXXOtbAbiKfgNN/TZki19CVqTeBmd2zjzQ4szan2J+99MUj43F35rb2X+f1z0SrhT77w3PFeSUJsi+rv17xcmMSfidrRf+ZiPHSBsgajY8Az7m8CaVwohGp6ZPR4+WaxwuOPTq+1+SbcL5FM7qXZRRAOrCcu+D6FFLv9RYJWqplZoWCT3rwEPQtvJ8YG4IYs6KeJkGDnE3zRlClV8v9Mgbji+lWmdeS1UHvfdqh83ThXwr8Sp+lVspZxBpD1wc0YABjmHy3TpT60Ghn6lF/1LXMWc7m/SWwWa1K6Xk8ByGvl4WumI8HG/nvJ2tMrQyqMzQ8IzNMrb5vNFGwky/a8d7DlHVHhS+qMisUjx24ZhvvteMfBlNN39Q160WSK2XunOvfDVn8wwZ+i5g98I9jz0+bS8YGdAZmsylJ3LKyH3Q6YGpNfwvZyvcoobufgATtIJsQCsT72VCxq7Hxo5Tbcg+LH37t/gcLIEUFevyvmiMkful0+afylOaFo2nH+5WoUEi/vyxhMdtLFNdDbB1OC+ovHOZUx0E92rWq+mR7PBfExAbbeN+4wJLWFXEUxfGqwkLm5flSicBJm242P6mXv8JFqsp7sleK134+Nj9A5uWGSQLxr8FQoF5DXIClWQRrPnor/jq4/ces6f64N3AJPs7V6pNF68ommwtfUxpQC7AJ1uRpGpSdyxBWidbkUZVxtJMijPYzpyaBaNRjKHReMVqQtPz7eWmwOr3D/hl1JAsnIv96YwloVL8G/o8SWeBsZv4LzOGtLtd/lVWlNVH0Q7ibUoseRNWzZQJVmBXBhONBTOx5AdCR6MLYzl8C3FgqE8CTZaERJ/+J6MIaCfB+7KrFkOYmrlxn12W62/zvqPj23TRyxU6OsVdoFrni+gvVSWfSSl9oIYyY1j5jZT26ENckYm1YThUYkEWtCIplEIiF7ArNj+f+qwK665u/IM0lV3zV/OFnnJLhNk8r/jPzppW8VP2rvvN0tQ3VffgTkU6t8T9jOKas5UT7n7iw8Ylg8s3/Eao9tWbH9LQ5RaMnzKrLTyxGjiPUA3ue3WF/vChOvITs4oyrf8eHHV8nktvzeif0YeYyugH1GOqwuc5/9ZW/AZh0MpMQbPZW4fwRIFCtrnYlmJv3qjYcrMGxFKMm0PvcmIdScn5rON6rgD8KHq4baF8dRMTNfHIvbRb50GL3ltrfS1DeMsUj73bm4U9nu3QJ8cM39LweE9IGtPWH+u14KSplLL/zX97hSNDX1Z74Wz17ZYZrnrqXwf5qWdMy7I+RWZu5bkjvZl4pYlrLCHbdXvJlRCe3Gxr4iSnYYhmfoBQNGtDlC+bkH0Qke1yyA4QNxCTLiL1gRiffLqFSOom3SymJzr/+8itaWf+9UdyzieTRsrLVVyyyLT0kskcEOdIH5bf1lN2o4OmLUlB/MyR3EDI17rH22YmdPvbo6V7Z/R4o/UnQMI82uRy7dXDc9pq3HHnrmzD+I+O2Z/Gyg31eg7bp3wbwa8vcOThh4ZzuPt/vvJtyAOSAI1xAP2dBGdQC5jrCDHv9UoOa2nWID9Lx9do2ZMKi7HwQa5HroE3TERvS1dFNXtQId1qTYo6MEOZ2b5PrAq9pI2Xa4aHtSY5kRjBWdpQroFdyuzj90g2vXW0KdV5NApcNlgsDPnq3/ETczvN+30tYvW1Ky47gNmj6Z/++l9tQuskyRsXfiILo0SuWWHd38Vj6R5/Fn1hX/z+moheK6zXLX/atB11vsnXKYD/R840I/2C++1VJjQ0qDoduFrRetzyGwnxwB+A5hq3eiNL103qnbsSoA48bDCKi80XSu6XvV4rfbBUbJv6lvtt3m+Guw81z863HL/MJpxCyIJaNGY7QDxtIyzgRA/np6mMFylMjOfE9FRCoNpaIftug8OFau9YWiHGkTHZN+zAQzBfxaUH+V5RyK7TXlyAzOW/PAsf8vJBA6OH7AEH9Pw9fM/U9c50DocpAcII8YR93nPJEWc1HTnwsZQJb9HYGdnqWrtB/INM1mya1BYFMaYS8IOuHNVmd4TL5HudZxn8ZTVmd0jL5ssUcfQaSJLFfkbBAv8O0UIO4fwWjMn+cECSnGVu6m/7zQhPLOCwJvNyMHTWDFUiNLQlgrdkVKvIhfBhljvma63df+3ZrcmgeUF+5Q0OVe73/kOGT3s6R+UWXSLz/LFQmTuRpVz7YtCOHq05nfq2lcRI5VU6xIMG+7TncSa/0r/WlI0QlRKKAoObJWOb/0XaI1vEk/k3qrG4Roa9xgek+w8G+XVMp5IRLktoRmvnFzIVlT4WBKEYlFvVnYaUV/VyJuduHMq5farQGrFT8X+hIUisVHg03y/5MgEVyxnTdGJVlRlXUb9y9dBiOfqwKfk7OexeD7/1Rh0FQPB9LlCxRfzXlYsWBkeCehfhnCF9EgvA8yWue698dadoyj79Z3OGTzj52RiaamgoyqCxSi334z80Twfgkn7uEavHmmqBr0dvLz8e6DpJJdw41x2RCjmqq4hQwueQdB/Pk4myZYphWFtXHMHWb0uGZVqa3mVr5062ONVqkznULzwI8veOT1WaQS7ndCqOETJzyuv0hWYPh/c55mpU1qkBJEwLF3YSsdwvEzp0uVTL7CX5H5bp1jiN3QIrUvSJTDqCrWUqV+/HrraLHkZ+5GlWMituOS2Iw245xWUPbFenEhgqW8rhAVAdurjboWWu2GoDbs05BZxI7vwCc5SLh0ukiSJ24uHTIF5qJtxSzbmEQezWIHOL2VC01lnuuBdRaX2jVeLXZnaXSIth9Wa42ihqVfA9CSJu3iKPA8Ssco9xGYo4UxXs/jQSFVlJ4hd8d3QKYD2H58rZPXvuHgEXJZr2IqTtNueRcFKBxnXoEap+fwwQPeO0OxK7ZKdmvZbYcpVek5KRJ6mQZHeDeHEJRiPXKAUDFvihCgat7bqAX3zrj5O8uofuWIiC0MG5hQexlv+yvKPQHURZh6uXRwPmGDvN2KwxL44a10LyEO2vGOLzZUFYEqXCVlgLTEQNIPJ/f1BB7kqttzlEbazOcExS+JdoznMUc0it5zWxoia2oHJ1rfkNCFSz3J693nau1/f+Hhn5Bskbf6uDq8++9quXczc2tC9zWPOufQsJfNrq1P7VDzxrHladXJv6O9OJvRaFglonAz4mJzO7hSyPsNovR2IKRfrgkmKglCt/V4E8HV/Bm6ZZBNIQ65EBIrVbTjEijIKLNxMpIz7UpaRsBHTjY6Ay+/Fh7us5mzgSAiOL+KeNmZUYEKLGh/4ZJ9j1chpkXsBFsgdMPeIwhPK+1LdqvX/cOcisVDZTAPiyXUlhDY73LPZHntMl9J0g9L6pP3ewoGo2vtjH4QajRX5Re4xgkGKUXUTDBqZVQFzcneKw4LlYdrOjWJXUFLuBMT5X3+gcKIiJPA/MLAuiH9jd3VuCM3NowRbBw5qYpecozRz+78MN3+AQ7iesv2naK26Xi7sMhLbWUWBuxZrUH1JLu3DK0mr00AwD4Lbr0cS/t3KU9s9PeDrqRErzrZQcXXubH8RUgfaw7K4U0qoQJexkio1siBKBjfIDphe9eZpNQv4IgntHZnPCzDuwrBADRFhtcEL5xCHHo3qotFetCBOjJwo3n+V79xbGvXjpQIrekSBxFEMFVeXVF6TBTttfp2iy4EujSAUFYHqb1IcgeSkusj4ECs4M/vXQyX70IQ++5IzaThzc0yfSpERyVQJ4NoKLTS9JlWGDceTcpKiGHNAb51RIK/Avs9kfhLwzxLVLXG8oPd6ax3ZeRU5e21zCr2zRifYNRGFpU/XKu7YRTOAJALVvq+yaO4uJor04v6hE/hEOx+81PzmLAswosm/ErIyGfgyUlhYCDAJiHC/DnIfXB9kXN5Bh+eEF95ed8L7XkAf0Ngy8dUJfwoOdxnamvBLoksB0ZLBtSsCndRvyBfwpASKM0AxvY1cF7e66GNaZGEIAS0CtaVGs+GXpyP4otMxxWB0Wkop0bBJyM4NBrQE/uUjDZkSgQNlzClkeOTNdRANUryu05KaJjpXexujpMGu2GvEUDSAM173leUfQnujc9hocfFfkREeblKl+Z6X1hXPW8r/hBLd/nFV43awjdXxkXghAJhmFKINO3e5C4066GNARJZPvX2y44ySDVF2zVaoBODwnX2tpjahLElKCOGUmNEwB42ZCavawMPJya0FSk1ReAzygEgO9lMrvgUtSLwqB7ZM/uKIQ6iNQxSLgA5BLfCEAMkkkgg2eOnk/H0iEx5hGToWQeg/ihAtiMlD0kjBi809Dh+2taFLoDdCqHwMs8FtxggHxRkwysphU00E1rwYcUmJQehNOTQppm5LnebVQLZzXJU9EY26NtqUbBpyuGXral714uXS3rw0+PdpEdMZSa4W9WpXwG1XsB8/SgLDCo6NnlsBtXu8K+m/adJ7R2D4mjOq2AjjImr4hJegEV0Er9Sjuw2SnRQ+JbTtQyB/o2AGIqfBTP47qOQzvOff9o6/NUu9MYc42g4RAcAnOI78aBYyO+QRwB4jypx+2YMpT35NZcYGlEQ20prJft5K1Q4LkMEuAD2k7WZ1CFxawFXP0nft4K6k3qbgvE1MdY96z2XblsMGJw0Hc4UdDHg1oKJCQU/VOEF5HlCfy/pxSZBrDCtjJ+WUSqoN0rkPyTNoZOQB6AMY8V/hHazgxvQMJ7sYQzh0Abm2AGKU10YN/8EbgGsWoMJ1eYEVxzdAsDYUttE95ABxMZ38xlQAUAIXCo6Q709YtgmQY4e1uqBq5cEcxY9/Ki2N6DhkLnIgizfmoPBKAJHEp5yYUgbsE3oKa5CP82sGI2ErTwcZXFtScZctFdrDXzyfCa9vjlNWNuE0QE2pQ0QMXYqiaEmaKwABivursXNsdMs3svU51eF9B4GxG6JBEAC3A87cAo7xTUnsAlzCM3KyuYgEgBAooRAtotqJFsWYAf6wP8mP1YGgHaZAavWdWnID+BM/YsMbCCu3EHuinPHOG6/j0I6/Ho8Boxsle5X88YAHAsHbx4CKZLHePohBPzBQYFIGhooAP+fi2A8txI4VYgqiIq0mBbzMMPIB5n9HmMpK2tX6Cbe90hR94hiJhCMzD315xCtlaEAF3B7nZeTcVhqc5YO05WAAHtLegeHR543lFYmP5r1NR7vRYAVl0ohS/UWCBnCS2LIqSigc5st8Bj43AbtDYYB0rzMR1gAAcKXyg0s/rCaX8bB27uqdjefX7mEWCtq2GjIE9j108XzZhFp1imMKBEVLQX4XPwYAwB1YB0qgDg2zEpPSjNC7jeiQuUS7W1ZYENRFYrDXXDgBvMBNJm3DxuB96BCV0B4IdbkJ6XPDxHu4EX4eIoCIn0GJRONVkF49vsgAdc1Z2AWOH8tIPBgJqK7tdK55fpEBQQHPfKYx40BzvdiXpDB+55AvFBXeZsmrtzML1UGSGkp6amPI2AqAYS4OsUtBAZPpXXb7opAlvY+1IGznjHp0FIBEZSWyAiRh7ABltjnnHAXDyEVikAeVOZT7VboHV2lCDQ54JXLx9Afh6AADWhWxWhWzuPDpAlzwcrfuZGAjBNWoGKwffqmEmOOCic1KDSS3jKdwQNAJ3U9rgpvRn88w8p/xR4i1IXNQD86SZXyRFO8eHf2cyh2nQFbOmEQaWCWaHpWtBN2bUbwJL76h6I+O/lc2VBQt7f3PfwzU08fwZEACQ0Cd6xrtb83a8btGBnc3UoUlIFEEPA66F4pVUE/sm/G76uTcQXU8IDBBMugAx1zu4dnWJg96c2bcYA8HAiBP4F6o99I4QEqLq3g43BLhdCEgrTi9MLl2nv4SkBACrWLccfB7VxpwhqbcmT2DGOMNV2+EUBIhkA3CjaBjrYHNSZnumF0I4PWJhlNoWUwF12urkJd+kQcoHw8QJMKjHshUlY0ng4mlVPKZ9wnh2dPj4qoGwZKCp2TPl6OLu1iwaQyR2Qahf0WeomRDOSQ0Q/2IPJ1aNw34BPW+ArTV/RhA2CU6WEFcxW3eYF8K1sbfcJzWxLCM1s8goLdy3zbQltiAmszA9tbfAJdixRpfnpbFJkkuQwlKLZe5XZy8xuNMY1brDJgdK/h42I8YXX1FnYWNQ+5P18LiwgN2DZyK/MnFkUecISKJ4RDaMsMLsLLjpySlb27/t5fSdO8+2JiI76Y3i/dg/eA3WlzJWGodzsuF3dimt9+Q0kYPPt6/P9+iGXgVYW5UcGmDK8XPbQTI6HSPlSOZID3dMTNSCY+Y9IcORof4xkQ1FzlWSSkY6fC0HnR4Y7xBKiRmalHxffxXy4fs4+uw5zBb7/nSzbfbM6r4FgHEi4LY3NP/9oLMlwNwDJ5Qz+PFU+O/xThSwY22vM9OizSnkKhGRMlII50jjBTrYpIJ5DnMThNqAcxalyK6mu/1NqV3LoktaHj+7oueqvVVq6LX9V/tg0f2jpig5lIzeTc7BQHfQfrW58x63/4Za6vmCvFYN64FIkxDyor7fBtbbJrVPxkLtTRyrn24JmW5EkiQmPfTywG3de60SyetkimXvsSKlX8fY3oHtT8M5vgghCs+bcAum99OKQOfwWRrl88Gvhyf3WkNNxGRpNTiGBfIEvuRz+HmtR1e8exk9JSyMy+t0r+9C5KTD97AP4U/pShl79ubPRhzoXpAnLVqZMw4EYbDnNa5TsGEkUKbJ1Cpc5eS4U42QMPh/fWvHJkGtmvZI/yq8zjMyl907WU1MWhrsm9h7Gir8Gt4Yzdhpa9HembafmNuz138gj2+5LUrQL3TeGENph4AqhNp+YsvRja1R6HnWjD6yiYxJUkqeXIW4Pq6oe00R300+mhwOURt21k8KwGkmFND/MaBUnVHzUrg+O8KvdX/OdWFMtDlvtP6iwElUsf8KZFr7RPkKZ1sosa3Upr1nPpjfW+WlDWrPAq2Ygi8W7IKhUnXT0ePfSPIBfz3SL8aI8chiruuuRUJdFdciwg3WPSUwqALpSlgnxOa8T8iEJA8a/xOy/l0XW/NCwMtLoZgM+XmTIDQtw3XwStHlF
*/