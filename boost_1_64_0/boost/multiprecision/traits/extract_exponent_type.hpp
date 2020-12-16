///////////////////////////////////////////////////////////////
//  Copyright 2012 John Maddock. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt

#ifndef BOOST_MATH_EXTRACT_EXPONENT_HPP
#define BOOST_MATH_EXTRACT_EXPONENT_HPP

#include <boost/multiprecision/number.hpp>

namespace boost {
namespace multiprecision {
namespace backends {

template <class Backend, int cat>
struct extract_exponent_type
{
   typedef int type;
};
template <class Backend>
struct extract_exponent_type<Backend, number_kind_floating_point>
{
   typedef typename Backend::exponent_type type;
};

}}} // namespace boost::multiprecision::backends

#endif

/* extract_exponent_type.hpp
z0ZdQc7mbQz4vOLt3068zdsiTe9bOd9sZ0jv2D3+G4/0Ur9xhfhaPdTPJjCc1VPSsf+enCO/TpqOay14rYJ0PG0H59StHaX/XCtOySFbtxiPlWU6x3P8XptySCHlp8nlNZ38/sR7/zceqR2kx+TzFo703vqvvKbe+ftwvtGKkN7P/VdeU++hnYzP20X8ZqhyavKa7afiQs3m3FM9GiLIJ+KAQtxzBretpzIB3Gp+5n9yKYF0PozJsG8yxeHnm3Ka+sr7m1wq0uTTC5xjfl8pr+7aBbz/2ZeC/pNKy23xtTxWbSSX48M13VcPMHnUEpKvbm3OUdvIqe5vPJC49H3Q7V0l3Ph+1N+OZfg+RK5ndRLvuZ1pJ/TcZ6UeyKn9ERKL8hlz7+QvJYIrmLRtDLvnxFkbZpzeEnG0M7IjyIFXsqHR7hn6fyVlcUf7UyaVtP5Gw1V9DHLYDfwoyxy8TaI3i9d+y+vonFjOa7B9Q7+u9MLFqKSV1uwXhwlfXpF7SHicflNhc0acmP7f1pwTcy36RwknjM7s6ulxIuFESeoWVnC7Yyp8XEMMDdZw3sr0yTXBNPWssH3u9IVy3jRTqxjkP9yuJmRZeBWUkzCzHLWX5X5amn8nEe2c6zCEEVtuyR+cjx9hmFzRv1vJMazaWdTV71oYZTiu0pPsOY6t9vo9tp9w1xjD5c6wxdlTfXZvAXGa+3Kev4Uwti/nJg+H2RztLPA2wgZ7dtQezQGGTtbO4mI45iaeYtDOKas16XvL+UgktK4bTLJ8z4SXBIFrR86dlqNqLlDZM81BGrX58hsVjlfFQJy1ub1hE5NtEMnuG0EcilpnXbmHZK9IDE1WaTXnBdNRA8dCRvLYmeO4OW94mePmvCHluc7ByOv4NQOHv5zqLQ3y6kv3GuTVbH/pgHIevZMJvtXvK7Mt2wus3BcF5A90k49MVY/XoNiysTaycW+ez2UShpblhv9PPocPUnHlUTXz+fdDKpmy3pIfJocJQ2c0fH3NwOUdw3N47ljfw0YcVh+uyPDlxa50I35rYH2OnblleG+pwslPb7+X7qdARJmXR0V623NVODur5qre9gTww0twPFbP2aJ/6jmn83p4Ne1E48cPMEyWIhrfXUAMz97rsDbAw7b3vWDXO9ZxrDS1LSeRe7feycOmpb+1fcV/UPsd4Qyt0q1zXjGicTA3iTTgfGy0hSNvJSAOnl0mDrbYpEbrG41taXDYBQe072mrxgNCW7zLbRqnz+xRWb0hOWqydA77Q7Te+/xxxP7nNDy71+APZv5oZfs4w1n+Dc5FVZz106dfitkxuHPlHhSutraRTHlPwtAVJLNrB4ajE2FMUJUz6hO/BTE8C68VDDqgr8X5r6289dNsLHSvJocO6Wu6brby8JA+cuhsT5ND3+faz/dpctRBfjonrzhn4BGCOiJ0LwLDKNEkG+5kOCaWsAsMk5En7LH31TCMtC7HMBlZWjP6kjpzCbHoLpyh8OMfGYTDCbZB/4+1U7EoCrcos+S272yBxRhYR+R90T8Oec8uO6UNd0lImj4mXBtBHNYU+3CtN5w+XV6F1K305uQVi9g91OrAnlHkVjpsLHLZwgY7e6XhRwsJ0jfw/OQwfgPnWAcCz5qrvQbnJN6dH6Aku6GwDQ0EWVqbfWeF92c5Tme2L44g3tMs0x6MQ5+osQ15O15rX+oQy5NMuHlop35i33meYF9K+WKu2ZeSuPIFcwVhlS+YKwir/EBu0DDlA+YC2g9R+aDpAjWf+m34xrzrJfVc+ABe7vYr/DuAHz9YrcNAazS72tVwbY39ZlUOYYSJfe+qe/AI2kNt4tQVIx2QBJPT1e/uCUd1nMYV9P250sA=
*/