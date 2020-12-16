///////////////////////////////////////////////////////////////////////////////
// weighted_sum.hpp
//
//  Copyright 2006 Eric Niebler, Olivier Gygi. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_ACCUMULATORS_STATISTICS_WEIGHTED_SUM_HPP_EAN_28_10_2005
#define BOOST_ACCUMULATORS_STATISTICS_WEIGHTED_SUM_HPP_EAN_28_10_2005

#include <boost/mpl/placeholders.hpp>
#include <boost/accumulators/framework/accumulator_base.hpp>
#include <boost/accumulators/framework/extractor.hpp>
#include <boost/accumulators/numeric/functional.hpp>
#include <boost/accumulators/framework/parameters/sample.hpp>
#include <boost/accumulators/framework/parameters/weight.hpp>
#include <boost/accumulators/framework/accumulators/external_accumulator.hpp>
#include <boost/accumulators/framework/depends_on.hpp>
#include <boost/accumulators/statistics_fwd.hpp>

namespace boost { namespace accumulators
{

namespace impl
{
    ///////////////////////////////////////////////////////////////////////////////
    // weighted_sum_impl
    template<typename Sample, typename Weight, typename Tag>
    struct weighted_sum_impl
      : accumulator_base
    {
        typedef typename numeric::functional::multiplies<Sample, Weight>::result_type weighted_sample;

        // for boost::result_of
        typedef weighted_sample result_type;

        template<typename Args>
        weighted_sum_impl(Args const &args)
          : weighted_sum_(
                args[parameter::keyword<Tag>::get() | Sample()]
                  * numeric::one<Weight>::value
            )
        {
        }

        template<typename Args>
        void operator ()(Args const &args)
        {
            // what about overflow?
            this->weighted_sum_ += args[parameter::keyword<Tag>::get()] * args[weight];
        }

        result_type result(dont_care) const
        {
            return this->weighted_sum_;
        }

        // make this accumulator serializeable
        template<class Archive>
        void serialize(Archive & ar, const unsigned int file_version)
        {
            ar & weighted_sum_;
        }

    private:

        weighted_sample weighted_sum_;
    };

} // namespace impl

///////////////////////////////////////////////////////////////////////////////
// tag::weighted_sum
//
namespace tag
{
    struct weighted_sum
      : depends_on<>
    {
        /// INTERNAL ONLY
        ///
        typedef accumulators::impl::weighted_sum_impl<mpl::_1, mpl::_2, tag::sample> impl;
    };

    template<typename VariateType, typename VariateTag>
    struct weighted_sum_of_variates
      : depends_on<>
    {
        /// INTERNAL ONLY
        ///
        typedef accumulators::impl::weighted_sum_impl<VariateType, mpl::_2, VariateTag> impl;
    };

    struct abstract_weighted_sum_of_variates
      : depends_on<>
    {
    };
}

///////////////////////////////////////////////////////////////////////////////
// extract::weighted_sum
//
namespace extract
{
    extractor<tag::weighted_sum> const weighted_sum = {};
    extractor<tag::abstract_weighted_sum_of_variates> const weighted_sum_of_variates = {};

    BOOST_ACCUMULATORS_IGNORE_GLOBAL(weighted_sum)
    BOOST_ACCUMULATORS_IGNORE_GLOBAL(weighted_sum_of_variates)
}

using extract::weighted_sum;
using extract::weighted_sum_of_variates;

template<typename VariateType, typename VariateTag>
struct feature_of<tag::weighted_sum_of_variates<VariateType, VariateTag> >
  : feature_of<tag::abstract_weighted_sum_of_variates>
{
};

}} // namespace boost::accumulators

#endif

