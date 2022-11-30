/*-----------------------------------------------------------------------------+    
Copyright (c) 2008-2009: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_TYPE_TRAITS_IS_ELEMENT_CONTAINER_HPP_JOFA_090830
#define BOOST_ICL_TYPE_TRAITS_IS_ELEMENT_CONTAINER_HPP_JOFA_090830

#include <boost/mpl/and.hpp> 
#include <boost/mpl/or.hpp> 
#include <boost/mpl/not.hpp> 
#include <boost/icl/type_traits/is_container.hpp> 
#include <boost/icl/type_traits/is_interval_container.hpp> 
#include <boost/icl/type_traits/is_set.hpp> 

namespace boost{ namespace icl
{
    template<class Type> 
    struct is_element_map
    {
        typedef is_element_map<Type> type;
        BOOST_STATIC_CONSTANT(bool, value = 
            (mpl::and_<is_map<Type>, mpl::not_<is_interval_container<Type> > >::value)
            );
    };

    template<class Type> 
    struct is_element_set
    {
        typedef is_element_set<Type> type;
        BOOST_STATIC_CONSTANT(bool, value = 
            (mpl::or_< mpl::and_< is_set<Type>
                                , mpl::not_<is_interval_container<Type> > > 
                     , is_std_set<Type>
                     >::value)
            );
    };

    template <class Type> 
    struct is_element_container
    { 
        typedef is_element_container<Type> type;
        BOOST_STATIC_CONSTANT(bool, value = 
            (mpl::or_<is_element_set<Type>, is_element_map<Type> >::value) 
            );
    };
}} // namespace boost icl

#endif



/* is_element_container.hpp
DzNzz/Ke7T3vOfe8v58TdXL8OQ173Zrs/SjgqKQPmOqjxksyanKmG9WWTYLdINkmsUCzJCh/k+wf1Ev5OoDvrA5GsL4AfYf7jPM1ELlhYBvsyjmZt6R460nV7IKq2QXMn8AJk2IrAgsA/4zriHQByShAio+5VZK4THDo91R/wDwlyONDYf/G2bILwVBiZUGTo2UwgUAWYk3SsMOfWfun5SHrJA/wtshgwPqCkAdgVYSMFyqRbMvAN5w/P45pgoMtRtQdQRWREct/Ad2D9cdwszMvzZBL+jDYxoDdASeUAW+XcEUBV17wBL8JZHzkin7IEIL4cLwVzfVSHZI0LRb2AxcGurn0PI3aGex5DEZAR8OnsIAvl2iw5NrsSDweC4eC1yuQwQRlfYiO7DxTvkn0KxT9HPL5TXZsVUa0hXgoRJWBHNkGfFq30nykA9yV5VNFIEwHoi8V12aWaUuSjwdvLSivO6//pwEb837yejn9dO8PJtypNTvugO+rxu+bPZ92sscO580GiwYeDXzT8kvblaPPP7578r0aM2P2+byS9V2TZ1O+DH3HfsNjwRNHumx66ufWy0eeDd858e/ac/p90un1nB9bvDjsVM/3xt9utHjQ57ot1t/ar37yQt+Pp97XzIje673OcMlz6ZATIdvG/V5vfuLhzm+Yr7ZaNuJMnw+L/3rs6fiDfq+Zfmj+wtCvw94tvNXwmaRjQW/l/9pu1ZhvIz+a8k/NWbH7O67Pvtz0udSvum93/FF/4YDPum4ee63NilHnInZNultnbsIh/w25V1q+NPybXu8X/dl4yeAvur1tu95hTcbFqD3THgiaGjVrPVa7Tt16HvUbNGzUWOvZpGmz5i1aerVq3aZtu/YdRG+fjr5+nfwDOnfpGhik6xYcEtq9R1jPXr37hEc8Htk3Sh8dExsX3y+hf+ITAwYmDRqcPCQlNW3osOHpI0aOGj3myYxMQxbwoebmmZ8aa8m32grG2R3OwvFFE4onTpo8Zeq06TNmzpr99Jy58+YvWLjomcVLSpY++9zzL7z40svLlq9YuWr1mrXrXln/6muvb9j4xqbNb7615e2t297ZvuPd997/4MOdu3Z/9PGe0r379h84+MmhTw8f+ezosc+/OH7iy69Ofn3qm9Nnzp47/+2Fi2WXvrv8/Q8/Xvnp6s/Xfvn1t+vlv9/44+at23/e+evvu/f+uf+AjYk4sx0DQxRz44SsZ+Un8Q4nmhSQmazSbZRxOYU6jwlANmKCg5YwkMcTfQjn+X3cTNQ+9Dy1nyNcjCV+1TLgGD68actRKAbMC+SHuy9OUyUMnx6UQzQy8fnTIJKfm48fioHhXulwkP31sb8J9kMgcLA4aICfpTCQHmqFhNDXzhFELjv2ThMeNR2KHY1tBey4gatSoqFSpiPgcuINCtCj2MsN488bTVbChICCB8B52kichSC3DTkeiyrXTmM7BOrXjgnjoO4yogeNYPWtzpi2VR7SixYe7ApZr0HUGZE6wqol5mRwCcw9w1w7UCOknclX0rYYchyZtQXQgPxkyRqf9g1lGPd9JFtRDlx3JCsKkFJBGOwwyTBUKkqHqnGRo/vEYYfbgTpM7nqBpNHxMSUr8K9YAHBSxjTBThsEvgHHj7HlFjoeIf5DjYvAytPDtlw+sRkZ2aCP2ujzIe1YQT3JLsF+DgFXPvQDMzGQIU4Rri+ZjZf2RpDRZcxAeKYuSK8jnqrYjBADwKzozDuT8e3CTnor6wdnIdOAOGx2J6UTd2SbCOgQ5ZqgOkxUDCI5oaqeE00BsuhCgoOrSIvVtepnnEcqsAoRry9isICMbmTpZ8Cu4IDHQNlhKD8n1C5aVWASNzofsLVIGm0X+A0+I7sWr+Hh+zD4IZV0dpn3U7ZfmOpOZL0VbzxiyD5MCQ7uxskD0+LRwEVNCFWci4apA5b7YvKgBOlsvJKm3Y6B7yibsJsweagQeF9LhohjYIpw7BV6IEUPHWsqLkJNKdD/7GfmDh8iBom9+gBML2DIUmDpkW7iY5RZ4i5ttlHyTPCtzreNZyRbLKhgoeTrlQUCAEZLVYHwnEPKzuSXJAVrOjg0HcIMJrCplIuIx0iFDOTE4rHLN0sJ8JHi052kYVyfTUyTnvF8DiJqXgo5Bi0PvaogNnogDYnq3mLOEnOkTig7eIkyv5rSlw6VBTBoSXp8M0phqDehS4BEyYtD1R+5QFI+FJPEYrNXGCbLDIZKAQDWolApCTHRJBovizKM1Je7GiwFeQYa3H1Y2puNVaWJ8q00HXn8sIRYOFz3fGXk4zcQAE8A5DR4TCXGRafxeTsgOzt+vYHXFFYMxC9Xjku/MMfGJtPWTiN8xBifmkJdYBwpTCIuoffyMTjuXhaDhpN4cVUxKtQ5qoRd5HQA5i95KJU1JjGNVqSinxWB0ZoxIdIvB8OQos/F6LOH3L/6pySRBwTWxF3fwWFglnUJoQoDjOvWKtLJAig614SWL4O/q1Gx+DQ40a7OlEGpEhIC6YSU8VuQdbKBAH3JOjmkZxB0KhyZKGYM+4R+yyD1g+yH3pXE5yLaCp1Btpwg4s4E/VNKxI3exnhtlFeI6nm+DirML2tAQlw18quqvFwybsvLxhtayOTaMfkJI7Q301d3Sl1YaIVKZHrQ1q+fQ+rnfiGhupBQU2XhC/qPkMOzvNFqjNNNBMc0MSleCievVckiFQ35AlRibBmEI2MLzjKofwuk4IWRfkZM0cY/R8aITgTDgURlz4oopRv+WfmbMgade5Lw3OP9//0HvP+gn16qTS45LmauLQsu2FpeK272gWZpz5/0Nb76fQ/njpt1+8/71Cv95dMBeRt/6j3hgzsNBi462nb0yvOBljd/eXzy7nua6Bl7PYcsPeFtWHcpZNy23x+Lf/pg86EvfO1neu2HsMJ3b9VLnH+41YhlZzqb37jap/jDvxomPXOs3ZhV3wblv/Vr5JSP/qkRM3Nfk5Rnv/TJeuW7UPs7N2r3m/NJi2EvnuqU8/qPPce/d9vjiQVHWo9cfrbLU5t+Dp+48+9GgxZ/3v7J1Rd01i2/9Z368f2asbP2N0197quO2esvd3ds/6NOwtxDLYe/9I1/7oYrvYre/7P+gIWftRm14lzXsZuvRUzadbfx4CVfdMhYc7Gb7e3rUdP2PBC0YrA+ObNgesnaraXHy8o1nt4h0UMM42YsXbdt74lLv9do4hMak5Jln/nsK+/s+/K7GzWbduwem5rtmPXc+u37v7r8R61mvj3i0ozO2c+/uuPAye9vPtbcLyx+qKnw6Rdee/fg1z/cqt2iU89+w3LGz3nx9fc+OfXj7Tot/XslDM8tmvvShvcPfXPlz7peAb37p+dNmPfyxg8+Pf3TnXqtOvdJHGEunr/sjQ8Pn7n6l0frLuFPjHxq4oLlm3YeOfvz3/XbdI0YMGrspIUrNu/67Ny1uw3aBj4+cLRl8qKVb+4+ev6Xew3bBUUmjcmf8syqtz469u2v/zRqr+s76Enr1MWrt3z8+YXf7jfu0C1qcIZt2pI1b+/54uL1B15BcWl3vevpV3RdN2fF7NqRa/dduz+g/44+glDS/sDuUzEVPWf/JzXbknBp4uwoMpi89BWF7zx6yb5bAeU0nD5KHU4d/lGfk3yW6QkvrJgiWQ0JtkK7odAowktV+g4GS/5flof9Dudb9PTcs4B9dB7uO5pH+4In3rGjA/ued/Mc0JvgdIQYogvVdRel12piSJ8+YUGhwcFhYpLBPlaMRstduwhnwuFcY22hjlBXqCd4CPWFhkJjwVNoKrQU2ggdhI5CV6G7ECHECqlCtuAQZgnrhf3CZQH8fTAOierypFcTejWlVzN6NaeXVjgsHMDeFjWoDHVQ/g1RzFaCtxAiRAsGYYawV9BoZmg0NTQ1NbU0tTV1NQ00Wo2XRtQEa/SaTD5/lifLC/Joga6W6PJCVyt0tUZXG3S1RVc7dOnRtfF0b225yVcr5PhqtegW0T36TG9tQa6vtnyRr3brAl9t8EL0HO5ZKAy6p6O7bD76jJ5lzkX/0b3WiMI/ePBgILgITovq0LhOTc2D+/fulJeVTmd4NoKmZp3GHaKmrUXpH3f4aneg/8lTfbXJM1E66C5Ad/DZ3lo9+i0T3QXono5ugfrXtIX3Kuj51tm+2lJ0H0d3GbonQ5w5Dydv6UwiL6RZAvHRs2R4ju4CdB9Av01f4Jom+OaVorQAR4alCenAGfNyFCd4kWuceedQHa9EcUo6a0sXI1nQLSxBccMDtCWRAVohIkCbiT7rUZhS9B/wEsqiArQnUbySVUh+uPsEaLeiuwzdEE8fLscrQXfpal+CE0X92epSP6p61J+F+X15Uh8Vkfq0NEF3feyDRMZSA+wHBX42xEU2gLrHdsZ+HQLqPaQtGlI/Nzhf1gjdzWn7gJ9CF+pOy9xm4dBBV+qb0A77IhG/r5bobk/d0QOp6y24L0dQF9wg6p7bgfpn6KhbLnBOR1L33G7URbcvdc991FvQH0xfkxozQNAnhq732eh5MN170j1HVt7B9D3x9YOneq1JveeIzk/LWpO6PTo6qEnLmAFZeWlZU9NjBnhH7AzY30wdPzF0T/z2aO+IxNCZ/r3alDVc71M/ODpoZ8B6n15t9jRZXG+j51SvJi33N9voWdZwcb2L1M2rPOq6of+25JDbUUdsSUu3XLkZtcnTcj3r+I0o9jxiz4ZSs+/VqF3ioUkTh1yKGrPZfmHoxhP0v0ZPfvfUk3Ct9CS+j56k56sn6XfSC5rp/TS0j0DmfjmEhjE6C79aNYnjCg1WJ4PoB7JzvH0qgxK6wEsTf1bY4gXAQVg0WAxOuivEIyfKyMsKmjA17CY2pSl4NuYDIHDVMhO10WSB0zomo7eEA8yDUxmcArdFBEKQVWuFoYVHll+JmPro6Sng+Kyif6Q/Bi+ssAQ+gRQCOhvWldkYkB7zAsKeEvCpSgDw3iocabLikgBlYfljNzoIiLJbWQXQhwXdOmG9WF7DT8KMEWr6abXoZjopFnNGUdJZAhUVHm4xW8f6Sysmh8zEkW1BZUbzsxV9CaQksFajG7phwLi2EuhuTOCNEgRMR3ymMFDNgc5eHkvlYxDfDl315DNwL1a4hTEBg1UATCph73H3JcJwzM4ShDplsGVcQqQCDA4HWrU5aJEkHKhEnofSLQOzC8WvojQULduQBZCNirbHxSTbfQZX4XAXYB3TNXfG+UAIllhcUgoOr9/h2hiuBTGa8alJZ7GOW1tnYsxKs3GCf8UFzM4zZY/NQGt0AGPNgAj+Ur1VgJeeY7HRTTC8Y+N+PPLvLTheEpoI2ajz9gAvdzkO9FzR7CC+7zg+gfw3O0TBR+chiD4KuRRCuZUiUNopMktbq1KyFeWO5mzvh8yHIcXigtI9IHqGpZJ6BFTSLJvNYjJYq1eJLHC1KrHCfK1SY/CZumMGV2WvavfqSqGWw4E54SorMKlNTlDCVUGUAeVQzYdz34CsyIkHW76YqIhtJLF+VKl0/2X5VDhNAAJMlRQTjc1nYBxw75erltadnO46UBVtyQmOp9xxsH0NVNCgUkKq3Z9I/pUog2p0qYdSC/x4rKSR/uWgF9ykj7muAY9aUuLuuwWG/OXCUK1cUWbVK0fFSsVdO1SkTKrRCA+rVtzl/z9VKvxk5mSc8WxCQ+JkwDbNeJNRpojXgX0nzYvKFAXBahOEYpNDwCdJsPkmCmb26h3mA9GdnnDC6WA291dR6kCOXwRblZiSE6OfY5oRJLS3R7wS4xQ6lWQyuskf2fAmp4RuPYFSSstlw1Xsw1cNiZFRaMWksMYMKayPTlDYRHjOJecXmDkG330iRAn3Ws2+yJs/Kk4/9XBUE+RRLneScTiXDnnvhdplFAEIz7UgI8wyxg1fDsXjJucyADOomL2XRxXJYXnbmUcAFgroN7MBCpGA67iiddM1FIMfrxxinRDB8UwjCt5Qt8D8RYwGSTq0QvqJhAXPeMwpel6OGIKJEMLCdK79gVDVYDosOuNwxjWuKN7s54RjrzFkPp5sW0Exrg+Z/gmOtlqwAWFxh8ROeFEY8juF2ScaLBMtfqU+mAOOL5jnKcuUg1kRuUJgkQuwDZuaTc7jMNtdQoXHc2VSbJoLKVYg287kykHWZq48k7AMZOnB6QYMZd+NYdor0OzZsSKM6A8MNECUCXRf7mTQCVN04kCuxcy05vlmk/HsK+1QgSJA1lWSXPfe8ELPASfQKHa+Tk6bDDI11j6pI3X9uHZ8df3w4lWrchRMkHIbklfgeKCjLsKxL0g7IyaJ6JSUOBjEDIsQuyug/c05jL4zBw3fQjvtf4QSXSLmofrApZDKUe3SlZXMn4/KKmA35eJaJIUiudEVFlH4yhVlNvZ/c4q5JnqKHU8SEu8XwIq7jj2njaoJWkBcdQ7FIET2ST5KilBDEtZmfDI1oJiQAWEmIEykAVnRE9eFTuzDQ1YPeWbTeEq+bHDKq278AhfJIwksC0v2YnRCLMvS7XqANE/F5eUaTkGNTBU4qj4DOVsKux1UveCvFrLi5+jTYgfHuUkKtzch5AVHRytMzJiQwwHY7WZHnmuVg9FsRrMZnAMWGSmhI89cgJs2FtVlBldm1v/l7Q93ugMNeAXnrbeYJHGDqQdESM/uvXu47G9wHHUqPuMK0gpRplW1XgBCb28hSeIkc8Pgy+2r6fBrI+4ZEL/YbKQnYn6o6qZDxiMcDyY+VBbXvvEv8heBRA1NwiZ6LBKIggvzCZ179fNQysZszMpjeWM/zlxrRpZlbAZgjqPvToydH2vMIb4ZBqND3b7V0J9udGc4x6pDyUUx4Rtj/QF2Qxv1SCVU0iEspwgpaiiLWmjl2ILUobsjwx0NXEZybVLxdBM+VCQTJaxWEYFHiD3wGA7DupwtiXkxqUO7GIvW0fkGli/wLxqNEiulAZytjbjGWVYh6qwk3iXYCkYi2YupMmLmCW4/hY5QbSJCfVU+acjkUY80VYjREp0Or/7MeB83xwZUA45wDw+uPNUqTpxMlQS1DVsq6CteQwCTe7XzfNh8hzHiMH7vUhYFNb9bQ5nJyLZ9HqZaHko+GUX1fyfhv6s/MieBPOoFlVHZtkS1yXJVW7Cq5PoP2+JiPusgAIBDS+VdzW8kx3XfQy72iackx14CNIfaJpcz5MqKVmODJlcys0vuiqQkK8JmtznTQ7Y4X5meIXes1SmAjdwE5B/wn6BbLjn4DzAC5xgECPwHBIhvuabeV9Wr6poZcj8UGY4RiOR2V1e9evXqff7eLLq9/ZndlO9Ug7ToFIT12VZlbQqUUWhBGrX23hL/HVipkbvOrRCmuCzak1lMKXbngh5grz+P2dspU6C9B9Xy9lvgs0WN7mBHA/+KtUlvU53nAirNjtHevhH9ZjLc7OndaHyv9yr13VReMVd+FvQSr+iF192jY7OMUvVexublrKGceN+w7cDpkdXUNXjmvwCz2Kbw8jcpbOhgHiol9SttHjRm1/3Ya/UeeNzpJOh+2n6D8jRsOK1nQ3/hDrf7qDGKoQiuzgm6lvz30/BtHC/e0rp05W3r+JG2194aY5E1a1uMoWE2viB2dvgw9Ez8hA235ff3mxsbG8sJMsYLyvil5svzCVixIyicUcv60zEaVh80oSU1
*/