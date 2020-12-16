/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   attributes.hpp
 * \author Andrey Semashev
 * \date   13.07.2009
 *
 * This header includes other Boost.Log headers with all attributes.
 */

#ifndef BOOST_LOG_ATTRIBUTES_HPP_INCLUDED_
#define BOOST_LOG_ATTRIBUTES_HPP_INCLUDED_

#include <boost/log/detail/config.hpp>

#include <boost/log/attributes/attribute.hpp>
#include <boost/log/attributes/clock.hpp>
#include <boost/log/attributes/constant.hpp>
#include <boost/log/attributes/counter.hpp>
#include <boost/log/attributes/function.hpp>
#include <boost/log/attributes/mutable_constant.hpp>
#include <boost/log/attributes/named_scope.hpp>
#include <boost/log/attributes/timer.hpp>
#include <boost/log/attributes/current_process_name.hpp>
#include <boost/log/attributes/current_process_id.hpp>
#if !defined(BOOST_LOG_NO_THREADS)
#include <boost/log/attributes/current_thread_id.hpp>
#endif

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

#endif // BOOST_LOG_ATTRIBUTES_HPP_INCLUDED_

/* attributes.hpp
nh8Ivy/gLLdk535jzrVynDIueZDslHOdruCx0MQONWW51B7fLq9RzuaxUJhtJuGZ9oozlSl+T12unXuvOft+Ozr6AyiTPnwppjydMjOkV16du9On+7iXqWsKrSn8zzPLM+HqepK9NEPWu/gz7nmn5/UqlXuG1Y/UTMKYZFnCkHG1zGWG0Z8OWYfqfTFLtHw596pz5mtFJxUe6azmUnvuaUUgXyecN0uNUPOWO9+R3KD61IvymFQ25R/Xu+vDglxzX1P71e3HzKbhtx92PJIkHsF1I/dzpfVA55ppXW6PBYPSWlYjrWkta09rmzqk1enXF6Xa6dL5xvct+HXly6w65Atxri1ftFwQB+yIg6sdyepS891FXDrh6ryadN60sVNGKdHIL8hbnJtZvqIkzzVGNeYXYZy0nmDsbB4fOsfOE7v5PS/DRGOWYu7F77AVwXvmZefmGt9TkJ3WKOV3odWaFE7GmOJLeO41PLUuTolyG8XIy2csb32tbhez9RpJK5VbK0PZm67L0WtVbFRuDU1tGteF32/Dr7Peof0z990SwhrrBq0DpPtuxN3Zd+O89r5bhYoT31C6xv4tZKB8joz9+2IqCOtocFk7dBANOgJS/7+jrkkzv5NyPXMmvb8ok5y69wQkLV+tMOv5Hejuv3ihBFKAeYhr01a60lJYYpBbeceu/M4lbuznaB47EF4N2dNym6ncBlhnWgZdHOO1OXp9kgLl1sAkt1xnlD+TrOI3PPkLZ81iJX8ueUtwyVuiQd7KVRx4Fl16Vcd6WOrIkbol274fYR10l5HoVYmsab2qlIAenPI/S9UvIzFTze9mCNe9ty86SA7dvQ+Uey+1B6vxfUWYeRmqr0rc3bpQ5F2wLtSZq/x5tcolz1f38ge4QAKej/kx1w7DvzOvcnMWh5TnUcrvHDUOHm6WZ8ILXQ8XKbf+oeSZaw31sJTR8lUh5ZnrwpfnYavCK4O6yHOI+jSkPG+QMlrtKqNjsrDNTLnxDMxaey7CXUbc25FHpnKQazzusjTlu/br0NvV47MvlFsvRngddJk6ddr+pNyHW+eKXlhFL/Izza8XVq+er6dBL0zpcvnzX8ZyYezzqnTfXHkba3iXG7ta6nNXXbFPXuT1kLapu7RNw/DvyFtplUK3S+cp/51NeS5heRxp/fbt0lSdjuA9iF/u7b84XwLJw1Ry7brgdKgu3/iS0uKFefPKC5bmuTchDvmMb1wdaLNYX97c1+Jexj3OtUz8ULn3pz71GOVNrtd6BsY9h43+VhieaZO/laa+FP7C38983erw6olw5hgM+5i79BeWu/QXVqjzZvp8Zci9y98QObkkPfjdw6G+Nev7O7i/taamnGTns+J03sn3LQ/ISJQKI1O9yx5rlhHuU7uMpCn3flY7s4xwfXgyYq0JT0asNeH3ua01/96yD9XvzlbxIi6ust7XT/eD1JEtZV0RblmXWCHL+noVxqxa64OKk5T1Q8q9T8j6oCLMsq4Is6wr6lDW/2TvTOCrKM4Avi8JISEBwxXuEO4AAUICcsgRuW9CEiBcJgECRK4AAUFQoaDS1mq0WFHRgqLFs1RBqVKNN1pUVFS0HqlXsahNERWP2v533vcm+zaz4UXRXnn8Pv7ZnW/u2ZnZnavkPzSvj+m8Dm7H4vpZ6pcngclF9vTk/oVBeS2HG3jnayOlP7WqZxg33X25fJ2n6cqsh9fzi93Q56zEXXj68iC4T5bvuXajUPnJOgzX+EN6f0v9puj91VjjZT9LrvR17dXv/fwoe+Orfn4uPMXzo8yTvJ+f05h+5jJMOyPp9RPXO/+dZ+lzudVvGvIAdq2LKqXX0iX+ERvvdkXZmVRVWuFu1Wk=
*/