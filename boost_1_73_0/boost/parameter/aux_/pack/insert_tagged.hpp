// Copyright David Abrahams, Daniel Wallin 2003.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PARAMETER_AUX_PACK_INSERT_TAGGED_HPP
#define BOOST_PARAMETER_AUX_PACK_INSERT_TAGGED_HPP

#include <boost/parameter/aux_/set.hpp>

namespace boost { namespace parameter { namespace aux {

    // Inserts Tagged::key_type into the UserArgs set.
    // Extra indirection to lazily evaluate Tagged::key_type.
    template <typename UsedArgs, typename Tagged>
    struct insert_tagged
      : ::boost::parameter::aux::insert_<UsedArgs,typename Tagged::key_type>
    {
    };
}}} // namespace boost::parameter::aux

#endif  // include guard


/* insert_tagged.hpp
bDntqPc8djQ3lYv5cyE631WmxnMiMZ4XifHcSIznR2I8RxLjeZIYz5XEeL4kxnMmMTlv8q7HOnU93qnrOZS6nkep67mUenyOx3t8jsd7fI7He3yOx28PPQ6r67FYXY/H6vE5Hu/xOR7v8Tke7/E5Hu/xOR7v8Tke7/E5Ht/X4nM83uNzPN7jczze43M83uNzPN7jczze43M83uNzPN7jczze43M8fj/Scz11fdedur7vTl3f
*/