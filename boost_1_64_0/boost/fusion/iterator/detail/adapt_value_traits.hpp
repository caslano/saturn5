/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_ADAPT_VALUE_TRAITS_05062005_0859)
#define FUSION_ADAPT_VALUE_TRAITS_05062005_0859

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/value_of.hpp>

namespace boost { namespace fusion { namespace detail
{
    struct adapt_value_traits
    {
        template <typename Iterator>
        struct apply
        {
            typedef typename
                result_of::value_of<typename Iterator::first_type>::type
            type;
        };
    };
}}}

#endif



/* adapt_value_traits.hpp
xTlZHFla6FCmpZg+D3sm7sSOwjdSj3l2IGeeo439jJoXGxPHYVdxeDUMewA3CV/T1DvpK8BFnhbnjtH16B85WSg2hpiN71yELy1DR54l5hIPMq+Rq6TwU4da+HR6OfDU/yDjTcj1DGhcY+sgZy70tKvoUXjAq9oJndhT5k10gnolegD7YP2Mnae/Ty+D/E8Ieg7XDWXOscyFTdHzT26jX0JPNXQ4/vkfgznz6oLPZb6/k7uvIy4yb/ISZMc+ovsiC2w9iZ0I5kymxlG7EkvAqcpAMz7Ecxb90K7I8WviKzJJX4xtfEt9d3UP3mPM/o/C39Xgky7F9shb48+w7y3kMkvY13D8eD22TA1uPYlObUMn/l2MLcKjZeP5t+FZ/1L491ER9TNyhn+hteifhV6jVyHOBr3dyA1PKSY3KKJ3iP02UKON8tDfQubkSfHT+tObJQ5dRoy28x7+XfLkE4Pwecj6dGL1FuLb1Txn8lf4tgOcA8YityKRfo65d8KTWfgv/GpmJX5tAv7zJfTqb9D8HT7sHnBvR0/oD4QS5FFf4QeJS2l0yvMk+raZ80rbf3zDel/jA8ipUr8m/p7dH92h5i/BDxXRz0K//G34hSriLTJLv8n8Xag/OvUnbsKnx/G39NS8Y8mVn4bOFWOgmXxpKudKx7PHL/En5I1iBHu3897tvfEJ1L08i5qcwrNGH/bh341DN55Ddz5mvy/im85hPrvuZu0o9mfNQQ+/ZN/05ZK70eGp6OIt+Ej00UN/v6oJPTqAOqILOngy1/7D/rDh1IYx6BO8pg+X4TdEnu+9CBtfgg7X7UPfcwjnIujBe/ilB6G5hbqd/NRaTeyiP2ThW8VT7Bt/mhHk0+Tg/oOw8b/Drz196cGS69tx+Kl++ETk0Yyd/I0ac/RYYjg+44/oo2Ce79G5ucRK+CqIv97Z9AAt4vy10LkfOvA1+6OP4rHrtw3kYn/nOafvsNeTsAtqvyridGwkPeDXofcOdMz2I+S/iU3I4Tb0ow9yokfCuQa9hNHUfOhsEl+Qhi+34ovIDb1rkCE+xI9fjgv0pwz7KEZPt0P3TuTYatF7Q7/Ri3gZ+4RXCWqTNHrkQ98y5IT+d9g7/Suf7avmo3tvg1M8kl4uOujHdiqK0An0bTm/48kH7XOmU4lV9Jl8g6DvmX7EUORy3TB67ugGtpvujQ+9nnwT20hOpLalNxwnB03txOcfznpB7PL+Yt57Tj+cPlRyCb6qP3Ganop1koU9l+DXBovEUdh3DBmTU1mfo9vErSjPCvGlK5FGplXPsg9PH75jSh+mCX90EWdHO+DrKvCHMN9d6P80+LWd2If+ZP6E/O7ugf8HVoQvup486i1qsHXEwQw5UQVyQn4x9Dz+Bz5vhOfk8/HB8J8+fqoL98C30PSRnEcSe1rJHf7D/vl3ShPnIQN6a6GPB9GDK8bvMccmrqWpmaLM+QkymdcPf48enU3OXEyedi7PlpI/eg+GrxPY9yHw5XD85Qpoeh7d2YRerOHaG+PwdfhH4Bno9nO/8NvvXezKueYw6iRiVSWxAZ7Fr4du/v38xBR8MDWZ2IEfQ0/j/Lv3grlCi9AX5vZTL1Q1o7cz8UvXYlPXIJsRHnJ6etfQmOmDHzkBfjXxeybxDT2qYv30D/2wVWLvJPJAejHew9G5fanFd2IH9GrS0OaZhT0fh40t8fAedXTwTWT5CDl7awk9nR48I11C7o5PIp/1nTqeepc66ADqp03kFL+3z+npnbVij8xr/R2f9yx5Lj0agX55yR9D55IH+7ClG4q5j5xsK74R+wldgC+xn9NDJunB7LUfPWT0RNTg+5Bp5nXypZc4665n7m7kQr8lz4A=
*/