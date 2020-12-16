/*-----------------------------------------------------------------------------+
Copyright (c) 2007-2009: Joachim Faulhaber
+------------------------------------------------------------------------------+
Copyright (c) 1999-2006: Cortex Software GmbH, Kantstrasse 57, Berlin
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
    Macro definitions for some useful notations e.g. iteration headers
-----------------------------------------------------------------------------*/
#ifndef  BOOST_ICL_DETAIL_NOTATE_HPP_JOFA_990119
#define  BOOST_ICL_DETAIL_NOTATE_HPP_JOFA_990119


// Iterations over stl or stl-compatible containers:
#define ICL_FORALL(type,iter,obj) for(type::iterator iter=(obj).begin(); (iter)!=(obj).end(); (iter)++)
#define ICL_const_FORALL(type,iter,obj) for(type::const_iterator iter=(obj).begin(); !((iter)==(obj).end()); (iter)++)

#define ICL_FORALL_THIS(iter) for(iterator iter=begin(); (iter)!=end(); (iter)++)
#define ICL_const_FORALL_THIS(iter) for(const_iterator iter=this->begin(); (iter)!=this->end(); (iter)++)

// Plain old array iteration (assuming member function VecT::size()!)
#define ICL_FORALL_VEC(idx, vec) for(int idx=0; idx<vec.size(); idx++)

namespace boost{namespace icl
{
    const int UNDEFINED_INDEX = -1;
}} // namespace icl boost


#endif // BOOST_ICL_DETAIL_NOTATE_HPP_JOFA_990119



/* notate.hpp
fIOWQ1I88imtOSt77WbbuPJpzs+aHN0DLcr+OWaUO+xU2qPSoyFCEn0HhryeqlE5ulf8qubmAtuW6iO6oE++1FGXfOa8EFaId3H0Pb0vpKXIF/1t4Et1RH8fP9afLxMTKXgtN9ifdpjctW9GiJmJNdMDj1JcTUpPlaRLF2t2x1gmMUG47ZRAdOOHx8MCI4WxTRx1B8k3H750d/0E20U/D9YtNgcLMtJ2TSv27DMUkDYiGd9Tb8TvJmtoIe0TQF25ibFrZwqPoOeerLT6o0c7+WcmWWv5TtKHDb0QoysfrWqgtrrUyhoRdSpEmTUs+R2NJforuGurFTW5WajbdO3Ky2qlBSHDw8wuzbf5fZfaUWnBjg+z4oB/XZVBSrMjo4z4gcKcF3bVGPpX8S/3MA96J+SuWh9ed3LD0ZPsORXRCh/zXvjsTi9bM1F1Jf7I4bFlvcbMMnrDEcdCGfQbardcqqeU8u2O2yYoOTaiuuGJq648wJ3owxSVZGRDLVly9x04T1xRyrSLkiGXL2ef4SuxctXaVp2rYRE4MriLD2e9zpuHznVJqJVdj3ZRypiNiBC78abWAWOS4XcJOrmlgcw8wfKKYDhLR9qUirpJhooTY0ktI6+cg2DqR590i0kehdu6VzH5i5TWUlu9YvJ8bijE1R0PyG5z0P27dpjTi4ndXy+S4rq3GVObXnbm4Zbye1XxmTuKazwr1x+Rtlv2Y/wROy/8miS7bWUyC61cOiVh9NHaOxX/aPxp5njafdXclbs/c6Wt3ek3aStkZPMYnDoMPuZVD/aqBymNdwU6Pxi6F9/gc9HZU410p71fG6tzxXCI48YqAapt4+OlB8KHvC53rVnat+WlAq7OSMUYteevxH4WN285O6lIdZUF3aowP79rvYCJLflJ4X+UN8fqbTdkzMibCpS2FTff22FV8MSG27XdmSGcPzAK7pix5gZtZjBNbN14cOfHwxxJTCnS51dx2PpultBQ76xwcW+cTU1oClA7r1yKliDE5qFYo7zS8U8Kw3RLea9f4N2/5YrVaNWKhoZS/+DDxyOtZsRZwveib/hzPhIAAP6c/5ul866Y25bOsXjFh08Nj9L7N3mffylyOZx1c7B19I3jgtSr5lK2dp6LcmuWqLLb+GGW/OZjU5Nt8ryfa7dsvVpYEv7+bf8Q9Z5iDwXDJoPlOdsNy5yYWjlcZebvh5KMFf8wbpbFyew9yd6f2/R54pJPLf9Rr7dXMAayZQakTVsi09M29mTfPznA8K/oZb33gpO4iVsN3r4yfZQrU/6j6VWNHNJDIW81D+0XEZQuWdYRy+ulx3aPvcYii4ffZWvn+ISJSc67L7FVooO7Me7+l+9o7rK558xjHaVR4tnlRl0ek1ac4ehgf/XScSMBHhS83aUc+IS+QZr9mimb7Y96hfv6MSThkt4V1NEBMbnH/R/X56F/RS9uE/I5AVEHw0uT90mfFujmr+DGSJ6kxTJ2VK+54C7n6FR8mKnm6IMHYH78ZN6dDjWDhwNWNTOGl+7pWg6ZMVAOxCfJrKC4xmq08SKH5xbPB/0HPaIOpJcw9X1wm/hh3NQ97xXLzpKHbVVm365vr7eoF9vi93NqE1XMINkxF4egXrpTPJVR2RHJCCG0UAw/W9f+Tvm82R2p54WyxwbL3tcaBaTFXLNnpShtNij9tKV1qxzvIysNV8a28V5BpR0z1wbe2J5WGA8kDY8Sei+RM5kro/o87UaKTp/Sa3zt3ozDg+93hq3KYtjYKmHiKmbRer9CwWlzvd4UQggtHfPawNzFAsasAxNXm27M23LrLf3eaBaJTi0nOazl7OHo5G+t589P5hMkf+llmEC9TZ+FQ2RA3UU=
*/