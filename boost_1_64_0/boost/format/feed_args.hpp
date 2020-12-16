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
0es7F0v7AKm+WC7qehgHgi/z8gXD7C10wXDrxbhgeIl/wef9N9YaVGcdyu2oNm1i6I8m5FWJ2xmI1rQg4IDImgJO7t38dap3Z6reHb2INAXgYr+64tANv1blx1TwWT12MYdq8znuJYOGQRoOilCVqr6mP+jU9bg38H556Tp4P//9kHvWqJ7LIyWDe/jmRDH813cBUl3Rj4O4GBIxl9XJC2HFuBnq47b+Mi20KzmGicOwIFpeBFnCNIwh7RCkyZ7CwAHfR6txRp05eS3ltjn+2mNU7fOn4XLZl5exBIzmexbIQWaI2XbO2SMPPswb9UtxnSKka77u93DXct9UfcLM1b61Cw7w1dA3Iq5WLXGHyV3KJ3++fuTw31JaRTcYHlfKolG+P9EXfgGcXiP/czV/BZNGGe4DbxwSzn3bTFG03SgmRE88KkqFd1+JOs28OrDT8CHN71ne62AdGr65nys2nNVC/28tfpxT8ONc6Nf/m0cbznq+15anF9Tm/q2w0YE8DyNdCwnMemEvYQ2CWR4IppDBDDLL6/XI7LpKu2td4P5nq/i7SdohSMXv6cq7hEmZt0yiJPNLiuy+OPHKTH6+XME2JCYfIbknIbWFkepJSN0WiNQXcwmpnfh84p7AVcviyw1o789Wbi+7gkTrsf5lsqU8ALRnjikjDwk/RgoPxglqHcuRelC+vojeNkZv0z28LgaglzFX3nq6r1hpyNwobeawlbxLrelzYb+q5+fYVYqznAMr1T9uDxx/p8FI9B2rsU+WYZ8s8NM/c2jNb2B0YSx2jWyt/tow5TR+/ILQe2Ulf4JdVgbg5a3jn12PFtNgd0ZM5wv9t7vV6C3y678VyjH7+43nwHncmjBxrkr+ITBeU2BYb1oPOhKuPCON9v/iKpUe/W6/TkWIVbYnYG+IH2QVK61QQccn3AnvpH6KUcxuEIZvDUcYHkr/rzhg1jy/PGjWGKy4Xn+XmjWL1Vj8MptGoIWh3wdPlN87q8+MFleswxqLIPRW3sljcKaoylkzo8g/a95iTP+0Ss2aJQrTbMCUSzw7qhLOv58QgPPdo6qDc+X95t0iRntEvrB/99CR8/vr3Vz0b/A/ENr+nUB366zQ9u82Vtf+3QqG99KQ0PbvNoZvz6hYgIqbVcn+3Yaw7N+J8p2HBJefJMtX+f2vMMo/h4Un/7wjWP654UgY8jm+/3mH8f7nsPDkkVPuqOT/aVI15IntgvGNlvhWh578+vYqFzk2szDbKi/Tb2QyW8TXBlLH4KX9q9tYXqHOnUyJOJWbV3Kzmd/QMwVe0M7g7fNjTMVWcw8oA6SAxXdI5EhWOcZDjqxVvDGY7bDCHZiJnqZkVEoqRL0B+0lFf0HK5lb7kw/dP0Yn63tu40k4SNz+zzWSiL/jNWvInWrNelStWQ/cQmTUyXOYKdxMFzSVLaxnWRDkT2ok9pBsom1YJdsRYBswx1dbvtvpne0qqu73YPcrkYMlvyV2rgc7N2pejIn6lUZTT7zSgYa1aST2iMwNVOaP5tJYoWFt9GYKjY02SdPwXHxz7TgTJpOTcHb4fDk9e3oAVuTjNsM0H939ZOi6ybSQzCDO5u5LKMLuuzuw+26cGcIM4v6+VZlBfLFvgBnE0r7SNtYTeGt5rFbIshdpyoyZGwu5/nUrQgzfxzOgXGsYjgw2XPUqSUGEa6Vc7SCKzTqcFfPOVxcNScJnz4n5kHiJfNJfzB90qPmO0Pb0Di7lWf+hrvvpp4rMcM5r94qiv9dZkNlHrkpV2X8V+VuNPIc9JRdnYjyeGBTe+hqzNHh9bVZYHX2PN5YEl98/thrr80oubljd14S9n2QvMdo/GBjW/tU4uL5f4PBWnfs=
*/