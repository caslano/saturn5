/*!
@file
Defines `boost::hana::Constant`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_CONCEPT_CONSTANT_HPP
#define BOOST_HANA_CONCEPT_CONSTANT_HPP

#include <boost/hana/fwd/concept/constant.hpp>

#include <boost/hana/config.hpp>
#include <boost/hana/core/default.hpp>
#include <boost/hana/core/tag_of.hpp>
#include <boost/hana/detail/integral_constant.hpp>
#include <boost/hana/value.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    template <typename C>
    struct Constant
        : hana::integral_constant<bool,
            !is_default<value_impl<typename tag_of<C>::type>>::value
        >
    { };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_CONCEPT_CONSTANT_HPP

/* constant.hpp
gXQjXrdFQPXfzOM0BOMtSoV7BRDJeifXd7jFXMea5d+7rhEgzzQxwA5b8pEwC05O6Tc/9gkDknpMMeyxkNYjps3AVfOfBQTMgDNSd9WktUobLiIX5Obncm8rHmnuLkZkQuylLlfgAP3SuvCPx1mQr6tlnAJkzjnU6bFanvzNtJfZqtMcSDrG1fT37jSWAH/ERMRePE4VEAtYeLLfO163xRCq35IDtNkG3unFotrxjQrwW+6ob4mAlJUVDjjrx8GqgObMelzzbzMuLmZRww3FWg+Llre6ORXHznt1YVLJqGCuzCrt97z/nVSfUel92K3oNGJa4nrKNEsdS2PI2J54rx7Nhjev//cznAJz7gBc5Ln9AyOdbEhvf/28Yia/Q3FCH0xlzg/7QBD14fWBRWj1vIbWL7LI2VYwM16g3ed90vGOQ34e2BLs7G7Yga9eatFq2wNT8ek4tp9xjsYP4zo4L/XBHuOoj2MNeOJppdEWo1NXuXZnR0K6YSWLkfaTcx677/od4DATm3yr86ryCuLCorVOGy+G2ggBsroIEDkBuEem5KLcdHZwyq/P/w==
*/