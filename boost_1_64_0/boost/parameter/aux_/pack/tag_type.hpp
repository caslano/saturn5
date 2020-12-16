// Copyright David Abrahams, Daniel Wallin 2003.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PARAMETER_AUX_PACK_TAG_TYPE_HPP
#define BOOST_PARAMETER_AUX_PACK_TAG_TYPE_HPP

namespace boost { namespace parameter { namespace aux {

    // helper for tag_type<...>, below.
    template <typename T>
    struct get_tag_type0
    {
        typedef typename T::key_type type;
    };
}}} // namespace boost::parameter::aux

#include <boost/parameter/deduced.hpp>
#include <boost/parameter/config.hpp>

#if defined(BOOST_PARAMETER_CAN_USE_MP11)
#include <boost/mp11/utility.hpp>
#else
#include <boost/mpl/eval_if.hpp>
#endif

namespace boost { namespace parameter { namespace aux {

    template <typename T>
    struct get_tag_type
#if defined(BOOST_PARAMETER_CAN_USE_MP11)
      : ::boost::mp11::mp_if<
#else
      : ::boost::mpl::eval_if<
#endif
            ::boost::parameter::aux::is_deduced0<T>
          , ::boost::parameter::aux::get_tag_type0<typename T::key_type>
          , ::boost::parameter::aux::get_tag_type0<T>
        >
    {
    };
}}} // namespace boost::parameter::aux

#include <boost/parameter/required.hpp>
#include <boost/parameter/optional.hpp>

#if defined(BOOST_PARAMETER_CAN_USE_MP11)
#include <boost/mp11/integral.hpp>

namespace boost { namespace parameter { namespace aux {

    template <typename T>
    using tag_type = ::boost::mp11::mp_if<
        ::boost::mp11::mp_if<
            ::boost::parameter::aux::is_optional<T>
          , ::boost::mp11::mp_true
          , ::boost::parameter::aux::is_required<T>
        >
      , ::boost::parameter::aux::get_tag_type<T>
      , ::boost::mp11::mp_identity<T>
    >;
}}} // namespace boost::parameter::aux

#else   // !defined(BOOST_PARAMETER_CAN_USE_MP11)
#include <boost/mpl/bool.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/identity.hpp>

namespace boost { namespace parameter { namespace aux {

    template <typename T>
    struct tag_type
      : ::boost::mpl::eval_if<
            typename ::boost::mpl::if_<
                ::boost::parameter::aux::is_optional<T>
              , ::boost::mpl::true_
              , ::boost::parameter::aux::is_required<T>
            >::type
          , ::boost::parameter::aux::get_tag_type<T>
          , ::boost::mpl::identity<T>
        >
    {
    };
}}} // namespace boost::parameter::aux

#endif  // BOOST_PARAMETER_CAN_USE_MP11
#endif  // include guard


/* tag_type.hpp
1s3FvgNJNyRM+Fx+WpLWeS34gZSnnpSnI3XfjPZeRXVhNMWsSouco/oH9gP1t/5zSdr+td2V6We1rcR8L9T5pG/lmtg/2CiyPy5tFyrA2WR0JDwa7iKRYQ+ae8j7KcN7L5n+Y7qErZN4WJWn/O4h0jrw94vFD8n3i/3O2c7+B2HQ8NgRXZSf2zWZ5expdQvEmfeXoZJGvyoNrFpV6uu7U8htMG4ZgQsDb1u743u6z+OeNUbNtJ3MkLJ+kzCBk01nBAqsrsHV1vlxze0Z8Ymmvcxeq/NE5JFLHtdInFaJnm8vpp3sEL+T7FOtUzjj+27zntdmleP+94QEa1RC1HyyuR8fkrhxJs5qsQ+2G3AKdfjdWdzoRrgmwkR9v9F0fhe5uXM69z0Umsfqzqnr+u5l0vHc0+YaqklZ7wzWsRoww9c/UD/iGu4K8vUlcFQg214Y3P989ccPy3On3dxOULdwnZ0ideaNO1nrJXwNCx4M9Rnher1P7NUSBwVKrM/Q+3l9MDXop9v3g9XaB4e/T4ks8uwC6yUzFhy9RuRjj6d1b8BsxzR24pvyfRSXznW+FnzZuieumvVuXLxv+cNr/25ZK+lJWYsi2uCC4D1xCdIGo+blzfvgxVK+JNPmb5Hr/LbKM1z7xMD91tJgJ+vH4JOBxmXa/M320/YAzs3fYdUKNojzziU21mv/RdK6rkoOaVW319rHB7sFVyU8Zcar+x4RvVD+16b97E1ybUllvg2cqrIcLHF6V8m0egRyAg2s2YFz0GCcZlUJxlvpwQyre7DAXhHXyvokrsTKij/BWhHfwNqM+RFTP6GB1Svhe53TDOdVfb/f1e4gP8JEf3Mw7/xu3IJwgzT6mH+S9rvA7sL7xCXWN3p/hK+7DXqX/7DL9iOz7E6BFVan4C/BqO8Z5j2tkdTh8fYARqlY9dQ28I7UU6xvIuOk3Q5i5A1aZ/p/EzHfVW5h7GmJ/U791gHN/ObDae4YtCYF/zKm/N9Sisz3lPKZj/Xd/LZyvps731uo84jvLXOw7+97Syr2qT7fVdbH+K5y7UPmO6fYu//DfFcR+wy1H6n2W1ZH+j8q9wjfn+uF7K9G2T+Msn8bZf/Dtcs4fIKux9h9ZEgovUJgDiE0Dm9e547Dqvsxu6goSxRdTcoucBQVe8dkv/FX07DLfF9wMn5f/FoSz/tdpDBvRInbJ30uYVqrnd5Q7MGI8GM98wtxj8l3k3KvfdW6jJg7WddJn0ts/GB/eCx1kPmY0ZnnN3ci1zjCs9Yizak7iXO91QZpzMToGgNNa6xXVrj5fusy3007i393uxnPKpdzjU9YZ/i9M5FO+eZiTpVwzf3mVkgj5lyMXEOKCTPKxAu5HXhOJtzPzJKw2/iCXIUR/ywzFnwn7mcYWV0r9p1l5pblrA7xu9J3XiddwxwrYe6Sr0t8ZSw7v6N1tVHCzSJEbc+zRAkzAvl5OaPd54G3JFyGeX/o+7j7rW4v9/4O8b9O5kf2HEmddAzPu0y7PSnAZE+tqLWExNtDvE0S7yGjH/0JsS/jefls8z3iR3GL852X2SB+J5ixxJJynU7bPkHK0rcD7Yyy3OApS5CyyDpf/KyO4bma/7B3H/BRVHkAx2d2s5sEAimEAAFC6B1CR0CKhN5CLwKhJBQJISShF0MHKYJ0AaWIByd4HIKiIKCCAoICogLiCScqIGpABe5Evd++/DM7WWYhOa9f4mf8Mu3Nmzd1Z978X9ruLM+PZD1aM357xjPgJgEOX2bXVLoBDI+mmxmcdZzxnFXm31VTnu3mmVYmgHeKruHtGbaDLuOZ7rSK3p7ptpEyduU1jum3SV5ZXm2rvFaplRl3Ou1igI0KqBSeeg4=
*/