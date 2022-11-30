// Copyright 2008 Christophe Henry
// henry UNDERSCORE christophe AT hotmail DOT com
// This is an extended version of the state machine available in the boost::mpl library
// Distributed under the same license as the original.
// Copyright for the original version:
// Copyright 2005 David Abrahams and Aleksey Gurtovoy. Distributed
// under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MSM_FRONT_EUML_TYPEOF_H
#define BOOST_MSM_FRONT_EUML_TYPEOF_H

#include <boost/typeof/typeof.hpp>


#include BOOST_TYPEOF_INCREMENT_REGISTRATION_GROUP()

BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::mpl::vector0, 1)
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::mpl::vector50, 50)
BOOST_TYPEOF_REGISTER_TYPE(::boost::mpl::na)
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::fusion::vector, 10)
BOOST_TYPEOF_REGISTER_TYPE(::boost::fusion::void_)
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::mpl::vector, 20)
BOOST_TYPEOF_REGISTER_TYPE(std::string)
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::mpl::size_t, (unsigned int))

BOOST_TYPEOF_REGISTER_TYPE(::boost::msm::front::default_base_state)
BOOST_TYPEOF_REGISTER_TEMPLATE(boost::msm::front::detail::inherit_attributes, 1)

BOOST_TYPEOF_REGISTER_TEMPLATE(boost::msm::front::euml::func_state, 6)
BOOST_TYPEOF_REGISTER_TEMPLATE(boost::msm::front::euml::entry_func_state, (int)(typename)(typename)(typename)(typename)(typename)(typename))
BOOST_TYPEOF_REGISTER_TEMPLATE(boost::msm::front::euml::explicit_entry_func_state, (int)(typename)(typename)(typename)(typename)(typename)(typename))
BOOST_TYPEOF_REGISTER_TEMPLATE(boost::msm::front::euml::exit_func_state, 7)

BOOST_TYPEOF_REGISTER_TEMPLATE(boost::msm::front::euml::define_flag, 1)
BOOST_TYPEOF_REGISTER_TEMPLATE(boost::msm::front::euml::attribute, 1)
BOOST_TYPEOF_REGISTER_TEMPLATE(boost::msm::front::euml::define_defer, 1)
BOOST_TYPEOF_REGISTER_TEMPLATE(boost::msm::front::euml::define_init, 1)
BOOST_TYPEOF_REGISTER_TEMPLATE(boost::msm::front::euml::Source_, (int))
BOOST_TYPEOF_REGISTER_TEMPLATE(boost::msm::front::euml::Target_, (int))
BOOST_TYPEOF_REGISTER_TEMPLATE(boost::msm::front::euml::Current_, (int))
BOOST_TYPEOF_REGISTER_TEMPLATE(boost::msm::front::euml::Event_, (int))
BOOST_TYPEOF_REGISTER_TEMPLATE(boost::msm::front::euml::State_Attribute_, (typename)(int))
BOOST_TYPEOF_REGISTER_TEMPLATE(boost::msm::front::euml::State_Machine_, (int))
BOOST_TYPEOF_REGISTER_TYPE(boost::msm::front::none)
BOOST_TYPEOF_REGISTER_TEMPLATE(boost::msm::front::Row, 5)
BOOST_TYPEOF_REGISTER_TEMPLATE(boost::msm::front::ActionSequence_, 1)

