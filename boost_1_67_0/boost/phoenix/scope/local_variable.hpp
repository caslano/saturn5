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