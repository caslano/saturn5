#ifndef BOOST_POINTER_TO_OTHER_HPP_INCLUDED
#define BOOST_POINTER_TO_OTHER_HPP_INCLUDED

//
//  pointer_to_other.hpp
//
//  (C) Copyright Ion Gaztanaga 2005.
//  Copyright (c) 2005 Peter Dimov.
//
//  Distributed under the Boost Software License, Version 1.0.
//
//  (See accompanying file LICENSE_1_0.txt or copy at 
//  http://www.boost.org/LICENSE_1_0.txt)
//
//  See http://www.boost.org/libs/smart_ptr/ for documentation.
//

namespace boost
{

// Defines the same pointer type (raw or smart) to another pointee type

template<class T, class U>
struct pointer_to_other;

template<class T, class U, 
         template<class> class Sp>
struct pointer_to_other< Sp<T>, U >
{
   typedef Sp<U> type;
};

template<class T, class T2, class U, 
         template<class, class> class Sp>
struct pointer_to_other< Sp<T, T2>, U >
{
   typedef Sp<U, T2> type;
};

template<class T, class T2, class T3, class U, 
         template<class, class, class> class Sp>
struct pointer_to_other< Sp<T, T2, T3>, U >
{
   typedef Sp<U, T2, T3> type;
};

template<class T, class U>
struct pointer_to_other< T*, U >
{
   typedef U* type;
};

} // namespace boost

#endif // #ifndef BOOST_POINTER_TO_OTHER_HPP_INCLUDED

/* pointer_to_other.hpp
tS2XvW0hmHVayCcQSiGSwrf/cqL3JT5/xb+O+HAZs1jIn/heAsnDNIpnkCZrF3DTvvFR5XTorAmifBHUeYF3b2PjnBAxlUnZzhsUmnE9U2aJXsztD1Lla6DEPe5QmRFlnq0vgd1qCRJcjd90ytItNt5pb5tIRz3aEu2p2wWgFOqil/IhAMVOeQbaErmvuc0s2j7nJE0XTqXGlZh2LP47p3chQWjcHko2NFXqKV/Z2EVhGl+m7wQdxxfo0xpanwzwZXTR8rd6+DmEPIOdJ8W90eofyvDjWBhjjoWNKYi0dJ93uLF0tFP4tvQg377HKfiy8yBukHrsflh9v3R266wcoSgLZ3qS/djZraTtc7KPOxVTZ8/CqzPxPXK5QmDI503BVBqxiZ9ywA5boCBEroxikECVC6GwS/BzhhrXc8pkXK/VtyHXPqRKLWJjXbqqDSlXGguHCTAQJ16c7LLsiP3ncyR9Mmq2T+DbZWw+A19FW+aM0LM65X49q4Ups7oZ8E8BUPWb/UW3BXq+UuqQdmKe5VRX5pdc0xSZYY7W0WfLwWirE6d/UsSjjvxHav/HC2Xy/THzLbyKsBz2HfNkcGZLEDbOZiGWwPPfxrZIpwXYG399fG8Ho1YXbZtTqofrpPv0cA1IXQRqnFjxawQ6XSouf5Vjhlo5QPQelnRFS+stpXjYARCmfSWLLqE3rfEl2sVf3xaRN460YP+w/RL21vMQDVxrlhcui8exvtlrwTLoq2Q/nasw6xRiMN5+UG+HWsi+TwOx89Nu9Tyf3Z9wx9+bYBDoEH4qdDLxGo6DuSAuMXE2G5F48bx8gJb3tO++g8B16Ep9Y197MZ4Ma50yP9z4NhJNWLoVbTI9w+E+EGrq09HofHgCc4THsalJgA9a9YFYKE2r/xY0s405V/o9z2edFIKta5nneScEFVd1YO9uRkHrasTBM1amNf6BfcLcTf9NQ29u9XKfNuhbl6KPy1hZxNVQO6e/4Xne3zUN0b5Qm9TVBPN35/SXpCZM6kb25mdnKSGCv9/EYBm46rNoCYSIpVqIqEg6i57Cab3sXxum/AvxQ3aj3y/Qu1HC+1QDWAaw5ZdxaMTf8k4I93YT6AN5iRfHJUP1/zbxs8n+KX4ymhvRZqgKzU/a98qFCpO+5ST1mBBPrg/Sp36zVWYWGUbMiJJCVyivzYGbVOZHgJf96TUWWb1QpYpDWnoUi010Mr3PmdjHvq4V+6N1o8+2KVpvMVU592ESXuX5mSrJShjCMrGuVPFlWPbPDuktfoBABH/1LVAA7IHnYfkT6mQwavxJG+9meyCezEg8HvYLSTiDLi+6U+WiyMIK+gJR/sVHq024H11oqH4VSkr5A41ujjl7wVF+dyzkSTwTj4ScTiMezeRe+a/DI346jmcjiBSep9SFtJUPIVwJET9I644mcqtQxO5S4XvFuTRNlR8dL68uAWyu5sy9YMro0F/cRabipx0/kqQPJEwFL7hDoRY+nYc52lutvmu+LSRwfv6+xlRnCLqK30cl6xiq4lZox9WojENrSlg+DG3SqTuafov9eXP1V/+0if80t9XV4D4zXjW/6Hi4xd44//T88m94lgx3Dpr0xI7yHJj6ptkTVLePTnHPbC9dcJBDcNRAV6QeiZiVqSNmfSU/4IkPJlDE8mfmSF/Z/Smc3ss4vdMK9nDsTXSfXGZxkPtjECn59luzYGqOY8ClG0Pf9Rp77aWXIggxbmXgp8HQgrGRoypb0iDlW1WVjUdX2kcbrq2RijTX664tSz85ou7yvY2VLS6rKl6FLBfvNh02Antu2U6cxP7JwQ5dOrwlDnsNsFXBsgZUZ2JpAOz94b3BRCMvqBmxgUrA9Cw=
*/