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