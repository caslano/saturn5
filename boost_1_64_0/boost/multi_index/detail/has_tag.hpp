/* Copyright 2003-2013 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/multi_index for library home page.
 */

#ifndef BOOST_MULTI_INDEX_DETAIL_HAS_TAG_HPP
#define BOOST_MULTI_INDEX_DETAIL_HAS_TAG_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp> /* keep it first to prevent nasty warns in MSVC */
#include <boost/mpl/contains.hpp>

namespace boost{

namespace multi_index{

namespace detail{

/* determines whether an index type has a given tag in its tag list */

template<typename Tag>
struct has_tag
{
  template<typename Index>
  struct apply:mpl::contains<BOOST_DEDUCED_TYPENAME Index::tag_list,Tag>
  {
  }; 
};

} /* namespace multi_index::detail */

} /* namespace multi_index */

} /* namespace boost */

#endif

/* has_tag.hpp
mxsWn5fmReHLVFihUW2+r1n9V8rMC4IwEZb7fc1GbFKX39ML/MQHd5aRVz7/Hv/BKl9SxVEVhIGwr15btu8/eT5hGhepl6cC5t2T86CSlv56DF+Ubh6VsSPqeRrxqBv397huJJUbVkWVC+0X7C1nYDrOqXa41L/Q3eC6seRx3Yjj1HfCUrNiXOia5QLuD3i8HfzYSVLppeIyMOn439qNqZnWcJw9x+JLwkJpvhcgH9qNnG/X4gvioojcNOV8WE6cC1/N6xZmSem7TqbrhpHVLJvmbZzHTXzXK5NIqBaEwbyIOx+k/d9nlU/6We64Mq6jySzq6UB5du3tmZFC7ul8xrPvGaeuHzdrFn3NdLIA3O/ymI9NXvluVeRCBepjDANT1l95lk+yKmcZlqlY62xg7Ra31JDBMNd4F+rvjDcVQZFXMNTE2sXdxp7SLlsv2uvDP1lAYDyT8un5UZlnUimZpywzhe+t8buwD/atfV7p+kFQeaJ5T2tybrx9L1syckemYepqb0g9whd3+uoHjNqeeo1w0LXWWG/zuT54fp5UaSbA9iH54x1cw/cJyleJyi0qP/IcsdHdBc+27uX1bneju4F8obEjKZ/niSyWYV5Eot5WhUvIG/rlBvM2oS49hCTo7w27ZJ02FXC7KA/cQvW1I2qlWFQLj6HusCHe/cI3+RYYby7CMiryMK4M78Dwrvd2t8A1T9+KGYy1/bmA63YWpYkflr5Q67Tuei0CerF52gz9THGdGlj7YKXjJkngcn4+Jl2zZmC8iYi8PEzy0AFeZWj0hkZj4Nb54GJnuI66I/DeJ5NR6Ik7jJyCyFAf+aYPtBfP3v76EDt19IZFwHTIyzwndDOnCVIC+Q/G1o6/suqe+bHjJJVUTHugB+osCN70gEc9Onvn8frfhqn/sZDXv5KR4waRL3rKdj/f2dZPKZpBu9nfUy0wtm/22NC+p+vLME0SIqMZiJpzD/c0QsvPNYgLL/EJ3/qW0hjVVHtGafDu8rmQjZvcz+PYrVJktcuK/pIhP/+QgRM5ZT7i2+qajUFh2vhqyPUzVqPbyaUzYupdpB1tr1neabVP6YZ+6YQS+blmo//0hxlfLNK8jFM/IPnuqL/0Gc+iPtOr+QXG4rX44XSulBHjH4AeLjIbVODeWsjvvQReGvlORtjVaWbN08G9NatPPRlXmV/GnImVF/XoWMTPIPLIdWI/RFY2gEkcjAdHvH+SxCur1MkJo45oD//q7FwZG79PjqxYAV5Rxn7u2fwD9Q+YhoZdNabMdhKxZzci6zzEjaKyCkk5dmvzoNmHwX3giLdZmss8L1zSZtA/3Q1Sepz7rlm8oSudwE0jwtu7iPrB9etDVrv5buIEeVSMeF/c3VMzR31PG9v9omvs6cg6qyqTogqrRBh1rme8zmC917MG5DA0OsZkZKrNqqgo4gpl0MkLZKh/k+8oxo2YjfkcnDtVWPpVKMzrwYtrMDzNTAaTGszsm6ZApk6PjHmd/Ch1yjJ1iBw0YtCWsOaYOOb73pXrF54rRyLUR7pn2YbnYmtfIw49T1bJiAnujdZfc3su3I2tPSU3S4sqcwmvuiuw2TMTDMaPYXxSBJUbZY4TGT4ccHjbgH87PxFb+5ZxIF0pqxF/vRRrPvxdMo/jXvyPrHonnhdGfhgTGV3gHo5M2oHJ/88x153SV70uwxR5sbshehcfBKGZcySVUYkiy6IsSkgb7O+oCXZv0Nme1OvYfwvSmvcgjE/s+UTOcHOJ7iaO3l/OJNOXwEmSPAhyZKXlNjzPkTyeRhJ6ZSmlUKbp8KA1xLa05kk4WXYLV9SqtUOGOtWzoanja6W17s7KNPeTTPNbyw97jn63lXc=
*/