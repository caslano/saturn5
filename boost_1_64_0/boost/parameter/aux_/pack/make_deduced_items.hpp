// Copyright David Abrahams, Daniel Wallin 2003.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PARAMETER_AUX_PACK_MAKE_DEDUCED_ITEMS_HPP
#define BOOST_PARAMETER_AUX_PACK_MAKE_DEDUCED_ITEMS_HPP

#include <boost/parameter/aux_/void.hpp>
#include <boost/parameter/aux_/pack/deduced_item.hpp>
#include <boost/parameter/deduced.hpp>
#include <boost/parameter/config.hpp>

#if defined(BOOST_PARAMETER_CAN_USE_MP11)
#include <boost/mp11/utility.hpp>
#include <type_traits>
#else
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/type_traits/is_same.hpp>
#endif

namespace boost { namespace parameter { namespace aux {

    template <typename Spec, typename Tail>
#if defined(BOOST_PARAMETER_CAN_USE_MP11)
    using make_deduced_items = ::boost::mp11::mp_if<
        ::std::is_same<Spec,::boost::parameter::void_>
      , ::boost::mp11::mp_identity< ::boost::parameter::void_>
      , ::boost::mp11::mp_if<
            ::boost::parameter::aux::is_deduced<Spec>
          , ::boost::parameter::aux::make_deduced_item<Spec,Tail>
          , Tail
        >
    >;
#else
    struct make_deduced_items
      : ::boost::mpl::eval_if<
            ::boost::is_same<Spec,::boost::parameter::void_>
          , ::boost::mpl::identity< ::boost::parameter::void_>
          , ::boost::mpl::eval_if<
                ::boost::parameter::aux::is_deduced<Spec>
              , ::boost::parameter::aux::make_deduced_item<Spec,Tail>
              , Tail
            >
        >
    {
    };
#endif  // BOOST_PARAMETER_CAN_USE_MP11
}}} // namespace boost::parameter::aux

#endif  // include guard


/* make_deduced_items.hpp
4PHOM7BqTy/Oy6GNxxiPfpR4s+3QWm9Nh9R7WXu87Qv3aH3O0neZPudX8Z8u6SR60jnH+tCko+4R/aNt7n23jr6TMIts32eh6HYue2WypDB+bUzDR6+HNv1pQk3Ri8y6vr2EwQ1btxTH7WRPeysx7e0uCZ9g1l/kiL03LY61jkgqVdeLjxT3FvZKOS/ItNvi0ZTUe48dK+Faad60R7H30fTDZRnEO2c8b53BMmVM1XXyfYmH3X6D/FS2Jj/Ea8rfUsKlm3WNXcX+N/vD6HhaJ+F4GRIu2dxns8Xe1OwRaCL2QnsP6dTnHop3+g8dX8ImX++nxAOc7cO1xRxnUiPmdrg4z70VNZZE6U437UTur++kvDwvqu6aw1OM3Z1HViXfIhH97jE2vM65Vtn7TYchHVtCbduVIZQ46f7vabWixyVJzTwz+I31jrWVxOsXkrmO9dO5ia7U8cqM7QeYxx1Wy8hcxzAds/UawvPt6kbZIse1pceFEnxc79O1mA7IaV4MOWXlTKBrtCL2a8bcc6uySTftUyJnjSjMHlkc9VwVJTu5F6PWUZg+62FJd370c5QZe17W+qpCzYfHtTvFbZnVGtce3JOtkDvtkdLSszhG5Z8Do+sgMeY4ou0+NaoOTNvVcym8z0xRMiA81xpdP247LuwVymyAZtofM5C2Pi3VUz8lWXSO43h7yR/TMXK8MDKZIeFP482rs29dkZ5nLY72tx3d/u5W8e9wUHNB4WvZptfSQCPUx9zvfIt0r6V43Hgzh8265QN/j3b6ALu26gutG6lvfWpvf33rmbUrpm/dCf9n9K0Tv4y+9S8CsfVo+evLqrheKX/9WrH1Zc0RfVk/n7pj8exvB1182bpZZ7QfetzAiuuP8teLFVu/k7/erdh6n/z1X8XW0+WvJyqWHqqK6+Py13NVcX1ZFdV75q/HLLYeMH+9XhXXX19R/VqOXvVcj1715bBuILR+rTXMdu4Hz99fev4eQ3j+pucK7W9L4e9+lOt592/2prl/f0+49kY3BXWPmYcJYlpoGZZVs6Y5XA5rwPtgWHfzPI0XjyFNr+5m0nfDLS1nuFXlDLfRE651VDiu3YTbvJ9w2Z5wpeUMt7sc4dqH91WDRj7y7Fk9JM9jYUN4HPweFmHaa7xTNF51T1uYnxSKdyOsDe+GTeEK2ByuhC3gEthR3Turexd4CzxJ3fuJu16Xrft0dc/xPNgUk2brvFWyNS0ZNq4R0o3WDB4Dm8PjYRN4CsyEZ8BWcDA8DF4AD4eTYRs4A7aD98D2cDvsDn+DPeDv8Gho28gFxsFesDrsAxvCk2E7OBB2hmfDU+HhcDw8B5bAIfBKeC68Cp4Pl8BhcC3MhhvgcPgOHAE/h6Pht3AU/JfaHTktDe9LhFVUTrUwCywdp6tTbtgQVoeNYGPYGHaFTeAgmAkLYXN4MWwBZ8PD4LXwcHgfbAOfhu3gZngUfAd2hntgF/g77AoTbOSo7WhVvO57072J8+BqzDJVqNBX29/JsDk8DXaA12k7mQe7wjNx7wv7wzPVf6D6nw0H4p6t7nnqPgL+DfcidS9R9wlwKO6XwgvgInghXKz+t8Nhet3Z8AE4HD4Gc+ATMA9+BEfCX2A+pB4kfiIcjT0dFsJmcAVsDZ1ytNVw7eB43HvAYngcnAgHwklwsIYbAi/HPgxOg3nwCjgKXgmL4Qw4Cc6EV8JZcDacDRfCv8PFcA58WtN9Bt6A/VW4EO6EN8M/4K0wOcC6Z1gXLoXd4R2wL7wTngIXwyHwdngBvBsWwnvgRfB+OAGugDOhc/1/h/Pg1fAhp3zqfrO63wJX4/6guj+s7qvhuuqUGz4DX1T/19T/dfgk7p+q+2c=
*/