///////////////////////////////////////////////////////////////////////////////
// rolling_sum.hpp
//
// Copyright 2008 Eric Niebler. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_ACCUMULATORS_STATISTICS_ROLLING_SUM_HPP_EAN_26_12_2008
#define BOOST_ACCUMULATORS_STATISTICS_ROLLING_SUM_HPP_EAN_26_12_2008

#include <boost/mpl/placeholders.hpp>
#include <boost/accumulators/framework/accumulator_base.hpp>
#include <boost/accumulators/framework/extractor.hpp>
#include <boost/accumulators/numeric/functional.hpp>
#include <boost/accumulators/framework/parameters/sample.hpp>
#include <boost/accumulators/framework/depends_on.hpp>
#include <boost/accumulators/statistics_fwd.hpp>
#include <boost/accumulators/statistics/rolling_window.hpp>

namespace boost { namespace accumulators
{
namespace impl
{
    ///////////////////////////////////////////////////////////////////////////////
    // rolling_sum_impl
    //    returns the sum of the samples in the rolling window
    template<typename Sample>
    struct rolling_sum_impl
      : accumulator_base
    {
        typedef Sample result_type;

        template<typename Args>
        rolling_sum_impl(Args const &args)
          : sum_(args[sample | Sample()])
        {}

        template<typename Args>
        void operator ()(Args const &args)
        {
            if(is_rolling_window_plus1_full(args))
            {
                this->sum_ -= rolling_window_plus1(args).front();
            }
            this->sum_ += args[sample];
        }

        template<typename Args>
        result_type result(Args const & /*args*/) const
        {
            return this->sum_;
        }

        // make this accumulator serializeable
        template<class Archive>
        void serialize(Archive & ar, const unsigned int file_version)
        { 
            ar & sum_;
        }

    private:
        Sample sum_;
    };
} // namespace impl

///////////////////////////////////////////////////////////////////////////////
// tag::rolling_sum
//
namespace tag
{
    struct rolling_sum
      : depends_on< rolling_window_plus1 >
    {
        /// INTERNAL ONLY
        ///
        typedef accumulators::impl::rolling_sum_impl< mpl::_1 > impl;

        #ifdef BOOST_ACCUMULATORS_DOXYGEN_INVOKED
        /// tag::rolling_window::window_size named parameter
        static boost::parameter::keyword<tag::rolling_window_size> const window_size;
        #endif
    };
} // namespace tag

///////////////////////////////////////////////////////////////////////////////
// extract::rolling_sum
//
namespace extract
{
    extractor<tag::rolling_sum> const rolling_sum = {};

    BOOST_ACCUMULATORS_IGNORE_GLOBAL(rolling_sum)
}

using extract::rolling_sum;
}} // namespace boost::accumulators

#endif

/* rolling_sum.hpp
32AH8VVihOX7/AwKkBz3dHnE7jcRe7P6uSnqQj0AHeC40dmadocTnR3gQBCd7ROPsBPhzghnIexEeDTCWQhPRRg9nS2dHoDOzpPO3kcxSJB+PUiRSFvC/tGQqqMpXNond2bnkLtSqGPvny7z0T08Ymx3kUvO3FMySscAMYEvlOa8UTmbsiSkjmoaYmq0CKFWoPrfRvDxb/oJbk8u5neGNgRQNRnW5MC2u52kWZqgBp0oo1VaXlpp/ajmJwXJNCiF75lIdqmdjXk+bKZK88J5nmVRoe4oVHJCCr1YsdBLjWm1eElWi6ITslrM7sU1zZM7jf2IzZvpRnVJCH2HEH46wXu7F4Ll1m1ALPfV+FgxpNiU2q3Jzri9MY8iFvpMbJO5E7F9zPpwd15z2rdE/bIUpW+lZQRH0dq0gqnYUALmQwHmMg3MkVSULD5/a3jV/xjy8ewOojFzREaD7+IeYxqOebZFLN9MtufNkmcGop5AFMG9+lQZRY1HV/bhgE5RGX3Epj6injkuUbcf4lxORHUsk6itdThXx8Ia+n3d7qZi/5p0OcoEKT2SOKq2KZmnSEfHqt5cn72/ue2lv6f5tc12uTNHJz87XsYAvgJ8iLZxBjhA5e3p+w+pDdR2JTow+udo0RpqBnXSyvyfSoncGe5Q7Cw8F0JpM44vB2uTCHIu9DcqWq3Nnelm2WVncf3NxHQZoPUqbO/t82k/SlMuiSXDiSQEHmpvwdlgpTQ3hflzHHRlaYl6oJ3pgvQShPUWBgLiumgYPfjTMVbxYnVCV8H9tNhmQS7tK045M2sx5UQ7Wn4MgAQ+V8G9lC/BaUiOdyAjJf/6waoU36va+u97PvmlzBeg/2VJv8EWeF8015J++Fhg+XGW9DktAsv3tqT3qx2YfrElPaJbYHq4pHujRjYDg1jeWHQmiPgzEIGtT8PWMg7NOVSzdRUs55anr+cThL67Yl5p+h5J8pBjuXTvEpHjJCLvHynvao/Xke9bfEL8M/X3I1ESP1l/r+sm3386I+kRKeYB62WGr/pDbfp/bWPqt7yjoblBf+/4RVrbr79P15X4z/X35RqqCEB1Tiis9kLuljbZXMixlU5PI/UITigBppLv3TmjLh0np7dhfrTvWJHNwxFvCRPbfKwoVCIejeCIFceKakjE5SeY8y2xF+6LzOaYdyXmT8eKIiTL39pymXxkqZ3toBiF/vD7WpwwEFtHYptC8KffWVbVVklVPtbzzi2tDfspxiOYwg68TiEEFPGlGd3zCcvG/nSrOlyTEeZiP8d8ONb607y4iwpOGyiRiIPuKxC7NJSaeq1nhaOPF3cP7IEd6i/nc15Bf0xV3UUXa/nQdrkP1eNqKrnmkU22MYcBWH2sw1Cg88W8c1tjOlI0nRPpgzahxjOyWYohH0p8c5zfaPhicqVEXG6k7SzZ71wSJdmvMrOHniV7k+d19ovN7DXOkr3pcA3MsVsN8EMizgp+WwP8j281Gog4S/aaRvbHzezOs2T/7medfbwJD22+z1JihVGii78HNc9a4imjRKi/ROhZS8wwSmycapaoUUkJDmtqOe859o/8WOfvmxfK/BVij8532crLFqa+icXGCR7FJjXaLqLddU57eJzGlW8rpGdRehEWDsLSsAmI6YkYPNOrizLYwP4ucTNSVGRH09X57dgnmO8MPjK33BNVIi75eAd8+s+o85YEKp/TnuQfusQEyjx4EqtE9JqowqIr8oOi8+ECgfdPj7Y03z9qr9SFRwWSLFaM6GsoRsyI8itn0MT9FotOftSnd6AbF7TXKvO9oz5AmOrJHzSN6riKBT9vgt2tQc2jUbO6xFIP8FC2OFbu7NVHYJm57xPuQz4=
*/