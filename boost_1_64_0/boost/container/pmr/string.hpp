//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2015-2015. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/container for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_CONTAINER_PMR_STRING_HPP
#define BOOST_CONTAINER_PMR_STRING_HPP

#if defined (_MSC_VER)
#  pragma once 
#endif

#include <boost/container/string.hpp>
#include <boost/container/pmr/polymorphic_allocator.hpp>

namespace boost {
namespace container {
namespace pmr {

#if !defined(BOOST_NO_CXX11_TEMPLATE_ALIASES)

template <class CharT, class Traits = std::char_traits<CharT>  >
using basic_string =
   boost::container::basic_string<CharT, Traits, polymorphic_allocator<CharT> >;

#endif

//! A portable metafunction to obtain a basic_string
//! that uses a polymorphic allocator
template <class CharT, class Traits = std::char_traits<CharT> >
struct basic_string_of
{
   typedef boost::container::basic_string
      <CharT, Traits, polymorphic_allocator<CharT> > type;
};

typedef basic_string_of<char>::type    string;

typedef basic_string_of<wchar_t>::type wstring;

}  //namespace pmr {
}  //namespace container {
}  //namespace boost {

#endif   //BOOST_CONTAINER_PMR_STRING_HPP

/* string.hpp
PDoYrj/078NN8BouuD4Fx50nenver3YXhK3Y5HkvicfhehquE+EJxzB4zBy4TgHDx1IXceI+FW5v1Hl+/kqHcZ4c3XCdBMfm98M1AtoxQGwqXOVcpXA9AddoyDMDrqVwFTmPbtTOXb3x/PKv3nj++UXbwvA+fDzWJPKJ3KLdXVLuqZAvLsi/BpEzx1sD5nt65cXliTjHPNimaIs+VrTTBfGirSN3KcoNQSJOtCnakWsT7WJdnpoSgjEHre/i+lR918X3SbSz+q7z64tvmfzn+jL1HPtyMTnM55iDm2s4hiKHiKftizaOu0UOaF+0TcYth7S/y1OfnAPynnt/AsM8OZ91n1ufLmbc1lxkjh8as+nnMWZym4ejzr6Oivai3bieivE6t7l9ruupXIuIFblEfpEb26R9PbFBtCdqEXl+vPF8bsOFj6e8bSiAtkSbr4ec//bBN34Xv/0W8TM2iDrObS7+UL/6bvjfb/P+tP7C+kLnPLaF827P+h9vzmv17bUgURONJfNnvagDlxvUdg79FfVgfzAnzt209SJGPE4+jjm/4xyzd5weDBZ5+GMeOj44Fjd/X+PFH/+0rzu3OXCx60/1OebBHJBPzgPjJXKIZSn6jtsgsexF22ffFuWvE+N3ftsieKzII+JFm54aoR0DiRe1iHkllp+oWdQj6hZ1YN0in2i7m9QkzXeol88b/u95MSfMAZFT5D63vJATcou857d+nW15Hi44t+VJ1g35eQu0CVaA2wPRnsiJjxHLGdsRbXhilnvzinZFnHi8aFeMAfbnBjIWsG04a7/EnJH7JtrFesU4ieU7ueCH+3gh40hziVrCf6Q8/8qx9tyW1+shF77ff2btue/3LzTHyv9ADnm8cN8BcwhipZxrcV3XHr+E4ItfTnQ+RK794eVE9zWiPbluGt++Bvd9IiduP8/9Ofb32yuyvxOx4vGiHRFDa39+jWhPxIi2Rc4LHxNsc92aC9t/X0zOK/8HOUW8+QLyXkzO46vPP9/F9vO51bgfw+OYH942JQRf/DwqWP3DeS42x4zV+Dzs3LcXuG+j5/r6rEYXMWIZibziuAjXV7ru4bZAuHjc2Z//iW2YaJvWdCIf2jiPbYGow0DqOVst2J/n8kU9ot0ffizmWUNiRA7sBz2PKfpBj7FFPbSfOKdoP6d5+onzDvsLuc6tz55tINYg4s6/hki/Gs5vzDG/+J7uK+V9x9FVOM9wTmjPB9EHeT48s+rC5gM+ltYm+i9c7F9XrfI/thJ14L4h7iK3J1NWnfvz8vPJc7bjgYhVUPd5rNsXc47t++W58sfpm5xn1Y+U52xjOHXlxY3h+fTLvPK/v387sULkEnnPbz9wMTn3rLiwfuJzzsRA/3VY5BG5NwSKtkQ7WAeeq4DH5PnXIOoXdb2fd7Ztxf9vrpUr/rv5Us8hn3xeKmyF1nmp/2xtFXk/XFsC3H9muaI0wHUbXOV5PHe5J/5xaZ+Bc188plT0g5xLU6U+OZbjeRGsXfRTmufE6H5J5BGPwXrltr9b5mn7cek8JbQNtYg82uss5pKfy2I78vPZg8uwTZHPuy89h20CnieSjzvKl9GaadvYLh2X829/0Xm2j+3hzzj+dOzlMUnB8Zee35N8mEerfdgO8jl6/wdycO23LP1x23/iPNrnljGdm/KyXrpUtPXD+xJ5WzRpqfa2iM4djMN6xWPpc4LQpVrz9OzrSqrG9gS3JapGLR+6RD2YC7d9WJfIcXHL6inXuS8rfH7BPbegy2OFS/tYHWvCtk9cYP1XnEf9F9J+2I/c/pElP277z/zI7f+Ybef/yLVP/ZHbjzyP9vFYQTwG1x/xmCWLYY4sFnG4naHrEuY=
*/