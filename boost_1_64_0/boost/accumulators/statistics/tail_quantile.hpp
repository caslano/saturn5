///////////////////////////////////////////////////////////////////////////////
// tail_quantile.hpp
//
//  Copyright 2006 Daniel Egloff, Olivier Gygi. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_ACCUMULATORS_STATISTICS_TAIL_QUANTILE_HPP_DE_01_01_2006
#define BOOST_ACCUMULATORS_STATISTICS_TAIL_QUANTILE_HPP_DE_01_01_2006

#include <vector>
#include <limits>
#include <functional>
#include <sstream>
#include <stdexcept>
#include <boost/config/no_tr1/cmath.hpp>             // For ceil
#include <boost/throw_exception.hpp>
#include <boost/parameter/keyword.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/if.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/accumulators/framework/depends_on.hpp>
#include <boost/accumulators/framework/accumulator_base.hpp>
#include <boost/accumulators/framework/extractor.hpp>
#include <boost/accumulators/numeric/functional.hpp>
#include <boost/accumulators/framework/parameters/sample.hpp>
#include <boost/accumulators/statistics_fwd.hpp>
#include <boost/accumulators/statistics/tail.hpp>
#include <boost/accumulators/statistics/count.hpp>
#include <boost/accumulators/statistics/parameters/quantile_probability.hpp>

#ifdef _MSC_VER
# pragma warning(push)
# pragma warning(disable: 4127) // conditional expression is constant
#endif

namespace boost { namespace accumulators
{

namespace impl
{
    ///////////////////////////////////////////////////////////////////////////////
    // tail_quantile_impl
    //  Tail quantile estimation based on order statistics
    /**
        @brief Tail quantile estimation based on order statistics (for both left and right tails)

        The estimation of a tail quantile \f$\hat{q}\f$ with level \f$\alpha\f$ based on order statistics requires the
        caching of at least the \f$\lceil n\alpha\rceil\f$ smallest or the \f$\lceil n(1-\alpha)\rceil\f$ largest samples,
        \f$n\f$ being the total number of samples. The largest of the \f$\lceil n\alpha\rceil\f$ smallest samples or the
        smallest of the \f$\lceil n(1-\alpha)\rceil\f$ largest samples provides an estimate for the quantile:

        \f[
            \hat{q}_{n,\alpha} = X_{\lceil \alpha n \rceil:n}
        \f]

        @param quantile_probability
    */
    template<typename Sample, typename LeftRight>
    struct tail_quantile_impl
      : accumulator_base
    {
        // for boost::result_of
        typedef Sample result_type;

        tail_quantile_impl(dont_care) {}

        template<typename Args>
        result_type result(Args const &args) const
        {
            std::size_t cnt = count(args);

            std::size_t n = static_cast<std::size_t>(
                std::ceil(
                    cnt * ( ( is_same<LeftRight, left>::value ) ? args[quantile_probability] : 1. - args[quantile_probability] )
                )
            );

            // If n is in a valid range, return result, otherwise return NaN or throw exception
            if ( n < static_cast<std::size_t>(tail(args).size()))
            {
               // Note that the cached samples of the left are sorted in ascending order,
               // whereas the samples of the right tail are sorted in descending order
               return *(boost::begin(tail(args)) + n - 1);
            }
            else
            {
                if (std::numeric_limits<result_type>::has_quiet_NaN)
                {
                    return std::numeric_limits<result_type>::quiet_NaN();
                }
                else
                {
                    std::ostringstream msg;
                    msg << "index n = " << n << " is not in valid range [0, " << tail(args).size() << ")";
                    boost::throw_exception(std::runtime_error(msg.str()));
                    return Sample(0);
                }
            }
        }
        
        // serialization is done by accumulators it depends on
        template<class Archive>
        void serialize(Archive & ar, const unsigned int file_version) {}
    };
} // namespace impl

///////////////////////////////////////////////////////////////////////////////
// tag::tail_quantile<>
//
namespace tag
{
    template<typename LeftRight>
    struct tail_quantile
      : depends_on<count, tail<LeftRight> >
    {
        /// INTERNAL ONLY
        ///
        typedef accumulators::impl::tail_quantile_impl<mpl::_1, LeftRight> impl;
    };
}

///////////////////////////////////////////////////////////////////////////////
// extract::tail_quantile
//
namespace extract
{
    extractor<tag::quantile> const tail_quantile = {};

    BOOST_ACCUMULATORS_IGNORE_GLOBAL(tail_quantile)
}

using extract::tail_quantile;

// for the purposes of feature-based dependency resolution,
// tail_quantile<LeftRight> provide the same feature as quantile
template<typename LeftRight>
struct feature_of<tag::tail_quantile<LeftRight> >
  : feature_of<tag::quantile>
{
};

// So that tail_quantile can be automatically substituted with
// weighted_tail_quantile when the weight parameter is non-void.
template<typename LeftRight>
struct as_weighted_feature<tag::tail_quantile<LeftRight> >
{
    typedef tag::weighted_tail_quantile<LeftRight> type;
};

template<typename LeftRight>
struct feature_of<tag::weighted_tail_quantile<LeftRight> >
  : feature_of<tag::tail_quantile<LeftRight> >
{};

}} // namespace boost::accumulators

