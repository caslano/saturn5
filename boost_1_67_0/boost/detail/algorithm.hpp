// (C) Copyright Jeremy Siek 2001.
// Distributed under the Boost Software License, Version 1.0. (See accompany-
// ing file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

/*
 *
 * Copyright (c) 1994
 * Hewlett-Packard Company
 *
 * Permission to use, copy, modify, distribute and sell this software
 * and its documentation for any purpose is hereby granted without fee,
 * provided that the above copyright notice appear in all copies and
 * that both that copyright notice and this permission notice appear
 * in supporting documentation.  Hewlett-Packard Company makes no
 * representations about the suitability of this software for any
 * purpose.  It is provided "as is" without express or implied warranty.
 *
 *
 * Copyright (c) 1996
 * Silicon Graphics Computer Systems, Inc.
 *
 * Permission to use, copy, modify, distribute and sell this software
 * and its documentation for any purpose is hereby granted without fee,
 * provided that the above copyright notice appear in all copies and
 * that both that copyright notice and this permission notice appear
 * in supporting documentation.  Silicon Graphics makes no
 * representations about the suitability of this software for any
 * purpose.  It is provided "as is" without express or implied warranty.
 */

#ifndef BOOST_ALGORITHM_HPP
#define BOOST_ALGORITHM_HPP
#include <boost/detail/iterator.hpp>
// Algorithms on sequences
//
// The functions in this file have not yet gone through formal
// review, and are subject to change. This is a work in progress.
// They have been checked into the detail directory because
// there are some graph algorithms that use these functions.

#include <algorithm>
#include <vector>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/algorithm/copy.hpp>
#include <boost/range/algorithm/equal.hpp>
#include <boost/range/algorithm/sort.hpp>
#include <boost/range/algorithm/stable_sort.hpp>
#include <boost/range/algorithm/find_if.hpp>
#include <boost/range/algorithm/count.hpp>
#include <boost/range/algorithm/count_if.hpp>
#include <boost/range/algorithm_ext/is_sorted.hpp>
#include <boost/range/algorithm_ext/iota.hpp>

namespace boost
{

template < typename InputIterator, typename Predicate >
bool any_if(InputIterator first, InputIterator last, Predicate p)
{
    return std::find_if(first, last, p) != last;
}

template < typename Container, typename Predicate >
bool any_if(const Container& c, Predicate p)
{
    return any_if(boost::begin(c), boost::end(c), p);
}

template < typename InputIterator, typename T >
bool container_contains(InputIterator first, InputIterator last, T value)
{
    return std::find(first, last, value) != last;
}
template < typename Container, typename T >
bool container_contains(const Container& c, const T& value)
{
    return container_contains(boost::begin(c), boost::end(c), value);
}

} // namespace boost

#endif // BOOST_ALGORITHM_HPP

