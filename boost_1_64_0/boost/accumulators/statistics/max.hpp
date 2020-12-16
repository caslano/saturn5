///////////////////////////////////////////////////////////////////////////////
// max.hpp
//
//  Copyright 2005 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_ACCUMULATORS_STATISTICS_MAX_HPP_EAN_28_10_2005
#define BOOST_ACCUMULATORS_STATISTICS_MAX_HPP_EAN_28_10_2005

#include <limits>
#include <boost/mpl/placeholders.hpp>
#include <boost/accumulators/framework/accumulator_base.hpp>
#include <boost/accumulators/framework/extractor.hpp>
#include <boost/accumulators/framework/parameters/sample.hpp>
#include <boost/accumulators/numeric/functional.hpp>
#include <boost/accumulators/framework/depends_on.hpp>
#include <boost/accumulators/statistics_fwd.hpp>

namespace boost { namespace accumulators
{

namespace impl
{
    ///////////////////////////////////////////////////////////////////////////////
    // max_impl
    template<typename Sample>
    struct max_impl
      : accumulator_base
    {
        // for boost::result_of
        typedef Sample result_type;

        template<typename Args>
        max_impl(Args const &args)
          : max_(numeric::as_min(args[sample | Sample()]))
        {
        }

        template<typename Args>
        void operator ()(Args const &args)
        {
            numeric::max_assign(this->max_, args[sample]);
        }

        result_type result(dont_care) const
        {
            return this->max_;
        }

        // make this accumulator serializeable
        template<class Archive>
        void serialize(Archive & ar, const unsigned int file_version)
        { 
            ar & max_;
        }

    private:
        Sample max_;
    };

} // namespace impl

///////////////////////////////////////////////////////////////////////////////
// tag::max
//
namespace tag
{
    struct max
      : depends_on<>
    {
        /// INTERNAL ONLY
        ///
        typedef accumulators::impl::max_impl<mpl::_1> impl;
    };
}

///////////////////////////////////////////////////////////////////////////////
// extract::max
//
namespace extract
{
    extractor<tag::max> const max = {};

    BOOST_ACCUMULATORS_IGNORE_GLOBAL(max)
}

using extract::max;

}} // namespace boost::accumulators

#endif

/* max.hpp
PHmtMAsf4aFi+32YaT+Nae71R3hS1zmnLKKFnbiOxigTry78DYDDuGg06DH22t3Alf87IqUxb8kqSkPfW/KiOMKabxFs62qdSukfE2Yffx5zb7erTcOMU5mCuIPFjLK+/q6Jngjlzi1CTV3XulNhKcqZS+tZxgN5MD2kzYEMzBcLkRmCyGMv2hHZ7RNCZH9B5KcvCiKbRNkQufSYDcYtAuOtCjBK9xCMWwXGExrG1kgbjNvtMG4QGPfYYExXf2MYNwqMIRqGYYfRHjBc+XdJjq46x21mDloR84SoxSHNlT+OM8bsZR1p/xu0k6YTk6lMq3hHXpBd9F5ZIyEGqj2aEsgvJ4+MF+4lyoravREKe3WG/348JBZHG2OHUL0jyEJXkjdxv7Zf6PG36uox2LJX4CjVGcFG7ZzLzmKagY2BBg6kA8OJuTT6Y3cQL7nWRrtTFzPU0Ss9qXuzu1i4ekBw1esFO76nQX9BOk2qlIGGaCpVmMMVysFL321AZ1rggvTyjheUeYKimmdhucHNICI06yXKm/i5tb+DlkHny6JtddygYCXRph6pin1NHhffHUQTcq+80uGcPo3ndl2SBKDuNHHjwV5BYJGjTLJ3R3YXzDxeuUIjBZmBktQ9Y3qA0+D8wrTwqzlM+13lqHiX6vu9lA+e0OVd+SZWg0WeHfs8qbtGr8RMkLK6hyCnREk9qaXOKRexvt47ZrMYf/zUUtNxY41KXSN1tAkXkeYw3uMT1xJJcM5cRvjhW+vhvO6zqLY4ROIZYFtAAo1Hz2k0hpcKnEEnqErkpIWJmcTDcC6DuRkcaeLNoJukLwao+Bq+zZt4yO0X9IKf7JsX2blvt6bxzuliCCnMuTImmk1FIWgUGruPflKo2qCe9N3Gg8zyphZmX4HGdABTGurmI9xGdfXH0qb34EJTZwfnBHCPrMLYU9A9vMjskfuD8mllZFmEnLQC/atV26VSfBKKg/8u6eQ1nNzhB7kmGnLi7Jl7iilU8w9L9oHIbs4YxgTP+WLMeeDROaUlxoRwI+Oi0Rtc5w6uJ5QzkgHFPwd4RL+S07sJa5/dA0+LNa5v/Uhq+gaeLnlM0/MmyE4UOPyjjjKRQPmXrWNVhe6cRRy3yFJajdzW2vtO9s31z9rpVD2gkKjRPOSUGh768f8eHf//+//vV/34fYcIAMSQ8hP7QwKAb/XJ3t3LOOoyEHFEtXgTyVjBNx8MVjhE8wMEmDeWY59+SrCF3myI9CxQajeIW7ZAW+imq4V3bAfoxO3Y+gdFACZY6eZqD2oTXlZbZO0bIU7Y+gelGc2+ZUEPpzVFGjvYDDBx6UCALbf7qHTyghAdWaYKP0BNn2sXyhEQNWBDKYjkLY8eQ04+RnoQ45q7c4/1GjcE/zcPI+7U1WN7I1nONQV8rumCcHwEh/lgcx7CF9J2HYeCvRErRxqBAkHr6nCuxJvnqivEL++BIPEIhSrCs+MbOv/B3baX2CWP8RlY9F2ufK95LWaxVJe9XGoZ8rUZTH/yaf1YryJqXWrbNnT4AGpLXk9nARzvuoElHtuW0LiSDmvYhnHIYFQ+zNs2pO2ocPSnlGM+cphmccmYL8XN5DjR0J/ClP1Dwv99L8hmQJwiS/1gD4adCfChm+3Vwg4KAVh1QHIO4JxOMvjQHYVpb6JoOowyg+JJ/WxMF+H/Ibks5wc5LQBA3vS/FRAo9aTRVBoFRn/EdeNIFPSm7hvTnyoWe6KouI+u+GMAp/uWMOG3rPbpbPE626thGvLxaGCDwHqC73tTvwzxMy9KUXaHhW3RIy/jR73DM3G8KQ8y34TGkXrbdbEke7o33ij3+u/Fk9Eu6Xk5Dnexi4WPxdNZrMfT8SE=
*/