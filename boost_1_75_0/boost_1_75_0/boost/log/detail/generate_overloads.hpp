/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */

BOOST_LOG_AUX_OVERLOAD(const&, const&)
BOOST_LOG_AUX_OVERLOAD(&, const&)
BOOST_LOG_AUX_OVERLOAD(const&, &)
BOOST_LOG_AUX_OVERLOAD(&, &)

#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)

BOOST_LOG_AUX_OVERLOAD(const&&, const&&)
BOOST_LOG_AUX_OVERLOAD(&&, const&&)
BOOST_LOG_AUX_OVERLOAD(const&&, &&)
BOOST_LOG_AUX_OVERLOAD(&&, &&)

BOOST_LOG_AUX_OVERLOAD(const&&, const&)
BOOST_LOG_AUX_OVERLOAD(&&, const&)
BOOST_LOG_AUX_OVERLOAD(const&&, &)
BOOST_LOG_AUX_OVERLOAD(&&, &)

BOOST_LOG_AUX_OVERLOAD(const&, const&&)
BOOST_LOG_AUX_OVERLOAD(&, const&&)
BOOST_LOG_AUX_OVERLOAD(const&, &&)
BOOST_LOG_AUX_OVERLOAD(&, &&)

#endif // !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)

/* generate_overloads.hpp
TA6mPOkJVsWCe1OnUqGXHEwL4e3gNrAFd6h2pYJHVjVzHg8igcM3KfuRxnbMBzXC/krTWNT/qaur7U7WXvtg8EcMJ2g7VmOMAFbJ9mBum+qp5qdkTJaMR3/103m8tTV6Qd6hjI3JGLN//xL1lg5AJh8nwobw0/PYuZyACVf/fckYW19dIp4ViZkg/+MJsBP8aDJ4h67tfdjAY+KbabE1jtoGL1sJiHxxSAZ7Q/dMT83ZY6PPktIgkz59BXmHa2DkVyyDrJz9cpeyBSLJhXtpI5VLZtMYTL+FeiZtC8TpHMb2iT4JpWWx4F5b4zDoeE1yMT1fzAX3QxEH9iOUv8pYBHYQJ+hAbB3y8nCqXwkrRA7fMgx9mLasRlDjkcfxFPT9nOfNjuoVKJNNhv6Z5ORzSFjSLK/WMWiD9ws8EQqIvDaNh53GeTJxTgkXD3f1Dg7DenHznUFOd7hs7lXlVjr6zgjfIY0n5YM40uT30ime8STT6+ou9ogDiaNYGn8q6rptLeVWtrACDN9+jSEFa4ppL+F9cyrG+WdvsLUmrRdg8aPZWk3NtgDM7sAGK3BHUiHTCvtxYuL2brA8HUyfkuE8VDgJEPaKhwFemuMSN6AFeEIC+t/2Ai2/qWFZ4MiE92Eaxunz81xqh7/e6uF6FztT+qKFxg8smpncZHs8Vfe4cKxbym1r1k5CPXT30LhiQc1UfLJ62CaDx08+Ha4e
*/