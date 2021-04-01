/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005 Eric Niebler

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_CONS_FWD_HPP_INCLUDED)
#define BOOST_FUSION_CONS_FWD_HPP_INCLUDED

namespace boost { namespace fusion
{
    struct nil_;
    #ifndef nil
    typedef nil_ nil;
    #endif

    template <typename Car, typename Cdr = nil_>
    struct cons;
}}

#endif


/* cons_fwd.hpp
13rMzt7dDxKnz5kkO/C2K4Wj5C/EN3+zsNXgwlfE38X6Bos3R1p+PmJWMXeN/w1c9+z184wKBpXTzk36DqTRjgv/cRXU2dXSTLiTUlpGfwb0uHYrhXbPaQSjAMTG4nPdtAnhkr8UnJ65JY5rze3dl8vkEsUVGOLtRvJ+TQpDamDygvWAizbwTZDsgsmEl97+6n0cnrKwVnRrr4/IysvjKO7H+gOunEdSnMqzMr4l/Doj09Xg5b9Pov5r3U2l3F9osXyBbH3kz57zTuIJ7LfWh4ITcHxdMDAfMTXT6Lj5/vE2WdIUcjINEGEpSQ3GqihMBIJkK38gDINEai1+oc3OL2kn6+022ukusyXB/lbzk68zFYORAOjCtbrgdCkpAQxOBSHsunnmQMSSkWYhha0ICpIjb16ZuRDxVMyzE2+Fs+sgIxwrDztpo+YvpEvMm762AE5No5bIIyo11fhmvND/h6sWgUlVeMgMm93KQ+cNY3TG/9bAdupp+Gd+X4gdBZV2utXbH8NsESN1BIu3jIy8N7RjDSpp9wF3XojP9K9iEL8ZsmzTmuFZfgUGbA==
*/