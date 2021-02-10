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
2vDuRud7YNfSqSgwx26SaKWStPBIztIMdiI5GZq5iQGNRZ6zImlKjmy7tQi20XIzuui3h24fTFNnmzIuFUgep6Xu9yP/y/Iy4xZyPCP2EtcVLxIuX24fQfuNMKH7dMzdm3aCGYGJ7V26wuXZm9q1r1ym+xMkTDFge4UEqBn0tYQDq2DHeQF31UGoO0KfaixSlFIoEYvMI7PFKgDUY7y6QQb5b/fCIGt/uYJ5GKxH9LU1nkHC6SaCKBjRN61FwCc/8g3y5XEZ6bO76qHHMhMseXG2loY8x6l9ccG+/rz/AFBLAwQKAAAACAAtZ0pSLi2HSfwBAAB1AwAAHgAJAGN1cmwtbWFzdGVyL3Rlc3RzL2RhdGEvdGVzdDk0N1VUBQABtkgkYG1Tf2/aMBD93xLf4dQKaZOaBLIAA5logYFgAoWFdNI0TZNJjLCWxGls2vHtd04otGqVyD/unt97d06o5konTHGfUFHsJU5/+elJVqnyyXYdb8g22K7qAYL7eAGhGd06YC0jEs2n3rDnmbk/8IZmHvTdz4Q6VxrqNMzkltzCllePvLKUSDmhFS+zEwJUHUzy1CdXkcksiGaoMNusfjba7qceBEd94IUWCdM8ReoXR6lz5quFpplA3FkoqTcXJZ+oXJeX0z4BWrCc
*/