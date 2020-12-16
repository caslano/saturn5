// (C) Copyright 2008 CodeRage, LLC (turkanis at coderage dot com)
// (C) Copyright 2003-2007 Jonathan Turkanis
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

#ifndef BOOST_IOSTREAMS_FILTERING_STREAMBUF_HPP_INCLUDED
#define BOOST_IOSTREAMS_FILTERING_STREAMBUF_HPP_INCLUDED

#if defined(_MSC_VER)
# pragma once
#endif              

#include <exception>
#include <memory>                               // allocator.
#include <boost/iostreams/chain.hpp>
#include <boost/iostreams/detail/access_control.hpp>
#include <boost/iostreams/detail/char_traits.hpp>
#include <boost/iostreams/detail/push.hpp>
#include <boost/iostreams/detail/streambuf.hpp> // pubsync.
#include <boost/iostreams/detail/streambuf/chainbuf.hpp>
#include <boost/mpl/if.hpp>                    

namespace boost { namespace iostreams {

//
// Macro: BOOST_IOSTREAMS_DEFINE_FILTERBUF(name_, chain_type_, default_char_)
// Description: Defines a template derived from std::basic_streambuf which uses
//      a chain to perform i/o. The template has the following parameters:
//      Ch - The character type.
//      Tr - The character traits type.
//      Alloc - The allocator type.
//      Access - Indicates accessibility of the chain interface; must be either
//          public_ or protected_; defaults to public_.
//
#define BOOST_IOSTREAMS_DEFINE_FILTER_STREAMBUF(name_, chain_type_, default_char_) \
    template< typename Mode, \
              typename Ch = default_char_, \
              typename Tr = BOOST_IOSTREAMS_CHAR_TRAITS(Ch), \
              typename Alloc = std::allocator<Ch>, \
              typename Access = public_ > \
    class name_ : public boost::iostreams::detail::chainbuf< \
                             chain_type_<Mode, Ch, Tr, Alloc>, Mode, Access \
                         > \
    { \
    public: \
        typedef Ch                                             char_type; \
        struct category \
            : Mode, closable_tag, streambuf_tag \
            { }; \
        BOOST_IOSTREAMS_STREAMBUF_TYPEDEFS(Tr) \
        typedef Mode                                           mode; \
        typedef chain_type_<Mode, Ch, Tr, Alloc>               chain_type; \
        name_() { } \
        BOOST_IOSTREAMS_DEFINE_PUSH_CONSTRUCTOR(name_, mode, Ch, push_impl) \
        ~name_() { if (this->is_complete()) this->BOOST_IOSTREAMS_PUBSYNC(); } \
    }; \
    /**/ 
BOOST_IOSTREAMS_DEFINE_FILTER_STREAMBUF(filtering_streambuf, boost::iostreams::chain, char)
BOOST_IOSTREAMS_DEFINE_FILTER_STREAMBUF(filtering_wstreambuf, boost::iostreams::chain, wchar_t)

typedef filtering_streambuf<input>    filtering_istreambuf;
typedef filtering_streambuf<output>   filtering_ostreambuf;
typedef filtering_wstreambuf<input>   filtering_wistreambuf;
typedef filtering_wstreambuf<output>  filtering_wostreambuf;

} } // End namespaces iostreams, boost.

#endif // #ifndef BOOST_IOSTREAMS_FILTERING_STREAMBUF_HPP_INCLUDED

