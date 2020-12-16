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
18DlVwwgPbQspFa16LuQPK+oXgHYSTiALghD94Tt6ActPHsAA11wA3YBKPauMADIvUPAgd/wIN1vRr+9BDeFPRr3GQBvaDdwRgDw24X3APx2UfggyQOew4Ae2IcAl9N3tukcf0DJxcJZHyn9astv/7fc3mjQXpnfXqXfvnS5vcSgveGgPeegvd+g/Va/tW2ZO0PnbEr3WUr3TUr3NIL2LfzW48vtMfjtG2jr5CxLudXd2VagvSvKylS6Ij7b6rvoEZeEFc+uGU7ZwCZNUiYUoprZx1r5aRm2SzvUZt8Hs3kh3CbMkOjZ3IxfBSJf5a/u94CF/NsvS+7hIL+wDYFhOj873rbe7s08SFzVvm4PvRe6A9sw1FUIEtbPn3O1YWfO5a8rSkJW5XzCTNqUFFKJb3io+GEMBYk/dQ3uTsuU36Gy2azC+Z3WHEoCarEMycvRs56L4doFO2AVN4LDEMsqjsCRmTbfzVGIwlK441VnCFnpIqFNLPms7iWRk6BUJx2dgISjI9wZK4fypmjCVEfodg71SZ2pPqlz8tWeRzIfLX/ZX8+38uWUvwe1X+5JZnyzIkgXsjHLj1YdyI1gryu5drKSuZETF3/SmkL1qGhOpdPRN/SYwcx+p2PbNgz++Ot1c+tWsxXlZzX84h1t2/bTz/ZFJuPZtXjTvM98kMmDiUhPf6QHt9+FhyN9xesQjdnvjwQLjgMtHB/fNyky5FU5mtZW2sxfbUvSts0WZbW5zWwvR5eADuQyykrSnx4fh2zgObu+AnQDURGoOgJOp9LVjs7uCOaeq82Hm+tR8JUnRjJuDa72KkbLGV2kCnU95zycswB0f+CSC43QL5oNvlPwUcuN0OUrjRDfb77UCPVcYISC7linuwYff5ERegzw6f7B3y0xQp8GDd2F9uPmiq+Ur7QuyGpNufJCKxrh3UOR/s49fKNp72PCc46HPpqqrK7meXu/iKtmApmo9PWWb5umcF1es8XBXWtQmi9ppU8h2rbRYin/EqF5f5NOboT3jEZ29nU+AscTB0aleZeGugk/bnkhLkRfjh+grK2hqx/PMxY21NTX1NbU19VSmQDa12r5Nwn5aruva/ZvaPabNfs3Nfu3YM/Y9m9r9ls0+3f4t/GU/bua/XuwH7ft39fsP6hlC9t/qNk/w/Eq81nN/jnN/nnN/tIax36C5VHmJs3+BZZHmVfXOPYvsjzKfEnJoHDqHJzX1Tk4b6hzcBbWK5xaXtDE82LjQuRAC+VEY01jbWNdQ01DbUNdfU19bX1dXQ0yoq62pra2tu63v/3d726/vb6uAdycewe3My/124F1/JuDHMa/OdigfksQ2ax+m/C39m8Q/s5Qvz14u8FhzCdv83lJjeLzIBv/Gzb+zTZ+PcepjMQv+S1yZLh4OfIcYDqRi/XCsin5mBhFUOQU/TjyHuAwkVvhNxlKnq/f2wi9HNB3HyN0LSC2zAgtQRt0HsI23NQQWox3j/0uoB17NnBFfwnYHw5cY558au4hPhe6+FTeZv63mXLtl95w4xbksri8synYwW2eTJC5M7zmGl6MX9+2jb5gSaQLslUmu12MVkl/OytftXzk4jsXXSRztLGiJ6/97sbQAUCQXpMPedCjDa4Tqm5dt7fRuO6KRlfYeYb6HeU7EHYHwiaN+ZvP/APyXIV7hnlRaMG8f0Ooaqqmav6/zDsPNxj/7wbL4SOvff5PP9Lc/8qd7zlxZOf0m8cfyHec+64v8I0bdg/Rti9Hu9fFsOlNl7WpT8Db4hau9ZBw9KYI7u+Or83E1XcRWxmUWWZUTdVUTdVUTaXmLvt36r7Eb8f9on0NId19c0l43bQ7/KQW/p6ZhtCtM+7wD2o=
*/