/* algorithm.hpp
5lEvR4ZGMxqwWZW4P3UHMUP5m56qPl5Oz6/e4wKyZajO+udt8wuwP3SyKYYCYiIBys9HP9ackiSjyGn3GxqzbCqm1otYog71oSIvFCSc9UnmvYV0tSCnM/I5n5WHt+o4Wmx9fkcsTVLAbmyfnRYXw+4gEQAeaoHEU30Lk6p+IabqC4a0zsnULuMc4btvzeQ0aeimaX7qTn7TgkPRzMSuqbC2NqlZ5eLQSZ8NkpbDFIBLTUHqdGnaqJaL6tVrbcsM4d/8Y6thZLij4R0voO3PKWRBYPFETgv+u9o/yeVEcuZJYXEUKEY4GIsH1//9w5V9/9iW9v5htaecPrp6hEFC4ziBYcA6tjxTXKrhWogUu7qlcHcLNdTy0rfrvnPpPXWXvU5MuCTqWCOm8BkwbI1WzFVzGX6epETL1wOIHaRLfjD8lKzumgr+SUQfEbvII5pgOV+o4QXglOcL9V3LW+rqeYma5CprS+CmCn3vOCI+wFIt0DnxootB+aq8rrGB1sJ6lRv3O/QV3FEtC9j+n7irX7rhp7tv+F9qvDwfJ0vWAfHLhQP3/r+IaDzy9n7/X5/u/izfapHxnj1hvRq3FEbihvKRpQuhcUHYm4llYrY9DN4tvY8Kl37YmmIxWYb4PWoFS8vO+5hlimOhORUE87QYXdtzW8DrkrR3Wgpfr1SnJy06yPr0nNVUBa7GRYxVGeJd808eW4mqF8lL7/HVuuaTuhUZubvFvxawofeC+dWX09rNFhwA39LIIonC20MyWFA9pF3Iwy6n8PYn66mmh8g6HKcsp2ryVj8Ok7elKt4TLqc3WXVZznTzpC0+iRzR7ljL2cvJch7ojI11PoslgAu7v4KMipDwYdFyrtmocy9j+7LMQ4kYN76N7n+ixbmuETNPQSrNS6JBmQ00Kd9fpKIC46Fdvf/+Z8z8HzG8sQ9p8A00q3D0ayk9gTaTU8VcsyyjRxccZWFxGWlfVtUqEAq8AJ3mqGV8kd+bgnrZr1skNnNcCFAMO9exH/zchsKAFlZGhhwLCC+DJF6tUrSMq/EP6mGTNZEp7ZeFxjUYxEXgRdY1EGBWLOGgc3OgtVfZ+8RCYxu0OL7ksv7BpZu6S15ZDGHeR7oBtTUHJmoHVz4Fn5LPOACX/rgjA2piItr9STZrgYyg/IGSnOeCHFZMKs7Oi8ZLmps1VRxVgaqX0pccuqtABruvCjPbKcdBCdDaGDmvGa6OEKgz/vDtO98M+hL1/rPIyEnOD3BcsmwcIQjvvukW1xJuEQrYKi2IJBu4+Nrpkj/8PhNtj+yJahQMHN80v3wmcQolywVyamxjlukoa+vLT+axl3B4CoQTYQLdf9sLn+h7i7tY+Sv8x/3dnj+YnhbaWFNKa1svky60IVwnw2mK24bLJBVsZjeZl5Gxdyedt7+LlRWeT5atjUsSaqB5PctYZqlILevXn3ET5bzBFhiYqLDmUHrJKfWbRyDj4YfXwQ/K/5ePY9Ky9PERdrPwUJwSwvWLwuiBXhtMO69uvB8+3f3Pktv79dNdmccfP39qbj717ZOUb/GzvqUWfIMAsxAAhY8EOyWIeUC4ZyjrnEx2dTJxgw39ByKC5mTxGohyohdrpDZtLcalVLeBTas5rYS4F9gJOCLrWKGBl0DZ7jPcxG6jf4oftg82MK04EPMotdqxqmqZsuD/YOyhVEQq8QXDbB+DHBFqooPt6RRU+nDeYLX7IcEGsw5desgHSwmH6dDpTTtVtaMhAAKKSAHw86ZVG7+8dPr9iwzrAYQRgb7t25Kwb3knDKSuijTc/4D2T3r3BG7YejutQ+hvXOB7HnQno2+HTh25aQc3Lo8zy4PSJXv5gG+Y0G5JGqBpFyBcAyBBZZuDAr8LqKURiGsIwNQOB4OrK06849V65D2heyz0ulOezZEIm7nv9+xYcNSWJ5toqe5ymwKOUhEFvLR9UpXAfzKZXgN6LvosUHLZoHEy/nF1vj/cRCeY7afyNnEnRe4eFxBu+LwzOepvq69ZkAz9IsXoJBxI8KWm+NL6mtGEuxqbjEbXsMzVR7dFwbS/bKTvTBj9k8QUAJb8mANP2xD5dKpdHQ+62lQnyz8JcfNxb3iVSjuJaJWTWv0kF13+1XAue7S1HmIAiZY1zRtqhR1IoyP5nu7hokfTVZyTpkt96XShUtx3/ihRgq3496i8eBggW5dSActFTYgzoxLopLOkSsmjX1dACcApgJ8oWF8KekbYIvMXZZcGRiYgW7i8i9rhTfsLR02eEkisR2sREfMuqPqjwqlbBLvS2Zl7RilgmlPgQYB/oF7nme/smKdhBSNf8AxZxL1QZf0bEfeOzUa4OsB3PXfPSeZDgF+77hKz5OpIGXj39QsshD5++96QhowlbMmL5gA5h1KY4O7hO9HcRT4YzX11LNdvroD1cYJP4JhzG6C0C/UkywuBE0VcTPBnLWs97beIQ2sKPsJ5jADTj73W54mYtWwAJj+1vQnA8C1EPLS7QByNAGnkewj68eXkM2UQOJbQYm8KHD1gKNug6BlWuxjrM5vGHWa02a0mzqIB3DN0FI0NG10i33OkaXpgbI6crueOZjubmz/KgxQfH9dzpGLUtzEALxoilxjRvDPS2xRND5ttMGyGd9HNkHv2LFupKpFPJfbsupOIV4cP0o+kz5Sf9G2AojJAtNCB7J40L+Znt3j+3zGu8sFHJM0KFStvYcbuPsBwg3jLdrCB/UYcVWTiYI0QA5F5dtvQDstvDL00ZPNe1VtqDyj73YhdrBVRMD7C4jcQHgnrWp37dLVns5J8eCrNqBVDB7hgB9bjG1FYdZs2+/iyb8P7lfKz9NVI34zwauA2kmjjluMj+wVrY5IXaG4VN0ecuyGQlztCP0bNbvf/bILQGU0l0AuCCrFKySBFAyaaRiKYtXjCOL8fZjK9uX6R9VPkqF6u1cuqE5AOWYjcmrTmx4jJg9XQS0rOKSYtQm5OyLFkqn85vlYxxfvnJXZRIjZ2KmoE9if4kYZnaeJ/Mpw7X4dv2hzv9RZ9LOb+/ObA8e8RL7uIQH7yof422bhOA8URzxNTt+7JTYmHm2gGuoS7OwZl9ftG9r7grZtUkW4gOknFQflf338H+RrM8mTDFnz3KR2xwhDRhYpjz/akUOp3iUEozzAGSYVcaqoo9mLrAIAxS03sPNPEu7lN6+1nb7BX1OyoYW2CyVt6QO0+S8o53pWrssJ5OHRTxf6uhUg8Hd4+rjFTZJIGnhnDPK4jRmtRVirKEaYMqdLXtbBL8loEduVVBcy8Iro3+sHwOfMbupnm1RgoCK/se/1Y2oBA9JTCMTTzXeZQH+jDh9Xnm8Bq3dWdla+KfIE8LX4ASUPJq3x08/AijFJuD2JG7Eu+xE3eu82LPsDyfKxCEFF56FZi9+3x64NwcuxB+5rlsOElFlxVxTlhgT0vOQmpXy1w4id0kjIZkDdLMivZ0Mdd5x65eLXdc8SSusaDTaEjdMpxWMJyJ40vyEUwcUAcQo5kcUdcKNUt9Bxc3TIfh6jiHENuieNawO0rfsR2PvjMt45/TsEVBGMZ88kbuOSSIs1xjbXEZRX9ttmLv7f+wbu3Nu+vauL3103576+yU0xoUWFTdn5aBkuYPMKv+uTXsi3l+169/S+LoCt4PXUWGlxPfn+skA8CNR+ZR2m8O7hGLykRY1JbUQaKV/eE+NE9uZd8dDbxBmjv6731xhCWJokp2aTU4ktWA7ZkF6WDufEkfvvj0qIPoq/8/VOzK/8PhSfm4sP63pZPgwuxPDkk0tLWgdP5wVrh7sPt/ZfC1gJ6VMGV3RH3glBDEHCNQGSNHeXGRuieX1WDX8uY77ryJTAnehnuOrGjJeQRcQHUCUU4K9x9wzwg3R5k05Wxp11phzsSBINHTQEq036v+g5b63GzutQILHqmVIPTc3tBcIh3LCzAF+5AuhOEBjBWPPpctadfLAZ6jdKh/o66na6qGf78SgT/UCrgTDMFJeasqtHoVi87aQiV8ZliPdjODjzNmydX46qE1ZdNTdO5QUYvT914ACultOuWQ5hXzgvsWpeEST1ITbVBik9Xx++7MTKU7ztdHrlfI+bt4/m6pT5k2vJ+ExF6LTWGwvOVKsvE37lO1Ji8q78vP/z6GET9tqTqlo9kjYclib9u/oVDo4jR1YiV2N3/clPJt253EyXM8n9ZiZq9NbyMcTWSME3b15cP8j8rUVcO02S/sJ48+9t18rzSVMS4nbKbN2XSO3ltdUmMjSKD2eFbG2Do3rrA2bH9McoZ9OnulOeAonZ3hms7w8q7aj24haG58w8Bv9sw+AkOu9pAU4Ddo7LV0apT4i4IjtVIyehko/m3jvnYbQK8eNRLBxrhVWFqnWXScZZR5wzdzsHsFDRfL537OkzN+KVydPh5d2NQZre6vIiUTYmeVsA8lYyU+jM3IM534yr/B3HqaIskiDNcr6/t6xj3GlG7x/oIcgyiTVfCffuv2KZ+MxV6iZXqKsX2LQzjloNWxHX3e8niL9bc03cV63XjAqOXkpxVah3FS3gqUIUWec8jnJBh9Ly+S88s7XkD3aeDHKYzqWNX2U5TU61OocGHapoCXVhdD4F08JdFXCQ/eIQ0XYJlEYXeNBM6m55/cnvxEV5Qqq9h1IlklMD5tIJIsp3DN1N4OqNYFVk9rm1wtIhpizi72KDsjfNakKjBX93krias5aZ8OW5WmTXCDVBeaFpzFbW+gejJSaEmtkkrUmWa0ExU2OoAFnZ0uDndxrA2sT7ZxGvU8qL1GmltYhPbB3PNZGhXNG7xz8Qm/aj+UeAaWcHmV+tvInTb+Ta/5rA0XUd1UkjWRJ5Crtgl+dM9VQhRK+2qqxygKCjkWDjGtSQbkeI6CZLQk1fJ/KRrhyUqspOUosu2mrMSK9JqkdcWytE+8BrS1v5kPDnNs3MeInQwp5PQqT1E62nGLu9dq3A2K08nApp5gTrH+CMSPtenIc4XAWNySuKWwT3u6CAgroGu8TYxHaLZvUYIes7P52F0t85SfRF7kkMP5l+8DR4RMYuaolcxUGU7w4+AtYZVSCPYJiZNpY5wsXFdyXVUVjI4soi4+hXXr5/dWXOOI5wuxzfwpCa/jIeQn5VN8PFdEuyCPXhwtTiAQwd5iT4E2K3QfAqxkcuDZopn+8wbjv/iYz2FSYw50CVxzBk5kt6Dmt//MhWcWrWdQTzYKupf+9vyMTZR/5kkPsc00xSvQAiAuwkaNd0wf8L88t66fefjhFVXrzCz18ui3C0jeOxVUs3qWSWsJ4LdvFzUh97LZkdt/P7/8sfMC4BdLg+uUxh1a46lz1urgBjZHdHrR7ANRxjSWTe0JGWDrODZP+L1reYoEyPNsU4HOLGzmRL6VU2y6Spcz4COwxO3MXzTY0J5ZZtitJacVDIOMY4SyDxCsgvMc13Zl6g0FEtNpJnZLVt7XEGTQTjy2nKp+m//41Pz+VMztM/DqE5ZYJLMHehs57AiavTFaPRPxqEiB5Uehwp0WsaNs98R+JWKd8Ks09AuuqdUUByxyZ8jD6gJLWQPQ85QQWqGUIEogN+phOqWBkq/2ZqKohh9sD5E+TQypNwPntihCDM7P+WO3buMNhXC0uPhcMBmFvapwETQTlVIImS0anKy664B1/gN8aruoVPtmqE79RrWQ1mNKYEaXl486wzWFQDwe774PiUQ5SIDrH+imJe5eu0Qwc8O+YHE20PfPl1nHvAU+Hx9tuyjEPAy/8Hf9etlxiBqnr2vMxK+pdNM8C4r971uC/R254fQZztE9qJKwmJbQGoMNkOvDy6R9efmD+B00nHRcGpLCkmK5AZvA7sVRnc0wYFWfek1/4nSCvU1QSyRorATZMWAOSmXnA5+myq6GCS6+A51BZzw66tg4zBHvSDuG048AtWXPb3W0qwugpEwObj4G59OaxZlV3euKH5R0w39GudQVYuL8g3vSfCJHdk1YFnQ/CfOt8P5qaWUhQA1OT91yuRsz1Q62DCp31QHfAWf1aXOZ1pNp9xfhHlhEehP54u0N4EoiGrio40hchxiv9zLu1q2gYM+fKdFZySJW+hNGDzvw2UaPKCLmEa5mRJ1ZXiUhWNAeAgePF7H3jd0yoNXGvYRUMwZN+J6n0bLXVkzxCZ5WDfJw+i5S7qTzeDN8jCqw40T3NcE9FJWYKeDiGZIz7Yr2cBnWeufVS57CFaZYH1oVashze7Z6a3Ox4T60WWC4LUfcmgjNUPlhImSkWckgCRNqiFLS5YgO4aKYNAuEBHRvCaAwZ5PvpDEZsunY/IRRsGDRmj+acESyWOpAv0zfYPsLbG8bWFVlL+tZpisXQZQR/lkPTOA9XHE6UN7tzXoF4XR8g5nWKx/RuBvUGC3ee7IqbtcOsM6BRFGglnVf+uC6wF+ipFUeKbf4HGPsDARXz+FhSrbnHosmXwo2w+9Zz98nBM/48eHTZY0POA8tc//rfWyIHlVFAL3xrsAJs25gfBREODKFldK0uEgryKkRsdw3DlXKBo5nGYBrgIAVwadyzkMkO0NKkYE3wCE8y+FSdtDeAhAHWhgXXnCTxxRGaiCqQrvx6uGUCGuE5/vYAi7gDIdWl5LvJWVOkKfIQi7Oxe9YSiC5mqre8bNFwyJkx1YKtoehQQnhVTl9uPdd7XP6FR29tPLxc9aWLbTkfJGOuYE6KUJU9BIrpFwepI13A3lq0Sk7TVNDq95nkVYfQCQImNzqqemEU3hdsNfOoYea+KxnbcQ+/QNicvHeFp0UF2o986SgJJsKYxm658XvLB9LKo+tfVDfPgK9xcSa9/98IpcFuGz1BoArdAAtD4faVXnC3pE13otPulWZ3ncHRxSJwNgc1vIJCcnu4opPy2ztSYVwgDdGCiKGL0TP9VHY6T2MkI0BVJFtK2QDxOHHF/D01qrwqKySmAtv/jUF4Tefjg7ONNs+ZcmiGiTshZPOhK7b4L0T0f5zO5xDIGr6RUlPZ/CtqOwmfWT/OkJzdyC7b8EEQNikNlzAKlRE5Ed7E/JGmB7YqtkAMWvw30H4JPvfVQ8V4y7HkDumQXIdk921k9mVwrCUJTT8KDqkBOp4Q3c7epvzBDQgvAI9u3kknTqdIJpVXE8gBpMAOvHS8nug3u73OjtcqMPjxq9PWoUPjn8VAiMG9ippj8Lm0VH61Hu/Bd0AX9v9LOIx+T1mV0orfc2Pitvtwh4QO7j4UbCN3L61fMEoV/vp7miUGUyP1k5K3xQfP0GXBbTU4R19lWEVCxK+ctz1SOEjScdqp1kpx7P39ZnMtv7HcS7vPsA7ahgzcq+197zHj61+lOZbWK6W6rvc2DNPYvzXzq82zJwFC6DBuGCYeTQEeuHheSMbbr4tXi4P3fG3ViBprvl5xPUoNXtFuySIaehu4CDQnWOAmLVIuTmNgjxG6frc5e18TSmbI3dUiQPT4zXnyQdF/5SyXjk3VVBqe/qD5JEoadrzIPXmM6uo4M1Qq9/vRwjLBU4f2rKw/vSOcY2n6zUNkKXZS8kdm1sZeMdgB5/vhB6Phu7wVtws+I4gNKZ8O9/3P8aMay0VW8QTEeGUufEIqrTkaZC/ZAXRv4R0XiX38s3HqWCA9Mh2hQlqOmyiARXO1WX1pSrmqBnjQ5dXSEAyfScHl+8mhdIe2y5Qn78gmcdPON9U6tfzV0UDXn3wQXPEYZN3V5OFRj4oa+MJFwZOXR9SrgqbvIKcrc3yfZPulpCYylN0uWQFJIToFqQ6newVAOA/EE6PB8HidwNMwRa6XCAf6zZCFf+8KP15+vvD7QdZEYgiTNF4FGYxIY2//egLW06vFSrtiLDTmXJ9UX2XoSuga76nQztEXkPU54Ob2ryw/ZCsEmISeDU6TVuKZmKeBlwcPrr7k9IG5vktjjzqILDKR2S3/XS5k7iskJMsatiZR4ZZYlSQbAjtSOcj237pHdZxvQmZPXBdPgYvDdKXekFtG5YYLAGtHOLTgkBRepKVpGi1I4JXqLr8aivT1Xmk3QjxV2D9zya1OuvjivS4EMHmQpnGBrRybKRdKq74XRaQ/tVAvZuugfMMjiwoWLyR0pNuAT1g4DI3pGSmHCBM4iy5GICL7g6nhchF5XIdIh6iIMDAC8wBRFhra8V4ArysTGQfFn11IZ9+B2eIYCns2+jbHCNnxQtk2vE7+aTiK8Rq2580pFe+fVLNNALPbx+Z9v0pbe5gkMbZQ70XtDLW0aJOHcffFA2O1liynS+eE9T2MGHsost83AaW57yIFSzFmZRl3IEh+jWY6nx2IYeczKzju3aAxRK6Q2EOlhlStYKCr/u+FsqcOxUiKAz/CiMuFqe8KNC7sRTsmzXAI2cDk/XLmDJKHNtpZ8MTnwFYF1IHKFgwKxtW4L4fGndewJD9ZXPQ5jEyYLdCMPupCUyrUMwHa5y2YAEWq5TArOR0suwyfrF/FdBugVZftrrPkdKZEsQgAvhNM1o/9STcLo4nLonnVjtTS2F5RdUdpOOLP4om8yE4/kSdznG0MwemiEjgtOH52P3BnSIZ97/4BS6RnmIFHB2R83eHCUp3feQT97ikn1jSSWM5DtUR4bnZ6SDFfJfBXwTkXir9mOaWyOZJ//VsZN/irH4KzN1/yLYO+YjeWbMcutQHmuy3AteGaxfKMfQzq9+GRwFhhChUp4Text2Brhw8GezoWC1cSEUzhLK/yO0K1kAZh0Ep5guyywfsy0gnGpgsiVmToVTP8fSWLjyy9UhrHDBykUZ989HXZj7vzNMsukFZr0wgYRpsCliHkiYreSZQtPEvPv8J4JU+s23P1Tjwth/qgbQS8JZhpTwo8VuLAs6eHZY8C21e03Wz+1hlDdm2+Xkn45eJZdsoRKQSlzYzBUHJ7J41VxmqT9i2zDacLwJmyYVJeZfMLoTiN0//86tKgmbE3jckBrcoFJ2dPJUI1y15spKzFiM1/fR6sRJao1l2H29Kf//KP/3JVXJKuvqr0J90awLvsgm6+5rbp+fj5KR0a/Mr5oxgCG2+PXx65+V4ulbxZg2TPCFf0WDIyKmZ+ItjxMR1E9jafqFFkQAy2QJncXWNm3QuLYI/GrFxdweVqfrosKNQ0+d8RvagiTGV2oABl0kBcS4zLLn94sQNI0RXp1koAsnvcRBN6C+iFhsqWJDzRtq8/IgNa0T+44YMTZWkLX+FbRWL1ThqrA7nt0=
*/