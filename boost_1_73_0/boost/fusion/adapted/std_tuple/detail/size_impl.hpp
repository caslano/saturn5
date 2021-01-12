/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_SIZE_IMPL_09242011_1744)
#define BOOST_FUSION_SIZE_IMPL_09242011_1744

#include <boost/fusion/support/config.hpp>
#include <tuple>
#include <boost/mpl/int.hpp>
#include <boost/type_traits/remove_const.hpp>

namespace boost { namespace fusion
{
    struct std_tuple_tag;

    namespace extension
    {
        template<typename T>
        struct size_impl;

        template <>
        struct size_impl<std_tuple_tag>
        {
            template <typename Sequence>
            struct apply :
                mpl::int_<std::tuple_size<
                    typename remove_const<Sequence>::type>::value
                >
            {};
        };
    }
}}

#endif

/* size_impl.hpp
toZVYXt93hUmw14wDQ6G9bVdbQCzYCM4BTaG02ETeANsCZfBNvAp2Ba+CtvB3fBS+AVsD7+CHeCvsCMs56H/AhvCzrAZ7AEvgT1hJ9gHDoB94QjYD06E/eE8OABeAy+Hy+AouBIOg3+G6fB5OAbuhBnwIzgBfgYnwZNwMjwLp0Cvl/44rACnw8YwF14Ma8JOsBbsDvPhSFgAs2AhnAaLoKzHeHRvtO753gD7O78133SLJj/C
*/