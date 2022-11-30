//  Boost string_algo library string_traits.hpp header file  ---------------------------//

//  Copyright Pavol Droba 2002-2003.
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org/ for updates, documentation, and revision history.

#ifndef BOOST_STRING_STD_ROPE_TRAITS_HPP
#define BOOST_STRING_STD_ROPE_TRAITS_HPP

#include <boost/algorithm/string/yes_no_type.hpp>
#include <rope>
#include <boost/algorithm/string/sequence_traits.hpp>

namespace boost {
    namespace algorithm {

//  SGI's std::rope<> traits  -----------------------------------------------//

    
    // native replace trait
        template<typename T, typename TraitsT, typename AllocT>
        class has_native_replace< std::rope<T,TraitsT,AllocT> >
        {
        public:
#if BOOST_WORKAROUND( __IBMCPP__, <= 600 )
            enum { value = true };
#else
            BOOST_STATIC_CONSTANT(bool, value=true);
#endif // BOOST_WORKAROUND( __IBMCPP__, <= 600 )
            typedef mpl::bool_<value> type;     
        };

    // stable iterators trait
        template<typename T, typename TraitsT, typename AllocT>
        class has_stable_iterators< std::rope<T,TraitsT,AllocT> >
        {
        public:
#if BOOST_WORKAROUND( __IBMCPP__, <= 600 )
            enum { value = true };
#else
            BOOST_STATIC_CONSTANT(bool, value=true);
#endif // BOOST_WORKAROUND( __IBMCPP__, <= 600 )
            typedef mpl::bool_<value> type;     
        };

    // const time insert trait
        template<typename T, typename TraitsT, typename AllocT>
        class has_const_time_insert< std::rope<T,TraitsT,AllocT> >
        {
        public:
#if BOOST_WORKAROUND( __IBMCPP__, <= 600 )
            enum { value = true };
#else
            BOOST_STATIC_CONSTANT(bool, value=true);
#endif // BOOST_WORKAROUND( __IBMCPP__, <= 600 )
            typedef mpl::bool_<value> type;     
        };

    // const time erase trait
        template<typename T, typename TraitsT, typename AllocT>
        class has_const_time_erase< std::rope<T,TraitsT,AllocT> >
        {
        public:
#if BOOST_WORKAROUND( __IBMCPP__, <= 600 )
            enum { value = true };
#else
            BOOST_STATIC_CONSTANT(bool, value=true);
#endif // BOOST_WORKAROUND( __IBMCPP__, <= 600 )
            typedef mpl::bool_<value> type;     
        };


    } // namespace algorithm
} // namespace boost


#endif  // BOOST_STRING_ROPE_TRAITS_HPP

