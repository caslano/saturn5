/*
Copyright 2014-2015 Glen Joseph Fernandes
(glenjofe@gmail.com)

Distributed under the Boost Software License, Version 1.0.
(http://www.boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_ALIGN_DETAIL_MAX_SIZE_HPP
#define BOOST_ALIGN_DETAIL_MAX_SIZE_HPP

#include <boost/align/detail/integral_constant.hpp>
#include <cstddef>

namespace boost {
namespace alignment {
namespace detail {

template<std::size_t A, std::size_t B>
struct max_size
    : integral_constant<std::size_t, (A > B) ? A : B> { };

} /* detail */
} /* alignment */
} /* boost */

#endif

/* max_size.hpp
9XkXNOVWacctsr6Qm4qrpCMVrycp6ryXmNt2QI5rJ2KnD2uF2+axhJwzAsea5dQKHMvxtyns/nKw1bwMuhy0mHcZ/Tl7Xnf6c8a1rfBal1Mr/pKfQ+SObWD8vC4qwss3XwdDpLmA+m9jOV/KOrRypA0fKpkaEqiR1MCxhjkpgWPtc85GSzlJ3AP/BTDuraWVWDqMhJqRCS6t5DfUxa0gz0rn9W+ibgabJSiA/iy4riytE8zs6ehapsSGCeQFjvyUiO7mMzuDNqdles+SqtsP08+fkiz6PXpTbrceNZsFP1HSNJqaA6IWSZmqNz5uZII04oM7c+HFoJL4Ma5VqJ9vSGwoW0I6unWwnqcidbNv73yb9jKIS2qr+y/9sX0eeT6BdhWpw5fWaETPNIkSvKR+gjhXL+iQKLfUs/Rlh+362WffqfWzOvzwQ2da9F30LmiXY1GtL8/4XgLZdpXra423oHCsvtQORk2JdSGmyEI7fsw4X46yCzv3wkDZaWl2YccubPHoK7zNpbfcDpAKTp7TPT2rtjuMJh8cdoYa77dGj4CBX+9T0/0A9aKTRDDMLuzQxQec1HuAZT0toZ49vhxpXBFfPqyz32bdH9hzautu316+TXspB+3w7Ofdp9ker33jxhH05YodTF/SsdHbCHGRllsyhckhT9JfnTpxsaMvzzeyIvUn26ndzmj3NmmyBzcp9uDDau6vHpGJ1t5Fjaz0LJvb68DjlPZ4cvUy/bTo2ZKGFddvbwOhL5dJVAU7EpPoVCQm2VmOxPxjv93SO3ed2tJXSV/cDa1LMWS/PX1ZdWE16Et4vuc2sKjyUMC9a+qrW3zk/Hp7J+LJhXzR0Y0ULFpLmibBtjfPPfWlr4LendsgTO/yLPSuDbBM0bsxY5EcJnlP0ou9QfWS9cu//NVUr5r0r36Y/uUZ9O8Z134L/RtNPVQk8AnqHqgggoYlnCYVDH8qoPa3iUangCRQL8VtsGy4fg8OIzBUsGaKREY24te31jB7DQxek1X4JE9t4d+pz/pjv/6wVPqv0qks8txUDDZ9Ah1I8GV/En+IzX0/rGNir/8RUb6blK9tlE+oGb38Rnf58u3p0olYBr+o8pdW0f6EiPKxUl4zyj/hil6+W0T5nfu5/4/jAJXx/7GK8UeUf0XKtzPKJ7iqGH+98uU/3cDlY4zyl1bR/oSI8kOl/CIcSzJ+oE/V9KtzPSv9WsXkcRkTS6uSwm7wM9Wjh6G65ehhJfUd/wfqq0r/u2758f3cgte3YJ1a33oXRJ8ff0T5+VLeZ5TvmxC9/BUR5e/7jud39nZVfvT50csfqVO+/B+l/KNG+a/jo5efFVF+ZTPu/3UHjfFX0b4/ovzTUv7kd8b446sYf0T5K2V/fWqUH92iivHXLl/+6NlcfqhR/uu46uDn9NpWfLrhc3t8are3uvjZs1x9P621r+/2Q9Wtz12uvu8xJrv6XttT3foW1LLW93ol9c05WPX+8dcqP/9Zqxn/1m9S87/6vCrWP6J8HSk/zih/QWx11u9gTet41u6xn+/Hd1d3fiaXq294JfVN+q669XUuV19sJfXt3lXd+kIua30f7q6E/h2obn3Ty9V3diX1tat2/3q6qkPvbz9QNX41lpo4YuznQIyrQC9FPoYHDDv9pxrl4WsY8KuctvCzIuA77FWIt6a5LXx+BPwZBvzf7OvvFgE/8WsF/5B9/edHwPcz4Ova138koTz8/fFqvG77+pdEwKcZ8O+JMrD9eo5JsK5n3S3267mm2vhxfbn6PvnSvr6/7K9ufQfjraE2/My0Hou0a8bdBQPeQgiBl6eDZxuv2Pt/oVfsKt9Cy71/lmsvPlp7f1HtZYeCqr0=
*/