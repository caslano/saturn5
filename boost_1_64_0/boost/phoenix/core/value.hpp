/*==============================================================================
    Copyright (c) 2001-2010 Joel de Guzman
    Copyright (c) 2010 Thomas Heller

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef BOOST_PHOENIX_CORE_VALUE_HPP
#define BOOST_PHOENIX_CORE_VALUE_HPP

#include <boost/phoenix/core/limits.hpp>
#include <boost/phoenix/core/actor.hpp>
#include <boost/phoenix/core/as_actor.hpp>
#include <boost/phoenix/core/terminal.hpp>
#include <boost/phoenix/core/is_value.hpp>
#include <boost/utility/result_of.hpp>

namespace boost { namespace phoenix
{
    ////////////////////////////////////////////////////////////////////////////
    //
    // values
    //
    //      function for evaluating values, e.g. val(123)
    //
    ////////////////////////////////////////////////////////////////////////////
 
    namespace expression
    {
        template <typename T>
        struct value
            : expression::terminal<T>
        {
            typedef
                typename expression::terminal<T>::type
                type;
           /*
            static const type make(T & t)
            {
                typename value<T>::type const e = {{t}};
                return e;
            }
           */
        };
    }

    template <typename T>
    inline
    typename expression::value<T>::type const
    val(T t)
    {
        return expression::value<T>::make(t);
    }

    // Identifies this Expr as a value.
    // I think this is wrong. It is identifying all actors as values.
    // Yes, it is giving false positives and needs a rethink.
    // And this gives no positives.
    //template <typename T>
    //struct is_value<expression::value<T> >
    //    : mpl::true_
    //{};

    // Call out actor for special handling
  // Is this correct? It applies to any actor.
  // In which case why is it here?
    template<typename Expr>
    struct is_custom_terminal<actor<Expr> >
      : mpl::true_
    {};
    
    // Special handling for actor
    template<typename Expr>
    struct custom_terminal<actor<Expr> >
    {
        template <typename Sig>
        struct result;

        template <typename This, typename Actor, typename Context>
        struct result<This(Actor, Context)>
            : boost::remove_const<
                    typename boost::remove_reference<
                    typename evaluator::impl<Actor, Context, proto::empty_env>::result_type
                 >::type
             >
        {};

        template <typename Context>
        typename result<custom_terminal(actor<Expr> const &, Context &)>::type
        operator()(actor<Expr> const & expr, Context & ctx) const
        {
          typedef typename result<custom_terminal(actor<Expr> const &, Context &)>::type result_type;
          result_type r = boost::phoenix::eval(expr, ctx);
          // std::cout << "Evaluating val() = " << r << std::endl;
          return r;
        }
    };

    namespace meta
    {
        template<typename T>
        struct const_ref
            : add_reference<typename add_const<T>::type>
        {};

        template<typename T>
        struct argument_type
            : mpl::eval_if_c<
                is_function<typename remove_pointer<T>::type>::value
              , mpl::identity<T>
              , const_ref<T>
            >
        {
            typedef T type;
        };

        template <typename T>
        struct decay
        {
            typedef T type;
        };
        template <typename T, int N>
        struct decay<T[N]> : decay<T const *> {};
    }
    
    template <typename T>
    struct as_actor<T, mpl::false_>
    {
        typedef typename expression::value<typename meta::decay<T>::type >::type type;

        static type
        convert(typename meta::argument_type<typename meta::decay<T>::type>::type t)
        {
            return expression::value<typename meta::decay<T>::type >::make(t);
        }
    };
}}

#endif

