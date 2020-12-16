/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   begins_with.hpp
 * \author Andrey Semashev
 * \date   30.03.2008
 *
 * This header contains a predicate for checking if the provided string begins with a substring.
 */

#ifndef BOOST_LOG_UTILITY_FUNCTIONAL_BEGINS_WITH_HPP_INCLUDED_
#define BOOST_LOG_UTILITY_FUNCTIONAL_BEGINS_WITH_HPP_INCLUDED_

#include <boost/log/detail/config.hpp>
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

//! The \c begins_with functor
struct begins_with_fun
{
    typedef bool result_type;

    template< typename T, typename U >
    bool operator() (T const& left, U const& right) const
    {
        typedef typename T::const_iterator left_iterator;
        typedef typename U::const_iterator right_iterator;

        left_iterator left_it = left.begin(), left_end = left.end();
        right_iterator right_it = right.begin(), right_end = right.end();
        for (; left_it != left_end && right_it != right_end; ++left_it, ++right_it)
        {
            if (*left_it != *right_it)
                break;
        }
        return right_it == right_end;
    }
};

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_UTILITY_FUNCTIONAL_BEGINS_WITH_HPP_INCLUDED_

/* begins_with.hpp
IfJsDidvNfrw12G7laMBHzfYJHeozo+/8fKmeqwJn9J2l5zV+TF5bs8KeU3UY/LmoRXygdGPafdVD0D++ljmNJnpjLwuw528fj7j5CMKy2t38r1Rl0TeTg7gaeWleZSEj2lbISdDeblQ3hIobx2Ut0srrz/m34i6P6iEsnofAl4bbLsS71j5j6y8xcj/BXWbIndguh3SlTfM8+2m+W2qlCWdqpSHelQpu/pVKc8OKVdeGlWl6ezM324U3of05HfDKoH3Zm/c3+D5PJy891GvpTLTC3mBLA7yiseWGKaXXAX8j/D9LM3OTl5rzLtwUl0fZTiTK58Afl/0LS97KCvLyWuA9V3kHSfvVTqz8oCv1c3Pu369uU2PK+taH1W2RBxRnr73qHK87zHlrcFHlcvRR5WmrC6n4Z3XB+A3JSIHKH/0Tgu65r087Jr37g7XvFkeD2eevX2ceQ71Cff8m1dM3V+88ppc91rf0dOb+5kzz3MRuFZishfLZ4D33gB8L7K9ovjEBNl88sJsPus72HxYHg9nnq0o+7U+PT0beWfW/chrVRPZe3/Hj7xYe2OeAGyvB7Q7c2eBdxPLUx2sXZH3M/pdA61+wNPa5IwtuGVo+6ve3Xtf9Z44/CrT3ebhzHMsEtel3HeQJ8fiHrRnQ6YHlpmI90SbdPW87jW+7nUvXn/nbxLa6RiTYXM4eRejnLyV2lhxHnhe1fttdt5OwNN0vGQLaqm2v+3drvdt7+jhtzUdnXm+HIvfOrM3rH4PeU2TcC++SX1PL+8edb1Y/hfxt0Bs+/4e3JedvO/uxW/6eDJ9kNdzFNpIYTyHk3dzKN6F82zMyr8APB/UceukP3jsk1/2CQn0CJvQlfk6/v41+v/smH1ycTjTA/nvDUI72bkeTt6A8U7em1pbAQ9i6k5ehJ3pgbw6OIZ282T55IvAG41jyEU7sxXynsV1RitP1p+QdxvX7vsmfSAPHMdkejj5fx2B92xVro+T13QIzslaGzh5H6I+hVq/vwS8Pw9HfRTeF4Gn2e6E9EsrNp4j/3WcI8NDS+RZfkwG8i+Oc/Lr2VnbyZeB91X1vv6km/LQsYzv4eQfxPVj/eAfPZt7cX2d/F0Lcazh+iIvfiqepQhnNpOvAO8Kyn110nnbCyFPNv7F/taYDIXJx9+T+2G7Aaps4uC+7+QfxjXK01qZTt4B7G8Obh/kPY16ZHA7yp8Bbw760yU7qzPydqB92vP+4uHkvYF9LpjPgci7C9tyzaTlnkdG8bKd/DFYN3tLpjvyOqLNwkKGOS5pPuPk/x773GhPxpOvAW8b+tv0jqws5N3Etjk86Sl56jhuHyd/Ndb9HpXX6TrwvsJ6hnCbOYCn2f34mBBevnwD+Lcx701PPt8CT8vbX/KT3hxz05O1tRQPv2EcHk4OsPJsiYT3oi2V5pPSaT4lj/D6K4WUJ5XQd6VSwltsK6Pv2tZQXZQN9F2l3MXDsw3Ou9Ku8wLZwv203CXaXpAWz1/Mebpvm32MPF9JH3P9g1u+CEhhi8V8XSG1Xizm6wHpzFIxXySkN5Cn4JmJn6AODZ1nijwlKa+lJOWES3DCbEmmqrRQHYHVZ3hebUbv253FvuIv1OcV5PngeSQu8waXaV/SVq3noyp3u8lktnaueYOq3/dgMvFvMZPJMA/+jUNfGyyF6u76BWO+FVCnbCy/MSt/WCtWvrz4Q9XDS7X7qA4/ybxenVBOE6FeA5B3F8oNZXK3cLn2xQdV2UeQF6r79uJI1PVraaBUptVBgeSFMsNRZhCTeY3LvGdpgpl+RzthPxX0O4k8H0G/1NZMVoOlreAonWGbO/FEBeq3Sda3+YPIU3lMHP86YxnThTY=
*/