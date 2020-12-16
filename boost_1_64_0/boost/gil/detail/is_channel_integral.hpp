//
// Copyright 2019 Mateusz Loskot <mateusz at loskot dot net>
// Copyright 2005-2007 Adobe Systems Incorporated
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_DETAIL_IS_CHANNEL_INTEGRAL_HPP
#define BOOST_GIL_DETAIL_IS_CHANNEL_INTEGRAL_HPP

#include <boost/gil/channel.hpp>

#include <type_traits>

namespace boost { namespace gil { namespace detail {

template <typename ChannelValue>
struct is_channel_integral : std::is_integral<ChannelValue> {};

template <int NumBits>
struct is_channel_integral<boost::gil::packed_channel_value<NumBits>> : std::true_type {};

template <typename BitField, int FirstBit, int NumBits, bool IsMutable>
struct is_channel_integral
    <
        boost::gil::packed_channel_reference<BitField, FirstBit, NumBits, IsMutable>
    > : std::true_type
{};

template <typename BitField, int NumBits, bool IsMutable>
struct is_channel_integral
    <
        boost::gil::packed_dynamic_channel_reference<BitField, NumBits, IsMutable>
    > : std::true_type
{};

template <typename BaseChannelValue, typename MinVal, typename MaxVal>
struct is_channel_integral
    <
        boost::gil::scoped_channel_value<BaseChannelValue, MinVal, MaxVal>
    > : std::is_integral<BaseChannelValue>
{};

}}} //namespace boost::gil::detail

#endif

/* is_channel_integral.hpp
wvJ8dTPXTMSwyqpqsnSbl2/Q3xlZTfXJ0r1oaXuAsqy1qlUs9hEHbbiHqzZYtWsLWInf7s7CeCALtetW4NrPbWHbqS+xdH8EnR2L+txhVaPZ8Wp1Ob4A9bkreS6AJb1orv+muNuqNrA8P8zZqRZi2GNVQ5itmJMdv1toHSmR5Tn0y1Ejke4nip3Z+X0f6nsU7LeqtaycgabsOJ7jkJXeidPtaP24COR5Ql9HFvJcR5JlgRnXIbFk/U26LS5+8iP0pVMUHzO18RHuK7rO0BzJ8rxwNy3KGX2W1kTMjr9/rgnmELKdih2vytOf0JfOWVVudrz6f9TU33G/YFUZmCXdK7Ecx7toVa2Z3e3S4VOkSzTGsDquLMrp96tVFWc2pvOUTMjzilW1Z+X8x2/HG2BeIjvKbPqS+lhrqGv0JVuW547BcajPkOs0/pj13Fathv7eRPK6FfakYNwBxHCT+rxZt139am+A3aH1NbNsTWad0a/HaC6w6Pb8wLAhiO+RVVHTw449Oz8a8+dTq3rCyhl0JMcT5Pmc0rHjjf1zi/5b8iur2sti+ODMxMaw1/oa0+FxfURPm2O96/C4Dggnywwz9usYsl7MdjWdra/LTTZ2POO1UzhZQ5jx2inB5L0sTrNNzYUZr4+UxbvFk+F4HtdODisz47UTrWe9lyWJbCuzhm074dyYaLOpQsy6ZPwWc7mf3aYawIzXVeFkTWHG66oEslYw43WVM41N9YYZr6sSyCbDjNdV0WltqjnMeO2USJYFZpyzVDobrp0cHtdOcWSoM89v/KW34TdFh3v/X4xNsn8w25qvj/6+qGDxZGWYXaw8YwLKmcHYDgd3rf8W45YsG7NxtzsiTxdZCWb2Cadqo87I6jBr4Sp3EnVGRnM5bMPpZxhjcZlsig4O27u3mB/iy2xTs1i64WtPlIf52dQelq7RoxYlYFmN469ygatj9GfIbSqW5Vm7zeAiaIccNkVb0cFOzTixCvWZ06ZysHSl51VsjXS5baqaRbf8g4ORLiC/TQ1gVqzJsu9RZw4brvEcHtd4CWTfMdu+6MXXKEthmxrObEt0O/154SI2XI85PJ8jEyyeLBfM4ztGQjq/oqyfeV7HkZWCGa+5Ysi8lsV7OqpA7+kCinlPF17Me3wxQp7xxbzHp4p7NyeZtzzDybyVM45suw1G9zl+1e/rl7Vp609Yx+x90+A8Vs6mRrH+uX/X4oPoZ+VpbrXqdrzrx9eRZyWbGsTybL4qUJ93g2zqUVrdlo7O3QPHc9q06z9Y8JGkYjhebZtazPtudB/9vYI6NnrshJ1zIq8VRewNbKprVt3unOkcirIE21R7lm7QnR/1d0LpKxtH2PHeaXxjNfLsZlNWu24PMy7FGtrZx6ausPFufW2PQL30t6myzH6qWmUtjjfIpsysPq81CBiK40XRnMzKuW995MdIN8ymZtjY+eFF9law0TaVhx3v96Ryz1HOsXQ8ls5V4gjm8phJNnU8m263z463Yl6KtalxLM+hGW9HoR2W2hQtkGAvX+aYCFtmU33d6bQ+3KaPv/5O9td0HoNpY+5oENKtpDrLqFuloTv1vVq22rS90WBnsy+Kxpphp031MOm2c7h/VtRnvE17vwrW7PPc+vOKu+g8xsry6HDZhvo77tR3meU8or/r7Npnw/NSRbQYVm7T39feb1MDmbXd3uURYiBrzezc4k6Lke5nOsfBKJvq6SojHRn1CViPrXHvYawcsqkIli4qh30K5tbDNhXK7OnM+EnIk6ynCUZ7Uu7Q718fsanKzKZ02PQj+vVRm/qY5Vn60eu8KMsxm/qC2doF7Uzog8dtKpDZ9hpF8yAd2ddu0wZzjwPzjqI=
*/