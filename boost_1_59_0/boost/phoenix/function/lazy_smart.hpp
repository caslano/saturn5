////////////////////////////////////////////////////////////////////////////
// lazy smart.hpp
//
// Build lazy functoid traits for Phoenix equivalents for FC++
//
// These are equivalents of the Boost FC++ functoid traits in smart.hpp
//
// I have copied the versions for zero, one, two and three arguments.
//
/*=============================================================================
    Copyright (c) 2000-2003 Brian McNamara and Yannis Smaragdakis
    Copyright (c) 2001-2007 Joel de Guzman
    Copyright (c) 2015 John Fletcher

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_PHOENIX_FUNCTION_LAZY_SMART
#define BOOST_PHOENIX_FUNCTION_LAZY_SMART

namespace boost {
    namespace phoenix {
      namespace fcpp {

//////////////////////////////////////////////////////////////////////
// Feature: Smartness
//////////////////////////////////////////////////////////////////////
// If F is smart, then we can refer to these entities:
//
//    functoid_traits<F>::template accepts<N>::args
//       A bool which says whether F can accept N arguments
//
//    functoid_traits<F>::max_args
//       An int which says what the most arguments F can accept is
//
//    functoid_traits<F>::template ensure_accepts<N>::args()
//       A no-op call that compiles only if F can accept N args
//
// We use traits so that if you happen to ask a non-smart functoid these
// questions, you will hopefully get a literate error message.

struct SmartFunctoid {};

// We add crazy identifiers to ensure that users don't accidentally talk
// to functoids directly; they should always be going through the traits
// class to ask for info.
struct smart_functoid0 : public SmartFunctoid {
   template <class Dummy, int i> struct crazy_accepts {
      static const bool args = false;
   };
   template <class Dummy> struct crazy_accepts<Dummy,0> {
      static const bool args = true;
   };
   static const int crazy_max_args = 0;
};

struct smart_functoid1 : public SmartFunctoid {
   template <class Dummy, int i> struct crazy_accepts {
      static const bool args = false;
   };
   template <class Dummy> struct crazy_accepts<Dummy,1> {
      static const bool args = true;
   };
   static const int crazy_max_args = 1;
};

struct smart_functoid2 : public SmartFunctoid {
   template <class Dummy, int i> struct crazy_accepts {
      static const bool args = false;
   };
   template <class Dummy> struct crazy_accepts<Dummy,1> {
      static const bool args = true;
   };
   template <class Dummy> struct crazy_accepts<Dummy,2> {
      static const bool args = true;
   };
   static const int crazy_max_args = 2;
};

struct smart_functoid3 : public SmartFunctoid {
   template <class Dummy, int i> struct crazy_accepts {
      static const bool args = false;
   };
   template <class Dummy> struct crazy_accepts<Dummy,1> {
      static const bool args = true;
   };
   template <class Dummy> struct crazy_accepts<Dummy,2> {
      static const bool args = true;
   };
   template <class Dummy> struct crazy_accepts<Dummy,3> {
      static const bool args = true;
   };
   static const int crazy_max_args = 3;
};


namespace impl {
   template <class F, bool b> struct NeededASmartFunctoidButInsteadGot {};
   template <class F> struct NeededASmartFunctoidButInsteadGot<F,true> {
      typedef F type;
   };
   template <bool b> struct Ensure;
   template <> struct Ensure<true> {};
} // end namespace impl

template <class MaybeASmartFunctoid>
struct functoid_traits {
  typedef typename boost::remove_reference<MaybeASmartFunctoid>::type MaybeASmartFunctoidT;
   typedef
      typename impl::NeededASmartFunctoidButInsteadGot<MaybeASmartFunctoidT,
         boost::is_base_and_derived<SmartFunctoid,
         MaybeASmartFunctoidT>::value>::type F;
      template <int i> struct accepts {
      static const bool args = F::template crazy_accepts<int,i>::args;
   };
   template <int i> struct ensure_accepts {
      static const bool ok = F::template crazy_accepts<int,i>::args;
      inline static void args() { (void) impl::Ensure<ok>(); }
   };
   static const int max_args = F::crazy_max_args;
};

// These can be used to make functoids smart without having to alter
// code elsewhere. These are used instead of boost::phoenix::function
// to declare the object.
template <typename F>
struct smart_function0 : public smart_functoid0,
                         public boost::phoenix::function<F>
{ };

template <typename F>
struct smart_function1 : public smart_functoid1,
                         public boost::phoenix::function<F>
{
  typedef F type;
};

template <typename F>
struct smart_function2 : public smart_functoid2,
                         public boost::phoenix::function<F>
{ };

template <typename F>
struct smart_function3 : public smart_functoid3,
                         public boost::phoenix::function<F>
{ };
      }
    }
}


#endif

/* lazy_smart.hpp
fR04pKCwOC83NzdWrKFzLKOLfERlM6mDudllN7RcLvyRfWfu+RMjohttHud6dGdhm+dZwt24t0Vopmx9gzXPgXNt+CaNUmYUnIlyrGEP5lDpFOXL8fzFwIA8mc2QpinlK+Pt3zt1EI+2tKwsqjSgorwc/1lI/zDoylTkbdYYWXd7rdKmWWzERecLzhjuvO97O4toush2mY7EhIQ9WLOIS8tanOf5GnNcRhAabimUblo24x3ryvGqE7h/oUL/V2ZmtGIGX2BLmUj2b+6roqz7UtFRkeQKNiJdV93G6jGTqxsD4fLBDNsBqiw6LgVttLoDVtNIw0+O357rD1xG+eD0mdAUVTyao7S/TB1UeHeZp73SSmnyu0WT8f6p4IlsRbMNo6+THOH5EdxXn+kducf1Mr/OJi7MphoO2viNfIvcyFFSx7V4l/Vm3f/DnBC2O67CqrtKF7NKGJbKO4WH7yrWhIeBs7lhwDeifqi3wsmBbHGWQT3K+KrSssyiQMLbvbhcE4hA7P6yO4XiGEvhNysWpk9ot2r3Hulp6t+mW3LBe4FF1d+tfHipbldkpk7XWJ4zBGrH2JE7PNBvHWdY9Jq3eYIA/ffJS7LvVuXllYQVcgpzCoNnU2zmW2gih8tynzIPskZziZOXWHNlxAOTDcpz+/0MdJGfm4nrr9RQ/J95rN3QrZ1c6KH6aCtuFaFLCyMwktWvy4xmq9QvxvZRHWKp/N4J8JkqN2NjCHCAG0nojpzrk+kebVbonCzKA9kHbvelx6t8XywuadFPfyleONlhXC6SyvS1iffbC5HwD4JGuO5QyedqvGtpjTm8hNulPuB1CLUoZVIBYz6jcmw23ZO0GKv6ZRfXvQ2DKDUv6FU54fa2GcfVQBn0zdMoGH49d6j0XP8QVc+uLyvO/BRNMaMISKr2LYTk+/vn56SsxOLMErVJTRp5YcL7tW15bc0ZC8eyfO875fAv+HvDgrFopAru8+4f7ihuvzo78GAdv1sT/b7KUyAV7DIaPYWKZifH1winOZqF6b0SNZ6oSk1uY5kpYO9iBz/m9DgMRLKJWd0Iqdxw5I0PuX1t46fwvmXrWgpESUFovDHOiEMX/JLx2fg7DswqqvI9JH5aFPM/xwjOTupP7uyAK+SclC/JBDJvdin6Gu6OMMXj8LrTum7G3IlHu3QwB2yQFs0yUc1I7g8dg7jR4lyeZEjdWjeYuogHzFwoozOMDZoOwVwLQS5Y0VbWIIxUzQBndf8/p6LN2dG9xmLG8yCTNRl55i4d7OmNoudW89zIK6roC+L33DOl8A/dfkCqlF8uxIY8LqO3Yl/XqGBDZ93tfZbwkBqq6F1r4LUS0vDzyrqH5GbnmIf9PSBVOeBJgsLf1j/tIaAFJ5T1rmISZBKLekDyuEgf0DKL/a9jxTZngM+xXIBguiY8pIVMi+ioin+xqV/UCicscPmNGzcXf/2/4Soju9FwKf/kfKgBE0U6DJ6Eht88Zg+ypi4GtpCnKi8c+Y6xdrdjrh1MOcNJPSjljslo/1BhZEnV3vlntFCnhv30YUol++mAABvzj20pnr8qQv1lxVMpvEnLJY7iplJt2G08sQubDRDgv0L0XDKrOsD/s/hITv7qz8eBYpnbSrsJ4nBDOFm+iZNE9oESoUFTwt92TH4SSmCI9olliImZmQRLKxWWJFpOlanWWcD3K4iIZl5LXOqN9UT62+tTxVKzv15xVv2hr6osLlgUz1+/iZ3d8LGxhP6E3vAcgjEnZmpCUpjPgmhGojtkrQh/z8ZRaalNyDUx8yMkNWElgRHdXdj/fiS5neVTuRJLRmruxWUSxJop/Cm/LMdilnMo9CK+f7r7Fr7F8MLctJSjAg0+/qTiIXgL62H39kf951cUj4NvcTHnrSV7UckU5W6nrT9LdJOvEjWorgfDXb2EYw5M6GvBDAW/N0A264o8OiDd1AOjb8dTVQC0b7ZlE3nBoV/VigOx8nC/qjW93LmQ3gMoDz/ytlU10XlMzw1EPBHBrMIxsQlt9OuJl0r4zoIyBwMCOzuR0JwpcY8xeXTwZgwuwPVYqiOSh2XoNrSREKI/JRVfATEMBW4Qx/QpmCwB5VqxtrV1ldjGE1Fczj/te7OLTRzU5U2nIGbHsoG7VhlgeMMZrThkaFAW5oIb7dvwQxB3gD3jAGBumHmwFqZpXI6yWx94wm0UVEMUnXfNGx12NwEOFzpgRwHquFNEnxFCiQb8uPhGF7V+d+28YprVZXK6IZbBMN1QnlZycLt3XhW6B79oGTDLhq5ugaWjE0Z1qiktIQDb0jsLhTSrNngPuUxlXctTSjpLh9iBIN8LZ/ItyaL2LWZD590T55/O5SsCpldkQghAejXy0yflumMwFyixykLMwgUW8oSXmjL8EOyTt/+UMlTiunydjDTWdJwFeg812ssgKUNyGxHyj2spLFcw6G2fKHpKcb1HktmgifnadnHmzgVJegkLxzvzu/lzd2UpAqcZaD9/S5bk0CXT+AnFLrBsNdBOLpDU57lfGH6tcANY0poKkMq9FM39S5G7CEP6YYZ5mAP4WVQjTjM5So7WIIJqC/wwx0Exl13ohsqUWqjP8BdN4WI2N9wtdxoiwXngqpfv85t/Sc6nLsCDsKe8qv6pw32FPFECbVNU4dsJi/X6CsbKbxXpE+3Dw9nfhbdPg002vmooZ0aeWfcc7IX+3zTrxWsSGivKC7zE0OjptFVMXQu7F4U6yZMasRRNOPbhXrkXFltE/4m5Tw3RvdU1V2AzKO8wCpnp86j3Exzr3+npqStUB6BgsDtYt6pi0PT+UWELpxkS42IhZGpWtSAx/mJwSYQmrSE9lwYBDQAo+l0kPInwUZYjaT7uvWy6OSYUTc1ID5BMr0EEZ4CCD6OCkI1bfwC4/eExogn+6HSU0hcrazYoRDdg7045nJ0HREIzh9TzkI6fx4upz3OKelTmTi+tFgKeSWMmHKG5ADU0bPkQIPdfCrMYfpvPhL4meaLa+cOfB0qLZa0/t5Sk5zryxTCsM9m01ASFAV0GTGNE+1oUM1bYSRUBZu3PlL8qPj/dE7KfPqVXf4VUxwxgpQBrhAYlDWNasTTB5g28nhVZ+m3nNjbQ1cUJxVt3Sg+iMnV3958A8GvP4EtmZOOHs9Qy2E9PZAeS9MVnFP+MXNGdX/l5C3+BLgelnllIIibGYfrgNwrEqYdpda2//HAjgV1qqEq8fwEBNva+y1k33aiuaYYXmKd2GuA3uKKDaTrKnbaL5B3znFsIlX5xc4kXAd7YqacNQATHtuuzCogQV3Oo8jNKZvfvizX6p0o8l0vCnFuFoCeRA0zHnX9UTi77L9qiT3uifouyF3ejBZAqZ6cou/N22JZizDHRJdvkS/9Ul6gOvdGkfwiJX7kEFBFnYOtXpQEm6VN0s7jTTh3KxOBWABbO0JYL1sYRFFLBB0HkhFE+FgCmxBEd+FYY6qWsc/IdpNvQxqsAwCLgMEWSAl9bzDXmTUnu34BI+Uhr52VjUsEfdDGdHvVzHE3KzVlF46mydQdjCZSpLwebcg/izuDbnrdUYztoRAqcYzPHhfX2y5/0Ol0FK/QaIhcqDRVOFquqdkOW2y3cOoxSmza17NguLvwAd71+t+/Pnt1TbvvIBZy/LGgHUx0M/aKdwVVXV9996H3EhV8BysB0/emmu3jj2bAU73z0X3R1y4a/trylylTc1Fxd9Q0TWFMLeEJRbXsa0r/QMpZwa7lHcujko88he+3R8Q4JBf1BxqSYpgtMzOJ2EC6UyQ1HCW02yztLRyv7wcRFt1w+QLNi+9MCvLW1RWc1RmzCJZ1rhWfmp/aHNN/cIVhiGhWtiTcDb9cQlvLI1e5RZ3l1VVNUsBJRb2PH5a6SFPstG4UxcdpYZQd6l2LXCbtWeAYEAD5Nzj8CgjnfNLNCcbvEh09QqCqA5emBTWJPgD6v58DNGXVqAdpL/WfqvsktBKzo5LVlfXjUJXG5Xod8NqtrgPoQA5CDjWOPourCeFvuagCOOPHRH1USLcKNc7+pB45k1EXEaZR04zQG3xlBw+ndEkzZx7N740g7yHjNewB6f0PQ3tFpkC3Y/XvPj+wGLAJ73HWtOJXxfLi7tDdV7B5uzm3+MjFPBscUSLmVYQfUZJ6F3Ot16PPp2PI5s6WN/hsKcf7ld3Sqb/s/5QW1uLPlUsRYJonMVtq8qpRhKfujKTcAAiz906HYZDprUlvpWJXMULk/HQ8bvuKr8FrHdaGnZTcfwCssZbMRSPIWmpDolC/y8nGEdai4nUZ4n4DoV0dzPEauBcaofIm3Hwp2hx0LgVK2LJ7leNG3f/HxrUzUUXY/7rQDLnvx8vyozeMM7+eiH9iKup2hB+U6Ul72S/JeovBjTV+TEXjnySeq6L+jb+Gj8ZOpjpWDL2ou4YUX++dSOE0Xhc9P7PV7VfpHw9qA4hansz+8wl6zsbhe81dNGkJQ9p5VNf/6hc1rovq7wTS+TOMjB5+S0COCegpenB8QtCLcice7RPij4knK3N+hob9CAFslHoaCu+Hj2XHrCmyP7w2WFpAVe6Sd2bW8JL4Ve/1OUQMrBWfUGMPZFWS7Hj27n05jTTIlR/mJs6sSesg2P30J94qHYqevmI86CrhazoskXwKs30edZiZQ0phJ5IU8tXygp8VL0EcteaZn+iyuvyD5x6wNFQVN+C5qnDQfp9BN/g9l9wFJh8Oy4bwJ2YfWoiK5L+AlV7Rbl2TVmXwhxmJPp2ka1jJlS/cfZ+5tRQVFhcXFsoUtjJmOh8SrLXaS9dSjbhblw6oUbfdPyidEYPi+9glIF0ahAOj/p6MBVVjlv4GRMfFvVm1TAVUuXNUp/9XSAZPY/LJFZ8fAUv6AXSwRr2f5axKdYeGPIe134LdxCNXZ3RTmOM4Yy//09z3WmMVWgTaMyFhoE3sEN/pAgl4m5epJ8pBoiw9+IjdGZWY/Bqe5oXDlesSErHAuovH1dVkRE3NA1lLhhcQ3KLg7gXd7rpBgHARl08tgWSgnnwHuJecEO8eOQTGsLBGTW3jBREUVQTzqZDsGbkG8QNwe0d3trIhhu1hZntQdSLwmd3C9Av/JHfss+az32Di4UI1tRoBtEJcjSXlJiwq4HoYj4gxuOUS/JEQNaDuj6xFUFlrjbvHcuEE5LZo3zOKJyFU2UoDwUSd98N6yGxOYK+xUBqmk+XOKI0WKMh7D8lElc8hniHL/5wvYh9JylsJ+XNw8TTunonnlte8n2aRKyo7ESlXtfJFi6wClNlyNqY1JhunOSYZZ2GTxbCCn5bRV2HlhVacPlgOJv5s7xcqP5/u24qnsvPxB/mkvRqMCM0ajot1iz6nhdLD6+JHX34MX0MwRledMGtXDVMtN2NHrE+3tbAiedfFhT8is+9WOIKiiH/QYB5CBFiZSS5bFcHmLxY4WaMaFE1dih9S/yyOk1ls0axWyaaBGSD9YtEHUs204JqoQkCejLF3QlGzYVp14juIT+R4TEhJ2knlHVNFoExCO8nnetteQmzfYuM7Z6jsR5TumyX7x7R+8llO2vXrUxGssbAar3U+vNZeXzg5fjY3D+QzINvoFD4hf/zjMSL/yT4j+Ip7GuyiJevCDpc4oFdsVu18tAirvnjEvQwPVsbB219FGLFYfnvD7Fm5CMIv9S8FvZp1hZ+ciKXxXlF3CVcectpWuqLBPzs1KlMZV0RGLfRdd06wLgD7yB/JyZ0gdwd/JDsQBnuqN4Q43YgHOl/DOri3UE84utwedLnRiEcl5Tr6Gb1C1z/HdBGvQADj2AqCLbA3axd6c671l4WfU12dXCUTrzFQHw/td8iaENL/XuhkBJyyepO13slBq4+wm7p4B5JD1J2lQhmixCfTnYlcO6ZjXkV8/cV87KsHenPqoKmCUk5zp5ac2rw7ovd1JC3DL9lpEm+NSmGT1/sfZc2DUv3aEh55HxoUWSJ8/bWWJdeXLxHwXAonBWeQdkcsm4NnnDSTpbEagOVf7juhS9mkD23+jTyhI/VkD9D7Hx1kDNczCWW8D3o/12h7drfu0018Hex7l/QOwFP+cfg6sblelqDPbxPphsUm+0ulE6I8sSus+Ln6vnNf0oFzE/6BYXNIGC7MEPmMpLjWkjYj7/JL1r41hozpXPeG5AMQDUy2FJwHTeIkv08JJ0Gnxkttd/o7rQbaNjoRSL3FZ0MYNl2itL4ko+AGo12aFXrGpLsN5lqGQ8cAH+20J3xZ/fQ5R2/le1Iw/Gd6/JzIjKjXwtUOsNmjY3CUsIb1pbtd6uecUI/17hz6KtWQuQJLnO4MVf/5GiWb9873toLS6vn8zKeZiEy99afHxHQf0z2KGuWE/fpnXSUpRayoxpKXhubCpJOqZUvX5kusWCwdz0Sv8m1dsYYrRJgtX9W+jTdqBPbaG1DHRu2cGxdvncwqzGVvIQrettW/+Bzz1NiybSt6/bTrDWUIeNycpgMdm1FfOLmFUWIsP/mV8oL/YCyDAC4vcUQX8Jodk6bADbrG5JnuHWT3DCo9KzW96RiHPVYVjPgb9c/L8dkdgKQ+c/3yiLv3KU9CyzwYjdMa4U+HgpAKIALCZg39yWWSoulPoryRqvwYHcPKWArpq2u/BAb3c3jpBzyjtMd3Y/vfg8EnCR8ogp0+PTEE33N5Fm/BrsgXOnhc1lfJnI/nQJJWjKbUWtLFq/dDpv9z51mNL3J8b/dhiqoiVE4u/F5XMFs3ckszaHJymfX6Jq7PZyDmYbveFfBP//s8Wt/CP/emPWvPtZTMs/WGqVW5ALcpdCTXJ/vHM/OP5qPioJWZyukgx47CfCFCQYgQs2RA13fB/WBfqJN6OWAaDwLd9fnfz2o7KYxGJjIcaMaAc4n/CBT49RxW6FU8cFOArw6OW54bXhPoTEnaAskQZv60NR3PjF6YJo1ituZkkHNRWdNzTtWwIi+H0E7nzdIVHSwXTfYJB9ir4hmo/7Cg0vpazFqnvjP26jjIZn5lRy7ojkir3o/zyhQyzuFBgkjd8Nr1f912tu5tYMZtaGfphuaLCLIp+QiYuocKsDCqah20WPlG524q5tKYM0bIQ3V+Z8Dw3RoUzaRra31rTLi4N1FdYjUrTGLJ7D2CDm7sUwAycpv3dP2P2frMXoNEQHthtINKcGjiI9bo/zmmf/JL7uANCQFVQDlkalX7kCSY6WLoycwWRdLsFXomd/bMJHyfxxKi4Q9EIRT6KPnR58ntt3B/zVUE5t1ANWqoTHs5WB60mMk2csY8mSazL9ne2MP6ZxWCI1CNvMNqeWsybyl5G5azbFXitxSghKn+pHOb+1evIk+v3neyrBfiOnpfmC3aSGf4kx5ucX+N3p4hOUM7KE+rXz1vKWMABXl7eGZ6Gatu8Nf4hInjUUhlKu8qPuI3X1QwRu3s2n4r+OpQukv2Gq3k4ohFTFWtz4e1MgNWIL6nIr+6HyhE4IvD4AfxqdMz55JOkr/PFJ0iByWno3Qgne95P6kINgfLoUCwqWZ/8AZWr5iuN/4eGu4xqo23bhl2gQHEtLqVYKRLcpZRiBUqB4hJcirsT3KW4Q3F31+Du7l7cXULy5Xru7/2xrTWZTDKZmeM8zn1CFsocsSPnaV8lXRWL8N6/5/Y5FrkNseA6ik7lKjGc
*/