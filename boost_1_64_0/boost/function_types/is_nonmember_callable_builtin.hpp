
// (C) Copyright Tobias Schwinger
//
// Use modification and distribution are subject to the boost Software License,
// Version 1.0. (See http://www.boost.org/LICENSE_1_0.txt).

//------------------------------------------------------------------------------

#ifndef BOOST_FT_IS_NONMEMBER_CALLABLE_BUILTIN_HPP_INCLUDED
#define BOOST_FT_IS_NONMEMBER_CALLABLE_BUILTIN_HPP_INCLUDED

#include <boost/mpl/aux_/lambda_support.hpp>

#include <boost/function_types/components.hpp>

namespace boost 
{ 
  namespace function_types 
  {
    template< typename T, typename Tag = null_tag > 
    struct is_nonmember_callable_builtin
      : function_types::represents
        < function_types::components<T>
        , function_types::tag<Tag,detail::nonmember_callable_builtin_tag> 
        >
    { 
      BOOST_MPL_AUX_LAMBDA_SUPPORT(2,is_nonmember_callable_builtin,(T,Tag))
    };
  }
} 

#endif 


/* is_nonmember_callable_builtin.hpp
mm0k6ItOQNs0EV7YfRmRd5ZDfV49HVQxINHEL6gTyqb5Ea1E5vu4mHILJpzbzIpm/4bcDCWyKTpJK0JSSHigGBlaE7mqbBXFHS4gVwk3XD8cTN4LHWi04C44GsfgRvVZGibkRWox8qR1az55nrrBLYSyIBS9CsafKxBq+pKJx+qg0VidCuJ1SSNDi13ZM5dcwxvQ2SvIz14nk/+az/R+8xg264MyXX9RS5/cf1NVVTplPP1J/xIiKGeBFC4+eMIzdgnetE0PSW54NoLL9pKpgNsbuusyqSlPwYbbcvkPI9DcLoyF8iU4J1LD1yyKgX7DNubyLBM8ezeL708gi5up3HzIfnpovoHW2hrQuhWevGeeDmy7TvKesD00Z2ER19zTjvDESNrRPRkHlBgo5RkdeijO47Q8cex7F0w3LIf2Ojc6luMI16HJqOsugdeUefz6zFmICXJiqncP0NGH37ChUIyEZHPZrG9l2DqtnKmaOVCejDyP7cjBpRnHWUdOCEynpdHKrfcEmnwCP318Ff28pkgabyPxSuoIqYoXQKZ+EjvhfBFHxqfg3a1AfPbbiIctD+lZcwXZTn9C6uPPkWyWCamqRPErc3txb38dDPOFIbf6P/5eypMe/9PmJWwnBTlyqr4zEZ//lTFNkSmC/tRveH5UgX1EEZw0i+Gw8ROfOj6demwX0yN/SUqfpEZbTCSxbsCGGpTz6EVlAZWMiYGttyWb3bIEfOQ7ss1cTq7Zf7nhPg20PsliqaudqCg+iuY7PCZ34ygE3VlA4SOHUlijKQWdtebL2maRhfIi2h/ZgSurOEYECPSLnQH/dfMsVibr8iT3XBLXnorXO5QpxDKJriCXQrgzNZjeJY/KXkiMrccpXTf+QlaU1GoLoFqqhzaKxJBiUdQuqBb0CX6TxeIPrPvREFLYGcla5p2jrJYaLJm/jA6MvIGknVcwscUG1ttPINfkEsUY2KN/YwSb1NZCoeO3ca2R2QibPo2nh/6iplJjliDITd7GXcNvrXac/zaUrazSwgvn9ezwr0LSSbgGI/nrZKg/hUt8daDz9uO5xwRvejhGk0LfLsWHuLcoOvoFMxPEKHSZBS1ecp0CtS7R3P0h9OPSNSreqsBfjCqBrY05vzImDA3pNQj8Nkegk8fzNRMUaPQKcz5xcS6StPtYikgXondfpk1GPuRZV8Ey4zwFObI1VJ20qLL5L1z3n8MMSXd+WvUbvLdcglfLZZJdlwHhPxqUXt3FJF42UVf+Huxzzse1bwYYL5pM19lP5F1ehkO9JaRa6yfwIyJMcZ4ojHQEGZ+gR+1xeB6tCxhNJWYJPFh6DSrrB/mh/Y/p0lIVXp0kQ9dJi4UHd2PQdzsWrm+GSk4dKSSq0fUSNypSrCOJvkdsyIjddONlH918v5v28tdkoD0UyQm7mVXQX9IZcR1DzkbR4aFf0V3BIKk4iWbfNoBmSA/7q/sQeVOEyNDxPOXcHsuaFuuS+/xL3HtoJFY+SIDs4EFst97OBmq2wGpnHk330ISkjgtuL+ii7wnD6OFzIqbjxT8/a8Huwa8UpOiAgUkbmSok4W56jUltm0xVZTo4YH4SWuZxJHIyBWOfivHBsz2CfFKFb/gB6jPTI9t6f6SJEhseWYSC07lse/kbeJVbojakDtJK8fy1YxlmHwrgFUkusFqgy47c/A6xFSk0b7lAB1g+o4aCJJotfJ4SbEvpd0YwJqlfpabDMlx+dyEke0LJ96swPHy/sI06NujwmkLCjtpYvV+guZylcGmcMX95+yudfqKFyuIkar5cyoVOp+FIUgabKKZAD/cYQm1LGHkoCP6T3PAhyUf+rL51AqYeuUcx/+JpbeAH7jk=
*/