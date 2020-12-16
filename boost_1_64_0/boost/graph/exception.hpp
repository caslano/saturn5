//=======================================================================
// Copyright 2002 Indiana University.
// Authors: Andrew Lumsdaine, Lie-Quan Lee, Jeremy G. Siek
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//=======================================================================

#ifndef BOOST_GRAPH_EXCEPTION_HPP
#define BOOST_GRAPH_EXCEPTION_HPP

#include <stdexcept>
#include <string>

namespace boost
{

struct BOOST_SYMBOL_VISIBLE bad_graph : public std::invalid_argument
{
    bad_graph(const std::string& what_arg) : std::invalid_argument(what_arg) {}
};

struct BOOST_SYMBOL_VISIBLE not_a_dag : public bad_graph
{
    not_a_dag() : bad_graph("The graph must be a DAG.") {}
};

struct BOOST_SYMBOL_VISIBLE negative_edge : public bad_graph
{
    negative_edge()
    : bad_graph("The graph may not contain an edge with negative weight.")
    {
    }
};

struct BOOST_SYMBOL_VISIBLE negative_cycle : public bad_graph
{
    negative_cycle() : bad_graph("The graph may not contain negative cycles.")
    {
    }
};

struct BOOST_SYMBOL_VISIBLE not_connected : public bad_graph
{
    not_connected() : bad_graph("The graph must be connected.") {}
};

struct BOOST_SYMBOL_VISIBLE not_complete : public bad_graph
{
    not_complete() : bad_graph("The graph must be complete.") {}
};

} // namespace boost

#endif // BOOST_GRAPH_EXCEPTION_HPP

/* exception.hpp
vgK8DbnQ6+fAvcjj4fvA4fXrwXs+WL/+YP36/2/9Wqn31/+/V/edvwrZN+B+pLFvwOph277JAOcik+FLwHXI8fDt4E5kCnwPeACZCj/08N6lh3HzAP1wpdIyUjVepK8/v4Lx0EalZe86S2/mR4Z/qLTsrLX1E/G/5McKf2x9xNPvVloOnmPrM9BnPq+0LGm19Yejb3+R8G+29dnoe/+qXHdbbH2OF/9/Ki0zt1p6sy4zmDhOy/7zbP0inu+fMI56betzPf0UV995oa2/62b6kwNcfUm7pTfj7MgcVz98ka0v8sL/IVefu83Wl6CPnuPqO8pTLH0F+pKTCF/o+Sr0g4tdffslofChz106jn4afagetfP+7A5bH+X5SAvpF9K3oe/8iKvvvszWt6OPnob/2239dvRV15F/nba+A33vzaTv1239Ts//u3j+elvf6YW/19UPftvWd3nP96HvsvXdXvndRfxvtPW93vO/Fr2eh7P1fV76/I78+S760H7Ajt34/z1b3+/5/5Srr1tjl48B9MOvU76+bz+/29OnJ2iZeYutH/TSfxr6H9n6Ie/9y9HfbetHPP+/4uojD9n6pAeJ/x8SkKH2BX3Jc/j/RKh9QR95Ef+ftPWZ6KsOSNSy4+QUu/6Xe+N9V9+92NKzj174dlc/fIqtz8J/9XVXX5Vn69U5+P9d3r/M1md78f+hq+9fbutzPP3PEzmnlWKtg+Sip/3kz9cXjKEvGkNfMoa+Ygx91Rj6ujH00TH0bWPo28fQbx9DvzOOPhHZhT7U/ht9zxj6vjH0A2Poh8bQj4yhT9317vrMMfQ5Y+hLxtDXjaFvH0PPekRc/VVjPL9zDH3nGPquMfTdY+h7xtDfNYb+3jH0fWPod42hHxhDPziGfmgM/cgYevXQu+sjY+gzx9BnjaHPGUNfNIa+ZAx91Rj66Bj69jH0HWPoO8fQd4+h7x1D3z+GfnAM/fAY+pEx9OpXY7R/Y+gjY+gzx9DPHkO/cAz9ojH0BWPoS8bQV42hj46hbx9D3zFav1f27dBvsNND4/yk0LgvNWxngYd5PhM8As4FJz1Cvw5mntkMvFK13g9ABEwA/L+93G+UwDxg5uP2OkGi5x6+FZkE3w7egUyG3wnuRo6H7wGzD8Ds2+qH35VrrysMee8bCO2zBOciU+GLwHXICfDRgfc3H1P3BzsdouAdyCQvvuBbRQbToRfcE9o3MwivdtvxSgVnIc19AeBR+0fhW5FpXr6AvyUymJ7d4D7kRPh+8AhykheeJyinyMnwWeAK5L7eeil4B3KKlz7gm5ERrzyAB5BTvfQBjyDNeYAnsbd+F9r3D25Amn3/4G8hZ3jpAN6FnOmtt4GTfh+6L0Bj397dL7S+uaPNXqfJxX37Znudpur39r6lA3HfBn8V8iD4neCbkQfD94Cpv2adZsjzBz7TrDva++pmxdlXd2hofXYE/w6DT/2DvQ50OGsU2fCsG5n7AkrgR+CPirM+dKRZH7LXFRLi7GvJ2st1YfUe98v9p/e/Ul9Nva962lo3NPW+HZ5znabed8EPIM15H8HB9Ej7L6VH7jNx9g/Cm/2qVjrF35d6/jN2vLeDaRdMvDvhe0UG493nhQc52Vt/A0//o73fMwO8EBnx6ic4ipzKelqb4GA9mRannuxj6gk8z0338g0cbx/DLvRpuB8ADyPTca+epR1CToTPAuciJ8GXPPufy//avch/L52SYqdTeN+NKS8pcfb7p4bKy6LQfvn25+x9xmmhfcY96M2+QzD1zd93CE/9NP1d5Hm7/Zkcan/IZ9OvZT0f2o+/l/Vwb8dj4fqUGGd/fZKXDs/b8TLjsfcZzr0Nb5I5Fxl//zA=
*/