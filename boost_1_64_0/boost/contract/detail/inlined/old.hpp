
#ifndef BOOST_CONTRACT_DETAIL_INLINED_OLD_HPP_
#define BOOST_CONTRACT_DETAIL_INLINED_OLD_HPP_

// Copyright (C) 2008-2018 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0 (see accompanying
// file LICENSE_1_0.txt or a copy at http://www.boost.org/LICENSE_1_0.txt).
// See: http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

// IMPORTANT: Do NOT use config macros BOOST_CONTRACT_... in this file so lib
// .cpp does not need recompiling if config changes (recompile only user code).

#include <boost/contract/old.hpp>
#include <boost/contract/detail/declspec.hpp>

namespace boost { namespace contract {

BOOST_CONTRACT_DETAIL_DECLINLINE
old_value null_old() { return old_value(); }

BOOST_CONTRACT_DETAIL_DECLINLINE
old_pointer make_old(old_value const& old) {
    return old_pointer(0, old);
}

BOOST_CONTRACT_DETAIL_DECLINLINE
old_pointer make_old(virtual_* v, old_value const& old) {
    return old_pointer(v, old);
}

} } // namespacd

#endif // #include guard


/* old.hpp
bM3L9G0v7WGX6zAfUe+wd8iLrUCHTU2wRRJ6KGIHOgO5TySv2zDOMdHuLxd4xEHmYTrpNtjqxWLGhzx/2AubdjG26Wl0+GXo6M7UAf/eiVw9jc4uQJ7fWY5NHmKLt2tin6HVtBasHVJHPmPcE4Feou6U9uhncNpzbcCAyHlv+tcTHPjE35DVSdjm+9Dn4bSbTGzqDGw/fLftGiFisIM/ggEzR8E/i5HfWugr9ED0IHQLf3+4nD1hs5jjC2jzA0tEglc30Kc+pzMnS6in3BZXoDseeYpbtqWtho8unckeReQ5F1omPoHtHQEux1aNxyY3iENngNs82MTspjbvWeLx2z3ik/fh0dn0Ed2+ZixnsF6GZu+gf9Br71Zim1PAPiOh4efI1WRoRpux+A09sPEFA8BYt1niI/DxlrHo9H3w2UBLvAauD0c3zUf/xcxgzvKQ4RrI963kY9fGMtbFj6MLs8Cscy2xCSz2BbrhVsa6h/mYngBNeoPTRnvE5RjCscPh7bXojGYecdEn6II29LMJvoMsUwc+P+wR8xvxDYbX+KYHui4N2hS2gZ/Q2XlgySPglkE3CnH5QvqOHV8WgX5YyjezRkKHz9CNA+FrdEQOPDn7KvZ9omPOeQKZhp/av8H5iAuxax9ho9BbPcCOhXego6diP8DAH4H1epFeUNvvI5WnW2JuFGfS/sq+OuiYBH2uxed45xniB7uZZ+x2Im1mn48uRJe2+A6/pSW2G/vXaQi+C/avtgW/NMSXKGRP9Tb24oOzrNY2GM0jfkbmLz5qi68fpI8NSP/RFpd6wMzojIruxCOgy63p2Of5Fhfq4Gtcgjw8CN44DPaDzm8eQQ8z/7dUglvAZdcytlaHwPuNqWcfZ3/fJG0mc33AEqOY83FgkHzw7vMt4S/m53704w8VYFsPura/LRYh/613gT/AsKdBq/PBJIPAGu3gyTYveMTQBbboYtniDXRIcrRHjIC/Xj3oEfUWsZ/rXDApfsUX8HXnYvb908+S68C6zcCSMxnDM7aoL2mNP3H5FnDj93yzrwdywVgj5FlE5v7DNI8Ydp1H9P0GfOMDo5bjZ96GzcEXenIvfkBzaA6dPppjqXu63ngN+cdvKWyBPjoEdmFso3/gbMtsxrYH/U8f3z3MPUmbPOJZLz4LtuGv+CLFZ0DDprRXA78N2/zxdmS1nhB3V8JLO9C5yNdzn1riLymclUHHvQR/2Enw9W74qw16lvo33ouexuY9OBr9lA8mKBUiDSyxai7j/oA2cjxi6UhLVF6P3aVM8cNgCezOjSmWOP0QODEBeVhEGnq9nD69/iD4DTzTAJ8p805w07PohDtt0Rxe+/YxS3wJtk6AzsNzwB7QJGMktuNcaAXunhiPrhDgAfirB3I2vivv/QOduxpZQx9MsNA19+MzoavaDWePHn7vkOvxYbBr/T+mrbngNZ53EwOIexI+nc5e/ifQnVPYsXMRfbuPvLMs8Q1jEJQ5B712sA9juQh7T3sdKsCHYNQzc2yxGtp14v9Ng7GrZeA43n+6AeNKY/7w+TvBSzf81RIr8bWXj8Nvw6ZcEwl/7kFWX8Z2v4D/fD+6pQ7fVfCCFTczJ9iDZ/BzfgaPH0BGlz0NHpqEn7nMIxYeRMfcYokM+pvA75bw10O8V9kc+1OMnQW3F93C3NTHTnwCHY4wz/D6vWuJs+P7vxUJvp9F+8je1heZ1/WW+PwpxnsuMc0C9O9ybMXD9D2bfmVgv561xPOf4+f9yrr+Qxb2Bd3fFL8SGq0BZ8dVgEOh9cvoxcaPIVcd0AGZ2Ol52Mty+BDfOrUp/a4FjZ+HRz3olzTsL/xyIzi7RjZyOIT6hlniEuz6bGQ=
*/