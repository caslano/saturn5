/*
 [auto_generated]
 boost/numeric/odeint/integrate/detail/integrate_adaptive.hpp

 [begin_description]
 Default Integrate adaptive implementation.
 [end_description]

 Copyright 2011-2013 Karsten Ahnert
 Copyright 2011-2015 Mario Mulansky
 Copyright 2012 Christoph Koke

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */


#ifndef BOOST_NUMERIC_ODEINT_INTEGRATE_DETAIL_INTEGRATE_ADAPTIVE_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_INTEGRATE_DETAIL_INTEGRATE_ADAPTIVE_HPP_INCLUDED

#include <stdexcept>

#include <boost/throw_exception.hpp>

#include <boost/numeric/odeint/stepper/stepper_categories.hpp>
#include <boost/numeric/odeint/stepper/controlled_step_result.hpp>
#include <boost/numeric/odeint/integrate/max_step_checker.hpp>
#include <boost/numeric/odeint/integrate/detail/integrate_const.hpp>
#include <boost/numeric/odeint/util/bind.hpp>
#include <boost/numeric/odeint/util/unwrap_reference.hpp>
#include <boost/numeric/odeint/util/copy.hpp>

#include <boost/numeric/odeint/util/detail/less_with_sign.hpp>


#include <iostream>

namespace boost {
namespace numeric {
namespace odeint {
namespace detail {

// forward declaration
template< class Stepper , class System , class State , class Time , class Observer >
size_t integrate_const(
        Stepper stepper , System system , State &start_state ,
        Time start_time , Time end_time , Time dt ,
        Observer observer , stepper_tag );

/*
 * integrate_adaptive for simple stepper is basically an integrate_const + some last step
 */
template< class Stepper , class System , class State , class Time , class Observer >
size_t integrate_adaptive(
        Stepper stepper , System system , State &start_state ,
        Time start_time , Time end_time , Time dt ,
        Observer observer , stepper_tag
)
{
    size_t steps = detail::integrate_const( stepper , system , start_state , start_time ,
                                            end_time , dt , observer , stepper_tag() );
    typename odeint::unwrap_reference< Observer >::type &obs = observer;
    typename odeint::unwrap_reference< Stepper >::type &st = stepper;

    Time end = start_time + dt*steps;
    if( less_with_sign( end , end_time , dt ) )
    {   //make a last step to end exactly at end_time
        st.do_step( system , start_state , end , end_time - end );
        steps++;
        obs( start_state , end_time );
    }
    return steps;
}


/*
 * integrate adaptive for controlled stepper
 */
template< class Stepper , class System , class State , class Time , class Observer >
size_t integrate_adaptive(
        Stepper stepper , System system , State &start_state ,
        Time &start_time , Time end_time , Time &dt ,
        Observer observer , controlled_stepper_tag
)
{
    typename odeint::unwrap_reference< Observer >::type &obs = observer;
    typename odeint::unwrap_reference< Stepper >::type &st = stepper;

    failed_step_checker fail_checker;  // to throw a runtime_error if step size adjustment fails
    size_t count = 0;
    while( less_with_sign( start_time , end_time , dt ) )
    {
        obs( start_state , start_time );
        if( less_with_sign( end_time , static_cast<Time>(start_time + dt) , dt ) )
        {
            dt = end_time - start_time;
        }

        controlled_step_result res;
        do
        {
            res = st.try_step( system , start_state , start_time , dt );
            fail_checker();  // check number of failed steps
        }
        while( res == fail );
        fail_checker.reset();  // if we reach here, the step was successful -> reset fail checker

        ++count;
    }
    obs( start_state , start_time );
    return count;
}


/*
 * integrate adaptive for dense output steppers
 *
 * step size control is used if the stepper supports it
 */
template< class Stepper , class System , class State , class Time , class Observer >
size_t integrate_adaptive(
        Stepper stepper , System system , State &start_state ,
        Time start_time , Time end_time , Time dt ,
        Observer observer , dense_output_stepper_tag )
{
    typename odeint::unwrap_reference< Observer >::type &obs = observer;
    typename odeint::unwrap_reference< Stepper >::type &st = stepper;

    size_t count = 0;
    st.initialize( start_state , start_time , dt );

    while( less_with_sign( st.current_time() , end_time , st.current_time_step() ) )
    {
        while( less_eq_with_sign( static_cast<Time>(st.current_time() + st.current_time_step()) ,
               end_time ,
               st.current_time_step() ) )
        {   //make sure we don't go beyond the end_time
            obs( st.current_state() , st.current_time() );
            st.do_step( system );
            ++count;
        }
        // calculate time step to arrive exactly at end time
        st.initialize( st.current_state() , st.current_time() , static_cast<Time>(end_time - st.current_time()) );
    }
    obs( st.current_state() , st.current_time() );
    // overwrite start_state with the final point
    boost::numeric::odeint::copy( st.current_state() , start_state );
    return count;
}




} // namespace detail
} // namespace odeint
} // namespace numeric
} // namespace boost


