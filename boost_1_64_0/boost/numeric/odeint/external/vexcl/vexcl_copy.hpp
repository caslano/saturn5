/*
 [auto_generated]
 boost/numeric/odeint/external/vexcl/vexcl_copy.hpp

 [begin_description]
 copy_impl specializations for vexcl
 [end_description]

 Copyright 2009-2011 Karsten Ahnert
 Copyright 2009-2011 Mario Mulansky

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */


#ifndef BOOST_NUMERIC_ODEINT_EXTERNAL_VEXCL_VEXCL_COPY_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_EXTERNAL_VEXCL_VEXCL_COPY_HPP_INCLUDED

#include <vexcl/vector.hpp>
#include <vexcl/multivector.hpp>

#include <boost/numeric/odeint/util/copy.hpp>

namespace boost {
namespace numeric {
namespace odeint {

template< typename T1, typename T2 >
struct copy_impl< vex::vector<T1>, vex::vector<T2> >
{
    static void copy( const vex::vector<T1> &from , vex::vector<T2> &to )
    {
        to = from;
    }
};

template< typename T1, typename T2, size_t N >
struct copy_impl< vex::multivector<T1, N>, vex::multivector<T2, N> >
{
    static void copy( const vex::multivector<T1, N> &from , vex::multivector<T2, N> &to )
    {
        to = from;
    }
};


} // namespace odeint
} // namespace numeric
} // namespace boost



#endif // BOOST_NUMERIC_ODEINT_EXTERNAL_VEXCL_VEXCL_COPY_HPP_INCLUDED

/* vexcl_copy.hpp
8a5+t6/m5nWFXjyd7utshWzZtyQratVcZxjt7tjQW5JbDpr+Mff40psmzt19kLjetnQi7Uk41Z7qZLo8ethviHqoyqOH/ZUeMvuXlarMhUOyKdemUb/htl8FPqShnsO0GtB0eFNJOHxusZzdTUu7VvvbNr9RXp1qN/9V8/6mzDtczLOqTPVN6B+/WiH941Rnw1zL1oZwsG/BTVe4GYJz4UOKw+G1JnyOCae9cHieyBuUh2W168TZtaKju8tFRz69gXsO9nzznNrQnT7gBtYt6i3YxUY66WMFw/U5cQXe3FqZl0B/xAaYoP3DjhHfQHsM0rXDKZ16q9+dE9TnBjux7yrrj6aoNrmscX5sQWNLo26UOppjceR4PkwezjcE63/OAG8CN9cGZw3b1PvM6GP60x1B3zaN5VloypNvjKvSeRkdFVBHGT/Ui0JteGVT88rGVZiVkKuElb8GjDPR/sAWS927s2PpAv7MPsFS4CLPvOTNX8ak5bXGH/+EaFlWKvsan0feVbWD+pHz1fpRJ0o4Klu/LWa+MsO01SOkbTo5dsNP7xmsEbpLi3TSV4F+NPGH14b9drWoPuYYI8OxRoaYysPn8yWzxx03dLuv2CZ08DZ7/qAn8tZnB4zaf2AuU58qDA1yH432JH2Lfbu1g/3qSFXmDSxzhkdfOWoNvz7+Nmo9g0eXjDGkiX56pH+0suBfuceh+8ckcFp+jbf3WvqULWr+2hbT0t+Cbu+TCH97d2Vzbfgs0nFYC/BeiinHYLx297Zybn1CrT5XFl0/n0ac/jZzItOuZ1pbt6eXBu9If7k0rJvPKj3C5plPgL/B7Kd+TrBoKwNjP6/rZxDsF0CXuzzD09kX9ZwdtrT73qI3d352jOT9erG5EwG9nV5LPM/jajww6t3pAH+G2An4G1sxd/VlTVPoncn6GW/WJWchvLY43OecLTI5+mGUmz/kqfCQ6VzyPtzU/XkIIz+TTvT+dd3vEKfXP9/Ev9NA30P50IQsfPfP1o9JD4nOr9XjBMth91KBUboAzuylSr+BsoTXohczjHj7LRHYXF7fVbwON7wuZ3jtfjLHs2Oclf1Kg4naK77aYKL2zq8188n6/dV6l2tu4jmfVPvFfMuO5cJazux/Moz4nD3LZoO9iWHEEyt2ZtOONmlvkXZoz7pgXa33vYhBuW+j3ZaZOcUdBl9G/J3ENxv83QbfTPw9xEP+EP5egwfd4X8mtojy5e4z3a/oZRH0nyt6cwT9l4qOPHPoD4qtYF0UPSffAYw+S/O6jFGqLAXew6Yshxsb+g3CnEOwLQ2+jhuv02AMflzNjTiOsz1Gfr8lT2JYR0+zjpbsn/uO4m9BQxnljTbgnzXj7Tj1xhzrlHjujdbqMGQUuwRe7urqPF5kGtB4b1fS3MK7af3mbtrLqu7eyIN5RY2JlXIOKtKnyZ8UlnLiZ3USYF+lTpLqPLRJS3ly53avi36CMwCVHHskLdOZtQTnHX+VcsOeo/v4vxHDeo3E/EPKq/iwvEbmdwRLfvmx/0Kcre9HqsJ5v6vGhZfMGaT/mPLdknMPFP+fqDHBvT2L2QUY2ikwEef1DI83IvIZOVG9Xc/5nC7zWp7PKBQc9JMft4fgAr8qrGf7/Xe0yO5w7ebtpr1EduFj6rdoYtDOnykP2rkuRwloSj5ggnzHmPKeXmrtP8CNNeXNx6+MMkzjuR1Jk593+UT2i5QB8diLkX5R0sjapELSgPfQ0uxnynp2heD0vk2l1YngZJwArsroJB+/GoPLx682jx6SA5SpLjcNsAOnmRzS3dDyqQ+lGVo+0yZyzWHS4DdIfrt70yUtyjW8tA20wZvKwmu8mYgv5rm7v6ixT68=
*/