///////////////////////////////////////////////////////////////////////////////
// tail_variate_means.hpp
//
//  Copyright 2006 Daniel Egloff, Olivier Gygi. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_ACCUMULATORS_STATISTICS_TAIL_VARIATE_MEANS_HPP_DE_01_01_2006
#define BOOST_ACCUMULATORS_STATISTICS_TAIL_VARIATE_MEANS_HPP_DE_01_01_2006

#include <numeric>
#include <vector>
#include <limits>
#include <functional>
#include <sstream>
#include <stdexcept>
#include <boost/throw_exception.hpp>
#include <boost/parameter/keyword.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/accumulators/framework/accumulator_base.hpp>
#include <boost/accumulators/framework/extractor.hpp>
#include <boost/accumulators/numeric/functional.hpp>
#include <boost/accumulators/framework/parameters/sample.hpp>
#include <boost/accumulators/statistics_fwd.hpp>
#include <boost/accumulators/statistics/tail.hpp>
#include <boost/accumulators/statistics/tail_variate.hpp>
#include <boost/accumulators/statistics/tail_mean.hpp>
#include <boost/accumulators/statistics/parameters/quantile_probability.hpp>
#include <boost/serialization/vector.hpp>

#ifdef _MSC_VER
# pragma warning(push)
# pragma warning(disable: 4127) // conditional expression is constant
#endif

namespace boost { namespace accumulators
{

namespace impl
{
    /**
        @brief Estimation of the absolute and relative tail variate means (for both left and right tails)

        For all \f$j\f$-th variates associated to the \f$\lceil n(1-\alpha)\rceil\f$ largest samples (or the
        \f$\lceil n(1-\alpha)\rceil\f$ smallest samples in case of the left tail), the absolute tail means
        \f$\widehat{ATM}_{n,\alpha}(X, j)\f$ are computed and returned as an iterator range. Alternatively,
        the relative tail means \f$\widehat{RTM}_{n,\alpha}(X, j)\f$ are returned, which are the absolute
        tail means normalized with the (non-coherent) sample tail mean \f$\widehat{NCTM}_{n,\alpha}(X)\f$.

        \f[
            \widehat{ATM}_{n,\alpha}^{\mathrm{right}}(X, j) =
                \frac{1}{\lceil n(1-\alpha) \rceil}
                \sum_{i=\lceil \alpha n \rceil}^n \xi_{j,i}
        \f]

        \f[
            \widehat{ATM}_{n,\alpha}^{\mathrm{left}}(X, j) =
                \frac{1}{\lceil n\alpha \rceil}
                \sum_{i=1}^{\lceil n\alpha \rceil} \xi_{j,i}
        \f]

        \f[
            \widehat{RTM}_{n,\alpha}^{\mathrm{right}}(X, j) =
                \frac{\sum_{i=\lceil n\alpha \rceil}^n \xi_{j,i}}
            {\lceil n(1-\alpha)\rceil\widehat{NCTM}_{n,\alpha}^{\mathrm{right}}(X)}
        \f]

        \f[
            \widehat{RTM}_{n,\alpha}^{\mathrm{left}}(X, j) =
                \frac{\sum_{i=1}^{\lceil n\alpha \rceil} \xi_{j,i}}
            {\lceil n\alpha\rceil\widehat{NCTM}_{n,\alpha}^{\mathrm{left}}(X)}
        \f]
    */

