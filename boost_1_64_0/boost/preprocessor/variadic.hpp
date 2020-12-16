# /* **************************************************************************
#  *                                                                          *
#  *     (C) Copyright Edward Diener 2011.                                    *
#  *     (C) Copyright Paul Mensonides 2011.                                  *
#  *     Distributed under the Boost Software License, Version 1.0. (See      *
#  *     accompanying file LICENSE_1_0.txt or copy at                         *
#  *     http://www.boost.org/LICENSE_1_0.txt)                                *
#  *                                                                          *
#  ************************************************************************** */
#
# /* See http://www.boost.org for most recent version. */
#
# ifndef BOOST_PREPROCESSOR_VARIADIC_HPP
# define BOOST_PREPROCESSOR_VARIADIC_HPP
#
# include <boost/preprocessor/variadic/elem.hpp>
# include <boost/preprocessor/variadic/has_opt.hpp>
# include <boost/preprocessor/variadic/size.hpp>
# include <boost/preprocessor/variadic/to_array.hpp>
# include <boost/preprocessor/variadic/to_list.hpp>
# include <boost/preprocessor/variadic/to_seq.hpp>
# include <boost/preprocessor/variadic/to_tuple.hpp>
#
# endif

/* variadic.hpp
407hR9Ha2vgw7/L8kxRB7Pm+7mG41IRT5m1yr0gCOZE2RhhLRo6/T8wkSnn3MK3/DM045h1ZQrC5vFAQdedmopycRB4TE/ugkP6J2bQeFmz+z2g9JsoFWYbBuo4ag39cwMJYWE73CQF1c8OIi0U2T8or3xcOaaEs3ZY3heUZhEyh4tBahkxpOkVylPRqplHW1tD6l0lHzq8qtF7QUCMN0TJ2q0HJDBFnedp8GMuo1RuT0+YG/1oSFH3nvrY2yDUaoFnXHWB8RhxOBRv75eJAs1hwWJ4RDmd5ysCdpunpcwpCiNGGjCNTj2G1holkYjxRyvDx5IwGZXfQGO6cAWNVuMD6f6ph7v34LXOeTyijdJO9GsLsL57FxvMSW8M41hqm3IzHWsNUaC45TWmv9a0JyohB8PetiITBJPrj2wGbLFS4jWxS6VKJnQwWVbCCL29MwnamEzzvEgmb8eddqtL5YW0SlnFScgxbRjFVO1g7LAfe3VDMmfn851j88NmWfF7ejMeSzzkkn1fU3RdS93H29XT3bx+Mnzg0sH1QFTsLSvtCryJaG33n6p342Gqvr4Xke6f3Hpbva7z3Bvne5epfBOhXs3pHxNzjzzL/2jQ+Q2UfTmXNoOy1tCZ97Txpn0C0X6PyDccrMAC6zc/1YDNsrqdgaqULWLtYAKhY8LrmquWNWOWZWPPXG9pYe1Os+Rt8vMO2muU0/aY2eQHrN2+09OJNzXgsvTif9OKCunvy6kuQdA5RX0GjCq+GMDp6oVX+wih02Yob2U3lv9VK29TspW2gtG+ntBfV2TcvR9w8yKskdTHleSflOTLE7YL0YGn7Lpht4PA4HyCZrfClmSgUUsLYDBeXSMo7DLnd4PB49XE3xtIQWYNb4uJwX6jD1qMKpg8UejaF+EskJ+WmaTbL16YuDpuEbG1K6ccUGPNBiiN+F9O7lQH6jG6/J6ucc38PtcV7mY+hK+r9XlvlzP77kfYDeHhMyaVE54PNVvoaMVEfpvSX8fRMbyrCn/5ySv9RbSsDnNkd2ObaShuqbeXH6sYQJMvZwoT/QgwO4ucfmuudwcDCLZM3JMwb8fDJKvUvR2bH7Hya6n8Vped+AGSpEfs3iak4jyYw76b8z/L4KNZeeNRe7zXAl4U/XuVzxMu1Vfr8QXgqs/iPiOsoz/VMz1DGrLJvBB5wowN2rMxNROcLnG9Tdv28X6S8t2geDmho0XESwoqTqETBdY09+MYae/BJ4Jp0vCB0xJxha9Z2xszXVbvFNIxMAhZTJo+0lUssPJ39M/ilFr6MjzLwNWebhZe7uHwPebnB+88+vw38ruDxGuy+gHcAt1KUcC36dJqjJe4S4DqwL1+uku/dwHWp2A3PTp5R5Sz2+5AuJeT6pOo+vWrTSY7H5hPf18iKufc1iiLYvsaHlO7r/Xw0K6vPR4DbofiYSKOe8O1m0loOVwB3DuORoc25713Wue8J5c/Cl3zY+3kCa9TVwsQDXIA8uKlIsmL2bD+OdLtV3Ia5dcTEM1wkrHgG8jVdIkw8gFnHvFfM3ve/VPj3/S8Ttff9rxC19/2vFNa+P8WFXEVxIcYfws648nib62rE29xUI95G8n6LFf9hzoHWiT25TeNYvMj9Wldq6OO/kO/BOrEodwP/MMX6mHV8jZinK1He43zcEV4swBNi7lgAESAWQMogUj92QjTWiZ1osmInjD8/pOWk2hAuF2/d/ikV28L7kTsKap4+A/wSs89twiWq1nHp7HRm//lq0Gnje/5qs0YmEaaNO3x4NR4ikYcf9OETaUeh3fI/D/pFK6YAWNOvx5C/bMVCAGd43+HHGb4bpb2oHzskdtWJHVoF/LnW3vANzf4=
*/