#ifdef _MSC_VER
# pragma warning(pop)
#endif

#endif

/* tail_quantile.hpp
+vpt1BKDArbBPCiyT2BQ+DC+P7RDvrAMsXmte0HQ6c5vyd6RKtDOmmvlqi1lN3JuI5QOnjm91EL83D86McYxfSerk8G7hHE6V2SQ64WZwuK2qU2LZciNd7Kf38AkzghxVJvJIj08ZUHw6MR2aXbck2HhQsAQ/aPPjzGGIAgDj+7dI8yF8oUND69JuCp5Gm8oGqRXssIEfmHBOF+GDUwJT2KUTH/dJF85FtaAsWCHWrkZ/tHxWGwXp8XzXsx1YU5lFPMRFScMxt5noanD41TF8c34ntfci6gwmU5V9wnU90fcoWKP68SYF0q9Ga7DOcl5a6h0Y5VzrVV5s7fn7xlH1xOgsT7nqoEz3Y6Fk+w/HQ2FCizeYIbF699tyS3l3KzIrTjtfKoNsnPk/wUPXKYjn1zKIO/c5l6YNYpZONt0p+SdIHzn9kArLJSOGMSNXteRnDZObAVsyQ+Na+51/giHQJH2U/nXUvnuguqwkkYFSiy5u5EOWYZz56ypj2dcAm2LId3OuEcV0/P3eMB42D4M5kklV6FgU7W4CnWkXmOrE3WMX6B7Lh1rGxh6tuTeG28c0tOb/7vjQA54tBo0ksjEfzJ2XFLwRhDpuglLG1GMjrnnB288GdpiDokNbXEdymnq/MGbvVZn5Mte47Vu1UwT94jvTYwJDLGb6pYfgnWbo1txwFramFDuk6iYlCB/NSYPhVmPUg2oDfhCahl1o6ddM7dx3GvIUEAcR1cXDZ3sI+hU9VQ1jBniyzaXK7eGeJgE+e/yWn8Ij56SF4FDtwHEuEoKT4odkWYgovGOsJZzsMb//0ev/18Q7k3IXelJic25KELveWXi3gWes9yhFeTe5Xs3Se8sj487SJeznVbfEd0fqXR8IU5KzjSOBkd9ianDQ6u+/erBqZFp4X3WpSqeEaZb9IyQTzwu2DXkP3r3yMtJz9SbuPJ6x8Jp9oMvx8UYsws+wh/IOfQV2GJg9PnJocDohExjS7qx2m38DRSoZr5DtGoUl7iQFw20cT+WfhYRRbaIKHJoInP+y/zg/CWvaWk8N41O+LzNXOdJWYu/wMp5ZPYD/iKZ7JRM3pJMvsSfev61iEg/3l8yhKQakX9ymvD5PX0Twvuq2Y8h4uwFT4YzzP1G84GOEzQHb07ibjqhoxnyMUu7qcAqvGdhXJU+i7o6JsUiAtd3zwKRHvdjKIVZNgYwYqosiMglwxBRplqU9OfBB0PlcHbHfO4WmNy3HYN2FJfGmt0RV3lgAzZON78UFzMS39X4HsB3GL7j8Z2ELuqL/xhLDfnEWm3Vavw2n+qb/js+Zv3g3mfC+kE4lm2x2F6LqemuCSCjVn+ILMqv1m5li1PPt7AkRn0UwO2YdFsaEnaTy7qdlOxxrHEq7LNto0M0Y7CW4dvKCJg1+RfsmEX8X0rdxXG0yfUlCRhq/mTzRSAI0S8NOM19YiZ56bxbBK8R4+WQz9cYZeLR/cPJ4afvIchw4rMySzDjd8bTYX/2cGd/L4qoeDMJBgY5zFxn2kEIAPGnzl3uZx9XJ2bVueo/yN/hLVEtxvfzuIpuQ2lD7lH5pMHYRIxxAYZyWFTuGWaMPouYogyIyMuDEJ2MuYd5jD3qpYER9jPuSpJrovqE1pAiSNicNUP0CSL3WdJszjLwqh2ZWPVP2o0Qkgi/InpLs9EEsTiGjSzTWrtKjBNgFsCZo9tRvn+gSyJxezV0nrCcR3k5Wezca7h81jKdHPVoY5avKtfHqusz7qZwXT4VQQE1GZ+HxqmXIPdAlCqtRcDjAMjjNxrOLrx95ZaGd8C5IsXKRSyPa0/Odo9zj9s4VLqZ0UVvJt9DYmSC3INTugiEG017JgT2K39SI2o=
*/