///////////////////////////////////////////////////////////////////////////////
// kurtosis.hpp
//
//  Copyright 2006 Olivier Gygi, Daniel Egloff. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_ACCUMULATORS_STATISTICS_KURTOSIS_HPP_EAN_28_10_2005
#define BOOST_ACCUMULATORS_STATISTICS_KURTOSIS_HPP_EAN_28_10_2005

#include <limits>
#include <boost/mpl/placeholders.hpp>
#include <boost/accumulators/framework/accumulator_base.hpp>
#include <boost/accumulators/framework/extractor.hpp>
#include <boost/accumulators/framework/parameters/sample.hpp>
#include <boost/accumulators/numeric/functional.hpp>
#include <boost/accumulators/framework/depends_on.hpp>
#include <boost/accumulators/statistics/mean.hpp>
#include <boost/accumulators/statistics/moment.hpp>

namespace boost { namespace accumulators
{

namespace impl
{
    ///////////////////////////////////////////////////////////////////////////////
    // kurtosis_impl
    /**
        @brief Kurtosis estimation

        The kurtosis of a sample distribution is defined as the ratio of the 4th central moment and the square of the 2nd central
        moment (the variance) of the samples, minus 3. The term \f$ -3 \f$ is added in order to ensure that the normal distribution
        has zero kurtosis. The kurtosis can also be expressed by the simple moments:

        \f[
            \hat{g}_2 =
                \frac
                {\widehat{m}_n^{(4)}-4\widehat{m}_n^{(3)}\hat{\mu}_n+6\widehat{m}_n^{(2)}\hat{\mu}_n^2-3\hat{\mu}_n^4}
                {\left(\widehat{m}_n^{(2)} - \hat{\mu}_n^{2}\right)^2} - 3,
        \f]

        where \f$ \widehat{m}_n^{(i)} \f$ are the \f$ i \f$-th moment and \f$ \hat{\mu}_n \f$ the mean (first moment) of the
        \f$ n \f$ samples.
    */
    template<typename Sample>
    struct kurtosis_impl
      : accumulator_base
    {
        // for boost::result_of
        typedef typename numeric::functional::fdiv<Sample, Sample>::result_type result_type;

        kurtosis_impl(dont_care) {}

        template<typename Args>
        result_type result(Args const &args) const
        {
            return numeric::fdiv(
                        accumulators::moment<4>(args)
                        - 4. * accumulators::moment<3>(args) * mean(args)
                        + 6. * accumulators::moment<2>(args) * mean(args) * mean(args)
                        - 3. * mean(args) * mean(args) * mean(args) * mean(args)
                      , ( accumulators::moment<2>(args) - mean(args) * mean(args) )
                        * ( accumulators::moment<2>(args) - mean(args) * mean(args) )
                    ) - 3.;
        }
        
        // serialization is done by accumulators it depends on
        template<class Archive>
        void serialize(Archive & ar, const unsigned int file_version) {}
    };

} // namespace impl

///////////////////////////////////////////////////////////////////////////////
// tag::kurtosis
//
namespace tag
{
    struct kurtosis
      : depends_on<mean, moment<2>, moment<3>, moment<4> >
    {
        /// INTERNAL ONLY
        ///
        typedef accumulators::impl::kurtosis_impl<mpl::_1> impl;
    };
}

///////////////////////////////////////////////////////////////////////////////
// extract::kurtosis
//
namespace extract
{
    extractor<tag::kurtosis> const kurtosis = {};

    BOOST_ACCUMULATORS_IGNORE_GLOBAL(kurtosis)
}

using extract::kurtosis;

// So that kurtosis can be automatically substituted with
// weighted_kurtosis when the weight parameter is non-void
template<>
struct as_weighted_feature<tag::kurtosis>
{
    typedef tag::weighted_kurtosis type;
};

template<>
struct feature_of<tag::weighted_kurtosis>
  : feature_of<tag::kurtosis>
{
};

}} // namespace boost::accumulators

#endif

