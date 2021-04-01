
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
Mn3BWX8U1CJzCIJHNAz8ZAz2hVdEdsen9LiLbWSJJN22+MpGGj59g7O0bLq/ftgTdYbcc7LNTbK98bQ57wZl8MrBoh+U/MbbOsxE6n+wycIR4MNmgmiXYilztKoUl11iYLPBMxmolZfsCs+Ff8/qqhU9dc9uwYmRDGVvVvD6mn6cWkbr0cHC0vK9MziNMM4uXk9N1EEoPJgZYVqYrm+W5Te+4rFXD9ypE9xfnRIaqYOzSZoTw5naCumyZeaMBolE2I8yFVHp4HvEV/A8merQq4z+4zokziBrVoZ9wh3z7wsf09zrTF5hN3GLEhfxy/j9wSNJBATkMxm7YvqttSkt3/lzo3jV3z5QXwIVBv0GK+kAqw0jSFCfVEKqKpSMJPCjxjA1A79WAgNDk87Fb+bMyIwfgC/Ph08KtSBzObTp+uxktOouEo26tLwx11cSM/uf/fd2H2F+bz04uSTP79pd4+J3FgMv9wnMC8senE2bOiYETBEWfSAqF7vC0LzzF3Za1QYkPmAPSH8au1D6woTJseguvqXLO/rXovDl3Bfy7BmyN8CwiC312O2FLg==
*/