    ///////////////////////////////////////////////////////////////////////////////
    // tail_variate_means_impl
    //  by default: absolute tail_variate_means
    template<typename Sample, typename Impl, typename LeftRight, typename VariateTag>
    struct tail_variate_means_impl
      : accumulator_base
    {
        typedef typename numeric::functional::fdiv<Sample, std::size_t>::result_type float_type;
        typedef std::vector<float_type> array_type;
        // for boost::result_of
        typedef iterator_range<typename array_type::iterator> result_type;

        tail_variate_means_impl(dont_care) {}

        template<typename Args>
        result_type result(Args const &args) const
        {
            std::size_t cnt = count(args);

            std::size_t n = static_cast<std::size_t>(
                std::ceil(
                    cnt * ( ( is_same<LeftRight, left>::value ) ? args[quantile_probability] : 1. - args[quantile_probability] )
                )
            );

            std::size_t num_variates = tail_variate(args).begin()->size();

            this->tail_means_.clear();
            this->tail_means_.resize(num_variates, Sample(0));

            // If n is in a valid range, return result, otherwise return NaN or throw exception
            if (n < static_cast<std::size_t>(tail(args).size()))
            {
                this->tail_means_ = std::accumulate(
                    tail_variate(args).begin()
                  , tail_variate(args).begin() + n
                  , this->tail_means_
                  , numeric::plus
                );

                float_type factor = n * ( (is_same<Impl, relative>::value) ? non_coherent_tail_mean(args) : 1. );

                std::transform(
                    this->tail_means_.begin()
                  , this->tail_means_.end()
                  , this->tail_means_.begin()
#ifdef BOOST_NO_CXX98_BINDERS
                  , std::bind(std::divides<float_type>(), std::placeholders::_1, factor)
#else
                  , std::bind2nd(std::divides<float_type>(), factor)
#endif
                );
            }
            else
            {
                if (std::numeric_limits<float_type>::has_quiet_NaN)
                {
                    std::fill(
                        this->tail_means_.begin()
                      , this->tail_means_.end()
                      , std::numeric_limits<float_type>::quiet_NaN()
                    );
                }
                else
                {
                    std::ostringstream msg;
                    msg << "index n = " << n << " is not in valid range [0, " << tail(args).size() << ")";
                    boost::throw_exception(std::runtime_error(msg.str()));
                }
            }
            return make_iterator_range(this->tail_means_);
        }

        // make this accumulator serializeable
        template<class Archive>
        void serialize(Archive & ar, const unsigned int file_version)
        { 
            ar & tail_means_;
        }

    private:

        mutable array_type tail_means_;

    };

} // namespace impl

///////////////////////////////////////////////////////////////////////////////
// tag::absolute_tail_variate_means
// tag::relative_tail_variate_means
//
namespace tag
{
    template<typename LeftRight, typename VariateType, typename VariateTag>
    struct absolute_tail_variate_means
      : depends_on<count, non_coherent_tail_mean<LeftRight>, tail_variate<VariateType, VariateTag, LeftRight> >
    {
        typedef accumulators::impl::tail_variate_means_impl<mpl::_1, absolute, LeftRight, VariateTag> impl;
    };
    template<typename LeftRight, typename VariateType, typename VariateTag>
    struct relative_tail_variate_means
      : depends_on<count, non_coherent_tail_mean<LeftRight>, tail_variate<VariateType, VariateTag, LeftRight> >
    {
        typedef accumulators::impl::tail_variate_means_impl<mpl::_1, relative, LeftRight, VariateTag> impl;
    };
    struct abstract_absolute_tail_variate_means
      : depends_on<>
    {
    };
    struct abstract_relative_tail_variate_means
      : depends_on<>
    {
    };
}

///////////////////////////////////////////////////////////////////////////////
// extract::tail_variate_means
// extract::relative_tail_variate_means
//
namespace extract
{
    extractor<tag::abstract_absolute_tail_variate_means> const tail_variate_means = {};
    extractor<tag::abstract_relative_tail_variate_means> const relative_tail_variate_means = {};

    BOOST_ACCUMULATORS_IGNORE_GLOBAL(tail_variate_means)
    BOOST_ACCUMULATORS_IGNORE_GLOBAL(relative_tail_variate_means)
}

using extract::tail_variate_means;
using extract::relative_tail_variate_means;

// tail_variate_means<LeftRight, VariateType, VariateTag>(absolute) -> absolute_tail_variate_means<LeftRight, VariateType, VariateTag>
template<typename LeftRight, typename VariateType, typename VariateTag>
struct as_feature<tag::tail_variate_means<LeftRight, VariateType, VariateTag>(absolute)>
{
    typedef tag::absolute_tail_variate_means<LeftRight, VariateType, VariateTag> type;
};

// tail_variate_means<LeftRight, VariateType, VariateTag>(relative) ->relative_tail_variate_means<LeftRight, VariateType, VariateTag>
template<typename LeftRight, typename VariateType, typename VariateTag>
struct as_feature<tag::tail_variate_means<LeftRight, VariateType, VariateTag>(relative)>
{
    typedef tag::relative_tail_variate_means<LeftRight, VariateType, VariateTag> type;
};

// Provides non-templatized extractor
template<typename LeftRight, typename VariateType, typename VariateTag>
struct feature_of<tag::absolute_tail_variate_means<LeftRight, VariateType, VariateTag> >
  : feature_of<tag::abstract_absolute_tail_variate_means>
{
};

// Provides non-templatized extractor
template<typename LeftRight, typename VariateType, typename VariateTag>
struct feature_of<tag::relative_tail_variate_means<LeftRight, VariateType, VariateTag> >
  : feature_of<tag::abstract_relative_tail_variate_means>
{
};

// So that absolute_tail_means can be automatically substituted
// with absolute_weighted_tail_means when the weight parameter is non-void.
template<typename LeftRight, typename VariateType, typename VariateTag>
struct as_weighted_feature<tag::absolute_tail_variate_means<LeftRight, VariateType, VariateTag> >
{
    typedef tag::absolute_weighted_tail_variate_means<LeftRight, VariateType, VariateTag> type;
};

template<typename LeftRight, typename VariateType, typename VariateTag>
struct feature_of<tag::absolute_weighted_tail_variate_means<LeftRight, VariateType, VariateTag> >
  : feature_of<tag::absolute_tail_variate_means<LeftRight, VariateType, VariateTag> >
{
};

// So that relative_tail_means can be automatically substituted
// with relative_weighted_tail_means when the weight parameter is non-void.
template<typename LeftRight, typename VariateType, typename VariateTag>
struct as_weighted_feature<tag::relative_tail_variate_means<LeftRight, VariateType, VariateTag> >
{
    typedef tag::relative_weighted_tail_variate_means<LeftRight, VariateType, VariateTag> type;
};

template<typename LeftRight, typename VariateType, typename VariateTag>
struct feature_of<tag::relative_weighted_tail_variate_means<LeftRight, VariateType, VariateTag> >
  : feature_of<tag::relative_tail_variate_means<LeftRight, VariateType, VariateTag> >
{
};

}} // namespace boost::accumulators

