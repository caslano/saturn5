/*==============================================================================
    Copyright (c) 2005-2010 Joel de Guzman
    Copyright (c) 2010-2011 Thomas Heller

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef BOOST_PHOENIX_SCOPE_LOCAL_VARIABLE_HPP
#define BOOST_PHOENIX_SCOPE_LOCAL_VARIABLE_HPP

#include <boost/phoenix/core/limits.hpp>
#include <boost/phoenix/core/call.hpp>
#include <boost/phoenix/core/expression.hpp>
#include <boost/phoenix/core/reference.hpp>
#include <boost/phoenix/core/value.hpp>
#include <boost/phoenix/scope/scoped_environment.hpp>
#include <boost/phoenix/scope/detail/local_variable.hpp>
#include <boost/phoenix/statement/sequence.hpp>

namespace boost { namespace phoenix
{
    namespace expression
    {
        template <typename Key>
        struct local_variable
            : expression::terminal<detail::local<Key> >
        {
            typedef typename expression::terminal<detail::local<Key> >::type type;

            static type make()
            {
                type const e = {};
                return e;
            }
        };
    }

    namespace rule
    {
        struct local_variable
            : expression::local_variable<proto::_>
        {};

        struct local_var_def
            : proto::assign<local_variable, meta_grammar>
        {};
    }

    namespace result_of
    {
        template <typename Key>
        struct is_nullary<custom_terminal<detail::local<Key> > >
            : mpl::false_
        {};
    }
  
    namespace detail
    {
        struct scope_is_nullary_actions
        {
            template <typename Rule, typename Dummy = void>
            struct when
                : boost::phoenix::is_nullary::when<Rule, Dummy>
            {};
        };

        template <typename Dummy>
        struct scope_is_nullary_actions::when<boost::phoenix::rule::custom_terminal, Dummy>
            : proto::or_<
                proto::when<boost::phoenix::rule::local_variable, mpl::true_()>
              , proto::otherwise<
                    is_nullary::when<boost::phoenix::rule::custom_terminal, Dummy>
                >
            >
        {};

        struct local_var_not_found
        {
        };
    }
    
    template<typename Key>
    struct is_custom_terminal<detail::local<Key> >
      : mpl::true_
    {};

  template <typename Key>
  struct custom_terminal<detail::local<Key> >
    {
        template <typename Sig>
        struct result;

        template <typename This, typename Local, typename Context>
        struct result<This(Local, Context)>
            : result<This(Local const &, Context)>
        {};

        template <typename This, typename Local, typename Context>
        struct result<This(Local &, Context)>
        {
            typedef
                typename remove_reference<
                    typename result_of::env<Context>::type
                >::type
                env_type;
                
                typedef typename detail::apply_local<detail::local<Key>, env_type>::type type;
        };

        template <typename Local, typename Context>
        typename result<custom_terminal(Local const &, Context const&)>::type
        operator()(Local, Context const & ctx)
        {
            typedef
                typename remove_reference<
                    typename result_of::env<Context>::type
                >::type
                env_type;
                
                typedef typename detail::apply_local<detail::local<Key>, env_type>::type return_type;
            
            static const int index_value = detail::get_index<typename env_type::map_type, detail::local<Key> >::value;

            typedef detail::eval_local<Key> eval_local;

            // Detect if the return_type is for a value.
            //typedef typename is_value<return_type>::type is_value_type;

            return eval_local::template get<return_type, index_value>(
                phoenix::env(ctx));
        }
    };

    namespace local_names
    {
        typedef expression::local_variable<struct _a_key>::type _a_type;
        typedef expression::local_variable<struct _b_key>::type _b_type;
        typedef expression::local_variable<struct _c_key>::type _c_type;
        typedef expression::local_variable<struct _d_key>::type _d_type;
        typedef expression::local_variable<struct _e_key>::type _e_type;
        typedef expression::local_variable<struct _f_key>::type _f_type;
        typedef expression::local_variable<struct _g_key>::type _g_type;
        typedef expression::local_variable<struct _h_key>::type _h_type;
        typedef expression::local_variable<struct _i_key>::type _i_type;
        typedef expression::local_variable<struct _j_key>::type _j_type;
        typedef expression::local_variable<struct _k_key>::type _k_type;
        typedef expression::local_variable<struct _l_key>::type _l_type;
        typedef expression::local_variable<struct _m_key>::type _m_type;
        typedef expression::local_variable<struct _n_key>::type _n_type;
        typedef expression::local_variable<struct _o_key>::type _o_type;
        typedef expression::local_variable<struct _p_key>::type _p_type;
        typedef expression::local_variable<struct _q_key>::type _q_type;
        typedef expression::local_variable<struct _r_key>::type _r_type;
        typedef expression::local_variable<struct _s_key>::type _s_type;
        typedef expression::local_variable<struct _t_key>::type _t_type;
        typedef expression::local_variable<struct _u_key>::type _u_type;
        typedef expression::local_variable<struct _v_key>::type _v_type;
        typedef expression::local_variable<struct _w_key>::type _w_type;
        typedef expression::local_variable<struct _x_key>::type _x_type;
        typedef expression::local_variable<struct _y_key>::type _y_type;
        typedef expression::local_variable<struct _z_key>::type _z_type;

#ifndef BOOST_PHOENIX_NO_PREDEFINED_TERMINALS
        BOOST_ATTRIBUTE_UNUSED _a_type const _a = {{{}}};
        BOOST_ATTRIBUTE_UNUSED _b_type const _b = {{{}}};
        BOOST_ATTRIBUTE_UNUSED _c_type const _c = {{{}}};
        BOOST_ATTRIBUTE_UNUSED _d_type const _d = {{{}}};
        BOOST_ATTRIBUTE_UNUSED _e_type const _e = {{{}}};
        BOOST_ATTRIBUTE_UNUSED _f_type const _f = {{{}}};
        BOOST_ATTRIBUTE_UNUSED _g_type const _g = {{{}}};
        BOOST_ATTRIBUTE_UNUSED _h_type const _h = {{{}}};
        BOOST_ATTRIBUTE_UNUSED _i_type const _i = {{{}}};
        BOOST_ATTRIBUTE_UNUSED _j_type const _j = {{{}}};
        BOOST_ATTRIBUTE_UNUSED _k_type const _k = {{{}}};
        BOOST_ATTRIBUTE_UNUSED _l_type const _l = {{{}}};
        BOOST_ATTRIBUTE_UNUSED _m_type const _m = {{{}}};
        BOOST_ATTRIBUTE_UNUSED _n_type const _n = {{{}}};
        BOOST_ATTRIBUTE_UNUSED _o_type const _o = {{{}}};
        BOOST_ATTRIBUTE_UNUSED _p_type const _p = {{{}}};
        BOOST_ATTRIBUTE_UNUSED _q_type const _q = {{{}}};
        BOOST_ATTRIBUTE_UNUSED _r_type const _r = {{{}}};
        BOOST_ATTRIBUTE_UNUSED _s_type const _s = {{{}}};
        BOOST_ATTRIBUTE_UNUSED _t_type const _t = {{{}}};
        BOOST_ATTRIBUTE_UNUSED _u_type const _u = {{{}}};
        BOOST_ATTRIBUTE_UNUSED _v_type const _v = {{{}}};
        BOOST_ATTRIBUTE_UNUSED _w_type const _w = {{{}}};
        BOOST_ATTRIBUTE_UNUSED _x_type const _x = {{{}}};
        BOOST_ATTRIBUTE_UNUSED _y_type const _y = {{{}}};
        BOOST_ATTRIBUTE_UNUSED _z_type const _z = {{{}}};
#endif
    }
}}

#endif

/* local_variable.hpp
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
*/