BOOST_TYPEOF_REGISTER_TYPE(boost::msm::front::euml::NoAction)
BOOST_TYPEOF_REGISTER_TEMPLATE(boost::msm::front::euml::And_, 2)
BOOST_TYPEOF_REGISTER_TEMPLATE(boost::msm::front::euml::Or_, 2)
BOOST_TYPEOF_REGISTER_TEMPLATE(boost::msm::front::euml::Not_, 1)
BOOST_TYPEOF_REGISTER_TEMPLATE(boost::msm::front::euml::If_Else_, 3)
BOOST_TYPEOF_REGISTER_TYPE(boost::msm::front::euml::If)
BOOST_TYPEOF_REGISTER_TEMPLATE(boost::msm::front::euml::If_Then_, 2)
BOOST_TYPEOF_REGISTER_TYPE(boost::msm::front::euml::If_Then)
BOOST_TYPEOF_REGISTER_TEMPLATE(boost::msm::front::euml::While_Do_, 2)
BOOST_TYPEOF_REGISTER_TYPE(boost::msm::front::euml::While_)
BOOST_TYPEOF_REGISTER_TEMPLATE(boost::msm::front::euml::Do_While_, 2)
BOOST_TYPEOF_REGISTER_TYPE(boost::msm::front::euml::Do_While_)
BOOST_TYPEOF_REGISTER_TEMPLATE(boost::msm::front::euml::For_Loop_, 4)
BOOST_TYPEOF_REGISTER_TYPE(boost::msm::front::euml::For_Loop_)
BOOST_TYPEOF_REGISTER_TEMPLATE(boost::msm::front::euml::Process_, 1)
BOOST_TYPEOF_REGISTER_TYPE(boost::msm::front::euml::Process_)
BOOST_TYPEOF_REGISTER_TEMPLATE(boost::msm::front::euml::Process2_, 2)
BOOST_TYPEOF_REGISTER_TYPE(boost::msm::front::euml::Process2_)
BOOST_TYPEOF_REGISTER_TEMPLATE(boost::msm::front::euml::Get_Flag_, 1)
BOOST_TYPEOF_REGISTER_TYPE(boost::msm::front::euml::Get_Flag_)
BOOST_TYPEOF_REGISTER_TEMPLATE(boost::msm::front::euml::Begin_, 1)
BOOST_TYPEOF_REGISTER_TYPE(boost::msm::front::euml::Begin_Helper)
BOOST_TYPEOF_REGISTER_TEMPLATE(boost::msm::front::euml::End_, 1)
BOOST_TYPEOF_REGISTER_TYPE(boost::msm::front::euml::End_Helper)
BOOST_TYPEOF_REGISTER_TEMPLATE(boost::msm::front::euml::Deref_, 1)
BOOST_TYPEOF_REGISTER_TYPE(boost::msm::front::euml::Deref_Helper)
BOOST_TYPEOF_REGISTER_TEMPLATE(boost::msm::front::euml::Push_Back_, 2)
BOOST_TYPEOF_REGISTER_TYPE(boost::msm::front::euml::Push_Back_Helper)
BOOST_TYPEOF_REGISTER_TEMPLATE(boost::msm::front::euml::Clear_, 1)
BOOST_TYPEOF_REGISTER_TYPE(boost::msm::front::euml::Clear_Helper)
BOOST_TYPEOF_REGISTER_TEMPLATE(boost::msm::front::euml::Empty_, 1)
BOOST_TYPEOF_REGISTER_TYPE(boost::msm::front::euml::Empty_Helper)
BOOST_TYPEOF_REGISTER_TEMPLATE(boost::msm::front::euml::Find_, 2)
BOOST_TYPEOF_REGISTER_TYPE(boost::msm::front::euml::Find_Helper)
BOOST_TYPEOF_REGISTER_TEMPLATE(boost::msm::front::euml::Npos_, 1)
BOOST_TYPEOF_REGISTER_TYPE(boost::msm::front::euml::False_)
BOOST_TYPEOF_REGISTER_TYPE(boost::msm::front::euml::True_)
BOOST_TYPEOF_REGISTER_TEMPLATE(boost::msm::front::euml::Int_, (int))
BOOST_TYPEOF_REGISTER_TYPE(boost::msm::front::euml::Int)
BOOST_TYPEOF_REGISTER_TEMPLATE(boost::msm::front::euml::Pre_inc_, 1)
BOOST_TYPEOF_REGISTER_TEMPLATE(boost::msm::front::euml::Pre_dec_, 1)
BOOST_TYPEOF_REGISTER_TEMPLATE(boost::msm::front::euml::Post_inc_, 1)
BOOST_TYPEOF_REGISTER_TEMPLATE(boost::msm::front::euml::Post_dec_, 1)
BOOST_TYPEOF_REGISTER_TEMPLATE(boost::msm::front::euml::Plus_, 2)
BOOST_TYPEOF_REGISTER_TEMPLATE(boost::msm::front::euml::Minus_, 2)
BOOST_TYPEOF_REGISTER_TEMPLATE(boost::msm::front::euml::Multiplies_, 2)
BOOST_TYPEOF_REGISTER_TEMPLATE(boost::msm::front::euml::Divides_, 2)
BOOST_TYPEOF_REGISTER_TEMPLATE(boost::msm::front::euml::Modulus_, 2)
BOOST_TYPEOF_REGISTER_TEMPLATE(boost::msm::front::euml::Bitwise_And_, 2)
BOOST_TYPEOF_REGISTER_TEMPLATE(boost::msm::front::euml::Bitwise_Or_, 2)
BOOST_TYPEOF_REGISTER_TEMPLATE(boost::msm::front::euml::Bitwise_Xor_, 2)
BOOST_TYPEOF_REGISTER_TEMPLATE(boost::msm::front::euml::Subscript_, 2)
BOOST_TYPEOF_REGISTER_TEMPLATE(boost::msm::front::euml::Plus_Assign_, 2)
BOOST_TYPEOF_REGISTER_TEMPLATE(boost::msm::front::euml::Minus_Assign_, 2)
BOOST_TYPEOF_REGISTER_TEMPLATE(boost::msm::front::euml::Multiplies_Assign_, 2)
BOOST_TYPEOF_REGISTER_TEMPLATE(boost::msm::front::euml::Divides_Assign_, 2)
BOOST_TYPEOF_REGISTER_TEMPLATE(boost::msm::front::euml::Modulus_Assign_, 2)
BOOST_TYPEOF_REGISTER_TEMPLATE(boost::msm::front::euml::ShiftLeft_Assign_, 2)
BOOST_TYPEOF_REGISTER_TEMPLATE(boost::msm::front::euml::ShiftRight_Assign_, 2)
BOOST_TYPEOF_REGISTER_TEMPLATE(boost::msm::front::euml::ShiftLeft_, 2)
BOOST_TYPEOF_REGISTER_TEMPLATE(boost::msm::front::euml::ShiftRight_, 2)
BOOST_TYPEOF_REGISTER_TEMPLATE(boost::msm::front::euml::Assign_, 2)
BOOST_TYPEOF_REGISTER_TEMPLATE(boost::msm::front::euml::Unary_Plus_, 1)
BOOST_TYPEOF_REGISTER_TEMPLATE(boost::msm::front::euml::Unary_Minus_, 1)
BOOST_TYPEOF_REGISTER_TEMPLATE(boost::msm::front::euml::Less_, 2)
BOOST_TYPEOF_REGISTER_TEMPLATE(boost::msm::front::euml::LessEqual_, 2)
BOOST_TYPEOF_REGISTER_TEMPLATE(boost::msm::front::euml::Greater_, 2)
BOOST_TYPEOF_REGISTER_TEMPLATE(boost::msm::front::euml::GreaterEqual_, 2)
BOOST_TYPEOF_REGISTER_TEMPLATE(boost::msm::front::euml::EqualTo_, 2)
BOOST_TYPEOF_REGISTER_TEMPLATE(boost::msm::front::euml::NotEqualTo_, 2)

#endif //BOOST_MSM_FRONT_EUML_TYPEOF_H

/* euml_typeof.hpp
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
*/