#ifdef _MSC_VER
# pragma warning(pop)
#endif

#endif

/* tail_variate_means.hpp
6Dxw1XIMV3KzBdUVxwDNdN1gFJ15bU6nP9w4M2wqF+wD/WEZjeWj6maqmwhkM16kYf0FxK+Os0jy6gjOPSctLHm99B5LXgXvacmL+N5r08U6J8NogPFKuyw7cmQOH3ceNjXSsTLYTlN4t6dFuDqNAoyvNZUssYFd3RuoXrox+dPSYl/gWlG+NMuFB5NCevqdREMt/kbgd/RinvQxwO97oSWm8reQboAFlb8MgjAxHAIP6ou0VOUkqTKG6O0Ij0w2i3IQMwMhJOm0Qv56SP7tdlkvDSYJyomf8UshgwAr5+HbCd8PAe/G9yi+8/CNiarWLDV+o09s5Mlq0w/V/ttUfOXsX6eH5Q1VYyLLFxUnvEg/OYbjvZDHF8PPRj6I3P8brFIeUCmc2zr1j4HhKX3C8PDTY/cfDJnm9dO2p1vQNH+3eO6M5u+M2047f9ccapq/U1kdJrP259OiyrCvfNhgBh+s7TZYQ8P6mVWonXguaCnza2e0KEO2EaY8y/Y+UIKxyuNPYYWZeKR5Xy2cKuvwPrwb0DYmJ4FCx+JwKoXeoNVqfdg0yOxfxaF3Yrv2EM0aNl3hk+0qMO0roFtPIcZt7WGnaa39mINyxYiYvXgtw+3OkxQ7F9hPsxenoZEIhgLFAQWXjZ4hRVIY29i8SwG0RWf1drRhsT2i5jL6cyaXxmIvEAqZYJcUrzWO9QMfKc/uWijB5fzBZ93lzXNRzPvjqZ5xNalFOdlQ4824HgM90oDgzYwrddvdEAgjxhVoMmnQWvI0StNv4yi2KXYrxGatCwHP3csTtxXaD+gT3otk/TtkTXYV+L696d/7Se1ZzlfGtKlavklnbRqO63iMXdpqweQvwkRZA9ShPyKNaNJ+9zSISivRUsIUdbVFdFB3FwhFXRqmHbaQohvlmEQGG8mgCudw7LD2sLtdh92iW0vxRnRrExT1IfZSrd8RgUDN43EeJvq4GmAibWGnJXhJpeVcgR31YBZ8wFiRlAghVD/tg8SYUmwBuQKjW6PgnN5eo567cHUC7a9aqRzEJOXNMLYhHZfineu1WEH4dB8ZgtvamUx60lCQkLuqcUiaf3TjmHE12QynbZh+6H1mFqNFXYApH0bWTDqaaoC1csiMpGmUxYSxDd+PNv1LPqeTJ0YXlJcnPHKGyzJU93mZ6vQUCxTu4I3Qbf5xZArkiZtcYXkiYS3LE9+v0fIEnVnpD+UlTAq72fFNwDcx0K11oH9bmcqxsUZzuXXuGckS/vHA/celq/3jQUDLSN1ih/5kXel8CshtQCh1opv0kuJtjlbDuKk1Ao5DedQ/SdcEdSoZY+68mV3RKHOF7p/DDQaNd4Zip+QuUqog0W0sOnRrKYKGWjaEBZZZxjbK5LbfI2YKYhAwMJ9f1aXYqgBKTgg+JRfiZfJ64+OS8/Awc8vquJhLgKnH8b0M3+vwHYrvc/iuwXc33sdYtLbDarNb7b/Np1pU6/Efp+Ywz7ef55v0FdmLY0RfseFeqCEu6h7RV7QpTm0s+4Ft6U898QBrL1rS5NzUXWjEiN3hvfr+u8cr6C/kMrgZgyPyx4AhZyN/nMqfVbNI3SPyiCyLkLF6brDU3vC2VJ5+pI94SvQRPwyEPgLt5KreiflTard5cPhp131nWbly+p9J5v2/x85Ifgl0P638sv6eX7D/V+V9p8Ootl/6w4byW3c0EEN5GKYTc7r7Po2+YeRkTl34qIh4jw+DncDCLu0cC0enFO2yxx31ZZcBbs/PeHDRA0hppC3desTXLvn+P0BYgczSgTJZfxsP3zu1G+zGFHbgFg7LxH2iImxs4VeZmKp2fVmLuA5uD7KC1sQjqQ8XDpIEw5JMwAX5hkJLLy4=
*/