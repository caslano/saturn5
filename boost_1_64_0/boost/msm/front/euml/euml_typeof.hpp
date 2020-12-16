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
tKK+klmeEx0AF/gdaqhjMHEfwPZNzgO5WOOHfOJq+L30bbE/8M8HrfwkfE9V2Et/gSwcsGsoDzDKd1SDvTwuj+V4eaDv7oKL+o42WK59R3LdHpz2HYF57QEweb6jPTD5vqPC68Dk+o5KYPb3HaWKi/uOtsDl+452wcT1Jnk95FHf0cTh80Ae8x0V8fv9fUeL4PJ9R5uKifuOdsDt7zsagYv7jibeAHmu72irhfxHfUd1hOH7jqCrkO/vF9oGF/cL7Sm59gsV3ggm6hdCf/MNP0/UTE3/1W6tsf2zh7YD31ETe7jRjnN9R2iDxZuCVb4jpPsMmH39QjvPALevXyglv5Djcv1Ci+QXYibfL5T8CZzyCxVDGYqRfSo7b0aate8IbwRf1DHad7QDWdx3VEKd5/uOUjBx39EIaYz7jibeouTKdzR6PNKZ6ztapPFUM9p3tJHHrch3BRFf1He0u40wor6jLcSR7zva0YyeayEd2ne0AVncd7Q4upiTx31HO5Dn+442fycZEJDvQR73He0hj/m+o+TBilG+o/TNYKK+owmEke87KkUYWefpx6CHUd9R0rwc5DHfURHy/X1Hi+DyfUcTH0Ba9vUdbSHNcd/RrpJr31F6RTC5vqMtxWjf0a5ilO+IFFsxyndUR3+wv+8ovRb6nTzf0SzS9mnFKt9R8hnFKN/RCGNE3Hc0usJBJ8/3HU1cEUzUd1RXcu072gAT9x1tQx73He1BHvcdFQ5BHvUdlZRc+45SxWjf0RaYuO9oV8m17yi5Ephc31ERTL7vaBFMvu9oUzHad5R8HDoS9R3VbwI9i/qORteVcitGveO3cd9R4fyXhjz0HZUgi/uOUiXXvqMtxWjf0e40mKjvKJmBPOo72p6HXPmO9iCL+44KC5Dn+o5Kion7jlLFad/RFphc3xHPlUKWevVjYgxL7gJ5rm+pCCbuW1pU8rhvaVNxcd/SIsZM37eEdvUSPxxppcL+DMOg6obvDbLQr2TsabvuOWYnHrIfa9dAYct/4qBm2fRYGXPJJ3M5E94K9inkc3RI10/nxr6sn87RbdCeY/6yFYSJvMc4P/6tfVkbP+x/sHF/2R7k2l+2Sf4yyPbxl008E/1h1F9WhzzfX1b455j53/xlJfBxf1nhLciX8pclD4Us6i+bgDzuL9uaQJ1G/WUl/D7fX7aoGO0v27g64on6y/bIZ+Tkuf6yDcSzv79sW3F6zlR4GOKL+sv2OAztL0MYilH+shLiyfeXpWDy/WWb0IHAX4Z4lFzN4RY1w3M49DFYL1D+stIt0YaUvyyFTPvLNjGHiPvLdiDP95eNFBP3lxUWFRf1lxXBaX/ZImQ5/jIl98Peglz7y3Yhi/vLRpDH/WWFFuS5/rISmLi/LFVy7S/bVIz2l22gL4z7yybeC33z/GWFd6EviPrLSpDH/WWFRyDcXH9ZHXFrf1nxo5Dl+stK7wMT9ZctbkKu/GWbSqb9ZRtoi3F/2baWe/1K/VmQ5/rLNhSj/WWFl4KJ+stKSq79ZcW3gon6ywrvgFz5y0papspqD2UR95cVNiCP+st2UB9xf9nWp6Bvyl+2jXm29peVEK/2l6WBTNZd8T6Q9dpcvYOTfa670QcuzwyyZRmsAUFHwRj5AP3un9x6V5fWkHiIG+BOjHFf3zV9fXISbeez+I4xAPV1d9fP95VvJ8U58vdeMYdpOjeHsMk/Djb02/D8H3H6fpvr4EwP5NrvIvdBjv03A89/M482ddal5Yzyfx1Hu5wEE13D2r4F5GoNC3PqP2f10j3S8eqlgX7zixd2cr9e0q/iu6qXPVuOfZKF5Yh4d5uHwMTKcXRjyKPlyHvss7jOEJdbTsUqmGg=
*/