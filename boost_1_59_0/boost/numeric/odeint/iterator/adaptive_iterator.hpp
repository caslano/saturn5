
/*
 [auto_generated]
 boost/numeric/odeint/iterator/adaptive_iterator.hpp

 [begin_description]
 Iterator for iterating throught the solution of an ODE with adaptive step size. The dereferenced types containes also the time.
 [end_description]

 Copyright 2012-2013 Karsten Ahnert
 Copyright 2012 Mario Mulansky

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */


#ifndef BOOST_NUMERIC_ODEINT_ITERATOR_ADAPTIVE_ITERATOR_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_ITERATOR_ADAPTIVE_ITERATOR_HPP_INCLUDED

#include <boost/numeric/odeint/util/stepper_traits.hpp>
#include <boost/numeric/odeint/util/unit_helper.hpp>
#include <boost/numeric/odeint/stepper/stepper_categories.hpp>
#include <boost/numeric/odeint/stepper/controlled_step_result.hpp>
#include <boost/numeric/odeint/iterator/impl/adaptive_iterator_impl.hpp>

namespace boost {
namespace numeric {
namespace odeint {

    /* use the adaptive_iterator_impl with the right tags */
    template< class Stepper , class System , class State
#ifndef DOXYGEN_SKIP
        , class StepperTag = typename base_tag< typename traits::stepper_category< Stepper >::type >::type
#endif
    >
    class adaptive_iterator : public adaptive_iterator_impl<
            adaptive_iterator< Stepper , System , State , StepperTag > ,
            Stepper , System , State , detail::ode_state_iterator_tag , StepperTag
        >
    {
        typedef typename traits::time_type< Stepper >::type time_type;
        typedef adaptive_iterator< Stepper , System , State , StepperTag > iterator_type;

    public:
        adaptive_iterator( Stepper stepper , System sys , State &s , time_type t_start , time_type t_end , time_type dt )
            : adaptive_iterator_impl< iterator_type , Stepper , System , State , detail::ode_state_iterator_tag , StepperTag >( stepper , sys , s , t_start , t_end , dt )
        {}

        adaptive_iterator( Stepper stepper , System sys , State &s )
            : adaptive_iterator_impl< iterator_type , Stepper , System , State , detail::ode_state_iterator_tag , StepperTag >( stepper , sys , s )
        {}
    };




    template< class Stepper , class System , class State >
    adaptive_iterator< Stepper , System , State > make_adaptive_iterator_begin(
        Stepper stepper ,
        System system , 
        State &x ,
        typename traits::time_type< Stepper >::type t_start ,
        typename traits::time_type< Stepper >::type t_end ,
        typename traits::time_type< Stepper >::type dt )
    {
        return adaptive_iterator< Stepper , System , State >( stepper , system , x , t_start , t_end , dt );
    }


    template< class Stepper , class System , class State >
    adaptive_iterator< Stepper , System , State > make_adaptive_iterator_end(
        Stepper stepper ,
        System system , 
        State &x )
    {
        return adaptive_iterator< Stepper , System , State >( stepper , system , x );
    }


    template< class Stepper , class System , class State >
    std::pair< adaptive_iterator< Stepper , System , State > , adaptive_iterator< Stepper , System , State > >
    make_adaptive_range(
        Stepper stepper ,
        System system , 
        State &x ,
        typename traits::time_type< Stepper >::type t_start ,
        typename traits::time_type< Stepper >::type t_end ,
        typename traits::time_type< Stepper >::type dt )
    {
        return std::make_pair(
            adaptive_iterator< Stepper , System , State >( stepper , system , x , t_start , t_end , dt ) ,
            adaptive_iterator< Stepper , System , State >( stepper , system , x )
            );
    }

