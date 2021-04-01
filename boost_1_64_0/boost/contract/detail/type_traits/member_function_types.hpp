
#ifndef BOOST_CONTRACT_DETAIL_MEMBER_FUNCTION_TYPES_HPP_
#define BOOST_CONTRACT_DETAIL_MEMBER_FUNCTION_TYPES_HPP_

// Copyright (C) 2008-2018 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0 (see accompanying
// file LICENSE_1_0.txt or a copy at http://www.boost.org/LICENSE_1_0.txt).
// See: http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

#include <boost/contract/detail/none.hpp>
#include <boost/function_types/parameter_types.hpp>
#include <boost/function_types/result_type.hpp>
#include <boost/function_types/property_tags.hpp>
#include <boost/type_traits/is_const.hpp>
#include <boost/type_traits/is_volatile.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/mpl/pop_front.hpp>
#include <boost/mpl/push_back.hpp>
#include <boost/mpl/back.hpp>
#include <boost/mpl/and.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/identity.hpp>

namespace boost {
    namespace contract {
        class virtual_;
    }
}

namespace boost { namespace contract { namespace detail {

template<class C, typename F>
struct member_function_types {
    typedef typename boost::function_types::result_type<F>::type result_type;

    // Never include leading class type.
    typedef typename boost::mpl::pop_front<typename boost::function_types::
            parameter_types<F>::type>::type argument_types;

    // Always include trailing virtual_* type.
    typedef typename boost::mpl::if_<boost::is_same<typename boost::
            mpl::back<argument_types>::type, boost::contract::virtual_*>,
        boost::mpl::identity<argument_types>
    ,
        boost::mpl::push_back<argument_types, boost::contract::virtual_*>
    >::type::type virtual_argument_types;

    typedef typename boost::mpl::if_<boost::mpl::and_<boost::is_const<C>,
            boost::is_volatile<C> >,
        boost::function_types::cv_qualified
    , typename boost::mpl::if_<boost::is_const<C>,
        boost::function_types::const_non_volatile
    , typename boost::mpl::if_<boost::is_volatile<C>,
        boost::function_types::volatile_non_const
    ,
        boost::function_types::null_tag
    >::type>::type>::type property_tag;
};

// Also handles none type.
template<class C>
struct member_function_types<C, none> {
    typedef none result_type;
    typedef none argument_types;
    typedef none virtual_argument_types;
    typedef none property_tag;
};

} } } // namespace

#endif // #include guard


/* member_function_types.hpp
c55FTFyvJbpyuq9zYWXc1Kd3yHpjkQXWxr87ru/bt+RQbsRjgXVorE0aGkzp0lep7jPaPgLtJUpQX6S/YpIABRX+3ktfkOP9Xu14zDMlZprTOKIbM/xNd/6vyS85u2mlfIqpF3Uy4BUC5p26EE9bu+FX5ONQ51hmfqdqNWls9wnzaiizHw7kIozlrVFsFeB5bDyUlCVOE9buC75B/x0t1BFPCttCjsUzBPUbx4zf18Sakw3A84KkicxOkmTpPiqYqTvQH6BgPVBVpU41JIhjBalLbL7JYRPbmfis/MwkA5VcpQgITEiovfhIQrF/Pt98GguYJwZ3o+NRZVIfg5q2BYbBYgs50kMThhs6/Iy12k/6Y/mwoJP2UOiQHbNcO2or/NP9aaRwN1ZXnIUN7zNFLV+ryIyHT/UbPQTkXIp9vUwvb1qnKAAn0Fy0NGpq9OoaAA4slxzsO2Xiu3JjPJ3Yvf7cloMhEY3zzFkGSvnwvYIDSMhiO80QAoKAJU2rzAi1HtphShfgDM+ns7PQffQcKXAmGWIGM215Uko1TOxhLlbcHmI4iS0tE1FqBQ==
*/