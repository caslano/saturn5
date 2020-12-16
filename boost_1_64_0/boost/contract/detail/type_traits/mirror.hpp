
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
LmF4U0MNF/az/o/fSX0lePY+Rq7Iy+ELxboJfFzMP8PXHLftG8C9JfV49BX+g/WZ9Uhifwp53kc9FJGPrlP2DbqWZn2k9o50sj+N92vTXuEuajW78QVnnvnEYkPtL78evFfavNbhyOphZ9J4RN8tHksD4I3EH+TiGzzBUWtl3CnldGa5duAhvS4Hz4rXuuBdB9b2lU/h71mxaYvvsgXvzPTzKcaTzH46TvhQPK7it9il1iA/zW/MW9Xl79fwOw1c7zvjwEETNsv34fDHvsyxaBzWIegn0VWZac9YnFTz8bti4uDE4ZnG65nAzjRVTrGIX25trV+6LbTTFXqvFs0lr27I69OjYeBd+S9eN/BKtvM+n8bf1cHzcfgV59QSg//ReOuvwnWaZ6C8DX4/5WSxi7J+7Y3pHj3wUh4ex/zu0MwTaZbGPPP2obyuPEzPq7Zqad1aO2OdBo6/SvfqyVSYIEfFo+hQGHHHXsQ6ve+U9rEG8jdt1P1R9YST6sbqJeXz//No/LV61+qxTRc6wrx33BdjOdWXfr+QHhYfsA7Ge22RsTeiow6EnCd2Xfw94z9xUi8F3aPu6+rJmv8oFjdpzeh4vD2Rvj0A+93ziU9pyt14h+7vAON2qI/IN/oUanNM55DnoPiqRFy8A2e9Bk/1mvp9Reu3xOv54PrTPquezxaCF/zau5fk9vPiUwbP8E0PT6k39dP1rhqPxvXN8XHQR4Kp+2OtDyxtr39ckpeehreCs0PXh8NRurp/T1xBw8W0cI+X9GOfohv1BAfIk5kL5KzPbvPzG3C1IP4sToPVuYpv9ZZSbKTXW5iT3EvDJ7W0dnm+5kvpr37d9LXvGRss6bXUOl7lU8bDJv6uwFRrKq5zUtDGA/jvj9RLMXXAZzc8ip86hJL2Dy/pG23io584LSan9aBuqt3CcsjPnlhEs+CfTXqJy1dEqU8YJgZ91U/wjMy4suLn2Z28IXtW6mO/Hv6Qe/DxbWc0XOfvfOp7T8Sc6Zcz8rC5udFxcw/RaNYh4396zmdC5umZfD2UxsvhyJmopN7nv8a+rpReQxf5k5W2wLmLm4b1c3jiDXD9ffVID40Vr5Pt3Kek/KZlurj+pI24ZweeFsfy9NhOtfQT3GtQnhberd8kjtvE7iwuHW7NvihPp8mxJzPK9XTBezxpSj+/W8w5OvyRbEHw3k1rr1bmXubnxLbOENdQpw0jtHwjsRsPx8V5Qs+Ic/w0jLi9ALf9KPTmSveOE9O4x5z83ydqWf9jOm58Ve+qyAYaSG6fMa/l2/VX5cTlaerwa5jZS47pqb0bnCXMYFyDQ0nnpXPzq3Xp0RlF+ETzHBnkaX383xBX/6O/AL/vGfePegZV9HXrfKxnAeMG8wZT3ae77715St6XwucvwiQ1de643l9a1/lB//Y/eNkNL/8sp+V7qAFt8LR7Dae1vzSfi2L/m/VI43vuP/cs7P5eb96Z5VenhLwf0RqLaUIfeZ2C13GP4Hco9bNGEfuUnejn+GbB8xnuf57/llNfDpQLu2BTP3r7nLkkBmf45EBwpo82Gp7AW07nAbdbe/mVPjcvWMVZoOJySby6j1GTP7qn/PqXNp9uTM/TZZNq6i8UsZ4TrJt5/rUCJsOGt/6lJ0/yoXSbfqCGpfr3b//SKgllzdN4d+OieyP4iY9xQPCuNX7uSuDBW9JZ4tnimNqkX07ikC9u6pEvVBPBc5hyOGGbfudJOrOgNVW/d40rXXP1ttSeuPoZ+p11nxxKeg9xT/fbrjabdabRx9CgeKSRHFk8Qj+U9w/rw1w7QXPwuVXsu7VzveuvqVc53FtvZLvxl8lHW6jbz8Vyg3qadCnAVHHeJWfh6SU=
*/