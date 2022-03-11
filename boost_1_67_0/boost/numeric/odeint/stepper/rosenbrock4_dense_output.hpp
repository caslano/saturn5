/*
 [auto_generated]
 boost/numeric/odeint/stepper/rosenbrock4_dense_output.hpp

 [begin_description]
 Dense output for Rosenbrock 4.
 [end_description]

 Copyright 2011-2012 Karsten Ahnert
 Copyright 2011-2015 Mario Mulansky
 Copyright 2012 Christoph Koke

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */


#ifndef BOOST_NUMERIC_ODEINT_STEPPER_ROSENBROCK4_DENSE_OUTPUT_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_STEPPER_ROSENBROCK4_DENSE_OUTPUT_HPP_INCLUDED


#include <utility>

#include <boost/numeric/odeint/util/bind.hpp>

#include <boost/numeric/odeint/stepper/rosenbrock4_controller.hpp>
#include <boost/numeric/odeint/util/is_resizeable.hpp>

#include <boost/numeric/odeint/integrate/max_step_checker.hpp>


namespace boost {
namespace numeric {
namespace odeint {

template< class ControlledStepper >
class rosenbrock4_dense_output
{

public:

    typedef ControlledStepper controlled_stepper_type;
    typedef typename unwrap_reference< controlled_stepper_type >::type unwrapped_controlled_stepper_type;
    typedef typename unwrapped_controlled_stepper_type::stepper_type stepper_type;
    typedef typename stepper_type::value_type value_type;
    typedef typename stepper_type::state_type state_type;
    typedef typename stepper_type::wrapped_state_type wrapped_state_type;
    typedef typename stepper_type::time_type time_type;
    typedef typename stepper_type::deriv_type deriv_type;
    typedef typename stepper_type::wrapped_deriv_type wrapped_deriv_type;
    typedef typename stepper_type::resizer_type resizer_type;
    typedef dense_output_stepper_tag stepper_category;

    typedef rosenbrock4_dense_output< ControlledStepper > dense_output_stepper_type;

    rosenbrock4_dense_output( const controlled_stepper_type &stepper = controlled_stepper_type() )
    : m_stepper( stepper ) , 
      m_x1() , m_x2() , 
      m_current_state_x1( true ) ,
      m_t() , m_t_old() , m_dt()
    {
    }



    template< class StateType >
    void initialize( const StateType &x0 , time_type t0 , time_type dt0 )
    {
        m_resizer.adjust_size( x0 , detail::bind( &dense_output_stepper_type::template resize_impl< StateType > , detail::ref( *this ) , detail::_1 ) );
        get_current_state() = x0;
        m_t = t0;
        m_dt = dt0;
    }

    template< class System >
    std::pair< time_type , time_type > do_step( System system )
    {
        unwrapped_controlled_stepper_type &stepper = m_stepper;
        failed_step_checker fail_checker;  // to throw a runtime_error if step size adjustment fails
        controlled_step_result res = fail;
        m_t_old = m_t;
        do
        {
            res = stepper.try_step( system , get_current_state() , m_t , get_old_state() , m_dt );
            fail_checker();  // check for overflow of failed steps
        }
        while( res == fail );
        stepper.stepper().prepare_dense_output();
        this->toggle_current_state();
        return std::make_pair( m_t_old , m_t );
    }


    /*
     * The two overloads are needed in order to solve the forwarding problem.
     */
    template< class StateOut >
    void calc_state( time_type t , StateOut &x )
    {
        unwrapped_controlled_stepper_type &stepper = m_stepper;
        stepper.stepper().calc_state( t , x , get_old_state() , m_t_old , get_current_state() , m_t );
    }

    template< class StateOut >
    void calc_state( time_type t , const StateOut &x )
    {
        unwrapped_controlled_stepper_type &stepper = m_stepper;
        stepper.stepper().calc_state( t , x , get_old_state() , m_t_old , get_current_state() , m_t );
    }