    /**
     * \class adaptive_iterator
     *
     * \brief ODE Iterator with adaptive step size. The value type of this iterator is the state type of the stepper.
     *
     * Implements an iterator representing the solution of an ODE from t_start
     * to t_end evaluated at steps with an adaptive step size dt.
     * After each iteration the iterator dereferences to the state x at the next
     * time t+dt where dt is controlled by the stepper.
     * This iterator can be used with ControlledSteppers and
     * DenseOutputSteppers and it always makes use of the all the given steppers
     * capabilities. A for_each over such an iterator range behaves similar to
     * the integrate_adaptive routine.
     *
     * adaptive_iterator is a model of single-pass iterator.
     *
     * The value type of this iterator is the state type of the stepper. Hence one can only access the state and not the current time.
     *
     * \tparam Stepper The stepper type which should be used during the iteration.
     * \tparam System The type of the system function (ODE) which should be solved.
     * \tparam State The state type of the ODE.
     */






    /**
     * \fn make_adaptive_iterator_begin( Stepper stepper , System system , State &x ,
        typename traits::time_type< Stepper >::type t_start ,
        typename traits::time_type< Stepper >::type t_end ,
        typename traits::time_type< Stepper >::type dt )
     *
     * \brief Factory function for adaptive_iterator. Constructs a begin iterator.
     *
     * \param stepper The stepper to use during the iteration.
     * \param system The system function (ODE) to solve.
     * \param x The initial state.
     * \param t_start The initial time.
     * \param t_end The end time, at which the iteration should stop.
     * \param dt The initial time step.
     * \returns The adaptive iterator.
     */


    /**
     * \fn make_adaptive_iterator_end( Stepper stepper , System system , State &x )
     * \brief Factory function for adaptive_iterator. Constructs a end iterator.
     *
     * \param stepper The stepper to use during the iteration.
     * \param system The system function (ODE) to solve.
     * \param x The initial state.
     * \returns The adaptive iterator.
     */


    /**
     * \fn make_adaptive_range( Stepper stepper , System system , State &x ,
        typename traits::time_type< Stepper >::type t_start ,
        typename traits::time_type< Stepper >::type t_end ,
        typename traits::time_type< Stepper >::type dt )
     *
     * \brief Factory function to construct a single pass range of adaptive iterators. A range is here a pair of adaptive_iterator.
     *
     * \param stepper The stepper to use during the iteration.
     * \param system The system function (ODE) to solve.
     * \param x The initial state.
     * \param t_start The initial time.
     * \param t_end The end time, at which the iteration should stop.
     * \param dt The initial time step.
     * \returns The adaptive range.
     */






} // namespace odeint
} // namespace numeric
} // namespace boost



#endif // BOOST_NUMERIC_ODEINT_ITERATOR_ADAPTIVE_ITERATOR_HPP_INCLUDED