/* rope_traits.hpp
A8XjUUZHJW5y5HLwpIlgFT6+bo6IdrZtaF57Ybza8IXSupYn+szbvAFb5+EE7HbWL4aWfn89mw3Xfc6ShLaxSkeb4XRl/RN/85U+jRly94insUK9W5mUAIXCzLE6VQtaZM1lRB/4A8hBayH6P4LIoGf/3yMyWFjpWegFmYT52L5eJjCyC/CxsrAxCrLTfX1f7IzC7Ow8+FzM7HQC9F+PT5CBkU2ATYCdkZ5NWJCVUYCPWZiOTZiF/n+IyBACAEF+vQqH3gIAwbcBgFDmAECYFAAgPE0AEHE7AIisAwBE+RQdIQwAoh0FANF5/TWRwUT/fxES/2Uig4HtPxIZypyR2Kww3B2LuvoQiABEQASnTf5HiFnBjlJNcY2NBSxi3kxjV6oCcc2ypCsuLkCydph2GM9S++Om51Fa2JGnW+fCkect5dV0OSu45/Hzxjm3G/tolbciSfkOXueCo0yp8IM6KXy4mJ8JLulftd2adrGcSFQhaHvDCo+Z+j2bIKpDyMPiP8rfYxo1eTDOhDJjGwHYBuUtudzQDJYk2F61pmeGe4QKmfonzBxTb65cTXC4Z062EpVZgO9/pDwaQyE4pfH1lb2hIQ2pPkdRtbGSLH/FeoCJKxUToGvIOV7HuCREuMAj3KR3ykSJ7nkttyjBFSNEfxixMlV3EtqciV3+daRknLfqSx/Y3NEEpsNXC+KZjHywtliSQ2mn6PeklJsVu6EdChwzcoIrVaAoPiuXKEbn9PfnTqo7a7/RglEUQY6aYu++PqxwbiwEmXRVyCuE9Ocu1DhfmuXS7M+nleAzPF76fBT20tP1jtkPMEzwRT/EKyhf+KNxKBDKQiS2ugILywpFcx8OrYSdjFnke+qg0mhXb4Vncn4CIw+IJqyOqlT7pjDY1ZlUQTFD3EeXvSMC8JrPzGo5QXvtqyDNKpnjtt30nkfNf4xM96Fv32nk71PEnR7IHCGUVMT+jKUO2qCUKuuJyePTqkK1v9s0GlhJpcRy2VwGWkP4Mc+3azleimtCLahL7yPbPHFCbukc7As9G992OhCI3BRCF8oNV2Wb1J1ysVPY8jMT1bVpBXUKyObsBi1fHG+miUOaYYt+H24kexlU8XucIO9w0BhrhEzuUErxczhb+2SLaBIUTeeiN592qX3vis5UJEPZyWYWVt3qDSU/D6kJW3mwJLY5xui0yxzmSFlQIwINhrJpQ10M5lIFQvYsFFmfz295s8kW8l7oGWaxGCye4NI8bA/omdSHE510G9Atx4y8cVhZNLr1LAiNqsUaKXL6kJpokyWP0TdV8fM/qVR88MUrlpyl/tvCU718jsz44mHyYcewEiHbQhAPlkJ5RXusS/rIWTViEYxzQ/J8qqXbJlQxTzVidZ7RWP8t9PBS1yqy3WeFyjSC0gK2l6UhCN2pA4x95zWxlR2f+H3UJVQBy5J7n2vkCcTkjSkGxKL57TMNxu9GGosqNvHhOzURBw36EuZZxtg2eFMWWjGYZj9YfKndeR+JLZC/VSpJ3g27pWVDd/Gp9ojvPYUlqgn81sHWFwfjK46IazmoC3XAF9tZd6cuwc1NK/sMnumPPUw7RRWyabCf7JvfvJGunJkSzcsWMIfZRWuEvqmQMVbZJH+5XkL3GfqWY6N1MzViffCLlt975raSmm11AqQ2M2rD57Q9bkfJLnhC+6HkrS39xqQ8yjhqrIn1dcmXyhapPlpE5+pIRHOPmXZd9UogKf0YqGMub15LrTj7BQalf04zRdnZfFSDL/AehKsqLR3+hPX+5p0a9UUFqn8Qte+kxCR0RSqp+KyL/fsz7lyTqzy+xovm5xPl7m/0uQQcSdO4o7Z7kRr1750SOnopvKRxejPprWMR5E5XkgUqiExKES9MUQR6KOGNY/OvzN5QEwYuOYW2M+s03L02/uDuvTdDYLXHZYiuIowsBwKb25xn13G1ftjAgrlRBoRBn0yWVU2DsXcGlhK3q1N4irtUNkZZ9BBE4PmmVfi9s6Jl5oO8wuUR26eojsuPoXgO1NaLtNfvb5gmtx49uB5A6KRx1v6PUPjvfMHB/A8mFL79/NpIAvi7lzsNPAAIFAAGBAoN9KtE1e+RDDaEsrYroMQMjEy6EZmVHWPHv3NCvnlafqrGCaMjwy96cRFPW75w9v+7eo99nXdCGC7WdG1N8I41GCMuF2uJpTnG+BKUEZeTtdr89L1+K22G+nnoVet762nO1RuUuFanHjLDCB3MVimqltMeek6qIMDUianhUSp9wJyBCnhZlPju7q5dxcj7IautLfE/VCQQ4Hv9TwSdvAj9p9um/P31u5wJuXgjBM21d7sE6Ve5InDxRTOZy85tKmrFSOFQQTpu+df0LSIlcakgfC7e9/TMEcdzqcBBHEAz8uEZsQDjPtjgQJAYmRDt97QLfB4mSl8vHgJ1j5+FdL3usseOKV/sA2EeCPTNm3eMnLUy8Erc6BaQP+Dss2Bl4B2yXc0ouEhZLy0t9Q+Uvqq/g70n51xd+8J5ln0UFNZ+NC50lHcM10WsdeMJf8f/fYeKedI4eX/BZJvrQLc0i2vLaEGEb8v8+RuMLU6WeQ44TgWveAITzqnU5kLeQfhqnN0RLUV8I0g12HPjMorAQH//HGIru/kLLqZqhPyWvau/2mtCttJ1tvNJXjN6byNRIbyJFsfGPsxiooz86w5xkbH1AXvnknarW8xdlwI8kSjqsc06oKZ984LdbHdcyTqRxEXwo4rSvMKzMvGzzF9ODcK/kyhgYP9/L2GBDv7rRwzsSVv2m68gEQn4ZJGQ6UGfEhaImPhtvTJW5OQjfi/EPRN9WsyAZshM/rWh4ZDhsxn3hg6Nhtd4k+G9VgKDhmOi07HjAw4niU7notPZ2dkTDLWHSUdZbNJeWkFmi04o0/CZr1ls0RcymsZx1BrRkcCbBDrlDKvzmFRpnnpGXWMiR9cpitISda+k1HS8vFkspjbozfQM046KmfSS9hfdAk5nzw7f7IONRwA4faIZdMg7BRDxI/QhZrCeTgqgHMdgo0TvNV0UwHhTd6hIfBB2GD0qO64eGbtEv6FW7m8LVFWoi9feCkjeBIbhZcaQJHxshL80EQFTNo92tix7dNIRNg3BUC5B7P+rCdUgu/MFQZJ6KHjun1exoZcW52gPPeGXtS42+zztrvyAL+tYJG7TupQoUd7Fzmgwyws8oy6tN8v1RVTXfD0lBaN7+e5a/S6Y50sapWeE3xLShvXJMw/iz/Ge/L8tkJlh5vLS28/w4mUmGY1SfUBGPXQFZIYSXWDg+K79omv7ZVzG86Zx5RbI+fbE01ScJSxyIEoo3HXip8sS8CFJmYs2RYGfhZhdRwICpKy0Xie7sRy2xfaQMDc4d9p8WWh8UEePnt7Yetb7wWrv2kIvNHiwNBgIEBw4XSEibKQsDHgrLGSukpXFSJkF4CUirCm2qKZQqQJWmQGOqBwt0Bt8pq8BJTzAnxNERxLymvxZhyuUDVhuG6zd+bvllvds3hPafuw3na+1OpP5TMs+JN/rjZlU2xHZ4WQer0h0pk0u3BMlYMUfoIVBaSE/5H7ewf642GvS7CT3Je+c5REg+hSegAKRTz/Ki+9NASej/xSioICb3ssK5Wj0hTu7bEGfv9WXvV6+idXrgMRjARPljH6oM2WuGc6U8mJ2tCzDJzW6PrGKJCUBBvssp2sqgWr/o85WDg1pcZ+xkQDES+JVlQS6/XydrfVkCSRSnBgY7LuoAD2DD5UZb7MfJgKyfCgVIJqX8kShXh2wJbIx1PC6Du3a/7ZrRxEyQwGQBYD8Y+VvhQTo6P5RfyIBAYD8LocaAAT+46oBGAgYFBQM+DcJMKCIBPRgSMh8DPyyujaMK0ReT5TA8e8xgZgjdsolW7nFmDGhIeo+TWSN8W9V6U6HU4Rj+fKU5i43hX0ya3o8lMCqsvi0xG7VmcFXQ3rFe5tkm6nvUjAsTLfFxmJ7vlcbyL8uL+YmrUx+rKYMevAMvbhyW64XuLlRpAQgVDYbNI5turu/6YibTFqvdj7daK2dP2vN/kySNZJGfV47k3NOek2N63ZtXVLbwsiUWv7gm5D4SsVTQHKIrPhlRoZzKn1Cg6AGMNhRQQ304HHwUD/hMjytu1S+lnGwkZUsGsDLdddSgTJjFDNDE/btFNS2PXjDIVkIqZiefH55zV7qqtO4QSwJRxC01q+ad1WuwkX6BhAWkTIwJyuO8cOiYonqyfiZC/RX+fDIqEReS78zV6EvIupHXzSG8NT98yofKTmTIDGj46A9zvAZol6UIL8Aq1sv3+LRbzr08VI6N7nqDxoW7/N7XnK+H3S2WbBruJUN9nCEjj9Zq92yuyiia+a/ip9h2ZwyQvPXRsLcXJwv7jyGXtXXWEhSSJaAvLcrnys2kyZ559EwazHNTIbY+VJjn8Uc06s8bJL0AfWhELzzpUzSlfpNPhbkPb/1ivVuJRflKcnnrpdeqrgo15FHq3jtxWFQd32Ox3DLMsGMIFR5hvV4IEf8dIMwlSmxy25wLZAf6Bj6HdS9vvCc2eik6Mk41owMYauQqUTjHNidiqA+myaBcNW4m3KCwUq2EClnZdYCAd/CQth/PqT8tqOhp8sVxE6T6sogGlg4s1H1y5P6X8i+aiVS5hlmYKAkVFVRVmE45KS250lmFHDx7vZuNjAz2ue7/Oz2Io5GjgJAiNDlI4DSZjkCGlVnsGez81PRv6kXGPt5YIkMafg+SL252/n3O/dUWpMPsbRmnhJoNbLgKERNQAWF+J3ZjjrMzILoCqH74LlB8SYNvkHxpkjC2goWJbeYgmNxU1iUHj0RTIbnwv2fK/LTigXOBlwLfl+WkKls7cRcklan6KflKi8mjn9LSrA1m9UnLw5JaAGfsqCPnhYeXPIxq0XvNycysuarkR1kFqGb+ruTEv5ZYrM/E/yDgEIAfe3keUpKAIKEAAMD/3VSAvh3xf84KAqBgm3k2JPmv4pZ1ruikpDo662SDb/+13nvD/7mvwpLkEJGkXtJeA/eamfMosJLBksJ4yuMkrVtgeWeZPDBrEjClHHelPGIEbNhJPlan2wLlRr6fY9i1rbk137BX/XjULsjLYVFcIPGVA58CzkAfV8tDbashJHsVZbpOnZClq5O1fYjLOH197CE708AnjO8//YwSyQvJxRfY3zz7dQzt4Bt1AHaH6EIyd8zF7QFL79lLqh6fnuYuuCyFphuwkeEI8sdPLhxPq5WKhG2hLNwpLHVSbuANCEQhZqEF+GBz0WOTggg8X1xMneK+M2Vil7FvcEHedn6oH1BBxQYvQsVlW8ohtrPC/ECcNTPlJg5LyfRvHvnrzlCG4QwTOpODD23fWzG3jWS6VVksVuaZyCaXTCrB88HRECpnp2Zd4D28S04DVOIvxgGuZZ9auflWxj/otLSef9HACmAnRe8n/ughWjlRvRPhit4OUj07hEw+g6e9/MqZ5c2IQDvmQJWaZqNBe1s2zagr3rKktj9TM6zHjAIsMhaWhjnwct+v3hyVYG9ajzO25IahpqVLHnzAjMnQzi7gIKQgYg6R/TrWPPPSbNkIxJDU97zAj5UagoI2RbaPwJgP7VNAuy+njCfu1cwHaKQnTdViufz0/cQnNF2uTPtjPpVRLZgKZF8+aayTayT3JPe3ZqWCJgSzZoRHRHhzrGf6lIZgq52Z4bXM1SHPDu1rrJPs2TOtyR2fS7ovq6fk6/nWnCalx9ZUeDpOBVgzBZe4dz+LeqAGebVm29RB3HfIhPeBw2DfVYiSV758QSVybYfiQmvvycmCCB9+paYkHP/7WF6p17fxjNDT91129lFZab9kYyQ/A9IRmD5h3l9/+7mDfQpWurXyQjgT68M8YdkhCddv5Ju9BihrI2tfRUZK7+wXsQKChGxQmQFg5f3u4zfXzDdtCgVhXyY3AwkP1dZUDHzaXekMTI2cojfftBTNLVvHCi/YoNxx+aH/FTkNC89Pu4Y2eCclnCjn3UdpJQzvkfzYTmd/swGksihZM2UU0JsSTz3h7S/DvFf0v5mJq4gghlhHQevJUxcwdMfyQiH+m7R5wPxOBmOvn4ROPZGECY4Kxnrcj+TEWY/E7/5Q6/oiFyR7sj/B9P0Yq5cVACAQ0vtvQVUXMm6sN24Q3B3twCNe3AL7hokuAV3CBDc3d3dHUJwh+AOgeDuECx/iJwzM2fuOfe761vfzL/Wbau3qti1ge6utXv3+9STF9ji/KxjI3ObTRepFfHk4xlpeeiHw6fdBEcsxhFuyV6wD4hpffFegHI2cUH+tWMRyx9mBPKGex/mxFdsJekX/OSBoxFlTyn+A/r660T9eggzlwRgMyrYurH21a8Uhmdnp98vWjU/a1vw0vKKEkS3vUjD3gW3MiV6xtCdBRf3lNVvjPDpmgFKT3D/swFD8WfLR1oWpH76I9sHS1WPyvt8+iN7D0tV3h1PKWRseC+xj4FHMBjEeiowQmrzZIkcWua+XwEgMkWK+q1DcLwYjM+ubWa4oVDCFELQD9i1b1tcOQ7Y0rYv5LKolaz6l/tM5DYomYCQszYv+c1VViM1hzcwR5o/3cvdx9Nf2YVsLdutBGxUCUWcMt2VfwXkhb5mp0WcO8pmvptvW3vwaWp0O1EJdItl/YSdz53yhtf3UqDrmE0goEkdeioo87hurCG46GTRp2hcnVgpEpPJ138iPlJtXkkk+FLdJbyBecHRZ/UA45qjb2La4pHKU/EfqfxUnlLoUcNMXNWiJ7O1zwQwV78CQpj8dWNB2U/hiOHAekf2+hfUtLQ+rX+207OCudJzpFgErciOkeubYJdbPThcfDRxRFu8EKq8Q4/RxwZjTXU8IaiNJw8LauC+AS89gMdVJZDAp/M7WlGlELCVFFnfdDSbSnWkKGCp7Cjt0+hTQwRr8ygBVo9J7c8HKBdNmhxlQHFG5ETK4jqU4QrMaSGeqC6cM9PZd7YnxmnkAcN3T+wSbzldnRfLTBYQOz85+cSgSeYgLAYQ3XYtbtXYGEKmM/pQyUCt62+p+78+ymBZktNC6u4ZTvynFME8C0Nt9xwiTWDmap1kS/o3UoSkX1KEPevkpF/J/DXImMCETZmMRjU56K8AG0yg9q9k/rbDc63fJPPbkf1GipAEGqDwqPYVoOk+8ZTNz12IeMp4Xqwdw+XpZHLX+pJn/6/M5mfi/Htl8/8LAPV0DAX+a6b89qkSHBoO6hcA9e1z5PclvIlRmQT0oDBJ5JVjOibQMUgVbbyjs6qqx9GAtlE1nWtkggr6Bn+YKa9Md+fjC/CErORJYtHwxl08rPPWqyvs72PDMjXiTXJAWcRZilFkXquqM616MWxuVR2X5RAbLxgmqQQzkgr6KRRKcMbOqjONrWGPcXlEoeHp64zGqyqsOjK7G7/iS1KVW3VEgh51mTwI5OhuS6Mrz3t/gPc/76Cja0rIh2tWXs+jjlzFPYKvIK+wbjPNn0phBomt1yxGSVZFdwAZJh2/oWxjm/7sOS1dwWUkBGPSoDKRytrzqhmKMZzzQsWla+dGlPYdRtWrFPFj64tJLAKUhZ5OhEKnhlvTcPJotGfB6OkevunAzRq5KEFP5Gh6nI/wa4mp5bCkGDyso8klMDnKpgIak8sw2SrFsDORD7hfAef3oc/9vPbh
*/