/* kurtosis.hpp
+iduvX0vEKOovB1YG0OCbCih7WDR8dLT2w4sedUYqTF3Od8AkErhuW7Dv5ClDeDjbdJ/LTQtnlwx4qTn6WZmfzyxVd4XDcWbkpPIF/Yc00V3q/nrQrcRxuHkoKpHStP+FRwBicLVagFWsO2u7SLy+uYVF993/CKnEQ1Abf7RKlsS9Z4skC2qe0PZP5KM4l8nQbDkf1az5YGe0S/F1ExPysv8XBWx6LLolJcafH9DRh41OjaWa7jHLHD8vnNAihrl0O87J44gLKZAKTceU55eG0UQNlo626TxY6n2bI4Ugqu869kCZwk9PCZ9ndfpKuZWquYmEicTUM+OUkhWbxPJqhMZiBylc+oNvwI9If/f0g/rPGnxCyk2CfOCvzmJNY9WFxVVUGCagXhmfulQ+75N/eidL6uKmN3FadGk0YK/cZG0WtOSWKfJ+QXfSaaYOk2XaKC9KgP9E4DiiCkoiEEutlrQ8J/DaOgF6IOK53JeYNkneZyv10scP/9kTc9rh4Q8fhHfrp4sYzyzm6rVbpIfgCYe8cK4NUGnvzPZEskhl3EUISYyvYxDXtL2dhlBiiJhVTr+krIUxY+g/+Xgf2Lvdlg6/pfmTo3NZq3+BYS+Ffre/dXQ1v6yavMFi1CfAxgyLd2YePaGeKmnciDoDOSJHx/iieNJC4MGydkmjOgvYDunzUQYNNiTun405uv8dmkIi5bJtPdpIE0jNrvwKYm55biHR03OqQ2xr/A7HSxKU0OEjaFQPrJDh3bKY2Bpux76e9SdfP950LI4Eg85HgUm8fMsp1gYGYFpUbqUlo4CONWhQcjm4accHaDoWI4G4kgqnMmM7Ge0KpOwKkP2kZD7oAhFn0VRWqy76ldcrJ+68g9LjslLZTUuYw2CA/RwqBci9hLUZvwYam9pxXXuyi+Tor256GY1HkVd+eUS2YUjt6hbKdIoJiTHU8rk92kmmf7KoFVSxIIPxAWawFVWhrGUcJNBNvVJPO7p5osVL1IZRq94Un1hD+YZRpg69wTT4DEe40bY+ue5m6WGHsbyci7LiIOF4nmi43L0B49xLYxyjnC4U791O/t8O6kw6N6x3+18FWr/b2JCUi3XJmSn8GBRa3bIhLt7SWjC+dXSz6j/RwNXoJXvOrhBh4xfcBeQRttpgvQ6FUXcEWtc+Z/L9kqeOFutwTcv82fyae1/IUk80g2Qn1JmIAUuIKL5OOfK/1LIw4HF4G/u5EJf60I5iP54sRS6Binaufth2cox3SO8/m5emkcZROu3gFaxphG/JFpFIYp+mz74fR2nz+fmww8dximiiFYpkQ3TKrpzajcH5XqnXQr/LXQnFnuM3ZaZqMTP4Pw1WrSvEZfPnV2NTBRaRaHUN7mCMeAEnCURpM/02kE0fZ77qm11w8JG181n79+Xua+Kj+BgFAU7uK+60MHBSArGYQX2RiCCAg0QaOo+ZxUqDs+bGeTGRkLDUGoXXzw7vnA7TBtUV6ZUbQNxO5nouzQx4jNcCRhNU9QCyNvYDJAA7Ubz38f2SN3dGmD2NHAH12qd72J0GvEALXia0oRc5IF8mRjlcWD3EEfDeU77UnKDDufUQLjMs/qOEHVzvGKfbC5ebNntkjzGocBGONhis4BY6/VNE9slaz1GrzgvneCxIvyRuwmtX2D2i2Wx7EK0GY1MRQPHgfcfTDOnp4Nh8rxkZi/D325Phv++PehIzC7Ai0ePPw0MIMaZXT84X1Xu1M1jhiVv9+SlBd0RhZ6jhz2pvWLHpltr5Wohej1etjd/yt9pznaXNdEBSdS4G+qUhfp0FEr/mGvclJIo8fZi+OI9xndksCl1lzP3VQIslC8zyEwqVNNQOLGQCqVlJAY=
*/