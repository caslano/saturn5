/*==============================================================================
    Copyright (c) 2001-2010 Joel de Guzman
    Copyright (c) 2004 Daniel Wallin
    Copyright (c) 2010 Thomas Heller

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef BOOST_PHOENIX_SCOPE_DYNAMIC_HPP
#define BOOST_PHOENIX_SCOPE_DYNAMIC_HPP

#include <boost/phoenix/core/limits.hpp>
#include <boost/assert.hpp>
#include <boost/noncopyable.hpp>
#include <boost/fusion/sequence/intrinsic/at.hpp>
#include <boost/phoenix/core/expression.hpp>
#include <boost/phoenix/core/meta_grammar.hpp>
#include <boost/phoenix/core/call.hpp>
#include <boost/phoenix/support/iterate.hpp>
#include <boost/preprocessor/seq/for_each.hpp>
#include <boost/preprocessor/seq/fold_left.hpp>
#include <boost/preprocessor/punctuation/comma.hpp>
#include <boost/type_traits/remove_pointer.hpp>

#define BOOST_PHOENIX_DYNAMIC_TEMPLATE_PARAMS(R, DATA, I, ELEM)                 \
      BOOST_PP_COMMA_IF(I) BOOST_PP_TUPLE_ELEM(2, 0, ELEM)                      \
/**/

#define BOOST_PHOENIX_DYNAMIC_CTOR_INIT(R, DATA, I, ELEM)                       \
    BOOST_PP_COMMA_IF(I) BOOST_PP_TUPLE_ELEM(2, 1, ELEM)(init<I>(this))         \
/**/

#define BOOST_PHOENIX_DYNAMIC_MEMBER(R, DATA, I, ELEM)                          \
    BOOST_PP_CAT(member, BOOST_PP_INC(I)) BOOST_PP_TUPLE_ELEM(2, 1, ELEM);      \
/**/

#define BOOST_PHOENIX_DYNAMIC_FILLER_0(X, Y)                                    \
    ((X, Y)) BOOST_PHOENIX_DYNAMIC_FILLER_1                                     \
/**/

#define BOOST_PHOENIX_DYNAMIC_FILLER_1(X, Y)                                    \
    ((X, Y)) BOOST_PHOENIX_DYNAMIC_FILLER_0                                     \
/**/

#define BOOST_PHOENIX_DYNAMIC_FILLER_0_END
#define BOOST_PHOENIX_DYNAMIC_FILLER_1_END

#define BOOST_PHOENIX_DYNAMIC_BASE(NAME, MEMBER)                                \
struct NAME                                                                     \
    : ::boost::phoenix::dynamic<                                                \
        BOOST_PP_SEQ_FOR_EACH_I(                                                \
                BOOST_PHOENIX_DYNAMIC_TEMPLATE_PARAMS                           \
              , _                                                               \
              , MEMBER)                                                         \
    >                                                                           \
{                                                                               \
    NAME()                                                                      \
        : BOOST_PP_SEQ_FOR_EACH_I(BOOST_PHOENIX_DYNAMIC_CTOR_INIT, _, MEMBER)   \
    {}                                                                          \
                                                                                \
    BOOST_PP_SEQ_FOR_EACH_I(BOOST_PHOENIX_DYNAMIC_MEMBER, _, MEMBER)            \
}                                                                               \
/**/

#define BOOST_PHOENIX_DYNAMIC(NAME, MEMBER)                                     \
    BOOST_PHOENIX_DYNAMIC_BASE(                                                 \
        NAME                                                                    \
      , BOOST_PP_CAT(BOOST_PHOENIX_DYNAMIC_FILLER_0 MEMBER,_END)                \
    )                                                                           \
/**/

BOOST_PHOENIX_DEFINE_EXPRESSION(
    (boost)(phoenix)(dynamic_member)
  , (proto::terminal<proto::_>)
    (proto::terminal<proto::_>)
)

namespace boost { namespace phoenix
{
    template <typename DynamicScope>
    struct dynamic_frame : noncopyable
    {
        typedef typename DynamicScope::tuple_type tuple_type;

        dynamic_frame(DynamicScope const& s)
            : tuple()
            , save(s.frame)
            , scope(s)
        {
            scope.frame = this;
        }

        template <typename Tuple>
        dynamic_frame(DynamicScope const& s, Tuple const& init)
            : tuple(init)
            , save(s.frame)
            , scope(s)
        {
            scope.frame = this;
        }

        ~dynamic_frame()
        {
            scope.frame = save;
        }

        tuple_type& data() { return tuple; }
        tuple_type const& data() const { return tuple; }

        private:
            tuple_type tuple;
            dynamic_frame *save;
            DynamicScope const& scope;
    };

    struct dynamic_member_eval
    {
        template <typename Sig>
        struct result;

        template <typename This, typename N, typename Scope, typename Context>
        struct result<This(N, Scope, Context)>
        {
            typedef
                typename boost::remove_pointer<
                    typename proto::detail::uncvref<
                        typename proto::result_of::value<Scope>::type
                    >::type
                >::type
                scope_type;
            typedef 
                typename scope_type::dynamic_frame_type::tuple_type
                tuple_type;

            typedef
                typename fusion::result_of::at_c<
                    tuple_type
                  , proto::detail::uncvref<
                        typename proto::result_of::value<N>::type
                    >::type::value
                >::type
                type;

        };

        template <typename N, typename Scope, typename Context>
        typename result<dynamic_member_eval(N, Scope, Context)>::type
        operator()(N, Scope s, Context const &) const
        {
            return
                fusion::at_c<
                    proto::detail::uncvref<
                        typename proto::result_of::value<N>::type
                    >::type::value
                >(
                    proto::value(s)->frame->data()
                );
        }
    };

    template <typename Dummy>
    struct default_actions::when<rule::dynamic_member, Dummy>
        : call<dynamic_member_eval>
    {};

//#if defined(BOOST_PHOENIX_NO_VARIADIC_SCOPE)
    template <
        BOOST_PHOENIX_typename_A_void(BOOST_PHOENIX_DYNAMIC_LIMIT)
      , typename Dummy = void
    >
    struct dynamic;

    // Bring in the rest ...
    #include <boost/phoenix/scope/detail/cpp03/dynamic.hpp>
//#else
//    // TODO:
//#endif
}}

#endif

/* dynamic.hpp
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
*/