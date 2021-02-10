//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_EXPERIMENTAL_SORT_BY_TRANSFORM_HPP
#define BOOST_COMPUTE_EXPERIMENTAL_SORT_BY_TRANSFORM_HPP

#include <iterator>

#include <boost/compute/algorithm/sort_by_key.hpp>
#include <boost/compute/algorithm/transform.hpp>
#include <boost/compute/container/vector.hpp>
#include <boost/compute/detail/iterator_range_size.hpp>
#include <boost/compute/type_traits/result_of.hpp>

namespace boost {
namespace compute {
namespace experimental {

template<class Iterator, class Transform, class Compare>
inline void sort_by_transform(Iterator first,
                              Iterator last,
                              Transform transform,
                              Compare compare,
                              command_queue &queue = system::default_queue())
{
    typedef typename std::iterator_traits<Iterator>::value_type value_type;
    typedef typename boost::compute::result_of<Transform(value_type)>::type key_type;

    size_t n = detail::iterator_range_size(first, last);
    if(n < 2){
        return;
    }

    const context &context = queue.get_context();

    ::boost::compute::vector<key_type> keys(n, context);

    ::boost::compute::transform(
        first,
        last,
        keys.begin(),
        transform,
        queue
    );

    ::boost::compute::sort_by_key(
        keys.begin(),
        keys.end(),
        first,
        compare,
        queue
    );
}

} // end experimental namespace
} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_EXPERIMENTAL_SORT_BY_TRANSFORM_HPP

/* sort_by_transform.hpp
K7YlfNkgXFCE9NDx/CYIT33yJkr1F2e1FfBHP1yBaUsnvD96HXrPanzIUUHSBOGxO/hQosDFRbM6sg2UsmdCzgoI3CBVcQFh3Evtgt4IbKUUe1kDPDh7GoZVR4vSVZTEppeIdKYr85LfYL+XhdqmLL7fs8VhOctVg76UGKZpCUWjITEYezLp+bARksQq+IqdokY6PI4A4CXQRYHTgAdt9UBDyRobTj3UnKXqBuAmSjYplFaNTqeKqckUvzrU5GsJLpC5GSeBZEtTJxwyDuhGCNjQJshX9IMa7szw1dFxWZ0oZgAOp6em1e8BQJ3h5wHDJ7xl2kcavzBQhJ18SQgwd+r7Yk1wI3W3MW+EZbpcUsahaDTUjczCys6puxJsV4rdRneAUJy5xMVNRZk0C3kBnxD05S8nJ1XBTTQRTksw1Sf6atpZdeVIhkMGEpbrRIB4mPJVc6ZI6SKIDhNEJwp1I3olqbKg6WtG/Udd9V7HZabNfafugOCDkIs+JgbL5ooob/An9CupalDNYOuOPN9zx+3HCpDurEQlgwwEbc+4h+mgzRBKijwMp6TJJcHAg+0Klb2tltAtMSrFxO+Anqpz1OiBNeS797rPev+E1fZ69277IyYgPuLOib5y5ikTDmawv1eQcxDQkwe1rL7j
*/