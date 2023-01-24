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
JAAxGNdAesKPGFdYGFtbxEPA4RaxmhH1WtdQzt3pPImlGG626y1igwx27QZB7BdFGRrhRUfEGlcDS0o9a7T7W0j4YU6tGFedtMNkHxRlLtwQkyYymYFDvTbKPHybxPkL0pM2QrYPWIjNEDeYxe+ZKHAWH2N8BL1e2U/PLldaHLrtB/SwuPYaHNgTx6oZBULOVYNF1PM0kVtNsJy2lhejHw2Li6qK9Im4PjPUm2/Odbh6fJPljg3rp+abi8fUfJPlyTeVfS+bb675b6h8k+WHbx7qe7X55q+M/x3fOJeGwjffFUp8Uz3Hm2+y1HxjygjKN+OW/pv4JtPF+abQIvHNq/uQbx7ZR3zz1Z//EN+sSbh6fGN0x37XR80361xqvjF68s0rfS6bb/Z/GirfGP3wzU19rjbffN37f8c3Sz4PhW9eLJD4pnSWN98Y1XxTr3dQvrn3838T38Q5Od/0MUt88/Ae5Jtb9hDfTP3jH+Ib+41Xj28S3LEvCmq+meVU802CJ99kC5fNN4s+DpVvEvzwzbFeV5tvZvT63/FN/qeh8M2DUyS+KbB7802Cmm+29wzKN2Gf/pv45tARzjdNe0p8c/MPyDcnvye+6fn75fMNUFHBxBgYviGorrWCuNfWXBDN6NZj3dTy0vWCUDgcRh+W5DCPoMRtLa5XVxY7BwwH6ODFoByMTKBz1ii6kbRPAK7Z2gyrSXWVi0aN6SWV
*/