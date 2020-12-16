// Copyright 2008 Christophe Henry
// henry UNDERSCORE christophe AT hotmail DOT com
// This is an extended version of the state machine available in the boost::mpl library
// Distributed under the same license as the original.
// Copyright for the original version:
// Copyright 2005 David Abrahams and Aleksey Gurtovoy. Distributed
// under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MSM_BACK_TOOLS_H
#define BOOST_MSM_BACK_TOOLS_H


#include <string>
#include <iostream>
#include <boost/msm/back/common_types.hpp>
#include <boost/msm/back/metafunctions.hpp>

namespace boost { namespace msm { namespace back
{

// fills the array passed in with the state names in the correct order
// the array must be big enough. To know the needed size, use mpl::size
// on fsm::generate_state_set
template <class stt>
struct fill_state_names
{
    fill_state_names(char const** names):m_names(names){}
    template <class StateType>
    void operator()(boost::msm::wrap<StateType> const&)
    {
        m_names[get_state_id<stt,StateType>::value]= typeid(StateType).name();
    }
private:
    char const** m_names;
};

// fills the typeid-generated name of the given state in the string passed as argument
template <class stt>
struct get_state_name
{
    get_state_name(std::string& name_to_fill, int state_id):m_name(name_to_fill),m_state_id(state_id){}
    template <class StateType>
    void operator()(boost::msm::wrap<StateType> const&)
    {
        if (get_state_id<stt,StateType>::value == m_state_id)
        {
            m_name = typeid(StateType).name();
        }
    }
private:
    std::string&    m_name;
    int             m_state_id;
};

// displays the typeid of the given Type
struct display_type 
{
    template <class Type>
    void operator()(boost::msm::wrap<Type> const&)
    {
        std::cout << typeid(Type).name() << std::endl;
    }
};

} } }//boost::msm::back
#endif //BOOST_MSM_BACK_TOOLS_H

/* tools.hpp
x9sWANt5eh4n64XDjfPC9cq0+Iw8Lqb5HDUIMc/dCYbJ11Pl3L+nWDNfpXE0vQEdgXuzx7n9T4S2+HWfq7XMKrNzVuMbYaaStNr0wC/Pe1WclHw5z/B13OghG5P7nj2fM9ezqMM5myYffozPcfvkfQKfceuVx89vXtrlxFtWsOkg475Z2w8zlFG8bI26HOzCUufKa1n5HFUE9//Yb8jlUeD2fSNu19G3Qr/hE/9Z2IV8LvHC5r4s/BvqzHjM2g4ziSi3Cuwjh/XLrZ/LcbnJsXiYy/N95qwcom/nsbqMs98Uc3/jGbjsb3f5DdUL8rqcy3GjkGtg27m8rkf4h6ot0Vgj+sahr6chUOc0Dk+8LeBzidMPwF9VnDlmK84qvZN1W5n8TuozPO2IGcvYB+gHdVoMl3eOn+kxs1TiYmwth3QThAhj+DyPORbTSMU+dfww6NN186HnQ6ab5jIYbXv6OJ2sbz/C09M0cp/s6178k8+XunHW0giw7hvWKZeinF7kMyYR7D9OBvW0rOHDK8YmlBjcL2GbnbYHhWKU43dczWajjvpWuq7v7nc9xqvvgdK5vjEmfeEyLmM+9pqmBUz05QBjwhJpGQy9uGxxYC7gh3F8fFcojUmeqf1KkDOxgYkeA2Zm7vD89AzPAcCUQox3R70cYrz753GYId9J2LRgmtwmttAvPE7oaBOsTz5e6GgTrMeOrtvEzkukrtvEwNfZmDiMl0pGt4l+UKcgpG/mM9wm2A64D7z7tJ7n8Zz1B5cWnJ7jlYL6OD3rqJcfKcYMt3X0VVKHfbBeVmnddO72xwHd+vVIQ/HHIg62rw76Kz8MfHKew5iUYfC8hNfVVRiker5sL8hsmfqhjThx71Fy2q/nuvY5Dovb6bskI/15YXffkAz78ugPlM5+PO7qyXi8/dyi1NhHbsNGHF37xz2ty0m9yQ777pLVfnSC9pjDkQFzP5jDkAEjvlGYsd/9Zj8neneAQ51yugoBzvfbinkMrUqmVUxFIu//h3kyYHN+wLDiLf4ACyMVY01Zc6ZRbaHOtJ7k1dkgyOo6GwU4v84K79GMX2elIKPrrBzkdJ3FAc6vs50gk19nvSAfrrNBkNV1NnI408e5d9Ci90qd4pB3xxyNfkYa2u8/oNEFY+u5yLfZXd3xI5Y53PKhGekzc/jx+yRDvc+62d9m32gU1NNEYiz7gGRgW8hfydXJFmoRtA9KjdqDfAP2xgWpJWbIlWlf/hD/lrayDk6U6Z6g0EcfZp0UkgkiHXm7UkHqPILKc/tXCTP2TGkDabmq5qgj5vHkakrHfT2sO11dMfY2dL3eJoty1kNz2TF4DrauOaeDl75y+bJhlvZyKhgDwuHZsLiNLYfCwpV8aptrLYxBg5wwWzFdPE+PBfH+TYA19wZtvbXQbq6hOXnXrhvWzWmoDaxXBJiEylhmwlmvCPOyrFuYl1w2zMqyjq4ZYrisM64Y4Mg8bZmIvYWPOu1Bfjd/A/XmM/qb+a2M7e7G0qa3ZIc+q7+V30I6H3kBl6WVCPODEtk1/L0chnqoRlWsdZUepbl0VGO73360ZtJeittb8TE5jClp0aeUH6s5/5tqgxBjGq9cZ3pcDpNaHbhBDme/vc9rfo/XnP9dqsITNMMjPMdZyuNsPtF35nGNTn1TcHEOZ5fQeb8myPH1dPkNvFGI5avnfF76iWHOe8GzirHul5fxePdNj9jTzVe9qFPh+YCvU+jOeO7pq5tiz/RXSpNvN3eQd58jc5cg0noht9+o1b3vMF04pFvnS65p/PwyQa61UQNT/JjPbFBi0t4H6z0X8eOjeq1z/1W4WEhPk4P2EGaoRs0oynGVL+lw+rtHl/L1cN4=
*/