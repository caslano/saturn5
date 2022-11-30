// ----------------------------------------------------------------------------
//  feed_args.hpp :  functions for processing each argument 
//                      (feed, feed_manip, and distribute)
// ----------------------------------------------------------------------------

//  Copyright Samuel Krempp 2003. Use, modification, and distribution are
//  subject to the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org/libs/format for library home page

// ----------------------------------------------------------------------------

#ifndef BOOST_FORMAT_FEED_ARGS_HPP
#define BOOST_FORMAT_FEED_ARGS_HPP

#include <boost/config.hpp>
#include <boost/assert.hpp>
#include <boost/throw_exception.hpp>

#include <boost/format/format_class.hpp>
#include <boost/format/group.hpp>
#include <boost/format/detail/msvc_disambiguater.hpp>

namespace boost {
namespace io {
namespace detail {

    template<class Ch, class Tr, class Alloc>
    void mk_str( std::basic_string<Ch,Tr, Alloc> & res, 
                 const Ch * beg,
                 typename std::basic_string<Ch,Tr,Alloc>::size_type size,
                 std::streamsize w, 
                 const Ch fill_char,
                 std::ios_base::fmtflags f, 
                 const Ch prefix_space, // 0 if no space-padding
                 bool center) 
    // applies centered/left/right  padding  to the string  [beg, beg+size[
    // Effects : the result is placed in res.
    {
        typedef typename std::basic_string<Ch,Tr,Alloc>::size_type size_type;
        res.resize(0);
        if(w<=0 || static_cast<size_type>(w) <=size) {
            // no need to pad.
            res.reserve(size + !!prefix_space);
            if(prefix_space) 
              res.append(1, prefix_space);
            if (size)
              res.append(beg, size);
        }
        else { 
            std::streamsize n=static_cast<std::streamsize>(w-size-!!prefix_space);
            std::streamsize n_after = 0, n_before = 0; 
            res.reserve(static_cast<size_type>(w)); // allocate once for the 2 inserts
            if(center) 
                n_after = n/2, n_before = n - n_after; 
            else 
                if(f & std::ios_base::left)
                    n_after = n;
                else
                    n_before = n;
            // now make the res string :
            if(n_before) res.append(static_cast<size_type>(n_before), fill_char);
            if(prefix_space) 
              res.append(1, prefix_space);
            if (size)  
              res.append(beg, size);
            if(n_after) res.append(static_cast<size_type>(n_after), fill_char);
        }
    } // -mk_str(..) 


#if BOOST_WORKAROUND(__DECCXX_VER, BOOST_TESTED_AT(60590042))
// __DECCXX needs to be tricked to disambiguate this simple overload..
// the trick is in "boost/format/msvc_disambiguater.hpp"
  
    template< class Ch, class Tr, class T> inline
    void put_head (BOOST_IO_STD basic_ostream<Ch, Tr> & os, const T& x ) {
        disambiguater<Ch, Tr, T>::put_head(os, x, 1L);
    }
    template< class Ch, class Tr, class T> inline
    void put_last (BOOST_IO_STD basic_ostream<Ch, Tr> & os, const T& x ) {
        disambiguater<Ch, Tr, T>::put_last(os, x, 1L);
    }

#else  

    template< class Ch, class Tr, class T> inline
    void put_head (BOOST_IO_STD basic_ostream<Ch, Tr> &, const T& ) {
    }

    template< class Ch, class Tr, class T> inline
    void put_head( BOOST_IO_STD basic_ostream<Ch, Tr> & os, const group1<T>& x ) {
        os << group_head(x.a1_); // send the first N-1 items, not the last
    }

    template< class Ch, class Tr, class T> inline
    void put_last( BOOST_IO_STD basic_ostream<Ch, Tr> & os, const T& x ) {
        os << x ;
    }

