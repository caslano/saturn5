// Copyright David Abrahams, Daniel Wallin 2003.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PARAMETER_AUX_PACK_ITEM_HPP
#define BOOST_PARAMETER_AUX_PACK_ITEM_HPP

#include <boost/parameter/aux_/void.hpp>
#include <boost/config.hpp>
#include <boost/config/workaround.hpp>

#if BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x564))
#include <boost/type_traits/is_const.hpp>
#include <boost/type_traits/remove_reference.hpp>
#endif

namespace boost { namespace parameter { namespace aux {

    // A parameter spec item typelist.
    template <
        typename Spec
      , typename Arg
      , typename Tail = ::boost::parameter::void_
    >
    struct item
    {
        typedef Spec spec;
#if BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x564))
        typedef ::boost::is_const<
            typename ::boost::remove_reference<Arg>::type
        > is_arg_const;
#endif
        typedef Arg arg;
        typedef Tail tail;
    };

    template <typename Spec, typename Arg, typename Tail>
    struct make_item
    {
        typedef boost::parameter::aux
        ::item<Spec,Arg,typename Tail::type> type;
    };
}}} // namespace boost::parameter::aux

#endif  // include guard


/* item.hpp
sW/IPABZ3JHapPfwEyhvYqhbO+3nvXV6lbIgqNqp1NspZP2YloAhNQ2Zv9D0t0281CfjuxBZF6JhbAKdP/ourWn6gBUp21fJu5Ico9n//phGv9DAf9YIVQHrqmOucGrP4/erQYYJBljH9mbUwAhcydw88dmuCVO1f+oNvqUX7ECvFuXUcqlnJm6V1hhZDhaDQ0IAzMNNv+ffeKoEiAoKRQRlWO7xNgXtiLJSRLItgQ4xMO+0A0GvNTQuYYyJ0S3xwmILgwQXCnimPERdRWmdlSOA/YCQat7IuqjD04OKbWJD/GdC2l1xi2YCtsCEwjn1GdYpqeQm+R3dvaXQbRKH3xY6c76F+7r/JlVQV7oupkdC2YAvp5oi12XaNsDEtHcjXQS4bdVksDA6lK8Ntz40/Eo8KreU+hBLLLeGD53E0Gj+26imbF9sCFPpZu669IMQK63pRl5zxuDBA2NT/i/5zUt/LXwAKKc216gIE+54i+VKL+E1TKMM6I5RHjofCYvXoOscxKlA6BAczDmWaka+vZpvehtR5HdCSCtPPxvmK9+7tkR1iH6pxV0yZQ==
*/