    template< class StateType >
    void adjust_size( const StateType &x )
    {
        unwrapped_controlled_stepper_type &stepper = m_stepper;
        stepper.adjust_size( x );
        resize_impl( x );
    }




    const state_type& current_state( void ) const
    {
        return get_current_state();
    }

    time_type current_time( void ) const
    {
        return m_t;
    }

    const state_type& previous_state( void ) const
    {
        return get_old_state();
    }

    time_type previous_time( void ) const
    {
        return m_t_old;
    }

    time_type current_time_step( void ) const
    {
        return m_dt;
    }




private:

    state_type& get_current_state( void )
    {
        return m_current_state_x1 ? m_x1.m_v : m_x2.m_v ;
    }
    
    const state_type& get_current_state( void ) const
    {
        return m_current_state_x1 ? m_x1.m_v : m_x2.m_v ;
    }
    
    state_type& get_old_state( void )
    {
        return m_current_state_x1 ? m_x2.m_v : m_x1.m_v ;
    }
    
    const state_type& get_old_state( void ) const
    {
        return m_current_state_x1 ? m_x2.m_v : m_x1.m_v ;
    }

    void toggle_current_state( void )
    {
        m_current_state_x1 = ! m_current_state_x1;
    }


    template< class StateIn >
    bool resize_impl( const StateIn &x )
    {
        bool resized = false;
        resized |= adjust_size_by_resizeability( m_x1 , x , typename is_resizeable<state_type>::type() );
        resized |= adjust_size_by_resizeability( m_x2 , x , typename is_resizeable<state_type>::type() );
        return resized;
    }


    controlled_stepper_type m_stepper;
    resizer_type m_resizer;
    wrapped_state_type m_x1 , m_x2;
    bool m_current_state_x1;
    time_type m_t , m_t_old , m_dt;
};



} // namespace odeint
} // namespace numeric
} // namespace boost


#endif // BOOST_NUMERIC_ODEINT_STEPPER_ROSENBROCK4_DENSE_OUTPUT_HPP_INCLUDED