    template< class Ch, class Tr, class T> inline
    void put_last( BOOST_IO_STD basic_ostream<Ch, Tr> & os, const group1<T>& x ) {
        os << group_last(x.a1_); // this selects the last element
    }

#ifndef BOOST_NO_OVERLOAD_FOR_NON_CONST 
    template< class Ch, class Tr, class T> inline
    void put_head( BOOST_IO_STD basic_ostream<Ch, Tr> &, T& ) {
    }

    template< class Ch, class Tr, class T> inline
    void put_last( BOOST_IO_STD basic_ostream<Ch, Tr> & os, T& x) {
        os << x ;
    }
#endif
#endif  // -__DECCXX workaround

    template< class Ch, class Tr, class T>
    void call_put_head(BOOST_IO_STD basic_ostream<Ch, Tr> & os, const void* x) {
        put_head(os, *(static_cast<T const *>(x)));
    }

    template< class Ch, class Tr, class T>
    void call_put_last(BOOST_IO_STD basic_ostream<Ch, Tr> & os, const void* x) {
        put_last(os, *(static_cast<T const *>(x)));
    }

    template< class Ch, class Tr>
    struct put_holder {
        template<class T>
        put_holder(T& t)
          : arg(&t),
            put_head(&call_put_head<Ch, Tr, T>),
            put_last(&call_put_last<Ch, Tr, T>)
        {}
        const void* arg;
        void (*put_head)(BOOST_IO_STD basic_ostream<Ch, Tr> & os, const void* x);
        void (*put_last)(BOOST_IO_STD basic_ostream<Ch, Tr> & os, const void* x);
    };
    
    template< class Ch, class Tr> inline
    void put_head( BOOST_IO_STD basic_ostream<Ch, Tr> & os, const put_holder<Ch, Tr>& t) {
        t.put_head(os, t.arg);
    }
    
    template< class Ch, class Tr> inline
    void put_last( BOOST_IO_STD basic_ostream<Ch, Tr> & os, const put_holder<Ch, Tr>& t) {
        t.put_last(os, t.arg);
    }


