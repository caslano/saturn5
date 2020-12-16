//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_REPLACE_HPP
#define BOOST_COMPUTE_ALGORITHM_REPLACE_HPP

#include <boost/static_assert.hpp>

#include <boost/compute/system.hpp>
#include <boost/compute/command_queue.hpp>
#include <boost/compute/detail/meta_kernel.hpp>
#include <boost/compute/detail/iterator_range_size.hpp>
#include <boost/compute/type_traits/is_device_iterator.hpp>

namespace boost {
namespace compute {
namespace detail {

template<class Iterator, class T>
class replace_kernel : public meta_kernel
{
public:
    replace_kernel()
        : meta_kernel("replace")
    {
        m_count = 0;
    }

    void set_range(Iterator first, Iterator last)
    {
        m_count = detail::iterator_range_size(first, last);

        *this <<
            "const uint i = get_global_id(0);\n" <<
            "if(" << first[var<cl_uint>("i")] << " == " << var<T>("old_value") << ")\n" <<
            "    " << first[var<cl_uint>("i")] << '=' << var<T>("new_value") << ";\n";
    }

    void set_old_value(const T &old_value)
    {
        add_set_arg<T>("old_value", old_value);
    }

    void set_new_value(const T &new_value)
    {
        add_set_arg<T>("new_value", new_value);
    }

    void exec(command_queue &queue)
    {
        if(m_count == 0){
            // nothing to do
            return;
        }

        exec_1d(queue, 0, m_count);
    }

private:
    size_t m_count;
};

} // end detail namespace

/// Replaces each instance of \p old_value in the range [\p first,
/// \p last) with \p new_value.
///
/// Space complexity: \Omega(1)
template<class Iterator, class T>
inline void replace(Iterator first,
                    Iterator last,
                    const T &old_value,
                    const T &new_value,
                    command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<Iterator>::value);
    detail::replace_kernel<Iterator, T> kernel;

    kernel.set_range(first, last);
    kernel.set_old_value(old_value);
    kernel.set_new_value(new_value);

    kernel.exec(queue);
}

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_REPLACE_HPP

/* replace.hpp
SBc+Ad+CT8Nz4HNqXw7PgivUPt9/PzLXmYM5GlOMmY65GnMXphqzErMeE1hvvGj/aGsZzAlZRxzbo4GsJR6h64U76rpgXf+rc6zO9bt9zHpc3MLW2/5MfklbyROTt9Wbi/XEE0888cQTTzzxxBNPPPHEk78qO2r+f3ud/xcfov/vQZ8O8Or6/76YBPyrvzHzgPl1Pf9P4pCC+3yg8Y+sqygYJuL5f+q/zfP/CFPn8/9Cw0510Qdk9MaFha0IOSsw4R9+VqDfrcJlH0OPQB+Idu8DKd86+oDpAe7tr+Ejtz/+tbc/YSK3v/jX3v4p39a9/VO+rXv7E9a1/Zv/29t/J/f2r3C0f1at7V9RS/tX1KH9K2pp/4o6tH9FPdq/oh7tXxGh/Vv8S9s/cH7oRpkr637dq7Oq0q5LvOXgg5ZveHXeFj0bxTz3KIjL2SiJum8oCfaFyZB4em9Fjpei8dpovLYmHn9sI15HjZeu8faESWHnlU5jvLsSU+2Ne3viiSeeeOKJJ3+T7Kjv/7H52+f7v1HI/v+J+v3fT9/9u2Oa4F8c/P4n39rXAkt4UnF/93f6m3d/895v/CO+9xv/yO/9hAm+nx+3jXf5jLCwvFerXgEYR/n1fT6rlvf5bJf3+RyXtaW5oe/z6pbn8i5/nMu7/PhtvLe3udn/3n54u8MGrTk5e2nz8rw2r1wwxVfz3p5nyihta854PDjs3P+msBlMgCkwCbZTezpMhN3VvZfa48Let9d679meeOKJJ5544oknnnjiye/snQtwE0UYx7ehaBFGG3QKImJFRcBS+wIRBSkJSKWW2lZatJqmybUNTXLx7lpaRIWKb1TUquALFHXqG7UqPtCOdBTfih1FBxUVX4hSmYo4g+j/NntpEhqxelHU7zd8XG9vd/+7e5fCt5v97n9CImyg8P9Li7Mc2Vnpbq8Xe6Xhp+/P98UYHNijn56fVzADF+FzWngdNSL3loUp3ENlquyqlTTd9zNFZ7jQ6RC5O0M6NXWaW54LH9V0rckJjLM5pCVperfkgHn9MsavJUHkbgpp+d2abLpOspg72bUwTCcOYzdf6CQZ/VEkV32VIvtM1DL6tFlo7VgYphUHnfw+jLPI0PFrco1qvk6r0PnY0PF6VE3ym6YzQugcLb5DcZuh45Fdmld8cE0cP+OZWCL0Wgy9avM/T0bf8Kojzl1RWn6nTzKzb4ZeQOjdFKana3n8VXI89DYJvYfD9GpkVats1FXN1ysU37e4MkzP6XYr8epfm9BbYuhVKZJkCJqoZzybaSK2xAZDDxFb/JLL1M+B0bfbhNb6kJZXViXzP3fG75NEsUH6daGHrdqm/s43dLxC5yVDx+lySSZ+to17tUHotAodVJpbrDkVrS5gmtZo43e+iKNgaQrTkrR8p6pNVRRZMfN+GZpt0OTHsP6dGifN0PN/AOM8E6Zpw8qOX4wpQRAE8d8glv8/mqVE/PtxIMx3Tg//duwD5QmCIAiCIAiCIAiC2Lv/nyL871z7rNzCPMMD7/0csrGuoYncqcZceZEUkBVtar3k10qDc9amaaYLzU6Re0i3ZrW+Wqpw1WK+pSFe2kasykMMbbuk7KlurnZo/U9o1xjaNn2vQ7Gn2j/dqdaUmqpprEuUGfsuIjUlTZcsdCpOn7l9Nca5Q+imRegWBTee2GS/JjVozOR7PDpqzf+0CG2sxpwZDCUcL912oWuP1i1U5Po4jLXxXI0Xa/RZUbr+IqffLfviovmg0CyM0JzaoP/ywBCbqmk8UyPF+rk/UhObz/UB9rglRS2N171dIbTHR2jbJVVT5MY4PlODxTJeZU+6+mfYZF3j/i4WurOidF36wWRNo6+JYo0=
*/