/* Copyright 2003-2013 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/multi_index for library home page.
 */

#ifndef BOOST_MULTI_INDEX_HASHED_INDEX_FWD_HPP
#define BOOST_MULTI_INDEX_HASHED_INDEX_FWD_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/multi_index/detail/hash_index_args.hpp>

namespace boost{

namespace multi_index{

namespace detail{

template<
  typename KeyFromValue,typename Hash,typename Pred,
  typename SuperMeta,typename TagList,typename Category
>
class hashed_index;

template<
  typename KeyFromValue,typename Hash,typename Pred,
  typename SuperMeta,typename TagList,typename Category
>
bool operator==(
  const hashed_index<KeyFromValue,Hash,Pred,SuperMeta,TagList,Category>& x,
  const hashed_index<KeyFromValue,Hash,Pred,SuperMeta,TagList,Category>& y);

template<
  typename KeyFromValue,typename Hash,typename Pred,
  typename SuperMeta,typename TagList,typename Category
>
bool operator!=(
  const hashed_index<KeyFromValue,Hash,Pred,SuperMeta,TagList,Category>& x,
  const hashed_index<KeyFromValue,Hash,Pred,SuperMeta,TagList,Category>& y);

template<
  typename KeyFromValue,typename Hash,typename Pred,
  typename SuperMeta,typename TagList,typename Category
>
void swap(
  hashed_index<KeyFromValue,Hash,Pred,SuperMeta,TagList,Category>& x,
  hashed_index<KeyFromValue,Hash,Pred,SuperMeta,TagList,Category>& y);

} /* namespace multi_index::detail */

/* hashed_index specifiers */

template<
  typename Arg1,typename Arg2=mpl::na,
  typename Arg3=mpl::na,typename Arg4=mpl::na
>
struct hashed_unique;

template<
  typename Arg1,typename Arg2=mpl::na,
  typename Arg3=mpl::na,typename Arg4=mpl::na
>
struct hashed_non_unique;

} /* namespace multi_index */

} /* namespace boost */

#endif

/* hashed_index_fwd.hpp
TM4TgReWPrwwGOg+eH6/mMUvSrIkdkJHS9H8PmX485R/IJEyylM3FNjZaAHFR1vPlF+JPK6SLJal4L0Nb29v5zJVFjhF6RWC90DcFvVlK9/SsozCIKm00OpAvmH6r3+W9wVlkPk+ZBv2VjxuP6D8QuRlUYEpLvGK06t1fVOza9MWcI3F60BYpWUYFCDC8hj5v+Bx8qLISdKoAgHW2gz/T5zvxpGfStcDPjYbmlf/YXnliFxFqAIfm9a0hNu0hrO1DrfxnnulLJWCwemKEcU+7fGf431oAIbCEynoLMa2+TpJZTIhZRAFqr01MoP9dGSFkVUlvDATZMaDYaCPD5amQBRh7paVdGuh9n4afXx8zmqrWVblhSwaWbuqOli/qVwl4iCPfdcvBJ9Z8bRd5mmLZFVUmRMLOtuy/ZB+mcUvEmXpVUGYh0IlaG1leVHbkz+tltTcYm8H7cxa5e1GbhkUZSXU1AfuyqmVUldtKEDQRhZtPt+w8rVychlmRSbmTvfWlBA0R7U5sbZyZnaN2DzuPNHUUSr/9NzNqigJIsFMJJt4bv08L4fKzV3HLwJcHTduC5SbigFfiQ9nspUos7JyklzAwcoS2HVuOqh90CAGrRtjXvtMTyiKVMZF7FbaecDKitojwjSfVdek181YbOJxjMp7nggCvwx8P1JldWax29hohpxWaZmfs7d1BMbj7SwesfByP5d54IomH5TZ5tXFFjPNuK6l8rnInSKKa3Pmis+70H0m7t9kcQf/L6ppl5EvZoxp7oFNqHlV6yAzXjmz2i/HX7G4S1HEUQX2aIXqv0noLN6JqS9WOVaxDFMpEwG5pQtRP6uFKjcze6q2ew0Fc6aHfhhQ1+5rfJ8nCcPC8UuXlQX0klCvmvJYUdvYc6va8LIYoTazmC4pgjJPnDROma4zS0NKtu9b9c2gh/o9iTJZxmEqTL2cWVRnW+121GHNdEztfVaPgDUTjGzE+LP6A/inx0fgYibiaACa3omGiUrf/jMQ0QA07ANc1et8R+8DfKf+HfcB4Jzhu+qbuX/8UHIetNyBr93lxkkQw3oGA+crZM0x1TEYADDC12tk3Ku7ytebUvqRmybRna83Z/R680EkLi/X4eklPcbxxR36HbxR9uM4uqHB9B251ZpB8vOKhaMG4Jh7Hef1vqmKjnlFjl6AMK0XP2PtS7qJl5WJe7dpxbn7Z/hc0i/zKHADTygihq7vi/J++AaTkyJROe4XlcPlXk4kRybQpxiTdUTkZ4Uf5ymXPW26XUetEbFcVjr6gisw626bnONMdDgOpz+4f8MxvdDHvY4NAxhUdpTdMcpwOFlG2Ysc066edN3Fe7mI09Sh7j9xHCo4yv5uM8WaFkPmaBcv8zE7dtModROnfzag6huOavV4Xxj7kZ+m9SgTaeamZeYUd1uPoD+B9r9D9zeNAES3ZY9mVbedJnJkX+DJHcBABts+YlMbCFbnAGLXNxoMrzDgec7OUYMpiN5lxu+8L3mcOVvaNIhPLy1P155x+n3OVSv/CgmrwzK42/yj/d+azp96/FKxQmxPh2F64wTvMHEMntxNz/R6xq4E9j87NwzwjB0M1HV+gAP3BE4vd6fV1TGia3SjzcMCQM76IEdvlLG9pEEOFBbqODY6gGP7wr3kAQ5GGDnRJpuD7RDj8oNBjq6JeC9js42zCoRhfXmAh+0Wy3PXFsaBDToM55scWx1Wnv5Wmzc2UJ43LM6w8uzdg/PayvOmzeHliXe3OIeX59Z7cbytPC9YnLby3LmNc9rK85rFsctzz705Pqw8f2DxSHliX9BjfUEqwiIHP/Z3fE/S9AXwvnjDA1V41n63Q/ZpzRzl53ClFOKlR1g=
*/