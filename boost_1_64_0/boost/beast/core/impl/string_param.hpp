//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_IMPL_STRING_PARAM_HPP
#define BOOST_BEAST_IMPL_STRING_PARAM_HPP

namespace boost {
namespace beast {

template<class T>
typename std::enable_if<
    std::is_integral<T>::value>::type
string_param::
print(T const& t)
{
    auto const last = buf_ + sizeof(buf_);
    auto const it = detail::raw_to_string<
        char, T, std::char_traits<char>>(
            last, sizeof(buf_), t);
    sv_ = {it, static_cast<std::size_t>(
        last - it)};
}

template<class T>
typename std::enable_if<
    ! std::is_integral<T>::value &&
    ! std::is_convertible<T, string_view>::value
>::type
string_param::
print(T const& t)
{
    os_.emplace(buf_, sizeof(buf_));
    *os_ << t;
    os_->flush();
    sv_ = os_->str();
}

inline
void
string_param::
print(string_view sv)
{
    sv_ = sv;
}

template<class T>
typename std::enable_if<
    std::is_integral<T>::value>::type
string_param::
print_1(T const& t)
{
    char buf[detail::max_digits(sizeof(T))];
    auto const last = buf + sizeof(buf);
    auto const it = detail::raw_to_string<
        char, T, std::char_traits<char>>(
            last, sizeof(buf), t);
    *os_ << string_view{it,
        static_cast<std::size_t>(last - it)};
}

template<class T>
typename std::enable_if<
    ! std::is_integral<T>::value>::type
string_param::
print_1(T const& t)
{
    *os_ << t;
}

template<class T0, class... TN>
void
string_param::
print_n(T0 const& t0, TN const&... tn)
{
    print_1(t0);
    print_n(tn...);
}

template<class T0, class T1, class... TN>
void
string_param::
print(T0 const& t0, T1 const& t1, TN const&... tn)
{
    os_.emplace(buf_, sizeof(buf_));
    print_1(t0);
    print_1(t1);
    print_n(tn...);
    os_->flush();
    sv_ = os_->str();
}

template<class... Args>
string_param::
string_param(Args const&... args)
{
    print(args...);
}

} // beast
} // boost

#endif

/* string_param.hpp
qyBduYHO1QRdN9Ilka67ga62CbqppMsm3TQjP6IJulTS9SFdmpGv0ATdANINIt1AI3+gCboh/2HvWuCzGsP4OWu3SK112Wypreu62tpWSxdLqanFEEJYtil0+XQhhLlE7kMYQu5RmHsYcr9T5B5yDyGEkMv/PN//vDvn+86772wm4Tu/nv57z/s8z7m873u+c97n8lIun3J5So7jTCM3hHLDKDfU2X71yO1KudGUGwXsA+aw7xrvmOL64okjxhEzhrjetYv4/aCLGf7r8cLaWGGUv8d7OCh1I9YkAo0HBUDngJaBXgCt2xh9545u0S26Rbfo9v/Ztsj3//Q5U6c2Qd4/22/fED//6S6/+0rHmv0ZGr97o+47Cs4ucla+fLZt/6MaftNm83umN30RV4wTvZa+iPn9hFfFiZvGp1LeRvmaafw0KNdGynuh/KqrrPR4+m0UgX+l1LeXconSl8R6Wz7O049jT8XfnWV1vIjfa39H3L7tM7OZ38vxPGAc/cFq6tojYo4ztAn546UN0Gc0vmBuPlRrfMDcfKlaHzA3X4aPeAfrfiR63MskD1+vVA9fr4xoXP5W69cwReYgFg1fetr+1y3rvdB4+7lOt0276L/r16DWQN5db5vvHGKb78pvYTwn+DyCDsrFASVoiN/qbYA70raYDezO3Fu9gf2dcwbUE+9x/CwevycwDtgLWBmDcfXDlou131rtilGbYsNsin/VntgBfa4ANP6H6DxFdItu0S26Rbe/vm2R73/LmtiE3//Zg63vf0upxKCr/H9Var+KIVcyG1SdxGqr/SVD1H7EEQbnEmY55hKmauYSAuPqbKU8kYjfb05b7zMavZUuvbwQH9+GTttrRowm74BDNy+4QXrn6nIO1OnlDfan1/6Ob0Fb8e+gzo6468W7iV77/kacWwG/Kxb+JSm/qJtTAb87Fv55Kb+ii30BvzsW/hkpr9LGwj8p9cxxT3ldLPyczJDyPxQLb8dYpXJS5UvaG99jmxQWqzZxB8Pr51cg446HP0LKtcYt+nh4yLjj4ScXM7ZdHw8PGXc8fLmUVxi31RMPf7DwPA9/acbDU0998fDT1fm74+EPLK4/Hv5kqa/WxsMfs5XFw9vj801+cixgLMIMO1dFUbAv8FkScXyC351LQsbDRF0fIH83NZ7bCX8nlk3jECmnhPcHtlOy1O/M/mHr68x6ynvNeTI2tJXUT2G/oLxXDDb7Uqbwj1Px820Zx3mszzjOpo6/ttvv7uZyHJmD6wZaxnnSDaNV+0WcJ7XuZ7pc/2VsT1u+t26+lPVZ6n6mivz1unlT8uezbBqnCX9icG7c1M+jUo5lJSf8H2LSBj17WsCxdozEDbJ9NqbW4fGZwfaaxzU/rL+PZ9slmfXHPuOAas2PDDO8HbPMsDlaXFP4HG2B6ZqjVfO2uA7sw3WEtG3ttoZsKYwb/Z1jc+0YaVv+Hkcem+B3tVXiWKv8tW5sgt8dNxpHfs2zGfzuuNEY4f9e+9v5xxjq49iDfL1xoz1E30rcuxHauNErhGeiZ9zoiXz2uvb9C+JGo/P3W8f8/Vup1v42O616+5YR76xonjl15cZHxw3978/fB8Zp5u85/27QZy6BZVuuspFyVY2UW9wIuQyD7+x8rkJO/m5LuZ6Kj++MwC89+HqTr8DgOwRwAfligX1Atp0ji3aO0fRZnAHsoWK++FsHfNEj5iuX9o08xtTlU89AxvjtDJwOLOQaLcOBC4GDgTcxf/Ey4Eh1XXzu8vcl9Lp6Wfwx6AO0hywAXg+q/eH/HXPVUNtI5fwEX/aRRfMTojaSemwkq9HvNoCSfkww+oCKQFNAC0BLQE/8GLWdRLfoFt2iW3Q=
*/