#ifndef BOOST_BIND_APPLY_HPP_INCLUDED
#define BOOST_BIND_APPLY_HPP_INCLUDED

//
//  apply.hpp
//
//  Copyright (c) 2002, 2003 Peter Dimov and Multi Media Ltd.
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//

namespace boost
{

template<class R> struct apply
{
    typedef R result_type;

    template<class F> result_type operator()(F & f) const
    {
        return f();
    }

    template<class F, class A1> result_type operator()(F & f, A1 & a1) const
    {
        return f(a1);
    }

    template<class F, class A1, class A2> result_type operator()(F & f, A1 & a1, A2 & a2) const
    {
        return f(a1, a2);
    }

    template<class F, class A1, class A2, class A3> result_type operator()(F & f, A1 & a1, A2 & a2, A3 & a3) const
    {
        return f(a1, a2, a3);
    }

    template<class F, class A1, class A2, class A3, class A4> result_type operator()(F & f, A1 & a1, A2 & a2, A3 & a3, A4 & a4) const
    {
        return f(a1, a2, a3, a4);
    }

    template<class F, class A1, class A2, class A3, class A4, class A5> result_type operator()(F & f, A1 & a1, A2 & a2, A3 & a3, A4 & a4, A5 & a5) const
    {
        return f(a1, a2, a3, a4, a5);
    }

    template<class F, class A1, class A2, class A3, class A4, class A5, class A6> result_type operator()(F & f, A1 & a1, A2 & a2, A3 & a3, A4 & a4, A5 & a5, A6 & a6) const
    {
        return f(a1, a2, a3, a4, a5, a6);
    }

    template<class F, class A1, class A2, class A3, class A4, class A5, class A6, class A7> result_type operator()(F & f, A1 & a1, A2 & a2, A3 & a3, A4 & a4, A5 & a5, A6 & a6, A7 & a7) const
    {
        return f(a1, a2, a3, a4, a5, a6, a7);
    }

    template<class F, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8> result_type operator()(F & f, A1 & a1, A2 & a2, A3 & a3, A4 & a4, A5 & a5, A6 & a6, A7 & a7, A8 & a8) const
    {
        return f(a1, a2, a3, a4, a5, a6, a7, a8);
    }

    template<class F, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9> result_type operator()(F & f, A1 & a1, A2 & a2, A3 & a3, A4 & a4, A5 & a5, A6 & a6, A7 & a7, A8 & a8, A9 & a9) const
    {
        return f(a1, a2, a3, a4, a5, a6, a7, a8, a9);
    }
};

} // namespace boost

#endif // #ifndef BOOST_BIND_APPLY_HPP_INCLUDED

/* apply.hpp
pTyRq5hZUTbP8Zaf5fEOnvon1Fa0264Yj/f9jFz4vaThOjkaSbq4dj3v6x0efB+ju+41oQGNxryC/+Q4z7RGvFHkeY/TMMZQ8xpHvT+k+kaNTKpZ32F1T9zSvd8pCvnzfKdIz+u7VvXnWYIzz36hd4CC+4avPsSS3zZ91vsU3I6H6qj85a4SfMgrmevZT6nfvua57c1ivysm6rmw9j03yPnVMZK/xn/vyPukGatfJ+ebxTxqzWWPnWrN86C/XkanbMcE297f5V2Q4LmB0c95td+8Q+MU8f6LWQu+U86vlPNNJSdn2A999Nr0M/H2+bkmLllyvSGW47lwqb0gmKo6WEtF/iXfqdYUX+iZtK6bI1MQLaPrgpSFLaPXbdPIlqmmX2hn7r154tbb1856wfP6nwfi67uOHt31vSQtW5+ElWrP26TdesXVGV5EXE0erZawZrrGM1Xj6YxDeiCuKpeI3FHswRJHCCdQ983zcDGV+px7mj4Ln6CGZyZiz0K2SGVPxq0EBt1yNRzc5J2ddOwjMvb9GTl1LOIZefT44VmXddiN4WOKyGfklFvUs3TN+2g5WVP3eFco0n+68e+UDd8Pfne+7gGlY+TlmGfs9+Mam/7CPI/nJfqprPh6vQ+ifjqb+fkYsddIey2QPlP1bxvZDqZ9jhT7ea5r58MDcYl8z8u0kSPk/EJZ9dN7tuPdsb3qQD88+AxtEeGYZ2ge6+rNdIxIPHCrDcvL0X1C+rgyMIX6vMpq4szLIlQ2lHMnkzVhXTePfn6Jn7C1zTZiH02f3sSxTzoPVELPqtRPBzOf6CD2Q9Hy1Nzhp2Se9i/SxrJEZixv6sdJOOXm2lku6+QNf0+TNHnsu06cQ3mrbsQpol4uPdQ9L+vC8zIwkNxLXtZF5OUfGpCXdRF5eWMD8vK66LzUcLIinlH8e/JymOZlX/044kQf11S+Z184MVz3YBWq9UtOLRsteWp5jgfUX47JzxyxD+XOHOPaN0w0fjqZuXAnsQ/wbbKSwuasaJQ27foSkXmRcIerG7EVt0ruh/1d59Cny/kPrbOtlHrX4o8TuVhfcC3+ZtaJ0k3/EpYTZm6Sk2T7OcTMa16WMNJkLX7ZoeR/P51TM5f25yce05C1+JMIw7kWv6evxf4nOufphO/sZHvO09lzHq3XvrlfcB49OykusZ61eJV/tl9wLb6uLmpdD3s89mmcXyj9Z+h9tAn7rB/UObcO9aVROjK0jk7W52ETMQ9mE8ckU0dD04BS7/fCNon8MKuvWUfXMJAI5WFD7wn16/ScNFDn1Jimujfxc8Q5v6mJc01pUUnNnN58RjKv0uu+qfJ9zbrco2I3fZOk0dE3qXxvtRt5Vx1np8q5QquzrKPjZuTjgu+s8RPlh0Zf7Qg5n6v2UPiaf+TdXnWi7vW5dKCvCqZrUEqpXIO9+NqH3wfuGazzRE5mwL5wB3m8PSyPedxiv7daUzF3jmlrks9h7/wmNpO+2Kf5rmG0icq3VnZ5imySL976Ufzb124hbutUBg3ZYj/ROkzXxTKMW7G4eT0L6C4yI+T8GwFdi2HnL5bzbTzX8v4h5wdIf1FIAawYpGvMse1kzeNIrzUPlV8/SNd3E/OtqLavMruRWS1h1tVJoJ3Ne2We4balrG7PcF9LCcZ10mDtpxrXvZoUO5pA6w+zGvl1gTA/8Fjvoz03/Hn8UYF5d2nk92GxuhnqBbq2dzbma2SXNg/VM57pRS1OeKy/SH37s/g91crnOuMxWu80zMzI9RjxN9Gcr7b6IzMtbLwhU1Lzbv0tIjeXWS8tXPu7cuM/PTDm0Pb6OR6+2Ie+O3J9Ynz4mo64FZp2LPEKa7cJqvPuDe3PX9E=
*/