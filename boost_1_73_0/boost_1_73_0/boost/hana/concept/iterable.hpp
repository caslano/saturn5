/*!
@file
Defines `boost::hana::Iterable`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_CONCEPT_ITERABLE_HPP
#define BOOST_HANA_CONCEPT_ITERABLE_HPP

#include <boost/hana/fwd/concept/iterable.hpp>

#include <boost/hana/at.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/default.hpp>
#include <boost/hana/core/tag_of.hpp>
#include <boost/hana/detail/integral_constant.hpp>
#include <boost/hana/drop_front.hpp>
#include <boost/hana/is_empty.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    template <typename It>
    struct Iterable
        : hana::integral_constant<bool,
            !is_default<at_impl<typename tag_of<It>::type>>::value &&
            !is_default<drop_front_impl<typename tag_of<It>::type>>::value &&
            !is_default<is_empty_impl<typename tag_of<It>::type>>::value
        >
    { };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_CONCEPT_ITERABLE_HPP

/* iterable.hpp
DLsbTlzrJhTMIqGReZZHN7V9pW+8KadXIpX2LLzoUjkYMyDNHcR2+l93kgYXkN4ZNHomiY9gFqPtrxK17uC6XEoJyb9rB4vAqSDAx9b+KtH10B8fGvCLdkxXjiRrkgaZo5lyihwMLJVG2auc5QRgIJEqJBdmYjlPeX10gEkp3s+FgKVcC3nJOAHvuQDfWZ6nN6q24RJY6TSBuW0MQshhyw6prR3P803nhhmqEaFL0T59atrCX630ZgNfoktBT6UuDWywHatPO3VJX6VhxRUEo/ChrN860Wkxf6UcfQNLEG90UAZqwjnpO+ir0K1hli0CNK8fyEWxXF701kWavul2dCFdZYtlvodIAewKq1mUfZjwTOcj1sGMVTcxWdLCt7VoICWyTzqySJP8clkaqM6wizKVnPebMhEyJ9W3halTI7wqJGjenri3APXZo5JfKUC6rPaIAtTXXB5bgA2MlafIdmHrPpveZKCSMbSqq6Qosw0Njt4UZbKYX0GWaC0ZI2aUJOu+0U3NoA7SFMqQw7dCKo1FAE34nj72UpAMQzOiEV106dfv9hDE6Kkjx+Lo3GPzMFt5azzBCCLvUtBBBZ3QlVH5mVD4pbiQucC0ha6aYmzgtAo80QWb1PaoHQU3zsjCmM7HLnmGI3Xbb23b
*/