
#ifndef BOOST_MPL_ITER_PUSH_FRONT_HPP_INCLUDED
#define BOOST_MPL_ITER_PUSH_FRONT_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2002-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/push_front.hpp>
#include <boost/mpl/deref.hpp>

namespace boost { namespace mpl { namespace aux {

template<
      typename Sequence
    , typename Iterator
    >
struct iter_push_front
{
    typedef typename push_front<
          Sequence
        , typename deref<Iterator>::type
        >::type type;
};

}}}

#endif // BOOST_MPL_ITER_PUSH_FRONT_HPP_INCLUDED

/* iter_push_front.hpp
98bWgYVsK1whn6JDMP/zf+l0DSTTu6nYo1pf59GUwf6wlAG61t+xFyXKADm+yCr/qv1Aahyus/lYqvXYYjMhZjQC1zwnOHIX8H+JYQIWHIEZVH6TJi/wFewWxo5lUuw9Hh/I9Vk2HuZutrnx4Em96AcHj7pB3SnWrGYLeRWRH8zjluhLL0IDvBnZ5yay7doQKibyyv4LAAjMzDiM8p+Lt/jP76PuG8OcdG6Utav4wssb+dEexvNdBmNJtuj9rQPAcdDcXSzzMCl7AOSC75Ggi2A4yjeS8NphpOkxaaGlob5qnmYnfju5JcpPGVdqMzW5ZdncN0ZKQms2Bcc6CWjxSL8TpU0NriatihCkYawfdu6kELnWz9iAWQk/BZ+D/P3RZ75wcwgCo0cxpr1rSk387F5YFtp+G2VbC0VuCUeqSeehUE3NY3p1lKvfzUOyakDKO1R91agqRuG9vzaueY6dk3Rlct5Ds0SdXb+KOK3PLfS4mcIJcsg47zqQbdHiRea/yK7sr+PCzpFyCWcFo7YYx1O1one//OaSAqH8d6+fUGpm6JenBc113tG7+O5TEBuYNZxGTC8e71eeAiNzM1nmk+42wtxbNak6lYmCa7R845jtnlcLL9m7kfREn1UR+DrZNtaLtaYnrpHsHKmj/vlXfpB13D5wF2gX8lc+0hdaPto/xBISx5y8Ba+1uvOy6oA0NGdOPBKNfAmg9QMdCyLVQpkwmJX3r/nz+EZaa10yPUUam7IHt68vv4um2x4EphFu7R6j2nUK9f6S9/+t29/HZ9X2R3FIsA92PPIGpfiC546Sv1o2WT4D3b7ckTqNV+SMP6yTsGNfEm6uBKPqCqPqSjItEU5si8AW6O4zx4B6NCv8hznyUsQyIxYXpFreVWBi65vB2Rr2AXRm83oKBumqenGgI0W+PFIDBu+HJtvDBT3JwW/qk+WjRBEWpzpcdbtOZ5lzWJw9ttd8nyzC9sRTf4I71U4tgzdh5EHBfGQAdbLfkcwjXcxjPPwoT6fqUTwupPHBgzDZf7XpMAVQWt6HB557K0lT1ZWrS43+hq+W8JxOtpSN0dVKzVjqDRyAfjuJUYL06UNJOV3MAM0c+k9R1E+S65Fyai3aAGeNVFqiNHIA51ehhAGaIAeZ8nxL3CB3FsOUMNauqEhJxuAmhIFG7YbJqBIN47STS+6qp7OEJ8QttyRs1+5qP4/p5U4Ow+tN4dCxfa3IjWMbgGcx16dXdgMsj7/fjNx7J1gO3Rtu8HQc/rLoHX9ZYvZ8FP3p0JXDFz/W9o0maDYyLnGUvUCtWbka9fC+snJE8oqRkUu8sS1ucW6VDItSW6xQj0VxDG8zG4PeOzv0lN2mwKtlpPQejuyZf7OU5Gu5BHeiI50JWPIyCU5x9NxNby0fNXLWeCPhds5cyG4Pr/jFs8UWerjCkzYXjO+SGntInuJ28KoQtM4O+Dud4pZYri3A4YFvipUlk9l+YsfQOTr77Hk6Wq7LNKRSptpJL3lAkdtXLWsnP2idJPU6hkm2Aa1t7T+mM7XnpuRiYep86R9JBXufyzIB/FGc7e+Xic5dHYlLpW3HoZH/Su3ybG+0wtb5dVhy5HLYdSWzgnGapH46E6GmkUq53tGVu3Tu6WzL4iYTquUIatkoK6cnLKMasO6hIyerqvp39y07Z6KZi+VuCKNQKACBHRLOuF6K8tMkRAoy4Uq4s0y7R3jFROfC/DV0bC0hTqVH16dMqFlj1mzE28iLOtVvtEJcGDvgep3sRm+xJiU5KFjZikvEyymVLa8MNZvSd9dV/nv0o50oNCksSzZlvdc446GzGwA9+3gHi3IO94k6Olbj/eRtgs7djdz6WJCYcwnjQ/l1g7tBbPdNVm/hXFB+/N3b9bhIMN5x1tyJ07RSVBMI0GeciwSliphXRhI8pZqZ9cINeU571OVgITW2ttyLak0Mf2xQGPGPMVunN5/AQWpzPACNWd4QyrGqhcxpbTnkiDv07VTZjoJc3Ug36bTckOW4vKeBZu9Z6Tte0X3hQoNtohgc1S7Ds6U9UcKjQ0xRk1IZxiMr82efKehzleerCBEzoqXuJ0QLpwJk/oI4pem5B434HeLLrs7BNbI6ZNsiqwa/OcGXE9fwddICI0mZYa86e6SaPsUBr77kll/DQkjV7NMSWNPjgPu8VcMG5216skaeOOsXCZgWknwk8GMK9EbxQ4aG46R7H2V3V9jOhEvLh941JMllgQ/9+Co+6gw8vXWTfNB3uMTYcQHu+gaf7q+Cmt70/2fLpwmUwoWy0Fd3JhTWdwrScrUVucm02GT48XDiJIfpkX7ukL7q0yzv7OTDTWXEMbUXpRcbPmgdeciAzDCltjDI8EkdUyW5QEBuOUfNCLtBxgKhm53/72x49eEcAkVasZq3p8ViJB270Hr+NymwnQcZT4f+ViXimcexiIYYx2e3OASSo0P37NvW1nd/ksX+yTcO6epY5JbT0P7pg6b+gg40diZp/ywBhcNTuG/eAwmHNxFG7HTc/mma2pnDk9nNW9+G29/HyKyXGEedAwgL90a3N8H+SAFQ9BSS4WOaOrH/zN6kFKCQvx6q/2zemMETpZ8SksFzaUNVEhEeItdN2X8enIeOz09IBcblp11ghUMOEQNXrdcGgeJZe4XD/+P64a4TudWuGJzqADVJKspXC5W8MOu0hLTwdeg14d18i8kC0YU9Np+ACgkPETcdT+GGJzlQCj+oaYwn14eqn08MwWONX8HFtVCIt31xYNVmiPFUV8fASXHsaMqjAsuYxP0dhRaMHh8Djj6uJHvCUNaWh9UaO7TRrehasqNHLBXraTtXdvc1mReYnOW5FK2YEwjL1bRqxskiVtk8dACZRSzYOvRb9SVo2Bbdb48kkaVQfCE65rlQjYrvQuitfuvqLb8ZidAg6uQMoKHsKppGgSbrH1e7U8TBEbT1HdSbxiiDxgJv//0ztRvthqW6YN5RbAdLz3GNKWY3FFyiBqp64PWTTT+ShRtm9lpIT2mKluR+kSJzDvoW9PVrm1BvYOnB6pjGq5zq2RqRQRlnbdoem+4bK7JvhHtQa8tZD5naDFlpoknyxYZJbPOLfkTPLkIOSYd6On23eG0GmDv70dIAbHWePoDPdpRMlj34fUgqp219K5ogU3I7f9o8T7OEQ1b7by6Sz1wT3JGUJuqU23ebMBYedrr7oO3yblpUwtKasgPfUutLxdw7qxKuHgh5oY7+RgAILPfTzUpvv5yvP6r5Se1XyphBC9YoejV52mRYE4b6OW1QCeR3A477x+V1/6w6nKK3dkkoFKxa24dfeoXSvUoSmnw5dVyhZMasMfWzaQs/m83iee/IsJ4nfvMEXa+JxMnmdzfPSCvw8sYrrHgI5YfyauqKMXEI1VKxORt7XZT3q99cWjdPuPQRVMx1GLmBSiRL1Di7CaM25qXLvclovIMksnxUKXohxdxVMvv9z2LmyfOCMEjN8ff0qT1gHlXW2A8hQ1iXJnxWOBvWdTBEYec0Yt4r2FbMgKzg8Izjlhn8jD997Uc8qfqEpYz+B+Y1n6/nsPt5L69kaVcE8//+fVbp+HgrqWTKbsgDdZNSolkTCmgdAAERa+Jo2c4HQqKYk3zn/8s3UQVkRkUlmediKya12f+BM5igWxxez0hRMTP5GjFARbSyGkWj5acYiybgaFjQgIduDFxBanq68Zhtz5PQ5K7xE3Ca5cWf/dx6/O455S0gPV97j4IZvHioSi2j9pMwxZbiOYO0qmumv4SBe6rfPBLfXwKJ6O3o2HrISk2BioYDzkGHO+7hCX8bvOm8VLjthNZl0FHfKez8jfWWvmUWqocPoQcUcSXpo7IyV80XagI/MVy+ssDy2sOYVDSF/uJN7V34zpgqyhhix9Unk8TygXQsmbwtH26M0ORJastGWTUNb8BXfY9MHbEwbTvufDAUIF8fbcmPXd6JX4xNLU6qT9oBEf8pie9V9ZwmOHfdEjEWbJJZkU7tTsOz4vms29MDP9wd70flusrt/Uid4H7z0N5jaxrDYVpewK49LU1VbF561f5m7/tutcezKzTcVcL6fKGvCfx70oQtx5uruWUI6QMmPQz6BgOLpFN/lXq/r/veJ8FD+6LXPkev0Nd+mlB5JOfzB+f/vb3sioG5iIxyoeM6a2CDeG0fpHewpAuK5MRZxdkUxVoq8aGLuNlYcWGq3M1bIT/fWKf70c3IXzQ+r/SIGmL55A9DXRfO81tdmIlRJBOwv2GTZgj0KgCeutxN7ESEOm576BLsQpDPHiuWkskxtd2nop8Hu/JeW/b5zLCYk95QEWKyLjQahJCd62tMs32Yo504lKlQ5a5LOs91kugDR3wHeGHCJLyaoQ1wKfGJNfR4BDgH3dofXQHrjglUMJp3M/zsAQkl/yL2zYLUMHiuyuXjKdw2BqL0rpuz57cTgJzFTk5JJ8+PUV2BxQkaz60B2ToM00kG9HtlkvZEkOnKIHX2dxn4szB+xSQzUVFCiJrdlYX/WgdcVbFwwxaaKgNjprYmxHbKZOXuyy+yzz/pYPfw8zaFiYOsAY93d0LtZxdmeoJEf29Kk+Xglnjvsh8mP02J3g4i9xGCG5N8acGD/4BbuN5oc3KjhMKI6OEt9j6jooW5XoVdAuNZgEhh7pK8e5z3+yZ0EI4+x5lVgENSCyM1SGD/99nDIPQfwZwFzkayhUBZiLEoFWSbBWq2Tw/53Ca46EKjidIcKochdhfZB/M8Pz4W5GTxB3JP/RlGR3PPKj8V/Zrlwa7XE/W56Khl4AY/LmF4OJq9BnmNbsYs/m5yaGC83thSuHCyzH/pp+Ba0l/3Yr2CkwLlrtH0rO+JEm+qKCCCReuvF44BfBdXtesefCdEYgZPiCnzJwwMH6JI3ruTNdLvn/8pBSsWTEmX9DoVI/s3X+sQ/zNiO132JXAB+oBpPnTzrEUUNbDD2H1Jz12Qzf5RZylmyotj4Dvlg/LOjTl4NKbhk4NNmVVS8M7Focoz4M3bT/fW7Odzz0jRyZ6s6KwbjAchX1Qxxf7gWCtjT9DXngDsjQGl6g0L0EPXJuxAYl0mwYIZ1qCN4k2ZqWI2BvgS6wEMBHr9r4TqAf04Vgj0ULrMOFtDHe0E2JR/tJPj155Jay/uk0njo2u4ny3Wr7YDtP2DSvgrO86+V5ErWyJw6y2viVDTj6IYhbUjUG8zfvyjZ+LdHPyoPdxu2zss2ESTghSeVZ5Dm/gKHZltXJl0liYaaPLReCAMQa3mJKbsawqgC7KtgG3PHPwO0EEsdfJUzsLnzOTZ4ASsDH6/7MOeU9XnDNPS5yyiAj7Nb+lDf4WNHjhFZLWLh3j/8VY7u/ycD/QCybZkoY1ufuT5PKrJIYa2pNrqeVXykksCa2ICQ4zJ5KeG6efnheHuVCb66NYsgvFNK4lD+Ifgv1z+MTvxr+fz98uofj2D+tyeSqwPAj5ZXMAnVNqFV9kiq4lk7q+NFxUQBN8P0AldIo0Z/88yXmzwG7+B6Fo3PKAeqP/eHIcOqP3KvI/F7o8xqPTmFFm8+w9f71FX7kDvGfHgvE1O4EfU8O6ex25dvG3WGBj0Vovu7XjvUpCG0dGj6C/l3xtE74e/w5+pK3x0o6r07cgADNTQYFb4piPm+E5vlltm3XqVN06vxMDs8naZfrThgfwa/3vLworqxRQ6thNF8VPyG/pAG95tTUC9uTfo2+U71f9ap/Rb/RWa3D35VXm79DAX+CE6XeVjE4ktDDmp+fw8Wc2rG7rNIqhvewGfrfXpeL83YulcXYHz8f2OoPuWs/iAFRKnn61t5tyrvI//Whk7sg6E5RS+CUtv/qDWqsIV6HeBvKqV85Dqf3io2hsN7NW6y0P+8inOt5pH8O8G4XXMBW6eNOnZbjiU6ngd0YmGp2W6+069LoTM8F5DwpKIAZj9L7n17zEFXNthD4p4fbR+JLoMwlGTDJlvqEQdQsHSD/Cv8eiyskWG1Y/uMYzZRoBRh40Gi7OzqMMURjnvweHSvMoKviVQUI56+yRTZH7rGN1laqOORneyr7h5xvq+dLCfFWbaMCxk7YMlPfi8XlJP+5IOvEBrky7SSV+GPgil3Vxco7R2bXisGsLcrdmmiCouwZfvLcurhM4cMQ0dYWOC42sx6vGlk+iI2VQYpDtjlD1Sk63hV8iYZu830kezNCfxc3LE9rGgGfny7qn8UGKS2NJOoPQgphjISt7l0ldwv8koO9gHmKWP9jf77VJ3f7m4v0q54yk9WK8cfjyeVeE59cNDlqMEFSCrvL88Gq/AvV6jllFddM80IEBk/Yc51lTcJZMbC7T20KIoSSGx26Ka5JuW6ZuW3MPI1J1REncAbNETh/pWxgCAP3s8fHAYnxsnhIQPrswHZ/H+NlX5cJ/gBsCHkHR6yYrlAVf+gJN4xIlAGcfawkMYw0NJMFs7HCGcm+Q2nFgqRS+XRjKLqJJLV82DFsNzDzyObPggvTKxWDyxSDruRKKYm7z2cLU0lgT14L0G/5BuOLFYnVaqlXiaTSXXqprbiSd/PO6pb359Gv9v+BFpL0Po/u0mOoS8ahQ59e6pzH1Ak6e2Rumep9OWgMe+p+WlmYSNKlkxEGLXr01u0K11wq116LVdvEep+MU5vP1xvUgGX3UxrPiJN+FcL7EXHTMOzvw557x+tHBy72jVqIbfoDwLItdxlwuktNh70sm1R9j3bVvc3ZYjh95Hv7wTcMuBj+rhOstpzoIl0D9zphc9PRCPvSDFdGcFIXN7Ly9Z7TfgNykgRlX/jbvd67kRjOvCZfHfHQomOHd2nXJhKWpq5nvhMs/506UXNf9RLcjGvCJywzW0wydVWQwIH9YVYsixKdNZwq0FUjT6IegpZb9HapF2n145V3R2Wtg/FYiUnCFy06fKwTHKYmemeBICe6UnWkcDWhSHKSlmA+sRRh97ySuSEEvC3ypmd+RxX4iPZmLg880fbwUnYTQ27WPom4sr1g3gxiXcftthXECooj7TcVT5+uWo1A6CN/3bN8ryK/01DQ9oZjsPCFMwrc501m0KZeAWAW+hXRSifvMmFZ+GpVsDKt22xLcVB7g7sbowjTDMrmPi4s5I+FPOIw4JN27xQ801P7cjRXNCz1WU0WwIyOltJQHMdEncBc15Jjg4wvlNc8W+VhRqwR5thFoKB4ZpOqcunHu2tK6Y1CGGFHEmyVSQ3C9AyP0gi0gU0RwUB4KQhB9tDvyism480hAdatAV8f72hMULui577ikZIgI+lSt/XIy5DpS16lyiisf06zyQWBxXK1zOeKqGHN+tKuI3fnyjU++qUPXnwniucCmBmE/YKYcisbv16oOI7BMpiT3uT5z33TRCnnHQYZDfOyhgPCUyRTFZ+5bUj09DuH1tbRvuJbUn9K9nm6IesKq3zipfRgwGp1QdG3cLWkinNU5lJYtikEpm7XI+J8YnteIdqJVhl5R5OioMNJ/zXHlm/wHtdooaMk4NgXZ9ERGyuy1XdR6FmsW03wuva8Y5VM3IoqEBKw0F63r/garBUsZgADTt0zpiaU+f2x2i6dS2vS4Qm4AOVDrg0p6jR676YCcZTJWyJBGos4x2Q08lKx+4JydYhII1WDrZTHyCrRAJxd/qfnKZiJ9z/XTl6NaPMxgVx0wyizn7EWoeZkBplpXWt/3afwoNumwfiYFW9K/UpgasAcJBdsw40vQj63zHY2TpCQGFtbu4/l1TU19SkkiDj3URHc+RYqz21BwqCXEiWs4u+dDtHVHQ9+z6kHixypoB+hHGvjf9t7UzLNosxL+kXwdJPkW9PGLtw99+HXA0xwJDBnjObwfTZ0xoBKLRufDa9R10x0uqI4M2C7ZdCUecKJ84K/i2vr5xG/g3bJafg6JGxn5tqxSvYagjVcxnmvV1E7ZCdoK0ZDJfaZbHZQ305LSlAhR1tQOY3fMqQwat/YoWdokBL1le+swum7qmrYp9Df5ZS15yuuj7qq/ZpfBJGD+M5lY39paRigRXYIUm3l77JEzKrhxXN89Jev7Qe1JjvXkJfpVjvcfCYG3UhS3AlqnkwjuGn1yQRBJJcpVvqajBNfUknnQbQKOYBhlCPXp1E7lwPjqAiAwZ3YR//V2uJv0HhzMxdEBWqMTQMZiUDuWWNO1JPPhk7G3fean5eio0HTUhiTO28Mu6lPhocwmCw7T7Mo6CtdlddL8s8T4jqMZ+WaqfcOcg37C4JCYYf76cjwwTzo0N80di0OknIbI4wfIZFVKUhmpi9Hk3GNAWZS9RWksTYvB8eX9qef5WqVsmWed8KqYyFtnBNAmqDAOtKVAW3z8qSig6rRXUZ1I5pdiwZH2qwEQJT9LlEGvib1MSjkoR2Gnj1k7bfOc2R+G3OQ8kUoeOK2wPSAwPiBagOnj5CF74YdTEeB72GsoZFnFIi1hF4sKFaiLOBPhbl8Pf8RIR6RTDEavIsUHmZaKHJaKSBqKFbffAHohaReEKxSFP9p0K+oEi6oNBziAUA6fDIJEOohWptJG8hKt96ekvxxmkDwTftDWpSIlkScHtf967ZpIyWKH+ZmLmrkTeFm6UN9MLx+eLTElCPaqQB3AoYZJX6yLuXZkyQNMjogu9BXL8WtSusTBGaCEOJ/SSH/ssPlQSv+l83zASZnJYA9votqGQhnxmJP6I5VPQFkLrP3znlOOfW9B2ioNklibN23CPsN6eaqHZGRpw2KoVjRWbtmGDiAtSAe1JA59opnMyqQheUUl54/luqEK8JD5YwsWtyMyaIwtcdsKsT890Hx3h0Yr/0Yc0efr8Z3QAKcIFGT8rw0T+1fet63L/oIKmcv9AisyaeGvKk0tTpRGhlD8Uq0nqWo3UqRrxzd4wRYxgKzjK1UKF2Pr/49cdfRrNk8QN51r2MWw+wO2DaeHe46yGEOqw/XMRZir1Sq26DJWsafR8H0zqm6PtZwWlFKM6tD+1bIJPC8kZ5B/j4qUpe+XsgF/3S8rXshgY96E5u6m9105goP1P6ZS7ysUA0nlya+CGYvL0xNKrtUNP0977ZTxfR498Jo0LN2wQkdQCsdZ/RNioVyznCd2OqmFTA1fYNii4tt2kQFmQdT7sBGxnSJ3go6lVoy+W6v1sXGsWK0bY1aOuwIOpE3XbKBHTV1r4PH6sbC1RIUW9DhL4uPS+vDFYNdaEfsUVdL0dISD1sua0X4Y=
*/