#endif // BOOST_NUMERIC_ODEINT_INTEGRATE_DETAIL_INTEGRATE_ADAPTIVE_HPP_INCLUDED

/* integrate_adaptive.hpp
qfjVgvQgtj9UjtKsQO34JF04r70aqrHMdCUl0aHlMsTaMkD92eKwBP7h4gvE81/31/67Au+Hhk0XoBjHWAhKbU377CdXchE7yKwbugmH9+P3fe/yzGiD3y9kVS7QHdkV8GyaWK7Wp9cMRsEM2okimnHEWA1NBYgnSAgVXKZZ0yXXDrcM0QJWxB+SeRaYpQSiz1kUmgUpjYV07DBeJcwuCOSZC9E2YKQA0QzPdz/czt4hsl0REFreRIydJ0Z681OYy/YzcfMwWbFqaZ4z8NFi649H4tnFtpWtOL0WPjwulHLiGiPoi+vdm+H4n4ptIWMA5xzsIVnH1G5usfit5aVcj5M+3QU4NFFWRXAVHt8Kt9u8mc6XufzmQOsCk83eCuRiIt0IA8kkesKNe1/0jBWTNsMk2GgLlfJu4+x0fpQ8fpIegC5XccrjpGjc6F200URF3mRre0h6DFREUme6cae0UiW9FcHGy5LG69NC9RfLxueRf0vaQ7vLVkZVyPVhq6KC74CuVkjjKISKKLr6aaeJdAd8ZDFV7jLeXtXV1enU16972CV4eB69QAhkSFl2R4W/fPECV1lR8Q0DDv9fMyINAjDqq2WIM6fV2NHr2A6fApmK785EyuXw6ykyVI2JrDyptvClntQ/bW+Rn36gHW6fwoeIH3WnAoDpPLSODw3XANZURBqNcOCHopF0vlUEhltngUyeAeSo/q6oeWa/KxM6AHWose9YPGT1Eq1CL+LH2+dl1kxUneBdzSWeo74uUDwWTrlMJI6JZ8ftsR7WXBLeT9M5mV+3z17+fGs/wECrdG8QG6tczDXn/uEb8ZsI7cLe88fjEhVERZrsVFio85VSp5J5FJMTQPOOgwxD6nPDLVsf4rbEY+DFCYjqoumB8RhA5IuK+yL9xBH31H0ugtKo7rML6KH6hXtb8GNryS0FBncXXpzCGGZ2/cNvysk+W/3OYh32XLVnedcoGpmC4HJ/aud5LSNpmhUecs59Ck4APBAmCNMdOMQ0Rw5WuGTee7yVbD7+wrJEACfqnhHwJIYSrcdhntolW8faEnRmGlLnXG/XOYPwxf4txHp7eXEX/Po1G52TAvNefAHX0RlxzdzdnuVe5I7J8vYwE4CGZhEwVFMDfzq/dr29BdzSOUAENY/dwzik5oaOUMTfqhygqyzO54mrI7bRNOBEDyxWm0u7bunHouJlAXYAqWfSAcDrNCth9C9T7j8DjiwC6Ze83a8iMjK1CocTVwMbfrXHHo5PCV+k7+meX+K2vkix/3aLmGV6BhTbnwTADhT8blsCJh+6l+WtYYl1p185WR9z7JTfegipg4mnO5ph9IkjJ7jQL2bPYSLnWVsA6lHQ2zQRDRqltOde6r/CpTvJwkL1ShMbxjnFTznUv/zpNAMNApdtlwM4Bjmcmm24bF0EvzBsKdgqjnq2R6JRjy7cC4wGmVgiWIkisu5RGD+FnyKL/miH2D2gW+EdXFLXb50/2uHtSs83gu/tmMTxuRQLx5DP0xNKwzWMGAjClfBg/pzrxFuRg7eu/t4LsE4x7/hqWXIk2f4w6V7ythhF1YbX431MpRfFIA0/n9eynMaelRG3klcnd92+elwSy/Dp8GoKjIUliXrx8zBUDwP1PFbbIKQnA15U+dIoH1fmELYXiDHbHuRD6WHCLgLhc/ByxO1zBow29U4H3CospRWKsnowZgsYIPu9Vkj5tPoW50rUDlAnRzxezs9oDUDRScZKRFK8ureahSJLO64Dtxp46DrRWihFYMcRLXoRaYv1Fm4/sAZgm234FQbgjNgvLyW7qVzbQE/qXtysoJAJypBlqGQCcSTjASg0GB8i9GuH7Dvh1U3Z3yPn1/7dU58bq/rz6D2nk9PvcVq9QebayXRZP7LD84RIkz5kae9Ja638XyqakP2KbgsDyVdlDuXnPDjv3KoxhoNN7k/3XPhwjdmVrUxnPf8NiFOTGNkfW2EM99j1786sXsCknudOCEbp3IYaP0NFBCyxyW3C5Wgp+sgJDNNvbyeiIfUD9I3MKZbzxhKfj6Ue+cWKv2ngeB83rt9k73DdPd6g8BwSmNN5RtQndX7hAfe01NTnWwMpEm6kLkQaxLFcCtLi/PybqKbyeG8caw+fXEMKYRj6OaR20C7Zim81yxXBX+ZgcVZNNSOrGWtL7Ms5tz6E1OZDCS8pCFW1J1G1eWSONI6K/c8/ASapSPWOVlqR64ZTugBqzrm/yaqEN78BOj52//EV3IpVNnpu3Gkq/5PMzRmiw9tyVQ1Yhs/6mfirhy1Jvr7A403ZW1dccl0hMI+vH5OdzD3wqvj1VmuDMVM/XypU9OzYKB4xcaOQ8QLq+jZ8T5/CCfCOsWeeV/RNSO7pO36H2tbD1qJPpZFt7pgwO5/vt91+L6x6rmwNdpItPfGe/JzO/98YeMJpzi5f3FR94d7zJILmJcWXwmGnrlkhlohmrU4ZVuJ54fMPuPmfkkbROdeljt2Lwh7cL7LSX/lUEYB2UL1Iuv0++qb4gxK6ygn69zeEKyaHb3JYp1oMSjJcNKaY+8ff8ikxC92fENfnePuKFsU9ih1KXV5sdH8C/9cDgeO+1VX5SA6dhgYFLWw1IP7+fXN6Eb1hiG7RKsMSt/uWK0fGWU3/TKvdpKtfjnNG9HiQv8jyw+Dukiod8wqoVpoccFEjj0tbQd9l+PBZioHTT6o1wNEGLoFyKV/xBgiDZH119oDmNCqOfpwHSuaV6siLDXzLGvc3Wz/aCFDTfiRGFx0juqT3D8WHfX2i5Pql30eNnJ3XM20ClDyvDVxZlGm4XDZ7B2T1mdHYCNVY9HUyf2qfTQMtgIett24bjGcF4pUHMFw/doCMzX5fvxIWCsZf6wMFw4GCYcAZXjhC+A/vx6ezz1zdv92jHkv8JOVnfMsBun8z6Rw45oCGLT6c2LQdeeyJyE09QkWfU4tWc2N4cI0/i0Yy0Cj15c3nC/9SYEDrCc6vPLj5XEWtwD+faCLO536a13I5u/3e8dXVxQ9f1PLj5nkz0ZCaBfbGpLe3v7bwSw9XZrsP33zQ/OIeOIUOlUUusy6Oft0UMTTlQmox9YfbKcyHKPzxP1FieXX118tP6btZ4pbd9xY/g1FI9r6qi53cWDUEEE4b1AwE7xusPrvIsioexIs4WPyQ2Yd56WO1u4eCrwKwGuUTa1kX0H1iFDH33YCXnAqMFfU58ZCsP7eIMiz+GSfPk39kMY402d9lVZQnAU/YvybKPsX4vX51c+e++x0Rm0DwkNCord+7rsyI0OnxJ1lGLvZ32qeUS8lwzL4qovIQaXI7Sz8RWmP2FnVZteXWxWI2C+1jR7Fl94lX2n7n6f/WuExs05Vz2vs67uv/uq+bWKKim845q9vZ1lEaDnxrgaKUwKFXmtAG+O/uQJMl1WFlNQ9RDB2LQoZd7Jbzb2yx73Xi+MhtNCo8kv+QFD79Q4zd0/+55W4fBsx1iBQ+c1Vz/Q7sXz9wUuzm7opjb0eEoB1CSw5sOWdzHht94+wLIuLtPt+qNw5B80/NSA9Tc1i/syiNlcMpDVSMzF43tSpvHUd+nNg4ZHcq/VefhXE9tvn0STa/awrRkDTtl0I4Wu8pyPv1S2nVNwO5Lb4Ax9bYTVNykoattgbXgpBZcCjT6vKV1MX9nvdk2zDM0duehmXks1PvF+oXvEDk5Cr8JYQApkjR4ZRhkgK4+DVlMP83Unme71GUaH1bzasDfaBtxQDuhwMr8o0Lb0m1/lqnNaIh3YRPA3phvnAfYmdjy4XJBuG0HJWwerL/a21IPtH9mWIuWEUGdPFuPWt4UgJFvQAu/G/5Wj0FL2LFGiHnP1RXCDYDJ81qqL6/DAX+mWf1LxR+k00EwaWUIEz9YEHd9Gw105tH6Oscd75UMTftjRcHG2lXfF2tgTUq6SNNVmQX9NeCQyzcq187EzCPQHh7Ycxjl3CBIRYveoJS0RcXAVLlSy8yCehl6GYgwyI8NDhjXVX6lEGMh6M8Mi9yuxCp6HI1Cz9O8WL7yp5lSgVmQz6PMqZrPsKVzqkUifQE65kmWnB80q3Gdpte95RhxwptObMNQrFB+VJkdLQUpFQCj9zs8vZ+28O6Z9i0s9Dorm1ORBD3HZI/arv+6Cp2FMBFLjj04JUTsIaYNPFbbSXYYYFDxAwgjhASdutChv4CSvcpaiI6IXBZgnToy0BnCI+LH68wSDC28rsswElrUclcafPn3d/PRLfoQYIjYd4qW4AF0EjpJECUeW7VIq5qRvPS5p9V5fZJpN13ytbGB7wy7yKWpKYAD6sJcEQtpVirRp6b1GqGRasBCqpAq6jBUYfRpX2/TKBINlAK9tyiahh/WhmorSrtLXTiE5Mx4//K5Wl0BCMpUvI7AdZWvYsol293LPFISE6qrcxjBY7Q6vkzpb1zkSMAkc9q2+Gesu9WAhKp25U3iUPPIdWvPW7gzARPc5IHSSsAyin36l/0nhhLuuxKVAS5QALK/fGzBL7VZTK5a0T2PFDxLl6XF9YccBwh7CZc9aj3MVsArqTSLYQJ1yyE/mv1pxdLGHJYdTb4F7bkPoXz8vL6KoGH/khIEGIdlMAvrPe4+5K2WcX1Tgk8bpZLkkVkq7z9Bxpl86Te7FHT8irNRWNLcM0SA52kHvhdOBb1Nlu7KQpNpF2H/97BaxpbB30opfTwqCoqJEsGbgQZXS8PbVdqMOURBu00g/TD2P2O4Lc11gA+4F4MAEnRqwSIIv59CEofTCRt/SfqC6vK2RjLJxBS8PylYWDhnt2y83568BrtLzIcN6eKu1eq+3o5/DLb7CYrKyhzEtpZ5bNdNMVNtVUv88yd/R4sTPWifHgsjIAb15AMgtPcB//WTc1Tf5T+XdbvWtH7v2Fzn/1LLuo9hM6B2+vKdgAk1dSfJxfiPo5WclrbcrdAKwvD4n5H0Gg0KvrGk6Ug+G+ws+K9La8RTN24w8rzC/dHH3Mk+tfT7xEVfoq135JbpQ2Ce+c5VKr2qzOdMxAwZd8se+jfkQ/XPlr5bFeS/iX412E++q8HxfhH+GPfj2Ok0+Yi1GDlZzsw2VMQrFn9IXzrv7cYiW1DDhEZZzGEbdKEZZxBGJtRClRB24JjHnQBIGnTKwX5C6jTu2+8onq8ssJnFDXB88lYUbFWbmFCrsGLWxfab+0mesikU06nAMijBA6rnwcU+ezZEBBds5+NcxGLYKBsq/iPTrLqE7+kWAkC1xOIeYEWsPCdEG7nCwN4c1ayCJxNbUJDZeEWbT3jkXhQm0nhMVpvXGW8gncwM8tlVdkuLlbt8SebUxFoqTNVm3HnbGiBUG6lOSO9wZaIez2PcKXD+R6pNtp11QK0aOKEiaf+D9dawjrBBWVgZWvFL50qJw62XonipM0ttDHSulcUBuSlva4le1swgPdEMYKKurAX+daQ9plsYmr4R6Msm6LZ5mX3aa/DJQRGyVFNsx11ctfuwFXLrp758krZGzpMOLAmGld+bL5BbZERVzVHVaQbE2b2Kfb1z7/Xs8bABsMGfRhgzyqyrcuCMnIbkGqbn/1QL3rusTZSWDzSHCfDmHydeFff2pOOEH3qffPU+/TUIbtrypU9ofNThecPBerEes2LrHK1Y04Keqt6Huletn8CcredS4BbUX800DrvyK9udr8d9kdXesegiZL0HTiUd6zwUQUmyxsmLCy8VpJ14az39GnvP20ACp5dAJWQiD8xsIOcDFPuQyo7MN2vk5Hej862JHQYCPXn3vN6B+6+tKgGTCc2hIXuA+yWhK/3DZxo9hXk3gm8m9hPVR7ODXABTAGO2nwpQDNqnDw/hsm24infzkA8B8g2DLOFLZhHtM6Bt5gvOXleTwHWOP2Gydiw9ATwd+aZjN0w306ptP06ECvv4e+/A2TGivWvPaY9YRnbM56ZeIwXIPYd0KfJvqkVe/ag5zpR417MUzm/OhWs4kg+FS01Aoq9QXg6Dr15winFRn1rcvf5rcbxC8Un/hntWbkqs+oUq8tMwZUiveFu6kYJDNJq8uauyVztBecdo773Lg4/hy8Aw+gxZVLTgzzCzEGpj0X1dUuX9daenC1Hoh3UgZuBDYra+tZppGdxpaTejvDfQ3D/cjL6HD5KT5DqJLIRbf2JeTr8a9YN7wcZWYTSdqIoUHI8H4KU8m9WdpA7vLtpcO4fbkuUHE5y2okPzPgvJsnIyERKlI0XaBMT09L2ieRowvLZ6UkUBHUHNVBlHsuAUb4wHGB3CDiOts7es3uNzSg8f+BlIeREBEd14p9hQy/O1Gd02Ii5prfwiI9NBTY+HCBzmgqYkdkaII/M6pjL4TsLj4TxFkCT8ikMMAb4Zff5I5TOBqAMomNvfXYM3Kx7VuWXxo87EUAllfXpjnjLpMgWuoJ5NAfISjJRAb/ayqkhHBiAB/OMM7GHaAD22/YqZ5iCXxFku7Yvdvu333iuODYqqozybl47P5348Jub7WSAS1Zopjzfpz3rddGYD+zJd/p5csKiTt0UTf2oyFOzw4DOLq2wlH2/sGz/GVO6KS+ZmaTQNxFKQoNnEhQETFJLNJehlySzd2RjuxxYkjlVN207OPWzNnIIfafsfY6iZR7OTmXXS2nVLDTntdFvIvuHJ4Vx0mbRnTpMa1aCFRFoxKcAia0Yt86oVdrrp7U9rLG15tynN324GnJ+3q/VQzX+EuitwiN3Cxrqr56d/3fS2Cv5EyFZj1hxIlLkWcD8vkk2D+4BFTGELA970Pg++cYkTGoSZiL64vYBNKMGkUWz9ZCg0RQV5p5HIP4RL7eoZwJVfAJsARRvJDDyDl8T/iYHwJDNgiuc6f6qa1b5bTYxmOdaplGuGLZysvwk8wDT7RNjBUFIfiWdlIesWf9MWyWwW89dAGYVLOYKf60oqYgNpOOf3qP91uNL29sY6EB36GBsn38R0CKzmAb6IMJz5C+thX55YjVBXw6TRRCVBmpXTc2zxMz4NFzlNxkjfksyueUV6rQ8e3Zm9uzCIPtTRsAF4sHYdSIHixyfVSYfs3Zt19wTq3aim894QkQ5bWn7Lv4GOcGTdgUdg9GN+/lE9da6WQTlGrmr51JC8WDh0Aecd87DvqADjmh9Ik0QXGkXznWcuPuNqehRv6KU9NCb21ap1x5cM6l0TL9hFevcPvEzJnnDDmTWw42+g9suY1vexWTYQb2vPP7+cPekoKDAT6L2cara8Nevf1wouG6ghqyxU067Y/w2oajYpJ+7y6rdcJZPV7oHELWarEzM09pM1nWC4t1bmKz+ueVQNGr5XTsUQ7xOjFRHBPwqISuR8xsB2JP2MT/JG3fOyLqEWh+2581QqSRvKJunK92XeWsDWAMw0zhm69xGi54BkmvnVkfOa39xty7JdWokRWBty+igSvoQUbcZIy/AFFalHoSWtfYHv37R/bIdPwjRWtuqYeA9HAQyGsQwsHy7bGXqpzCIua6tbf93K058eOFRUGtzg9Tve7/HJoOeSbnpJAgU6TY8Cv7uwXQEp/hj0HiLYBJOVOBzK2NIHKjoSQ/HOx2p3VqFBh8f3K8MzfBlbYqPw/x5bbWnq6fiCq8SPYJDJJkvs0WWQTX1pDE+BiLtv3e9x6pI6xoHFZGyHUHmqenaGzXCY1OmsGZddIsrr3Ms/EuyTDeFhLrsaiBAI0oHcwvfgv6JLwqBuy03DozeQr5rUhLQSq/L+P597YjUXEBeV4Yn/7UXQc+RKo+3FbWhSnhO/45JR8+aG8Zm+7x10GmYw/wX1ucLcEYn4lGq6fU7hxC1i6zZCKJyMrQJzByT4O13INeaN73h4tfy3zpAd/WmGKIycK2CcoUb4B3QJfRNibTQ8NN8e8HO83KKdC3ULlg4VTKBv4e+tmbyxtelEfIUQY6rvfI+3vfBSYgSuottJbem8aWHNz77svSu75D5PJ8hpjgST2Ktd04kN/30nLm/rXW/vscSxul45vFAwByqbfL3rx6uRekwBVq9pjxuouYawvh699BCGsFrGH2Qpn8h9ih4cP9Hb6QubyQ6688EE1VcWR6xiACa5/u6poIsimrvWu9zxoNZ3MWlJl/2OI0BznymdUV2Yd3wcNHVZZYzClgQHHKFOc5f3gzm6rPyOr+bUPrfM9BtGvNb+EWZF7r/jTX/0cIL95L0HLUNcpmgGLe26tUhVgduFdS6BGvpTggwmonU3YXPYpXwPmbunp6enfHI3W02qPL+/kDVihKsNJNQUuMI+xUZBKceTDPGNrYt/1RQp8PAtScZGKqbxVLQ0EHc9yg4R5ATMQsN+TIKwDj6Td8R9SshpdPrNGLza6AdUe9roGqvAApQGL/xX1uAxkSekaRfMRqIFjHfAqSD9k6MK9PqyFA5DC6AzifDcOboRAa2tcPUui4jm1j75Ndg87Ns6CmQ+KCSODu0ew2DwOEfRIj+4uQ5bmXrJ3tT77dGeXJtC2iQ5nj5oj4Ir9HZxC+UnPRYFR5Tob3sXqDZkp5RRFpYFfrpFyv5H71cMHuCMwo/ZaK+I+zU0eDIUpJ8EEWh9zmugtdP8plyi/LfW9ZQQ5FD88/MLq3jRQTtDv8x3Zm4Tf8QC+hvIuxT3vDVY/jE5lWO/L/Q6hCZXWkHr0OrhK4U9PsoqicPonsNP6uxr8ItCykr2w7DrlSC0U5fkqX6mfRC5dqz9uiGMYn5wa57vtvmgw715fGnzs19H/aO7nhfFRcXPxHNzfWopR2C41xqNh/UtRCE0s1g7CIJQP08PI2D7sG2N0M4FtHhfq8oq0dtitDNIj74ioi/gxvmmNL4r69Hzrn4YeaHSOeOVsxOpqD+gQMY/hGoOOM0/7EBmulm52kzHfuvyjmzxdNkATaANrKIPAm/5uBXYD/UtW3u1iJfJMXbGE0LAXM2N8bBW7AVqZ+x7gKCw5ucS1Kq5oQp7W2n/Su5K9jQfXD6j8CTNpsIvQC+CpGL88/8780wvckscZMhl0YxQtEXpi8rFUw0a8wCM2yM2ltCbBGU72TqSFlMA1aSaougLtKl/vx2I0TqxJiO7XPohhRqZV7i4yebIWbvpIuls3jsVviVKFqbfaW3TEX/A6uuwdOZZWRsSM7tT+a47cvcu/OxsILYVqKbP1w7oUT8p3kw6A8zW5yiduwFnfAUuU3Fh+/ULj2CYpZ5HOo2n1csl5mKuxvGGn02WtxTcvlmrB3AJ4T8/Hw=
*/