// Copyright David Abrahams, Daniel Wallin 2003.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PARAMETER_AUX_PACK_TAG_DEDUCED_HPP
#define BOOST_PARAMETER_AUX_PACK_TAG_DEDUCED_HPP

#include <boost/parameter/aux_/set.hpp>
#include <boost/parameter/aux_/pack/tag_type.hpp>
#include <boost/parameter/config.hpp>

#if defined(BOOST_PARAMETER_CAN_USE_MP11)
#include <boost/mp11/list.hpp>
#include <boost/mp11/utility.hpp>
#else
#include <boost/mpl/pair.hpp>
#include <boost/mpl/apply_wrap.hpp>
#endif

namespace boost { namespace parameter { namespace aux {

    // Tags a deduced argument Arg with the keyword tag of Spec using TagFn.
    // Returns the tagged argument and the mpl::set<> UsedArgs with the
    // tag of Spec inserted.
    template <typename UsedArgs, typename Spec, typename Arg, typename TagFn>
    struct tag_deduced
    {
#if defined(BOOST_PARAMETER_CAN_USE_MP11)
        using type = ::boost::mp11::mp_list<
            ::boost::mp11::mp_apply_q<
                TagFn
              , ::boost::mp11::mp_list<
                    typename ::boost::parameter::aux::tag_type<Spec>::type
                  , Arg
                >
            >
#else
        typedef ::boost::mpl::pair<
            typename ::boost::mpl::apply_wrap2<
                TagFn
              , typename ::boost::parameter::aux::tag_type<Spec>::type
              , Arg
            >::type
#endif  // BOOST_PARAMETER_CAN_USE_MP11
          , typename ::boost::parameter::aux::insert_<
                UsedArgs
              , typename ::boost::parameter::aux::tag_type<Spec>::type
            >::type
#if defined(BOOST_PARAMETER_CAN_USE_MP11)
        >;
#else
        > type;
#endif
    };
}}} // namespace boost::parameter::aux

#endif  // include guard


/* tag_deduced.hpp
dIMCnuvd8OT1hmBcIx45HYcprtVb1qu2o6TOi/MsGH1/dZXV8fdg8/bOpWfk+7dUL8bQ55OERO8RE2k3qJs13aHdkt393bQ0gAAiZ/4hN3HprrfaePro+jidOIsv9CX8HfBr0NZx9fFWX9i/5EHhRc0KCjD+ErsQ7M/ljO3MXEfgjXmutH0RU0yEF2J9zGArWj7sz+SJBsM4QzlDP0M7wyRX+Qz7EvCXD6xEyNOkWwhGzM/FyO/17ETK9DEJRPI0j+1hmLFx5h+FjUNj1OMdcAUsp21hWxNxxQS8Plv5OaSf7a3u173IOXaUgH2fHh9yPCH1Y/g2EBkPorIcJer9Yoeix0AyXvuZI+xMzVFyEVL5Yo6HbuNpTpayjrUzebx8ygisuY6dUNPBxlhyehs8LxhHGN5AdkDE5uLQ93dNeiAPGGZvROIHdRg6P8gzJVzZROYi4ZmajAHrEJdQzqA0+VNnQE5pjmtnWsIUiTw9Vi0ZRxVEhoEbG7UMl8QTK/tuoLrLvXpi0a402/iy8fP5hxT/DbJvPnkpjdFWH21vdUxXEzKIFfrC+r+KQcq5sj8JmAlj1EZkWt1/pXVQJfmcM+vIvNf3NvKDlnBK406qiV9MjWEDu0P0+/6PgI976UqZC6RyuB50p0Hpkzj24hz0pY0E+J58BGkY8tzo4lsq+bST06A2Wmdpr5H3yNQzT6BfeQdtI+1ku42ddL7w
*/