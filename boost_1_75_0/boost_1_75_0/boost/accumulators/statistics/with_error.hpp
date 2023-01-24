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
kjeOIdqzoUUaTq4VwNMOFkHikKUH8PKZ4EYbwBIVT9GU68Yo49fgwnA6jiWmhzeZYRlPGvzseSsMpB6aUg+W1ENXNJq2yJJpgIwARfxBDj4mgbdQ+0jXG0rXG0jXm9EvOWji7TN7nrsJY/YsKUzORC308j+Sgd8UW6ENi6uvuc3Sl5VA9MihuvM0WZy+qzRFIz/SKy2HFThMdNgQL9YuY3frsqsPXnY157Ytu3677vKHSqBIDVwktYyfa493I1ZchQjSOuTTIl1Am1P+xo3BpKAmNwE3/BpIbrB4tmazebYms0W6JBcZf2MGFjEor73tqpYVd7XlJWsbNN5EmTpdAqnMsGSxTKUcK+42k/5Sjuoojkn/jeYgU55maABMoLFQt4WCVFMoqY4PZYhCPKAZY8dwvKx9itFeGqD1k1gtBUt5pN9vszLGwYvFm6XJm605chbDS4UkLUqaQpnn8aPy9k28Bfh73TobknYvb2y2wu/8NAVNqA8Yp8vz1ORtZWAsHYI0N3K3HVAmOFYO9rzVLKndAeUFCyG3hoBjtmkQpJojOk5KWRliHeaIKkgPA7LxlA8EjNOEDAxIhf1DDojvhGEkxYYkSmI9XOIq6RxROJVpARncKpzfYcvcFYXbsQzGTRTGc0QH9NWAJ8oaAuZ+/EIn+bgH/hgG1z/+AIRz3Bzsg1azLLMtEyzTLGstpdKUVnqmbXLEN9kzRPM6
*/