/* adaptive_iterator.hpp
BRL7bPDrsO8tA8n1K4oB8JeYnIqGDFRbwBeEqunnPGO4YVnRFWDcOXidDvyGk/Efvxjr6An1NHaVEWNtMwnMci4Z6uKrqufNdtqmH0hXIGfB3L6BcthX3N/3Zus1Z9UhprycBLXLfl5cMQwAtUpHIfhOxrjraYzkMguRumux9fcHSzPvKALjgNFIp5vHH2jdg5gLxYXlmWPGG5F9tHATvFBKCeVS4An6sF//0rMpV7QmU+zqFjDKhTCKwVVcO2IsmRNaeM8uGusZsXQLjQ2nDKhcBoO3spcrzrdXTgOIxmDqUJlWZU7oFvsnnZlgdgJedclcpVmO5k82AAnPUlQlTfzBXVmAQEoCJhmzS5OI67WHPRrwcJZWdgJ31StaxPaapWao9Z58iXIgrpI81n0Njtf/V1rHxOy5tnbUb1Dj5x1+PYg3NMNRFYWwa0lNebirvm96phhwyqP47en3onVPMFWkjij1icdcsjHBki5u9C+Q5wFT04GWpxGuT0riRqHnM0Ugc8xRXxTueA7Zl1wdyGSfjipzbVc4lDsoVoEicFqA6lz6iJJmlKo7At4fHiFzth0lUt3H/WF4Tc7Y14dmbHzcFfqj2yroZb9U5+uNv6h2rLdq7r2ROtp+aLmk69UZYBruhD1ch8PHsM+vWLjTGrtov2mvfHgb2Ly6Km+hrU3r2I4kFejjUQVVk60ZzIRPIBkt71lFxrleNsZKjuL4tJUURUv3sgVsMia4IZ4uJRXGyNdj+QvrPYcxyts8GfCUVNPr6go+DvBTuog/rv2rGBze+IEug2c2jhG3Jz+ckJQ9fl4Twh2bAcYmPLkUybpFmUX7QTTtiO9MtWkDSIYEWj5KSYpDAtU+kXlNRgyIkOYgSGEj5u2hx4GvIGAA0VZOMkGF4VmirAE2ajdUDoJiB5fdM0ld0LfuvAHJ5Ap+A6jh24W6plI3oq+iZh8mOXqtDGeYlaZ1AP/4hH6Q6Wtw0i0UN79Ak59C1ueq6lZgKAOOt+vuxl+Q8BpyOJcfSeQOV3wFQnVuaHY590f4c+RB8jnY+cfhkE/w7CsFzTLBA2QsQV2gYhhahuHShX5/Uhr19YLwsxnKt3pET+6VNFpPvtdq/2UidcXQRoe+CPZ51qaQGauwkCknBqWkAGfbzGL2Y4KVyulqjiBJ8nik73XKHqVp1qCRymQ0zIIGOqoXFcmks74IJceqcp7J9il2np4bv5/31BVShAa4sV/N/R30kvkyV4npiQ7TE5ypUDUjCL9IEvXxg/C9O8KntmSXoyB5gQRrZJkBZmUjKe59y2dhVbDzz6HCmJm44Vrj5hwpTUWevpvAotJzKX8r/6n/SH7WRjgEXjzY8pUg4kDsO6bPmj6CFKM7O1mrx0b2oQH9erAcnAgxFfSeLMBvZcmURpaD63hT9PAJeK9Yy+MNKXvxHoDp3xl5fK2a/FtHGJH8Pa4BCGHD9epJiTBkyIN09akGAHf8Yc0F5xrm29qomAp42Ig56mH9fI84vZFQ22uX7a/EN0dxlzarpB/VMUHJosQd5yz0QZ9YAV33wnciabWMaNHfiJ9pkevE37jqol+E4Q+RUxQcDAdN5B/FPtAERKaHEV0nnttvgrzB0EzG1N6j5Q/Ag6makO1fFTy8ODx8qDx8kBm4E/QNaua2B4aPFYMvDA/97t/zVOZO+Fp7GdP9/oclSx9a5itV5zNocq6X+9l5+n4TU4F/+rL1QW/lSzjLzkJaImA1sZzrVf5esxWHhf5Bwe2VMH2h5/hzfGRV9ad6fNtcoWfn7phgXlP4r74lw+pJrg8mhnWsf6kh87R5cr6WNY3jHqVg+x/XISS7uTdxMPbz+qyUqbrRmgXpStiE5bHLMzhxyEbst3Ss7TWNInL0WeDXPywKkfzXb0x5E+ZnQm7f6WlypVQP03BqNk1N0qo+2l0756H5mJ70VG38cREfjrnCfpywlyouzJ170gONBWgrEyJJlsKh7t3GNsZFLR/lVzKm7MrmTRjgPpYn+h5JaKB+ZCWDSC7qJhDL/MCCL7w8rGXnk9t92CvJZhLH3nO34OvPMM/RLQYY9vSqG+KwmeOySDnMQoN3qRZriJYYVD6zjh0bWOAgKlOGzyjm5EsiVACmiP3Y53QzNNVL63nfCsvmocT5xPEo1gTaH8G9wfo5lI9132FvO61mskE9T8EyBFEZri9R5bP5JbZT0H9uV69m3TggW466TwUJAJUlYFPjyvmuZgUbuIrfPOnF7v/S8zazTvWmG1koMIgJJAPyutgNSp4ErTHq0l5douTpuOuN4TVorZMazvX5R7hv09/3dQi+SLRdEvaHpDs1PgGNxMODeZeXn38QQMqHxqlXjMVSYc1qd7OOMjnZC2GOpPdDwc1GVPmRdnwRVyYYf3lkq0sFHQnbIwIOS9cfR5Sr2LcymXXgtT9blb/OWC2tcJH1SAj6cm6NCSltiowxFGqte5bqYgw1DulTcHbJ79Tup8IysqrpaSO2CecfHR3okvrCDeAT8trxYS1gcy0wupACdqq3+xiQVFFpFkINTWp15AtABl/7A+mliqGuoasKkK+6CgJi50brHps7+TObuYiizK3iKOcJ/KkLLi2ECtLfrKSZAPXxcdGW2XNwq9F48wWc7fkj6GaqehUVcpJjxXLr1Uti2TRSBgQw271qvvfm4OTf08xduN9+gwXLkz0P2nGoFxFU2rXv1yLdWAidFWVJKLhzsOxiYe3kr6MIinT8XrhB520dSaWArUoguTNXdbWQcwokXjiiH9eateRioePkH1GGJjb2RLtBNx1Lx0Bf0SfhPohpk0omij4WTsUgtbNQcYVk+UIEVSSGyrCCc9EGdqdpsy97EefW/f2cf8eVoPvJBNRbC9A9Kp7vCnOJl1kLz1mjxYjR6wpoA+t/tgXUfd5GznH5aQ5Sy9nCLRNt8CWeOhfleWjzjpE/6I4evpuGx6fnOGtevRmLaHz7GgoC7qDkoMSbMcpBTRvXj75b0lezYcFvyXnNaWNpboxufNgxEpt41NFGR2yrZ8ZTqgPfUBxyOYxZF04v533LElI90yNWE32DC67DKO1WXtesc2n45iF5actbk/ZSbBBXb+0kAajt70/Lakq/zHwn81wgMx5zp9mAXiw9rBP3lLjKaKUK9GJF7NJnq+do4J5L0DZSpwyPN1pyNG0/bQTS/zKYAY05j9+gtD+4zYruUMCPQdYXikNxJ7oEDvp+2Vnxb8Djk0HwIZ8C9iochYevCae16UOMoTMAHfSG1U5tegdcO1JlKwDRc6LT3wL4G5FALbKh1xP/uowyu9pKnDj0mGUM++tpbuYJJ6VjJIOKGU5qZ40HKoO1/eXpwMTejIikD3gSVPA1042tf2mvOPAe4UK1RLylYsqvSj093i03cSoe6oA8qUwqHLzKj+mtRD1Ggxo0829VJ5WOXXSqcopTS4oKlMFiitxdWacUokzzkaKvUya6abfMbAUs/nPfEUt49RYmfTCZmL1BTHj+332XelBhdshTBpFLv7OOr2aW/cED23+pFR1J2HrCZ8moGA3IiEQH6Tw/HfHWPYyePXy11R5chiL+9bim3QC3BzIX6FcYFeDfB7CtdSL3BpubCvYnlRYD64dTtVnuyVSyU7YLqBhzw2rMKgneIup5vi9APS1dH9HXAdfCXdKwVTLFArcHexMGNXx7m+mVepom+nS9TRNh+cUA0NVYq/nkgAVsLBt60erDSd3ZWeFFhXvLP7GVkguKW1fWx3RQPihSODix0XLuEzKwoes7rh93hqbbnRhxfyYAU5zP8j5OXZi5bHbSw4zvyvkKYuSbFZp4OhF9YEj9U+JEgWpOMB/0g7EqyDvMOOxpO0c6zKoKQhGvv7zdlmeSNXYeEsCFGw3cqIGx/xp/gI7TrL6Oi2hS2+kJmkDySnbngh1lQOnTx2jbf/jeeWMREPJEHx3GV5kacf3NWl4ql++nvxDWs1ws5HIbvuL1PlgE6Jv4AgsW7tecTmzn5ahklINb33d81yOxOO1lRPMtZIvo9Jvk0F50DbqkmpaAaGsKRFLkCktQKxzgemSEv1wLiXHDw+UURPrwqyKB5pAc9k5jaTGEHp6vlheY3+zT9Ib8uzBdr0CoXLxc8SnytXUibdy6j8M9lx3o9HTir78m0cTC4gguUewnRUnoJF+cU+IIj7A2m2vijUcBfD0f9Q3mYi0L/Zch4sAPyyiaEET+uN+Mnvimjj4kc0QYJ2XXzJAqLApAcYmy35LlVriW28Own0HUDj9DV0LT8LflqgMVc0HVKhGHbGmb/WNx9y+CckZlCV2RQ9QMaJ5GrbcQQqKOU52Fe7rKRyveQz5QtViKzIUClSqqqFngULW/R75mdFZ76egoZcAWeDg4nTD1e7Z4jwk9eoZmQTna4CmS4o1Pho7tvcZMS00BSJNC0qXwL88xcz2smpTuWCRzsjyHU7IpVfTUkFlDEOdjcX+6tn5fuhOGBZmnPZmv49cJIKzrrXRZoAdEXfUu1GAyzIxTC2i+X3yfoQCqp/FenqAKZhaxlK+DyaNEfzIHrHj6VsBq86UY9XSd4XoCWOUijflr4+Shsp13AftRGm3vsFYOW9GxIyZ38FzGxzFC29PKOFHHwcc2xwGfZ3ImeRD5oT053JFklAM88P5iwOB8AtDSBAFlXETUEL6cvyhL+Ch0GYm3wx7v5FnCrZgJJ92+ttpIfgMIK55Y1vmad2quzDIyGVUh3yuT3zy1ybw5bJf6IgtvDpEJ9bWHkz0Err/zEbhLJ3a0jjp/JVlJ3NuH/C1qalb9mKXwi0+cKXxJMcr8Rib0jUZuMZ/spOMMJn4kCUAKb2OlhI7gfeIrRCRz26SckappxEOakD2eMuPMYdUS0+M9C0nM3Rci6usZXEc+S5MpJJf7GbQ3AnNFLTSRqCYC5UiZE1i8JzlRq8W6UnKU6Di4TnL8yd/Ba/hng5dQHjJThtR1rANRpTB0SVJdku4hwK2we0EjGhwZ9DCLrghekzQQO6+VsF7fvzlBQYWz7DnLMEVGDQLjHjJoH1upQDPD15iTuSK4anA24LHR0Pk2mFwSrJsMzjGywiQow6DpXuMCP1emUfL1h+gWQOWuB9r/ONQnomuWsHXOekCkBhAgJlDGYk+iDfHFybUBTYpX0jal0QssJlxZrpwpIQ8N8+U77IY/HlCvyMchPg6cKqvFxQ3emOZaJ8L9sBBXHLfcuTPbB8D0lb/bTAn0VblyJQ4RhbMs4jD/ptaQSqsQczvhx5sR/bsVlUltvRQZxQzVKVzPD36EhWy7IXOfzFHwaIv6G9B1DCAf2jHA7ceNYMcXhoiubpfIKcrJSSZjPHedZQ6NlKI0qlAkqqg7G5Y2pWNkCLxqOixLQhYNNAN5XuCGuisdFh4ZeMqbUwEr7fF3vwwRmHzuHmGV5hqgNEm88+nThfiPt3tMpiVjD4HuiU1Irz9apcOo7BcDt6ukW0Lwg+OMiieUtzXuRmC2E53Z06sf6a0anew6j4ajSHDYa9tuhVYgAm4XgCQGg8YyW265n3UViY4PEv5cJZLzpHcZZ/pzwPDSuSZyi+aRjxVXRi/HTUDJGnO5rArTlmnUiJ+lMF2zpOyVpwXGw9bf/DaOhSN3kI+AZLSvzWSViHYwdU3sy2P/f3b0rWx6ksFpVnbBOGuRgd1V3eizujsZ32zBKESxlSChrbUQcH/hbQExbKQ7T7Ic4TYZksGJu1OO+Y1Vi0S7GT6Y8Uubx3cMqidwf1bw9b1zHGv49xWLGxi/LgA6+rE/ONhjyofjVDbO8D12AIlWK5lj4PN7RK7AqzW9Fc/tPvy3zSt8weuD6KETS+N11e5Su18H2MGUr2rt40plm2eNDrBNHWYSL32M4N3RypPnqIBEgajTwVLVEjS/gmHzTyH63m8vBCbUJIKCRz4Frrd23CpJTJPydoVfH1+V2/ZLwdg/z0sDMjudyYJRQ5pQ+5seOy0Ge9F3r9xEWCuLwqbcCO/opEQGwC1ufTaVs6jTQGRHk0uHkkt3NHLgNrkzk4YZSCqo42UzIlIR5Pdt3F9Gu69HctelkoW/ZxX0KQsVxkyPiQ9PeBIM7aHM8nkAT2RhWgk8LcP6aeXIO+IRTe0yyYG8O2mBK15kiycnyzOyzRSu9ZSuLeIyL2Y9kqPnqiwzoa3jzzUg/KyyfVgQLqYMqPq4mIPE/gSJKUNGOyBEa1Pm/y1/pM3uMUGISK8m6adu9UGyisyNeOfUgnC9rVDFnhMINcYPk/yze5T05MJj4Zgfl8QIogfY6A3EGXn0BimoV4np5/419B3FQX+gAxB4wRfE6QCijW0MyTGwZV4M96aYhjlpEVDWzrTjf5ILtrchhC1BZUNwdl5Pbk3AtBkcL4HHh8kVMIkAtg0Pc4W/HAs22kbFMQK+dLyvDQVPfNdva0G/7ESNB29Yzu2EpWUJaRcta42pbQJrhfUiqDMhTt4DAxI+raDEvZuGsU7uZSyNUAABVAoeAk7nyoeUtegAnGPlw4iTSkQkbiAfuj4lgjjAATKrN/HX8l3TiFCJDN7ZjwkgmEsgGJ97KVNu6jqf7/UCOJxF2c5e1JiLeynWglKbtryHtEH42+mSywzfLPnAcBwb0VACZ4wPS5JBliIqjvEvPmLk4RgKDlySox8L/VoaWuPqDwoPc2joiUyfRBKdvTMMbQIgRzKotFE/kzAstgHN/ECDcDBpzsRbFAi7n/oLgVs0k0gftCmI8g+JWB/1PAK0LiYEPQBDn9X9oQWjZ8kOuEsx91bqgT5w2boHsZNZlHbjRedcvDSXWYF2Iz03CJ2kDPuyL7V5SyGfYCPul+ictfjN4uQjjUd+2gjt9egC6FOBSXI8b3JGsZSLMKQTa3Qa6DAXQqRpMRcQ7Zz0SfRa7dQeVQtOa1ZLlvJdZmRnpd2X2sib7VKV06T9ixnXpIXL4+d6+AlJ4EftXVyrjGaQsjrmbLBH9DNbl4z+veTNs2qiaTX2pJCEfkkWZdNaoBqwVL/vaSG6x5D3LcG44c1BebgwVYxszu4eBAdwatekBDRWPILLNEM6G3K6HCFTtqXRX+LkHqNMXQhayKPYnFt54J29rMUjH6PN7E+RvfBl1wVv1qzwStodT4dhmIDk8n7q9cADUpkxgcdX00Meja6T2QLWuSFHNRHrFz36tljS5PLVddTRg4c62tIg9eO5u/bmKf6Gu+EJO6I+6wZRQog8pk0sTzRrbeQHZe5QoPIt5O9Aq1VmkJQhtisJlNs62Fo+IPpdfjTBhCb5p6nDYMras35mgpOXbd63mXBWXt2DlVHhEPBup5hGVyzc26JQ3bNTCs7HCHAx8wTYpDaZWaxihx+ULhR9C3V6fclnnye4lTexDvi4R7Lgg5xQuY8uFCPmRXf164cz+YTDBLPbtNDkIgfZgk+SbjXMULXAMCiPukHgeDo1/b0TNh5rjm2BlpcABgz7MsGYtPisNwNAQpToIiamQlvKEq/Ssnudj3n6wfl/ub5sECanveUusnOAZrO0/Vphn3y+5ivjwBCaylJ0vSCfqslMOKQ9oMc3CA5iN01w2LvzNXJwdxRnAcLtD4Qow9IrRaCBrnywzsdkNHqtenYx47IagL46xA7QJ+mWvsEOTvmIZSKO07/tWIoj
*/