/* value.hpp
bVJ66t8I2GKZ+LsDYo4CS2k15W8ETDYelcKpfx/haViaFKdsLyomx/mGSE/EKexdKZxqH8IyNHYUlqmx1PFWfao2GDZQY9NhuRpbRGwNLEdjt47Xl2ErLFtjT8JSNfYsLE3TRk0wh9lf1L/l0xItO0z9Wz6ZEyxT/5ZPgWTy38VINsrxXjwPVDhO6kudTJsftvB/ivnRW1cmChOWgu/0SE+2GV/hK/xu/6gko3PkZwniZ/uOGEaXyM8Sxc/c3zTM7ZLEzzpNjv4sWfwsyRb9WSfxsx93iv7sDPGzeXnIT0IkW+JnX+FrjvHPZOQPuRmIzJcYa41641fGn40vjb62c23FtittP7bttO2z/dPWM2FiwmUJSxKuT7gv4aWEjxJSE4cnzkisTNyQeG/i84nvJSYlDUqamlSWVJd0V9LTke9XkvYnHUj6JMlITkzulJySnJk8IDkv+Zzk6clFyZcnFydfkbwc3xuTtyT/Mvnl5P3JB5L/qf22IY8OHG36I5/98e0Q/+8n3jmMQfh/N8OB7wGRn0REvGv7Hf7qamQh3q74TsR3gpGKd10ir1S8bPjuZaBf47tH5NuGF/+6DK8deL1nYL9FG1yE15V47cWrB+r/wgR8xusBvJrxcqLfLMBrK15HE9F70AF/iNdHeE1GywTxehKvRLTpJLxCeO3GK/0MbIvXDXg9jdeneA3GwFSd0vovwuJ9JAzSarsdwok0kb7IH/KMdFvzlSilhTyLfITT7WGWAeVrk2ekifREfEi3Nb3dKSKu1vQSWtNHeKQlyo54RR6QjkhT5D2c78RIfqJlFWmLMobDXynqVcQfCXMoJZIG8hJJA/kRaUTyfdTME8oRSStdqtNPzbQzOxvGjM6t6a7uHEkbeRNlFu+RDuJp/VmiaAOYmT7yh/Tb5rGhcyQd5E3kK1KeKVI+UA7kVa37SF6RXrSeRbuLeJBemz7wVue28R6FIy3kpzW/W0W/aE0z3cwXyiXSbBb9oGNpJ6W2n/bE1JNPH2kgDyJtqQ7bpn1127RFmeW6TBR9WN4HRN9H3k4u7R2nIe2O1PshTb3363Ly9S7KYvbToi5yGdrmfYG572+V9n3kH/GreW+Tb1E/KA/Sj5b3fzfOhcNMjtSvSFek06zkYW0XuT+Y8UTGKVF3Iv0eCaK+RFrIs8jD3g629/Yup3YfRz9B/JGfIR752CXGrch2+7q0qUeR3ylmWyLPSEMd06R+Y5ZZPq483cHxLSnt1JZdbsMZnZG22VZTwumZ6Z6VJvInp4s4xfgg4ks3jxPIC/Igjl1SP5ePDfGX/fI00fdFHnDMQtyt+UYb4rgVux6Qb11dYHtRHrGfhH19Wms8n4pjtwgjjoHIR5t96QYzn8g78ir6E/ISyYfcd1BOs4/AdqSJejeP26JeRJ5EWCmt94z46zIc/zsn9iPU49frS4hfjLvyPoTtkaYIjzhFviJxd05vzRfSRHyRvCD/oh+KPD4g0hXllI4XYjuRrjQ3E2Pj2HTR1qKv92hNE3mIzmVEXsTYhLyLOVK4LJNE/YuyiLZk7SC3QVl6+/vyjekn3waxjh170k/f8UM3Tz6cfvrnyR3p+9kZp3YMdSbGX0fyOFqYcWJbTUxVj/Vy+4h2E22EfNE2X5KhzhlEfEgr/jZHGTVlit3n6jNOf5+LtjfCI0xrHHIe3sgQ+6fS7vLxOZrH+No93rTTu576tGPV+bSup6/OY6V91WlMWzfG3NP1vzPGtJd2038h7Vh1fuw01rkohziOinCRfAyxy2UQ8SOOtmVB/OJ8Xp0XowwiPbkO5X2i2Zw7XWRvjUNd40g3609dP3pAc14nz6WcorzSXB3p3G/Htnj16mY=
*/