/* weighted_sum.hpp
/rw2cX4nE6f3ekycnBhMnMPq2L8xnnwGKejjHKUSRet4snCfTplMwv9pO4v9kxMxOaxzK5SK6rsRBaBwsoeuGAnAXHn3tQNwOcrKnJTKHMv7rgwAZH1shSujHOC1ArC4xQnQdccbg1dWvNHdW4cuW6BTPtDwOMO3+VmG75BcElSQUjxpQkHPSEjdccDa1RuQC+Ah/xrBykSyXytL7Hcf8BLLQdvVeuzKKM19M5k3X5VuT1nptHzglXNC4MuMykk28pSw/TScL0xqhxJrCh1520CGq6sQpS2alMAofyCAQItLls8UlwX91reGlpHvj/7uu1IO41i1Kz4D0K68DZIdeQkf59KBuvlS4NjTHHlbCRrgXldehXoTavLe3E47GeAOxuzQse4p8lJ28n683rNxM05elV3BEfiHrpRNdsg3oUHOU9qVsdH6WEUOzeQVrXbk0DQu707n93ZMY3v3nTT1UULF0fH7vMXC2ic+tbg9FHmAFYnD7YLxn4mItNXqc2CaEVq/jEOPIsQ9fGwDD9FnFrpoITu8WhzQae7cQndqMYdHa2lyEmsuQwuHUYqyDSglGerO4oTvaxddPArU5hJVZnLEcvl7oip3QF0K/K+oUGamyXuD8JsbhN80Eb+ZsRz7wxHmRodJ6iJJPZ1SuyLVAR4yFjfjkghDHbdArAZosj1sZvQJ34fEA++YJyTBBHbJIx7YSK2gE8J3zFEq/BXkUgkT+vQs8V2inZ48WCLfDaDv8oqSbXiymhpMWdW7tMQzOZKahwI6i08aTalrsJblZ6bbUDIiuXD1rmmSsgcpb4n2w95xw4S/ELjp+7M1uN9GhlDI9j8oKX+PKNmmlUyqTrhNLeOTMa/xp2llOJNLIn0te0aZu2MOQq2sy66LzrWXdOBjPVLR+wKo4ixK76Jl8uuZOsJ5NDLtp0wHC6KR8YwgoOOJ5sIHCrqx+mUWT9BQD4MJGs2HgNc7ynqOF+5KMnU/PA95MAeQRTxfi2OSInwGhyQ094Tk+u/XiTb+pgx8/JwOsLeypJVVQFfLh0BF5H685VWRp5Ozcsi5IWPF3UZT3ta24sbsC0jmqj6Nz2Qt+qL0tZiJFBASduVAFhMS0PEtaJ+VnngaqgYErehhzaogFbfPXgoskgJ2uzOu1I/pBz+YUYzgIaOx5pCrI6+b5ZNZrMw7fg4W4tvJzyIP+Hp2J+gip0paJnzE+Wh454INoGfDgoAV/g2rMOAoXvPD9OxUDDhAmQmoebjByfFw50adJP9JGv37inQUuqJVSWJczw6C+XCTnr30ajnOre3RweRv/9ShjqZVMf2QoQncCLIYkoCKYNhnpwEypod8VLfprKH3GGIUuw0hY377iIrQcD7CxvIFCmP9CRWNpkv5IzlozG8y1i9KDcbvO4WU7x0aAQ/idJhaGluDn3colWcs/57uKyoizj9fCjLTmZk55FGbutfp343jCOvy3QljL9bEki3GnO6pjx3XCzcTmTG9WObptg200KOt+LMYa9y8MG2PvYmFwCeDZxyPY97frWl4nC+tSNsZdO2QS/1bmODx28Z1xMV212BbWiF8cC0e6nQcOhLf67uhExHt7UkveltGpZtXW4fiMia4QP30ohxwSB9vkv0+1eCOQpkgThxOjA9R7Klh7U0IC8eFhHn6Rp5/vCiqfDR+a5xKZrojMIQO/257YAyvDh3DTBnD/iFjmMJjGI9DE/vU9INkiWrlnWM1DvZi1L1Fv2Zs6WdUJZr8r6ApagON1mCMFrvhUIYneA6zo4o8oSUSP+RBuw8PFQ5LWGot7iPCtIqqH3qSKPNmm0RmarDUviAUWv+p/gVo4ORs9/2+wYcH/g1p1gdn88Y=
*/