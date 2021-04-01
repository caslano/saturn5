///////////////////////////////////////////////////////////////////////////////
// with_error.hpp
//
//  Copyright 2005 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_ACCUMULATORS_STATISTICS_WITH_ERROR_HPP_EAN_01_11_2005
#define BOOST_ACCUMULATORS_STATISTICS_WITH_ERROR_HPP_EAN_01_11_2005

#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/transform_view.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/accumulators/statistics_fwd.hpp>
#include <boost/accumulators/statistics/error_of.hpp>

namespace boost { namespace accumulators
{

namespace detail
{
    template<typename Feature>
    struct error_of_tag
    {
        typedef tag::error_of<Feature> type;
    };
}

///////////////////////////////////////////////////////////////////////////////
// with_error
//
template<BOOST_PP_ENUM_PARAMS(BOOST_ACCUMULATORS_MAX_FEATURES, typename Feature)>
struct with_error
  : mpl::transform_view<
        mpl::vector<BOOST_PP_ENUM_PARAMS(BOOST_ACCUMULATORS_MAX_FEATURES, Feature)>
      , detail::error_of_tag<mpl::_1>
    >
{
};

}} // namespace boost::accumulators

#endif

/* with_error.hpp
5ghxs/Gtaox8DZhepbCKbeXiapPByCIe/S4eftZ/RpGQrfTYJ4gF7jEy0zCT/DmLZeazdVyn+ohPdQVzeYTgC3mCKzFqRYzyg3d/s0F8KKvHCWJuQlcdjx0KTafUXDNtCsyWl1KILp0P42XiupFVxL3UPcPCDKR2ixZynEsnvQal+Bg61Hqh1wUs4EyLuWy0zQ+NoxAAJTCk3VXN+WXMIQhrBIUwJn8Fsh1nLtdPDbdca3LL51gud0r0v9Jfrt1x2N9vtQ6wDi559m8skQUIdPKwl1KF9mly5HmiHN20rRSSOFKPbloMLtYLNg32qlJhFYF3kgJn+fz2heQQexBcvbHtIo7PZw12XLl4BjQTXFGr5uzHHO6vFuIchR39i3N/Vp2aQDfrgAZ2g5SQG2z2zUzrr+vEZz5PaGy6giTCVw3NfSLlv5Go57/yCLFl5p43oGfWiILHqAELVmJCoWhoIFIkLcPGy27Y6xLKh3YOUrKdwF7b+mqEltUICwAQRYU3tM1ULje3yuBnqhBZU9mt9krC+QLwsdOT4jwpaGoi+cBktGHpN/NQgEGpjw==
*/