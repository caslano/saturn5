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
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
*/