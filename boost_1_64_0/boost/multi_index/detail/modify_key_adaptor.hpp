/* Copyright 2003-2013 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/multi_index for library home page.
 */

#ifndef BOOST_MULTI_INDEX_DETAIL_MODIFY_KEY_ADAPTOR_HPP
#define BOOST_MULTI_INDEX_DETAIL_MODIFY_KEY_ADAPTOR_HPP

#if defined(_MSC_VER)
#pragma once
#endif

namespace boost{

namespace multi_index{

namespace detail{

/* Functional adaptor to resolve modify_key as a call to modify.
 * Preferred over compose_f_gx and stuff cause it eliminates problems
 * with references to references, dealing with function pointers, etc.
 */

template<typename Fun,typename Value,typename KeyFromValue>
struct modify_key_adaptor
{

  modify_key_adaptor(Fun f_,KeyFromValue kfv_):f(f_),kfv(kfv_){}

  void operator()(Value& x)
  {
    f(kfv(x));
  }

private:
  Fun          f;
  KeyFromValue kfv;
};

} /* namespace multi_index::detail */

} /* namespace multi_index */

} /* namespace boost */

#endif

/* modify_key_adaptor.hpp
BuzxJxcY9ho3KGJgrGBcu8HE6p5uTO5E8UeLnAeoNhMRtL4FMtqICyNi9CFDXWvR4NGNEPVX19vCx8qL0VeCIKTW6guIq3nWuXxFlvkaFy2t6KXSZb2JB62FEZt1i5700RrA7++OXJUs6KRDgPnqgesxa3YhGfvN3n7ib7WOGjPPlvB7YmmO/V0gzuQvtCFULb1UcNBJeO1F+H7nwbvV7/F/+2Q5ntwtAucMCk2Esjwl+b8+GVDQ/LxSFRSHhX4+FPRbiqhcpRc3bPK1CUl+AvG23qjE6IeHX5wOg9k0Dxk5sqPHSOTBtuUb4u6KFslf7ZqisM7zUMd8EzuzacArHq/YagBZGxOxK5mjMqvO5ejLgCVR/br7m17e1klsp6YwAqayhMTYBf4Z7dwll7mfaX5f6FjPHlm2F/D+lfz9EIDbiQLgWCSwS3R2Iiu9k4Gkgj8S5Kd/u3Mg6Tz0zlSZE8zwL9Y6scW1GSZaRKw/vb97JSZ/csh7PJongyLinEGFya6Raui66K898l9m1iaPm4pJdtL4GxXLgxNDH1G0+C4DFaH6GZA9BOlpKQ==
*/