    template< class Ch, class Tr, class Alloc, class T> 
    void put( T x, 
              const format_item<Ch, Tr, Alloc>& specs, 
              typename basic_format<Ch, Tr, Alloc>::string_type& res, 
              typename basic_format<Ch, Tr, Alloc>::internal_streambuf_t & buf,
              io::detail::locale_t *loc_p = NULL)
    {
#ifdef BOOST_MSVC
       // If std::min<unsigned> or std::max<unsigned> are already instantiated
       // at this point then we get a blizzard of warning messages when we call
       // those templates with std::size_t as arguments.  Weird and very annoyning...
#pragma warning(push)
#pragma warning(disable:4267)
#endif
        // does the actual conversion of x, with given params, into a string
        // using the supplied stringbuf.

        typedef typename basic_format<Ch, Tr, Alloc>::string_type   string_type;
        typedef typename basic_format<Ch, Tr, Alloc>::format_item_t format_item_t;
        typedef typename string_type::size_type size_type;

        basic_oaltstringstream<Ch, Tr, Alloc>  oss( &buf);

#if !defined(BOOST_NO_STD_LOCALE)
        if(loc_p != NULL)
            oss.imbue(*loc_p);
#endif

        specs.fmtstate_.apply_on(oss, loc_p);

        // the stream format state can be modified by manipulators in the argument :
        put_head( oss, x );
        // in case x is a group, apply the manip part of it, 
        // in order to find width

        const std::ios_base::fmtflags fl=oss.flags();
        const bool internal = (fl & std::ios_base::internal) != 0;
        const std::streamsize w = oss.width();
        const bool two_stepped_padding= internal && (w!=0);
      
        res.resize(0);
        if(! two_stepped_padding) {
            if(w>0) // handle padding via mk_str, not natively in stream 
                oss.width(0);
            put_last( oss, x);
            const Ch * res_beg = buf.pbase();
            Ch prefix_space = 0;
            if(specs.pad_scheme_ & format_item_t::spacepad)
                if(buf.pcount()== 0 || 
                   (res_beg[0] !=oss.widen('+') && res_beg[0] !=oss.widen('-')  ))
                    prefix_space = oss.widen(' ');
            size_type res_size = (std::min)(
                (static_cast<size_type>((specs.truncate_ & (std::numeric_limits<size_type>::max)())) - !!prefix_space), 
                buf.pcount() );
            mk_str(res, res_beg, res_size, w, oss.fill(), fl, 
                   prefix_space, (specs.pad_scheme_ & format_item_t::centered) !=0 );
        }
        else  { // 2-stepped padding
            // internal can be implied by zeropad, or user-set.
            // left, right, and centered alignment overrule internal,
            // but spacepad or truncate might be mixed with internal (using manipulator)
            put_last( oss, x); // may pad
            const Ch * res_beg = buf.pbase();
            size_type res_size = buf.pcount();
            bool prefix_space=false;
            if(specs.pad_scheme_ & format_item_t::spacepad)
                if(buf.pcount()== 0 || 
                   (res_beg[0] !=oss.widen('+') && res_beg[0] !=oss.widen('-')  ))
                    prefix_space = true;
            if(res_size == static_cast<size_type>(w) && w<=specs.truncate_ && !prefix_space) {
                // okay, only one thing was printed and padded, so res is fine
                res.assign(res_beg, res_size);
            }
            else { //   length w exceeded
                // either it was multi-output with first output padding up all width..
                // either it was one big arg and we are fine.
                // Note that res_size<w is possible  (in case of bad user-defined formatting)
                res.assign(res_beg, res_size);
                res_beg=NULL;  // invalidate pointers.
                
                // make a new stream, to start re-formatting from scratch :
                buf.clear_buffer();
                basic_oaltstringstream<Ch, Tr, Alloc>  oss2( &buf);
                specs.fmtstate_.apply_on(oss2, loc_p);
                put_head( oss2, x );

                oss2.width(0);
                if(prefix_space)
                    oss2 << ' ';
                put_last(oss2, x );
                if(buf.pcount()==0 && specs.pad_scheme_ & format_item_t::spacepad) {
                    prefix_space =true;
                    oss2 << ' ';
                }
                // we now have the minimal-length output
                const Ch * tmp_beg = buf.pbase();
                size_type tmp_size = (std::min)(
                    (static_cast<size_type>(specs.truncate_ & (std::numeric_limits<size_type>::max)())),
                    buf.pcount());
                
                if(static_cast<size_type>(w) <= tmp_size) { 
                    // minimal length is already >= w, so no padding (cool!)
                        res.assign(tmp_beg, tmp_size);
                }
                else { // hum..  we need to pad (multi_output, or spacepad present)
                    //find where we should pad
                    size_type sz = (std::min)(res_size + (prefix_space ? 1 : 0), tmp_size);
                    size_type i = prefix_space;
                    for(; i<sz && tmp_beg[i] == res[i - (prefix_space ? 1 : 0)]; ++i) {}
                    if(i>=tmp_size) i=prefix_space;
                    res.assign(tmp_beg, i);
                                        std::streamsize d = w - static_cast<std::streamsize>(tmp_size);
                                        BOOST_ASSERT(d>0);
                    res.append(static_cast<size_type>( d ), oss2.fill());
                    res.append(tmp_beg+i, tmp_size-i);
                    BOOST_ASSERT(i+(tmp_size-i)+(std::max)(d,(std::streamsize)0) 
                                 == static_cast<size_type>(w));
                    BOOST_ASSERT(res.size() == static_cast<size_type>(w));
                }
            }
        }
        buf.clear_buffer();
#ifdef BOOST_MSVC
#pragma warning(pop)
#endif
    } // end- put(..)


