// Copyright (c) 2016 Klemens D. Morgenstern
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)


#ifndef BOOST_PROCESS_WINDOWS_CMD_HPP_
#define BOOST_PROCESS_WINDOWS_CMD_HPP_

#include <string>

namespace boost
{
namespace process
{
namespace detail
{
namespace windows
{

template<typename CharType>
struct cmd_setter_ : ::boost::process::detail::handler_base
{
    typedef CharType value_type;
    typedef std::basic_string<value_type> string_type;

    cmd_setter_(string_type && cmd_line)      : _cmd_line(std::move(cmd_line)) {}
    cmd_setter_(const string_type & cmd_line) : _cmd_line(cmd_line) {}
    template <class Executor>
    void on_setup(Executor& exec)
    {
        exec.cmd_line = _cmd_line.c_str();
    }
    const string_type & str() const {return _cmd_line;}

private:
    string_type _cmd_line;
};

}


}
}
}



#endif /* INCLUDE_BOOST_PROCESS_WINDOWS_ARGS_HPP_ */

/* cmd.hpp
D7fCAXAbHARfhIPh63AI3Aez4cdwKDwEh8Fv4XD4MxwBY2pQX8F0eCGsDUfCBnAUbAIvgt3gH+EAmAOHwWpwPMyEk2BNOA3WggtgbbgK+uDd8A9wM6wD34BnwH2wLvwC1oPfwvowoibtE4yBDWAteBZsCBvBVrAxzIJnw36wCRwNW8CJsB1cBJvCTTAnOB4VnCuk5jaVqbkNc4zA389qfMuM4P5CF8yAcbAGdMOm0APPgxGwp5KPgLHwj0o/B0bCYhgF50IvXKjsj8JiPReGOljFJxYzTsXnCuIjdlDOroQ+uAw2hVfD1nA57AWvgUPhtTBP6U1V7q+CK1U+vKnnXVCnqXCrYp6TUCF6CXAnTIQvwmT4EqwOX4a14auwOXwNngdfhwPhGzAbvgVHwl0wB+6Bk+E7cAp8G5ao61Ll33K4H66GH8N18AN4FyyHf4Ifwq3wI7hN6R2FM4Pfx+FAla44TIFK10GVn1/CKvAQTIFfqXT9FdaFR2ADeAK2gt+r9P0A28JvYHt4DA5Q8qMw0VTfg9W35jJYGxOcg74GvTh4i7qfG9R9vFXdx42wC7wNXgBvhxfBO+A0eCecAe+Ci+AmeB28G66B98Et8H74HHwAvgY3w3fhg/Az+BD8AT4MTeK2BSbBR2ANuBXWg4/CtvAxeD58HA6BT8IJcBucAZ+CC+AOuAxugBvg0ypfSoPf42Chui/xmBJ1X8ag52ce9MLxMB4Wqvs0QZW3ibCukp8JL4ad4CTYX12PggWq/E+Gk5X+tghDzogJfz4M/rPL50LMBkwZphxzApMY6TEaY7Iw4zBzMGsxWzBvYg5hPDRqGZg2mBGYYsxizAbMY5g3o9DDeL0eoy6mPSYbU4ApxazDPIbZ40UPU0Z8Uonfyunuf8m5NN5oz//s2TRtoskzN26iPb97Rs2yaM+/9JyaxAtO7ayaLdGef/i8mt87q2Z/tOd3z6uhsxX2zJqmMZ5/y7k12TGe/6mza078nefXFMR4KnWGzboYz991js2ruLOfZXMsxvNffZ7NBnWmTbntXJu6sdSJmGzMTMw6zDZMOcYT5zFO/53+O/13+u/03+m/03+n/07/nf77b/7zYMb/y87/kyWk/5QzAP3ni3XCbeg5f8js5/xpmXXOnyVzi2zIkL4tLJlHZNl9hzRjnF3JIrQsB6klj7TkzQ1bWFEiHzikD7IEJYsW2TDcerl2Pv9opH+vC3W2z8RouR3yjlNP8Tg25ctkup7KScfzffQ887ir/bL2+rwfcYtPV7tt5/0oudN5P8EzJlziz3mmhwk1aWaEXhv29nLkaj9Obxj/ldxaN5kZ2PPbPqf+3GuwZ8TThV+Zai57goSZ4/6RFRNnulzMdbHOFCmWuZ4tbXv8T84vzJlOfrDLZnC//J9++aWt+HGxu4XbLWEXVvPryrJSvS+sR3Ty3RGuKkaZa6OSkwqJUzm7v/VjP78Y3LNfKH72kzT7XE7nd1SFVcV+GLHdwfzMB4w7zPvs++JLwmV/RfxqLmFPcbdz/+rME72OOEt05riuNzswD2m83s/wLxLOS+zUPIAx+A7sH+pl/udq4zpT9j5Wz0GRzuN+4s+9lMNVyGxnTIwpmhrc97+cONUXvbnunsTJaW1xV8mXemaJEWFL19QpxcqPI/jRSvwodLdW6Zos+U79oHROoJMsOte5R6Jj3cdpU/Nypk4rLi6aUpI3TnQPoNtEdKe7O6o4dU2UfNLlPE/i1AF/bHlDjqi8kTj0lHI3Ztr44Bon/LWVn9yZIeVnP/bnS7jj3eeodCytJrp5JRO5P6o81BGd+e5G5lXGd+YI256cwyrk7TF0zxLdS91d3fa9ZtWjbFjPW6Q=
*/