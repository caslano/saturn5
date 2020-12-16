///////////////////////////////////////////////////////////////////////////////
// skewness.hpp
//
//  Copyright 2006 Olivier Gygi, Daniel Egloff. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_ACCUMULATORS_STATISTICS_SKEWNESS_HPP_EAN_28_10_2005
#define BOOST_ACCUMULATORS_STATISTICS_SKEWNESS_HPP_EAN_28_10_2005

#include <limits>
#include <boost/mpl/placeholders.hpp>
#include <boost/accumulators/framework/accumulator_base.hpp>
#include <boost/accumulators/framework/extractor.hpp>
#include <boost/accumulators/framework/parameters/sample.hpp>
#include <boost/accumulators/numeric/functional.hpp>
#include <boost/accumulators/framework/depends_on.hpp>
#include <boost/accumulators/statistics_fwd.hpp>
#include <boost/accumulators/statistics/moment.hpp>
#include <boost/accumulators/statistics/mean.hpp>


namespace boost { namespace accumulators
{

namespace impl
{
    ///////////////////////////////////////////////////////////////////////////////
    // skewness_impl
    /**
        @brief Skewness estimation

        The skewness of a sample distribution is defined as the ratio of the 3rd central moment and the \f$ 3/2 \f$-th power
        of the 2nd central moment (the variance) of the samples 3. The skewness can also be expressed by the simple moments:

        \f[
            \hat{g}_1 =
                \frac
                {\widehat{m}_n^{(3)}-3\widehat{m}_n^{(2)}\hat{\mu}_n+2\hat{\mu}_n^3}
                {\left(\widehat{m}_n^{(2)} - \hat{\mu}_n^{2}\right)^{3/2}}
        \f]

        where \f$ \widehat{m}_n^{(i)} \f$ are the \f$ i \f$-th moment and \f$ \hat{\mu}_n \f$ the mean (first moment) of the
        \f$ n \f$ samples.
    */
    template<typename Sample>
    struct skewness_impl
      : accumulator_base
    {
        // for boost::result_of
        typedef typename numeric::functional::fdiv<Sample, Sample>::result_type result_type;

        skewness_impl(dont_care)
        {
        }

        template<typename Args>
        result_type result(Args const &args) const
        {
            return numeric::fdiv(
                        accumulators::moment<3>(args)
                        - 3. * accumulators::moment<2>(args) * mean(args)
                        + 2. * mean(args) * mean(args) * mean(args)
                      , ( accumulators::moment<2>(args) - mean(args) * mean(args) )
                        * std::sqrt( accumulators::moment<2>(args) - mean(args) * mean(args) )
                   );
        }
        
        // serialization is done by accumulators it depends on
        template<class Archive>
        void serialize(Archive & ar, const unsigned int file_version) {}
    };

} // namespace impl

///////////////////////////////////////////////////////////////////////////////
// tag::skewness
//
namespace tag
{
    struct skewness
      : depends_on<mean, moment<2>, moment<3> >
    {
        /// INTERNAL ONLY
        ///
        typedef accumulators::impl::skewness_impl<mpl::_1> impl;
    };
}

///////////////////////////////////////////////////////////////////////////////
// extract::skewness
//
namespace extract
{
    extractor<tag::skewness> const skewness = {};

    BOOST_ACCUMULATORS_IGNORE_GLOBAL(skewness)
}

using extract::skewness;

// So that skewness can be automatically substituted with
// weighted_skewness when the weight parameter is non-void
template<>
struct as_weighted_feature<tag::skewness>
{
    typedef tag::weighted_skewness type;
};

template<>
struct feature_of<tag::weighted_skewness>
  : feature_of<tag::skewness>
{
};

}} // namespace boost::accumulators

#endif