    template< class Ch, class Tr, class Alloc, class T> 
    void distribute (basic_format<Ch,Tr, Alloc>& self, T x) {
        // call put(x, ..) on every occurrence of the current argument :
        if(self.cur_arg_ >= self.num_args_)  {
            if( self.exceptions() & too_many_args_bit )
                boost::throw_exception(too_many_args(self.cur_arg_, self.num_args_)); 
            else return;
        }
        for(unsigned long i=0; i < self.items_.size(); ++i) {
            if(self.items_[i].argN_ == self.cur_arg_) {
                put<Ch, Tr, Alloc, T> (x, self.items_[i], self.items_[i].res_, 
                                self.buf_, boost::get_pointer(self.loc_) );
            }
        }
    }

    template<class Ch, class Tr, class Alloc, class T> 
    basic_format<Ch, Tr, Alloc>&  
    feed_impl (basic_format<Ch,Tr, Alloc>& self, T x) {
        if(self.dumped_) self.clear();
        distribute<Ch, Tr, Alloc, T> (self, x);
        ++self.cur_arg_;
        if(self.bound_.size() != 0) {
                while( self.cur_arg_ < self.num_args_ && self.bound_[self.cur_arg_] )
                    ++self.cur_arg_;
        }
        return self;
    }

    template<class Ch, class Tr, class Alloc, class T> inline
    basic_format<Ch, Tr, Alloc>&  
    feed (basic_format<Ch,Tr, Alloc>& self, T x) {
        return feed_impl<Ch, Tr, Alloc, const put_holder<Ch, Tr>&>(self, put_holder<Ch, Tr>(x));
    }
    
} // namespace detail
} // namespace io
} // namespace boost


#endif //  BOOST_FORMAT_FEED_ARGS_HPP