/* filtering_streambuf.hpp
KHcb5iBu1VoBzS3qd8xfiFc19/7Lm2ctSNt4Mf3hXgm1Wjfe8J85f1HbKBPUeYv1A8G4THnGe0iH3sH1A6d9cxQ+4zM+4zM+4zM+4zM+4zP/0ebOyf/9B9wq+b886//N6//Lw+oMhuyYZJL/8ehi6f+TiiH7JxVD9k8qhuyfVAzZP8lSnreW/ZPyrSuogLys+J8m0xdTfq9L8vu0ZlE1l3RQzyvnAsRj417u8J8pvzfUy4DragTXuViL9f8OluNDwbA7KMf7nfbJ8T7jMz7jMz7jMz7jMz7jM/+L5nbv/6fL/7dC9g/BfnRhkCEjsHmoLLp0QXA0HxBjOhPwmo3P/PX3ngnXEfTgnpzmN+YD0tIpdqa9ATON/fU/JX+9JN6jmu9ra5ofYDfTWWLYW9DYq/zZDnR2t/W3As2t5X99D/MDdH0V7R/tZ/h/3jyHYA6D95AeH6/9q+8VHXovnfvikZHDoWK7R09XLLlv8+j70cfQ7/OeG+FkxdFeipyOhBba9X5+VUQi9uGNwh6fieJtKUL8Co6Ro8RfcNZ3cyVCTFESxRUlVCSoiWKXGiEctkQx2RYl3gdb2yPEn+yJOC8lSrRxtBL7cIpUCWeimO2MEp+APVwRYrGrrQhyR4mu7kRx1B0hynkSxWJPtPgGbMdpCqG4HPNUQ0zipdfEP6QVOKHrNTFNWSHqq28Ll22F2GH7s3jMvka0c7wmwpwrxF7na2Kpa4VIdr8mynuep7BCtT10KawDnjLiLPZBXS8uSGvEK/J6MU5ZLuLU18U1dbl4w7ZeTLUvFw0cm4XTuVxsd64Xj7ueE23d60WoZ40I4fLpT2FNQugDjTNYSlP5XzGXTx3t35qclktUfndR+ZTF+S2KPFp6TBktBdpGS0/aH5RKO0dLz7lGSwEc35kU3ixjz3QXPdPtbwq/Lu1/wXtOnqZybeIqiVNon5VGSRWVUdJL6iipln2U9LpjlBTC5RtG4YShPjuMs0Lm07MSjDMMqpCfs36mZ1Ed0f1/Sv4jjTMHj5H/KgJpM86vCKT4vO/R80yl34F+A0Wm21T36Cz7dpyGHymc9dgH/Rj2/N0u3pM2iYfl7aK1skko6nbxsbpJPGbbLrrYN4lAx3ZxyLFJzHduF6muTTin4gNx2r3FqDvjKKzSfpPEn7D/9VhRVU4Xx+WxYoOSLoaqY0U9W7q4YBsr3rani3GOsaK5M11cc44Vu1zpYqp7rEj0jBBTOX0nqOza+T2FHZgXS8niqhSOE5mSxQeyQ5RTksUj2B3/DJioOsQaNVnYcNpDhi1ZfGZz4CSgZPG43U9cBlMcDvGqI1kEO8PFQ85k8bXTIRq4knGSU4iQ3ckize0Q74BlkGuzPN3E9x4Hzc/5FWE/d5qfo/7MPDeXZvm9j/m8yboe634zo7PpO6qRhfebU8hfT+439fvamPtNdrPuN+9PLbTf5PsK7zdndM7Tb7L/54ww2O2m/eb2LrgOr95+c4fRb35J7jlGv7mffv9QaL95lp7T/9/Sby5Bv/mtqd98j+Jy/A/0m6uMfrMFpfuLP9BvvmD0m8EU1kN5+s2P+ty831zVuXj9ZoPUvP3mFrrfU2i/ubBr0frNHZ0L9pv3pebtN78gP+cK7TenpObtN5/uUrDffJfcthv95mv0Owj9Zlah/eZK8rPhd/abu8R3pn4zhsKK+t395v2mfnMe5Uf7O9xvJovzd6DfxD7qZGa4ERY4FYyA3+gBN/rNzPSs1GHpExCW3m+O6fcgHMxnO8eT/8e4vur3TzH1n+zGfVi4qR/Uy+wSXd/kaiW6ix9wIs3LUh2cHdZdnJHriNlKHVFNrSN2qI3EUFsd4bbXETPsvUSsI10=
*/