/* Copyright 2006-2008 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/flyweight for library home page.
 */

#ifndef BOOST_FLYWEIGHT_TRACKING_TAG_HPP
#define BOOST_FLYWEIGHT_TRACKING_TAG_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp> /* keep it first to prevent nasty warns in MSVC */
#include <boost/parameter/parameters.hpp>
#include <boost/type_traits/is_base_and_derived.hpp>

namespace boost{

namespace flyweights{

/* Three ways to indicate that a given class T is a tracking policy:
 *   1. Make it derived from tracking_marker.
 *   2. Specialize is_tracking to evaluate to boost::mpl::true_.
 *   3. Pass it as tracking<T> when defining a flyweight type.
 */

struct tracking_marker{};

template<typename T>
struct is_tracking:is_base_and_derived<tracking_marker,T>
{};

template<typename T=parameter::void_>
struct tracking:parameter::template_keyword<tracking<>,T>
{};

} /* namespace flyweights */

} /* namespace boost */

#endif

/* tracking_tag.hpp
VRt4RaLQHOQbNAfeSpoDbyXNgddCc+AVmoMU6C9J0HHiehTvgpHQ4X63YxPVh+nuUI3yi0MnTWoRtkGioIQ7L5gCJ1OYdbwrEKb1f5rv2XdkhOY5cGqVS05axVYR1M5dVKgjQbKs1AteoV5AAtcvBALR0I2cIn/zIhXjFToGL3NMSNRf6XQ5sJRwH9pK+mDSpfSLId0/Hu3XEpU+mLOQ9cFR8Ed7uaRMuAMdFRhqbsCeCPKwDtIz0FXwB1VICv/KYZdkzh2Lua/Xc0NTi442B4YnOYnzgRIbj73gcVt0c8dHd8c7cgrjHQvgGwnfn+HbCb674NuzKN7hnPS/vZ+o7of7P99Lpygtn6zCHihtr3KetXqxrfOzqL2m87MvP7R9frb/NaW8/UuqOj97ikC1kcuqoH+yiu/oInv2TH1EJlmDG0urY89Ws1L+yFU8vx37rr17TPxbeYjntrm+pbLjij2qfpxNa1lsvmMCERi93I5SPeq1z4iPyTMX7zGdh9xxuqKyLspH8u4VD0h59w4p5oWsJ11Ulechk3/hsZl76Wchj0Aam72Ifv3YotWLRknTFYhVJMURQGDgcf3MYul8cWZR83TFubwtFjxetnO31PwXSFW3ePJUOm08RtyLmi9Vg/mSe68+z7jXj6bj52AlorqM3MLmylrCFNzvJIiHJUSGAlEDIT4ivVe+hIhXIFwI8RJB7JsnIBwKhBshHnYQHRLiMGmLmNU6M78uxHtG8vUW5XUovsYwrcXy9RL+WnaMvyE/QmjT8PP9yI98Iz9e+BduGugAdcshYbVz8RHkUqAd1+7pcZzgF/Mem0L6OL0PfQCS8jnrCb/uA+fto+Yb45Muvh+ez+zP4okdutGc8B+wA8ae9ECRJEP+n2IOfH1tAWK7EUIeG7xFINgIceRGQswe1XMTjfFViX75/Aw+V+m/7p1X5fySq5qm6XZs2m3chCdHNVn6gcbMvPlyxlkm+8j859iYeTeMzThZcsbJYjNOlvSOVrM929lnRc/ND0MFg/Iqrj0/h8WQpYhA8a9XwP9m878DecjVOQvUmKevvkhDRwD4FxDUaAPU4wQViVDIewqGGkkD4F/zKBiqoXLPg1RfKXrZ+TODRS+rN9MQvcwzU0QvC4EzC/8C8tYUOVM9RD520snCZ84irctAGjDFf0dKIcbiv2AWRSIbEJG1GZFPGYmMtiKycEYwIsfOMBB5ywxB5A0fApHfkA/5EZ4QhxJTdceVLDhmJm7PMmmXC7aaGFiQuE7N49/npLZC5hIoulzjYQwzadkIucKDPiw2hEMMw9sALXkjtYyiKQuZWt6WggS2JDaEs8lqqZEN7rUWbMifHowNN083sOGm6YIN1xwCNmguc+BOL4Wj5eEc1brkr8e6LOtLdZlnrgvlXGSVs6J2COQcxXMuUnMWYM4CE6uJCRcSE1z3IROWGZkQ8qwFE/KmBWPCsGkGJgydJpjQ/wNgwqfQjnRJNB23Drmk9rtpmR4ksAuRcudci4mhYA2gWOIk77Xw+m+kpugzV+3+b8wBesmfmDzDEzp1wt3YCncTxJ3h5L1MHLNQVFU6YgHha/ImmspyqRE4kAxFCRA3cIi89JKeRN2aOYrjh6dQegMG5JqsJ71E2ZQ5FpTdsxooW8mVdXmkz1nHFvaJTFnZl/L2YHl9xrw9IW9gXCbKY0xVp88HB3frx0T9CUOIVemhiOFCOa3TgQKywD/6x4oKwjUMJHT9dn9OII6Sh0Iykdt6vjCDjJuPc/tfTtP+BB+zPUzgJSm1ZBmD7amR9lA3GKU4nMiW8ZLa6Km+5vSbKxN9HuPtU3Quy095b5vNFBjH4I92HGQNo68see4jS00=
*/