#ifndef BOOST_ARCHIVE_BINARY_IARCHIVE_HPP
#define BOOST_ARCHIVE_BINARY_IARCHIVE_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// binary_iarchive.hpp

// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com .
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

#include <istream>
#include <boost/archive/binary_iarchive_impl.hpp>
#include <boost/archive/detail/register_archive.hpp>

#ifdef BOOST_MSVC
#  pragma warning(push)
#  pragma warning(disable : 4511 4512)
#endif

namespace boost {
namespace archive {

// do not derive from this class.  If you want to extend this functionality
// via inhertance, derived from binary_iarchive_impl instead.  This will
// preserve correct static polymorphism.
class BOOST_SYMBOL_VISIBLE binary_iarchive :
    public binary_iarchive_impl<
        boost::archive::binary_iarchive,
        std::istream::char_type,
        std::istream::traits_type
    >{
public:
    binary_iarchive(std::istream & is, unsigned int flags = 0) :
        binary_iarchive_impl<
            binary_iarchive, std::istream::char_type, std::istream::traits_type
        >(is, flags)
    {
        init(flags);
    }
    binary_iarchive(std::streambuf & bsb, unsigned int flags = 0) :
        binary_iarchive_impl<
            binary_iarchive, std::istream::char_type, std::istream::traits_type
        >(bsb, flags)
    {
        init(flags);
    }
};

} // namespace archive
} // namespace boost

// required by export
BOOST_SERIALIZATION_REGISTER_ARCHIVE(boost::archive::binary_iarchive)
BOOST_SERIALIZATION_USE_ARRAY_OPTIMIZATION(boost::archive::binary_iarchive)

#ifdef BOOST_MSVC
#pragma warning(pop)
#endif

#endif // BOOST_ARCHIVE_BINARY_IARCHIVE_HPP

/* binary_iarchive.hpp
PyKwgnbwLFCY2E65iWhEcafNbLD/+pPc+I3U+Jh61vnwpeN69MXA/6hEn+IJmFDe5ar9BPwZgEV/c8qE5h22TOjbhy0Tmhh2gRMaw4CCkInuSkPnsq7gOg44L7BPKwCI7Qinr2l0jfsj0wQxS62C4W8iXdgb0jH8NLpUcGD12DPc4cu4sfEX2thAAPqrm5WDrqPt79WGulSavBZ0xfxmJXPVjS+0alLZlRNlVi9XUSJ1viXdiNWl89v1zNNyK7PKkkCrsNG0byz75c69vF8e2wS5IwtSzHvxreO8RTofxBYZcHGpe/E+NWtt6V5sQU5Zb7qAEWDdzH6XKd7oJ4sTKUDMAnCCoD1lE/3/gKUX9lHyv2qGffE7R6OFv3c3ChX/s6rpT9WArxIK/jUTvtUxBb+nYSj5hwn/zhEFP6fhhflfTZGiosyhWJ5Yul0iM0vd3t+gIxSvkOjcqbXV7d2Cbu8kub1Ra2X55sHXuLJcjfD8UfJfNOf+EvZGvX9VMey1WxnjfaNBKP+3JvydBvzoUPBNTHhzPj2h4I/Hm/05rOBr2sOnDghqRH8ipdJ56kH0EYNVSTFYdDCVDhkmf2X/MIeX7LGwwnk1wsQbnPiZa0pPJ5VJgtwAKIFjD3AwENwV0DvZ9qVQgPXEX7mkA68lNWACTWO2YYpDCZy/UPEGKG5EVb3nnmLxIgGQJYQzc68Kg4YHdyIJnQDaQ9fCsaH1l8GtuVnNhvQ6MWVEuX0FbkhqYwnoma+puh2M9+BGBYDYB0w/DuPSg0jIkywF9A1B4AxruwsTjHZ7EQnSnEv2k3bdSGEJL9qlYYJf+WwXU6aPRYEI8F8Cqq8eVYYKUNVIVEVybrq694DZU/QgJlaZJ4wNWib8sTpZNvqflYP6j/3DbfQ/LfmNvygur/9pyV9qk9/Bkp9yqHx+giU/wSb/eCWL/59LbPQ/Lfndbdr/yJI/06b8DEt+mE15nyV/IJW36ofdBsy1zM5f0BWqlPY5q3prVYHflgNYbwvRBW1ETiZ5KiV+FKBEJISUKomrVHG4s7uiIQX+9ijtdF1/tKHQkErLbDDqpUeAKxykIDnc0DGbVyLSzTuZNUk1VUnXsxNfqPcQ+aWf3ilHezpry3T4Bk3E1VP+AK5mOqOEHiAQhCel0iFk+prEzevpTKlEgL5a+B6WUmkHfa+k3oFPgOnwt00qYAXw8v4eogK+DNYlO+DJJeHWRn3LQfRA4Q8x/h+OPtHr632s+r1SlBpFVxVdtowof7h6/+gluj7XoCO5PRfh/SNCn3+S35vjkVwVPkq9GhmQVse3Uopn/r2S0AygSvEsAVIHstNlPLBBf3wDTWPRqMAfqeSj5P+xxnvBAeM+cKA359f/iDXfOwz4wfVD3DeTBd6L+9iAX1I71P1nwEcOMuBHh4JvIvAM+OT28uct0pKvo6Iy8YFk+38dY+hSk6VPlbPGbeJrjn7PVVu/B2/9W4ytv/A4rZl467nRdIuxgTb+CBUiSHdul41PJovTJN7FzehDhjYY/MERkgaz2NaLzU/vn/3jMyEUabnGtI8I605OMNJakjZSYCn6408nGVWmttRLUV6qULaz5SbKXYLcg+T+C7XWh0i/Jklf3vFX16q58wyViwqf8oPiZazZlPVnibZxw2dy8dzAB2EFDoLpAANDMMeXf4uhQOcQ+yY+BotxDHbp7+PRl+2himlK/ItM2AECe68JG6tPAiwChtOR2b07GgqtUdh6e3aXOTJ5KqEZQNWR2VtfnDyFcSNFV/+hZ+W88nhG0oo+fS5aIek/YyOclknupFUj/OPdzDMfj8URVI2A4+cgg6eFYkAfNgeSLfpbGdrPjBmq7r9oi/8=
*/