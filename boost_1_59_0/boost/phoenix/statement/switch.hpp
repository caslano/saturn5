/*==============================================================================
    Copyright (c) 2001-2010 Joel de Guzman
    Copyright (c) 2010 Thomas Heller

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef BOOST_PHOENIX_STATEMENT_SWITCH_HPP
#define BOOST_PHOENIX_STATEMENT_SWITCH_HPP

#include <boost/phoenix/core/limits.hpp>
#include <boost/fusion/iterator/advance.hpp>
#include <boost/phoenix/core/call.hpp>
#include <boost/phoenix/core/expression.hpp>
#include <boost/phoenix/core/meta_grammar.hpp>
#include <boost/phoenix/core/is_nullary.hpp>
#include <boost/phoenix/support/iterate.hpp>
#include <boost/proto/make_expr.hpp>
#include <boost/proto/fusion.hpp>

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4065) // switch statement contains 'default' but no 'case' labels
#endif

BOOST_PHOENIX_DEFINE_EXPRESSION(
    (boost)(phoenix)(switch_case)
  , (proto::terminal<proto::_>)
    (meta_grammar)
)

BOOST_PHOENIX_DEFINE_EXPRESSION(
    (boost)(phoenix)(switch_default_case)
  , (meta_grammar)
)

namespace boost { namespace phoenix
{
    namespace detail
    {
        struct switch_case_grammar;
        struct switch_case_with_default_grammar;
        struct switch_grammar
            : proto::or_<
                proto::when<
                    detail::switch_case_grammar
                  , mpl::false_()
                >
              , proto::when<
                    detail::switch_case_with_default_grammar
                  , mpl::true_()
                >
            >
        {};
    }

    namespace detail
    {
        struct switch_case_is_nullary
            : proto::or_<
                proto::when<
                    proto::comma<
                        switch_case_is_nullary
                      , proto::or_<phoenix::rule::switch_default_case, phoenix::rule::switch_case>
                    >
                  , mpl::and_<
                        switch_case_is_nullary(
                            proto::_child_c<0>
                          , proto::_state
                        )
                      , switch_case_is_nullary(
                            proto::_child_c<1>
                          , proto::_state
                        )
                    >()
                >
              , proto::when<
                    proto::or_<phoenix::rule::switch_default_case, phoenix::rule::switch_case>
                  , evaluator(proto::_child_c<0>, proto::_state)
                >
            >
        {};

        struct switch_case_grammar
            : proto::or_<
                proto::comma<switch_case_grammar, phoenix::rule::switch_case>
              , proto::when<phoenix::rule::switch_case, proto::_>
            >
        {};

        struct switch_case_with_default_grammar
            : proto::or_<
                proto::comma<switch_case_grammar, phoenix::rule::switch_default_case>
              , proto::when<phoenix::rule::switch_default_case, proto::_>
            >
        {};

        struct switch_size
            : proto::or_<
                proto::when<
                    proto::comma<switch_size, proto::_>
                  , mpl::next<switch_size(proto::_left)>()
                >
              , proto::when<proto::_, mpl::int_<1>()>
            >
        {};
    }
}}

BOOST_PHOENIX_DEFINE_EXPRESSION(
    (boost)(phoenix)(switch_)
  , (meta_grammar)           // Cond
    (detail::switch_grammar) // Cases
)

namespace boost { namespace phoenix {

    template <typename Dummy>
    struct is_nullary::when<rule::switch_, Dummy>
        : proto::and_<
            evaluator(proto::_child_c<0>, _context)
          , detail::switch_case_is_nullary(proto::_child_c<1>, _context)
        >
    {};

    struct switch_eval
    {
        typedef void result_type;
        
        template <typename Context>
        result_type
        operator()(Context const &) const
        {
        }

        template <typename Cond, typename Cases, typename Context>
        result_type
        operator()(Cond const & cond, Cases const & cases, Context const & ctx) const
        {
            this->evaluate(
                    ctx
                  , cond
                  , cases
                  , typename detail::switch_size::impl<Cases, int, proto::empty_env>::result_type()
                  , typename detail::switch_grammar::impl<Cases, int, proto::empty_env>::result_type()
                );
        }

        private:
            template <typename Context, typename Cond, typename Cases>
            result_type
            evaluate(
                Context const & ctx
              , Cond const & cond
              , Cases const & cases
              , mpl::int_<1>
              , mpl::false_
            ) const
            {
                typedef
                    typename proto::result_of::value<
                        typename proto::result_of::child_c<
                            Cases
                          , 0
                        >::type
                    >::type
                    case_label;

                switch(boost::phoenix::eval(cond, ctx))
                {
                    case case_label::value:
                        boost::phoenix::eval(proto::child_c<1>(cases), ctx);
                }
            }
            
            template <typename Context, typename Cond, typename Cases>
            result_type
            evaluate(
                Context const & ctx
              , Cond const & cond
              , Cases const & cases
              , mpl::int_<1>
              , mpl::true_
            ) const
            {
                switch(boost::phoenix::eval(cond, ctx))
                {
                    default:
                        boost::phoenix::eval(proto::child_c<0>(cases), ctx);
                }
            }

            // Bring in the evaluation functions
            #include <boost/phoenix/statement/detail/switch.hpp>
    };
    
    template <typename Dummy>
    struct default_actions::when<rule::switch_, Dummy>
        : call<switch_eval>
    {};

    template <int N, typename A>
    inline
    typename proto::result_of::make_expr<
        tag::switch_case
      , proto::basic_default_domain
      , mpl::int_<N>
      , A
    >::type const
    case_(A const & a)
    {
        return
            proto::make_expr<
                tag::switch_case
              , proto::basic_default_domain
            >(
                mpl::int_<N>()
              , a
            );
    }

    template <typename A>
    inline
    typename proto::result_of::make_expr<
        tag::switch_default_case
      , proto::basic_default_domain
      , A
    >::type const
    default_(A const& a)
    {
        return
            proto::make_expr<
                tag::switch_default_case
              , proto::basic_default_domain
            >(a);
    }

    template <typename Cond>
    struct switch_gen
    {
        switch_gen(Cond const& cond_) : cond(cond_) {}

        template <typename Cases>
        typename expression::switch_<
            Cond
          , Cases
        >::type
        operator[](Cases const& cases) const
        {
            return
                this->generate(
                    cases
                  , proto::matches<Cases, detail::switch_grammar>()
                );
        }

        private:
            Cond const& cond;

            template <typename Cases>
            typename expression::switch_<
                Cond
              , Cases
            >::type
            generate(Cases const & cases, mpl::true_) const
            {
                return expression::switch_<Cond, Cases>::make(cond, cases);
            }
            
            template <typename Cases>
            typename expression::switch_<
                Cond
              , Cases
            >::type
            generate(Cases const &, mpl::false_) const
            {
                BOOST_MPL_ASSERT_MSG(
                    false
                  , INVALID_SWITCH_CASE_STATEMENT
                  , (Cases)
                );
            }
    };

    template <typename Cond>
    inline
    switch_gen<Cond> const
    switch_(Cond const& cond)
    {
        return switch_gen<Cond>(cond);
    }

}}

#ifdef _MSC_VER
#pragma warning(pop)
#endif

#endif


/* switch.hpp
GBE3u10iGU5SGVJKfGdKFxSKF7p6t59Hu5SX4voGy1m7MOuNfxar8g2RvdkSoYr4pP8i9m1NUS7vBZx06LHx2qsiwYomjhyV2+f2Y9gcsuG4lCrhV2a7A8plZmISR72AIOPmAmpra3P/XjFKjA+Ar/fQwL9pyavxXD088qtvDQeqz3sz/Rhrnbb69WrFzm1PcGhiikiuMbZAfU3uVPUcOwntMq4mr91M3kealwHaD1DwzoCxW9tSVZippDT1B3iIGPDtVWC6zVhWiOIlOPnqfcZpg4iRjObZD/7L1WyJJJHAGlFzdRZr/8u9s5qQLB/ReofzIf8yJeN8r4A3l9CXSpgSAZVormNGvyeOi3EPJDs1so0TMr6N+gwClLlXwW60Q1Apjj7an982QbRiF8vU+I+u47/wxdin/+lGrQpxb437P3QaYzze3xkKf8EdiUSEHKX+bvbHo/roopH2Hl+h7KoM3Y+1jqvnIjqEtZlT66aZpYGUl0Wn8vtlFuzZd5kAvYYal5GN7Mqt49HmlNXxeGHuwi6etHvpM5G1u17HGTvhq6BRP56xhiANM5wvJ5C3x/GEzeQldpoYdf5r45I7fiVfb04fdI4QXMy2x8gJhJj4xL/shJYxcm6P24/4Aq3jFe2m1Dt+/C6lNkNIm3paFVjhbXShU0Jdd+P7SO/PMOXJaKQV/y7lnR+DU9+bwKDbr45WNb3L5m+/NxOSYEspLYTyfqif8DuholLdAHs0Kd3rCmdPpaF+daAS3pg0r/ovzMzMsJ2MK52xdbhAVP2rrngoHskcQ2eXfDn+u5vpJNtDfcG6aRh6sibmglqTeq3Jz1sXQi4wJKuuLp3ANfhajK6T0V1mEOtTAt6sD3TvzwfMQxM0/ROJ9gwLD+sz43Y++BRyA+pltJGc3ukRc/xT0Kd/Ij1VY3prD47MgnrlXGVBSIDrJH+TsxVGUv6cs2C6cmA90uDIHmAGAwgzN2Sum9LDPRgw16wYJ63x6p9DGBxyaV7i+YXPxsepEzbFU+mEr2jSJgEq0cwk88l0IhcGLG2Uix81byhyC/h+JbQ+X9fFOCjYb7dQxEunk7hTKbvGdpaiQ1W3O+K6xAtQ1GIz3tTDOkjMY1b/3mvT9ISAzn9+nh5WfUdLkLcA6DoQK7rX38UbFzNPeCc0pks/+HwPZ2wk6M2fQgcaj82LScXLPFJt7u/xpI3YuZicMvLnzvK0PNK+4fS6tS/LWL4xIot436ul07HMamU3sokzQn5OHGAv5IuPUv0eJS1VbbT4kBtLcjRbNRNv218bori/U1ar6dVl+45/DmieAugeyrkJlTgGYiaXqCMi3EfiDGvmH51wXO0K5vRym5pLrts7uFesN7r5yv9JukjdcK/QEp+O+zBmpHaAFkcFud1Sw2b9kshEPp0KeX9BGM1JdpeMyc3DOplpPiFOW6ttRh0VgPV878yy4pF37ru8oneQDKZLW5SPcJ2bqCJGu9ERBTEyioWUesQL1tXVVe7/Gozyr8bGw8UdXOv0gau13VE7N8ksYLhC6B+7qFoim8o5gkUoeoctMlLQ7Tak45czl+xgpLAaH5ww++KdFuSr4CSAxuqGXNY/DqYEgHUnhJ5vE7B7RoLnG7wdj84q1YT1leXwSo23WYnT1FCaO742+uaZi3+kpOi/V9PpUwa5nYm9i1QLz1oVX3XtV8mqPb5ztarRcrnK2PM1wmhNcIjueq/86h9O6Rvpy+7rUgHoN7vAbYCFJNIijLY6kuwA+1vDSVG3IaxDgaie9q034frIsmm6/83e5GvxdsM/R8EOOiwPjx+FzowrFIyV+T/NrmkZOw1IArve0MHCCRNjKZPQ337AF/rDraNMOtLa7sYaKWCd/TPf2+VdIofGb7Mq2Mn3fz++fpAAx9uWOHfImxd/u7qhwCv9nZV7FlCuFVbW4QDqcAj7+6/pA1aDvJrmKz/UX+Nst8eYFfDiHtLTjSXj6Jh25ggFUxce0ju4O1ZA5Hz/2b2W+355i88tLldIopsMLNQK6le+uYhe8GE/xZ+f5tbyvgTCpNUSMEUv12YyDhVpoFaT+0GJH1gsaMARt4z6jlzmLC/xJhWCEK5zpEpd1y4soLasw6SMNK+Lw0AAphVywvvBKAWt+7u9vSFwqy+k/r9zTyWVXuUiRru9SSxqRmyYFio3CoXNf57ntmf0RVGdC8w408VTLTWc2Z+YU9XnxBbCoNu7xenhazBJs+x9uhm3M2LM65HAu92e584m9GOxwM94HIoqL44fWfdv+MZH0YB/3x4Xcrqhi44EVE/8PsiZ9adtlIrvfoMMGSJnfT90Z6aZldrZ91zTdW/0RL91deyZfV/kaxfJGkotaLmZdEXmJZoehufO95LutvZLbzjN2sG6Gh7VF4hhEaai8+56HetaIbcnq0CQmQxXV4dGMPhTtmMznnGd6u2+E4vXdNTxzp/rjZKE1FoAoQ+u430A/RSVbsjATnE5VFKi71V6ySK90BgVujXHPA3wY5DAJyL7uRWgZTlnY2eOeK3mhtFlR8cCz6JyV43ocY8eGO3PRzzWSA/pMwqfLAnL8Q4HBbzBspwNCPjf46+yDn8Pg/Zh7lZUk42/8HPzSUny8hLup2g478tiVyiYWybW4TvyycH5X+bDdTGsc97v0TH7BOJlLr1wM9ap88urvgkurd8kxm9tqJHaQvmbl4s12lH2XmMBgdnMIHFrbnGWHjHwixR1zAdjWFnMPt2qWHPrPKb1TVlkh0gbGW102/FnkFgYP6Ya+92x6JLF4x8CE28IDKXmwJkAZLZb+DlPWMkF/+BzKU1nk1P9JXNVPJ0JOswNmdLtHoRwJ5DUzD0BcHYVf1QV9gqFn0D9QChSSzCoJPkWkzQJkFvLpRMaerCnScUjbTf28m8uM+b7V7o46v9EKhxzvB59A3kxcFR4dQZYdX8FzgqQv+PT5NX5HnrFbKfr/6kb+e5ek9F1NEPmt0Qu5PS7hD6v9MKLFaSWimOjGMHiAD4W5gDRNa0GHBtMI5l/b17knnLlhM/NnIBu+13CcOFVVwXRAOXfLQ817/MTGZbqaNK8PwzEtgmx1+iK5SjBs6U3RVk6YX8dcep7notofBuJqyvOsVdPbMlZMQK9kVm4PmlMKJ/31a0XjCSi1iCHBGSRz3RRNzrEXFVdlJfAWy8fNO2Au/MSe3fmWvYu1kxf9h71+7fI7VM61EjLvYCS37/NWogVqvyFjndA5b7dv4ci4jMly+Os5WGXdvKIjU+IzkGjA45zBjuJw05x9dzt0HId7eQcd5kzbJai4JM+U8i8sM0VhqoIqG/wIj91tmsKrryR+gBeX89G4UuOHzuMBRYVFfnb/fgxR0tJqVx4hiqtwAnGfH/1Ae6H1KFGNfLOrQYv9cQ4CvkZ1vWkUmHpIARFeAC9uz0yx+lYbia4H/CyViQpeaeuCKAwtC8dEMZ1FKPFqW74AyBK3dWCdyyWW2Zv9E+pRCcVLu/99ABFHnOCpNR8vFEPQXZ66MFoAQhEgpE2DVCHM7+e8zsUjU7mfTfBq2cZOPPdJVpL16xo9iVyb/+AUy+Kyw/Iggw6YXy16D9kACk+qyHjdowR6G2sNnH7ee4NlRRQ0pnCXytgiW849wiV0oZHjW3cIdlIR9K9ZrImxpJz7q2b2dPDDnHP7Dp7aUsnSzxWeDZSI1b6gB/ETVVI0xgel/SYQtKT0L9ZBOI6F9jPiRr5ZVF7mSj5g8RB052kA2IM3AtoujN4H2Jq5agawYuva6agdqDzlHIKZFujZGuumq2/VgVwFFGAzPfWFsi0K+jXvlG0bYRW7LuPpa8rT3ZpdiK6yC2j5+40EF0TSElf/M4ZzaOYM9nvUotEnOk5Nh+clNw6KMcKDDUcZ9HTh7MI2z0YDVQ2ghtGa2ZcuFB/ctm9Uv5spLbltkIDo6LGV1H4vijjXWktrbnuWXzf9+/fv0beXuyg4hviLulvAh2/XKM0HU1+lCYZOZCtfeus1tm0vMR4mCxmHNk2fKHfFQUQ5CM0k8IxzbROArgQnhYp4fmGMznTTfrT1weR0UN7zIhDuGQOLyx3e5znFI8KH6PR+C/YZ5KZqHhkfUTtUJXzB2PFUNAfFLfBr0czvlfJlf08N1IGPyNmXipHf9U3rRx6SfbdnsfIPOZCzy56fsXs71BK60Rka7Sby6GegJBj6YLGTdv4K/10aqYrTsupPydka8L+6k7SZ50tIp5a2QkJrZ6R6DvX6GSuHB++Wtvmfso+VyD0c6kwOMY9sz2/6Xe5Xd/52cjij9IDYIglqqcT5S2cmMdl0PN+9r6xj5/yluQbw1uecX8Hsh7mAefmnxVSxTutoLGxnBL6TJACq7ArxSzcw0JR2mw0H9VqdpFlEpJVZ4zdNw8rHdBQZfuuI+vkHKwLye9WT6996y7r4IbAHtLgyKdFR+rOLG8lteNaxrgMvy2q46CsQ/fKJ59+HtCIfcYqtaMIhkae8JBl4bqF5t4YSAL+qSsYny/aGHs0QYZiKFFf9fTaLqw9myAO93Xmw7HG8wsLU7RUVOIX51v9UgdnN0R44v6PD6twDd/eiunma+buDwbkEnFzBNotFN1ozfM1/b+ozg3ZqdIiJL5BTbsnEVhuWTG1oH0GX4S4vNgx/RSSkemOQ1qvh8ECg1txo1dN3dWVYqzvWoOiOu6olMQm3BBbJYg+IylmJHC+EvtbYdKrgyleBQdJCX96CvUfqigHGQweFB807qsGXEAwEi31aLGiZclkuNZaeDNoCM38wbd25dsNGXyW5Vo7gTDj9EjSZytgor07fwEbv0zEUwhTds6gcrXe6oNa3sJLHWMcnKLu/a0/8uIZHzSsY2mMJ/OFRnIvMb5qHmOoVJKsHK76pHWDdqKiSA7sJX9tN9AIu8xldW0kSvZisG25f8Bttu5qhkDwPgibxqWpf0cZJJbzza3RiAx77Pk8ASD1+6oxR+o5Y+VO2Ju1+c852N7ZDtBjDRdvi2+5UsB42qsu2iF5RMyj3uniHR8ccQG8UHBIp22LAk5rbP5a+OEgoNzGtQz4XXfGGusqd/ZRu4h6Naaw/dXWj2tR/9youY2ZXB/Jx1mX4lVGYn/2G3ttbe17kEXKoto+dnlFBSQekA8/W0d8OhNKxTctyYpZyGa59XHZvAwhtMi+Dss8fNXyTo0Hd8OKj8DmTjKoyto09/RHsPAUPeY+vVkYjcg54fY6Gd2yD+HsczJGO+jrXVo9RbyDwpOBktJoncAMGzn+AQqZpJaXnKMVTmeV2Hb/hZNKGY8cCu/Lxfzu6USjntdylt/Iq2vpAWmoMihOY4G/mEGKjetAcOjMX7TUTCGzAktGLiHeDCHzDicAMoD6/k4Ccoesr/HUsHrphl7a8CIS7fp5831cuctlvYdjWI70/j4Wzhk2Tmk/YqeuxZ8NDf9gtNFNlrRTJkdPLlnP8GzBy68ZzVjKZlAoTvQrNepEhqw6OiXvz5FL0fCJtGupQH9KHU2C0o+Zf1RxNXeNoLO5KzCbhsclsARJu4/Ul6uE/4ZJ/PUyduX26uaUFqvQnjzEzoMmXLWhTSAeJxBoD17IuysEHxRhmjdLC9x7PGC7ULDO5wZ242fw+eo8CUy0l4h5hmYE30NuyElbHtM+AMcfhJgA9yyZHCvbGqc27HapHl5RUlN3VpeUwI+NfVFRTnktLZ77PT3SPJ3/5NIj8uz1EQ7z3GxIora2TQWBh3dmztuvLxnhvfanYo6mPx31JXCN7Kzper6TwpYmeiXbRYQ7tgBU4IKw8+wrwkYf+m1xUvpBD97ZoBQ6a/D7XepZFsxX6n7O6OWqFAWC3iRH5tp1b3kUlSOxV2Z1Fq3ru0D0gEudYzKdgu6Rl4A/C+Qczb2OzC7e897OPbFUtZqtxuSOug2Br5bCR1MmW2bHhJtDanLLFkcXOOdGvh2Z8YUeC/KQiZoE8C78JUpdBf7tlAfkr0g+HwzkmTdmtQt1TjG6Px4kC6ft9tiKXonSdOsLblJVP8ZYfKmFl9ru5j+uJ3PDIClcstebZCTetRycH0ucDHlRqE8UU3MmdGVXcZH8yos//WPXAw8U/JgD+7rhcK11dfu21OM3fBXwG8adi6O+0r30Ou+vVDG2yQZ+EQyQBgcchD3XYbxrULy0Bu6GVTNI/YXc1+/DZfp1HbRYvPPFF4jQSyTi3fqo2fK5zg3gNBJg/r/JNH6H1go5aoduhPjKpA91tbXT22Rg1I6IupYWf2F3N/hYUGo3uigW0Pf1kP2RTdjR0vk5Mza9o74QUXu0Uf/PhfCc3YDu+R8vVqf6/dq9hDs04qjS1PA4pIuOGQZ8OBUjwV+KMDmVYH7AXVpB6Zm636wStuHlHxjnBskL6TfSqHhk7I70/lqm5UuMZ1HV0mFyjKDZXZOtxgMEyctr+z/8oUYGSNg990aJKjmbALhsBRPQMh0VyKfr0bXL7irsVx07s2fqqBdXmN0335lfZl2T/Bj80G91ZAEwltIENmi3/fqbE2AkPR7Ic8pBvdXzoaUJqqhD5xPpDDszo2rMLO3o7Y/gFy9OyTWYHEw6FqXRqjcq1fB6XF73rs+P9f8WUvL9pxIXRaJqDlMCp94peGEPufVPcwXe6/jLnRQUbNP1a4Y0OEIwHURWOongDJxABu7q0jXSyp9iXlq/HDCpspF6BiRBm/N71giNaxL3/2uByOedJGsc3WCNu5LVSCar75eIfwsZbT4wb9+yE2732Iu7DJfylCx+KKu0Vs5VVlJSeui2sfZCbiOM/aDnk11dkhD95p+GqVezfc/m+8dAlpIt1VyeJPek/hcMTjFupvYABCz70+784pwQM5Zciotomj60YxEsPRQasidMuMNWMtZeP+DcMIrgtC2NSucTHofSPQ3QgppHWmbkE3EYRcHJ7jstpTdJgLc20fpyeGn5ApOv7NP3D0bq5bWrSbxHAjYYFuB/jnl1rEAZPTSMX2PJq5wGWioR8w5MmIIzOD+GLK5IOQF6zdt6q+7vTTApaomERCkMX7c7dv6L2Iq2883+4WGGtx6oMUk6GOyULja7VQEjtAwtzqr4SqVOWG2VYONzPhI0w/rHsFUT8Yi+gH2NUe+AsnmfLT7Sl8S+2zsv7qYqcx9PYzhKz27xzTiyLU5zineNIubRaEMqhhujDBhjA45aWdxHsFMXIOjq2T/YoszYC5nDqXDMNvC/ePm3SIbTsGDJCQReI2Uq7wAz2qQjGVLPqO/QKu+Q+aPncobl3OWvfdVf78SsYakVhXltJndLNFX54oZVgof2ouT8YR6PBa3GHsYsQNReWSt59+2jtiZZx8L6emc69Kp27rko3giCEzknhY5ZbdwdGhr04nbpqGyNnsPRmM+wihZalxkHhF05eV7JOpsQ9mWTMq7Ys213ptIvozSL0CnpEJufiIPf5DP9EHjXF3OI+VmXqFLGvE+PnzlzxyADfYWvaibBXgVvKa/EUeI+UncxCU1uL7YSm4r3S2cg1VL4RZvKbo+VdyDIsTWiq9uSHYkSXEATG0EzDSCi2AzmbiNf52pZ3nmQOsm2+5xinTGMbMr8LJhZZv/v8DNfe9KpKmzOVqxqzOZreXjQyxGKFyK5Rp4gJS1iNAViAjQ0kVzQubNkrhoDXY6GXZJV
*/