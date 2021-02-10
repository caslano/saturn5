 //////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2011-2012. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTERPROCESS_WINDOWS_NAMED_CONDITION_HPP
#define BOOST_INTERPROCESS_WINDOWS_NAMED_CONDITION_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/interprocess/detail/config_begin.hpp>
#include <boost/interprocess/detail/workaround.hpp>
#include <boost/interprocess/sync/windows/named_condition_any.hpp>

namespace boost {
namespace interprocess {
namespace ipcdetail {

typedef windows_named_condition_any windows_named_condition;

}  //namespace ipcdetail {
}  //namespace interprocess {
}  //namespace boost {

#include <boost/interprocess/detail/config_end.hpp>

#endif   //BOOST_INTERPROCESS_WINDOWS_NAMED_CONDITION_HPP

/* named_condition.hpp
nDlCQrlBVteGEqCcP7rE9N5sSJvn6ub9KhVKt7116t6lxTa2kuLqg+6OHwjtTzBc+12mytteRpWBbu92eKv+1oKeFiiw1WjyqDuuc/SCoZwXx+u2jqyJZtB5M9BcLTg1EFqQfInx9dCyQIIRiMcrzQiU5JNsBDrySDkCFVkTj0A5tvQj0I1PEhLoyCMVCVRkTUgC5djSkkA3PslJoCOPFCVQsVCiEsjHL10JtGRNWgLlCqQugXi8EphASbY0JtAtazITKMWW0gS6ZU1sAqXY0ptAt+xJTqAVa6oTKJc94Qm0Yk17AuUKJD+BeLxSoEBJ5kQokI5POhToyCMpClQsnhoFGrIlSIFuLGlSoBqPZClQkSlCBRpySJwC3TJGp0A17klUoCJTZAo05JVQBeIViEqBkhySq0C3PBEpkK6ERCvQMWM0ClRjSLoCnTJGokA1hgQs0CljFApUY0rGAqUyR6BAN6bELFAqc/TJYegWdCyUbMWr/ULzKg2uC53m9/7G7/d73SBfie0lZ+mdnrROWq9OXp3+0jrttqPOWF37eeF1rWhMVa/V+rb+73ahG9Nvy2++fe2fdr7tFvit215Vy6UN0bFKxVo0NLmo8vxoVeqxY09oFatSuVQR0+mkCke6+dfQnNhkRkxXMwp3
*/