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
Zghpuk/Y5vfHZ5sbbE0mWvQYr2Sh6POGh73Seeux5CldsFX88MK4e65y9whkl+wSEtQ71E5b5ci4xqY+dIAh6BF+XaE0AyLrE4K0Pc9j7cY0RDilvEBhthrJ5mJfya839O9cIpZBufNY6K/vw/AO5XqZfF6mD860K/npyyL4r9gJHxm80ZiVmL15rEFdg/M0/zJ9ns1CIX93z7mrh+CTH/0MkiAFB+E6rxCsZ8S8BQG9JNQqEzVaUBUwrrPxiTYeaGPbtkESa2sKZ2rZP66pibM3cCk2eJwsdJOFfWVKtTXQVchhCu22aZQ24AyGr7ScHEiharrZkWvXATSCMErWB5tE3aMqz9RmI2R+HOvMda8eoySdL2ZXnfoiilP3++QbOM5GVLWjs8bAvdz9/SNzoVFSo+98CodN9Ttcoa6KA+TCCBCFQQ2mROhOB0rRwiuiBKstlbEY3/VYj1iTW3qEv4zDYB0H/modxHEUM45aK52pnBqe3JLTh5y2pIzKVO2x4DGMgLod9Qf4sc8R+7Wcp6N+ric0d0+23D1f9D9QSwMECgAAAAgALWdKUsGnTrLfAQAA/gIAAB4ACQBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3Q5NThVVAUAAbZIJGB1UsFu2zAMvQvI
*/