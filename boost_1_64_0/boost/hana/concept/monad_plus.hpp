/*!
@file
Defines `boost::hana::MonadPlus`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_CONCEPT_MONAD_PLUS_HPP
#define BOOST_HANA_CONCEPT_MONAD_PLUS_HPP

#include <boost/hana/fwd/concept/monad_plus.hpp>

#include <boost/hana/concat.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/default.hpp>
#include <boost/hana/core/tag_of.hpp>
#include <boost/hana/detail/integral_constant.hpp>
#include <boost/hana/empty.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    template <typename M>
    struct MonadPlus
        : hana::integral_constant<bool,
            !is_default<concat_impl<typename tag_of<M>::type>>::value &&
            !is_default<empty_impl<typename tag_of<M>::type>>::value
        >
    { };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_CONCEPT_MONAD_PLUS_HPP

/* monad_plus.hpp
sEJ8JvfwuSc1g+Ujm2K3Umbe0MN4b8tvd94s9YTx/UynrOygzBfGexvvO0xmIgDG+ZmUy5UotYbxuVsoboPMYDDMkp/z0OJwZSGw/NyHgpc7KQvX4uwmvzonPYLxnIXXqBsjte4hf78/2745WwdIzbT7nfl8NkFq1tP4HdBw1ynpkR/MgWzA5lHnJXcYX3NQ86jnkh/Mkue6zrRKykK1a5rPDP4o+cF45jdaHygkuwlzInt6tMYkmUEY9/at548EqYuW37IH85JlBrW4Dc+GVpQZ7MkzCLMsVVTqCbMmu1dydLScZ72M33EZvTfMUeYP47joF59clQXBuH/Pv2RKfjEwrmfMm+tOymJh5cgSvxnku+A6jGe3ZkezM8rSYHXpfkFDbsre+vY2fs4Dv3cXkRxgNmQWV44Ol5mA2ZLtPhRTV/ZBs9XtM8bITMD4/RDQL0jO6zAY57fj2PUUZWthOSnu8b7lO2QmYHwOnjqSLnXZrd0vz9Bl8pyJMP5+Ofyxmbz/kmHch8xeuS1kXjTbZjb2l9QaxnP2eeuU5srSYTzXOQ44TldmEmrcvzpT5rWROYMV5r2d2UfOED8Y71Ho59/y7giAOZEtsq47Q3oE41qXGPUrVdlM7VmSStZsLfMJ43Opz5gemcqSYMXIhi5u0lPZJxjX5Wjlre0k9z74NR7FpQZ1/FfmE8bndS2/qo8kP5g92dJfqQMlPy0un3XaSJkzGD9naOVVUbJjMO7thpkBETJnMBey/WeO3pLcYbwrVj2qTJV5gTmT+Xn7ypxlwngGL6z5WFP63tf4/ec9f7rskQeMZ35uC9OCMhMwb7I5a45Jj1rBuA9zy87YriwExvMSt++EvIvDYQayCcNCSyiLhBUga9D14iepJ4zzG/4rvaOyeJgD2UqP97uknjBrsoNtEi9IPWFcz0lxSbJ/mdpz7q115pzUs5/xN1Hr5PpyPz+YLdm7sau+yZzBOIcypiM9lQXB+DlvfnWXfQ+BeZGtMyT0kZpp96tQukOi7BjMjax42xHS2wTtWUJmeAyVmsHced/NWpRWlg7jurRacEvmLBNWkizesDdY9q+/8VznW7jITZk/jPf2n7qzlkjuWty9m/dnyv7BSpDl8rF/JfOixdWpfWWBzAusDOfX9Y2psjQY18W53MbLyt7BCpKZPQldpswwwHiP7CqukrPHA5aXzH2c+0mZFxjfL2ebXi1lXmC8f0+O2n1XFqrFmfrXKi47BuP+vXLr+Oe7AGbLNXMZbqMsDsbvB6+Jl+KVJcO47wu9vK2lZjAXskrHyjVUZjLQuC5/BSV+lprBypJFNkivpyxQiyvddpSJsmAY389kUO7ckjuM83s5fuh82RVYZbIF9R5JDolaXOma1VZJ7pot7VjSXHKHeZJdTR+0W86JQcbnbl+v6BwyEzDu7eIZ4fUldxjP7qMbmYcldxifkX55H7jLPmhx36MfyjdKhBbXeqhXPpkJLa7b0jn3ZCa0uOAHu3pLzWDWZMuuhXlJzWDOZLU6tZEz8h2M35v5Oo4JVuYWZvx9dnt05Q9SMxjXuvC0k05SM5iBrHi1l3WkZjAPsv/srx8m8xJmvJuX11/dJPOi3a94yxmzlcVr9ytYoLRYona/8tNmPpF5gbmSfegdM0V2ZbDxvDQfM2CyMieYHZ9Zkx49UOYHK0T2e1u6o7IgGNe6kumP8jITsCJk1z5W/y19h3HuP2t8DpHewkrwu7hmlUOSwxDjX8uceu32TJ4T5k5mUaVoP3lOGOdeZ+oJeR+Fwjj3a7/Mb0gOMK71q7fPeimL1eJW3o+Vcz4BxjWrXHJDf2Up2nMOtw1aoSwT5kY21MfFW3o01Li3fo8=
*/