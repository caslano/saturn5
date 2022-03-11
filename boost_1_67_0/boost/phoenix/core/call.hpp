/*==============================================================================
    Copyright (c) 2005-2010 Joel de Guzman
    Copyright (c) 2011 Thomas Heller

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef BOOST_PHOENIX_CORE_CALL_HPP
#define BOOST_PHOENIX_CORE_CALL_HPP

#include <boost/phoenix/core/limits.hpp>
#include <boost/phoenix/core/environment.hpp>
#include <boost/proto/proto_fwd.hpp>
#include <boost/proto/traits.hpp>
#include <boost/proto/transform/impl.hpp>

#ifndef BOOST_PHOENIX_NO_VARIADIC_CALL
#   include <boost/phoenix/core/detail/index_sequence.hpp>
#endif

namespace boost { namespace phoenix
{
    namespace detail
    {
        template <
            typename Fun
          , typename Expr
          , typename State
          , typename Data
          , long Arity = proto::arity_of<Expr>::value
        >
        struct call_impl;

        template <typename Fun, typename Expr, typename State, typename Data>
        struct call_impl<Fun, Expr, State, Data, 0>
            : proto::transform_impl<Expr, State, Data>
        {
            typedef
                typename boost::phoenix::result_of::context<State, Data>::type
                context_type;

            typedef
                typename boost::result_of<
                    Fun(Expr, context_type)
                >::type
                result_type;

            result_type operator()(
                typename call_impl::expr_param e
              , typename call_impl::state_param s
              , typename call_impl::data_param d
            ) const
            {
                return Fun()(e, boost::phoenix::context(s, d));
            }
        };

#ifdef BOOST_PHOENIX_NO_VARIADIC_CALL
        #include <boost/phoenix/core/detail/cpp03/call.hpp>
#else
        template <typename Fun, typename Expr, typename State, typename Data
                , typename Indices>
        struct call_impl_;

        template <typename Fun, typename Expr, typename State, typename Data
                , std::size_t... Indices>
        struct call_impl_<Fun, Expr, State, Data, index_sequence<Indices...> >
            : proto::transform_impl<Expr, State, Data>
        {
            typedef
                typename boost::phoenix::result_of::context<State, Data>::type
                context_type;
            template <std::size_t Index>
            struct result_of_expr
            {
                typedef
                    typename proto::result_of::child_c<Expr, Index>::type
                    type;
            };
            typedef
                typename boost::result_of<
                    Fun(
                        typename result_of_expr<Indices>::type...
                      , context_type
                    )
                >::type
                result_type;
            result_type operator()(
                typename call_impl_::expr_param e
              , typename call_impl_::state_param s
              , typename call_impl_::data_param d
            ) const
            {
                return
                    Fun()(
                        proto::child_c<Indices>(e)...
                      , boost::phoenix::context(s, d)
                    );
            }
        };

        template <typename Fun, typename Expr, typename State, typename Data, long Arity>
        struct call_impl
            : call_impl_<Fun, Expr, State, Data, typename make_index_sequence<Arity>::type>
        {
        };
#endif
    }

    template <typename Fun, typename Dummy = void>
    struct call
        : proto::transform<call<Fun> >
    {
        template <typename Expr, typename State, typename Data>
        struct impl
            : detail::call_impl<Fun, Expr, State, Data>
        {};
    };
}

    namespace proto
    {
        template <typename Fun, typename Dummy>
        struct is_callable<phoenix::call<Fun, Dummy> > : mpl::true_ {};
    }
}

#endif

/* call.hpp
YJdIWAc5VyJO5rBiUcov4BEDhiQNLqUGrm8+6c14kVX+7I4e5obbbgrCkYJlgOt0tVR6JAd2qHpHF1Dx+wg6sWh6wciJ0dQ/zsRPXsksjNVePlbYfJjJn5fPmo7wqIqqRUELIS31yD9sGrQJwTmhJRDtoRmcf09X5QeqUgT8nwxOYFuL/maFCpS0PPmAswhD1bNcoMtG4OmbLZc5jWmI8GOB5SDOIRAdqVtn3aL8ZS1Nx5w66Nyzwzm1IkbJ5h+TEHOY4r+zfy0VmAvx9QjKp/h2UiS7UwUnrAC2VHkOnmV6UT2Aq1F7WCox7zgh93Db94172T5x2mFHp50VcfcDuaKSXhe/0oDW+/i5fshaCXMDerxl0mV9RWX5U+8WL1fDxuPvk6K9ZP/CQ976YPvndYvHNnODn8WPzRcmAD9ZiraiAM9gJG3gSZZlUcZnbL/R1Ej+wx1QjFqpWWipZklII0LLAbrcDtbhuROwR76zATMGo4BBQfUYNCFArJqprJxdAO7/hIJuvggwNK6kFhHbL4p2YbSW+4ek5AJsffzl/zoOa2CLO3Y20uQ8F05MWkahxf+Sfvh80eHsPafAYRldWi7nPN/MnKMYyy91BhIiPgXe3HGIokeqe1k9Tc6xx778bHruSMUuUkVdRoQN8yqKhIwg9A78dUlsueMyIKkakc1UbW3fiJ1AWn3fNkAcWI7tUUDMZpfxFVp4sIm78u/QbJqSEvCUEi19Kq/0VH28S3ClZ8B8jxkVGno9cFTO+dTgZh8fWyvYq5jmu4GK2LYkCmj97shk/BSRA1luz8ovrtQZM0Stc2AU0nmxgKpK2OD+bliKmwTr0+sxrQvXpLERl9gPtDVJPqJQGLXLm5FkooVz0kq9jc3yO1O97mQ1bPmSSC+kGI1+F6wgBv0YMgoCUmWv7kSlN0xbuW5vr0QTWbppGS6GZaoWYO70MxHOo/gLC1BqXYSBD4GiE6kg1hZW2Fl+6gWGzCvsmgIifuTPlmYcxR/Pp4kd0SsL5YboYBFDfYsWdfmAPwY363HNLUKpDNfDUhsP1IuafJbQhSP3CXjrBeFcYXVhPWweUcCa5pwin8aLugKdRy2Gtj2SnZR9TusJgTqkOcJx6wr71W00e3Xi9SukQoLMfCkQsuCJhf3S4rvIu3oUa+LUx2DxsZas4V2om8vrFZx2iQitNFUDTOJ/uTiORKbKBbk4tMPrT+4Go3LmfILb4aVcZ/cwSBIO6gPADCcZIxsMt5On6MtvelMMSDfwnmFafQPfJa1NuXt8L00afYeudnmzw3msWmdlUy4rwrKJOizWue3JCQspIiVlMKQBSXRmzHom87qdPcBcUUT5m8kly2mtJftPtNtBeIK3DqitPIG5gqPB6vXlgO3gqAorvdyA0DKe1tpTIxp6U+j1oIct+gb0IZz0ap4pVgsRvJUAm/4h1cQzG+G2UTOc8sglr38n1RBaiYhYBRgPDW4jM3hLToDyFcaLQ5/Sj/FnldsCkY4giaTIZAf7ewFLFVnrRK9NSFWEXJfVXdVtLIabGWGD6YP7nsMjvG8gsW19Lq1NXgeYgTSp63xorb4hx6RzP0eMI6NKBoNPltBuPe89oQBwhONTUPrUu3qS8XFGXBm5k7U7Vq4iKd0geMb6P6gNZ414kgIsNjVDeq116z96mz5p965INzVgc4R1lVqJEyr/waEVnIMc9C5tbraJtD8HrBImUrIP8WE8ddFwiWYCOcWQivy6z0hXRH5ZOvTjtpkO00ZCMXs4U7kFo/H7alPyH94FUgtQZhC1Ad9soRVhJCvUChS6sctzslAU2FKcQLekgqXEFX5CjWMuhnGScPK7iSqa8zZbl48dk5fDxSSLZToWvQzj99tHd1SbtxFH7sgJYFDE7cznsluaoYgDakkxtMJ7dMrucAA9puVmnmowDIw84h4ZslmLUJHjBJRxA0ghSChx5sN4pDy+9nNk9gB7iKzI6/qqj6cGJbuFbyKAj9Q+kqt4Fhre8OFmmYpYG3zR7WKANZJaznGsZ6b95/RCAyhdU7L94T4F5ROlmtYwfaDhVq6fTTriM9OJFy3U+0eoR0mV1OnJ2xoQGjWqqYDPtEUmtRlvmmkVutejLwEU+ijLAzTVx1gWUy4KY+yZBAkjtN2sHw79xzXMUU+YI0qmD1m19gb9MHKEGnq9Q3Xqy2VUSseYQlqNOCugQbxybS2IdOvZUTvDjwV+1ujGA8d4RF/+vpxJwhuNDq9bqaZy5UtmVu3v1iBUgt+Dv34Qyxikz81GkKrJbLFzTVAUTrxwLFevFgwJPFzTvJ4xmCPnNUDBNrS0/G1zIFVwmardbqjfG/jF6IXj+D0lVRrKRB8RBgRSSQGqMbLkLvNhfcoizC3tbOqBGg0UbBHAd8waGzyxzKzr7Xovw98zuJzjd+f0AUL85TcDpsOmoFzBiaqZNUh+9GnoCOzysGO0rGTzpmVxN8IzsP4VC/CgkFZ/4bnvpoh/mrOmNfKZNX7rC2sazqgP/pcre8DqKZe77HSrGdJm7l0p0LPaWRzIKBd4/GJf64WVNmEf7xXHgWw/BW5H4O01iGbuPIBZogbh7n7Lq2fuZf/YMDknoOAwOWeggKJhG/uJorX1gmGio2cEE+8SmT5wS+rD3U/T2mgMZXhYIPF6tidi7JlUA3Kg4lPhp/2TdX/YuWi7RingdgL+iNrQU2ic8C01Ntaf91pVWRCc57gVUWpBAHmeCResQ4blW+BTyCqd5DkBmvOQRTe08Xvr5hYC9OfShk7nIEvUcC3DwubwRmjHGooVOhisuFB1fn5zSXlZCbN740x0osP3hpLshG4xBOFklRfMpZUeA9X22WD1o7uPGLaBx3nLeOpjtP8mbdrIL1v+4fXmVcDX5FmAo0bVZsSE2ZrBvW9HK3osxAaTFsrHmKAy/9a0RKOyBYGtagISd8WjnnejK7GDcUXtk/0gQ9fkOS/H7sX4dxkRuGyZ0iZMV5jQZiZobP4YZnY7AWc2PETQwwsW0JGtpbOHXc2IUn3nnOHhc0FuYZw2uHBiAUuoRxla4GPrlYbzdozYwc6NA9ujg6ueTVyWRbjSDIm7GXg1768wAM4cK+lsDK5nBSmbNV9CY2atZxRDwDcEMuCgJPOY4iDsVK//wY9MksUH8g4+eyfFl3HOvhRkuYchd2/gMeV0ivmgMftKcwlnXAa/Wy3zhva78Tpg88rlUrGIj91PAVqXTxtzFLikWKLvRunpQd8+pvi+ZbPa4gOfpMQiyL15+cBq+vPCIBV1JODa07MU8mOKYTZtcoohffFX3cKfV3Mr72jbE7hrpz0kBiL0G0We3XtapdMQ0Hgsfway8YpjcWPg5wSrl3W9VQKh745tGtjGM2Md0+mfnhWe1B17TiYBJ+nwNyS5E6ryyanEpmHi6p+hipW4z/csa5ckYmcRtzHUsEd4/D1vL203ZLNKu5kdQDpTc0xA7pECi9uzATGBkqlPKjqj6rRLd1wssh07wachWeeuPj1AOzSjK3C93qiUHZ8M0HUSlyNpyHOm+gvDllmQ3ibuT+wA71RAFrCF5xl+a/hITQRGZ0mAZ246401Tev0ddlBPcBBtM5dg2l6cdPDhn8IOxEpDHfSvGaANQIvtk2gDwc47ga+nL6p+pZxDMQsB0Hi4Z8Bhapuz3bwm+CrAsnKaz4PjwHlaD5ODle9kKXNuZjKc7fGMXPVenZlpvacZxKdPQ5Y0MOwe/jOmBTsFeGOzsHN2gxWqwYgcShdpUdkTY2vchBI+T/31JPRMKKCn8qovCILGW8Uoxfp+BOVZKN5gmYwb/mMXwJ1pE68OV8gDzQzcD91T5lMVYx2lGUXsb5WtrBmESurKudI6zaVN7u42ZuPY92flNl1cYe4Rfmm4tkN7SFlbQAZtnOX0Y1CTHCbjkSD5jg4Id1yzPYG3rpUf9qPj+NlI+p5FjHWcW+6QN6UrlbHVp9x840vfQDLGfiG8bddwRNNOnu3ToFzup7tSexHGYSGN8lwjdiq0QjedbDhrY8PMvIx6M3xp13O3DJLh7ggKoOByp2Rv6JKxrdw6vSEl/byId75W+cwewMUEGjRSUfcirBiEGsZxX+CJ1ZFjr+Fxw57gG9qpo+O3Zl91l60ELB3p8r2l3tBen+MkvWC9FhoWjUJBDq67W5jYl+7zXogw7U7y9uUX+m1gTKkYSGHThEJ2yYTHyufDtMKhFBDS8VPpiyufDKb3XD+eMXicqo8EwyrkYx2K6A2ynmE2xzH1etUyyRh7+xoHgNog8x5gA+YuBiicFJg5Iqy7oGbKOzcfMa6GZY1OLB1Ivkxqdj/i4443XX3FakrU91p9wBZUNAsBp/ZVzRbtS2/ON/zUT6zWQ0IuBopi5udpV2qEG623rWrSwpv7OSJTzj+1Dajj6z4pMbJV/VaGC9WklJSpRNbI9rYytxMLR6wjNJQL5jaVfz61/m0KNdmfjwvQTjJBgsywXqEe42FaBxwx9FqB/tjSubqx4zK9NUdZnlslZ7tvKHXD+61dcbACHL4yo4JPhpylQewgcxfDtyG92rJcYtDJ8PQFe6Noq6lL7htJm4ABGKiG6eMTOJ4xhBsxfYBqu2ZXgUROcIHIYegVtctdzH+hB+XNpMm+GBoJnLO19wQssdfVUGiqDpxnKVH3njubOMMP8xmRXKnH3mictvo/UQ7KZE7KeGfW19SnVeV5nyrH3zg8ptMtC6MmBj+mW6utAH3NfhVMEQ8Kfrg0GGCgvJBVmZLr6Ghczitq9hUXT/kZNiQOoG+4ca5hwRsuWyU3s9IJA8YdtyMNzmA4z+hpO0K+ogPg8IHequmLNAD14h/RoS8bQLOk7hcOXsmDcOS22C/KWLYtwrT7HS+4xNQccaFx2mxPufvs5KDh0oT6/UPqzUM9eEdAGEjc9HYdYXI9OIwhmAmPCe4o/ZdJupEFUNCh9WeTk52ZdlPRBnem2CQ0+2gt7OEEHpNUhUpzYv+KdM27QtHw8lQ0jNd8ZgQZBDBn3RCBo8MJFXZ4rVyMj6RSnPebkarIN4t7LVycd5uS6AsVe22mnjT2ILcNr+nzw6yuC3vQaacjt/wVNRAvvtEvMKoJFIRpGkCTjJ1iNrLh288FjaJJPyzGkDBewFsGViw0KpUley9iaG1LS21q/2RRuylD0iLmtKyMKqxkTqnIESWUvrm+0K+lDOrE8EVxcoLebQFQwCFMGwEOgrJ2+Cce33As9JJgcseUNtU7m2Xjgx5vTW4QiS65HdHdhAB6Ukn27b78YWZpGJYjja05oGbvViV/ZKTSEfaVa9eCv/eQDgmT/ARtWJZ1WHemOQ3NXEX0pokO5K253jgqhJTb/K6cSB1Wsx9bQpCQ0JS3469HrmURIMAWwzDLPjNrQU3EM5Yq34NPyE97hAM8zrkXGqtK6uKxiCjaOOxeoOLo1pQBz4geqwJKvvbBm+DHjEbAVM3gMKAabKEcOEi3zkmyBSdFt9877JZmHjdkycA5NZzZjlHwUNP62HXlH1i1LmPpmp5hjSxpg5fEUdSdnpBW8Eo9zNd/MNv50i81VjBmHWujFOgYWypacYR/YN2aSkpadopZzrcFrnCXNZBmHdTzH4dBx6dA129+5sco9e431soyaKVsdO4NP5DsdB34KjsivFfAm1xUVgESvuIKY6lZjKq3DjkwKl2aaMN+ZmAWmbS+OTXhaBrSW9goIkMK8RxyWDd4NtO4z4zACQtPMQFmuLnSu3DGaJ6v9xvUUw99oUQkNMfLHCc149CgG83ROq1LPUG5lGQPyJVeELl6Ga7zTOioE5Z9MtIlgL9GuZ4rdiPAjBRn8d6h6WpV9bABsWehPt9KNlJVevTtRpm2JkpZ0Df9EojyiZSFFv6NltYFmAD/SdXAld6ou2hf5J5jSrXmCJEGnXtkslrPyPgjLatqu9y1h1LriUPOF6WdOn8tprH5gTBMoyCyvE2bI1GI7jK0tutKPCnF+4XjHUVIdRus9z28qXRvG8BFVhyd5pklxIRsnHguPUzeu0p6yqTTGCFljcOMwCS+IwQizEuPwIR/7fn2jqNUIdOyfkR1PlSju2ct5knZ5jMiqfYJKXiW6XOFRyd5OUEkikNzgRPW8FG9OHEAqU0c2gb2EeTjZ9yf4MVa+iDb/q33XqIIYnspv30kidbl3CM/zBPeOV35ehF3LnWeWWR5JWwbj2k15DklHOiQxRCB47UT1DoQXCW4dLcY1WemQoZYTJH3yMJnbrG8qDz0DQo2IaUHpx6JgjGmKE1ukD/h7LXxVfZKkzFZ/zjThoIwNSvB7eoPqS4UasZjI9TUhgV667gM5cZj4lK/k6yM1mB/6ait3YbEz4UTqPdiQwEN2yQOIBMrSqLj93MK0hVx08bBv6D2V1oAOj442tPCAUox0McDAlYMQOpOG//RTQCXtpTjjgimpwCyowq0ti4TQbqiOQO3D9QwdWmHznRskhT6kofJKmY7avNQoslhkDU83JA8mkpZO5/bWMdK6eSCE1vf2oJW+2j4H33O3TzgLYvxVQooOsDu2OGi96u49YD1GnQ+vwcIvgw3esT1PpszeQBmLRidJ22mHg2Kp2Ukt+3+0bNU1kWfZQmgAsdqNOnz5S1NR/hK/gABs6BGhZjzlJ6zMMtD9RONwT/jB1zv7O1rvjLK62kBb5N/+rAzxpkh+eRPuB3g5xJtfbH6otAGrBaI66eD0OGwtXkM0LPYGTTt52vKT2mRYJan46pndgzMjItvOTaQ7hotFRN/86Ji1pPM85AX/95i50DjOboRiW7cLcpkKCYZhZJdpsGgwq9sAlPWBqrPkPBmQU4G9kwSPIO1LPt2H3x7Ns5uYDwGlxfQTrPYy7YongMeC8BIYERFarCAAaoej2EheUkUivRy2oDONzaaJm42PAe456ahddzqYho6edfpRdSoO3e8qCRWUD0yQVxgioPGNXW+L5HP66QxiXdo8Qa8sEVZKlTHkKz8o0TjLzDW47Neab7EORbh+qD1POYYWpGK/wSluMvRN9YHVrBuIurYkE3FICAuXot2Ai/fBnDMQ/q7lAleeUQ+/TrWj8VeSN9d3VbqqOVnguKviuCzv3GNiaGZELhy4+KoQs+CFyupQTFY40XWVBM70uJPxTS6zqnrX16BE+TdgZTW6tjKdtCVJoKcK/N6IGsoyB1OXoWDOXF3LWRl+uwI6iPhja+hjUkwz9jUHiQ2M3/OQNAlVHzlBP8ejd7yDVDbt7s21SIGS0NGThWtTdGoCmnnh7Ttrov6By95D06fjSOr99Ass0R0wd2gKia7zQrLsn/z76hUI4HLQbWAhragNxT1BSSekZlE73HNdvgIXJ0KkG0ZgjmEDsCh+V0Yq1RR461HkNjJHQofJsl82QXRNp5ZN1/GDvy/wI39aP27M6I785rE2zdrFVzTIxanQS9ktWcDDAGgHaJFW9M2MUKdABmVaT729kpq8NogMVQrvdSAfXCpTxY+t5wyUoUplBo/YvT2nAb0E7INDpMLP0px+2i3isrBLjilT3hAMHNOQYIJpNFLZYIPxMgzcqrvfmdgVHwNYPl7oqGaFXpe8LZLjqie3rtZiRUI7oisszehqL0tOlQaoZ1Vd6RAe89LrY5c7dRqiuOvOaLXkuJJw3XthTfAj66gBh2QozkmalBOnK9eEdwpvbuUU3AVB96UYwPIgPErLvekWBLsOaM+1SVVjVVz3xO34cONVm3C6h1/OeJvjli9r6DAk2K0s1oMTtaSERW10rQ3GpEPZwNVfMoq0imM+o2+ND1kHWfyC3PqcMkRf+AalExsu81Da5eniPjjJndIJIw9sxfFKiYP4LOQLXAEawmbRdacRKRN8NlmObbXBh+Re2O9fDeY/GTYLgQ6A2G5DJKHA3VUQjfBT/NLcCZeHXgnMIqfxaJ7oSIP5TUpm1iF+OLLQzQyTgyfEibJNccXRti4ZHjS8RGkvHKHUrhtsDocugkP+xs2IAbhjW9LEmv/unmhc4YOGQNbu2gE0u8UKK50DBlqvilT5Ye5qrJOkWPG5DWQekpFvRzJczzFic0+Z4lyzrZub3E/D9a55JndsQoKM6zGrjfmnN33lpe/48mXRSgD5w4uhYM2bz9arD89aq1AK9UGF8taui9d7qxVmk+61RvsPusm9L4d1wA06+84K+zDTuZ6XvePh6WjTr2hdysTjGryIbLO9/ORhvB0xu/chz2ccuksowaqgJRWf6ORDVpxZvJXrEq6ITsJSO8kY8gFotvJxn266EiZIxssw3IMx6UU09f41vU0qykvDub11TVdO8YqQqNzhDyiG7D2ezsX2zrJsksuvwnqqij35jEEbxjanjrpITZdnbGufK4YL9PDRux0e3Pc/Ov4OxLfmhJHUy5VhMA0VpMHxDR4+1WijJp+9NKPmEycO9OulZHv2AgKZXzN8Tj9xqLyydzB/tBelyZclWZuTWRO6rTNxsJgNJ5dBaRMBAUUh9PFS+UaWXe/mAuDxw8rNudivGw+2X/LpoNfu0tevkOU3jAZ1YLCz9pubuZ7Wzla8uqHjrjhTaL0uP3QfXQRiky8sxXSh+3ueXzRo/QNlECUEP5xisb3xMhA02sIpSXxTLd7+1Jfe9ix1GLtkH/+JPN0rnE8nnvIgN3fhgz6GImy96UdjulTrejrZXxnEzReO7uPQs5cBAZriXvbCL49Br+FY0P4q2ymN1Dla6Lusqn5Qjdh9m2Sh+FQ8wCuMUSyYlwndq5f8DxEWKvtEb9V3ZspC4LDzgmirHwNFSm1GJVjWxToniKNzHUTpp27L95zXmRBHp0kp4ufDIUyzcL2IUX2vlXNsiuzf6H44BMUPMxzPnDR0mRPfKed1425j1Xc7SymmBt1SUkNdiHufWFIimX2AJb3J5lC7JAtOgnZOazCWMi4lQZrpvDrKTrxGDLOuTkiIHS2LUaC4enpn8iyW4iLL2yibqirkvv2eVne/N5W1onQhsMKu6shuWQIc0oTNK6u/kh2R6l7UUBLsFyPJwscuXvU0skVap6PKK55lpS0YzbhVOL1sHQE7Db6kb5byKVeVoUViIGlbq4l9nQ2V0ufWBP6OAHCzcgj6pTj19JDSAKp5QfdZcG/HNZR73GnNba/hC8e33mTpbUER2eZ65k/YD4pzy+zcw/myF/wT4FskmVnE2M9DUVrvtOAMj0=
*/