/*-----------------------------------------------------------------------------+
Copyright (c) 2010-2010: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_INTERVAL_HPP_JOFA_101014
#define BOOST_ICL_INTERVAL_HPP_JOFA_101014


#include <boost/icl/type_traits/interval_type_default.hpp>


namespace boost{ namespace icl
{

    template <class IntervalT, bool IsDiscrete, bound_type PretendedBounds, bound_type RepresentedBounds> 
    struct static_interval;

    template <class DomainT, ICL_COMPARE Compare = ICL_COMPARE_INSTANCE(ICL_COMPARE_DEFAULT, DomainT)> 
    struct interval
    {
        typedef typename interval_type_default<DomainT,Compare>::type interval_type;
        typedef interval_type type;

#ifdef BOOST_ICL_USE_STATIC_BOUNDED_INTERVALS

        static inline interval_type open(const DomainT& low, const DomainT& up)
        {
            return 
                static_interval
                < interval_type                // if the domain_type is discrete ...
                , is_discrete<typename interval_traits<interval_type>::domain_type>::value
                , interval_bounds::static_open // 'pretended' bounds will be transformed to
                , interval_bound_type<interval_type>::value // the represented bounds
                >
                ::construct(low, up); 
        }

        static inline interval_type left_open(const DomainT& low, const DomainT& up)
        {
            return 
                static_interval
                < interval_type
                , is_discrete<typename interval_traits<interval_type>::domain_type>::value
                , interval_bounds::static_left_open
                , interval_bound_type<interval_type>::value
                >
                ::construct(low, up); 
        }

        static inline interval_type right_open(const DomainT& low, const DomainT& up)
        {
            return 
                static_interval
                < interval_type
                , is_discrete<typename interval_traits<interval_type>::domain_type>::value
                , interval_bounds::static_right_open
                , interval_bound_type<interval_type>::value
                >
                ::construct(low, up); 
        }

        static inline interval_type closed(const DomainT& low, const DomainT& up)
        {
            return 
                static_interval
                < interval_type
                , is_discrete<typename interval_traits<interval_type>::domain_type>::value
                , interval_bounds::static_closed
                , interval_bound_type<interval_type>::value
                >
                ::construct(low, up); 
        }

        static inline interval_type construct(const DomainT& low, const DomainT& up)
        { return icl::construct<interval_type>(low, up); }

#else // ICL_USE_DYNAMIC_INTERVAL_BORDER_DEFAULTS
        static inline interval_type right_open(const DomainT& low, const DomainT& up)
        { return icl::construct<interval_type>(low, up, interval_bounds::right_open()); }

        static inline interval_type left_open(const DomainT& low, const DomainT& up)
        { return icl::construct<interval_type>(low, up, interval_bounds::left_open()); }

        static inline interval_type open(const DomainT& low, const DomainT& up)
        { return icl::construct<interval_type>(low, up, interval_bounds::open()); }

        static inline interval_type closed(const DomainT& low, const DomainT& up)
        { return icl::construct<interval_type>(low, up, interval_bounds::closed()); }

        static inline interval_type construct(const DomainT& low, const DomainT& up)
        { return icl::construct<interval_type>(low, up); }

#endif 
    };

    template <class IntervalT, bound_type PretendedBounds, bound_type RepresentedBounds> 
    struct static_interval<IntervalT, true, PretendedBounds, RepresentedBounds>
    {// is_discrete<domain_type<IntervalT>>
        typedef typename interval_traits<IntervalT>::domain_type domain_type;

        static inline IntervalT construct(const domain_type& low, const domain_type& up)
        {
            return icl::construct<IntervalT>(
                  shift_lower(interval_bounds(PretendedBounds), interval_bounds(RepresentedBounds), low)
                , shift_upper(interval_bounds(PretendedBounds), interval_bounds(RepresentedBounds), up )
                ); 
        }
    };

    template <class IntervalT, bound_type PretendedBounds, bound_type RepresentedBounds> 
    struct static_interval<IntervalT, false, PretendedBounds, RepresentedBounds>
    {// !is_discrete<domain_type<IntervalT>>
        typedef typename interval_traits<IntervalT>::domain_type domain_type;

        static inline IntervalT construct(const domain_type& low, const domain_type& up)
        {
            BOOST_STATIC_ASSERT((is_discrete<domain_type>::value || PretendedBounds==RepresentedBounds));
            // For domain_types that are not discrete, e.g. interval<float> 
            // one of the following must hold: If you call
            // interval<T>::right_open(x,y) then interval<T>::type must be static_right_open
            // interval<T>::left_open(x,y)  then interval<T>::type must be static_left_open
            // interval<T>::open(x,y)       then interval<T>::type must be static_open
            // interval<T>::closed(x,y)     then interval<T>::type must be static_closed
            // Conversion between 'PretendedBounds' and 'RepresentedBounds' is only possible
            // for discrete domain_types.
            return icl::construct<IntervalT>(low, up);
        }
    };

}} // namespace boost icl

#endif // BOOST_ICL_INTERVAL_HPP_JOFA_101014


/* interval.hpp
uX233G3OQLlu/t7lSpFJqZaUarwMczGKpjUZr5Z9V7IfBTLFJN+PsQ/WsHZsBx3ZKARU973wsLVP5dKIPJaw3wZQcB1c0bcXAKN3ewlzOTHQnIliPMBgYocFCtXsKoz0YGi4JKaSuycQhGH4h4L55YY7fRQHDagdYY/d6w66Wd0L5tjhLE+NuhBvosoCAB2MaCF3P0lk0gtmTk/XvWBic29l029V6nXMW+AMx0T71qAKtIjtaIh7FjtZx2I9CaVxSGaMcPcCcFouEUG2jon3wYfH461BwHVBPxa72uLK2Y69R8VrWEXYXM39E/Clgai47JYro6ZroiU/NjP3OWa8lU28VZlEJ9dbQK5or6D/RvA98hWASXoLwzEDho6moICDRfTeIndd4D4DuRT+D8OYdX6gRS91YugQjL2F8p08uevHWPIT1o2RwaPFZo8XRkunyX8tnsRSGpZJbi/XAu7GiwnuWbnJyfOtyF0meHX0MPfYQCb2u9JypdY4r4cDwToCrHsMi+xn2Drc4BWzWI0ExapNCDFp4FLjHuNpOrzC+AtZ5AMic9lLCIIU8R7IyVBlNKIAAiz902qhXPj+4a7rgctE8aFTlDccYPViM9y4Ffc7a6vrEzUYB8IG9JFS8lwub9OFW4wyRmMwxu4y2u8yoShTjsoEr2WSPTKo9SCHaTWpVv7e/IPklmORu3+OEJQch4no+/msqoDFEHSN4VWFuqQEG2iSurW5AAnoTx7N/d0aiiJRqhO25u+N9Icupdic/kfMSibUL4Ytm4Dh3BfY9wSPI6gxX6EzvB0AEs9AsBfWxUleun4K0WHiI1uA80G/CFT+muSu23g4Nit7iPa6zOyBZeB7jRvrr2fRQYrUwrf1PkpRXcZ3u8zkInbTJnd9gjH8ygzsIVqDaBoiCF0xBhJQ7jKSTmx5Eh4eInj4AcDDJ+yhvwceKOCr21HLHj5MUoTvl/jYJhxOeaQfgz0ia48iTh1HKka5ez+PQeWM+pz1WvxMK1AxGGdvGSx/pcTuwIgT8oaj3GM2m02sr/YgrOxgZYBUTfZePGsrJjKvhPHMgScKScxlzd976lRkLz4JiOj2hGr+2w35e1nvqc8UDFh1JpIIiTl/YecpTOLxSE/oe6zgl0MopLZZFzUdJ2dA8nqa7sXP7BoPHUYL1M5lvWwXwAvcycKJaq/aNZhI3MoqV2PEyERoKovfqkxt7UMgcQc+1XIimeHwBn9C5FYJdwSe7zHw2D/CuzQ6ZMe8UhKn2rcytSUYez8LMxMPTMEWhuKFO37Jlv0SSbyCap86lYthnBT7ciVGVrTAwOjwJfE9xWO+lfnnrMbRrblVySMQXhT4DLsSTgsH3BRH9E0an0vCsUYxSB+G9aetBbS1GW9A4YBwmi1yAOLCIF55AJ5QChlXFH+wrXKXHSASyUEAD1R2Hd19lkaH/prPIDxobBJ7mCC2Ax9R/B37H1ZZ2BoCxyUAjn9gawgcJwA4wp1T4wbYixcR/MeLSHlGmsyjOv/N4aMZ/vkL/Sai4MQkBYe39NJeVulE9nnUK+DZbv5Pm/HiJTy/GCrhH7PEEz+jErWa37PY3NSs9yWMbH9nCXmqtfUoj9OkhdVPwqH+V1bmQHuMu0qSatyQJ9wnhXud9WhYZmJ3iB5PtfrYZ0gNn4P9hPvLWONRuz5D1zSDB+VPvkS9CcgJ3JMqR3ib2YlURV8d4QlzcNPyhkYYcZXYpJugo9LVYnQN7rVSa4l2YKgmpdwKTxDpdFCo9lqbUp4NTzLoiYBPcjHRWbEZHgr0UCSKaMJqTGtWW6CUY0K0xnixk0Lp92L8MMsELX5Y/jYMFZYHP+sxGlgBfImc9LEX6ZHSZsPsOWiK9NI8qBucEL4gBqezLKXJxGTlB2Y220dL29lGNeHem8RKnl9MwfINrOL5JkSePGJ2YDqbrTSboO73zUz2JaZhYFm7Dh77hiYPbUmwWMILei25eP5xVJAgWpY3FkyOnAxOjpr+qfUMrktoGssCqhGhM9le5KT/6s6znb3sdRKeRF/MRRMa1hs7DMRALzJpKcoaVa3Cn4vDZ9E0yxh6rK+NyupgJviZn8g/2dZDgfi2qP7FUf5U3qKzbw/MWCNv6SpAY2ol+JzVVWbf6f8zjyO2c9979jNB7tSN0GdIg77OrgJsItpGH3s+LAWCdQMS7/k90adwxzbj9rDzf31KW8yT+y/tudII18WEhLYYyTCxITcuqbwxmDctkghK9qDNvCpzteManX/srlnJc1ate0V8QYvW2iFdE9zEumiDtdBKs3+PoZUQNEYQ9EA83C6x/ZGDvgCQy1bqIBs7gO+pPmCbXiXbt30fCgOb8aLO2Vl1xeC+DyeHDOHzBvJo7bqP9DtUeGpMxaCKHXo2Fai+IrcyVXGJgUuxzcVmT6JWIu2qv5HNUGahBsklYkKP6RRFOvBPbGqfXnfxmlcO1Yx9aAgfT46iZbUSMjQqt0vLn9Ev7W3Eu3X0fG9D2QIm+zH65JcLc2CJWfwe4dT+KiRY/FfsGSwGkD4dPjs5NJtVWtm0+AJTprYiBg8BI6t7DACmLQf3tkbdTHHhRZQozsBkSgf9M3ysV/350ONzUH3Ta9/KN/J4WszAU0w4FkUSgczio7+h2Kpy6GpOn1nlLa0nELiVHjjz1eqSoYYw2G14wAiFV70ZSeDhbZmMcHHqXfKJ3ZOIJCjCJswiUQqNnw6fnwSz8FpZBpynkbOArmLvi8LbzPQIzGYyn83Aea03/0JG6aG3q/tTj65DIiv/IBDc39jxL/loIWaWu65OYDC00D9oQ8dm2MRq9efJWoEsTuX0wscz+hEbUtu5zGaA7WhetYmS+tx2PjXZ9aQlTMryXJyt1CU0yPClgcbdABo+DTS+D9hrqhbrInP1QF6HeTQopZd3ppWH3X7wAx7Jb2/IEq00soSWvABW8L8+oOiBQDvGg0cbG3AmDXxW6VAWPpZN7GMBc5kpTBd7GqlKX7RFooCJcUZRROEFcSdu/GVhHolCwLoxG4yNeUys/UVK4Y5MDTwilsT/j6wU06hfykqzUfptIvvEoRUOb8vuZe2IPmsRkEOrot1ougdNOAYmJqkVHmw3g3W145XOqs2s7iEHW2gCsipKOeiiJW3ZRKQDxWV6xENZfNU499DGTYkmWTzpYfnlaRpB5VCMvOdiXB4MnOoIrmOVmLnBpEzDlUimcXCLWnBemzIbCS+ljHz+lSrUgeYpPkkpMypVJraR5o/5L2jOU1h99oLwe1lKwKbUZydusi3FDaApL8X1p2/a+ttQbpLLGC47K0Z3Z6fo9UXvQcqUJ3fdxaaxIpF76hvoQBZJtA3VRkr+V4TcdLYGkVE/5ehBqjlPff1M8iRk5vfn9wzMYZMBXyJCZDNqE9MJRVdwWX8thkmUlHn8i1G5E00kbRQBz8pnbVHKUJSVrVRJig+YARORarbeEfZTt6HqdBBXWn5ZlxO7J+PU/lpK/+C3Ab7YM+gibHVhcmgmBRZBBJ6ZdkMkxOfzEy8g8uH8n4ADlF8Wi6CaUDbwr+GEHLqMPYSoJlp1InZULGIfn3on9idRuCC8okTxeaSnBTrdMxjpoRCd/n9IdTpJ69SYxJEaaol9CNVZxUu6aMlLuiLFkJ8A0qj1LOIMuesexBeJhqUhIVGqa1w+Ah+QMC8J/z62BbfRP5+VIRhcw7q149kfuiRahfb72vlclzqcW4PHeG2lzJaosnG4pAPRnDoQxvoh+h2h4Gus7Wk6D26A0geWEbQ6gbi5vwIPAavYYKrxqndyRt+mQT6mVgWKpm6DaQTom4JPLefoYShfZuuxEkMyqutNEmWQtWCm1LU2K/9A96b87fAl24CCv+VGoM9KeKpgeJhnoGEbvD6KDb7W5sDiPZsxjGwU7q+/PgXPnLwlrEUvwjsS0RdtVsDGHWttbnj616fiYUTOuGKp+UOpLbpX/s2e36/xJ8Ak7/Ub7G+uEtknLFbUepoIMjX8SuJlXo4VMDiYkv3UKoN9h19kF9ieZKkPInvlLoxAy6Qfs4IwC7aZhY8V+PJcG44j2kUfZZGTcfHHxH1CgeBXmB4LjiqDL1veZ/61ZmUtPWNda6lEG324gJmFd3LX9WiaYdCms4bBjkJjvJUFUAZ+RdvoV8v7R6dCWTgNV+G51vbf/yLmyckOX7CGpnFYVr5pSsIxkFa4IUDZ4ceFWIehrDVBU41vQc5n82UUirOzTfqaAWnklZ7ORyUs2naQxQIy5iN6VLwKfrvRWG01L3bhQps0Fz5Xt4n4kQFFeCf0ceHVDnOqvbueWVgZ+BlQjYX0MzBlTWebCdtbBCjo084uE9ZA9BJto68X+jsMrI2ACOi/XPx4U8mAJwRBi0R4WIDfFhi0NpVFUscCY34/EbkY3zW/Zz6sWGBCR8nUaUVOntfj+ILwGWvoj1C5Aqo09rVPo+Aa+TuXqi//KlPH/ph2himUI+o52wn/0nlF5pMMzUs4AsZQXHI3BuOtjXbjuUOhg9WnyRfhhGWwu02sydxZ4jC39USXOcxw8ku2LMaLwKv+8MqzZMQED/j1s6mC1W1ZjOHiH+CxR/oEfWdJrgWqBnMtWPXpJl71xmTVp5t41SeXsbqnm7BqnVY1S69F5bfxsTvDW0UtJH8dSnmWoap1+dKGpJUucJeG8DFDWw/d+iZ+2/uN8VLR+qwNPgyHNwLzPxV+H95Av2/+LXTMhbx77VuhUVgKJBujpSa+GLWaa4LZp+WPsABMw3oshvWwUSbxHyGPfgY4toQYnEUC8XkkEFd+aGaZ3oSRwlXB67MjXn8z9ZqVvFQBS4IWd02iiAyaF+EdduelChZ8qULDLcBSlTy2jAp6hwoSJwfPWfCxZVQMtRoDlwOqz/X40PLj7o8TiWjFY45qMg5p/hhX1so4u2hEuxhAgNMAXTqJhaRlhuuBi9fQm0buysRVXqrUS0q9kWPzBqUUr/7lIyOWpvQHt2n6A1z//P64bvfzaF0tKW6H4s5V3MsUd4XidiruPMV9s+L2KO4SxV2guG9R3HWK2624CxV3k+JePFLhUV2LzBEwSZZx+aNOlwS7EsnkmZfgsh6PVzJzLsUkd2FaRrYdo7/BkTi1P3rb9hQ+QuirNKYYKKBBXSYgXitR5xnIH8EIBVK0vXkEbT8DI7shg2RC1moWZ60WQnPIW/39jWKILOC83DgdnIMcKUbj4pBZud3SmJ7SB+7zT9h+WiLUoM6JHFw5U96S5SHRqLqeU7Bl5YEBIH56aT9PkO5CbkeTaN+ewfwEZ8rKiOJITA2Nuw1eCSX/u2JHxLa9fmCL2pdFxY6EbgDu9PYKYHAmEWcidVarV/FuIwn/VOYtrGFxdSZ/wlwOVulkb8ZdhaTevQFFvS4Ht8/vHeJXfOyEivkTta1/Ck1MNQbm1fOUr95lxsB7LiMyLLTc0PrwFU9jQgIpRnPkis+mAH204pVG5GbmjLV5w5saZ/PSm7KyVkx/ihgo8FW2mRNV9jMha7TSBgR7yMoeTxFUvcHjuDeoBfY6tF1K15dJxFGzUmB3vOz3xOywlwqR0IKR1pvZAuoywgk6/0zmKoGdnMoq3dWsT/2Ntu4RvFTJGl/i2qo/UC7Ht6IRItnqCMqMtSyhKQ/qSBZqZNJ9QIt1Ir326EuIPPedYRVbbGxrTkyp24LBw633oImt9dT+hXjHEDBdngKmyaEZrF6XpF1LdfWEHDsrpbZ+VmwCGKpAGNpMMFTRXsFMmwGM5nM++f2zSRiSGfn8xtXd/BENDMnKKE4qdYEgFwFH3w5gs5TdZGZeDOQMq1ZpQq7oN7Q+x4HhofWZwrxuYnhuL1G87kRlicbvSCP1sXDfkp6YlZtZGFedTfOyZ/kuvJCHa+fF+1ZCTsgtKpUmFtZYS6Abh3bD666B3bj8fHICNvZjBBBmqM8/bn9L0QKbyQ+UY4D5yRquovtJfGgHGuwQU+EoQoFG6dHTmky4Zeqpd/clWPwURjPPHsjchyKLbF7mDQJPOOkrs6DnCXj9npdDxdHlJ2IDYjHbd+oPsfdE4SO+Ga4Cv4QHOrEa+ZGBS3A3RkhJajlrVh7YiVKQF7gUhCX2JIpJDnKWsyq2UawKRxuxP4rCQNtethN2s659GRM7o1KnU9GPgTx4/iuR9BCsVz2IRkioJakjvi8f9VCWBaRfMsndb2Og+OMoSCosYrFvJFbhsSgM4JSnozQedgXOsQGZRJdJWSCyn9LuHFw+BAiV7qLwkSy0zalMAsLSIR8hzX6gyszu57vPnl+WtutlyV2/f+T54zt+tQay9w/JDebjeTan9BUlj+luRYUrpjbdd0Z+eauGut9HVQdVg/rF9v3BN5bjKAiqy5JQ/TL1mlg6CqxDSbB+Rj/8xm09ho7SQGpiRAfWihDMqs1e9ttlPOmwgWX42GZCLy4jyi84emnVpmfh/czU0EslmqR1UaBwnOVa+gbk5YO5vDWTvY6CS5AWY9V8pD8lDs8llAPWzVlftmvfIEbCLVlrCaDcAF9LsMehPdC4lfTqDhZCVaNUKwxy3FqPyRVIEWmUH1iJBB5fz4o2WwQzeljxEMzEgQHY32kvsZlX3QYjPgfL+oVhvvEU7R7cQuHjRsD92u06u4ZvkfNU6nbF0aGECcXMB6HHVd3h0/qQtPqIvkO6vPgoSXX61FW8c34eStv6EbXBYZCejIpPAhfPsSAchrn8MPyyWn37ZPIwGJOYoA7ou/5b50sLaBDyY7Fq9fmTdFXyC2oECfDTk8MGSQOEQwTgllS4du+gQ7QKiNqVc9nthSzkKBXOsu38NN1eqIQcbJff0Hr6l7AohE2eP0Xbns2BB25h4IGqkydMIVDpXz4ElEplSfKUVSaBsnUbwmFv8nyVoTCPnyy41XxJsOtTK6Cr5NW/m5RFxtTtX2VOngUMpgDnAUB9OH9E/LxqwOFuIXy7TruKB+W1Mfvujgqeu5corG5MBBRtT7IIWj5kABRc+wzYqnUFeIfuDVSwJtOAQPxTLvFPueZAYVt/NPj04oAIf5vCN+oCk73qtWbODWVxsRXwQrORE1r0F9isClseZ6SIHkXVrSZhiXPlOiYoMwbvQwuh4f6KZFm6zGaq57MkdkgJWDuWS2wdzbAbR4mRmt+S1/bYd3WQKwtwsxOBRdr9IvBKX4cvni3wJVd76umBH5fPb3EiUxWD4jOA3m9SBc6NEJFf6gT+GsoadNugbBZ8eabXZpy/hbhPpLi7t+Hi3YRhPC3R9eoQ/w8zNdIaWpigXO+fMn8Lji+wAjiugUwgrJSWAs52+RdFEkmWKxPIK+Kppir3mJOGSMBTcVbJNcQqGTlPBazSS2msErKXxmjFSxXVPlzvD0i4mp/QGE/LEOOZ5IpMZEbR5UESu6VQaXEoLTAwiybnakFzgNISnjNyXH7o8DaNH6ogZshDbFAdMUCLifVxNvB4rRKpUM2syhHpZ4+TIU9ZCWrSkkF45O5+zKTYY6xHnYOXBLp5kZPBKeELYouBlTwPWDMwi8lAohfgIs1W7jSzLB9nPO/fhNyeqmO3Pe+W274KDcHHDzCDrZ9XyaMqXPd49Eb0OS951krrWiY24XVDal1a12eBqXzW+l8dtwDWSeaLkp/PQ/V3uCcDaFfM982/
*/