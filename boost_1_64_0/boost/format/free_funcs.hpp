// ----------------------------------------------------------------------------
// free_funcs.hpp :  implementation of the free functions of boost::format
// ----------------------------------------------------------------------------

//  Copyright Samuel Krempp 2003. Use, modification, and distribution are
//  subject to the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org/libs/format for library home page

// ----------------------------------------------------------------------------

#ifndef BOOST_FORMAT_FUNCS_HPP
#define BOOST_FORMAT_FUNCS_HPP

#include <boost/format/format_class.hpp>
#include <boost/throw_exception.hpp>

namespace boost {

    template<class Ch, class Tr, class Alloc> inline 
    std::basic_string<Ch, Tr, Alloc> str(const basic_format<Ch, Tr, Alloc>& f) {
        // adds up all pieces of strings and converted items, and return the formatted string
        return f.str();
    }
    namespace io {
         using ::boost::str; // keep compatibility with when it was defined in this N.S.
    }   // - namespace io

#ifndef  BOOST_NO_TEMPLATE_STD_STREAM
        template<class Ch, class Tr, class Alloc>
        std::basic_ostream<Ch, Tr> & 
        operator<<( std::basic_ostream<Ch, Tr> & os,
                    const basic_format<Ch, Tr, Alloc>& f)
#else
        template<class Ch, class Tr, class Alloc>
        std::ostream & 
        operator<<( std::ostream & os,
                    const basic_format<Ch, Tr, Alloc>& f)
#endif
        // effect: "return os << str(f);" but we can do it faster
    {
        typedef boost::basic_format<Ch, Tr, Alloc>   format_t;
        if(f.items_.size()==0) 
            os << f.prefix_;
        else {
            if(f.cur_arg_ < f.num_args_)
                if( f.exceptions() & io::too_few_args_bit )
                    // not enough variables supplied
                    boost::throw_exception(io::too_few_args(f.cur_arg_, f.num_args_)); 
            if(f.style_ & format_t::special_needs) 
                os << f.str();
            else {
                // else we dont have to count chars output, so we dump directly to os :
                os << f.prefix_;
                for(unsigned long i=0; i<f.items_.size(); ++i) {
                    const typename format_t::format_item_t& item = f.items_[i];
                    os << item.res_;
                    os << item.appendix_;
                }
            }
        }
        f.dumped_=true;
        return os;
    }

} // namespace boost


#endif // BOOST_FORMAT_FUNCS_HPP

/* free_funcs.hpp
b7sfUoE8Q8SiDyGlT2CHl3B0Lc7dX9RoYicxZVB2rTo5ZnuYIZOF6oMGqkD7MIm5IMQuCYs1a1z/uAKQ65vZT/MgKWXPqHpRM5AuyVzebxzLoKLSgp+3m4r36YkfvB2LcfEB2iq+Qyo7n2gWsED31yMo9aFnaLqZlT24ZA94YshOAXmhAbJTjJgTIeMraSHUCdjMnXvAdFhQvTbPeTutGr+Q+mYnPYFEk2SpMwFsYHKwdnea6KM0xRFPi182SDolDOZut4m/bZ8YeZDzIOXMxaA3sCR2WHApl1le4XOqK3xOMwNxIj9FEGZ1GKgdz2RMdyKRfpRVyGey3c9Eps6j/OopaFuXIgtq+yMfN1dGn2hAruIsTomKieYq2jh2flLI+LkLc0PGu6vIP3Jhasj41PnzQsb3WDRO9Cu09DqDx0MWIgCbZla34ILuEhZuJrqz4HvCWbrvYCxOthgCtc+OTWWov9CHkB8MQSxKLTiTDaomt8hy1kA0KnrhASAtZNH2BY0V1swk55qtVB1GJFesA26Egs+ja1mgPgfXfzsZdwH8+Fsy5aGzK056o2JGIQ8qT8oeLKLMx1n7lZkE26sNTPe8rMqM+vu+1iXfYpuYwnlS7mmY6lyVkGDyFKqcy4P1hWLyM5YerY2/sr5mdQC7yoPZxMzpxKQ4yropXxPIx4cibo5ya2LH3lCaH1Bu2YuEnHVWKzWN5/aPMmiv/XYg1iRqx1VHSV+Qt8HHMBevSlKRaIvRfmJaiAXOw8tUISWIr5Fz8Se48Ab/i1um8Md8tf9lrEzhZaGl/6W9N4mPWoYMHbx80XfGJbEhdzF/vFW/0IfmbolDHmNXxX2RBuYhYs3aOFSdghFpDEP1FsTBhaodwP6At3vS6e0xeAvvLua56ZFOfQz0iJydySQ13mlRysPfZMATiVTCYzgE6k/5iYvdbr5j2vtsATqcjNF+7gSkju04vKFcUtafjQxSYs8Ux70Ladr97YM8Doe2fyChbxbQNxH0tfC2rHdeBsR5O+y1jcYH/ggS3VBvXD7WcMNV1LtD+mDMWIzpd1X4lyq5/q9cov7frsH6OwC8bS6EdxnCG5pJNRynOnUvxPSBmL22NyEzDmSY56vFXEmXwzBbeoMYR3usAx7/bRu95HX3HvjDe/NMAEq5rsRcExMo1zzOlU+5bMLLZeIwQIFpxDNOsjG+/CcTJWSohHXxnHAEGQh2ZfP/044c/Rp36JetZcKvN3DCE5zQqIFMaGrlhLWcUCdOJmR2wQTvQqj2QL6sVvNQ5M0QuUtFxmAkX+ts0VUW10GcIK51fqcidwMfW1zrrBgq6eBNcOQQ1zpftcicv1wu1FRjtafPiOXDB2RFnBuq1U4lo0qsrRM84w+iO2P0DYMpurmI7rIr3PlysX8G+3dXSc59dh/FuU/NwI8KVOu+uTHKtJMNziBV/jAo75BZdrwLC0mlFnKwPVzIzZDXXH5dOObjxPzvTXXriQ/ujjWh4wXpvu+88rTHuSTuSzBZWX3CA8pRWYgmShOwg6V9nDK1Vz0rKGR3SSsb20MYFYUVP2ypfMXgNmKDibXNaQQ4iAB627NeeVmGEAW7S9ox0CgAymmWIcJnoa+nu7QjpEKXVoyMEhy1ccQRBay1b0EG4i7pzMX3jZTFdw++VC6l/f7Wgzp2cLqySUUEQe/LYPvQC1q4S5ubCf02iP5kRH88GckHBSyUh0VAxyZ+3StGjMUVbUSHlpqJXkjYE4trC3T1o00ChLUI2cmQD94AkBcryBU/E+RrIpRJkRRyvLHP4HgjLv6O4xa/443135Wj440VCSnseEPp1ji1th2Zlqr4CvLDBDEkfQ8rFSXtt7COWZ4=
*/