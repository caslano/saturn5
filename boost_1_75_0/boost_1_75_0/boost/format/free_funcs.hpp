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
WuktHeBA7L+zp7blS+fZdvhv6akeQlpTlomRDEo0OhYS6XSQ/vmyTLUJ1CRq0IFq/paWtwh3UQUZHKIM3FZwVr+tjEdwsH8cw0RDy0T4gp//gQajZas1q21bHsSB3NXFcaFuuuSsMcFdnd9DaeIl5W3v/Z0rad5JWCy5Y+3yXtizXATIx/JRDp6g0WYB2jaO4bS13OrkK3ZOFS3IrQPezTJQtVNP1U4DVe9zg4Cra4V4GYqeBKRnr+oMIehJBXp6jwFUYiSo3Kku3c3akty6P7MtuvX7BUUNeooaDBQt4aYBVpJ4WdT7oKuVfd5pIqlI/qOo5jdL7d2JxNXO3FeHuA07jLzvjksE7EqCA4BUCVqqzVqqvpAK9xcACLMTiphY1ZcefNXL+LyYnchHHrxhswwlE0Ombq42nE+zQdn8DR/7Ji1L+snSVvIsv0ugNGAfQvA3h3b2wKEeFfmUH6k18Z1aW9CR2q78SG1RF0LMhoDS2UVsQMbY64ExaFnCbXRHvj8xIVUQOokfrtU5sk8YlamSBK+wUDp3O2CUCritDThL9Waw+CnryvsVXDMWjlz+yKSSmepTxv1J9PJF8yf5h+yoe1eS7IUS/Yvmoyn1RXVc14thCSjgItWLLBWGFSuu+dE1W7H6S3EJjIaf70rx4CMwqY8vExe1x0dqhtVaVmhx7JFi2mCkht7kP305HX6Er8i8OtCXfBkr0v/D
*/