/* rosenbrock4_dense_output.hpp
4ecbv/9OMj87G+ObA/TSj7j/iqOzUzmax+2Gburbnb9ETasSK6RdgUdZ12sEo6IuFD7XEOTm9UKGqMvMlE/8XsZ5iN7cHvL9qO6rOKjoUHJvqZ4wk5TbhzCsob89FoaPYr0aHSOGTC2M4x4QIJR42A8UWp9+828Y8z8b0XaxtUUfxHm3grt6cHAxaHfVqNpPPJEJVrQqYmp1nnmJUxxKlvGs1IFINtbhdPWAnUN3ytLC0fscubJYU15JfSAmEdCHu854f2QjdwETXWQl0558aT06kxSR5HGDK+Gnrj4g+RdrhZeU2HxrqwgMDTgu+dZFxbDf/0SJ+3GJVFk7RjEvmkIuoUdNqRavi2ibdijQ1Guty9yuuX59ujv5Ouo8paCfYX/5yl5HoKpal+Rvc2G/X59b8LrrPCehn3Wf/eTt3kFWtCzK3A77f3t25kLRVO2S83ckeFapXtiMpuO/aRCN6bW7t/J23Ho2XhWKNNMhvjoshYB2OPPsdEy2W2t+637xtNV/1dA//fJeHX57ui3Owea9FimF2nOvf3ev3fjCKBpn5E+UPn87v21fP9FYeS+jLv1+QaYnf8ESf/yuxPn/94V/tY+HPrIK4qt0ggQo4pWAebgjCAQijCFzByloqkVafEy6uLp+NCGiCDydsYEov3JY4r/Ga/LL8AnKi1Na2poGKMkwMAi1AG0G3CxKyIlMnLg9AUT+j8qK145SMogz392feFm5V6/ay22V5wpfk/cb2i3d6lwcp5TZgzL4jZ3ilNqe+bl9tcPX7ayXw4bkiu9c9cSBti/r3DUPB6lkbVbiwiBnDGHRdLlL0j0RiWbKu1Z7pSNttlBytSey1HTgEwazwXS2rV16tw3pbKqX74slBCaz4OJ4StcsjxNwzC2zvPxkqIN6043ZnY1JsBy47H1ohcKJBw6P0GAUSypjN3bYzZjegm6zKlPru2V13veLlzX6Nz+N39evlntdO53f1l+4ld/dt23Qy4/e6sPblsNAtNGViMROELyv3OT6gBJbLi48m/HfnPjfBJX6r8DWbzfvpuIuL9fR+/niFEU3m+u0WN7HDHOK1s2bNxaH1OLtE1ubVtIMR+8YDDqOOMEv6ya8u0MYbvbT0E7wrriI8X/pafkwuf4coo5NwXCqgWgbFVfuZM4QPfYGEgSYcdmxH6B6aw6nFuuqPpAsYjyVnYVw8RAobcnYkuBsPLOOtyVOjuPJ/4COPNF4SsPEM3BCZUCj07C7hY9DN3spbMb94lueesW1XvSKsh/+/C9RpCrzaDX3J84GEA2iUVMzZtTIB+0ovOYFMy2E9F9mF0S2cMe+utfq4D6eH1I0Jz5tnmgb57QivOD5EP5b0lRTepQ1kxwhDWaxdqI1xwYTFCg2zPpJsVNL32W91HzcvNTE01vVk9nVl8DDVJFEj0JPTagFyji84EvDzMgSXJqrKsToWufDcSF9pehH7fyVXZrYjTF7+NEaC5lWqoPtj7pYH00HznbHiTWb3g9uPXvgU51gtZE2JT2PjLwPJXPC7GgvrnFI6KH8FXJf4a/1a1UsS+TI4akwcmxtYCzGomiKgpHDOulCtUkvKdWOHOWAy3Ki8ZSUlutsQfrKPA+LWg+MhCgioqre82XWXP5RlDyxTI72bf8SHvDNnN4t/grC+eWC1pddUErgug6lS2RZDG5Rh7auf7FXfk298zGgL5z2qu4Kce42GJ3dnWxBV21HuVRYdkWKU0iPhHkPClQvI50bf70daxk/S8nxz1UoWsYq4I5ySoUzzmzyRDsnQL5eOprotj0/75DEqZcVrMz/zqDfmZILYgjSjfsNCtirRmIxydzt77qUaUpkpx5lTWMm1oQ3lr6LmVLE8uqJT1S3TFB/koWONAEmiLsl9tkaelV434INO77rFNYWvHEoqka2uPyI+Wfor5060A3Ru2d3+etg2nF1fabZXmHUsdK7SqBjtLHI4qUSVWOmmh1eA0tvXZKOzoo7UGfA6ro5mtXDmNhjW2kMoEHLn7dbAEH4bwH+FtKPOQyP5K1Q90v+UFlN0Ck4giq/lfCSesYw0R/1tMCIkkofAlmYRUOBBmtOSwm+i3QFc7XbKHiSYnClzcwEmtasXzL9P2Mj7FfoPaNT/Farg+XRgYeEaiRL6/W2kBagrknJHcg1GecHZxyY2/419i0AfCI1sjdTI2c6PZNrcswtmN8YmJvB3xQYJ083blcxMfT+9mjrUfOnfiguXa6Za8FBEVrgQOyGiKSh0/MHlkr7jqVUu5Z1xRMBrG3+uJjkTDOyxqTBUg7VwLnleB/daqnUXcYVmhssfV4/7huPK2v9O50D+PpJBAw4CNqAY8BYUMHBe3gHPo8H2NPQMJGbtkch9xs9deDYUgKc/ALFN6AS+UEcxiKHc4nC+DyHZNJXP2gL7y/7yvq4kdF0UbMwTD6hJdThfdSRYfw8pFJUHd/yiLu8NZZciK5U+Yh9uorqQ9kCCUp/4UWOuZnlhmvqnyuTkL7QGkj8dAbHV4vo/ZwBK1z7c+/o0dsHc8sEMScPZjdMn+BYPztXGhl8hFSIzp4g6Dtu4KfcbXTMRInQKA7ctknCz7Zo7n/su+25hP81vTRgcwhnvnyb1QwaVgQGINITnY0YObioG68YWIS6qJuWC3kdFF8U+myo/rsfBV+FjSX0w/q+58UK62yMFoOf32okH0ivKD/a3FLJQtxItB+4KcT1iy/gOf8BGAMzrtqHPR21bwQ03RTBxQCerKBzJGsZNLpkNw1F4JKfj6EQnW20W3lkN0Uuk9USjZHYgMS9gVLgQBidv34JPnE4HEWQhcM1AsUaUpzAaI03bo8XApgyL7+Xt7t03OHCLrCGXGCFcevX6JlzvPluahDANkwdNlzNPu8KOZyOU3himnUoNC+l5YMI5FErZWdezRdAwuWZ1pueVu/FGImW9Cp7X8z62S0MU53VnYd4JbQH2Hh6fFoV+AiQ+dnx1Omng1PJJSiCIzWtzBs6+2EyoH5nOFFHSs8Gtcs0XcTWSXmqp2kEAwW9vCYItYEQ9T93vIdriG6H6KnRheHo8aiHI+YGXzWPqHB5PxKBNgl2+VptlB81gfCfDHiGIBj9QKMoWCgdNUYHzO0NJtWqs+VKkb/p3ZeqnnRSDpO75MGzTSEBoYVcIQvGJsh5VJhoP6LRPsQ+3Mco6lTxXlaAZjOv20LSuuTm9qldApLwFGKGeaH/Tpy7sxAtKmT9bOhjS1hZQb9UoXFyGJKH/g9k1gFi+TiQCiI2NHAuz/Sc4ils2fKAPrKsF+RMHpZWNmrv/D836D5G9bCZOBUfqsLCDLpKnv25leWGnnCYp3+mp0knn4mGcvv93eL9yDo9WD3aVc8TRw5GgxaH3OaCdbrV35wSMlshj7gGE//lKcISuxFkVC0dI3tzfN+3oKIOdci0ufBc5cbDOnS691m1tO6Aj18sKpey9WJ34wCmUoB0AsoWSwrydlrdGRfw0bSCkkPkSD+L52AKuh5pChg3FJ4OABUpcV/+s7+XfgROHTJybliPsHYiU1WWY4XDCMMBqzwEZpPVW3B1YZ4j0tq1jT0knysazyoOhpV5p2juIwt0lRoOjiJONGcsKDR6x8HNiPlAu5J1QF9mNjAs3bknQWnf7NvPtTuJLaU7vXpyGWTip0TpxOZD4AkdDePXfJd42FXNGi84gr7uVyCm2X10mLnttYj9Qqn/aBr+b/DMy6KPxwfACjpUcy6BI9CmRRUz9mfeLbRGjOQLHmDy0nEAsj0QwGgim74Ixyo007FUUuFSPmjqyDe5HF0P2OiQEtkhU8hW5xFF3D26TVgfPauu4vI5OZPEDogzw6Q2ktSC2PIz75zf+yp1clhsyT3Jfve03tCxUGOgbl+1EXjwVuqOu1rXpvcFL05rl3QudYJerCiFkgo4Z00bG32fj7Mgcda2xn50s6R9ANV1lhtrXd2AnZeNcvGYXXsVYb9JN6du1ABprlljLmDJ/+lyHAWU0mKv3hzOIO9omZW/13AMQYd2qJjlDddNt+1fGcxYhegXnlxwCI4K4RtcOuVaDT59MiMANvmK4hPStLE10A0cFBoEfLTtNCTgUgdQNgf6/uV0USvTN71HrObTDrgTHqU/juC2XED8tQ+TLQbzD2FMDn/ZEttAj0ivhPiDQ7MzLAAZneA7bnyDBMve3iZzBYL+bekjouN1ezByK8mWLWU2phG1q9PbzhSL5bsBLu0AgyZD30KIY3jC9isCZ4hn03cbdT9y+mVMh8MXoi6p9dXxnMu8MuDJ8vGN3SToirdcP/l2Ivk/MrUumTfViiOb/i9Ld+tGTMxYP86x0d8hGLsvgjcuSD+KOzIKxed+3oXCW/C0xx3AWiTiGr08uP3PblPiwebXKGEVLo3T6/hhJFDRhsjWRwm3GJR/yNlgq5lZpQgJQqlMO0P1bC1gCOuJv2Oqg8MUHdz/yiJM++0EH5P5vBexLe4iaVqPuOq2ptzEU2P5B86aud+GbOzmM4WCcDukUh/f0dzDA3eEAUYzB8zoYqMAHIGRSzxIYk+WeTbehoTtIsg2N6/Gcf0e3q9c8Frdm0BFKvdb12EyWrUK2FS6ytSang9Evu/sEyr7vJ7imWNZURljl3nCjWI9IUdwA9Dqkt9HcCnvfsLsIuU8GyKReMKH+TwhIwpHgh4tL/EVHJCHqrZEazaIhHBVnxFeBO/ls7DAwJyKiHGxIOvXTeFZN2mQRmr5ImGsYgQri9he8UFYVJtODi8TvmhNQ3HgP106hOadae0KmZTwzkLwJezOeavDZdYioNgjeRHBHqXzJux+Eo+WvAzanuTfDNl9G2kjNL7hjAWSIwr9e4aTR7/R8uzqrw4R4Co+ETqwqfGz88Bf76Mh/HfSKt0PVL293AjPc/Nau8JDx4CYX92PHcoRu0vWs3CG4rmB8aZVJ/BcC2Sae5l2CIbM+/CPFj0D4/qFwwzkw29843zoAU94urPF/P1R/Ucs9Hqr7RS/cSN5Mb1hNg/jUIlDN2baM9cFY7dJpxAnqb25HYVKjmkndrRv0T6gTLVPHl6hb/gmehEo9SijkBWO/H5gOEhrkb7MC/nGS2GIzps7xAhFrS4H70NTR6+QDw1DEJ0fZgn6BbUMQ1xtBpSQEJiSnBEcMO4hwFoMQ2MyKA7tq1L8oJSCZOUFXV3HjWAzLWDaOZZoISMwRu916++G64K0Kr1+zVstNsOF9K01LdhsT48IYNtSTLZUHt1ARC90oreV5ststq1DgcizsCSnbKxzziGjjxFR5jbElhN4SddUaFj0ZODYl76wj2i3aLHpxNi1ckJxjB5ObA5hyvvXMUJut10oD1pAaP1XZFePI9QkTveR/zmL3J19qb07QsoVm1miwpJRQACDf7qR80cdYuQlvIk5wCtSt+WjXgVxMT5aV+0D1URMMKkoxNIOx5/Msrgd1yOPW2uDhtxsQekNhaVYozCzguNyc6JS5orSJdustJWIdjdw1qxm1jZVpj5Ijj4r9gx7gniABmGMX+TpXtMPyYVxpqyt7b964EhNcfY8OUpTaJI+FWulhaoxU9UUaKEurAC5XPNrec5TqZJoQ7QIzU8y2Jxn07mV0XzTfP+sLbheL9pZjF4n+sFvmh0sNL50rvNi2DjHc+1YVUZS+1GssLdGuG4OiDozQ+5o8hfybw6jJKl+G18suH78Tf+GHxK7UmfaBqwy5edUFtmXPGObzSglXIJbeQd3z6kmAcu9lmU8rPdYlJty3rwzk48OEwVEnmjVSF5XyPZS4U9BoBUYm2wuAAJ5bZKfa2tZqkQfUGFvm6dKS71CteMt8nURmqd9VmdgdVYM2SDLojr4grWt5gSBt4mJUvb1IhbomU4GHufeH0uXbAOl2tXIvEF+lgfesCVaVfEBDepQtIV3D3L3xR6R+12Zo4f+wzNlTgczfZP/OTyqGHk14ZeJWajuwa7d60e5vdckbo+IqsB7j2BCPtGXBADRJR0cuHAgJ5uwAfa1SzismOhEAhXmxfIKrNF55DpUywxL7AjnQwT13knBT2LHm+AWYZ0qOHQozqB5RdPrg5fNdGQj9tyO4dd3rjyWld3/DJbYvvmzvGlOH2hJYEaBoQ/n1q1+bNrc3yd9lxhNQPiDREA+Y8v2gQbcbpeH4ALwKk/337pON0G9QbIkDcJWLbpYHT2xNqQvNkGS6aTezOrrKTsMxFXRnr3/V1Q/Wbe0Jwxs5CnTpqqFkDVd/yoMAhNWOjrw31ys1sgOHuXcLzsYZC4b1eTJra0+ZQkg3yNmTTOSStvU+AA9LzgPhItzU3i9UbiBtm8aVy3XTfsE8mVJPi2wEd4eNsnTYr7lD7XbHqJqt+bqtsdiAyDP+mYlw5RJOdNcePnqgoApZB32A7yzSgZANL22CtQFewbplqUcel0AbUJp24EPC1plW28M/yizYdujOZ6reJDdN1v96H2g5jm1cjlq+TvTli/dmBf5t+fAoDJqN3LxCoIt4t0dhaNFu8QAfXqLvdE/ojZytXHYEdDBMZdS8h6dCcX1MFRV14gBWUy7mL0PxTreud2wQ39ZOt5p1anD/LTzlnAXcsEwBR8PdKwbo8NAVxBQDx8/ABLLRsFw3DA8MfDNpYqT3SNYZ6XHXDJtQOzK1gMiPz5U71VsDXr8JDGL4Lb42NpjDNcKxJ7LopPeqPTv72GZf0ONLnVs+aDPEPvwtXSEY+k690zSawf49OQD5UEm3VkjRgtnvKyQ7cM3P+Ok8jmWEwjSHrih57X5I71PkNDAWLQceKrktiQ5ZXSEdzwGlUANdlzIje7JbCK4HKTVO0Cfo7rlBXQT1TFmJ1pPDVCnibovdJ/GWFquc3OTOzx4LJWvM2ie6w6PMN1X78fadF4Q5yaR5I1dR1BbxH6/3BZqYIork6eJii8D70WR11Idazvcz3gUzZGlvKoUSXXQtktfVkR3s3JmQEwVjuTeYwDNNSkD/ZI3mtr4cryGQc3PqeRWjuLXyoH7SwZ0GjHB5pv7KHXa47w2hS/hPeD14Apc7dEk08Po0nG2sEWVW5Hy6JvrXsh0HSLH4Lyb6w+qTB8SoQ7gHJwdrmmtna0kO5KQ300TZctuVrB43idCWcQ3ETL+kYpswdiryopWr7tQ1T7TAIXNXiqGic8IMvPFUFt7/sQtr1hO1dc+DQGad9M+awGbuYWoWxr+6b01eS+2VXVNr6w5nozFuhNKvYoEG14OIM2vj3dyFewjRL/3d+0TYGHBRSdIa3r8inn7qNzSaw6R5rdbYZiEMRafO8PoPnsiXa8hDSrX5SKi0qQgE8OAp5kGPBStGbUdRRN8BmdzzSRo4lbb5wR2uuZX8PDbj87v3yRlZKUFKNw7a9Qq2rQBDyXhv+jf6L9IYTumv8t3q3C+ar7ij/TzlRR1KjHThyvt6KaGCH4GvMJd42dEvDT18AmyKTGsP3mSqcz8x2ZcfnGSx5P5Zr5xtsmf87+ZRzUHvdk/u4R4m4FWSMnFZ5Hwg4yeHOvynvvz5nw+gAC0hTwgLDlX+LvYQ68IwEpWJw7/MSCiNKtawnvBRYDDvGLRBEsh8VGD4BKhtA/VTJ+I0wDGMx/ZQHr4BVjLJEULsaBaZhZ2RxXURczZPIqf0n5EfcSSGLsUMi3DxT7201o/6WelzrOfkt8Z4g3HhVe4AAMs/NMiBbu1YzoSVHyi6vw4hlPPpNq7LkfelahIiYcvmX3oMtEflrH74LyrriCegV9EKbN1XnrwIsyNO/IzBTudjelJmGccu6WOgea541qED8w6Cc48m7twf414HSRVghvBXfgjt+BcYHSnFLM+nrYXLWFDvRf4TEk/ipQ8DpBAKPf39ph7k9edQo8aqvL+p81s9EbUJPgPbe/tsDjkoRaCs0R6eSTVs6kP2e5GoHblAsJDzeNDhhPc71PIqJLcduENU46cH0rbbNzkUyHj0iYsR6h0c78epsMbKK6aR5tQhU0qP1QN2KWzt5Le8oFuhOOmOpb0/UOm4jSiwSJy2l0xsem+sim0suzGrfu/2FYvfk6+n8YaNDRsGHbvDbd5ab3++XMfH5D5dLS4pWsoNKOkpItNxGDSte8CFbqvPagSXXcM5SpRogDAwC5kAdix4pAuRPKYpEPQ8228rDRjqBcxdcFpL3pmbhpPupB/VMNn7IUM9IIns8CSSEtIgDxNyl4OgapJxnQ/yEX1kZFuFiIWaGi3Vi8pa/rSRHj+nL2geXDxlmMLU2gvrGX8TvkvFFyqYpTNnvtvHlQ1/2k6IDHCx75cmTJRS3G+cNuN3ur2sWCxQ/jGDppcy3EH8LtFoLxwwKGl2Lrbo3ofn85XVeSwgSo0zRiarNxrpKh0wU7izZLa7j9e+nupwGoNpZea/UawBxIp6AmrdzFcrrS4m5C3u8QSxJxHMoqboOJjd676hQUr285+4hn9aod/WGWcLaZXTqwotFWgLsHkCvP6EgdHLB1vmb2ff8+x6Jy7+d1/NrCcOnqR3HfWsszVK4oQSBzLRMJw8UTAxb0BwYH9THkGnkdYyemuejSqDARLGuTiBqLsCQJadhAxjZ4QIY+JfJZPNOK0VVwfKppqtSMWDuUERgxMVz0xB2A+gFawo1rlwR56ybW16XjbATXY1mGcf86+yjfZV5OGVCYNbp8JR91Ov97ldTD6ziBedrJuI15mmgcHm7gxq+RpuYa0KK48NTrlDWZtidaqRjY5xPjsOhXdfgXVzpkcElZmjplt3GFt0RyoLTeO98JHGUGyyoCKsS9lGPoG2lxxyRNPbU+6/gZa8egvqo+9H8pOeQHnHJd+fja83tHMoD1u68XOiYFa6ol8WrngrUA3r3/YUZZBZY3m5DWZDpCclX+YfN6JLP0Al8N4H/Wpg9NBE118gvF95ocz3QCUmdVF/GcCdCh+M26jXAEPlowzfWbKNEjmXFoG9TmwJDtexXfsRc7E5OEp53oAA6UQTOuKOXZ6X3oZAAaSQhOLK33fIPwEpAaHSzcZg9PSrJN1oAoEyC8u0FR2tXC8QaaAeT1LQlk4EI8jMzDq0zKJKl7juHH9eBC16k+9+POltmjf6ZxDG7wgAnY4316X1ztnuH/JmTn8sfK76yj5I3ac9BM7QfGJl8x07Kc80/SrwNE4oy6bM+xkCE/rzTecntg5Y+u529M1SeMM88bSYaj63stpCqP1rSeD1rg=
*/