/* skewness.hpp
yMCx1exTZf3bEKb794eR0r/7R0r/stTjNSyw33aYYb91pAn7+JEC+3UjNexDzgV7l18Ju5b/hRm7iWXXiiRzLp1ol4aLbUB6LLwCT+XUni0m9xkKggDs04QDuwsjDMVI0bq8HHTl1Fw6dzvnaYWodZqXn4rkXPUK42pIxCvfIA+YJv1e5aDLeGyxOgEYTWLxVZ5hQe8/Qo35vmsEKGesg2Xoa0ece/Jq+adRPvyxERo/XsQDJYydfHc4djcOtXJzRfQMP14BPSsamuhpqXExdpuJnj/rXLvqVEBP3j4/el6ya/REjDhv9BjjbzPw89drgJ80uWN44Zpz4yfA3uAXIYY9AN7KfKHKztA+5jPtcxuGHdUYoInJlFmbxYxfVeq/I8QUvHpPgrX5Yk5kNCZuBvTV+jyaJLOi4n+ED6brYRJZ3QoQkIPVnrepT6+LZBsvIzh2PTieKpa84Gp9GNpi7xaGdN7GqkN6dn5f5CvT/F4t3ye7HPMiCKRf8f5HcqvHOetqlrsnYuU/O78ZxaVEf+ykunqfpdMW52Hztkg9Z73/MKANXztc0/vrTO8uTe9O9ckPJq3fUdhQm+TMDWO6vanQqQn5629la1c4QUfM3MgRfUXVoraEkmn/5hNN6+dlNrRGVLyOKpNKGiBq8S8SNXGTfz6cDtfzIX74bzUfYn7R/Y9aOwzz4Q/hPB+WDavCfPC6pheVC/ORvcgSnkfhs58HHj+jR/IEm4Y4YL1P6W7cp0wBeJkPkJ4PRlpr6CCqG6JyYtTrYXTtlqMPyal0Zu6hnkAkSdLNJ4ZuqezO0pY4asgpgy/xKEMryjCAj2LUhcIn5ChWfwsdxRYoGMX6TTziV+V8NPd05fgYYeDjVnS+Rx7JOfda8dEuj/HxVKgVH9cTPpzqPkTqGwUTJePPhZLJjJI5hJLfC0p8mwglD6mD3/3mKAnAh5PlX6cC8aFlYdmAxbD+VbiSVZa+ZX8sWQxcSaFgpeE8IOqb3VZE2RCV017dhrWACxrPxel9Cyo1bFj8RdXkmkqzVV9kzfA+SgSdqVUfyjZK8/cbzbvy+7WGZZs71cZvuVQPN0yXUQlgl530AMUUJYKtrRTVGfhmO/UUSKBfU1mXF7ZvrEZ3PWJ099fjthL9junl9VUeJsgkSsLzzHAQe0ve8A8Hx1rkcHlRfy4X9trahyJkCRcF1/86oTnQDozMjfdhsC4nHQVvJCkDNAUnfL4GGd/ZzXEqci2+i8P0QCYhuz5lgo+fo7+oroMIbeKlSe1vIeY5NEAHQ34jF69uX4ZUkoFUZg+Iz4Xixy6Lqtt0nKvLIBo9QfcfcyEnJGo9nHhQTfyqDO7tWtB9Ywe09S3YOgRuP+JLdV1RJr5rTrLIphbliaD1eiMqZAOb4m5rKlmeW8uvL19g46V8v+mtxday071233p2I/fBEWOdyumPeTAWrc1bT8re8crzgf/tEA1qsTMOw4oq8sLULogi5FGkFm648yaRH2tUrPryGbx/BLkmf/yI//chWbqceZPies/9xtOGzEUP/YXjpiKPg3BdCzKli8F1MvKyHcW9uD34XaqBvsx1Ybn7QCzDoXek/3ovhn0fbUjyQfXkkX0EbNhNQueyk9K9+9gdG56xTBJJzdvr5PZuGA6zpcsKC/QMvlP7JVnnn8HvqDSsGKUL1/4LPpb9nLCy144xmSTuFCtgyY1z6gsLzaIZPlxmuOr4BYspr8sFRn63i37bWY/lLW0HKJ6IT21isafY0P09zwU3I92uNpzmYajp9o5ylE5PHhWXc9QNX+sYjMZ8ot3+IY8EsozQDPHu2sfCDw/EqSunLmH1Qa4gJ5ZKYaj3QYDg+0TT1brS1u4=
*/