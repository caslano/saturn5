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