/* feed_args.hpp
b1O/KSSQVXcDCqOpfSiMkEEFdiauXNGfyCPBeDlmFdtOgGEJplD4EZwXmghWzWEuVujcdUBf0wEwFDs5zyFaXoEL+yBM9AN7QGxMlyNuzf79ypH2vlVf2nurO9h0EzPVYRL36zg3fas+wPk5RvNTh5dRPo3iqgJk2hOSyIA5wqe/IraUcOdIcCve1AWSCthnx8uYewVCxd4Hfb7/Rh/Sor6XaBEwEDvecLEufWTCVOY35CA74tHZg3SNgKV2NvK3AQlAooiTKNrYK07OVVqBkjjdOjHVSitr4k9+LwSUqxOM84GL4j0e/gp8o1/HYsAd90EHNv0tRSOsmntOxd6sRL7or05nxHcgOotEvih/82eJTNFRy2MavxqAJnL3CpS0io7wIzHavzNom+4w6Kmcus99vn67rjin35SBfhfcpPdbPNDvU/dCvztPx/sVQAcgBiT/vhk6zIHc1xd7EzBbZ+gwv12UgPlThPlzhMnlypiWuJfMIYd4gXJ3ibKwRJldolxboowJ8Qwc5lMPJ4a5VAQjYPWVoSViaPi3tdyya665XP+1rs/OLqUM3bf11svwJUd/od9GyvxvyTdopHcUnDPSfT0D1HPoIx0yMNJF98BIq4AajUmXHOEgp5UoV9HwzDi8NzedZ3jj/n+g3H7FOSgPH0D5uFNH2bswgfKflwHKf+/5bybcfS4Z3jiVgDm1RIeZMgBzPsK8B2HWTSzCXJNb6NNPn7X0uQU/D9Xtxj8Jc7EtNmAurvjL2ed2oMJ1STmxc89XYU7SyZ9J56vwr6QKI89X4cIkk/WbF8+pMBmDAb4ACanT/l/jPvPKPO190BFu/vJ74D7gslOTigMa/yWUL0zOnh4M5OZBQO6OAykZDGT82UDwvq6856Q0SVLkoRhQVJ15Pc48SaqXlPS1pRNwo9bL7+7v09YumYCRV8zZHEg+Pv24nvUVtOBhmltjmjigHc1kznkNfEjP0VCboXLgl6Qw7/fv0AavZb6vCNh6XBeYNdMWdQGEPDYtH0YUWK59sCRcf9+lgRHi4cKeRsorG05HQlDF/Ps+SugbmihIydBPkFCabiLpgG507/LjlbdeEYCBVikwFZi/tOPmONMMOjetu0h863zMTwU3QHWAj9CNUURHK3oS+OMRHHUXkpV+g48OUK/Uf+mUOboLHJ3MFStwtC8UR4gLHF22twvwAHVuJf/uXxnJp5xzkg/hYr/PPoaXQfLBXQ/qjk1ej7/4d4n2fiCPtcDMHmFd/Lt5QHoHx1A361UuDGnGoDGQsjAAHjcSFemIe+ylIS1jVWpIG14DH6bgNGwiA21T8Y60H/ec8PT800udZS+FPvBbvHFmFGvCq9l8IT5EmV6iXF1SoowqUUpYU+IU68U0KvzxCDPoRlev5an6klBbaqg+I3pCL+uybK4P1WdGDya9R2ZKGdHXEo1+Xx8xhXFTP/rMQB6ZIMumR2N4WSH9Bld4v2I+1VikpOvh2VONRuUy1phvsOysFxnG9SG+JtR8gRvvdXPjyVJeCEx3qnGiYgU3lZuAKenXBR/DQrNyPTxfAx0A4GuQZ/DSCs+jeM1uQzQl9JnB4yf7YaUexRM/AXiET0ScHLGFIoev7pBgKFwWvxkb05rSNv90hJW3H6Ntcvz1HL51Y58WegZ/xkvCJH2Qg3ejHHzlZEIOYpP4hl0PcCCjhrjpv/3x+KY/z8vD8x/fZNBPbbEuq5UvBwh+TGzl3ud1N60LOShmb1ZSOV15PP6bjKT0gLVJ8qn8+b6zf/ANU3LxwmvCetjD+j1J9qbgKJ/PL62mg/ctmNUTkPmDDG9bzQWPzMjuy2OuHFZmYj9GsZTnY/eZ2c1ywfe+gsNl5V5MOToIkMlM7F+lL9nceKrF2RdUgMn7S0q4yNGFzY9KcEkG0uarG1EsqaWrbAemi/1/kTegOqtU5xx13WYq2UKfL9An7XOvo9/WoiCf2EVWnUoT3fGERpu6kQ7NUM5nE2X0kyk9cJgC5AKejF+4iRJmf7a2FKSkZGIPIrza+ioXeVcgzdaelrJg0fwI/o6HvxfA3+m4iODvAyDmxtFeT9RMG1vR1FelDEkap3VpWmbDUBoWAaRUIpyR0H1VUsJEjCesWtlwL+sK/SvFi5yMrvIj9BO+DllPFPX6D30PkuIkL3o+Jn4iue072hyYSO/KjxgRCY/NuHnqKEma769CBb0ij/8pG97mCyLqCfpenwB3mp98LhncEf4JvSvZ/JpsgmbWdmE7/jcEwnve7tMKq9wgpdPx7LbIwWIP4ZSALzTUx7fjhX/P0vYHO7KwsqPHD7ykUZJRnqTk8KtO4wEtBXWLGa/JsbLmSu3ni9jhyo4PvbA+9UNN//gqI36o6ZHfA4Q0+rUKPbGLfggljX6g+LCwi+JHm177Pd7v+nV8XXiSL2DV/tqn8dGbUFOJsDDtF47D+b3sw0woQ+7ablRKthuUzPCHynWv4dxF08MfBicEim61fWg7UGhRrgy9dUF5Gf4DyobaYoIp8UjQLXhZcnp0SKJwYfynERN5Vs9gcYw//pA4WaxYxe9FXxDaiF+kRIfRu5Iu3g1i/a4lvAyK0VbfuD0laOa+h2Lih6aVL2E2B87wQA8wzBzcUafxjTNIRdI03M0J5uP9V/rNLZvWEAlpTbI0ujJUHIAZMCIGoL214wegGf7n0NjDtH/hkL09e0nty2yy+9ZRVsNEeEdlNIRNnoPvy0xQYBIFWOGKZXIllMhUko1VrnCb8QZtpZCVrTJY2cP0MwBuE3sYp+oKt8weXk8PZqZin2s/QaRhlSLW00JSenSK3saKALDh+njDNT/Y0BQqMqVXiIuNyMr9IKpLd0qKXqJI/CIMcW3UV0Gal/+hG8hGKUqhZ/BTGogVmhkJNrFOeUcGLKo/vAWLapk7KIcWuaVQyS1xrXDlYuDmmzozBg7qeW2n1InqMtNrKMgKg2ZlSGHQqpjYW9EU2wFVjpcE4yUlpqSDsj42jaM5c9Ivtelpj35D/CnBHng4qXMXnpUZYIdOK53YSxgelvXlMI8eH+cHMH8lAtbQCbda3atWdKkV3Vr2BNwYc3S5xVE3St33aMFutOy6NLeCWqxxVQBGeBC3bg+zFv7iapI6WeETwHRzMTnnIP8yQpLJRNQonko/w6pFjawKgG7FG7R5lTum2fcr+Um/0Gr/QMlmzfzeu/EGq2AGnUowhWbfQgfw2RgkwKo5Cdx66ZL8btqKmfqKnuOfD/azvVcZ7wOb6bj4JflcDPcUTdVPsWHcGQpo36FEQK6+GAuqbtGCGQmavgvLRIvnqdYhzQsdcvBC6vldbLRqKG6xJ1JZF95WmWRG5g6+g8fr89hOgbIKOHFHsoJr2YuABKdm5Bgs4U4K5JE9qQY7gS/VYLeK28dkWzo4A9KXWAuCnayit6CiixVlYczX0W4/rCzoId1Eq87tLisYiusuIJUJi9EM7TESopuqXUStdnj3FkwWFb3nr4X7ewC/UZmjw8c1XMImY1V3QSou5TK3uJ8VbN7BbYFTeMEYrALFnoB0bo2EjXr/ibjljcbEPpwPvKwps57OdZ4iuWXVD5h+96NUsHFWJJKXp5ZirEj80ol+eGaEN/IQmRK0fc9HgM4XWhIY9Q9g2yRr3df+QAw7lsvDxE/QJLTttGHJ2rYygZ7tmz5xwC6dX4RcKfNTYDAFjPMqMa96St2nKFo+/0LXe7t55hN4l/RRm4YMgxcABiz506HhD40fx1Nk1a3CMcHUHfquDe+Wr+ZqdWfcfWnDYOBLZM22M1cbG7NvJ9605e75sAxvydHeFXfl7OYTN8brxL8FmO+idm0rg+9Jwyp0308b1S+G+mBL1geyEudYB1delVDHu/nm34AAe+yLATM1aPZFHGZ2GrH7w9yYHm41RyeFT8HKAoCTFZh3PC0w+Q54oHPby0y8rZAkwRAwTz6eBaRLfRq/HXQJwMnQHrQIJeXHQtWRxelWkB8upl9eHVjuViGZUWEZNGsUj0ers2LaeaFdfA60oaI1NHXL1NY1qO3gG7sMOGQvrDaRWQ5rjhS3pRa0qfQc/jaOpfYiit54kp1DX8RpcoslKOMSru7GlVvdiYsXVhadvrEdK/TmWh7bu92kDAHrIDX0Vlp0eI+jXdqCzl/orYyoMfSWlRnKAxomDogoEXO12o+sSmVHVFcrc7SBFE5ljeACs+r2niZq+WPmzTI4c+zvrE5h76jeLCjOQ4AGpxy9BV5ATSoz2dzegqNXOK3q3K7odVDohsJrmDfHUJplPwoNj6reHCi2UsNSU3QkvBTBSyab213wzhWlZnVuJ5vbaXyHubqMzaEbpIXq3G7V1XubgmveDSJLW5bn5T1Xoh8Ss70Ny4g/9EFG8hVl7kH3ooF7LaiCF8KpLvDn65+TLEjdS8DAAM33baR6x7ZtLHsp8A38hdfmbdu2qY59axfvQ82/TZ3boqRprjrNtVuYGqqjde3iVrJPjIa5h4BIaxe3kRwzXjH3OMkF/spTYkMggvNxoNDVZql9AHljhgwEhalkM0wwp2yGGeaUPUg+jKvT3qA4ywJpbr4gE38rmNPV0coImu4VJhBy/JFMymKO318dSMNyYYUHM/CrHPD9LwZ1F+R4n3D2jh142R8S7jDfflO/Rt+w6noQCWsXczK5wA1rYY7jBY5D7LAbjbdD4Is9OqMfb3hxtGIgpoUdhvLlstvNV0E5SJS1i9tJL1w4qK0GbbVgHffNwB+VapOULNFWg7ZacDeAnUbf7JOU/whVc4lNWwbUVEYJCD7ROfbFs6leq6QM91HPWAjNz9yExe3gZiWaaNQEqvBPbtJ7HeGjHrEUCMUP3IRDWVhZ6OBgXpIWM2TiyIawoWRbzjIVOtrxjQzLWXKho02RnyabcoZZv65uwnvJLIZX/6TyA9v6tB5iLVwewnrE44U+bTLykjaZRjeWVZnZMlPBq3Q7glRwBhzkgNH4jRezAqK5rErWv5rIikwF3weMBWd8+JXx/XJMDvqFwL4o2eQazOAer+0EHqwBs9Oxg1LjJwJihZRNT0eEX0XxUrFbrahXK/apFc3iN2/VCrzQsLDCqvw04tgthKDQHJ2kOfA8MppsakVvXHMQF91HWqELVAJzdMInNc5GHcIcO3rWxckRmdttqWUSJpjPLw8YPJ4ykNaq62VtJzFrnvx/OPv++KbKe/+kTdtQAglQsFPQoqi44kQLShbUIgSqEkwJNDB+zinGXLchnoM4KVBPCz0egqjocFPEqzh35504Uaoglh8jZXChSgdFel3nxe106bRCLYVWzvfz/jznJCng3X19+SM0J895znOeH5/fn/cHm3Uw5EV4FDGMwZpb828v3KkGanz+9nJ7SaG//YXCXR93Zu5MZGk5qr9GCzs01thV/4FMf3tscK7qb9AmuQoZR0CdU1+4S5teU7hT269Ob9Kmb8/cqfobAdwYaOa6QVOL9o0rPX8kz+ckR4LQeoxkCIIX/LXmUDp5KJ3WULK1SQ6M5R5nIdsQBAqA6q/XcmKDMwr/VFhH4l7m/kx/vTrnAINK1oCK+mvVAPJ5mQLpjCfoP0BTuBk8ZAti/MRw3sq2cU52vhnOmxRo/uOT3BSen7Ct/v7H0Fj1ZXCgBZzKGUP2QU3oYBXTKV0etbHAGZGt0mGMPMOa5unElKSoPxCSb6KvdVsvb8lkTtG5gYS9yL3IjVgYTN3O+qczgqx37p22RM0pthT39G1PTrOyWvAaiStT8BqokBPS5jno/r/N7zaERFag+rfLeRVddtBWV0VXBsK1qpDXXdEFervIWdHVi/5f7I4p81FaqbOXe5UXdqvHPuwyiGZrk/JU/xZtUj4tUcy/JaVmREfQfCNU5T//QWJUNpJTAgdKiVpB89gS9x8YCb5PfLy8jfqpQ5Blm35fE+lgNRiMr1Huf9pfT21WSL3i/loGCrpcub+WfpEGEY1KGl57aTSK4snUh1JeZ1v6oFJea5N/Il5FviJd7u8xh9JJw0g8aK6BPCytxyWXoMdAna9kslQSGYEbsXKJPxlyXVqy2/Xpg8jGU6VLezzNnr7cmr9OC+xRx02mR5+ZIZAmTIQT+Q6lfLtNKtDmbDeL7rmEHn81KV5rZsBgvZ2+NXNfZkiqGz7qv44k+cvCuUniUJ48lGYCF+hGTjXQrRiF7if20uO2IfFOMW5Y3F8xvFIfxZgiOX1d7iouNmjXZE8s4Ck1M6rDxtp8IY87Nb+n5Vkb16QXMA15vi6G8nGFkgGYCWJ1c7sNcad1UfV76Bnyj7Qpzo++REBFONf3J3rkIXmS709yf2XZfJt8qzYF/vsrVnhtiXz65XpT5pOHiR+yFyhem3yJOarolESOkAPDemSoiVDU46DWAiiDD85HkPGuihcdL/qkY6dd6k16UI4wJrk6dmZIOUS/M6PFP1L+2q1ye99hyQOzUgj/aI7nLWf1/+fUYVVculPk9Pj2S7302eLSzagmMKdbBH72TddhSEY+qB8ss35iHB5Uv2aHIdGYWrMMDrHfcQDaqZk9GV63YVP6WxiIE6ZcDAMRV/WuZ8/DQIRlzV3NGDocd7YsKlD8Y44rgrp7IGDFtGVO/mYfyDEv2hRHYWcsr2Ln3zPCU7UyZ2F94eGdn2dk7p4ac1QE9ed+1w38MjPwzO+k/zLriELpTX/LBUolYs/iiD2jNtNdVuTZ11bk2eANXWbtEyhc49Ms4sXPpiziNYCy3R211Qx0kgyX+2murSOr/mGSEeTLlD78B+w6kfYv6Nd7X6P7Xj1AF1/BBzBDGG3KmYJFztDatL36rz+F8d5Wcxv6fO8Y+mzkPq9W+jQm+3zgd9meSBBzWW4IUOaZM19toJ+NgfjUp5u9PIBeFnIvzVYvzT176f4B9XJLqpcm9CJMOAPxt97L7Gst+hrGfelWX3qyr9kvOjyR1h+YFZ/Mvk5wX0BFQ0e1x0RH76Oj443oqM3qqK1nR43o6N9THbVyR+e7AYyBuK5HzH4/R78K99tp9dvZs9/ZmLK7Uv22c78XgcA2BuInvY/Zde9e1PVw7tq2yOya/0jN40J0/dW3ya67uetkd/iq72gU3Y1Cd8eOojun1Z1zUc8ZwK7ZmOrOsahHd/iq/7yxp4GazdPzf91lhON+5x9fGlxR1KE7j+SiaA7CG2edPlVM9Chfm+N0b8179MHjz9pt9qLDmW3qdKfv60U6nROTK9e8MaV/smYbglo+idvq6JLvT8szo7kz1aAjXuzsB0km6FKDHjWYZ5ZvMw2EImkb1Wu1co+aU/TJ6cVOgH55AMfZIQ3VRj2fQF0UX47sNku4df1PlyhMjipZJyCCsyq8N9EheAECbTjAS3bqzxuMu9sbSZIBl2onLpLCCEhv+NNkQ2fPhsmScN+PeqyScDddZpaEy/zkztiE+vb0inAeqyKcAZReD5eBk/roV27tYrDRvy3qMpQHaLgCgUqUgkERmB965zoXXxcGduLY9YkBom6bV9Rt+/oXJIndTmvWMt4317noeNHxeYBI/WwNA746tCl5DPvq0Q9cSmrU3DxUh1Ne4JBYrEXLumR1OBRbw6Uevrvn15znuystLQtjYhCqx4EB+hTEn7XRfI/1TnIQa7IbjyIy6g9fdwNO94hZWK1N83fT
*/