// (C) Copyright 2008 CodeRage, LLC (turkanis at coderage dot com)
// (C) Copyright 2003-2007 Jonathan Turkanis
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

#ifndef BOOST_IOSTREAMS_DETAIL_VALUE_TYPE_HPP_INCLUDED
#define BOOST_IOSTREAMS_DETAIL_VALUE_TYPE_HPP_INCLUDED

#if defined(_MSC_VER)
# pragma once
#endif              

#include <boost/iostreams/traits.hpp>
#include <boost/mpl/if.hpp>

namespace boost { namespace iostreams { namespace detail {

template<typename T>
struct param_type {
    typedef typename mpl::if_<is_std_io<T>, T&, const T&>::type type;
};

template<typename T>
struct value_type {
    typedef typename mpl::if_<is_std_io<T>, T&, T>::type type;
};

} } } // End namespaces detail, iostreams, boost.

#endif // #ifndef BOOST_IOSTREAMS_DETAIL_VALUE_TYPE_HPP_INCLUDED //-----------//

/* call_traits.hpp
/KfwOJwXHm4tDve6NmXuupvrsVq8mdwPB1V5tU48bo1kn0xN9qqwjtF3Ta2vEsItL5tVL5H7cMBq29+VEegQdwPr9+DHMIN0zibM5/BbZCHpvJp0RpK+RNK3Gt5Jepv5I6xNSK+wCOvFsGhrVHiY9VF4tNwPHqtIpaNTUnMrKgmbMGoMeaqqr77e2vw+zG/Hz4E68z3Od/euUfnJ4LdT32lpqWJXpvhHDhWmTWKpPmS4z+DZG+xzfrdsVt9m/45RYU9o19Pj7iRxrw9xHmvB6vxa7Xzptftak0QXz19jn3s91s/u/BvZEXeap8B6AOmKPj7rjfC/HL7SuiiiwPorMjdyqfVjZIG1MqrAqotO3oO0QycfRwbGFFivx6yxZtQ8y3N/bG3r+VivlS16+J3Kz/bwxtRTR+6uh6iz7eS3B/U0CN3aCV+j7kZ4o6xLqLMPqLu/wZnU2Xzq7hvoRaeuQrcK0bE4dKoBOnUbvA82R7c6oVuOjbsz7lHfIFFf4zuFf1dIue5U5fBB4iCrJnsuh1mduF5/rhPv72IN9cdaE7nG9+hEHHGtJM6bkXoR4VZztO33cDPsEBlunRXpt56EL7Hx49yocGtsFOvMoyKsaTUirL8ji6KjrZiYaGttTJT1Sow38tWEKOtAAmET27h9iHtUmYx17YX+SenPAkqF9FA+tq69rNXdpdbxBLs+D+L2qbqv74zgt/qO2aHr7N+FvtL67e+2NW9eb59rRrseZSWorxdH+1J9BdZ2ZBDtzBtIOm3NYSQ/3OtfQp3GU5/rkBbU6RakD23Ny0gabc1BJDduqfVt3EqrgPammdTxMyoNa+s492Ud71xruO+huK649EEc3d6k8p1nZUs57FN5+SjOy5OpMTp/OrrQAV14GD4Jz0IXzqWOdsO34AXowiR04kP4BcxCJ/LRiZP+MGsl93Td8AjrHu7ndhHR1pMROyIWxUVZhcR+hZTzhaqdWxIZRRoLSOsaSjyBazVCD9fDB7hmG67VlWttg8/C/lxrJNcqhn+B47nmdK55CH4NZ6OHv0EPLfSlJrpzcXikZ2pElLUAfXmfdByN8Evf2GlfItS9uY26+1LVz2hvrLQtNyo9mO+x6/+IVv9PWEsSSut3stvvf0yVZ7iK75jm39SHyFXXirYaSti3ld/ZvihsO6bSLzgP6w6fkfPGch/tUef3hUWhO2dQN72sU7iXHvWs9R7zOv2OjYX4YUfvMOt9j/N9x/eULnj9I8nXD95tro4PVH7/4RvGjvVBvkuUjq/T0vyIr69Xb8O6SBu3MUQb103Or9bOB/eP7pC8j1BpGh7WgXwMRtKR25BNyG7E74mx6iMdkOnIIuRmZA/yMXISSfFG8xSIZz9zLM+XVuwnjbFeQj71drZ6+2KsMUi+r4e119fYivLHW639MdZQZDLyG+Rh3F6GB5B6YTFWe8TpXz5ipx/ftxCDnseumm2mUetK6/q+UO1+e0udfy7U+Y4l57eEOp9acn6XUZcGWJdIeX6snsMnavq5iwqRBjwz7vMsZa/aSmsHz46hvlt9h8NnWGkRtBlILs+Nk0gBz44E2pj1NZZaLaNXWttoZ/rTxhQj42uutSaJbg5S7cKcyFjq5nbuyz94vOxjo8/B/bgVPgP7cj+ex/34InwdXsj9OIX78WN4FC4IC7N8PN+vQ+pzH96LdIoMs9qKfqcpnXiJlrkm+wb9aPYF7NlL5hp8W8A3sNZwWtxJnL1C9DpJlf/vIk+3vMThD3iOnSPPsWLSOYr0jZfn2CF5juWTvmPQ8kdV+Bx7FhbD1hEfWcmRXvf+6aueaxnquZbIv87zoIu6rzYH6E1nbWzg76qNiFL+NxjrdZI=
*/