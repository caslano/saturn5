
#ifndef BOOST_CONTRACT_DETAIL_MIRROR_HPP_
#define BOOST_CONTRACT_DETAIL_MIRROR_HPP_

// Copyright (C) 2008-2018 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0 (see accompanying
// file LICENSE_1_0.txt or a copy at http://www.boost.org/LICENSE_1_0.txt).
// See: http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

#include <boost/contract/detail/name.hpp>
#include <boost/function_types/member_function_pointer.hpp>
#include <boost/function_types/function_pointer.hpp>
#include <boost/function_types/property_tags.hpp>
#include <boost/mpl/push_front.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/tuple/rem.hpp>
#include <boost/preprocessor/tuple/eat.hpp>

// NOTE: Unfortunately, it is not possible to use Boost.TTI because it not
// always works on MSVC (e.g., when the mirror meta-function is invoked
// multiple times, MSVC 2010 gives an internal compiler error). This is a
// simpler mirror implementation that seems to work better on MSVC.

/* PRIVATE */

#define BOOST_CONTRACT_DETAIL_MIRROR_END_(tparam) \
        template<typename> \
        static boost::contract::detail::mirror::no& apply(...); \
    public: \
        static bool const value = sizeof(apply<tparam>(0)) == \
                sizeof(boost::contract::detail::mirror::yes); \
        typedef boost::mpl::bool_<value> type;

#define BOOST_CONTRACT_DETAIL_MIRROR_HAS_MEMBER_FUNCTION_(is_static, \
        trait, func_name) \
    template< \
        typename BOOST_CONTRACT_DETAIL_NAME1(T), \
        typename BOOST_CONTRACT_DETAIL_NAME1(R), \
        class BOOST_CONTRACT_DETAIL_NAME1(P), \
        class BOOST_CONTRACT_DETAIL_NAME1(G) = boost::function_types::null_tag \
    > \
    class trait { \
        template<class BOOST_CONTRACT_DETAIL_NAME1(C)> \
        static boost::contract::detail::mirror::yes& apply( \
            boost::contract::detail::mirror::check_function< \
                typename \
                    BOOST_PP_IIF(is_static, \
                        boost::function_types::function_pointer \
                    , \
                        boost::function_types::member_function_pointer \
                    ) \
                < \
                    typename boost::mpl::push_front< \
                        BOOST_PP_IIF(is_static, \
                            BOOST_CONTRACT_DETAIL_NAME1(P) \
                            BOOST_PP_TUPLE_EAT(2) \
                        , \
                            BOOST_PP_TUPLE_REM(2) \
                        )( \
                            typename boost::mpl::push_front< \
                                BOOST_CONTRACT_DETAIL_NAME1(P), \
                                BOOST_CONTRACT_DETAIL_NAME1(C) \
                            >::type \
                        ) \
                        , BOOST_CONTRACT_DETAIL_NAME1(R) \
                    >::type, \
                    BOOST_CONTRACT_DETAIL_NAME1(G) \
                >::type, \
                &BOOST_CONTRACT_DETAIL_NAME1(C)::func_name \
            >* \
        ); \
        BOOST_CONTRACT_DETAIL_MIRROR_END_( \
                BOOST_CONTRACT_DETAIL_NAME1(T)) \
    };

/* PUBLIC */

#define BOOST_CONTRACT_DETAIL_MIRROR_HAS_TYPE(trait, type_name)\
    template<typename BOOST_CONTRACT_DETAIL_NAME1(T)> \
    class trait { \
        template<class BOOST_CONTRACT_DETAIL_NAME1(C)> \
        static boost::contract::detail::mirror::yes& apply( \
                typename BOOST_CONTRACT_DETAIL_NAME1(C)::type_name*); \
        BOOST_CONTRACT_DETAIL_MIRROR_END_( \
                BOOST_CONTRACT_DETAIL_NAME1(T)) \
    };

#define BOOST_CONTRACT_DETAIL_MIRROR_HAS_MEMBER_FUNCTION( \
        trait, func_name) \
    BOOST_CONTRACT_DETAIL_MIRROR_HAS_MEMBER_FUNCTION_( \
            /* is_static = */ 0, trait, func_name)

#define BOOST_CONTRACT_DETAIL_MIRROR_HAS_STATIC_MEMBER_FUNCTION(trait, \
        func_name) \
    BOOST_CONTRACT_DETAIL_MIRROR_HAS_MEMBER_FUNCTION_( \
            /* is_static = */ 1, trait, func_name)
        
/* CODE */

namespace boost { namespace contract { namespace detail { namespace mirror {

typedef class {} yes;
typedef yes no[2];

template<typename F, F> class check_function;

} } } } // namespace

#endif // #include guard


/* mirror.hpp
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
*/